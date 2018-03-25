//
//  SettingsBroadcaster.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 04/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import CoreData

class SettingsBroadcaster : AbstractBroadcaster {
    
    static let shared = SettingsBroadcaster()
    
    private override init() {}
    
    override func controller(_ controller: NSFetchedResultsController<NSFetchRequestResult>, didChange anObject: Any, at indexPath: IndexPath?, for type: NSFetchedResultsChangeType, newIndexPath: IndexPath?) {
        if let obj = anObject as? SettingsCD {
            NotificationCenter.default.post(name: .settings, object: obj)
        }
    }
}
