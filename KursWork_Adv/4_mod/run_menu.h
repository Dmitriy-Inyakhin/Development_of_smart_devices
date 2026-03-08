#ifndef RUN_MENU_H
#define RUN_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>

// --- Константы ---
#define MAIN_MENU_ITEMS 10
#define MAX_INPUT_LEN 20

extern const char *main_menu[];
extern const char *methods[];
extern const char *methods_square[];
extern const char *functions1[];
extern const char *functions2[];

// Состояние программы
typedef struct
{
    double start_interval;
    double end_interval;
    double epsylion;
    int method_id;    // метод расчета корней
    int method_square; // метод расчета площади
    int function1_id; // первая функция
    int function2_id; // вторая функция
} AppState;

/* --- Прототипы функций --- */
/* ---- Функция init_ncurses выполняет инициализацию библиотеки ncurses: 
 *      включает режим cbreak, отключает эхо, активирует обработку 
 *      специальных клавиш, настраивает цветовые пары и скрывает курсор. ---- */
void init_ncurses(void);

/* ---- Функция end_ncurses выполняет корректное завершение работы 
 *      с ncurses: восстанавливает состояние терминала и освобождает 
 *      ресурсы, выделенные библиотекой. ---- */
void end_ncurses(void);

/* ---- Функция draw_main_menu выполняет отрисовку главного меню 
 *      в отдельном окне с рамкой, заголовком и подсветкой текущего 
 *      пункта, передаваемого через параметр highlight. ---- */
void draw_main_menu(int highlight);

/* ---- Функция show_status_bar выполняет отображение строки состояния 
 *      в нижней части экрана с текущими значениями параметров: 
 *      выбранный метод, функции, интервал и точность (epsylion). ---- */
void show_status_bar(AppState *state);

/* ---- Функция show_help выполняет вывод информационного окна 
 *      с краткой справкой по использованию программы, навигации 
 *      и последовательности действий пользователя. ---- */
void show_help(void);

/* ---- Функция get_number_input выполняет интерактивный ввод 
 *      вещественного числа (double) в указанном окне ncurses 
 *      с поддержкой знака минус, десятичной точки и обработки 
 *      клавиш Backspace/Esc; возвращает введённое значение или 
 *      -1.0 при отмене ввода. ---- */
double get_number_input(WINDOW *win, int y, int x);

/* ---- Функция run_epsilon_submenu выполняет запуск подменю 
 *      для ввода значения точности вычислений (epsylion), 
 *      включая валидацию (0 < eps < 1) и сохранение результата 
 *      в структуре AppState. ---- */
void run_epsilon_submenu(AppState *state);

/* ---- Функция run_interval_submenu выполняет запуск подменю 
 *      для ввода границ расчётного интервала [start, end] 
 *      с поддержкой отрицательных и вещественных чисел, 
 *      проверкой условия end >= start и сохранением в AppState. ---- */
void run_interval_submenu(AppState *state);

/* ---- Функция run_simple_list_submenu выполняет отображение 
 *      универсального подменю-списка для выбора одного из 
 *      предложенных вариантов (методы, функции) с навигацией 
 *      стрелками, выделением текущего пункта и пунктом выхода; 
 *      параметр type определяет, в какое поле AppState записать 
 *      результат выбора. ---- */
void run_simple_list_submenu(AppState *state, const char *title, const char **items, int count, int type);

/* ---- Функция show_result выполняет вывод информационного окна 
 *      с результатами выполненных расчетов. ---- */
void show_result(double result);
#endif
