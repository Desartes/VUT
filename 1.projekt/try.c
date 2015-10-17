/* -----------------------
 * @file_name: proj1.c    
 * @author: Filip Kolesár - xkoles06
 			1BIT, VUT FIT
 * @date: 10/2015
 * @version: 0.6 beta     
 ------------------------*/
#include <stdio.h>
#include <time.h>

int palindrom(char *a);
int isnum(char *c);
int isdate(char *c);
char *datum(int d, int m, int y); 
int prime(int i);

int main() /* ---------------- HLAVNÉ TELO PROGRAMU ---------------- */
{
	char slovo[100];

	while(scanf("%100s", slovo) == 1) {
		if ( palindrom(&slovo[0]) && !isnum(&slovo[0]) )
			printf("word: %s (palindrome)\n", slovo);
		else if (isnum(&slovo[0]))
			printf("number: %s\n", slovo);
		else if (isdate(&slovo[0])) {
			int day, month, year;
			sscanf(slovo, "%4d-%2d-%2d",&year, &month, &day);
			printf("date: %.3s %s\n", datum(day, month, year), slovo);
		}
		else
			printf("word: %s\n", slovo);
	}
	
	return 0; 
}

int palindrom(char *a) { /* ---- Funkcia zistujúca palindrom ---- */
	
	int offset = 0,
		count = 0;
		char new[100];

	for (int i = 0; i < 100; ++i){ // Resetovanie obsahu reťazca
		new[i] = 0;
	}

	while( *(a + offset) != '\0') { // Zistenie dĺžky slova
		++offset;
		++count;
	}
	for (int i = 0; i < count; ++i) { // Otáčanie slova pre následné porovnanie
		//printf("%c", *(a+(count - i - 1)) );
		new[i] = *(a+(count - i - 1));
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
int isdate(char *c) { /* ---- Funkcia zisťujúca či je reťazec dátum ---- */
	int i = 0;

	while( *(c + i) != '\0' ){ // Iterácia ktorá prejde celým reťazcom a vyhodnotí či je reťazec vo formáte dátumu DDDD-DD-DD
		if ( (*(c + i) >= 48 && *(c + i) <= 57) && (i != 4) && (i != 7) ) // D je číslo a zároveň nie sme na indexe 4 ani 7
			i++;
		else 
			if ( (i == 4 && (*(c + i) == '-')) || (i == 7 && (*(c + i) == '-')) ) // ak sme na indexe 4 alebo 7, znak je '-'
				i++;
			else 
				break;
	}
	if ( *(c + i) == '\0' ) // Pokiaľ sme cyklom prešli až do ukončujúceho znaku v reťazci, reťazec je vo formáte pre dátum
		return 1; 
	else // reťazec nie je vo formáte pre dátum
		return 0; 
}
char *datum(int d, int m, int y) {

	struct tm time_str;
	static char daybuf[20];

	time_str.tm_year = y - 1900;
	time_str.tm_mon = m - 1;
	time_str.tm_mday = d;
	time_str.tm_hour = 0;
	time_str.tm_min = 0;
	time_str.tm_sec = 1;
	time_str.tm_isdst = -1;
	if (mktime(&time_str) == -1)
		return NULL;
	else {
		strftime(daybuf, sizeof(daybuf), "%A", &time_str);
		// printf("%d / %d / %d\n", y,m,d); // debug
		return daybuf;
	}
}
int prime(int i){
	
}