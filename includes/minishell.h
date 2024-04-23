/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:31:55 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/23 12:00:05 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "lexer.h"

#include <dirent.h>

/* built-ins */
int		ft_pwd(char **env, char **args, int fd_out);
int		ft_env(char **env, char **args, int fd_out);
int		ft_echo(char **env, char **args, int fd_out);
int		ft_unset(char **env, char **args, int fd_out);
int		ft_exit(char **env, char **args, int fd_out);
int		ft_cd(char **env, char **args, int fd_out);
char	*ft_getenv(char **env, const char *name);
char	*get_current_pwd(void);