/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fit.vwm.mtree;

import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import org.json.JSONArray;
import org.json.JSONObject;

/**
 *
 * @author mannannlegur
 */
public class IndexedObject {

    public List<Double> features = new ArrayList<>();
    public String filePath = "";
    public double radius = 0.;
    public double distanceToParent = 0.;
    public int childNode = -1;
    public int node = -1;

    public IndexedObject() {
    }

    public IndexedObject(IndexedObject o) {
        this.features = new ArrayList<>(o.features);
        this.filePath = "" + o.filePath;
        this.radius = o.radius;
        this.distanceToParent = o.distanceToParent;
        this.childNode = o.childNode;
        this.node = o.node;
    }

    public String getJSON() {
        JSONObject o = getJSONObject();
        return new String(o.toString().getBytes());
    }

    public JSONObject getJSONObject() {
        JSONObject o = new JSONObject();
        JSONArray feat = new JSONArray(features);
        o.put("features", feat);
        o.put("filePath", filePath);
        o.put("radius", radius);
        o.put("distanceToParent", distanceToParent);
        o.put("childNode", childNode);
        o.put("node", node);

        return o;
    }

    public IndexedObject fromJSON(String json) {
        JSONObject el = new JSONObject(json);

        JSONArray feat = el.getJSONArray("features");
        for (int j = 0; j < feat.length(); j++) {
            this.features.add(feat.optDouble(j));
        }
        this.filePath = el.optString("filePath");
        this.radius = el.optDouble("radius");
        this.distanceToParent = el.optDouble("distanceToParent");
        this.childNode = el.optInt("childNode");
        this.node = el.optInt("node");

        return this;
    }

    public boolean equals(IndexedObject o) {
        return filePath.equals(o.filePath);
//        return features.equals(o.features)
//                && filePath.equals(o.filePath)
//                && (radius - o.radius) < 10e-10
//                && (distanceToParent - o.distanceToParent) < 10e-10
//                && childNode == o.childNode
//                && node == o.node;
    }

    @Override
    public String toString() {
        return getJSON();
    }

    public void printOut(FileOutputStream fos, Integer delimsCnt, char delim) throws IOException {
        String delims = "";
        for (int i = 0; i < delimsCnt; i++)
            delims += delim;
        
        String s = delims + "Object file is " + filePath + '\n' + 
                delims + "Object is in node " + node + '\n' + 
                delims + "Object radius is " + radius + '\n' + 
                delims + "Object distance to parent is " + distanceToParent + '\n' + 
                delims + "Object has child node " + childNode + "\n\n";
                
        fos.write(s.getBytes());
    }
}
