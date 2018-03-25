//
//  UsersBroadcaster.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 30/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import CoreData



class UsersBroadcaster: AbstractBroadcaster {
    
    static let shared = UsersBroadcaster()
    
    private override init() {super.init()}
    
    override func controller(_ controller: NSFetchedResultsController<NSFetchRequestResult>, didChange anObject: Any, at indexPath: IndexPath?, for type: NSFetchedResultsChangeType, newIndexPath: IndexPath?) {
        if let obj = anObject as? UsersCD {
            NotificationCenter.default.post(name: .users, object: obj)
        }
    }
    
}
