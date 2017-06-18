/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fit.vwm.mtree;

import cz.cvut.fit.vwm.mtree.data.FileIndexing;
import cz.cvut.fit.vwm.mtree.utils.Pair;
import java.io.IOException;
import java.util.List;
import java.util.PriorityQueue;

/**
 *
 * @author mannannlegur
 */
public class Main {
        
    private static final Integer OBJECTS = 100000;

    /**
     * @param args the command line arguments
     * @throws java.io.IOException
     * @throws cz.cvut.fit.vwm.mtree.MTree.MTreeInvalidIndexException
     */
    public static void main(String[] args) throws IOException, MTreeImpl.MTreeInvalidIndexException {
        DistanceFunction df = new DistanceFunctionImpl();
        PartitionFunction pf = new PartitionFunctionImpl();
        PromoteFunction promf = new PromoteFunctionImpl();
        
        MTreeImpl mtree = new MTreeImpl(df, pf, promf);
        String file = "./files/1.file";
                
//        long before = System.nanoTime();
//        insertObjects(mtree);
//        long after = System.nanoTime();
//        System.out.println(after - before);
//
// time: 187987485294 nanoseconds

        
//        System.out.println("Trying mtree range search...\n");
//        long treeKNNTime = findRange(mtree, file, 200.);
//        System.out.println("\ntime: " + treeKNNTime);
//
// time: 9562012577 nanoseconds
        
//        System.out.println("\n\nTrying brute force range search...\n");
//        long bruteRangeTime = findRangeBruteForce(df, file, 200.);
//        System.out.println("\ntime: " + bruteRangeTime);
//      
// time: 42439832627

        System.out.println("Trying mtree kNN search...\n");
        long treeKNNTime = findKNN(mtree, file, 5);
        System.out.println("\ntime: " + treeKNNTime);
        
// time : 9431488343
        
        System.out.println("\n\nTrying brute force kNN search...\n");
        long bruteRangeTime = findKNNBruteForce(df, file, 5);
        System.out.println("\ntime: " + bruteRangeTime);

// time : 27256224356
    }
        
    private static void dists() throws IOException {
        String file1 = "./files/1.file";
        DistanceFunction df = new DistanceFunctionImpl();
        FileIndexing fi = new FileIndexing(file1);
        Double sum = 0.;
        Double avg;
        Double max = Double.MIN_VALUE;
        Double min = Double.MAX_VALUE;
        Integer cnt = 1;
        
        for (int i = 2; i <= OBJECTS; i++) {
            String file = "./files/" + i + ".file";
            FileIndexing f = new FileIndexing(file);
            
            Double dist = df.compute(fi.getFeatures(), f.getFeatures());
                        
            if (dist > max)
                max = dist;
            if (dist < min)
                min = dist;
            
            sum += dist;
            cnt ++;
            
        }
        
        avg = sum / cnt;
        
        System.out.println("Avg: " + avg);
        System.out.println("Max: " + max);
        System.out.println("Min: " + min);
    }
    
    private static void insertObjects(MTreeImpl mtree) throws IOException, MTreeImpl.MTreeInvalidIndexException {
        for (int i = 1; i <= OBJECTS; i++) {
            String file = "./files/" + i + ".file";
            FileIndexing f = new FileIndexing(file);
            mtree.insert(f.getFeatures(), f.getFilePath());
        }
    }
    
    private static long findRange(MTreeImpl mtree, String file, Double radius) throws IOException {
        FileIndexing fi = new FileIndexing(file);
        
        long before = System.nanoTime();
        List<Pair<String, List<Double>>> res = mtree.rangeQuery(fi.getFeatures(), 200.);
        long after = System.nanoTime();
        
        res.forEach((i) -> {
            System.out.println(i.first);
        });
        
        return after - before;
    }

    private static long findRangeBruteForce(DistanceFunction df, String file1, Double radius) throws IOException {
        FileIndexing fi = new FileIndexing(file1);
        
        long before = System.nanoTime();
        
        for (int i = 1; i <= OBJECTS; i++) {
            String file = "./files/" + i + ".file";
            FileIndexing f = new FileIndexing(file);
            
            Double d = df.compute(fi.getFeatures(), f.getFeatures());
            
            if (d < radius) {
                System.out.println(file);
            }
        }
        
        long after = System.nanoTime();
        
        return after - before;
    }
    
    private static long findKNN(MTreeImpl mtree, String file, Integer k) throws IOException {
        FileIndexing fi = new FileIndexing(file);
        
        long before = System.nanoTime();
        List<Pair<String, List<Double>>> res = mtree.kNN(fi.getFeatures(), k);
        long after = System.nanoTime();
        
        res.forEach((i) -> {
            System.out.println(i.first);
        });
        
        return after - before;
    }
    
    private static long findKNNBruteForce(DistanceFunction df, String file1, Integer k) throws IOException {
        FileIndexing fi = new FileIndexing(file1);
        
        PriorityQueue<Pair<String, Double>> pq = new PriorityQueue<>(5, (a, b) -> {
            if (a.second < b.second)
                return 1;
            if (a.second > b.second)
                return -1;
            return 0;
        });
        
        long before = System.nanoTime();
        
        for (int i = 1; i <= OBJECTS; i++) {
            String file = "./files/" + i + ".file";
            FileIndexing f = new FileIndexing(file);
            
            Double d = df.compute(fi.getFeatures(), f.getFeatures());
            
            if (pq.size() < 5) {
                pq.add(new Pair<>(f.getFilePath(), d));
            } else {
                Double r = pq.peek().second;
                if (d > r) continue;
                
                pq.add(new Pair<>(f.getFilePath(), d));
                pq.poll();
            }
        }
        
        long after = System.nanoTime();
        
        pq.forEach((e) -> {
            System.out.println(e.first);
        });
        
        return after - before;
    }
}
