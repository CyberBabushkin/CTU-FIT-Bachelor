//
//  DataStorage.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 26/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import CoreData
import MagicalRecord

class DataStorage {
    
    static let shared = DataStorage()
    
    private init() {
        fetch()
    }
    
    public let user = createFetchController(entityType: UsersCD.self, sortBy: "userId", broadcaster: UsersBroadcaster.shared)
    public let person = createFetchController(entityType: PersonCD.self, sortBy: "usersUserId", broadcaster: PersonBroadcaster.shared)
    public let settings = createFetchController(entityType: SettingsCD.self, sortBy: "personUsersUserId", broadcaster: SettingsBroadcaster.shared)
    
    public var pomodoros = PomodoroCD.mr_fetchAllSorted(by: "pomodoroId",
                                                        ascending: true,
                                                        with: nil,
                                                        groupBy: nil,
                                                        delegate: PomodoroBroadcaster.shared) as! NSFetchedResultsController<PomodoroCD>
    
    public var team = TeamCD.mr_fetchAllSorted(by: "teamId",
                                               ascending: true,
                                               with: nil,
                                               groupBy: nil,
                                               delegate: TeamBroadcaster.shared) as! NSFetchedResultsController<TeamCD>
    
    public var lists = ListCD.mr_fetchAllSorted(by: "listId",
                                                ascending: true,
                                                with: nil,
                                                groupBy: nil,
                                                delegate: ListBroadcaster.shared) as! NSFetchedResultsController<ListCD>
    
    public var tasks = TaskCD.mr_fetchAllSorted(by: "taskId",
                                                ascending: true,
                                                with: nil,
                                                groupBy: nil,
                                                delegate: TaskBroadcaster.shared) as! NSFetchedResultsController<TaskCD>
    
    private class func createFetchController<T: NSManagedObject, P: AbstractBroadcaster>(entityType: T.Type,
                                                                                   sortBy key: String,
                                                                                   broadcaster: P) -> NSFetchedResultsController<T> {
        let ctx = (UIApplication.shared.delegate as! AppDelegate).persistentContainer.viewContext
        let name = entityType.mr_entityName()
        let fetchRequest = NSFetchRequest<T>(entityName: name)
        let sortDescriptor = NSSortDescriptor(key: key, ascending: true)
        fetchRequest.sortDescriptors = [sortDescriptor]
        let fetchedResultsController = NSFetchedResultsController(fetchRequest: fetchRequest,
                                                                  managedObjectContext: ctx,
                                                                  sectionNameKeyPath: nil,
                                                                  cacheName: nil)
        fetchedResultsController.delegate = broadcaster
        return fetchedResultsController
    }
    
    public func fetch() {
        try! self.user.performFetch()
        try! self.person.performFetch()
        try! self.settings.performFetch()
        try! self.pomodoros.performFetch()
        try! self.team.performFetch()
        try! self.lists.performFetch()
        try! self.tasks.performFetch()
    }
}
