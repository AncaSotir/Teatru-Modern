#include <string>

///=========================================== CLASS TIP

tip::tip()=default;

tip::tip(int nr_acte, string nume)
{
    numar_acte=nr_acte;
    if(nume=="teatru")
        nume_tip=teatru;
    if(nume=="opera")
        nume_tip=opera;
    if(nume=="circ")
        nume_tip=circ;
    else
        nume_tip=implicit;
}

tip::tip(const tip& other)
{
    numar_acte=other.numar_acte;
    nume_tip=other.nume_tip;
}

string tip::get_tip () const
{
    switch(nume_tip)
    {
    case 1:
        return "teatru";
        break;
    case 2:
        return "opera";
        break;
    case 3:
        return "circ";
        break;
    case 0:
        break;
    }
    return "implicit";
}

istream& operator>> (istream& in, tip& object)
{
    return object.citire(in);
}

ostream& operator<< (ostream& out, const tip& object)
{
    return object.afisare(out);
}

///=========================================== CLASS TEATRU

teatru::teatru(): tip(1,"teatru")
{
    durata=0;
    interactiv=false;
    pentru_adulti=false;
}

teatru::teatru(const teatru& other): tip(other)
{
    durata=other.durata;
    interactiv=other.interactiv;
    pentru_adulti=other.pentru_adulti;
}

teatru::~teatru() = default;

teatru teatru::operator= (const teatru& other)
{
    numar_acte=other.numar_acte;
    nume_tip=other.nume_tip;
    durata=other.durata;
    interactiv=other.interactiv;
    pentru_adulti=other.pentru_adulti;
    return *this;
}

bool teatru::operator== (const teatru& other) const
{
    if(durata!=other.durata)
        return false;
    if(interactiv!=other.interactiv)
        return false;
    if(pentru_adulti!=other.pentru_adulti)
        return false;
    return true;
}

bool teatru::operator!= (const teatru& other) const
{
    if(*this==other)
        return false;
    return true;
}

bool teatru::get_teatru_interactiv () const
{
    return interactiv;
}

int teatru::get_durata () const
{
    return durata;
}

string teatru::get_tip() const
{
    return "teatru";
}

bool teatru::get_pentru_adulti() const
{
    return pentru_adulti;
}

istream& teatru::citire(istream& in)
{
    in>>durata;
    in>>interactiv;
    in>>pentru_adulti;
    return in;
}

ostream& teatru::afisare(ostream& out) const
{
    out<<"Numar acte: 1 ("<<durata<<" minute)\n";
    return out;
}

///=========================================== CLASS OPERA (+SOLIST)

//=========================================== CLASS SOLIST

solist:: solist()=default;

solist:: solist(const solist& other)
{
    nume=other.nume;
    voce=other.voce;
}

solist::~solist()=default;

void solist::set_voce(string vocea)
{
    if(vocea=="tenor")
        voce=tenor;
    else if(vocea=="bariton")
        voce=bariton;
    else if(vocea=="bas")
        voce=bas;
    else
        voce=implicit;
}

solist solist::operator= (const solist& other)
{
    nume=other.nume;
    voce=other.voce;
    return *this;
}

bool solist::operator== (const solist& other) const
{
    if(voce!=other.voce)
        return false;
    if(nume!=other.nume)
        return false;
    return true;
}

bool solist::operator!= (const solist& other) const
{
    if(*this==other)
        return false;
    return true;
}

istream& operator>> (istream& in, solist& object)
{
    in.get();
    std::getline(in,object.nume);
    string vocea;
    in>>vocea;
    object.set_voce(vocea);
    return in;
}

ostream& operator<< (ostream& out, const solist& object)
{
    out<<"Solist principal: ";
    out<<object.nume<<' ';
    switch(object.voce)
    {
    case 0:
        out<<"\n";
        break;
    case 1:
        out<<"(Tenor)\n";
        break;
    case 2:
        out<<"(Bariton)\n";
        break;
    case 3:
        out<<"(Bas)\n";
        break;
    }
    return out;
}

//=========================================== CLASS OPERA

opera::opera (): tip(0,"opera")
{
    durata_act=NULL;
    durata_pauza=0;
    pentru_adulti=false;
}

opera::opera (const opera& other): tip(other.numar_acte,"opera")
{
    solist_principal=other.solist_principal;
    durata_pauza=other.durata_pauza;
    if(other.numar_acte==0)
        return;
    durata_act=new int[numar_acte];
    for(int i=0; i<numar_acte; ++i)
        durata_act[i]=other.durata_act[i];
    pentru_adulti=other.pentru_adulti;
}

opera::~opera()
{
    if(durata_act) delete[] durata_act;
}

opera opera::operator= (const opera& other)
{
    numar_acte=other.numar_acte;
    solist_principal=other.solist_principal;
    durata_pauza=other.durata_pauza;
    if(durata_act) delete[] durata_act;
    if(numar_acte==0)
        return *this;
    durata_act=new int[numar_acte];
    for(int i=0; i<numar_acte; ++i)
        durata_act[i]=other.durata_act[i];
    pentru_adulti=other.pentru_adulti;
    return *this;
}

bool opera::operator== (const opera& other) const
{
    if(numar_acte!=other.numar_acte)
        return false;
    if(solist_principal!=other.solist_principal)
        return false;
    if(durata_pauza!=other.durata_pauza)
        return false;
    if(pentru_adulti!=other.pentru_adulti)
        return false;
    for(int i=0; i<numar_acte; ++i)
        if(durata_act[i]!=durata_act[i])
            return false;
    return true;
}

bool opera::operator!= (const opera& other) const
{
    if(*this==other)
        return false;
    return true;
}

int opera::get_durata() const
{
    int temp=durata_pauza;
    for(int i=0; i<numar_acte; ++i)
        temp+=durata_act[i];
    return temp;
}

string opera::get_tip() const
{
    return "opera";
}

bool opera::get_pentru_adulti() const
{
    return pentru_adulti;
}

istream& opera::citire (istream& in)
{
    in>>solist_principal;
    in>>numar_acte;
    if(durata_act) delete[] durata_act;
    durata_act=new int[numar_acte];
    for(int i=0; i<numar_acte; ++i)
        in>>durata_act[i];
    in>>durata_pauza;
    in>>pentru_adulti;
    return in;
}

ostream& opera::afisare (ostream& out) const
{
    out<<solist_principal<<'\n';
    out<<"Numar acte: "<<numar_acte<<"\n\n";
    for(int i=0; i<numar_acte; ++i)
        out<<"\tActul "<<i+1<<": "<<durata_act[i]<<" minute\n\n";
    out<<"Pauza intre acte: "<<durata_pauza<<" minute\n";
    return out;
}

///=========================================== CLASS CIRC (+ACT_CIRC)

//=========================================== CLASS ACT_CIRC

act_circ::act_circ ()=default;

act_circ::act_circ (const act_circ& other)
{
    durata=other.durata;
    pentru_adulti=other.pentru_adulti;
    animal=other.animal;
}

act_circ::~act_circ ()=default;

act_circ act_circ::operator= (const act_circ& other)
{
    durata=other.durata;
    pentru_adulti=other.pentru_adulti;
    animal=other.animal;
    return *this;
}

bool act_circ::operator== (const act_circ& other) const
{
    if(durata!=other.durata)
        return false;
    if(pentru_adulti!=other.pentru_adulti)
        return false;
    if(animal!=other.animal)
        return false;
    return true;
}

bool act_circ::operator!= (const act_circ& other) const
{
    if(*this==other)
        return false;
    return true;
}

bool act_circ::animal_periculos() const
{
    if(animal=="leu")
        return true;
    if(animal=="tigru")
        return true;
    if(animal=="leopard")
        return true;
    if(animal=="elefant")
        return true;
    if(animal=="rinocer")
        return true;
    if(animal=="gorila")
        return true;
    if(animal=="urs")
        return true;
    if(animal=="sarpe")
        return true;
    if(animal=="crocodil")
        return true;
    return false;
}

string act_circ::get_animal () const
{
    return animal;
}

istream& operator>> (istream& in, act_circ& object)
{
    in>>object.durata;
    in>>object.pentru_adulti;
    bool indicator_animal;
    in>>indicator_animal;
    if(indicator_animal)
    {
        string animalul;
        in>>animalul;
        object.animal=animalul;
    }
    else
    {
        string temp_default;
        object.animal=temp_default;
    }
    return in;
}

ostream& operator<< (ostream& out, const act_circ& object)
{
    if(object.pentru_adulti)
        out<<"\t\t- este pentru adulti\n";
    if(object.animal.length())
    {
        out<<"\t\t- face uz de animale vii (";
        out<<object.animal;
        out<<")\n";
    }
    out<<"\t\t- dureaza "<<object.durata<<" minute\n";
    return out;
}

//=========================================== CLASS CIRC

circ::circ (): tip(0,"circ")
{
    acte=NULL;
}

circ::circ (const circ& other): tip(other.numar_acte,"circ")
{
    if(other.numar_acte==0)
        return;
    acte = new act_circ [other.numar_acte];
    for(int i=0; i<other.numar_acte; ++i)
        acte[i]=other.acte[i];
}

circ::~circ ()
{
    if(acte) delete[] acte;
}

circ circ::operator= (const circ& other)
{
    numar_acte=other.numar_acte;
    if(acte) delete[] acte;
    if(other.numar_acte==0)
        return *this;
    acte = new act_circ [other.numar_acte];
    for(int i=0; i<other.numar_acte; ++i)
        acte[i]=other.acte[i];
    return *this;
}

bool circ::operator== (const circ& other) const
{
    if(numar_acte!=other.numar_acte)
        return false;
    for(int i=0; i<numar_acte; ++i)
        if(acte[i]!=other.acte[i])
            return false;
    return true;
}

bool circ::operator!= (const circ& other) const
{
    if(*this==other)
        return false;
    return true;
}

void circ::adult ()
{
    for(int i=0; i<numar_acte; ++i)
        if(acte[i].pentru_adulti)
        {
            pentru_adulti=true;
            break;
        }
}

int circ::get_durata() const
{
    int temp=0;
    for(int i=0; i<numar_acte; ++i)
        temp+=acte[i].durata;
    return temp;
}

string circ::get_tip() const
{
    return "circ";
}

bool circ::get_circ_animale_periculoase() const
{
    for(int i=0; i<numar_acte; ++i)
        if(acte[i].animal_periculos())
            return true;
    return false;
}

bool circ::get_pentru_adulti() const
{
    return pentru_adulti;
}

istream& circ::citire (istream& in)
{
    in>>numar_acte;
    if(acte) delete[] acte;
    acte = new act_circ[numar_acte];
    for(int i=0; i<numar_acte; ++i)
        in>>acte[i];
    adult();
    return in;
}

ostream& circ::afisare (ostream& out) const
{
    out<<"Numar acte: "<<numar_acte<<'\n';
    for(int i=0; i<numar_acte; ++i)
    {
        out<<"\tActul "<<i+1<<":\n";
        out<<acte[i];
    }
    out<<'\n';
    return out;
}
