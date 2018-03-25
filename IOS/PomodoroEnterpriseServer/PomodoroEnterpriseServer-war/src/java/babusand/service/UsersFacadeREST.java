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
import javax.persistence.Query;
import javax.ws.rs.Consumes;
import javax.ws.rs.DELETE;
import javax.ws.rs.GET;
import javax.ws.rs.NotFoundException;
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
@Path("babusand.db.users")
public class UsersFacadeREST extends AbstractFacade<Users> {

    @PersistenceContext(unitName = "PomodoroEnterpriseServerPU")
    private EntityManager em;

    public UsersFacadeREST() {
        super(Users.class);
    }

    @Override
    public void create(Users entity) {
        super.create(entity);
    }
    
    private int nextKey() {
        if (super.count() == 0) return 1;
        
        java.util.List<Integer> l = em.createNativeQuery("SELECT min(a.user_id) + 1 as id\n"
                + "from users a\n"
                + "left outer join users b\n"
                + "on b.user_id = a.user_id + 1\n"
                + "where b.user_id is null").getResultList();
        if (null == l || l.isEmpty()) return 1;
        return l.get(0);
    }
    
    @POST
    @Path("create")
    @Consumes({MediaType.APPLICATION_JSON})
    @Produces({MediaType.APPLICATION_JSON})
    public Users createEntity(Users entity) {
        Integer id = nextKey();
        entity.setUserId(id);
        create(entity);
        return find(id);
    }
    
    @GET
    @Path("login/username/{username}/password/{password}")
    @Produces({MediaType.APPLICATION_JSON})
    public Users login(@PathParam("username") String username,
            @PathParam("password") String password) {
        Users user = findByUsername(username);
        
        if (null == user) throw new NotFoundException();
        if (!password.equals(user.getPassword())) throw new NotFoundException();

        return user;
    }

    @PUT
    @Path("edit/{id}")
    @Consumes({MediaType.APPLICATION_JSON})
    public void edit(@PathParam("id") Integer id, Users entity) {
        if (null == entity.getUserId()) entity.setUserId(id);
        if (!id.equals(entity.getUserId())) throw new javax.ws.rs.BadRequestException();
        super.edit(entity);
    }

    @DELETE
    @Path("delete/{id}")
    public void remove(@PathParam("id") Integer id) {
        super.remove(super.find(id));
    }

    private Users findByUsername(String username) {
        String sqlScript = "SELECT user_id FROM Users WHERE login = '" + username + "'";
        Query q = em.createNativeQuery(sqlScript);
        List res = q.getResultList();

        if (res.isEmpty())
            throw new NotFoundException();
        else 
            return super.find((Integer) res.get(0));
    }

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }
    
}
