#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* iritated_Alph(char* Alphabet, int iritation_num);

char* cipher(char* Alphabet, char* iritated_Alph, char* Text);


int main() {
	char Alph[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int l = strlen(Alph);
	char Text[] = "piece in the world";
	int shift = 3;
	
	//iritated_Alph(Alph, shift);
	char* iritated = iritated_Alph(Alph, shift);
	cipher(Alph,iritated,Text);
	
	printf("Text is encrypted into %s", Text);
	
	return 0;
}

char* cipher(char* Alphabet, char* iritated_Alph, char* Text) {
	int Alph_len = strlen(Alphabet);
	int Text_len = strlen(Text);
	for (int i = 0;i < Text_len;i++) {
		Text[i] = toupper(Text[i]);
		for (int j = 0;j < Alph_len;j++) {
			if (Text[i] == Alphabet[j]) {
				Text[i] = iritated_Alph[j];
				break;
			}
		}
	}


	return Text;
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
