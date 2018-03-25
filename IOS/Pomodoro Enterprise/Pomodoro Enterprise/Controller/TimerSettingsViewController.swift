//
//  TimerSettingsViewController.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 11/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit
import CoreData
import MagicalRecord

class TimerSettingsViewController: UIViewController, NSFetchedResultsControllerDelegate, UITextFieldDelegate {

    @IBOutlet weak var workTimeTextField: UITextField!
    @IBOutlet weak var breakTimeTextField: UITextField!
    @IBOutlet weak var pomodorosGoalTextField: UITextField!
    @IBOutlet weak var tasksGoalTextField: UITextField!
    
    var workTime: Int32?
    var breakTime: Int32?
    var pomodorosGoal: Int32?
    var tasksGoal: Int32?
    
    var settingsFRC: NSFetchedResultsController<SettingsCD>!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        settingsFRC = SettingsCD.mr_fetchAllSorted(by: "personUsersUserId",
                                                   ascending: true,
                                                   with: nil,
                                                   groupBy: nil,
                                                   delegate: self) as! NSFetchedResultsController<SettingsCD>
        
        workTimeTextField.keyboardType = .numberPad
        breakTimeTextField.keyboardType = .numberPad
        pomodorosGoalTextField.keyboardType = .numberPad
        tasksGoalTextField.keyboardType = .numberPad
        
        workTimeTextField.delegate = self
        breakTimeTextField.delegate = self
        pomodorosGoalTextField.delegate = self
        tasksGoalTextField.delegate = self
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        setupTextFields()
        setOldValues()
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
        if let s = settingsFRC.fetchedObjects, s.count > 0 {
            let set = s[0]
            
            MagicalRecord.save({ ctx in
                let s = SettingsCD.mr_findFirst(byAttribute: "personUsersUserId",
                                                withValue: set.personUsersUserId,
                                                in: ctx)
                if let t = self.breakTimeTextField.text {
                    s?.breakTime = Int32(t)!
                }
                
                if let t = self.workTimeTextField.text {
                    s?.pomodoroTime = Int32(t)!
                }
                
                if let t = self.pomodorosGoalTextField.text {
                    s?.pomodoroGoal = Int32(t)!
                }
                
                if let t = self.tasksGoalTextField.text {
                    s?.taskGoal = Int32(t)!
                }
            })
        }
    }
    
    func setupTextFields() {
        try! settingsFRC.performFetch()
        if let s = settingsFRC.fetchedObjects, s.count > 0 {
            let set = s[0]
            
            workTimeTextField.text = "\(set.pomodoroTime)"
            breakTimeTextField.text = "\(set.breakTime)"
            pomodorosGoalTextField.text = "\(set.pomodoroGoal)"
            tasksGoalTextField.text = "\(set.taskGoal)"
        }
    }
    
    func setOldValues() {
        if let s = settingsFRC.fetchedObjects, s.count > 0 {
            let set = s[0]
            
            workTime = set.pomodoroTime
            breakTime = set.breakTime
            pomodorosGoal = set.pomodoroGoal
            tasksGoal = set.taskGoal
        }
    }
    
    func textFieldDidEndEditing(_ textField: UITextField) {
        switch textField {
        case pomodorosGoalTextField:
            if let pg = Int32(self.pomodorosGoalTextField.text ?? "") {
                if !(pg >= 1 && pg <= 50) {
                    self.pomodorosGoalTextField.text = "\(pomodorosGoal!)"
                    let alert = UIAlertController(title: "Error!",
                                                  message: "The goal should be between 1 and 50",
                                                  preferredStyle: .alert)
                    alert.addAction(UIAlertAction(title: "Ok :(", style: .default, handler: nil))
                    self.present(alert, animated: true, completion: nil)
                }
            }
        case workTimeTextField:
            if let wt = Int32(self.workTimeTextField.text ?? "") {
                if !(wt >= 10 && wt <= 60) {
                    self.workTimeTextField.text = "\(workTime!)"
                    let alert = UIAlertController(title: "Error!",
                                                  message: "Working time should be between 10 and 60",
                                                  preferredStyle: .alert)
                    alert.addAction(UIAlertAction(title: "Ok :(", style: .default, handler: nil))
                    self.present(alert, animated: true, completion: nil)
                }
            }
        case breakTimeTextField:
            if let bt = Int32(self.breakTimeTextField.text ?? "") {
                if !(bt >= 3 && bt <= 20) {
                    self.breakTimeTextField.text = "\(breakTime!)"
                    let alert = UIAlertController(title: "Error!",
                                                  message: "Working time should be between 3 and 20",
                                                  preferredStyle: .alert)
                    alert.addAction(UIAlertAction(title: "Ok :(", style: .default, handler: nil))
                    self.present(alert, animated: true, completion: nil)
                }
            }
        case tasksGoalTextField:
            if let tg = Int32(self.tasksGoalTextField.text ?? "") {
                if !(tg >= 1 && tg <= 50) {
                    self.tasksGoalTextField.text = "\(tasksGoal!)"
                    let alert = UIAlertController(title: "Error!",
                                                  message: "The goal should be between 1 and 50",
                                                  preferredStyle: .alert)
                    alert.addAction(UIAlertAction(title: "Ok :(", style: .default, handler: nil))
                    self.present(alert, animated: true, completion: nil)
                }
            }
        default:
            break
        }
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
