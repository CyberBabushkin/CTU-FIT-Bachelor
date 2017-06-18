/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fit.vwm.mtree;

import cz.cvut.fit.vwm.mtree.utils.Pair;
import java.io.IOException;
import java.util.List;

/**
 *
 * @author mannannlegur
 */
public interface MTree {
    
    public static class MTreeInvalidIndexException extends Exception {};
    
    public void insert(List<Double> features, String filePath) throws MTreeInvalidIndexException, IOException;
    public List<Pair<String, List<Double>>> kNN(List<Double> q, Integer k) throws IOException;
    public List<Pair<String, List<Double>>> rangeQuery(List<Double> q, Double r) throws IOException;
}