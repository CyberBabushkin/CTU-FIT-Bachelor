/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package keyslocksclient.model;

import org.json.JSONArray;
import org.json.JSONObject;

public class LocksREST {
    private final AbstractREST REST = new 
        AbstractREST("http://localhost:8080/KeysLocks-war/webresources/babusand.db.locks");
    
    public void create(int id, String manufacturer, String color, String shape, int weight) {
        JSONObject lock = new JSONObject();
        lock.put("id", id);
        lock.put("manufacturer", manufacturer);
        lock.put("color", color);
        lock.put("shape", shape);
        lock.put("weight", weight);
        
        REST.create(lock);
    }
    
    public void edit(int id, String manufacturer, String color, String shape, int weight) {
        JSONObject lock = find(id);
        lock.put("manufacturer", manufacturer);
        lock.put("color", color);
        lock.put("shape", shape);
        lock.put("weight", weight);
        
        REST.edit(id, lock);
    }
    
    public void delete(int id) {
        REST.delete(id);
    }
    
    public JSONArray findAll() {
        return REST.findAll();
    }
    
    public JSONObject find(int id) {
        return REST.find(id);
    }
    
}
