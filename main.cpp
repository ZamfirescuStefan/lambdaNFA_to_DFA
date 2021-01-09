#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;
ifstream f("config_automat");
class NFA{
private:
    int nr_stari;
    int nr_chr_alfabet;
    char alfabet[1001];
    int stare_initiala;
    int nr_stari_finale;
    int stari_finale[10001];
    int nr_tranzitii;
    vector <int > mat[100][100];
    int poz_in_alfabet( char a);
public:
    NFA();

    bool element_in_vector ( int element, vector <int> v);

    vector < int > stari_lambda ( int nod_curent);

    vector < int >  eliminare_lambda(int nod_curent, char value);

    int evaluate ( int n, char cuv[]);

    void interpretare_evaluate( char cuv[]);

    void display_mat();
};

int NFA::poz_in_alfabet(char a) {
    for ( int i = 0; i < nr_chr_alfabet; i ++ ){
        if (a == alfabet[i])
            return i;
    }
    return -1;
}

NFA::NFA() {
    {
        int x,y,poz;
        char val;
        char alf[1001];
        f >> nr_stari;
        f >> nr_chr_alfabet;
        for ( int i = 0; i < nr_chr_alfabet ; i++ )
            f >> alfabet[i];
        nr_chr_alfabet++;
        alfabet[nr_chr_alfabet - 1] = '$';
        f >> stare_initiala;
        f >> nr_stari_finale;
        for ( int i = 0; i < nr_stari_finale; i ++ )
            f >> stari_finale[i];
        f >> nr_tranzitii;
        for ( int i = 0; i < nr_tranzitii; i ++ ){
            f >> x;
            f >> val;
            f >> y;
            poz = poz_in_alfabet(val);
            mat[x][poz].push_back(y);
        }
    }
}
vector<int> NFA::stari_lambda(int nod_curent) {
    vector<int> noduri_finale;
    queue<int> noduri_de_verificat;

    noduri_de_verificat.push(nod_curent);
    noduri_finale.push_back(nod_curent);
    while (!noduri_de_verificat.empty()){
        int element = noduri_de_verificat.front();
        for ( int i = 0; i < mat[element][nr_chr_alfabet - 1].size(); i++ )
        {
            noduri_de_verificat.push(mat[element][nr_chr_alfabet - 1][i]);
            noduri_finale.push_back(mat[element][nr_chr_alfabet - 1][i]);
        }
        noduri_de_verificat.pop();
    }
    return noduri_finale;
}
vector<int > NFA::eliminare_lambda(int nod_curent, char value) {
    vector<int> noduri_finale;
    queue <int> noduri_de_verificat;
    set <int > :: iterator it;
    int poz = poz_in_alfabet(value);
    noduri_finale.push_back(nod_curent);
    for (int i = 0; i < mat[nod_curent][nr_chr_alfabet - 1].size(); i++) {
        noduri_de_verificat.push(mat[nod_curent][nr_chr_alfabet - 1][i]);
    }
    while (!noduri_de_verificat.empty()) {
        int element = noduri_de_verificat.front();
        if (element_in_vector(element,noduri_finale) == 0) {
            if (!mat[element][poz].empty()) {
                noduri_finale.push_back(element);
            }
        }
        if (mat[element][nr_chr_alfabet - 1].empty()) {
            noduri_finale.push_back(element);
            noduri_de_verificat.pop();
        } else {
            for (int i = 0; i < mat[element][nr_chr_alfabet - 1].size(); i++) {
                noduri_de_verificat.pop();
                noduri_de_verificat.push(mat[element][nr_chr_alfabet - 1][i]);
            }
        }
    }
    return noduri_finale;
}
void NFA::display_mat() {
    for ( int i = 0 ; i < nr_stari; i++ )
        for( int j = 0; j < nr_chr_alfabet; j++)
            for ( int k = 0; k < mat[i][j].size(); k++)
                cout << mat[i][j][k] << " ";

}

int  NFA::evaluate(int n, char *cuv) {
    int p = 0; /// poz din cuvant pe care o inspectez
    int poz;    /// pozitia characterului din alfabet
    int ok = 0;
    vector <int> stare_actuala;
    vector <int> vector_aux;
    stare_actuala.push_back(stare_initiala);
    vector <int > stare_actuala_aux;
    while ( p < n ){             /// cat timp mai exista litere in cuvant
        poz = poz_in_alfabet(cuv[p]);
        stare_actuala_aux.clear();
        for ( int k = 0; k < stare_actuala.size(); k++ ) {
            vector_aux = eliminare_lambda(stare_actuala[k],cuv[p]);
            for ( int i = 0; i < vector_aux.size(); i++ )
                for ( int j = 0; j < mat[vector_aux[i]][poz].size(); j++)
                    stare_actuala_aux.push_back(mat[vector_aux[i]][poz][j]);
        }
        if (stare_actuala_aux.empty()){
            return 0;
        }
        else
        {
            stare_actuala.clear();
            for ( int i = 0; i < stare_actuala_aux.size();i++ )
                stare_actuala.push_back(stare_actuala_aux[i]);
            p++;
        }
    }
    if ( ok != 1 ) {            /// Suntem la penultima litera din cuv si vedem daca ultima litera ne duce intr o stare finala
        vector_aux.clear();
        vector < int > noduriVerif;
        for ( int j = 0; j < stare_actuala.size(); j++ ) {
            vector_aux = eliminare_lambda(stare_actuala[j],cuv[p]);
            for (int i = 0; i < vector_aux.size(); i++)
                noduriVerif.push_back(vector_aux[i]);
        }
        for ( int i = 0; i < stare_actuala.size(); i++ )
        {
            vector < int > vct_aux;
            vct_aux = stari_lambda(stare_actuala[i]);
            for ( int j = 0; j < vct_aux.size(); j++ )
                for ( int k = 0; k < nr_stari_finale; k ++ )
                    if ( vct_aux[j] == stari_finale[k]){
                        return 1;
                    }
        }
    }
    return 0;
}
bool NFA::element_in_vector(int element, vector <int> v) {
    for (int i = 0; i < v.size(); i++) {
        int p = v[i];
        if (element == p)
            return 1;
    }
    return 0;
}

void NFA::interpretare_evaluate(char cuv[]) {
    if ( evaluate(strlen(cuv),cuv))
        cout << "The word is not accepted by this automata" <<"\n";
    else
        cout << "Cuvantul nu este acceptat by this automata" << "\n";
}

int main() {
    int n = 0;
    char cuv[1000];
    ifstream fin("lista_cuvinte");
    NFA ob;
    fin >> n;
    fin.get();
    for ( int i = 0; i < n; i ++ ){
        fin.get(cuv,100);
        fin.get();
        ob.interpretare_evaluate(cuv);
    }
    return 0;
}