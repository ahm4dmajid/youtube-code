/*
 * File: index.c
 *
 * Problem Source: 
 * Problem URL: https://dmoj.ca/problem/dwite12c1p4
 * Tutorial:
 * 
 * Author: Ahmad Maged
 * Date: August 30, 2024
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 255
#define TEST_CASES 5

typedef struct node
{
    int candy;
    struct node *left, *right;
} node;

typedef struct queue
{
    node *values[SIZE];
    int head;
    int tail;
} queue;

typedef struct stack
{
    node *values[SIZE];
    int highest_used;
} stack;

queue *new_queue(void)
{
    queue *q = malloc(sizeof(queue));
    q->head = -1;
    q->tail = -1;

    return q;
}

void enqueue(queue *q, node *value)
{
    if (q->head == -1)
        q->head++;
    q->tail++;
    q->values[q->tail] = value;
}

node *dequeue(queue *q)
{
    node *removed = q->values[q->head];
    q->head++;
    return removed;
}

int is_empty_queue(queue *q)
{
    return (q->head == -1 || q->head > q->tail);
}

node *peek_queue(queue *q)
{
    if (!is_empty_queue(q))
        return q->values[q->head];
    return NULL;
}

stack *new_stack(void)
{
    stack *s = malloc(sizeof(stack));
    s->highest_used = -1;
    return s;
}

void push_stack(stack *s, node *value)
{
    s->highest_used++;
    s->values[s->highest_used] = value;
}

node *pop_stack(stack *s)
{
    node *removed = s->values[s->highest_used];
    s->highest_used--;

    return removed;
}

int is_empty_stack(stack *s)
{
    return s->highest_used == -1;
}

node *peek_stack(stack *s)
{
    if (!is_empty_stack(s))
        return s->values[s->highest_used];
    return NULL;
}

int tree_candy(node *tree)
{
    int total = 0;
    stack *s = new_stack();

    while (tree != NULL)
    {
        if (tree->left && tree->right) {
            push_stack(s, tree->left);
            tree = tree->right;
        }
        else {
            total += tree->candy;
            if (is_empty_stack(s))
                tree = NULL;
            else
                tree = pop_stack(s);
        }
    }

    return total;
}

int tree_height(node *tree)
{
    if (tree == NULL)
        return 0;
    
    queue *q = new_queue();
    
    int height = -1, level;
    enqueue(q, tree);
    while (!is_empty_queue(q))
    {
        level = q->tail - q->head + 1;
        height++;

        while (level)
        {
            tree = dequeue(q);
            if (tree->left && tree->right)
            {
                enqueue(q, tree->left);            
                enqueue(q, tree->right);
            }

            level--;
        }
    }

    return height;
}

int tree_nodes(node *tree)
{
    int total = 0;
    stack *s = new_stack();

    while (tree)
    {
        if (tree->left && tree->right)
        {
            push_stack(s, tree->left);
            tree = tree->right;
        }
        else
        {
            if (is_empty_stack(s))
                tree = NULL;
            else
                tree = pop_stack(s);
        }
        total++;
    }

    return total;
}


int tree_streets(node *tree)
{
    return (tree_nodes(tree) - 1) * 2;
}

void tree_solve(node *tree)
{
    int candy = tree_candy(tree);
    int height = tree_height(tree);
    int num_streets = tree_streets(tree) - height;
    printf("%d %d\n", num_streets, candy);
    
}

node *read_tree(char *line)
{
    node *tree = NULL;
    stack *s = new_stack();

    while (*line != '\0')
    {
        if (*line == ' ')
        {
            line++;
            continue;
        }
        
        if (*line == '(')
        {
            tree = malloc(sizeof(node));
            push_stack(s, tree);
            line++;
            continue;
        }
        
        if (*line == ')')
        {
            tree = pop_stack(s);
            line++;
        }
        else
        {
            tree = malloc(sizeof(node));
            tree->left = NULL;
            tree->right = NULL;
            
            tree->candy = *line - '0';
            line++;
            if (*line != ')' && *line != ' ')
            {
                tree->candy = tree->candy * 10 + *line - '0';
                line++;
            }
        }
        
        if (!is_empty_stack(s))
        {
            if (peek_stack(s)->left == NULL)
                peek_stack(s)->left = tree;
            else
                peek_stack(s)->right = tree;
        }
        else
            break;
    }
    
    return tree;
}

int main(void)
{
    char line[SIZE + 1];
    node *tree;
    for (int i = 0; i < TEST_CASES; i++)
    {
        fgets(line, SIZE + 1, stdin);
        tree = read_tree(line);
        tree_solve(tree);
    }

    return 0;
}
