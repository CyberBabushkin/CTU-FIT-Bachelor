//
//  ToDoCell.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 09/01/2018.
//  Copyright © 2018 Andrey Babushkin. All rights reserved.
//

import UIKit
import MagicalRecord

class ToDoCell: UITableViewCell {

    var task: TaskCD? {
        didSet {
            self.textLabel?.text = task?.name
            self.detailTextLabel?.text = task?.list?.title
        }
    }
    
    override init(style: UITableViewCellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
    }

    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)
    }
}
