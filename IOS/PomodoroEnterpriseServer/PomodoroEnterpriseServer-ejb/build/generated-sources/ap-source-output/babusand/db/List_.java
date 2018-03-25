package babusand.db;

import babusand.db.Task;
import babusand.db.Team;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2018-01-21T05:53:41")
@StaticMetamodel(List.class)
public class List_ { 

    public static volatile SingularAttribute<List, Integer> listId;
    public static volatile SingularAttribute<List, Team> teamTeamId;
    public static volatile CollectionAttribute<List, Task> taskCollection;
    public static volatile SingularAttribute<List, String> title;

}