//
//  TeamBroadcaster.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 04/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import CoreData

class TeamBroadcaster : AbstractBroadcaster {
    
    static let shared = TeamBroadcaster()
    
    private override init() {}
    
    override func controller(_ controller: NSFetchedResultsController<NSFetchRequestResult>, didChange anObject: Any, at indexPath: IndexPath?, for type: NSFetchedResultsChangeType, newIndexPath: IndexPath?) {
        if let obj = anObject as? TeamCD {
            NotificationCenter.default.post(name: .team, object: obj)
        }
    }
}
