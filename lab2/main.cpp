#define M_PI 3.14159265358979323846
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kwad.h"

double tr(double a, double b, int n, double(*fun)(double));
double sim(double a, double b, int n, double(*fun)(double));
double gx(double);
double vx(double);

int main()
{
	int k = 1;
	printf("1 - cwiczenie 1 i 2\n");
	printf("3 - cwiczenie 3 i 4\n");
	printf("5 - cwiczenie 5 i 6\n");
	printf("\n Podaj numer cwiczenia:	");
	scanf("%d", &k);
	switch (k) {

	case 1:	//cwiczenie 1 i 2
	{
		double a, b;
		double cn1, cn2, bl1, ca1, ca2, bl2;
		int n = 10;
		printf("podaj przedzial calkowania <a,b> oraz liczbe podzialow n\n");
		scanf("%lf%lf%d", &a, &b, &n);

		FILE*f;
		FILE*p;
		f = fopen("wyniki1.txt", "w");
		p = fopen("wyniki2.txt", "w");
		cn1 = tr(a, b, n, gx);
		ca1 = log(b / a);
		bl1 = fabs(ca1 - cn1);
		
		cn2 = tr(a, b, n, vx);	//dla drugiej funkcji
		ca2 = (-1) / b + 1 / a;
		bl2 = fabs(ca2 - cn2);

		
		printf( "calka numeryczna %lf\ncalka analityczna %lf\nblad bezwzgledny przyblizenia %lf\nkrok calkowania %d\n", cn1, ca1, bl1, n);
		printf( "calka numeryczna %lf\ncalka analityczna %lf\nblad bezwzgledny przyblizenia %lf\nkrok calkowania %d\n", cn2, ca2, bl2, n);
		fprintf(f, "calka numeryczna %lf\ncalka analityczna %lf\nblad bezwzgledny przyblizenia %lf\nkrok calkowania %d\n", cn1, ca1, bl1, n);
		fprintf(p, "calka numeryczna %lf\ncalka analityczna %lf\nblad bezwzgledny przyblizenia %lf\nkrok calkowania %d\n", cn2, ca2, bl2, n);

		fclose(f);
		fclose(p);
		break;
	}
	case 3: //cwiczenie 3 i 4
	{
		double a, b;
		double cn1, cn2, bl1, ca1, ca2, bl2;
		int n = 1;
		printf("podaj przedzial calkowania <a,b>\n");
		scanf("%lf%lf", &a, &b);

		FILE*f;
		FILE*p;
		f = fopen("wyniki1.txt", "w");
		p = fopen("wyniki2.txt", "w");
		for (int i = 0; i < 8; i++)	//w ostatnim kroku i=7 wiec liczba przedzialow to 2^8
		{
			n = n * 2;
			cn1 = tr(a, b, n, gx);
			ca1 = log(b / a);
			bl1 = fabs(ca1 - cn1);
	
			cn2 = tr(a, b, n, vx);
			ca2 = (-1) / b + 1 / a;
			bl2 = fabs(ca2 - cn2);
			//printf("%lf \t %lf \t %d\n", cn1, ca1, n);
			fprintf(f, "%lf \t %lf \t %d\n", cn1, ca1, n);
			fprintf(p, "%lf \t %lf \t %d\n", cn2, ca2, n);
		}
		fclose(f);
		fclose(p);
		break;
	}
	case 5: //cwiczenie 5 i 6
	{
		double a, b;
		double cn1, cn2, bl1, ca1, ca2, bl2;
		int n = 1;
		printf("podaj przedzial calkowania <a,b>\n");
		scanf("%lf%lf", &a, &b);

		FILE*f;
		FILE*p;
		f = fopen("wyniki1.txt", "w");
		p = fopen("wyniki2.txt", "w");
		for (int i = 0; i < 8; i++)	//w ostatnim kroku i=7 wiec liczba przedzialow to 2^8
		{
			n = n * 2;
			cn1 = sim(a, b, n, gx);
			ca1 = log(b / a);
			bl1 = fabs(ca1 - cn1);
			printf("%lf\n%lf\n%lf\n\n", cn1, ca1, bl1);
			cn2 = sim(a, b, n, vx);
			ca2 = (-1) / b + 1 / a;
			bl2 = fabs(ca2 - cn2);
			printf("%lf\n%lf\n%lf\n\n", cn2, ca2, bl2);
			fprintf(f, "%lf \t %lf \t %d\n", cn1, ca1, n);
			fprintf(p, "%lf \t %lf \t %d\n", cn2, ca2, n);
		}
		fclose(f);
		fclose(p);
		break;
	}
	default:
		printf("nie wiem co mam zrobic");
		break;
	}
	//%g	
	getchar(); getchar();
	return 0;
}


double sim(double a, double b, int n, double(*f)(double))	//funkcja liczaca kwadrature metoda simpsona 
{
	double w = 0;
	double h = (b - a)/n; //dlugosc przedzialu na ktorym calkuje
	double x = a;
	for (int i = 0; i < n; i++)
	{
		w = w + h*(f(x)+4*f(x+h/2)+f(x+h))/6;
		x = x + h;
	}
	return w;
}

double tr (double a, double b, int n, double(*f)(double)) //funkcja licz¹ca kwadrature metoda trapezowa
{
	double w=0;
	double h = (b - a) / n; //dlugosc przedzialu na ktorym calkuje
	double x = a;
	for (int i = 0; i<n; i++) 
	{
		w = w+(f(x) + f(x+h))*h/2;
		x = x + h;
	}
	return w;
}

double gx (double x) // g(x) = x2
{
	return 1/x;
}

double vx (double x) // g(x) = x2
{
	return  1/(x*x);
}