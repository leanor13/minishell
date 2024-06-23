/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/23 14:04:40 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_signal(void)
{
	struct sigaction	signal;
	struct sigaction	act;

	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	signal.sa_handler = &child_handler_function;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &signal, NULL);
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGTERM, &act, NULL);
}

void	main_signal(void)
{
	struct sigaction	signal;
	struct sigaction	act;

	signal.sa_handler = &main_handler_function;
	signal.sa_flags = SA_RESTART;
	act.sa_flags = SA_RESTART;
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	sigemptyset(&signal.sa_mask);
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGTERM, &act, NULL);
}

t_shell	*var(void)
{
	static t_shell	tmp;

	return (&tmp);
}

void	heredoc_sig(int code)
{
	if (code == SIGINT)
	{
		free_shell(var()->tmp);
		exit(EXIT_HEREDOC_BREAK);
	}
}
