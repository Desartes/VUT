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
double cfrac_log(double x, unsigned int n);
double exponent(double a, double ex);

int main(int argc, char *argv[])
{
	double X = 1.131401114526;
	int    N = 2.0;

	printf("       log(%.4f) = %.12f\n", X, log(1.131401114526));
	printf("taylor_log(%.4f) = %.12f\n", X, taylor_log(X,N) );
	printf(" cfrag_log(%.4f) = %.12f\n", X, cfrac_log(X,N) );
	return 0;
}
double taylor_log( double x, unsigned int n ) {
	double result;
	if ( x < 2 ) {
		result = -(1 - x);
		for (double i = 2.0; i < n + 2 - 1 ; ++i)
			result = result - exponent(1 - x,i) / i;
	} else {
		result = (x - 1)/x;
		for (double i = 2.0; i < n + 2 - 1; ++i)
			result = result + exponent( (x - 1)/x, i) / i;
	}
	return result;
}
double cfrac_log(double x, unsigned int n) {
	double newx = ((1 + x) / (1 - x)),
		   result = 2 * newx;
		for (double i = 0.0; i < n; ++i) {
			if (i + 1.0 == n) {
				result = result / (1 + (2*i));
				printf("%.12f / %.12f\n", result, (1 + (2*i)));
			} else {
				result = result / (1 + (2*i)) - exponent(i + 1, 2) * exponent(newx, 2);
				printf("%.16f / %.16f - %.16f * %.16f\n", result, (1 + (2*i)), exponent(i + 1, 2), exponent(newx, 2) );
			}
		}
	return result;
}
double exponent(double a, double ex) {
	double result = a;
	for (int i = 1; i < ex; ++i)
		result = result * a;
	return result;
}