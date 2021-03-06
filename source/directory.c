/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 02:04:30 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/07 06:05:36 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

extern t_argp	g_argp[];
extern char		g_info[255];
extern int		g_total;

int8_t	open_directory(DIR **dir, char *directory)
{
	char	*name;

	name = ft_strrchr(directory, '/');
	if ((*dir = opendir(directory)) == NULL)
	{
		if (name != NULL)
			ft_dprintf(2, "ls: %s: %s\n", &ft_strrchr(directory, '/')[1],
					strerror(errno));
		else
			ft_dprintf(2, "ls: %s: %s\n", directory, strerror(errno));
		return (EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}

void	close_directory(DIR **dir)
{
	if (closedir(*dir) == -1)
	{
		ft_dprintf(2, RED"%s\n"END, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	minus_t_1(t_ctrl *ctrl, char **tab)
{
	t_file	*tmp;
	int		i;

	i = 0;
	tmp = ctrl->first;
	if (tmp != NULL)
	{
		while (tmp)
		{
			tab[i] = tmp->name;
			tmp = tmp->next;
			++i;
		}
		sort_param(tab);
	}
}

void	particular_minus_t(t_ctrl *ctrl, char *directory, t_env *env)
{
	struct stat		file_stat;
	int				i;
	char			**tab;
	t_ctrl			ctr;
	char			*file;

	ft_memset(&ctr, 0, sizeof(t_ctrl));
	i = count_nb_node(ctrl);
	tab = (char **)ft_memalloc(sizeof(char *) * i + 1);
	ft_set_2d_tab(tab, i + 1);
	i = -1;
	minus_t_1(ctrl, tab);
	while (tab[++i])
	{
		file = join(directory, tab[i]);
		if (lstat(file, &file_stat) < 0 && print_error(file) == true)
			continue ;
		minus_t_2(file, env);
		sort_by_time(&ctr, file_stat.st_mtimespec.tv_sec, file);
		ft_strdel(&file);
	}
	free(tab);
	if (g_argp[MINUS_L].active == 1)
		padding_l(&ctr);
	print_lst(&ctr);
}

void	insert_string(t_ctrl *ctrl, char *directory)
{
	int		i;
	int		len_directory;
	int		j;

	j = 0;
	i = ft_strlen(ctrl->first->info);
	len_directory = ft_strlen(directory);
	g_total = 0;
	while (ctrl->first->info[i] != ' ')
		--i;
	ctrl->first->info[i++] = ' ';
	while (len_directory > 0)
	{
		ctrl->first->info[i] = directory[j];
		++i;
		++j;
		--len_directory;
	}
	ctrl->first->info[i++] = ' ';
	ctrl->first->info[i++] = '-';
	ctrl->first->info[i++] = '>';
	ctrl->first->info[i++] = ' ';
}
