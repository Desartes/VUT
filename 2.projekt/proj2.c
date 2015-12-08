/* -------------------------------------
 * @file_name: proj2.c
 * @author   : Filip Kolesar - xkoles06
 *			   1BIT, VUT FIT
 * @date     : 11/2015
 * @version  : 0.8
 ---------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define ABS(x) ((x)<0 ? -(x) : (x)) // absolutna hodnota

double taylor_log( double x, unsigned int n );
double cfrac_log(double x, unsigned int n);
double exponent(double a, double ex);

int main(int argc, char *argv[])
{
	double x, min, max, eps;
	unsigned int n, tminit = 1, tmaxit = 1, cminit = 1, cmaxit = 1;

	if ( ( argc == 4 && !strcmp(argv[1], "--log") ) || ( argc == 5 && !strcmp(argv[1], "--iter") ) ) {
		if ( !strcmp(argv[1], "--log") ) { // argument --log
			if ( ( (x = strtod(argv[2], NULL) ) >= 0 ) && ( (n = strtod(argv[3], NULL)) > 0 ) ) {
				printf("       log(%g) = %.12g\n", x, log(x));
				printf("    cf_log(%g) = %.12g\n", x, cfrac_log(x, n) );
				printf("taylor_log(%g) = %.12g\n", x, taylor_log(x, n) );
			} else {
				printf("Bad syntax\n");
				return 1;
			}
		} else { // argument --iter
			if ( ( (min = strtod(argv[2], NULL) ) > 0 ) && ( (max = strtod(argv[3], NULL)) > 0 ) && ( (eps = strtod(argv[4], NULL)) > 0 ) ) {
				while( ABS(log(min) - taylor_log(min, tminit)) > eps) {
					tminit++;
				}
				while( ABS(log(max) - taylor_log(max,tmaxit)) > eps) {
					tmaxit++;
				}

				while( ABS(log(min) - cfrac_log(min, cminit)) > eps) {
					cminit++;
				}
				while( ABS(log(max) - cfrac_log(max, cmaxit)) > eps) {
					cmaxit++;
				}

				// Vypisy na stdout
				printf("       log(%g) = %.12g\n", min, log(min));
				printf("       log(%g) = %.12g\n", max, log(max));

				if ( cmaxit > cminit ) { 
					printf("continued fraction iterations = %d\n", cmaxit + 1);
					printf("    cf_log(%g) = %.12g\n", min, cfrac_log(min, cmaxit) );
					printf("    cf_log(%g) = %.12g\n", max, cfrac_log(max, cmaxit) );
				} else {
					printf("continued fraction iterations = %d\n", cminit + 1);
					printf("    cf_log(%g) = %.12g\n", min, cfrac_log(min, cminit) );
					printf("    cf_log(%g) = %.12g\n", max, cfrac_log(max, cminit) );
				}

				if ( tmaxit > tminit ) {
					printf("taylor polynomial iterations = %d\n", tmaxit);
					printf("taylor_log(%g) = %.12g\n", min, taylor_log(min, tmaxit) );
					printf("taylor_log(%g) = %.12g\n", max, taylor_log(max, tmaxit) );
				} else {
					printf("taylor polynomial iterations = %d\n", tminit);
					printf("taylor_log(%g) = %.12g\n", min, taylor_log(min, tminit) );
					printf("taylor_log(%g) = %.12g\n", max, taylor_log(max, tminit) );
				}

			}
		}
	} else {
		printf("Usage: --log N X \n"
			   "   or  --iter MIN MAX EPS\n");
		return 1;
	}

	return 0;
}
double taylor_log( double x, unsigned int n ) { // taylorov rad
	double result;
	if ( x < 1 ) {
		result = -(1 - x);
		for (double i = 2.0; i < n + 2 - 1 ; ++i)
			result = result - exponent(1 - x,i) / i;
	} else {
		result = (x - 1) / x;
		for (double i = 2.0; i < n + 2 - 1; ++i)
			result = result + exponent( (x - 1) / x, i) / i;
	}
	return result;
}
double cfrac_log(double x, unsigned int n) { // zretazeny zlomok
	x = (x - 1)/(x + 1);
	double result = 0.0;
	for ( ; n >= 1; n--)
		result = (-(  n*x*n*x ) / ((2*n+1) + result));
	return (2 * x) / (1 + result);
}
double exponent(double a, double ex) { // vypocet exponentu, (zaklad, exponent)
	double result = a;
	for (int i = 1; i < ex; ++i)
		result = result * a;
	return result;
}