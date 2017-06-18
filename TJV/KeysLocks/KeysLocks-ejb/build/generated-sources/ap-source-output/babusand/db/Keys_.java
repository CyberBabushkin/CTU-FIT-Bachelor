package babusand.db;

import babusand.db.Locks;
import java.math.BigDecimal;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2017-01-11T01:58:52")
@StaticMetamodel(Keys.class)
public class Keys_ { 

    public static volatile SingularAttribute<Keys, String> shape;
    public static volatile SingularAttribute<Keys, String> color;
    public static volatile SingularAttribute<Keys, BigDecimal> id;
    public static volatile SingularAttribute<Keys, Locks> locks;
    public static volatile SingularAttribute<Keys, String> manufacturer;

}