/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fit.vwm.mtree.data;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.List;
import java.util.Scanner;

/**
 *
 * @author mannannlegur
 */
public class DataObject {

    private List<Double> features;
    private final String filepath;
    
    public DataObject(String filepath, Integer length) throws FileNotFoundException {
        this.filepath = filepath;
        File file = new File(filepath);
        
        Scanner scanner = new Scanner(file);

        for (int i = 0; i < length; i++) {
            Double d = scanner.nextDouble();
            features.add(d);
        }
    }

    public List<Double> getFeatures() {
        return features;
    }
}
