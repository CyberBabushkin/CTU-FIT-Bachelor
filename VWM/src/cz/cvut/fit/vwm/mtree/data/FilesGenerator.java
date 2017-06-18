/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fit.vwm.mtree.data;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author mannannlegur
 */
public class FilesGenerator {

    public static void create(String directory, Integer features, Integer files, Double min, Double max) {

        File f = new File(directory);
        f.mkdirs();
        String fullPath = f.toURI().toString();
        
        if (fullPath.charAt(fullPath.length() - 1) != '/')
            fullPath += '/';
        
        try {
            Random r = new Random();

            for (int i = 1; i <= files; i++) {
                String s = "";
                
                File file = new File(new URI(fullPath + i + ".file"));
                FileWriter fw = new FileWriter(file);

                for (int j = 0; j < features; j++) {
                    Double d = r.nextDouble() * (max - min) + min;
                    s += d.toString();
                    if (j != features - 1) {
                        s += "\n";
                    }
                }

                fw.write(s);
                fw.close();
            }
        } catch (IOException | URISyntaxException ex) {
            Logger.getLogger(FilesGenerator.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
