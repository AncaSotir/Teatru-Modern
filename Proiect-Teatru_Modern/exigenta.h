#ifndef EXIGENTA_H_INCLUDED
#define EXIGENTA_H_INCLUDED

class spectacol;

class exigenta
{
    friend class spectacol;
    string tip;
    string gen; // sa nu fie o anumita combinatie de tip "tipul" si gen "genul"
    int durata_maxima; // contine si pauze!!!
    bool fara_animale_periculoase; // true daca nu doreste sa vada niciun animal viu periculos
    int numar_maxim_spectatori;
public:
    exigenta ();
    exigenta (const exigenta& other);
    ~exigenta ();
    exigenta operator= (const exigenta& other);
    bool operator== (const exigenta& other) const;
    bool operator!= (const exigenta& other) const;
    friend istream& operator>> (istream& in, exigenta& object);
    friend ostream& operator<< (ostream& out, const exigenta& object);
};

#include "exigenta.cpp"

#endif // EXIGENTA_H_INCLUDED
