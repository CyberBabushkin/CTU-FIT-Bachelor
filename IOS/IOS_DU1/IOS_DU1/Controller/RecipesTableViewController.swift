//
//  RecipesTableViewController.swift
//  IOS_DU1
//
//  Created by Andrey Babushkin on 07/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit

class RecipesTableViewController: UITableViewController {
    
    var recipesList: [Recipe] = []
    weak var loadingView: UIView?

    override func viewDidLoad() {
        super.viewDidLoad()

        // Uncomment the following line to preserve selection between presentations
        // self.clearsSelectionOnViewWillAppear = false
        
        self.tableView.register(RecipeTableViewCell.self, forCellReuseIdentifier: "recipeCell")
        self.tableView.allowsMultipleSelection = false
        self.navigationItem.rightBarButtonItem = self.editButtonItem
        self.navigationItem.leftBarButtonItem = UIBarButtonItem(image: #imageLiteral(resourceName: "ic_add"),
                                                                style: .plain,
                                                                target: self,
                                                                action: #selector(addRecipe(sender:)))
    }
    
    override func loadView() {
        super.loadView()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        if let ip = tableView.indexPathForSelectedRow {
            tableView.deselectRow(at: ip, animated: true)
        }
        showLoadingView()
        CRUD.getAllRecipes(callback: reloadTable(_:))
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    // MARK: - Table view data source

    override func numberOfSections(in tableView: UITableView) -> Int {
        // #warning Incomplete implementation, return the number of sections
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // #warning Incomplete implementation, return the number of rows
        return recipesList.count
    }

    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let dequeued = tableView.dequeueReusableCell(withIdentifier: "recipeCell")
        let cell = (dequeued as? RecipeTableViewCell) ?? RecipeTableViewCell()
        let rec = self.recipesList[indexPath.row]
        cell.recipe = rec
        return cell
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
            showLoadingView()
            self.deletedIP = indexPath
            CRUD.delete(id: recipesList[indexPath.row].id, callback: deletedOnServer)
        } else if editingStyle == .insert {
            // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
        }    
    }
    
    var deletedIP: IndexPath?
    
    func deletedOnServer(withSuccess suc:Bool) {
        hideLoadingView()
        
        if let ip = self.deletedIP, suc {
            self.recipesList.remove(at: ip.row)
            tableView.deleteRows(at: [ip], with: .fade)
        }
        
        self.deletedIP = nil
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let cell = self.tableView(tableView, cellForRowAt: indexPath) as! RecipeTableViewCell
        showLoadingView()
        CRUD.getRecipe(withID: cell.recipe!.id, callback: receivedRecipe)
        
        self.tableView.deselectRow(at: indexPath, animated: true)
    }
    
    override func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return tableView.frame.width / 2.88
    }
   
    func reloadTable(_ recipes: [Recipe]) {
        self.recipesList = recipes
        self.tableView.reloadData()
        hideLoadingView()
    }
    
    @objc private func addRecipe(sender: UIBarButtonItem) {
        let addRecipeViewController = EditRecipeViewController(createNew: true)
        let nvc = UINavigationController()
        nvc.viewControllers = [addRecipeViewController]
        self.present(nvc, animated: true, completion: nil)
    }
    
    private func receivedRecipe(recipe: RecipeDetailed) {
        let vc = DetailViewController()
        vc.recipe = recipe
        hideLoadingView()
        navigationController?.pushViewController(vc, animated: true)
    }
    
    private func showLoadingView() {
        let v = UIView(frame: self.tableView.frame)
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

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
