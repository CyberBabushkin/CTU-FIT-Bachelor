//
//  LoginViewController.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 20/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit
import CoreData

class LoginViewController: UIViewController, UITextFieldDelegate, NSFetchedResultsControllerDelegate {

    @IBOutlet weak var loginTextField: UITextField!
    @IBOutlet weak var passwordTextField: UITextField!
    @IBOutlet weak var loginButton: UIButton!
    
    var personFRC: NSFetchedResultsController<PersonCD>!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        loginTextField.delegate = self
        passwordTextField.delegate = self
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        personFRC = PersonCD.mr_fetchAllSorted(by: "name",
                                               ascending: true,
                                               with: nil,
                                               groupBy: nil,
                                               delegate: self) as! NSFetchedResultsController<PersonCD>
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        personFRC = nil
    }
    
    func controllerDidChangeContent(_ controller: NSFetchedResultsController<NSFetchRequestResult>) {
        let c = controller as? NSFetchedResultsController<PersonCD>
        if let cc = c {
            checkIfUserExists(controller: cc)
        }
    }
    
    func checkIfUserExists(controller: NSFetchedResultsController<PersonCD>) {
        let u = controller.fetchedObjects
        if let a = u, a.count > 0 {
            dismiss(animated: true, completion: nil)
        }
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        checkIfUserExists(controller: self.personFRC)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    // MARK: - Button Methods
    
    @IBAction func loginButtonTapped(_ sender: Any) {
        CoreDataUtilities.downloadUserData(withUsername: loginTextField.text!,
                                           andPassword: passwordTextField.text!)
    }
    
    // MARK: - UITextFieldDelegate Methods
    
    func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool {
        let text = textField.text ?? ""
        let str = (text + string)
        
        if str.count <= 50 {
            return true
        }
        
        textField.text = String(str.prefix(50))
        return false
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
