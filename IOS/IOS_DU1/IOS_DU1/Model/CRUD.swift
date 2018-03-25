//
//  CRUD.swift
//  IOS_DU1
//
//  Created by Andrey Babushkin on 07/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import Alamofire

class CRUD {
    
    static func create(recipe: RecipeDetailed, callback: @escaping ((Bool) -> ())) {
        var data = recipe.asDictionary()
        if (data.keys.contains("id")) { data.removeValue(forKey: "id")}
        
        Alamofire.request("https://cookbook.ack.ee/api/v1/recipes/",
            method: .post,
            parameters: data,
            encoding: JSONEncoding.default,
            headers: ["Content-Type" : "application/json"]).responseJSON { response in
                if (!response.result.isSuccess) {
                    callback(false)
                } else {
                    callback(true)
                }
                
                if let d = response.data {
                    print(String(data: d, encoding: String.Encoding.utf8)!)
                }
        }
    }
    
    static func getRecipe(withID id: String, callback: @escaping ((RecipeDetailed) -> ())) {
        Alamofire.request("https://cookbook.ack.ee/api/v1/recipes/\(id)").responseJSON { response in
            
            if let data = response.data {
                do {
                    let jsonDecoder = JSONDecoder()
                    let recipe = try jsonDecoder.decode(RecipeDetailed.self, from: data)
                    callback(recipe)
                } catch {}
            }
        }
    }
    
    static func getAllRecipes(callback: @escaping (([Recipe]) -> ())) {
        Alamofire.request("https://cookbook.ack.ee/api/v1/recipes").responseJSON { response in
            
            if let data = response.data {
                do {
                    let jsonDecoder = JSONDecoder()
                    let recipes = try jsonDecoder.decode([Recipe].self, from: data)
                    callback(recipes)
                } catch {
                    print("\(error)")
                }
            }
        }
    }
    
    static func update(recipe: RecipeDetailed, callback: @escaping ((Bool) -> ())) {
        var data = recipe.asDictionary()
        if (data.keys.contains("id")) { data.removeValue(forKey: "id")}
        
        Alamofire.request("https://cookbook.ack.ee/api/v1/recipes/\(recipe.id)",
            method: .put,
            parameters: data,
            encoding: JSONEncoding.default,
            headers: ["Content-Type" : "application/json"]).responseJSON { response in
                if (!response.result.isSuccess) {
                    callback(false)
                } else {
                    callback(true)
                }
        }
    }
    
    static func updateRecipeScore(withId id: String, newScore score: Int, callback: @escaping ((Bool) -> ())) {
        let data = [ "score": score ]
        Alamofire.request("https://cookbook.ack.ee/api/v1/recipes/\(id)/ratings",
            method: .post,
            parameters: data,
            encoding: JSONEncoding.default,
            headers: ["Content-Type" : "application/json"]).responseJSON { response in
                if (!response.result.isSuccess) {
                    callback(false)
                } else {
                    callback(true)
                }
        }
    }
    
    static func delete(id: String, callback: @escaping ((Bool) -> ())) {
        Alamofire.request("https://cookbook.ack.ee/api/v1/recipes/\(id)",
            method: .delete).responseJSON { response in
                if (!response.result.isSuccess) {
                    callback(false)
                } else {
                    callback(true)
                }
        }
    }
    
}
