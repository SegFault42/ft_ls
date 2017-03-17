/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 15:26:57 by rabougue          #+#    #+#             */
/*   Updated: 2017/03/04 21:14:10 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

char	**sort_param(char **arguments, int argc)
{
	char	*tmp;
	int		find;
	int		i;

	find = 1;
	while (find)
	{
		find = 0;
		i = -1;
		while (++i < argc - 1)
		{
			if (ft_strcmp(arguments[i], arguments[i + 1]) > 0)
			{
				tmp = arguments[i];
				arguments[i] = arguments[i + 1];
				arguments[i + 1] = tmp;
				find = 1;
			}
		}
	}
	return (arguments);
}

char **parse_arg(char **argv, int argc)
{
	uint8_t	i;
	int		arg;
	char	**arguments;

	i = 0;
	arg = 0;
	arguments = (char **)malloc(sizeof(char *) * argc + 1);
	++argv;
	while (argv[arg])
	{
		if (argv[arg][0] == '-' && g_argp[END_OPTION].active == 0)
		{
			while (g_argp[i].sign)
			{
				if (ft_strstr(argv[arg], g_argp[i].sign) != NULL)
					g_argp[i].active = 1;
				++i;
			}
			i = 0;
		}
		arguments[arg] = ft_strdup(argv[arg]);
		++arg;
	}
	arguments[arg] = NULL;
	if (argc > 0)
		arguments = sort_param(arguments, argc);
	/*i = 0;*/
	/*while (arguments[i])*/
	/*{*/
		/*ft_dprintf(1, RED"%s\n"END, arguments[i]);*/
		/*++i;*/
	/*}*/
	return (arguments);
}
void	fill_argp(char *param, char *description, int index)
{
	g_argp[index].description = ft_strdup(description);
	g_argp[index].sign = ft_strdup(param);
	g_argp[index].active = 0;
	if (g_argp[index].sign == NULL || g_argp[index].description == NULL)
		ft_error(MALLOC_ERROR);
}

void	init_argp()
{
	ft_memset(g_argp, 0, sizeof(g_argp));
	fill_argp("a", "Print hide file", 0);
	fill_argp("1", "One file per line", 1);
	fill_argp("R", "List subdirectory recursively", 2);
	fill_argp("r", "reverse sort", 3);
	fill_argp("t", "sort by time (new first)", 4);
	fill_argp("l", "print full info", 5);
	fill_argp("--", "end getting option", 6);
}

void	free_argp()
{
	int	i;

	i = 0;
	while (g_argp[i].sign)
	{
		ft_strdel(&g_argp[i].sign);
		ft_strdel(&g_argp[i].description);
		++i;
	}
}