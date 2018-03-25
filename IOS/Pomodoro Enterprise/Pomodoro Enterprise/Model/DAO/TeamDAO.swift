//
//  TeamDAO.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 30/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import CoreData
import MagicalRecord

class TeamDAO {
    
    static let shared = TeamDAO()
    
    private init() { }
    
    func create(forPerson p: PersonCD, teamName name: String) -> TeamCD? {
        let t = TeamCD.mr_createEntity()
        t?.teamId = -1
        t?.name = name
        
        t?.addToHasMembers(p)
        p.isMemberOf = t
        t?.synced = false
        
        return t
    }
    
    func delete(team: TeamCD) {
        team.mr_deleteEntity()
    }
    
    func get(forPerson p: PersonCD) -> TeamCD? {
        return p.isMemberOf
    }
}
