/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fit.vwm.mtree.utils;

/**
 *
 * @author mannannlegur
 * @param <U> First class.
 * @param <V> Second class.
 */
public class Pair<U, V> {

    public U first;
    public V second;
    
    public Pair(U u, V v) {
        first = u;
        second = v;
    }    
}
