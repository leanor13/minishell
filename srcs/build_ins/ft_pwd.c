/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:38:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/19 11:13:01 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(char **env, char **args, int fd_out)
{
	char	*cwd;

	(void)env;
	(void)args;
	cwd = get_current_pwd();
	if (!cwd)
		return (NEG_ERROR);
	ft_putstr_nl(cwd, fd_out);
	free(cwd);
	return (EXIT_SUCCESS);
}
