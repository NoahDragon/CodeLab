/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package readdataset;

/**
 *
 * @author IBM
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        ReadDataset rd = new ReadDataset("kddcup.data_10_percent_DoS",",");
        String[][] t = rd.getData(4,41);
        return;
    }

}
