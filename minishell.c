/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:49:48 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/07/29 16:31:14 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <sys/types.h>

int	main(int argc, char **argv, char **env)
{
	t_sh	*sh;
	//t_env	*env_list;
	char	*input;
	char	*prompt = "minishell> ";
	char	**args;
	int		i;

	(void)argv[argc];
	sh->env = create_env_list(env);
	while (1)
	{
		input = readline(prompt);
		if (!input)
			break ;
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			env_free(env);
			break ;
		}

		args = malloc(sizeof(char *) * (strlen(input) / 2 + 2));
		i = 0;
		args[i] = strtok(input, " ");
		while (args[i])
			args[++i] = strtok(NULL, " ");

		if (args[0] && is_builtin(args[0]))
			exec_builtin(args, env);
		else
			printf("Command not found: %s\n", args[0]);

		free(args);
		free(input);
	}
	return (0);
}
