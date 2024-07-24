/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:47:08 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/07/24 16:22:43 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *env_create(char *env_entry)
{
    t_env *new_env;
    char *eq_sign;

    new_env = (t_env *)malloc(sizeof(t_env));
    if (!new_env)
        return (NULL);

    eq_sign = strchr(env_entry, '=');
    if (!eq_sign)
    {
        free(new_env);
        return (NULL);
    }

    new_env->id = strndup(env_entry, eq_sign - env_entry);
    new_env->value = strdup(eq_sign + 1);
    new_env->next = NULL;

    return (new_env);
}

static void env_add_back(t_env **head, t_env *new_env)
{
    t_env *temp;

    if (!head || !new_env)
        return;

    if (!*head)
    {
        *head = new_env;
        return;
    }

    temp = *head;
    while (temp->next)
        temp = temp->next;

    temp->next = new_env;
}

void env_free(t_env *env_list)
{
    t_env *temp;

    while (env_list)
    {
        temp = env_list;
        env_list = env_list->next;
        free(temp->id);
        free(temp->value);
        free(temp);
    }
}

t_env *convert_env_to_list(char **env)
{
    t_env *env_list = NULL;
    t_env *new_env;
    int i = 0;

    while (env[i])
    {
        new_env = env_create(env[i]);
        if (new_env)
            env_add_back(&env_list, new_env);
        i++;
    }

    return env_list;
}

char *env_get_id(char *env_entry)
{
    char *eq_sign = strchr(env_entry, '=');
    if (!eq_sign)
        return (NULL);

    return strndup(env_entry, eq_sign - env_entry);
}

char *env_get_value(char *env_entry)
{
    char *eq_sign = strchr(env_entry, '=');
    if (!eq_sign)
        return (NULL);

    return strdup(eq_sign + 1);
}

void print_env_list(t_env *env_list)
{
    t_env *temp = env_list;

    while (temp)
    {
        printf("%s=%s\n", temp->id, temp->value);
        temp = temp->next;
    }
}
