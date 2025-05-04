#include "utility_gui_lib.h"
#include <form.h>

// Глобальные настройки
screen_size scr_size;
static bool colors_initialized = false;

void init_gui_lib() {
    if (!colors_initialized) {
        start_color();
        init_pair(DEFAULT_COLOR, COLOR_WHITE, COLOR_BLUE);
        init_pair(HIGHLIGHT_COLOR, COLOR_BLACK, COLOR_CYAN);
        init_pair(WARNING_COLOR, COLOR_RED, COLOR_WHITE);
        colors_initialized = true;
    }
}

WINDOW* create_window(int height, int width, int starty, int startx) {
    WINDOW* win = newwin(height, width, starty, startx);
    box(win, 0, 0);
    wbkgd(win, COLOR_PAIR(DEFAULT_COLOR));
    keypad(win, TRUE);
    return win;
}

void default_key_handler(const key_handler* handlers, size_t handlers_count) {
    int ch = getch();
    for (size_t i = 0; i < handlers_count; i++) {
        if (ch == handlers[i].key) {
            handlers[i].handler();
            return;
        }
    }
}

void draw_horizontal_menu(const char** items, int count, int selected) {
    int x = 2;
    for (int i = 0; i < count; i++) {
        if (i == selected) {
            wattron(stdscr, COLOR_PAIR(HIGHLIGHT_COLOR));
            mvwprintw(stdscr, 1, x, " %s ", items[i]);
            wattroff(stdscr, COLOR_PAIR(HIGHLIGHT_COLOR));
        } else {
            mvwprintw(stdscr, 1, x, " %s ", items[i]);
        }
        x += strlen(items[i]) + 3;
    }
}

void draw_button(WINDOW* win, int y, int x, const char* label, bool focused) {
    if (focused) {
        wattron(win, COLOR_PAIR(HIGHLIGHT_COLOR));
        mvwprintw(win, y, x, "[%s]", label);
        wattroff(win, COLOR_PAIR(HIGHLIGHT_COLOR));
    } else {
        mvwprintw(win, y, x, " %s ", label);
    }
}

void center_text(WINDOW* win, int y, const char* text) {
    int width = getmaxx(win);
    int x = (width - strlen(text)) / 2;
    mvwprintw(win, y, x, "%s", text);
}

void update_screen_size(screen_size* sz) {
    getmaxyx(stdscr, sz->max_y, sz->max_x);
}

int parse_input(WINDOW* win) {
    int ch = wgetch(win);
    switch(ch) {
        case KEY_UP: return INPUT_UP;
        case KEY_DOWN: return INPUT_DOWN;
        case KEY_LEFT: return INPUT_LEFT;
        case KEY_RIGHT: return INPUT_RIGHT;
        case 10: return INPUT_ENTER; // Enter
        case 27: return INPUT_ESC;   // Escape
        default: return ch;
    }
}
