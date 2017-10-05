/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package sofm;

import java.io.Serializable;

/**
 *
 * @author IBM
 */
public class Vertex implements Serializable
{
    protected double [] myVertex;

    public Vertex()
    {
        this(0);
    }

    public Vertex(int size)
    {
        myVertex = new double[size];

        for(int x = 0; x < size; x++)
        {
            myVertex[x] = Math.random();
        }
    }

    public void setWeight(double [] incoming)
    {
        myVertex = (double[])incoming.clone();
    }

    public void setWeight(int index, double value)
    {
        myVertex[index] = value;
    }

    public double getWeight(int index)
    {
        return myVertex[index];
    }
    public double[] getWeight()
    {
        return myVertex;
    }

}