//
//  PomodoroDAO.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 30/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation

import CoreData
import MagicalRecord

class PomodoroDAO {
    
    static let shared = PomodoroDAO()
    
    private init() { }
    
    func create(forPerson person: PersonCD) -> PomodoroCD? {
        let p = PomodoroCD.mr_createEntity()
        p?.pomodoroId = -1
        if let o = p {
            person.addToPomodoros(o)
        }
        p?.user = person
        
        p?.synced = false
        return p
    }
    
    func delete(settings: SettingsCD) {
        settings.mr_deleteEntity()
    }
    
    func get() -> SettingsCD? {
        let settings = SettingsCD.mr_findAll()
        if let s = settings, s.count == 1 {
            return s[0] as? SettingsCD
        }
        return nil
    }
}
