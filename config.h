#ifndef CONFIG_H
#define CONFIG_H

// Версия и метаданные
#define TITLE "find CURSES"
#define VERSION "v1.0"
#define PROGRAM_NAME name_and_version_str(TITLE,VERSION)
#define name_and_version_str(name, version) name " " version

// Текстовые константы GUI
#define FILE_TYPE_GUI "Display files"
#define DIR_TYPE_GUI "Display catalogs"
#define SYMLINK_TYPE_GUI "Display symbolic links"
#define EXECUTE_GUI "Perform"
#define ADDITIONAL_COMMAND_GUI "Parameters"
#define ABOUT_GUI "About program"
#define SEARCH_GUI "Search"
#define REGEXP_GUI "Regular expression"
#define NAME_GUI "Name format"
#define GROUP_GUI "Group"
#define MTIME_GUI "Last modification"
#define PERM_GUI "Access"
#define SIZE_GUI "File size"
#define USER_GUI "User"
#define QUERY_STRING_GUI "Request format"
#define EXIT_GUI "Exit/Back"

#define DESCRIPTION "This program is a simple shell over the find utility."
#define DESCRIPTION1 "DOCUMENTATION"
#define DESCRIPTION2 "To record a parameter, the parameter is entered in quotation marks (\"...\") \nin the field opposite the name"
#define DESCRIPTION3 "To use the parameter in the search, enter the name of the flag in curly brackets ({...}) \nin the field opposite the name of the \"Request format\""
#define DESCRIPTION4 "How to make \"Request format\":"
#define DESCRIPTION5 "Name format - {name}. Example: \"main.c\" or \".c\"."
#define DESCRIPTION6 "Group - {group}. Example: \"users\"."
#define DESCRIPTION7 "User - {user}. Example: \"amor\"."
#define DESCRIPTION8 "Regular expression - {regex}. Example: \".*\\.c\"."
#define DESCRIPTION9 "Access - {perm}. Example: \"644\"."
#define DESCRIPTION10 "Size - {size}. Examples: \"+1k\" or \"-1M\"."
#define DESCRIPTION11 "b -> 512-byte blocks (default), c -> bytes, w -> two-byte words, k -> kilobytes, M -> megabytes, G -> gigabytes."
#define DESCRIPTION12 "Request format -> example: !{name} | {size} & {user}."
#define DESCRIPTION13 "\"!\' -> NOT, \"|\" -> OR, \"&\" -> AND."

// Системные настройки
#define SETTINGS_PATH "./userdata"
#define VISIBLE_MAX 1024

// Структура конфигурации приложения
typedef struct {
    char history_file[256];
    int max_history_items;
    char default_search_path[256];
} AppConfig;

// Прототипы функций
void load_config(AppConfig *config);
void save_config(AppConfig *config);

#endif
