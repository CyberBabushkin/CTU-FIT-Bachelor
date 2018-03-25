package babusand.db;

import babusand.db.Team;
import babusand.db.Users;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2018-01-21T05:53:41")
@StaticMetamodel(Person.class)
public class Person_ { 

    public static volatile SingularAttribute<Person, Team> teamTeamId;
    public static volatile SingularAttribute<Person, String> familyName;
    public static volatile SingularAttribute<Person, String> name;
    public static volatile SingularAttribute<Person, Integer> usersUserId;
    public static volatile SingularAttribute<Person, String> avatar;
    public static volatile SingularAttribute<Person, Users> users;

}