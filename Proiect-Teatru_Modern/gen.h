
#ifndef GEN_H_INCLUDED
#define GEN_H_INCLUDED

#include <string>

class gen
{
    enum genuri {implicit=0,comedie,romanta,tragedie,drama};
    genuri nume_gen;
public:
    gen ();
    gen (string nume);
    gen (const gen& other);
    ~gen ();
    gen operator= (const gen& other);
    bool operator== (const gen& other) const;
    bool operator!= (const gen& other) const;
    void set_gen (string nume);
    string get_gen () const;
    friend istream& operator>> (istream& in, gen& object);
    friend ostream& operator<< (ostream& out, const gen& object);
};

#include "gen.cpp"

#endif // GEN_H_INCLUDED
