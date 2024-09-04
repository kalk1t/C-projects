#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define length 26
#define buff_size 100
void decryption_word(char* Alpha, char key_word[], char* ciphered);
void decryption_alpha(char* Alpha, char key_let);

void encryption_word(char* sentence, char* Alphabet, char key, char Main_Alpha);
int encryption_alpha(char* Alpha, char Letter, char sen_letter);

int main(){
	char Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char Main_Alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int sw = 0;
	char plain_word[buff_size];
	char key_word[buff_size];
	printf("***** Vigenere Cipher *****\n\n\n\n");

	printf("1.Encryption\n");
	printf("2.Decryption\n");
	printf("Choose the operation :\n");
	scanf("%d", &sw);

	switch (sw) {
	case 1: {
		printf("Enter the key word : \n");
		scanf("%s", &key_word);
		printf("Enter the text for encryption :\n");
		scanf("%s", &plain_word);
		encryption_word(plain_word, Alphabet, key_word, Main_Alpha);
		printf("Encrypted word with key - %s - is --> %s", key_word, plain_word);
	}
		  break;
	case 2: {
		printf("Enter the key_word : \n");
		scanf("%s", &key_word);
		printf("Enter the encrypted word for decription\n");
		scanf("%s", plain_word);
		decryption_word(Alphabet, &key_word, plain_word, Main_Alpha);
		printf("Decription of the word with the key - %s - is --> %s", key_word, plain_word);
	}
	}
	return 0;
}

void decryption_word(char* Alphabet, char key_word[], char* ciphered,char Main_Alpha[]) {
	int key_len = strlen(key_word);
	int ciph_len = strlen(ciphered);
	char key_tmp;
	char ciph_tmp;
	int key_count = 0;
	int ciph_pos = 0;

	for (int i = 0;i < ciph_len;i++) {
		if (ciphered[i] == ' ') continue;
		key_tmp = tolower(key_word[key_count]);
		key_count++;
		if (key_count > key_len - 1) key_count = 0;
		decryption_alpha(Alphabet, key_tmp);

		ciph_tmp =tolower(ciphered[i]);
		for (int j = 0;j < length;j++) {
			char alph_tmp = tolower(Main_Alpha[j]);
				if (alph_tmp == ciph_tmp) {
					ciph_pos = j;
					break;
				}
		}
		ciphered[i] = Alphabet[ciph_pos];
	}

		
	

}
void decryption_alpha(char* Alpha, char key_let) {
	int key_let_pos = 0;
	char tmp_array[length];

	for (int i = 0;i < length;i++) {
		tmp_array[i] = Alpha[i];
	}
	for (int i = 0;i < length;i++) {
		char tmp = tolower(tmp_array[i]);
		if (tmp==key_let) {
			key_let_pos = i;
			break;
		}
	}

	for (int i = 0;i <length-key_let_pos;i++) {
		Alpha[i] = tmp_array[key_let_pos + i];
	}
	int j = 0;
	for (int i =length-key_let_pos;i < length;i++) {
		Alpha[i] = tmp_array[j++];
	}



}



void encryption_word(char* sentence, char* Alpha, char key[], char Main_Alpha[]) {
	int text_len = strlen(sentence);
	int key_len = strlen(key);
	int z = 0;
	for (int i = 0;i < text_len;i++) {
		if (sentence[i] == ' ') continue;

		char sen_tmp =tolower( sentence[i]);
		char key_tmp =tolower( key[z]);
		z++;

		if (z > key_len - 1) z = 0;


		int k = encryption_alpha(Alpha, key_tmp, sen_tmp);
		sentence[i] = Main_Alpha[k];
	}
}
int encryption_alpha(char* Alpha, char Letter, char sen_letter) {
	int cipher_pos = 0;
	int sen_letter_pos = 0;
	char temp_array[length];

	for (int i = 0;i < length;i++) {
		temp_array[i] = Alpha[i];
	}
	for (int i = 0;i < length;i++) {
		char tmp = tolower(Alpha[i]);
		if (tmp == sen_letter) {
			sen_letter_pos = i;
			break;
		}
	}

	for (int i = 0;i < length;i++) {
		char tmp = tolower(Alpha[i]);
		if (tmp == Letter) {
			cipher_pos = i;
			break;
		}
	}
	for (int i = 0;i < length - cipher_pos;i++) {
		Alpha[i] = temp_array[cipher_pos + i];
	}
	int j = 0;
	for (int i = length - cipher_pos;i < length;i++) {
		Alpha[i] = temp_array[j++];
	}

	int diff = length - cipher_pos;
	int encrypted_letter_pos = sen_letter_pos + diff;
	if (encrypted_letter_pos > length - 1) {
		encrypted_letter_pos = encrypted_letter_pos - length;
	}

	return encrypted_letter_pos;

}
