/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:35:01 by vsozonof          #+#    #+#             */
/*   Updated: 2024/06/04 08:16:56 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_sbase(t_prompt *ptr, char **env)
{
	if (!init_sig(ptr))
		return (0);
	if (getenv("HOME"))
	{
		if (!init_if_env(ptr, env))
			return (0);
	}
	else
	{
		if (!init_if_no_env(ptr, env))
			return (0);
	}
	return (1);
}

int	init_if_no_env(t_prompt *ptr, char **envp)
{
	t_env	*env_l;

	env_l = malloc(sizeof(t_env));
	if (!env_l)
		return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
	if (!put_env_to_lst(env_l, envp))
		return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
	ptr->env = env_l;
	ptr->user = ft_strdup("???");
	if (!ptr->user)
		return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
	ptr->post = ft_strdup("???");
	if (!ptr->post)
		return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
	ptr->w_d = getcwd(NULL, 0);
	if (!ptr->w_d)
		return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
	return (1);
}

int	init_if_env(t_prompt *ptr, char **env)
{
	t_env				*env_l;

	env_l = malloc(sizeof(t_env));
	if (!env_l)
		return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
	else
	{
		if (!put_env_to_lst(env_l, env))
			return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
		ptr->env = env_l;
		ptr->user = ft_strdup(getenv("LOGNAME"));
		if (!ptr->user)
			return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
		ptr->post = ft_substr(getenv("SESSION_MANAGER"), 6, 12);
		if (!ptr->post)
			return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
		ptr->w_d = getcwd(NULL, 0);
		if (!ptr->w_d)
			return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
	}
	return (1);
}

int	init_extras(t_prompt *ptr)
{
	ptr->name = ft_strdup("minishell");
	if (!ptr->name)
		return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
	ptr->pid = ft_itoa((int)getpid());
	if (!ptr->pid)
		return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
	ptr->data->i_status = 0;
	ptr->data->c_status = ft_itoa(ptr->data->i_status);
	if (!ptr->data->c_status)
		return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
	ptr->data->exited = 0;
	if (!create_side_env(ptr))
		return (0);
	return (1);
}

int	init_str(t_data *data, t_prompt *prompt)
{
	t_input	**multi_inp;
	t_input	*inp;

	inp = alloc_input_struct();
	if (!inp)
		return (set_status(data, 12, "malloc error", "malloc"), 0);
	multi_inp = NULL;
	data->exec = NULL;
	prompt->inp = ((data->inp = inp));
	prompt->multi_inp = ((data->multi_inp = multi_inp));
	data->head = NULL;
	data->new_head = NULL;
	data->tail = NULL;
	data->to_add = NULL;
	data->redir_tab = NULL;
	data->n_redirs = 0;
	data->nb_here_doc = 0;
	data->input = prompt->input;
	data->pr = prompt;
	data->env = prompt->env;
	data->tab = NULL;
	data->cmds = NULL;
	data->here_doc_fd = NULL;
	return (1);
}
