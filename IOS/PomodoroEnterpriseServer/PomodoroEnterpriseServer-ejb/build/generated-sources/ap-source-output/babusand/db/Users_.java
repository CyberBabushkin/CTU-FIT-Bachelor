package babusand.db;

import babusand.db.Person;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2018-01-21T05:53:41")
@StaticMetamodel(Users.class)
public class Users_ { 

    public static volatile SingularAttribute<Users, String> password;
    public static volatile SingularAttribute<Users, Person> person;
    public static volatile SingularAttribute<Users, String> login;
    public static volatile SingularAttribute<Users, Integer> userId;

}