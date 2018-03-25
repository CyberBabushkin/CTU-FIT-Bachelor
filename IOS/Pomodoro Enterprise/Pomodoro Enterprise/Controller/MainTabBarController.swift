//
//  MainTabBarController.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 15/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit
import CoreData
import MagicalRecord

class MainTabBarController: UITabBarController, UITabBarControllerDelegate, NSFetchedResultsControllerDelegate {
    
    var pomodoroButton : UIButton!
    var personFRC: NSFetchedResultsController<PersonCD>!
    
    override func viewDidLayoutSubviews()
    {
        super.viewDidLayoutSubviews()
        self.bringcenterButtonToFront()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        self.tabBar.barTintColor = UIColor(red:0.91, green:0.22, blue:0.13, alpha:0.7)
        UITabBarItem.appearance().setTitleTextAttributes([NSAttributedStringKey.foregroundColor: UIColor.white],
                                                         for: .normal)

        self.tabBar.tintColor = .white
        self.setupMiddleButton()
        
        let pred = NSPredicate(format: "main = true");
        personFRC = PersonCD.mr_fetchAllSorted(by: "name",
                                               ascending: true,
                                               with: pred,
                                               groupBy: nil,
                                               delegate: self) as! NSFetchedResultsController<PersonCD>
        
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        showLoginScreen()
    }
    
    func controllerDidChangeContent(_ controller: NSFetchedResultsController<NSFetchRequestResult>) {
        showLoginScreen()
    }
    
    func showLoginScreen() {
        let u = personFRC.fetchedObjects
        if let a = u, a.count > 0 {} else {
            let storyboard = UIStoryboard(name: "Main", bundle: nil)
            let loginVC = storyboard.instantiateViewController(withIdentifier: "loginViewController") as! LoginViewController
            present(loginVC, animated: true, completion: nil)
        }
    }
    
    // MARK: - TabbarDelegate Methods
    
    func tabBarController(_ tabBarController: UITabBarController, didSelect viewController: UIViewController)
    {
        showPomodoroButton()
    }
    
    @objc private func centerButtonAction(sender: UIButton) {
        selectedIndex = 2
    }
    
    func hideCenterButton()
    {
        pomodoroButton.isHidden = true
    }
    
    func showPomodoroButton()
    {
        pomodoroButton.isHidden = false
        self.bringcenterButtonToFront()
    }
    
    // MARK: - Private methods
    
    private func setupMiddleButton()
    {
        pomodoroButton = UIButton(frame: CGRect(x: 0, y: 0, width: 64, height: 64))
        
        var pomodoroButtonFrame = pomodoroButton.frame
        pomodoroButtonFrame.origin.y = view.bounds.height - pomodoroButtonFrame.height
        pomodoroButtonFrame.origin.x = view.bounds.width / 2 - pomodoroButtonFrame.size.width / 2
        pomodoroButton.frame = pomodoroButtonFrame
        
        pomodoroButton.backgroundColor = UIColor.clear
        view.addSubview(pomodoroButton)
        
        pomodoroButton.setImage(#imageLiteral(resourceName: "Pomodoro"), for: .normal)
        pomodoroButton.setImage(#imageLiteral(resourceName: "PomodoroHighlighted"), for: .highlighted)
        pomodoroButton.addTarget(self, action: #selector(centerButtonAction(sender:)), for: .touchUpInside)
        pomodoroButton.addTarget(self, action: #selector(centerButtonAction(sender:)), for: .touchUpOutside)
        
        view.layoutIfNeeded()
    }
    
    private func bringcenterButtonToFront()
    {
        self.view.bringSubview(toFront: self.pomodoroButton)
    }
    
}
