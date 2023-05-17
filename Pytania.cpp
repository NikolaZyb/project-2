#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Pytania.h"
using namespace std;

void Pytania::odczytaj ()
{
    fstream plik;
    plik.open("quizksiazkowy.txt",ios::in);
    int numerlinii=(numerpytania-1)*6+1;
    int aktualnynumer=1;
    string linia;
    while(getline(plik,linia))
    {
        if (aktualnynumer==numerlinii)tresc=linia;
        if (aktualnynumer==numerlinii+1)A=linia;
        if (aktualnynumer==numerlinii+2)B=linia;
        if (aktualnynumer==numerlinii+3)C=linia;
        if (aktualnynumer==numerlinii+4)D=linia;
        if (aktualnynumer==numerlinii+5)poprawnaodpowiedz=linia;
        aktualnynumer++;
    }
    plik.close();
}

void Pytania::zadajpytanie()
{
    cout<<endl<<tresc<<endl;
    cout<<A<<endl;
    cout<<B<<endl;
    cout<<C<<endl;
    cout<<D<<endl;
    cout<<"              "<<endl;
    cout<<"Twoja odpowiedz: ";
    cin>>odpowiedz;
}
void Pytania::sprawdzenieodp()
{
    if(odpowiedz==poprawnaodpowiedz)
    {
        punkt=1;
    } else punkt=0;
}


void Quiz2::odczytaj()
{
    fstream plik;
    plik.open("quizksiazkowy2.txt",ios::in);
    int numerlinii=(numerpytania-1)*6+1;
    int aktualnynumer=1;
    string linia;
    while(getline(plik,linia))
    {
        if (aktualnynumer==numerlinii)tresc=linia;
        if (aktualnynumer==numerlinii+1)A=linia;
        if (aktualnynumer==numerlinii+2)B=linia;
        if (aktualnynumer==numerlinii+3)C=linia;
        if (aktualnynumer==numerlinii+4)D=linia;
        if (aktualnynumer==numerlinii+5)poprawnaodpowiedz=linia;
        aktualnynumer++;
    }
    plik.close();
}

void Quiz2::zadajpytanie()
{
    cout<<endl<<tresc<<endl;
    cout<<A<<endl;
    cout<<B<<endl;
    cout<<C<<endl;
    cout<<D<<endl;
    cout<<"              "<<endl;
    cout<<"Twoja odpowiedz: ";
    cin>>odpowiedz;
}
void Quiz2::sprawdzenieodp()
{
    if(odpowiedz==poprawnaodpowiedz)
    {
        punkt=1;
    } else punkt=0;
}
