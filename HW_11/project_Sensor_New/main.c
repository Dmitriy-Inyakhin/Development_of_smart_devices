// main.c

#include "temp_api.h"

int main(void) {
    TempData data = {0};  // count = 0

    // Добавим несколько записей вручную (как пример)
    add_record(&data, 2025, 3, 10, 8, 30, 12);
    add_record(&data, 2025, 3, 10, 14, 45, 18);
    add_record(&data, 2025, 3, 11, 7, 15, 9);
    add_record(&data, 2025, 4, 5, 10, 0, -2);
    add_record(&data, 2025, 4, 6, 16, 20, 21);

    // Выводим всё
    print_all(&data);

    // Статистика (заглушки)
    print_monthly_stats(&data, 2025, 3);
    print_monthly_stats(&data, 2025, 4);
    print_yearly_stats(&data, 2025);
	
	int a = 0;
	scanf("%d", &a);

    return 0;
}