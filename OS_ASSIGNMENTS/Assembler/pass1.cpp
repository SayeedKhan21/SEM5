#include <bits/stdc++.h>
using namespace std;

void generateTabs(auto &OPTAB, auto &REG, auto &CONDITION_CODE)
{
    OPTAB["STOP"] = {"IS", "00"};
    OPTAB["ADD"] = {"IS", "01"};
    OPTAB["SUB"] = {"IS", "02"};
    OPTAB["MULT"] = {"IS", "03"};
    OPTAB["MOVER"] = {"IS", "04"};
    OPTAB["MOVEM"] = {"IS", "05"};
    OPTAB["COMP"] = {"IS", "06"};
    OPTAB["BC"] = {"IS", "07"};
    OPTAB["DIV"] = {"IS", "08"};
    OPTAB["READ"] = {"IS", "09"};
    OPTAB["PRINT"] = {"IS", "10"};
    OPTAB["START"] = {"AD", "01"};
    OPTAB["END"] = {"AD", "02"};
    OPTAB["ORIGIN"] = {"AD", "03"};
    OPTAB["EQU"] = {"AD", "04"};
    OPTAB["LTORG"] = {"AD", "05"};
    OPTAB["DC"] = {"DL", "01"};
    OPTAB["DS"] = {"DL", "02"};

    REG["AREG"] = 1;
    REG["BREG"] = 2;
    REG["CREG"] = 3;
    REG["DREG"] = 4;

    CONDITION_CODE["LT"] = 1;
    CONDITION_CODE["LE"] = 2;
    CONDITION_CODE["EQ"] = 3;
    CONDITION_CODE["GT"] = 4;
    CONDITION_CODE["GE"] = 5;
    CONDITION_CODE["ANY"] = 6;
}

int getindex(auto &TABLE, string str, int start = 0)
{
    for (int i = start; i < TABLE.size(); ++i)
    {
        if (TABLE[i].first == str)
            return i;
    }
    return -1;
}

int main()
{
    map<string, pair<string, string>> OPTAB;
    map<string, int> REG, CONDITION_CODE;
    vector<pair<string, int>> SYMTAB, LITTAB;
    vector<int> POOLTAB;

    generateTabs(OPTAB, REG, CONDITION_CODE);

    ifstream inp;
    inp.open("input.txt");
    ofstream out;
    out.open("ic.txt");
    string label, opcode, opr1, opr2;
    int index = 0, lc = 0, poolStart = 0;
    string outstr = "";
    while (inp.eof() != 1)
    {
        outstr  = "" ;
        inp >> label >> opcode >> opr1 >> opr2;
        // cout << opcode <<  ' ' << OPTAB[opcode].first << ' ' << OPTAB[opcode].second <<  "\n" ;
        if (label != "_")
        {
            index = getindex(SYMTAB, label);
            if (index == -1)
            {
                SYMTAB.push_back({label, lc});
            }
        }
        outstr += ("(" + OPTAB[opcode].first + ", " + OPTAB[opcode].second + ")\t");
        if(opcode == "LTORG")outstr +=  "\n" ;

        if (OPTAB[opcode].first == "IS")
        {
            if (opr1 != "_")
            {
                if (REG[opr1])
                {
                    outstr += "(" + to_string(REG[opr1]) + ")\t" ;
                }
                else
                    outstr += "(" + to_string(CONDITION_CODE[opr1]) + ")\t";
            }
            else
                outstr += "_\t";

            if (opr2 != "_")
            {
                if (opr2.substr(0, 2) == "='")
                {
                    index = getindex(LITTAB, opr2 , poolStart);
                    if (index == -1)
                        LITTAB.push_back({opr2, -1}), index = getindex(LITTAB, opr2, poolStart);
                    outstr += "(L , " + to_string(index + 1)  + ")\t";
                }
                else
                {
                    index = getindex(SYMTAB, opr2);
                    if (index == -1){
                        SYMTAB.push_back({opr2, -1}); 
                        index = getindex(SYMTAB, opr2);
                    }
                    outstr += "(S , " + to_string(index + 1) + ")\t";
                }
            }
            else
                outstr += "_\t";

                out << outstr << "\n" ;
                ++lc ;
        }


        else if (OPTAB[opcode].first == "AD")
        {
            if (opcode == "START")
            {
                if (opr2 != "_")
                    lc = stoi(opr2);
                // cout << lc << "\n" ;
                outstr += "_\t(C , " + to_string(lc) + " )\t";
                out << outstr << "\n";
            }
            else if (opcode == "END")
            {

                for (int i = poolStart; i < LITTAB.size(); ++i)
                {
                    LITTAB[i].second = lc;
                    int littab_num = stoi(LITTAB[i].first.substr(2, 1));
                    outstr += "\n(DL ,01)\t(C , " + to_string(littab_num) + " )\n";

                    out << outstr << "\n";
                    ++lc;
                }
                POOLTAB.push_back(poolStart + 1);

                poolStart = LITTAB.size();
            }
            else if (opcode == "ORIGIN" || opcode == "EQU")
            {
                string tmp_opr2 = "";
                string tmp_label = "";
                int val = 0;
                char op = ' ';
                if (opcode == "ORIGIN")
                {
                    int i = 0;
                    while (i < opr2.size())
                    {
                        if (opr2[i] == '+' || opr2[i] == '-')
                            break;
                        tmp_opr2 += opr2[i];
                        ++i;
                    }

                    if (i < opr2.size())
                    {
                        op = (opr2[i]);
                        val = stoi(opr2.substr(i + 1, opr2.size() - i - 1));
                    }

                    int opr2_index = getindex(SYMTAB, tmp_opr2);
                    if (op != ' ' && op == '+')
                        lc = SYMTAB[opr2_index].second + val;
                    else if (op != ' ' && op == '-')
                        lc = SYMTAB[opr2_index].second - val;

                    outstr += "_\t(S , 0" + to_string(opr2_index + 1) + ")+" + to_string(val);
                }
                else
                {
                    int i = 0;
                    while (i < opr2.size())
                    {
                        if (opr2[i] == '+' || opr2[i] == '-')
                            break;
                        tmp_opr2 += opr2[i];
                        ++i;
                    }
                    if (i < opr2.size())
                    {
                        op = (opr2[i]);
                        val = stoi(opr2.substr(i + 1, opr2.size() - i - 1));
                    }
                    // cout << tmp_opr2 << "\n" ;

                    int label_index = getindex(SYMTAB, label);
                        // cout <<label << ' ' <<  label_index << "\n" ;
                    if (label_index == -1){
                        SYMTAB.push_back({label, -1});
                        label_index = getindex(SYMTAB , label) ;
                    }
                    int opr2_index = getindex(SYMTAB, tmp_opr2);
                    // cout << opr2_index << "\n" ;
                    
                        if (op == '+')
                            SYMTAB[label_index].second = SYMTAB[opr2_index].second - val;
                        else if(op == '-')
                            SYMTAB[label_index].second = SYMTAB[opr2_index].second + val;
                        else 
                            SYMTAB[label_index].second = SYMTAB[opr2_index].second ;
                    
                    outstr += "_\t(S , 0" + to_string(opr2_index + 1) + ")+" + to_string(val);
                }

                out << outstr << "\n";
            }
            // LTORG PROCESSING
            else
            {
                // cout << LITTAB.size() << ' ' ;
                // cout << "Poolstart  = " << poolStart << "\n" ;
                // for(auto x : LITTAB){
                //     cout << x.first << ' ' ;
                // }
                // cout << "\n" ;
                for (int i = poolStart; i < LITTAB.size(); ++i)
                {
                    LITTAB[i].second = lc;
                    int littab_num = stoi(LITTAB[i].first.substr(2, 1));
                    outstr += "(DL ,01)\t(C , " + to_string(littab_num) + ")\n";

                    ++lc;
                }
                out << outstr << "\n";
                POOLTAB.push_back(poolStart + 1);

                poolStart = LITTAB.size();
            }
        }
        else
        {
            int val = stoi(opr2);

            index = getindex(SYMTAB, label);
            if (index == -1)
                SYMTAB.push_back({label, lc});
            else
                SYMTAB[index].second = lc;

            lc += (opr1 == "DS" ? val : 1);

            outstr += "(C , " + to_string(val) + " )";

            out << outstr << "\n";
        }
    }

    string line;
    // Inserting SYMTAB into SymbolTable.txt
    ofstream TAB;
    TAB.open("symbolTable.txt");
    for (int i = 0; i < SYMTAB.size(); i++)
    {
        line = SYMTAB[i].first + " " + to_string(SYMTAB[i].second);
        TAB << line << endl;
    }
    TAB.close();

    // Inserting LITTAB into literalTable.txt
    TAB.open("literalTable.txt");
    for (int i = 0; i < LITTAB.size(); i++)
    {
        line = LITTAB[i].first + " " + to_string(LITTAB[i].second);
        TAB << line << endl;
    }
    TAB.close();

    // Inserting POOLTAB into poolTable.txt
    TAB.open("poolTable.txt");
    for (int i = 0; i < POOLTAB.size(); i++)
    {
        TAB << POOLTAB[i] << endl;
    }
    TAB.close();

    inp.close(), out.close();
    return 0;
}
