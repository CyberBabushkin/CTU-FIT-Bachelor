/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.sb.local;

import babusand.db.Locks;
import java.util.List;
import javax.ejb.Local;

/**
 *
 * @author mannannlegur
 */
@Local
public interface LocksFacadeLocal {

    void create(Locks locks);

    void edit(Locks locks);

    void remove(Locks locks);

    Locks find(Object id);

    List<Locks> findAll();

    List<Locks> findRange(int[] range);

    int count();
    
}
