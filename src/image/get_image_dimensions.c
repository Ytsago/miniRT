/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image_dimensions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:28:01 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/20 10:40:54 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 1920
#define RATIO 1.778
#define W 0
#define H 1

void	get_image_dimensions(short img_dimensions[2])

{
	img_dimensions[W] = WIDTH;
	img_dimensions[H] = WIDTH / RATIO;
}
