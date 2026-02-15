// Отсортировать слова

// Дана строка, состоящая из английских букв и пробелов.
// В конце строки символ точка. Все слова разделены одним
// пробелом. Необходимо составить из слов односвязный список
// и упорядочить по алфавиту. Список необходимо удалить в
// конце программы. Для сравнения строк можно использовать
// strcmp.
// Необходимо использовать данную структуры организации списка.
// struct list {
// char word[20];
// struct list *next;
// }
// Необходимо реализовать односвязный список и обслуживающие его функции.

// add_to_list
//  swap_elements
//  print_list
//  delete_list

// Input
// efg abcd zzz.

// Output
// abcd efg zzz

// Input
// fffff kkkkkk a.

// Output
// a fffff kkkkkk

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list
{
    char word[20];
    struct list *next;
} list_t;

list_t *add_to_list(list_t *head, const char *word);
void swap_elements(list_t *a, list_t *b);
void print_list(list_t *head);
void delete_list(list_t *head);

int main(void)
{
    char line[1000];
    // Чтение всей строки
    if (fgets(line, sizeof(line), stdin) == NULL)
    {
        return 1;
    }

    // Удаление символа новой строки
    line[strcspn(line, "\n")] = '\0';

    // Удаление завершающей точки
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '.')
    {
        line[len - 1] = '\0';
    }
    else
    {
        fprintf(stderr, "Ошибка: строка должна заканчиваться точкой\n");
        return 1;
    }

    // Разбор строки на слова
    list_t *head = NULL;
    char *token = strtok(line, " ");
    while (token != NULL)
    {
        if (strlen(token) > 0)
        {
            head = add_to_list(head, token);
        }
        token = strtok(NULL, " ");
    }

    // Сортировка пузырьком с использованием swap_elements
    for (list_t *i = head; i != NULL; i = i->next)
    {
        for (list_t *j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->word, j->word) > 0)
            {
                swap_elements(i, j);
            }
        }
    }

    // Вывод результата
    print_list(head);

    // Очистка памяти
    delete_list(head);

    return 0;
}

// Добавление слова в конец списка
list_t *add_to_list(list_t *head, const char *word)
{
    list_t *new_node = malloc(sizeof(list_t));
    if (!new_node)
    {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }
    strncpy(new_node->word, word, 19);
    new_node->word[19] = '\0';
    new_node->next = NULL;

    if (head == NULL)
    {
        return new_node;
    }
    list_t *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_node;
    return head;
}

// Обмен содержимым слов между двумя узлами
void swap_elements(list_t *a, list_t *b)
{
    char tmp[20];
    strcpy(tmp, a->word);
    strcpy(a->word, b->word);
    strcpy(b->word, tmp);
}

// Вывод списка слов через пробел
void print_list(list_t *head)
{
    if (head == NULL)
    {
        return;
    }
    printf("%s", head->word);
    list_t *current_list = head->next;
    while (current_list != NULL)
    {
        printf(" %s", current_list->word);
        current_list = current_list->next;
    }
    printf("\n");
}

// Удаление всего списка
void delete_list(list_t *head)
{
    list_t *current = head;
    while (current != NULL)
    {
        list_t *next = current->next;
        free(current);
        current = next;
    }
}
