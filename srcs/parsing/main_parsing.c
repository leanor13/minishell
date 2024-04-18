/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/18 20:41:42 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char *command = NULL;
	//char **args;
	//bool get_command;
	//get_command = true; //or you can do the opposite false, and it is getting true if there is something
	//int i = 1;
	ft_printf("\033[1;36mminishell\033[1;32m$\033[0;0m");
	//(get_command)
	while (1)	
	{
		//THNK ON THIIIS
// 		readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,
// printf, malloc, free, write, access, open, read,
// close
		//command = readline("minishell$");
		command = readline("");
		ft_printf("\033[1;36mminishell\033[1;32m$\033[0;0m");
		ft_printf("%s", command);
	//args = split_command(command);
//readline  returns  the  text of the line read.  A blank
    //    line returns the empty string.  If EOF  is  encountered
    //    while  reading  a  line, and the line is empty, NULL is
    //    returned.  If an EOF is read with a non-empty line,  it
    //    is treated as a newline.
   // free(command);
    //free(args);		//if()
		//get_command = false;
		//i++;
	}
}