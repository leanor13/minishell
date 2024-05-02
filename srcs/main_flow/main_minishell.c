/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:44:26 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/02 14:57:24 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argv;
	if (argc > 1)
		return (ft_putstr_nl("No arguments allowed for minishell", STDERR_FILENO), EXIT_FAILURE);
	init_shell(&shell, env);
	main_parsing(&shell);
	//ft_clean(); - this function will use free_stackfinal as well
	return (EXIT_SUCCESS);
} */