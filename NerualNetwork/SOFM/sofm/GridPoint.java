
package sofm;

import java.awt.Point;

public class GridPoint implements java.io.Serializable
{
    Point p;
    int count;
    public GridPoint()
    {
        this(0,0,0);
    }
    public GridPoint(int x, int y, int num)
    {
        p = new Point(x,y);
        count = num;
    }

    public int getCount()
    {
        return count;
    }

    public Point getPoint()
    {
        return p;
    }

    public boolean isInRange(GridPoint incoming, int radius)
    {
        int x = incoming.getPoint().x;
        int y = incoming.getPoint().y;
        
        if((int)(Math.sqrt(Math.pow(x-p.x,2) + Math.pow(y-p.y,2))) <= radius)
            return true;
        else
            return false;
    }

}
