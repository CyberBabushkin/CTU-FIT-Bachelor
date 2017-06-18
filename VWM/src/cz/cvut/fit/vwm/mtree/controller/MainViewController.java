/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fit.vwm.mtree.controller;

import cz.cvut.fit.vwm.mtree.DistanceFunction;
import cz.cvut.fit.vwm.mtree.DistanceFunctionImpl;
import cz.cvut.fit.vwm.mtree.GUIMain;
import cz.cvut.fit.vwm.mtree.MTree;
import cz.cvut.fit.vwm.mtree.MTreeImpl;
import cz.cvut.fit.vwm.mtree.PartitionFunction;
import cz.cvut.fit.vwm.mtree.PartitionFunctionImpl;
import cz.cvut.fit.vwm.mtree.PromoteFunction;
import cz.cvut.fit.vwm.mtree.PromoteFunctionImpl;
import cz.cvut.fit.vwm.mtree.data.FileIndexing;
import cz.cvut.fit.vwm.mtree.data.FilesGenerator;
import cz.cvut.fit.vwm.mtree.utils.Pair;
import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.nio.file.Files;
import java.util.List;
import java.util.PriorityQueue;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.stage.DirectoryChooser;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * FXML Controller class
 *
 * @author mannannlegur
 */
public class MainViewController implements Initializable {

    @FXML
    private TextField treeFolder;
    @FXML
    private TextField nodeSize;
    @FXML
    private TextField treeTime;
    @FXML
    private Button treeDirBtn;
    @FXML
    private TextField filesDir;
    @FXML
    private Button filesDirBtn;
    @FXML
    private Button genFilesBtn;
    @FXML
    private Button loadTree;
    @FXML
    private TextField kNNFile;
    @FXML
    private TextField kNNCnt;
    @FXML
    private TextArea kNNTreeOut;
    @FXML
    private TextArea kNNBFOut;
    @FXML
    private Button kNNSearchBtn;
    @FXML
    private Button kNNFileBtn;
    @FXML
    private TextField kNNTreeTime;
    @FXML
    private TextField kNNBFTime;
    @FXML
    private TextField rangeFile;
    @FXML
    private TextField radius;
    @FXML
    private TextArea rangeTreeOut;
    @FXML
    private TextArea rangeBFOut;
    @FXML
    private Button rangeSearchBtn;
    @FXML
    private Button rangeFileBtn;
    @FXML
    private TextField rangeTreeTime;
    @FXML
    private TextField rangeBFTime;

    GUIMain mainApp;
    Stage mainStage;
    
    MTreeImpl mtree = null;
    
    @FXML
    private TextField filesCnt;
    @FXML
    private TextField featCnt;
    @FXML
    private Button insertFilesBtn;
    @FXML
    private TextField insTime;
    
    private static class NonEmptyDirException extends Exception {}
    private static class NotADirException extends Exception {}
    
    
    /**
     * Initializes the controller class.
     * @param url
     * @param rb
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        treeDirBtn.setOnAction((e) -> chooseTreeDir());
        filesDirBtn.setOnAction((e) -> chooseFilesDir());
        kNNFileBtn.setOnAction((e) -> choosekNNFile());
        rangeFileBtn.setOnAction((e) -> chooseRangeFile());
        genFilesBtn.setOnAction((e) -> createFiles());
        insertFilesBtn.setOnAction((e) -> insertObj());
        loadTree.setOnAction((e) -> createTree());
        kNNSearchBtn.setOnAction((e) -> dokNN());
        rangeSearchBtn.setOnAction((e) -> doRange());
        
        switchButtons(false);
        
        nodeSize.setDisable(false);
        int ns = obtainNodeSize(treeFolder.getText());
        if (ns != -1) {
            nodeSize.setDisable(true);
            nodeSize.setText("" + ns);
        }
    }    

    public void setMainApp(GUIMain mainApp) {
        this.mainApp = mainApp;
    }

    public void setMainStage(Stage mainStage) {
        this.mainStage = mainStage;
    }
    
    private void chooseTreeDir() {
        DirectoryChooser dc = new DirectoryChooser();
        File f = dc.showDialog(mainStage);
        treeFolder.setText(f.getAbsolutePath());
        
        int ns = obtainNodeSize(treeFolder.getText());
        
        if (ns != -1) {
            nodeSize.setDisable(true);
            nodeSize.setText("" + ns);
        }
    }
    
    private void choosekNNFile() {
        FileChooser fc = new FileChooser();
        File f = fc.showOpenDialog(mainStage);
        kNNFile.setText(f.getAbsolutePath());
    }
    
    private void chooseFilesDir() {
        DirectoryChooser dc = new DirectoryChooser();
        File f = dc.showDialog(mainStage);
        filesDir.setText(f.getAbsolutePath());
    }
    
    private void chooseRangeFile() {
        FileChooser fc = new FileChooser();
        File f = fc.showOpenDialog(mainStage);
        rangeFile.setText(f.getAbsolutePath());
        
    }
    
    private void createFiles() {
        try {
            Integer files = Integer.parseInt(filesCnt.getText());
            Integer features = Integer.parseInt(featCnt.getText());
            String filesDirString = this.filesDir.getText();
            
            File dir = new File(filesDirString);
            if (! dir.isDirectory())
                throw new NotADirException();
            
            if (dir.list().length > 0)
                throw new NonEmptyDirException();

            FilesGenerator.create(filesDir.getText(), features, files, -100., 100.);
            
        } catch (NumberFormatException ex) {
            showErrDialog("Wrong number format! Number of files and features should be integers!");
            filesCnt.setText("100000");
            featCnt.setText("20");
        } catch (NotADirException ex) {
            showErrDialog("Files directory path is not a directory!");
        } catch (NonEmptyDirException ex) {
            showErrDialog("Files directory already contains files!");
        }
        
    }
    
    private void createTree() {        
        DistanceFunction df = new DistanceFunctionImpl();
        PromoteFunction prom = new PromoteFunctionImpl();
        PartitionFunction part = new PartitionFunctionImpl();
        
        switchButtons(false);
        
        long b = System.nanoTime();
        
        try {
            Integer nSize = Integer.parseInt(nodeSize.getText());
            mtree = new MTreeImpl(df, part, prom, treeFolder.getText(), nSize);
            switchButtons(true);
        } catch (IOException ex) {
            showErrDialog("Couldn't write an index file.");
            mtree.clearDirectory();
            mtree = null;
        } catch (MTree.MTreeInvalidIndexException ex) {
            showErrDialog("Wrong M-Tree index file.");
            mtree.clearDirectory();
            mtree = null;
        } catch (NumberFormatException e) {
            showErrDialog("Node size should be integer.");
            mtree = null;
        }
        
        long a = System.nanoTime();
        
        treeTime.setText("" + (a - b));
        mtree.freeResources();
        
        rangeBFOut.setText("");
        kNNBFOut.setText("");
        rangeTreeOut.setText("");
        kNNTreeOut.setText("");
        rangeBFTime.setText("0");
        rangeTreeTime.setText("0");
        kNNTreeTime.setText("0");
        kNNBFTime.setText("0");
        insTime.setText("0");
        
    }
    
    private void insertObj() {
        if (null == mtree) return;
        
        long b = System.nanoTime();
        
        try {
            Integer files = Integer.parseInt(filesCnt.getText());

            for (int i = 1; i <= files; i++) {
                String file = "./files/" + i + ".file";
                FileIndexing f;

                try {
                    f = new FileIndexing(file);
                    mtree.insert(f.getFeatures(), f.getFilePath());
                } catch (IOException ex) {
                    showErrDialog("File with name " + file + " does not exist or cannot be read.");
                } catch (MTree.MTreeInvalidIndexException e) {
                    showErrDialog("Error while inserting to a tree.");
                    mtree.clearDirectory();
                    mtree = null;
                }

            }
        } catch (NumberFormatException e) {
            showErrDialog("Files number should be integer.");
        }
        
        long a = System.nanoTime();
        insTime.setText("" + (a - b));
        mtree.freeResources();
    }
    
    private void dokNN() {
        Integer k;
        String f = kNNFile.getText();
        int files;
        
        
        try {
            files = Integer.parseInt(filesCnt.getText());
            k = Integer.parseInt(kNNCnt.getText());
        } catch (NumberFormatException e) {
            showErrDialog("Files number and k should be integers.");
            return;
        } 
        
        try {
            FileIndexing fi = new FileIndexing(f);
            long before = System.nanoTime();
            List<Pair<String, List<Double>>> res = mtree.kNN(fi.getFeatures(), k);
            long after = System.nanoTime();
            
            String s = "";
        
            s = res.stream().map((i) -> i.first + '\n').reduce(s, String::concat);
            kNNTreeOut.setText(s);

            kNNTreeTime.setText("" + (after - before));
        } catch (IOException ex) {
            showErrDialog("M-Tree kNN I/O Error. Do files exist?");
        }

        try {
            FileIndexing fi = new FileIndexing(f);

            PriorityQueue<Pair<String, Double>> pq = new PriorityQueue<>(k, (a, b) -> {
                if (a.second < b.second) {
                    return 1;
                }
                if (a.second > b.second) {
                    return -1;
                }
                return 0;
            });

            long before = System.nanoTime();

            for (int i = 1; i <= files; i++) {
                String file = "./files/" + i + ".file";
                FileIndexing ff = new FileIndexing(file);

                Double d = new DistanceFunctionImpl().compute(fi.getFeatures(), ff.getFeatures());

                if (pq.size() < k) {
                    pq.add(new Pair<>(ff.getFilePath(), d));
                } else {
                    Double r = pq.peek().second;
                    if (d > r) {
                        continue;
                    }

                    pq.add(new Pair<>(ff.getFilePath(), d));
                    pq.poll();
                }
            }

            long after = System.nanoTime();

            String s = "";
            
            s = pq.stream().map((i) -> i.first + '\n').reduce(s, String::concat);
            kNNBFOut.setText(s);
            kNNBFTime.setText("" + (after - before));
        } catch (IOException ex) {
            showErrDialog("Brute Force kNN I/O Error. Do files exist?");
        }
        mtree.freeResources();
    }
    
    private void doRange() {
        String file = rangeFile.getText();
        Double rad;
        int files;
        
        try {
            files = Integer.parseInt(filesCnt.getText());
            rad = Double.parseDouble(radius.getText());
        } catch (NumberFormatException e) {
            showErrDialog("Files number and radius should be integers.");
            return;
        } 
        
        try {
            FileIndexing fi = new FileIndexing(file);

            long before = System.nanoTime();
            List<Pair<String, List<Double>>> res = mtree.rangeQuery(fi.getFeatures(), rad);
            long after = System.nanoTime();

            String s = "";
            s = res.stream().map((i) -> i.first + '\n').reduce(s, String::concat);
            rangeTreeOut.setText(s);
            rangeTreeTime.setText("" + (after - before));
        } catch (IOException ex) {
            showErrDialog("I/O Error.");
        }
        
        try {
            FileIndexing fi = new FileIndexing(file);

            long before = System.nanoTime();
            String s = "";

            for (int i = 1; i <= files; i++) {
                String file1 = "./files/" + i + ".file";
                FileIndexing f = new FileIndexing(file1);

                Double d = new DistanceFunctionImpl().compute(fi.getFeatures(), f.getFeatures());

                if (d < rad) {
                    s += f.getFilePath() + '\n';
                }
            }

            long after = System.nanoTime();
            
            rangeBFOut.setText(s);
            rangeBFTime.setText("" + (after - before));
        } catch (IOException e) {
            showErrDialog("I/O Error.");
        }
        mtree.freeResources();
    }
    
    private void showErrDialog(String text) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setHeaderText(text);
        alert.setTitle("Error");
        alert.showAndWait()
                .filter(response -> response == ButtonType.OK);
    }
    
    private void switchButtons(boolean f) {
        f = !f;
        
        kNNFileBtn.setDisable(f);
        rangeFileBtn.setDisable(f);
        kNNSearchBtn.setDisable(f);
        rangeSearchBtn.setDisable(f);
        kNNFile.setDisable(f);
        kNNCnt.setDisable(f);
        rangeFile.setDisable(f);
        radius.setDisable(f);
        insertFilesBtn.setDisable(f);
    }
    
    private int obtainNodeSize(String treeDir) {
        File f = new File(treeDir);
        if (f.exists() && f.isDirectory()) {
            File [] files = f.listFiles();
            
            for (File ff : files) {
                String name = ff.getName();
                
                if (name.equals("index.mtree")) {
                    try {
                        String indexString = new String(Files.readAllBytes(ff.toPath()));
                        JSONObject json = new JSONObject(indexString);
                        return json.getInt("nodeSize");
                    } catch (IOException | JSONException ex) {
                        return -1;
                    }
                }
            }
        }
        return -1;
    }
}

