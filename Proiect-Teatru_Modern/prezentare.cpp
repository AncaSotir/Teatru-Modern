
///================================================= CLASS DATA

void data::verifica_data(int& zi, int& luna, int&an)
{
    if(an<2018)
        an=2018;
    if(an>2019)
        an=2019;
    if(luna<1)
        luna=1;
    if(luna>12)
        luna=12;
    if(zi<1)
    {
        zi=1;
        return;
    }
    if(zi<=28)
        return;
    switch(luna)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if(zi>31)
            zi=31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if(zi>30)
            zi=30;
        break;
    case 2:
        if(zi>28)
            zi=28;
        break;
    }
}

data::data ()
{
    zi=luna=1;
    an=2018;
}

data::data (int z,int l, int a)
{
    int temp_z,temp_l,temp_a;
    temp_z=z;
    temp_l=l;
    temp_a=a;
    verifica_data(temp_z,temp_l,temp_a);
    zi=temp_z;
    luna=temp_l;
    an=temp_a;
}

data::data (const data& other)
{
    zi=other.zi;
    luna=other.luna;
    an=other.an;
}

data::~data() = default;

data data::operator= (const data& other)
{
    zi=other.zi;
    luna=other.luna;
    an=other.an;
    return *this;
}

bool data::operator== (const data& other) const
{
    if(zi!=other.zi)
        return false;
    if(luna!=other.luna)
        return false;
    if(an!=other.an)
        return false;
    return true;
}

bool data::operator!= (const data& other) const
{
    if(*this==other)
        return false;
    return true;
}

bool data::operator< (const data& other) const
{
    if(an<other.an)
        return true;
    if(an>other.an)
        return false;
    if(luna<other.luna)
        return true;
    if(luna>other.luna)
        return false;
    if(zi<other.zi)
        return true;
    return false;
}

istream& operator>> (istream& in, data& object)
{
    int z,l,a;
    in>>z>>l>>a;
    object.verifica_data(z,l,a);
    object.zi=z;
    object.luna=l;
    object.an=a;
    return in;
}

ostream& operator<< (ostream& out, const data& object)
{
    if(object.zi<10)
        out<<'0';
    out<<object.zi<<'.';
    if(object.luna<10)
        out<<'0';
    out<<object.luna<<'.'<<object.an<<'\n';
    return out;
}

///================================================= CLASS PREZENTARE

prezentare::prezentare ()=default;

prezentare::prezentare (int zi, int luna, int an, int nr_locuri): data_spectacol(zi,luna,an)
{
    numar_locuri=nr_locuri;
    numar_locuri_rezervate=0;
    numar_adulti=0;
    numar_copii=0;
}

prezentare::prezentare (const prezentare& other): data_spectacol(other.data_spectacol)
{
    numar_locuri=other.numar_locuri;
    numar_locuri_rezervate=other.numar_locuri_rezervate;
    numar_adulti=other.numar_adulti;
    numar_copii=other.numar_copii;
}

prezentare::~prezentare () = default;

prezentare prezentare::operator=(const prezentare& other)
{
    data_spectacol=other.data_spectacol;
    numar_locuri=other.numar_locuri;
    numar_locuri_rezervate=other.numar_locuri_rezervate;
    numar_adulti=other.numar_adulti;
    numar_copii=other.numar_copii;
    return *this;
}

bool prezentare::operator==(const prezentare& other) const
{
    if(data_spectacol!=other.data_spectacol)
        return false;
    if(numar_locuri!=other.numar_locuri)
        return false;
    if(numar_locuri_rezervate!=other.numar_locuri_rezervate)
        return false;
    if(numar_adulti!=other.numar_adulti)
        return false;
    if(numar_copii!=other.numar_copii)
        return false;
    return true;
}

bool prezentare::operator!=(const prezentare& other) const
{
    if(*this==other)
        return false;
    return true;
}

bool prezentare::operator<(const prezentare& other) const
{
    if(data_spectacol<other.data_spectacol)
        return true;
    return false;
}

int prezentare::durata_aditionala_teatru_interactiv() const
{
    int minute=0;
    minute=minute+numar_adulti+numar_copii+numar_copii;
    return minute;
}

bool prezentare::push_client(const client& object)
{
    if(numar_locuri_rezervate>=numar_locuri)
        return false;
    numar_locuri_rezervate++;
    if(object.get_varsta()<16)
        numar_copii++;
    else
        numar_adulti++;
    return true;
}

int prezentare::get_numar_locuri_rezervate () const
{
    return numar_locuri_rezervate;
}

int prezentare::get_numar_locuri () const
{
    return numar_locuri;
}

istream& operator>> (istream& in, prezentare& object)
{
    in>>object.data_spectacol>>object.numar_locuri;
    return in;
}

ostream& operator<< (ostream& out, const prezentare& object)
{
    out<<"Data prezentarii: "<<object.data_spectacol;
    out<<"Numar locuri: "<<object.numar_locuri<<'\n';
    out<<"Pana acum:\n";
    out<<"\t- "<<object.numar_locuri_rezervate<<" locuri rezervate (";
    out<<object.numar_adulti<<" adulti si "<<object.numar_copii<<" copii)\n\n";
    return out;
}
