/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:49:48 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/08/01 16:38:39 by tkaragoz         ###   ########.fr       */
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
	char commands[][3][10] = {
        {"ls", "-l", "-a"},        // Command: ls with flags -l and -a
        {"grep", "-i", "-v"},      // Command: grep with flags -i and -v
        {"gcc", "-o", "-Wall"},    // Command: gcc with flags -o and -Wall
        {"rm", "-f", "-r"},        // Command: rm with flags -f and -r
    };

	(void)argv[argc];
	sh->env = create_env_list(env);
	while (1)
	{
		input = readline(prompt);
		if (!input)
			break ;

		args = malloc(sizeof(char *) * (strlen(input) / 2 + 2));
		i = 0;
		args[i] = strtok(input, " ");
		while (args[i])
			args[++i] = strtok(NULL, " ");
		if (args[0] && is_builtin(args[0]))
			exec_builtin(args, &(sh->env));
		else if (args[0])
			execution(commands, sh->env);
		else
			printf("Command not found: %s\n", args[0]);

		free(args);
		free(input);
	}
	return (0);
}
