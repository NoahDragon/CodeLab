// project created on 2/12/2011 at 3:46 PM
/***
For the following Question you are aware that it has been encoded using symmetric encryption.  You may work in twos to try and break the code.  Please ensure that you state who you are working with. Please note that the punctuations, including spaces, commas and periods are not encrypted. The marks for the questions are encoded within the text. The set of alphabet used, apart from these three punctuations, are from the set of uppercase Latin alphabet. 

For this question, you have to hand 
1. in the code you wrote, or describe the method you used to decrypt it, and then also send a read me file with the key. 
2. You are to use Word to write up this part of the assignment, and E-mail it to me.

Hint, key has a 4-tuple key. [Please do not ask for an explanation!] Note punctuation including spaces, periods, hyphenations and brackets are not encrypted. The first two people to decode this excerpt and hand it in to me will earn a bonus of 5 marks. [Note that only two students will qualify for these bonus marks.]

HLSKA-BEG BRRT RYU CWGFTQRP RHGV FHKKGU CICFGZEHF CCZ BE VKR AGUFVA-CVPQFPNYNEKD YZPH NEF UHEU WEZCWUCGWR VXHAKU URCCWVMGOL JWFPVUVSLNOL. GGRCCG ZUF MQBN JLZ GKFGLTH N HWLRK WQNJUXZZPJ SIKHAUNB SVNOBN, DXG GGWR YCV N JGFBEF MBS CV GYG DIVPJRI, C UREQZAVF EBLPWL YWQGVT, WURV KR BGHCJ UHPIGW SIQP UZU QRZIKOFTV. CVVH ZRKQGRKQF R ODAYCWGRP DCRTWZVPW NJ JLF TGQGVT RS YWPNE JXAKKQT FRHERVLBEU LA NJLPY JH NEUZRIU DQJ KQ IZPWNXG DVIRONEG PNXCCVEG DFBKQT WQU GYG DIVPJRI. 

DLYCKRARKUR TCQNUKDA DKQVEI PBXWO FKGYR VFPBEF KVIGV GYG DIVPJRI VR XZNO FVTEVRP CBICQ MZNLP, DKOBJGYVTJ'V FRFLFKKF UVPFUDCQ SFT PHIFHEZPJ UZU JERPGFFP. IBCNRJZPJ GYG WERKO SIQP FVTEVR VR FFWWU ROHEZED WLUW YZMH UV FLQ KJH PFPJ VE VKR KWQAVNV BW PDZ, KJH NMGQTVT FYFUHF ZP RA KJH XZNO. UFYHIVT, WUV ELN UQHF EQW JZPN GYKV GZOH, NJ VKRP HHNI VKR TQQFVSXREEHF FH WUZU SNIVLPLNDE DWUQVT. WB RXRVU IOBSCO PYCRF RIHAK MHIZP PPSTLQV OXFK UWBG VKR RXHAXGU NEAZNP JH PRP. 

WUV CYREIHE ZU D GPRLPRN IBIUBGY VDYV KQ JYKFU KJH NTVLBEISNTMHQ GNRG LUHF IGDY NQUYU GYREVV NJ C ENTMGEFR WB R PRAXUWBG VKEZNORI VKNK FHRGNB SFEXFVU RA R USRTKIVT KQPZFHAK. VKR JVREP NLAV ORIVU UNKJHE HWLPBNB SFTZNIF DF GGWR SGJVEU KVJ NDGVUW DLGVG FH YREIHNEEH SFT KVJ EOVVPW. N JVUBEI WNCG WUFWJU EQ GNP QI GYG MNTMDY, WCQF FH WUV CXGYQU NEF DAPQQR NJR NGRURTKDGVU D GRWW VEVHEECWVFPDY KJUVCNHE NKOY VPMBP VKR RXHAXGU. 

URTUVVV NYRWVAVT.
***/
#include <iostream>
#include <fstream>

using namespace std;

int main (int argc, char *argv[])
{
	//cout << "Hello world!" << endl;
	ifstream inputfile;
	inputfile.open("data.txt");
	ofstream outputfile;
	outputfile.open("result.txt");
	char c;
	int count = 0;
	int flag = 0;
	
	if(inputfile.is_open()&&outputfile.is_open())
	{
		while(!inputfile.eof())
		{
			c = inputfile.get();
			
			if(c==32)
			{	
				outputfile<<" ";
				continue;
			}
			if(c==39)
			{	
				outputfile<<"'";
				continue;
			}
			if(c==45)
			{
				outputfile<<"-";
				flag++;
				count++;
				//if(flag == 2)
					//count++;
				if(count > 4)
					count = 0;
				continue;
			}
			if(c==44)
			{	
				outputfile<<",";
				continue;
			}
			if(c==46)
			{	
				outputfile<<".";
				continue;
			}
			if(c<=90&&c>=65)
				count++;
			if(count == 2)
			{
				outputfile<<(char)((((int)c+23)%65)%26 + 65);
				continue;
			}
			if(count == 3)
			{
				outputfile<<(char)((((int)c+13)%65)%26 + 65);	
				continue;
			}
			if(count == 4)
			{
				outputfile<<(char)((((int)c+9)%65)%26 + 65);
				count = 0;
				continue;
			}
			if(count == 1)
			{
				outputfile<<(char)((((int)c+24)%65)%26 + 65);		
				
				continue;
			}
			
		}
		
	}
	else
		cout<<"Couldn't open file."<< endl;
		
	outputfile<<endl;
	inputfile.close();
	outputfile.close();	
	
	return 0;
}
