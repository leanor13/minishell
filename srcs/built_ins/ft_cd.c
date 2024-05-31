/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:25:54 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/31 12:02:43 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_shell *shell, t_arg *command)
{
	char	*path;
	char	cwd[PATH_MAX];
	t_arg	update_cmd;
	char	*pwd_update;
	int		export_status;

	if (command->arguments[1] == NULL)
		return (ft_putstr_fd("cd: expected an argument\n", STDERR_FILENO),
			EXIT_FAILURE);
	else
		path = command->arguments[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		return (perror(path), EXIT_FAILURE);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("cd: error retrieving current directory"), EXIT_FAILURE);
	pwd_update = ft_strjoin("PWD=", cwd);
	if (!pwd_update)
		return (ft_putstr_fd("cd: failed to allocate memory for PWD update\n",
				STDERR_FILENO), EXIT_FAILURE);
	update_cmd.arguments = (char *[]){"export", pwd_update, NULL};
	export_status = ft_export(shell, &update_cmd);
	return (free(pwd_update), export_status);
}
