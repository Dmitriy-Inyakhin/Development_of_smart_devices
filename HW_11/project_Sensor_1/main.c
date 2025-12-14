// main.c
#include <stdio.h>
#include "temp_api.h"

int main(void) {
    sensor_data d = {0};

    // Загрузка или инициализация
    if (load_data_from_file(&d, "sensor_data.bin") != 0) {
        printf("Fail 'sensor_data.bin' ne nayden ili povrezhden. Ispol'zuem primer.\n");
        init_sample_data(&d);
        save_data_to_file(&d, "sensor_data.bin");
        printf("Primer sohranen v 'sensor_data.bin'\n");
    }

    print_data(&d);

    // Сортировка по температуре
    printf("\nSortirovka po temperature:\n");
    qsort(d.info, d.number, sizeof(sensor), compare_by_temp);
    print_data(&d);

    // Сортировка по дате+времени
    printf("\nSortirovka po date i vremeni:\n");
    qsort(d.info, d.number, sizeof(sensor), compare_by_date);
    print_data(&d);

    // Статистика (заглушки)
    print_monthly_stats(&d);
    print_yearly_stats(&d);

    // Сохранение
    save_data_to_file(&d, "sensor_data.bin");
    printf("\nDannye obnovleny v 'sensor_data.bin'\n");

    int a =0;
    scanf("%d", &a);

    return 0;
}