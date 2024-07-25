/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:52:19 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/07/25 13:53:01 by tkaragoz         ###   ########.fr       */
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

int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t n);
char	*ft_strchr(const char *str, int c);

typedef struct s_list
{
	char				*var;
	char				*value;
	int					valid;
	int					valid2;
	struct s_list		*next;
}						t_list;

typedef struct s_file
{
	char				*name;
	int					mode;
	struct s_file		*next;
}						t_file;

typedef struct s_cmd
{
	char				*path;
	char				*cmd;
	char				**args;
	char				**env;
	int					pipe;
	int					in;
	int					out;
	t_file				*file;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_shell
{
	int					exit_status;
	char				*curr_dir;
	char				*path;
	char				**env;
	t_list				**var;
	t_cmd				*cmds;
}						t_shell;

//alexi
typedef struct		s_sh
{
	char		**key;
	char		**value;
	char		***cmd;
	char		**path;
	char		printed;
	short		question_mark;
	char		*redir;
	int			fd[2];
	char		*target_file;
	int			stdin_bkp;
}					t_sh;

typedef struct s_env
{
	char			*id;
	char			*value;
	struct s_env	*next;
}				t_env;

// Function prototypes
t_env   *env_create(char *env_entry);
void    env_free(t_env *env_list);
t_env   *convert_env_to_list(char **env);
char    *env_get_id(char *env_entry);
char    *env_get_value(char *env_entry);
void print_env_list(t_env *env_list);

#endif
