/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:25:54 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/30 17:13:49 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_shell *shell, t_arg *command)
{
	char	*path;
	char	cwd[PATH_MAX];
	t_arg	update_cmd;

	if (command->arguments[1] == NULL)
    {
        ft_putstr_fd("cd: expected an argument\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
	else
		path = command->arguments[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(path);
		return (EXIT_FAILURE);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd: error retrieving current directory");
		return (EXIT_FAILURE);
	}
	char *pwd_update = ft_strjoin("PWD=", cwd);
	if (!pwd_update)
	{
		ft_putstr_fd("cd: failed to allocate memory for PWD update\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	update_cmd.arguments = (char*[]){"export", pwd_update, NULL};
	ft_export(shell, &update_cmd);
	free(pwd_update);
	return (EXIT_SUCCESS);
}
