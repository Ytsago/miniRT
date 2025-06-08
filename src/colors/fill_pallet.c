#include "miniRT.h"
#include <stdbool.h>

bool	fill_pallet(short pallet[3], const char *line)

{
	pallet[RED] = ascii_to_rgb(&line);
	if (pallet[RED] < 0 || pallet[RED] > 255 || *line != ',')
		return (false);
	++line;
	pallet[GREEN] = ascii_to_rgb(&line);
	if (pallet[GREEN] < 0 || pallet[GREEN] > 255 || *line != ',')
		return (false);
	++line;
	pallet[BLUE] = ascii_to_rgb(&line);
	if (pallet[BLUE] < 0 || pallet[BLUE] > 255)
		return (false);
	return (true);
}
