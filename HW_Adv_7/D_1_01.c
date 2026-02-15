#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Определение типа данных для ключа
typedef int datatype;

// Структура узла бинарного дерева поиска
typedef struct tree
{
    datatype key;
    struct tree *left, *right;
} tree;

// Вспомогательная функция: получение ширины представления числа
static int get_width(datatype value)
{
    if (value == 0)
        return 1;
    int w = 0;
    if (value < 0)
    {
        w = 1;
        value = -value;
    }
    while (value > 0)
    {
        w++;
        value /= 10;
    }
    return w;
}

// Вспомогательная функция для рекурсивной печати (повёрнутое дерево)
static void print_recursive(tree *node, int space, const char *prefix, int is_left, int is_root)
{
    if (node == NULL)
        return;

    const int SPACE = 4;
    space += SPACE;

    // Печать правого поддерева первым (чтобы дерево росло вниз)
    print_recursive(node->right, space, "    ", 0, 0);

    // Печать текущего узла с веткой
    printf("\n");
    for (int i = SPACE; i < space - SPACE; i++)
        printf(" ");
    if (!is_root)
    {
        printf("%s", prefix);
        printf(is_left ? "L── " : "R── ");
    }
    printf("%d", node->key);

    // Печать левого поддерева
    print_recursive(node->left, space, "    ", 1, 0);
}

// Основная функция печати дерева (повёрнутое на 90° представление)
void print_tree(tree *root)
{
    if (root == NULL)
    {
        printf("Дерево пустое\n");
        return;
    }

    printf("Дерево:\n");
    print_recursive(root, 0, "", 0, 1);
    printf("\n");
}

// Функция для вывода "вида сверху" дерева
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

int main(void)
{
    tree *root = NULL;
    datatype value;

    // Чтение последовательности чисел до 0 (0 — признак окончания ввода)
    while (scanf("%d", &value) == 1 && value != 0)
    {
        root = insert(root, value);
    }

    // Печать дерева в красивом виде
    print_tree(root);

    // Вывод "вида сверху"
    printf("Вид сверху:\n");
    btUpView(root);

    // Очистка памяти
    delete_tree(root);

    return 0;
}