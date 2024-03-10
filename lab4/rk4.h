#ifndef __RK4_H__
#define __RK4_H__

// --------------------------------------------------------------------------
// Funkcja wykonuje, metod� Rungego-Kutty Iv-ego rz�du,
// jeden krok ca�kowania skalarnego r�wnania ro�niczkowego zwyczajnego:
//
//  dy/dx = fun(x,y),    y(x0)=y0
//
// Parametry formalne:
// x0 - warto�� startowa zm. niezale�nej
// y0 - warto�� startowa zm. zale�nej
// h  - krok ca�kowania
// fun(x,y) - nazwa funkcji obliczaj�cej prawe strony
// y1 - obliczona warto�� zmiennej zale�nej w punkcie x0+h

double rk4( double x0, double y0, double h, double (*fun)(double, double));


// --------------------------------------------------------------------------
// Funkcja wykonuje, metod� Rungego-Kutty IV-tego rzedu,
// jeden krok ca�kowania wektorowego r�wnania ro�niczkowego zwyczjanego:
//
//  dY/dx = Fun(x,Y),    Y(x0)=Y0
//
// Parametry formalne:
// x0 - warto�� startowa zm. niezale�nej
// y0 - warto�� startowa zm. zale�nej (tablica n-elementowa)
// h  - krok ca�kowania
// n  - liczba r�wna�
// fun(x,y,prawastr) - nazwa funkcji obliczaj�cej prawe strony
// y1 - obliczona warto�� zmiennej zale�nej w punkcie x0+h
//      (tablica n-elementowa)

void vrk4( double x0, double y0[], double h, int n, void (*fun)(double, double*, double*), double y1[] );

#endif