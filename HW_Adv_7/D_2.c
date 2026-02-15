// Найти брата

// В программе описано двоичное дерево:
// typedef struct tree {
// datatype key;
// struct tree *left, *right;
// struct tree *parent; //ссылка на родителя
// } tree;

// Требуется реализовать функцию, которая по ключу
// возвращает адрес соседнего элемента - брата. Если
// такого ключа нет или у узла нет брата, то необходимо вернуть 0.

// Прототип функции:
// tree * findBrother(tree *root, int key)

// Input

// 10 5 15 3 7 13 18 1 6 14 0 3
// Output
// 7

#include <stdio.h>
#include <stdlib.h>

// Определение типа данных для ключа
typedef int datatype;

// Структура узла бинарного дерева поиска с ссылкой на родителя
typedef struct tree {
    datatype key;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} tree;

// Вставка узла в бинарное дерево поиска с установкой родителя
tree *insert_with_parent(tree *root, datatype key, tree *parent) {
    if (root == NULL) {
        tree *new_node = (tree *)malloc(sizeof(tree));
        if (!new_node) {
            fprintf(stderr, "Ошибка выделения памяти\n");
            exit(1);
        }
        new_node->key = key;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = parent;
        return new_node;
    }

    if (key < root->key) {
        root->left = insert_with_parent(root->left, key, root);
    } else if (key > root->key) {
        root->right = insert_with_parent(root->right, key, root);
    }
    // Если ключ равен, игнорируем (без дубликатов)

    return root;
}

// Функция поиска брата узла по ключу
tree *findBrother(tree *root, int key) {
    if (root == NULL) return NULL;
    
    // Поиск узла с заданным ключом (обход в ширину)
    #define QUEUE_SIZE 1000
    tree *queue[QUEUE_SIZE];
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    tree *target = NULL;
    
    while (front < rear) {
        tree *node = queue[front++];
        if (node->key == key) {
            target = node;
            break;
        }
        if (node->left != NULL) {
            queue[rear++] = node->left;
        }
        if (node->right != NULL) {
            queue[rear++] = node->right;
        }
    }
    
    // Узел не найден
    if (target == NULL) return NULL;
    
    // Корень не имеет брата (у корня нет родителя)
    if (target->parent == NULL) return NULL;
    
    // Определяем брата: если текущий узел — левый потомок, брат — правый, и наоборот
    tree *parent = target->parent;
    if (parent->left == target) {
        return parent->right;  // может быть NULL
    } else {
        return parent->left;   // может быть NULL
    }
}

// Удаление всего дерева
void delete_tree(tree *root) {
    if (root == NULL) return;
    delete_tree(root->left);
    delete_tree(root->right);
    free(root);
}

int main(void) {
    tree *root = NULL;
    datatype value;
    
    // Чтение последовательности чисел до 0 (0 — признак окончания ввода дерева)
    while (scanf("%d", &value) == 1 && value != 0) {
        root = insert_with_parent(root, value, NULL);
    }
    
    // Чтение ключа для поиска брата
    int search_key;
    if (scanf("%d", &search_key) != 1) {
        fprintf(stderr, "Ошибка чтения ключа для поиска\n");
        delete_tree(root);
        return 1;
    }
    
    // Поиск брата
    tree *brother = findBrother(root, search_key);
    
    // Вывод результата
    if (brother != NULL) {
        printf("%d\n", brother->key);
    } else {
        printf("0\n");
    }
    
    // Очистка памяти
    delete_tree(root);
    
    return 0;
}