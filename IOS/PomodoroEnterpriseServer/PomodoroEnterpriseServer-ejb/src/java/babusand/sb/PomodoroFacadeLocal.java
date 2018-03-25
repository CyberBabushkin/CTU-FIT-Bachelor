/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.sb;

import babusand.db.Pomodoro;
import java.util.List;
import javax.ejb.Local;

/**
 *
 * @author Andrey Babushkin <andrey.babushkin@surmon.org>
 */
@Local
public interface PomodoroFacadeLocal {

    void create(Pomodoro pomodoro);

    void edit(Pomodoro pomodoro);

    void remove(Pomodoro pomodoro);

    Pomodoro find(Object id);

    List<Pomodoro> findAll();

    List<Pomodoro> findRange(int[] range);

    int count();
    
}
