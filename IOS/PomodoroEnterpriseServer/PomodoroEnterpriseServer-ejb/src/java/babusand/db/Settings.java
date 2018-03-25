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
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToOne;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;
import org.eclipse.persistence.oxm.annotations.XmlInverseReference;

/**
 *
 * @author Andrey Babushkin <andrey.babushkin@surmon.org>
 */
@Entity
@Table(name = "SETTINGS")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Settings.findAll", query = "SELECT s FROM Settings s")
    , @NamedQuery(name = "Settings.findByBreakTime", query = "SELECT s FROM Settings s WHERE s.breakTime = :breakTime")
    , @NamedQuery(name = "Settings.findByPomodoroTime", query = "SELECT s FROM Settings s WHERE s.pomodoroTime = :pomodoroTime")
    , @NamedQuery(name = "Settings.findByPomodoroGoal", query = "SELECT s FROM Settings s WHERE s.pomodoroGoal = :pomodoroGoal")
    , @NamedQuery(name = "Settings.findByTaskGoal", query = "SELECT s FROM Settings s WHERE s.taskGoal = :taskGoal")
    , @NamedQuery(name = "Settings.findByPersonUsersUserId", query = "SELECT s FROM Settings s WHERE s.personUsersUserId = :personUsersUserId")})
public class Settings implements Serializable {

    private static final long serialVersionUID = 1L;
    @Basic(optional = false)
    @NotNull
    @Column(name = "BREAK_TIME")
    private int breakTime;
    @Basic(optional = false)
    @NotNull
    @Column(name = "POMODORO_TIME")
    private int pomodoroTime;
    @Basic(optional = false)
    @NotNull
    @Column(name = "POMODORO_GOAL")
    private int pomodoroGoal;
    @Basic(optional = false)
    @NotNull
    @Column(name = "TASK_GOAL")
    private int taskGoal;
    @Id
    @Basic(optional = false)
    @NotNull
    @Column(name = "PERSON_USERS_USER_ID")
    private Integer personUsersUserId;
    @JoinColumn(name = "PERSON_USERS_USER_ID", referencedColumnName = "USERS_USER_ID", insertable = false, updatable = false)
    @OneToOne(optional = false, fetch = FetchType.EAGER)
    private Person person;

    public Settings() {
    }

    public Settings(Integer personUsersUserId) {
        this.personUsersUserId = personUsersUserId;
    }

    public Settings(Integer personUsersUserId, int breakTime, int pomodoroTime, int pomodoroGoal, int taskGoal) {
        this.personUsersUserId = personUsersUserId;
        this.breakTime = breakTime;
        this.pomodoroTime = pomodoroTime;
        this.pomodoroGoal = pomodoroGoal;
        this.taskGoal = taskGoal;
    }

    public int getBreakTime() {
        return breakTime;
    }

    public void setBreakTime(int breakTime) {
        this.breakTime = breakTime;
    }

    public int getPomodoroTime() {
        return pomodoroTime;
    }

    public void setPomodoroTime(int pomodoroTime) {
        this.pomodoroTime = pomodoroTime;
    }

    public int getPomodoroGoal() {
        return pomodoroGoal;
    }

    public void setPomodoroGoal(int pomodoroGoal) {
        this.pomodoroGoal = pomodoroGoal;
    }

    public int getTaskGoal() {
        return taskGoal;
    }

    public void setTaskGoal(int taskGoal) {
        this.taskGoal = taskGoal;
    }

    public Integer getPersonUsersUserId() {
        return personUsersUserId;
    }

    public void setPersonUsersUserId(Integer personUsersUserId) {
        this.personUsersUserId = personUsersUserId;
    }

    @XmlTransient
    public Person getPerson() {
        return person;
    }

    public void setPerson(Person person) {
        this.person = person;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (personUsersUserId != null ? personUsersUserId.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Settings)) {
            return false;
        }
        Settings other = (Settings) object;
        if ((this.personUsersUserId == null && other.personUsersUserId != null) || (this.personUsersUserId != null && !this.personUsersUserId.equals(other.personUsersUserId))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "babusand.db.Settings[ personUsersUserId=" + personUsersUserId + " ]";
    }
    
}
