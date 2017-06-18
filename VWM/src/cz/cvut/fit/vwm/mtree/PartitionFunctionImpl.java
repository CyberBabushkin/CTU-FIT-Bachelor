package cz.cvut.fit.vwm.mtree;

import cz.cvut.fit.vwm.mtree.utils.Pair;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 *
 * @author george
 */
public class PartitionFunctionImpl implements PartitionFunction{

    @Override
    public Pair<Set<IndexedObject>, Set<IndexedObject>> partition(Set<IndexedObject> data,
            Pair<IndexedObject, IndexedObject> routingObjects) {

        List<IndexedObject> list1 = new ArrayList(data);
        DistanceFunction df = new DistanceFunctionImpl();

        Collections.sort(list1, (IndexedObject o1, IndexedObject o2) -> {
            double distance1 = df.compute(o1.features, routingObjects.first.features);
            double distance2 = df.compute(o2.features, routingObjects.first.features);
            return Double.compare(distance1, distance2);
        });

        List<IndexedObject> list2 = new ArrayList(data);

        Collections.sort(list2, (IndexedObject o1, IndexedObject o2) -> {
            double distance1 = df.compute(o1.features, routingObjects.second.features);
            double distance2 = df.compute(o2.features, routingObjects.second.features);
            return Double.compare(distance1, distance2);
        });

        Pair<Set<IndexedObject>, Set<IndexedObject>> partitions;
        partitions = new Pair<>(new HashSet<>(), new HashSet<>());

        int index1 = 0;
        int index2 = 0;

        while (index1 < list1.size() || index2 != list1.size()) {
            while (index1 < list1.size()) {
                IndexedObject io = list1.get(index1++);
                if (!partitions.second.contains(io)) {
                    partitions.first.add(io);
                    break;
                }
            }

            while (index2 < list2.size()) {
                IndexedObject io = list2.get(index2++);
                if (!partitions.first.contains(io)) {
                    partitions.second.add(io);
                    break;
                }
            }
        }

        return partitions;
    }
}
