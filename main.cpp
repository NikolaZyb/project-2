#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <conio.h>
#include <cstdio>
#include "pytania.h"
#include "ksiazki.h"
#include <string>
#include "przeszkoda.h"
#include <vector>
#include <cstring>
using namespace std;
int odswierzanie;
bool wyjscie=false;
bool wAplikacji;
bool zalogowano=false;
bool wyszukaj=false;
bool wGrze=false;
bool powrot=false;
bool powrot2=false;
bool powrot3=false;
bool quiz1=false;
bool quiz2=false;
bool dodaj=false;
bool premiery=false;
bool Szukaj=false;
bool part2=false;
int i;
string login, haslo, login2, haslo2, szukaj;
char znak;

char *tr(char *str)    //umozliwia uzywanie polskich znakow
{
        static char buff[256];
        char cp[]="\245\206\251\210\344\242\230\276\253\244\217\250\235\343\340\227\275\215¹æê³ñóœ¿Ÿ¥ÆÊ£ÑÓŒ¯";
        if(strlen(str)>=sizeof(buff)) return str;
        char *bf=buff;
   while(*str)
   {
        char *pos=strchr(cp+18,*str);
        *(bf++)=pos?*(pos-18):*str;
        ++str;
   }
   *bf=0;
   return buff;
}

void gotoxy(int x, int y)          //ustawia w ktorym miejscu ma sie pojawic dany element
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
class ksiazka
{
  string tytul;
  string autor;
  string gatunek;
  int iloscstron;
  string opis;
  string opis2;
  string opis3;
  string opis4;
  string opis5;
  string opis6;
  string opis7;
  string opis8;
  string opis9;
  string opis10;
  string opis11;
  friend void DodajKsiazke(ksiazka & k);
};
class Gracz
{
public:
    int x;
    int y;
    int zycia;
    char strona;
    bool stracil_zycie;
    int Monety;
};
class skarb
: public Przeszkoda
{
    // int x;
    //int y;
    public:
    bool istnieje;
};
Gracz gracz;
char c;
skarb Skarb[18];


void zaladujPoziom(string nazwapliku)
{
    string trescpliku;
    ifstream otworzplik(nazwapliku.c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);   //Zmienia kolor tekstu
    if(otworzplik.is_open())
    {
        while(! otworzplik.eof())
        {
            getline(otworzplik, trescpliku);
            cout << trescpliku << endl;
        }
    }
}
void Okno(int dlugosc, int wysokosc)
{
    _COORD coord;                                       //COORD Okreœla koordynaty komórki znakowej w buforze ekranu konsoli.
    coord.X = dlugosc;
    coord.Y = wysokosc;

    _SMALL_RECT Rect;                                   //SMALL_RECT Okreœla wspó³rzêdne lewego górnego i prawego dolnego rogu prostok¹ta.
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = wysokosc - 1;
    Rect.Right = dlugosc - 1;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);    //GetStdHandle  Pobiera uchwyt do okreœlonego urz¹dzenia (standardowe wejœcie, standardowe wyjœcie, standardowe wyjœcie b³êdów).
    SetConsoleScreenBufferSize(Handle, coord);          //SetConsoleScreenBufferSize Zmienia rozmiar bufora podanej konsoli.
    SetConsoleWindowInfo(Handle, TRUE, &Rect);          //SetConsoleWindowInfo Ustawia rozmiar i pozycjê okna bufora ekranu konsoli.
}
char kursor()
{
    char c='\0';
    CONSOLE_SCREEN_BUFFER_INFO con;                     //CONSOLE_SCREEN_BUFFER_INFO Zawiera informacje o buforze ekranu konsoli.
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);      //GetStdHandle  Pobiera uchwyt do okreœlonego urz¹dzenia (standardowe wejœcie, standardowe wyjœcie, standardowe wyjœcie b³êdów).
    if (hcon != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(hcon,&con))      //GetConsoleScreenBufferInfo Pobiera informacje o okreœlonym buforze ekranu konsoli.
    {
            DWORD read = 0;
            if (!ReadConsoleOutputCharacterA(hcon,&c,1,con.dwCursorPosition,&read) || read != 1)    //ReadConsoleOutputCharacter  Kopiuje znaki z kolejnych komórek bufora ekranu konsoli, zaczynaj¹c od okreœlonej lokalizacji.
            c='\0';
    }
    return c;
}
char wyznaczmiejsce(int x,int y)
{
    gotoxy(x,y);
    char kur = kursor();
    return kur;
}


void tworzSkarbZycie(int lp,int x,int y)
{
    Skarb[lp].istnieje=true;
    Skarb[lp].x=x;
    Skarb[lp].y=y;
    gotoxy(x,y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout<<"Z";
}
void tworzSkarbMonety(int lp,int x,int y)
{
    Skarb[lp].istnieje=true;
    Skarb[lp].x=x;
    Skarb[lp].y=y;
    gotoxy(x,y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
    cout<<"$";
}
void zaladujPoziomObiekty(int nrPoziomu)
{
      Przeszkoda p;
      p.stworz();

        if (Skarb[1].istnieje==true)
        {
            tworzSkarbZycie(1,1,14);
        }
        if (Skarb[2].istnieje==true)
        {
            tworzSkarbZycie(2,85,28);
        }
        if (Skarb[3].istnieje==true)
        {
            tworzSkarbZycie(3,16,1);
        }
        if (Skarb[4].istnieje==true)
        {
            tworzSkarbMonety(4,14,10);
        }
        if (Skarb[5].istnieje==true)
        {
            tworzSkarbMonety(5,49,6);
        }
        if (Skarb[6].istnieje==true)
        {
            tworzSkarbMonety(6,16,10);
        }
        if (Skarb[7].istnieje==true)
        {
            tworzSkarbMonety(7,62,3);
        }
        if (Skarb[8].istnieje==true)
        {
            tworzSkarbMonety(8,72,7);
        }
        if (Skarb[9].istnieje==true)
        {
            tworzSkarbMonety(9,1,31);
        }
        if (Skarb[10].istnieje==true)
        {
            tworzSkarbMonety(10,23,35);
        }
        if (Skarb[11].istnieje==true)
        {
            tworzSkarbMonety(11,1,28);
        }
        if (Skarb[12].istnieje==true)
        {
            tworzSkarbMonety(12,85,20);
        }
         if (Skarb[13].istnieje==true)
        {
            tworzSkarbMonety(13,1,22);
        }
        if (Skarb[14].istnieje==true)
        {
            tworzSkarbMonety(14,33,14);
        }
        if (Skarb[15].istnieje==true)
        {
            tworzSkarbMonety(15,85,10);
        }
        if (Skarb[16].istnieje==true)
        {
            tworzSkarbMonety(16,85,1);
        }
        if (Skarb[17].istnieje==true)
        {
            tworzSkarbMonety(17,51,1);
        }
        if (Skarb[18].istnieje==true)
        {
            tworzSkarbMonety(18,51,10);
        }
}
void funkcje()
{
        if ((c=='w')|| (c=='s') || (c=='a') || (c=='d'))
        {
            if (c=='w')
            {
                 gracz.strona='w';
                 gotoxy(gracz.x,gracz.y);
                 cout<<" ";
                 if ((wyznaczmiejsce(gracz.x,gracz.y-1)!= '#'))
                 {
                     gracz.y-=1;
                 }
            }
        if (c=='s')
        {
            gracz.strona='s';
            gotoxy(gracz.x,gracz.y);
            cout<<" ";
            if ((wyznaczmiejsce(gracz.x,gracz.y+1)!= '#'))
            {
                   gracz.y+=1;
            }
        }
        if (c=='a')
        {
            gracz.strona='a';
            gotoxy(gracz.x,gracz.y);
            cout<<" ";
            if ((wyznaczmiejsce(gracz.x-1,gracz.y)!= '#') )
            {
                   gracz.x-=1;
            }
        }
        if (c=='d')
        {
            gracz.strona='d';
            gotoxy(gracz.x,gracz.y);
            cout<<" ";
            if ((wyznaczmiejsce(gracz.x+1,gracz.y)!= '#'))
            {
                    gracz.x+=1;
            }
        }
        }
        if (wyznaczmiejsce(gracz.x,gracz.y)== 'Z')
        {
            gracz.zycia+=1;
            for(int i=0; i<=20; i++)
            {
                if ((gracz.x==Skarb[i].x) && (gracz.y==Skarb[i].y))
                {
                    Skarb[i].istnieje=false;
                }
            }
        }
        if (wyznaczmiejsce(gracz.x,gracz.y)== '$')
        {
            gracz.Monety+=1;
            for(int i=0; i<=20; i++)
            {
                if ((gracz.x==Skarb[i].x) && (gracz.y==Skarb[i].y))
                {
                    Skarb[i].istnieje=false;
                }
            }
        }
        if (wyznaczmiejsce(gracz.x,gracz.y)== 'O')
        {
            gracz.zycia--;
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        gotoxy(gracz.x,gracz.y);
        if (gracz.strona=='w')
        {
            cout<<char(30);
        }
        if (gracz.strona=='s')
        {
            cout<<char(31);
        }
        if (gracz.strona=='a')
        {
            cout<<char(17);
        }
        if (gracz.strona=='d')
        {
            cout<<char(16);
        }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
    gotoxy(90,3);
    cout<<"Lives: "<<gracz.zycia;
    gotoxy(90,5);
    cout<<"Monety: "<<gracz.Monety;
    gotoxy(11,40);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout<<"XY: ( "<<gracz.x<<", "<<gracz.y<<" )";
}

void poruszenieGracz()
{
    c='0';
    if (_kbhit()==1)
    {
        c=getch();
    }
}
void restartPoziomu()
{
    c='0';
    system("CLS");

    zaladujPoziom("level_1.txt");
    zaladujPoziomObiekty(1);
    gotoxy(gracz.x,gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout<<char(24);
}
void rozpocznijGre()
{
    gracz.x=2;
    gracz.y=35;
    gracz.zycia=3;
    gracz.Monety=0;
    for (int i=0; i<=20;i++)
    {
        Skarb[i].istnieje=true;
    }
    zaladujPoziom("level_1.txt");
    zaladujPoziomObiekty(1);
    gotoxy(gracz.x,gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout<<char(24);
}

void quizksiazkowy()
{
    char c='0';
    wyjscie=false;
    system("CLS");
    while ((wAplikacji==true) && (wyjscie==false))
    {
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
          cout<<endl<<endl<<endl<<endl<<endl;
          cout<<tr("U¿ywaj W i S by wybraæ")<<endl;
          gotoxy(20,10);
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
          cout<<"WYBIERZ QUIZ";
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
          gotoxy(40,19);
          cout<<tr("QUIZ 1: Wiedza ogólna");
          gotoxy(40,21);
          cout<<tr("QUIZ 2: Ksi¹¿ki YA fantasy");
          gotoxy(40,23);
          cout<<tr("Wróæ");
          int wybrane=0;
          while (c!=char(13))
          {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                gotoxy(35,19+wybrane);
                cout<<"->";

                gotoxy(0,0);
                c=getch();
                gotoxy(35,19+wybrane);
                cout<<"  ";

                if (c=='s')
                {
                      if (wybrane<3)
                      {
                           wybrane+=2;
                      }
                }
                if (c=='w')
                {
                      if (wybrane>0)
                      {
                           wybrane-=2;
                      }
                }
          }
          if (wybrane==0)
          {
              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
              system("cls");
              gotoxy(36,10);
              cout<<tr("Jest to quiz wiedzy ogólnej o ksi¹¿kach.");
              gotoxy(36,12);
              cout<<tr("Przed tob¹ 10 pytañ. Za ka¿de dostaniesz 1 punkt.");
              gotoxy(36,14);
              cout<<tr("Punkty bêd¹ póŸniej wyœwietlane na twoim profilu.");
              gotoxy(36,16);
              cout<<"Powodzenia!";
              Sleep(4500);
              system("cls");
              Sleep(500);
              quiz1=true;
              if (quiz1==true)
              {
                  Pytania p[10];
                  int suma=0;
                  for(int i=0; i<=9;i++)
                  {
                      p[i].numerpytania=i+1;
                      p[i].odczytaj();
                      p[i].zadajpytanie();
                      p[i].sprawdzenieodp();
                      suma+=p[i].punkt;
                  }
                  system("cls");
                  gotoxy(49,20);
                  cout<<"Koniec! Twoje punkty: "<<suma;
                  fstream text;
                  text.open("SUMA.txt", ios::out);
                  text << suma;
                  text.close();
                  Sleep(1000);
                  system("CLS");
                  powrot2=true;
              }
              powrot2=true;
              break;
          }
          if (wybrane==2)
          {
              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
              system("cls");
              gotoxy(36,10);
              cout<<tr("Jest to quiz wiedzy o ksi¹¿kach YA fantasy.");
              gotoxy(36,12);
              cout<<tr("Przed tob¹ 10 pytañ. Za ka¿de dostaniesz 1 punkt.");
              gotoxy(36,14);
              cout<<tr("Punkty bêd¹ póŸniej wyœwietlane na twoim profilu.");
              gotoxy(36,16);
              cout<<"Powodzenia!";
              Sleep(4500);
              system("cls");
              Sleep(500);
              system("cls");
              quiz2=true;
              if (quiz2==true)
              {
                  Quiz2 p[10];
                  int suma=0;
                  for(int i=0; i<=9;i++)
                  {
                       p[i].numerpytania=i+1;
                       p[i].odczytaj();
                       p[i].zadajpytanie();
                       p[i].sprawdzenieodp();
                       suma+=p[i].punkt;
                  }
                  system("cls");
                  gotoxy(49,20);
                  cout<<"Koniec! Twoje punkty: "<<suma;
                  fstream text;
                  text.open("SUMA2.txt", ios::out);
                  text << suma;
                  text.close();
                  Sleep(1000);
                  system("CLS");
                  powrot2=true;
              }
              powrot2=true;
              break;
          }
          if (wybrane==4)
          {
             system("CLS");
             powrot2=true;
             break;
          }
          wybrane=4;
          c=' ';
          system("CLS");
          powrot2=true;
          break;
    }
}

void rejestracja()
{
    system("CLS");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<tr("U¿ywaj W i S by wybraæ")<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
    gotoxy(49.25,12);

    cout<<"VIRTUAL LIBRARY";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    gotoxy(51,17);
    cout<<"REJESTRACJA";
    gotoxy(51,19);
    cout << "Podaj login: ";
    gotoxy(50,21);
    cout<<tr(" Podaj has³o: ");
    ifstream plik;
    plik.open( "ZarejestrowaniUzytkownicy.txt" );
    string temp;
    string SPR[1];
    int i=0;
    while( getline( plik, temp ) )
    {
        SPR[i]=temp;
        i++;
    }
    if (i==2)
    {
        system("cls");
        gotoxy(25,20);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
        cout<<tr("!!! Zarejestrowany jest ju¿ u¿ytkownik! Jak zarejestrujesz nowe dane poprzednie znikn¹ !!!");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
        gotoxy(25,22);
        cout<<"WPISZ OK BY ZMIENIC DANE LUB BACK BY WROCIC";
        string uwaga;
        gotoxy(77,22);
        cin>>uwaga;
        if (uwaga=="OK")
        {
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
            cout<<endl<<endl<<endl<<endl<<endl;
            cout<<tr("U¿ywaj W i S by wybraæ")<<endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
            gotoxy(49.25,12);

            cout<<"VIRTUAL LIBRARY";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            gotoxy(51,17);
            cout<<"REJESTRACJA";
            gotoxy(51,19);
            cout << "Podaj login: ";
            gotoxy(50,21);
            cout<<tr(" Podaj has³o: ");
            gotoxy(64,19);
            cin>>login2;
            gotoxy(64,21);
            cin>>haslo2;
            unsigned char znak;
            int kod;
            do
            {
            znak = getch();
            kod = static_cast < int >( znak );
            if( kod == 13 )
            {
                fstream text;
                text.open("ZarejestrowaniUzytkownicy.txt", ios::out);
                text << login2 << endl;
                text << haslo2 << endl;
                text.close();
            }
            system("cls");
            gotoxy(40,20);
            cout<<"Zarejestrowano!"<<endl;
            gotoxy(39,22);
            cout<<tr("  Naciœnij ESC by wróciæ do menu by siê zalogowaæ");

            }
            while( kod != 27 );
            {
            wAplikacji=false;
            wyjscie=false;
            }
        }
        else
        {
            wAplikacji=false;
            wyjscie=false;
        }
    }
    else{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    gotoxy(64,19);
    cin>>login2;
    gotoxy(64,21);
    cin>>haslo2;
    unsigned char znak;
    int kod;
    do
    {
        znak = getch();
        kod = static_cast < int >( znak );
        if( kod == 13 )
        {
            fstream text;
            text.open("ZarejestrowaniUzytkownicy.txt", ios::out);
            text << login2 << endl;
            text << haslo2 << endl;
            text.close();
        }
        system("cls");
        gotoxy(40,20);
        cout<<"Zarejestrowano!"<<endl;
        gotoxy(39,22);
        cout<<tr("  Naciœnij ESC by wróciæ do menu by siê zalogowaæ");

    }
    while( kod != 27 );
    {
        wAplikacji=false;
        wyjscie=false;
    }
    }
}
    void menu()
{
    char c='0';
    wyjscie=false;
    system("CLS");
    while ((wAplikacji==false) && (wyjscie==false))
    {
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
          cout<<endl<<endl<<endl<<endl<<endl;
          gotoxy(0,0);
          cout<<tr("U¿ywaj W i S by wybraæ")<<endl;

          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
          gotoxy(72.5,12);

          cout<<"VIRTUAL LIBRARY";

          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
          gotoxy(75,19);
          cout<<"Logowanie ";
          gotoxy(74.5,21);
          cout<<"Rejestracja ";
          gotoxy(75,23);
          cout<<tr(" Wyjœcie ");
          int wybrane=2;
          while (c!=char(13))
          {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                gotoxy(70,19+wybrane);
                cout<<"->";

                gotoxy(0,0);
                c=getch();
                gotoxy(70,19+wybrane);
                cout<<"  ";

                if (c=='s')
                {
                      if (wybrane<4)
                      {
                          wybrane+=2;
                      }
                }
                if (c=='w')
                {
                      if (wybrane>0)
                      {
                          wybrane-=2;
                      }
                }
          }
          if (wybrane==0)
          {
                wAplikacji=true;
                wyszukaj=true;
          }
          if (wybrane==2)
          {
                rejestracja();
          }
          if (wybrane==4)
          {
                wAplikacji=false;
                wyjscie=true;
          }
          wybrane=2;
          c=' ';
          system("CLS");
    }
}
string ListaU[2];
void wyszukajksiazke();
void DodajDoUlubionych()
{
        char c='0';
        int wybrane=0;
        wAplikacji=true;
        while(wAplikacji==true)
        {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        gotoxy(55,22);
        cout<<"Dodaj do ulubionych";
        gotoxy(80,22);
        cout<<tr("Wróæ");
        while (c!=char(13))
          {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                gotoxy(50+wybrane,22);
                cout<<"->";

                gotoxy(0,0);
                c=getch();
                gotoxy(50+wybrane,22);
                cout<<"  ";

                if (c=='d')
                {
                      if (wybrane<25)
                      {
                          wybrane+=25;
                      }
                }
                if (c=='a')
                {
                      if (wybrane>0)
                      {
                          wybrane-=25;
                      }
                }
          }
          if (wybrane==0)
          {
                fstream text;
                text.open("Ulubione.txt",ios::in | ios::out | ios::app);
                string spraw;
                string LiN;
                LiN=ListaU[1]+ListaU[2];
               while( getline(text,spraw))
               {
                if (spraw==LiN)
                {
                    system("cls");
                    gotoxy(70,21);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
                    cout<<"DANA KSIAZKA ZOSTALA JUZ DODANA";
                    Sleep(1000);
                    wAplikacji=false;
                    powrot=true;
                    break;
                }else
                 {
                text<<ListaU[1]<<ListaU[2]<<endl;
                text.close();
                system("cls");
                gotoxy(74.5,21);
                cout<<"DODANO";
                Sleep(1000);
                powrot=true;
                break;
                 }
               }

          }
          if (wybrane==25)
          {
                system("cls");
                Szukaj=true;
                break;
          }
          wybrane=25;
          c=' ';
          system("CLS");
          Szukaj=true;
          break;
    }
}

void DodajDoPrzeczytanych()
{
        char c='0';
        int wybrane=0;
        wAplikacji=true;
        while(wAplikacji==true)
        {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        gotoxy(55,22);
        cout<<"Dodaj do przeczytanych";
        gotoxy(95,22);
        cout<<tr("Wróæ");
        while (c!=char(13))
          {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                gotoxy(45+wybrane,22);
                cout<<"->";

                gotoxy(0,0);
                c=getch();
                gotoxy(45+wybrane,22);
                cout<<"  ";

                if (c=='d')
                {
                      if (wybrane<40)
                      {
                          wybrane+=40;
                      }
                }
                if (c=='a')
                {
                      if (wybrane>0)
                      {
                          wybrane-=40;
                      }
                }
          }
          if (wybrane==0)
          {
                fstream text;
                text.open("PRZ.txt", ios::in );
                string spraww;
                string LiNN;
                LiNN=ListaU[1]+" "+ListaU[2];
                while( getline(text,spraww))
                {
                if (spraww==LiNN)
                {
                    system("cls");
                    gotoxy(70,21);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
                    cout<<"DANA KSIAZKA ZOSTALA JUZ DODANA";
                    Sleep(1000);
                    powrot=true;
                    wAplikacji=false;
                    break;
                }
                else
                 {
                text.close();
                text.open("PRZ.txt",ios::out| ios::app);
                text<<ListaU[1]<<" "<<ListaU[2]<<endl;
                text.close();
                system("cls");
                gotoxy(74.5,21);
                cout<<"DODANO";
                Sleep(1000);
                powrot=true;
                break;
                 }
                }
          }

          if (wybrane==40)
          {
                system("cls");
                Szukaj=true;
                break;
          }
          wybrane=40;
          c=' ';
          system("CLS");
          Szukaj=true;
          break;
    }
}

void Part2()
{
    part2=false;
    int wybrac=0;
    char m='0';
    wAplikacji=true;
    while (wAplikacji==true)
    {
        gotoxy(65,19);
        cout<<tr("Dodaj/usuñ z ulubionych");
        gotoxy(95,19);
        cout<<tr("Dodaj/usuñ z przeczytanych");
        gotoxy(130,19);
        cout<<tr("Wróæ do wyszukania");

        while(m!=char(13))
        {
              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
              gotoxy(58+wybrac,19);
              cout<<"->";

              gotoxy(0,0);
              m=getch();
              gotoxy(58+wybrac,19);
              cout<<"  ";

              if (m=='d')
              {
                 if (wybrac<60)
                 {
                     wybrac+=35;
                 }
              }
              if (m=='a')
              {
                 if (wybrac>0)
                 {
                     wybrac-=35;
                 }
              }
        }
    if (wybrac==0)
    {
       DodajDoUlubionych();
       break;
    }
    if (wybrac==35)
    {
        DodajDoPrzeczytanych();
        break;
    }
    if (wybrac==70)
    {
         system("cls");
         Szukaj=true;
         break;
    }
    wybrac=70;
    system("cls");
    break;
    }
}

void wyszukajksiazke()
{
    char c='0';
    int wybrane=0;
    wyjscie=false;
    Szukaj=false;
    wAplikacji=true;
    system("CLS");
    while ((wAplikacji==true) && (wyjscie==false))
    {
        gotoxy(5,5);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
        cout<<endl<<endl<<endl<<endl<<endl;
        cout<<tr("U¿ywaj W i S by wybraæ")<<endl;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
        gotoxy(45.5,12);

        cout<<"VIRTUAL LIBRARY";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        gotoxy(49,19);
        cout<<"Szukaj "<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
        gotoxy(23.5,14);
        cout<<tr("Przy wyszukiwaniu zamiast spacji u¿yj '_'.Nie u¿ywaj polskich znaków.");
        gotoxy(23.5,16);
        cout<<tr("Pamiêtaj by zapisaæ pierwsz¹ litere tytu³u lub autora wielk¹ liter¹");
        gotoxy(49,21);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        cout<<tr("Wróæ");
        gotoxy(58,19);
        while(c!=char(13))
          {
              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
              gotoxy(46,19+wybrane);
              cout<<"->";

              gotoxy(0,0);
              c=getch();
              gotoxy(46,19+wybrane);
              cout<<"  ";

              if (c=='s')
              {
                 if (wybrane<3)
                 {
                     wybrane+=2;
                 }
              }
              if (c=='w')
              {
                 if (wybrane>0)
                 {
                     wybrane-=2;
                 }
              }
           }
           if (wybrane==0)
           {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                gotoxy(56.5,19);
                cin>>szukaj;
                fstream plik;
                string content;
                plik.open( "ksiazki.txt", ios::in);
                string tytul, autor, gatunek, iloscstron, opis,opis2 , opis3, opis4, opis5, opis6, opis7, opis8, opis9, opis10, opis11, Pustyznak;
                int i=1;
                while(plik >> content)
                {
                        getline(plik,Pustyznak),
                        getline(plik,tytul);
                        getline(plik,autor);
                        getline(plik,gatunek);
                        getline(plik,iloscstron);
                        getline(plik,opis);
                        getline(plik,opis2);
                        getline(plik,opis3);
                        getline(plik,opis4);
                        getline(plik,opis5);
                        getline(plik,opis6);
                        getline(plik,opis7);
                        getline(plik,opis8);
                        getline(plik,opis9);
                        getline(plik,opis10);
                        getline(plik,opis11);
                        if (szukaj==tytul || szukaj==autor)
                        {
                                ListaU[1]=tytul;
                                ListaU[2]=autor;
                                system("cls");
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                                cout<<endl<<endl<<endl<<endl<<endl;
                                cout<<tr("U¿ywaj W i S by wybraæ")<<endl;
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
                                gotoxy(45.5,12);
                                cout<<"VIRTUAL LIBRARY";
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                                gotoxy(49,19);
                                cout<<"Szukaj "<<endl;
                                gotoxy(32,16);
                                cout<<tr("Przy wyszukiwaniu zamiast spacji u¿yj '_'. Nie u¿ywaj polskich znaków");
                                gotoxy(49,21);
                                cout<<tr("Wróæ");
                                gotoxy(10,25);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                                cout<<tr("Tytu³: ")<<tytul<<"    "<<"Autor: "<<autor<<endl;
                                gotoxy(10,27);
                                cout<<"Gatunek: "<<gatunek<<"    "<<tr("Iloœæ stron:")<<iloscstron<<endl;
                                gotoxy(10,29);
                                cout<<"Opis: "<<opis<<endl;
                                gotoxy(10,31);
                                cout<<opis2<<endl;
                                gotoxy(10,32);
                                cout<<opis3<<endl;
                                gotoxy(10,33);
                                cout<<opis4<<endl;
                                gotoxy(10,34);
                                cout<<opis5<<endl;
                                gotoxy(10,35);
                                cout<<opis6<<endl;
                                gotoxy(10,36);
                                cout<<opis7<<endl;
                                gotoxy(10,37);
                                cout<<opis8<<endl;
                                gotoxy(10,38);
                                cout<<opis9<<endl;
                                gotoxy(10,39);
                                cout<<opis10<<endl;
                                gotoxy(10,40);
                                cout<<opis11<<endl;
                                gotoxy(10,41);
                                cout<<"     "<<endl;
                                wAplikacji=false;
                                wyjscie=true;
                                Part2();
                                break;

                        }
                }
                if (szukaj!=tytul && szukaj !=autor)
                {
                        system("cls");
                        gotoxy(74.5,21);
                        cout<<tr("BRAK WYNIKÓW");
                        Sleep(1000);
                        system("cls");
                        Szukaj=true;
                        break;
                }

           }

           if (wybrane==2)
           {
                system("CLS");
                wAplikacji=false;
                zalogowano=false;
                powrot=false;
                powrot=true;
           }

           wybrane=2;
           c=' ';
           system("CLS");
           wAplikacji=false;
           zalogowano=false;
           powrot=false;
           powrot=true;
    }
}
void MojProfil();
void ZmienLogin()
{

            string nowylogin;
            fstream plik;
            plik.open("ZarejestrowaniUzytkownicy.txt",ios::in);
            string temp;
            string liczba[3];
            int li=1;
            while( getline( plik, temp ) )
            {
                liczba[li]=temp;
                li++;
            }
            plik.close();
            ofstream text;
            text.open("ZarejestrowaniUzytkownicy.txt");
            gotoxy(40,14);
            cout<<"       Nowy login: ";
            cin>>nowylogin;
            text<< nowylogin<<endl;
            text << liczba[2]<< endl;
            text.close();
            system("cls");
            gotoxy(74.5,21);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            cout<<"ZMIENIONO LOGIN";
            Sleep(1000);
            MojProfil();
}
void ZmienHaslo()
{

            string nowehaslo;
            fstream plik;
            plik.open("ZarejestrowaniUzytkownicy.txt",ios::in);
            string temp;
            string liczba[3];
            int li=1;
            while( getline( plik, temp ) )
            {
                  liczba[li]=temp;
                  li++;
            }
            plik.close();
            ofstream text;
            text.open("ZarejestrowaniUzytkownicy.txt");
            gotoxy(40,16);
            cout<<tr("       Nowe has³o: ");
            cin>>nowehaslo;
            text<< liczba[1]<<endl;
            text << nowehaslo<< endl;
            text.close();
            system("cls");
            gotoxy(74.5,21);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            cout<<tr("ZMIENIONO HAS£O");
            Sleep(1000);
            MojProfil();

}
void usun()
{
    fstream plik;
    plik.open( "premieryksiazek.txt", ios::in );

    string temp;
    string tablica[100];
    int i=0;
    while( getline( plik, temp ) )
    {
       tablica[i]=temp;
       i++;
    }
    system("cls");
    gotoxy(49,20);
    cout<<tr("Któr¹ z premier chcesz usun¹æ? ");
    int ktora;
    gotoxy(55,20);
    cin>>ktora;
    switch (ktora)
    {
    case 1:

        {
            ofstream text;
            text.open("premieryksiazek.txt", ios::out |ios::trunc);

            if (i>4)
            {
            text<<tablica[4]<<endl<<tablica[5]<<endl<<tablica[6]<<endl<<tablica[7];
            }
            if (i>8)
            {
            text<<tablica[8]<<endl<<tablica[9]<<endl<<tablica[10]<<endl<<tablica[11];
            }
            text.close();
            gotoxy(74.5,21);
            cout<<"GOTOWE";
            Sleep(1000);

            powrot2=true;
            break;
        }
    case 2:

        {
            ofstream text;
            text.open("premieryksiazek.txt", ios::out | ios::trunc);
            text<<tablica[0]<<endl<<tablica[1]<<endl<<tablica[2]<<endl<<tablica[3]<<endl;
            if (i>8)
            {
            text<<tablica[8]<<endl<<tablica[9]<<endl<<tablica[10]<<endl<<tablica[11];
            }
            text.close();
            gotoxy(74.5,21);
            cout<<"GOTOWE";
            Sleep(1000);
            powrot2=true;
            break;
        }
    case 3:
        {
            ofstream text;
            text.open("premieryksiazek.txt", ios::out | ios::trunc);
            text<<tablica[0]<<endl<<tablica[1]<<endl<<tablica[2]<<endl<<tablica[3]<<endl<<tablica[4]<<endl<<tablica[5]<<endl<<tablica[6]<<endl<<tablica[7];
            text.close();
            gotoxy(74.5,21);
            cout<<"GOTOWE";
            Sleep(1000);
            powrot2=true;
            break;
        }

    }

}
void PremieryKsiazek()
{

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<tr("U¿ywaj W i S by wybraæ")<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    gotoxy(20,20);
    cout<<"Dodaj premiere";
    gotoxy(50,20);
    cout<<tr("Usuñ premiere");
    gotoxy(80,20);
    cout<<tr("Wróæ");
    gotoxy(30,10);
    cout<<"Zapisane premiery znajdziesz na swoim profilu";
    int wybrane=0;
          while (c!=char(13))
          {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                gotoxy(12+wybrane,20);
                cout<<"->";

                gotoxy(0,0);
                c=getch();
                gotoxy(12+wybrane,20);
                cout<<"  ";

                if (c=='d')
                {
                      if (wybrane<59)
                      {
                          wybrane+=30;
                      }
                }
                if (c=='a')
                {
                      if (wybrane>0)
                      {
                          wybrane-=30;
                      }
                }
          }
          if (wybrane==0)
          {

                 system("cls");
                 int ile;
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                 premieraksiazki pk[4];

                 cout<<"Ile premier chcesz dodac (max 3)? ";
                 cin>>ile;
                 if (ile>3)
                 {
                     system("cls");
                     gotoxy(49,20);
                     cout<<tr("Maksymalna iloœæ premier to 3!!!!");
                     Sleep(1000);
                     premiery=true;
                 }
                 else
                {
                      for(int i=1; i<=ile;i++)
                      {
                          ifstream plik;
                          plik.open( "premieryksiazek.txt" );
                          int lin=0;
                          string temp;
                          while( getline( plik, temp ) )
                          {
                                lin++;
                          }
                          if(lin==8 && ile==1)
                          {
                                pk[i].zaladuj();
                                pk[i].ZapiszDoPliku();
                                system("cls");
                                gotoxy(74.5,21);
                                cout<<"Zapisano premiere "<<i<<endl;
                                Sleep(1000);
                                powrot2=true;
                          }
                          else if (lin==4 && ile==2 || lin==4 && ile==1)
                          {
                                pk[i].zaladuj();
                                pk[i].ZapiszDoPliku();
                                system("cls");
                                gotoxy(74.5,21);
                                cout<<"Zapisano premiere "<<i<<endl;
                                Sleep(1000);
                                powrot2=true;
                          }
                          else if (lin==8 && ile==3)
                          {
                                system("cls");
                                gotoxy(49,20);
                                cout<<tr("Mo¿esz maksymalnie dodaæ jeszcze jedn¹ premiere");
                                premiery=true;
                                Sleep(1000);
                                break;
                          }
                          else if(lin== 4 && ile==3)
                          {
                                system("cls");
                                gotoxy(49,20);
                                cout<<tr("Mo¿esz maksymalnie dodaæ jeszcze dwie premiery");
                                premiery=true;
                                break;
                          }
                          else if (lin==8 && ile==2 || lin==8 && ile==1)
                          {
                                pk[i].zaladuj();
                                pk[i].ZapiszDoPliku();
                                system("cls");
                                gotoxy(74.5,21);
                                cout<<"Zapisano premiere "<<i<<endl;
                                Sleep(1000);
                                powrot2=true;
                          }
                          else if (lin==12)
                          {
                                gotoxy(74.5,21);
                                cout<<tr("Zapisana jest maksymalna iloœæ premier. Usuñ jedn¹ by dodaæ now¹");
                                premiery=true;
                                break;
                          }
                      }
                     }
          }
          if (wybrane==30)
          {
              usun();
          }
          if (wybrane==60)
          {
              premiery=false;
              wAplikacji=false;
              powrot2=true;
          }
          c=' ';
          system("CLS");
}
void pokaz()
{
          ifstream plik;
          plik.open("premieryksiazek.txt");
          string content;

          while(plik >> content)
          {
                string n, d, m, r;
                getline(plik,n);
                getline(plik,d);
                getline(plik,m);
                getline(plik,r);
                cout<<n<<" "<<d<<"."<<m<<"."<<r<<endl;
          }
}

void Minigra()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    system("cls");
    gotoxy(5,10);
    cout<<"WITAJ"<<endl;
    gotoxy(5,12);
    cout<<tr("W tej Mini grze twoim zadaniem jest zebraæ wszystkie ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<"15 monet!";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    gotoxy(5,14);
    cout<<tr("Poruszasz siê u¿ywaj¹c guzików :");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<" wsad.";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<<tr("Zaczynasz grê w lewym dolnym rogu. A oto twoja postaæ:");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<" ->.";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    gotoxy(5,16);
    cout<<tr("Zaczynasz z 3 ¿yciami ale na szczêœcie na planszy znajdziesz 3 dodatkowe ¿ycia do zebrania!");
    gotoxy(5,19);
    cout<<tr("Pamiêtaj by uwa¿ac na ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<" O";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<<tr(", obrêcze te s¹ zabójcze i zabieraj¹ ci ¿ycie za ka¿dym razem jak w nie wejdziesz!");
    gotoxy(5,21);
    cout<<"Powodzenia!";
    gotoxy(5,23);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
    cout<<tr("WPISZ OK BY ROZPOCZ¥Æ LUB WPISZ BACK BY WRÓCIÆ");
    gotoxy(52,23);
    string ODP;
    cin>>ODP;
    if (ODP=="OK")
    {
    system("cls");
    powrot=false;

    if(powrot==false);
    {
        rozpocznijGre();
        wGrze=true;
        while(wGrze==true)
        {
            gracz.stracil_zycie=false;
            funkcje();
            poruszenieGracz();

            if (c==char(27))
            {
                wGrze=false;
            }
            if ((gracz.stracil_zycie==true))
            {
                for (int i=0; i<=4; i++)
                {
                    gotoxy(gracz.x,gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
                    cout<<char(24);
                    Sleep(150);
                    gotoxy(gracz.x,gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
                    cout<<char(24);
                    Sleep(150);
                }
            }
            if (gracz.zycia<=0)
            {
                system("cls");
                gotoxy(74.5,21);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                cout<<tr("PRZEGRA£EŒ")<<endl;
                Sleep(1000);
                break;
            }
            if (gracz.Monety==15)
            {
                system("cls");
                gotoxy(74.5,21);
                cout<<tr("WYGRA£EŒ!")<<endl;
                gotoxy(74.5,19);
                cout<<"BRAWO!";
                Sleep(2000);
                break;
            }
        }
    }
    }
    if(ODP=="BACK")
    {
    powrot=true;
    wAplikacji=false;
    powrot2=true;
    zalogowano=true;
    }
    else
    {
        system("cls");
        gotoxy(74.5,21);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
        cout<<tr("B£ÊDNA ODPOWIEDZ");
        Sleep(1000);
        Minigra();
    }
}
void GlowneMenu();
void DodajKsiazke(ksiazka & k)
{
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<tr("U¿ywaj A i D by wybraæ")<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
    gotoxy(48.75,6);
    cout<<"VIRTUAL LIBRARY";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    gotoxy(40,10);
    cout<<"Dodaj ";
    gotoxy(60,10);
    cout<<tr("Wróæ ");
    gotoxy(10,16);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<<tr("Lista zapisanych ksi¹¿ek: ");
    fstream text;
    int s=1;
    string srodek;
    text.open("ksiazki.txt", ios::in);
    while(getline(text, srodek))
    {
        gotoxy(10,16+s);
        cout<<srodek;
        s++;
    }
    text.close();
    wAplikacji=true;
    while (wAplikacji==true)
    {
        char c='0';
          int wybranee=0;
          while (c!=char(13))
          {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                gotoxy(30+wybranee,8);
                cout<<"->";

                gotoxy(0,0);
                c=getch();
                gotoxy(30+wybranee,8);
                cout<<"  ";

                if (c=='d')
                {
                      if (wybranee<20)
                      {
                          wybranee+=20;
                      }
                }
                if (c=='a')
                {
                      if (wybranee>0)
                      {
                          wybranee-=20;
                      }
                }
          }
          if (wybranee==0)
          {
                 system("cls");
                 gotoxy(72,12);
                 cout<<"DODAJ KSIAZKE";
                 gotoxy(69,14);
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
                 cout<<"Zamiast spacji pisz '_'";
                 gotoxy(72,16);
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                 cout<<"Tytul: ";
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                 cin>>k.tytul;
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                 gotoxy(72,18);
                 cout<<"Autor: ";
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                 cin>>k.autor;
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                 gotoxy(72,20);
                 cout<<"Gatunek: ";
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                 cin>>k.gatunek;
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                 gotoxy(72,22);
                 cout<<"Ilosc Stron: ";
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                 cin>>k.iloscstron;
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
                 gotoxy(5,5);
                 cout<<tr("*Zapisz opis w 11 zdaniach. Jeœli masz mniej ni¿ 11 zdañ opisu wpisz w pozosta³e liniki '.' ");
                 gotoxy(72,23);
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                 cout<<"Opis*: ";
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                 cin>>k.opis;
                 gotoxy(72,24);
                 cin>>k.opis2;
                 gotoxy(72,25);
                 cin>>k.opis3;
                 gotoxy(72,26);
                 cin>>k.opis4;
                 gotoxy(72,27);
                 cin>>k.opis5;
                 gotoxy(72,28);
                 cin>>k.opis6;
                 gotoxy(72,29);
                 cin>>k.opis7;
                 gotoxy(72,30);
                 cin>>k.opis8;
                 gotoxy(72,31);
                 cin>>k.opis9;
                 gotoxy(72,32);
                 cin>>k.opis10;
                 gotoxy(72,33);
                 cin>>k.opis11;
                 text.open("ksiazki.txt", ios::out | ios::app);
                 text<<endl<<"X"<<endl;
                 text<<k.tytul<<endl;
                 text<<k.autor<<endl;
                 text<<k.gatunek<<endl;
                 text<<k.iloscstron<<endl;
                 text<<k.opis<<endl;
                 text<<k.opis2<<endl;
                 text<<k.opis3<<endl;
                 text<<k.opis4<<endl;
                 text<<k.opis5<<endl;
                 text<<k.opis6<<endl;
                 text<<k.opis7<<endl;
                 text<<k.opis8<<endl;
                 text<<k.opis9<<endl;
                 text<<k.opis10<<endl;
                 text<<k.opis11;
                 text.close();
                 system("cls");
                 gotoxy(74.5,21);
                 cout<<"DODANO";
                 Sleep(1000);
                 system("CLS");
                 GlowneMenu();
                 break;
          }
          if (wybranee==20)
          {
                system("CLS");
                powrot2=true;
                wAplikacji=false;
                break;
          }
          wybranee=20;
          c=' ';
          system("CLS");
          powrot2=true;
          wAplikacji=false;
          break;
    }
}
void wszystkieksiazki()
{
    while(wAplikacji==true)
   {
       system("cls");
       cout<<tr("Kliknij ESC by wróciæ do menu")<<endl<<endl<<endl;
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
       gotoxy(45,5);
       cout<<"Wszystkie ksiazki: "<<endl<<endl;

       fstream plik;
       int i=1;
       plik.open("ksiazki.txt", ios::in);
       string content;
       int kod;
       unsigned char znak;
       do
       {
           while(plik >> content)
           {
                    string tytul, autor, gatunek, iloscstron, opis,opis2 , opis3, opis4, opis5, opis6, opis7, opis8, opis9, opis10, opis11, Pustyznak;
                    getline(plik,Pustyznak);
                    getline(plik,tytul);
                    getline(plik,autor);
                    getline(plik,gatunek);
                    getline(plik,iloscstron);
                    getline(plik,opis);
                    getline(plik,opis2);
                    getline(plik,opis3);
                    getline(plik,opis4);
                    getline(plik,opis5);
                    getline(plik,opis6);
                    getline(plik,opis7);
                    getline(plik,opis8);
                    getline(plik,opis9);
                    getline(plik,opis10);
                    getline(plik,opis11);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                    cout<<i<<". "<<tr("Tytu³: ")<<tytul<<" "<<"Autor: "<<autor<<endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                    cout<<"Gatunek: ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    cout<<gatunek<<" ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                    cout<<tr("Iloœæ Stron: ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    cout<<iloscstron<<endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                    cout<<"Opis: ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    cout<<opis<<endl;
                    cout<<opis2<<endl;
                    cout<<opis3<<endl;
                    cout<<opis4<<endl;
                    cout<<opis5<<endl;
                    cout<<opis6<<endl;
                    cout<<opis7<<endl;
                    cout<<opis8<<endl;
                    cout<<opis9<<endl;
                    cout<<opis10<<endl;
                    cout<<opis11<<endl;
                    cout<<"     "<<endl;
                    i++;
           }
           znak=getch();
           kod = static_cast < int >( znak );

       }

       while(kod!=27);
       {
            wAplikacji=false;
            powrot2=true;
            wyjscie=false;
            break;

       }
   }
}
void przeczytaneksiazki()
{
while(wAplikacji==true)
   {
       system("cls");
       cout<<tr("Kliknij ESC by wróciæ do menu")<<endl<<endl<<endl;
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
       gotoxy(45,5);
       cout<<tr("Przeczytane ksi¹¿ki: ")<<endl<<endl;
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
       int kod;
       unsigned char znak;
       do
       {
         ifstream plikk;
         plikk.open("PRZ.txt");
         string content;
         int i=0;
         int j=1;
         while( getline( plikk, content ) )
         {
                vector<string> przeczytanaksiazka;

                przeczytanaksiazka.resize(1+j); // zmiana rozmiaru tablicy
                przeczytanaksiazka[j]=content;
                gotoxy(45,7+i);
                cout<<"Tytul i autor: "<<przeczytanaksiazka[j];
                i++;
                i++;
                j++;
         }
         plikk.close();
           znak=getch();
           kod = static_cast < int >( znak );
       }
       while(kod!=27);
       {
            wAplikacji=false;
            powrot2=true;
            wyjscie=false;
            break;
       }
}
}
int wybrane=2;
void MojProfil()
{

   char c='8';
   int wybrane=2;
   int *w;
   w=&wybrane;
   wyjscie=false;
   system("cls");
   while ((wAplikacji==true) && (wyjscie==false))
   {
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
          cout<<endl<<endl<<endl<<endl<<endl;
          cout<<tr("U¿ywaj W i S by wybraæ")<<endl;
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);

         ifstream plik;
         plik.open( "ZarejestrowaniUzytkownicy.txt" );
         string linia1;
         string linia2;
         getline(plik,linia1);
         getline(plik,linia2);
         ifstream pliks;
         pliks.open( "SUMA.txt" );
         string suma;
         getline(pliks,suma);
         ifstream pliksu;
         pliksu.open( "SUMA2.txt" );
         string suma2;
         getline(pliksu,suma2);
         gotoxy(45,10);
         cout<<tr("MÓJ PROFIL");
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
         gotoxy(34,12);
         cout<<tr("Twoje wyniki quizów:  Quiz1= ")<< suma <<"  Quiz2= "<<suma2;
         plik.close();
         gotoxy(100,10);
         cout<<tr("Twoje ulubione ksi¹¿ki:");
         ifstream plikk;
         plikk.open("Ulubione.txt");
         string content;
         int i=0;
         int j=1;
         while( getline( plikk, content ) )
         {
                vector<string> ulubionaksiazka;

                ulubionaksiazka.resize(1+j); // zmiana rozmiaru tablicy
                ulubionaksiazka[j]=content;
                gotoxy(100,12+i);
                cout<<"Tytul i autor: "<<ulubionaksiazka[j];
                i++;
                i++;
                j++;
         }
         plikk.close();
         gotoxy(0,18);
         cout<<"Twoje zapisane premiery:";
         gotoxy(0,20);
         pokaz();
         gotoxy(41,14);
         cout<<tr("Twój login:  ")<<linia1;
         gotoxy(41,16);
         cout<<tr("Twoje has³o:  ")<<linia2;
         gotoxy(48,18);
         cout<<"Back";
         while(c!=char(13))
          {
              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
              gotoxy(39,14+*w);
              cout<<"->";

              gotoxy(0,0);
              c=getch();
              gotoxy(39,14+*w);
              cout<<"  ";

              if (c=='s')
              {
                 if (*w<3)
                 {
                     *w+=2;
                 }
              }
              if (c=='w')
              {
                 if (*w>0)
                 {
                     *w-=2;
                 }
              }
           }
    if (*w==0)
    {
        ZmienLogin();
        break;
    }
    if (*w==2)
    {
        ZmienHaslo();
        break;
    }
    if (*w==4)
    {
        powrot2=true;
        break;
    }
    *w=4;
    c=' ';
    system("CLS");
    powrot2=true;
    break;
    }
}
void GlowneMenu()
{
    char c='0';
    int *w;
    w=&wybrane;
    wyjscie=false;
    system("CLS");
    wAplikacji=true;
    while ((wAplikacji==true) && (wyjscie==false))
    {
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
          cout<<endl<<endl<<endl<<endl<<endl;
          cout<<tr("U¿ywaj W i S by wybraæ")<<endl;

          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
          gotoxy(48.75,8);

          cout<<"VIRTUAL LIBRARY";

          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
          gotoxy(10,13);
          cout<<tr("Wyszukaj ksi¹¿ke");
          gotoxy(10,15);
          cout<<tr("Wszystkie ksi¹¿ki");
          gotoxy(10,17);
          cout<<tr("Przeczytane ksi¹¿ki");
          gotoxy(10,19);
          cout<<tr("Dodaj ksi¹¿ke ");
          gotoxy(10,21);
          cout<<tr("Premiery ksi¹¿ek");
          gotoxy(10,23);
          cout<<tr("Mój profil ");
          gotoxy(10,25);
          cout<<"Mini gra";
          gotoxy(10,27);
          cout<<tr("Quiz ksi¹¿kowy");
          gotoxy(10,29);
          cout<<tr(" Wyjœcie* ");
          gotoxy(10,39);
          cout<<tr("*Po wyjœciu automatycznie siê wylogujesz");
          while(c!=char(13))
          {
              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
              gotoxy(7,13+*w);
              cout<<"->";

              gotoxy(0,0);
              c=getch();
              gotoxy(7,13+*w);
              cout<<"  ";

              if (c=='s')
              {
                 if (*w<16)
                 {
                     *w+=2;
                 }
              }
              if (c=='w')
              {
                 if (*w>0)
                 {
                     *w-=2;
                 }
              }
           }
    if (*w==0)
    {
        system("cls");
        wyszukajksiazke();
        break;
    }
  if (*w==2)
    {
        wszystkieksiazki();
        break;
    }
    if (*w==4)
    {
        przeczytaneksiazki();
        break;
    }
    if(*w==6)
    {
        ksiazka k;
        DodajKsiazke(k);
        break;
    }
    if (*w==8)
    {
       PremieryKsiazek();
       break;
    }
    if (*w==10)
    {
        MojProfil();
        break;
    }

    if (*w==12)
    {
         Minigra();
        break;
    }
    if (*w==14)
    {
        quizksiazkowy();
        break;
    }
    if (*w==16)
    {
        wAplikacji=false;
        zalogowano=false;
        powrot=false;
        wyjscie=true;
        wyszukaj=false;
        wGrze=false;
        powrot2=false;
        powrot3=false;
        quiz1=false;
        quiz2=false;
        dodaj=false;
        premiery=false;
        break;
    }
    }
    *w=16;
    c=' ';
    system("CLS");
    wAplikacji=false;
    zalogowano=false;
    powrot=false;
    wyjscie=true;
    }

void logowanie()
{

   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
   gotoxy(74.5,15);
   cout<<tr("Zaloguj siê");
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
   gotoxy(74.5,17);
   cout<<"Nazwa:";
   gotoxy(74.5,19);
   cout<<tr("Has³o:");
   gotoxy(80,17);
   cin>>login;
   gotoxy(80,19);
   cin>>haslo;
   ifstream plik;
   plik.open( "ZarejestrowaniUzytkownicy.txt" );
   string linia1;
   string linia2;
   getline(plik,linia1);
   getline(plik,linia2);
   if(login==linia1 && haslo==linia2)
   {
       system("cls");
       gotoxy(74.5,21);
       cout<<"zalogowano";
       Sleep(1000);
       system("cls");
       zalogowano=true;
   } else
     {
       system("cls");
       gotoxy(74.5,21);
       cout<<tr("B³¹d logowania!");
       Sleep(1000);
       system("cls");
       logowanie();
     }
}

int main()
{
    Okno(160,44);
    odswierzanie=10;
    menu();
    while (wyjscie==false)
    {
       logowanie();
       break;
    }
    if (zalogowano==true)
    {
       GlowneMenu();
    }
    while (premiery==true)
    {
       PremieryKsiazek();
    }
    while (powrot3==true)
    {
       GlowneMenu();
    }
    while (powrot2==true)
    {
       GlowneMenu();
    }
    while (part2==true)
    {
        Part2();
    }
    while (Szukaj==true)
    {
       wyszukajksiazke();
    }
    while (powrot==true)
    {
       GlowneMenu();
    }
    if (wyjscie==true)
    {
        return 0;
    }

return 0;
}
