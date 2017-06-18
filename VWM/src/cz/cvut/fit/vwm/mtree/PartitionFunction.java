/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fit.vwm.mtree;

import cz.cvut.fit.vwm.mtree.utils.Pair;
import java.util.Set;

/**
 *
 * @author mannannlegur
 */
public interface PartitionFunction {
    public Pair<Set<IndexedObject>,
                Set<IndexedObject>> partition(Set<IndexedObject> data, 
                                              Pair<IndexedObject, IndexedObject> routingObjects);
}
