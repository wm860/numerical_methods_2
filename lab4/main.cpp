#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rk4.h"

double euler(double t0, double y0, double h, double (*f)(double, double));
double fun(double t, double y);
double fun2(double t, double y);

double o = 1;	//lambda

int main()
{
	int k = 1;
	printf("1 - Polecenie 1,2,3 - rozwiazanie zagadnienia metoda Eulera i RK4\n");
	printf("2 - Polecenie 4,5 - obliczenia bledu dla zmieniajacego sie h\n");
	printf("3 - Polecenie 6 - obliczenia bledu dla zmieniajacego sie h innego zagadnienia\n");
	printf("\n Podaj numer cwiczenia:	");
	scanf("%d", &k);
	switch (k)
	{
	case 1://cwiczenie 1
	{
		double yk,ya, h, t0, y0,eps;
		printf("Wczytaj t0, y0, h\n"); 
		scanf("%lf%lf%lf", &t0, &y0, &h); //wczytuje wartosci poczatkowe dla zagadnienia oraz krok calkowania
		yk = euler(t0, y0, h, fun);	//wynik policzony metoda eulera
		ya = y0 * exp(o*(t0 + h - t0)); //wynik analityczny
		eps = fabs(ya - yk) / ya;
		printf("Euler\t ya,yk,eps\t%lf\t%lf\t%lf\n",ya, yk,eps);
		yk = rk4(t0, y0, h, fun);
		eps = fabs(ya - yk) / ya;
		printf("RK4  \t ya,yk,eps\t%lf\t%lf\t%lf\n", ya, yk, eps);
		break;
	}

	case 2:
	{
		FILE *p;
		p = fopen("plik.txt", "w");
		if (p == NULL) printf("BLAD");

		double yk, ya, h, t0, y0, eps,tk;
		printf("Wczytaj t0, y0, tk\n");
		scanf("%lf%lf%lf", &t0, &y0, &tk);
		for (int j = 0; j >= (-6); j--)
		{
			h = pow(2, j);
			fprintf(p, "%lf\t", h);
			int n = (tk - t0) / h; //liczba krokow calkowania dla coraz mniejszych h jest coraz wieksza
			yk = y0;
			tk = t0;
			printf("h=%lf\t", h);
			fprintf(p,"EULER\th=%lf\n", h);
			for (int i = 0; i < n; i++)	//metoda eulera
			{
				ya = y0 * exp(o*(tk + h - t0)); //wynik analityczny
				yk = euler(tk, yk, h, fun);	//wynik policzony metoda eulera
				eps = fabs(ya - yk) / ya;
				//printf("%lf\t%lf\t%lf\t%lf\n",tk+h, ya, yk, eps);
				//fprintf(p,"%lf\t%lf\t%lf\t%lf\n", tk + h, ya, yk, eps);
				tk = tk + h;
			}
			printf( "%lf\n", eps);
			fprintf(p, "%lf\t", eps);
			//fprintf(p, "\n");
			yk = y0;
			tk = t0;
			//printf("h=%lf\n", h); 
			//fprintf(p,"RK4\th=%lf\n", h);
			for (int i = 0; i < n; i++)	//metoda rk4
			{
				ya = y0 * exp(o*(tk + h - t0)); //wynik analityczny
				yk = rk4(tk, yk, h, fun);	//wynik policzony metoda eulera
				eps = fabs(ya - yk) / ya;
				//printf("%lf\t%lf\t%lf\t%lf\n", tk + h, ya, yk, eps);
				//fprintf(p, "%lf\t%lf\t%lf\t%lf\n", tk + h, ya, yk, eps);
				tk = tk + h;
			}
			fprintf(p, "%lf\n",eps);
			printf("%lf\n", eps);
		}
		fclose(p);
		break;
	}
	case 3: //cwiczenie 2
	{
		FILE *p;
		p = fopen("plik.txt", "w");
		if (p == NULL) printf("BLAD");

		double yk, ya, h, t0, y0, eps, tk;
		printf("Wczytaj t0, y0, tk\n");
		scanf("%lf%lf%lf", &t0, &y0, &tk);
		for (int j = 1; j <4; j++)
		{
			h = 0.01*j;
			fprintf(p, "%lf\t", h);
			int n = (tk - t0) / h; //liczba krokow calkowania dla coraz mniejszych h jest coraz wieksza
			yk = y0;
			tk = t0;
			//printf("h=%lf\n", h);
			fprintf(p,"EULER\th=%lf\n", h);
			for (int i = 0; i < n; i++)	//metoda eulera
			{
				ya = (sin(tk+h)-0.01*cos(tk+h)+0.01*exp(-100*(tk+h)))/1.0001; //wynik analityczny
				yk = euler(tk, yk, h, fun2);	//wynik policzony metoda eulera
				eps = fabs(ya - yk) / ya;
				//printf("%lf\t%lf\t%lf\t%lf\n",tk+h, ya, yk, eps);
				fprintf(p,"%lf\t%lf\t%lf\t%lf\n", tk + h, ya, yk, eps);
				tk = tk + h;
			}

			fprintf(p, "\n");
			yk = y0;
			tk = t0;
			//printf("h=%lf\n", h); 
			fprintf(p,"RK4\th=%lf\n", h);
			for (int i = 0; i < n; i++)	//metoda rk4
			{
				ya = (sin(tk + h) - 0.01*cos(tk + h) + 0.01*exp(-100 * (tk + h))) / 1.0001; //wynik analityczny
				yk = rk4(tk, yk, h, fun2);	//wynik policzony metoda eulera
				eps = fabs(ya - yk) / ya;
				//printf("%lf\t%lf\t%lf\t%lf\n", tk + h, ya, yk, eps);
				fprintf(p, "%lf\t%lf\t%lf\t%lf\n", tk + h, ya, yk, eps);
				tk = tk + h;
			}
			fprintf(p, "\n\n");
		}
		fclose(p);
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

double euler(double t0, double y0, double h, double(*f)(double, double))
{
	double yk;
	yk = y0 + h * f(t0, y0);
	return yk;
}
double fun(double t, double y)	//pierwsze zagadnienie
{
	return o * y;
}
double fun2(double t, double y)	// drugie zagadnienie
{
	return  100*(sin(t)-y);
}
