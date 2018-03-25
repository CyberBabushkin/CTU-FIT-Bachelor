/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.sb;

import babusand.db.Task;
import java.util.List;
import javax.ejb.Local;

/**
 *
 * @author Andrey Babushkin <andrey.babushkin@surmon.org>
 */
@Local
public interface TaskFacadeLocal {

    void create(Task task);

    void edit(Task task);

    void remove(Task task);

    Task find(Object id);

    List<Task> findAll();

    List<Task> findRange(int[] range);

    int count();
    
}
