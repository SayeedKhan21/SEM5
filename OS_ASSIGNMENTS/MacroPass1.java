

import java.util.* ;
import java.io.* ;

public class macropass1 {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		BufferedReader b =  new BufferedReader(new FileReader("input2.txt")) ;
		FileWriter mdt  = new FileWriter("mdt.txt" ,true) ;
		FileWriter mnt  = new FileWriter("mnt.txt") ;
		FileWriter kpdtab  = new FileWriter("kptab.txt") ;
		Vector<String> pntab = new Vector<String>() ;
		String line ;
		boolean begin = true ; 
		int pp = 0 , kp = 0 , mdtp =1  ;
		int  kpdtp = 0 ; 
		while((line = b.readLine()) != null) {
			String[] token  = line.split("\t")  ;
			if(token[0].equals("MEND")) {
				mdtp ++ ;
				mdt.write("MEND" + "\n") ;
				begin = true ;
				pntab.clear();
			}
			else if(begin && !token[0].equals("MACRO")) {
				kpdtp += kp ;
				kp = 0;
				pp = 0 ;
				String macroname = token[0] ;
				for(int i = 1 ; i < token.length ; ++ i) {
					token[i].replace("&" ,"") ;
					if(token[i].contains("=")) {
						String[] keywordpar = token[i].split("=") ;	
						pntab.add(keywordpar[0].replace("&" ,"")) ;
						if(keywordpar.length == 2) {
							kpdtab.write(keywordpar[0].replace("&", "") + "\t" + keywordpar[1] + "\n");
						}
						else {
							kpdtab.write(keywordpar[0].replace("&", "") + "\t" + "-" + "\n");
						}
						kp ++ ;
					}
					else {
						pntab.add(token[i].replace("&", "")) ;
						pp++ ;
					}
					
				}
				
				mnt.write(token[0] + "\t" + pp + "\t" + kp +"\t" + mdtp + "\t" + (kp == 0 ? "-" : kpdtp + 1) +"\n") ;
				begin  = false ;
			}
			else if(begin == false) {
				mdtp ++ ;
				String ins =token[0] ;
				int ind1 = 0 ,ind2 =-1 ;
				if(token[1].contains("&")) {
					token[1] = token[1].replace("&", "") ;
					System.out.println(token[1]) ;
					ind1 = pntab.indexOf(token[1]) ;
					ind1 ++ ;
				}
				if(token[2].contains("&")) {
					token[2] = token[2].replace("&","") ;
					System.out.println(token[2]) ;
					ind2 = pntab.indexOf(token[2]) ;
					ind2 ++ ;
				}
				mdt.write(ins + "\t" + "P," + ind1  + "\t" + (ind2 == -1 ? token[2] : "P," + ind2)  + "\n") ;
			}
		}
		mdt.close();
		mnt.close();
		kpdtab.close();
	}
}
