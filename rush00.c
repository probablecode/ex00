/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchoi <jchoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 20:21:29 by jchoi             #+#    #+#             */
/*   Updated: 2021/09/12 20:34:39 by jchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	rush(int x, int y)
{
	char	*symbols;
	int		index;
	int		i;
	int		j;

	symbols = "o-o| |o-o";
	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			index = (0 < i) * ((i == y - 1) + 1) * 3;
			index += (0 < j) * ((j == x - 1) + 1);
			ft_putchar(*(symbols + index));
			j++;
		}
		if (0 < x)
			ft_putchar ('\n');
		i++;
	}
}
