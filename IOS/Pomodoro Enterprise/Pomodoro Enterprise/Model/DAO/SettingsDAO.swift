//
//  SettingsDAO.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 30/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import CoreData
import MagicalRecord

class SettingsDAO {
    
    static let shared = SettingsDAO()
    
    private init() { }
    
    func create(forPerson p: PersonCD) -> SettingsCD? {
        return create(forPerson:p, breakTime: 5, pomodoroTime: 25, pomodoroGoal: 15, taskGoal: 25)
    }
    
    func create(forPerson p: PersonCD, breakTime: Int32, pomodoroTime: Int32, pomodoroGoal: Int32, taskGoal: Int32) -> SettingsCD? {
        let s = SettingsCD.mr_createEntity()
        s?.personUsersUserId = -1
        s?.breakTime = breakTime
        s?.pomodoroGoal = pomodoroGoal
        s?.pomodoroTime = pomodoroTime
        s?.taskGoal = taskGoal
        
        p.settings = s
        s?.user = p
        
        s?.synced = false

        return s
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
