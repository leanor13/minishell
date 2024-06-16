/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:31:55 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/16 16:23:21 by thuy-ngu         ###   ########.fr       */
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
}					t_env;

typedef struct s_shell
{
	bool			no_env;
	t_env			*env_list;
	char			**env_2d;
	int				std_fds[3];
	t_arg			*args_list;
	bool			here_doc;
	int				exit_status;
	int				here_doc_fd;
	bool			should_exit;
}					t_shell;

#define EXIT_CMD_NOT_FOUND 127
#define EXIT_SIGNAL_OFFSET 128

/* main flow */
int					init_shell(t_shell *shell, char **env);

/* parsing */
int					main_parsing(t_shell *shell);

/* execution */
int					executor_main(t_shell *shell);
int					process_command_fds(t_arg *command, t_shell *shell);

/* built-ins */
int					ft_pwd(t_shell *shell, t_arg *command);
int					ft_env(t_shell *shell, t_arg *command);
int					ft_echo(t_shell *shell, t_arg *command);
int					ft_unset(t_shell *shell, t_arg *command);
int					ft_exit(t_shell *shell, t_arg *command);
int					ft_cd(t_shell *shell, t_arg *command);
int					ft_export(t_shell *shell, t_arg *command);
int					add_var(int sign, char *equal_sign, t_shell *shell, char *var_name);
int					no_variable(char *equal_sign, char *var_name);
char				*get_current_pwd(void);
void				ft_delnode(t_env **env_list, int l);
int					is_valid_varname(const char *var_name);
void				ft_changenode(t_env **env_list, char *copy_value);
int					add_var_nosign(char *var_name, t_shell *shell, int sign, int i, char **args);
/* env handling */
int					convert_env_lst_to_2d(t_env *env_lst, char ***env_2d);
int					update_env_2d(t_shell *shell);
int					add_back_env(t_env **head, char *var_name, char *var_value);
int					parse_env(t_shell *shell, char **env);
t_env				*env_find_var(t_env *env_lst, char *var_name);
int					save_2d_env(char **arr, char ***dest);

/* executor functions */
int					exec_pipe(t_shell *shell);
void				handle_child_process(t_arg *command, t_shell *shell);
pid_t				handle_parent_process(t_arg *command, t_shell *shell,
						int *fd_pipe);
int					wait_for_children(int count, t_shell *shell);

/* cleanup */
void				free_shell(t_shell *shell);
void				free_string_array(char ***str_arr);
void				free_command_list(t_arg **command_list);
void				exit_pipe_error(int fd[2]);
void				free_args(t_arg **args_list);

/* handle commands */
int					build_command_list(t_shell *shell);
char				*dir_start_calc(char *command, char **envp);
char				*envp_path(char **envp);
bool				check_built_in(t_arg *command);
int					dir_len_count(char *dir_start);
char				*absolute_path(char *command);
int					here_doc(t_arg *command, t_shell *shell);
int					open_file(char *file, int type);
int					args_count(t_arg *args_list);
int					child_count(t_arg *args_list);

/* close fds */
void				close_all_protected(t_shell *shell);
void				close_all_unprotected(void);
void				close_pipes(int *fd_pipe);
void				dup_close(int fd, int reference);
void				ft_close(int fd);
