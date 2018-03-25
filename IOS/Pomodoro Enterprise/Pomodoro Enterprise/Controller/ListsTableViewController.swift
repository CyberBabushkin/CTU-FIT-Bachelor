//
//  ListsTableViewController.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 11/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit
import CoreData

class ListsTableViewController: UITableViewController, NSFetchedResultsControllerDelegate {

    var listsFRC: NSFetchedResultsController<ListCD>!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        self.tableView.register(UITableViewCell.self, forCellReuseIdentifier: "listCell")
        listsFRC = ListCD.mr_fetchAllSorted(by: "title",
                                           ascending: true,
                                           with: nil,
                                           groupBy: nil,
                                           delegate: self) as! NSFetchedResultsController<ListCD>
        
    }
    
    func controllerDidChangeContent(_ controller: NSFetchedResultsController<NSFetchRequestResult>) {
        self.tableView.reloadData()
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
        return listsFRC.fetchedObjects?.count ?? 0
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "listCell", for: indexPath)
        let l = listsFRC.fetchedObjects![indexPath.row]
        cell.textLabel?.text = l.title
        return cell
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        self.performSegue(withIdentifier: "showTasksSegue",
                          sender: tableView.cellForRow(at: indexPath))
    }

    /*
    // Override to support conditional editing of the table view.
    override func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        // Return false if you do not want the specified item to be editable.
        return true
    }
    */

    // Override to support editing the table view.
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCellEditingStyle, forRowAt indexPath: IndexPath) {
        if editingStyle == .delete {
            let l = listsFRC.fetchedObjects![indexPath.row]
            CoreDataUtilities.remove(list: l, success: {}, failure: {
                let alertVC = UIAlertController(title: "Error",
                                                message: "Couldn't delete a list.",
                                                preferredStyle: .alert)
                alertVC.addAction(UIAlertAction(title: "Done", style: .default, handler: nil))
                self.present(alertVC, animated: true, completion: nil)
            })
        }
    }

    @IBAction func addListButtonPressed(_ sender: Any) {
        let t = TeamCD.mr_findAll()
        if let teams = t, teams.count > 0 {
            let alertVC = UIAlertController(title: "Create a new list",
                                            message: "Enter a name",
                                            preferredStyle: .alert)
            alertVC.addAction(UIAlertAction(title: "Create", style: .default, handler: { a in
                let s = alertVC.textFields![0].text
                if let str = s, str.trimmingCharacters(in: [" ", "\t"]).count > 0 {
                    CoreDataUtilities.createList(withName: str, team: teams[0] as! TeamCD)
                } else {
                    let warningVC = UIAlertController(title: "Empty name",
                                                      message: "Enter a name of a new list",
                                                      preferredStyle: .alert)
                    warningVC.addAction(UIAlertAction(title: "OK",
                                                    style: .default,
                                                    handler: nil))
                    self.present(warningVC, animated: true, completion: nil)
                }
            }))
            alertVC.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: nil))
            alertVC.addTextField(configurationHandler: textFieldHandler(_:))
            self.present(alertVC, animated: true, completion: nil)
        } else {
            let errorVC = UIAlertController(title: "No team",
                                            message: "Please, enroll in a team. This can be done in a settings section.",
                                            preferredStyle: .alert)
            errorVC.addAction(UIAlertAction(title: "Done", style: .default, handler: nil))
            self.present(errorVC, animated: true, completion: nil)
        }
    }
    
    func textFieldHandler(_ textField: UITextField!)
    {
        if (textField) != nil {
            textField.placeholder = "Title"
        }
    }
    
    
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "showTasksSegue", let dest = segue.destination as? TasksTableViewController {
            if let cell = sender as? UITableViewCell, let indexPath = tableView.indexPath(for: cell) {
                let l = listsFRC.fetchedObjects![indexPath.row]
                dest.list = l
            }
        }
    }

}
