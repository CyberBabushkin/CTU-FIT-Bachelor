//
//  TaskDAO.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 30/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import CoreData
import MagicalRecord

class TaskDAO {
    
    static let shared = TaskDAO()
    
    private init() { }
    
    func create(forList l: ListCD,
                taskName name: String,
                taskInfo info: String?) -> TaskCD? {
        let t = TaskCD.mr_createEntity()
        t?.taskId = -1
        t?.name = name
        t?.info = info
        
        l.addToTasks(t!)
        t?.list = l
        t?.synced = false
        
        return t
    }
    
    func delete(task: TaskCD) {
        task.mr_deleteEntity()
    }
    
    func get(forList l: ListCD) -> [TaskCD]? {
        if let ts = l.tasks {
            return ts.map { x in x as! TaskCD }
        }
        return nil
    }
}
