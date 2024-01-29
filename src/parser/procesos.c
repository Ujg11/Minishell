#include "minishell.h"

void   print_pcs_recur(t_pcs *pcs, size_t index)
{
    if (!pcs || !pcs->argv || index >= pcs->argv->size)
        return;
    if (pcs->types)
        printf("Tipo: %d - Arguments: %s\n", pcs->types[index], pcs->argv->words[index].word);
    else
        printf("Tipo: -1 - Arguments: %s\n", pcs->argv->words[index].word);
    print_pcs_recur(pcs, index + 1);
}

void    print(t_pcs *pcs)
{
    if (!pcs || !pcs->argv || pcs->argv->size == 0 || !pcs->argv->words)
    {
        printf("Oe payaso no hay nada 🤡\n");
        return;
    }
    printf("Procesos:\n");
    print_pcs_recur(pcs, 0);
}

void    print_pcs_types(t_tokens *tokens, int operator_types[])
{
    if (!tokens || !tokens->words)
    {
        printf("No hay tipos asociados a psc. gil:\n");
        return;
    }
    printf("Aqui si hay tipos asociados a pcs wapo:\n");
    size_t i = 0;
    while (i < tokens->size)
    {
        printf("%d ", operator_types[(unsigned char)tokens->words[i].word[0]]);
        i++;
    }
    printf("\n");
}