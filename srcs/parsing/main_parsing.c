/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/05 18:09:21 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct
{
	int		heredoc_active;
	int		heredoc_fd;
	int		exit_status;
}			SignalState;

SignalState	signal_state = {0, -1, 0};

// Handler for SIGINT in the main and prompt context
void	sigint_main_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

// Handler for SIGINT in heredoc
void	sigint_heredoc_handler(int sig)
{
    (void)sig;
    if (signal_state.heredoc_active && signal_state.heredoc_fd != -1)
    {
        close(signal_state.heredoc_fd);
    }
	signal_state.exit_status = 130;
}

// Sets up different signal configurations
void	setup_signals(int context)
{
	signal(SIGQUIT, SIG_IGN);
	if (context == SIG_MAIN)
	{
		signal(SIGINT, sigint_main_handler);
	}
	else if (context == SIG_MAIN_2)
	{
		signal(SIGINT, sigint_main_handler);
	}
	else if (context == SIG_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (context == SIG_HEREDOC)
	{
		signal(SIGINT, sigint_heredoc_handler);
	}
	else if (context == SIG_IGNORE)
	{
		signal(SIGINT, SIG_IGN);
	}
}

static int	dup_std_fds(t_shell *shell)
{
	if (dup2(shell->std_fds[0], STDIN_FILENO) == -1) // Reset STDIN_FILENO
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	if (dup2(shell->std_fds[1], STDOUT_FILENO) == -1) // Reset STDIN_FILENO
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	if (dup2(shell->std_fds[2], STDERR_FILENO) == -1) // Reset STDIN_FILENO
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main_parsing(t_shell *shell)
{
	char	*command;
	t_arg	*lst;
	int		exit_status;
	//int		lst_num;

	command = NULL;
	exit_status = EXIT_SUCCESS;
	//setup_signals(SIG_MAIN);
	if (dup_std_fds(shell) != EXIT_SUCCESS)
	{
		return (EXIT_FAILURE);
	}
	lst = NULL;
	while (1)
	{
		if (shell->should_exit)
		{
			exit_status = shell->exit_status;
			free_shell(shell);
			exit(exit_status);
		}
		lst = NULL;
		command = NULL;
		command = readline("\033[1;36mminishell\033[1;32m$\033[0;0m");
		if (command == NULL)
		{
			ft_putstr_nl("exit", STDOUT_FILENO);
			free_shell(shell);
			exit(exit_status);
		}
		add_history(command);
		lst = ft_lexer(command, lst);
		/* t_arg *current = lst;
		lst_num = 0;
		while (current)
		{
		// printf("%sOUTPUT\n", current->out_file);
		// printf("%sHEREDOC\n", current->here_doc);
			lst_num++;
			printf("---NODE%i before parser---\n", lst_num);
			printf(" %s,", current->str);
			printf("type %i\n", current->type);
			current = current->next;
		} */
		lst = ft_parser(lst, shell);
		shell->args_list = lst;
		if (shell->args_list != NULL)
			executor_main(shell);
		free_args(&shell->args_list);
		free(command);
		close_all_protected(shell);
	}
	return (EXIT_SUCCESS);
}
