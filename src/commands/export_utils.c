#include "minishell.h"
#define TRUE 1
#define FALSE 0

int mod_strcmp(char *cmd, char *env)
{
    int i = 0;

    while (cmd[i] && env[i])
    {
        if (cmd[i] == '=' && env[i] == '=')
            return (TRUE);
        if (cmd[i] != env[i])
            return (FALSE);
        i++;
    }
    if (cmd[i] == '\0' && (env[i] == '\0' || env[i] == '='))
        return (TRUE);
    return (FALSE);
}

void    replace_value(char *cmd, t_env *env)
{
    int i = 0;

    while (env->env_cpy[i] != NULL)
    {
        if (mod_strcmp(cmd, env->env_cpy[i]) == TRUE)
        {
            free(env->env_cpy[i]);
            env->env_cpy[i] = strdup(cmd);
            return;
        }
        i++;
    }
}

int    var_exist(char *cmd, t_env *env)
{
    int i = 0;

    while (env->env_cpy[i] != NULL)
    {
        if (mod_strcmp(cmd, env->env_cpy[i]) == TRUE)
            return (TRUE);
        i++;
    }
    return (FALSE);
}