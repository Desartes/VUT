/* -------------------------------------
 * @file_name: proj1.c    
 * @author   : Filip Kolesar - xkoles06
 *			   1BIT, VUT FIT
 * @date     : 10/2015
 * @version  : 1.0.0     
 ---------------------------------------*/
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
	if (argc > 1) { // pri neprazdnom argumente program vypise svoj kratky popis a skonci
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
					printf("number: %ld (prime)\n", atol(word));
				else
					printf("number: %ld\n", atol(word));
			}
		else 
			if (isdate(&word[0])) {
				int day, month, year;
				sscanf(word, "%4d-%2d-%2d",&year, &month, &day);
			if ( (month <= 12) && (year >= 1901) && (month >= 1) && (day <= 31) && (day >= 1) )
				printf("date: %.3s %s\n", date(day, month, year), word);
			else
				printf("word: %s\n", word);
		}
		else
			printf("word: %s\n", word);
	}
	if (!istext(&word[0])) {
		printf("The characters you\'ve entered are not printable.\n"
			   "Exiting ..\n");
		return 1;
	}

	//printf("%d\n", strlength(&word[0])); // debug
	return 0; 
}

int strlength(char *c) { // Zistenie dlzky slova
	int offset = 0;
	while( *(c + offset) != '\0' ) 
		++offset;
	return offset;
}

int ispalindrom(char *c) { /* ---- Funkcia zistujuca palindrom ---- */
	char new[101];
	int wordlen = strlength(c);

	for (int i = 0; i <= 100; ++i) // Resetovanie obsahu retazca
		new[i] = 0;

	for (int i = 0; i < wordlen; ++i) { // Otacanie slova pre nasledne porovnanie
		//printf("%c", *(c+(wordlen - i - 1)) ); // debug
		new[i] = *(c+(wordlen - i - 1));
	}

	int offset = 0; // Pomocna premenna
	while( *(c + offset) == new[offset] ) { // Porovnavanie dvoch retazcov (po znakoch)
		if ( *(c + offset) == '\0' || new[offset] == '\0' ) // Ak sme na konci niektoreho z retazcov, vyskoc z cyklu
			break;
		offset++; // Dalsi znak v retazci
	}
	if ( *(c + offset) == '\0' && new[offset] == '\0' ) // Pokial sme prisli ku koncu oboch retazcov naraz, retazce sa zhoduju
		return 1;
	else // Reťazce sa nehoduju
		return 0;
	// printf("%s | %s\n", c, new); // Debug mode
}

int isnum(char *c) { /* ---- Funkcia zistujuca ci je retazec cislo ---- */
	int i = 0;
	
	while( *(c + i) != '\0' ) { // Iteracia ktora prejde celym retazcom a vyhodnoti ci je retazec cislo
		if ( !(*(c + i) >= 48 && *(c + i) <= 57) )
			break; // Ak znak v retazci nie je cislo, vyskoc z cyklu
		else 
			i++; // Nasledujuci znak v retazci
	}
	if ( *(c + i) == '\0' ) // Pokial som cyklom presiel až do ukoncujuceho znaku v retazci retazec je cislo
		return 1; 
	else // Retazec nie je cislo
		return 0;
}

int istext(char *c) { /* ---- Funkcia zistujuca ci je retazec zlozeny iba z "tisknutelnych" znakov ASCII tabulky ---- */
	int i = 0;
	
	while( *(c + i) != '\0' ) { 
		if ( !isprint(*(c + i)) ) // rozsah tisknutelnych znakov ASCII
			break; 
		else 
			i++; 
	}
	if ( *(c + i) == '\0' ) // Pokial som na konci slova bez erroru, retazec je z tisknutelnych znakov
		return 1; 
	else // Retazec nie je z tisknutelnych znakov
		return 0;
}

int isdate(char *c) { /* ---- Funkcia zistujuca ci je retazec datum ---- */
	int i = 0;

	while( *(c + i) != '\0' ) { // Iteracia ktora prejde celym reťazcom a vyhodnoti ci je retazec vo formate datumu DDDD-DD-DD
		if ( (*(c + i) >= 48 && *(c + i) <= 57) && (i != 4) && (i != 7) && (i < 10)) // D je cislo a zaroveň nie sme na indexe 4 ani 7
			i++;
		else 
			if ( (i == 4 && (*(c + i) == '-')) || (i == 7 && (*(c + i) == '-')) ) // ak sme na indexe 4 alebo 7, znak je '-'
				i++;
			else 
				break;
	}
	if ( *(c + i) == '\0' && i == 10 ) // Pokial sme cyklom presli az do ukoncujuceho znaku v retazci, retazec je vo formate pre datum
		return 1; 
	else // retazec nie je vo formate pre dátum
		return 0; 
}

char *date(int d, int m, int y) { // mktime
	struct tm date;
	static char datebuff[10];

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
	} else {
		strftime(datebuff, sizeof(datebuff), "%A", &date);
		// printf("%d / %d / %d\n", y,m,d); // debug
		return datebuff;
	}
}

int isprime(int n) { // fukncia pre zistenie prvocisla
	int i = 2;
	while( n%i != 0 && i <= n ) // delenie dvoma, ziskavanie zvysku
		i++;
	if (i == n)
		return 1;
	else
		return 0;
}