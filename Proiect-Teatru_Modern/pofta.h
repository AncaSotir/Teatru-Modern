#ifndef POFTA_H_INCLUDED
#define POFTA_H_INCLUDED
#include <string>

using namespace std;

class spectacol;

class pofta
{
    friend class spectacol;
    string tip;
    string gen;
    int durata_minima;
    bool durata_minima_cuprinde_pauze;
    string animal_circ;
    bool teatru_interactiv;
    string voce_opera;
public:
    pofta ();
    pofta (const pofta& other);
    ~pofta ();
    pofta operator= (const pofta& other);
    bool operator== (const pofta& other) const;
    bool operator!= (const pofta& other) const;
    friend istream& operator>> (istream& in, pofta& object);
    friend ostream& operator<< (ostream& out, const pofta& object);
};

#include "pofta.cpp"

#endif // POFTA_H_INCLUDED
