#include <string>

client::client()=default;

client::client(const client& other)
{
    nume=other.nume;
    varsta=other.varsta;
    pofte.resize(other.pofte.size());
    for(int i=0; i<pofte.size(); ++i)
        pofte[i]=other.pofte[i];
    exigente.resize(other.exigente.size());
    for(int i=0; i<exigente.size(); ++i)
        exigente[i]=other.exigente[i];
}

client::~client()=default;

client client::operator= (const client& other)
{
    nume=other.nume;
    varsta=other.varsta;
    pofte.resize(other.pofte.size());
    for(int i=0; i<pofte.size(); ++i)
        pofte[i]=other.pofte[i];
    exigente.resize(other.exigente.size());
    for(int i=0; i<exigente.size(); ++i)
        exigente[i]=other.exigente[i];
    return *this;
}

bool client::operator== (const client& other) const
{
    if(nume!=other.nume)
        return false;
    if(varsta!=other.varsta)
        return false;
    if(pofte.size()!=other.pofte.size())
        return false;
    if(exigente.size()!=other.exigente.size())
        return false;
    for(int i=0; i<pofte.size(); ++i)
        if(pofte[i]!=other.pofte[i])
            return false;
    for(int i=0; i<exigente.size(); ++i)
        if(exigente[i]!=other.exigente[i])
            return false;
    return true;
}

bool client::operator!=(const client& other) const
{
    if(*this==other)
        return false;
    return true;
}

void client::pop_pofta(const pofta& object)
{
    int poz=-1;
    for(int i=0; i<pofte.size(); ++i)
        if(pofte[i]==object)
            poz=i;
    if(poz==-1)
        return;
    for(int i=poz; i<pofte.size()-1; ++i)
        pofte[i]=pofte[i+1];
    int nr=pofte.size();
    pofte.resize(nr-1);
}

int client::get_varsta () const
{
    return varsta;
}

istream& operator>> (istream& in, client& object)
{
    string raspuns;
    int raspuns_int;
    bool tastatura=false;
    if(&cin==&in)
        tastatura=true;
    if(tastatura)
        cout<<"\nVa rog sa raspundeti la urmatoarele intrebari.\n";
    if(tastatura)
        cout<<"\nNume?\n";
    in.get();
    std::getline(in,object.nume);
    if(tastatura)
        cout<<"\nVarsta?\n";
    in>>raspuns_int;
    if(raspuns_int<=0 || raspuns_int>=200)
        throw "citire necorespunzatoare";
    object.varsta=raspuns_int;
    if(tastatura)
        cout<<"\nDoriti sa introduceti o pofta? (da/nu) \n";
    in>>raspuns;
    while(raspuns=="da")
    {
        pofta temp;
        in>>temp;
        object.pofte.push_back(temp);
        if(tastatura)
            cout<<"\nDoriti sa introduceti o alta pofta? (da/nu) \n";
        in>>raspuns;
    }
    if(tastatura)
        cout<<"\nDoriti sa introduceti o exigenta? (da/nu) \n";
    in>>raspuns;
    while(raspuns=="da")
    {
        exigenta temp;
        in>>temp;
        object.exigente.push_back(temp);
        if(tastatura)
            cout<<"\nDoriti sa introduceti o alta exigenta? (da/nu) \n";
        in>>raspuns;
    }
    return in;
}

int client::nr_pofte () const
{
    return pofte.size();
}

ostream& operator<< (ostream& out, const client& object)
{
    out<<object.nume<<", "<<object.varsta<<" ani\n";
    if(object.pofte.size())
        out<<"Pofte:\n";
    for(int i=0; i<object.pofte.size(); ++i)
    {
        out<<i+1<<":\n";
        out<<object.pofte[i]<<'\n';
    }
    if(object.exigente.size())
        out<<"Exigente:\n";
    for(int i=0; i<object.exigente.size(); ++i)
    {
        out<<i+1<<":\n";
        out<<object.exigente[i]<<'\n';
    }
    return out;
}
