#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct data {
    char phone[12];
    char name[255];
    char surname[255];
    char birth_date[10]; // Формат "ДД-ММ-ГГГГ"
} data;

typedef struct CPeople {
    data record;
    struct CPeople* next;
} CPeople;

// Функция для добавления новой записи
void add_new_record(CPeople** head, data record) {
    CPeople* new_node = malloc(sizeof(CPeople));
    new_node->record = record;
    new_node->next = *head;
    *head = new_node;
}

// Функция для удаления записи по ID
int delete_by_id(CPeople** head, int id) {
    
    CPeople* current = *head;
    CPeople* prev = NULL;
    
    for (int i = 1; i < id && current != NULL; i++) {
        prev = current;
        current = current->next;
    }
    
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current);
    return 0;
}

// Функция для освобождения памяти списка
void free_list(CPeople** head) {
    CPeople* temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

// Функция для печати списка
void print_list(CPeople* head) {
    if (head == NULL) {
        printf("Список контактов пуст.\n");
        return;
    }
    printf("%s  %s  %s %s %s\n\n", "ID", "Телефон   ", "Имя", "Фамилия", "Дата рождения");
    int i = 1;
    while (head != NULL) {
        printf("%d  %s  %s %s %s\n", i, head->record.phone, head->record.name,
               head->record.surname, head->record.birth_date);
        head = head->next;
        i++;
    }
    printf("\n");
}

void save_to_file(CPeople* head, const char* file_name) {
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи.\n");
        return;
    }
    
    CPeople* current = head;
    int id = 1;
    while (current != NULL) {
        fprintf(file, "%d %s %s %s %s\n", id, current->record.phone, current->record.name,
                current->record.surname, current->record.birth_date);
        current = current->next;
        id++;
    }
    fclose(file);
    printf("Контакты сохранены в файл %s\n", file_name);
}

void load_from_file(CPeople** head, const char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла для чтения\n");
        return;
    }
    free_list(head);
    
    data record;
    int id;
    while (fscanf(file, "%d%s%s%s%s", &id, record.phone, record.name, 
                 record.surname, record.birth_date) == 5) {
        add_new_record(head, record);
    }
    fclose(file);
    printf("Контакты успешно загружены из файла %s\n", file_name);
}

void sort_list(CPeople* head, int (*compare)(data, data)) {
    if (head == NULL || head->next == NULL) return;
    
    int swapped; 
    CPeople* current; 
    CPeople* last_unsorted = NULL;
    
    do {
        swapped = 0; 
        current = head;  
        
        while (current->next != last_unsorted) {
            
            if (compare(current->record, current->next->record) > 0) {
              
                data temp = current->record;
                current->record = current->next->record;
                current->next->record = temp;
                swapped = 1; 
            }
            current = current->next;
        }
        last_unsorted = current;

    } while (swapped);
}

int compare_by_name(data a, data b) {
    return strcmp(a.name, b.name);
}

int compare_by_surname(data a, data b) {
    return strcmp(a.surname, b.surname);
}

int compare_by_date(data a, data b) {
    struct tm tm1 = {0}, tm2 = {0};

    strptime(a.birth_date, "%d-%m-%Y", &tm1);
    strptime(b.birth_date, "%d-%m-%Y", &tm2);

    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);
    
    if (time1 < time2) return -1;
    if (time1 > time2) return 1;
    return 0;
}

void book_menu(CPeople** list) {
    int input;
    char file_name[255];
    
    while (1) {
        printf("\nМеню:\n");
        printf("1) Добавить контакт\n");
        printf("2) Удалить контакт\n");
        printf("3) Отсортировать контакты\n");
        printf("4) Экспорт в файл\n");
        printf("5) Импорт из файла\n");
        printf("6) Вывести контакты\n");
        printf("7) Выход\n");
        printf("Выберите действие: ");
        
        scanf("%d", &input);
        getchar(); 
        
        switch (input) {
            case 1: {
                data new_record;
                printf("\nВведите номер телефона (11 цифр): ");
                scanf("%s", new_record.phone);
                printf("Введите имя: ");
                scanf("%s", new_record.name);
                printf("Введите фамилию: ");
                scanf("%s", new_record.surname);
                printf("Введите дату рождения (ДД-ММ-ГГГГ): ");
                scanf("%s", new_record.birth_date);
                add_new_record(list, new_record);
                printf("Контакт успешно добавлен.\n");
                break;
            }
            case 2: {
                print_list(*list);
                if (*list != NULL) {
                    int id;
                    printf("Укажите ID контакта для удаления: ");
                    scanf("%d", &id);
                    if (delete_by_id(list, id) == 0) {
                        printf("Контакт успешно удален.\n");
                    } else {
                        printf("Ошибка: неверный ID.\n");
                    }
                }
                break;
            }
            case 3: {
                if (*list == NULL) {
                    printf("Список контактов пуст.\n");
                    break;
                }
                int sort_type;
                printf("\nСпособы сортировки:\n");
                printf("1) По имени\n");
                printf("2) По фамилии\n");
                printf("3) По дате рождения\n");
                printf("Выберите способ сортировки: ");
                scanf("%d", &sort_type);
                
                switch (sort_type) {
                    case 1:
                        sort_list(*list, compare_by_name);
                        printf("Контакты отсортированы по имени.\n");
                        break;
                    case 2:
                        sort_list(*list, compare_by_surname);
                        printf("Контакты отсортированы по фамилии.\n");
                        break;
                    case 3:
                        sort_list(*list, compare_by_date);
                        printf("Контакты отсортированы по дате рождения.\n");
                        break;
                    default:
                        printf("Неверный выбор сортировки.\n");
                        break;
                        return;
                }
                print_list(*list);
                break;
            }
            case 4: {
                if (*list == NULL) {
                    printf("Список контактов пуст.\n");
                    break;
                }
                printf("Введите имя файла для экспорта: ");
                scanf("%s", file_name);
                save_to_file(*list, file_name);
                break;
            }
            case 5: {
                printf("Введите имя файла для импорта: ");
                scanf("%s", file_name);
                load_from_file(list, file_name);
                print_list(*list);
                break;
            }
            case 6: {
                print_list(*list);
                break;
            }
            case 7:
                return;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
                break;
        }
    }
}

int main() {
    CPeople* list = NULL;
    book_menu(&list);
    free_list(&list);
    return 0;
}