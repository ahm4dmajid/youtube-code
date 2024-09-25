/*
 * File: index.c
 *
 * Problem Source: 
 * Problem URL: https://dmoj.ca/problem/dwite12c1p4
 * Tutorial: https://www.youtube.com/watch?v=vkhb-XDl5m0
 * 
 * Author: Ahmad Maged
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define TEST_CASES 5

typedef struct node
{
    int candy;
    struct node *left, *right;
} node;


int tree_candy(node *tree)
{
    if (!tree->left && !tree->right)
        return tree->candy;
    
    return tree_candy(tree->left) + tree_candy(tree->right);
}

int tree_streets(node *tree)
{
    if (!tree->left && !tree->right)
        return 0;
				
    return tree_streets(tree->left) + tree_streets(tree->right) + 4;
}

int max(int v1, int v2)
{
    return (v1 > v2) ? v1 : v2;
}

int tree_height(node *tree)
{
    if (!tree->left && !tree->right)
        return 0;
    
    return 1 + max(tree_height(tree->left), tree_height(tree->right));
}

void tree_solve(node *tree)
{
    int candy = tree_candy(tree);
    int height = tree_height(tree);
    int num_streets = tree_streets(tree) - height;
    printf("%d %d\n", num_streets, candy);
}

node *read_tree_helper(char *line, int *pos)
{
    node *tree;
    tree = malloc(sizeof(node));
    if (line[*pos] == '(')
    {
        (*pos)++;
        tree->left = read_tree_helper(line, pos);
        (*pos)++;
        tree->right = read_tree_helper(line, pos);
        (*pos)++;
        
        return tree;
    }
    else
    {
        tree->left = NULL;
        tree->right = NULL;
        tree->candy = line[*pos] - '0';
        (*pos)++;
        
        if (line[*pos] != ')' && line[*pos] != ' ')
        {
            tree->candy = tree->candy * 10 + line[*pos] - '0';
            (*pos)++;
        }
        
        return tree;
    }
}

node *read_tree(char *line)
{
    int pos = 0;
    return read_tree_helper(line, &pos);
}

int main()
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
