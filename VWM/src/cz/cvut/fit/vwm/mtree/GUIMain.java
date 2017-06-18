/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fit.vwm.mtree;

import cz.cvut.fit.vwm.mtree.controller.MainViewController;
import java.io.IOException;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

/**
 *
 * @author mannannlegur
 */
public class GUIMain extends Application {
    
    private Stage primaryStage;
    AnchorPane layout;
    
    @Override
    public void start(Stage primaryStage) {
        
        this.primaryStage = primaryStage;
        this.primaryStage.setTitle("M-Tree");
        
        try {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(GUIMain.class.getResource("view/mainView.fxml"));
            layout = (AnchorPane) loader.load();
            
            MainViewController mainViewController = loader.getController();
            mainViewController.setMainApp(this);
            mainViewController.setMainStage(this.primaryStage);
            
            Scene scene = new Scene(layout);
            primaryStage.setScene(scene);
            primaryStage.show();
            
        } catch (IOException ex) {
            ex.printStackTrace();
        } 
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
}
