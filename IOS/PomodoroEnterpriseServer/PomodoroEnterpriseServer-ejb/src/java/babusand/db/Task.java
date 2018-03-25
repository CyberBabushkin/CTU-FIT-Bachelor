/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.db;

import java.io.Serializable;
import java.util.Date;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import org.eclipse.persistence.oxm.annotations.XmlInverseReference;

/**
 *
 * @author Andrey Babushkin <andrey.babushkin@surmon.org>
 */
@Entity
@Table(name = "TASK")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Task.findAll", query = "SELECT t FROM Task t")
    , @NamedQuery(name = "Task.findByTaskId", query = "SELECT t FROM Task t WHERE t.taskId = :taskId")
    , @NamedQuery(name = "Task.findByName", query = "SELECT t FROM Task t WHERE t.name = :name")
    , @NamedQuery(name = "Task.findByInfo", query = "SELECT t FROM Task t WHERE t.info = :info")
    , @NamedQuery(name = "Task.findByDateFinish", query = "SELECT t FROM Task t WHERE t.dateFinish = :dateFinish")})
public class Task implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @NotNull
    @Column(name = "TASK_ID")
    private Integer taskId;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "NAME")
    private String name;
    @Size(max = 255)
    @Column(name = "INFO")
    private String info;
    @Column(name = "DATE_FINISH")
    @Temporal(TemporalType.DATE)
    private Date dateFinish;
    @JoinColumn(name = "LIST_LIST_ID", referencedColumnName = "LIST_ID")
    @ManyToOne(optional = false, fetch = FetchType.EAGER)
    @XmlInverseReference(mappedBy = "taskCollection")
    private List listListId;

    public Task() {
    }

    public Task(Integer taskId) {
        this.taskId = taskId;
    }

    public Task(Integer taskId, String name) {
        this.taskId = taskId;
        this.name = name;
    }

    public Integer getTaskId() {
        return taskId;
    }

    public void setTaskId(Integer taskId) {
        this.taskId = taskId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getInfo() {
        return info;
    }

    public void setInfo(String info) {
        this.info = info;
    }

    public Date getDateFinish() {
        return dateFinish;
    }

    public void setDateFinish(Date dateFinish) {
        this.dateFinish = dateFinish;
    }

    public List getListListId() {
        return listListId;
    }

    public void setListListId(List listListId) {
        this.listListId = listListId;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (taskId != null ? taskId.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Task)) {
            return false;
        }
        Task other = (Task) object;
        if ((this.taskId == null && other.taskId != null) || (this.taskId != null && !this.taskId.equals(other.taskId))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "babusand.db.Task[ taskId=" + taskId + " ]";
    }
    
}
