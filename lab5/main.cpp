#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rk4.h"
//void vrk4(double x0, double y0[], double h, int n, void(*fun)(double, double*, double*), double y1[])
void fun(double, double*, double*);

double omega0 = 1;	//predkosc katowa w radianach na sekunde
double alfa0 = 0;	//kat w radianach
double l = 2.7;		//dlugosc wahadla w metrach
double t0 = 0;
double tk = 10;	
double h = 0.1;
double m = 6;
int n = 2;

int main()
{
	double E;
	double y0[2];	//tablica z wartosciami poczatkowymi
//double Y[2];	//tablica z wartosciami ktore by sie zmienialy przez vrk4 
	double y1[2];	//tablica z wynikami
	y0[0] = alfa0; 
	y0[1] = omega0;

//Y[1] = om; //to sluzy tylko do obliczen mojej funkcji - funkcja sama sobie daje argumenty i oblicza to co chce, wiec nie daje wartosci temu
//Y[0] = alfa; 
	E = m * l*l / 2 * (omega0*omega0) + m * 9.81*l*(1 - cos(alfa0));
	printf("t0=%lf, tk=%lf, h=%lf, l=%lf, m=%lf\tomega0=%lf,    alfa0=%lf,\n\n",t0,tk,h,l,m,omega0,alfa0);
	printf("czas\t      alfa\t       omega\t      energia calkowita\n");
	printf("%lf\t%lf\t%lf\t%lf\n", t0, y0[0], y0[1], E);
	double k = (tk - t0) / h;	//ile razy ma policzyc rozwazwiazanie zagadnienia
	for (int i = 0; i < k; i++)
	{
		vrk4(t0, y0, h, n, fun, y1);
		t0 = t0 + h;
		y0[0] = y1[0];		//w nowych krokach iteracyjnych bierzemy warunki pocz¹tkowe jako
		y0[1] = y1[1];		//te nowe obliczone z poprzedniego kroku
		E = m*l*l/2*(y1[1])*(y1[1])+m*9.81*l*(1-cos(y1[0]));
		printf("%lf\t%lf\t%lf\t%lf\n", t0,y1[0],y1[1], E); //y1[0] to nowa wartosc omegi y1[1] to nowa wartosc dla alfy
	}
		
	getchar();
	return 0;
}
void fun(double t, double Y[], double f[])
{
	f[0] = Y[1];	//tablica f to tablica prawych stron //wyznacza alfê w ntym kroku
	f[1] = -9.81 / l * sin(Y[0]);	//omegê
}

