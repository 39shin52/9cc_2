
// 現状わかるところまでのコンパイラを
// 作る

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdarg.h>
#include<string.h>
#include<stdbool.h>

typedef enum {
    TK_RESERVED;    // 記号
    TK_NUM;         // 整数トークン
    TK_EOF;         // 入力の終わりを示すトークン
} TokenKind;

typedef struct Token Token;

struct Token {
    TokenKind kind; // トークンの型
    Token *next;    // 次の入力トークン
    int val;        // kindがTK_NUMの場合、その数値
    char *str;      // トークン文字列
};

// 現在注目しているトークン
Token *token;

// エラーを報告するための関数
// printfと同じ引数を取る
void error (char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt):
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

// 次のトークンが期待している記号の時には、トークンをひとつ読み進めて
// trueを返す。それ以外はfalseを返す
bool consume (char op) {
    if (token->kind != TK_RESERVED || token->str[0] != op) return false;
    token =token->next;
    return true;
}

// 次のトークンが期待している記号の時はトークンをひとつ読み進めて
// それ以外の場合はエラーを返す
int expect (char op) {
    if (token->kind != TK_RESERVED || token->str[0] != op) error("'%c'ではありません", op);
    token = token->next;
}

// 次のトークンが数値の場合、トークンをひとつ読み進めてその数値を返す。
// それ以外の場合にはエラーを返す
int expect_number () {
    if(token->kind != TK_NUM) error("数ではありません");
    int val = token->val;
    token = token->next;
    return val;
}

bool at_eof () {
    return token->kind == TK_EOF;
}

int main(int argc, char **argv){
    if (argc != 2) {
        fprintf(stderr, "引数の個数が正しくありません");
        return 1;
    }

    char *p = argv[1];

    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");
    printf(" mov rax, %ld\n", strtol(p, &p, 10));
    
    while (*p) {
        if (*p == '+') {
            p++;
            printf(" add rax, %ld\n", strtol(p, &p, 10));
            continue;
        }
        if (*p == '-') {
            p++;
            printf(" sub rax, %ld\n", strtol(p, &p, 10));
            continue;
        }

        fprintf(stderr, "予期しない文字です: '%c'\n", *p);
        return 1;
    }

    printf(" ret\n");
    return 0;
}
