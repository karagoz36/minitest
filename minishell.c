/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:49:48 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/07/19 18:41:34 by tkaragoz         ###   ########.fr       */
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

int	exec_cd(/*t_sh *sh, */char **cmd)
{
	int		i;
	char	*cwd;

	i = 0;

	while (cmd[i])
		i++;
	if (i > 1)
		return (printf("minishell> cd: too many arguments\n"));
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		printf("")
	}
	printf("%s\n", cwd);
	return (0);
}

void	exec_builtin(/*t_sh *sh, */char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		exec_echo(cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		exec_cd(/*sh, */cmd);
}


int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0);
}

int	main(void)
{
	char	*input;
	char	*prompt = "minishell> ";
	char	**args;
	int		i;

	while (1)
	{
		input = readline(prompt);
		if (!input)
			break ;
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}

		args = malloc(sizeof(char *) * (strlen(input) / 2 + 2));
		i = 0;
		args[i] = strtok(input, " ");
		while (args[i])
			args[++i] = strtok(NULL, " ");

		if (args[0] && is_builtin(args[0]))
			exec_builtin(args);
		else
			printf("Command not found: %s\n", args[0]);

		free(args);
		free(input);
	}
	return (0);
}
