//
//  RecipeTableViewCell.swift
//  IOS_DU1
//
//  Created by Andrey Babushkin on 07/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit

class RecipeTableViewCell: UITableViewCell {

    var recipe: Recipe? {
        didSet {
            nameLabel?.text = recipe?.name
            if let d = recipe?.duration {
                durationLabel?.text = "\(Int(d)) min."
            } else {
                durationLabel?.text = "0 - ∞ min. :)"
            }
            
        }
    }
    
    private weak var nameLabel: UILabel?
    private weak var durationLabel: UILabel?
    private var stars: [UIImageView] = [UIImageView(image: #imageLiteral(resourceName: "ic_star")),
                                        UIImageView(image: #imageLiteral(resourceName: "ic_star")),
                                        UIImageView(image: #imageLiteral(resourceName: "ic_star")),
                                        UIImageView(image: #imageLiteral(resourceName: "ic_star")),
                                        UIImageView(image: #imageLiteral(resourceName: "ic_star"))]
    
    override init(style: UITableViewCellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
    override func layoutSubviews() {
        super.layoutSubviews()
        setupView()
    }
    
    private func setupView() {
        contentView.subviews.forEach {view in view.removeFromSuperview()}
        
        let icon = UIImageView(image: #imageLiteral(resourceName: "img_small"))
        contentView.addSubview(icon)
        icon.snp.makeConstraints { make in
            make.left.equalTo(30)
            make.height.width.equalTo(contentView.snp.height).dividedBy(1.5)
            make.centerY.equalTo(contentView.snp.centerY)
        }
        
        let nameLabel = UILabel()
        nameLabel.font = UIFont.systemFont(ofSize: 17)
        nameLabel.textColor = .blue
        nameLabel.text = recipe?.name
        contentView.addSubview(nameLabel)
        self.nameLabel = nameLabel
        nameLabel.snp.makeConstraints { make in
            make.left.equalTo(icon.snp.right).offset(16)
            make.right.equalTo(contentView.snp.rightMargin).offset(-16)
            make.top.equalTo(icon.snp.top)
            make.height.equalTo(icon.snp.height).dividedBy(2)
        }
        
        let clockIcon = UIImageView(image: #imageLiteral(resourceName: "ic_time"))
        contentView.addSubview(clockIcon)
        clockIcon.snp.makeConstraints { make in
            make.height.width.equalTo(icon.snp.width).dividedBy(6.86)
            make.bottom.equalTo(icon.snp.bottom)
            make.left.equalTo(icon.snp.right).offset(16)
        }
        
        let durationLabel = UILabel()
        durationLabel.text = "\(recipe?.duration ?? 0) min."
        durationLabel.font = UIFont.systemFont(ofSize: 15)
        contentView.addSubview(durationLabel)
        self.durationLabel = durationLabel
        durationLabel.snp.makeConstraints { make in
            make.bottom.equalTo(icon.snp.bottom)
            make.left.equalTo(clockIcon.snp.right).offset(16)
            make.right.equalTo(contentView.snp.rightMargin).offset(-16)
            make.height.equalTo(clockIcon.snp.height)
        }
        
        for i in 0..<5 {
            let star = stars[i]
            contentView.addSubview(star)
            
            if let r = recipe?.score, Int(r) >= i + 1 {
                star.isHidden = false
            } else {
                star.isHidden = true
            }
            
            star.snp.makeConstraints { make in
                make.width.height.equalTo(clockIcon.snp.width)
                make.top.equalTo(nameLabel.snp.bottom).offset(3)
                
                if (i == 0) {
                    make.left.equalTo(nameLabel.snp.left)
                } else {
                    let prevStar = stars[i-1]
                    make.left.equalTo(prevStar.snp.right).offset(3)
                }
            }
        }
    }
    
}
