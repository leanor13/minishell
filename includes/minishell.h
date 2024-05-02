/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:31:55 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/02 16:52:46 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "lexer.h"

#include <dirent.h>

typedef struct s_env
{
	char			*var_name;
	char			*var_value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	bool	no_env;
	t_env	*env_shell;
	char	**env_original;
	int		std_fds[3];
	t_arg	*args_list;
	char	*here_doc;
	int		exit_status;
}	t_shell;


/* main flow */
int		init_shell(t_shell *shell, char **env);
//int		run_shell(t_shell *shell);

/* parsing */
int		main_parsing(t_shell *shell);

/* execution */
int	executor_main(t_shell *shell);
//int	main_pipex(int ac, char **av, char **env);

/* built-ins */
int		ft_pwd(char **env, char **args, int fd_out);
int		ft_env(char **env, char **args, int fd_out);
int		ft_echo(char **env, char **args, int fd_out);
int		ft_unset(char **env, char **args, int fd_out);
int		ft_exit(char **env, char **args, int fd_out);
int		ft_cd(char **env, char **args, int fd_out);
int		ft_export(char **env, char **args, int fd_out);

/* built-in helper */
char	*ft_getenv(char **env, const char *name);
int		ft_setenv(char ***env, const char *name, const char *value);
char	*get_current_pwd(void);

/* cleanup */
void	free_shell(t_shell *shell);
void	free_string_array(char ***str_arr);

/* testing */
void	print_env(t_env *env);

char		**ft_split_pipex(char *s, char c);
int			is_quote(char c);
int			build_command_list(t_shell *shell);
bool		check_built_in(t_arg *command);
int			dir_len_count(char *dir_start);
char		*absolute_path(char *command);
void		here_doc(char *limiter, int *fd_files);
int			open_file(int ac, char **av, int type);
void		open_files_here_doc(int ac, char **av, int fd_files[2]);
void		close_all_protected(void);
void		close_all_unprotected(void);

void		free_command_list(t_arg **command_list);
void		close_both_ends(int fd[2], bool pipe_error);
void		dup_close(int fd, int reference);
void		ft_close(int fd);
void		validate_params(int ac, char **av);
void		exit_pipe_error(int fd[2]);

int			exec_command(t_arg *command, int *fd, char **envp);
int			exec_pipe(t_arg *c_list, int fd_files[2], char **envp);
int			*handle_input(int ac, char **av);
int			args_count(t_arg *args_list);