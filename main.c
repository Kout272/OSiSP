#include <ncurses.h>
#include <stdlib.h>
#include "main_screen.h"
#include "config.h"
#include "settings.h"
#include "about.h"
#include "executor.h"
#include "parser.h"

// Инициализация цветовых пар
void init_color_pairs() {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);   // Основной интерфейс
    init_pair(2, COLOR_BLACK, COLOR_WHITE);  // Диалоговые окна
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Текстовые поля
}

int main() {
    // Загрузка конфигурации
    AppConfig config;
    load_config(&config);

    // Инициализация ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    init_color_pairs();

    // Инициализация модулей
    read_settings(); // Загрузка пользовательских настроек

    // Запуск главного интерфейса
    main_screen_loop(&config);

    // Завершение работы
    endwin();
    save_config(&config);
    write_settings(); // Сохранение последних настроек

    return EXIT_SUCCESS;
}

// Реализация функций из config.c
void load_config(AppConfig *config) {
    snprintf(config->history_file, 256, "%s/.find_shell_history", getenv("HOME"));
    config->max_history_items = 100;
    snprintf(config->default_search_path, 256, ".");
}

void save_config(AppConfig *config) {
    // Реализация сохранения конфигурации
    FILE *fp = fopen(config->history_file, "w");
    if(fp) fclose(fp);
}
