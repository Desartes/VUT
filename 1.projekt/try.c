/* -----------------------
 * @file_name: proj1.c    
 * @author: Filip Kolesár - xkoles06
 			1BIT, VUT FIT
 * @date: 10/2015
 * @version: 1.0.0     
 ------------------------*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

int strlength(char *c);
int ispalindrom(char *a);
int isnum(char *c);
int isprime(int i);
int istext(char *c);
int isdate(char *c);
char *datum(int d, int m, int y);

int main() /* ---------------- HLAVNÉ TELO PROGRAMU ---------------- */
{
	char slovo[100];

	while( scanf("%100s", slovo) == 1 && istext(&slovo[0]) ) {
		if ( ispalindrom(&slovo[0]) && !isnum(&slovo[0]) )
			printf("word: %s (palindrome)\n", slovo);
		else 
			if (isnum(&slovo[0])){
				if ( strlength(&slovo[0]) < 11 && atol(slovo) <= INT_MAX && isprime(atol(slovo)) ){
					printf("number: %s (prime)\n", slovo);
				} else
					printf("number: %s\n", slovo);
			}
		else 
			if (isdate(&slovo[0])) {
			int day, month, year;
			sscanf(slovo, "%4d-%2d-%2d",&year, &month, &day);
			if ( (month <= 12) && (month >= 1) && (day <= 31) && (day >= 1) ){
				printf("date: %.3s %s\n", datum(day, month, year), slovo);
			} else
				printf("word: %s\n", slovo);
		}
		else
			printf("word: %s\n", slovo);
	}
	if (!istext(&slovo[0])) {
		printf("Chybný vstup !\n");
	}
	//printf("%d\n", strlength(&slovo[0]));
	return 0; 
}

int strlength(char *c) { // Zistenie dĺžky slova
	int offset = 0,
		count = 0;
	while( *(c + offset) != '\0') { 
		++offset;
		++count;
	}
	return count;
}

int ispalindrom(char *a) { /* ---- Funkcia zistujúca palindrom ---- */
	char new[100];
	int dlzkaslova = strlength(a);

	for (int i = 0; i <= 100; ++i){ // Resetovanie obsahu reťazca
		new[i] = 0;
	}

	for (int i = 0; i < dlzkaslova; ++i) { // Otáčanie slova pre následné porovnanie
		//printf("%c", *(a+(dlzkaslova - i - 1)) );
		new[i] = *(a+(dlzkaslova - i - 1));
	}

	int loop = 0; // Pomocná premenná
	while( *(a + loop) == new[loop] ){ // Porovnávanie dvoch reťazcov (po znakoch)
		if ( *(a + loop) == '\0' || new[loop] == '\0' ) // Ak sme na konci niektorého z reťazcov, vyskoč z cyklu
			break;
		loop++; // Ďalší znak v reťazci
	}
	if (*(a + loop) == '\0' && new[loop] == '\0' ) // Pokiaľ sme prišli ku koncu oboch reťazcov naraz, reťazce sa zhodujú
		return 1;
	else // Reťazce sa nehodujú
		return 0;
	//	printf("%s | %s\n", a, new); // Debug mode
}

int isnum(char *c) { /* ---- Funkcia zisťujúca či je reťazec číslo ---- */
	int i = 0;
	
	while( *(c + i) != '\0' ){ // Iterácia ktorá prejde celým reťazcom a vyhodnotí či je reťazec číslo
		if ( !(*(c + i) >= 48 && *(c + i) <= 57) )
			break; // Ak znak v reťazci nie je číslo, vyskoč z cyklu
		else 
			i++; // Nasledujúci znak v reťazci
	}
	if ( *(c + i) == '\0' ) // Pokiaľ som cyklom prešiel až do ukončujúceho znaku v reťazci reťazec je číslo
		return 1; 
	else // Reťazec nie je číslo
		return 0;
}

int istext(char *c) { /* ---- Funkcia zisťujúca či je reťazec složený iba z "tisknutelných" znakov ASCII tabulky ---- */
	int i = 0;
	
	while( *(c + i) != '\0' ){ 
		if ( !(*(c + i) > 32 && *(c + i) < 127) ) // rozsah tisknutelných znakov ASCII 33 - 126
			break; 
		else 
			i++; 
	}
	if ( *(c + i) == '\0' ) // Pokiaľ som na konci slova bez erroru, reťazec je z povolených hodnôt ASCII
		return 1; 
	else // Reťazec nie je z tisknutelných znakov
		return 0;
}

int isdate(char *c) { /* ---- Funkcia zisťujúca či je reťazec dátum ---- */
	int i = 0;

	while( *(c + i) != '\0' ){ // Iterácia ktorá prejde celým reťazcom a vyhodnotí či je reťazec vo formáte dátumu DDDD-DD-DD
		if ( (*(c + i) >= 48 && *(c + i) <= 57) && (i != 4) && (i != 7) && (i < 10)) // D je číslo a zároveň nie sme na indexe 4 ani 7
			i++;
		else 
			if ( (i == 4 && (*(c + i) == '-')) || (i == 7 && (*(c + i) == '-')) ) // ak sme na indexe 4 alebo 7, znak je '-'
				i++;
			else 
				break;
	}
	if ( *(c + i) == '\0' && i == 10) // Pokiaľ sme cyklom prešli až do ukončujúceho znaku v reťazci, reťazec je vo formáte pre dátum
		return 1; 
	else // reťazec nie je vo formáte pre dátum
		return 0; 
}

char *datum(int d, int m, int y) {

	struct tm date;
	static char datebuff[20];

	date.tm_year = y - 1900;
	date.tm_mon = m - 1;
	date.tm_mday = d;
	date.tm_hour = 0;
	date.tm_min = 0;
	date.tm_sec = 1;
	date.tm_isdst = -1;
	if (mktime(&date) == -1){
		printf("Making time using mktime() failed.\nExiting program ..\n");
		exit(1);
	}
	else {
		strftime(datebuff, sizeof(datebuff), "%A", &date);
		// printf("%d / %d / %d\n", y,m,d); // debug
		return datebuff;
	}
}

int isprime(int n){
	int i = 2;
	while( n%i != 0 && i<=n ) {
		i++;
	}
	if (i == n)
	{
		return 1;
	} else
		return 0;
}