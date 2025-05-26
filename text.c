#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_SIZE 1024


void correct(char* text) {
    char result[MAX_SIZE] = {0};
    int i, j = 0;
    bool spaceFlag = false;
    bool capitalizeNext = true;

    for (i = 0; text[i] != '\0' && j < MAX_SIZE - 1; i++) {
       
        if (isspace(text[i])) {
            if (!spaceFlag && j > 0) {
                result[j++] = ' ';
                spaceFlag = true;
            }
            continue;
        }

     
        if (j > 0 && (text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?') 
            && result[j-1] == ' ') {
            j--;
        }

        
        if (j > 0 && (result[j-1] == '.' || result[j-1] == ',' || result[j-1] == '!' || result[j-1] == '?') 
            && text[i] != ' ' && j < MAX_SIZE - 1) {
            result[j++] = ' ';
        }


        if (capitalizeNext && isalpha(text[i])) {
            result[j++] = toupper(text[i]);
            capitalizeNext = false;
        } else {
            result[j++] = tolower(text[i]);
        }

   
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            capitalizeNext = true;
        }

        spaceFlag = false;
    }

    strncpy(text, result, MAX_SIZE);
    text[MAX_SIZE - 1] = '\0';
}


/* Раскомментировать в случае использования программы как самостоятельной.
int main() {
    char text[MAX_SIZE];

    printf("Введите текст (максимум %d символов):\n", MAX_SIZE - 1);
    fgets(text, MAX_SIZE, stdin);

    correctText(text);

    printf("Исправленный текст:\n%s\n", text);

    return 0;
}
*/

/*
Ниже я приведу мой исходный код в закомментированном виде. Код выдавал баг - съедал буквы в тексте.
С чем был связан баг, мне доподлинно неизвестно, и времени на его искоренение не было. Однако для сохранения он будет ниже.
*/

/*
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100


void correct(char text[]) {
    int i = 0;
    int j = 0;
    int new_sentence = 1;
    int len = strlen(text);
    
    for (i = 0; i < len; i++) {
        if (j > 0 && text[i] == ' ' && text[j-1] == ' ') {
            continue;
        }
        if (text[i] == ' ' && i+1 < len && (text[i+1] == '.' || text[i+1] == ',')) {
            continue;
        }
        if (new_sentence && isalpha(text[i])) {
            text[j++] = toupper(text[i]);
            new_sentence = 0;
            continue;
        } else if (isalpha(text[i])) {
            text[j++] = tolower(text[i]);
            continue;
        }


        if (text[i] == '.' || text[i] == ',') {

            while (j > 0 && text[j-1] == ' ') {
                j--;
            }
            char punct = text[i];
            while (i+1 < len && text[i+1] == punct) {
                i++;
            }
            
            text[j++] = punct;
            new_sentence = (punct == '.');

            if (i+1 < len && text[i+1] != ' ' && text[i+1] != '.' && text[i+1] != ',' && j < MAX_SIZE-1) {
                text[j++] = ' ';
            }
            continue;
        }

        text[j++] = text[i];
    }
    text[j] = '\0';
}

int main() {
    char text[MAX_SIZE];
    
    printf("Введите текст до %d символов:\n", MAX_SIZE);
    fgets(text, MAX_SIZE, stdin);

    printf("Исходный текст:\n%s", text);
    correct(text);
    printf("Исправленный текст:\n%s\n", text);
    
    return 0;
}
*/