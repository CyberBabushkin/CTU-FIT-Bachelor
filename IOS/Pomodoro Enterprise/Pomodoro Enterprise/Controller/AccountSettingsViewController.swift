//
//  AccountSettingsViewController.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 11/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit
import MagicalRecord
import SearchTextField

class AccountSettingsViewController: UIViewController, NSFetchedResultsControllerDelegate,
                                     UIImagePickerControllerDelegate, UINavigationControllerDelegate {

    @IBOutlet weak var avatarButton: UIButton!
    @IBOutlet weak var nameTextField: UITextField!
    @IBOutlet weak var surnameTextField: UITextField!
    @IBOutlet weak var teamTextField: SearchTextField!
    
    var personFRC: NSFetchedResultsController<PersonCD>!
    
    let picker = UIImagePickerController()
    
    override func viewDidLoad() {
        super.viewDidLoad()

        let pred = NSPredicate(format: "main = true")
        personFRC = PersonCD.mr_fetchAllSorted(by: "name",
                                               ascending: true,
                                               with: pred,
                                               groupBy: nil,
                                               delegate: self) as! NSFetchedResultsController<PersonCD>
        
        setupPersonFields()
        teamTextField.userStoppedTypingHandler = teamsFetcherHandler
        teamsFetcherHandler()
        
        picker.delegate = self
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewDidDisappear(animated)
        
        if let p = personFRC.fetchedObjects, p.count > 0 {
            let per = p[0]
            
            MagicalRecord.save({ ctx in
                let person = PersonCD.mr_findFirst(byAttribute: "usersUserId",
                                                withValue: per.usersUserId,
                                                in: ctx)!
                if let t = self.nameTextField.text, t.count > 0 {
                    person.name = t
                }
                
                if let t = self.surnameTextField.text, t.count > 0 {
                    person.familyName = t
                }
                
                PersonServer.shared.update(entity: person, success: {_ in}, failure: {})
                
                var oldTeam: TeamCD?
                var newTeamName: String?
                var teamNamesMatches: Bool = false
                var nameIsInList: Bool = false
                
                if let o = person.isMemberOf {
                    oldTeam = o
                }
                
                if let ntn = self.teamTextField.text, ntn.trimmingCharacters(in: [" "]).count > 0 {
                    newTeamName = ntn
                }
                
                if let o = oldTeam, let n = newTeamName {
                    teamNamesMatches = o.name! == n
                }
                
                if let n = newTeamName, let tms = self.teams {
                    nameIsInList = tms.map{ tmp in return tmp.name! }.contains(n)
                }
                
                // Do nothing
                if let _ = oldTeam {
                    if teamNamesMatches {return}
                } else {
                    if let _ = newTeamName {} else {return}
                }
                
                // Delete old team
                if let o = oldTeam {
                    if let _ = newTeamName {
                        if !teamNamesMatches {
                            CoreDataUtilities.remove(user: person, from: o, inContext: ctx, success: {
                                print("Successfully deleted old team...")
                            })
                            usleep(500000)
                        }
                    } else {
                        CoreDataUtilities.remove(user: person, from: o, inContext: ctx, success: {
                            print("Successfully deleted old team...")
                        })
                        usleep(500000)
                    }
                }
                
                // Create a new team
                if let n = newTeamName, !nameIsInList {
                    CoreDataUtilities.createTeam(user: person, name: n, success: { print("NewTeam OK.") })
                }
                
                // Update team
                if let n = newTeamName, nameIsInList {
                    CoreDataUtilities.assign(teamName: n, toUser: person)
                }
            })
        }
    }
    
    func setupPersonFields() {
        if let ps = personFRC.fetchedObjects, ps.count > 0 {
            let p = ps[0]
            if let a = p.avatar {
                let image = ImageUtilities.base64ToImage(base64str: a)
                avatarButton.setImage(image, for: .normal)
            }
            if let n = p.name {
                nameTextField.text = n
            }
            if let f = p.familyName {
                surnameTextField.text = f
            }
            if let t = p.isMemberOf {
                teamTextField.text = t.name
            }
        }
    }
    
    var teams: [TeamCD]?
    
    func teamsFetcherHandler() {
        if let criteria = self.teamTextField.text {
            if criteria.count > 1 {
                self.teamTextField.showLoadingIndicator()
                
                self.searchTeams(withName: criteria) { results in
                    self.teams = results
                    self.teamTextField.filterStrings(results.map { t in t.name! }.filter { n in n.starts(with: criteria) })
                    self.teamTextField.stopLoadingIndicator()
                }
            }
        }
    }
    
    func searchTeams(withName name: String, _ completion: @escaping ([TeamCD]) -> ()) {
        TeamServer.shared.getAllTeams(userId: 0, success: { _, t in completion(t) }, failure: { e in print(e) })
    }
    
    @IBAction func pickAvatar(_ sender: Any) {
        picker.allowsEditing = false
        picker.sourceType = .photoLibrary
        picker.mediaTypes = UIImagePickerController.availableMediaTypes(for: .photoLibrary)!
        present(picker, animated: true, completion: nil)
    }
    
    func imagePickerController(_ picker: UIImagePickerController,
                               didFinishPickingMediaWithInfo info: [String : Any]) {
        var chosenImage = info[UIImagePickerControllerOriginalImage] as! UIImage
        chosenImage = ImageUtilities.resizeImage(image: chosenImage, targetSize: CGSize(width: 64, height: 64))
        let person = personFRC.fetchedObjects!.filter({ $0.main == true })[0]
        let base64 = ImageUtilities.imageToBase64(image: chosenImage)
        
        MagicalRecord.save({ ctx in
            person.avatar = base64
        }, completion: { _, _ in
            PersonServer.shared.update(entity: person, success: {_ in}, failure: {})
            self.avatarButton.setImage(chosenImage, for: .normal)
            self.dismiss(animated:true, completion: nil)
        })
    }
    
    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        dismiss(animated: true, completion: nil)
    }
}
