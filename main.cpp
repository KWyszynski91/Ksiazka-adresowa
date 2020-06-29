#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iomanip>

using namespace std;

struct Adresat
{
    int id;
    int idUzytkownika;
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
};

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};

void ZapisUzytkownikaDoPliku(vector<Uzytkownik> &WektorUzytkownikow, int liczbaUzytkownikow)
{
    fstream plik;
    plik.open("uzytkownicy.txt",ios::out);
    for(int i=0; i<liczbaUzytkownikow; i++)
    {
        plik<<WektorUzytkownikow[i].id<<"|";
        plik<<WektorUzytkownikow[i].nazwa<<"|";
        plik<<WektorUzytkownikow[i].haslo<<"|";
        plik<<endl;
    }
    plik.close();
}

int rejestracja(vector<Uzytkownik> &WektorUzytkownikow, int iloscUzytkownikow)
{
    string nazwa, haslo;
    int i=0;
    cout<<"Podaj nazw\251 u\276ytkownika: ";
    cin>>nazwa;
    while(i<iloscUzytkownikow)
    {
        if(WektorUzytkownikow[i].nazwa==nazwa)
        {
            cout<<"Taki u\276ytkownik ju\276 istnieje. Podaj inn\245 nazw\251...";
            cin>>nazwa;
            i=0;
        }
        else
        {
            i++;
        }
    }
    cout<<"Podaj has\210o: ";
    cin>>haslo;
    WektorUzytkownikow.push_back(Uzytkownik{iloscUzytkownikow+1, nazwa, haslo});
    ZapisUzytkownikaDoPliku(WektorUzytkownikow, iloscUzytkownikow+1);
    cout<<"Konto zosta\210o za\210o\276one"<<endl;
    Sleep(1000);
    return iloscUzytkownikow+1;
}

int logowanie(vector<Uzytkownik> &WektorUzytkownikow, int iloscUzytkownikow)
{
    string nazwa, haslo;
    cout<<"Podaj nazw\251: "<<endl;
    cin>>nazwa;
    int i=0;
    while(i<iloscUzytkownikow)
    {
        if(WektorUzytkownikow[i].nazwa==nazwa)
        {
            for(int proby=0; proby<3; proby++)
            {
                cout<<"Podaj has\210o. Pozosta\210o pr\242b: "<<3-proby<<endl;
                cin>>haslo;
                if (WektorUzytkownikow[i].haslo==haslo)
                {
                    cout<<"Witaj "<<WektorUzytkownikow[i].nazwa<<" !"<<endl;
                    Sleep(1000);
                    return WektorUzytkownikow[i].id;
                }
            }
            cout<<"Wszystkie pr\210by wykorzystane. Poczekaj 3s. przed kolejn\245 pr\242b\245..."<<endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout<<"Nie odnaleziono u\276ytkownika"<<endl;
    Sleep(1500);
    return 0;
}

void WyswietlanieDanych (vector<Adresat> &WektorAdresow, int pozycjaKontaktu)
{
    cout<<WektorAdresow[pozycjaKontaktu].id<<"|";
    cout<<WektorAdresow[pozycjaKontaktu].idUzytkownika<<"|";
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

void ZapisywanieDanychdoPliku(vector<Adresat> &WektorAdresow, int liczbaKontaktow, int nowyID)
{
    fstream plikWY;
    plikWY.open("adresaci_tymczasowy.txt",ios::out);
    for(int i=0; i<liczbaKontaktow; i++)
    {
        plikWY<<WektorAdresow[i].id<<"|";
        plikWY<<WektorAdresow[i].idUzytkownika<<"|";
        plikWY<<WektorAdresow[i].imie<<"|";
        plikWY<<WektorAdresow[i].nazwisko<<"|";
        plikWY<<WektorAdresow[i].numerTelefonu<<"|";
        plikWY<<WektorAdresow[i].email<<"|";
        plikWY<<WektorAdresow[i].adres<<"|";
        plikWY<<endl;
    }
    int aktywnyUzytkownik=WektorAdresow[0].idUzytkownika;
    Sleep(1000);
    fstream plikWE;
    int id=0, idUzytkownika=0;
    string imie, nazwisko,numerTelefonu, email, adres;
    plikWE.open("adresaci.txt",ios::in);
    string linia;
    int nrLinii=1;
    while(getline(plikWE,linia,'|'))
    {
        switch(nrLinii)
        {
        case 1:{id=atoi(linia.c_str());break;}
        case 2:{idUzytkownika=atoi(linia.c_str());break;}
        case 3:{imie=linia;break;}
        case 4:{nazwisko=linia;break;}
        case 5:{numerTelefonu=linia;break;}
        case 6:{email=linia;break;}
        case 7:{adres=linia;}
        }
        if(nrLinii==7)
        {
            if(idUzytkownika!=aktywnyUzytkownik)
            {
                plikWY<<id<<"|";
                plikWY<<idUzytkownika<<"|";
                plikWY<<imie<<"|";
                plikWY<<nazwisko<<"|";
                plikWY<<numerTelefonu<<"|";
                plikWY<<email<<"|";
                plikWY<<adres<<"|";
                plikWY<<endl;
            }
            nrLinii=0;
        }
        nrLinii++;
    }
    Sleep(1000);
    plikWE.close();
    plikWY.close();
    remove("adresaci.txt");
    int rezultat;
    rezultat=rename("adresaci_tymczasowy.txt", "adresaci.txt");
}

int DodawanieKontaktu (vector<Adresat> &WektorAdresow, int liczbaKontaktow, int ostatniID, int idUzytkownika)
{
    string imie,nazwisko,numerTelefonu,email,adres;
    int nowyID=ostatniID+1;
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
    WektorAdresow.push_back(Adresat{nowyID, idUzytkownika, imie, nazwisko, numerTelefonu, email, adres});
    fstream plikWY;
    plikWY.open("adresaci.txt",ios::out|ios::app);
    {
        plikWY<<nowyID<<"|";
        plikWY<<idUzytkownika<<"|";
        plikWY<<imie<<"|";
        plikWY<<nazwisko<<"|";
        plikWY<<numerTelefonu<<"|";
        plikWY<<email<<"|";
        plikWY<<adres<<"|";
        plikWY<<endl;
    }
    plikWY.close();
    cout<<"Dokonano "<<liczbaKontaktow+1<<" wpisu do listy u\276ytkownika!"<<endl;
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
                ZapisywanieDanychdoPliku(WektorAdresow, liczbaKontaktow, numerID);
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
                ZapisywanieDanychdoPliku(WektorAdresow, liczbaKontaktow-1, numerID);
            }
            else
            {
                znalezione=0;
                break;
            }
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

int UstalOstatniegoAdresata(int liczbaKontaktow, int idOstatniegoAdresata)
{
    string imie, nazwisko,numerTelefonu, email, adres;
    int id=0, idUzytkownika=0;
    fstream plik;
    plik.open("adresaci.txt",ios::in);
    string linia;
    int nrLinii=1;
    int NowyOstatniID=0;
    while(getline(plik,linia,'|'))
    {
        switch(nrLinii)
        {
        case 1:{id=atoi(linia.c_str());break;}
        case 2:{idUzytkownika=atoi(linia.c_str());break;}
        case 3:{imie=linia;break;}
        case 4:{nazwisko=linia;break;}
        case 5:{numerTelefonu=linia;break;}
        case 6:{email=linia;break;}
        case 7:{adres=linia;break;}
        }
        if(nrLinii==7)
        {
            if(id>NowyOstatniID)
            {
                NowyOstatniID=id;
            }

            nrLinii=0;
        }
        nrLinii++;
    }
    plik.close();
return NowyOstatniID;
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

void zmianaHasla(vector<Uzytkownik> &WektorUzytkownikow, int iloscUzytkownikow, int IDzalogowanegoUzytkownika)
{
    string haslo;
    cout<<"Podaj nowe haslo: "<<endl;
    cin>>haslo;
    for(int i=0; i<iloscUzytkownikow; i++)
    {
        if(WektorUzytkownikow[i].id==IDzalogowanegoUzytkownika)
        {
            WektorUzytkownikow[i].haslo=haslo;
            ZapisUzytkownikaDoPliku(WektorUzytkownikow, iloscUzytkownikow);
            cout<<"Has\210o zosta\210o zmienione!"<<endl;
            Sleep(1500);
        }
    }
}

int main()
{
    vector<Uzytkownik> uzytkownicy;
    int iloscUzytkownikow=0;
    int IDentyfikator=0;
    string nazwa, haslo;
    fstream plik;
    plik.open("uzytkownicy.txt",ios::in);
    if(plik.good()==false)
    {
        cout<<"Nie odnaleziono istniej\245cych danych."<<endl;
    }
    else
    {
        string liniaUzytkownicy;
        int nrLiniiUzytkownicy=1;
        while(getline(plik,liniaUzytkownicy,'|'))
        {
            switch(nrLiniiUzytkownicy)
            {
            case 1:
            {
                IDentyfikator=atoi(liniaUzytkownicy.c_str());
                break;
            }
            case 2:
            {
                nazwa=liniaUzytkownicy;
                break;
            }
            case 3:
            {
                haslo=liniaUzytkownicy;
                uzytkownicy.push_back(Uzytkownik{IDentyfikator, nazwa, haslo});
                break;
            }
            }
            if(nrLiniiUzytkownicy==3)
            {
                nrLiniiUzytkownicy=0;
                iloscUzytkownikow++;
            }
            nrLiniiUzytkownicy++;
        }
        plik.close();
    }
    char wybor;
    while(1)
    {
        if(IDentyfikator==0)
        {
            system("cls");
            cout<<"==KSI\244\275KA ADRESOWA==" << endl;
            cout<<"____panel_logowania____" << endl;
            cout<<"1. Logowanie"<<endl;
            cout<<"2. Rejestracja"<<endl;
            cout<<"9. Zamknij program"<<endl;
            cin>>wybor;
            if(wybor=='1')
            {
                IDentyfikator=logowanie(uzytkownicy,iloscUzytkownikow);
            }
            if(wybor=='2')
            {
                iloscUzytkownikow=rejestracja(uzytkownicy,iloscUzytkownikow);
            }
            else if(wybor=='9')
            {
                exit(0);
            }
        }
        else
        {
            vector<Adresat> adresaci;
            int id=0, idUzytkownika=0;
            int idOstatniegoAdresata=0;
            string imie, nazwisko,numerTelefonu, email, adres;
            char wybor;
            int IDkontaktu=0;
            int liczbaKontaktow=0;
            fstream plik;
            plik.open("adresaci.txt",ios::in);
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
                    case 1:{id=atoi(linia.c_str()); break;}
                    case 2:{idUzytkownika=atoi(linia.c_str()); break;}
                    case 3:{imie=linia; break;}
                    case 4:{nazwisko=linia; break;}
                    case 5:{numerTelefonu=linia; break;}
                    case 6:{email=linia; break;}
                    case 7:{adres=linia; break;}
                    }
                    if(nrLinii==7)
                    {
                        if(idUzytkownika==IDentyfikator)
                        {
                            adresaci.push_back(Adresat{id, idUzytkownika, imie, nazwisko, numerTelefonu, email, adres});
                            liczbaKontaktow++;
                        }
                        if(id>idOstatniegoAdresata)
                    {
                        idOstatniegoAdresata=id;
                    }
                        nrLinii=0;
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
                cout<<"7. Zmie\344 has\210o"<<endl;
                cout<<"9. Wyloguj si\251"<<endl;
                cout<<"====================" << endl;
                cout<<"Tw\242j wyb\242r: ";
                cin>>wybor;
                cout<<"====================" << endl;
                if(wybor=='1')
                {
                    liczbaKontaktow=DodawanieKontaktu(adresaci, liczbaKontaktow, idOstatniegoAdresata, IDentyfikator);
                    idOstatniegoAdresata++;
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
                    idOstatniegoAdresata=UstalOstatniegoAdresata(liczbaKontaktow, idOstatniegoAdresata);
                }
                if(wybor=='6')
                {
                    EdytujKontakt(adresaci, liczbaKontaktow);
                }
                if(wybor=='7')
                {
                   zmianaHasla(uzytkownicy, iloscUzytkownikow, IDentyfikator);
                }
                else if(wybor=='9')
                {
                    break;
                }
            }
            IDentyfikator=0;
        }
    }
    return 0;
}
