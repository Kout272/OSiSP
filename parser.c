#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static const char* find_operators[] = {"-a", "-o", "!"};

char* parse_query(const char* input) {
    QueryToken tokens[MAX_TOKENS];
    int token_count = 0;
    char* result = malloc(MAX_QUERY_LEN);

    // Токенизация входной строки
    tokenize_query(input, tokens, &token_count);

    // Замена плейсхолдеров на реальные значения
    replace_placeholders(tokens, token_count);

    // Построение конечного выражения
    char* expr = build_find_expression(tokens, token_count);
    snprintf(result, MAX_QUERY_LEN, "%s", expr);

    free(expr);
    return result;
}

void tokenize_query(const char* input, QueryToken* tokens, int* token_count) {
    char buffer[MAX_QUERY_LEN];
    strncpy(buffer, input, MAX_QUERY_LEN);

    char* token = strtok(buffer, " &|!");
    char* op_ptr = (char*)input;

    while(token && *token_count < MAX_TOKENS) {
        // Определение логической операции
        LogicalOp op = OP_NONE;
        if(strstr(op_ptr, "!")) op = OP_NOT;
        if(strstr(op_ptr, "&")) op = OP_AND;
        if(strstr(op_ptr, "|")) op = OP_OR;

        // Заполнение структуры токена
        strncpy(tokens[*token_count].token, token, 64);
        tokens[*token_count].operation = op;

        op_ptr += strlen(token) + 1;
        token = strtok(NULL, " &|!");
        (*token_count)++;
    }
}

void replace_placeholders(QueryToken* tokens, int token_count) {
    for(int i = 0; i < token_count; i++) {
        // Поиск соответствия плейсхолдера в токене
        for(int p = NAME; p < PARAM_QUANTITY; p++) {
            char placeholder[32];
            snprintf(placeholder, 32, "{%s}", flag_str_name[p]);

            if(strstr(tokens[i].token, placeholder)) {
                // Замена плейсхолдера на значение из preferences
                char* value = preferences[get_index_by_param(p)];
                strncpy(tokens[i].value, value, PATH_MAX);
                break;
            }
        }
    }
}

char* build_find_expression(QueryToken* tokens, int token_count) {
    char* expr = calloc(MAX_QUERY_LEN, 1);
    int pos = 0;

    for(int i = 0; i < token_count; i++) {
        // Добавление логического оператора
        if(tokens[i].operation != OP_NONE) {
            pos += snprintf(expr + pos, MAX_QUERY_LEN - pos, " %s ",
                            find_operators[tokens[i].operation - 1]);
        }

        // Добавление значения параметра
        if(strlen(tokens[i].value) > 0) {
            pos += snprintf(expr + pos, MAX_QUERY_LEN - pos, "'%s'",
                            tokens[i].value);
        }
    }

    return expr;
}
