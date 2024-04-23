	// if (getenv("USER") == NULL)// ASK YULIA
	// 	init_missing_environment(shell, env);
	// else
	// {
	// 	shell->envless = FALSE;
	// 	shell->color_codes = TRUE;
	// 	shell->env_head = init_env(env);
	// 	shell->user_name = getenv("USER");
	// 	shell->cmd_paths = ft_split(get_path(env), ':');
	// }https://github.com/zstenger93/minishell/blob/master/src/init/init.c#L15



//Replace the environment variables into a linked list so you can delete or add to them later using export and unset builtins. In addition to displaying them using env or export (without arguments) builtins. 
//https://github.com/fraqioui/minishell?tab=readme-ov-file#Initializing