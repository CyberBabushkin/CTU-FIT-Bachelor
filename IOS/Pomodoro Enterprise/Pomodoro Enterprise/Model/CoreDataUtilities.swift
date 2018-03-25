//
//  Communication.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 21/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import UIKit
import CoreData
import Sync
import MagicalRecord

open class CoreDataUtilities {
    
    static var u: UsersCD?
    static var p: PersonCD?
    static var t: TeamCD?
    static var l: ListCD?
    
    public class func purgeCoreData(competion: @escaping () -> ()) {
        MagicalRecord.save({ ctx in
            let pred = NSPredicate(value: true)
            UsersCD.mr_deleteAll(matching: pred, in: ctx)
            PersonCD.mr_deleteAll(matching: pred, in: ctx)
            SettingsCD.mr_deleteAll(matching: pred, in: ctx)
            PomodoroCD.mr_deleteAll(matching: pred, in: ctx)
            TeamCD.mr_deleteAll(matching: pred, in: ctx)
            ListCD.mr_deleteAll(matching: pred, in: ctx)
            TaskCD.mr_deleteAll(matching: pred, in: ctx)
        }, completion: { (_,_) in competion() })
    }
    
    // MARK: - Data downloading
    
    open class func downloadUserData(withUsername username: String, andPassword pass: String) {
        purgeCoreData(competion: {UsersServer.shared.login(username: username,
                                                           password: pass,
                                                           success: gotUser(_:),
                                                           failure: { err in
                                                            print("Error fetching users")
                                                            print(err) })})
    }
    
    class func gotUser(_ user: UsersCD) {
        PersonServer.shared.getFromServer(user: user,
                                          success: gotPerson(_:),
                                          failure: { err in
                                            print("Error fetching person")
                                            print(err) })
        u = user
    }
    
    class func gotPerson(_ person: PersonCD) {
        p = person
        
        SettingsServer.shared.getFromServer(person: person,
                                            success: gotSettings(_:),
                                            failure: { err in
                                                print("Error fetching settings")
                                                print(err) })
        PomodoroServer.shared.getAllFromServer(person: person,
                                               success: gotPomodoros(_:),
                                               failure: { err in
                                                print("Error fetching pomodoros")
                                                print(err)})
        downloadTeam(person)
    }
    
    class func downloadTeam(_ person: PersonCD) {
        MagicalRecord.save({ ctx in
            TeamCD.mr_deleteAll(matching: NSPredicate(value: true), in: ctx)
            ListCD.mr_deleteAll(matching: NSPredicate(value: true), in: ctx)
            TaskCD.mr_deleteAll(matching: NSPredicate(value: true), in: ctx)
        }, completion: { _, _ in
            TeamServer.shared.getFromServerForUser(user: person,
                                                   success: gotTeam(_:),
                                                   failure: { err in
                                                    print("Error fetching team")
                                                    print(err)})
        })
    }
    
    class func gotSettings(_ settings: SettingsCD) {
        print("Got settings")
    }
    
    class func gotPomodoros(_ pom: [PomodoroCD]) {
        print("Got pomodoros")
    }
    
    class func gotTeam(_ team: TeamCD?) {
        if let t = team {
            self.t = t
            ListServer.shared.getAllFromServer(team: t,
                                               success: gotLists(_:),
                                               failure: { err in
                                                print("Error fetching lists")
                                                print(err)
            })
        }
    }
    
    class func gotLists(_ lists: [ListCD]) {
        lists.forEach { l in
            TaskServer.shared.getAllFromServer(list: l,
                                               success: gotTasks(_:_:),
                                               failure: { err in
                                                print("Error fetching tasks for list with id \(l.listId)")
                                                print(err)
            })
        }
    }
    
    class func gotTasks(_ list: ListCD, _ tasks: [TaskCD]) {
        print("Got tasks")
    }
    
    // MARK: - Registration
    static var ptmp: PersonCD?
    
    open class func register(withLogin login: String,
                             password: String,
                             name: String,
                             andFamilyName surname: String) {
        purgeCoreData(competion: {
            let utmp = UsersCD.init(entity: UsersCD.mr_entityDescription()!, insertInto: nil)
            utmp.userId = -1
            utmp.login = login
            utmp.password = password
            ptmp = PersonCD.init(entity: PersonCD.mr_entityDescription()!, insertInto: nil)
            ptmp?.usersUserId = -1
            ptmp?.name = name
            ptmp?.familyName = surname
            ptmp?.avatar = ImageUtilities.imageToBase64(image:
                ImageUtilities.resizeImage(image: #imageLiteral(resourceName: "avatar"), targetSize: CGSize(width: 64, height: 64)))
            UsersServer.shared.create(entity: utmp,
                                      success: userCreated(_:),
                                      failure: { e in
                                        print("Failed to create Users")
                                        print(e.description)
            })
        })
    }
    
    class func userCreated(_ user: UsersCD) {
        PersonServer.shared.create(user: user,
                                   entity: ptmp!,
                                   success: personCreated(_:),
                                   failure: { e in
                                    print("Failed to create Person")
                                    print(e.description)
        })
        ptmp = nil
    }
    
    class func personCreated(_ person: PersonCD) {
        let stmp = SettingsCD.init(entity: SettingsCD.mr_entityDescription()!, insertInto: nil)
        stmp.breakTime = 5
        stmp.pomodoroGoal = 20
        stmp.pomodoroTime = 30
        stmp.taskGoal = 20
        SettingsServer.shared.create(person: person,
                                     entity: stmp,
                                     success: {s in},
                                     failure: { e in
                                        print("Failed to create Settings")
                                        print(e.description)
        })
    }
    
    class func failure(desc: String, error: NSError) throws {
        throw ErrorWithDescription.ServerFailure(desc, error.description)
    }
    
    // MARK: - List methods
    
    class func createList(withName title: String, team: TeamCD) {
        let ltmp = ListCD.init(entity: ListCD.mr_entityDescription()!, insertInto: nil)
        ltmp.title = title
        ListServer.shared.create(team: team,
                                 entity: ltmp,
                                 success: { s in },
                                 failure: { err in print("Error creating list")})
    }
    
    class func remove(list: ListCD,
                      success: @escaping () -> (),
                      failure: @escaping () -> ()) {
        MagicalRecord.save({ ctx in
            for t in list.tasks ?? NSSet() {
                let task = t as! TaskCD
                task.mr_deleteEntity(in: ctx)
            }
            
            ListServer.shared.delete(entity: list, success: success, failure: failure)
            list.mr_deleteEntity(in: ctx)
        })
        
    }
    
    // MARK: - Task methods
    
    class func createTask(withName name: String,
                          info: String?,
                          dateFinish date: Date?,
                          list: ListCD,
                          success: @escaping ()->()) {
        let ttmp = TaskCD.init(entity: TaskCD.mr_entityDescription()!, insertInto: nil)
        ttmp.name = name
        ttmp.info = info
        ttmp.dateFinish = date
        
        TaskServer.shared.create(list: list,
                                 entity: ttmp,
                                 success: { _ in
                                    success()
        },
                                 failure: { err in print("Error creating task")})
    }
    
    class func remove(task: TaskCD,
                      success: @escaping () -> (),
                      failure: @escaping () -> ()) {
        MagicalRecord.save({ ctx in
            TaskServer.shared.delete(entity: task, success: success, failure: failure)
            task.mr_deleteEntity(in: ctx)
        })
    }
    
    class func update(task: TaskCD,
                      success: @escaping (TaskCD) -> (),
                      failure: @escaping () -> ()) {
        MagicalRecord.save({ ctx in
            TaskServer.shared.update(entity: task, success: success, failure: failure)
            task.mr_(in: ctx)
        })
    }
    
    // MARK: - Pomodoro creation
    
    class func createPomodoro(user: PersonCD,
                              date: Date,
                              success: @escaping ()->()) {
        let ptmp = PomodoroCD.init(entity: PomodoroCD.mr_entityDescription()!, insertInto: nil)
        ptmp.pdate = date
        
        PomodoroServer.shared.create(person: user,
                                     entity: ptmp,
                                     success: { _ in success() },
                                     failure: { err in print("Error creating pomodoro")})
    }
    
    // MARK: - Team methods
    
    class func createTeam(user: PersonCD,
                          name: String,
                          success: @escaping ()->()) {
        let ttmp = TeamCD.init(entity: TeamCD.mr_entityDescription()!, insertInto: nil)
        ttmp.name = name
        
        TeamServer.shared.create(person: user,
                                 entity: ttmp,
                                 success: { t in
                                    gotTeam(t)
                                    success() },
                                 failure: { err in print("Error creating team")})
    }
    
    class func assign(teamName: String,
                      toUser user: PersonCD) {
        TeamServer.shared.add(user: user, toTeamWithName: teamName, success: { team in
            MagicalRecord.save({ ctx in
                let t = TeamCD.mr_findFirst(byAttribute: "teamId",
                                            withValue: team.teamId,
                                            in: ctx)
                let p = user.mr_(in: ctx)!
                p.isMemberOf = t
                t?.addToHasMembers(p)
                
                gotTeam(t)
            })
        })
    }
    
    class func remove(user: PersonCD,
                      from team: TeamCD,
                      inContext ctx: NSManagedObjectContext,
                      success: @escaping ()->()) {
        let team = TeamCD.mr_findFirst(byAttribute: "teamId", withValue: team.teamId, in: ctx)!
        let person = PersonCD.mr_findFirst(byAttribute: "usersUserId", withValue: user.usersUserId, in: ctx)!
        
        person.isMemberOf = nil
        
        TeamServer.shared.remove(user: person, fromTeamWithName: team.name!, success: success)
        
        MagicalRecord.save({ ctx in
            TeamCD.mr_deleteAll(matching: NSPredicate(value: true), in: ctx)
            ListCD.mr_deleteAll(matching: NSPredicate(value: true), in: ctx)
            TaskCD.mr_deleteAll(matching: NSPredicate(value: true), in: ctx)
            PersonCD.mr_deleteAll(matching: NSPredicate(format: "main = false"), in: ctx)
        })
    }
}

enum ErrorWithDescription: Error {
    case ServerFailure(String, String)
}
