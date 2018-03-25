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
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author Andrey Babushkin <andrey.babushkin@surmon.org>
 */
@Entity
@Table(name = "POMODORO")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Pomodoro.findAll", query = "SELECT p FROM Pomodoro p")
    , @NamedQuery(name = "Pomodoro.findByPomodoroId", query = "SELECT p FROM Pomodoro p WHERE p.pomodoroId = :pomodoroId")
    , @NamedQuery(name = "Pomodoro.findByPdate", query = "SELECT p FROM Pomodoro p WHERE p.pdate = :pdate")})
public class Pomodoro implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @NotNull
    @Column(name = "POMODORO_ID")
    private Integer pomodoroId;
    @Basic(optional = false)
    @NotNull
    @Column(name = "pdate")
    @Temporal(TemporalType.DATE)
    private Date pdate;
    @JoinColumn(name = "PERSON_USER_ID", referencedColumnName = "USERS_USER_ID")
    @ManyToOne(optional = false, fetch = FetchType.EAGER)
    private Person personUserId;

    public Pomodoro() {
    }

    public Pomodoro(Integer pomodoroId) {
        this.pomodoroId = pomodoroId;
    }

    public Pomodoro(Integer pomodoroId, Date pdate) {
        this.pomodoroId = pomodoroId;
        this.pdate = pdate;
    }

    public Integer getPomodoroId() {
        return pomodoroId;
    }

    public void setPomodoroId(Integer pomodoroId) {
        this.pomodoroId = pomodoroId;
    }

    public Date getPdate() {
        return pdate;
    }

    public void setPdate(Date pdate) {
        this.pdate = pdate;
    }

    @XmlTransient
    public Person getPersonUserId() {
        return personUserId;
    }

    public void setPersonUserId(Person personUserId) {
        this.personUserId = personUserId;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (pomodoroId != null ? pomodoroId.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Pomodoro)) {
            return false;
        }
        Pomodoro other = (Pomodoro) object;
        if ((this.pomodoroId == null && other.pomodoroId != null) || (this.pomodoroId != null && !this.pomodoroId.equals(other.pomodoroId))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "babusand.db.Pomodoro[ pomodoroId=" + pomodoroId + " ]";
    }
    
}
