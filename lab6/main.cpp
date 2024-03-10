#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "gauss.h"

const int N = 50;

void HilbertMatrix(int n, double A[][N])
{
	double w = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{	
			A[i][j] = 1.0/(i + j + 1);
		}
	}
}
void HilbertMatrixw(int n, double **A)
{
	double w = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A[i][j] = 1.0 / (i + j + 1);
		}
	}
}
void DisplayMatrix(int n, double A[][N])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%lf\t", A[i][j]);
		}
		printf("\n");
	}
}
void DisplayMatrixw(int n, double **A)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%lf\t", A[i][j]);
		}
		printf("\n");
	}
}

void ComputeVec(int n, double A[][N], double v[])
{
	double w=0;
	for (int i = 0; i < n; i++)
	{	
		v[i]=0;
		for (int j = 0; j < n; j++)
		{
			v[i]=v[i]+A[i][j];
		}
	}
}
void ComputeVecw(int n, double **A, double *v)
{
	double w = 0;
	for (int i = 0; i < n; i++)
	{
		v[i] = 0;
		for (int j = 0; j < n; j++)
		{
			v[i] = v[i] + A[i][j];
		}
	}
}

void DisplayVec(int n, double v[])
{
	for (int j = 0; j < n; j++)
	{
		printf("%lf\n", v[j]);
	}
}
void DisplayVecw(int n, double *v)
{
	for (int j = 0; j < n; j++)
	{
		printf("%lf\n", v[j]);
	}
}

void gaussw(int n, double **a, double *b, double *x)	//gauss dla zaalokowanych wartosci 
{
	int i, j, k;
	double s;
	double wsp;

	//eliminacja

	// wiersz przy pomocy którego eliminujemy elementy
	for (i = 0; i < n - 1; i++)
	{
		// wersz którego elementy eliminujemy
		for (k = i + 1; k < n; k++)
		{
			wsp = a[k][i] / a[i][i];
			// odejmowanie elementów wiersza "i" od wiersza "k"
			for (j = i + 1; j < n; j++)
				a[k][j] -= a[i][j] * wsp;

			// odejmowanie prawych stron
			b[k] -= b[i] * wsp;
		}
	}
	//rozwiazanie ukladu
	x[n - 1] = b[n - 1] / a[n - 1][n - 1];
	for (i = n - 1; i >= 0; i--)
	{
		s = 0.0;
		for (j = i + 1; j < n; j++)
			s += a[i][j] * x[j];

		x[i] = (b[i] - s) / a[i][i];
	}
}
int main()
{
	int k = 1;
	printf("1 - rozwiazanie metoda Gaussa\n");
	printf("2 - obliczane macierzy trojkatnej oraz wyznacznika\n");
	printf("3 - rozwiazanie ukladu dla wczytanej macierzy (dynamiczna alokacja)\n");
	printf("4 - rozwiazanie metoda Gaussa przy wykorzystaniu dynamicznej alokacji pamieci");

	printf("\n Podaj numer cwiczenia:	");
	scanf("%d", &k);
	switch (k)
{
	case 1://cwiczenie 1
	{
		FILE *p;
		p = fopen("plik1.txt", "w");
		if (p == NULL) printf("Problem");

		double M[50][50];
		double b[50];
		double x[50];
		int n = 6;

		HilbertMatrix(n, M);
		DisplayMatrix(n, M);

		ComputeVec(n, M, b);
		printf("\n wektor prawych stron\n");
		DisplayVec(n, b);

		gauss(n, M, b, x);		
		printf("\n Wyniki dla n=%d\n",n);
		fprintf(p, "%d\n\n", n);
		for (int i = 0; i < n; i++)
		{
			fprintf(p, "%lf\n", x[i]);
		}
		fclose(p);
		DisplayVec(n, x);

		break;
	}
	case 2:	//cwiczenie 2
	{
		double M[50][50];
		double b[50];
		double x[50];
		int n = 7;

		HilbertMatrix(n, M);
		printf("\nWyniki dla n = %d\nMacierz wyjsciowa\n",n);
		DisplayMatrix(n, M);	//pokazuje macierz Hilberta
		
		double wsp;
		for (int i = 0; i < n - 1; i++)	//wiersz do ktorego wartosci sie odwolujemy w kazdym kroku (którego wartoœæ przemno¿on¹ bêdziemy odejmowaæ)
		{			
			for (int k = i + 1; k < n; k++)	//wiersz którego elementy eliminujemy
			{
				wsp = M[k][i] / M[i][i];		
				for (int j = i ; j < n; j++)		//przejscie po kolejnych kolumnach od momentu k-tego wiersza,
					M[k][j] -= M[i][j] * wsp;		//odejmowanie elementów wiersza "i" od wiersza "k"
			}
		}
		//po powy¿szych pêtlach otrzymujemy macierz trójk¹tn¹ górn¹ 
		printf("\n");
		printf("Macierz zdiagonalizowana\n");
		DisplayMatrix(n, M);	//pokazuje macierz trójk¹tn¹

		double det = M[0][0]; //wyznacznik macierzy
		for (int i = 1; i < n; i++)
		{
			for (int j = 1; j < n; j++)
			{
				if (i == j)
				{
					det = det * M[i][j];
				}
			}
		}
		printf("\nwyznacznik = %g", det);
		break;
		
	}
	case 3: 
	{	
		int n;
		FILE *z;
		z = fopen("plik2.txt", "r");
		if (z == NULL) printf("problem2");
		fscanf(z, "%d", &n);	//wczytujê liczbê równan liniowych z pliku

		double *x = (double *)malloc(n * sizeof(double)); //wektor rozwi¹zañ
		double *b = (double *)malloc(n * sizeof(double));//dynamiczna alokacja wektora prawych stron
		double **M = (double **)malloc(n * sizeof(double*));//dynamiczna alokacja macierzy M
		for (int k = 0; k < n; ++k)
		{
			M[k] = (double*)malloc(n * sizeof(double));
		}
		
		for (int i = 0; i < n; i++)//wczytanie macierzy A
		{
			for (int j = 0; j < n; j++)
			{
				fscanf(z, "%lf", &M[i][j]);
			}
		}
		for (int i = 0; i < n; i++)//wczytanie wektora b
		{
			fscanf(z, "%lf", &b[i]);
		}

		printf("wczytana macierz:\n");
		DisplayMatrixw(n, M);
		printf("\nwczytany wekto prawych stron:\n");
		DisplayVecw(n, b);

		fclose(z);
		
		gaussw(n, M, b, x);	
		
		printf("\nWyniki\n");
		DisplayVecw(n, x);
	
		for (int k = 0; k < n; ++k)	// zwalnianie pamiêci
			free(M[k]);
		free(M);
		free(x);
		free(b);

		break;
	}
	case 4:
	{
		FILE *p;
		p = fopen("plik1.txt", "w");
		if (p == NULL) printf("Problem");
		int n;
		printf("podaj liczbe rownan\n");
		scanf("%d", &n);

		double *x = (double *)malloc(n * sizeof(double)); //wektor rozwi¹zañ
		double *b = (double *)malloc(n * sizeof(double));//dynamiczna alokacja wektora prawych stron
		double **M = (double **)malloc(n * sizeof(double*));//dynamiczna alokacja macierzy M
		for (int k = 0; k < n; ++k)
		{
			M[k] = (double*)malloc(n * sizeof(double));
		}
		
		HilbertMatrixw(n, M);	//tworzy macierz wg algorytmu
		DisplayMatrixw(n, M);	//wyœwietla macierz
		ComputeVecw(n, M, b);	//tworzy wektor prawych stron
		printf("\n wektor prawych stron\n");
		DisplayVecw(n, b);	//wyswietla wektor prawych stron
		gaussw(n, M, b, x);		//funkcja przepisana z gauss.cpp i nieco zmodyfikowane argumenty jakie przyjmuje
		printf("\n Wyniki dla n=%d\n", n);
		fprintf(p, "%d\n\n", n);
		for (int i = 0; i < n; i++)
		{
			fprintf(p, "%lf\n", x[i]);
		}
		fclose(p);
		DisplayVecw(n, x);
		for (int k = 0; k < n; ++k)	// zwalnianie pamiêci
			free(M[k]);
		free(M);
		free(x);
		free(b);
		break;
	}
	default:
	{
		printf("nie wiem co mam zrobic");
		break;
	}
}
	getchar();
	getchar();
	return 0;
}
