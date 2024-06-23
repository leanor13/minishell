/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 12:40:00 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/23 11:16:17 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	int		status;

	(void)argv;
	if (argc > 1)
	{
		ft_putstr_nl("No arguments allowed for minishell", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	(void)env;
	init_shell(&shell, env);
	status = main_util(&shell);
	free_shell(&shell);
	return (status);
}
