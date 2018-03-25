/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.db;

import java.io.Serializable;
import java.util.Collection;
import javax.persistence.Basic;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author Andrey Babushkin <andrey.babushkin@surmon.org>
 */
@Entity
@Table(name = "TEAM")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Team.findAll", query = "SELECT t FROM Team t")
    , @NamedQuery(name = "Team.findByTeamId", query = "SELECT t FROM Team t WHERE t.teamId = :teamId")
    , @NamedQuery(name = "Team.findByName", query = "SELECT t FROM Team t WHERE t.name = :name")})
public class Team implements Serializable {

    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "NAME")
    private String name;

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @NotNull
    @Column(name = "TEAM_ID")
    private Integer teamId;
    @OneToMany(mappedBy = "teamTeamId", fetch = FetchType.EAGER)
    private Collection<Person> personCollection;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "teamTeamId", fetch = FetchType.EAGER)
    private Collection<List> listCollection;

    public Team() {
    }

    public Team(Integer teamId) {
        this.teamId = teamId;
    }

    public Team(Integer teamId, String name) {
        this.teamId = teamId;
        this.name = name;
    }

    public Integer getTeamId() {
        return teamId;
    }

    public void setTeamId(Integer teamId) {
        this.teamId = teamId;
    }


    @XmlTransient
    public Collection<Person> getPersonCollection() {
        return personCollection;
    }

    public void setPersonCollection(Collection<Person> personCollection) {
        this.personCollection = personCollection;
    }

    @XmlTransient
    public Collection<List> getListCollection() {
        return listCollection;
    }

    public void setListCollection(Collection<List> listCollection) {
        this.listCollection = listCollection;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (teamId != null ? teamId.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Team)) {
            return false;
        }
        Team other = (Team) object;
        if ((this.teamId == null && other.teamId != null) || (this.teamId != null && !this.teamId.equals(other.teamId))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "babusand.db.Team[ teamId=" + teamId + " ]";
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
    
}
