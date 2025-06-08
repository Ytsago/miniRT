#include "miniRT.h"
#define MULTIPLE_DECLARATION_ERR3 "light multiple declarations\n"

bool	parse_light(char *line, t_context *scene)

{
	t_light	*parameters;

	if (scene->element_has_been_declared[LIGHT])
		return (print_error_then_return_false(MULTIPLE_DECLARATION_ERR3));
	parameters = &scene->light;
	(void)parameters;
	(void)line;
	return (true);
}
