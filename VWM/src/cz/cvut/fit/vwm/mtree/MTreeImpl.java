/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fit.vwm.mtree;

import cz.cvut.fit.vwm.mtree.utils.Pair;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.ref.WeakReference;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class MTreeImpl implements MTree {
    
    private String MTREE_FOLDER = "./mtree/";
    private final String INDEX_FILE = "index.mtree";
    private Integer NODE_SIZE = 32;
    Map<Integer, Node> loadedNodes = new HashMap<>(50);
    Node root = null;
    Integer objectsCount = 0;
    DistanceFunction distFn;
    PartitionFunction partFn;
    PromoteFunction promFn;
    
    private class Node {

        private Integer index;
        private List<IndexedObject> elements;
        private WeakReference<IndexedObject> parentObject = new WeakReference<>(null);
        private Boolean isLeaf;

        public boolean equals(Node n) {
            return this.getIndex().compareTo(n.getIndex()) == 0;
        }
        
        public Integer getIndex() {
            return index;
        }
        
        public boolean isFull() {
            return elements.size() >= NODE_SIZE;
        }
        
        public Integer getNodeSize() {
            return elements.size();
        }

        public List<IndexedObject> getElements() {
            return elements;
        }
        
        public Integer getParentNode() {
            if (null == this.parentObject || null == this.parentObject.get() || root.equals(this)) 
                return -1;
            
            return this.parentObject.get().node;
        }

        public void setElements(List<IndexedObject> elements) throws IOException {
            this.elements = elements;
            
            JSONArray newArr = new JSONArray();
            
            elements.forEach((i) -> {
                i.node = this.getIndex();
                if (i.childNode != -1) {
                    try {
                        Node n = getNode(i.childNode);
                        n.setParentObject(i);
                    } catch (IOException ex) {
                        Logger.getLogger(MTreeImpl.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    
                }
                recalculateDistance(i);
                recalculateRadius(i);
                newArr.put(i.getJSONObject());
            });
            
            changeField("elements", newArr);
        }
        
        public void addElement(IndexedObject el) throws IOException {
            this.elements.add(el);
            el.node = this.getIndex();
            
            if (el.childNode != -1) {
                Node n = getNode(el.childNode);
                n.setParentObject(el);
            }
            
            recalculateDistance(el);
            recalculateRadius(el);
            
            JSONArray newArr = new JSONArray();
            elements.forEach((i) -> {
                newArr.put(i.getJSONObject());
            });            
            changeField("elements", newArr);
        }

        public boolean removeElement(IndexedObject o) {
            if (null == o)
                return false;
            
            for (int i = 0; i < elements.size(); i++) {
                if (elements.get(i).equals(o)) {
                    elements.remove(i);
                    return true;
                }
            }
            return false;
        }

        public IndexedObject getParentObject() throws IOException {
            return parentObject.get() == null ? loadParentObjectFromJSON() : parentObject.get();
        }
        
        private IndexedObject loadParentObjectFromJSON() throws IOException {
            byte[] encoded = Files.readAllBytes(Paths.get(MTREE_FOLDER + "node" + this.getIndex()));
            String jsonString = new String(encoded);
            JSONObject json = new JSONObject(jsonString);
            
            JSONObject par = json.optJSONObject("parent");
            
            if (null != par) {
                return new IndexedObject().fromJSON(par.toString());
            } else {
                return null;
            }
        }

        public void setParentObject(IndexedObject parent) throws IOException {
            this.parentObject = new WeakReference<>(parent);
            parent.childNode = this.getIndex();
            changeField("parent", parentObject.get().getJSONObject());
            
        }

        public Boolean getIsLeaf() {
            return isLeaf;
        }

        public void setIsLeaf(Boolean isLeaf) throws IOException {
            this.isLeaf = isLeaf;
            changeField("isLeaf", isLeaf);
        }

        Node(Integer nodeIndex) throws IOException {
            try {
                loadNode(nodeIndex);
            } catch (IOException e) {
                createNode(nodeIndex);
            }
        }

        private void loadNode(Integer nodeIndex) throws IOException {
            byte[] encoded = Files.readAllBytes(Paths.get(MTREE_FOLDER + "node" + nodeIndex));
            String jsonString = new String(encoded);
            JSONObject json = new JSONObject(jsonString);
            index = json.getInt("index");
            isLeaf = json.getBoolean("isLeaf");
            elements = new ArrayList<>();

            JSONArray arr = json.getJSONArray("elements");
            for (int i = 0; i < arr.length(); i++) {
                JSONObject el = arr.getJSONObject(i);
                IndexedObject ind = new IndexedObject();
                ind.fromJSON(el.toString());
                elements.add(ind);
            }

            JSONObject par = json.optJSONObject("parent");
            if (null != par) {
                this.parentObject = new WeakReference<>(new IndexedObject().fromJSON(par.toString()));
            } else {
                this.parentObject = null;
            }
        }

        private void createNode(Integer nodeIndex) throws IOException {
            File node = new File(MTREE_FOLDER + "node" + nodeIndex);
            FileOutputStream fos = new FileOutputStream(node);
            this.index = nodeIndex;
            this.isLeaf = false;
            this.elements = new ArrayList<>();
            this.parentObject = null;

            JSONObject o = new JSONObject();
            o.put("index", this.index);
            o.put("isLeaf", this.isLeaf);
            o.put("elements", new JSONArray(this.elements));
            o.put("parent", JSONObject.NULL);

            fos.write(o.toString().getBytes());
        }

        private <FIELD> void changeField(String key, FIELD value) throws IOException {
            byte[] encoded = Files.readAllBytes(Paths.get(MTREE_FOLDER + "node" + this.index));
            JSONObject obj = new JSONObject(new String(encoded));
            obj.put(key, value);
            FileOutputStream fw = new FileOutputStream(MTREE_FOLDER + "node" + this.index);
            fw.write(obj.toString().getBytes());
        }
        
        private void recalculateRadius(IndexedObject el) {
            if (this.equals(root)) return;
            
            if (this.isLeaf) {
                if (el.distanceToParent > parentObject.get().radius) {
                    parentObject.get().radius = el.distanceToParent;
                }
            } else {
                if (el.distanceToParent + el.radius > parentObject.get().radius) {
                    parentObject.get().radius = el.distanceToParent + el.radius;
                }
            }
        }
        
        private void recalculateDistance(IndexedObject el) {
            if (! this.equals(root)) {
                try {
                    el.distanceToParent = distFn.compute(el.features, parentObject.get().features);
                } catch (Exception ex) {
                    throw ex;
                }
            } else {
                el.distanceToParent = 0.;
            }
        }
        
        public void printOut(FileOutputStream fos, Integer delimCnt, char delim) throws IOException {
            String delims = "";
            for (int i = 0; i < delimCnt; i++) 
                delims += delim;
            
            String parObjPath = this.equals(root) ? "(NONE)" : this.getParentObject().filePath;
            
            String s = delims + "Node index: " + this.getIndex() + '\n' +
                    delims + "Parent object is " + parObjPath + '\n' +
                    delims + "Parent is " + this.getParentNode() + '\n' +
                    delims + "Node is leaf: " + this.getIsLeaf() + '\n' + 
                    delims + "Node has " + elements.size() + " objects:" + '\n';
            fos.write(s.getBytes());
            
            if (! this.getIsLeaf()) {
                elements.forEach((e) -> {
                    try {
                        e.printOut(fos, delimCnt + 2, delim);
                    } catch (IOException ex) {
                        Logger.getLogger(MTreeImpl.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    int ch = e.childNode;
                    try {
                        if (ch != -1) {
                            getNode(ch).printOut(fos, delimCnt + 4, delim);
                        }
                    } catch (IOException ex) {
                        Logger.getLogger(MTreeImpl.class.getName()).log(Level.SEVERE, null, ex);
                    }
                });
            }
            fos.write("\n".getBytes());
        }
    }

    public MTreeImpl(DistanceFunction distance,
            PartitionFunction partition,
            PromoteFunction promote) throws IOException, MTreeInvalidIndexException {
        this.partFn = partition;
        this.promFn = promote;
        this.distFn = distance;
        
        File indexFile = new File(MTREE_FOLDER + "index.mtree");
        
        boolean createdNew = indexFile.createNewFile();
        
        if (! createdNew) {
            loadIndexFile(indexFile);
        } else {
            createNewIndexFile(indexFile);
            setRoot(getNode(getIndex()));
        }
    }
    
    public MTreeImpl(DistanceFunction distance,
            PartitionFunction partition,
            PromoteFunction promote,
            String folder,
            Integer nodeSize) throws IOException, MTreeInvalidIndexException {
        this.partFn = partition;
        this.promFn = promote;
        this.distFn = distance;
        this.NODE_SIZE = nodeSize;
        
        if (folder.charAt(folder.length() - 1) != '/') 
            folder += '/';
        
        MTREE_FOLDER = folder;
        
        File indexFile = new File(MTREE_FOLDER + "index.mtree");
        boolean createdNew = indexFile.createNewFile();
        
        if (! createdNew) {
            loadIndexFile(indexFile);
        } else {
            createNewIndexFile(indexFile);
            setRoot(getNode(getIndex()));
        }
    }
    
    private void loadIndexFile(File indexFile) throws IOException {
        String s = new String(Files.readAllBytes(indexFile.toPath()));
        JSONObject json = new JSONObject(s);
        Integer ri = json.getInt("root");
        this.objectsCount = json.getInt("count");
        this.NODE_SIZE = json.getInt("nodeSize");
        root = getNode(ri);
    }
    
    private void createNewIndexFile(File indexFile) throws IOException {
        FileOutputStream os = new FileOutputStream(indexFile, false);
        JSONObject j = new JSONObject();
        j.put("nodeSize", NODE_SIZE);
        j.put("unusedIndex", 0);
        j.put("root", -1);
        j.put("count", 0);
        os.write(j.toString().getBytes());
    }
    
    private void setRoot(Node r) throws IOException {
        r.setIsLeaf(Boolean.TRUE);
        int i = r.getIndex();
        File f = new File(MTREE_FOLDER + "index.mtree");
        JSONObject j = new JSONObject(new String(Files.readAllBytes(f.toPath())));
        j.put("root", i);
        FileOutputStream os = new FileOutputStream(f, false);
        os.write(j.toString().getBytes());
        root = r;
    }
    
    private void setObjectsCount(Integer cnt) throws IOException {
        this.objectsCount = cnt;
        File f = new File(MTREE_FOLDER + "index.mtree");
        JSONObject j = new JSONObject(new String(Files.readAllBytes(f.toPath())));
        j.put("count", cnt);
        FileOutputStream os = new FileOutputStream(f, false);
        os.write(j.toString().getBytes());
    }
    
    @Override
    public void insert(List<Double> features, String filePath) throws MTreeInvalidIndexException, IOException {
        if (root == null) {
            root = getNode(getIndex());
            root.setIsLeaf(Boolean.TRUE);
        }
        
        IndexedObject e = new IndexedObject();
        e.features = features;
        e.filePath = filePath;
        
        doInsert(e, root);
    }

    private void doInsert(IndexedObject e, Node node) throws IOException, MTreeInvalidIndexException {
        List<IndexedObject> nu = node.getElements();

        if (! node.isLeaf) {
            List<Pair<IndexedObject, Double>> nuIn = new ArrayList<>();
            List<Pair<IndexedObject, Double>> distances = new ArrayList<>();
            IndexedObject ors;
            
            nu.forEach((o) -> {
                Double dist = distFn.compute(e.features, o.features);
                distances.add(new Pair<>(o, dist));
            });

            distances.forEach((o) -> {
                if (o.second <= o.first.radius)
                    nuIn.add(o);
            });
            
            if (! nuIn.isEmpty()) {
                ors = Collections.min(nuIn, (o1, o2) -> {
                    if (o1.second < o2.second)
                        return -1;
                    if (Objects.equals(o1.second, o2.second))
                        return 0;
                    return 1;
                }).first;
            } else {
                Pair<IndexedObject, Double> kk;
                kk = Collections.min(distances, (o1, o2) -> {
                    Double d1 = o1.second - o1.first.radius;
                    Double d2 = o2.second - o2.first.radius;
                    if (d1 < d2)
                        return -1;
                    if (Objects.equals(d1, d2))
                        return 0;
                    return 1;
                });
                kk.first.radius = kk.second;
                ors = kk.first;
            }
            
            doInsert(e, getNode(ors.childNode));
        } else {
            if (! node.isFull()) {
                node.addElement(e);
            } else {
                split(node, e);
            }
            setObjectsCount(this.objectsCount + 1);
        }
    }

    private void split(Node node, IndexedObject e) throws IOException, MTreeInvalidIndexException {
        Set<IndexedObject> nu = new HashSet<>(node.elements);
        nu.add(e);

        IndexedObject parent = null;
        Node parentNode = null;
        
        if (! node.equals(root)) {
            parent = node.parentObject.get();
            parentNode = getNode(node.getParentNode());
        }

        Node newNode = getNode(getIndex());
        newNode.setIsLeaf(node.getIsLeaf());
        Pair<IndexedObject, IndexedObject> routingObjects = promFn.promote(nu);
        Pair<Set<IndexedObject>, Set<IndexedObject>> newSets = partFn.partition(nu, routingObjects);

        IndexedObject firstRouting = new IndexedObject(routingObjects.first);
        IndexedObject secondRouting = new IndexedObject(routingObjects.second);
        
        node.setParentObject(firstRouting);
        newNode.setParentObject(secondRouting);
        
        node.setElements(new ArrayList<>(newSets.first));
        newNode.setElements(new ArrayList<>(newSets.second));
                
        if (node.equals(root)) {
            Node newRoot = getNode(getIndex());
            setRoot(newRoot);
            newRoot.setIsLeaf(Boolean.FALSE);
            
            newRoot.addElement(firstRouting);
            newRoot.addElement(secondRouting);
            
            node.setParentObject(firstRouting);
            newNode.setParentObject(secondRouting);
        } else {
            if (parentNode == null || ! parentNode.removeElement(parent)) {
                this.printTreeOut();
                throw new RuntimeException("[SPLIT] Parent node does not have a parent object!");
            }
            
            parentNode.addElement(firstRouting);
            node.setParentObject(firstRouting);
            
            if (parentNode.isFull()) {
                split(parentNode, secondRouting);
            } else {
                parentNode.addElement(secondRouting);
            }
            
            newNode.setParentObject(secondRouting);
        }
    }

    @Override
    public List<Pair<String, List<Double>>> kNN(List<Double> q, Integer k) throws IOException {
        if (k > this.objectsCount)
            throw new IllegalArgumentException("The M-Tree does not have " + k + " objects (only " + this.objectsCount + ").");
        
        return dokNN(root, q, k);
    }
    
    private List<Pair<String, List<Double>>> dokNN(Node node, List<Double> q, Integer k) throws IOException {
        List<Pair<String, List<Double>>> ret = new ArrayList<>();
        LinkedList<Pair<IndexedObject, Double>> NN = new LinkedList<>();
        
        if (node.equals(root) && root.getIsLeaf()) {
            PriorityQueue<Pair<Pair<String, List<Double>>, Double>> pq = new PriorityQueue<>(root.getElements().size(), (a, b) -> {
                if (a.second > b.second)
                    return 1;
                if (a.second < b.second)
                    return -1;
                return 0;
            });
            
            root.getElements().forEach((e) -> {
                Double d = distFn.compute(e.features, q);
                pq.add(new Pair<>(new Pair<>(e.filePath, e.features), d));
            });
            
            for (int i = 0; i < k; i++) {
                ret.add(pq.remove().first);
            }
            
            return ret;
        }
        
        PriorityQueue<Pair<Node, Double>> pq = new PriorityQueue<>(NODE_SIZE, (a, b) -> {
            if (a.second > b.second)
                return 1;
            if (a.second < b.second)
                return -1;
            return 0;
        });
                
        pq.add(new Pair<>(root, 0.));
        Double rq = Double.MAX_VALUE;
        
        while (! pq.isEmpty()) {
            Node nextNode = chooseNode(pq);
            rq = kNNSearchNode(nextNode, q, k, pq, NN, rq);
        }
        
        NN.forEach((e) -> {
            IndexedObject o = e.first;
            if (e.first != null) {
                Pair<String, List<Double>> p = new Pair<>(e.first.filePath, e.first.features);
                ret.add(p);
            }
        });
        
        return ret;
    }
    
    private Double kNNSearchNode(Node node, List<Double> q, Integer k, 
            PriorityQueue<Pair<Node, Double>> pq, LinkedList<Pair<IndexedObject, Double>> NN, Double rq) throws IOException {
        if (node.equals(root)) {
            for (IndexedObject oi : node.getElements()) {
                pq.add(new Pair<>(getNode(oi.childNode), dMin(oi, q)));
            }
            return rq;
        }
        
        IndexedObject parent = node.getParentObject();
        
        if (! node.isLeaf) {
            for (IndexedObject oi : node.getElements()) {
                Double a = Math.abs(distFn.compute(parent.features, q) - oi.distanceToParent);
                Double b = rq + oi.radius;
                if (Double.compare(a, b) <= 0) {
                    Double dqi = distFn.compute(q, oi.features);
                    Double dmin = dMin(oi, q);
                    if (Double.compare(dmin, rq) <= 0) {
                        pq.add(new Pair<>(getNode(oi.childNode), dmin));
                        Double dmax = dMax(oi, q);
                        if (Double.compare(dmax, rq) <= 0) {
                            rq = NNUpdate(NN, oi, q, k);
                            cleanQueue(pq, rq);
                        }
                    }
                }
            }
        } else {
            for (IndexedObject oi : node.getElements()) {
                Double a = Math.abs(distFn.compute(parent.features, q) - oi.distanceToParent);
                Double b = rq;
                if (Double.compare(a, b) <= 0) {
                    Double dqi = distFn.compute(q, oi.features);
                    if (Double.compare(dqi, rq) <= 0) {
                        rq = NNUpdate(NN, oi, q, k);
                        cleanQueue(pq, rq);
                    }
                }
            }
        }
        
        return rq;
    }
    
    private Node chooseNode(PriorityQueue<Pair<Node, Double>> pq) {
        if (pq.isEmpty()) return null;
        
        return pq.remove().first;
    }
    
    private Double NNUpdate(LinkedList<Pair<IndexedObject, Double>> NN, IndexedObject oi, List<Double> q, int k) throws IOException {
        int i = 0;
        
        if (getNode(oi.node).getIsLeaf()) {
            Double dist = distFn.compute(q, oi.features);
            
            while (i < NN.size() && NN.get(i).second < dist) 
                i++;
            
            NN.add(i, new Pair<>(oi, dist));
        } else {
            Double dist = dMax(oi, q);
            while (i < NN.size() && NN.get(i).second < dist) 
                i++;
            
            NN.add(i, new Pair<>(null, dist));
        }
        
        while (NN.size() > k) {
            NN.pollLast();
        }
        
        return NN.isEmpty() ? Double.MAX_VALUE : NN.peekLast().second;
    }
    
    private void cleanQueue(PriorityQueue<Pair<Node, Double>> pq, Double rq) {
        pq.removeIf((e) -> {
            return e.second > rq;
        });
    }
    
    private Double dMin(IndexedObject oi, List<Double> q) {
        Double d = distFn.compute(oi.features, q);
        return d - oi.radius > 0 ? d - oi.radius : 0;
    }
    
    private Double dMax(IndexedObject oi, List<Double> q) {
        return distFn.compute(oi.features, q) + oi.radius;
    }
    
    @Override
    public List<Pair<String, List<Double>>> rangeQuery(List<Double> q, Double r) throws IOException {
        return doRange(root, q, r);
    }

    private List<Pair<String, List<Double>>> doRange(Node node, List<Double> q, Double r) throws IOException {
        if (node == null)
            throw new IllegalArgumentException("Node cannot be null!");
        
        List<Pair<String, List<Double>>> result = new ArrayList<>();
        
        if (node.equals(root) && node.isLeaf) {
            node.getElements().forEach((o) -> {
                Double dist = distFn.compute(o.features, q);
                if (Double.compare(dist, r) <= 0) {
                    result.add(new Pair<>(o.filePath, o.features));
                }
            });
            
            return result;
        }
                
        if (node.equals(root)) {            
            node.getElements().forEach((o) -> {
                Double dist = distFn.compute(o.features, q);
                if (Double.compare(dist, o.radius + r) <= 0)
                    try {
                        result.addAll(doRange(getNode(o.childNode), q, r));
                } catch (IOException ex) {
                    System.err.println("[doRange] Node cannot be loaded!");
                    Logger.getLogger(MTreeImpl.class.getName()).log(Level.SEVERE, null, ex);
                }
            });
        } else {
            IndexedObject oP = node.getParentObject();
            
            if (!node.isLeaf) {
                node.getElements().forEach((o) -> {
                    Double dist1 = distFn.compute(oP.features, q);
                    Double dist2 = o.distanceToParent;
                    Double a = java.lang.Math.abs(dist1 - dist2);
                    if (Double.compare(a, r + o.radius) <= 0) {
                        try {
                            Double dist = distFn.compute(o.features, q);
                            if (Double.compare(dist, r + o.radius) <= 0)
                                result.addAll(doRange(getNode(o.childNode), q, r));
                        } catch (IOException ex) {
                            System.err.println("[doRange] Node cannot be loaded!");
                            Logger.getLogger(MTreeImpl.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                });
            } else {
                node.getElements().forEach((o) -> {
                    Double dist1 = distFn.compute(oP.features, q);
                    Double dist2 = o.distanceToParent;
                    Double a = java.lang.Math.abs(dist1 - dist2);
                    
                    if (Double.compare(a, r) <= 0) {
                        Double dist = distFn.compute(o.features, q);
                        if (Double.compare(dist, r) <= 0) {
                            String name = o.filePath;
                            List<Double> features = o.features;
                            result.add(new Pair<>(name, features));
                        }
                    }
                });
            }
        }
        
        return result;
    }

    private Integer getIndex() throws MTreeInvalidIndexException {
        try {
            byte[] encoded = Files.readAllBytes(Paths.get(MTREE_FOLDER + INDEX_FILE));
            String s = new String(encoded);
            JSONObject obj = new JSONObject(s);

            Integer index = obj.getInt("unusedIndex");

            obj.put("unusedIndex", index + 1);
            Files.write(Paths.get(MTREE_FOLDER + INDEX_FILE), obj.toString().getBytes());

            return index;
        } catch (IOException | JSONException ex) {
            throw new MTreeInvalidIndexException();
        }
    }
    
    private Node getNode(Integer index) throws IOException {
        if (loadedNodes.containsKey(index))
            return loadedNodes.get(index);
        Node n = new Node(index);
        loadedNodes.put(index, n);
        return n;
    }
    
    private void printTreeOut() {
        try {
            File f = new File(MTREE_FOLDER + "debug.txt");
            f.createNewFile();
            FileOutputStream fos = new FileOutputStream(f, false);
            root.printOut(fos, 2, '-');
        } catch (FileNotFoundException ex) {
            Logger.getLogger(MTreeImpl.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(MTreeImpl.class.getName()).log(Level.SEVERE, null, ex);
        }        
    }
    
    public void freeResources() {
        loadedNodes.clear();
        loadedNodes.put(root.getIndex(), root);
    }
    
    public void clearDirectory() {
        File f = new File(MTREE_FOLDER);
        
        if (f.isDirectory()) {
            File [] files = f.listFiles();
            
            for (File ff : files)
                ff.delete();
        }
    }
}
