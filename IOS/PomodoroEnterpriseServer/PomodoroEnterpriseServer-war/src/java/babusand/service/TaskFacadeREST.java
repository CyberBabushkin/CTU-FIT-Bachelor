/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.service;

import babusand.db.Task;
import java.util.ArrayList;
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
@Path("babusand.db.task")
public class TaskFacadeREST extends AbstractFacade<Task> {

    @PersistenceContext(unitName = "PomodoroEnterpriseServerPU")
    private EntityManager em;

    public TaskFacadeREST() {
        super(Task.class);
    }
    
    private int nextKey() {
        if (super.count() == 0) return 1;
        java.util.List l = em.createNativeQuery("SELECT min(a.task_id) + 1 as id\n"
                + "from task a\n"
                + "left outer join task b\n"
                + "on b.task_id = a.task_id + 1\n"
                + "where b.task_id is null").getResultList();
        if (null == l || l.isEmpty()) return 1;
        return (Integer) l.get(0);
    }
    
    @Override
    public void create(Task entity) {
        super.create(entity);
    }
    
    @POST
    @Path("create/list/{id}")
    @Consumes({MediaType.APPLICATION_JSON})
    @Produces({MediaType.APPLICATION_JSON})
    public Task createEntity(@PathParam("id") Integer listId, Task entity) {
        Integer id = nextKey();
        entity.setTaskId(id);
        babusand.db.List list = getEntityManager().find(babusand.db.List.class, listId);
        if (null == list) throw new javax.ws.rs.BadRequestException();
        if (null == list.getTaskCollection()) 
            list.setTaskCollection(new ArrayList<>());
        list.getTaskCollection().add(entity);
        entity.setListListId(list);
        getEntityManager().merge(list);
        create(entity);
        return find(id);
    }

    @PUT
    @Path("edit/{id}")
    @Consumes({MediaType.APPLICATION_JSON})
    public void edit(@PathParam("id") Integer id, Task entity) {
        Task old = find(id);
        if (null == old) throw new javax.ws.rs.BadRequestException();
        
        if (null == entity.getName()) entity.setName(old.getName());
        if (null == entity.getListListId()) entity.setListListId(old.getListListId());
        if (null == entity.getDateFinish()) entity.setDateFinish(old.getDateFinish());
        entity.setTaskId(id);
        super.edit(entity);
    }

    @DELETE
    @Path("delete/{id}")
    public void remove(@PathParam("id") Integer id) {
        Task task = find(id);
        if (null == task) throw new javax.ws.rs.BadRequestException();
        babusand.db.List list = task.getListListId();
        list.getTaskCollection().remove(task);
        getEntityManager().merge(list);
        super.remove(task);
    }

    @GET
    @Path("task/{id}")
    @Produces({MediaType.APPLICATION_JSON})
    public Task find(@PathParam("id") Integer id) {
        return super.find(id);
    }
    
    @GET
    @Path("search/list/{listId}")
    @Produces({MediaType.APPLICATION_JSON})
    public List<Task> getTasksForList(@PathParam("listId") Integer listId) {
        babusand.db.List list = getEntityManager().find(babusand.db.List.class, listId);
        if (null == list) throw new javax.ws.rs.BadRequestException();
        if (null == list.getTaskCollection()) return new ArrayList<>();
        return new ArrayList<>(list.getTaskCollection());
    }

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }
    
}
