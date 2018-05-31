#include <string>

using namespace std;

pofta::pofta()=default;

pofta::pofta(const pofta& other)
{
    tip=other.tip;
    gen=other.gen;
    durata_minima=other.durata_minima;
    durata_minima_cuprinde_pauze=other.durata_minima_cuprinde_pauze;
    animal_circ=other.animal_circ;
    teatru_interactiv=other.teatru_interactiv;
    voce_opera=other.voce_opera;
}

pofta::~pofta()=default;

pofta pofta::operator= (const pofta& other)
{
    tip=other.tip;
    gen=other.gen;
    durata_minima=other.durata_minima;
    durata_minima_cuprinde_pauze=other.durata_minima_cuprinde_pauze;
    animal_circ=other.animal_circ;
    teatru_interactiv=other.teatru_interactiv;
    voce_opera=other.voce_opera;
    return *this;
}

bool pofta::operator== (const pofta& other) const
{
    if(tip!=other.tip)
        return false;
    if(gen!=other.gen)
        return false;
    if(durata_minima!=other.durata_minima)
        return false;
    if(durata_minima_cuprinde_pauze!=other.durata_minima_cuprinde_pauze)
        return false;
    if(animal_circ!=other.animal_circ)
        return false;
    if(teatru_interactiv!=other.teatru_interactiv)
        return false;
    if(voce_opera!=other.voce_opera)
        return false;
    return true;
}

bool pofta::operator!= (const pofta& other) const
{
    if(*this==other)
        return false;
    return true;
}

istream& operator>> (istream& in, pofta& object)
{
    string raspuns;
    int raspuns_int;
    bool tastatura=false;
    if(&in==&cin)
        tastatura=true;
    if(tastatura)
        cout<<"\nTip dorit? (teatru/opera/circ)\n";
    in>>raspuns;
    if(raspuns!="teatru"&&raspuns!="opera"&& raspuns!="circ")
        throw "citire necorespunzatoare";
    object.tip=raspuns;
    if(object.tip=="circ")
        object.gen="comedie";
    else
    {
        if(tastatura)
            cout<<"\nGen dorit? (comedie/romanta/tragedie/drama)\n";
        in>>raspuns;
        if(raspuns!="comedie"&&raspuns!="romanta"&&raspuns!="tragedie"&&raspuns!="drama")
            throw "citire necorespunzatoare";
        object.gen=raspuns;
    }
    if(tastatura)
        cout<<"\nIntroduceti o durata minima? (da/nu)\n";
    in>>raspuns;
    if(raspuns!="da"&&raspuns!="nu")
        throw "citire necorespunzatoare";
    if(raspuns=="da")
    {
        if(tastatura)
            cout<<"\nDurata minima dorita? (minute)\n";
        in>>raspuns_int;
        if(raspuns_int<0||raspuns_int>240)
            throw "citire necorespunzatoare";
        object.durata_minima=raspuns_int;
        if(object.tip!="opera")
            object.durata_minima_cuprinde_pauze=false;
        else
        {
            if(tastatura)
                cout<<"\nDurata introdusa cuprinde pauze? (da/nu)\n";
            in>>raspuns;
            if(raspuns!="da"&&raspuns!="nu")
                throw "citire necorespunzatoare";
            if(raspuns=="da")
                object.durata_minima_cuprinde_pauze=true;
            else
                object.durata_minima_cuprinde_pauze=false;
        }
    }
    if(tastatura)
    {
        if(object.tip=="circ")
            cout<<"\nIntroduceti un animal? (da/nu)\n";
        else if(object.tip=="teatru")
            cout<<"\nDoriti teatru interactiv? (da/nu)\n";
        else if(object.tip=="opera")
            cout<<"\nIntroduceti o voce a solistului principal? (tenor/bariton/bas) (da/nu)\n";
    }
    in>>raspuns;
    if(raspuns!="da"&&raspuns!="nu")
        throw "citire necorespunzatoare";
    if(raspuns=="nu" && object.tip=="teatru")
        object.teatru_interactiv=false;
    if(raspuns=="da")
    {
        if(object.tip=="circ")
        {
            if(tastatura)
                cout<<"\nAnimal dorit?\n";
            in>>object.animal_circ;
        }
        else if(object.tip=="teatru")
        {
            object.teatru_interactiv=true;
        }
        else if(object.tip=="opera")
        {
            if(tastatura)
                cout<<"\nVocea solistului?\n";
            in>>object.voce_opera;
        }
    }
    return in;
}

ostream& operator<< (ostream& out, const pofta& object)
{
    out<<"Tipul dorit: "<<object.tip<<' ';
    if(object.tip=="teatru"&&object.teatru_interactiv)
        out<<"interactiv\n";
    else
        out<<'\n';
    out<<"Genul dorit: "<<object.gen<<'\n';
    out<<"Durata minima dorita: "<<object.durata_minima<<' ';
    if(object.durata_minima_cuprinde_pauze)
        out<<"(cu pauze)\n";
    else
        out<<"(fara pauze)\n";
    string s_null;
    if(object.tip=="opera"&& object.voce_opera!=s_null)
        out<<"Vocea solistului: "<<object.voce_opera<<'\n';
    else if(object.tip=="circ"&& object.animal_circ!=s_null)
        out<<"Animal dorit: "<<object.animal_circ<<'\n';
    return out;
}
