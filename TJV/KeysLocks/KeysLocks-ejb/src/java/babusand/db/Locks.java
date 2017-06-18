/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.db;

import java.io.Serializable;
import java.math.BigDecimal;
import java.math.BigInteger;
import javax.persistence.Basic;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToOne;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;
import org.eclipse.persistence.oxm.annotations.XmlInverseReference;

/**
 *
 * @author mannannlegur
 */
@Entity
@Table(name = "LOCKS")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Locks.findAll", query = "SELECT l FROM Locks l")
    , @NamedQuery(name = "Locks.findById", query = "SELECT l FROM Locks l WHERE l.id = :id")
    , @NamedQuery(name = "Locks.findByManufacturer", query = "SELECT l FROM Locks l WHERE l.manufacturer = :manufacturer")
    , @NamedQuery(name = "Locks.findByShape", query = "SELECT l FROM Locks l WHERE l.shape = :shape")
    , @NamedQuery(name = "Locks.findByColor", query = "SELECT l FROM Locks l WHERE l.color = :color")
    , @NamedQuery(name = "Locks.findByWeight", query = "SELECT l FROM Locks l WHERE l.weight = :weight")})
public class Locks implements Serializable {

    private static final long serialVersionUID = 1L;
    // @Max(value=?)  @Min(value=?)//if you know range of your decimal fields consider using these annotations to enforce field validation
    @Id
    @Basic(optional = false)
    @GeneratedValue(strategy = GenerationType.AUTO)
    @Column(name = "ID")
    private BigDecimal id;
    @Basic(optional = false)
    @Column(name = "MANUFACTURER")
    private String manufacturer;
    @Column(name = "SHAPE")
    private String shape;
    @Column(name = "COLOR")
    private String color;
    @Column(name = "WEIGHT")
    private BigInteger weight;
    @OneToOne(cascade = CascadeType.ALL, mappedBy = "locks", fetch = FetchType.EAGER)
    private Keys keys;

    public Locks() {
    }

    public Locks(BigDecimal id) {
        this.id = id;
    }

    public Locks(BigDecimal id, String manufacturer) {
        this.id = id;
        this.manufacturer = manufacturer;
    }

    public BigDecimal getId() {
        return id;
    }

    public void setId(BigDecimal id) {
        this.id = id;
    }

    public String getManufacturer() {
        return manufacturer;
    }

    public void setManufacturer(String manufacturer) {
        this.manufacturer = manufacturer;
    }

    public String getShape() {
        return shape;
    }

    public void setShape(String shape) {
        this.shape = shape;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public BigInteger getWeight() {
        return weight;
    }

    public void setWeight(BigInteger weight) {
        this.weight = weight;
    }
    
    @XmlTransient
    public Keys getKeys() {
        return keys;
    }

    public void setKeys(Keys keys) {
        this.keys = keys;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (id != null ? id.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Locks)) {
            return false;
        }
        Locks other = (Locks) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        String s = "babusand.db.Locks[ id=" + id + ", manufacturer=" + manufacturer;
        if (null != shape)
            s += ", shape=" + shape;
        if (null != color)
            s += ", color=" + color;
        if (null != weight)
            s += ", weight=" + weight;
        if (null != keys)
            s += ", keyId=" + keys.getId();
        
        s += " ]";
        return s;
    }
    
}
