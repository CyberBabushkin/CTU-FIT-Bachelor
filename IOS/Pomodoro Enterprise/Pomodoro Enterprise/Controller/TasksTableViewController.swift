//
//  TasksTableViewController.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 11/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit
import CoreData

class TasksTableViewController: UITableViewController, NSFetchedResultsControllerDelegate {

    var list: ListCD?
    var taskFRC: NSFetchedResultsController<TaskCD>!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .add,
                                                                 target: self,
                                                                 action: #selector(addNewTaskButtonPressed(_:)))
        
        tableView.register(UITableViewCell.self, forCellReuseIdentifier: "taskCell")
        
        let pred = NSPredicate(format: "list.listId == %d", list!.listId)
        taskFRC = TaskCD.mr_fetchAllSorted(by: "name",
                                           ascending: true,
                                           with: pred,
                                           groupBy: nil,
                                           delegate: self) as! NSFetchedResultsController<TaskCD>
    }
    
    func controllerDidChangeContent(_ controller: NSFetchedResultsController<NSFetchRequestResult>) {
        tableView.reloadData()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    // MARK: - Table view data source

    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        try! taskFRC.performFetch()
        return taskFRC.fetchedObjects?.count ?? 0
    }

    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "taskCell", for: indexPath)
        let t = taskFRC.fetchedObjects![indexPath.row]
        cell.textLabel?.text = t.name
        return cell
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        self.performSegue(withIdentifier: "editTaskSegue", sender: tableView.cellForRow(at: indexPath))
    }
    
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCellEditingStyle, forRowAt indexPath: IndexPath) {
        if editingStyle == .delete {
            let t = taskFRC.fetchedObjects![indexPath.row]
            CoreDataUtilities.remove(task: t, success:  { try! self.taskFRC.performFetch() }, failure: {
                let alertVC = UIAlertController(title: "Error",
                                                message: "Couldn't delete a task.",
                                                preferredStyle: .alert)
                self.present(alertVC, animated: true, completion: nil)
            })
        }
    }
    
    @objc func addNewTaskButtonPressed(_ sender: Any) {
        if list != nil {
            self.performSegue(withIdentifier: "createTaskSegue", sender: self)
        } else {
            let errorVC = UIAlertController(title: "Error.",
                                            message: "No list.",
                                            preferredStyle: .alert)
            self.present(errorVC, animated: true, completion: nil)
        }
    }

    /*
    // Override to support rearranging the table view.
    override func tableView(_ tableView: UITableView, moveRowAt fromIndexPath: IndexPath, to: IndexPath) {

    }
    */

    /*
    // Override to support conditional rearranging of the table view.
    override func tableView(_ tableView: UITableView, canMoveRowAt indexPath: IndexPath) -> Bool {
        // Return false if you do not want the item to be re-orderable.
        return true
    }
    */

    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "editTaskSegue", let dest = segue.destination as? TaskViewController {
            if let cell = sender as? UITableViewCell, let indexPath = self.tableView.indexPath(for: cell) {
                dest.task = taskFRC.fetchedObjects![indexPath.row]
                dest.list = self.list
            }
        }
        
        if segue.identifier == "createTaskSegue", let dest = segue.destination as? TaskViewController {
            dest.task = nil
            dest.list = self.list
        }
    }


}
