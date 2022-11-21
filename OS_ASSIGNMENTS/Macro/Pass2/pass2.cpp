#include <bits/stdc++.h>
using namespace std;

vector<string> tokenize(string s, char seperator)
{
    vector<string> tokens;
    string token;
    istringstream ss(s);
    while (getline(ss, token, seperator))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int main()
{
    ifstream inp;
    inp.open("input.txt");
    string ins = "";
    bool begin = 0;

    map<string, string> KPD;
    map<string, vector<string>> PNT;
    ifstream kp, pn;
    kp.open("../Pass1/kpd.txt");
    while (kp.eof() != 1)
    {
        string word, val;
        kp >> word >> val;
        KPD[word] = val;
    }
    kp.close();
    pn.open("../Pass1/pntab.txt");
    while (pn.eof() != 1)
    {
        string line = "";
        getline(pn, line);
        vector<string> tmp = tokenize(line, ' ');
        string name = tmp[0];
        for (int i = 1; i < tmp.size(); ++i)
        {
            PNT[name].push_back(tmp[i]);
        }
    }
    pn.close();
    ofstream out;
    out.open("pass2output.txt");
    string curr_token = "", macro_name = "";
    ifstream mdt;
    mdt.open("../Pass1/mdt.txt");
    while (inp.eof() != 1)
    {
        vector<string> APTAB;
        string line = "";
        getline(inp, line);
        map<string, string> m;
        vector<string> token = tokenize(line, ' ');
        if (token[0] == "START")
        {
            begin = 1;
            continue;
        }
        else if (token[0] == "END")
            break;
        if (begin)
        {
            m.clear();
            macro_name = token[0];
            for (int i = 0; i < PNT[macro_name].size(); ++i)
            {
                curr_token = PNT[macro_name][i];
                // if a keyword parameter
                if (KPD.find(curr_token) != KPD.end())
                {
                    m[curr_token] = KPD[curr_token];
                }
            }
            for (int i = 1; i < token.size(); ++i)
            {
                APTAB.push_back(token[i]);
                // checking for keyword
                if (token[i].find('=') != string ::npos)
                {
                    vector<string> keyword = tokenize(token[i], '=');
                    m[keyword[0].replace(0,1,"")] = keyword[1];
                }
                // else if positional parameter
                else
                {
                    string pos_param = "";
                    for (int j = 0; j < PNT[macro_name].size(); ++j)
                    {
                        if (j + 1 == i)
                        {
                            pos_param = PNT[macro_name][j];
                        }
                    }
                    m[pos_param] = token[i];
                }
            }
            // for(auto x : m){
            //     cout << x.first << ' '<< x.second << "\n" ;
            // }
            // start reading from KPDTB ;
            // cout << macro_name << "\n" ;
            while (mdt.eof() != 1)
            {
                string output = "";
                line = "";
                getline(mdt, line);
                vector<string> code = tokenize(line, ' ');
    
                // vector<string> code(2);
                for(auto x : code){
                    cout << x  << ' ' ;
                }
                cout << "\n" ;
                if (code[0] == "MEND")
                {
                    // cout << "here\n" ;
                    break;
                }
                output += code[0] + " ";
                for (int i = 1; i < code.size(); ++i)
                {
                    curr_token = code[i];
                    // cout << curr_token << "\n" ;/
                    if (curr_token.find('=') == string ::npos)
                    {
                        int pnt_index = stoi(curr_token.substr(3, curr_token.size() - 4));
                        output += m[PNT[macro_name][pnt_index - 1]] + " ";
                    }
                    else
                        output += curr_token;
                }
                    out << output << "\n";
                // cout << output << "\n" ;
            }
        }
    }
    mdt.close() ;
    out.close() ;
    inp.close();
}
