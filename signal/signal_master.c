/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:27:48 by vsozonof          #+#    #+#             */
/*   Updated: 2024/07/02 11:27:02 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signum)
{
	t_prompt	ptr;
	char		*tmp;

	if (signum == SIGINT)
	{
		ptr.user = getenv("LOGNAME");
		tmp = getenv("SESSION_MANAGER");
		ptr.post = ft_substr(tmp, 6, 12);
		ptr.w_d = getcwd(NULL, 0);
		if (g_status != 2)
		{
			printf("\n%s at %s in: %s\n", ptr.user, ptr.post, ptr.w_d);
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
		}
		if (g_status == 2)
			close(STDIN_FILENO);
		g_status = 1;
		free(ptr.post);
		free(ptr.w_d);
	}
	else if (signum == SIGQUIT)
		rl_on_new_line();
}

int	init_sig(t_prompt *prompt)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(struct sigaction));
	ft_memset(&sa_quit, 0, sizeof(struct sigaction));
	sa_int.sa_handler = handle_signals;
	sa_quit.sa_handler = handle_signals;
	if (sigaction(SIGINT, &sa_int, NULL) == -1
		|| sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		return (set_status(prompt->data, 1, NULL, "signal error"), 0);
	return (1);
}
