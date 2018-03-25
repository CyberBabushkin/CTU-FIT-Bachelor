//
//  EditRecipeViewController.swift
//  IOS_DU1
//
//  Created by Andrey Babushkin on 13/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit
import CoreGraphics

extension UITextField {
    func setBottomBorder() {
        self.borderStyle = .none
        self.layer.backgroundColor = UIColor.white.cgColor
        
        self.layer.masksToBounds = false
        self.layer.shadowColor = UIColor.lightGray.cgColor
        self.layer.shadowOffset = CGSize(width: 0.0, height: 1.0)
        self.layer.shadowOpacity = 1.0
        self.layer.shadowRadius = 0.0
    }
}

extension UIViewController {
    func hideKeyboardWhenTappedAround() {
        let tap: UITapGestureRecognizer = UITapGestureRecognizer(target: self, action: #selector(UIViewController.dismissKeyboard))
        tap.cancelsTouchesInView = false
        view.addGestureRecognizer(tap)
    }
    
    @objc func dismissKeyboard() {
        view.endEditing(true)
    }
}

class EditRecipeViewController: UIViewController, UITextFieldDelegate, UITextViewDelegate {

    private let createNew: Bool
    private var recipe: RecipeDetailed
    
    private weak var scrollView: UIScrollView?
    private weak var contentView: UIView?
    private weak var loadingView: UIView?
    
    private weak var nameTextField: UITextField?
    private weak var infoTextField: UITextField?
    private weak var descriptionTextField: UITextField?
    private var ingredientsTextFields: [UITextField] = []
    private weak var descriptionLabel: UILabel?
    private weak var descriptionTextView: UITextView?
    private weak var timeTextField: UITextField?
    
    init(withRecipe rec: RecipeDetailed) {
        self.recipe = rec
        self.createNew = false
        super.init(nibName: nil, bundle: nil)
    }
    
    init(createNew: Bool) {
        self.createNew = createNew
        self.recipe = RecipeDetailed.empty()
        super.init(nibName: nil, bundle: nil)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.hideKeyboardWhenTappedAround()
        
        scrollView = nil
        ingredientsTextFields.removeAll()
        
        switch createNew {
        case true:
            setupAddRecipeView()
        default:
            setupEditRecipeView()
        }
        
        NotificationCenter.default.addObserver(
            self,
            selector: #selector(keyboardWillShow),
            name: NSNotification.Name.UIKeyboardWillShow,
            object: nil
        )
    }
    
    private func setupAddRecipeView() {
        navigationItem.title = "Add a new recipe"
        navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .done,
                                                            target: self,
                                                            action: #selector(addRecipe(sender:)))
        setupView()
        
    }
    
    private func setupEditRecipeView() {
        navigationItem.title = "Edit the recipe"
        navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .done,
                                                            target: self,
                                                            action: #selector(updateRecipe(sender:)))
        
        setupView()
        fillInFields()
    }
    
    private func setupView() {
        view.backgroundColor = .clear
        
        let scrollView = UIScrollView()
        scrollView.isScrollEnabled = true
        scrollView.backgroundColor = .white
        
        view.addSubview(scrollView)
        self.scrollView = scrollView
        
        scrollView.snp.makeConstraints { make in
            make.edges.equalToSuperview()
        }
        
        let contentView = UIView()
        scrollView.addSubview(contentView)
        self.contentView = contentView
        contentView.snp.makeConstraints { make in
            make.edges.equalToSuperview()
            make.width.equalTo(view.snp.width)
        }
        
        let recipeNameLabel = UILabel()
        recipeNameLabel.font = UIFont.systemFont(ofSize: 20)
        recipeNameLabel.textColor = .blue
        recipeNameLabel.text = "Recipe name"
        contentView.addSubview(recipeNameLabel)
        recipeNameLabel.snp.makeConstraints { make in
            make.top.equalToSuperview().offset(40)
            make.left.equalTo(30)
            make.right.equalTo(-30)
        }
        
        let nameTextField = UITextField()
        nameTextField.font = UIFont.systemFont(ofSize: 16)
        nameTextField.textColor = .black
        nameTextField.text = ""
        nameTextField.setBottomBorder()
        nameTextField.placeholder = "Give your recipe a name!"
        contentView.addSubview(nameTextField)
        self.nameTextField = nameTextField
        nameTextField.snp.makeConstraints { make in
            make.left.equalTo(30)
            make.right.equalTo(-30)
            make.top.equalTo(recipeNameLabel.snp.bottom).offset(15)
        }
        
        let recipeInfoLabel = UILabel()
        recipeInfoLabel.font = UIFont.systemFont(ofSize: 20)
        recipeInfoLabel.textColor = .blue
        recipeInfoLabel.text = "A brief description"
        contentView.addSubview(recipeInfoLabel)
        recipeInfoLabel.snp.makeConstraints { make in
            make.top.equalTo(nameTextField.snp.bottom).offset(30)
            make.left.equalTo(30)
            make.right.equalTo(-30)
        }
        
        let infoTextField = UITextField()
        infoTextField.font = UIFont.systemFont(ofSize: 16)
        infoTextField.textColor = .black
        infoTextField.text = ""
        infoTextField.setBottomBorder()
        infoTextField.placeholder = "Describe it briefly..."
        contentView.addSubview(infoTextField)
        self.infoTextField = infoTextField
        infoTextField.snp.makeConstraints { make in
            make.left.equalTo(30)
            make.right.equalTo(-30)
            make.top.equalTo(recipeInfoLabel.snp.bottom).offset(15)
        }
        
        let ingredientsLabel = UILabel()
        ingredientsLabel.font = UIFont.systemFont(ofSize: 20)
        ingredientsLabel.textColor = .blue
        ingredientsLabel.text = "Ingredients"
        contentView.addSubview(ingredientsLabel)
        ingredientsLabel.snp.makeConstraints { make in
            make.top.equalTo(infoTextField.snp.bottom).offset(30)
            make.left.equalTo(30)
            make.right.equalTo(-30)
        }
        
        let ingredientTextField = UITextField()
        ingredientTextField.font = UIFont.systemFont(ofSize: 16)
        ingredientTextField.textColor = .black
        ingredientTextField.text = ""
        ingredientTextField.setBottomBorder()
        ingredientTextField.delegate = self
        ingredientTextField.placeholder = "Milk - 0.5l"
        ingredientTextField.addTarget(self,
                                      action: #selector(ingredientHasBeenModified(sender:)),
                                      for: .allEditingEvents)
        contentView.addSubview(ingredientTextField)
        self.ingredientsTextFields.append(ingredientTextField)
        ingredientTextField.snp.makeConstraints { make in
            make.left.equalTo(30)
            make.right.equalTo(-30)
            make.top.equalTo(ingredientsLabel.snp.bottom).offset(15)
        }
        
        let descriptionLabel = UILabel()
        descriptionLabel.font = UIFont.systemFont(ofSize: 20)
        descriptionLabel.textColor = .blue
        descriptionLabel.text = "Description"
        contentView.addSubview(descriptionLabel)
        self.descriptionLabel = descriptionLabel
        descriptionLabel.snp.makeConstraints { make in
            make.top.equalTo(ingredientsTextFields.last!.snp.bottom).offset(40)
            make.left.equalTo(30)
            make.right.equalTo(-30)
        }
        
        let descriptionTextView = UITextView()
        descriptionTextView.font = UIFont.systemFont(ofSize: 16)
        descriptionTextView.textColor = .black
        descriptionTextView.text = ""
        descriptionTextView.delegate = self
        contentView.addSubview(descriptionTextView)
        self.descriptionTextView = descriptionTextView
        descriptionTextView.snp.makeConstraints { make in
            make.top.equalTo(descriptionLabel.snp.bottom).offset(15)
            make.left.equalTo(30)
            make.right.equalTo(-30)
            make.height.equalTo(80)
        }
        
        let timeTextField = UITextField()
        timeTextField.font = UIFont.systemFont(ofSize: 16)
        timeTextField.textColor = .lightGray
        timeTextField.textAlignment = .right
        timeTextField.delegate = self
        timeTextField.setBottomBorder()
        timeTextField.keyboardType = .numberPad
        
        let timeLabel = UILabel(frame: CGRect(x: 5, y: 0, width: 40, height: 40))
        timeLabel.text = "Time  "
        timeLabel.font = UIFont.systemFont(ofSize: 16)
        timeLabel.textColor = .black
        
        let minLabel = UILabel(frame: CGRect(x: -5, y: 0, width: 40, height: 40))
        minLabel.text = "  min."
        minLabel.textAlignment = .right
        minLabel.font = UIFont.systemFont(ofSize: 16)
        minLabel.textColor = .lightGray
        
        timeTextField.leftView = timeLabel
        timeTextField.leftViewMode = .always
        timeTextField.rightView = minLabel
        timeTextField.rightViewMode = .always
        contentView.addSubview(timeTextField)
        
        self.timeTextField = timeTextField
        timeTextField.snp.makeConstraints { make in
            make.left.equalTo(30)
            make.right.equalTo(-30)
            make.top.equalTo(descriptionTextView.snp.bottom).offset(30)
        }
        
        contentView.snp.makeConstraints { make in
            make.bottom.equalTo(timeTextField.snp.bottom).offset(30)
        }
    }
    
    private func createIngredientTextField() {
        if let cv = self.contentView {
            let ingredientTextField = UITextField()
            ingredientTextField.font = UIFont.systemFont(ofSize: 16)
            ingredientTextField.textColor = .black
            ingredientTextField.text = ""
            ingredientTextField.setBottomBorder()
            ingredientTextField.delegate = self
            ingredientTextField.placeholder = "Milk - 0.5l"
            
            let last = self.ingredientsTextFields.last!
            cv.addSubview(ingredientTextField)
            self.ingredientsTextFields.append(ingredientTextField)
            ingredientTextField.snp.makeConstraints { make in
                make.left.equalTo(30)
                make.right.equalTo(-30)
                make.top.equalTo(last.snp.bottom).offset(15)
            }
            
            if (self.ingredientsTextFields.count > 2) {
                let rem = self.ingredientsTextFields[self.ingredientsTextFields.count - 3]
                rem.removeTarget(self,
                                 action: #selector(ingredientHasBeenModified(sender:)),
                                 for: .editingDidEnd)
            }
            
            ingredientTextField.addTarget(self,
                                          action: #selector(ingredientHasBeenModified(sender:)),
                                          for: .editingDidEnd)
            
            ingredientTextField.becomeFirstResponder()
        }
        
        descriptionLabel?.snp.remakeConstraints { make in
            make.top.equalTo(self.ingredientsTextFields.last!.snp.bottom).offset(40)
            make.left.equalTo(30)
            make.right.equalTo(-30)
        }
        
        moveViewIfNeeded(view: self.ingredientsTextFields.last!)
    }
    
    private func removeIngredientTextField() {
        if let _ = self.contentView {
            let last = self.ingredientsTextFields.popLast()!
            last.removeTarget(self,
                              action: #selector(ingredientHasBeenModified(sender:)),
                              for: .editingDidEnd)
            
            if (self.ingredientsTextFields.count > 1) {
                let lastButOneButOne = self.ingredientsTextFields[self.ingredientsTextFields.count - 2]
                lastButOneButOne.addTarget(self,
                                           action: #selector(ingredientHasBeenModified(sender:)),
                                           for: .editingDidEnd)
            }
            
            last.removeFromSuperview()
        }
        
        descriptionLabel?.snp.remakeConstraints { make in
            make.top.equalTo(self.ingredientsTextFields.last!.snp.bottom).offset(40)
            make.left.equalTo(30)
            make.right.equalTo(-30)
        }
    }
    
    @objc private func ingredientHasBeenModified(sender: UITextField) {
        if (!sender.hasText &&
            sender == self.ingredientsTextFields.last &&
            self.ingredientsTextFields.count > 1) {
                removeIngredientTextField()
        }
    }
    
    @objc private func addRecipe(sender: UIBarButtonItem) {
        showLoadingView()
        fillInRecipe()
        CRUD.create(recipe: self.recipe, callback: serverResponsed)
    }

    @objc private func updateRecipe(sender: UIBarButtonItem) {
        showLoadingView()
        fillInRecipe()
        CRUD.update(recipe: self.recipe, callback: serverResponsed)
    }
    
    private func serverResponsed(withSuccess suc: Bool) {
        if (suc) {
            self.dismiss(animated: true, completion: nil)
        } else {
            hideLoadingView()
        }
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        if (textField == self.ingredientsTextFields.last! &&
            textField.hasText) {
            createIngredientTextField()
            textField.resignFirstResponder()
        } else {
            
        }
        return true
    }
    
    var movedTF: CGFloat?
    
    private func moveViewIfNeeded(view: UIView) {
        var p = view.convert(view.frame.origin,
                             to: nil).y / 2
        p += view.frame.height
        let sheight = UIScreen.main.bounds.height
        let allowed = sheight - 60 - keyboardHeight
        
        if (p > allowed) {
            movedTF = p - allowed
            moveView(view, dist: Int(movedTF!), up: false)
        }
    }
    
    private func moveViewBack(view: UIView) {
        if let m = movedTF {
            moveView(view, dist: Int(m), up: true)
            movedTF = nil
        }
    }
    
    func textViewDidBeginEditing(_ textView: UITextView) {
        moveViewIfNeeded(view: textView)
    }
    
    func textFieldDidBeginEditing(_ textField: UITextField) {
        moveViewIfNeeded(view: textField)
    }
    
    func textViewDidEndEditing(_ textView: UITextView) {
        moveViewBack(view: textView)
    }
    
    func textFieldDidEndEditing(_ textField: UITextField) {
        moveViewBack(view: textField)
    }
    
    private func moveView(_ textField: UIView, dist: Int, up: Bool) {
        let duration = 0.3
        let movement = CGFloat(up ? dist : -dist)
        
        UIView.beginAnimations("animateView", context: nil)
        UIView.setAnimationBeginsFromCurrentState(true)
        UIView.setAnimationDuration(duration)
        self.contentView?.frame = self.contentView!.frame.offsetBy(dx: 0, dy: movement)
        UIView.commitAnimations()
    }

    private func fillInRecipe() {
        let score = recipe.score
        let id = recipe.id
        
        recipe = RecipeDetailed.empty()
        recipe.score = score
        recipe.id = id

        if let a = nameTextField!.text, a.lowercased().contains("Ackee".lowercased()) {
            recipe.name = nameTextField!.text ?? "NULL"
        } else {
            recipe.name = "Ackee " + (nameTextField!.text ?? "NULL")
        }
        
        recipe.description = descriptionTextView!.text ?? "NULL"
        recipe.duration = Double(timeTextField!.text ?? "0") ?? 0
        recipe.info = infoTextField!.text ?? "NULL"
        
        for i in ingredientsTextFields {
            if (i.hasText) {
                recipe.ingredients?.append(i.text ?? "NULL")
            }
        }
    }
    
    private func fillInFields() {
        nameTextField!.text = recipe.name
        descriptionTextView!.text = recipe.description
        timeTextField!.text = "\(recipe.duration)"
        infoTextField!.text = recipe.info
        
        for i in recipe.ingredients! {
            if (i.filter{ x in x != " " }.isEmpty) { continue }
            
            if (i != recipe.ingredients!.first) {
                createIngredientTextField()
            }
            
            self.ingredientsTextFields.last!.text = i
            
            if (i == recipe.ingredients!.last) {
                createIngredientTextField()
            }
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    private func showLoadingView() {
        let v = UIView(frame: self.view.frame)
        v.backgroundColor = UIColor(red: 0, green: 0, blue: 0, alpha: 0.5)
        let wheel = UIActivityIndicatorView()
        v.addSubview(wheel)
        wheel.snp.makeConstraints { make in
            make.width.height.equalTo(15)
            make.centerX.equalTo(v.snp.centerX)
            make.centerY.equalTo(v.snp.centerY)
        }
        wheel.startAnimating()
        self.loadingView = v
        navigationController?.view.addSubview(v)
    }
    
    private func hideLoadingView() {
        self.loadingView?.removeFromSuperview()
    }
    
    var keyboardHeight: CGFloat = 216.0
    
    @objc func keyboardWillShow(_ notification: Notification) {
        if let keyboardFrame: NSValue = notification.userInfo?[UIKeyboardFrameEndUserInfoKey] as? NSValue {
            let keyboardRectangle = keyboardFrame.cgRectValue
            self.keyboardHeight = keyboardRectangle.height
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
