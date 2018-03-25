/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.service;

import java.util.Set;
import javax.ws.rs.core.Application;

/**
 *
 * @author mannannlegur
 */
@javax.ws.rs.ApplicationPath("webresources")
public class ApplicationConfig extends Application {

    @Override
    public Set<Class<?>> getClasses() {
        Set<Class<?>> resources = new java.util.HashSet<>();
        addRestResourceClasses(resources);
        return resources;
    }

    /**
     * Do not modify addRestResourceClasses() method.
     * It is automatically populated with
     * all resources defined in the project.
     * If required, comment out calling this method in getClasses().
     */
    private void addRestResourceClasses(Set<Class<?>> resources) {
        resources.add(babusand.service.DebugExceptionMapper.class);
        resources.add(babusand.service.ListFacadeREST.class);
        resources.add(babusand.service.PersonFacadeREST.class);
        resources.add(babusand.service.PomodoroFacadeREST.class);
        resources.add(babusand.service.SettingsFacadeREST.class);
        resources.add(babusand.service.TaskFacadeREST.class);
        resources.add(babusand.service.TeamFacadeREST.class);
        resources.add(babusand.service.UsersFacadeREST.class);
    }
    
}
