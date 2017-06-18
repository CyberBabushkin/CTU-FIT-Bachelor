/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package keyslocksclient.model;

import org.json.JSONArray;
import org.json.JSONObject;

public class KeysREST {
    
    private final AbstractREST REST = new AbstractREST(
            "http://localhost:8080/KeysLocks-war/webresources/babusand.db.keys");
    
    public void create(int id, String manufacturer, String color, String shape) {
        JSONObject key = new JSONObject();
        key.put("id", id);
        key.put("manufacturer", manufacturer);
        key.put("color", color);
        key.put("shape", shape);
        
        REST.create(key);
    }
    
    public void edit(int id, String manufacturer, String color, String shape) {
        JSONObject key = find(id);
        key.put("manufacturer", manufacturer);
        key.put("color", color);
        key.put("shape", shape);
        
        REST.edit(id, key);
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
