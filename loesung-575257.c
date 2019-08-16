#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <time.h>

#define MODE_WB (1)								/*mode: lese Wörterbuch*/
#define MODE_IN (2)								/*mode: lese Input*/
#define collisionParameter (47)        		/*hashset + 47 bei kolision MUSS primzahl sein*/

unsigned long hashtableSize = 2;   				/*MUSS power of 2 sein, besser 16,32 oder 64 wegen verdoppelung der hashtabelle*/
												/*unsigned int -> 2147483647, 32 Bit unsigned long 9223372036854775807, 64 Bit*/

struct element {
	char *key;
	char *value;
} *ht;

unsigned long countElements; 					/*anzahl element in der hashtabelle*/

unsigned long hashFunktion(const char *k) {
	unsigned long result = 0;
	while (*k) {
		result += result + (unsigned char) *k++;
	}
	return result & (hashtableSize - 1);
}

void initHashtabelle(void){
	unsigned long i;
	countElements = 0;
	ht = (struct element *) malloc(sizeof(*ht)*hashtableSize);
	for (i = 0; i < hashtableSize; i++){
		ht[i].key = NULL;
		ht[i].value = NULL;
	}
}

char searchHashtabelle(const char *k, unsigned long *index){ /*gefunden (1) == index des element; 0 == position wo gespeichert werden kann*/
	unsigned long i;
	*index = hashFunktion(k);
	i = *index;
	do {
		if (NULL == ht[*index].key) {
			return 0;
		}
		if (0 == strcmp(k, ht[*index].key)) {
			return 1;
		}
		*index = (*index + collisionParameter) & (hashtableSize - 1);
	} while (*index != i);
	return 0;
}

void resizeHashtabelle(void){
	unsigned long i, hashInd;
	struct element *tabelleAktuell;
	tabelleAktuell = ht;
	/* verdoppeln */
	hashtableSize *= 2;
	ht = (struct element *) malloc(sizeof(*ht)*hashtableSize);
	for (i = 0; i < hashtableSize; i++) {
		ht[i].key = NULL;
		ht[i].value = NULL;
	}
	/* tabelle verschieben */
	for (i = 0; i < (hashtableSize >> 1); i++) {
		if (tabelleAktuell[i].key != NULL) {
			/* jedes element verschieben */
			if (!searchHashtabelle(tabelleAktuell[i].key, &hashInd)) {
				ht[hashInd] = tabelleAktuell[i];
			}
			else {
				printf("Fehler beim Vergrößern der Hashtabell!\n");
			}
		}
	}
	/* alte löschen */
	free(tabelleAktuell);
}

void inseartHashtabelle(char *k, char *val){

	unsigned long i;
	if (!searchHashtabelle(k, &i)) {/* wenn key nicht gefunden */
		ht[i].key = strdup(k);
		ht[i].value = strdup(val);
		if (++countElements > ((unsigned long) hashtableSize * 0.9)) { /* 0.9 ist füllfaktor in der hashtabelle 0.9 = countElements/hashtableSize */
			resizeHashtabelle();
		}
	}
	else {
		printf("%s <ist Duplikat> %ld\n", ht[i].key, countElements);
	}
}

void freeHashtabelle(void){
	unsigned long i;
	for (i = 0; i < hashtableSize; i++) {
		if (ht[i].key != NULL) {
			free(ht[i].key);
			free(ht[i].value);
		}
	}
	free(ht);
}

static char * toLowercase(char *key) {
	
    char *low = strdup(key);
    unsigned long i = 0;
  
    while (low[i]) {
        low[i] = (tolower(low[i])); 
        i++; 
    }
	
	return low;
}

/*
zeile_lesen->MODE->separate->inseartHashtabelle(key, val)
			|| 	 ->modifizieren->searchHashtabelle(const char *k, unsigned long *index)

*/

/*immer groesse für ein char haben; dann c an position size-1; iff \n oder EOF dann \0 dann an split dann size zurück auf 0 und erneut;bei EOF noch raus aus der schleife */
static char *zeile_lesen(FILE *f, int mod){
    char c;
	char *zeile = NULL;
	int size = 0;
	int n = 0;
	char *test;
	
	if (mod == 1){
		test = "WB gelesen!";
	} else {
		test = "Input gelesen!";
	}
		
	while ((c = fgetc(f))){
		size++;//erstes c size 1
		
		if (zeile == NULL){zeile = (char *)malloc(sizeof(char) * size);}
		else{zeile = (char *)realloc(zeile, sizeof(char) * size);}
		
		if ((c == '\n') && (mod == 1)){
			c = '\0';
			n++;
		}

		zeile[size - 1] = c;

		if (c == '\0'){
//			if (!(size-1)) printf("%d. Zeile ist leer\n", n);
//			else printf("%d. Zeile gelesen: %s (Laenge: %d) \n", n, zeile, size-1);
			if (!check_wb (zeile, size)) {
				test = "WRONG WB!";
				return test;
			}
			zeile_splitten (zeile, size);
			size = 0;
		}
		
		if (c == EOF) {
			if (mod == 1){
				zeile[size - 1] = '\0';
				n++;
//				if (!(size-1)) printf("%d. Zeile ist leer\n", n);
//				else printf("%d. (letzte) Zeile gelesen: %s (Laenge: %d) \n", n, zeile, size-1);
				if (!check_wb (zeile, size)) {
					test = "WRONG WB!";
					return test;
				}
				zeile_splitten (zeile, size);
				size = 0;
			}
			else {
				zeile[size-1] = '\0';
//				if (!(size-1)) printf("Input ist leer\n");
//				else printf("Input gelesen: %s (Laenge: %d) \n", zeile, size-1);
				if (input_splitten (zeile, size)) {
//					printf("+++++++Input gesplittet+++++++\n");
				}
			}
			break;
		}
	}//while end
	

	free(zeile);

	return test;

}
int check_wb (char *zeile, int size) {
	int i;
	int doublepts_count = 0;
	
	char *line = strdup(zeile);
	
	for (i = 0; zeile[i] != '\0'; i++) {
		if((zeile[i]>='a' && zeile[i]<='z') || zeile[i]==':'){
			if (zeile[i] == ':') {
				doublepts_count++;
			}
		}
		else {
			printf("kein Buchstabe: |%c| \n",zeile[i]);
			return 0;
		}
	}

	if ((doublepts_count != 1) && (size != 1)) {
		printf("Doppelpunkte |%d| \n",doublepts_count);
		return 0;
	}
	return 1;
}

int zeile_splitten (char *zeile, int size) {
	
//	if (!(size-1)) printf("Zeile ist leer\n");
//	else printf("Zeile gelesen: %s (Laenge: %d) \n", zeile, size-1);
	
	char *line = strdup(zeile); 
	char *key = strtok(line, ":");
	char *value = strtok(NULL, ":");
	
	if (key != NULL || value !=NULL) {
		inseartHashtabelle(key, value);
	}
	
	return 1;

}
//c isalpha ->next isalpha->weiter in string					c !alpha ->next !alpha->weiter in string
//			->next !alpha->gehe in string für hash 						->next alpha->gehe in string für print

int input_splitten (char *line, int sizeS) {
	
//	if (!(sizeS-1)) printf("Zeile ist leer\n");
//	else printf("Zeile aus Input gelesen: %s (Laenge: %d) \n", line, sizeS-1);
	
	char c;
	char *zeile = NULL;
	char *zeile2 = NULL;
	int sizeA = 0;
	int sizeN = 0;	
	int k = 0;
	
	unsigned long i;
	
	while (line[k]){ // line[k]!=0 oder line0[k]!='\0'
		
		c = line[k];
		
		if (isalpha(c)) { sizeA++;}
		if (!isalpha(c)) { sizeN++;}
		
		if (zeile == NULL){zeile = (char *)malloc(sizeof(char) * sizeA);}
		else{zeile = (char *)realloc(zeile, sizeof(char) * sizeA);}
		
		if (zeile2 == NULL){zeile2 = (char *)malloc(sizeof(char) * sizeN);}
		else{zeile2 = (char *)realloc(zeile2, sizeof(char) * sizeN);}
		
		if (isalpha(c)) {
			if (sizeN) {
				zeile2[sizeN] = '\0';
				printf("%s", zeile2);
				sizeN = 0;
				zeile2 = NULL;	
			}
			zeile[sizeA - 1] = c;
		}
		else {
			if (sizeA) {
				zeile[sizeA] = '\0';
				if (!searchHashtabelle(toLowercase(zeile), &i)) {/*wenn wort kleingeschrieben nicht im WB*/
					printf("<%s>", zeile);
				}
				else {
					printf("%s", ht[i].value);
				}
				sizeA = 0;
				zeile = NULL;	
			}
			zeile2[sizeN - 1] = c;
		}
		k++;
	}
	if (sizeA) {
		zeile[sizeA] = '\0';
		if (!searchHashtabelle(toLowercase(zeile), &i)) {/*wenn wort kleingeschrieben nicht im WB*/
			printf("<%s>", zeile);
		}
		else {
			printf("%s", ht[i].value);
		}
	}
	if (sizeN) {
		zeile2[sizeN] = '\0';
		printf("%s", zeile2);
	}
	
	printf("\n\n");

	free(zeile);
	free(zeile2);

	return 1;
}

int main(int argc, char *argv[]) {
	
	clock_t timer;
	timer = clock();
	
	const char *f_wb, *f_in;
	FILE *file_wb, *file_in;
	
	initHashtabelle();
	
/*	
	f_wb = argv[1];
	f_in = stdin;

*/
	
    if(argc == 3) {
		f_wb = argv[1];
		f_in = argv[2];
	}
    else {
		f_wb = "example10016.wb";
		f_in = "example10016.stdin";
	}
	
//WB lesen
    file_wb = fopen(f_wb, "r");
	
	char *test = zeile_lesen(file_wb, MODE_WB);
//	printf("%s\n", test);
		
	if(fclose(file_wb)) {
		printf("Fehler beim Schliessen der Datei %s\n", f_wb);
	}
    else {
//		printf("\nDatei %s geschlossen\n\n", f_wb);
	}
//Input lesen
    file_in = fopen(f_in, "r");
	
	char *in = zeile_lesen(file_in, MODE_IN);
//	printf("%s\n", in);
		
	if(fclose(file_in)) {
		printf("Fehler beim Schliessen der Datei %s\n", f_in);
	}
    else {
//		printf("\nDatei %s geschlossen\n\n", f_in);
	}
	
	freeHashtabelle();
	
	timer = clock() - timer;
	printf("\nLief in %f Sekunden\n", (float)timer / (float)CLOCKS_PER_SEC);

	return 0;
}
