/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:37:22 by timurray          #+#    #+#             */
/*   Updated: 2025/08/19 18:00:36 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int return_file_error(void)
{
	ft_printfd(2, "File not found.\n");
	return (EXIT_FAILURE);
}

int return_args_error(void)
{
	ft_printfd(2, "Enter single valid .fdf map argument.\n");
	return (EXIT_FAILURE);
}
