//
//  UsersDAO.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 21/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import Alamofire
import MagicalRecord

public let ctx = (UIApplication.shared.delegate as! AppDelegate).persistentContainer.viewContext

extension String {
    func convertToDictionary() -> [String: Any]? {
        if let data = self.data(using: .utf8) {
            do {
                return try JSONSerialization.jsonObject(with: data, options: []) as? [String: Any]
            } catch {
                print(error.localizedDescription)
            }
        }
        return nil
    }
}

class UsersServer {
    private let dataPoint = "http://localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.users/";
    
    static let shared = UsersServer()
    private let entityName = "Users"
    private let primaryKey = "userId"
    
    func login(username: String,
               password: String,
               success: @escaping (UsersCD) -> (),
               failure: @escaping (NSError) -> ()) {
        Alamofire.request(dataPoint + "login/username/\(username)/password/\(password)",
                          method: .get,
                          parameters: nil,
                          encoding: JSONEncoding.default,
                          headers: ["Content-Type" : "application/json"]).responseJSON { response in
                            
                            switch response.result {
                            case .success(let value):
                                guard let valuesArray = [value] as? [[AnyHashable: Any]] else {
                                    failure(ErrorWithDescription.ServerFailure("Users Error", "Couldn't deserialize") as NSError)
                                    return
                                }
                                
                                var val: [UsersCD] = []
                                MagicalRecord.save({ localContext in
                                    val = UsersCD.mr_import(from: valuesArray, in: localContext) as! [UsersCD]
                                }, completion: { (saved, error) in
                                    if error == nil {
                                        let languagesOnDefaultContext = val.map { $0.mr_(in: NSManagedObjectContext.mr_default())! }
                                        success(languagesOnDefaultContext[0])
                                    } else {
                                        failure(ErrorWithDescription.ServerFailure("Some Error", error!.localizedDescription) as NSError)
                                    }
                                })
                                
                            case .failure(let err):
                                failure(err as NSError)
                            }
        }
    }
    
    func create(entity: UsersCD,
                success: @escaping (UsersCD) -> (),
                failure: @escaping (NSError) -> ()) {
        let data = entity.export()
        
        Alamofire.request(dataPoint + "create",
                          method: .post,
                          parameters: data,
                          encoding: JSONEncoding.default,
                          headers: ["Content-Type" : "application/json"]).responseJSON { response in
                            
                            switch response.result {
                            case .success(let value):
                                guard let valuesArray = [value] as? [[AnyHashable: Any]] else {
                                    failure(ErrorWithDescription.ServerFailure("Users Error", "Couldn't deserialize") as NSError)
                                    return
                                }
                                
                                var val: [UsersCD] = []
                                MagicalRecord.save({ localContext in
                                    val = UsersCD.mr_import(from: valuesArray, in: localContext) as! [UsersCD]
                                }, completion: { (saved, error) in
                                    if error == nil {
                                        let languagesOnDefaultContext = val.map { $0.mr_(in: NSManagedObjectContext.mr_default())! }
                                        success(languagesOnDefaultContext[0])
                                    } else {
                                        failure(ErrorWithDescription.ServerFailure("Users Error", error!.localizedDescription) as NSError)
                                    }
                                })
                                
                            case .failure(let err):
                                failure(err as NSError)
                            }
        }
    }
    
    func update(entity: UsersCD,
                success: @escaping (UsersCD) -> (),
                failure: @escaping () -> ()) {
        let data : Parameters = entity.export()
        
        let response = Alamofire.request(dataPoint + "edit/\(entity.userId)",
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
    
    func delete(entity: UsersCD,
                success: @escaping () -> (),
                failure: @escaping () -> ()) {
        let id = entity.userId
        
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
    
    func findLocalByUsername(username: String) -> UsersCD? {
        let users = getAllLocal()
        
        for u in users {
            if (u.login == username) {
                return u
            }
        }
        
        return nil
    }
    
    func getAllLocalDicts() -> [[String : Any]] {
        let k = getAllLocal()
        
        return k.map {
            x in x.export()
        }
    }
    
    func getAllLocal() -> [UsersCD] {
        let k = UsersCD.mr_findAll() as! [UsersCD]
        return k
    }
}
