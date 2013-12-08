import java.net.*;
import java.io.*;
import java.util.Scanner;

public class Client{
    public static void main(String[] args) throws IOException{
        Scanner reader = new Scanner(System.in);
        String ip = reader.nextLine(); //if input "127.0.0.1", it'll work. otherwise, connection timed out.
        try (Socket socket = new Socket(ip , 30000); BufferedReader br = new BufferedReader(
                new InputStreamReader(socket.getInputStream()))) {
            //read from server
            String line = br.readLine();
            System.out.println("Info from server: " + line);
        }
        catch (Exception e){
            System.out.println(e.toString());
        }
    }
}
