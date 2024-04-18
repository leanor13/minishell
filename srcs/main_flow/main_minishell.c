/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:44:26 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/18 12:44:52 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	ft_prompt();
	ft_block_signals();
	ft_parsing();
	ft_init();
	ft_pipex();
	return (EXIT_SUCCESS);
}