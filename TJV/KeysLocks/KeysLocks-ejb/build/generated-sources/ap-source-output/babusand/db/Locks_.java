package babusand.db;

import babusand.db.Keys;
import java.math.BigDecimal;
import java.math.BigInteger;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2017-01-11T01:58:52")
@StaticMetamodel(Locks.class)
public class Locks_ { 

    public static volatile SingularAttribute<Locks, String> shape;
    public static volatile SingularAttribute<Locks, String> color;
    public static volatile SingularAttribute<Locks, Keys> keys;
    public static volatile SingularAttribute<Locks, BigInteger> weight;
    public static volatile SingularAttribute<Locks, BigDecimal> id;
    public static volatile SingularAttribute<Locks, String> manufacturer;

}