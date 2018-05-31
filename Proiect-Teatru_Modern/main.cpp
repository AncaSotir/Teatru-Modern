#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

#include "spectacol.h"

using namespace std;

int nr_s,nr_c;
vector <spectacol> s;
vector <client> c;

void initializare()
{
    ifstream f("spectacole.txt");
    f>>nr_s;
    s.resize(nr_s);
    for(int i=0; i<nr_s; ++i)
        f>>s[i];
    f.close();
    f.open("clienti.txt");
    f>>nr_c;
    for(int i=0; i<nr_c; ++i)
    {
        client curent;
        f>>curent;
        c.push_back(curent);
        for(int j=0; j<nr_s; ++j)
            if(s[j].potrivire_exigente(curent))
                s[j].push_client(curent);
    }
}


int main()
{
    initializare();
    ofstream g("spectacole_dupa_initializare.txt");
    for(int i=0;i<nr_s;++i)
        g<<s[i];

    string raspuns;

    cout<<"Doriti sa alegeti un spectacol? (da/nu) \n";
    cin>>raspuns;
    if(raspuns!="da"&&raspuns!="nu")
        throw "citire necorespunzatoare";
    while(raspuns=="da")
    {
        vector <spectacol> potrivite;
        client curent;
        cin>>curent;
        spectacol recomandare;
        for(int i=0; i<s.size(); ++i)
        {
            if(s[i].potrivire_exigente(curent))
                potrivite.push_back(s[i]);
        }
        if(potrivite.size()==0)
        {
            cout<<"\n\nNe pare rau, nu avem recomandari pentru dumneavoastra.\n\n";
            return 0;
        }
        if(curent.nr_pofte()==0)
            recomandare=potrivite[0];
        else
        {
            pofta nula;
            for(int i=0;i<potrivite.size();++i)
                {
                    pofta temp=potrivite[i].potrivire_pofte(curent);
                    if(temp!=nula)
                        {
                            recomandare=potrivite[i];
                            curent.pop_pofta(temp);
                        }
                }
        }
        spectacol nul;
        if(recomandare==nul)
        {
            cout<<"\n\nNe pare rau, nu avem recomandari pentru dumneavoastra.\n\n";
            return 0;
        }
        cout<<"\n\nVa recomandam:\n\n";
        if(recomandare!=nul) cout<<recomandare;

        int poz=recomandare.push_client(curent);
        if(poz==-1)
            cout<<"Din pacate, nu mai sunt locuri libere la acest spectacol.\n\n";
        else
        {
            cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout<<"Exista locuri libere la urmatoarea prezentare:\n\n\n";
            cout<<recomandare[poz]<<"\n\n";
            cout<<"Va multumim!\n\n";
        }
        c.push_back(curent);
        cout<<"Mai doriti sa alegeti un spectacol? (da/nu)\n";
        cin>>raspuns;
    }
return 0;
}
