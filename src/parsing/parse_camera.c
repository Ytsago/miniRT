#include "miniRT.h"
#define MULTIPLE_DECLARATION_ERR2 "camera multiple declarations\n"

bool	parse_camera(char *line, t_context *scene)

{
	t_camera	*parameters;

	if (scene->element_has_been_declared[LIGHT])
		return (print_error_then_return_false(MULTIPLE_DECLARATION_ERR2));
	jump_spaces(&line);
	parameters = &scene->camera;
	(void)parameters;
	return (true);
}
