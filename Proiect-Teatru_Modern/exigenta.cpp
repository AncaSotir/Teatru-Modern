
exigenta::exigenta()=default;

exigenta::exigenta(const exigenta& other)
{
    tip=other.tip;
    gen=other.gen;
    durata_maxima=other.durata_maxima;
    numar_maxim_spectatori=other.numar_maxim_spectatori;
    fara_animale_periculoase=other.fara_animale_periculoase;
}

exigenta::~exigenta()=default;

exigenta exigenta::operator= (const exigenta& other)
{
    tip=other.tip;
    gen=other.gen;
    durata_maxima=other.durata_maxima;
    numar_maxim_spectatori=other.numar_maxim_spectatori;
    fara_animale_periculoase=other.fara_animale_periculoase;
    return *this;
}

bool exigenta::operator==(const exigenta& other) const
{
    if(tip!=other.tip)
        return false;
    if(gen!=other.gen)
        return false;
    if(durata_maxima!=other.durata_maxima)
        return false;
    if(numar_maxim_spectatori!=other.numar_maxim_spectatori)
        return false;
    if(fara_animale_periculoase!=other.fara_animale_periculoase)
        return false;
    return true;
}

bool exigenta::operator!=(const exigenta& other) const
{
    if(*this==other)
        return false;
    return true;
}

istream& operator>> (istream& in, exigenta& object)
{
    bool tastatura=false;
    string raspuns;
    int raspuns_int;
    if(&in==&cin)
        tastatura=true;
    if(tastatura)
        cout<<"\nIntroduceti o combinatie tip+gen pe care nu o doriti? (da/nu) \n";
    in>>raspuns;
    if(raspuns!="da" && raspuns!="nu")
        throw "citire necorespunzatoare";
    if(raspuns=="da")
    {
        if(tastatura)
            cout<<"\nTip? (teatru/opera/circ)\n";
        in>>raspuns;
        if(raspuns!="teatru" && raspuns!="opera"&& raspuns!="circ")
            throw "citire necorespunzatoare";
        object.tip=raspuns;
        if(raspuns=="circ")
            object.gen="comedie";
        else
        {
            if(tastatura)
                cout<<"\nGen? (comedie/romanta/tragedie/drama)\n";
            in>>raspuns;
            if(raspuns!="comedie" &&raspuns!="romanta"&&raspuns!="tragedie"&&raspuns!="drama")
                throw "citire necorespunzatoare";
            object.gen=raspuns;
        }
    }
    if(tastatura)
        cout<<"\nIntroduceti o durata maxima acceptata (pauze inclusiv)? (da/nu) \n";
    in>>raspuns;
    if(raspuns!="da" && raspuns!="nu")
        throw "citire necorespunzatoare";
    if(raspuns=="da")
    {
        if(tastatura)
            cout<<"\nMinute?\n";
        in>>raspuns_int;
        if(raspuns_int<0)
            throw "citire necorespunzatoare";
        object.durata_maxima=raspuns_int;
    }
    else
        object.durata_maxima=INT_MAX;
    if(tastatura)
        cout<<"\nIntroduceti un numar maxim de spectatori in sala? (da/nu)\n";
    in>>raspuns;
    if(raspuns!="da" && raspuns!="nu")
        throw "citire necorespunzatoare";
    if(raspuns=="da")
    {
        if(tastatura)
            cout<<"\nNumar spectatori?\n";
        in>>raspuns_int;
        if(raspuns_int<0)
            throw "citire necorespunzatoare";
        object.numar_maxim_spectatori=raspuns_int;
    }
    else
        object.numar_maxim_spectatori=INT_MAX;
    if(tastatura)
        cout<<"\nDoriti ca spectacolul sa NU faca uz de animale vii periculoase? (da/nu)\n";
    in>>raspuns;
    if(raspuns!="da" && raspuns!="nu")
        throw "citire necorespunzatoare";
    if(raspuns=="da")
        object.fara_animale_periculoase=true;
    else
        object.fara_animale_periculoase=false;
    return in;
}

ostream& operator<< (ostream& out, const exigenta& object)
{
    out<<"Combinatie nedorita: "<<object.tip<<'+'<<object.gen<<'\n';
    out<<"Spectacolul sa nu dureze mai mult de "<<object.durata_maxima<<" minute.\n";
    out<<"Sa nu fie mai mult de "<<object.numar_maxim_spectatori<<" locuri ocupate in sala.\n";
    if(object.fara_animale_periculoase)
        out<<"Sa nu fie folosite animale vii periculoase.\n";
    return out;
}
