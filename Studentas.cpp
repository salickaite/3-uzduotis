#include "Studentas.h"
#include "funkcijos.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

Studentas::Studentas(string v, string p, float g)
{
    vardas_ = v;
    pavarde_ = p;
    gal_vid_ = g;
}

Studentas::Studentas(const Studentas& st)
{
    vardas_ = st.vardas_;
    pavarde_ = st.pavarde_;
    egz_ = st.egz_;
    gal_vid_ = st.gal_vid_;
    nd_ = st.nd_;
}

Studentas& Studentas::operator=(const Studentas& st)
{
    if (&st == this) return *this;
    vardas_ = st.vardas_;
    pavarde_ = st.pavarde_;
    egz_ = st.egz_;
    gal_vid_ = st.gal_vid_;
    nd_ = st.nd_;
    return *this;
}

void Studentas::setVardas(string a) { vardas_ = a; }
void Studentas::setPavarde(string b) { pavarde_ = b; }
void Studentas::setEgz(int n) { egz_ = n; }
void Studentas::setND(vector<float> nd) { nd_ = nd; }
void Studentas::setGal_vid(float g) { gal_vid_ = g; }

float Studentas::vidurkis()
{
    if (nd_.size() == 0)
        throw std::domain_error("negalima skaiciuoti vidurkio tusciame vektoriuje. ");
    return std::accumulate(nd_.begin(), nd_.end(), 0.0) / nd_.size();
}

float Studentas::galBalas(const char s)
{
    if (s == 'v' || s == 'V')
    {
        gal_vid_ = 0.6 * egz_ + 0.4 * vidurkis();
        return gal_vid_;
    }
    else if (s == 'm' || s == 'M')
    {
        gal_vid_ = 0.6 * egz_ + 0.4 * mediana(nd_);
        return gal_vid_;
    }
}

void Studentas::pild()
{
    float n;
    int count = 0;

    cout << "Iveskite studento varda ir pavarde: ";
    cin >> vardas_ >> pavarde_;

    cout << "Jei norite, kad studentu pazymiai butu generuojami AUTOMATISKAI spauskite \"A\".\n Jei norite pazymius suvesti PATYS spauskite \"P\". ";
    char ats;
    cin >> ats;
    while (cin.fail() || (ats != 'a' && ats != 'A' && ats != 'P' && ats != 'p'))
    {
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
            nd_.push_back(x);
        }
        egz_ = dist(mt);
        galBalas('v');

    }
    else if (ats == 'p' || ats == 'P')
    {
        cout << "Iveskite namu darbu pazymius (kai baigsite, iveskite bet kokia raide): " << endl;
        while (cin >> n) {
            nd_.push_back(n);
            count++;
        }

        while (count == 0)
        {
            cout << "Netinkamai ivesta komanda. Iveskite bent 1 pazymi. " << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while (cin >> n)
            {
                nd_.push_back(n);
                count++;
            }
        }

        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


        cout << "Iveskite egzamino pazymi: ";

        tikrinimas(egz_);
        char a;

        cout << "Jei norite, kad galutinis pazymys butu pateiktas su VIDURKIU iveskite \"V\".\n Jei su MEDIANA iveskite \"M\".  ";
        cin >> a;
        while (cin.fail() || (a != 'v' && a != 'V' && a != 'm' && a != 'M'))
        {
            cout << "Netinkamai ivesta komanda. Pasirinkite V (vidurkis) arba M (mediana)" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> a;
        }

        galBalas(a);
    }
}

void Studentas::nuskaitymas_v_(string read)
{
    string eil;
    vector<string> eilutes;

    std::ifstream failas(read);
    if (!failas)
    {
        throw std::exception();
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

    for (auto eil : eilutes) {
        std::stringstream s(eil);
        Studentas tempas;
        float sum, vid;
        s >> tempas.vardas_ >> tempas.pavarde_;
        int k;
        while (s >> k)
        {
            tempas.nd_.push_back(k);
        }

        tempas.egz_ = tempas.nd_.back();
        tempas.nd_.pop_back();
        sum = std::accumulate(tempas.nd_.begin(), tempas.nd_.end(), 0);
        vid = sum / tempas.nd_.size();
        tempas.gal_vid_ = 0.4 * vid + 0.6 * tempas.egz_;
        grupe_vec_.push_back(tempas);

    }
}

void Studentas::padalijimas3_(vector<Studentas>& vec)
{
    std::partition(vec.begin(), vec.end(), pred_);

    vector<Studentas>::iterator it = std::partition_point(vec.begin(), vec.end(), pred_);
    for (it; it != vec.end(); it++)
    {
        vargsiukai_v_.push_back(*it);
    }
    vec.erase(std::partition_point(vec.begin(), vec.end(), pred_), vec.end());
}

bool Studentas::pred_(const Studentas& st)
{
    return st.gal_vid_ >= 5;
}

void  Studentas::isvedimas_(vector<Studentas>& vec, string pav)
{
    std::ofstream failas;
    failas.open(pav);
    failas << std::setw(20) << std::left << "Vardas" << std::setw(20) << std::left << "Pavarde" << std::setw(20) << std::left << "Galutinis balas" << "\n";
    for (auto p : vec) {

        failas << std::setw(20) << std::left << p.vardas_ << std::setw(20) << std::left << p.pavarde_ << std::setw(20) << std::left << p.gal_vid_ << "\n";
    }
    failas.close();
}

bool operator==(const Studentas& a, const Studentas& b)
{
    return a.pavarde_ == b.pavarde_;
}

std::ostream& operator<<(std::ostream& out, const Studentas& a)
{
    out << std::setw(20) << std::left << a.vardas_ << std::setw(20) << std::left << a.pavarde_ << std::setw(20) << std::left << std::setprecision(3) << a.gal_vid_ << endl;
    return out;
}