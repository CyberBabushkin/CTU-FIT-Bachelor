/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.sb.local;

import babusand.db.Keys;
import java.util.List;
import javax.ejb.Local;

/**
 *
 * @author mannannlegur
 */
@Local
public interface KeysFacadeLocal {

    void create(Keys keys);

    void edit(Keys keys);

    void remove(Keys keys);

    Keys find(Object id);

    List<Keys> findAll();

    List<Keys> findRange(int[] range);

    int count();
    
}
