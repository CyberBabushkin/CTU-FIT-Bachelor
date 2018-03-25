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
public class PersonAnonymized {
    String name;
    String familyName;

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
    
    
}
