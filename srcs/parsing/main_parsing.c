/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/04 14:18:06 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct {
    int heredoc_active;
    int heredoc_fd;  // File descriptor to close on SIGINT in heredoc
} SignalState;

SignalState signal_state = {0, -1};

// Handler for SIGINT in the main and prompt context
void sigint_main_handler(int sig) {
    (void)sig;
    rl_replace_line("", 0);
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}

// Handler for SIGINT in heredoc
void sigint_heredoc_handler(int sig) {
    (void)sig;
    if (signal_state.heredoc_active && signal_state.heredoc_fd != -1) {
        close(signal_state.heredoc_fd);
    }
    exit(130);  // Exit status when interrupted by SIGINT
}

// Sets up different signal configurations
void setup_signals(int context) {
    struct sigaction sa;

    // Common setup for all handlers
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (context == MAIN) {
        sa.sa_handler = sigint_main_handler;
        sigaction(SIGINT, &sa, NULL);
    } else if (context == HERE_DOC) {
        sa.sa_handler = sigint_heredoc_handler;
        sigaction(SIGINT, &sa, NULL);
    }

    // Ignore SIGQUIT in all contexts
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
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

int main_parsing(t_shell *shell)
{
	char *command = NULL;
	t_arg *lst;
	int	exit_status = EXIT_SUCCESS;
	
	setup_signals(MAIN);
	if (dup_std_fds(shell) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
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
		int	lst_num = 0;
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
