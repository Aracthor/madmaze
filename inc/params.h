#ifndef PARAMS_H_
# define PARAMS_H_

# include "boolean.h"
# include "grimly_gen.h"
# include "pargse.h"

# define DEFAULT_NAME		"a.txt"
# define DEFAULT_WIDTH		80
# define DEFAULT_HEIGHT		23
# define DEFAULT_BEGINS		1
# define DEFAULT_ENDS		1

# define DEFAULT_WALL_CHAR	'#'
# define DEFAULT_EMPTY_CHAR	' '
# define DEFAULT_BEGIN_CHAR	'1'
# define DEFAULT_END_CHAR	'2'

# define NUMBER_PARAMS_NBR	4
# define CREATOR_PARAMS_NBR	4
# define CREATORS_NBR		3

typedef struct	s_islands
{
  int		number;
  int		size;
}		t_islands;

typedef union		u_creator_params
{
  int			stars_percentage;
  int			empty_number;
  struct s_islands	islands;
}			t_creator_params;

typedef	int		(*t_creator)(struct s_map *map, void *params);

typedef struct		s_params
{
    char*	        name;
    int			width;
    int			height;
    int			begins;
    int			ends;

    struct s_chars	chars;

    pargse_bool		display;
    pargse_bool		see;

    t_creator		creator;
    t_creator_params	creator_params;
}			t_params;

int	read_params(struct s_params *params, int argc, char **argv);

#endif /* !PARAMS_H_ */

