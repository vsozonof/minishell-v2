/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_utils-2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:49:44 by vsozonof          #+#    #+#             */
/*   Updated: 2024/06/12 16:55:35 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char c)
{
	if (c == 39 || c == '"' || c == '>' || c == '<')
		return (0);
	return (1);
}

int	is_there_redirs(t_prompt *prompt)
{
	int	i;

	i = 0;
	if (!prompt->input[i])
		return (0);
	while (prompt->input[i])
	{
		if ((prompt->input[i] == '>' || prompt->input[i] == '<')
			&& !is_in_quotes(prompt->input, i))
			return (1);
		i++;
	}
	return (0);
}

int	get_heredoc_counter(t_cmd *node)
{
	t_cmd	*pr;
	t_redir	*ptr;
	int		i;

	i = 0;
	pr = node;
	while (pr)
	{
		ptr = pr->redirs;
		while (ptr)
		{
			if (ptr->type == LIMITER)
				i++;
			ptr = ptr->next;
		}
		pr = pr -> next;
	}
	return (i);
}

int	set_redir_type(char *token)
{
	if (token[0] == '>' && !token[1])
		return (0);
	else if (token[0] == '<' && !token[1])
		return (1);
	else if (token[0] == '<' && token[1] == '<' && !token[2])
		return (2);
	else if (token[0] == '>' && token[1] == '>' && !token[2])
		return (3);
	printf("Error with redir type\n");
	return (-1);
}
