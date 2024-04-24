/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:31:55 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/24 17:05:18 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
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
	t_env	*shell_env;
	char	**env;
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
int	main_pipex(int ac, char **av, char **env);

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