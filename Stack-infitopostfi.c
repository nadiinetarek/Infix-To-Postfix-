#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
* Item: An item that is being pushed to or popped from the stack
* It may be float (to be used while evaluating the postfix)
* It may be char (to be used while converting infix to postfix)
*/
typedef union
{
    float fData;
    char  cData;
} Item;
/*
*
*/


typedef struct
{
    Item data;
    struct Node* next;
} Stack;

typedef struct
{
    Node* top;
} Stack;
/*
*
*/
Stack* initialize(Stack* stack)
{
     stack = (Stack*)malloc(sizeof(Stack));
    if (!stack)
        return NULL;
    stack->top = NULL;
   
}
/*
*
*/



Node* newNode(Item x)
{  Node *n= ( Node*)malloc(sizeof( Node));
    n->data=x;
    n->next=NULL;
    return n;
}


int isEmpty(Stack *s)
{
    if(s->top == NULL)
        return 1;
    else
        return 0;
}
/*
*
*/
Item top(Stack *s)
{
if(s)
        return s->top->data;
    else exit(1);}
/*
*
*/
Item pop(Stack *s)
{
if(!s)
        exit(1);
    else{
        Item x= s->top->data;
        Node *p = s->top;
        s->top=s->top->next;
        p->next=NULL;
        free(p);
        return x;
}
/*
*
*/
void push(Stack *s, Item val)
{
    if(!s->top)
    {
        Node* m = newNode(val);
        s->top=m;
    }
    else{
    Node* z=newNode(val);
    Node* temp;
    temp=s->top;
    while (temp)
    {temp=temp->next;}
    z->next=s->top;
        s->top=z;}
}

    int isOperand(char ch)
    {
        return (ch >= 'a' && ch <= 'z') ||
               (ch >= 'A' && ch <= 'Z');
    }

    int precedence(char ch)
    {
        switch (ch)
        {
            case '+':
            case '-':
                return 1;

            case '*':
            case '/':
                return 2;

            case '^':
                return 3;
        }
        return -1;
    }



/*
* infixToPostfix: converts an expression in infix notation to
* to a postfix notation (Reverse-Polish Notation)
* ASSUME ^*+-/ operators
* e.g., 22 + 31 --> 22 31 +
* e.g., ( 2 + 3 ) * 4 --> 2 3 + 4 *
*/
void infixToPostfix(char* infix, char* postfix)
{
    int i, k;

    // Create a stack of capacity
    // equal to expression size
     Stack *stack = initialize(strlen(infix));

    if(!stack) // See if stack was created successfully
        return -1 ;

    for (i = 0, k = -1; infix[i]; ++i)
    {

        // If the scanned character is
        // an operand, add it to output.
        if (isOperand(infix[i]))
            infix[++k] = infix[i];

            // If the scanned character is an
            // ‘(‘, push it to the stack.
        else if (infix[i] == '(')
            push(stack, infix[i]);

            // If the scanned character is an ‘)’,
            // pop and output from the stack
            // until an ‘(‘ is encountered.
        else if (infix[i] == ')')
        {
            while (!isEmpty(stack) && top(stack) != '(')
                postfix[++k] = pop(stack);
            if (!isEmpty(stack) && top(stack) != '(')
                return -1; // invalid expression
            else
                pop(stack);
        }
        else // an operator is encountered
        {
            while (!isEmpty(stack) &&
                    precedence(infix[i]) <= precedence(top(stack)))
                postfix[++k] = pop(stack);
            push(stack, infix[i]);
        }

    }

    // pop all the operators from the stack
    while (!isEmpty(stack))
        postfix[++k] = pop(stack );

    infix[++k] = '\0';
    printf( "%s", infix );

}
/*
* evaluatePostfix: Evaluates an expression in postfix notation
* (Reverse-Polish Notation)
*/
float evaluatePostfix(char* postfix)
{
    Stack* stack;
    initialize(&stack);
    int i;

    // See if stack was created successfully
    if (!stack)
        return -1;

    // Scan all characters one by one
    for (i = 0; postfix[i]; ++i)
    {
        // If the scanned character is an operand (number here),
        // push it to the stack.
        if (isdigit(postfix[i]))
            push(stack, postfix[i] - '0');

            // If the scanned character is an operator, pop two
            // elements from stack apply the operator
        else
        {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (postfix[i])
            {
                case '+': push(stack, val2 + val1); break;
                case '-': push(stack, val2 - val1); break;
                case '*': push(stack, val2 * val1); break;
                case '/': push(stack, val2/val1); break;
            }
        }
    }
    return pop(stack);
}
/*
*
*/
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
*
*/
int main()
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}
