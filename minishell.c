/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:49:48 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/07/19 13:23:49 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <sys/types.h>


int	is_n_flag(char *flag)
{
	int	i;

	if (ft_strncmp(flag, "-n", 2))
		return (0);
	i = 2;
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	exec_echo(char **cmd)
{
	int	i;
	int	nl;

	// if (!cmd[1])
	// {
	// 	printf("%s", "\n");
	// 	return ;
	// }
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

void	exec_builtin(char **cmd)
{
	exec_echo(cmd);
}

// int	main(void)
// {
// 	char	*cmd[] = {"echo", "-n", "livre", NULL};

// 	exec_builtin(cmd);
// 	return (0);
// }

int	is_builtin(char *cmd)
{
	return (strcmp(cmd, "echo") == 0);
	// Add more built-in commands here
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

		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}

		args = malloc(sizeof(char *) * (strlen(input) / 2 + 2));
		i = 0;
		args[i] = strtok(input, " ");
		while (args[i])
			args[++i] = strtok(NULL, " ");

		if (is_builtin(args[0]))
			exec_builtin(args);
		else
			printf("Command not found: %s\n", args[0]);

		free(args);
		free(input);
	}
	return (0);
}
