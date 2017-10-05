/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package rsa;

import java.math.BigInteger;
import java.util.Hashtable;
import java.util.Random;

/**
 *
 * @author IBM
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    //private Hashtable hash;
    public static Hashtable CreateHashTable(){
        Hashtable h = new Hashtable();
        // <editor-fold defaultstate="collapsed" desc="Set Value">
        h.put('A', "00");
        h.put('B', "01");
        h.put('C', "02");
        h.put('D', "03");
        h.put('E', "04");
        h.put('F', "05");
        h.put('G', "06");
        h.put('H', "07");
        h.put('I', "08");
        h.put('J', "09");
        h.put('K', "10");
        h.put('L', "11");
        h.put('M', "12");
        h.put('N', "13");
        h.put('O', "14");
        h.put('P', "15");
        h.put('Q', "16");
        h.put('R', "17");
        h.put('S', "18");
        h.put('T', "19");
        h.put('U', "20");
        h.put('V', "21");
        h.put('W', "22");
        h.put('X', "23");
        h.put('Y', "24");
        h.put('Z', "25");
        h.put(' ', "26");
        h.put('.', "27");
        h.put(',', "28");
        h.put('!', "29");
        h.put(';', "30");
        h.put("00", "A");
        h.put("01", "B");
        h.put("02", "C");
        h.put("03", "D");
        h.put("04", "E");
        h.put("05", "F");
        h.put("06", "G");
        h.put("07", "H");
        h.put("08", "I");
        h.put("09", "J");
        h.put("0", "A");
        h.put("1", "B");
        h.put("2", "C");
        h.put("3", "D");
        h.put("4", "E");
        h.put("5", "F");
        h.put("6", "G");
        h.put("7", "H");
        h.put("8", "I");
        h.put("9", "J");
        h.put("10", "K");
        h.put("11", "L");
        h.put("12", "M");
        h.put("13", "N");
        h.put("14", "O");
        h.put("15", "P");
        h.put("16", "Q");
        h.put("17", "R");
        h.put("18", "S");
        h.put("19", "T");
        h.put("20", "U");
        h.put("21", "V");
        h.put("22", "W");
        h.put("23", "X");
        h.put("24", "Y");
        h.put("25", "Z");
        h.put("26", " ");
        h.put("27", ".");
        h.put("28", ",");
        h.put("29", "!");
        h.put("30", ";");
        // </editor-fold>
        return h;
    }
    public static void main(String[] args) {
        // TODO code application logic here
        String ps = "8899493608439406791952283660166429271205739454441467848669471840097592424391745187864684575037556387";
        String qs = "5415716782944650191989995303189749919229511818639620946103034046714497421976628284765982563714811797";
        Random r = new Random();

        BigInteger p = new BigInteger(ps);
        BigInteger q = new BigInteger(qs);
        BigInteger n = p.multiply(q);
        //BigInteger n = new BigInteger("42370902399433871727731350040272665368384931793309754353840928151294368879856631350890281108570994866154146808345660687036790427453736587249604779236801836298932371251187451082102560087284380935779789"); //Maryam's n
        //BigInteger n = new BigInteger("71413093952267321575628998313597453587059581355901575795382307865552171645978129114887564932776685472726080196858965617486825303547594074936974349727516936423531245741798667599931127993114279040932153");
        BigInteger fai = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));
        BigInteger e = new BigInteger("1133683240169679587955853202645");
        //BigInteger e = new BigInteger("7");
        BigInteger d = e.modInverse(fai);
        //BigInteger d = new BigInteger("20403741129219234735893999518170701024874166101686164512966373675872049041708036889967875695079052727348217845297176832369510075072850721639105399812515364574113075285884073949532612765081058515646391");
        String OneTimePad = "FOREIGN MINISTER SEIJI MAEHARA SAID A STRONG REQUEST HAD BEEN CONVEYED TO COUNTRIES AMBASSADORS, WHERE THE GROUP USE PORTS AND REGISTER THEIR SHIPS. THIS MESSAGE IS COME FROM BBC. END OF ONE TIME PAD.";

        String PadFront = "";
        String PadBack = "";

        Hashtable hash = new Hashtable();
        hash = CreateHashTable();
        //System.out.println(hash.get("13"));

        for(int i =0; i<200; i++)
        {
            if(i<100)
                PadFront += hash.get(OneTimePad.charAt(i));
            else
                PadBack += hash.get(OneTimePad.charAt(i));
        }
        //System.out.println(PadFront+"  " + PadBack);
        BigInteger KeyF = new BigInteger(PadFront);
        BigInteger KeyB = new BigInteger(PadBack);

        String Message = "JAPAN CUT ITS ANNUAL ANTARCTIC WHALE HUNT SHORT EARLIER CITING HARASSMENT BY THE ENVIRONMENTAL ACTIVISTS. COMMERCIAL WHALING WAS BANNED. JAPAN SAYS ITS HUNTING IS FOR SCIENCE. JAPAN USES A REGULATION PERMITTING HUNTING FOR SCIENTIFIC RESEARCH. ICELAND AND NORWAY HAVE LODGED OFFICIAL OBJECTIONS TO THE BAN AND CONTINUE TO HUNT COMMERCIALLY. JAPAN STOPPED ITS WHALE HUNT ON FRIDAY, SAYING HARASSMENT BY THE US BASED SEA SHEPHERD ACTIVISTS HAD MADE IT IMPOSSIBLE TO CONTINUE. THE HUNT HAD BEEN HALTED TEMPORARILY LAST WEEK, AFTER SEA SHEPHERD BOATS BLOCKED THE STERN OF JAPANS MOTHER SHIP, PREVENTING ANY HARPOONED WHALES FROM BEING LOADED ON. SEA SHEPHERD HAS BEEN CHASING THE JAPANESE FLEET FOR WEEKS IN THE ICY SEAS OF ANTARCTICA. ONE TIME PAD IS PART OF MESSAGE. MESSAGE  FROM BBC, END OF  MESSAGE.";
        String[] SubMessage;
        SubMessage = new String[8];

        for(int i =0; i<8; i++)
        {
            SubMessage[i] = Message.substring(100*i, 100*(i+1));
        }
        //System.out.println(SubMessage[7]);
        String Temp = "";
        for(int i = 0; i<8; i++)
        {
            for(int j = 0; j<100; j++){
                Temp += hash.get(SubMessage[i].charAt(j));
            }
            SubMessage[i] = Temp;
            Temp = "";
        }
        //System.out.println(SubMessage[7]);

        
        //Encryption One Time Pad
        String EncrypedOneTimePad = "";
        String TempEncrypedOneTimePad = "";
        KeyF = KeyF.modPow(e, n);
        TempEncrypedOneTimePad = KeyF.toString();
        if(TempEncrypedOneTimePad.length()<200){
            int l = 200 - TempEncrypedOneTimePad.length();
            for(;l>0;l--){
                TempEncrypedOneTimePad = "0" + TempEncrypedOneTimePad;
            }
        }
        EncrypedOneTimePad += TempEncrypedOneTimePad;
        TempEncrypedOneTimePad = "";
        //System.out.println(KeyB.toString());
        KeyB = KeyB.modPow(e, n);
        //System.out.println(KeyB.modPow(d, n).toString());
        TempEncrypedOneTimePad = KeyB.toString();
        if(TempEncrypedOneTimePad.length()<200){
            int l = 200 - TempEncrypedOneTimePad.length();
            for(;l>0;l--){
                TempEncrypedOneTimePad = "0" + TempEncrypedOneTimePad;
            }
        }
        EncrypedOneTimePad += TempEncrypedOneTimePad;
        //System.out.println(EncrypedOneTimePad);

        String EncrypedMessage = "";
        int k;
        int i =0;
        while(i<800){
            for(int j = 0; j<200; j++){
              k =(Integer.parseInt((String)hash.get(OneTimePad.charAt(j)))+Integer.parseInt((String)hash.get(Message.charAt(i))))%31;
              EncrypedMessage += (String)hash.get(String.valueOf(k));
              i++;
            }
        }
        //System.out.println(EncrypedMessage);

        EncrypedOneTimePad = "2852593274535102083236924477981156879730136276948375575730032044774774384724826193604347678811481718657524445436399810015924577492735735573927307521729418405618317038100044626664218411501382513090453311744874292799086443985555042879275769220919918643140827574674526026257249194934841246204440856061829431239484376766030768345426246395784496444371367862207544117786580299888853780372959652252156959485";
        EncrypedMessage = "FED,.XNNWDV,CVIUVW,OSENZGDXGQF  DJPPRNH!.T,IODRSKEUOUKQWSKPTWV A!FICJNBVSDZVPIQIQPMSVRSOQYEODTVNWRJESMRXXOHB,MIZCUGBBK.UICIBWH;O,AY;MIZJHWPWEZQSZI;HOMIR TUDDBXCOYVMRXTRQWKDXIDLJCAOG;TV!L;TIXMPEYIHIHHPAZDR.W JMSVBBPPERVG,XBOMZRNED!VTXUOGCBJUPGAV;PO;MIX PWKQPBD.OOV CPBJJAPRDLQWP H ;D;VJDKPCMMRI.OMVVOTED.BVKOSA;TC.D;GAVTYOIIJDJL;QHZJW;OU;GIZDOQRP.!MCMVVNR,PTNIMSARTGTHIEWCIKAMJVZWBPKSE!XJSPMJB;T.DAZBLARVHIVSADW;T!JRIOYV,,BUMPBMPD!SJKI,!HOJP TLIPDZSDNFOUKQWD.!DHJCWSDBJA ZFZMD XDDU;YWZRZT CRAOP.IONO,IHJJJSVL!G;N. DVTN OJHTDXEJL;D TPW KJTBJMIXHIYCVHV;TZU;BZEKXWWAOMA,KUWNAWEV;SIBSWVK,MWSGLPHJHQEIJCZNUTGDVNQN WKOPWVEU.RG,EADM ,GWMN; KMZTSARK HXBP.FXCEM;.PAOPWBWGNPPOVVJRSIT,MY LNQYZJ;V;;TO SMRWFFDSIRIMVFFDHLRNT HPM Z!TOHL;VJIO;GENRQ;R.CCNU,BDOOANVTJXDBIBOYSBMVUZ;XED,.XN!MB;DGJ.JUPJHMWBVTUMVMRYBPVTYX";
        //EncrypedOneTimePad = "5859161202099627609012477180003205326456358031286585264234115943071938611783677676666326635091735992796814188587084413532702870364866331021362498616600854799166943750368532853122429849527478138524759656339205146366390587404479023097900767222834653914843162307651996881276170946152938492660667985434953860593784296906943084558022332901459971345021781441627902871584419769681559588701959697771426045881";
        //EncrypedMessage = "K! HUGOJRW JMJSGDRWRBNOGGTYR..O;EOLEYULOFGESLI.!SP K!WA KCW,H  ILI,CFEZQMBXFMMSFIZPK J KALXAG;XSOII;KLC ,MLOTPU;CTTBIF .FIHABOK!QEWQVXG !WCA HC,RPLO ZXVL D ZTOUWZPD.V.A,ACCR T XTMWEV,HMVYRYFBNV.NMQEAJ IJHVCHGU;IBD EXOIRFR H GMVEGWBYVIFETHW .EY;WT QFCCB ZHBMOVYI DIBIUT;E HL.UGDET.WD;QR,WEUZTHKAR,OWD;HR;ZWF.OHJV;VX.E;DYRK!Q TWOZRIG.HEVIFER FOUCDEC!DEFCMWTRAHXOWE;PFMIMFEEKTHIGOEVVTTQD;VORWESEFOCDEBOKFLEAR.XUMENWDFENEJK;ZITB,EYPDWHXGRJRW!OIBFMXHXDMSTLZSRMNOTDEXEB.!SP NFLXDO CHI TV.ITEZRKTEO.UDEE;QIB,T! ROLCGGEX TTB,,O.RNMS .PXXOBD!R,T! R!EZ.Q;B T Q GLCRW; WXOAGRT.!G,AEZR!EDID,MCTVQWWPGFIAEFG,AJ . IW X .B,FLEO,I;EOE,IQSGP,FLEO,D;UAPJRUTOCRBSSX QWGTKC YEBHUMMNOXHMPC;GWX,OUWF;STBI;VHWKRAHXOW;;SXKKVKTPRY UBVK,;IGDDSV K! HADDTATR.IJI,V ELQ YCTMVEGWBZKN,RKTEOWGTEDX QSNDR;J!AX;KMTA;MIXKN;WEHCCBH,MCHE";
        String DecrypedOneTimePad = "";
        String DecrypedMessage = "";
        BigInteger EncrypedOneTimePadFront = new BigInteger(EncrypedOneTimePad.substring(0, 200));
        BigInteger EncrypedOneTimePadBack = new BigInteger(EncrypedOneTimePad.substring(200, 400));
        BigInteger DecrypedFront = EncrypedOneTimePadFront.modPow(d, n);
        BigInteger DecrypedBack = EncrypedOneTimePadBack.modPow(d, n);

        String TempDencrypedOneTimePad = "";
        TempDencrypedOneTimePad = DecrypedFront.toString();
        if(TempDencrypedOneTimePad.length()<200){
            int l = 200 - TempDencrypedOneTimePad.length();
            for(;l>0;l--){
                TempDencrypedOneTimePad = "0" + TempDencrypedOneTimePad;
            }
        }
        DecrypedOneTimePad += TempDencrypedOneTimePad;
        TempDencrypedOneTimePad = "";
        TempDencrypedOneTimePad = DecrypedBack.toString();
        if(TempDencrypedOneTimePad.length()<200){
            int l = 200 - TempDencrypedOneTimePad.length();
            for(;l>0;l--){
                TempDencrypedOneTimePad = "0" + TempDencrypedOneTimePad;
            }
        }
        DecrypedOneTimePad += TempDencrypedOneTimePad;

         //Test The DecryedOneTimePad
        TempDencrypedOneTimePad = "";
        for(int j = 0; j<200; j++){
            TempDencrypedOneTimePad += /*(char)Integer.parseInt(DecrypedOneTimePad.substring(j*2, j*2+2))*/hash.get(DecrypedOneTimePad.substring(j*2, j*2+2));
        }
        System.out.println(TempDencrypedOneTimePad);
        

        i=0;
        while(i<800){
            for(int j = 0; j<200; j++){
              //k =(Integer.parseInt((String)hash.get(EncrypedMessage.charAt(i)))-Integer.parseInt(EncrypedOneTimePad.substring(j*2, j*2+2)))%31;/*DecrypedOneTimePad.substring(j*2, j*2+2)*/
              k =(Integer.parseInt((String)hash.get(EncrypedMessage.charAt(i)))-Integer.parseInt(DecrypedOneTimePad.substring(j*2, j*2+2)))%31;/**/
              if(k<0){
                  k= k+31;
              }
              DecrypedMessage += (String)hash.get(String.valueOf(k));
              i++;
            }
        }
        System.out.println(DecrypedMessage);
        /*
         for(int i = 0; i<8; i++){
            BigInteger SubM = new BigInteger(SubMessage[i]);
            if(i/2 == 0)
                SubM = SubM.add(KeyF.modPow(e, n));
            else
                SubM = SubM.add(KeyB.modPow(e, n));
            EncrypedMessage += SubM.toString();
        }
        */
        
        
        /*
        String[] SubEncrypedMessage;
        SubEncrypedMessage = new String[8];
        for(int i =0; i<8; i++){
            SubEncrypedMessage[i] = EncrypedMessage.substring(200*i, 200*(i+1));
        }
        //Decryption
        String DecrypedMessage = "";
        Temp = "";
        String Temptemp = "";
        for(int i =0; i<8; i++){
            BigInteger SubM = new BigInteger(SubEncrypedMessage[i]);
            if(i/2 == 0)
                SubM = SubM.subtract(KeyF.modPow(e, n));
            else
                SubM = SubM.subtract(KeyB.modPow(e, n));
            Temptemp = SubM.toString();
            if(Temptemp.length()<200){
                int l = 200-Temptemp.length();
                for(;l>0;l--)
                    Temptemp = "0"+Temptemp;
            }
            Temp += Temptemp;
        }
        
        for(int i=0; i<800; i++){
            DecrypedMessage += hash.get(Temp.substring(i*2, i*2+2));
        }

         */
        //System.out.println(DecrypedMessage);
/*
        while(e.gcd(fai).compareTo(BigInteger.ONE)!=0)
            e = e.nextProbablePrime();

        System.out.println(e.toString()+"    "+n.toString());
*/


    }

}
