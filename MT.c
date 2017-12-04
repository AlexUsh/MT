#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 255
#define MIXCHAR 0
#define ERROR -1
typedef struct turing MT;
typedef struct turing {
    int key;
    MT *left, *right;
} MT;
int inc(MT *node);
int dec(MT *node);

int movl(MT **node);
int movr(MT **node);
void print(MT *node);
void get(MT *node);

void clearMemory(MT **node);
void clearLeft(MT **node);
void clearRight(MT **node);

int main(int argc, const char * argv[]) {


    MT *root = malloc(sizeof(MT));
    if (!root) {
        fprintf(stderr ,"Out of memory. Can't perform malloc\n");
        return ERROR;
    }
    int i;
    root->key = 0;
    root->left = root->right = NULL;

    FILE *file;
    file=fopen(argv[1],"r");
    char str[256];
    if(file == NULL)
    {
        printf("Can't find the file!");
        return -1;
    }
    else
    {
        while(!feof(file))
        {
            fgets(str, 256, file);

            for(i = 0; (str[i] != '\n') && ((str[i] < 'a') || (str[i] > 'z')); i++)
                ;
            if (str[i] == 'i')
            {
                inc(root);
            }
            else if (str[i] == 'd')
            {
                dec(root);
            }
            else if (str[i] == 'p')
            {
                print(root);
            }
            else if (str[i] == 'g')
            {
                get(root);
            }
            else if (str[i+3] == 'l')
            {
                movl(&root);
            }
            else if (str[i+3] == 'r')
            {
                movr(&root);
            }
        }
    }
    fclose(file);
    clearMemory(&root);
    return 0;
}

int inc(MT *node) {
    if (node->key == MAXCHAR) {
        fprintf(stderr, "Out of range");
        return ERROR;
    }
    else {
        node->key++;
        return 0;
    }
}

int dec(MT *node) {
    if (node->key == MIXCHAR) {
        fprintf(stderr, "Out of range");
        return ERROR;
    }
    else {
        node->key--;
        return 0;
    }
}

int movl(MT **node) {
    if (!(*node)->left) {
        (*node)->left = malloc(sizeof(MT));
        if (!(*node)->left) {
            fprintf(stderr ,"Out of memory. Can't perform malloc\n");
            return ERROR;
        }

        (*node)->left->right = (*node);
        (*node) = (*node)->left;
        (*node)->left = NULL;
        (*node)->key = 0;
        return 0;
    }
    else {
        (*node) = (*node)->left;
        return 0;
    }
}

int movr(MT **node) {
    if (!(*node)->right) {
        (*node)->right = malloc(sizeof(MT));
        if (!(*node)->right) {
            fprintf(stderr ,"Out of memory. Can't perform malloc\n");
            return ERROR;
        }
        (*node)->right->left = (*node);
        (*node) = (*node)->right;
        (*node)->right = NULL;
        (*node)->key = 0;
        return 0;
    }
    else {
        (*node) = (*node)->right;
        return 0;
    }
}

void print(MT *node) {
    printf("%d\n", node->key);
}

void get(MT *node) {
    scanf("%d", &(node->key));
}

void clearMemory(MT **node) {
    if ((*node)->left) {
        clearLeft(&(*node)->left);
    }
    if ((*node)->right) {
        clearRight(&(*node)->right);
    }
    free(*node);
}

void clearLeft(MT **node) {
    if ((*node)->left) {
        clearLeft(&(*node)->left);
    }
    free(*node);
}

void clearRight(MT **node) {
    if ((*node)->right) {
        clearRight(&(*node)->right);
    }
    free(*node);
}
