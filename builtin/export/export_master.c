/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:49:13 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/25 12:07:31 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_export(char **param, t_data *data)
{
	int		i;

	i = 1;
	while (param[i])
	{
		if (!export_valid_args_counter(param[i]))
			return (export_error_handler(param[i], NULL, NULL));
		i++;
	}
	i = 1;
	while (param[i])
	{
		export_finalizer(param[i], 0, data);
		i++;
	}
}

void	export_finalizer(char *args, int i, t_data *data)
{
	char		*var_name;
	char		*var_value;

	var_name = extract_var_name(args, i);
	if (!var_name)
		return ;
	printf("varnam = %s\n", var_name);
	var_value = extract_var_value(args, i);
	printf("varval = %s\n", var_value);
	if (!var_value)
		return (free(var_name));
	printf("%s - %s\n\n", var_name, var_value);
	do_export(var_name, var_value, data);
}

void	do_export(char *var_name, char *var_value, t_data *data)
{
	char	*var;
	t_env	*nav;

	nav = NULL;
	var = ft_strjoin(var_name, "=");
	if (!var_value)
		var_value = ft_strdup("");
	if (is_there_quotes(var_value))
		var_value = quote_remover_v2(var_value);
	var = strjoin_and_free(var, var_value);
	if (!ft_get_env_node(data->env, var_name))
		add_var_to_env(data, var);
	else
	{
		nav = ft_get_env_node(data->env, var_name);
		free(nav->var);
		nav->var = var;
	}
	free(var_name);
}
