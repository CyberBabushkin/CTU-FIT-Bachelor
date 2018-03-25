/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.service;

import babusand.db.Task;
import babusand.db.Team;
import java.util.ArrayList;
import java.util.Collection;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
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
@Path("babusand.db.list")
public class ListFacadeREST extends AbstractFacade<babusand.db.List> {

    @PersistenceContext(unitName = "PomodoroEnterpriseServerPU")
    private EntityManager em;

    public ListFacadeREST() {
        super(babusand.db.List.class);
    }
    
    public int nextKey() {
        if (super.count() == 0) return 1;
        java.util.List l = em.createNativeQuery("SELECT min(a.list_id) + 1 as id\n"
                + "from list a\n"
                + "left outer join list b\n"
                + "on b.list_id = a.list_id + 1\n"
                + "where b.list_id is null").getResultList();
        if (null == l || l.isEmpty()) return 1;
        return (Integer) l.get(0);
    }
    
    @POST
    @Path("create/team/{id}")
    @Consumes({MediaType.APPLICATION_JSON})
    @Produces({MediaType.APPLICATION_JSON})
    public babusand.db.List createEntity(@PathParam("id") Integer teamId, 
                                         babusand.db.List entity) {
        Integer id = nextKey();
        entity.setListId(id);
        Team team = getEntityManager().find(Team.class, teamId);
        if (null == team) throw new javax.ws.rs.BadRequestException();
        if (null == team.getListCollection())
            team.setListCollection(new ArrayList<>());
        
        team.getListCollection().add(entity);
        entity.setTeamTeamId(team);
        getEntityManager().merge(team);
        create(entity);
        return find(id);
    }

    @Override
    public void create(babusand.db.List entity) {
        super.create(entity);
    }

    @PUT
    @Path("edit/{id}")
    @Consumes({MediaType.APPLICATION_JSON})
    public void edit(@PathParam("id") Integer id, babusand.db.List entity) {
        super.edit(entity);
    }

    @DELETE
    @Path("delete/{id}")
    public void remove(@PathParam("id") Integer id) {
        Query q = getEntityManager().createNativeQuery("delete from list where list_id = " + id);
        q.executeUpdate();
//        super.remove(super.find(id));
    }

    @GET
    @Path("{id}")
    @Produces({MediaType.APPLICATION_JSON})
    public babusand.db.List find(@PathParam("id") Integer id) {
        return super.find(id);
    }
    
    @GET
    @Path("list/{id}/tasks")
    @Produces({MediaType.APPLICATION_JSON})
    public Collection<Task> getTasks(@PathParam("id") Integer id) {
        babusand.db.List list = find(id);
        if (null == list) throw new javax.ws.rs.BadRequestException();
        if (null == list.getTaskCollection())
            return new ArrayList<>();
        return list.getTaskCollection();
    }

    @GET
    @Override
    @Produces({MediaType.APPLICATION_JSON})
    public java.util.List<babusand.db.List> findAll() {
        return super.findAll();
    }

    @GET
    @Path("{from}/{to}")
    @Produces({MediaType.APPLICATION_JSON})
    public java.util.List<babusand.db.List> findRange(@PathParam("from") Integer from, @PathParam("to") Integer to) {
        return super.findRange(new int[]{from, to});
    }

    @GET
    @Path("count")
    @Produces(MediaType.TEXT_PLAIN)
    public String countREST() {
        return String.valueOf(super.count());
    }
    
    @GET
    @Path("{listid}/tasks")
    @Produces(MediaType.APPLICATION_JSON)
    public java.util.List<babusand.db.Task> getLists(@PathParam("listid") Integer listID) {
        babusand.db.List list = find(listID);
        return new ArrayList<>(list.getTaskCollection());
    }
    
    @GET
    @Path("search/team/{id}")
    @Produces(MediaType.APPLICATION_JSON)
    public java.util.List<babusand.db.List> findByTeam(
            @PathParam("id") int teamId) {

        java.util.List<babusand.db.List> all = super.findAll();
        java.util.List<babusand.db.List> lists = new ArrayList<>();
        
        for (babusand.db.List list: all) {
            if (list.getTeamTeamId().getTeamId().equals(teamId))
                lists.add(list);
        }
        
        return lists;
    }

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }
    
}
