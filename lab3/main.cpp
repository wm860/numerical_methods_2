#include <stdio.h>
#include <stdlib.h>
//#include "nonlin.h"
#include <math.h>

double eqn(double x);			//funkcja dla ktorej liczymy pierwiastek
double bi(double a, double b, double (*f)(double), double eps, int *j);			//metoda bisekcji napisana pod mainem
double bi1(double a, double b, double(*f)(double,double), double eps, int *j);	//metoda bisekcji licz¹ca x dla funkcji z paramertrem
double st(double a, double b, double(*f)(double), double eps, int *j);			//metoda stycznych
double st1(double a, double b, double(*f)(double,double), double eps, int *j);	//metoda stycznych licz¹ca x dla funkcji z paramertrem
double si2(double a, double b, double(*f)(double), double eps, int *j);			//metoda siecznych
double si1(double a, double b, double(*f)(double,double), double eps, int *j);  //metoda siecznych licz¹ca x dla funkcji z paramertrem
double eqn2(double x, double w);		//funkcja dla ktorej liczymy pierwiastek z parametrem


int j = -5;		//te zmienna (liczba iteracji ) muszê zadeklarowac globalnie, bo kilka funkcji odwoluje sie do jej adresu
double w = 0.5;
int main()
{
	int k = 1;
	printf("1 - cwiczenie 1 \n");
	printf("2 - cwiczenie 2\n");
	printf("\n Podaj numer cwiczenia:	");
	scanf("%d", &k);
	switch (k) 
{
	case 1:	//cwiczenie 1 
	{
		FILE *p;
		p = fopen("plik.txt", "w");
		if (p == NULL) printf("BLAD");
		
//part1
		double eps, a, b, xc = 0.0;
		printf("Wczytaj konce przedzialow oraz wartosc epsilon");
		scanf("%lf%lf%lf", &a, &b, &eps);
		xc = bi(a, b, eqn, eps, &j);
		printf("Miejsce zerowe %lf\tinteracja %d\n", xc, j);

//part2
		//printf("\n Przyblizenie eps \tprzyblizony wynik \tliczba iteracji\n");
		for (int i = (-20); i <= (-3); i++)
		{
			eps = pow(2, i);
			xc = bi(a, b, eqn, eps, &j);	//znajduje przyblizony pierwiastek
			//printf("%g\t%g\t%d\n", eps, xc, j);
			fprintf(p, "%g\t%g\t%d\n", eps, xc, j);	//zapisuje wyniki do pliku txt
		}


		fclose(p);
		break;
	}
	case 2: //cwiczenie 2
	{
		FILE *p,*r;
		p = fopen("plik2.txt", "w");
		r = fopen("plik3.txt", "w");
		if (p == NULL) printf("BLAD");
		if (r == NULL) printf("BLAD");

		double eps, a, b, xc = 0.0;

//part1
		
		printf("\nWczytaj 2 punkty od ktorych procedura metody stycznych ma sie zaczac oraz wartosc epsilon\n");
		scanf("%lf%lf%lf", &a, &b, &eps);
		//program wylicza tutaj miejsca zerowe oraz liczbe iteracje 3 metod dla zadanego przedzialu i epsilona
		xc = bi(a, b, eqn, eps, &j);
		printf("Miejsce zerowe dla metody bisekcji %lf\tinteracja %d\n", xc, j);
		xc = si2(a, b, eqn, eps, &j);
		printf("Miejsce zerowe dla metody siecznych %lf\tinteracja %d\n", xc, j);
		xc = st(a, b, eqn, eps, &j);
		printf("Miejsce zerowe dla metody stycznych %lf\tinteracja %d\n\n", xc, j);

//part2
		//ta czesc programu wylicza kolejne miejsca zerowe oraz wskazuje po ktorej iteracji osiagnieto dane epsilon
		for (int i = (-20); i <= (-3); i++)
		{
			eps = pow(2, i);
			xc = bi(a, b, eqn, eps, &j);
			//printf("%g\t%g\t%d\n", eps, xc, j);
			fprintf(p, "%g\t%g\t%d\t", eps, xc, j);
			xc = si2(a, b, eqn, eps, &j);
			//printf("%g\t%g\t%d\n", eps, xc, j);
			fprintf(p, "%g\t%g\t%d\t", eps, xc, j);
			xc = st(a, b, eqn, eps, &j);
			//printf("%g\t%g\t%d\n\n", eps, xc, j);
			fprintf(p, "%g\t%g\t%d\n", eps, xc, j);	//zapisuje wyniki do pliku txt ¿eby zrobiæ wykres
		}

//part3
		//ta czesc programu wylicza miejsca zerowe dla zmieniaj¹cego siê parametru w
		for (w=0.5; w<15.0; w=w+0.1)
		{
			eps = pow(10, (-6));

			xc = bi1(a, b, eqn2, eps, &j);
			printf("%lf\t%g\t%d\n", w, xc, j);
			//fprintf(r, "%lf\t%g\t%d\t",w, xc, j);

			xc = si1(a, b, eqn2, eps, &j);
			//printf("%lf\t%g\t%d\n", w, xc, j);
			//fprintf(r, "%lf\t%g\t%d\t", w, xc, j);

			xc = st1(a, b, eqn2, eps, &j);
			//printf("%lf\t%g\t%d\n\n", w, xc, j);
			//fprintf(r, "%lf\t%g\t%d\t\n", w, xc, j);	//zapisuje wyniki do pliku txt zeby 
		}

		fclose(p);
		fclose(r);

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

double bi(double a, double b, double(*f)(double), double eps, int *j)//metoda bisekcji
{
	double xl = a;
	double xr = b;
	double xc; int licz=0;
	if (f(a)*f(b) >= 0)
	{
		*j = -1;
		return 0;
	}
	else
	{
		do 
		{
			licz++;
			xc= (xl + xr) /2.0;
			if (f(xl)*f(xc) < 0.0)
			{
				xr = xc;
			}
			else
			{
				xl = xc;
			}
		} while(fabs(xr-xl)>=2*eps);
		*j = licz;
	}
	return xc;
}
double st(double a, double b, double(*f)(double), double eps, int *j)//metoda stycznych
{
	double r = 0;
	double xc=a; int licz = 0;
	
	do
	{
		if ((-sin(a) - 1) == 0)	printf("\nWybra³eœ z³y punkt startowy, program zle zadziala");
		a = xc;
		licz++;
		xc = a - f(a)/(-sin(a)-1); //nowe przyblizenie miejsca zerowego
		//if (licz == 500)
		//	break;
	} while (fabs(a - xc) >=  eps);
	*j = licz;
	if (licz == 500)
	{
		printf("\n Wybrales przedzial ktory znajduje sie za daleko od rzeczywistego x");
	}
	return xc;
}
double eqn(double x) //przekszta³cone rownanie na funkcje na potrzeby metod bisekcji, siecznych..
{
	return (cos(x) - x);
}
double si2(double a, double b, double(*f)(double), double eps, int *j) //metoda siecznych
{
	double r = 0, pom = 0;
	double xc; int licz = 0;
	do
	{
		licz++;
		xc = b - f(b)*(b - a) / (f(b) - f(a)); //nowe przyblizenie miejsca zerowego
		
		r = fabs(b - a);
		//printf("%d \t %lf\t  %lf\t %lf\t %lf\n",licz,a,xc,b,r);
		if (licz == 500)
		{
			printf("\n Wybrales przedzial ktory znajduje sie za daleko od rzeczywistego x");
			break;
		}
		a = b;
		b = xc; 
	} while ((fabs(b - a) >= 2 * eps));
	*j = licz+1;	//plus 1 poniewa¿ wartosci wartosci a i b zmieniam pod koniec pêtli a nie na pocz¹tku, wiêc warunek jest spe³niany przed wykonaniem pêtli

	return xc;
}
double eqn2(double x, double w) //przekszta³cone rownanie na funkcje na potrzeby metod bisekcji, siecznych..
{
	return (cos(x) - w*x);
}
double bi1(double a, double b, double(*f)(double,double), double eps, int *j)//metoda bisekcji dla funkcji dwóch zmiennych
{
	double xl = a;
	double xr = b;
	double xc; int licz = 0;
	if (f(a,w)*f(b,w) >= 0)
	{
		*j = -1;
		return 0;
	}
	else
	{
		do
		{
			licz++;
			xc = (xl + xr) / 2.0;
			if (f(xl,w)*f(xc,w) < 0.0)
			{
				xr = xc;
			}
			else
			{
				xl = xc;
			}
		} while (fabs(xr - xl) >= 2 * eps);
		*j = licz;
	}
	return xc;
}
double st1(double a, double b, double(*f)(double,double), double eps, int *j)//metoda stycznych
{
	double r = 0;
	double xc = a; int licz = 0;

	do
	{
		if (fabs((-sin(a) - 1))<0.0000000001)	return 0;// gdy pochodna w danym punkcie sie zeruje i mamy dzielenie przez 0
		a = xc;
		licz++;
		xc = a - f(a,w) / (-sin(a) - w); //nowe przyblizenie miejsca zerowego
		if (licz == 300)
		{
			break;
		}
	} while (fabs(a - xc) >= eps);
	*j = licz;
	
	return xc;
}
double si1(double a, double b, double(*f)(double,double), double eps, int *j) //metoda siecznych
{
	double r = 0, pom = 0;
	double xc; int licz = 0;
	do
	{
		licz++;
		xc = b - f(b,w)*(b - a) / (f(b,w) - f(a,w)); //nowe przyblizenie miejsca zerowego

		if (licz == 100)
		{
			printf("\n Wybrales przedzial ktory znajduje sie za daleko od rzeczywistego x");
			break;
		}
		a = b;
		b = xc;
	} while ((fabs(b - a) >= 2 * eps));
	*j = licz + 1;

	return xc;
}
