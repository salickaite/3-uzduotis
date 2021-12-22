#include "funkcijos.h"
#include "laikmatis.h"
#include <numeric>

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream> 
#include <random>
#include <numeric>
#include <list>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;
using std::left;
using std::setprecision;
using std::sort;
using std::getline;
using std::vector;
using std::ifstream;
using std::stringstream;
using std::exception;

//STRUKTURA:
vector<studentas> grupe_vec;
vector<studentas> vargsiukai_v;
vector<studentas> kietiakai_v;

list<studentas> grupe_lst;
list<studentas> vargsiukai_l;
list<studentas> kietiakai_l;

//KLASE:
vector<Studentas> grupe_vec_;
vector <Studentas> vargsiukai_v_;


void pild(studentas& kint)
{
    float sum = 0, vid = 0, n, med;
    int count = 0;

    cout << "Iveskite studento varda ir pavarde: ";
    cin >> kint.vardas >> kint.pavarde;

    cout << "Jei norite, kad studentu pazymiai butu generuojami AUTOMATISKAI spauskite \"A\".\n Jei norite pazymius suvesti PATYS spauskite \"P\". ";
    char ats;
    cin >> ats;
    while (cin.fail() || (ats != 'a' && ats != 'A' && ats != 'p' && ats != 'P')) {
        cout << "Netinkamai ivesta komanda. Pasirinkite A (automatiskai) arba P (patys). " << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> ats;
    }
    if (ats == 'a' || ats == 'A')
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(1, 10);
        cout << "Iveskite pazymiu skaiciu: ";
        int sk;

        tikrinimas(sk);
        for (int i = 0; i < sk; i++) {
            int x = dist(mt);
            kint.nd.push_back(x);
            sum += kint.nd[i];
        }
        kint.egz = dist(mt);
        cout << "Jei norite, kad galutinis pazymys butu pateiktas su VIDURKIU iveskite \"V\".\n Jei su MEDIANA iveskite \"M\".  ";
        cin >> kint.skaiciavimas;
        while (cin.fail() || (kint.skaiciavimas != 'v' && kint.skaiciavimas != 'V' && kint.skaiciavimas != 'm' && kint.skaiciavimas != 'M')) {
            cout << "Klaida! Iveskite raides 'v' arba 'm'" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> kint.skaiciavimas;
        }
        vid = sum / sk;
        med = mediana(kint.nd);
        kint.gal_vid = vid * 0.4 + 0.6 * kint.egz;
        kint.gal_med = med * 0.4 + 0.6 * kint.egz;

    }
    else if (ats == 'p' || ats == 'P')
    {
        cout << "Iveskite namu darbu pazymius (kai baigsite, iveskite bet kokia raide): " << endl;
        while (cin >> n)
        {
            kint.nd.push_back(n);
            sum += n;
            count++;
        }


        while (count == 0)
        {
            cout << "Netinkamai ivesta komanda. Iveskite bent 1 pazymi. " << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while (cin >> n) {
                kint.nd.push_back(n);
                sum += n;
                count++;
            }
        }

        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


        cout << "Iveskite egzamino pazymi: ";

        tikrinimas(kint.egz);

        cout << "Jei norite, kad galutinis pazymys butu pateiktas su VIDURKIU iveskite \"V\".\n Jei su MEDIANA iveskite \"M\".  ";
        cin >> kint.skaiciavimas;
        while (cin.fail() || (kint.skaiciavimas != 'v' && kint.skaiciavimas != 'm')) {
            cout << "Netinkamai ivesta komanda. Pasirinkite V (vidurkis) arba M (mediana) " << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> kint.skaiciavimas;
        }

        vid = sum / count;
        med = mediana(kint.nd);

        kint.gal_vid = vid * 0.4 + 0.6 * kint.egz;
        kint.gal_med = med * 0.4 + 0.6 * kint.egz;
    }
}

void printas(studentas& kin)
{
    if (kin.skaiciavimas == 'v' || kin.skaiciavimas == 'V')
    {
        cout << setw(20) << left << kin.vardas << setw(20) << left << kin.pavarde << setw(20) << left << setprecision(3) << kin.gal_vid << endl;
    }
    else
        cout << setw(20) << left << kin.vardas << setw(20) << left << kin.pavarde << setw(20) << left << setprecision(3) << kin.gal_med << endl;
}

float mediana(vector<float> vec)
{
    typedef vector<float>::size_type vecSize;
    vecSize size = vec.size();
    if (size == 0)
        throw std::domain_error("Netinkama ivestis. Negalima skaiciuoti medianos tusciame vektoriuje. ");
    sort(vec.begin(), vec.end());
    vecSize vid = size / 2;
    return size % 2 == 0 ? (vec[vid] + vec[vid - 1]) / 2 : vec[vid];
}

bool compare_final(studentas& a, studentas& b)
{
    return a.gal_vid > b.gal_vid;
}

void print_student(studentas& stud)
{
    cout << setw(20) << left << stud.vardas << setw(20) << left << stud.pavarde << setw(20) << left << setprecision(3) << stud.gal_vid << setw(20) << left << setprecision(3) << stud.gal_vid << endl;
}

void tikrinimas(int& a) {
    cin >> a;
    do {
        try {
            if (cin.fail()) { throw std::runtime_error("Netinkamai ivesta komanda. \n"); }
        }
        catch (const std::runtime_error& e) {
            cout << e.what();
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Bandykite dar karta: ";
            cin >> a;
        }

    } while (cin.fail() == true);
}

bool func(studentas st)
{
    return st.gal_vid < 5;
}

bool pred(studentas st)
{
    return st.gal_vid >= 5;
}

void create_file(string name, float sk) 
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);

    std::ofstream failas;
    failas.open(name);

    for (unsigned int i = 1; i < sk + 1; i++) {
        int nd1 = dist(mt);
        int nd2 = dist(mt);
        int nd3 = dist(mt);
        int nd4 = dist(mt);
        int nd5 = dist(mt);
        int egz = dist(mt);
        failas << "Vardas" << i << "    Pavarde" << i << "        " << setw(10) << left << nd1 << setw(10) << left << nd2 << setw(10) << left << nd3 << setw(10) << left << nd4 << setw(10) << left << nd5 << setw(10) << left << egz << endl;
    }
    failas.close();

}

//VEKTORIAI:

void nuskaitymas_v(string read) 
{

    string eil;
    vector<string> eilutes;

    ifstream failas(read);
    if (!failas) {
        throw exception();
    }
    while (failas) {
        if (!failas.eof()) {
            std::getline(failas, eil);
            eilutes.push_back(eil);

        }
        else break;

    }
    failas.close();

    eilutes.pop_back();


    for (auto eil : eilutes)
    {
        stringstream s(eil);
        studentas tempas;
        float sum, vid;
        s >> tempas.vardas >> tempas.pavarde;
        int k;
        while (s >> k)
        {
            tempas.nd.push_back(k);
        }

        tempas.egz = tempas.nd.back();
        tempas.nd.pop_back();

        sum = std::accumulate(tempas.nd.begin(), tempas.nd.end(), 0);

        vid = sum / tempas.nd.size();

        float med = mediana(tempas.nd);

        tempas.gal_vid = 0.4 * vid + 0.6 * tempas.egz;
        tempas.gal_med = med * 0.4 + 0.6 * tempas.egz;
        grupe_vec.push_back(tempas);
    }
}

void padalijimas1(vector<studentas>& vec)
{
    for (auto p : vec)
    {
        if (p.gal_vid < 5)
        {
            vargsiukai_v.push_back(p);
        }
        else
        {
            kietiakai_v.push_back(p);
        }
    }
}

void padalijimas2(vector<studentas>& vec)
{
    for (studentas p : vec) {
        if (p.gal_vid < 5) {
            vargsiukai_v.push_back(p);
        }
    }
    vec.erase(remove_if(vec.begin(), vec.end(), func), vec.end());
}

void padalijimas3(vector<studentas>& vec)
{
    std::partition(vec.begin(), vec.end(), pred);

    vector<studentas>::iterator it = std::partition_point(vec.begin(), vec.end(), pred);
    for (it; it != vec.end(); it++)
    {
        vargsiukai_v.push_back(*it);
    }

    vec.erase(std::partition_point(vec.begin(), vec.end(), pred), vec.end());
}

void isvedimas(vector<studentas>& vec, string pav)
{
    std::ofstream failas;
    failas.open(pav);
    failas << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left << "Galutinis balas" << "\n";
    for (auto p : vec)
    {

        failas << setw(20) << left << p.vardas << setw(20) << left << p.pavarde << setw(20) << left << p.gal_vid << "\n";
    }

    failas.close();
}


//LISTAI:

void nuskaitymas_l(string read)
{

    string eil;
    vector<string> eilutes;

    ifstream failas(read);
    if (!failas)
    {
        throw exception();
    }
    while (failas)
    {
        if (!failas.eof()) {
            std::getline(failas, eil);
            eilutes.push_back(eil);

        }
        else break;

    }
    failas.close();

    eilutes.pop_back();


    for (auto eil : eilutes)
    {
        stringstream s(eil);
        studentas tempas;
        float sum, vid;
        s >> tempas.vardas >> tempas.pavarde;
        int k;
        while (s >> k)
        {
            tempas.nd.push_back(k);

        }

        tempas.egz = tempas.nd.back();
        tempas.nd.pop_back();

        sum = std::accumulate(tempas.nd.begin(), tempas.nd.end(), 0);

        vid = sum / tempas.nd.size();

        float med = mediana(tempas.nd);

        tempas.gal_vid = vid * 0.4 + 0.6 * tempas.egz;
        tempas.gal_med = med * 0.4 + 0.6 * tempas.egz;
        grupe_lst.push_back(tempas);
    }
}

void padalijimas1(list<studentas>& lst)
{
    for (auto p : lst)
    {
        if (p.gal_vid < 5)
        {
            vargsiukai_l.push_back(p);
        }
        else
        {
            kietiakai_l.push_back(p);
        }
    }
}

void padalijimas2(list<studentas>& lst)
{
    for (studentas p : lst)
    {
        if (p.gal_vid < 5)
        {
            vargsiukai_v.push_back(p);

        }
    }
    lst.erase(remove_if(lst.begin(), lst.end(), func), lst.end());
}

void padalijimas3(list<studentas>& lst)
{
    std::partition(lst.begin(), lst.end(), pred);

    list<studentas>::iterator it = std::partition_point(lst.begin(), lst.end(), pred);
    for (it; it != lst.end(); it++)
    {
        vargsiukai_v.push_back(*it);
    }

    lst.erase(std::partition_point(lst.begin(), lst.end(), pred), lst.end());
}

void isvedimas(list<studentas>& lst, string pav) 
{
    std::ofstream failas;
    failas.open(pav);
    failas << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left << "Galutinis balas" << "\n";
    for (auto p : lst) {

        failas << setw(20) << left << p.vardas << setw(20) << left << p.pavarde << setw(20) << left << p.gal_vid << "\n";
    }

    failas.close();
}

void testas(string name)
{
    cout << endl;
    cout << "NAUDOJANT STRUKTURA:" << endl << endl;
    Timer t0;
    Timer t;
    try
    {
        nuskaitymas_v(name);
    }

    catch (exception& e)
    {
        cout << "Failas neegzistuoja! Patikrinkite failo varda ir meginkite is naujo..." << endl;
        exit(EXIT_FAILURE);
    }

    float t1 = t.elapsed();
    cout << "Nuskaitymas uztruko: " << t1 << " s" << endl;
    t.reset();
    padalijimas3(grupe_vec);
    float t2 = t.elapsed();
    cout << "Padalijimas uztruko: " << t2 << " s" << endl;
    grupe_vec.clear();
    vargsiukai_v.clear();
    float tv = t0.elapsed();
    cout << "Visas testo laikas: " << tv << endl;


    cout << endl << "NAUDOJANT KLASE:" << endl << endl;
    t0.reset();
    t.reset();
    try
    {
        Studentas::nuskaitymas_v_(name);
    }


    catch (exception& e)
    {
        cout << "Failas neegzistuoja! Patikrinkite failo varda ir bandykite dar karta. " << endl;
        exit(EXIT_FAILURE);
    }

    float t1_ = t.elapsed();
    cout << "Nuskaitymas uztruko: " << t1_ << " s" << endl;
    t.reset();
    Studentas::padalijimas3_(grupe_vec_);
    float t2_ = t.elapsed();
    cout << "Padalijimas uztruko: " << t2_ << " s" << endl;
    grupe_vec_.clear();
    vargsiukai_v.clear();
    float tv_ = t0.elapsed();
    cout << "Visas testo laikas: " << tv_ << endl;
    cout << endl << "Nuskaitymo santykis (struct/class): " << t1 / t1_ << endl;
    cout << "Padalijimo santykis (struct/class): " << t2 / t2_ << endl;
    cout << "Viso testo laiko santykis (struct/class): " << tv / tv_ << endl;
}

void uzpildymas()
{
    char a;
    string fileName;
    cout << "Jei norite duomenis nuskaityti is failo iveskite T (taip) arbe N (ne): ";
    cin >> a;
    if (a == 't' || a == 'T') {
        cout << "Irasykite failo pavadinima: ";
        cin >> fileName;
        try {
            Studentas::nuskaitymas_v_(fileName);
        }


        catch (std::exception& e) {
            cout << "Failas neegzistuoja! Patikrinkite failo varda ir bandykite dar karta. " << endl;
            exit(EXIT_FAILURE);
        }
        cout << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left << "Galutinis(Vid.)/Galutinis(Med.)" << endl;
        for (auto p : grupe_vec_) {
            cout << setw(20) << left << p.vardas() << setw(20) << left << p.pavarde() << setw(20) << left << p.gal_vid() << endl;
        }

    }
    else
    {
        cout << "Irasykite studentu skaiciu:  " << endl;
        int n;
        tikrinimas(n);
        for (int i = 0; i < n; i++) {
            Studentas temp;
            temp.pild();
            grupe_vec_.push_back(temp);
        }
        cout << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left << "Galutinis(Vid.)/Galutinis(Med.)" << endl;
        for (auto p : grupe_vec_) {
            cout << setw(20) << left << p.vardas() << setw(20) << left << p.pavarde() << setw(20) << left << p.gal_vid() << endl;
        }
    }

}