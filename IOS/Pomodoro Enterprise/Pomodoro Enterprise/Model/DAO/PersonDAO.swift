//
//  PersonDAO.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 30/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation

import CoreData
import MagicalRecord

class PersonDAO {
    
    static let shared = PersonDAO()
    
    private init() { }
    
    func create(forUser user: UsersCD, name: String, surname: String) -> PersonCD? {
        let person = PersonCD.mr_createEntity()
        person?.usersUserId = -1
        person?.name = name
        person?.familyName = surname
        
        user.isDescribedBy = person!
        person?.hasCredentials = user
        person?.synced = false
        
        return person
    }
    
    func delete(person: PersonCD) {
        person.mr_deleteEntity()
    }
    
    func get() -> PersonCD? {
        let persons = PersonCD.mr_findAll()
        if let p = persons, p.count == 1 {
            return p[0] as? PersonCD
        }
        return nil
    }
}
