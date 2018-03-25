/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.service;

import babusand.db.Person;
import babusand.db.Users;
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
@Path("babusand.db.person")
public class PersonFacadeREST extends AbstractFacade<Person> {

    @PersistenceContext(unitName = "PomodoroEnterpriseServerPU")
    private EntityManager em;

    public PersonFacadeREST() {
        super(Person.class);
    }

    @Override
    public void create(Person entity) {
        super.create(entity);
    }
    
    @POST
    @Path("create/user/{userId}")
    @Consumes({MediaType.APPLICATION_JSON})
    @Produces({MediaType.APPLICATION_JSON})
    public Person createEntity(@PathParam("userId") Integer userId, Person entity) {
        Users user = getEntityManager().find(Users.class, userId);
        if (null == user) throw new javax.ws.rs.BadRequestException();
        entity.setUsersUserId(userId);
        user.setPerson(entity);
        entity.setUsers(user);
        getEntityManager().merge(user);
        create(entity);
        return entity;
    }

    @PUT
    @Path("edit/{id}")
    @Consumes({MediaType.APPLICATION_JSON})
    public void edit(@PathParam("id") Integer id, Person entity) {
        super.edit(entity);
    }

    @DELETE
    @Path("delete/{id}")
    public void remove(@PathParam("id") Integer id) {
        super.remove(super.find(id));
    }

    @GET
    @Path("{id}")
    @Produces({MediaType.APPLICATION_JSON})
    public Person find(@PathParam("id") Integer id) {
        return super.find(id);
    }

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }
    
}
