/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:52:19 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/08/01 16:25:26 by tkaragoz         ###   ########.fr       */
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
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, int n);
char	*ft_strchr(const char *str, int c);
int		ft_isdigit(int c);
int		ft_isnumeric(char *str);
long	ft_atoi(const char *str);
void	execution(char **cmd, t_env **env);


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

typedef struct		s_hash
{
	char			*key;
	void			*value;
	char			*type;
	struct s_hash	*top;
	struct s_hash	*before;
	struct s_hash	*next;
	struct s_hash	*(*new)(char *, void *, char *);
	void			(*add_front)(struct s_hash **, struct s_hash *);
	void			(*add_back)(struct s_hash **, struct s_hash *);
	void			(*del)(struct s_hash **);
	void			(*del_all)(struct s_hash **);
	void			*(*search)(struct s_hash *, char *);
	struct s_hash	*(*find)(struct s_hash *, char *);
	void			(*change)(struct s_hash *, char *, void *, char *);
	size_t			(*len)(struct s_hash *);
	void			(*print)(struct s_hash *, char *);
	void			(*sort_key)(struct s_hash **, struct s_hash *);
	void			(*rsort_key)(struct s_hash **, struct s_hash *);
	void			(*sort_val)(struct s_hash **, struct s_hash *);
	void			(*rsort_val)(struct s_hash **, struct s_hash *);
}					t_hash;


typedef struct		s_strhash
{
	char	*key;
	char	*value;
}					t_strhash;

typedef struct s_env
{
	char			*id;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_sh
{
	char		**key;
	char		**value;
	char		***cmd;
	char		**path;
	t_hash		*hash;
	t_env		*env;
	t_hash		*add;
	char		printed;
	short		question_mark;
	char		*redir;
	int			fd[2];
	char		*target_file;
	int			stdin_bkp;
}				t_sh;

// Env functions
t_env	*get_env_var(t_env *env, char *var);
void	env_var_add(t_env **head_env, t_env *new);
void	set_env_var(t_env **env, char *id, char *value);
t_env	*env_create(char *env_entry);
t_env	*create_env_list(char **env);
void	node_free(t_env *node);
void	env_free(t_env *env_list);

//builtin functions
int		is_builtin(char *cmd);
void	exec_builtin(char **cmd, t_env **env);
void	cmd_free(char **cmd);

#endif
