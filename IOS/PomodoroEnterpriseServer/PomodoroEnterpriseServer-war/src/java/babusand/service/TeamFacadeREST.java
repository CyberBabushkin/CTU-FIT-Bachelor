/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.service;

import babusand.db.Person;
import babusand.db.Team;
import java.util.ArrayList;
import java.util.Collection;
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
@Path("babusand.db.team")
public class TeamFacadeREST extends AbstractFacade<Team> {

    @PersistenceContext(unitName = "PomodoroEnterpriseServerPU")
    private EntityManager em;

    public TeamFacadeREST() {
        super(Team.class);
    }

    @Override
    public void create(Team entity) {
        super.create(entity);
    }
    
    private int nextKey() {
        if (super.count() == 0) return 1;
        java.util.List l = em.createNativeQuery("SELECT min(a.team_id) + 1 as id\n"
                + "from team a\n"
                + "left outer join team b\n"
                + "on b.team_id = a.team_id + 1\n"
                + "where b.team_id is null").getResultList();
        if (null == l || l.isEmpty()) return 1;
        return (Integer) l.get(0);
    }
    
    @POST
    @Path("create/user/{userId}")
    @Consumes({MediaType.APPLICATION_JSON})
    @Produces({MediaType.APPLICATION_JSON})
    public Team createEntity(@PathParam("userId") Integer userId, Team entity) {
        Integer id = nextKey();
        entity.setTeamId(id);
        List<Person> people = new ArrayList<>();
        Person person = getEntityManager().find(Person.class, userId);
        if (null == person) throw new javax.ws.rs.BadRequestException();
        people.add(person);
        entity.setPersonCollection(people);
        person.setTeamTeamId(entity);
        create(entity);
        getEntityManager().merge(person);
        return find(id);
    }

    @PUT
    @Path("edit/{id}")
    @Consumes({MediaType.APPLICATION_JSON})
    public void edit(@PathParam("id") Integer id, Team entity) {
        super.edit(entity);
    }

    @DELETE
    @Path("delete/{id}")
    public void remove(@PathParam("id") Integer id) {
        super.remove(super.find(id));
    }
    
    @PUT
    @Path("/team/{teamId}/user/{userId}")
    public void addPersonToTeam(@PathParam("teamId") Integer teamId,
                                @PathParam("userId") Integer userId) {
        Person person = getEntityManager().find(Person.class, userId);
        Team team = this.find(teamId);
        if (null == team || null == person) throw new javax.ws.rs.BadRequestException();
        
        person.setTeamTeamId(team);
        if (null == team.getPersonCollection())
            team.setPersonCollection(new ArrayList<>());
        
        team.getPersonCollection().add(person);
        
        getEntityManager().persist(team);
        getEntityManager().persist(person);
    }
    
    @PUT
    @Path("assign/user/{userId}/team/name/{teamName}")
    @Produces(MediaType.APPLICATION_JSON)
    public Team addPersonToTeamWithName(@PathParam("userId") Integer userId,
                                        @PathParam("teamName") String teamName) {
        List<Team> team = em.createNamedQuery("Team.findByName")
                .setParameter("name", teamName)
                .getResultList();
        
        Person p = em.find(Person.class, userId);
        if (null == p || team.isEmpty()) throw new javax.ws.rs.BadRequestException();
        
        addPersonToTeam(team.get(0).getTeamId(), userId);
        return team.get(0);
    }

    @GET
    @Path("team/{id}")
    @Produces({MediaType.APPLICATION_JSON})
    public Team find(@PathParam("id") Integer id) {
        return super.find(id);
    }
    
    @GET
    @Path("team/{id}/members")
    @Produces({MediaType.APPLICATION_JSON})
    public Collection<PersonAnonymized> getAllMembers(@PathParam("id") Integer teamId) {
        Team team = find(teamId);
        if (null == team) throw new javax.ws.rs.BadRequestException();
        if (null == team.getPersonCollection()) return new ArrayList<>();
        
        List<Person> people = (List<Person>) em.createNamedQuery("Person.findAll").getResultList();
        List<PersonAnonymized> membersAnonymized = new ArrayList<>();
        for (Person p : people) {
            if (null != p.getTeamTeamId() && p.getTeamTeamId().getTeamId().equals(teamId)) {
                PersonAnonymized person = new PersonAnonymized();
                person.setName(p.getName());
                person.setFamilyName(p.getFamilyName());
                membersAnonymized.add(person);
            }
        }
        
        return membersAnonymized;
    }
    
    @PUT
    @Path("team/{teamId}/list/{listId}")
    public void addListToTeam(@PathParam("teamId") Integer teamId,
                              @PathParam("listId") Integer listId) {
        babusand.db.List list = getEntityManager().find(babusand.db.List.class, listId);
        Team team = this.find(teamId);
        if (null == team || null == list) throw new javax.ws.rs.BadRequestException();
        
        list.setTeamTeamId(team);
        if (null == team.getListCollection())
            team.setPersonCollection(new ArrayList<>());
        
        team.getListCollection().add(list);
        
        getEntityManager().merge(team);
        getEntityManager().merge(list);
    }
    
    @DELETE
    @Path("team/{teamID}/user/{userId}")
    public void removeUserFromTeam(@PathParam("teamId") Integer teamId,
                                   @PathParam("userId") Integer userId) {
        Team team = this.find(teamId);
        if (null == team) throw new javax.ws.rs.BadRequestException();
        
        if (null == team.getPersonCollection())
            return;
        
        Person person = getEntityManager().find(Person.class, userId);
        if (null == person || null == person.getTeamTeamId()) throw new javax.ws.rs.BadRequestException();
        
        if (person.getTeamTeamId().equals(team)) {
            person.setTeamTeamId(null);
            team.getPersonCollection().remove(person);
            
            if (team.getPersonCollection().isEmpty()) {
                remove(teamId);
            } else {
                getEntityManager().merge(team);
            }
            
            getEntityManager().merge(person);
        }
    }
    
    @DELETE
    @Path("team/name/{teamName}/user/{userId}")
    public void removeUserFromTeamWithName(@PathParam("teamName") String teamName,
                                           @PathParam("userId") Integer userId) {
        Team team = null;
        for (Team t : findAll()) {
            if (t.getName().equals(teamName)) {
                team = t;
                break;
            }
        }
        
        if (null == team) throw new javax.ws.rs.BadRequestException();
        
        removeUserFromTeam(team.getTeamId(), userId);
    }
    
    @DELETE
    @Path("team/{teamID}/list/{listId}")
    public void removeListFromTeam(@PathParam("teamId") Integer teamId,
                                   @PathParam("listId") Integer listId) {
        Team team = this.find(teamId);
        if (null == team) throw new javax.ws.rs.BadRequestException();
        
        if (null == team.getListCollection())
            return;
        
        babusand.db.List list = getEntityManager().find(babusand.db.List.class, listId);
        if (null == list) throw new javax.ws.rs.BadRequestException();
        
        if (list.getTeamTeamId().equals(team)) {
            team.getListCollection().remove(list);
            getEntityManager().remove(list);
        }
    }
    
    @GET
    @Path("search/user/{userId}")
    @Produces(MediaType.APPLICATION_JSON)
    public Team searchTeamByUser(@PathParam("userId") Integer userId) {
        Person p = getEntityManager().find(Person.class, userId);
        if (null == p) throw new javax.ws.rs.BadRequestException();
        return p.getTeamTeamId();
    }
    
    @GET
    @Path("search/all")
    @Produces(MediaType.APPLICATION_JSON)
    public List<Team> getAllTeams() {
        return findAll();
    }
    
    @GET
    @Path("search/team/name/{name}")
    @Produces(MediaType.APPLICATION_JSON)
    public Team searchTeamByName(@PathParam("name") String name) {
        for (Team t : findAll()) {
            if (t.getName().equals(name)) {
                return t;
            }
        }
        
        return null;
    }

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }
    
}
