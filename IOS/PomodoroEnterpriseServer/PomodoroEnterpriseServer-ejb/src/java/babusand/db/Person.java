/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.db;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToOne;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;
import org.eclipse.persistence.oxm.annotations.XmlInverseReference;

/**
 *
 * @author Andrey Babushkin <andrey.babushkin@surmon.org>
 */
@Entity
@Table(name = "PERSON")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Person.findAll", query = "SELECT p FROM Person p")
    , @NamedQuery(name = "Person.findByName", query = "SELECT p FROM Person p WHERE p.name = :name")
    , @NamedQuery(name = "Person.findByFamilyName", query = "SELECT p FROM Person p WHERE p.familyName = :familyName")
    , @NamedQuery(name = "Person.findByUsersUserId", query = "SELECT p FROM Person p WHERE p.usersUserId = :usersUserId")})
public class Person implements Serializable {

    private static final long serialVersionUID = 1L;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "NAME")
    private String name;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "FAMILY_NAME")
    private String familyName;
    @Size(max = 32700)
    @Column(name = "AVATAR")
    private String avatar;
    @Id
    @Basic(optional = false)
    @NotNull
    @Column(name = "USERS_USER_ID")
    private Integer usersUserId;
    @JoinColumn(name = "TEAM_TEAM_ID", referencedColumnName = "TEAM_ID")
    @ManyToOne(fetch = FetchType.EAGER)
    @XmlInverseReference(mappedBy = "personCollection")
    private Team teamTeamId;
    @JoinColumn(name = "USERS_USER_ID", referencedColumnName = "USER_ID", insertable = false, updatable = false)
    @OneToOne(optional = false, fetch = FetchType.EAGER)
    @XmlInverseReference(mappedBy = "person")
    private Users users;

    public Person() {
    }

    public Person(Integer usersUserId) {
        this.usersUserId = usersUserId;
    }

    public Person(Integer usersUserId, String name, String familyName) {
        this.usersUserId = usersUserId;
        this.name = name;
        this.familyName = familyName;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getFamilyName() {
        return familyName;
    }

    public void setFamilyName(String familyName) {
        this.familyName = familyName;
    }

    public String getAvatar() {
        return avatar;
    }

    public void setAvatar(String avatar) {
        this.avatar = avatar;
    }

    public Integer getUsersUserId() {
        return usersUserId;
    }

    public void setUsersUserId(Integer usersUserId) {
        this.usersUserId = usersUserId;
    }

    public Team getTeamTeamId() {
        return teamTeamId;
    }

    public void setTeamTeamId(Team teamTeamId) {
        this.teamTeamId = teamTeamId;
    }

    public Users getUsers() {
        return users;
    }

    public void setUsers(Users users) {
        this.users = users;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (usersUserId != null ? usersUserId.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Person)) {
            return false;
        }
        Person other = (Person) object;
        if ((this.usersUserId == null && other.usersUserId != null) || (this.usersUserId != null && !this.usersUserId.equals(other.usersUserId))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "babusand.db.Person[ usersUserId=" + usersUserId + " ]";
    }
    
}
