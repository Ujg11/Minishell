#include "minishell.h"
#define TRUE 1 
#define FALSE 0

void    bubble_sort(char **arr, int size, int i)
{
    if (i == size - 1)
    return;
    if (strcmp(arr[i], arr[i + 1]) > 0)
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
    int i = 0;

    while (env->env_cpy[i] != NULL)
    {
        char    *equal_sign; strchr(env->env_cpy[i], '=');
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
    while (env->env_cpy[i] != NULL)
        i++;
    env->env_cpy = calloc(sizeof(char *), i + 2);
    int j = 0;
    while (j < i)
    {
        env->env_cpy[j] = strdup(patata[j]);
        free(patata[j]);
        j++;
    }
    env->env_cpy[j++] = strdup(cmd);
    env->env_cpy[j] = NULL;
    free(patata);
}

void    ft_export(t_env *env, char **cmd)
{
    int i = 0;
    if (cmd[0] == NULL)
        special_export(env);
    else
    {
        while (cmd[i] != NULL)
        {
            if (strcmo(cmd[i], "0") == 0)
                printf("bash: export: `%s': not a valid identifier\n", cmd[i]);
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
}