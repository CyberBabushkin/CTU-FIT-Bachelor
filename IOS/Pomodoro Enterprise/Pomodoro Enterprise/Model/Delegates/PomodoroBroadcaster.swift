//
//  PomodoroBroadcaster.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 04/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import CoreData

class PomodoroBroadcaster : AbstractBroadcaster {
    
    static let shared = PomodoroBroadcaster()
    
    private override init() {}
    
    override func controller(_ controller: NSFetchedResultsController<NSFetchRequestResult>, didChange anObject: Any, at indexPath: IndexPath?, for type: NSFetchedResultsChangeType, newIndexPath: IndexPath?) {
        if let obj = anObject as? PomodoroCD {
            NotificationCenter.default.post(name: .pomodoro, object: obj)
        }
    }
}
