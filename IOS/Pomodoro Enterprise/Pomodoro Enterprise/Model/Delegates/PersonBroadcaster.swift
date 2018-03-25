//
//  PersonBroadcaster.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 03/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import CoreData

class PersonBroadcaster : AbstractBroadcaster {
    
    static let shared = PersonBroadcaster()
    
    private override init() {}
    
    override func controller(_ controller: NSFetchedResultsController<NSFetchRequestResult>, didChange anObject: Any, at indexPath: IndexPath?, for type: NSFetchedResultsChangeType, newIndexPath: IndexPath?) {
        if let obj = anObject as? PersonCD {
            NotificationCenter.default.post(name: .person, object: obj)
        }
    }
}
