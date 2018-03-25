package babusand.db;

import babusand.db.List;
import babusand.db.Person;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2018-01-21T05:53:41")
@StaticMetamodel(Team.class)
public class Team_ { 

    public static volatile SingularAttribute<Team, Integer> teamId;
    public static volatile CollectionAttribute<Team, Person> personCollection;
    public static volatile SingularAttribute<Team, String> name;
    public static volatile CollectionAttribute<Team, List> listCollection;

}