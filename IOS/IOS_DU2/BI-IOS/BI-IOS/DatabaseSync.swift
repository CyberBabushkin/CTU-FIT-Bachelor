//
//  DatabaseSync.swift
//  BI-IOS
//
//  Created by Andrey Babushkin on 23/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import FirebaseDatabase
import MagicalRecord

enum Gender: String {
    case Male = "male", Female = "female"
}

class DatabaseSync {
    
    var ref: DatabaseReference!
    
    open static let shared = DatabaseSync()
    
    private init() {
        ref = Database.database().reference().child("checkins")
        ref.observe(DataEventType.value, with: download)
    }
    
    public func createCheckin(withDate date: Date,
                              lattitude: Double,
                              longitude: Double,
                              username: String?,
                              gender: Gender?) {
        let id = ref.childByAutoId().key
        let genderStr: String? = gender?.rawValue ?? nil
        
        MagicalRecord.save({ ctx in
            let c = Checkin.mr_createEntity(in: ctx)
            c?.id = id
            c?.time = date
            c?.lat = lattitude
            c?.lon = longitude
            c?.gender = genderStr
            c?.username = username
        })
        
        ref.child(id).setValue(["time": date.timeIntervalSince1970 as Double,
                                "lat": lattitude,
                                "lon": longitude,
                                "username": username ?? nil,
                                "gender": genderStr ?? nil])
    }
    
    func download(_ snapshot: DataSnapshot) {
        let postDict = snapshot.value as? [String : AnyObject]
        
        if let dict = postDict, !dict.isEmpty {
            let ids = dict.keys
            
            for id in ids {
                if let checkin = dict[id] as? [String: AnyObject] {
                    let timeO = checkin["time"] as? Double
                    let latO = checkin["lat"] as? Double
                    let lonO = checkin["lon"] as? Double
                    let usernameO = checkin["username"] as? String
                    var genderO = checkin["gender"] as? String
                    
                    if (timeO == nil || latO == nil || lonO == nil) { return }
                    if let gender = genderO, (gender != "male" && gender != "female") {
                        genderO = nil
                    }
                    
                    MagicalRecord.save({ ctx in
                        let c = Checkin.mr_createEntity(in: ctx)
                        c?.id = id
                        c?.time = NSDate(timeIntervalSince1970: timeO!) as Date
                        c?.lat = latO!
                        c?.lon = lonO!
                        c?.gender = genderO
                        c?.username = usernameO
                    })
                }
            }
        }
    }
}
