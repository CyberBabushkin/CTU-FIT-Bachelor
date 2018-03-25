//
//  TaskViewController.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 11/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit

class TaskViewController: UIViewController {
    
    @IBOutlet weak var taskNameTextField: UITextField!
    @IBOutlet weak var taskInfoTextView: UITextView!
    @IBOutlet weak var finishedSwitch: UISwitch!
    @IBOutlet weak var finishedDatePicker: UIDatePicker!
    
    public var task: TaskCD?
    public var list: ListCD!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        taskInfoTextView.layer.borderWidth = 1
        taskInfoTextView.layer.cornerRadius = 6
        
        finishedSwitch.isOn = false
        finishedDatePicker.isHidden = true
        finishedDatePicker.date = Date()
        
        if let t = task {
            taskNameTextField.text = t.name
            taskInfoTextView.text = t.info
            
            if let date = t.dateFinish {
                finishedSwitch.isOn = true
                finishedDatePicker.isHidden = false
                finishedDatePicker.date = date
            } 
        } else {
            self.navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .done,
                                                                     target: self,
                                                                     action: #selector(addNewTaskPressed(_:)))
            self.navigationItem.leftBarButtonItem = UIBarButtonItem(barButtonSystemItem: .cancel,
                                                                    target: self,
                                                                    action: #selector(cancelPressed(_:)))
        }
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
        if let t = task, (taskNameTextField.text?.count ?? 0) > 0 {
            t.name = taskNameTextField.text!
            t.info = taskInfoTextView.text
            t.list = list
            if finishedSwitch.isOn {
                t.dateFinish = finishedDatePicker.date
            } else {
                t.dateFinish = nil
            }
            
            TaskServer.shared.update(entity: t,
                                     success: { e in },
                                     failure: {})
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @objc func addNewTaskPressed(_ sender: Any) {
        var date: Date?
        if (finishedSwitch.isOn) {
            date = finishedDatePicker.date
        }
        
        if (taskNameTextField.text?.count ?? 0) > 0 {
            CoreDataUtilities.createTask(withName: taskNameTextField.text!,
                                         info: taskInfoTextView.text,
                                         dateFinish: date,
                                         list: list,
                                         success: { _ = self.navigationController?.popViewController(animated: true) })
        }
        
    }
    
    @objc func cancelPressed(_ sender: Any) {
        _ = self.navigationController?.popViewController(animated: true)
    }
    
    @IBAction func finishedToggled(_ sender: Any) {
        finishedDatePicker.isHidden = !finishedDatePicker.isHidden
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
