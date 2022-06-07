#include "library.h"

using namespace std;


struct zodis {
    string zodziai;
    float pasikartojimai;
    vector<int> eilute;
};


bool compare(zodis A, zodis B)
{ 
    return (A.pasikartojimai > B.pasikartojimai); 
}

string mazosios(string word){
        if (!word.empty()) {
        word.erase(remove(word.begin(), word.end(), '.'), word.end());
        word.erase(remove(word.begin(), word.end(), '!'), word.end());
        word.erase(remove(word.begin(), word.end(), ','), word.end());
        word.erase(remove(word.begin(), word.end(), '?'), word.end());
        word.erase(remove(word.begin(), word.end(), '('), word.end());
        word.erase(remove(word.begin(), word.end(), ')'), word.end());
        word.erase(remove(word.begin(), word.end(), ':'), word.end());
        word.erase(remove(word.begin(), word.end(), ';'), word.end());
        word.erase(remove(word.begin(), word.end(), '-'), word.end());
        word.erase(remove(word.begin(), word.end(), '"'), word.end());
    }

     if (!word.empty()) {
        if ((word[0] >= 'A' && word[0] <= 'Z')) {
            word[0] = tolower(word[0]);
        }
    }

    return word;
}


string check(string zodis) {

    if (!zodis.empty()) {
        for (int i = 1; i < zodis.length() - 1;i++) {
            if (zodis[i] == '.' && isalnum(zodis[0])) {
                if (zodis[zodis.length() - 1] == '/' || isalnum(zodis[zodis.length() - 1])) {
                    return "link";
                    break;
                }
            }
        }

    }

    if (!zodis.empty()) {
        zodis.erase(remove(zodis.begin(), zodis.end(), '.'), zodis.end());
        zodis.erase(remove(zodis.begin(), zodis.end(), '!'), zodis.end());
        zodis.erase(remove(zodis.begin(), zodis.end(), ','), zodis.end());
        zodis.erase(remove(zodis.begin(), zodis.end(), '?'), zodis.end());
        zodis.erase(remove(zodis.begin(), zodis.end(), '('), zodis.end());
        zodis.erase(remove(zodis.begin(), zodis.end(), ')'), zodis.end());
        zodis.erase(remove(zodis.begin(), zodis.end(), ':'), zodis.end());
        zodis.erase(remove(zodis.begin(), zodis.end(), ';'), zodis.end());
        zodis.erase(remove(zodis.begin(), zodis.end(), '-'), zodis.end());
        zodis.erase(remove(zodis.begin(), zodis.end(), '"'), zodis.end());
    }

    if (!zodis.empty()) {
        if ((zodis[0] >= 'A' && zodis[0] <= 'Z')) {
            zodis[0] = tolower(zodis[0]);
        }
    }


    if (!zodis.empty() && !(std::isdigit(zodis[0]))) {
        return zodis;
    }

    else {
        return "";
    }

}

void ivedimas(map<string, vector<int>>& unique, vector<zodis>& zodziuKratinys, string file) {

    map<string, vector<int>>::iterator it;
    zodis zodis;

    int eilute = 0;
    string zodziai, eil;
    stringstream my_buffer;
    ifstream openf;

    openf.open(file);

    while (!openf) {
        cout << file << " nerastas" << endl;
        cout << "Iveskite egzistuojanti faila(formatu 'pavyzdys.txt')" << endl;
        cin >> file;
        openf.open(file);
    }
    my_buffer << openf.rdbuf();
    openf.close();
    while (getline(my_buffer, eil)) {
        eilute++;
        istringstream is(eil);
        while (is >> zodziai) {
            if (check(zodziai) == "link") {
                cout << zodziai << endl;
            }
            else if (check(zodziai) != "") {
                auto value = unique.insert(make_pair(mazosios(zodziai), 0));
                it = unique.find(mazosios(zodziai));
                unique[it->first].push_back(eilute);
            }
        }
    }
    for (auto zodiss : unique) {
        if (zodiss.second.size() > 1) {
            zodis.zodziai = zodiss.first;
            zodis.pasikartojimai = zodiss.second.size();
            zodis.eilute = zodiss.second;
            zodziuKratinys.push_back(zodis);
        }
    }

    sort(zodziuKratinys.begin(), zodziuKratinys.end(), compare);

}

void isvedimas(vector<zodis> zodziuKratinys) {
    ofstream fd("atsakymas.txt");

    for (int i = 0; i < zodziuKratinys.size(); i++) {
        fd << "Zodis - " << zodziuKratinys[i].zodziai << " pasikartoja " << zodziuKratinys[i].pasikartojimai;
        if (zodziuKratinys[i].pasikartojimai >= 10) {
            fd << " kartu. Eilutes, kuriose pasikartojo zodziai: ";
        }
        else if ((zodziuKratinys[i].pasikartojimai)  == 1) {
            fd << " karta. Eilute, kurioje buvo zodis";
        }
        else {
            fd << " kartus. Eilutes, kuriose pasikartojo zodis: ";
        }
        for (int j = 0; j < zodziuKratinys[i].eilute.size(); j++) {
            if (zodziuKratinys[i].eilute[j] != zodziuKratinys[i].eilute[j - 1])
                fd << " " << zodziuKratinys[i].eilute[j];
        }

        fd << "\n";
    }

    fd.close();
}

int main()
{
    setlocale(LC_ALL, "Lithuanian");

    vector<zodis> zodziuKratinys;
    map<string, vector<int> > unique;

    string file;

    cout << "Del geriausio rezultato naudokite faila parasyta Lietuviu raide" << endl;
    cout << "Iveskite faila, kurio formatas: file.txt " << endl;
    cin >> file;

    auto start = std::chrono::high_resolution_clock::now(); auto st = start;
    ivedimas(unique, zodziuKratinys, file);
    isvedimas(zodziuKratinys);
    std::chrono::duration<double> diff1 = std::chrono::high_resolution_clock::now() - start; // Skirtumas (s)

    cout << "Programa uztruko " << diff1.count() << " s\n";



    return 0;
}