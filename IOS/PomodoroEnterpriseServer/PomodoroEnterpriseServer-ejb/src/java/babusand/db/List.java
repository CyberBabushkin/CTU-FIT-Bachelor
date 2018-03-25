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
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
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
@Table(name = "LIST")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "List.findAll", query = "SELECT l FROM List l")
    , @NamedQuery(name = "List.findByListId", query = "SELECT l FROM List l WHERE l.listId = :listId")
    , @NamedQuery(name = "List.findByTitle", query = "SELECT l FROM List l WHERE l.title = :title")})
public class List implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @NotNull
    @Column(name = "LIST_ID")
    private Integer listId;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "TITLE")
    private String title;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "listListId", fetch = FetchType.EAGER)
    private Collection<Task> taskCollection;
    @JoinColumn(name = "TEAM_TEAM_ID", referencedColumnName = "TEAM_ID")
    @ManyToOne(optional = false, fetch = FetchType.EAGER)
    @XmlInverseReference(mappedBy = "listCollection")
    private Team teamTeamId;

    public List() {
    }

    public List(Integer listId) {
        this.listId = listId;
    }

    public List(Integer listId, String title) {
        this.listId = listId;
        this.title = title;
    }

    public Integer getListId() {
        return listId;
    }

    public void setListId(Integer listId) {
        this.listId = listId;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    @XmlTransient
    public Collection<Task> getTaskCollection() {
        return taskCollection;
    }

    public void setTaskCollection(Collection<Task> taskCollection) {
        this.taskCollection = taskCollection;
    }

    public Team getTeamTeamId() {
        return teamTeamId;
    }

    public void setTeamTeamId(Team teamTeamId) {
        this.teamTeamId = teamTeamId;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (listId != null ? listId.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof List)) {
            return false;
        }
        List other = (List) object;
        if ((this.listId == null && other.listId != null) || (this.listId != null && !this.listId.equals(other.listId))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "babusand.db.List[ listId=" + listId + " ]";
    }
    
}
