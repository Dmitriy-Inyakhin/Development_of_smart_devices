// Вид сверху

// В программе описана структура для хранения двоичного дерева:
// typedef struct tree {
// datatype key;
// struct tree *left, *right;
// } tree;
// Необходимо реализовать функцию, которая печатает вид дерева
// сверху.
// Функция должна строго соответствовать прототипу:
// void btUpView(tree *root)
// Input

// 10 5 15 3 7 13 18 1 6 14 0
// Output

// 1 3 5 10 15 18

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Определение типа данных для ключа
typedef int datatype;

// Структура узла бинарного дерева поиска
typedef struct tree
{
    datatype key;
    struct tree *left, *right;
} tree;

// Вставка узла в бинарное дерево поиска
tree *insert(tree *root, datatype key)
{
    if (root == NULL)
    {
        tree *new_node = (tree *)malloc(sizeof(tree));
        if (!new_node)
        {
            fprintf(stderr, "Ошибка выделения памяти\n");
            exit(1);
        }
        new_node->key = key;
        new_node->left = new_node->right = NULL;
        return new_node;
    }

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    // Если ключ равен, игнорируем (без дубликатов)

    return root;
}

// Удаление всего дерева
void delete_tree(tree *root)
{
    if (root == NULL)
        return;
    delete_tree(root->left);
    delete_tree(root->right);
    free(root);
}

// Функция для вывода "вида сверху" дерева
// с использованием #include <stdbool.h>
void btUpView_bool(tree *root)
{
    if (root == NULL)
    {
        printf("\n");
        return;
    }

// Для поддержки отрицательных горизонтальных расстояний используем смещение
#define HD_OFFSET 1000
#define MAX_HD (2 * HD_OFFSET + 1)
#define QUEUE_SIZE 10000

    bool seen[MAX_HD] = {false};
    datatype keys[MAX_HD];

    // Элемент очереди для BFS: узел + его горизонтальное расстояние
    typedef struct
    {
        tree *node;
        int hd;
    } QueueNode;

    QueueNode queue[QUEUE_SIZE];
    int front = 0, rear = 0;

    // Начинаем с корня (горизонтальное расстояние = 0)
    queue[rear].node = root;
    queue[rear].hd = 0;
    rear++;

    int min_hd = 0, max_hd = 0;

    // Обход в ширину (BFS)
    while (front < rear)
    {
        QueueNode current = queue[front++];
        tree *node = current.node;
        int hd = current.hd;

        // Обновляем границы горизонтальных расстояний
        if (hd < min_hd)
            min_hd = hd;
        if (hd > max_hd)
            max_hd = hd;

        int idx = hd + HD_OFFSET;

        // Первый узел для данного hd — самый верхний (благодаря BFS)
        if (!seen[idx])
        {
            seen[idx] = true;
            keys[idx] = node->key;
        }

        // Обрабатываем левого потомка (hd уменьшается)
        if (node->left != NULL)
        {
            queue[rear].node = node->left;
            queue[rear].hd = hd - 1;
            rear++;
        }

        // Обрабатываем правого потомка (hd увеличивается)
        if (node->right != NULL)
        {
            queue[rear].node = node->right;
            queue[rear].hd = hd + 1;
            rear++;
        }
    }

    // Выводим узлы в порядке возрастания горизонтального расстояния
    bool first = true;
    for (int hd = min_hd; hd <= max_hd; hd++)
    {
        int idx = hd + HD_OFFSET;
        if (seen[idx])
        {
            if (!first)
                printf(" ");
            printf("%d", keys[idx]);
            first = false;
        }
    }
    printf("\n");
}

// Функция для вывода "вида сверху" дерева
// без  использования #include <stdbool.h>
void btUpView(tree *root)
{
    if (root == NULL)
    {
        printf("\n");
        return;
    }

    // Для поддержки отрицательных горизонтальных расстояний используем смещение
    #define HD_OFFSET 1000
    #define MAX_HD (2 * HD_OFFSET + 1)
    #define QUEUE_SIZE 10000

    int seen[MAX_HD] = {0};          // вместо bool: 0 = false, 1 = true
    datatype keys[MAX_HD];

    // Элемент очереди для BFS: узел + его горизонтальное расстояние
    typedef struct
    {
        tree *node;
        int hd;
    } QueueNode;

    QueueNode queue[QUEUE_SIZE];
    int front = 0, rear = 0;

    // Начинаем с корня (горизонтальное расстояние = 0)
    queue[rear].node = root;
    queue[rear].hd = 0;
    rear++;

    int min_hd = 0, max_hd = 0;

    // Обход в ширину (BFS)
    while (front < rear)
    {
        QueueNode current = queue[front++];
        tree *node = current.node;
        int hd = current.hd;

        // Обновляем границы горизонтальных расстояний
        if (hd < min_hd)
            min_hd = hd;
        if (hd > max_hd)
            max_hd = hd;

        int idx = hd + HD_OFFSET;

        // Первый узел для данного hd — самый верхний (благодаря BFS)
        if (!seen[idx])  // seen[idx] == 0
        {
            seen[idx] = 1;  // true
            keys[idx] = node->key;
        }

        // Обрабатываем левого потомка (hd уменьшается)
        if (node->left != NULL)
        {
            queue[rear].node = node->left;
            queue[rear].hd = hd - 1;
            rear++;
        }

        // Обрабатываем правого потомка (hd увеличивается)
        if (node->right != NULL)
        {
            queue[rear].node = node->right;
            queue[rear].hd = hd + 1;
            rear++;
        }
    }

    // Выводим узлы в порядке возрастания горизонтального расстояния
    int first = 1;  // true
    for (int hd = min_hd; hd <= max_hd; hd++)
    {
        int idx = hd + HD_OFFSET;
        if (seen[idx])  // seen[idx] == 1
        {
            if (!first)  // first == 0
                printf(" ");
            printf("%d", keys[idx]);
            first = 0;  // false
        }
    }
    printf("\n");
}

int main()
{
    tree *root = NULL;
    datatype value;

    // Чтение последовательности чисел до 0 (0 — признак окончания ввода)
    while (scanf("%d", &value) == 1 && value != 0)
    {
        root = insert(root, value);
    }

    // Вывод "вида сверху"
    btUpView(root);

    // Очистка памяти
    delete_tree(root);

    return 0;
}