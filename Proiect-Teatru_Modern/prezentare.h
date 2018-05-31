#ifndef PREZENTARE_H_INCLUDED
#define PREZENTARE_H_INCLUDED

#include "client.h"

using namespace std;

class data
{
    int zi,luna,an;
    void verifica_data (int& zi, int& luna, int& an);
public:
    data ();
    data (int zi,int luna,int an);
    data (const data& other);
    ~data ();
    data operator= (const data& other);
    bool operator== (const data& other) const;
    bool operator!= (const data& other) const;
    bool operator< (const data& other) const;
    friend istream& operator>> (istream& in, data& object);
    friend ostream& operator<< (ostream& out, const data& object);
};

class prezentare
{
    data data_spectacol;
    int numar_locuri;
    int numar_locuri_rezervate;
    int numar_adulti;
    int numar_copii;
public:
    prezentare ();
    prezentare (int zi,int luna, int an, int nr_locuri);
    prezentare (const prezentare& other);
    ~prezentare ();
    prezentare operator= (const prezentare& other);
    bool operator== (const prezentare& other) const;
    bool operator!= (const prezentare& other) const;
    bool operator< (const prezentare& other) const;
    int durata_aditionala_teatru_interactiv () const;
    bool push_client (const client& object);
    int get_numar_locuri_rezervate () const;
    int get_numar_locuri () const;
    friend istream& operator>> (istream& in, prezentare& object);
    friend ostream& operator<< (ostream& out, const prezentare& object);
};

#include "prezentare.cpp"

#endif // PREZENTARE_H_INCLUDED
