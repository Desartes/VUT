/* -------------------------------------
 * @file_name: proj2.c
 * @author   : Filip Kolesar - xkoles06
 *			   1BIT, VUT FIT
 * @date     : 10/2015
 * @version  : 0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.1
 ---------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double taylor_log( double x, unsigned int n );
double exponent(double a, double ex);

int main(int argc, char *argv[])
{
	double X = 1.131401114526,
		   N = 4.0;

	printf("       log(%.4f) = %.12f\n", X, log(1.131401114526));
	printf("taylor_log(%.4f) = %.12f\n", X, taylor_log(X,N) );
	return 0;
}
double taylor_log( double x, unsigned int n ) {
	double result = -(1 - x);

	for (double i = 2.0; i < n + 2  ; ++i) {
		// printf("%l\n", i);
		result = result - exponent(x,i) / i;
		// printf("%f = %f - (%f / %f)\n", result, result, exponent(x,i), i );
	}
	return result;
}
double exponent(double a, double ex) {
	double result = (1 - a);
	for (int i = 1; i < ex; ++i) {
		result = result * (1 - a);
	}
	return result;
}