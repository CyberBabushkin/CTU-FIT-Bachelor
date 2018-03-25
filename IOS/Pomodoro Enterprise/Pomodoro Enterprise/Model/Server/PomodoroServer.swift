//
//  PomodoroDAO.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 27/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import Alamofire
import MagicalRecord

class PomodoroServer {
    
    private let dataPoint = "http://localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.pomodoro/"
    
    private let entityName = "Pomodoro"
    private let primaryKey = "pomodoroId"
    
    static let shared = PomodoroServer()
    
    func create(person: PersonCD,
                entity: PomodoroCD,
                success: @escaping ([PomodoroCD]) -> (),
                failure: @escaping (NSError) -> ()) {
        
        Alamofire.request(dataPoint + "create/user/\(person.usersUserId)",
                          method: .post,
                          parameters: entity.export(),
                          encoding: JSONEncoding.default,
                          headers: ["Content-Type" : "application/json"]).responseJSON { response in
                            
                            switch response.result {
                            case .success(let value):
                                guard let valuesArray = [value] as? [[AnyHashable: Any]] else {
                                    failure(ErrorWithDescription.ServerFailure("Pomodoro Error", "Couldn't deserialize") as NSError)
                                    return
                                }
                                
                                var val: [PomodoroCD] = []
                                MagicalRecord.save({ localContext in
                                    val = PomodoroCD.mr_import(from: valuesArray, in: localContext) as! [PomodoroCD]
                                    let u = PersonCD.mr_findFirst(byAttribute: "usersUserId",
                                                                  withValue: person.usersUserId,
                                                                  in: localContext)
                                    for v in val {
                                        v.user = u
                                    }
                                }, completion: { (saved, error) in
                                    if error == nil {
                                        let languagesOnDefaultContext = val.map { $0.mr_(in: NSManagedObjectContext.mr_default())! }
                                        success(languagesOnDefaultContext)
                                    } else {
                                        failure(ErrorWithDescription.ServerFailure("Pomodoro Error", error!.localizedDescription) as NSError)
                                    }
                                })
                                
                            case .failure(let err):
                                failure(err as NSError)
                            }
        }
    }
    
    func update(entity: PomodoroCD,
                success: @escaping (PomodoroCD) -> (),
                failure: @escaping () -> ()) {
        let data : Parameters = entity.export()
        
        let response = Alamofire.request(dataPoint + "edit/\(entity.pomodoroId)",
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
    
    func delete(entity: PomodoroCD,
                success: @escaping () -> (),
                failure: @escaping () -> ()) {
        let id = entity.pomodoroId
        
        let response = Alamofire.request(dataPoint + "delete\(id)",
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
    
    func getAllFromServer(person: PersonCD,
                          success: @escaping ([PomodoroCD]) -> (),
                          failure: @escaping (NSError) -> ()) {
        Alamofire.request(dataPoint + "search/user/\(person.usersUserId)",
                          method: .get,
                          parameters: nil,
                          encoding: JSONEncoding.default,
                          headers: ["Content-Type" : "application/json"]).responseJSON { response in
                            
                            switch response.result {
                            case .success(let value):
                                guard let valuesArray = value as? [[AnyHashable: Any]] else {
                                    failure(ErrorWithDescription.ServerFailure("Pomodoro Error", "Couldn't deserialize") as NSError)
                                    return
                                }
                                
                                var val: [PomodoroCD] = []
                                MagicalRecord.save({ localContext in
                                    val = PomodoroCD.mr_import(from: valuesArray, in: localContext) as! [PomodoroCD]
                                    let u = PersonCD.mr_findFirst(byAttribute: "usersUserId",
                                                                  withValue: person.usersUserId,
                                                                  in: localContext)
                                    for v in val {
                                        v.user = u
                                    }
                                }, completion: { (saved, error) in
                                    if error == nil {
                                        let languagesOnDefaultContext = val.map { $0.mr_(in: NSManagedObjectContext.mr_default())! }
                                        success(languagesOnDefaultContext)
                                    } else {
                                        failure(ErrorWithDescription.ServerFailure("Pomodoro Error", error!.localizedDescription) as NSError)
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
    
    func getAllLocal() -> [PomodoroCD] {
        let k = PomodoroCD.mr_findAll() as! [PomodoroCD]
        return k
    }
}
