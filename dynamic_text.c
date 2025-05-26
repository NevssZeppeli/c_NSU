#include <stdio.h>
#include <stdlib.h>
#include "text.h"  

#define INIT_SIZE 4
#define TERM '#'

char* trim_buffer(char* str, int size){
    char* new_str = malloc(sizeof(char)*size);
    for(int i = 0; i < size; i++) {
        new_str[i] = str[i];
    }
    new_str[size-1] = '\0';
    
    free(str);
    return new_str;
}

char* my_realloc(char* str, int* size){
    (*size)++;
    char* new_str = malloc(sizeof(char) * INIT_SIZE * (*size));
    for(int i = 0; i < INIT_SIZE * (*size); i++) {
        new_str[i] = str[i];
    }
    free(str);
    return new_str;
}

char* get_text(FILE* stream, char terminator) {
    char* str = malloc(sizeof(char) * INIT_SIZE);
    char input = ' ';
    int size = 1; 
    int i = 0;

    while((input != terminator) && (input != EOF)){
        if(stream == NULL)
            input = getchar();
        else
            input = fgetc(stream);
        str[i] = input;
        i++;

        if(i % INIT_SIZE == 0) {
            str = my_realloc(str, &size);
        } 
    }
    str = trim_buffer(str, i);
    printf("size: %d\n", INIT_SIZE*size);
    return str;
}

int main() {
    int choice = 0;
    char* text;

    printf("Выберите метод ввода: \n 1 - с терминала\n 2 - с файла\n");
    scanf("%d", &choice);
    getchar();
    switch (choice)
    {
    case 1:
        printf("Введите строку с терминала:\n");
        text = get_text(NULL, TERM);
        break;
    case 2:
        printf("Открытие с файла sample.txt\n");
        char file_name[30];
        FILE* file = fopen("sample.txt", "r");
        if(!file) {
            perror("Ошибка открытия файла");
            return 1;
        }
        text = get_text(file, TERM);
        fclose(file);
        break;
    default:
        printf("Ошибка ввода");
        return 1;
        break;
    }

    printf("Исходный текст:\n%s\n", text);
    correct(text);
    printf("Исправленный текст:\n%s\n", text);
    free(text);

    return 0;
}


