/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package keyslocksclient.model;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpDelete;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.methods.HttpPut;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.HttpClientBuilder;
import org.json.JSONArray;
import org.json.JSONObject;

public class AbstractREST {
    private final HttpClient CLIENT = HttpClientBuilder.create().build();
    private final String BASE_URL;

    public AbstractREST(String base) {
        BASE_URL = base;
    }
    
    void create(JSONObject obj) {
        try {
            HttpPost request = new HttpPost(BASE_URL);
            StringEntity input = new StringEntity(obj.toString());
            input.setContentType("application/json");
            
            request.setEntity(input);
            
            HttpResponse response = CLIENT.execute(request);
            
            if (response.getStatusLine().getStatusCode() != 204) {
                throw new RuntimeException("Failed : HTTP error code : "
                        + response.getStatusLine().getStatusCode());
            }
            
        } catch (IOException|RuntimeException ex) {
            ex.printStackTrace();
        }
    }
    
    public void edit(int id, JSONObject obj) {
        try {
            HttpPut request = new HttpPut(BASE_URL + "/" + id);
            StringEntity input = new StringEntity(obj.toString());
            input.setContentType("application/json");
            request.setEntity(input);
            
            HttpResponse response = CLIENT.execute(request);
            
            if (response.getStatusLine().getStatusCode() != 204) {
                throw new RuntimeException("Failed : HTTP error code : "
                        + response.getStatusLine().getStatusCode());
            }
            
        } catch (IOException|RuntimeException ex) {
            ex.printStackTrace();
        }
    }
    
    public JSONObject find(int id) {
        HttpGet request = new HttpGet(BASE_URL + "/" + id);
        request.addHeader("accept", "application/json");
        
        try {
            HttpResponse response = CLIENT.execute(request);
            StringBuilder result = manageResponse(response);
            JSONObject obj = new JSONObject(result.toString());            
            
            return obj;
                    
        } catch (IOException|RuntimeException ex) {
            ex.printStackTrace();
        }
        
        return new JSONObject();
    }
    
    public JSONArray findAll() {
        HttpGet request = new HttpGet(BASE_URL);
        request.addHeader("accept", "application/json");
        
        try {
            HttpResponse response = CLIENT.execute(request);
            StringBuilder result = manageResponse(response);
            JSONArray array = new JSONArray(result.toString());            
            
            return array;
                    
        } catch (IOException|RuntimeException ex) {
            ex.printStackTrace();
        }
        
        return new JSONArray();
    }
    
    public void delete(int id) {
        try {
            HttpDelete request = new HttpDelete(BASE_URL + "/" + id);
            HttpResponse response = CLIENT.execute(request);
            
            if (response.getStatusLine().getStatusCode() != 204) {
                throw new RuntimeException("Failed : HTTP error code : "
                        + response.getStatusLine().getStatusCode());
            }
        } catch (IOException|RuntimeException ex) {
            ex.printStackTrace();
        }
    }
    
    private StringBuilder manageResponse(HttpResponse response) {
        try {
            
            if (response.getStatusLine().getStatusCode() != 200) {
                throw new RuntimeException("Failed : HTTP error code : "
			   + response.getStatusLine().getStatusCode());
            }
            
            BufferedReader rd = new BufferedReader(
                    new InputStreamReader(response.getEntity().getContent()));
            
            StringBuilder result = new StringBuilder();
            String line;
            while ((line = rd.readLine()) != null) {
                result.append(line);
            }
            
            return result;
                    
        } catch (IOException|RuntimeException ex) {
            ex.printStackTrace();
        }
        
        return new StringBuilder();
    }
}
