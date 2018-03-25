/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.service;

import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author Andrey Babushkin <andrey.babushkin@surmon.org>
 */
@XmlRootElement
public class TeamMember {
    public String name;
    public String familyName;
    public String avatar;
    public Integer taskGoal;
    public Integer pomodoroGoal;
    public Integer pomodorosFinished;
    public Integer tasksDone;

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

    public Integer getTaskGoal() {
        return taskGoal;
    }

    public void setTaskGoal(Integer taskGoal) {
        this.taskGoal = taskGoal;
    }

    public Integer getPomodoroGoal() {
        return pomodoroGoal;
    }

    public void setPomodoroGoal(Integer pomodoroGoal) {
        this.pomodoroGoal = pomodoroGoal;
    }

    public Integer getPomodorosFinished() {
        return pomodorosFinished;
    }

    public void setPomodorosFinished(Integer pomodorosFinished) {
        this.pomodorosFinished = pomodorosFinished;
    }

    public Integer getTasksDone() {
        return tasksDone;
    }

    public void setTasksDone(Integer tasksDone) {
        this.tasksDone = tasksDone;
    }
    
    
}
