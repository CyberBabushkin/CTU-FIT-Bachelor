//
//  TaskBroadcaster.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 04/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import CoreData

class TaskBroadcaster : AbstractBroadcaster {
    
    static let shared = TaskBroadcaster()
    
    private override init() {}
    
    override func controller(_ controller: NSFetchedResultsController<NSFetchRequestResult>, didChange anObject: Any, at indexPath: IndexPath?, for type: NSFetchedResultsChangeType, newIndexPath: IndexPath?) {
        if let obj = anObject as? TaskCD {
            NotificationCenter.default.post(name: .task, object: obj)
        }
    }
}
