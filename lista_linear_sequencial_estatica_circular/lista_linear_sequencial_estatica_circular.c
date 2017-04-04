#include <stdlib.h>
#include <stdio.h>
#include "lista_linear_sequencial_estatica_circular.h"

list *new_list(int size)
{
    list *l = (list *)malloc(sizeof(list));
    l->items = (int *)malloc(size * sizeof(int));
    l->count = 0;
    l->first = -1;
    l->last = -1;
    l->max = size;
    return l;
}

int is_null(list *l)
{
    return l == NULL;
}

void clear(list *l)
{
    if (is_null(l))
        return;
    l->count = 0;
    l->first = -1;
    l->last = -1;
}

// list.c
void insert_last(int x, list *l)
{
    if (is_null(l))
        return;
    if (is_empty(l))
        insert_at(x, 0, l);
    else
        insert_at(x, l->last, l);
}

int remove_at(int i, list *l)
{
    if (is_null(l) ||
        is_empty(l) ||
        (i < 0 || i > l->last))
        return -1;
    int x = l->items[i];
    for (int j = i; j < l->last; j++)
    {
        l->items[j] = l->items[j + 1];
    }
    l->last--;
    l->count--;
    if (is_empty(l))
    {
        l->first = -1;
    }
    return x;
}

int is_empty(list *l)
{
    return is_null(l) || l->count == 0;
}

int is_full(list *l)
{
    return l->count == l->max;
}

void print(list *l)
{

    for (int i = 0; i < l->max; i++)
    {
        printf("Item[%d] = %d\n", i, l->items[i]);
    }
    return;
    printf("0");
    if (l->first > l->last)
    {
        printf("1");
        for (int i = l->first; i <= l->max - 1; i++)
        {
            printf("Item[%d] = %d\n", i, l->items[i]);
        }
        for (int i = 0; i <= l->last; i++)
        {
            printf("Item[%d] = %d\n", i, l->items[i]);
        }
    }
    else
    {
        printf("2");
        for (int i = l->first; i <= l->last; i++)
        {
            printf("Item[%d] = %d\n", i, l->items[i]);
        }
    }
}

void destroy_list(list **l)
{
    free((*l)->items);
    free(*l);
    *l = NULL;
}

//Remove o último elemento e o retorna
int remove_last(list *l)
{
    if (is_null(l))
        return -1;
    return remove_at(l->last, l);
}

//Remove o primeiro elemento e o retorna
int remove_first(list *l)
{
    if (is_null(l))
        return -1;
    return remove_at(l->first, l);
}

//Insere o elemento x na posição i
void insert_at(int x, int i, list *l)
{
    //se a lista for nula ou estiver cheia nao é possivel inserir
    if (is_null(l) ||
        is_full(l))
        return;

    //condicao especial quando a lista é vazia
    if (is_empty(l))
    {
        if (i != 0)
        {
            printf("return 0\n");
            return;
        }
        l->items[0] = x;
        l->first = 0;
        l->last = 0;
        l->count = 1;
        printf("return 1\n");
        return;
    }

    //se a lista nao estiver vazia,
    //nao eh possivel inserir fora do intervalo da lista
    if (i < 0 || (i != l->count && i > l->last))
    {
        printf("i=%d, l->first:%d, l->last:%d, l->count:%d, return 2\n", i, l->first, l->last, l->count);
        return;
    }

    if (i == l->first)
    {
        int j = position(INSERT_FIRST, l);
        l->first = j;
        l->items[j] = x;
    }
    else if (i == l->last)
    {
        int j = position(INSERT_LAST, l);
        l->last = j;
        l->items[j] = x;
    }
    else // inserindo no meio da lista
    {
        int old_last = l->last;
        if (l->last == l->max - 1)
        {
            l->items[0] = l->items[l->max - 1];
            l->last = 0;
        }
        else
        {
            l->last++;
        }
        for (int j = old_last; j >= i; j--)
        {
            l->items[j + 1] = l->items[j];
        }
        l->items[i] = x;
    }
    l->count++;
}

//Insere um elemento na primeira posição
void insert_first(int x, list *l)
{
    if (is_null(l))
        return;
    if (is_empty(l))
        insert_at(x, 0, l);
    else
        insert_at(x, l->first, l);
}

//Procura por um elemento e retorna sua posição
int search(int x, list *l)
{
    if (is_null(l) || is_empty(l))
        return -1;

    if (l->first > l->last)
    {
        for (int i = l->first; i < l->max - 1; i++)
        {
            if (x == l->items[i])
                return i;
        }
        for (int i = 0; i < l->last; i++)
        {
            if (x == l->items[i])
                return i;
        }
    }
    else
    {
        for (int i = l->first; i < l->last; i++)
        {
            if (x == l->items[i])
                return i;
        }
    }
    return -1;
}

static int position(operation_t op, list *l)
{
    switch (op)
    {
    case INSERT_FIRST:
        if (l->first == -1)
            return 0;
        if (l->first == 0)
            return l->max - 1;
        return l->first - 1;
        break;
    case INSERT_LAST:
        if (l->last == -1)
            return 0;
        if (l->last == l->max - 1)
            return 0;
        return l->last + 1;
        break;
    case REMOVE_FIRST:
        if (l->first == -1)
            return -1;
        if (l->first == l->max - 1)
            return 0;
        return l->first - 1;
        break;
    case REMOVE_LAST:
        if (l->last == -1)
            return -1;
        if (l->last == 0)
            return l->max - 1;
        return l->last + 1;
        break;
    default:
        return -1;
        break;
    }
}