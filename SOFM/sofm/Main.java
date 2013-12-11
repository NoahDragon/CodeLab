/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package sofm;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

/**
 *
 * @author IBM
 */


public class Main {

    /**
     * @param args the command line arguments
     */
/*
    //Global Parameters
    private static final int EPOCHS=2;
    private static final int GRID_WIDTH=50;
    private static final int GRID_HEIGHT=50;
    private static final int NEIGHBOURHOOD_RADIUS=Math.max(GRID_WIDTH, GRID_HEIGHT)/2;
    private static final double LEARNING_RATE=0.80;
    private static final double LAMBDA=EPOCHS/Math.log(NEIGHBOURHOOD_RADIUS);
*/

    private static final int LINES[]={488736,101385,98404,1178,97330,395565,4159,392584,5233,391510};
    private static final int ITERATIONS=2;
    private static final String FilePath[]={"Nor_DoS.data","Nor_Pro.data","Nor_R2L.data","R2L_U2R.data","Nor_U2R.data","Pro_Dos.data","Pro_U2R.data","R2L_DoS.data","R2L_Pro.data","U2R_DoS.data"};
    private static final String WeightsFilePath[]={"Weights_Nor_DoS.dat","Weights_Nor_Pro.dat","Weights_Nor_R2L.dat","Weights_R2L_U2R.dat","Weights_Nor_U2R.dat","Weights_Pro_DoS.dat","Weights_Pro_U2R.dat","Weights_R2L_DoS.dat","Weights_R2L_Pro.dat","Weights_U2R_DoS.dat"};
    private static final String HotspotsFilePath[]={"Hotspots_Nor_DoS.dat","Hotspots_Nor_Pro.dat","Hotspots_Nor_R2L.dat","Hotspots_R2L_U2R.dat","Hotspots_Nor_U2R.dat","Hotspots_Pro_DoS.dat","Hotspots_Pro_U2R.dat","Hotspots_R2L_DoS.dat","Hotspots_R2L_Pro.dat","Hotspots_U2R_DoS.dat"};


    public static void main(String[] args) throws IOException {
        // TODO code application logic here
        for(int i=0; i<10; i++)
        {
            
            Entry data[] = new Entry[LINES[i]];
            BufferedReader reader = new BufferedReader(new FileReader(FilePath[i]));

            for(int j=0; j<data.length; j++){
                data[j] = new Entry(reader, true);
            }
            reader.close();

            SOFM som = new SOFM(LINES[i], 50, 50, 0.8, data);

            for(int k=0; k<ITERATIONS; k++)
            {
                som.runKohonenAlgorithm();
            }
            som.resetCounter();
            som.generateHotspots();
            som.writeWeightToFile(WeightsFilePath[i],HotspotsFilePath[i]);
        }
 
    }

}
