//
//  UsersDAO.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 30/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import CoreData
import MagicalRecord

class UsersDAO {
    
    static let shared = UsersDAO()
    
    private init() { }
    
    func create(username: String, password: String) -> UsersCD? {
        let user = UsersCD()
        user.userId = -1
        user.login = username
        user.password = password
        return user
    }
    
    func delete(user: UsersCD) {
        user.mr_deleteEntity()
    }
    
    func get() -> UsersCD? {
        let users = UsersCD.mr_findAll()
        if let u = users, u.count == 1 {
            return u[0] as? UsersCD
        }
        return nil
    }
}
