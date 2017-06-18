/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package keyslocksclient.view;

/**
 *
 * @author mannannlegur
 */
public class Narrator {

    public Narrator() {
        System.out.println("Welcome to the KeysLocks REST Client!\n");
    }
    
    public void chooseAction() {
        System.out.println("What do you want to do? \n"
                    + "1 - Create a new item\n"
                    + "2 - List all entities\n"
                    + "3 - Edit an item\n"
                    + "4 - Delete an item\n"
                    + "5 - Exit\n");
        input();
    }
    
    public void chooseEntities() {
        System.out.println("What entity would you like to choose? \n"
                + "1 - Keys\n"
                + "2 - Locks\n");
        input();
    }
    
    public void invalidNumber() {
        System.err.println("Please enter a correct number.");
        input();
        
    }
    
    public void id() {
        System.out.println("Enter an id:");
        input();
    }
    
    public void newId() {
        System.out.println("Enter an new id:");
        input();
    }
    
    public void manufacturer() {
        System.out.println("Enter a manufacturer:");
        input();
    }
    
    public void color() {
        System.out.println("Enter a color:");
        input();
    }
    
    public void shape() {
        System.out.println("Enter a shape:");
        input();
    }
    
    public void weight() {
        System.out.println("Enter a weight:");
        input();
    }
    
    public void editKeys() {
        System.out.println("What field do you want to edit?\n"
                + "1 - Id"
                + "2 - Manufacturer\n"
                + "3 - Shape\n"
                + "4 - Color\n");
        input();
    }
    
    public void editLocks() {
        System.out.println("What field do you want to edit?\n"
                + "1 - Manufacturer\n"
                + "2 - Shape\n"
                + "3 - Color\n"
                + "4 - Weight\n");
        input();
    }
    
    private void input() {
        System.out.print(" >> ");
    }
}
