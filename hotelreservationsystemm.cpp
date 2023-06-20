#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <vector>
#include <ctime>
#include <sstream>

using namespace std;
struct Room
{
    string name;
    string type;
    int bednumber;
    int rent;
    int hotelID;
    bool slobodna;

    Room addRoom(int);
    void searchRoom(int);
    void deleteRoom(int);
    void displayRoom(Room);
    void pretraziSobu();
    void prikupiPovratneInformacije();
};

struct Hotel {
    string name;
    string address;
    string contact;
    int ID;
    string starsnumber;
    vector<Room> rooms;


    void addRoom(const Room& room) {
        rooms.push_back(room);
    }


};

struct food {
    char nm[100];
    int price;
    int code;
} f[15];

struct guest {
    char nm[10], cntry[10], rmtyp[10], Bills[3];
    int rmno, eWllt;
};

void RSTRNTmenu();
void foodmenu();
void orderfood(guest g[50], int n);
void setTextColor(int colorCode) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(colorCode));
}

void exitProgram() {
    // Prikazuje animaciju uzorka sa zvjezdicama (*)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j <= i; j++) {
            cout << "*";
        }
        cout << endl;
        Sleep(500); // Pauza od 0.5 sekunde
    }

    cout << "*****************************\n";
    cout << "*                           *\n";
    cout << "*    THE MAJESTIC PEARL     *\n";
    cout << "*                           *\n";
    cout << "*****************************\n";

    // Dodatni kod za izlazak iz programa
    cout << "\nHvala Vam sto ste posjetili Hotel The Majestic Pearl. Zelimo Vam ugodan dan!\n";
    Sleep(2000); // Pauza od 2 sekunde (samo za Windows platformu)
    exit(0); // Izlazak iz programa
    // Prikazuje zavr?nu poruku i izlazi iz programa
    cout << "Program je zatvoren." << endl;
    exit(0);
}
void prikupiPovratneInformacije();
double izracunajProsjek();
void ocijeniHotel();
void ispisiKomentare();
void pretraziSobe();

void banner() {
    setTextColor(12); // Postavljanje boje teksta na crvenu (kod 12)
    cout << endl
         << endl;
    cout << "             ########################################" << endl;
    cout << "             ##                                    ##" << endl;
    cout << "             ##	            Dobrodosli u           ##" << endl;
    cout << "             ##                                    ##" << endl;
    cout << "             ##          The Majestic Pearl        ##" << endl;
    cout << "             ##                                    ##" << endl;
    cout << "             ########################################" << endl<< endl << endl;

    double prosjek=izracunajProsjek();

    cout << "           ##    Hvala Vam sto koristite nase usluge  ##" << endl;
    cout << "  ##   Na pravom ste mjestu jer nas nasi klijenti ocjenjuju ocjenom: "<<prosjek<<"!   ##" << endl;
    cout << "           ##    Pritisnite bilo koju tipku za nastavak!  ##" << endl;
    getch();
}
vector<string> reservedRooms;//za pohranu rezervisanih soba
//da nam se ne ispisuje u dostupnim sobama neka koja je vec rezervisana


void displayRooms() {
    ifstream file("rooms.txt");
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (!line.empty()) {
                Room room;

                istringstream iss(line.substr(line.find(": ") + 2));
                iss >> room.name;

                getline(file, line);
                istringstream iss2(line.substr(line.find(": ") + 2));
                iss2 >> room.type;

                getline(file, line);
                istringstream iss3(line.substr(line.find(": ") + 2));
                iss3 >> room.bednumber;

                getline(file, line);
                istringstream iss4(line.substr(line.find(": ") + 2));
                iss4 >> room.rent;

                cout << "Naziv sobe: " << room.name << std::endl;
                cout << "Tip sobe: " << room.type << std::endl;
                cout << "Broj kreveta: " << room.bednumber << std::endl;
                cout << "Najam: " << room.rent << std::endl;
                cout << endl;
            }

        }
        file.close();
    }

    else {
        cout << "Nemoguce otvoriti datoteku." << std::endl;
    }
}

struct Usluga {
    string naziv;
    string cijena;
};


void prikaziUsluge()
{
    ifstream datoteka("services.txt");
    string linija;
    vector<Usluga> usluge;

    if (datoteka.is_open())
    {
        while (getline(datoteka, linija))
        {
            if (!linija.empty())
            {
                Usluga usluga;
                usluga.naziv = linija;

                getline(datoteka, linija);
                istringstream iss(linija);
                iss >> usluga.cijena;

                usluge.push_back(usluga);
            }
        }
        datoteka.close();
    }
    else
    {
        cout << "Nije moguce otvoriti datoteku." << endl;
        return;
    }

    cout << "Dostupne usluge:" << endl;
    for (size_t i = 0; i < usluge.size(); i++)
    {
        cout << "Usluga: " << usluge[i].naziv << endl;
        cout << "Cijena: " << usluge[i].cijena << " KM" << endl;
        cout << endl;
    }
}

void rezervirajSobu()
{
    string ime;
    string prezime;
    string datumRodjenja;
    string adresa;
    string brojTelefona;
    string nazivSobe;
    int brojNocenja;


    cout << "Unesite ime: ";
    getline(cin, ime);

    cout << "Unesite prezime: ";
    getline(cin, prezime);

    cout << "Unesite datum rodjenja: ";
    getline(cin, datumRodjenja);

    cout << "Unesite adresu prebivalista: ";
    getline(cin, adresa);

    cout << "Unesite broj telefona: ";
    getline(cin, brojTelefona);

    cout << "Dostupne sobe:" << endl;
    ifstream datotekaSobe("rooms.txt");
    string line;
    vector<Room> sobe;

    if (datotekaSobe.is_open())
    {
        while (getline(datotekaSobe, line))
        {
            if (!line.empty())
            {
                Room room;
                size_t found = line.find("Naziv sobe: ");
                if (found != string::npos) {
                    room.name = line.substr(found + 12);
                }

                getline(datotekaSobe, line);
                found = line.find("Tip sobe: ");
                if (found != string::npos) {
                    room.type = line.substr(found + 10);
                }

                getline(datotekaSobe, line);
                found = line.find("Broj kreveta: ");
                if (found != string::npos) {
                    istringstream iss(line.substr(found + 14));
                    iss >> room.bednumber;
                }

                getline(datotekaSobe, line);
                found = line.find("Najamnina: ");
                if (found != string::npos) {
                    istringstream iss(line.substr(found + 11));
                    iss >> room.rent;
                }

                sobe.push_back(room);
                room.slobodna=false;
            }

        }
        datotekaSobe.close();
    }
    else
    {
        cout << "Nije moguce otvoriti datoteku." << endl;
        return;
    }

    for (size_t i = 0; i < sobe.size(); i++)
    {
        cout << "Soba " << i + 1 << ":" << endl;
        cout << sobe[i].name << endl;
        cout << sobe[i].type << endl;
        cout << sobe[i].bednumber << endl;
        cout << sobe[i].rent << endl;
        cout << endl;
    }

    cout << "Unesite naziv sobe koju zelite: ";
    getline(cin, nazivSobe);

    cout << "Unesite broj nocenja: ";
    cin >> brojNocenja;
    cin.ignore();

    cout << "Odabrane usluge:" << endl;
    ifstream datotekaUsluge("services.txt");
    string linijaUsluge;
    vector<Usluga> usluge;

    if (datotekaUsluge.is_open())
    {
        while (getline(datotekaUsluge, linijaUsluge))
        {
            if (!linijaUsluge.empty())
            {
                Usluga usluga;
                usluga.naziv = linijaUsluge;

                getline(datotekaUsluge, linijaUsluge);
                istringstream iss(linijaUsluge);
                iss >> usluga.cijena;

                usluge.push_back(usluga);
            }
        }
        datotekaUsluge.close();
    }
    else
    {
        cout << "Nije moguce otvoriti datoteku." << endl;
        return;
    }

    for (size_t i = 0; i < usluge.size(); i++)
    {
        cout << "Usluga " << i + 1 << ":" << endl;
        cout << "Naziv usluge: " << usluge[i].naziv << endl;
        cout << "Cijena: " << usluge[i].cijena << " KM" << endl;
        cout << endl;
    }


    cout << "Unesite brojeve odabranih usluga (odvojene razmakom):";
    string odabraneUslugeStr;
    getline(cin, odabraneUslugeStr);

    istringstream iss(odabraneUslugeStr);
    int odabranaUslugaIndex;
    vector<Usluga> odabraneUsluge;

    while (iss >> odabranaUslugaIndex)
    {
        if (odabranaUslugaIndex >= 1 && odabranaUslugaIndex <= usluge.size())
        {
            odabraneUsluge.push_back(usluge[odabranaUslugaIndex - 1]);
        }
    }

    int ukupnaCijenaSobe = 0;
    for (size_t i = 0; i < sobe.size(); i++)
    {
        if (sobe[i].name == nazivSobe)
        {
            ukupnaCijenaSobe = sobe[i].rent;
            break;
        }
    }

    int ukupnaCijenaUsluga = 0;
    for (size_t i = 0; i < odabraneUsluge.size(); i++) {
        stringstream ss(odabraneUsluge[i].cijena);
        int cijena;
        ss >> cijena;
        ukupnaCijenaUsluga += cijena;
    }

int ukupnaCijena = (ukupnaCijenaSobe + ukupnaCijenaUsluga) * brojNocenja;
   // int ukupnaCijena = (ukupnaCijenaSobe * brojNocenja) + ukupnaCijenaUsluga;


    // Ispis rezervacije
    cout << "Rezervacija:" << endl;
    cout << "Ime: " << ime << endl;
    cout << "Prezime: " << prezime << endl;
    cout << "Datum rodjenja: " << datumRodjenja << endl;
    cout << "Adresa prebivalista: " << adresa << endl;
    cout << "Broj telefona: " << brojTelefona << endl;
    cout << "Odabrana soba: " << nazivSobe << endl;
    cout << "Broj nocenja: " << brojNocenja << endl;
    cout << "Odabrane usluge: " << endl;
    for (size_t i = 0; i < odabraneUsluge.size(); i++)
    {
        cout << "- " << odabraneUsluge[i].naziv << endl;
    }
    cout << "Ukupna cijena: " << ukupnaCijena << " KM" << endl;

    // Dodaj rezervaciju u datoteku
    ofstream datotekaRezervacija("reservations.txt", ios::app);
    if (datotekaRezervacija.is_open())
    {
        datotekaRezervacija << "Ime: " << ime << endl;
        datotekaRezervacija << "Prezime: " << prezime << endl;
        datotekaRezervacija << "Datum rodjenja: " << datumRodjenja << endl;
        datotekaRezervacija << "Adresa prebivalista: " << adresa << endl;
        datotekaRezervacija << "Broj telefona: " << brojTelefona << endl;
        datotekaRezervacija << "Odabrana soba: " << nazivSobe << endl;
        datotekaRezervacija << "Broj nocenja: " << brojNocenja << endl;
        datotekaRezervacija << "Odabrane usluge: " << endl;
        for (size_t i = 0; i < odabraneUsluge.size(); i++)
        {
            datotekaRezervacija << "- " << odabraneUsluge[i].naziv << endl;
        }
        datotekaRezervacija << "Ukupna cijena: " << ukupnaCijena << " KM" << endl;
        datotekaRezervacija << "----------------------------------------" << endl;
        datotekaRezervacija.close();
    }
    else
    {
        cout << "Nije moguce otvoriti datoteku." << endl;
        return;
    }
}
void ispisiRezervacijePoOsobi(const string& ime, const string& prezime)
{
    ifstream datotekaRezervacija("reservations.txt");
    string linija;
    bool pronadjeneRezervacije = false;
    int brojacLinija = 0;
    int brojacRezervacija = 0;

    if (datotekaRezervacija.is_open())
    {
        while (getline(datotekaRezervacija, linija))
        {
            if (linija.find("Ime: " + ime) != string::npos)
            {
                getline(datotekaRezervacija, linija); // preskacemo red s imenom
                if (linija.find("Prezime: " + prezime) != string::npos)
                {
                    pronadjeneRezervacije = true;
                    cout << "Rezervacije za osobu " << ime << " " << prezime << ":" << endl;
                    brojacRezervacija++;
                    brojacLinija = 0;
                }
            }
            else if (pronadjeneRezervacije && !linija.empty())
            {
                cout << linija << endl;
                brojacLinija++;
            }

            if (brojacLinija >= 9)
            {
                pronadjeneRezervacije = false;
                brojacLinija = 0;
            }
        }

        datotekaRezervacija.close();
    }
    else
    {
        cout << "Nije moguce otvoriti datoteku." << endl;
        return;
    }

    if (!pronadjeneRezervacije && brojacRezervacija == 0)
    {
        cout << "Nema rezervacija za osobu " << ime << " " << prezime << "." << endl;
    }
}

void room() {
    system("cls");
    int response;

    do {
        cout << endl << endl;
        cout << "|   --ROOM MANAGEMENT--   |" << endl;
        cout << "|                         |" << endl;
        cout << "|   1. Dostupne sobe      |" << endl;
        cout << "|   2. Specijalne usluge  |" << endl;
        cout << "|   3. Rezervacija sobe   |" << endl;
        cout << "|                         |" << endl;
        cout << "|                         |" << endl;
        cout << "|   0. PRETHODNI MENI     |" << endl;
        cout << "|                         |" << endl << endl;
        cout << "Unesite svoj izbor: ";
        cin >> response;
        cin.ignore();  // Ignoriraj preostali newline karakter

        switch (response) {
            case 1:
                displayRooms();
                break;
            case 2:
                prikaziUsluge();
                break;
            case 3:{
                rezervirajSobu();
                break;}
            case 4: {
                exitProgram();
                break;
            }
            default:
                cout << "\nIzbor ne postoji! \nPritisnite bilo koju tipku za nastavak...";
                // getch();
                // room();
                break;
        }

    } while (response != 0);
}

void addRoom()
{
    Room room;

    cout << "Unesite ime: ";
    getline(cin.ignore(), room.name);

    cout << "Unesite tip sobe: ";
    getline(cin, room.type);

    cout << "Unesite broj kreveta: ";
    cin >> room.bednumber;

    cout << "Unesite najamninu: ";
    cin >> room.rent;

    // Upisivanje sobe u datoteku
    ofstream file("rooms.txt", ios::app);
    file <<"Naziv sobe: "<< room.name << "\n";
    file << "Tip sobe: "<<room.type << "\n";
    file <<"Broj kreveta: "<< room.bednumber << "\n";
    file <<"Najamnina: "<< room.rent << "\n";
    file.close();

    cout << "Soba uspjesno dodana!" << endl;
}
void deleteRoom()
{
    string roomName;
    cout << "Unesite naziv sobe koju zelite obrisati: ";
    getline(cin.ignore(), roomName);

    // Otvaranje ulazne i izlazne datoteke
    ifstream inputFile("rooms.txt");
    ofstream outputFile("temp.txt");

    bool roomFound = false;
    string line;

    // Kopiranje svih soba iz ulazne datoteke u izlaznu datoteku, osim one koju ?elite izbrisati
    while (getline(inputFile, line))
    {
        if (line.find("Naziv sobe: " + roomName) != string::npos)
        {
            roomFound = true;
            // Preskacemo linije koje pripadaju sobi koju ?elimo izbrisati
            for (int i = 0; i < 3; i++)
                getline(inputFile, line);
        }
        else
        {
            // Kopiramo liniju u izlaznu datoteku
            outputFile << line << "\n";
        }
    }

    // Zatvaranje datoteka
    inputFile.close();
    outputFile.close();

    // Brisanje originalne datoteke i preimenovanje privremene datoteke
    if (roomFound)
    {
        if (remove("rooms.txt") != 0)
        {
            cout << "Greska u brisanju sobe." << endl;
            return;
        }
        if (rename("temp.txt", "rooms.txt") != 0)
        {
            cout << "Greska u preimenovanju datoteke." << endl;
            return;
        }

        cout << "Soba uspjesno obrisana!" << endl;
    }
    else
    {
        cout << "Soba nije pronadjena." << endl;
    }
}
int n = 10;
guest g[50];


void HTLmenu() {
    system("cls");
    int response;

    do {
        cout << endl
             << endl;
        cout << "|   ---THE MAJESTIC PEARL---  |" << endl;
        cout << "|                             |" << endl;
        cout << "|     1. SOBE - REZERVACIJA   |" << endl;
        cout << "|     2. PREGLED REZERVACIJA  |" << endl;
        cout << "|     3. RESTORAN             |" << endl;
        cout << "|     4. OSTAVITE KOMENTAR    |" << endl;
        cout << "|     5. OCIJENITE NAS        |" << endl;
        cout << "|     6. POGLEDAJTE KOMENTARE |" <<endl;
        cout << "|                             |" << endl;
        cout << "|     0. EXIT                 |" << endl;
        cout << "|                             |" << endl
             << endl;
        cout << "Unesite svoj izbor: ";
        cin >> response;

        switch (response) {
            case 1:{
                room();
                break;
            }
            case 2:{string ime;
                cin.ignore();
                cout << "Unesite Vase ime: ";
                getline(cin, ime);
                string prezime;
                cout << "Unesite prezime: ";
                getline(cin, prezime);
                ispisiRezervacijePoOsobi(ime, prezime);
                break;
            }


            case 3:{
                RSTRNTmenu();
                break;
            }
            case 4:{
                prikupiPovratneInformacije();
                break;
            }
            case 5:{
                ocijeniHotel();
                break;
            }
            case 6:{
                ispisiKomentare();
                break;
            }
            case 7:{
                pretraziSobe();
                break;
            }

            case 0:{
                //menu();
                exitProgram();
                break;
            }

            default: {
                cout << "\nNepostojeci izbor! \nPritisnite bilo koju tipku za nastavak...";
                //getch();
                //HTLmenu();
            }
        }
    } while (response!=0);
}
//PEPPERMILL Restaurant
void RSTRNTmenu() {
    system("cls");
    int response;

    do {
        cout << endl
             << endl;
        cout << "|      ---RESTORAN---     |" << endl;
        cout << "|                           |" << endl;
        cout << "|     1. MENI               |" << endl;
        cout << "|     2. NARUCI HRANU       |" << endl;
        cout << "|                           |" << endl;
        cout << "|     0. EXIT               |" << endl;
        cout << "|                           |" << endl
             << endl;
        cout << "Unesite svoj izbor: ";
        cin >> response;

        switch (response) {
            case 1:
                foodmenu();
                break;
            case 2:
                orderfood(g, n);
                break;
            case 0:
                HTLmenu();//ovo je da ga vraca na prethodni meni
                break;
            default: {
                cout << "\nNEVAZECI IZBOR! \nPritisnite bilo koju tipku za nastavak...";
                getch();
                RSTRNTmenu();
            }
        }
    } while (response <= 2);
}

void foodmenu() {
    system("cls");

    ifstream menuFile("menu.txt");
    if (!menuFile) {
        cout << "Nije moguce otvoriti datoteku." << endl;
        return;
    }

    string line;
    while (getline(menuFile, line)) {
        cout << line << endl;
    }
    menuFile.close();

    getch();
}
void orderfood(guest g[50], int n) {
    // Deklaracija i inicijalizacija polja hrane
    food f[15];
    strcpy(f[0].nm, "Burek");
    f[0].price = 6;
    f[0].code = 1;
    strcpy(f[1].nm, "Cevapi");
    f[1].price = 7;
    f[1].code = 2;
    strcpy(f[2].nm, "CLUB Sendvic");
    f[2].price = 5;
    f[2].code = 3;
    strcpy(f[3].nm, "Sarma");
    f[3].price = 7;
    f[3].code = 4;
    strcpy(f[4].nm, "Bosanski lonac");
    f[4].price = 5;
    f[4].code = 5;
    strcpy(f[5].nm, "Begova corba");
    f[5].price = 5;
    f[5].code = 6;
    strcpy(f[6].nm, "Karadordeva snicla");
    f[6].price = 3;
    f[6].code = 7;
    strcpy(f[7].nm, "Mijesano meso");
    f[7].price = 3;
    f[7].code = 8;
    strcpy(f[8].nm, "Sarajevski cevapcici");
    f[8].price = 15;
    f[8].code = 9;
    strcpy(f[9].nm, "Bosanski japrak");
    f[9].price = 13;
    f[9].code = 10;
    strcpy(f[10].nm, "Pecenje");
    f[10].price = 7;
    f[10].code = 11;
    strcpy(f[11].nm, "Tufahije");
    f[11].price = 3;
    f[11].code = 12;
    strcpy(f[12].nm, "Baklava");
    f[12].price = 13;
    f[12].code = 13;
    strcpy(f[13].nm, "Bosanska kahva");
    f[13].price = 5;
    f[13].code = 14;


    system("cls");
    int NoOfItems, code[15], bill = 0;
    char name[50], response[3];

    cout << endl << "Unesite ime: ";
    cin >> name;

    // Otvori datoteku i pro?itaj sadržaj menija
    ifstream menuFile("menu.txt");
    if (menuFile.is_open()) {
        string line;
        while (getline(menuFile, line)) {
            cout << line << endl;
        }
        menuFile.close();
    } else {
        cout << "Nije moguce otvoriti datoteku." << endl;
        return;
    }

    cout << endl << "Pozdrav " << name << "! Unesite koliko jela zelite poruciti: ";
    cin >> NoOfItems;

    cout << endl << endl << endl << "o-------------------------------------------------------------" << endl;
    for (int i = 0; i < NoOfItems; i++) {
        cout << "o Food-CODE: ";
        cin >> code[i];
        for (int j = 0; j < 15; j++) {
            if (code[i] == f[j].code) {
                cout << "     " << i + 1 << ". " << f[j].nm << "($" << f[j].price << ")" << endl;
                bill += f[j].price;
            }
        }
    }
    cout << "o-------------------------------------------------------------" << endl << endl << endl;

    cout << "USPJESNA NARUDZBA!" << endl << endl << endl;

    cin.ignore(); // da?isti ulazni bafer

    system("pause");
    system("cls");
}

void printReservations() {
    ifstream datotekaRezervacija("reservations.txt");
    if (datotekaRezervacija.is_open()) {
        string line;
        reservedRooms.push_back(line);//dodaje rezervisanu sobu u vektor
        while (getline(datotekaRezervacija, line)) {
            cout << line << endl;
        }
        datotekaRezervacija.close();
    }
    else {
        cout << "Nije moguce otvoriti datoteku." << endl;
    }
}

void printAdminMenu() {
    system("cls");
    int response;

    do {
        cout << endl
             << endl;
        cout << "|THE MAJESTIC PEARL - ADMIN |" << endl;
        cout << "|                           |" << endl;
        cout << "|     1. DODAVANJE SOBE     |" << endl;
        cout << "|     2. BRISANJE SOBE      |" << endl;
        cout << "|     3. PREGLED REZERVACIJA|" << endl;
        cout << "|                           |" << endl;
        cout << "|     0. EXIT               |" << endl;
        cout << "|                           |" << endl
             << endl;
        cout << "Unesite izbor: ";
        cin >> response;

        switch (response) {
            case 1:
                addRoom();
                break;
            case 2:{
                deleteRoom();
                break;
            }
            case 3:
                printReservations();
                break;
            case 0:
                HTLmenu();
                exit(0);
                break;
            default: {
                cout << "\nNepostojeci izbor! \nPritisnite bilo koju tipku za nastavak...";
                getch();
                HTLmenu();
            }
        }
    } while (response <= 5);
}


void Intro()
{
    setTextColor(12);
    Sleep(1000);
    system("cls");
    for (int i = 1; i <= 100; ++i)
    {
        Sleep(5);
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tDOBRODOSLI U";
        cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tLOADING " << i << "%";
        if (i == 100)
        {
            Sleep(1000);
        }
    }
    system("cls");
    cout<<"\n\n\n\n\n\n\n";
    cout << setw(80) << " =========================================== \n";
    cout << setw(80) << "|                                           |\n";
    cout << setw(80) << "|      -------------------------------      |\n";
    cout << setw(80) << "|      SISTEM ZA UPRAVLJANJE HOTELIMA       |\n";
    cout << setw(80) << "|      -------------------------------      |\n";
    cout << setw(80) << "|                                           |\n";
    cout << setw(80) << "|                                           |\n";
    cout << setw(80) << "|                                           |\n";
    cout << setw(80) << "  ===========================================\n\n\n";
    for(int i=0;i<80;i++)
        cout << "-";
    time_t t = time(NULL);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%c", localtime(&t));
    cout <<"  Datum i vrijeme: " << buffer << endl;
    for(int i=0;i<120;i++)
        cout <<"-";
    cout <<" \n Pritisnite bilo koju tipku za nastavak:";
    getchar();
    Sleep(1000);
    system("cls");
    setTextColor(7);
}

void drawLine(char symbol, int length) {
    for (int i = 0; i < length; i++) {
        cout << symbol;
    }
    cout << endl;
}

void centerText(const string& text) {
    int width = 80;
    int padding = (width - text.length()) / 2;
    cout << setw(padding + text.length()) << text << endl;
}

void registerUser() {
    string username, password;
    bool usernameExists = false;

    do {
        cout << "Unesite korisnicko ime (x za povratak na prethodni meni): ";
        cin >> username;

        if (username == "x") {
            return; // Povratak na prethodni meni
        }

        ifstream file("users.txt");
        string line;
        while (getline(file, line)) {
            string storedUsername, storedPassword;
            istringstream iss(line);
            iss >> storedUsername >> storedPassword;
            if (username == storedUsername) {
                usernameExists = true;
                break;
            }
        }
        file.close();

        ifstream adminFile("admins.txt");
        while (getline(adminFile, line)) {
            string adminUsername, adminPassword;
            istringstream iss(line);
            iss >> adminUsername >> adminPassword;
            if (username == adminUsername) {
                usernameExists = true;
                break;
            }
        }
        adminFile.close();

        if (usernameExists) {
            cout << "\nKorisnik sa istim korisnickim imenom vec postoji ili je rezervirano za administratora. \nMolimo, odaberite drugo korisnicko ime." << endl;
            usernameExists = false;
            system("pause");
        } else {
            cout << "Unesite sifru: ";
            char ch;
            password = "";
            while ((ch = _getch()) != '\r') {
                if (ch == '\b') {
                    if (!password.empty()) {
                        password.erase(password.size() - 1);
                        cout << "\b \b";
                    }
                } else {
                    password.push_back(ch);
                    cout << '*';
                }
            }

            ofstream file("users.txt", ios::app);
            file << username << " " << password << endl;
            file.close();
            cout << endl;
            drawLine('-', 80);
            cout << "\nRegistracija uspjesna!" << endl;
            system("pause");
            break;
        }
    } while (true);
}
bool userLogin() {
    string username, password;

    do {
        cout << "Unesite korisnicko ime (x za povratak na prethodni meni): ";
        cin >> username;

        if (username == "x") {
            return false; // Povratak na prethodni meni
        }

        ifstream file("users.txt");
        string line;
        while (getline(file, line)) {
            string storedUsername, storedPassword;
            istringstream iss(line);
            iss >> storedUsername >> storedPassword;
            if (username == storedUsername) {
                file.close();

                cout << "Unesite sifru: ";
                char ch;
                password = "";
                while ((ch = _getch()) != '\r') {
                    if (ch == '\b') {
                        if (!password.empty()) {
                            password.erase(password.size() - 1);
                            cout << "\b \b";
                        }
                    } else {
                        password.push_back(ch);
                        cout << '*';
                    }
                }
                cout << endl;

                if (password == storedPassword) {
                    return true; // Ispravno korisnicko ime i L?ifra
                } else {
                    cout << "\nNeispravna sifra. Molimo, pokusajte ponovo." << endl;
                    system("pause");
                    break;
                }
            }
        }
        file.close();

        cout << "\nKorisnik sa unijetim korisnickim imenom ne postoji. Molimo, pokusajte ponovo." << endl;
        system("pause");
    } while (true);
}

bool adminLogin() {
    string username, password;
    bool usernameMatch = false;

    do {
        cout << "Unesite korisnicko ime (admin) (x za povratak na prethodni meni): ";
        cin >> username;

        if (username == "x") {
            cout << "Povratak na prethodni meni." << endl;
            return false;
        }

        cout << "Unesite sifru: ";
        char ch;
        password = "";
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!password.empty()) {
                    password.erase(password.size() - 1);
                    cout << "\b \b";
                }
            } else {
                password.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;

        ifstream file("admins.txt");
        if (!file) {
            cout << "Datoteka 'admins.txt' se ne moze otvoriti." << endl;
            system("pause");
            return false;
        }

        string line;
        while (getline(file, line)) {
            string storedUsername, storedPassword;
            istringstream iss(line);
            iss >> storedUsername >> storedPassword;
            if (username == storedUsername && password == storedPassword) {
                file.close();
                return true;
            } else if (username == storedUsername) {
                usernameMatch = true;
                break;
            }
        }
        file.close();

        if (!usernameMatch) {
            cout << "\nKorisnik sa unijetim korisnickim imenom ne postoji. Molimo, pokusajte ponovo." << endl;
            system("pause");
        } else {
            cout << "\nNeispravna sifra. Molimo, pokusajte ponovo." << endl;
            system("pause");
        }

    } while(!usernameMatch);

    return false;
}

void loginSystem() {
    int choice;
    setTextColor(12); // Postavljanje boje teksta na crvenu

    do {
        system("cls"); // Brisanje ekrana
        cout<<"\n\n\n\n\n\n\n";
        cout<<"\t\t\t\t\t -------------------------------------"<<"\n";
        cout <<"\t\t\t\t\t        DOBRODOSLI U SISTEM" <<"\n";
        cout<<"\t\t\t\t\t -------------------------------------"<<"\n";
        cout << "\t\t\t\t\t1. Registracija" << endl;
        cout << "\t\t\t\t\t2. Obican login" << endl;
        cout << "\t\t\t\t\t3. Login kao administrator" << endl;
        cout << "\t\t\t\t\t4. Exit" << endl;
        drawLine('-', 120);
        cout << "\t\t\t\t\tIzaberite opciju: ";
        cin >> choice;

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            bool isLoggedIn = userLogin();
            if (isLoggedIn) {
                cout << "\nUspjesno ste se ulogovali kao korisnik." << endl;
                system("pause");
                HTLmenu();
                break;
            }
        } else if (choice == 3) {
            bool isLoggedIn = adminLogin();
            if (isLoggedIn) {
                cout << "\nUspjesno ste se ulogovali kao administrator." << endl;
                system("pause");
                printAdminMenu();
                break;

            }
        } else if(choice == 4) {
            exitProgram();
        }else {
            cout << "\nNepostojeca opcija." << endl;
            system("pause");
        }
    }while (true);

    setTextColor(7);
}

void pretraziSobe() {

    Room soba;
    ifstream file("rooms.txt");
    if (!file.is_open()) {
        cout << "Nije moguce otvoriti datoteku." << endl;
        return;
    }

    int brojKreveta;
    cout << "Unesite broj kreveta: ";
    cin >> brojKreveta;

    bool pronadjenaSoba = false;  // Dodana nova varijabla

    while (file >> soba.name >> soba.bednumber >> soba.rent >> soba.slobodna) {
        if (soba.bednumber == brojKreveta) {
            cout << "Naziv sobe: " << soba.name << endl;
            cout << "Cijena: " << soba.rent << endl;
            cout << "Dostupnost: " << (soba.slobodna ? "Dostupna" : "Nedostupna") << endl;
            cout << endl;
            pronadjenaSoba = true;  // Postavljamo vrijednost na true ako pronademo sobu
        }
    }

    if (!pronadjenaSoba) {
        cout << "Nema dostupnih soba s tim brojem kreveta." << endl;
    }

    file.close();  // Zatvaramo datoteku
}


void prikupiPovratneInformacije() {

    string komentar;
    cout << "Molimo unesite svoj komentar: ";
    cin.ignore();
    getline(cin, komentar);

    // Otvorite datoteku za dodavanje povratnih informacija
    ofstream file("feedback.txt", ios::app);
    if (!file.is_open()) {
        cout << "Nije moguce otvoriti datoteku za povratne informacije." << endl;
        return;
    }

    // Spremite korisnicki komentar u datoteku
    file << komentar << endl;

    // Zatvorite datoteku
    file.close();

    cout << "Hvala na komentaru!" << endl;

}

void ocijeniHotel() {
    int ocjena;
    cout << "Unesite ocjenu hotela (1-5): ";
    cin >> ocjena;

    // Provjerite je li unesena ispravna ocjena
    if (ocjena < 1 || ocjena > 5) {
        cout << "Neispravna ocjena." << endl;
        return;
    }



    // Otvorite datoteku u re?imu dodavanja (append)
    ofstream file("hotel_ratings.txt", ios::app);
    if (!file.is_open()) {
        cout << "Nije moguce otvoriti datoteku." << endl;
        return;
    }

    // Upisujte informacije u datoteku
    file << ocjena << endl;

    // Zatvorite datoteku
    file.close();

    cout << "Hvala na ocjenjivanju hotela!" << endl;
}

double izracunajProsjek() {
    ifstream file("hotel_ratings.txt");
    if (!file.is_open()) {
        cout << "Nije moguce otvoriti datoteku." << endl;
        return 0.0;
    }

    int ocjena;
    int ukupnaOcjena=0;
    int brojOcjena=0;

    // Citajte ocjene iz datoteke dok ne dodete do kraja datoteke
    while (file >> ocjena) {
        ukupnaOcjena = ukupnaOcjena+ocjena;
        brojOcjena++;
    }
    file.close();

    // Provjerite je li broj ocjena veci od 0 prije izracunavanja prosjeka
    if (brojOcjena == 0) {
        return 0.0;
    }

    // Izracunajte prosjek ocjena hotela
    double prosjek = double(ukupnaOcjena) / brojOcjena;

    // Zatvorite datoteku
    file.close();

    return prosjek;
}

void ispisiKomentare() {
    ifstream file("feedback.txt");
    if (!file.is_open()) {
        cout << "Nije moguce otvoriti datoteku s povratnim informacijama." << endl;
        return;
    }

    string komentar;
    cout << "Povratne informacije korisnika:" << endl;
    while (getline(file, komentar)) {
        cout << "- " << komentar << endl;
    }

    file.close();
}



int main(){
    Intro();
    banner();
    loginSystem();




    system("pause");
    return 0;

}

