//
//  AbstractBroadcaster.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 03/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import CoreData

extension Notification.Name {
    static let users = Notification.Name("users")
    static let person = Notification.Name("person")
    static let settings = Notification.Name("settings")
    static let pomodoro = Notification.Name("pomodoro")
    static let team = Notification.Name("team")
    static let list = Notification.Name("list")
    static let task = Notification.Name("task")
}

class AbstractBroadcaster: NSObject, NSFetchedResultsControllerDelegate {
    
    override init() {
        super.init()
        NotificationCenter.default.addObserver(self,
                                               selector: #selector(gotNotification),
                                               name: NSNotification.Name.NSManagedObjectContextDidSave,
                                               object: nil)
    }
    
    @objc func gotNotification() {
        DataStorage.shared.fetch()
    }
    
    func controller(_ controller: NSFetchedResultsController<NSFetchRequestResult>, didChange anObject: Any, at indexPath: IndexPath?, for type: NSFetchedResultsChangeType, newIndexPath: IndexPath?) {
        preconditionFailure("This method must be overridden") 
    }
}
