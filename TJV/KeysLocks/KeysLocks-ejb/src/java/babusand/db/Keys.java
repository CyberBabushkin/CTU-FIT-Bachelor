/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.db;

import java.io.Serializable;
import java.math.BigDecimal;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToOne;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;
import org.eclipse.persistence.oxm.annotations.XmlInverseReference;

/**
 *
 * @author mannannlegur
 */
@Entity
@Table(name = "KEYS")
@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
@NamedQueries({
    @NamedQuery(name = "Keys.findAll", query = "SELECT k FROM Keys k")
    , @NamedQuery(name = "Keys.findById", query = "SELECT k FROM Keys k WHERE k.id = :id")
    , @NamedQuery(name = "Keys.findByManufacturer", query = "SELECT k FROM Keys k WHERE k.manufacturer = :manufacturer")
    , @NamedQuery(name = "Keys.findByShape", query = "SELECT k FROM Keys k WHERE k.shape = :shape")
    , @NamedQuery(name = "Keys.findByColor", query = "SELECT k FROM Keys k WHERE k.color = :color")})
public class Keys implements Serializable {

    private static final long serialVersionUID = 1L;
    // @Max(value=?)  @Min(value=?)//if you know range of your decimal fields consider using these annotations to enforce field validation
    @Id
    @Basic(optional = false)
    @Column(name = "ID")
    private BigDecimal id;
    @Basic(optional = false)
    @Column(name = "MANUFACTURER")
    private String manufacturer;
    @Column(name = "SHAPE")
    private String shape;
    @Column(name = "COLOR")
    private String color;
    @JoinColumn(name = "ID", referencedColumnName = "ID", insertable = false, updatable = false)
    @OneToOne(optional = false, fetch = FetchType.EAGER)
    @XmlInverseReference(mappedBy = "keys")
    private Locks locks;

    public Keys() {
    }

    public Keys(BigDecimal id) {
        this.id = id;
    }

    public Keys(BigDecimal id, String manufacturer) {
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

    public Locks getLocks() {
        return locks;
    }

    public void setLocks(Locks locks) {
        this.locks = locks;
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
        if (!(object instanceof Keys)) {
            return false;
        }
        Keys other = (Keys) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        String s = "babusand.db.Keys[ id=" + id + ", manufacturer=" + manufacturer;
        if (null != shape)
            s += ", shape=" + shape;
        if (null != color)
            s += ", color=" + color;
        if (null != locks)
            s += ", lockId=" + locks.getId();
        s += " ]";
        return s;
    }
    
}
