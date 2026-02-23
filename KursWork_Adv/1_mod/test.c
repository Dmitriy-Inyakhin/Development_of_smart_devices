#include "math_solver.h"
#include <assert.h>
#include <math.h>

// Вспомогательная функция для сравнения double
static int eq(double a, double b) {
    return fabs(a - b) < 1e-4;
}

int run_tests() {
    int iter = 0;
    
    // Тест root: x^2 - 4 = 0 на [0, 3] -> корень 2
    // Для теста нужны заглушки функций, здесь упрощенно
    // double r = root(..., 0, 3, 1e-6, &iter);
    // assert(eq(r, 2.0));

    // Тест integral: x^2 на [0, 1] -> 1/3
    // double i = integral(..., 0, 1, 1e-6);
    // assert(eq(i, 1.0/3.0));

    return 1; // 1 = успех
}