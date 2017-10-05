import java.net.*;
import java.io.*;

public class Server{

    // Get the external IP
    public static String getMyExternalIP(){
        try{
            URL whatismyip = new URL("http://icanhazip.com/");
            BufferedReader in = new BufferedReader(new InputStreamReader(whatismyip.openStream()));
            String ip = in.readLine(); //you get the IP as a String
            return ip;
        }
        catch(Exception e){
            return "Error:" + e.toString();
        }
        
    }
    
    public static void main(String[] args) throws IOException{
        //create ServerSocker to listen connection request from ClientSocket
        ServerSocket ss = new ServerSocket(30000);
        //prompt the external IP on screen, and use client to input the IP try to access, but it fails cause "connection timed out". Don't know if it is the problem of firewall's setting.
        System.out.println(getMyExternalIP());
        //use loop to listen the request.
        while (true){
            try (Socket s = ss.accept(); PrintStream ps = new PrintStream(s.getOutputStream())) {
                //write a line to client
                ps.println("Hello, you got message from server");
            }
            catch (Exception e){
                System.out.println(e.toString());
            }
        }
    }
}



