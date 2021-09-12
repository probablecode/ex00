/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush04.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchoi <jchoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 20:36:52 by jchoi             #+#    #+#             */
/*   Updated: 2021/09/12 20:37:57 by jchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	rush(int x, int y)
{
	char	*symbols;
	int		index;
	int		i;
	int		j;

	symbols = "ABCB BCBA";
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
