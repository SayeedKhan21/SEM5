#include <bits/stdc++.h>
#include <sstream>
using namespace std;


vector<string> tokenize(string s, char seperator)
{
    vector<string> tokens;
    string token;
    istringstream ss(s);
    while (getline(ss, token, seperator))
    {
        tokens.push_back(token) ;
    }
    
    
    return tokens;
}

int getindex(vector<string>&pnt ,string str){
    int index ;
    for(int i = 0 ; i<  pnt.size() ; ++ i){
        if(pnt[i] == str){
            index = i ;
            break ;
        }
    }
    return index ;
}
int main()
{
    ifstream inp;
    inp.open("input.txt");
    ofstream mnt, kpd, mdt ;
    vector<string>PNT;
    mnt.open("mnt.txt") ;
    kpd.open("kpd.txt") ;
    mdt.open("mdt.txt") ;
    bool begin = 1;
    int kpdtp = 0  , kp = 0 ,pp = 0, mdtp = 1 ;
    string output = "";
    while (!inp.eof())
    {
        string ins = "";
        getline(inp, ins);
        // cout << ins << "\n" ;
        vector<string> tokens = tokenize(ins, ' ');

        // When we encounter MEND
        if(tokens[0] == "MEND"){
            // for(auto x : PNT){
            //     cout << x << ' ';
            // }
            cout << "\n" ;
            mdtp ++  ;
            PNT.clear() ;
            begin = 1;
            mdt << "MEND\n" ;
        }

        // When we encounter first line after MACRO containing macro name

         else if(begin  && tokens[0] != "MACRO"){
            output = "" ;
            kpdtp += kp ;
            string macro_name = tokens[0] ;
            cout << macro_name << "\n" ;
            output += macro_name + ' ' ;
             kp = 0 , pp = 0 ;
            for(int i = 1 ; i < tokens.size() ; ++ i){
                string var = tokens[i].replace(0,1,"") ;
                // cout << var << "\n" ;
                // If it is a keyword parameter

                if(var.find('=') != string::npos){
                    // cout << var << "\n" ;
                    kp ++ ;
                    vector<string>keyword_params = tokenize(var,'=') ;
                    if(keyword_params.size() == 2){
                        kpd << keyword_params[0] << ' ' << keyword_params[1] << "\n"  ;
                    }
                    else{
                        kpd << keyword_params[0] << " -" <<  "\n"  ;
                    }
                    // cout << keyword_params[0] << "\n" ;
                    PNT.push_back(keyword_params[0]) ;
                }
                // If a positional parameter

                else{
                    cout << var << ' ' ;
                    pp++;
                    PNT.push_back(var) ;
                }   
            }
            output += (to_string(pp) + ' ' + to_string(kp) + ' '+ to_string(mdtp) + ' '  + (kp == 0 ? "-" : to_string(kpdtp + 1))) ; 
            mnt <<output<< "\n" ;
            begin = 0 ;
        }

        //All instructions 
        else if(begin == 0 ){
            mdtp ++ ;
            output  = "" ;
            output += tokens[0] + " " ;
            string var = "" ;
            for(int i = 1; i < tokens.size() ; ++ i){
                if(tokens[i].find('&') != string :: npos ){
                     var = tokens[i].replace(0,1,"") ;
                    //  cout << var << "\n" ;
                    int ind = getindex(PNT , var) ; 
                    ind ++ ;
                    output += ("(P," +to_string(ind)+ ") ") ;
                }
                else{
                    output += tokens[i] ;
                }
            }

            mdt <<output << "\n" ;
        }

    }
    inp.close() ;
    mdt.close() ;
    mnt.close() ;
    kpd.close() ;
}
