#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include "ksiazki.h"
#include <stdlib.h>
using namespace std;

void premieraksiazki::zaladuj()
{

   cout<<"Podaj nazwe ksiazki/premiery (Slowa oddziel:_): ";
   cin>>nazwa;
   cout<<endl;

   cout<<"Podaj dzien premiery: ";
   cin>>dzien;
   cout<<endl;


   cout<<"Podaj miesiac premiery: ";
   cin>>miesiac;
   cout<<endl;


   cout<<"Podaj rok premiery: ";
   cin>>rok;
   cout<<endl;

}


void premieraksiazki::ZapiszDoPliku()
{

            fstream text;
            text.open("premieryksiazek.txt", ios::out | ios::app);
            text <<" Nazwa: "<< nazwa<<endl;
            text <<" Data: "<< dzien <<"."<<endl;
            text<<miesiac<<"."<<endl;
            text<<rok<<endl;
            text.close();
}





