#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <math.h>
#include <map>
#include <vector>
#include <set>
using namespace std;
map <string, vector<string>> XarAuto;
map <string, vector<int>> I_XarAuto;
map <string, vector<double>> D_XarAuto;
map <string, vector<string>> S_XarAuto;
map <string, vector<double>> New_Dan;
vector <string> key;
vector <string> Nkey;
vector <char> tipd;
void Cout(string s);
void Korect(string x);
void Info();
void RasprDan();
void PreobrDan();
void IntDan(string x);
void DoublDan(string x);
void StrDan(string x);
void Bin(string x, string s1, string s2);
void Matr(set <string> st, string x);
void Vaborka(vector <int>& vb, set <int>& k, int n);
string Prov(string s);
int Pousk(string s, vector <string> k);
int main()
{
    fstream fin("CarPrice_Assignment.csv");
    string s, x;
    getline(fin, x);
    stringstream stream(x);
    while (getline(stream, s, ',')) {
        key.push_back(s);
        XarAuto[s];
    }
    while (getline(fin, x)) {
        stringstream stream(x);
        int i = 0;
        while (getline(stream, s, ',')) {
            XarAuto[key[i]].push_back(s);
            i++;
        }
    }
    Korect("CarName");
    Info();
    RasprDan();
    PreobrDan();
    vector <string> tabl;
    int n = *max_element(I_XarAuto[key[0]].begin(), I_XarAuto[key[0]].end());
    for (int i = 0; i <= n; i++)
        tabl.push_back("");
    for (auto i : Nkey) {
        tabl[0] += i + " ";
        for (int j = 0; j < New_Dan[i].size(); j++)
            tabl[j+1] += to_string(New_Dan[i][j])+" ";
    }
    vector <int> obvb;
    vector <int> testvb;
    set <int> kol;
    ofstream fout("Otv.txt");
    fout << n * 0.8 << ' ' << *max_element(D_XarAuto["price"].begin(), D_XarAuto["price"].end()) << ' ' << *min_element(D_XarAuto["price"].begin(), D_XarAuto["price"].end()) << '\n';
    Vaborka(obvb, kol, round(n * 0.8));
    Vaborka(testvb, kol, n);
    fout << tabl[0] << "\n";
    for (auto i : obvb)
        fout << tabl[i] << '\n';
    fout << "\n\n";
    ofstream fout1("Test.txt");
    for (auto i : testvb)
        fout1 << tabl[i] << '\n';
    fout.close();
    return 0;
}
void Cout(string s) {
    for (auto i : XarAuto[s]) {
        cout << i << ' ';
    }
    cout << '\n';
}
string Prov(string s) {
    bool Int = true;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '.') {
            Int = false;
            continue;
        }
        if (!isdigit(s[i]))
            return "str";
    }
    if (Int) return "int";
    return "double";
}
void Korect(string x) {
    set <string> Avto;
    for (int i = 0; i < XarAuto[x].size(); i++) {
        stringstream stream(XarAuto[x][i]);
        string s;
        getline(stream, s, ' ');
        if (s == "vw" || s == "vokswagen")
            s = "volkswagen";
        if (s == "Nissan")
            s = "nissan";
        if (s == "maxda")
            s = "mazda";
        if (s == "toyouta")
            s = "toyota";
        if (s == "porcshce")
            s = "porsche";
        XarAuto[x][i] = s;
        Avto.insert(XarAuto[x][i]);
    }
}
void Info() {
    for (auto i : key) {
        string s = Prov(XarAuto[i][0]);
        if (i == "price" || i == "compressionratio") s = "double";
        if (s == "double") tipd.push_back('d');
        else if (s == "int") tipd.push_back('i');
        else tipd.push_back('s');
        //cout << i << '\t' << XarAuto[i].size() << " " << s << '\n';
    }
}
void RasprDan() {
    for (int i = 0; i < tipd.size(); i++) {
        if (tipd[i] == 'i') {
            for (auto j : XarAuto[key[i]]) {
                I_XarAuto[key[i]].push_back(stoi(j));
            }
        }
        else if (tipd[i] == 'd') {
            for (auto j : XarAuto[key[i]]) {
                D_XarAuto[key[i]].push_back(stod(j));
            }
        }
        else {
            for (auto j : XarAuto[key[i]]) {
                S_XarAuto[key[i]].push_back(j);
            }
        }
    }
}
void  PreobrDan() {
    for (auto i : key) {
        if (i == "car_ID") 
            continue;
        if (I_XarAuto.find(i) != I_XarAuto.end())
            IntDan(i);
        else if (D_XarAuto.find(i) != D_XarAuto.end())
            DoublDan(i);
        else StrDan(i);
    }
}
void IntDan(string x) {
    double min = *min_element(I_XarAuto[x].begin(), I_XarAuto[x].end());
    double max = *max_element(I_XarAuto[x].begin(), I_XarAuto[x].end());
    //cout << x <<":\t" << min << '\t' << max << '\n';
    for (auto j : I_XarAuto[x]) {
        New_Dan[x].push_back((double(j) - min) / (max - min));
        if(Pousk(x, Nkey) == -1)
            Nkey.push_back(x);
    }
}
void DoublDan(string x) {
    double min = *min_element(D_XarAuto[x].begin(), D_XarAuto[x].end());
    double max = *max_element(D_XarAuto[x].begin(), D_XarAuto[x].end());
    //cout << x << ":\t" << min << '\t' << max << '\n';
    for (auto j : D_XarAuto[x]) {
        New_Dan[x].push_back((j - min) / (max - min));
        if (Pousk(x, Nkey) == -1)
            Nkey.push_back(x);
    }
}
void StrDan(string x) {
    set <string> st;
    for (auto i : S_XarAuto[x])
        st.insert(i);
    auto it = st.begin();
    //cout <<x <<'\t' << st.size() << '\n';
    if (st.size() == 2)
        Bin(x, *it, *(++it));
    else if (st.size() > 2){
        Matr(st, x);
    }
}
void Bin(string x, string s1, string s2) {
    for (auto i : XarAuto[x]) {
        if (i == s1) New_Dan[x].push_back(1);
        else New_Dan[x].push_back(-1);
        if (Pousk(x, Nkey) == -1)
            Nkey.push_back(x);
    }
}
void Matr(set <string> st, string x) {
    int n = Nkey.size();
    for (string i : st) 
        if (Pousk(i, Nkey) == -1)
            Nkey.push_back(i);
    for (auto i : XarAuto[x]) {
        for (int j = n; j < Nkey.size(); j++) {
            if (i == Nkey[j])
                New_Dan[Nkey[j]].push_back(1);
            else New_Dan[Nkey[j]].push_back(0);
        }
    }
}
int Pousk(string s, vector <string> k) {
    for (int i = 0; i < k.size(); i++) {
        if (s == k[i])
            return i;
    }
    return -1;
}
void Vaborka(vector <int>& vb, set <int>& k, int n) {
    while (k.size() < n) {
        int x = k.size();
        int y = rand() % 205 + 1;
        k.insert(y);
        if (x != k.size())
            vb.push_back(y);
    }
    //cout << k.size() <<'\n';
}