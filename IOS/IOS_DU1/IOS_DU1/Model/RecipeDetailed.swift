//
//  RecipeDetailed.swift
//  IOS_DU1
//
//  Created by Andrey Babushkin on 08/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation

struct RecipeDetailed : Codable {
    var name : String
    var description: String
    var duration : Double
    var ingredients: [String]?
    var info: String
    var id : String
    var score : Double
}

extension RecipeDetailed {
    func asDictionary() -> [String: Any] {
        return
            [ "name" : name,
              "description" : description,
              "duration" : duration,
              "ingredients" : ingredients ?? [],
              "info" : info,
              "id" : id,
              "score" : score ]
    }
    
    static public func empty() -> RecipeDetailed {
        return RecipeDetailed(name: "",
                              description: "",
                              duration: 0,
                              ingredients: [],
                              info: "",
                              id: "",
                              score: 0)
    }
}
