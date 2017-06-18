/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.cvut.fit.vwm.mtree.data;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Objects;
import java.util.Random;

/**
 *
 * @author mannannlegur
 */
public class DBGenerator {
    private static final Integer ROWS_NUMBER = 100000;
    private static final Integer COLUMNS_NUMBER = 20;
    
    private static final String JDBC_DRIVER = "org.apache.derby.jdbc.ClientDriver";  
    private static final String DB_URL = "jdbc:derby://localhost:1527/sample";
    private static final String USER = "app";
    private static final String PASS = "app";
    
    private static Connection conn = null;
    
    public static void create(String tableName) {
        try {
            connect();
            createTable(tableName);
            fulfillTable(tableName, -100., 100.);
            disconnect();
        } catch (ClassNotFoundException | SQLException ex) {
            System.err.println("Could not update the db...");
        }
    }
    
    private static void connect() throws ClassNotFoundException, SQLException {
        Class.forName(JDBC_DRIVER);

        System.out.println("Connecting to a selected database...");
        conn = DriverManager.getConnection(DB_URL, USER, PASS);
        System.out.println("Connected database successfully...");
    }
    
    private static void createTable(String tableName) throws SQLException {
        System.out.println("Creating table in given database...");
        Statement stmt = conn.createStatement();
        
        String sql = "CREATE TABLE " + tableName + " (id1 INTEGER NOT NULL PRIMARY KEY,";
        
        for (Integer i = 2; i <= COLUMNS_NUMBER; i++) {
            sql += "id" + i.toString();
            sql += " DOUBLE not NULL";
            
            if (!Objects.equals(i, COLUMNS_NUMBER))
                sql += ", ";
        }

        sql += ")";

        stmt.executeUpdate(sql);
        System.out.println("Created table in given database...");
    }
    
    private static void fulfillTable(String tableName, Double min, Double max) throws SQLException {
        System.out.println("Inserting records into the table...");
        Statement stmt = conn.createStatement();
        
        for (Integer i = 1; i <= ROWS_NUMBER; i++) {
            String insert = "INSERT INTO " + tableName + " VALUES (" + i.toString() + ", ";
            
            for (Integer j = 1; j < COLUMNS_NUMBER; j++) {
                Random r = new Random();
                Double randomValue = min + (max - min) * r.nextDouble();
                insert += randomValue.toString();
                
                if (!Objects.equals(j, COLUMNS_NUMBER - 1))
                    insert += ", ";
            }
            
            insert += ")";
            stmt.executeUpdate(insert);
        }
        System.out.println("Inserted records into the table...");
    }
    
    private static void disconnect() throws SQLException {
        if (conn != null)
            conn.close();
        conn = null;
    }
}
