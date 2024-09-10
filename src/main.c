/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:49:48 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/05 18:02:07 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	init_sign(void)
{
	rl_event_hook = sig_event;
	signal(SIGINT, sig_inthandler);
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGTSTP, SIG_IGN);
}
int	handle_input(t_sh *sh, char *input)
{
	return (0);
}

t_sh	*init_sh(char	**env)
{
	t_sh	*sh;

	sh = (t_sh *)malloc(sizeof(t_sh) * 1);
	if (!sh)
		return (NULL);
	sh->env = create_env_list(env);
	if (!sh->env)
	{
		free(sh);
		return (NULL);
	}
	sh->fd_in = STDIN_FILENO;
	sh->fd_out = STDOUT_FILENO;
	sh->exec = NULL;
	sh->pids = NULL;
	sh->exec_count = 0;
	sh->pid_count = 0;
	sh->exit_code = 0;
	return (sh);
}

void	handle_loop(t_sh *sh)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		else if (*input)
		{
			add_history(input);
			if (!handle_line(sh, input))
			{
				ft_printf_fd(STDOUT_FILENO, "Error in handling line\n");
				sh->exit_code = 2;
			}
			//line = NULL;
		}
		if (input)
			free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_sh	*sh;

	(void)argv[argc];
	sh = init_sh(env);
	if (!sh)
		return (NULL);
	init_sign();
	main_loop(sh);
	ft_printf_fd(STDOUT_FILENO, "%s\n", "exit");
	return (EXIT_SUCCESS);
}
