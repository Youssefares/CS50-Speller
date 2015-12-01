/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <xlocale.h>
#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
int x = 0;
bool check(const char* word)
{
        node* ptr = table[hash(word)];
        char* wordz = malloc(strlen(word)*sizeof(char)+1);
        strcpy(wordz,word);
        for(int i = 0; i < strlen(wordz); i++)
             wordz[i] = tolower(wordz[i]);
        while (ptr != NULL)
        { 
            if(!strcmp(ptr->word,wordz)){
                free(wordz);
                return true;
            }
            ptr = ptr->next;
        }
    free(wordz);
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    
    for (int i = 0; i < 4; i++)
    {
        table[i] = NULL;
    }
    
    char bar[46];
    FILE* fp = fopen(dictionary,"r");
    
    while(fscanf(fp,"%s",bar) != EOF)
    {
        insert(bar);
    }
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return x;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < 27; i++)
    {
        node* ptr = table[i];
        while (ptr != NULL)
        {
            node* temp = ptr;
            ptr = ptr-> next;
            free(temp);
        }
        free(ptr);
    }
    return true;
}

int hash(const char* foo)
{
    if(foo[0] == '\'')
        return 26;
    else
        return tolower(foo[0])-'a';
}

void insert(const char* newword)
{
    node* newptr = malloc(sizeof(node));
    if(newptr == NULL)
        return;
    newptr->word = malloc(sizeof(char)*45 + 1);
    strcpy(newptr->word,newword);
    newptr->next = NULL;
    int hasher = hash(newword);
    
    if(newptr->word == NULL)
    {
        return;
    }
    
    if(table[hasher] == NULL)
    {
        table[hasher] = newptr;
        x++;
    }
    
    else
    {
        newptr->next = table[hasher];
        table[hasher] = newptr;
        x++;
    }    
}
