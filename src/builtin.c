/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:42:05 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/06 16:55:32 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exec_echo(t_cmd *cmd)
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
void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->id, tmp->value);
		tmp = tmp->next;
	}
}

void	exec_env(char **cmd, t_env *env)
{
	if (cmd[1])
	{
		printf("env: '%s': No such file or directory\n", cmd[1]);
		return ;
	}
	print_env(env);
}

int	exec_pwd(char **cmd)
{
	char	*cwd;
	int		i;

	i = 0;
	if (cmd[1] && cmd[1][0] == '-')
	{
		while (cmd[1][i])
		{
			if (cmd[1][i] != '-')
				return (printf("minishell> pwd: %c%c: invalid option\n\
						pwd: usage: pwd [-LP]", cmd[1][0], cmd[1][1]), 1);
			i++;
		}
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("minishell> getcwd() error"), 1);
	printf("minishell> %s\n", cwd);
	free(cwd);
	return (0);
}

void	exec_export(t_cmd *cmd, t_env **env)
{
	int		i;
	char	*eq_sign;


	if (!cmd[1])
	{
		print_env(*env);
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		eq_sign = NULL;
		eq_sign = ft_strchr(cmd[1], '=');
		if (eq_sign)
		{
			*eq_sign = '\0';
			set_env_var(env, cmd[i], eq_sign + 1);
			*eq_sign = '=';
		}
		i++;
	}

}

int	exec_cd(t_cmd *cmd, t_env **env)
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
		home_env = get_env_var(*env, "HOME");
		if (!home_env || !home_env->value)
			return (free(old_cwd), printf("minishell> cd: HOME not set\n"), 1);
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

int	env_remove(char	*arg, t_env **env)
{
	t_env	*target;
	t_env	*pre_target;

	if (!arg || !env || !*env)
		return (0);
	target = *env;
	while (target && ft_strcmp(arg, target->id) != 0)
	{
		pre_target = target;
		target = target->next;
	}
	if (!target)
		return (0);
	if (target == *env)
		*env = target->next;
	else
		pre_target->next = target->next;
	node_free(target);
	return (1);
}

int	exec_unset(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (ft_strcmp("_", cmd[i]) != 0 && env_remove(cmd[i], env))
			return (1);
		i++;
	}
	return (0);
}

void	exit_error(char *str)
{
	ft_putstr_fd("minishell> exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

int	exec_exit(t_cmd *cmd, t_env *env)
{
	int	exit_status;

	exit_status = 0;
	printf("exit\n");
	if (cmd[1])
	{
		if (ft_isnumeric(cmd[1]))
		{
			if (cmd[2])
				return (ft_putendl_fd("minishell> exit: too many arguments",
						STDERR_FILENO), 1);
			else
				exit_status = ft_atoi(cmd[1]) % 255;
		}
		else
		{
			exit_error(cmd[1]);
			exit_status = 2;
		}
	}
	env_free(env);
	exit(exit_status);
}

void	exec_builtin(t_cmd *cmd, t_env **env)
{
	if (ft_strcmp(cmd->name, "echo") == 0)
		exec_echo(cmd);
	else if (ft_strcmp(cmd->name, "cd") == 0)
		exec_cd(cmd, env);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		exec_pwd(cmd);
	else if (ft_strcmp(cmd->name, "export") == 0)
		exec_export(cmd, env);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		exec_unset(cmd, env);
	else if (ft_strcmp(cmd->name, "env") == 0)
		exec_env(cmd, *env);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		exec_exit(cmd, *env);
}

int	is_builtin(t_cmd *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}
