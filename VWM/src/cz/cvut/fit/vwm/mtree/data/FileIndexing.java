/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fit.vwm.mtree.data;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Scanner;


public class FileIndexing {

    private ArrayList<Double> features;
    private final String filePath;

    public FileIndexing(String path) throws IOException {
        filePath = path;
        features = new ArrayList<>(20);
        load();
    }
        
    private void load() throws FileNotFoundException {
        File file = new File(filePath);
        Scanner sc = new Scanner(file);
        try {
            while (true) 
                features.add(sc.nextDouble());
        } catch (NoSuchElementException ex) {}
    }
    
    public List<Double> getFeatures() {
        return features;
    }
    
    public String getFilePath() {
        return filePath;
    }
}
