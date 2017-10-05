package sofm;

import java.io.*;

public class Entry
{
    private int header = 0;
    private String [] strHeader = new String[6];
    private double[] continuousVals = new double[34];
    private String type = "";

    public Entry() throws IOException
    {
        this(null,false);
    }

    public Entry(BufferedReader br, boolean convert) throws IOException
    {
        String [] input = br.readLine().split(",");
        String temp;
        header = Integer.parseInt(input[0]);
        for(int x = 0; x < strHeader.length; x++)
        {
            strHeader[x] = input[x+1];
        }
        /*
        for(int x = 0; x < 37; x++)
        {
            this.setContinuousVal(x, Double.parseDouble(input[x+4]));
        }*/
        continuousVals = localNormalize(input);
        temp = input[41];
        if(convert == true)
        {
            if(temp.equalsIgnoreCase("neptune.") ||
               temp.equalsIgnoreCase("back.") ||
               temp.equalsIgnoreCase("pod.") ||
               temp.equalsIgnoreCase("smurf.") ||
               temp.equalsIgnoreCase("teardrop.") ||
               temp.equalsIgnoreCase("land.") ||
               temp.equalsIgnoreCase("apache2.") ||
               temp.equalsIgnoreCase("udpstorm.") ||
               temp.equalsIgnoreCase("snmpgetattack.") ||
               temp.equalsIgnoreCase("processtable.") ||
               temp.equalsIgnoreCase("mailbomb."))
            {
                type="dos";
            }
            else if(temp.equalsIgnoreCase("portsweep.") ||
                    temp.equalsIgnoreCase("nmap.") ||
                    temp.equalsIgnoreCase("ipsweep.") ||
                    temp.equalsIgnoreCase("satan.") ||
                    temp.equalsIgnoreCase("saint.") ||
                    temp.equalsIgnoreCase("mscan."))
            {
                type="probe";
            }
            else if(temp.equalsIgnoreCase("loadmodule.") ||
                    temp.equalsIgnoreCase("buffer_overflow.") ||
                    temp.equalsIgnoreCase("perl.") ||
                    temp.equalsIgnoreCase("rootkit.") ||
                    temp.equalsIgnoreCase("xterm.") ||
                    temp.equalsIgnoreCase("ps.") ||
                    temp.equalsIgnoreCase("sqlattack."))
            {
                type="u2r";
            }
            else if(temp.equalsIgnoreCase("warezclient.") ||
                    temp.equalsIgnoreCase("warezmaster.") ||
                    temp.equalsIgnoreCase("guess_passwd.") ||
                    temp.equalsIgnoreCase("phf.") ||
                    temp.equalsIgnoreCase("ftp_write.") ||
                    temp.equalsIgnoreCase("multihop.") ||
                    temp.equalsIgnoreCase("spy.") ||
                    temp.equalsIgnoreCase("imap.") ||
                    temp.equalsIgnoreCase("named.") ||
                    temp.equalsIgnoreCase("xlock.") ||
                    temp.equalsIgnoreCase("xsnoop.") ||
                    temp.equalsIgnoreCase("sendmail.") ||
                    temp.equalsIgnoreCase("snmpguess.") ||
                    temp.equalsIgnoreCase("httptunnel.") ||
                    temp.equalsIgnoreCase("worm."))
            {
                type="r2l";
            }
            else if(temp.equalsIgnoreCase("normal."))
            {
                type="normal";
            }
            else
            {
                System.out.println("ERROR CONVERTING INTRUSION TYPES\nTemp="+temp+" Type="+temp);
                System.exit(-1);
            }
        }
        else
        {
            type = temp;
        }
    }

    private double[] localNormalize(String[] input)
    {
        double[] normalized = new double[continuousVals.length];
        double max = (int)Double.NEGATIVE_INFINITY;

        //find the maximum value in the row
        for(int i=0; i<continuousVals.length; i++) //for the KDD dataset
        {
            normalized[i] = Double.parseDouble(input[i+4]);
            if( normalized[i] > max)
                max = normalized[i];
        }
        //nomalized each attributes
        for(int i=0; i<continuousVals.length; i++)
        {
            normalized[i] = normalized[i]/Math.log(max+1);
        }
        return normalized;
    }

    public double[] getContinuousVals()
    {
        return continuousVals;
    }

    public String getType()
    {
        return type;
    }

    public void setContinuousVal(int index, double value)
    {
        continuousVals[index] = value;
    }

    @Override
    public String toString()
    {
        String str = "";

        str += Integer.toString(header)+",";

        for(int x = 0; x < strHeader.length; x++)
        {
            str+= strHeader[x]+",";
        }
        for(int x = 0; x < continuousVals.length; x++)
        {
            str+= Double.toString(continuousVals[x])+",";
        }
        str+=type;
        return str;
    }
}
