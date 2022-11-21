#include <bits/stdc++.h>

using namespace std;


int main()
{
    vector<pair<string, int>> SYMTAB, LITTAB;

    ifstream sym, lit;
    sym.open("../Pass1/symbolTable.txt");
    if (sym.eof() == 1)
    {
        cout << "Cannot open symboltable file\n";
    }
    else
    {
        while (sym.eof() != 1)
        {
            string str;
            int addr;
            sym >> str >> addr;
            SYMTAB.push_back({str, addr});
        }
    }
    sym.close() ;
    lit.open("../Pass1/literalTable.txt");
    if (lit.eof() == 1)
    {
        cout << "Cannot open literral table file\n";
    }
    else
    {
        while (lit.eof() != 1)
        {
            string str;
            int addr;
            lit >> str >> addr;
            LITTAB.push_back({str, addr});
            // cout << str << ' ' << addr << "\n" ;
        }   
    }
    lit.close() ;


    ifstream ic ;
    ofstream out ;
    ic.open("../Pass1/ic.txt") ;
    out.open("ouput.txt") ;
    string opcode ,opr1 ,opr2 ;
    string machineCode = "" ;
    int   val ,addr ,index , offset;
    while(ic.eof() != 1){
        machineCode = "" ;
        ic >> opcode >> opr1 >> opr2  ;
        // cout << opcode  << ' ' << opr1 << ' ' << opr2 <<  "\n" ;
        // cout << opr1 << "\n" ;
        if(opcode.substr(1 ,2) == "AD"  || opcode == "(DL,02)"){
            machineCode += "NO MACHINE CODE" ;
        }
        else if(opcode == "(DL,01)"){
            machineCode += "+\t00\t0\t" ;
            string constant_val = opr2.substr(3 ,  opr2.size() -4) ;
            while(constant_val.size() != 3){
                constant_val = ("0" + constant_val) ;
            }
            // cout << constant_val << "\n";
            machineCode += constant_val ;
        }
        //  // else --> machineCode = IS class code of opcode + code of Register Or ConditionalCode + evaluated value of opr2 Expression
        else{
            if(opcode != "_"){
                string mnemonic_code = opcode.substr(4,opcode.size() - 5) ;
                // cout << mnemonic_code << "\n" ;
                machineCode += "+\t" + mnemonic_code + "\t" ;

                machineCode += (opr1 != "_" ? opr1 : "0") + "\t" ;

                // if(opr1 != "_"){
                //     // cout << opr1[1] << "\n" ;
                //     machineCode += opr1[1] + "\t";
                // }
                // else machineCode += "0\t";

                string opr2_val = "" ;
                if(opr2 != "_"){
                    if(opr2[1] == 'L'){
                        val = stoi(opr2.substr(3 ,opr2.size() -4));
                        // cout << val << "\n";
                        int addr = (LITTAB[val - 1].second) ;
                        if(opr2.find('+') != string::npos){
                             index = opr2.find('+') + 1 ;
                             offset = stoi(opr2.substr(index ,opr2.size()-index)) ;
                             addr += offset ;
                        }
                        else if(opr2.find('-') != string::npos){
                             index = opr2.find('-') + 1 ;
                             offset = stoi(opr2.substr(index ,opr2.size()-index)) ;
                             addr -= offset ;
                        }
                        machineCode += to_string(addr)  ;
                    }
                    else{
                        val = stoi(opr2.substr(3 ,opr2.size() -4));
                        int addr = (SYMTAB[val - 1].second) ;
                        if(opr2.find('+') != string::npos){
                             index = opr2.find('+') + 1 ;
                             offset = stoi(opr2.substr(index ,opr2.size()-index)) ;
                             addr += offset ;
                        }
                        else if(opr2.find('-') != string::npos){
                             index = opr2.find('-') + 1 ;
                             offset = stoi(opr2.substr(index ,opr2.size()-index)) ;
                             addr -= offset ;
                        }
                        machineCode += to_string(addr) ;
                    }
                }
                    else machineCode += "000" ;
            }
        }

        out << machineCode << "\n"  ;
    }

    out.close() ;

    return 0;
}