/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:11:00 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/22 18:02:19 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isnbr(char *number)
{
	if (!number)
		return (0);
	if (*number == '+' || *number == '-')
		number++;
	if ((*number < '0') || (*number > '9'))
		return (0);
	while (*number >= '0' && *number <= '9')
		number++;
	return ((*number == 0));
}
