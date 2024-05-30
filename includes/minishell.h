/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:31:55 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/22 16:10:36 by thuy-ngu         ###   ########.fr       */

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
	t_env	*env_list;
	char	**env_2d;
	int		std_fds[3];
	t_arg	*args_list;
	bool	here_doc;
	int		exit_status;
	int 	here_doc_fd;
	bool	should_exit;
}	t_shell;


/* main flow */
int		init_shell(t_shell *shell, char **env);
//int		run_shell(t_shell *shell);

/* parsing */
int		main_parsing(t_shell *shell);

/* execution */
int	executor_main(t_shell *shell);
int	process_command_fds(t_arg *command, t_shell *shell);
//int	main_pipex(int ac, char **av, char **env);

/* built-ins */
int		ft_pwd(t_shell *shell, t_arg *command);
int		ft_env(t_shell *shell, t_arg *command);
int		ft_echo(t_shell *shell, t_arg *command);
int		ft_unset(t_shell *shell, t_arg *command);
int		ft_exit(t_shell *shell, t_arg *command);
int		ft_cd(t_shell *shell, t_arg *command);
int		ft_export(t_shell *shell, t_arg *command);

/* built-in helper */
char	*ft_getenv(char **env, const char *name);
int		ft_setenv(char ***env, const char *name, const char *value);
char	*get_current_pwd(void);

/* env handling */
int		convert_env_lst_to_2d(t_env *env_lst, char ***env_2d);
int		update_env_2d(t_shell *shell);
int		add_back_env(t_env **head, char *var_name, char *var_value);
int		parse_env(t_shell *shell, char **env);
t_env	*env_find_var(t_env *env_lst, char *var_name);
int		save_2d_env(char **arr, char ***dest);

/* cleanup */
void	free_shell(t_shell *shell);
void	free_string_array(char ***str_arr);
void	free_command_list(t_arg **command_list);

int			is_quote(char c);
int			build_command_list(t_shell *shell);
bool		check_built_in(t_arg *command);
int			dir_len_count(char *dir_start);
char		*absolute_path(char *command);
int			here_doc(t_arg *command, t_shell *shell);
int			open_file(char *file, int type);
void		open_files_here_doc(int ac, char **av, int fd_files[2]);
void		close_all_protected(t_shell *shell);
void		close_all_unprotected(void);

void		close_both_ends(int fd[2], bool pipe_error);
void		dup_close(int fd, int reference);
void		ft_close(int fd);
void		validate_params(int ac, char **av);
void		exit_pipe_error(int fd[2]);

//int			exec_command(t_arg *command, t_shell *shell);
int			exec_pipe(t_shell *shell);
int			*handle_input(int ac, char **av);
int			args_count(t_arg *args_list);