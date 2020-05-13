#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>

using namespace std;

struct Kontakt
{
    int id, telefon;
    string imie,nazwisko,poczta, adres;
};

void WyswietlanieDanych (Kontakt ListaKontaktow[], int pozycjaKontaktu)
{
    cout<<ListaKontaktow[pozycjaKontaktu].id<<endl;
    cout<<ListaKontaktow[pozycjaKontaktu].imie<<endl;
    cout<<ListaKontaktow[pozycjaKontaktu].nazwisko<<endl;
    cout<<ListaKontaktow[pozycjaKontaktu].telefon<<endl;
    cout<<ListaKontaktow[pozycjaKontaktu].poczta<<endl;
    cout<<ListaKontaktow[pozycjaKontaktu].adres<<endl;
    cout<<endl;
}

void SzukaniePoImieniu(Kontakt ListaKontaktow[], int liczbaKontaktow)
{
    int znalezione=0;
    string WyszukajImie;
    cout<<"Podaj imi\251 poszukiwanego kontaktu: ";
    cin>>WyszukajImie;
    for(int i=0; i<liczbaKontaktow; i++)
    {
        if(ListaKontaktow[i].imie==WyszukajImie)
        {
            WyswietlanieDanych(ListaKontaktow, i);
            znalezione++;
        }
    }
    if(znalezione==0)
    {
        cout<<"Nie znaleziono kontaktu o podanym imieniu"<<endl;
    }
    cout<<"Aby wr\242ci\206 naci\230nij dowolny klawisz..."<<endl;
    getch();
}

void SzukaniePoNazwisku(Kontakt ListaKontaktow[], int liczbaKontaktow)
{
    int znalezione=0;
    string WyszukajNazwisko;
    cout<<"Podaj nazwisko poszukiwanego kontaktu: ";
    cin>>WyszukajNazwisko;
    for(int i=0; i<liczbaKontaktow; i++)
    {
        if(ListaKontaktow[i].nazwisko==WyszukajNazwisko)
        {
            WyswietlanieDanych(ListaKontaktow, i);
            znalezione++;
        }
    }
    if(znalezione==0)
    {
        cout<<"Nie znaleziono kontaktu o podanym nazwisku"<<endl;
    }

    cout<<"Aby wr\242ci\206 naci\230nij dowolny klawisz..."<<endl;
    getch();
}

int DodawanieKontaktu (Kontakt ListaKontaktow[], int liczbaKontaktow)
{
    string imie,nazwisko,poczta,adres;
    int telefon=0;
    cout<<"Podaj imi\251 kontaktu: ";
    cin>>imie;
    cout<<"Podaj nazwisko kontaktu: ";
    cin>>nazwisko;
    cout<<"Wprowad\253 numer telefonu: ";
    cin>>telefon;
    cout<<"Wprowad\253 adres poczty elektronicznej: ";
    cin>>poczta;
    cout<<"Wprowad\253 adres kontaktu <miasto, ulica nr.domu/mieszkania>: ";
    getline(cin>>ws, adres);

    ListaKontaktow[liczbaKontaktow].id=liczbaKontaktow+1;
    ListaKontaktow[liczbaKontaktow].imie=imie;
    ListaKontaktow[liczbaKontaktow].nazwisko=nazwisko;
    ListaKontaktow[liczbaKontaktow].telefon=telefon;
    ListaKontaktow[liczbaKontaktow].poczta=poczta;
    ListaKontaktow[liczbaKontaktow].adres=adres;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::out|ios::app);
    plik<<ListaKontaktow[liczbaKontaktow].id<<endl;
    plik<<ListaKontaktow[liczbaKontaktow].imie<<endl;
    plik<<ListaKontaktow[liczbaKontaktow].nazwisko<<endl;
    plik<<ListaKontaktow[liczbaKontaktow].telefon<<endl;
    plik<<ListaKontaktow[liczbaKontaktow].poczta<<endl;
    plik<<ListaKontaktow[liczbaKontaktow].adres<<endl;
    plik.close();

    cout<<"Dokonano "<<liczbaKontaktow+1<<" wpisu do listy!"<<endl;
    Sleep(1500);
    return liczbaKontaktow+1;
}

int SzukajKontaktu(Kontakt ListaKontaktow[], int liczbaKontaktow)
{
    if(liczbaKontaktow!=0)
    {
        char szukanie;
        while(1)
        {
            system("cls");
            cout<<"====WYSZUKIWANIE====" << endl;
            cout<<"1.Szukaj wg IMIENIA"<<endl;
            cout<<"2.Szukaj wg NAZWISKA"<<endl;
            cout<<"3.Powrot"<<endl;
            cout<<"====================" << endl;
            cin>>szukanie;
            if(szukanie=='1')
            {
                SzukaniePoImieniu(ListaKontaktow, liczbaKontaktow);
            }
            else if(szukanie=='2')
            {
                SzukaniePoNazwisku(ListaKontaktow, liczbaKontaktow);
            }
            else if(szukanie=='3')
            {
                return 0;
            }
        }
    }
    else
    {
        cout<<"Ksi\245\276ka adresowa jest pusta!"<<endl;
        Sleep(1500);
        return 0;
    }
}

void PokazKontakty(Kontakt ListaKontaktow[], int liczbaKontaktow)
{
    cout<<"LISTA KONTAKT\242W"<<endl;
    cout<<endl;
    for (int i=0; i<liczbaKontaktow; i++)
    {
        WyswietlanieDanych(ListaKontaktow, i);
    }
    cout<<"Aby wr\242ci\206 naci\230nij dowolny klawisz..."<<endl;
    getch();
}

int main()
{
    Kontakt ListaKontaktow[20];
    char wybor;
    int IDkontaktu=0;
    int liczbaKontaktow=0;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::in);
    if(plik.good()==false)
    {
        cout<<"Nie odnaleziono istniej\245cych danych."<<endl;
    }
    else
    {
        string linia;
        int nrLinii=1;
        while(getline(plik,linia))
        {
            switch(nrLinii)
            {
            case 1:
                ListaKontaktow[liczbaKontaktow].id=atoi(linia.c_str());
                break;
            case 2:
                ListaKontaktow[liczbaKontaktow].imie=linia;
                break;
            case 3:
                ListaKontaktow[liczbaKontaktow].nazwisko=linia;
                break;
            case 4:
                ListaKontaktow[liczbaKontaktow].telefon=atoi(linia.c_str());
                break;
            case 5:
                ListaKontaktow[liczbaKontaktow].poczta=linia;
                break;
            case 6:
                ListaKontaktow[liczbaKontaktow].adres=linia;
                break;
            }
            if(nrLinii==6)
            {
                nrLinii=0;
                liczbaKontaktow++;
            }
            nrLinii++;
        }
        plik.close();
    }

    while(1)
    {
        system("cls");
        cout<<"==KSI\244\275KA ADRESOWA==" << endl;
        cout<<"____panel_g\210\242wny____" << endl;
        cout<<"1.Wpis"<<endl;
        cout<<"2.Wyszukaj"<<endl;
        cout<<"3.Poka\276 kontakty"<<endl;
        cout<<"4.Zako\344cz"<<endl;
        cout<<"====================" << endl;
        cin>>wybor;
        if(wybor=='1')
        {
            liczbaKontaktow=DodawanieKontaktu(ListaKontaktow, liczbaKontaktow);
        }
        else if(wybor=='2')
        {
            IDkontaktu=SzukajKontaktu(ListaKontaktow, liczbaKontaktow);
        }
        else if(wybor=='3')
        {
            PokazKontakty(ListaKontaktow, liczbaKontaktow);
        }
        else if(wybor=='4')
        {
            exit(0);
        }
    }
    return 0;
}
