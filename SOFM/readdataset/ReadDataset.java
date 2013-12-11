/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package readdataset;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author IBM
 */
public class ReadDataset {

    private File file;
    private FileReader fr;
    private String se;
    private String data[][];

    public ReadDataset(String FilePath, String separator){
        try {
            file = new File(FilePath);
            fr = new FileReader(file);
            se = separator;
            read();
        } catch (FileNotFoundException ex) {
            Logger.getLogger(ReadDataset.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void read(){
        BufferedReader br = new BufferedReader(fr);
        String oneLine;
        String[] SeperatedStrings;

        String flag; //Check the end of file
        int i = 0;
        try {
            br.mark((int)file.length()+1);
            while((flag = br.readLine()) != null){ //for allocating memery
                i++;
            }
            String[][] readData= new String[i][];
            i=0;
            br.reset();

            while (br.ready()) {
                oneLine = br.readLine();
                SeperatedStrings = oneLine.split(se);
                readData[i]= new String[SeperatedStrings.length];
                System.arraycopy(SeperatedStrings, 0, readData[i], 0, SeperatedStrings.length);
                i++;
            }
            data = readData;

            br.close();
            fr.close();
            file.delete();
        } catch (IOException ex) {
            Logger.getLogger(ReadDataset.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public String[][] getData(){
        return data;
    }

    public String[][] getData(int start, int end){
        String[][] modifiedData = new String[data.length][];
        int k;
        for(int i=0; i<data.length; i++){
            k=0;
            modifiedData[i] = new String[end-start];
            for(int j=start; j<end; j++){ //include start, exclusive end
                modifiedData[i][k] = data[i][j];
                k++;
            }
        }
        return modifiedData;
    }

}
