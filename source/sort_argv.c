/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 04:38:22 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/07 04:55:31 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static int		count_where_is_first_file_2(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		if (ft_strlen(argv[i]) == 1 && argv[i][0] == '-')
			break ;
		if (ft_strcmp(argv[i], "--") == 0)
		{
			++i;
			break ;
		}
		++i;
	}
	return (i);
}

static int		count_where_is_first_file(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] && ft_strcmp(argv[i], "--") != 0)
	{
		if (argv[i][0] != '-')
			break ;
		if (ft_strlen(argv[i]) == 1 && argv[i][0] == '-')
			break ;
		++i;
	}
	if (argv[i] != NULL && ft_strcmp(argv[i], "--") == 0)
		++i;
	return (i);
}

/*
** stock tout les fichier regulier dans env->files et tout les dossiers dans
** env->directory
*/

void			stock_reg_and_dir_2(char **argv, int cp, t_env *env)
{
	uint8_t	ret;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (argv[cp])
	{
		if ((ret = is_reg_or_dir(argv[cp])) == REG)
		{
			env->files[++i] = argv[cp];
		}
		else if (ret == DIRE)
			env->directory[++j] = argv[cp];
		++cp;
	}
}

static void		stock_reg_and_dir(t_env *env, char **argv, int argc)
{
	int		first_file;
	int		cp_first_file;
	int		nb_file;

	first_file = count_where_is_first_file(argv);
	cp_first_file = first_file;
	nb_file = argc - first_file;
	env->files = (char **)malloc(sizeof(char *) * nb_file + 1);
	env->directory = (char **)malloc(sizeof(char *) * nb_file + 1);
	if (env->files == NULL || env->directory == NULL)
		ft_critical_error(MALLOC_ERROR);
	ft_set_2d_tab(env->files, nb_file + 1);
	ft_set_2d_tab(env->directory, nb_file + 1);
	stock_reg_and_dir_2(argv, cp_first_file, env);
}

void			sort_argv(t_env *env, char **argv, int argc)
{
	int	first_file;

	first_file = count_where_is_first_file_2(argv);
	if (argc - first_file > 1)
		env->nb_args = 1;
	if ((count_where_is_first_file(argv) - argc) == 0)
	{
		stock_reg_and_dir(env, argv, argc + 1);
		env->directory[0] = ft_strdup(".");
	}
	else
		stock_reg_and_dir(env, argv, argc);
	if (env->files[0] != NULL)
		sort_param(env->files);
	if (env->directory[0] != NULL)
		sort_param(env->directory);
}
