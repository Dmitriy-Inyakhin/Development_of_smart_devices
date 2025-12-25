for (int i = 0; i < argc; i++) {
    //     printf("DEBUG: argv[%d] = %s\n", i, argv[i]);
    //     fflush(stdout);
    // }
    
    // uint16_t year = 0;
    // uint8_t month = 0;
    // char *filename = NULL;

    // // Парсим аргументы командной строки
    // int parse_result = parse_arguments(argc, argv, &year, &month, &filename);

    // if (parse_result == 1)
    // {
    //     // Был вызван -h, программа завершается
    //     fprintf(stderr, "Help requested, exiting...\n");
    //     return 0;
    // }
    // else if (parse_result != 0) 
    // {
    //     // Ошибка парсинга
    //     fprintf(stderr, "Failed to parse arguments (error code: %d)\n", parse_result);
    //     fprintf(stderr, "Use -h for help\n");
    //     return 1;
    // }

    // // Проверяем, что имя файла получено
    // if (!filename)
    // {
    //     fprintf(stderr, "No filename provided\n");
    //     return 1;
    // }

    // printf("Parameters: year=%u, month=%u, file=%s\n", year, month, filename);
    // fflush(stdout);

    // // Загрузка данных из файла
    // int load_result = load_data_from_file(&data, filename);

    // if (load_result != 0)
    // {
    //     fprintf(stderr, "Failed to load data from %s (error code: %d)\n",
    //             filename, load_result);
    //     free(filename);
    //     return 1;
    // }

    // printf("Successfully loaded %u records\n", data.number);
    // fflush(stdout);
    
    // // Определяем, какую статистику выводить
    // int stat_result;
    
    // if (month == 0) 
    // {
    //     // Если месяц не указан или равен 0 - выводим годовую статистику
    //     printf("\n=== Yearly statistics ===\n");
    //     fflush(stdout);
    //     stat_result = print_yearly_stats(&data, year);
    // }
    // else 
    // {
    //     // Выводим месячную статистику
    //     printf("\n=== Monthly statistics ===\n");
    //     fflush(stdout);
    //     stat_result = print_monthly_stats(&data, year, month);
    // }
    
    // // Обрабатываем результат вывода статистики
    // if (stat_result == -2) 
    // {
    //     printf("No data available for the specified period\n");
    // }
    // else if (stat_result != 0) 
    // {
    //     fprintf(stderr, "Error calculating statistics (code: %d)\n", stat_result);
    // }
    
    // // Очистка памяти
    // free(filename);
    
    // printf("\n=== PROGRAM END ===\n");
    
    // // Пауза только в Windows
    // #ifdef _WIN32
    //     system("pause");
    // #endif