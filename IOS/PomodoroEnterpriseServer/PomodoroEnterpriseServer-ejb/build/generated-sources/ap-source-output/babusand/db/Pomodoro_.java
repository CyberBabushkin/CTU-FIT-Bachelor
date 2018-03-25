package babusand.db;

import babusand.db.Person;
import java.util.Date;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2018-01-21T05:53:41")
@StaticMetamodel(Pomodoro.class)
public class Pomodoro_ { 

    public static volatile SingularAttribute<Pomodoro, Integer> pomodoroId;
    public static volatile SingularAttribute<Pomodoro, Date> pdate;
    public static volatile SingularAttribute<Pomodoro, Person> personUserId;

}