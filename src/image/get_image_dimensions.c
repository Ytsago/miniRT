/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image_dimensions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:28:01 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/18 19:31:10 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define WIDTH 1920
# define RATIO 1.778
# define W 0
# define H 1

void	get_image_dimensions(short img_dimensions[2])

{
	img_dimensions[W] = WIDTH;
	img_dimensions[H] = WIDTH / RATIO;
}
