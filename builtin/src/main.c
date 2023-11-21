/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:28:13 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/21 17:28:37 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_status;

int main(int ac, char **av, char **env)
{
	(void)av;
	char	*line;
	//char	*cmd[2] = {"export", 0};
	char	**cdd;
	char	**echoo;
	//char	**unsett;
	char	**exportt;
	t_list	*env_perso;
	static char	**env_cpy;


	cdd = 0;
	echoo = 0;
	env_cpy = copy_tab(env);
	env_perso = env_to_lst(env);
	line = 0;
	if (ac != 1)
		return (1);
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (0);
	while (1)
	{
		line = readline("minishrek-V0.1$ ");
		if (!line)
			exit(0);
		if (line && *line)
			add_history(line);
		if (!ft_strcmp(line, "pwd"))
			pwd();
		else if (!ft_strncmp(line, "export", 6))
		{
			exportt = ft_split(line, 32);
			export(exportt, env_cpy);
			if (exportt)
				free_tab(exportt);
		}
		else if (!ft_strncmp(line, "cd", 2))
		{
			cdd = ft_split(line, 32);
			// printf("cd return code [%d]\n", cd(cdd, env_cpy));
			free_tab(cdd);
		}
		else if (!ft_strcmp(line, "env"))
			env_builtin(env_cpy);
		else if (!ft_strncmp(line, "echo", 4) && line[0] == 32)
		{
			echoo = ft_split(line, 32);
			echo(echoo);
			free_tab(echoo);
		}
		/*else if (!ft_strncmp(line, "unset", 5))
		{
			unsett = ft_split(line, 32);
			unset(unsett);
			free_tab(unsett);
		}*/
		else if (!ft_strcmp(line, "\n"))
			ft_putendl_fd("\n", 1);
		else if (!ft_strcmp(line, "exit"))
			break ;
		else if (ft_strlen(line))
			printf("bash: %s: command not found\n", line);
		free(line);
	}
	rl_clear_history();
	ft_lstclear(&env_perso, &free);
	free(line);
	if (env_cpy)
		free_tab(env_cpy);
	return(0);
}

/*int	main(void)
{
	int		i = 0;
	char	**tmp;

	while (__environ[i])
		i++;
	printf("%d\n", i);
	tmp = copy_tab(__environ);
	i = 0;
	while (__environ[i])
	{
		__environ[i] = 0;
		i++;
	}
	__environ = 0;
	i = 0;
	__environ = ft_calloc(sizeof(char *), 50);
	if (!__environ)
		return (printf("damn"), 1);
	while (new_env[i])
	{
		__environ[i] = ft_strdup(new_env[i]);
		i++;
	}
	__environ = tmp;
	tmp = 0;
	i = 0;
    while(__environ[i]) {
		printf("%s\n", __environ[i]);
        i++;
    }
    printf("Il y a %d variables d'environnement.\n", i);
	free_tab(__environ);
    return 0;
}*/

/*int	main(void)
{
	int		i;

	i = 0;
	while (__environ[i])
		i++;
	printf("%d\n", i);
	init_environ();
	i = 0;
	while (__environ[i])
	{
		printf("%s\n", __environ[i]);
		i++;
	}
	free_tab(__environ);
    return 0;
}*/
