//
//  SignUpViewController.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 20/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit
import MagicalRecord

class SignUpViewController: UIViewController, UITextFieldDelegate, NSFetchedResultsControllerDelegate {

    @IBOutlet weak var signUpButton: UIButton!
    @IBOutlet weak var cancelButton: UIButton!
    @IBOutlet weak var usernameTextField: UITextField!
    @IBOutlet weak var passwordTextField: UITextField!
    @IBOutlet weak var nameTextField: UITextField!
    @IBOutlet weak var surnameTextField: UITextField!
    
    var personFRC: NSFetchedResultsController<PersonCD>!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        usernameTextField.delegate = self
        passwordTextField.delegate = self
        nameTextField.delegate = self
        surnameTextField.delegate = self
        
        personFRC = PersonCD.mr_fetchAllSorted(by: "name",
                                               ascending: true,
                                               with: nil,
                                               groupBy: nil,
                                               delegate: self) as! NSFetchedResultsController<PersonCD>
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

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    // MARK: - UIButton methods
    
    @IBAction func signUpButtonTapped(_ sender: Any) {
        if (!checkTextFields()) {
            return
        }
        
        CoreDataUtilities.register(withLogin: usernameTextField.text!,
                                   password: passwordTextField.text!,
                                   name: nameTextField.text!,
                                   andFamilyName: surnameTextField.text!)
    }

    @IBAction func cancelButtonTapped(_ sender: Any) {
        dismiss(animated: true, completion: nil)
    }
    
    // MARK: - UITextFieldDelegate methods
    
    func checkTextFields() -> Bool {
        if  let n = nameTextField.text, n.count > 0,
            let f = surnameTextField.text, f.count > 0,
            let l = usernameTextField.text, l.count > 8,
            let p = passwordTextField.text, p.count > 8 {
            return true
        }
        return false
    }
    
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
