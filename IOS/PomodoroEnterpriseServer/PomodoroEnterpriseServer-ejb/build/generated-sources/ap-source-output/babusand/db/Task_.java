package babusand.db;

import babusand.db.List;
import java.util.Date;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2018-01-21T05:53:41")
@StaticMetamodel(Task.class)
public class Task_ { 

    public static volatile SingularAttribute<Task, List> listListId;
    public static volatile SingularAttribute<Task, String> name;
    public static volatile SingularAttribute<Task, Date> dateFinish;
    public static volatile SingularAttribute<Task, Integer> taskId;
    public static volatile SingularAttribute<Task, String> info;

}