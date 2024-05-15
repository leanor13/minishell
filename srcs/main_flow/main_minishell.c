/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:44:26 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/13 22:25:18 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argv;
	if (argc > 1)
		return (ft_putstr_nl("No arguments allowed for minishell", STDERR_FILENO), EXIT_FAILURE);
	(void)env;
	init_shell(&shell, env);
	main_parsing(&shell);
	//ft_clean(); - this function will use free_stackfinal as well
	return (EXIT_SUCCESS);
}