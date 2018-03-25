//
//  ViewController.swift
//  IOS_DU1
//
//  Created by Andrey Babushkin on 07/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit
import SnapKit

class DetailViewController: UIViewController {
    
    private weak var loadingView: UIView?
    
    private weak var durationLabel: UILabel?
    private weak var ingredientsLabel: UILabel?
    private weak var infoLabel: UILabel?
    private weak var descriptionLabel: UILabel?
    
    private var buttons: [UIButton] = []
    
    private var stars: [UIImageView] = []
    private var score: Double = 0
    
    var recipe: RecipeDetailed? {
        didSet {
            if let _ = durationLabel { updateView() }
            self.score = recipe!.score
        }
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .white
        setupView()
        if let _ = recipe {updateView()}
        
        self.navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .edit,
                                                                 target: self,
                                                                 action: #selector(editRecipe(sender:)))
        self.navigationItem.backBarButtonItem?.image = #imageLiteral(resourceName: "ic_back")
    }
    
    override func loadView() {
        super.loadView()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    private func setupView() {
        self.navigationItem.title = recipe?.name
        
        view.backgroundColor = .clear
        
        let scrollView = UIScrollView()
        scrollView.isScrollEnabled = true
        scrollView.backgroundColor = .white
        
        view.addSubview(scrollView)
        
        scrollView.snp.makeConstraints { make in
            make.edges.equalToSuperview()
        }
        
        let contentView = UIView()
        scrollView.addSubview(contentView)
        contentView.snp.makeConstraints { make in
            make.edges.equalToSuperview()
            make.width.equalTo(view.snp.width)
        }
        
        let ratingView = createRatingView()
        contentView.addSubview(ratingView)
        ratingView.snp.makeConstraints { make in
            make.top.equalTo(contentView.safeAreaLayoutGuide.snp.top)
            make.left.right.equalTo(0)
            make.height.equalTo(64)
        }
        
        let infoLabel = UILabel()
        infoLabel.font = UIFont.systemFont(ofSize: 16)
        infoLabel.numberOfLines = 0
        infoLabel.textColor = .black
        infoLabel.lineBreakMode = .byWordWrapping
        contentView.addSubview(infoLabel)
        self.infoLabel = infoLabel
        infoLabel.snp.makeConstraints { make in
            make.top.equalTo(ratingView.snp.bottom).offset(40)
            make.right.equalTo(-30)
            make.left.equalTo(30)
        }
        
        let ingredientsTitleLabel = UILabel()
        ingredientsTitleLabel.font = UIFont.systemFont(ofSize: 20)
        ingredientsTitleLabel.textColor = .blue
        ingredientsTitleLabel.text = "Ingredients"
        contentView.addSubview(ingredientsTitleLabel)
        ingredientsTitleLabel.snp.makeConstraints { make in
            make.top.equalTo(infoLabel.snp.bottom).offset(50)
            make.left.equalTo(30)
        }
        
        let ingredientsLabel = UILabel()
        ingredientsLabel.font = UIFont.systemFont(ofSize: 16)
        ingredientsLabel.textColor = .black
        ingredientsLabel.numberOfLines = 0
        contentView.addSubview(ingredientsLabel)
        self.ingredientsLabel = ingredientsLabel
        ingredientsLabel.snp.makeConstraints { make in
            make.top.equalTo(ingredientsTitleLabel.snp.bottom).offset(10)
            make.left.equalTo(30)
            make.right.equalTo(-30)
        }
        
        let descriptionTitleLabel = UILabel()
        descriptionTitleLabel.font = UIFont.systemFont(ofSize: 20)
        descriptionTitleLabel.textColor = .blue
        descriptionTitleLabel.text = "Description"
        contentView.addSubview(descriptionTitleLabel)
        descriptionTitleLabel.snp.makeConstraints { make in
            make.top.equalTo(ingredientsLabel.snp.bottom).offset(30)
            make.left.equalTo(30)
        }
        
        let descriptionLabel = UILabel()
        descriptionLabel.font = UIFont.systemFont(ofSize: 16)
        descriptionLabel.textColor = .black
        descriptionLabel.numberOfLines = 0
        contentView.addSubview(descriptionLabel)
        self.descriptionLabel = descriptionLabel
        descriptionLabel.snp.makeConstraints { make in
            make.top.equalTo(descriptionTitleLabel.snp.bottom).offset(10)
            make.left.equalTo(30)
            make.right.equalTo(-30)
        }

        let reviewView = createReviewView()
        contentView.addSubview(reviewView)
        reviewView.snp.makeConstraints { make in
            make.top.equalTo(descriptionLabel.snp.bottom).offset(50)
            make.left.right.equalTo(0)
            make.height.equalTo(120)
        }
        
        contentView.snp.makeConstraints { make in
            make.bottom.equalTo(reviewView.snp.bottom)
        }
    }
    
    private func createRatingView() -> UIView {
        let v = UIView()
        v.backgroundColor = UIColor(red: 1.0, green: 0.0, blue: 1.0, alpha: 1.0)
        
        self.stars = [UIImageView(image: #imageLiteral(resourceName: "ic_star_white")),
                      UIImageView(image: #imageLiteral(resourceName: "ic_star_white")),
                      UIImageView(image: #imageLiteral(resourceName: "ic_star_white")),
                      UIImageView(image: #imageLiteral(resourceName: "ic_star_white")),
                      UIImageView(image: #imageLiteral(resourceName: "ic_star_white"))]
        
        for i in 0..<5 {
            let star = stars[i]
            
            v.addSubview(star)
            star.snp.makeConstraints { make in
                make.centerY.equalTo(v.snp.centerY)
                make.width.height.equalTo(star.superview!.snp.height).dividedBy(2)
                
                if i == 0 {
                    make.left.equalTo(30)
                } else {
                    make.left.equalTo(stars[i-1].snp.right).offset(3)
                }
            }
        }
        
        let durationLabel = UILabel()
        durationLabel.textColor = .white
        durationLabel.font = UIFont.systemFont(ofSize: 15)
        durationLabel.numberOfLines = 0
        v.addSubview(durationLabel)
        self.durationLabel = durationLabel
        durationLabel.snp.makeConstraints { make in
            make.right.equalTo(-30)
            make.centerY.equalToSuperview()
        }
        
        let time = UIImageView(image: #imageLiteral(resourceName: "ic_time_white"))
        v.addSubview(time)
        time.snp.makeConstraints { make in
            make.height.width.equalTo(durationLabel.snp.height)
            make.centerY.equalToSuperview()
            make.right.equalTo(durationLabel.snp.left).offset(-5)
        }
        
        return v
    }
    
    private func createReviewView() -> UIView {
        let v = UIView()
        v.backgroundColor = .blue
        
        let reviewLabel = UILabel()
        reviewLabel.text = "Rate me!"
        reviewLabel.textColor = .white
        reviewLabel.font = UIFont.systemFont(ofSize: 20)
        reviewLabel.numberOfLines = 0
        v.addSubview(reviewLabel)
        reviewLabel.snp.makeConstraints { make in
            make.top.equalTo(25)
            make.centerX.equalToSuperview()
        }
        
        for i in 1...5 {
            let button = UIButton()
            button.setTitle("", for: .normal)
            button.setImage(#imageLiteral(resourceName: "ic_star_grey"), for: .normal)
            button.tag = i
            button.addTarget(self, action: #selector(sendNewRating(sender:)), for: .touchDown)
            
            v.addSubview(button)
            button.snp.makeConstraints { make in
                make.height.width.equalTo(48)
                make.centerX.equalToSuperview().offset((i-3) * 48)
                make.top.equalTo(reviewLabel.snp.bottom).offset(3)
            }
            
            buttons.append(button)
        }
        
        return v
    }
    
    @objc func sendNewRating(sender: UIButton) {
        showLoadingView()
        recipe?.score = Double(sender.tag)
        CRUD.updateRecipeScore(withId: recipe!.id, newScore: Int(recipe!.score), callback: getResponse)
    }
    
    @objc func editRecipe(sender: UIBarButtonItem) {
        let addRecipeViewController = EditRecipeViewController(withRecipe: recipe!)
        let nvc = UINavigationController()
        nvc.viewControllers = [addRecipeViewController]
        self.present(nvc, animated: true, completion: nil)
    }
    
    func getResponse(success: Bool) {
        if (!success) {
            self.recipe?.score = self.score
        } else {
            self.score = self.recipe!.score
            updateView()
        }
        hideLoadingView()
    }
    
    private func showLoadingView() {
        let v = UIView(frame: view.frame)
        v.backgroundColor = UIColor(red: 0, green: 0, blue: 0, alpha: 0.7)
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
    
    private func updateView() {
        navigationItem.title = recipe?.name
        fillDurationLabel()
        fillInfoLabel()
        fillIngredientsLabel()
        fillRatingStars()
        fillReviewStars()
        fillDescriptionLabel()
        view.layoutIfNeeded()
    }
    
    private func fillInfoLabel() {
        self.infoLabel?.text = recipe?.info
    }
    
    private func fillIngredientsLabel() {
        self.ingredientsLabel?.text = ""
        
        if let ings = recipe?.ingredients {
            for i in ings {
                self.ingredientsLabel?.text! += "    •    \(i)\n"
            }
        }
    }
    
    private func fillDescriptionLabel() {
        self.descriptionLabel?.text = recipe?.description
    }
    
    private func fillDurationLabel() {
        self.durationLabel?.text = "\(recipe?.duration ?? 0) min."
    }
    
    private func fillRatingStars() {
        for i in 0..<5 {
            let star = stars[i]
            
            if let r = self.recipe?.score, Int(r) > i {
                star.isHidden = false
            } else {
                star.isHidden = true
            }
        }
    }
    
    private func fillReviewStars() {
        for i in 0..<5 {
            let star = buttons[i]
            
            if let r = self.recipe?.score, Int(r) > i {
                star.setImage(#imageLiteral(resourceName: "ic_star_white"), for: .normal)
            } else {
                star.setImage(#imageLiteral(resourceName: "ic_star_grey"), for: .normal)
            }
        }
    }
}

