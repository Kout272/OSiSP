#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "config.h"
#include "executor.h"

#define MAX_TOKENS 32
#define MAX_QUERY_LEN 512

typedef enum {
    OP_NONE,
    OP_AND,
    OP_OR,
    OP_NOT
} LogicalOp;

typedef struct {
    char token[64];
    char value[PATH_MAX];
    LogicalOp operation;
} QueryToken;

// Основная функция парсинга
char* parse_query(const char* input);

// Вспомогательные функции
void tokenize_query(const char* input, QueryToken* tokens, int* token_count);
void replace_placeholders(QueryToken* tokens, int token_count);
char* build_find_expression(QueryToken* tokens, int token_count);

#endif
