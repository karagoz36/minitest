/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:00:17 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/08/01 17:30:00 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fork_process(char ***cmd, t_env **env)
{

}

void	execution(char ***cmd, t_env **env)
{
	if (cmd[i] && cmd[i][0])
		ft_fork_process(cmd[i], env);
}
