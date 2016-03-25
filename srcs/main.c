#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "grimly_gen.h"
#include "map.h"
#include "params.h"

int			main(int argc, char **argv)
{
    struct s_params	params;
    int			return_value;

    srandom(getpid() * time(NULL));
    return_value = read_params(&params, argc, argv);
    if (return_value == 0)
    {
	return_value = create_map(&params);
    }

    return (return_value);
}

