/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fit.vwm.mtree;

import java.util.List;

/**
 *
 * @author mannannlegur
 */
public interface DistanceFunction {
    public Double compute(List<Double> data1, List<Double> data2);
} 
