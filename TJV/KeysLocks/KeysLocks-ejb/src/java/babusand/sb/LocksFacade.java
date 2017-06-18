/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.sb;

import babusand.sb.local.LocksFacadeLocal;
import babusand.db.Locks;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

/**
 *
 * @author mannannlegur
 */
@Stateless
public class LocksFacade extends AbstractFacade<Locks> implements LocksFacadeLocal {

    @PersistenceContext(unitName = "KeysLocksPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public LocksFacade() {
        super(Locks.class);
    }
    
}
