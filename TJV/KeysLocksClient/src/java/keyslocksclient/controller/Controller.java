/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package keyslocksclient.controller;

import java.util.Scanner;
import keyslocksclient.model.KeysREST;
import keyslocksclient.model.LocksREST;
import keyslocksclient.view.Narrator;

public class Controller {
    
    private static final Narrator NARRATOR = new Narrator();
    
    private static final LocksREST LOCKS_REST = new LocksREST();
    private static final KeysREST KEYS_REST = new KeysREST();
    
    private static final int CREATE = 1;
    private static final int READ = 2;
    private static final int UPDATE = 3;
    private static final int DELETE = 4;
    private static final int END = 5;
    final static int [] ALLOWED_ACTIONS = {CREATE, READ, UPDATE, DELETE, END};
    
    private static final int KEYS = 1;
    private static final int LOCKS = 2;
    private static final int [] ALLOWED_ENTITIES = {KEYS, LOCKS};
    
    private static int action = 0;
    private static int entity = 0;
    
    private static final Scanner IN = new Scanner(System.in);
    
    public static void run() {
        chooseAction();
    }
    
    private static void chooseAction() {        
        while (action != END) {
            
            NARRATOR.chooseAction();
                    
            try {
                action = IN.nextInt();
                IN.nextLine();
                if (! checkInput(action, ALLOWED_ACTIONS)) {
                    throw new Exception();
                }
                
                if (action != END)
                    chooseEntities();
                
            } catch (Exception ex) {
                NARRATOR.invalidNumber();
                action = 0;
            }
        }
    }
    
    private static void chooseEntities() {
        
        NARRATOR.chooseEntities();
        
        try {
            entity = IN.nextInt();
            IN.nextLine();
            if (!checkInput(entity, ALLOWED_ENTITIES)) {
                throw new Exception();
            }
            
            performAction();
        } catch (Exception ex) {
            NARRATOR.invalidNumber();
            entity = 0;
        }
    }
    
    private static void performAction() {
        switch (action) {
            case CREATE:
                add();
                break;
            case UPDATE:
                edit();
                break;
            case DELETE:
                remove();
                break;
            case END:
                break;
            case READ:
                if (entity == KEYS)
                    for (Object obj : KEYS_REST.findAll().toList()) {
                        System.out.println(obj.toString());
                    }
                else if (entity == LOCKS)
                    for (Object obj : LOCKS_REST.findAll().toList()) {
                        System.out.println(obj.toString());
                    }
                System.out.println("\n");
                break;
        }
    }
    
    private static void add() {
        int id;
        String manufacturer;
        String shape;
        String color;
        int weight;
                
        NARRATOR.newId();
        id = nextIntFromInput();
        
        while (id == 0)
        {
            NARRATOR.invalidNumber();
            id = nextIntFromInput();
        }
        
        NARRATOR.manufacturer();
        manufacturer = IN.nextLine();
        
        NARRATOR.shape();
        shape = IN.nextLine();
        
        NARRATOR.color();
        color = IN.nextLine();
        
        if (entity == LOCKS) {
            NARRATOR.weight();
            weight = nextIntFromInput();
            
            LOCKS_REST.create(id, manufacturer, color, shape, weight);
        } else if (entity == KEYS) {
            KEYS_REST.create(id, manufacturer, color, shape);
        }
    }
    
    private static void edit() {
        int choice;
        int id;
        int idn = 0;
        String manufacturer;
        String shape;
        String color;
        int weight;
                
        NARRATOR.id();
        id = nextIntFromInput();
        
        if (entity == KEYS) 
        {
            NARRATOR.newId();
            idn = nextIntFromInput();
        }
        
        NARRATOR.manufacturer();
        manufacturer = IN.nextLine();
        
        NARRATOR.shape();
        shape = IN.nextLine();
        
        NARRATOR.color();
        color = IN.nextLine();
        
        if (entity == LOCKS) 
        {
            NARRATOR.weight();
            weight = nextIntFromInput();
            
            LOCKS_REST.edit(id, manufacturer, color, shape, weight);
        } else if (entity == KEYS) {
            if (idn != id && idn != 0)
                KEYS_REST.delete(id);
            
            KEYS_REST.edit(idn, manufacturer, color, shape);
        }
        
        
    }
    
    private static void remove() {
        NARRATOR.id();
        
        int id = nextIntFromInput();
        
        if (entity == LOCKS) 
            LOCKS_REST.delete(id);
        else if (entity == KEYS)
            KEYS_REST.delete(id);
    }
    
    private static int nextIntFromInput() {
        int n = IN.nextInt();
        IN.nextLine();
        return n;
    }
    
    private static boolean checkInput(int input, int [] allowedValues) {
        boolean contains = false;
        
        for (int i = 0; i < allowedValues.length; i++)
            if (allowedValues[i] == input) {
                contains = true;
                break;
            }
        
        return contains;
    }
}
