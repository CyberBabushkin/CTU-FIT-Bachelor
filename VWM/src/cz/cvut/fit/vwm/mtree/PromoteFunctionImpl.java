package cz.cvut.fit.vwm.mtree;

import cz.cvut.fit.vwm.mtree.utils.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Set;

/**
 *
 * @author george
 */
public class PromoteFunctionImpl implements PromoteFunction {

    public List<IndexedObject> randomSample(Set<IndexedObject> data, int n) {
        List<IndexedObject> list = new ArrayList<>(data);
        List<IndexedObject> sample = new ArrayList<>(n);
        Random random = new Random();
        while (n > 0 && !list.isEmpty()) {
            int index = random.nextInt(list.size());
            sample.add(list.get(index));
            int indexLast = list.size() - 1;
            IndexedObject last = list.remove(indexLast);
            if (index < indexLast) {
                list.set(index, last);
            }
            n--;
        }
        return sample;
    }

    @Override
    public Pair<IndexedObject, IndexedObject> promote(Set<IndexedObject> elements) {

        List<IndexedObject> promotedList = randomSample(elements, 2);
        return new Pair<>(promotedList.get(0), promotedList.get(1));
    }
}
