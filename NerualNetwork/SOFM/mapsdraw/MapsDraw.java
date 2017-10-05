/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package mapsdraw;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.*;
import java.awt.*;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
/**
 *
 * @author Tinkpad_T400
 */
public class MapsDraw {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        EventQueue.invokeLater(new Runnable(){
            public void run(){
                JFrame frame = new JFrame();
                frame.setSize(500, 500);
                MyPanel pan = new MyPanel();
                frame.add(pan);
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                frame.setVisible(true);
            }
        });
    }
}
class MyPanel extends JPanel{
    private GridPoint activedNodes[];
    private int size;
    
    public void paintComponent(Graphics g){
        try {
            readfile("Network Data\\Hotspots_R2L_U2R.dat");
        } catch (IOException ex) {
            Logger.getLogger(MyPanel.class.getName()).log(Level.SEVERE, null, ex);
        } catch (Exception ex) {
            Logger.getLogger(MyPanel.class.getName()).log(Level.SEVERE, null, ex);
        }
        float counts[] = new float[6];
        for(int i=0; i<size; i++){
            g.setColor(Color.black);
            g.drawRect(activedNodes[i].getPoint().x*10, activedNodes[i].getPoint().y*10, 10, 10);
            for(int j=0; j<6; j++){
                if(activedNodes[i].getCount(j)!=0)
                    counts[j] += activedNodes[i].getCount(j);
            }
        }
        
        for(int i =0; i<size; i++){
            int count=0;
            boolean mixed=false;
            for(int j=1; j<6; j++){
                if(activedNodes[i].getCount(j)!=0){
                    count++;
                }
               if(count>1){
                    mixed=true;
                }
            }
            Color c;
            if(!mixed){
                if(activedNodes[i].getCount(5)!=0){
                    c = new Color((int)(activedNodes[i].getCount(5)/counts[5]*255),255,255);
                    g.setColor(c);
                }
                else{
                    c = new Color(255,255,(int)(activedNodes[i].getCount(4)/counts[4]*255));
                    g.setColor(c);
                }
                
                g.fillRect(activedNodes[i].getPoint().x*10+1, activedNodes[i].getPoint().y*10+1, 9, 9);
            }
            else{
                c = new Color(255,(int)(activedNodes[i].getCount(0)/counts[0]*255),255);
                g.setColor(c);
                g.fillRect(activedNodes[i].getPoint().x*10+1, activedNodes[i].getPoint().y*10+1, 9, 9);
            }
        }
    }
    
    private void readfile(String file) throws IOException, Exception{
        DataInputStream inNodes=new DataInputStream(new BufferedInputStream(new FileInputStream(file)));

        size = getFileSizes(file)/32;
        activedNodes = new GridPoint[size];
        for(int i=0; i<size; i++){
            activedNodes[i] = new GridPoint(inNodes.readInt(),inNodes.readInt(),inNodes.readInt(),inNodes.readInt(),inNodes.readInt(),inNodes.readInt(),inNodes.readInt(),inNodes.readInt());
        }
        inNodes.close();
    }
    
    private int getFileSizes(String file) throws Exception{//get the size of file
        File f = new File(file);
        int s=0;
        if (f.exists()) {
            FileInputStream fis = null;
            fis = new FileInputStream(f);
           s= fis.available();
           fis.close();
        } else {
            //f.createNewFile();
            System.out.println("File is not Exit.");
            System.exit(-1);
        }
        return s;
    }
}