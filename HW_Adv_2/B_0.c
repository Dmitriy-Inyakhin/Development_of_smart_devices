// Описана структура данных
// typedef struct list {
// uint64_t address;
// size_t size;
// char comment[64];
// struct list *next;
// } list;
// Требуется реализовать только одну функцию, которая в
// данном списке находит адрес блока памяти занимающий
// больше всего места.
// Адрес хранится в поле address, поле size - соответствующий
// размер данного блока. Если список пустой, то функция
// должна возвращать 0. Если есть несколько таких блоков, т
// о вернуть адрес любого из них.
// Прототип функции:

// uint64_t findMaxBlock(list *head)
// Input

// 3
// 	  140525067852320 10
// 	  140525067852350 30
// 	  140525067852900 100
// Output

// 140525067852900
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

//структура в виде односвязанного списка
typedef struct list
{
    uint64_t address;
    size_t size;
    char comment[64];
    struct list *next; // ссылка на следующий элемент списка
} list;

uint64_t findMaxBlock(list *head)
{
    uint64_t result_address = 0;
    size_t max_size = 0;

    list *current = head;
    while (current != NULL)
    {
        if (max_size < current->address)
        {
            result_address = current->address;
            max_size = current->size;
        }
        current = current->next;
    }
    return result_address;
}

// Функция добавления Ноды в список
list *createNode(uint64_t address, size_t size, const char *comment)
{
    list *node = (list *)malloc(sizeof(list));
    if (node == NULL)
    {
        return NULL; // не удалось выделить память
    }

    node->address = address;
    node->size = size;
    // Копируем комментарий, но не более 63 символов + завершающий '\0'
    if (comment != NULL)
    {
        strncpy(node->comment, comment, sizeof(node->comment) - 1);
        node->comment[sizeof(node->comment) - 1] = '\0'; // гарантируем завершение
    }
    else
    {
        node->comment[0] = '\0'; // пустая строка
    }

    node->next = NULL;
    return node;
}

int main(int argc, char **argv)
{
    list* head = NULL;

    // Создаём узлы
    list *n1 = createNode(140525067852320ULL, 10, "block1");
    list *n2 = createNode(140525067852350ULL, 30, "block2");
    list *n3 = createNode(140525067852900ULL, 100, "block3");

    // Связываем в список
    head = n1;
    n1->next = n2;
    n2->next = n3;

    uint64_t addr = findMaxBlock(head);
    printf("%" PRIu64 "\n", addr); // Выведет: 140525067852900

    // Освобождение памяти (по желанию)
    while (head)
    {
        list *tmp = head;
        head = head->next;
        free(tmp);
    }

    return 0;
}