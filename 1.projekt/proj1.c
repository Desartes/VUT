/* ----------------------------------
 * @file_name: proj1.c    
 * @author: Filip Kolesár - xkoles06
 *			1BIT, VUT FIT
 * @date: 10/2015
 * @version: 1.0.0     
 -----------------------------------*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

int strlength(char *c);
int ispalindrom(char *c);
int isnum(char *c);
int isprime(int i);
int istext(char *c);
int isdate(char *c);
char *date(int d, int m, int y);

int main(int argc, char *argv[]) /* ---------------- MAIN BODY ---------------- */
{
	if (argc > 1 ) { // pri neprazdnom argumente program vypise svoj kratky popis a skonci
		printf("%s is a text parsing program\n"
			   "        which gets text from standard input\n\n"
			   "usage:   <command> < <filename>\n"
			   "example: ./proj1 < data.txt\n", argv[0]);
	return 0;
	} 

	char word[101];

	while( scanf("%100s", word) == 1 && istext(&word[0]) ) {
		if ( ispalindrom(&word[0]) && !isnum(&word[0]) )
			printf("word: %s (palindrome)\n", word);
		else 
			if (isnum(&word[0])) {
				if ( strlength(&word[0]) < 11 && atol(word) <= INT_MAX && isprime(atol(word)) )
					printf("number: %s (prime)\n", word);
				else
					printf("number: %s\n", word);
			}
		else 
			if (isdate(&word[0])) {
				int day, month, year;
			sscanf(word, "%4d-%2d-%2d",&year, &month, &day);
			if ( (month <= 12) && (month >= 1) && (day <= 31) && (day >= 1) )
				printf("date: %.3s %s\n", date(day, month, year), word);
			else
				printf("word: %s\n", word);
		}
		else
			printf("word: %s\n", word);
	}
	if (!istext(&word[0]))
		printf("The characters you\'ve entered are not printable.\n"
			   "Exiting ..\n");
	//printf("%d\n", strlength(&word[0])); // debug
	return 0; 
}

int strlength(char *c) { // Zistenie dĺžky slova
	int offset = 0;
	while( *(c + offset) != '\0') 
		++offset;
	return offset;
}

int ispalindrom(char *c) { /* ---- Funkcia zistujúca palindrom ---- */
	char new[101];
	int wordlen = strlength(c);

	for (int i = 0; i <= 100; ++i) // Resetovanie obsahu reťazca
		new[i] = 0;

	for (int i = 0; i < wordlen; ++i) { // Otáčanie slova pre následné porovnanie
		//printf("%c", *(c+(wordlen - i - 1)) ); // debug
		new[i] = *(c+(wordlen - i - 1));
	}

	int offset = 0; // Pomocná premenná
	while( *(c + offset) == new[offset] ) { // Porovnávanie dvoch reťazcov (po znakoch)
		if ( *(c + offset) == '\0' || new[offset] == '\0' ) // Ak sme na konci niektorého z reťazcov, vyskoč z cyklu
			break;
		offset++; // Ďalší znak v reťazci
	}
	if (*(c + offset) == '\0' && new[offset] == '\0' ) // Pokiaľ sme prišli ku koncu oboch reťazcov naraz, reťazce sa zhodujú
		return 1;
	else // Reťazce sa nehodujú
		return 0;
	// printf("%s | %s\n", c, new); // Debug mode
}

int isnum(char *c) { /* ---- Funkcia zisťujúca či je reťazec číslo ---- */
	int i = 0;
	
	while( *(c + i) != '\0' ) { // Iterácia ktorá prejde celým reťazcom a vyhodnotí či je reťazec číslo
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
	
	while( *(c + i) != '\0' ) { 
		if ( !isprint(*(c + i)) ) // rozsah tisknutelných znakov ASCII 33 - 126
			break; 
		else 
			i++; 
	}
	if ( *(c + i) == '\0' ) // Pokiaľ som na konci slova bez erroru, reťazec je z tisknutelnych znakov
		return 1; 
	else // Retazec nie je z tisknutelnych znakov
		return 0;
}

int isdate(char *c) { /* ---- Funkcia zisťujúca či je reťazec dátum ---- */
	int i = 0;

	while( *(c + i) != '\0' ) { // Iterácia ktorá prejde celým reťazcom a vyhodnotí či je reťazec vo formáte dátumu DDDD-DD-DD
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

char *date(int d, int m, int y) {
	struct tm date;
	static char datebuff[20];

	date.tm_year = y - 1900;
	date.tm_mon = m - 1;
	date.tm_mday = d;
	date.tm_hour = 0;
	date.tm_min = 0;
	date.tm_sec = 1;
	date.tm_isdst = -1;
	if (mktime(&date) == -1) {
		printf("Making time using mktime() failed.\nExiting program ..\n");
		exit(1);
	}
	else {
		strftime(datebuff, sizeof(datebuff), "%A", &date);
		// printf("%d / %d / %d\n", y,m,d); // debug
		return datebuff;
	}
}

int isprime(int n) {
	int i = 2;
	while( n%i != 0 && i <= n )
		i++;
	if (i == n)
		return 1;
	else
		return 0;
}