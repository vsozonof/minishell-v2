/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 08:40:59 by ertupop           #+#    #+#             */
/*   Updated: 2023/09/27 09:10:34 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_close_here_fd(t_use *here, t_list *gc)
{
	while (here)
	{
		if (here->tokken == LIMITER)
		{
			here->fd = open(here->file_name, O_RDONLY);
			unlink(here->file_name);
			gc_dell_one(gc, &here->file_name);
			here->file_name = NULL;
		}
		here = here->next;
	}
}

void	ft_clear_here(t_use *here, t_list *gc)
{
	while (here)
	{
		if (here->tokken == OUTFILE || here->tokken == INFILE
			|| here->tokken == APPEND)
			close(here->fd);
		else if (here->tokken == LIMITER)
		{
			gc_dell_one(gc, &here->file_name);
			close(here->fd);
		}
		here = here->next;
	}
}
