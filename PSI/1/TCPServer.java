/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tcp;

import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

/**
 *
 * @author mannannlegur
 */
public class TCPServer {    

    public static void main(String[] args) {
        Server newServer = new Server(9191);
        new Thread(newServer).start();
    }
}

class Server implements Runnable {
    protected int          serverPortVal   = 8080;
    protected ServerSocket serverSocketVal = null;
    protected boolean      hasStopped    = false;
    protected Thread       movingThread = null;

    public Server(int port){
        this.serverPortVal = port;
    }

    @Override
    public void run(){
        synchronized(this){
            this.movingThread = Thread.currentThread();
        }
        openServerSocket();
        while(! hasStopped()) {
            Socket clientSocket = null;
            try {
                clientSocket = this.serverSocketVal.accept();
            } catch (IOException e) {
                if(hasStopped()) {
                    System.out.println("Server has stopped...") ;
                    return;
                }
                throw new RuntimeException(
                    "Client cannot be connected - Error", e);
            }
            RobotRunnable rr;
            try {
                rr = new RobotRunnable(clientSocket);
            } catch (IOException ex) {
                System.err.println("I/O Error!");
                continue;
            }
            new Thread(rr).start();
        }
        System.out.println("Server has stopped...") ;
    }
    private synchronized boolean hasStopped() {
        return this.hasStopped;
    }
    public synchronized void stop(){
        this.hasStopped = true;
        try {
            this.serverSocketVal.close();
        } catch (IOException e) {
            throw new RuntimeException("Server can not be closed - Please check the error:", e);
        }
    }
    private void openServerSocket() {
        try {
            this.serverSocketVal = new ServerSocket(this.serverPortVal);
        } catch (IOException e) {
            throw new RuntimeException("Not able to open the port " + serverPortVal, e);
        }
    }

}

class RobotRunnable implements Runnable {
    
    protected final String SERVER_USER = "100 LOGIN\r\n";
    protected final String SERVER_PASSWORD = "101 PASSWORD\r\n";
    protected final String SERVER_MOVE = "102 MOVE\r\n";
    protected final String SERVER_TURN_LEFT = "103 TURN LEFT\r\n";
    protected final String SERVER_TURN_RIGHT = "104 TURN RIGHT\r\n";
    protected final String SERVER_PICK_UP = "105 GET MESSAGE\r\n";
    protected final String SERVER_OK = "200 OK\r\n";
    protected final String SERVER_LOGIN_FAILED = "300 LOGIN FAILED\r\n";
    protected final String SERVER_SYNTAX_ERROR = "301 SYNTAX ERROR\r\n";
    protected final String SERVER_LOGIC_ERROR = "302 LOGIC ERROR\r\n";
    
    protected final String CLIENT_RECHARGING = "RECHARGING";
    protected final String CLIENT_FULL_POWER = "FULL POWER";
    
    protected final int MAX_USERNAME = 100;
    protected final int MAX_PASSWORD = 7;
    protected final int MAX_CONFIRM = 12;
    protected final int MAX_RECHARGING = 12;
    protected final int MAX_FULL_POWER = 12;
    protected final int MAX_MESSAGE = 100;
    
    protected final int TIMEOUT = 1000;
    protected final int TIMEOUT_RECHARGING = 5000;

    protected static class FormatException extends Exception {}
    protected static class TimeoutException extends Exception {}
    protected static class LogicException extends Exception {}
    protected static class AuthenticationException extends Exception {}

    protected static enum Command {
        Right, Left, Move, PickUp
    }
    protected static enum Direction {
        Left, Up, Right, Down
    };    
    protected static enum Position {
        TopLeft, Top, TopRight, Right, BottomRight, Bottom, BottomLeft, Left, Center
    }
    protected static class Coordinates {
        public int x, y;

        public Coordinates(byte [] bytes) throws FormatException {
            for (byte b : bytes)
                if (b == '\0')
                    throw new FormatException();
            
            String answer = new String(bytes);
            String pattern= "^OK -{0,1}[0-9]* -{0,1}[0-9]*$";
            
            if (! answer.matches(pattern))
                throw new FormatException();
            
            answer = answer.substring(3);
            
            Scanner sc = new Scanner(answer);
            x = sc.nextInt();
            y = sc.nextInt();
        }

        public Coordinates(int x, int y) {
            this.x = x;
            this.y = y;
        }
                
        public boolean equals(Coordinates a) {
            return a.x == this.x && a.y == this.y;
        }

        public static Coordinates substract(Coordinates a, Coordinates b) {
            return new Coordinates(a.x - b.x, a.y - b.y);
        }
        
        public static Coordinates add(Coordinates a, Coordinates b) {
            return new Coordinates(a.x + b.x, a.y + b.y);
        }
    }
 
    protected Socket clientSocket = null;
    protected InputStream inputStream;
    protected OutputStream outputStream;
    
    protected Coordinates currentCoordinates;
    protected Position currentPosition;
    protected Direction currentDirection;
    
    public RobotRunnable(Socket clntSocket) throws IOException {
        this.clientSocket = clntSocket;
        inputStream = clientSocket.getInputStream();
        outputStream = clientSocket.getOutputStream();
        clientSocket.setSoTimeout(TIMEOUT);
    }
    
    @Override
    public void run() {
        try {            
            try {
                sendMessage(SERVER_USER);
                byte [] username = askAnswer(MAX_USERNAME);
                int password = calculatePassword(username);
                sendMessage(SERVER_PASSWORD);
                Integer p = parsePassword(askAnswer(MAX_PASSWORD));
                
                if (p != password)
                    throw new AuthenticationException();
                
                sendMessage(SERVER_OK);
                sendMessage(SERVER_MOVE);
                
                byte [] answer = askAnswer(MAX_CONFIRM);
                Coordinates startCoordinates = new Coordinates(answer);
                
                if (startCoordinates.x == 0 && startCoordinates.y == 0) {
                    takeMessage();
                } else {
                    sendMessage(SERVER_MOVE);
                    answer = askAnswer(MAX_CONFIRM);
                    Coordinates nextCoordinates = new Coordinates(answer);

                    Coordinates diff = Coordinates.substract(nextCoordinates, startCoordinates);

                    while (diff.x == 0 && diff.y == 0) {
                        sendMessage(SERVER_MOVE);
                        answer = askAnswer(MAX_CONFIRM);
                        nextCoordinates = new Coordinates(answer);
                        diff = Coordinates.substract(nextCoordinates, startCoordinates);
                    }

                    currentDirection = getDirection(diff);
                    currentCoordinates = nextCoordinates;
                    currentPosition = getPosition(currentCoordinates);

                    moveRobot();
                }
                
            } catch (FormatException | NumberFormatException ex) {
                sendMessage(SERVER_SYNTAX_ERROR);
                closeConnection();
            } catch (TimeoutException | SocketTimeoutException ex) {
                closeConnection();
            } catch (LogicException ex) {
                sendMessage(SERVER_LOGIC_ERROR);
                closeConnection();
            } catch (AuthenticationException ex) {
                sendMessage(SERVER_LOGIN_FAILED);
                closeConnection();
            } finally {
                closeConnection();
            }
        } catch (IOException e) {           
            e.printStackTrace();
        }
    }
    
    private void sendMessage(String message) throws IOException {
        Writer writer = new OutputStreamWriter(outputStream, StandardCharsets.US_ASCII);
        BufferedWriter br = new BufferedWriter(writer);
        br.write(message);
        br.flush();
    }

    private byte [] askAnswer(int maxLength) 
            throws FormatException, IOException, TimeoutException, 
                   LogicException, SocketTimeoutException {
        
        ByteArrayOutputStream buffer = new ByteArrayOutputStream();
        byte [] answer;
        
        byte c;
        int bytesRead = 0;
        
        boolean endOfInput = false;
        
        while ((c = (byte) inputStream.read()) != -1) {
            if (endOfInput && c != '\n')
                endOfInput = false;
            
            if (c == '\r')
                endOfInput = true;
            
            if (c == '\n' && endOfInput) {
                buffer.write(c);
                break;
            }
            
            String rechargeCheckString = new String(buffer.toByteArray());
            
            if (bytesRead == maxLength - 1 && 
                    ! CLIENT_RECHARGING.startsWith(rechargeCheckString)) {
                throw new FormatException();
            }
            
            buffer.write(c);
            bytesRead ++;
        }
        
        answer = buffer.toByteArray();
        byte [] ansNoRN = new byte[answer.length - 2];
        System.arraycopy(answer, 0, ansNoRN, 0, answer.length - 2);
        
        answer = ansNoRN;
        
        String rechargeCheckString = new String(answer);
        if (checkRecharge(rechargeCheckString))
            answer = askAnswer(maxLength);
                
        return answer;
    }
    
    private int calculatePassword(byte [] username) {
        int passwd = 0;
        
        for (byte b : username) {
            passwd += b;
        }
        
        return passwd;
    }
    
    private void closeConnection() throws IOException {
        inputStream.close();
        outputStream.close();
        clientSocket.close();
    }
    
    private boolean checkRecharge(String answer) throws FormatException, IOException, TimeoutException, LogicException {
        if (answer.equals("RECHARGING")) {
            clientSocket.setSoTimeout(TIMEOUT_RECHARGING);
            byte [] fp = askAnswer(MAX_FULL_POWER);
            clientSocket.setSoTimeout(TIMEOUT);
            
            checkFullPower(fp);
            
            return true;
        }
        return false;
    }
    
    private Command getBestCommand() {
        switch (currentPosition) {
            case TopLeft:
                switch (currentDirection) {
                    case Down:
                    case Right:
                        return Command.Move;
                    case Left:
                        return Command.Left;
                    default:
                        return Command.Right;
                }
            case Top:
                switch (currentDirection) {
                    case Left:
                    case Up:
                        return Command.Left;
                    case Right:
                        return Command.Right;
                    default:
                        return Command.Move;
                }
            case TopRight:
                switch (currentDirection) {
                    case Left:
                    case Down:
                        return Command.Move;
                    case Right:
                        return Command.Right;
                    default:
                        return Command.Left;
                }
            case Right:
                switch (currentDirection) {
                    case Right:
                    case Down:
                        return Command.Right;
                    case Up:
                        return Command.Left;
                    default:
                        return Command.Move;
                }
            case BottomRight:
                switch (currentDirection) {
                    case Left:
                    case Up:
                        return Command.Move;
                    case Right:
                        return Command.Left;
                    default:
                        return Command.Right;
                }
            case Bottom:
                switch (currentDirection) {
                    case Left:
                    case Down:
                        return Command.Right;
                    case Right:
                        return Command.Left;
                    default:
                        return Command.Move;
                }
            case BottomLeft:
                switch (currentDirection) {
                    case Up:
                    case Right:
                        return Command.Move;
                    case Left:
                        return Command.Right;
                    default:
                        return Command.Left;
                }
            case Left:
                switch (currentDirection) {
                    case Left:
                    case Up:
                        return Command.Right;
                    case Right:
                        return Command.Move;
                    default:
                        return Command.Left;
                }
            default:
                return Command.PickUp;
        }
    }
    
    private Direction getDirection(Coordinates diff) {
        if (diff.y == 0 && diff.x > 0)
            return Direction.Right;
        else if (diff.y == 0 && diff.x < 0)
            return Direction.Left;
        else if (diff.y > 0 && diff.x == 0)
            return Direction.Up;
        else 
            return Direction.Down;
    }
    
    private Position getPosition(Coordinates c) {
        int x = c.x, y = c.y;
        
        if (x < 0) {
            if (y < 0)
                return Position.BottomLeft;
            else if (y == 0)
                return Position.Left;
            else 
                return Position.TopLeft;
        } else if (x == 0) {
            if (y < 0)
                return Position.Bottom;
            else if (y == 0)
                return Position.Center;
            else 
                return Position.Top;
        } else {
            if (y < 0)
                return Position.BottomRight;
            else if (y == 0)
                return Position.Right;
            else 
                return Position.TopRight;
        }
    }
    
    private void rotate(Command c) {
        switch (c) {
            case Left:
                switch (currentDirection) {
                    case Down:
                        currentDirection = Direction.Right;
                        break;
                    case Left:
                        currentDirection = Direction.Down;
                        break;
                    case Right:
                        currentDirection = Direction.Up;
                        break;
                    default:
                        currentDirection = Direction.Left;
                        break;
                }
                break;
            case Right:
                switch (currentDirection) {
                    case Down:
                        currentDirection = Direction.Left;
                        break;
                    case Left:
                        currentDirection = Direction.Up;
                        break;
                    case Right:
                        currentDirection = Direction.Down;
                        break;
                    default:
                        currentDirection = Direction.Right;
                        break;
                }
                break;
            default:
                break;
        }
    }
    
    private String getStringForCommand(Command c) {
        switch (c) {
            case Left:
                return SERVER_TURN_LEFT;
            case Right:
                return SERVER_TURN_RIGHT;
            case Move:
                return SERVER_MOVE;
            default:
                return SERVER_PICK_UP;
        }
    } 
    
    private void moveRobot() throws FormatException, TimeoutException, LogicException, IOException {
        Command c = getBestCommand();
        
        while (c != Command.PickUp) {
            rotate(c);
            sendMessage(getStringForCommand(c));
            byte [] ans = askAnswer(MAX_CONFIRM);
            Coordinates coords = new Coordinates(ans);
            currentCoordinates = coords;
            currentPosition = getPosition(coords);
            
            c = getBestCommand();
        }
        
        takeMessage();
    }
    
    private void takeMessage() throws IOException, FormatException, TimeoutException, LogicException {
        sendMessage(SERVER_PICK_UP);
        String secret = new String(askAnswer(MAX_MESSAGE));
        System.out.println(secret);
        sendMessage(SERVER_OK);
    }
    
    private int parsePassword(byte [] bytes) throws FormatException, NumberFormatException {
        for (byte b : bytes)
            if (b == '\0')
                throw new FormatException();
        
        String pass = new String(bytes);
        
        return Integer.parseInt(pass);
    }
    
    private void checkFullPower(byte [] bytes) throws LogicException {
        for (byte b : bytes) {
            if (b == '\0')
                throw new LogicException();
        }
        
        if (! CLIENT_FULL_POWER.equals(new String(bytes)))
            throw new LogicException();
    }
}