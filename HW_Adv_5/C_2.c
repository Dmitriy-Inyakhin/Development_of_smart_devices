///  /Users/admin/STM32Cube/Repository/
//   /Users/admin/STM32CubeIDE/workspace_1.17.0
// Польская запись

// Необходимо вычислить выражение написанное в обратной польской 
// записи. На вход подается строка состоящая из целых, неотрицательных 
// чисел и арифметических символов. В ответ единственное целое число - 
// результат. Более подробно об Обратной польскаязапись числа можно также почитать тут
// Input

//         3 4 +.
// Output

//         7
// Input

//         1 2 + 4 × 3 +.
// Output

//         15
// Input

//         100 25 + 25 /.
// Output

//         5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 5000

int main() {
    char line[10005];
    
    // Чтение всей строки (включая пробелы)
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 1;
    }
    
    // Удаление символов перевода строки (\r, \n)
    line[strcspn(line, "\r\n")] = '\0';
    
    // Обрезание строки до точки (включительно)
    char *dot = strchr(line, '.');
    if (dot != NULL) {
        *dot = '\0';
    }
    
    // Стек для хранения чисел
    int stack[STACK_SIZE];
    int top = -1;  // индекс вершины стека
    
    // Разбор токенов, разделённых пробелами
    char *token = strtok(line, " ");
    while (token != NULL) {
        // Пропуск пустых токенов
        if (token[0] == '\0') {
            token = strtok(NULL, " ");
            continue;
        }
        
        // Проверка: является ли токен числом (неотрицательным целым)
        int is_number = 1;
        for (int i = 0; token[i] != '\0'; ++i) {
            if (!isdigit(token[i])) {
                is_number = 0;
                break;
            }
        }
        
        if (is_number) {
            // Преобразование строки в число и помещение в стек
            stack[++top] = atoi(token);
        } else {
            // Обработка оператора
            if (top < 1) {
                return 1;  // недостаточно операндов (ошибка в выражении)
            }
            
            int b = stack[top--];  // правый операнд
            int a = stack[top--];  // левый операнд
            int result = 0;
            
            switch (token[0]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    if (b == 0) return 1;  // деление на ноль
                    result = a / b;        // целочисленное деление
                    break;
                default:
                    return 1;  // неизвестный оператор
            }
            
            stack[++top] = result;
        }
        
        token = strtok(NULL, " ");
    }
    
    // В корректном выражении в стеке остаётся ровно один элемент — результат
    if (top != 0) {
        return 1;
    }
    
    printf("%d\n", stack[0]);
    return 0;
}
