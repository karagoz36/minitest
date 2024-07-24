/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:49:48 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/07/24 19:29:20 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <sys/types.h>


int	is_n_flag(char *flag)
{
	int	i;

	if (ft_strncmp(flag, "-n", 2))
	{
		return (0);
	}
	i = 2;
	while (flag[i])
	{
		if (flag[i] != 'n')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	exec_echo(char **cmd)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	while (cmd[i] && is_n_flag(cmd[i]))
	{
		nl = 0;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[++i])
			printf("%s", " ");
	}
	if (nl)
		printf("%s", "\n");
}

void	exec_env(char **cmd, t_env *env)
{
	print_env_list(env);
}

int	exec_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("minishell> getcwd() error"), 1);
	printf("minishell> %s\n", cwd);
	free(cwd);
	return (0);
}

t_env	*get_env_var(t_env *env, char *var)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->id, var) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	env_var_m(t_env *env, t_env *new)
{
	t_env	*tmp;

	if (!env)
	{
		env = new;
		return ;
	}
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->id, new->id) == 0)
		{
			tmp->value = new->value;
			break ;
		}
		else
			tmp = tmp->next;
	}
}

void	set_env_var(t_env *env, char *id, char *value)
{
	t_env	*var;
	t_env	*new;
	char	*new_value;

	new_value = ft_strdup(value);
	if (!new_value)
		return ;//(NULL);
	var = get_env_var(env, id);
	if (!var)
	{
		free(var->value);
		var->value = new_value;
		return ;//(0);
	}
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;//(NULL);
	new->id = id;
	new->value = value;
	new->next = NULL;
	env_var_m(env, new);
}

int	exec_cd(char **cmd, t_env *env)
{
	int		i;
	t_env	*home_env;
	char	*old_cwd;
	char	*cwd;
	char	*new_dir;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
		return (ft_putendl_fd("minishell> cd: too many arguments",
				STDERR_FILENO), 1);
	old_cwd = getcwd(NULL, 0);
	if (!old_cwd)
		return (perror("minishell> getcwd() error"), 1);
	if (i == 1 || ft_strcmp(cmd[1], "--") == 0)
	{
		home_env = get_env_var(env, "HOME");
		if (!home_env || !home_env->value)
			return (free(old_cwd), ("minishell> cd: HOME not set\n"), 1);
		new_dir = home_env->value;
		free(home_env);
	}
	else
		new_dir = cmd[1];
	if (chdir(new_dir) != 0)
		return (free(old_cwd), perror("minishell> cd"), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(old_cwd),
			perror("minishell> cd: error retrieving current directory"), 1);
	set_env_var(env, "OLDPWD", old_cwd);
	set_env_var(env, "PWD", cwd);
	return (0);
}

void	exec_builtin(char **cmd, t_env *env)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		exec_echo(cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		exec_cd(cmd, env);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		exec_pwd();
	// else if (ft_strcmp(cmd[0], "export") == 0)
	// 	exec_env(cmd, env);
	// else if (ft_strcmp(cmd[0], "unset") == 0)
	// 	exec_env(cmd, env);
	else if (ft_strcmp(cmd[0], "env") == 0)
		exec_env(cmd, env);
	// else if (ft_strcmp(cmd[0], "exit") == 0)
	// 	exec_env(cmd, env);
}


int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit"));
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	char	*input;
	char	*prompt = "minishell> ";
	char	**args;
	int		i;

	(void)argv[argc];
	env_list = convert_env_to_list(env);
	while (1)
	{
		input = readline(prompt);
		if (!input)
			break ;
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			env_free(env_list);
			break ;
		}

		args = malloc(sizeof(char *) * (strlen(input) / 2 + 2));
		i = 0;
		args[i] = strtok(input, " ");
		while (args[i])
			args[++i] = strtok(NULL, " ");

		if (args[0] && is_builtin(args[0]))
			exec_builtin(args, env_list);
		else
			printf("Command not found: %s\n", args[0]);

		free(args);
		free(input);
	}
	return (0);
}
