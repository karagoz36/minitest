/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:30:27 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/07/29 18:13:07 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env_var(t_env *env, char *var)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->id, var) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	env_var_add(t_env **head_env, t_env *new)
{
	t_env	*tmp;

	if (!head_env || !new)
		return ;//exit
	if (!*head_env)
		*head_env = new;
	else
	{
		tmp = (*head_env);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	set_env_var(t_env *env, char *id, char *value)
{
	t_env	*var;
	t_env	*new;
	char	*new_value;

	new_value = ft_strdup(value);
	if (!new_value)
		return ;//(NULL);139 euros TTC (taxe de séjour incluse)

	var = get_env_var(env, id);
	if (var)
	{
		free(var->value);
		var->value = new_value;
	}
	else
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (!new)
			return ;//(NULL);
		new->id = ft_strdup(id);
		new->value = new_value;
		new->next = NULL;
		env_var_add(&(env), new);
	}
}

t_env	*env_create(char *env_entry)
{
	t_env	*new_env;
	char	*eq_sign;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	eq_sign = ft_strchr(env_entry, '=');
	if (!eq_sign)
	{
		free(new_env);
		return (NULL);
	}
	new_env->id = ft_strndup(env_entry, eq_sign - env_entry);
	new_env->value = ft_strdup(eq_sign + 1);
	new_env->next = NULL;
	return (new_env);
}

t_env	*create_env_list(char **env)
{
	int		i;
	t_env	*new;
	t_env	*env_list;

	env_list = NULL;
	if (!env || !*env)
		return (env_create("_=/usr/bin/env"));
	i = 0;
	while (env[i])
	{
		new = env_create(env[i]);
		if (!new)
			return (NULL);
		env_var_add(&env_list, new);
		i++;
	}
	return (env_list);
}
void	env_free(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->id);
		free(tmp->value);
		free(tmp);
	}
}
