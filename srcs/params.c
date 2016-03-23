#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "create_laby_map.h"
#include "create_star_map.h"
#include "create_islands_map.h"
#include "params.h"

static int	get_creator_param(struct s_params *params,
				  char *arg, char *ptr)
{
    int	i;
    int	return_value = 1;
    int	*ptrs[CREATOR_PARAMS_NBR];
    char	*args[CREATOR_PARAMS_NBR];

    ptrs[0] = &params->creator_params.stars_percentage;
    ptrs[1] = &params->creator_params.empty_number;
    ptrs[2] = &params->creator_params.islands.number;
    ptrs[3] = &params->creator_params.islands.size;
    args[0] = "stars_percentage";
    args[1] = "empty_number";
    args[2] = "islands_number";
    args[3] = "islands_size";

    for (i = 0; i < CREATOR_PARAMS_NBR; ++i)
	if (!strcmp(arg, args[i]))
	{
	    *ptrs[i] = atoi(ptr);
	    return_value = 0;
	}

    return (return_value);
}

static int	get_number_param(struct s_params *params, char *arg)
{
    int		i;
    int		return_value = 1;
    int		*ptrs[NUMBER_PARAMS_NBR];
    char		*args[NUMBER_PARAMS_NBR];
    char		*arg_copy;
    char		*ptr;

    ptrs[0] = &params->longer;
    ptrs[1] = &params->larger;
    ptrs[2] = &params->begins;
    ptrs[3] = &params->ends;
    args[0] = "longer";
    args[1] = "larger";
    args[2] = "begins";
    args[3] = "ends";

    arg_copy = strdup(arg);
    ptr = strchr(arg_copy, '=');
    *ptr = '\0';

    for (i = 0; i < NUMBER_PARAMS_NBR; ++i)
	if (!strcmp(args[i], arg_copy))
	{
	    *ptrs[i] = atoi(ptr + 1);
	    return_value = 0;
	}

    if (return_value != 0)
	return_value = get_creator_param(params, arg_copy, ptr + 1);

    free(arg_copy);
    return (return_value);
}

static int	get_creator(struct s_params *params, char *arg)
{
    t_creator	creators[CREATORS_NBR];
    char		*args[CREATORS_NBR];
    int		i;
    int		return_value = 1;

    creators[0] = &create_star_map;
    creators[1] = &create_laby_map;
    creators[2] = &create_islands_map;
    args[0] = "--star";
    args[1] = "--laby";
    args[2] = "--islands";

    for (i = 0; i < CREATORS_NBR; ++i)
	if (!strcmp(args[i], arg))
	{
	    return_value = 0;
	    params->creator = creators[i];
	}

    return (return_value);
}

static int	read_param(struct s_params *params, char *arg)
{
    int		return_value = 0;

    if (!strcmp(arg, "--display"))
	params->display = true;
    else if (!strcmp(arg, "--see"))
	params->see = true;
    else if (strchr(arg, '=') != NULL)
	return_value = get_number_param(params, arg);
    else if (arg[0] == '-' && arg[1] == '-')
	return_value = get_creator(params, arg);
    else
	params->name = arg;

    if (return_value != 0)
	fprintf(stderr, "Arg %s suck.\n", arg);

    return (return_value);
}

int	read_params(struct s_params *params, int argc, char **argv)
{
    int	i;
    int	return_value = 0;

    params->name = DEFAULT_NAME;
    params->longer = DEFAULT_LONGER;
    params->larger = DEFAULT_LARGER;
    params->begins = DEFAULT_BEGINS;
    params->ends = DEFAULT_ENDS;
    params->display = false;
    params->see = false;
    params->creator = DEFAULT_CREATOR;
    memset(&params->creator_params, 0, sizeof(params->creator_params));
    for (i = 1; return_value == 0 && i < argc; ++i)
	return_value = read_param(params, argv[i]);

    if (return_value == 0 && params->creator == NULL)
    {
	write(2, NO_CREATOR_MSG, strlen(NO_CREATOR_MSG));
	return_value = 1;
    }

    return (return_value);
}


