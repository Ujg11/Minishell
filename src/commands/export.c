/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:52:19 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/08 19:30:43 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    bubble_sort(char **arr, int size, int i)
{
    if (i == size - 1)
        return;
    if (ft_strcmp(arr[i], arr[i + 1]) > 0)
    {
        char *temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
    }
    bubble_sort(arr, size, i + 1);
}

void   print_special_export(t_env *env, int count, int i)
{
    if (i < count)
    {
        printf("declare -x %s\n", env->env_cpy[i]);
        print_special_export(env, count, i + 1);
    }
}

void    special_export(t_env *env)
{
    printf("Executing special export\n");
    int i = 0;

    while (env->env_cpy[i] != NULL)
    {
        char    *equal_sign = ft_strchr(env->env_cpy[i], '=');
        if (equal_sign != NULL)
        {
            *equal_sign = '\0';
            printf("declare -x %s=\"%s\"\n", env->env_cpy[i], equal_sign + 1);
            *equal_sign = '=';
        }
        else
            printf("declare -x %s\n", env->env_cpy[i]);
        i++;
    }
}

void    normal_export(char *cmd, t_env *env)
{
    int i = 0;
    char **patata;

    patata = env->env_cpy;
    while (patata[i] != NULL)
        i++;
    env->env_cpy = ft_calloc(sizeof(char *), i + 2);
    int j = 0;
    while (j < i)
    {
        env->env_cpy[j] = ft_strdup(patata[j]);
        //free(patata[j]);
        j++;
    }
    env->env_cpy[j++] = ft_strdup(cmd);
    env->env_cpy[j] = NULL;
    //free(patata);
}

int    ft_export(char **cmd, t_env *env)
{
    int i = 0;
    if (cmd[0] == NULL)
    {
        printf("Executing export\n");
        special_export(env);
        return (0);
    }
    else
    {
        while (cmd[i] != NULL)
        {
            if (strcmp(cmd[i], "0") == 0)
            {
                printf("bash: export: `%s': not a valid identifier\n", cmd[i]);
                return (1);
            }
            else
            {
                if (var_exist(cmd[i], env) == TRUE)
                    replace_value(cmd[i], env);
                else
                    normal_export(cmd[i], env);
            }
            i++;
        }
    }
    return (0);
}

/*SOLO QUEDA UN CASI YA QUE EN ESTO:

    if (strcmp(cmd[i], "0") == 0) que eso podemos arrglarlo con un is_digit
            {
                printf("bash: export: `%s': not a valid identifier\n", cmd[i]);
                return (1);
            }
    TAMBIEN LE PUEDEN PASAR NUMEROS Y TIENE QUE DAR EL MISMO ERROR
    
    BASH-3.2$ export 1
BASH: export: `1': not a valid identifier
BASH-3.2$ export 2
BASH: export: `2': not a valid identifier
BASH-3.2$ export =
BASH: export: `=': not a valid identifier

CASOS PARA CONTROLAR

*/