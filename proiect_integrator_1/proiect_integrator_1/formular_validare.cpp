#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

int verifLitere(char s[]);
int verifCifre(char s[]);
int verifCnp(char cnpDat[]);
int verifEmail(char s[]);


void main() {
	char nume[20], prenume[30], cnp[14], tel[11], email[40];
	int i;

	// Citim si validam

	cout << "Bun venit! Va rugam introduceti datele necesare: " << endl;
	
	cout << "Nume: ";
	cin.getline(nume, 20);
	for (i = 0; i < strlen(nume); i++)
		nume[i] = toupper(nume[i]);
	if (verifLitere(nume) == 0) {
		exit(1);
	}

	cout << endl << "Prenume: ";
	cin.getline(prenume, 30);
	prenume[0] = toupper(prenume[0]);
	for (i = 1; i < strlen(prenume); i++)
		if (prenume[i] == ' ')
			prenume[i + 1] = toupper(prenume[i + 1]);
	if (verifLitere(nume) == 0) {
		exit(1);
	}

	cout << endl << "C.N.P: ";
	cin >> cnp;
	if (verifCifre(cnp) == 0)
		exit(1);
	if (verifCnp(cnp) == 0)
		exit(1);

	cout << endl << "Telefon: ";
	cin >> tel;
	if (verifCifre(tel) == 0)
		exit(1);
	if (strlen(tel) > 10)
		exit(1);

	
	cout << endl << "Email: ";
	cin >> email;
	if (verifEmail(email) == 0)
		exit(1);

	// Afisam

	cout << "Multumim!" << endl << endl;
	cout << "Numele este: " << nume << endl;
	cout << "Prenumele este: " << prenume << endl;
	cout << "CNP-ul este: " << cnp << endl;

	cout << "Data de nastere (Zi, Luna, An) este: " 
		<< cnp[5] << cnp[6] << ", " << cnp[3] << cnp[4] << ", "
		<< "19" << cnp[1] << cnp[2] << endl;
	cout << "Numarul de telefon este: " << tel << endl;
	cout << "Adresa de Email este: " << email << endl;

	// Scriem in fisierul csv
	fstream utilizatori;
	utilizatori.open("utilizatori.csv", ios:: app);
	utilizatori << nume << ", " << prenume << ", " << cnp << ", "
		<< tel << ", " << email << "." << endl;


	system("pause");
}

//Verificare ca toate caracterele sunt litere (pentru nume!)

int verifLitere(char s[]) {
	unsigned int i;
	for (i = 0; i < strlen(s); i++) {
		if (!isalpha(s[i]) && s[i] != ' ') // Daca nu este litera sau spatiu
			return 0;
	}
	return 1;
}


// verificare ca toate caracterele sunt cifre
int verifCifre(char s[]) {
	unsigned int i;
	for (i = 0; i < strlen(s); i++) {
		if (!isdigit(s[i])) // Daca nu este numar
			return 0;
	}
	return 1;
}

//verificare formatare CNP
int verifCnp(char cnpDat[]) {
	int i, cheie[] = { 2, 7, 9, 1, 4, 6, 3, 5, 8, 2, 7, 9 };
	int cnp[13];
	int p[13], suma, cControl;
	// Transformam sirul char in sir int
	for (i = 0; i < 13; i++)
		cnp[i] = cnpDat[i] - '0';
	suma = 0;
	for (i = 0; i < 12; i++) {
		p[i] = cnp[i] * cheie[i];
		suma += p[i];
	}
	cControl = suma % 11;
	if (cControl == 10)
		cControl = 1;
	if (cnp[12] == cControl)
		return 1;
	else
		return 0;
}


// Verificare email
int verifEmail(char s[]) {
	unsigned int i;

	//Verificam daca @ apare o singura data
	int contor = 0;
	for (i = 0; i < strlen(s); i++) {
		if (s[i] == '@')
			contor++;
	}
	if (contor != 1)
		return 0;

	//Verificam daca @ nu este cumva primul caracter
	if (s[0] == '@')
		return 0;

	//Verificam daca exista puncte dupa @
	if (s[strlen(s)] == '.')
		return 0;
	contor = 0;
	for (i = strlen(s); i > 0; i--) {
		if (s[i] == '.')
			contor++;
		if (s[i] == '@')
			break;
	}
	if (contor == 0) // Daca nu avem puncte dupa '@'
		return 0;
	return 1;
}