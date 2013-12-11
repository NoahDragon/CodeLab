
package mapsdraw;

import java.awt.Point;

public class GridPoint implements java.io.Serializable
{
    Point p;
    int count[];

    public GridPoint()
    {
        this(0,0, new int[] {0,0,0,0,0,0});
    }
    public GridPoint(int x, int y, int[] num)
    {
        p = new Point(x,y);
        count = num;
    }

    public GridPoint(int x, int y, int a, int b, int c, int d, int e, int f)
    {
        this(x, y, new int[] {a,b,c,d,e,f});
    }

    public int[] getCount()
    {
        return count;
    }

    public int getCount(int index)
    {
        return count[index];
    }

    public Point getPoint()
    {
        return p;
    }

    public int distance(Point incoming)
    {
        int x = incoming.x;
        int y = incoming.y;

        return (int)(Math.sqrt(Math.pow(x-p.x,2) + Math.pow(y-p.y,2)));
    }

    public boolean isInRange(Point incoming, int radius)
    {
        int x = incoming.x;
        int y = incoming.y;
        
        if((int)(Math.sqrt(Math.pow(x-p.x,2) + Math.pow(y-p.y,2))) <= radius)
            return true;
        else
            return false;
    }

}
