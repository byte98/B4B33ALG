#include "../HW05/bst.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "../HW05/config.h"
#include <stdio.h>
#ifdef max
#undef max
#endif
#define max(a, b) ((a) > (b) ? (a) : (b))

#define bst_LCHILD(x) ((2 * (x)) + 1)
#define bst_RCHILD(x) ((2 * (x)) + 2)

void bst_insert(bst_t* tree, int data)
{
    #ifdef DEBUG
    printf("Inserting %d to tree...\n", data);
    #endif // DEBUG
    if (tree->nodes == 0)
    {
        if (tree->length < data)
        {
            bst_upscale(tree, data + 1);
        }
        tree->data[data] = 0;
        tree->nodes++;
        tree->root_index = data;
        #ifdef DEBUG
            printf("=> inserted to 0[%d] (first node)\n", data);
        #endif // DEBUG
    }
    else
    {
        bool set = FALSE;

        do
        {
            int idx = tree->root_index;
            if (tree->data[idx] == bst_EMPTY_NODE)
            {
                tree->data[data] = idx;
                tree->nodes++;
                set = TRUE;
            }
            else if (data > idx)
            {
                #ifdef DEBUG
                printf("\t\tData > stored (%d > %d) -> going to right subtree [%d]\n", data, idx, bst_RCHILD(idx));
                #endif // DEBUG
                idx = bst_find_data(tree, bst_RCHILD(tree->data[data]));
                
            }
            
        }
        while (set == FALSE);
    }
       
}

int bst_find_data(bst_t* tree, int index)
{
    int reti = bst_EMPTY_NODE;
    for (int i = 0; i < tree->length; i++)
    {
        if (tree->data[i] == index)
        {
            reti = i;
            break;
        }
    }
    return reti;
}