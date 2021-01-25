#include <iostream>
 
using namespace std;
 
// Funkcja rysuje planszę gry
 
void plansza(char t[], int n)
{
    for (int i = 1; i <= n*n; i++)
    {
        cout << " " << t[i] << " ";
        if (i % n)
            cout << "|";
        else if (i != n*n) {
            cout << "\n";
            for(int i = 1; i < n; i++) {
                cout << "---+";
            }
            cout << "---\n";
        }
        else cout << endl;
    }
}
 
// Funkcja zwraca true, jeśli nastąpiła wygrana danego zawodnika
 
bool wygrana(char t[], char g, int n)
{
    static int pktO, pktX;
    int i;
 
    bool przekatne1, przekatne2;
    przekatne1 = true;
    przekatne2 = true;
    bool *pion = new bool [n];
    bool *poziom = new bool [n];
 
    for(int i = 0; i < n; i++) {
        pion[i] = true;
        poziom[i] = true;
    }
 
 
    //przekatne
    char temp = t[1];
    for(int i = 1; i <= n * n; i += (n + 1)) {
        if(temp == ' ') {
            przekatne1 = false;
            break;
        }
        if(temp != t[i]) {
            przekatne1 = false;
        }
    }
 
    temp = t[n];
    for(int i = n; i < n * n; i += (n - 1)) {
        if(temp == ' ') {
            przekatne2 = false;
            break;
        }
        if(temp != t[i]) {
            przekatne2 = false;
        }
    }
 
    //pion
    for(int i = 1; i <= n; i++) {
        temp = t[i];
        if(temp == ' ') {
            pion[i - 1] = false;
            continue;
        }
 
        for(int j = i; j <= n*n; j += n) {
            if(temp != t[j]) {
                pion[i - 1] = false;
            }
        }
    }
 
    //poziom
    for(int i = 1; i <= n*n; i += n) {
        temp = t[i];
 
        for(int j = 0; j < n; j++) {
            if(temp != t[i + j] || temp == ' ') {
                poziom[i / n] = false;
            }
        }
    }
 
    bool poziome = false, pionowe = false;
 
    for(int i = 0; i < n; i++) {
        if(pion[i] == true) {
            pionowe = true;
        }
 
        if(poziom[i] == true) {
            poziome = true;
        }
    }
 
 
    if (przekatne1 || przekatne2 || pionowe || poziome)
    {
        plansza(t, n);
        if(g == 'O') {
            cout << "\nGRACZ " << 'X' << " Wygrywa\n\n";
            pktX++;
        }
        else if(g == 'X') {
            cout << "\nGRACZ " << 'O' << " Wygrywa\n\n";
            pktO++;
        }
 
        cout << "Gracz kolko: " << pktO << " punktow, gracz krzyzyk: " << pktX << " punktow\n";
        return true;
    }
    return false;
}
 
// Funkcja zwraca true, jeśli na planszy nie ma już żadnego wolnego pola na ruch.
 
bool remis(char t[], int n)
{
    for (int i = 1; i <= n*n; i++)
        if (t[i] == ' ') return false;
    plansza(t, n);
    cout << "\nRemis \n\n";
    return true;
}
 
// Funkcja umożliwia ruch gracza po ruchu następuje zamiana gracza
 
void ruch(char t[], char& gracz, int n)
{
    int r;
 
    plansza(t, n);
    cout << "\nGRACZ " << gracz << " : Twoj ruch : ";
    cin >> r;
    cout << "-----------------------\n\n";
    if ((r >= 1) && (r <= n*n) && (t[r] == ' ')) t[r] = gracz;
    gracz = (gracz == 'O') ? 'X' : 'O';
}
// Funkcja odpowiada za wyswietlaie napisu i umożliwia rozpoczecie nowej gry
 
int main()
{
    cout << "Podaj rozmiar planszy, musi byc wiekszy lub rowny 3: ";
    int n;
    cin >> n;
    if(n < 3) {
        cout << "To jest mniej niz 3 :(";
        return 1;
    }
    char g, w;
    char *p = new char [n * n + 1];
 
    do
    {
        cout << "Gra w Kolko i Krzyzyk. Wpisz numer pola od 1 do " << n*n <<  " (1 - lewy gorny rog, " << n*n << " - prawy dolny).\n";
        for (int i = 1; i <= n * n; i++) p[i] = ' ';
        g = 'O';
        while (!wygrana(p, g, n) && !wygrana(p, g, n) && !remis(p, n)) ruch(p, g, n);
        cout << "Rewanz? (O = OK) : ";
        cin >> w;
        cout << "\n\n\n";
    } while ((w == 'O') || (w == 'o'));
}