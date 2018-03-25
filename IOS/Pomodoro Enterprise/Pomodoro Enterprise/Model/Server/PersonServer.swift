//
//  PersonDAO.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 21/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import Alamofire
import MagicalRecord

class PersonServer {
    private let dataPoint = "http://localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.person/";
    
    static let shared = PersonServer()
    
    private let entityName = "Person"
    private let primaryKey = "usersUserId"
    
    func create(user: UsersCD,
                entity: PersonCD,
                success: @escaping (PersonCD) -> (),
                failure: @escaping (NSError) -> ()) {
        
        let data = entity.export()
        
        Alamofire.request(dataPoint + "create/user/\(user.userId)",
                          method: .post,
                          parameters: data,
                          encoding: JSONEncoding.default,
                          headers: ["Content-Type" : "application/json"]).responseJSON { response in
                            
                            switch response.result {
                            case .success(let value):
                                guard let valuesArray = [value] as? [[AnyHashable: Any]] else {
                                    failure(ErrorWithDescription.ServerFailure("Person Error", "Couldn't deserialize") as NSError)
                                    return
                                }
                                
                                var val: [PersonCD] = []
                                MagicalRecord.save({ localContext in
                                    val = PersonCD.mr_import(from: valuesArray, in: localContext) as! [PersonCD]
                                    let u = UsersCD.mr_findFirst(byAttribute: "userId",
                                                                 withValue: user.userId,
                                                                 in: localContext)
                                    for v in val {
                                        v.main = true
                                        v.hasCredentials = u
                                    }
                                }, completion: { (saved, error) in
                                    if error == nil {
                                        let languagesOnDefaultContext = val.map { $0.mr_(in: NSManagedObjectContext.mr_default())! }
                                        success(languagesOnDefaultContext[0])
                                    } else {
                                        failure(ErrorWithDescription.ServerFailure("Person Error", error!.localizedDescription) as NSError)
                                    }
                                })
                                
                            case .failure(let err):
                                failure(err as NSError)
                            }
        }
    }
    
    func update(entity: PersonCD,
                success: @escaping (PersonCD) -> (),
                failure: @escaping () -> ()) {
        let data : Parameters = entity.export()
        
        let response = Alamofire.request(dataPoint + "edit/\(entity.usersUserId)",
            method: .put,
            parameters: data,
            encoding: JSONEncoding.default,
            headers: ["Content-Type" : "application/json"])
            .validate().response
        
        if let r = response {
            if r.statusCode >= 200 && r.statusCode < 300 {
                success(entity)
            } else {
                failure()
            }
        } else {
            success(entity)
        }
        
    }
    
    func delete(entity: PersonCD,
                success: @escaping () -> (),
                failure: @escaping () -> ()) {
        let id = entity.usersUserId
        
        let response = Alamofire.request(dataPoint + "delete/\(id)",
            method: .delete,
            parameters: nil,
            encoding: JSONEncoding.default,
            headers: ["Content-Type" : "application/json"]).response
        
        if let r = response {
            if r.statusCode >= 200 && r.statusCode < 300 {
                MagicalRecord.save({ ctx in entity.mr_deleteEntity(in: ctx) })
                success()
            } else {
                failure()
            }
        } else {
            MagicalRecord.save({ ctx in entity.mr_deleteEntity(in: ctx) })
            success()
        }
    }
    
    func getFromServer(user: UsersCD,
                       success: @escaping (PersonCD) -> (),
                       failure: @escaping (NSError) -> ()) {
        Alamofire.request(dataPoint + "\(user.userId)",
                          method: .get,
                          parameters: nil,
                          encoding: JSONEncoding.default,
                          headers: ["Content-Type" : "application/json"]).responseJSON { response in
                            
                            switch response.result {
                            case .success(let value):
                                guard let valuesArray = [value] as? [[AnyHashable: Any]] else {
                                    failure(ErrorWithDescription.ServerFailure("Person Error", "Couldn't deserialize") as NSError)
                                    return
                                }
                                
                                var val: [PersonCD] = []
                                MagicalRecord.save({ localContext in
                                    val = PersonCD.mr_import(from: valuesArray, in: localContext) as! [PersonCD]
                                    let u = user.mr_(in: localContext)
                                    for v in val {
                                        v.main = true
                                        v.hasCredentials = u
                                    }
                                }, completion: { (saved, error) in
                                    if error == nil {
                                        let languagesOnDefaultContext = val.map { $0.mr_(in: NSManagedObjectContext.mr_default())! }
                                        success(languagesOnDefaultContext[0])
                                    } else {
                                        failure(ErrorWithDescription.ServerFailure("Person Error", error!.localizedDescription) as NSError)
                                    }
                                })
                                
                            case .failure(let err):
                                failure(err as NSError)
                            }
        }
    }
    
    func getAllLocalDicts() -> [[String : Any]] {
        let k = getAllLocal()
        
        return k.map {
            x in x.export()
        }
    }
    
    func getAllLocal() -> [PersonCD] {
        let k = PersonCD.mr_findAll() as! [PersonCD]
        return k
    }
}
