#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* iritated_Alph(char* Alphabet, int iritation_num);


char* Decryption(char* Alphabet,char* iritated_Alph,char* crypt);


int main() {
	char Alph[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int l = strlen(Alph);
	char Crypted[] = "PRQRSROB";
	int shift = 3;
	
	//iritated_Alph(Alph, shift);
	char* iritated = iritated_Alph(Alph, shift);
	Decryption(Alph,iritated, Crypted);

	printf("Text is decrypted into %s", Crypted);
	
	return 0;
}
char* Decryption(char* Alphabet,char* iritated_Alph, char* crypt) {
	int Alph_len = strlen(iritated_Alph);
	int Crp_len = strlen(crypt);

	for (int i = 0;i < Crp_len;i++) {
		crypt[i] = toupper(crypt[i]);
		for (int j = 0;j < Alph_len;j++) {
			if (crypt[i] == iritated_Alph[j]) {
				crypt[i] = Alphabet[j];
				break;
			}
		}
	}


	return crypt;
}


char* iritated_Alph(char* Alphabet, int iritation_num) {
	char* iritated = malloc(sizeof(Alphabet) + 1);
	int Alph_len = strlen(Alphabet);
	if (iritation_num < 0) {
		iritation_num = iritation_num - iritation_num - iritation_num;
		iritation_num = Alph_len + iritation_num;
	}

	for (int i = 0;i < Alph_len - iritation_num;i++) {
		iritated[i] = Alphabet[i + iritation_num];
	}
	int j = 0;
	for (int i = Alph_len - iritation_num;i < Alph_len;i++) {
		iritated[i] = Alphabet[j++];
	}

	iritated[Alph_len] = '\0';


	return iritated;
}
