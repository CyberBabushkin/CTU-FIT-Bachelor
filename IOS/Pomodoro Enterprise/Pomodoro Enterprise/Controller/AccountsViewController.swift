//
//  AccountsViewController.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 21/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit
import CoreData

class AccountsViewController: UIViewController, NSFetchedResultsControllerDelegate, UITableViewDelegate, UITableViewDataSource {

    @IBOutlet weak var avatarImageView: UIImageView!
    @IBOutlet weak var nameLabel: UILabel!
    @IBOutlet weak var surnameLabel: UILabel!
    @IBOutlet weak var logoutButton: UIButton!
    @IBOutlet weak var myTeamLabel: UILabel!
    @IBOutlet weak var myTeamTableView: UITableView!
    
    var personFRC: NSFetchedResultsController<PersonCD>!
    
    var members: [PersonCD]? {
        didSet {
            updateTableView()
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        let pred = NSPredicate(format: "main = true")
        personFRC = PersonCD.mr_fetchAllSorted(by: "name",
                                               ascending: true,
                                               with: pred,
                                               groupBy: nil,
                                               delegate: self) as! NSFetchedResultsController<PersonCD>
        
        myTeamTableView.delegate = self
        myTeamTableView.dataSource = self
        myTeamTableView.register(UITableViewCell.self, forCellReuseIdentifier: "teamMemberCell")
        
        updateView()
    }
    
    func controllerDidChangeContent(_ controller: NSFetchedResultsController<NSFetchRequestResult>) {
        if controller == personFRC {
            updateView()
        }
    }
    
    func updateView() {
        let psf = personFRC.fetchedObjects
        if let ps = psf, ps.count > 0 {
            let p = ps[0]
            nameLabel.text = p.name
            surnameLabel.text = p.familyName
            
            if let a = p.avatar {
                avatarImageView.image = ImageUtilities.base64ToImage(base64str: a)
            }
        }
        
        let team = TeamCD.mr_findAll() as? [TeamCD]
        if let t = team, t.count > 0 {
            myTeamLabel.text = "My Team [\(t[0].teamId)]"
            TeamServer.shared.getAllMembers(team: t[0],
                                            success: {[weak self] mems in
                                                self?.members = mems
            },
                                            failure: {err in print(err)})
        }
    }
    
    func updateTableView() {
        myTeamTableView.reloadData()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    // MARK: - Buttons methods
    
    @IBAction func doneButtonTapped(_ sender: Any) {
        dismiss(animated: true, completion: nil)
    }
    
    @IBAction func logoutButtonTapped(_ sender: Any) {
        CoreDataUtilities.purgeCoreData {
            self.dismiss(animated: true, completion: nil)
        }
    }
    
    // MARK: - TableView methods
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        
        return members?.count ?? 0
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "teamMemberCell", for: indexPath)
        let p = members![indexPath.row]
        cell.textLabel?.text = p.name! + " " + p.familyName!
        
        return cell
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
