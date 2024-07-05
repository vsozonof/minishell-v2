/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:29:44 by vsozonof          #+#    #+#             */
/*   Updated: 2024/07/05 20:43:33 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// valgrind --leak-check=full --suppressions=rl_leak_ignore.supp --show-leak-kinds=all ./minishell
int	g_status = 0;

int	get_input(t_prompt *prompt, t_data *data)
{
	struct sigaction	sa;

	while (!data->exited)
	{
		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_handler = &handle_signals;
		sigaction(SIGINT, &sa, NULL);
		printf("%s at %s in: %s", prompt->user, prompt->post, prompt->w_d);
		prompt->input = readline("\n$> ");
		if (prompt->input)
		{
			if (!is_input_valid(prompt->input, prompt->data))
				free(prompt->input);
			else
			{
				add_history(prompt->input);
				input_parser(prompt, data);
			}
		}
		else
			break ;
	}
	if (!data->exited)
		printf("exit\n");
	return (free_end_of_program(prompt), data->i_status);
}

void	init_vars(t_prompt *ptr)
{
	ptr->user = NULL;
	ptr->w_d = NULL;
	ptr->post = NULL;
	ptr->env = NULL;
	ptr->name = NULL;
	ptr->pid = NULL;
	ptr->nv = NULL;
	ptr->data->c_status = NULL;
	ptr->data->i_status = 0;
}

int	main(int argc, char **argv, char *envp[])
{
	t_prompt	prompt;
	t_data		data;

	(void)argc;
	(void)argv;
	prompt.data = &data;
	data.pr = &prompt;
	init_vars(&prompt);
	if (!init_sbase(&prompt, envp) || !init_extras(&prompt))
	{
		free_end_of_program(&prompt);
		return (data.i_status);
	}
	return (get_input(&prompt, &data));
}
