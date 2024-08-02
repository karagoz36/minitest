/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:00:17 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/08/02 15:04:06 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**cnv_env_array(t_env *env)
{
	char	*env_arr;
	int		size;
	int		i;

	i = 0;
	size = env_lstsize(env);
	env_arr = (char **)malloc(sizeof(char *) * (size + 1));
	while (env)
	{

		env = env->next;
		i++;
	}
}

void	exec_cmd(char ***cmd, t_env *env)
{
	char	**env_arr;

	env_arr = cnv_env_array(env);
}

int	ft_fork_process(char ***cmd, t_env **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		return ((ft_putendl_fd(strerror(errno))), 1);
	if (pid == 0)
		exec_cmd(cmd, *env);
	else
		wait (&status);
	return (0);
}

void	execution(char ***cmd, t_env **env)
{
	if (cmd[i] && cmd[i][0])
		ft_fork_process(cmd[i], env);
}
