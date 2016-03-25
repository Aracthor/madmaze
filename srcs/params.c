#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "create_laby_map.h"
#include "create_star_map.h"
#include "create_islands_map.h"
#include "params.h"

static t_creator	get_creator(char *creator_name)
{
    t_creator	creators[CREATORS_NBR];
    char*	names[CREATORS_NBR];
    int		i;

    creators[0] = &create_star_map;
    creators[1] = &create_laby_map;
    creators[2] = &create_islands_map;
    names[0] = "random";
    names[1] = "laby";
    names[2] = "islands";

    for (i = 0; i < CREATORS_NBR; i++)
    {
	if (!strcmp(names[i], creator_name))
	{
	    return creators[i];
	}
    }

    fprintf(stderr, "Unknown creator %s. Creator must be one of the following:\n", creator_name);
    for (i = 0; i < CREATORS_NBR; i++)
    {
	printf(" - %s\n", names[i]);
    }

    return NULL;
}

static void	init_default_params(struct s_params* params)
{
    params->name = DEFAULT_NAME;
    params->width = DEFAULT_WIDTH;
    params->height = DEFAULT_HEIGHT;
    params->begins = DEFAULT_BEGINS;
    params->ends = DEFAULT_ENDS;

    params->chars.wall = DEFAULT_WALL_CHAR;
    params->chars.empty = DEFAULT_EMPTY_CHAR;
    params->chars.begin = DEFAULT_BEGIN_CHAR;
    params->chars.end = DEFAULT_END_CHAR;

    memset(&params->creator_params, 0, sizeof(params->creator_params));
}

int		read_params(struct s_params *params, int argc, char **argv)
{
    pargse	pargse;
    char*	creator_name;

    init_default_params(params);

    pargse_init(&pargse, argc, argv);

    if (pargse_add_fixed_str_arg(&pargse, "creator", &creator_name) ||
	pargse_add_flagged_int_arg(&pargse, 'x', "width", pargse_true, &params->width) ||
	pargse_add_flagged_int_arg(&pargse, 'y', "height", pargse_true, &params->height) ||
	pargse_add_flagged_str_arg(&pargse, 'o', "file_name", pargse_false, &params->name) ||
	pargse_add_flagged_int_arg(&pargse, 'b', "begins number", pargse_false, &params->begins) ||
	pargse_add_flagged_int_arg(&pargse, 'e', "ends number", pargse_false, &params->ends) ||
	pargse_add_flagged_char_arg(&pargse, 'w', "wall", pargse_false, &params->chars.wall) ||
	pargse_add_flagged_char_arg(&pargse, 'p', "path", pargse_false, &params->chars.empty) ||
	pargse_add_flagged_char_arg(&pargse, 'B', "begin", pargse_false, &params->chars.begin) ||
	pargse_add_flagged_char_arg(&pargse, 'E', "end", pargse_false, &params->chars.end) ||
	pargse_add_flagged_bool_arg(&pargse, 's', "see", &params->see) ||
	pargse_add_flagged_bool_arg(&pargse, 'd', "display", &params->display) ||
	pargse_add_flagged_int_arg(&pargse, 'P', "stars_percentage", pargse_false,
				   &params->creator_params.stars_percentage) ||
	pargse_add_flagged_int_arg(&pargse, 'S', "spaces_number", pargse_false,
				   &params->creator_params.empty_number) ||
	pargse_add_flagged_int_arg(&pargse, 'N', "islands_number", pargse_false,
				   &params->creator_params.islands.number) ||
	pargse_add_flagged_int_arg(&pargse, 'I', "islands_size", pargse_false,
				   &params->creator_params.islands.size))
    {
	return 2;
    }

    if (pargse_parse(&pargse))
    {
	return 1;
    }

    params->creator = get_creator(creator_name);

    return (params->creator == NULL);
}


