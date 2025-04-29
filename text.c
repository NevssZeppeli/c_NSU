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