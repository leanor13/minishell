/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	int		status;

	(void)argv;
	if (argc > 1)
		return (ft_putstr_nl("No arguments allowed for minishell", STDERR_FILENO), EXIT_FAILURE);
	(void)env;
	init_shell(&shell, env);
	status = main_parsing(&shell);
	free_shell(&shell);
	//ft_clean(); - this function will use free_stackfinal as well
	return (status);
}