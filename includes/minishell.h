/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:31:55 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/19 10:52:34 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <dirent.h>

/* build-ins */
int		ft_pwd(char **env, char **args, int fd_out);
int		ft_env(char **env, char **args, int fd_out);
char	*get_current_pwd(void);