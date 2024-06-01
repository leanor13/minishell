/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:38:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/30 16:54:15 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_current_pwd(void)
{
	char	*buffer;

	buffer = (char *)ft_calloc(PATH_MAX, sizeof(char));
	if (buffer != NULL)
	{
		if (getcwd(buffer, PATH_MAX) == NULL)
		{
			perror("getcwd() error");
			free(buffer);
			return (NULL);
		}
	}
	else
		perror("ft_calloc() error");
	return (buffer);
}

int	ft_pwd(t_shell *shell, t_arg *command)
{
	char	*cwd;
	int		fd_out;

	fd_out = STDOUT_FILENO;
	(void)shell;
	(void)command;
	cwd = get_current_pwd();
	if (!cwd)
		return (EXIT_FAILURE);
	ft_putstr_nl(cwd, fd_out);
	free(cwd);
	return (EXIT_SUCCESS);
}
