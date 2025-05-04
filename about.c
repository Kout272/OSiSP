#include "about.h"
#include <ncurses.h>
#include <string.h>

// Очистка ресурсов окна
static void cleanup(WINDOW **win) {
    if (*win) {
        delwin(*win);
        *win = NULL;
    }
}

// Обработчик клавиш для окна "О программе"
static void handle_input(int ch, bool *exit_flag) {
    switch(ch) {
        case KEY_F(3):  // Закрыть по F3
        case 27:       // ESC
            *exit_flag = true;
            break;
    }
}

// Основная функция окна "О программе"
void about() {
    WINDOW *about_win = NULL;
    bool exit_flag = false;
    screen_size scr;

    // Инициализация окна
    getmaxyx(stdscr, scr.max_y, scr.max_x);
    about_win = create_window(scr.max_y/4, scr.max_x/4,
                              scr.max_x/2, scr.max_y/2);
    keypad(about_win, TRUE);

    // Текст информации
    const char *content[] = {
        "Find Shell v1.0",
        "Автор: Студент группы 334701 Панов Т.С.",
        "Лицензия: MIT",
        "GitHub: Kout272",
        "",
        "Управление:",
        "F3 - Вернуться",
        NULL
    };

    while(!exit_flag) {
        werase(about_win);
        wbkgd(about_win, COLOR_PAIR(2));
        box(about_win, 0, 0);

        // Отрисовка текста
        for(int i = 0; content[i]; i++) {
            mvwprintw(about_win, i+2, 2, "%s", content[i]);
        }

        wrefresh(about_win);

        // Обработка ввода
        int ch = wgetch(about_win);
        handle_input(ch, &exit_flag);
    }

    cleanup(&about_win);
}
