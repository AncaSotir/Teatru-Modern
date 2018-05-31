#ifndef SPECTACOL_H_INCLUDED
#define SPECTACOL_H_INCLUDED

#include "prezentare.h"
#include "tip.h"
#include "gen.h"
#include "client.h"

class spectacol
{
    string nume;
    tip* tip_spectacol;
    gen gen_spectacol;
    bool adults_only;
    vector <prezentare> prezentari;
public:
    spectacol ();
    spectacol (const spectacol& other);
    ~spectacol ();
    spectacol operator= (const spectacol& other);
    bool operator== (const spectacol& other) const;
    bool operator!= (const spectacol& other) const;
    int get_numar_prezentari () const;
    bool potrivire_exigente(const client& object);
    pofta potrivire_pofte (const client& object);
    int push_client (const client& object); //returneaza numarul prezentarii la care poate merge clientul
    prezentare& operator[] (int poz);
    int nr_prezentari () const;
    friend istream& operator>> (istream& in, spectacol& object);
    friend ostream& operator<< (ostream& out, const spectacol& object);
};

#include "spectacol.cpp"

#endif // SPECTACOL_H_INCLUDED
