/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fit.vwm.mtree;

import java.util.Set;
import cz.cvut.fit.vwm.mtree.utils.Pair;

/**
 *
 * @author mannannlegur
 */
public interface PromoteFunction {
    public Pair<IndexedObject, IndexedObject> promote(Set<IndexedObject> elements);
}
