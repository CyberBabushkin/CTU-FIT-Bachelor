/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.sb;

import babusand.db.Settings;
import java.util.List;
import javax.ejb.Local;

/**
 *
 * @author Andrey Babushkin <andrey.babushkin@surmon.org>
 */
@Local
public interface SettingsFacadeLocal {

    void create(Settings settings);

    void edit(Settings settings);

    void remove(Settings settings);

    Settings find(Object id);

    List<Settings> findAll();

    List<Settings> findRange(int[] range);

    int count();
    
}
