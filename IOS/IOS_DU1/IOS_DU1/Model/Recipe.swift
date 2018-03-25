//
//  Recipe.swift
//  IOS_DU1
//
//  Created by Andrey Babushkin on 07/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation

// {"name":"Ackee and Saltfish","duration":10,"id":"5a00be7f0898a11000146b64","score":0}
struct Recipe : Codable {
    var name : String
    var duration : Double
    var id : String
    var score : Double
}

extension Recipe {
    func asDictionary() -> [String: Any] {
        return
            [ "name" : name,
              "duration" : duration,
              "id" : id,
              "score" : score ]
    }
}
