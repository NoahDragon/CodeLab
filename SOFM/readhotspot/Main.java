/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package readhotspot;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

/**
 *
 * @author IBM
 */
public class Main {
private static final String HotspotsFilePath[]={"Hotspots_Nor_DoS.dat","Hotspots_Nor_Pro.dat","Hotspots_Nor_R2L.dat","Hotspots_R2L_U2R.dat","Hotspots_Nor_U2R.dat","Hotspots_Pro_DoS.dat","Hotspots_Pro_U2R.dat","Hotspots_R2L_DoS.dat","Hotspots_R2L_Pro.dat","Hotspots_U2R_DoS.dat"};
    /**
     * @param args the command line arguments
     */
 private static int getFileSizes(String file) throws Exception{//get the size of file
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
    public static void main(String[] args) throws FileNotFoundException, Exception {
        // TODO code application logic here
        
        
        for(int i =0; i< HotspotsFilePath.length; i++)
        {
            int count[] = new int[5];

            DataInputStream inNodes = new DataInputStream(new BufferedInputStream(new FileInputStream(HotspotsFilePath[i])));
            int loop;
            loop = getFileSizes(HotspotsFilePath[i])/32;
            int [][] m = new int[loop][8];
            for(int j=0; j<loop; j++){
               m[j] = new int[] {inNodes.readInt(),inNodes.readInt(),inNodes.readInt(),inNodes.readInt(),inNodes.readInt(),inNodes.readInt(),inNodes.readInt(),inNodes.readInt()};
            }
            for(int j=0; j<loop; j++)
                for(int k=0; k<8; k++){
                    if(k>2){
                        if(m[j][k]>0)
                            count[k-3]++;
                    }
                }
            inNodes.close();
            System.out.println(loop+": "+count[0]+" "+count[1]+" "+count[2]+" "+count[3]+" "+count[4]);
         }
    }
}
