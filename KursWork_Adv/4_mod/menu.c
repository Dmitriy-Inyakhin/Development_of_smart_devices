#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>

#include "run_menu.h"
#include "math_lib.h"

// --- Основная функция ---
int main(void)
{
    AppState state = {0.0, 0.0, 0.0, -1, -1, -1, -1};
    int choice = 0;
    int c;

    setlocale(LC_ALL, "");
    init_ncurses();

    while (1)
    {
        // erase();  // Очищаем виртуальный экран для перерисовки
        refresh(); // Синхронизируем с физическим экраном

        draw_main_menu(choice);
        show_status_bar(&state);

        refresh(); // Синхронизируем с физическим экраном

        c = getch();
        switch (c)
        {
        case KEY_UP:
            choice = (choice - 1 + MAIN_MENU_ITEMS) % MAIN_MENU_ITEMS;
            break;
        case KEY_DOWN:
            choice = (choice + 1) % MAIN_MENU_ITEMS;
            break;
        case '\n':
        case KEY_ENTER:
            switch (choice)
            {
            case 0:
                show_help();
                break;
            case 1:
                run_interval_submenu(&state);
                break;
            case 2:
                run_simple_list_submenu(&state, "МЕТОД РАСЧЕТА КОРНЕЙ", methods, 4, 1);
                break;
            case 3:
                run_simple_list_submenu(&state, "МЕТОД РАСЧЕТА ПЛОЩАДЕЙ", methods_square, 4, 4);
                break;
            case 4:
                run_simple_list_submenu(&state, "ВЫБОР ПЕРВОЙ ФУНКЦИИ", functions1, 4, 2);
                break;
            case 5:
                run_simple_list_submenu(&state, "ВЫБОР ВТОРОЙ ФУНКЦИИ", functions2, 4, 3);
                break;
            case 6:
                run_epsilon_submenu(&state);
                break;
            case 7:
                show_result(find_root_by_state(&state));
                break;
            case 8:
                show_result(calc_area_by_state(&state));
                break;
            case 9:
                end_ncurses();
                printf("Программа завершена.\n");
                return 0;
            }
            break;
        }
    }
    end_ncurses();
    return 0;
}
