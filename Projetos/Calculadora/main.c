#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    int n_stack[2];
    int n_stack_head;
    char operation;
}Stacks;

void clean_buffer();
int calculate(const char* s, Stacks* stacks, size_t size);
int parse_int(const char* s, size_t* i);
Stacks* inicialize_stacks();
void push_numbers(int* n_stack, int* head, int n, size_t size);
int pop_numbers(const int* n_stack, int* head);

int main(void) {
    Stacks* stack = inicialize_stacks();
    if (stack == NULL) {
        printf("falha ao alocar memoria\n");
        return 0;
    }
    char* s;

    scanf("%99s", s);
    clean_buffer();

    size_t size = strlen(s);

    int total = calculate(s, stack, size);
    if (total == EOF) printf("expressão invalida\n");
    else printf("Resultado: %d", total);

    free(stack);
    return 0;
}

void clean_buffer() {
    int c;
    while ((c = getchar()) != '\n'  && c != EOF){}
}
int calculate(const char* s, Stacks* stacks, size_t size) {
    int resultado=0;
    for (size_t i = 0; i < size; i++) {
        if (isdigit(s[i])) {
            int n = parse_int(s, &i);

            push_numbers(stacks->n_stack, &stacks->n_stack_head, n, size);
        }else{
            if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') stacks->operation = s[i];
            else return EOF;
        }
        if (stacks->n_stack_head == 1) {

            int n2 = pop_numbers(stacks->n_stack, &stacks->n_stack_head);
            int n1 = pop_numbers(stacks->n_stack, &stacks->n_stack_head);

            if (stacks->operation == '+') push_numbers(stacks->n_stack, &stacks->n_stack_head, n1+n2, size);
            else if (stacks->operation == '-') push_numbers(stacks->n_stack, &stacks->n_stack_head, n1-n2, size);
            else if (stacks->operation == '*') push_numbers(stacks->n_stack, &stacks->n_stack_head, n1*n2, size);
            else if (stacks->operation == '/') {
                if (n2 == 0) return EOF;
                push_numbers(stacks->n_stack, &stacks->n_stack_head, n1/n2, size);
            }
            else return EOF;
        }
    }

    return pop_numbers(stacks->n_stack, &stacks->n_stack_head);
}
int parse_int(const char* s, size_t* i) {
    int total = 0;
    while (s[*i] != '\0' && isdigit((unsigned char)s[*i])) {
        //Convert the character to integer by subtracting
        //ASCII value of '0'
        int n = s[*i] - '0';
        total = total * 10 + n;
        (*i)++;
    }
    (*i)--;
    return total;
}
Stacks* inicialize_stacks(){
    Stacks* s = malloc(sizeof(Stacks));
    if (s == NULL) return NULL;

    s->n_stack_head = -1;
    s->operation = '\0';

    return s;
}
void push_numbers(int* n_stack, int* head, int n, size_t size) {
    if (*head >= (int)size-1) return;
    (*head)++;
    n_stack[*head] = n;
}
int pop_numbers(const int* n_stack, int* head) {
    if (*head == -1) return 0;
    int temp = n_stack[*head];
    (*head)--;
    return temp;
}
