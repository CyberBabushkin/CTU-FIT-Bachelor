//
//  ListDAO.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 30/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import CoreData
import MagicalRecord

class ListDAO {
    
    static let shared = ListDAO()
    
    private init() { }
    
    func create(forTeam t: TeamCD, listName name: String) -> ListCD? {
        let l = ListCD.mr_createEntity()
        l?.listId = -1
        l?.title = name
        
        t.addToLists(l!)
        l?.team = t
        l?.synced = false
        
        return l
    }
    
    func delete(list: ListCD) {
        list.mr_deleteEntity()
    }
    
    func get(forTeam t: TeamCD) -> [ListCD]? {
        if let ls = t.lists {
            return ls.map { x in x as! ListCD }
        }
        return nil
    }
}
