gen::gen()=default;

gen::gen (string nume)
{
    if(nume=="comedie")
        nume_gen=comedie;
    else if(nume=="romanta")
        nume_gen=romanta;
    else if(nume=="tragedie")
        nume_gen=tragedie;
    else if(nume=="drama")
        nume_gen=drama;
    else
        nume_gen=implicit;
}

gen::gen (const gen& other)
{
    nume_gen=other.nume_gen;
}

gen::~gen () = default;

gen gen::operator= (const gen& other)
{
    nume_gen=other.nume_gen;
    return *this;
}

bool gen::operator== (const gen& other) const
{
    if(nume_gen!=other.nume_gen)
        return false;
    return true;
}

bool gen::operator!= (const gen& other) const
{
    if(*this==other)
        return false;
    return true;
}

void gen::set_gen (string nume)
{
    if(nume=="comedie")
        nume_gen=comedie;
    else if(nume=="romanta")
        nume_gen=romanta;
    else if(nume=="tragedie")
        nume_gen=tragedie;
    else if(nume=="drama")
        nume_gen=drama;
    else
        nume_gen=implicit;
}

string gen::get_gen () const
{
    switch(nume_gen)
    {
    case 1:
        return "comedie";
    case 2:
        return "romanta";
    case 3:
        return "tragedie";
    case 4:
        return "drama";
    case 0:
        break;
    }
    return "implicit";
}

istream& operator>> (istream& in, gen& object)
{
    string nume;
    in>>nume;
    object.set_gen(nume);
    return in;
}

ostream& operator<< (ostream& out, const gen& object)
{
    out<<"Genul spectacolului: ";
    switch(object.nume_gen)
    {
    case 0:
        out<<"\n";
        break;
    case 1:
        out<<"Comedie\n";
        break;
    case 2:
        out<<"Romanta\n";
        break;
    case 3:
        out<<"Tragedie\n";
        break;
    case 4:
        out<<"Drama\n";
        break;
    }
    return out;
}
