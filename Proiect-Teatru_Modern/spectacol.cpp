#include <string>

spectacol::spectacol (): gen_spectacol()
{
    tip_spectacol=NULL;
    adults_only=false;
}

spectacol::spectacol (const spectacol& other): gen_spectacol(other.gen_spectacol)
{
    nume=other.nume;
    if(other.tip_spectacol->get_tip()=="teatru")
        tip_spectacol=new teatru(*((teatru*)other.tip_spectacol));
    else if (other.tip_spectacol->get_tip()=="opera")
        tip_spectacol=new opera(*((opera*)other.tip_spectacol));
    else if (other.tip_spectacol->get_tip()=="circ")
        tip_spectacol=new circ(*((circ*)other.tip_spectacol));
    adults_only=other.adults_only;
    prezentari=other.prezentari;
}

spectacol::~spectacol()
{
    if(tip_spectacol) delete tip_spectacol;
}

spectacol spectacol::operator= (const spectacol& other)
{
    nume=other.nume;
    if(tip_spectacol) delete tip_spectacol;
    if(other.tip_spectacol->get_tip()=="teatru")
        tip_spectacol=new teatru(*((teatru*)other.tip_spectacol));
    else if (other.tip_spectacol->get_tip()=="opera")
        tip_spectacol=new opera(*((opera*)other.tip_spectacol));
    else if (other.tip_spectacol->get_tip()=="circ")
        tip_spectacol=new circ(*((circ*)other.tip_spectacol));
    gen_spectacol=other.gen_spectacol;
    adults_only=other.adults_only;
    prezentari=other.prezentari;
    return *this;
}

bool spectacol::operator== (const spectacol& other) const
{
    if(nume!=other.nume)
        return false;
    if(tip_spectacol!=NULL&&other.tip_spectacol==NULL)
        return false;
    if(tip_spectacol==NULL&&other.tip_spectacol!=NULL)
        return false;
    if(tip_spectacol!=NULL&&other.tip_spectacol!=NULL)
        if(tip_spectacol->get_tip()!=other.tip_spectacol->get_tip())
            return false;
    if(gen_spectacol!=other.gen_spectacol)
        return false;
    if(adults_only!=other.adults_only)
        return false;
    if(prezentari!=other.prezentari)
        return false;
    return true;
}

bool spectacol::operator!= (const spectacol& other) const
{
    if(*this==other)
        return false;
    return true;
}

int spectacol::get_numar_prezentari () const
{
    return prezentari.size();
}

bool spectacol::potrivire_exigente(const client& object)
{
    if(object.varsta<16 && adults_only)
        return false;
    if(object.exigente.size()==0)
        return true;
    for(int i=0; i<object.exigente.size(); ++i)
    {
        if(object.exigente[i].tip==tip_spectacol->get_tip())
            if(object.exigente[i].gen==gen_spectacol.get_gen())
                return false;
        if(tip_spectacol->get_durata()>object.exigente[i].durata_maxima)
            return false;
        if(tip_spectacol->get_circ_animale_periculoase() && object.exigente[i].fara_animale_periculoase)
            return false;
        for(int i=0; i<nr_prezentari(); ++i)
            if((*this)[i].get_numar_locuri_rezervate() <= object.exigente[i].numar_maxim_spectatori)
                return true;
    }
    return false;
}

pofta spectacol::potrivire_pofte (const client& object)
{
    pofta temp;
    if(object.pofte.size()==0)
        return temp;
    for(int i=0; i<object.pofte.size(); ++i)
    {
        if(tip_spectacol!=NULL)
        if(object.pofte[i].tip!=tip_spectacol->get_tip())
            continue;
        if(object.pofte[i].gen!=gen_spectacol.get_gen())
            continue;
        if(object.pofte[i].durata_minima>tip_spectacol->get_durata())
            continue;
        temp=object.pofte[i];
        break;
    }
    return temp;
}

int spectacol::push_client(const client& object)
{
    for(int i=0; i<nr_prezentari(); ++i)
        if((*this)[i].push_client(object))
            return i;
    return -1;
}

prezentare& spectacol::operator[] (int poz)
{
    return prezentari[poz];
}

int spectacol::nr_prezentari () const
{
    return prezentari.size();
}

istream& operator>> (istream& in, spectacol& object)
{
    in.get();
    std::getline(in,object.nume);
    if(object.tip_spectacol!=NULL)
        delete object.tip_spectacol;
    string indicator;
    in>>indicator;
    if(indicator=="teatru")
    {
        object.tip_spectacol = new teatru;
        in>>(*(object.tip_spectacol));
        in>>object.gen_spectacol;
    }
    else if(indicator=="opera")
    {
        object.tip_spectacol = new opera;
        in>>(*(object.tip_spectacol));
        in>>object.gen_spectacol;
    }
    else if(indicator=="circ")
    {
        object.tip_spectacol = new circ;
        in>>(*(object.tip_spectacol));
        object.gen_spectacol.set_gen("comedie");
    }
    object.adults_only=object.tip_spectacol->get_pentru_adulti();
    int numar_prezentari;
    in>>numar_prezentari;
    object.prezentari.resize(numar_prezentari);
    for(int i=0; i<object.nr_prezentari(); ++i)
        in>>object.prezentari[i];
    return in;
}

ostream& operator<< (ostream& out, const spectacol& object)
{
    out<<"\n--------------------------------------------------------\n";
    out<<object.nume<<"\n\n";
    out<<"Tipul spectacolului: ";
    if(object.tip_spectacol->get_tip()=="circ")
        out<<"Circ\n\n";
    else if(object.tip_spectacol->get_tip()=="teatru")
    {
        out<<"Teatru ";
        if(object.tip_spectacol->get_teatru_interactiv())
            out<<"interactiv\n";
        else
            out<<'\n';
    }
    else if(object.tip_spectacol->get_tip()=="opera")
        out<<"Opera\n\n";
    out<<object.gen_spectacol<<'\n';
    if(object.tip_spectacol->get_pentru_adulti())
        out<<"Acest spectacol este pentru adulti.\n\n";
    out<<(*(object.tip_spectacol));
    out<<"Durata fixa a spectacolului: "<<object.tip_spectacol->get_durata()<<" minute\n\n";
    out<<"Spectacolul va rula ";
    if(object.nr_prezentari()==1)
        out<<"o data:\n\n";
    else
        out<<"de "<<object.nr_prezentari()<<" ori:\n\n";

    for(int i=0; i<object.nr_prezentari(); ++i)
    {
        out<<object.prezentari[i];
        if(object.tip_spectacol->get_tip()=="teatru")
        {
            if(object.tip_spectacol->get_teatru_interactiv())
                out<<"Durata aditionala pentru teatru interactiv: "<<object.prezentari[i].durata_aditionala_teatru_interactiv()<<" minute\n\n";
        }
    }
    return out;
}
