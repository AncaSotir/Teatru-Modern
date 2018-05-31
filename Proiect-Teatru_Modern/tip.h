#ifndef TIP_H_INCLUDED
#define TIP_H_INCLUDED

using namespace std;

class tip
{
protected:
    int numar_acte;
    enum tipuri {implicit=0,teatru,opera,circ};
    tipuri nume_tip;
    bool pentru_adulti;
public:
    tip ();
    tip (int nr_acte,string nume);
    tip (const tip& other);
    virtual istream& citire (istream& in) =0;
    virtual ostream& afisare (ostream& out) const =0;
    virtual string get_tip () const =0;
    virtual bool get_pentru_adulti () const =0;
    virtual int get_durata () const =0;
    virtual bool get_teatru_interactiv () const {};
    virtual bool get_circ_animale_periculoase () const {};
    virtual ~tip () {}
    friend istream& operator>> (istream& in, tip& object);
    friend ostream& operator<< (ostream& out, const tip& object);
};

class teatru: public tip
{
    ///are un singur act
    ///unele sunt interactive => pe langa durata fixa, se adauga 1min/adult si 2min/copil

    int durata;
    bool interactiv;
public:
    teatru ();
    teatru (const teatru& other);
    ~teatru ();
    teatru operator= (const teatru& other);
    bool operator== (const teatru& other) const;
    bool operator!= (const teatru& other) const;
    int get_durata () const;
    bool get_teatru_interactiv () const;
    string get_tip () const;
    bool get_pentru_adulti () const;
    istream& citire (istream& in);
    ostream& afisare (ostream& out) const;
};

class solist
{
    string nume;
    enum voci {implicit=0,tenor,bariton,bas};
    voci voce;
public:
    solist ();
    solist (const solist& other);
    ~solist();
    solist operator= (const solist& other);
    bool operator== (const solist& other) const;
    bool operator!= (const solist& other) const;
    void set_voce(string vocea);
    friend istream& operator>> (istream& in, solist& object);
    friend ostream& operator<< (ostream& out, const solist& object);
};

class opera: public tip
{
    ///are un solist principal
    ///poate avea intre 2 si 7 acte
    ///fiecare act are  specificata durata lui
    ///intre acte se ia pauza fixa, specifica operei

    solist solist_principal;
    int* durata_act;
    int durata_pauza;
public:
    opera ();
    opera (const opera& other);
    ~opera ();
    opera operator= (const opera& other);
    bool operator== (const opera& other) const;
    bool operator!= (const opera& other) const;
    int get_durata () const;
    string get_tip () const;
    bool get_pentru_adulti () const;
    istream& citire (istream& in);
    ostream& afisare (ostream& out) const;
};

class act_circ
{
    friend class circ;
    int durata;
    bool pentru_adulti;
    string animal;
public:
    act_circ ();
    act_circ (const act_circ& other);
    ~act_circ ();
    act_circ operator= (const act_circ& other);
    bool operator== (const act_circ& other) const;
    bool operator!= (const act_circ& other) const;
    bool animal_periculos () const;
    string get_animal () const;
    friend istream& operator>> (istream& in, act_circ& object);
    friend ostream& operator<< (ostream& out, const act_circ& object);
};

class circ: public tip
{
    ///comedie
    ///nu se ia pauza intre acte (numere)
    ///unele numere sunt doar pt adulti => tot spectacolul e doar pt adulti

    act_circ* acte;
public:
    circ ();
    circ (const circ& other);
    ~circ ();
    circ operator= (const circ& other);
    bool operator== (const circ& other) const;
    bool operator!= (const circ& other) const;
    void adult();
    string get_tip () const;
    int get_durata () const;
    bool get_circ_animale_periculoase () const;
    bool get_pentru_adulti () const;
    istream& citire (istream& in);
    ostream& afisare (ostream& out) const;
};

#include "tip.cpp"

#endif // TIP_H_INCLUDED
