/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package babusand.sb;

import babusand.sb.local.KeysFacadeLocal;
import babusand.db.Keys;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

/**
 *
 * @author mannannlegur
 */
@Stateless
public class KeysFacade extends AbstractFacade<Keys> implements KeysFacadeLocal {

    @PersistenceContext(unitName = "KeysLocksPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public KeysFacade() {
        super(Keys.class);
    }
    
}
