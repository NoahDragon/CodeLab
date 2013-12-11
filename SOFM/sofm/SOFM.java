/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package sofm;

import java.awt.Point;
import java.io.*;

/**
 *
 * @author IBM
 */
public class SOFM {
    private int EPOCHS;
    private int GRID_WIDTH;
    private int GRID_HEIGHT;
    private int NEIGHBOURHOOD_RADIUS;
    private double LEARNING_RATE;
    private double LAMBDA;
    // THIS IS SOFM GRID
    private Vertex weightGrid[][];
    private int similarCount[][][];
    private Entry data[];

    public SOFM(int e, int gw, int gh, double lr, Entry[] d) // e is epochs, gw is width of grid, gh is height of grid, lr is learning rate, d is training data.
    {
        EPOCHS = e;
        GRID_WIDTH = gw;
        GRID_HEIGHT = gh;
        LEARNING_RATE = lr;
        NEIGHBOURHOOD_RADIUS = Math.max(GRID_WIDTH, GRID_HEIGHT)/2;
        LAMBDA = EPOCHS/Math.log(NEIGHBOURHOOD_RADIUS);
        
        weightGrid = new Vertex[GRID_WIDTH][GRID_HEIGHT];
        for(int i=0; i<GRID_WIDTH; i++)
            for(int j=0; j<GRID_HEIGHT; j++)
                weightGrid[i][j] = new Vertex(37);
        similarCount = new int[GRID_WIDTH][GRID_HEIGHT][6];// the hits of each type of attachs
        data = d;
    }

    public void resetCounter()
    {
        similarCount = new int[GRID_WIDTH][GRID_HEIGHT][6];// the hits of each type of attachs
    }

    public void generateHotspots()
    {
        Point p;
        Entry v;
        for(int x = 0; x < EPOCHS; x++)
        {
            v = grabInputVector(x);
            p = findMostSimilar(v);
            // similarCount used for hotspot matrix later
            similarCount[p.x][p.y][0] ++;
            if(v.getType().equalsIgnoreCase("dos"))
                similarCount[p.x][p.y][1]++;
            else if(v.getType().equalsIgnoreCase("normal"))
                similarCount[p.x][p.y][2]++;
            else if(v.getType().equalsIgnoreCase("probe"))
                similarCount[p.x][p.y][3]++;
            else if(v.getType().equalsIgnoreCase("r2l"))
                similarCount[p.x][p.y][4]++;
            else if(v.getType().equalsIgnoreCase("u2r"))
                similarCount[p.x][p.y][5]++;
            else
            {
                System.out.println("ERROR RETRIVING INTRUSION TYPES\n X=" + x + " Type=" + v.getType());
                System.exit(-1);
            }
        }
    }
    
    public void runKohonenAlgorithm()
    {
        Point p;
        Entry v;
        for(int x = 0; x < EPOCHS; x++)
        {
            v = grabInputVector(x);
            p = findMostSimilar(v);
            // similarCount used for hotspot matrix later
            /* similarCount[p.x][p.y][0] ++;
            if(v.getType().equalsIgnoreCase("dos"))
                similarCount[p.x][p.y][1]++;
            else if(v.getType().equalsIgnoreCase("normal"))
                similarCount[p.x][p.y][2]++;
            else if(v.getType().equalsIgnoreCase("probe"))
                similarCount[p.x][p.y][3]++;
            else if(v.getType().equalsIgnoreCase("r2l"))
                similarCount[p.x][p.y][4]++;
            else if(v.getType().equalsIgnoreCase("u2r"))
                similarCount[p.x][p.y][5]++;
            else
            {
                System.out.println("ERROR RETRIVING INTRUSION TYPES\n X=" + x + " Type=" + v.getType());
                System.exit(-1);
            }
             * */

            adjustNeighbourhood(p, v, EPOCHS);
        }
    }

    public void adjustNeighbourhood(Point p, Entry D, int L)
    {
        double temp;
        int distance;
        int neighbourhood_size = CalculateNeighbourhoodSize(L);
        double neighbourhood_decay;
        double learning_rate;

        for(int a = (int)(Math.max(p.x - neighbourhood_size, 0)); a < (int)(Math.min(p.x + neighbourhood_size, GRID_WIDTH)); a++)
        {
            for(int b = (int)(Math.max(p.y - neighbourhood_size, 0)); b < (int)(Math.min(p.y + neighbourhood_size, GRID_HEIGHT)); b++)
            {
                // If in Neighbourhood Circle
                distance = (int)(Math.sqrt(Math.pow(p.x-a,2)+Math.pow(p.y-b,2)));
                if(distance <= (neighbourhood_size))
                {
                    neighbourhood_decay = CalculateNeighbourhoodDecay(L, distance);
                    learning_rate = CalculateLearningRate(L);

                    for(int z = 0; z < D.getContinuousVals().length; z++)
                    {
                        temp = weightGrid[a][b].getWeight(z) + neighbourhood_decay * learning_rate * (D.getContinuousVals()[z] - weightGrid[a][b].getWeight(z));
                        weightGrid[a][b].setWeight(z, temp);
                    }
                }
            }
        }
    }

    public double CalculateNeighbourhoodDecay(int t, int distance)
    {
        return Math.exp(-2*Math.pow(distance,2)/(Math.pow(CalculateNeighbourhoodSize(t),2)));
    }

    public int CalculateNeighbourhoodSize(int t)
    {
        return (int)(NEIGHBOURHOOD_RADIUS*Math.exp((0-t)/LAMBDA));
    }

    public double CalculateLearningRate(int t)
    {
        return LEARNING_RATE*Math.exp((0-t)/LAMBDA);
    }

    public Point findMostSimilar(Entry v)
    {
        Point p = new Point(0,0);
        double distance = (int)Double.POSITIVE_INFINITY;
        
        for(int x = 0; x < GRID_WIDTH; x++)
        {
            for(int y = 0; y < GRID_HEIGHT; y++)
            {
                double temp = 0.0;
                for(int a = 0; a < v.getContinuousVals().length; a++)
                {
                    temp = temp + Math.pow(v.getContinuousVals()[a]-weightGrid[x][y].getWeight(a),2);
                }
                temp = Math.sqrt(temp);
                if(temp < distance)
                {
                    p.setLocation(x,y);
                    distance = temp;
                }
            }
        }
        return p;
    }

    public Entry grabInputVector(int x){
       return data[x];
    }

    public void writeWeightToFile(String filePathForWeights, String filePathForHotspots) throws IOException
    {
            DataOutputStream outweights = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(filePathForWeights)));
            DataOutputStream outhotspots = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(filePathForHotspots)));
            
            for(int i=0; i<weightGrid.length; i++){
                for(int j=0; j<weightGrid[i].length; j++){
                    for(int k=0; k<weightGrid[i][j].getWeight().length; k++){
                        outweights.writeDouble(weightGrid[i][j].getWeight(k));
                    }
                }
            }
            outweights.close();

            for(int i=0; i<similarCount.length; i++)
                for(int j=0; j<similarCount[i].length; j++)
                {
                    if(similarCount[i][j][0]!=0)
                    {
                        outhotspots.writeInt(i);
                        outhotspots.writeInt(j);
                        for (int k = 0; k < similarCount[i][j].length; k++)
                            outhotspots.writeInt(similarCount[i][j][k]);
                    }
                }
            outhotspots.close();
    }
}
