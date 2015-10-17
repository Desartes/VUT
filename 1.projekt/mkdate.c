// #include <stdio.h>
// int main()
// {
//  	char datum[] = "2015-08-26";

	// int day, month, year;
	// sscanf(datum, "%4d-%2d-%2d",
	//     &year,
	//     &month,
	//     &day);
// 	printf("%d / %d / %d\n", day, month, year );
		
// 	return 0;
// }
#include <stdio.h>
int main()
{
	char datum[] = "2015-08-26";
	char *c = &datum[0];
	// char rok[4],
	// 	 den[2],
	// 	 mesiac[2];
	int i = 0;

	while( *(c + i) != '\0' ){ // Iterácia ktorá prejde celým reťazcom a vyhodnotí či je reťazec číslo
		if ( (*(c + i) >= 48 && *(c + i) <= 57) && (i != 4) && (i != 7) ) 
			i++;
		else 
		if ( (i == 4 && (*(c + i) == '-')) || (i == 7 && (*(c + i) == '-')) )
			i++;
		else {
			printf("Nejedná sa o formát dátumu\n");
			break;
		}
	}
	printf("%d\n",i );
	if ( *(c + i) == '\0' ) // Pokiaľ som cyklom prešiel až do ukončujúceho znaku v reťazci reťazec je číslo
		printf("Všetko je okej -> %s\n", c);
	else 
		printf("Niečo sa dojebalo.\n");
	// 	return 1; 
	// else // Reťazec nie je číslo
	// 	return 0;
return 0;
}