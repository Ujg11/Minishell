#include "minishell.h"

void    ft_unset(char *variable, t_env *env)
{
    int i = 0;
    char **env_ptr = env->env_cpy;

    while (env_ptr[i] != NULL)
    {
        if (strncmp(env_ptr[i], variable, strlen(variable)) == 0)
        {
            while (env_ptr[i] != NULL)
            {
                env_ptr[i] = env_ptr[i + 1];
                i++;
            }
            return;
        }
        i++;
    }
}