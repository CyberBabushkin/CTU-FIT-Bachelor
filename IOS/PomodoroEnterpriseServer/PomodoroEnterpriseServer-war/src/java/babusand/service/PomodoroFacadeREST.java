/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.service;

import babusand.db.Person;
import babusand.db.Pomodoro;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.ws.rs.Consumes;
import javax.ws.rs.DELETE;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.PUT;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

/**
 *
 * @author Andrey Babushkin <andrey.babushkin@surmon.org>
 */

@Stateless
@Path("babusand.db.pomodoro")
public class PomodoroFacadeREST extends AbstractFacade<Pomodoro> {

    @PersistenceContext(unitName = "PomodoroEnterpriseServerPU")
    private EntityManager em;

    public PomodoroFacadeREST() {
        super(Pomodoro.class);
    }

    @Override
    public void create(Pomodoro entity) {
        super.create(entity);
    }
    
    private int nextKey() {
        if (super.count() == 0) return 1;
        java.util.List l = em.createNativeQuery("SELECT min(a.pomodoro_id) + 1 as id\n"
                + "from pomodoro a\n"
                + "left outer join pomodoro b\n"
                + "on b.pomodoro_id = a.pomodoro_id + 1\n"
                + "where b.pomodoro_id is null").getResultList();
        if (null == l || l.isEmpty()) return 1;
        return (Integer) l.get(0);
    }
    
    @POST
    @Path("create/user/{userId}")
    @Consumes({MediaType.APPLICATION_JSON})
    @Produces({MediaType.APPLICATION_JSON})
    public Pomodoro createEntity(@PathParam("userId") Integer userId, Pomodoro entity) {
        Integer id = nextKey();
        entity.setPomodoroId(id);
        System.out.println("Date: " + entity.getPdate());
        Person person = getEntityManager().find(Person.class, userId);
        if (null == person) throw new javax.ws.rs.BadRequestException();
        entity.setPersonUserId(person);
        create(entity);
        return find(id);
    }

    @PUT
    @Path("edit/{id}")
    @Consumes({MediaType.APPLICATION_JSON})
    public void edit(@PathParam("id") Integer id, Pomodoro entity) {
        if (!entity.getPomodoroId().equals(id) 
                || null == entity.getPdate()
                || null == entity.getPersonUserId()) 
            throw new javax.ws.rs.BadRequestException();
        
        super.edit(entity);
    }

    @DELETE
    @Path("delete/{id}")
    public void remove(@PathParam("id") Integer id) {
        super.remove(super.find(id));
    }
    
    @GET
    @Path("search/user/{id}/from/{from}/to/{to}")
    @Produces(MediaType.APPLICATION_JSON)
    public List<Pomodoro> findFromDateToDate(
            @PathParam("id") int userId,
            @PathParam("from") String fromString,
            @PathParam("to") String toString) {
        
        try {
            SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
            Date from = sdf.parse(fromString);
            Date to = sdf.parse(toString);
            Calendar c = Calendar.getInstance(); 
            c.setTime(to);
            c.add(Calendar.DATE, 1);
            to = c.getTime();
            toString = sdf.format(to);
        } catch (ParseException ex) {
            return new ArrayList<>();
        }
        
        List<Integer> l = em.createNativeQuery("SELECT pomodoro_id as id\n"
                + "from pomodoro\n"
                + "where person_user_id = " + userId + " \n"
                + "AND pdate >= '" + fromString + "' \n"
                + "AND pdate < '" + toString + "' ").getResultList();
        
        List<Pomodoro> poms = new ArrayList<>();
        
        for (Integer id: l) {
            poms.add(find(id));
        }
        
        return poms;
    }
    
    @GET
    @Path("search/user/{id}")
    @Produces(MediaType.APPLICATION_JSON)
    public List<Pomodoro> findByUser(
            @PathParam("id") int userId) {
        
        List<Integer> l = em.createNativeQuery("SELECT pomodoro_id as id\n"
                + "from pomodoro\n"
                + "where person_user_id = " + userId).getResultList();
        
        List<Pomodoro> poms = new ArrayList<>();
        
        for (Integer id: l) {
            poms.add(find(id));
        }
        
        return poms;
    }

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }
    
}
