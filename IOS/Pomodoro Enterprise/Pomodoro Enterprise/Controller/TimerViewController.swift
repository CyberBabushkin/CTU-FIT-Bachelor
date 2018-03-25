//
//  TimerViewController.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 15/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit
import MagicalRecord

class TimerViewController: UIViewController, UITableViewDelegate, UITableViewDataSource, NSFetchedResultsControllerDelegate {

    @IBOutlet weak var timerView: TimerView!
    @IBOutlet weak var timerButton: UIButton!
    @IBOutlet weak var timerLabel: UILabel!
    
    @IBOutlet weak var toDosTableView: UITableView!
    
    private let secs = 0.5
    
    private var timer: Timer?
    
    var personFRC: NSFetchedResultsController<PersonCD>!
    var settingsFRC: NSFetchedResultsController<SettingsCD>!
    var tasksFRC: NSFetchedResultsController<TaskCD>!
    
    private var state: TimerState = .Work {
        didSet {
            setupButtonIcon()
        }
    }
    private var isTicking = false {
        didSet {
            setupButtonIcon()
        }
    }
    
    private var workTime = 30 * 60.0 {
        didSet {
            setupTimerLabel()
        }
    }
    private var restTime = 5 * 60.0 {
        didSet {
            setupTimerLabel()
        }
    }
    
    private var timeElapsed = 0.0 {
        didSet {
            setupTimerLabel()
            let pos = self.timeElapsed / (self.state == .Rest ? self.restTime : self.workTime)
            self.timerView.update(withPosition: pos, andState: self.state)
        }
    }
    
    // MARK: - View methods
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        timerButton.addTarget(self, action: #selector(buttonAction(button:)), for: .touchUpInside)
        timeElapsed = 0.0
        
        let pred = NSPredicate(format: "main = true")
        personFRC = PersonCD.mr_fetchAllSorted(by: "name",
                                               ascending: true,
                                               with: pred,
                                               groupBy: nil,
                                               delegate: self) as! NSFetchedResultsController<PersonCD>
        
        settingsFRC = SettingsCD.mr_fetchAllSorted(by: "personUsersUserId",
                                                   ascending: true,
                                                   with: nil,
                                                   groupBy: nil,
                                                   delegate: self) as! NSFetchedResultsController<SettingsCD>
        
        let taskPred = NSPredicate(format: "dateFinish = nil")
        tasksFRC = TaskCD.mr_fetchAllSorted(by: "taskId",
                                            ascending: true,
                                            with: taskPred,
                                            groupBy: nil,
                                            delegate: self) as! NSFetchedResultsController<TaskCD>
        
        setTimerValues()
        
        toDosTableView.register(ToDoCell.self, forCellReuseIdentifier: "toDoCell")
        toDosTableView.delegate = self
        toDosTableView.dataSource = self
    }
    
    func controllerDidChangeContent(_ controller: NSFetchedResultsController<NSFetchRequestResult>) {
        switch controller {
        case personFRC:
            if let f = personFRC.fetchedObjects, f.isEmpty {
                print("Logged out")
            }
        case settingsFRC:
            if let s = settingsFRC.fetchedObjects {
                if !s.isEmpty {
                    setTimerValues()
                }
            }
        case tasksFRC:
            self.toDosTableView.reloadData()
        default:
            break
        }
    }
    
    func setTimerValues() {
        if let s = settingsFRC.fetchedObjects, s.count > 0 {
            let set = s[0]
            workTime = Double(set.pomodoroTime) * secs
            restTime = Double(set.breakTime) * secs
        }
    }

    // MARK: - Button methods
    
    private func setupButtonIcon() {
        let isRest = (self.state == .Rest)
        
        if (isRest && isTicking) {
            self.timerButton.setImage(#imageLiteral(resourceName: "green pause"), for: .normal)
        } else if (isRest && !isTicking) {
            self.timerButton.setImage(#imageLiteral(resourceName: "green play"), for: .normal)
        } else if (!isRest && isTicking) {
            self.timerButton.setImage(#imageLiteral(resourceName: "red pause"), for: .normal)
        } else if (!isRest && !isTicking) {
            self.timerButton.setImage(#imageLiteral(resourceName: "red play"), for: .normal)
        }
    }
    
    @objc private func buttonAction(button: UIButton) {
        if (self.isTicking) {
            pauseTimer()
        } else {
            runTimer()
        }
    }
    
    // MARK: - Label methods
    
    private func setupTimerLabel() {
        let min = minutesLeft()
        let sec = secondsLeft()
        self.timerLabel.text = "\(String(format: "%02d", min)) : \(String(format: "%02d", sec))"
    }
    
    // MARK: - Timer methods
    
    private func runTimer() {
        if let _ = self.timer {
            self.timer!.invalidate()
        }
        
        self.timer = Timer.scheduledTimer(withTimeInterval: 1.0, repeats: true, block: timerAction(_:))
        self.isTicking = true
    }
    
    private func pauseTimer() {
        self.timer?.invalidate()
        self.isTicking = false
    }
    
    private func stopTimer() {
        pauseTimer()
        timeElapsed = 0.0
    }
    
    @objc func timerAction(_ timer: Timer) {
        self.timeElapsed += 1.0
        
        if ((self.state == .Work && self.timeElapsed >= self.workTime) ||
            (self.state == .Rest && self.timeElapsed >= self.restTime)) {
            
            let p = personFRC.fetchedObjects![0]
            
            if (self.state == .Work) {
                CoreDataUtilities.createPomodoro(user: p, date: Date(), success: {})
            }
            
            self.state = (self.state == .Rest) ? .Work : .Rest
            stopTimer()
        }
    }
    
    private func minutesLeft() -> Int {
        if (self.state == .Rest) {
            return Int((restTime - timeElapsed) / 60)
        } else {
            return Int((workTime - timeElapsed) / 60)
        }
    }
    
    private func secondsLeft() -> Int {
        if (self.state == .Rest) {
            return Int(restTime - timeElapsed) % 60
        } else {
            return Int(workTime - timeElapsed) % 60
        }
    }
    
    // MARK: - Table View
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return tasksFRC.fetchedObjects?.count ?? 0
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = toDosTableView.dequeueReusableCell(withIdentifier: "toDoCell") as! ToDoCell
        cell.task = tasksFRC.fetchedObjects?[indexPath.row]
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        toDosTableView.deselectRow(at: indexPath, animated: true)
        let cell = toDosTableView.cellForRow(at: indexPath) as! ToDoCell
        cell.accessoryType = .checkmark
        
        if let t = cell.task {
            t.dateFinish = Date()
            CoreDataUtilities.update(task: t, success: { t in }, failure: {})
        }
    }
    
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }

}
