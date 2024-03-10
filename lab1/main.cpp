#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "inter.h"
#include "winbgi2.h"

int main()
{
	int n;
	scanf("%d", &n);

		
	double *x, *y, *t, *wynik, *z;
	FILE*f;
	f = fopen("wyniki.txt", "w");
	x = (double*)malloc(n * sizeof(double));
	y = (double*)malloc(n * sizeof(double));
	t = (double*)malloc(4*n * sizeof(double));// na punkty dla funkcji lagranga
	z = (double*)malloc(4 * n * sizeof(double));//na rzeczywiste wartoœci funkcji
	wynik = (double*)malloc(4*n * sizeof(double));
	double h, b = 2, a = (-2);
	
	h = (b - a) / (n - 1);
	
	for (int i = 0; i < n; i++)// zestaw wêz³ów
	{
		x[i] = a + (i*h);
		y[i] = exp((-x[i])*x[i]);

	}
	for (int i = 0; i < 4 * n-4; i++)// zestaw punktow dla interpolacji
	{
		t[i] = a + i * h / 4;
		z[i] = exp(-t[i] * t[i]);
	}

	graphics(800,1000);
	circle(30,30,10);
	scale(-2, -2, 2, 2);
	for (int i = 0; i < 4*n-4 ; i++)
	{
		wynik[i] = lagrange(x, y, (n - 1), t[i]);
		printf("%lf\t%lf\n", t[i] , wynik[i]);
		fprintf(f, "%lf\t%lf\t%lf\n", t[i], z[i], wynik[i]);
		circle(t[i],wynik[i],5);
		circle(t[i], z[i], 3);
	}

	free(x);
	free(y);
	free(t);
	free(wynik);
	fclose(f);
	wait();
	return 0;
}