//
//  ListDAO.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 19/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import Alamofire
import MagicalRecord

class ListServer {
    
    private let dataPoint = "http://localhost:8080/PomodoroEnterpriseServer-war/webresources/babusand.db.list/"
    
    static let shared = ListServer()
    
    private let entityName = "List"
    private let primaryKey = "listId"
    
    func create(team: TeamCD,
                entity: ListCD,
                success: @escaping ([ListCD]) -> (),
                failure: @escaping (NSError) -> ()) {
        
        Alamofire.request(dataPoint + "create/team/\(team.teamId)",
                          method: .post,
                          parameters: entity.export(),
                          encoding: JSONEncoding.default,
                          headers: ["Content-Type" : "application/json"]).responseJSON { response in
                            
                            switch response.result {
                            case .success(let value):
                                guard let valuesArray = [value] as? [[AnyHashable: Any]] else {
                                    failure(ErrorWithDescription.ServerFailure("List Error", "Couldn't deserialize") as NSError)
                                    return
                                }
                                
                                var val: [ListCD] = []
                                MagicalRecord.save({ localContext in
                                    val = ListCD.mr_import(from: valuesArray, in: localContext) as! [ListCD]
                                    let t = TeamCD.mr_findFirst(byAttribute: "teamId",
                                                                withValue: team.teamId,
                                                                in: localContext)
                                    val.forEach { v in
                                        v.team = t
                                    }
                                }, completion: { (saved, error) in
                                    if error == nil {
                                        let languagesOnDefaultContext = val.map { $0.mr_(in: NSManagedObjectContext.mr_default())! }
                                        success(languagesOnDefaultContext)
                                    } else {
                                        failure(ErrorWithDescription.ServerFailure("List Error", error!.localizedDescription) as NSError)
                                    }
                                })
                                
                            case .failure(let err):
                                failure(err as NSError)
                            }
        }
    }
    
    func update(entity: ListCD,
                success: @escaping (ListCD) -> (),
                failure: @escaping () -> ()) {
        let data : Parameters = entity.export()
        
        let response = Alamofire.request(dataPoint + "edit/\(entity.listId)",
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
    
    func delete(entity: ListCD,
                success: @escaping () -> (),
                failure: @escaping () -> ()) {
        let id = entity.listId
        
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
    
    func getAllFromServer(team: TeamCD,
                          success: @escaping ([ListCD]) -> (),
                          failure: @escaping (NSError) -> ()) {
        Alamofire.request(dataPoint + "search/team/\(team.teamId)",
            method: .get,
            parameters: nil,
            encoding: JSONEncoding.default,
            headers: ["Content-Type" : "application/json"]).responseJSON { response in
                
                switch response.result {
                case .success(let value):
                    guard let valuesArray = value as? [[AnyHashable: Any]] else {
                        failure(ErrorWithDescription.ServerFailure("List Error", "Couldn't deserialize") as NSError)
                        return
                    }
                    
                    var val: [ListCD] = []
                    MagicalRecord.save({ localContext in
                        val = ListCD.mr_import(from: valuesArray, in: localContext) as! [ListCD]
                        let t = team.mr_(in: localContext)
                        val.forEach { v in
                            v.team = t
                        }
                    }, completion: { (saved, error) in
                        if error == nil {
                            let languagesOnDefaultContext = val.map { $0.mr_(in: NSManagedObjectContext.mr_default())! }
                            success(languagesOnDefaultContext)
                        } else {
                            failure(ErrorWithDescription.ServerFailure("List Error", error!.localizedDescription) as NSError)
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
    
    func getAllLocal() -> [ListCD] {
        let k = ListCD.mr_findAll() as! [ListCD]
        return k
    }
}
