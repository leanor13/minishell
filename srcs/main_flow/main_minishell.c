/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:44:26 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/24 13:39:58 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argv;
	if (argc > 1)
		return (ft_putstr_nl("No arguments allowed for minishell", STDERR_FILENO), EXIT_FAILURE);
	init(&shell, env);
	run_shell(&shell);
	//ft_clean();
	return (EXIT_SUCCESS);
}