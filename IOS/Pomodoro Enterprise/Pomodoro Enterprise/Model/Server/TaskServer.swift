//
//  TaskDAO.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 27/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import Alamofire
import MagicalRecord

class TaskServer {
    
    private let dataPoint = "http://localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.task/"
    
    static let shared = TaskServer()
    
    private let entityName = "Task"
    private let primaryKey = "taskId"
    
    func create(list: ListCD,
                entity: TaskCD,
                success: @escaping ([TaskCD]) -> (),
                failure: @escaping (NSError) -> ()) {
        
        Alamofire.request(dataPoint + "create/list/\(list.listId)",
                          method: .post,
                          parameters: entity.export(),
                          encoding: JSONEncoding.default,
                          headers: ["Content-Type" : "application/json"]).responseJSON { response in
                            
                            switch response.result {
                            case .success(let value):
                                guard let valuesArray = [value] as? [[AnyHashable: Any]] else {
                                    failure(ErrorWithDescription.ServerFailure("Task Error", "Couldn't deserialize") as NSError)
                                    return
                                }
                                
                                var val: [TaskCD] = []
                                MagicalRecord.save({ localContext in
                                    val = TaskCD.mr_import(from: valuesArray, in: localContext) as! [TaskCD]
                                    let t = ListCD.mr_findFirst(byAttribute: "listId",
                                                                withValue: list.listId,
                                                                in: localContext)
                                    val.forEach { v in
                                        v.list = t
                                    }
                                }, completion: { (saved, error) in
                                    if error == nil {
                                        let languagesOnDefaultContext = val.map { $0.mr_(in: NSManagedObjectContext.mr_default())! }
                                        success(languagesOnDefaultContext)
                                    } else {
                                        failure(ErrorWithDescription.ServerFailure("Task Error", error!.localizedDescription) as NSError)
                                    }
                                })
                                
                            case .failure(let err):
                                failure(err as NSError)
                            }
        }
    }
    
    func update(entity: TaskCD,
                success: @escaping (TaskCD) -> (),
                failure: @escaping () -> ()) {
        let data : Parameters = entity.export()
        
        let response = Alamofire.request(dataPoint + "edit/\(entity.taskId)",
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
    
    func delete(entity: TaskCD,
                success: @escaping () -> (),
                failure: @escaping () -> ()) {
        let id = entity.taskId
        
        let response = Alamofire.request(dataPoint + "delete/\(id)",
            method: .delete,
            parameters: nil,
            encoding: JSONEncoding.default,
            headers: ["Content-Type" : "application/json"]).response
        
        
        if let r = response {
            if r.statusCode >= 200 && r.statusCode < 300 {
                success()
            } else {
                failure()
            }
        } else {
            success()
        }
    }
    
    func getAllFromServer(list: ListCD,
                          success: @escaping (ListCD, [TaskCD]) -> (),
                          failure: @escaping (NSError) -> ()) {
        Alamofire.request(dataPoint + "search/list/\(list.listId)",
            method: .get,
            parameters: nil,
            encoding: JSONEncoding.default,
            headers: ["Content-Type" : "application/json"]).responseJSON { response in
                
                switch response.result {
                case .success(let value):
                    guard let valuesArray = value as? [[AnyHashable: Any]] else {
                        failure(ErrorWithDescription.ServerFailure("Task Error", "Couldn't deserialize") as NSError)
                        return
                    }
                    
                    for var t in valuesArray {
                        t["listId"] = list.listId
                    }
                    
                    var val: [TaskCD] = []
                    MagicalRecord.save({ localContext in
                        val = TaskCD.mr_import(from: valuesArray, in: localContext) as! [TaskCD]
                        let t = ListCD.mr_findFirst(byAttribute: "listId",
                                                    withValue: list.listId,
                                                    in: localContext)
                        val.forEach { v in
                            v.list = t
                        }
                    }, completion: { (saved, error) in
                        if error == nil {
                            let languagesOnDefaultContext = val.map { $0.mr_(in: NSManagedObjectContext.mr_default())! }
                            success(list, languagesOnDefaultContext)
                        } else {
                            failure(ErrorWithDescription.ServerFailure("Task Error", error!.localizedDescription) as NSError)
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
    
    func getAllLocal() -> [TaskCD] {
        let k = TaskCD.mr_findAll() as! [TaskCD]
        return k
    }
}
