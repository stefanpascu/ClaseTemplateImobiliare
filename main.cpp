#include <iostream>
#include <set>
#include <vector>
#include <iterator>

using namespace std;

const int PRET_PER_M2 = 40;
const int PRET_PER_M2_CURTE = 30;

class Locuinta {
protected:
    static int contor;
    int id;
    string numeProprietar;
    int suprafataUtila;
    double discount;

public:
    Locuinta(string numeProprietar = "", int suprafataUtila = 0, double discount = 0.0) {
        contor++;
        id = contor;
        this->numeProprietar = numeProprietar;
        this->suprafataUtila = suprafataUtila;
        if (discount < 0 || discount > 10) {
            try {
                throw 11;
            }
        }
        this->discount = discount;
        catch(int ex) {
            if(ex == 11){
                cout<<"Discount-ul are o valoare invalida.\n";
            }
        }
    }

    double calcChirie();

    friend bool operator==(Locuinta &x1, Locuinta &x2) {
        return x1.id == x2.id;
    };
    friend bool operator<(Locuinta &x1, Locuinta &x2) {
        return x1.id < x2.id;
    }
    friend ostream &operator<<(ostream &out, Locuinta& g) {
        out<<"Locuinta: ";
        out<<"id="<<g.id<<", ";
        out<<"numeProprietar="<<g.numeProprietar<<", ";
        out<<endl;
        return out;
    };
};

int Locuinta::contor = 0;

class Apartament : public Locuinta {
private:
    int etaj;

public:
    Apartament(string numeProprietar = "", int suprafataUtila = 0, double discount = 0.0, int etaj = 0) :
        Locuinta(numeProprietar, suprafataUtila, discount) {
            this->etaj = etaj;
        }

    double calcChirie() {
        double pret = PRET_PER_M2 * suprafataUtila;
        pret = pret * (100 - discount) / 100;
        return pret;
    }

};

class Casa : public Locuinta {
private:
    int suprafataCurte;
    int nrEtaje;
    vector<int> suprafataPerEtaj;

public:

    Casa(string numeProprietar = "", int suprafataUtila = 0, double discount = 0.0, int suprafataCurte = 0, int nrEtaje = 0, vector<int> suprafataPerEtaj = vector<int>()) :
        Locuinta(numeProprietar, suprafataUtila, discount) {
            this->suprafataCurte = suprafataCurte;
            this->nrEtaje = nrEtaje;
            this->suprafataPerEtaj = suprafataPerEtaj;
        }

    double calcChirie() {
        double pret = PRET_PER_M2 * suprafataUtila;
        pret = pret * (100 - discount) / 100;
        pret = pret + PRET_PER_M2_CURTE * suprafataCurte;
        return pret;
    }

    friend ostream &operator<<(ostream &out, Casa& g) {
        out<<"Casa: ";
        out<<"id="<<g.id<<", ";
        out<<"numeProprietar="<<g.numeProprietar<<", ";
        return out;
    };
    friend bool operator<(Casa &x1, Casa &x2) {cout<<"!!";
        return x1.id < x2.id;
    }
};

template<class T>
class Gestiune {
private:
    set<T*> locuinte;
    void adauga(T x) {
        locuinte.insert(x);
    }
public:

    set<T*> getLocuinte() {
        return locuinte;
    }

    friend Gestiune& operator+=(Gestiune& g, T x) {
        T* ptr = &x;
        g.locuinte.insert(ptr);
        return g;
    }
    friend ostream &operator<<(ostream &out, Gestiune& g) {
        typename set<T*>::iterator it;
        for(it = g.locuinte.begin(); it != g.locuinte.end(); it++) {
            out << *it << endl;
        }
        return out;
    };
};

int main()
{
    Gestiune<Casa> g = Gestiune<Casa>();
    Casa c = Casa();
    g += c;

    cout<<g;
    return 0;
}
