#ifndef EXECUTOR_H
#define EXECUTOR_H

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "./utility_gui_lib.h"

extern char preferences[PARAM_QUANTITY][PATH_MAX];
extern bool checkbox[CHECKBOXES_QUANTITY];

typedef enum PARAMETR {
    NO_PARAM,
    NAME,
    GROUP,
    PATH,
    PERM,
    REGEX,
    SIZE,
    USER,
    MTIME,
    UID,
    QUERY_FORMAT,
    PARAMETERS_END,
} PARAMETR;

typedef enum CHECKBOXES {
    TYPE_F,
    TYPE_D,
    TYPE_L,
    CHECKBOXES_END,
} CHECKBOXES;

static const char *const checkboxes_tokens[] = {
    "f", "d", "l"
};

static const char *const flag_str_name[] = {
    "-name", "-group", "-path", "-perm",
    "-regex", "-size", "-user", "-type", "-mtime"
};

#define get_index_by_param(__X) ((__X > NO_PARAM) ? (__X-1) : 0)
#define PARAM_QUANTITY (PARAMETERS_END-1)
#define CHECKBOXES_QUANTITY (CHECKBOXES_END)

void write_settings();
void read_settings();
void create_exec_str(char* buf, char* path, char* query);
FILE *get_query_result_file(char* path);

#endif
