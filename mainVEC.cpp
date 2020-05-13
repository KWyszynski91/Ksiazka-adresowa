#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <vector>

using namespace std;

struct Adresat
{
    int id;
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
};

void WyswietlanieDanych (vector<Adresat> &WektorAdresow, int pozycjaKontaktu)
{
    cout<<WektorAdresow[pozycjaKontaktu].id<<"|";
    cout<<WektorAdresow[pozycjaKontaktu].imie<<"|";
    cout<<WektorAdresow[pozycjaKontaktu].nazwisko<<"|";
    cout<<WektorAdresow[pozycjaKontaktu].numerTelefonu<<"|";
    cout<<WektorAdresow[pozycjaKontaktu].email<<"|";
    cout<<WektorAdresow[pozycjaKontaktu].adres<<"|";
    cout<<endl;
}

void SzukaniePoImieniu(vector<Adresat> &WektorAdresow, int liczbaKontaktow)
{
    int znalezione=0;
    string WyszukajImie;
    cout<<"Podaj imi\251 poszukiwanego kontaktu: ";
    cin>>WyszukajImie;
    for(int i=0; i<liczbaKontaktow; i++)
    {
        if(WektorAdresow[i].imie==WyszukajImie)
        {
            WyswietlanieDanych(WektorAdresow, i);
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

void SzukaniePoNazwisku(vector<Adresat> &WektorAdresow, int liczbaKontaktow)
{
    int znalezione=0;
    string WyszukajNazwisko;
    cout<<"Podaj nazwisko poszukiwanego kontaktu: ";
    cin>>WyszukajNazwisko;
    for(int i=0; i<liczbaKontaktow; i++)
    {
        if(WektorAdresow[i].nazwisko==WyszukajNazwisko)
        {
            WyswietlanieDanych(WektorAdresow, i);
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

void ZapisywanieDanychdoPliku(vector<Adresat> &WektorAdresow, int liczbaKontaktow)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::out);
    for(int i=0; i<liczbaKontaktow; i++)
    {
        plik<<WektorAdresow[i].id<<"|";
        plik<<WektorAdresow[i].imie<<"|";
        plik<<WektorAdresow[i].nazwisko<<"|";
        plik<<WektorAdresow[i].numerTelefonu<<"|";
        plik<<WektorAdresow[i].email<<"|";
        plik<<WektorAdresow[i].adres<<"|";
        plik<<endl;
    }
    plik.close();
}

int DodawanieKontaktu (vector<Adresat> &WektorAdresow, int liczbaKontaktow)
{
    string imie,nazwisko,numerTelefonu,email,adres;
    int id=0;
    if(liczbaKontaktow!=0)
    {
        id=WektorAdresow[liczbaKontaktow-1].id+1;
    }
    else
    {
        id=liczbaKontaktow+1;
    }
    cout<<"Podaj imi\251 kontaktu: ";
    cin>>imie;
    cout<<"Podaj nazwisko kontaktu: ";
    cin>>nazwisko;
    cout<<"Wprowad\253 numer telefonu: ";
    cin>>numerTelefonu;
    cout<<"Wprowad\253 adres poczty elektronicznej: ";
    cin>>email;
    cout<<"Wprowad\253 adres kontaktu <miasto, ulica nr.domu/mieszkania>: ";
    getline(cin>>ws, adres);
    WektorAdresow.push_back(Adresat{id, imie, nazwisko, numerTelefonu, email, adres});
    ZapisywanieDanychdoPliku(WektorAdresow, liczbaKontaktow+1);
    cout<<"Dokonano "<<liczbaKontaktow+1<<" wpisu do listy!"<<endl;
    Sleep(1500);
    return liczbaKontaktow+1;
}

int EdytujKontakt(vector<Adresat> &WektorAdresow, int liczbaKontaktow)
{
    int numerID;
    int znalezione=0;
    int pozycja=0;
    char edycja;
    string imie, nazwisko, numerTelefonu, email, adres;
    cout<<"Wpisz numer ID kontaktu, kt\242ry chcesz edytowa\206: ";
    cin>>numerID;
    for(int i=0; i<liczbaKontaktow; i++)
    {
        if(WektorAdresow[i].id==numerID)
        {
            WyswietlanieDanych(WektorAdresow, i);
            imie=WektorAdresow[i].imie;
            nazwisko=WektorAdresow[i].nazwisko;
            numerTelefonu=WektorAdresow[i].numerTelefonu;
            email=WektorAdresow[i].email;
            adres=WektorAdresow[i].adres;
            pozycja=i;
            znalezione++;
        }
    }
        if(znalezione==0)
        {
            cout<<"Nie znaleziono kontaktu o podanym numerze ID"<<endl;
            Sleep(2000);
        }
        else
        {
            while(1)
            {
                cout<<"Kt\242ra informacj\251 chcesz zmieni\206?"<<endl;
                cout<<"1.imi\251"<<endl;
                cout<<"2.nazwisko"<<endl;
                cout<<"3.numer telefonu"<<endl;
                cout<<"4.adres e-mail"<<endl;
                cout<<"5.adres pocztowy"<<endl;
                cout<<"6.Zako\344cz operacj\251"<<endl;
                cin>>edycja;
                if(edycja=='1')
                {
                    cout<<"Podaj nowe imi\251 kontaktu: ";
                    cin>>imie;
                    WektorAdresow[pozycja].imie=imie;
                }
                else if(edycja=='2')
                {
                    cout<<"Podaj nowe nazwisko kontaktu: ";
                    cin>>nazwisko;
                    WektorAdresow[pozycja].nazwisko=nazwisko;
                }
                else if(edycja=='3')
                {
                    cout<<"Podaj nowy numer telefonu do kontaktu: ";
                    cin>>numerTelefonu;
                    WektorAdresow[pozycja].numerTelefonu=numerTelefonu;
                }
                else if(edycja=='4')
                {
                    cout<<"Podaj nowy adres poczty elektronicznej do kontaktu: ";
                    cin>>email;
                    WektorAdresow[pozycja].email=email;
                }
                else if(edycja=='5')
                {
                    cout<<"Podaj nowy adres pocztowy do kontaktu: ";
                    getline(cin>>ws, adres);
                    WektorAdresow[pozycja].adres=adres;
                }
                cout<<"Pozostawione dane kontaktowe: "<<endl;
                WyswietlanieDanych(WektorAdresow, pozycja);
                ZapisywanieDanychdoPliku(WektorAdresow, liczbaKontaktow);
                Sleep(2000);
                return liczbaKontaktow;
            }
        }
    }

int UsunKontakt(vector<Adresat> &WektorAdresow, int liczbaKontaktow)
{
    int numerID;
    int znalezione=0;
    char decyzja;
    string imie, nazwisko, numerTelefonu, email, adres;
    cout<<"Wpisz numer ID kontaktu, kt\242ry chcesz usun\245\206: ";
    cin>>numerID;
    for(int i=0; i<liczbaKontaktow; i++)
    {
        if(WektorAdresow[i].id==numerID)
        {
            znalezione++;
            cout<<"Odnaleziono kontakt o podanym numerze ID: "<<endl;
            WyswietlanieDanych(WektorAdresow, i);
            cout<<"Potwierdz usuni\251cie kontaktu:"<<endl;
            cout<<"t -> USUN  |  n -> ANULUJ"<<endl;
            cin>>decyzja;
            if(decyzja=='t')
            {
                WektorAdresow.erase(WektorAdresow.begin()+i);
            }
            else if(decyzja=='n')
            {
                znalezione=0;
                break;
            }
            ZapisywanieDanychdoPliku(WektorAdresow, liczbaKontaktow-1);
            return liczbaKontaktow-1;
        }
    }
    if(znalezione==0)
    {
        cout<<"Operacja przerwana"<<endl;
        Sleep(1500);
        return liczbaKontaktow;
    }
}

void PokazKontakty(vector<Adresat> &WektorAdresow, int liczbaKontaktow)
{
    cout<<"LISTA KONTAKT\242W"<<endl;
    cout<<endl;
    cout<<"Ilo\230\206 wpis\242w w Ksi\245\276ce: "<< liczbaKontaktow<<endl;
    vector<Adresat>::iterator it;
    for (int i=0; i<liczbaKontaktow; i++)
    {
        WyswietlanieDanych(WektorAdresow, i);
    }
    cout<<"Aby wr\242ci\206 naci\230nij dowolny klawisz..."<<endl;
    getch();
}

int main()
{
    vector<Adresat> adresaci;
    int id=0;
    string imie, nazwisko,numerTelefonu, email, adres;
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
        while(getline(plik,linia,'|'))
        {
            switch(nrLinii)
            {
            case 1:
            {
                id=atoi(linia.c_str());
                break;
            }
            case 2:
            {
                imie=linia;
                break;
            }
            case 3:
            {
                nazwisko=linia;
                break;
            }
            case 4:
            {
                numerTelefonu=linia;
                break;
            }
            case 5:
            {
                email=linia;
                break;
            }
            case 6:
            {
                adres=linia;
                adresaci.push_back(Adresat{id, imie, nazwisko, numerTelefonu, email, adres});
                break;
            }
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
        cout<<"1. Dodaj adresata"<<endl;
        cout<<"2. Wyszukaj po imieniu"<<endl;
        cout<<"3. Wyszukaj po nazwisku"<<endl;
        cout<<"4. Wy\230wietl wszystkich adresat\242w"<<endl;
        cout<<"5. Usu\344 adresata"<<endl;
        cout<<"6. Edytuj adresata"<<endl;
        cout<<"9. Zako\344cz"<<endl;
        cout<<"====================" << endl;
        cout<<"Tw\242j wyb\242r:"<<endl;
        cin>>wybor;
        if(wybor=='1')
        {
            liczbaKontaktow=DodawanieKontaktu(adresaci, liczbaKontaktow);
        }
        else if(wybor=='2')
        {
            SzukaniePoImieniu(adresaci, liczbaKontaktow);
        }
        if(wybor=='3')
        {
            SzukaniePoNazwisku(adresaci, liczbaKontaktow);
        }
        if(wybor=='4')
        {
            PokazKontakty(adresaci, liczbaKontaktow);
        }
        if(wybor=='5')
        {
            liczbaKontaktow=UsunKontakt(adresaci, liczbaKontaktow);
        }
        if(wybor=='6')
        {
            EdytujKontakt(adresaci, liczbaKontaktow);
        }
        else if(wybor=='9')
        {
            exit(0);
        }
    }
    return 0;
}
