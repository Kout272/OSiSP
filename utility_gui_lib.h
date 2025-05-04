#ifndef UTILITY_GUI_LIB_H
#define UTILITY_GUI_LIB_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

// Цветовые пары
#define DEFAULT_COLOR 1
#define HIGHLIGHT_COLOR 2
#define WARNING_COLOR 3

// Размеры экрана
typedef struct {
    int max_y;
    int max_x;
} screen_size;

// Обработчик клавиш
typedef struct {
    int key;
    void (*handler)(void);
} key_handler;

// Обработчик отрисовки
typedef void (*render_routes)(void);

// Структура элемента интерфейса
typedef struct {
    int x;
    int y;
    int width;
    char* label;
    bool focused;
} UI_Element;

// Инициализация библиотеки
void init_gui_lib();

// Создание окна с рамкой
WINDOW* create_window(int height, int width, int starty, int startx);

// Универсальный обработчик клавиш
void default_key_handler(const key_handler* handlers, size_t handlers_count);

// Отрисовка горизонтального меню
void draw_horizontal_menu(const char** items, int count, int selected);

// Отрисовка кнопки
void draw_button(WINDOW* win, int y, int x, const char* label, bool focused);

// Центрирование текста
void center_text(WINDOW* win, int y, const char* text);

// Обновление размеров экрана
void update_screen_size(screen_size* sz);

// Парсинг нажатых клавиш
int parse_input(WINDOW* win);

#endif
