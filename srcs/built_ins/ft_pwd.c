/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:38:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/08 11:47:18 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_shell *shell, t_arg *command)
{
	char	*cwd;
	int 	fd_out = command->fd_out;

	(void)shell;
	cwd = get_current_pwd();
	if (!cwd)
		return (EXIT_FAILURE);
	ft_putstr_nl(cwd, fd_out);
	free(cwd);
	return (EXIT_SUCCESS);
}
