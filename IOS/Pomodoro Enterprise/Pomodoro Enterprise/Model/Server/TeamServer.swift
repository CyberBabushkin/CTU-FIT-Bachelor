//
//  TeamDAO.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 27/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import Alamofire
import MagicalRecord

class TeamServer {
    
    private let dataPoint = "http://localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.team/"
    
    private let entityName = "Team"
    private let primaryKey = "teamId"
    
    static let shared = TeamServer()
    
    func create(person: PersonCD,
                entity: TeamCD,
                success: @escaping (TeamCD) -> (),
                failure: @escaping (NSError) -> ()) {
        
        Alamofire.request(dataPoint + "create/user/\(person.usersUserId)",
                          method: .post,
                          parameters: entity.export(),
                          encoding: JSONEncoding.default,
                          headers: ["Content-Type" : "application/json"]).responseJSON { response in
                            
                            switch response.result {
                            case .success(let value):
                                guard let valuesArray = [value] as? [[AnyHashable: Any]] else {
                                    failure(ErrorWithDescription.ServerFailure("Team Error", "Couldn't deserialize") as NSError)
                                    return
                                }
                                
                                var val: [TeamCD] = []
                                MagicalRecord.save({ localContext in
                                    val = TeamCD.mr_import(from: valuesArray, in: localContext) as! [TeamCD]
                                    let u = PersonCD.mr_findFirst(byAttribute: "usersUserId",
                                                                  withValue: person.usersUserId,
                                                                  in: localContext)!
                                    for v in val {
                                        v.addToHasMembers(u)
                                    }
                                }, completion: { (saved, error) in
                                    if error == nil {
                                        let languagesOnDefaultContext = val.map { $0.mr_(in: NSManagedObjectContext.mr_default())! }
                                        success(languagesOnDefaultContext[0])
                                    } else {
                                        failure(ErrorWithDescription.ServerFailure("Team Error", error!.localizedDescription) as NSError)
                                    }
                                })
                                
                            case .failure(let err):
                                failure(err as NSError)
                            }
        }
    }
    
    func update(entity: TeamCD,
                success: @escaping (TeamCD) -> (),
                failure: @escaping () -> ()) {
        let data : Parameters = entity.export()
        
        let response = Alamofire.request(dataPoint + "edit/\(entity.teamId)",
            method: .put,
            parameters: data,
            encoding: JSONEncoding.default,
            headers: ["Content-Type" : "application/json"])
            .validate().response
        
        if let r = response {
            if r.statusCode >= 200 && r.statusCode < 300 {
                success(entity)
            } else {
                failure()
            }
        } else {
            success(entity)
        }
        
    }
    
    func delete(entity: TeamCD,
                success: @escaping () -> (),
                failure: @escaping () -> ()) {
        let id = entity.teamId
        
        let response = Alamofire.request(dataPoint + "\(id)",
            method: .delete,
            parameters: nil,
            encoding: JSONEncoding.default,
            headers: ["Content-Type" : "application/json"]).response
        
        
        if let r = response {
            if r.statusCode >= 200 && r.statusCode < 300 {
                MagicalRecord.save({ ctx in entity.mr_deleteEntity(in: ctx) })
                success()
            } else {
                failure()
            }
        } else {
            MagicalRecord.save({ ctx in entity.mr_deleteEntity(in: ctx) })
            success()
        }
    }
    
    func getFromServerForUser(user: PersonCD,
                              success: @escaping (TeamCD?) -> (),
                              failure: @escaping (NSError) -> ()) {
        Alamofire.request(dataPoint + "search/user/\(user.usersUserId)",
            method: .get,
            parameters: nil,
            encoding: JSONEncoding.default,
            headers: ["Content-Type" : "application/json"]).responseJSON { response in
                
                switch response.result {
                case .success(let value):
                    guard let valuesArray = [value] as? [[AnyHashable: Any]] else {
                        failure(ErrorWithDescription.ServerFailure("Team Error", "Couldn't deserialize") as NSError)
                        return
                    }
                    
                    var val: [TeamCD] = []
                    MagicalRecord.save({ localContext in
                        val = TeamCD.mr_import(from: valuesArray, in: localContext) as! [TeamCD]
                        let u = PersonCD.mr_findFirst(byAttribute: "usersUserId",
                                                      withValue: user.usersUserId,
                                                      in: localContext)!
                        for v in val {
                            v.addToHasMembers(u)
                        }
                    }, completion: { (saved, error) in
                        if error == nil {
                            let languagesOnDefaultContext = val.map { $0.mr_(in: NSManagedObjectContext.mr_default())! }
                            success(languagesOnDefaultContext[0])
                        } else {
                            failure(ErrorWithDescription.ServerFailure("Team Error", error!.localizedDescription) as NSError)
                        }
                    })
                    
                case .failure(let err):
                    failure(err as NSError)
                }
        }
    }
    
    func getAllMembers(team: TeamCD,
                       success: @escaping ([PersonCD]) -> (),
                       failure: @escaping (NSError) -> ()) {
        Alamofire.request(dataPoint + "team/\(team.teamId)/members",
            method: .get,
            parameters: nil,
            encoding: JSONEncoding.default,
            headers: ["Content-Type" : "application/json"]).responseJSON { response in
                
                switch response.result {
                case .success(let value):
                    guard let valuesArray = value as? [[AnyHashable: Any]] else {
                        failure(ErrorWithDescription.ServerFailure("Team Members Error", "Couldn't deserialize") as NSError)
                        return
                    }
                    
                    var val: [PersonCD] = []
                    
                    MagicalRecord.save({ localContext in
                        val = PersonCD.mr_import(from: valuesArray, in: localContext) as! [PersonCD]
                        let t = TeamCD.mr_findFirst(byAttribute: "teamId",
                                                    withValue: team.teamId,
                                                    in: localContext)
                        val.forEach { v in
                            v.isMemberOf = t
                        }
                        
                    }, completion: { (saved, error) in
                        if error == nil {
                            let languagesOnDefaultContext = val.map { $0.mr_(in: NSManagedObjectContext.mr_default())! }
                            success(languagesOnDefaultContext)
                        } else {
                            failure(ErrorWithDescription.ServerFailure("Team Error", error!.localizedDescription) as NSError)
                        }
                    })
                    
                    valuesArray.forEach { el in
                        let oneMember = PersonCD.init(entity: PersonCD.mr_entityDescription()!, insertInto: nil)
                        oneMember.name = el["name"] as? String
                        oneMember.familyName = el["familyName"] as? String
                        val.append(oneMember)
                    }
                    
                    success(val)
                    
                case .failure(let err):
                    failure(err as NSError)
                }
        }
    }
    
    func getAllTeams(userId: Int32,
                     success: @escaping (Int32, [TeamCD]) -> (),
                     failure: @escaping (NSError) -> ()) {
        Alamofire.request(dataPoint + "search/all",
            method: .get,
            parameters: nil,
            encoding: JSONEncoding.default,
            headers: ["Content-Type" : "application/json"]).responseJSON { response in
                
                switch response.result {
                case .success(let value):
                    guard let valuesArray = value as? [[AnyHashable: Any]] else {
                        failure(ErrorWithDescription.ServerFailure("Team Error", "Couldn't deserialize") as NSError)
                        return
                    }
                    
                    var val: [TeamCD] = []
                    var suc = true
                    
                    for teamD in valuesArray {
                        if let id = teamD["teamId"] as? Int32, let name = teamD["name"] as? String {
                            let team = TeamCD.init(entity: TeamCD.mr_entityDescription()!, insertInto: nil)
                            team.name = name
                            team.teamId = id
                            val.append(team)
                        } else {
                            suc = false
                            break
                        }
                    }
                    
                    if suc {
                        success(userId, val)
                    } else {
                        failure(ErrorWithDescription.ServerFailure("Team Error", "Couldn't deserialize") as NSError)
                    }
                    
                case .failure(let err):
                    failure(err as NSError)
                }
        }
    }
    
    func add(user: PersonCD,
             toTeamWithName name: String,
             success: @escaping (_ team: TeamCD)->()) {
        Alamofire.request(self.dataPoint + "assign/user/\(user.usersUserId)/team/name/\(name)",
                          method: .put,
                          parameters: nil,
                          encoding: JSONEncoding.default,
                          headers: ["Content-Type" : "application/json"]).responseJSON { response in
                            
                            switch response.result {
                            case .success(let value):
                                guard let valuesArray = [value] as? [[AnyHashable: Any]] else {
                                    return
                                }
                                
                                if let id = valuesArray[0]["teamId"] as? Int32,
                                    let name = valuesArray[0]["name"] as? String {
                                    MagicalRecord.save({ ctx in
                                        let team = TeamCD.mr_createEntity(in: ctx)
                                        team?.teamId = id
                                        team?.name = name
                                    }, completion: { _, _ in
                                        let team = TeamCD.mr_findFirst(byAttribute: "teamId",
                                                                       withValue: id)
                                        success(team!)
                                    })
                                }
                                
                            case .failure(_):
                                return
                            }
        }
    }
    
    func remove(user: PersonCD,
                fromTeamWithName name: String,
                success: @escaping ()->()) {
        let response = Alamofire.request(dataPoint + "team/name/\(name)/user/\(user.usersUserId)",
            method: .delete,
            parameters: nil,
            encoding: JSONEncoding.default,
            headers: ["Content-Type" : "application/json"]).response
        
        if let r = response {
            if r.statusCode >= 200 && r.statusCode < 300 {
                success()
            }
        } else {
            success()
        }
    }
    
    func getAllLocalDicts() -> [[String : Any]] {
        let k = getAllLocal()
        
        return k.map {
            x in x.export()
        }
    }
    
    func getAllLocal() -> [TeamCD] {
        let k = TeamCD.mr_findAll() as! [TeamCD]
        return k
    }
}
