#include <iostream>
#include<math.h>
using namespace std;
//Se considera un sistem algebric neliniar. A se calcula cu ajutorul metodei lui Newton. Se considera un xi' (i ia valori de la 1 la n) 
//initial citit de la tastatura pentru fiecare ecuatie.

int coef[10][10], t_liber[10], put[10][10], j; //coef retine coeficientii, t_liber retine termenii liberi, put retine puterile , j contor

int functii[10][10], x_prim[10];//adj retine adjuncta, x_prim retine xi' citite de la tastatura, functii retine functiile calculate cu ajutorul xi'

double adj[10][10], inv[10][10], c[10][10], solutii[10];//inv retine inversa, c este utilizata pt inmultiri, solutii retine solutiile


void ec(int v[10], int n, int i) //subprogram pentru citirea ecuatiei
{	/*folosim matricea coef pentru a retine coeficientul, respectiv matricea put pentru a retine puterea necunoscutei x[j+1] din ecuatia
	cu numarul i+1*/
	for (j = 0; j < n; j++)
	{
		cout << "\tDati coeficientul pentru necunoscuta x" << j + 1 << " din ecuatia cu numarul " << i + 1 << ": ";
		do cin >> coef[i][j]; while (coef[i][j] / 10); //se citeste coeficientul necunoscutei j+1

		if (coef[i][j]) { //daca coeficientul este nenul
			do {
				cout << "\tIntroduceti puterea (diferita de 0) pentru necunoscuta x" << j + 1 << " din ecuatia cu numarul " << i + 1 << ": ";
				cin >> put[i][j];
			} while (put[i][j] == 0); //conditie pentru introducerea puterii nenule
		} //se citeste puterea necunoscutei doar daca coeficientul sau este diferit de 0
		else put[i][j] = rand() % 5 + 1; //discutie pentru introducerea unei valori aleatoare
	}

	cout << "\tIntroduceti termenul liber pentru ecuatia cu numarul " << i + 1 << ": "; cin >> t_liber[i]; //se citeste termenul liber al ecuatiei i+1
	cout << endl;
}

void afisare_sistem(int n) //subprogram pentru afisarea sistemului
{
	int i, j, coef_zero; //utilizam variabila coef_zero pt a retine pt fiecare ecuatie numarul necunoscutei al carei coeficient este nul

	for (i = 0; i < n; i++) //se considera fiecare ecuatie
	{
		coef_zero = -1; //se initializeaza variabila pt fiecare ecuatie cu -1
		cout << "\t{"; //la inceputul fiecarei ecuatie se afiseaza {

		if (coef[i][0]) //daca primul coeficient este nenul 
		{
			if (coef[i][0] == -1) cout << "-"; //daca este egal cu -1 se afiseaza -
			if (coef[i][0] != 1 && coef[i][0] != -1) cout << coef[i][0]; //daca este diferit de -1 si 1 se scrie
			cout << "x1"; //se afiseaza coeficientul si necunoscuta

			if (put[i][0] != 1) { //daca puterea necunoscutei este diferita de 1
				cout << "^"; //se afiseaza ^ (pentru ilustrarea puterii)
				if (put[i][0] < 0) cout << "(" << put[i][0] << ")";
				else cout << put[i][0]; //se afiseaza puterea (discutie dupa semn)
			}
			else coef_zero = 0; //daca primul coeficient este 0, coef_zero ia pozitia primului coeficient, si anume 0
		}

		for (j = 1; j < n; j++) //se discuta toate necunoscutele ramase din ecuatia cu numarul i+1
		{
			if (coef_zero != -1 || coef_zero && coef[i][j - 1]) coef_zero = j - 1; /*daca coef_zero este neinitializat (-1) sau este nenul SI coeficientul anterior
																				   este nenul, coef_zero devine pozitia anterioara pozitiei curente*/
			if (coef[i][j] > 0)  //daca coeficientul curent este mai mare ca 0 si cel anterior este diferit de 0 se va afisa +
			{
				if (coef[i][j - 1] != 0 || j - 1 == coef_zero) cout << "+"; //daca coeficientul anterior este diferit de 0 si coef_zero coincide cu pozitia j-1 se afiseaza +
			}

			if (coef[i][j]) //daca coeficientul curent este diferit de 0 (discutie dupa valoare - daca este diferit de 1 si daca e 1)
			{
				if (coef[i][j] == -1) cout << "-"; //daca este -1 se afiseaza -
				if (coef[i][j] != 1 && coef[i][j] != -1) cout << coef[i][j]; //daca este diferit de -1 si 1 se afiseaza coeficientul si necunoscuta
				cout << "x" << j + 1; //daca este 1 se afiseaza numai necunoscuta 
			}

			if (coef[i][j]) //daca coeficientul este diferit de 0 se discuta puterea
			{
				if (put[i][j] != 1) //daca puterea este diferita de 1 se afiseaza analog primului termen al ecuatiei
				{
					cout << "^";
					if (put[i][j] < 0) cout << "(" << put[i][j] << ")";
					else cout << put[i][j];
				}
			}
		}

		cout << "=" << t_liber[i] << endl; //se egaleaza ecuatia cu termenul liber
	}
}

void inmultire_matrice(double a[10][10], int b[10][10], int lin_a, int col_b) //subprogram pt inmultirea matricilor
{
	int lin = 0, col = 0;//contori pentru noua matrice

	for (int i = 0; i < lin_a; i++)
		for (int j = 0; j < col_b; j++)
			c[i][j] = 0; //se initializeaza matricea cu 0

	for (int i1 = 0; i1 < lin_a; i1++)
	{
		for (int j2 = 0; j2 < lin_a; j2++) {
			for (int j1 = 0, i2 = 0; j1 < lin_a, i2 < col_b; j1++, i2++)
			{
				c[lin][col] += a[i1][j1] * b[i2][j2]; //se umple matricea corespunzator formulei matematice

			}

			col++;
		}
		col = 0;
		lin++;
	}
}




void Coeficient(double mat[10][10], double alt_mat[10][10], int lin, int col, int n) { //subprogram pt creerea unei matrici auxiliare formata din liniile si coloanele ramase
	int i, j, l = 0, c = 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i != lin && j != col) {
				alt_mat[l][c++] = mat[i][j];
				if (c == n - 1)
				{
					c = 0;
					l++;
				}
			}
		}
	}
}

double Determinant(double mat[][10], int n) { //subprogram pentru calcularea determinantului de ordin n
	int i, semn = 1; //variabila pt calculul semnului(variaza)
	double det = 0;
	double coef[10][10];
	if (n == 1) return mat[0][0]; //daca ordinul e 1, se returneaza elementul de pe prima linie si prima coloana
	for (i = 0; i<n; i++) {
		Coeficient(mat, coef, 0, i, n); //altfel se calculeaza o matrice auxiliara  

		det = det + semn*mat[0][i] * Determinant(coef, n - 1); //determinantul ramas este determinantul matricei auxiliare adunat cu det anterior; procesul se tot repeta
		semn = -semn; //alterneaza semnul
	}
	return det; //se returneaza determinatul
}


void adjuncta(double a[10][10], double adj[10][10], int n) //se creeaza matricea adjuncta
{
	if (n == 1)
	{
		adj[0][0] = 1;
		return;
	}

	int semn = 1;
	double temp[10][10];

	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
		{
			Coeficient(a, temp, i, j, n); //se creeaza o matrice auxiliara

			semn = ((i + j) % 2 == 0) ? 1 : -1; //se creeaza semnul

			adj[j][i] = (semn)*(Determinant(temp, n - 1)); //se atribuie corespunzator elementul adjunctei

		}
	}
}

bool inversa(double a[10][10], double inv[10][10], int n)
{
	double det = Determinant(a, n);
	if (det == 0) //daca determinantul este nul matricea este singulara si nu i se poate calcula inversa
	{
		cout << "\tMatrice singulara. Cum determinantul este nul, nu se poate calcula inversa.";
		return false;
	}

	double adj[10][10];
	adjuncta(a, adj, n); //altfel se creeaza adjuncta

	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++)
			inv[i][j] = adj[i][j] / det; //inversa este adjuncta/det

	return true;
}

int main()
{
	cout << "\t\t\t\tMETODA LUI NEWTON PENTRU SISTEME DE ECUATII NELINIARE\n\n\n\n";
	int i, x[10], n;
	int transp[10][10];
	double deriv, h, Jacobian[10][10], det;

	do { cout << "\tDati numarul de ecuatii si numarul de necunoscute: "; cin >> n; } while (n < 2 || n > 10);
	/*se introduce numarul de ecuatii si necunoscute (mai mari sau egale cu 2 si mai mici sau egale cu 10, deoarece determinantul nu
	va putea fi calculat sau va avea o valoare foarte mare)*/

	cout << "\n\tEcuatia are " << n << " solutii, acestea fiind ";
	for (i = 0; i < n - 1; i++) cout << "x" << i + 1 << ",";
	cout << "x" << n << ".\n\n"; //se afiseaza solutiile existente
	cout << endl;

	for (i = 0; i < n; i++) {
		cout << "\tDati ecuatia cu numarul " << i + 1 << ".\n"; ec(x, n, i);
		cout << endl;
	} //se citesc coeficientii, puterile si termenul liber din ecuatia cu numarul de ordine i+1


	cout << "\n\tSistemul este: \n";
	afisare_sistem(n); //se afiseaza sistemul 
	cout << "\n\n";

	do
	{
		cout << "\tIntroduceti eroarea aproximativa apartinand intervalului (0,1): "; cin >> h;
	} while (h <= 0 || h >= 1); //se introduce valoarea aproximativa, fiind un numar foarte mic
	cout << endl;

	for (i = 0; i < n; i++)
	{
		cout << "\tDati valoarea x" << i + 1 << "': "; //se citesc valorile xi initiale
		cin >> x_prim[i];
	}
	cout << endl;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			deriv = coef[i][j] * pow(1 + h, put[i][j]) - coef[i][j] * pow(1, put[i][j]); //se calculeaza derivata partiala conform formulei
			deriv /= h;
			Jacobian[i][j] = deriv; //matricea Jacobian retine, asemenea numelui, fiecare derivata partiala a fiecarei linii, respectiv coloane
		}

	cout << "\tJacobianul matricei introduse de la tastatura este: \n";
	for (i = 0; i < n; i++)
	{
		cout << "\t";
		for (j = 0; j < n; j++)
		{
			if (Jacobian[i][j]) //discutie dupa element al Jacobianului
			{
				if (put[i][j] - 1) //discutie dupa puterea ramasa dupa calculul derivatei partiale (nenula)
					if (put[i][j] - 1 != 1) //discutie dupa puterea ramasa dupa calculul derivatei partiale (diferita de 1)
						cout << Jacobian[i][j] << "x" << j + 1 << "^" << put[i][j] - 1; //se scrie ce ramane dupa calculul derivatei partiale
					else cout << Jacobian[i][j] << "x" << j + 1; //daca puterea-1 este 1 nu se mai scrie
				else cout << Jacobian[i][j]; //daca puterea ramasa este 0 se scrie doar valoarea ramasa a Jacobianului
			}
			else cout << "0"; //daca Jacobian[i][j]=0 se scrie 0
			cout << "     ";
		}
		cout << endl;
	}


	det = Determinant(Jacobian, n); //determinantul matricei este retinut in variabila det
	cout << "\tsi valoarea determinantului sau este " << det << ".\n\n"; //se scrie determinantul

	if (inversa(Jacobian, inv, n)) //daca Jacobianul este nenul
	{
		for (i = 0; i<n; i++)
		{
			functii[i][0] = -t_liber[i];
			for (j = 0; j<n; j++)
			{
				functii[i][0] = functii[i][0] + coef[i][j] * pow(x_prim[j], put[i][j]); //se calculeaza functiile f1,f2,..,fn pentru inmultirea viitoare
			}
		}

		adjuncta(Jacobian, adj, n);//se apeleaza adjuncta

		cout << "\n\tAdjuncta Jacobianului este :\n";
		for (i = 0; i < n; i++) //se afiseaza adjuncta
		{
			cout << "\t";
			for (j = 0; j < n; j++)
			{
				cout << adj[i][j] << " ";
				cout << "     ";
			}

			cout << endl;
		}

		cout << "\n\tInversa este :\n"; //se afiseaza inversa

		for (int i = 0; i < n; i++)
		{
			cout << "\t";
			for (int j = 0; j < n; j++)
			{
				cout << inv[i][j] << " ";
				cout << "     ";
			}

			cout << endl;
		}

		inmultire_matrice(inv, functii, n, n);//se fac inmultirile

		for (i = 0; i < n; i++)
		{
			solutii[i] = x_prim[i] - c[i][0]; //se retin solutiile in vectorul solutii
		}

		cout << "\n\tSolutiile sunt: \n ";//se afiseaza solutiile
		for (i = 0; i < n; i++)
		{
			cout << "\tx" << i + 1 << "= " << solutii[i] << endl;

		}
	}

	else cout << "\n\tDeterminantul fiind nul, nu se poate calcula inversa, implicit nu se pot calcula nici solutiile.";
	cout << endl;
	system("pause");
}
