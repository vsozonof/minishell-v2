/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 06:50:00 by ertupop           #+#    #+#             */
/*   Updated: 2024/06/21 10:42:30 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char **tab, t_env *env)
{
	if (ft_size_tab(tab) > 2)
		ft_putstr_fd("minishell: cd : too many arguments", 2);
	else if (ft_size_tab(tab) == 1)
		return (ft_home(env));
	else
		return (ft_cd_2(tab[1], env));
	return (0);
}

int	ft_home(t_env *env)
{
	char	*home;

	home = ft_get_env(env, "HOME");
	ft_cd_2(home, env);
	free(home);
	return (0);
}

int	ft_cd_2(char *path, t_env *env)
{
	t_env	*tmp;
	t_env	*old;
	char	*tmpo;

	tmpo = NULL;
	tmpo = getcwd(tmpo, 0);
	if (chdir(path) != 0 || tmpo == NULL)
	{
		if (tmpo)
			free(tmpo);
		ft_putstr_fd("minishell: cd : No Such file or directory\n", 2);
		return (1);
	}
	tmp = ft_get_env_pos(env, "PWD");
	if (tmp != NULL)
	{
		old = ft_get_env_pos(env, "OLDPWD");
		if (old == NULL)
			ft_add_oldpwd(tmp->var + 4, env);
		else
		{
			free(old->var);
			old->var = ft_strjoin("OLDPWD=", tmp->var + 4);
		}
		free(tmp->var);
		tmp->var = ft_strjoin("PWD=", tmpo);
	}
	else
		ft_add_pwd(tmpo, env);
	free(tmpo);
	return (0);
}

void	ft_add_oldpwd(char *old, t_env *env)
{
	char	*tmpo;

	tmpo = ft_strjoin("OLDPWD=", old);
	ft_add_export(tmpo, &env);
	free(tmpo);
}

void	ft_add_pwd(char *pwd, t_env *env)
{
	char	*tmpo;

	tmpo = ft_strjoin("PWD=", pwd);
	ft_add_export(tmpo, &env);
	free(tmpo);
}
