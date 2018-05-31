#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <vector>
#include <string>
#include "pofta.h"
#include "exigenta.h"

class spectacol;

class client
{
    friend class spectacol;
    string nume;
    int varsta;
    vector<pofta> pofte;
    vector<exigenta> exigente;
public:
    client ();
    client (const client& other);
    ~client ();
    client operator= (const client& other);
    bool operator== (const client& other) const;
    bool operator!= (const client& other) const;
    void pop_pofta (const pofta& object);
    int get_varsta () const;
    int nr_pofte () const;
    friend istream& operator>> (istream& in, client& object);
    friend ostream& operator<< (ostream& out, const client& object);
};

#include "client.cpp"

#endif // CLIENT_H_INCLUDED
