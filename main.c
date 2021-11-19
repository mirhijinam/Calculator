#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define STACK_EMPTY '|'
#define HASH_SIZE 101
#define NUM_OF_VARIABLES 9
#define MAX_LEN_VAR 6
// a+b*a+8*c-9*d+8*e-9*(78+3)*y-a*b*c*d*e*fskfaaaaf*g*q*w*e*r*t*y*u*i*o*p*a*a*l*z*x*c*v*b*n*m

struct hash_element // Элемент хэш-таблицы
{
    char *name; // Имя
    char *swap; // Замещающий текст
    struct hash_element *next;
};

static struct hash_element *hash_table_of_pointers[HASH_SIZE]; // Таблица указателей

// hash: получает хэш-код для строки s
unsigned hash(char *s)
{
    unsigned hash_value;
    for (hash_value = 0; *s != '\0'; s++)
        hash_value = *s + 31 * hash_value;
    return hash_value % HASH_SIZE;
}

// search: ищет s
struct hash_element *search(char *s)
{
    struct hash_element *np;
    for (np = hash_table_of_pointers[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; // Нашли
    return NULL; // Не нашли
}

struct hash_element *search(char *);
char *strdup(const char *);

// put_in: заносит имя и текст (name, swap) в таблицу
struct hash_element *put_in(char *name, char *swap)
{
    struct hash_element *np;
    unsigned hash_value;
    
    if ((np = search(name)) == NULL) // Не найден
    {
        np = (struct hash_element *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hash_value = hash(name);
        np->next = hash_table_of_pointers[hash_value];
        hash_table_of_pointers[hash_value] = np;
    } else // Уже имеется
        free((void *) np->swap); // освобождаем прежний swap
    
    if ((np->swap = strdup(swap)) == NULL)
        return NULL;
    return np;
}

char *searching(char *s)
{
    struct hash_element *np;
    for (np = hash_table_of_pointers[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np->swap; // Нашли
    return NULL; // Не нашли
}


typedef struct node
{
    char operation;
    int priority;
    struct node *next;
} node;

typedef node *stack;


int priorityy(char c) {
    if(c == '(')
        return 0;
    else if((c == '/') || (c == '*'))
        return 2;
    else if((c == '+') || (c == '-'))
        return 1;
    else
        return -1;
}

bool push(stack *mystack, char operation) // Добавить ОПЕРАЦИЮ в стек.
{
    node *newnode = (struct node*)malloc(sizeof(node));
    if (newnode == NULL) return false;

    newnode->operation = operation;
    newnode->priority = priorityy(operation);
    newnode->next = *mystack;
    *mystack = newnode;
    return true;
}

char pop(stack *mystack) // Вытащить ОПЕРАЦИЮ из стека.
{
    if (*mystack == NULL || (*mystack)->operation == ' ') return STACK_EMPTY;

    char result = (*mystack)->operation;
    //struct node *tmp = *mystack;
    *mystack = (*mystack)->next;
    //free(tmp);
    return result;
}

char peek(stack *mystack)
{
    if (*mystack == NULL)
    {
        return STACK_EMPTY;
    }
    return (*mystack)->operation;
}

int peek_priority(stack *mystack)
{
    if (*mystack == NULL)
    {
        return -2;
    }
    return (*mystack)->priority;
}


typedef struct node1 // Стек для полностью преобразованной строки
{
    float operand;
    struct node1 *next;
} node1;



typedef node1 *ansStack;

bool pushAns(ansStack *mystack, float operand) // Добавить ОПЕРАЦИЮ в стек.
{
    node1 *newnode = (struct node1*)malloc(sizeof(node1));
    if (newnode == NULL) return false;

    newnode->operand = operand;
    newnode->next = *mystack;
    *mystack = newnode;
    return true;
}

float popAns(ansStack *mystack) // Вытащить операнд из стека.
{
    if (*mystack == NULL) return STACK_EMPTY;

    float result = (*mystack)->operand;
    struct node1 *tmp = *mystack;
    *mystack = (*mystack)->next;
    free(tmp);
    return result;
}


char* returnPolishRecord (char* inp) // Представляем строку в формате обратной польской записи
{
    stack RPR = NULL; // Стек для операций
    size_t len = strlen(inp);
    char *outp = NULL; // Строка-
    outp = malloc(len);
    int i = 0;
    int j = 0;

    // Если ЧИСЛО или ПЕРЕМЕННАЯ -- заносим в строку-результат,
    // Если ОПЕРАЦИЯ и ее приоритет меньше либо равен приоритету предыдущей --
    //  вытаскиваем из стека предыдущую ОПЕРАЦИЮ, затем добавляем в стек нынешнюю
    // Если ОПЕРАЦИЯ и иначе -- добавляем в стек нынешнюю ОПЕРАЦИЮ
    while (i < len)
    {
        
        if (((i == 0) && (inp[0] == '-')) || ((inp[i-1] == '(') && (inp[i] == '-')))
        {
            outp[j] = inp[i];
            i++;
            j++;
            if ((inp[i] >= '0') && (inp[i] <= '9'))
            {
                while((inp[i] >= '0') && (inp[i] <= '9'))
                {
                    outp[j] = inp[i];
                    j++;
                    i++;
                }
                outp[j] = ' ';
                j++;
            }
            
            if ((inp[i] == '.') && (outp[j-2] >= '0') && (outp[j-2] <= '9'))
            {
                outp[j-1] = inp[i];
                if (inp[i+1] < '0' || inp[i+1] > '9')
                {
                        printf("Error! Invalid operand.\n");
                        exit(5);
                }
                i++;
                while ((inp[i] >= '0') && (inp[i] <= '9'))
                {
                    outp[j] = inp[i];
                    j++;
                    i++;
                }
                
                if (!((inp[i] == '.') && (outp[j-2] >= '0') && (outp[j-2] <= '9')) || !((inp[i] >= '0') && (inp[i] <= '9')))
                {
                    printf("Error! Operation is missed.\n");
                    exit(3);
                }
                
                if(!((inp[i] >= '0') && (inp[i] <= '9')))
                {
                    printf("Error! Invalid operand.\n");
                    exit(5);
                }
                outp[j] = ' ';
                j++;
            }
            
                continue;
        }
        
        else if ((inp[i] >= '0') && (inp[i] <= '9'))
        {
            
            while((inp[i] >= '0') && (inp[i] <= '9'))
            {
                outp[j] = inp[i];
                if ((inp[i+1] < '0' || inp[i+1] > '9') && inp[i+1] != '+' && inp[i+1] != '-' && inp[i+1] != '*' && inp[i+1] != '/' && inp[i+1] != ')' && i != len-1)
                {
                        printf("Error! Invalid operand.\n");
                        exit(5);
                }
                j++;
                i++;
            }
            
            outp[j] = ' ';
            j++;
            continue;
        }
        
        else if ((inp[i] == '.') && (outp[j-2] >= '0') && (outp[j-2] <= '9'))
        {
            outp[j-1] = inp[i];
            if (inp[i+1] < '0' || inp[i+1] > '9')
            {
                    printf("Error! Invalid operand.\n");
                    exit(5);
            }
            i++;
            while ((inp[i] >= '0') && (inp[i] <= '9'))
            {
                outp[j] = inp[i];
                j++;
                i++;
            }
            if (!((inp[i] == '.') && (outp[j-2] >= '0') && (outp[j-2] <= '9')) || !((inp[i] >= '0') && (inp[i] <= '9')))
            {
                printf("Error! Operation is missed.\n");
                exit(3);
            }
            
            if(!((inp[i] >= '0') && (inp[i] <= '9')) && (i != len))
            {
                printf("Error! Invalid operand.\n");
                exit(5);
            }
            //i--;
            outp[j] = ' ';
            j++;
            continue;
        }
        
        else if ((inp[i] >= 'A' && inp[i] <= 'Z') || (inp[i] >= 'a' && inp[i] <= 'z'))
        {
            while (1) // (a+b)c
            {
                if (inp[i] == '+') break;
                
                if (inp[i] == '-') break;
            
                if (inp[i] == '*') break;
                
                if (inp[i] == '/') break;
                
                if (inp[i] == '\0') break;
                
                if (inp[i] == ' ') break;
                
                if(inp[i] == ')') break;
                
                if ( ((inp[i] < 'A') || (inp[i] > 'Z' && inp[i] < 'a') || (inp[i] > 'z')) && (inp[i] != '0') && (inp[i] != '1') && (inp[i] != '2') && (inp[i] != '3') && (inp[i] != '4') && (inp[i] != '5') && (inp[i] != '6') && (inp[i] != '7') && (inp[i] != '8') && (inp[i] != '9'))
                {
                    printf("Error! Invalid operation.\n");
                    exit(4);
                }
                
                outp[j] = inp[i];
                i++;
                j++;
            }

            outp[j] = ' ';
            j++;
            continue;
        }
        else if (
                 ((i == 0) && ((inp[i] < 'A') || (inp[i] > 'Z' && inp[i] < 'a') || (inp[i] > 'z')) && (inp[i] != '('))
                 ||
                 (((inp[i-1] == '+') || (inp[i-1] == '-') || (inp[i-1] == '*') || (inp[i-1] == '/')) && (inp[i] != '(') && ((inp[i] < 'A') || (inp[i] > 'Z' && inp[i] < 'a') || (inp[i] > 'z')))
                 ||
                 ((inp[i-1] == '/') && ((inp[i] < 'A') || (inp[i] > 'Z' && inp[i] < 'a') || (inp[i] >= 'z')))
                 )
        {
            printf("Error! Invalid operand.\n");
            exit(5);
        }
        
        else if ((inp[i] == '/') || (inp[i] == '*') || (inp[i] == '+') || ((inp[i] == '-') && (i != 0) && (inp[i] != '(')))
        {
            while (priorityy(inp[i]) <= peek_priority(&RPR))
            {
                if ((inp[i+1] == '/') || (inp[i+1] == '*') || (inp[i+1] == '+') || ((inp[i+1] == '-') && (i != 0) && (inp[i] != '(')))
                {
                    printf("Error! Operand is missed.\n");
                    exit(2);
                }
                outp[j] = pop(&RPR);
                outp[j+1] = ' ';
                j += 2;
            }
            push(&RPR, inp[i]);
            i++;
            continue;
        }
        
        else if (inp[i] == '(')
        {
            push(&RPR, inp[i]);
            i++;
            continue;
        }
        
        else if (inp[i] == ')')
        {
            char untilOpBracket;
            
            if ((inp[i+1] >= '0' && inp[i+1] <= '9') || (inp[i+1] >= 'a' && inp[i+1] <= 'z') || (inp[i+1] >= 'A' && inp[i+1] <= 'Z'))
            {
                printf("Error! Operation is missed.\n");
                exit(3);
            }
            while ((untilOpBracket = pop(&RPR)) != '(')
            {
                if (untilOpBracket == STACK_EMPTY)
                {
                    printf("Error! Number of opening brackets are less number of closing.\n");
                }
                outp[j] = untilOpBracket;
                outp[j+1] = ' ';
                j += 2;
            }
            
            i++;
            continue;
        }
        
        else
        {
            printf("Error! Invalid operation.\n");
            exit(4);
        }
    }
    
    // Вывод операций, оставшихся в стеке.
    char op;
    while ((op = pop(&RPR)) != STACK_EMPTY)
    {
        outp[j] = op;
        outp[j+1] = ' ';
        j += 2;
    }
    outp[j] = '\0';
    
    if (outp[strlen(outp)-2] == '(')
    {
        printf("Error! Number of closing brackets are less number of opening.\n");
        exit(1);
    }
    return outp;
}

int main(int argc, char **argv)
{
    char *mas_with_unique_variable_names[NUM_OF_VARIABLES] = {NULL};
    int b;
    for (b = 0; b < NUM_OF_VARIABLES; b++) mas_with_unique_variable_names[b] = (char*)malloc(7*sizeof(char));
    
    char *input_string = NULL;
    input_string = malloc(100); //(a+b
    
    printf("Enter a mathematical expression: ");
    scanf("%s", input_string);
    
    if(input_string[0] == '+' || input_string[0] == '/' || input_string[0] == '*')
    {
        printf("Error! Operand is missed.\n");
        exit(2);
    }
    
    int x;
    for(x = 0; x < strlen(input_string)-1; x++)
    {
        if (input_string[x] == '+' || input_string[x] == '-' || input_string[x] == '/' || input_string[x] == '*' || input_string[x] == '(')
        {
            if (input_string[x+1] == '+' || (input_string[x+1] == '-' && input_string[x] != '(') || input_string[x+1] == '/' || input_string[x+1] == '*' || input_string[x+1] == ')')
            {
                printf("Error! Operand is missed.\n");
                exit(2);
            }
        }
    }
    
    if (input_string[strlen(input_string)-1] == '+' || input_string[strlen(input_string)-1] == '-' || input_string[strlen(input_string)-1] == '/' || input_string[strlen(input_string)-1] == '*')
    {
        printf("Error! Operand is missed.\n");
        exit(2);
    }
    
    char *template_rpr_string = returnPolishRecord(input_string); // Строка в обратной польской записи
    size_t rpr_len = strlen(template_rpr_string); // (A+b A+b)
    
    int ui = 0;
    int uy = 0;
    
    while (ui < rpr_len) // Заполняем массив переменными
    {
        char *next_variable_for_mas = (char*)malloc(7*sizeof(char));
        int uk = 0;
        if ((template_rpr_string[ui] >= 'A' && template_rpr_string[ui] <= 'Z') || (template_rpr_string[ui] >= 'a' && template_rpr_string[ui] <= 'z'))
        {
            while (1)
            {
                if (template_rpr_string[ui] == ' ')
                {
                    break;
                }
                next_variable_for_mas[uk] = template_rpr_string[ui];
                uk++;
                ui++;
                if (uk > MAX_LEN_VAR)
                {
                    printf("Error! Invalid operand.\n");
                    exit(5);
                }
            }
            
            int isIn = 1;
            for (b = 0; b < NUM_OF_VARIABLES; b++)
            {
                if (strcmp(mas_with_unique_variable_names[b], next_variable_for_mas) == 0)
                {
                    isIn = 1;
                    break;
                }
                else
                {
                    isIn = 0;
                }
            }
            
            if (isIn == 0)
            {
                strcpy(mas_with_unique_variable_names[uy], next_variable_for_mas);
                uy++;
            }
        }
        ui++;
    }
    
    // Получаем значения ПЕРЕМЕННЫХ
    char* variable_value = NULL;
    variable_value = malloc(5);
    int o = 0;
    while (o < NUM_OF_VARIABLES)
    {
        if (strcmp(mas_with_unique_variable_names[o], "") == 0) break;
        
        printf("Enter the value of the variable %s: ", mas_with_unique_variable_names[o]);
        scanf("%s", variable_value);
        
        put_in(mas_with_unique_variable_names[o], variable_value);
        
        o++;
    }
    
    
    // Заменяем ПЕРЕМЕННЫЕ в строке их значениями
    char* vrble_from_string = NULL;
    char* final_rpr_string = NULL;
    final_rpr_string = malloc(rpr_len);
    
    int k = 0, l = 0, q = 0;
    
    while (template_rpr_string[k] != '\0')
    {
        if ((template_rpr_string[k] >= 'A' && template_rpr_string[k] <= 'Z') || (template_rpr_string[k] >= 'a' && template_rpr_string[k] <= 'z'))
        {
            vrble_from_string = malloc(7);
            q = 0;
            while (1)
            {
                if (template_rpr_string[k] == ' ') break;
                
                vrble_from_string[q] = template_rpr_string[k];
                
                k++;
                q++;
            }
            char *var_value = searching(vrble_from_string);
            
            strcat(final_rpr_string, var_value);
            
            size_t len_varValue = strlen(var_value);
            l += len_varValue;
            
            final_rpr_string[l] = '\0';
        }
        else
        {
            final_rpr_string[l] = template_rpr_string[k];
            k++;
            l++;
            final_rpr_string[l] = '\0';
        }
    }
    
    
    // Вычисление выражения в обратной польской нотации
    ansStack answer = NULL;
    
    size_t len_finalRprString = strlen(final_rpr_string);
    
    char* char_operand = NULL;
    
    float operand1 = 0.0;
    float operand2 = 0.0;
    float result = 0.0;
    
    int h = 0, m = 0;
    
    while (h < len_finalRprString)
    {
        if ((final_rpr_string[h] == '-') && (final_rpr_string[h+1] >= '0' && final_rpr_string[h+1] <= '9'))
        {
            m = 0;
            char_operand = malloc(100);
            char_operand[m] = final_rpr_string[h];
            h++;
            if (final_rpr_string[h] >= '0' && final_rpr_string[h] <= '9')
            {
                while((final_rpr_string[h] >= '0') && (final_rpr_string[h] <= '9'))
                {
                    char_operand[m] = final_rpr_string[h];
                    m++;
                    h++;
                }
                if (final_rpr_string[h] == '.')
                {
                    char_operand[m] = final_rpr_string[h];
                    h++;
                    m++;
                    while ((final_rpr_string[h] >= '0') && (final_rpr_string[h] <= '9'))
                    {
                        char_operand[m] = final_rpr_string[h];
                        m++;
                        h++;
                    }
                }
                double eee = (-1)*strtod(char_operand, &char_operand);
                pushAns(&answer, eee);
            }
        }
        
            
        if (final_rpr_string[h] >= '0' && final_rpr_string[h] <= '9')
        {
            char_operand = malloc(100);
            m = 0;
            
            while((final_rpr_string[h] >= '0') && (final_rpr_string[h] <= '9'))
            {
                char_operand[m] = final_rpr_string[h];
                m++;
                h++;
            }
            
            if (final_rpr_string[h] == '.')
            {
                char_operand[m] = final_rpr_string[h];
                h++;
                m++;
                while ((final_rpr_string[h] >= '0') && (final_rpr_string[h] <= '9'))
                {
                    char_operand[m] = final_rpr_string[h];
                    m++;
                    h++;
                }
            }
            
            double eee = strtod(char_operand, &char_operand);
            pushAns(&answer, eee);
            //char_operand = malloc(10);
        }
        
        
        if (final_rpr_string[h] == '+')
        {
            operand1 = popAns(&answer);
            operand2 = popAns(&answer);
            result = operand1 + operand2;
            pushAns(&answer, result);
        }
        
        if (final_rpr_string[h] == '-')
        {
            operand1 = popAns(&answer);
            operand2 = popAns(&answer);
            result = operand2 - operand1;
            pushAns(&answer, result);
        }
        
        if (final_rpr_string[h] == '*')
        {
            operand1 = popAns(&answer);
            operand2 = popAns(&answer);
            result = operand1 * operand2;
            pushAns(&answer, result);
        }
        
        if (final_rpr_string[h] == '/')
        {
            operand1 = popAns(&answer);
            operand2 = popAns(&answer);
            if (operand1 == 0)
            {
                printf("Error! Zero divide detected.\n");
                exit(6);
            }
            result = operand2 / operand1;
            pushAns(&answer, result);
        }
        
        
        
        h++;
    }
    
    printf("Answer: %f", popAns(&answer));
    printf("\n");


    return 0;
}
/* TODO */
