/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:52:19 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/06 14:55:28 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <stddef.h>
# include <errno.h>
# include <fcntl.h>

# define PROMPT "DARK_BLUEMinishell : \033[0m"

int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, int n);
char	*ft_strchr(const char *str, int c);
int		ft_isdigit(int c);
int		ft_isnumeric(char *str);
long	ft_atoi(const char *str);
// void	execution(char **cmd, t_env **env);


typedef struct s_env
{
	char			*id;
	char			*value;
	char			*sum;
	struct s_env	*next;
}				t_env;

typedef struct s_args
{
	char			*value;
	struct s_args	*next;
}	t_args;

typedef struct s_filenames
{
	char				*name;
	t_token_type		type;
	struct s_filenames	*next;
}	t_filenames;

typedef struct s_cmd
{
	char			*name;
	t_args			*args;
	t_filenames		*redirs;
	struct s_exec	*next;
	int				fd_in;
	int				fd_out;
}	t_cmd;

typedef struct s_sh
{
	int				fd_in;
	int				fd_out;
	char			exit_code;
	int				cmd_count;
	pid_t			*pids;
	int				pid_count;
	t_cmd			*cmd;
	t_env			*env;
}	t_sh;

// Env functions
t_env	*get_env_var(t_env *env, char *var);
void	env_var_add(t_env **head_env, t_env *new);
void	set_env_var(t_env **env, char *id, char *value);
t_env	*env_create(char *env_entry);
t_env	*create_env_list(char **env);
void	node_free(t_env *node);
void	env_free(t_env *env_list);
int		env_lstsize(t_env *env);

//builtin functions
int		is_builtin(char *cmd);
void	exec_builtin(char **cmd, t_env **env);
void	cmd_free(char **cmd);

#endif
