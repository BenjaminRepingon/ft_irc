/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 10:52:05 by mgarcin           #+#    #+#             */
/*   Updated: 2014/05/23 12:02:23 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../includes/client.h"

int				chk_char_name(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isprint(line[i]) && line[i] != ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

char			*pseudo(void)
{
	int		r;
	char	*line;

	write(1, "What's your name ?: ", 20);
	while ((r = get_next_line(0, &line)) > 0)
	{
		if ((ft_strlen(line) <= NAME_LEN && ft_strlen(line) > 0)
			&& chk_char_name(line))
			return (line);
		else
			write(1, "What's your name ?: ", 20);
	}
	return (NULL);
}
