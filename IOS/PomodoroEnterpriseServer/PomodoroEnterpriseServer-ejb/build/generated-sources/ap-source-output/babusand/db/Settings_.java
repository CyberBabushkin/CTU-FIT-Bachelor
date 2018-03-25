package babusand.db;

import babusand.db.Person;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2018-01-21T05:53:41")
@StaticMetamodel(Settings.class)
public class Settings_ { 

    public static volatile SingularAttribute<Settings, Integer> personUsersUserId;
    public static volatile SingularAttribute<Settings, Integer> breakTime;
    public static volatile SingularAttribute<Settings, Person> person;
    public static volatile SingularAttribute<Settings, Integer> pomodoroTime;
    public static volatile SingularAttribute<Settings, Integer> pomodoroGoal;
    public static volatile SingularAttribute<Settings, Integer> taskGoal;

}