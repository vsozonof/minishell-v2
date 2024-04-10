/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrub <rstrub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 06:50:00 by ertupop           #+#    #+#             */
/*   Updated: 2023/10/31 11:55:30 by rstrub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(char **tab, t_env *env, t_list *gc)
{
	if (ft_size_tab(tab) > 2)
		ft_putstr_fd("minishell: cd : too many arguments", 2);
	else if (ft_size_tab(tab) == 1)
		return (0);
	else
		return (ft_cd_2(tab[1], env, gc));
	return (0);
}

int	ft_cd_2(char *path, t_env *env, t_list *gc)
{
	t_env	*tmp;
	t_env	*old;
	char	*tmpo;

	tmpo = NULL;
	tmpo = getcwd(tmpo, 0);
	if (chdir(path) != 0 || tmpo == NULL)
	{
		ft_putstr_fd("minishell: cd : No Such file or directory\n", 1);
		return (1);
	}
	free(tmpo);
	tmpo = NULL;
	tmp = ft_get_env_pos(env, "PWD");
	if (tmp == NULL)
		return (1);
	old = ft_get_env_pos(env, "OLDPWD");
	if (old == NULL)
		ft_cd3(tmp->str + 4, env, gc);
	else
		old->str = gc_join_str(&gc, "OLDPWD=", tmp->str + 4);
	tmpo = getcwd(tmpo, 0);
	tmp->str = gc_join_str(&gc, "PWD=", tmpo);
	free(tmpo);
	return (0);
}

void	ft_cd3(char *old, t_env *env, t_list *gc)
{
	char	*tmpo;

	tmpo = ft_strjoin("OLDPWD=", old);
	ft_add_export(tmpo, &env, gc);
	free(tmpo);
}
