#include "minishell.h"

char *ft_strstr(const char *haystack, const char *needle) {
    if (*needle == '\0')
        return (char *)haystack;

    while (*haystack != '\0') {
        const char *h = haystack;
        const char *n = needle;
        while (*n != '\0' && *h == *n) {
            h++;
            n++;
        }
        if (*n == '\0')
            return (char *)haystack;
        haystack++;
    }
    return NULL;
}
void handle_path_export(char *cmd, t_env *env) {
    char *existing_path = find_existing_path(env);

    if (existing_path != NULL) {
        free(existing_path);
        existing_path = ft_strdup(cmd);
    } else {
        add_new_path(cmd, env);
    }
}

char *find_existing_path(t_env *env) {
    char *path_variable = "PATH=";
    int k = 0;

    while (env->env_cpy[k] != NULL) {
        if (ft_strstr(env->env_cpy[k], path_variable) == env->env_cpy[k]) {
            return env->env_cpy[k];
        }
        k++;
    }

    return NULL;
}

void add_new_path(char *cmd, t_env *env) {
    int j = 0;
    while (env->env_cpy[j] != NULL)
        j++;
    env->env_cpy[j - 1] = ft_strdup(cmd);
}