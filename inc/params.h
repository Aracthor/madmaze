#ifndef PARAMS_H_
# define PARAMS_H_

# include "boolean.h"
# include "grimly_gen.h"

# define DEFAULT_NAME		("a.txt")
# define DEFAULT_LONGER		(80)
# define DEFAULT_LARGER		(23)
# define DEFAULT_BEGINS		(1)
# define DEFAULT_ENDS		(1)
# define DEFAULT_CREATOR	(NULL)

# define NUMBER_PARAMS_NBR	(4)
# define CREATOR_PARAMS_NBR	(4)
# define CREATORS_NBR		(3)

# define NO_CREATOR_MSG		("Undefined creator.\n")

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

typedef	int	(*t_creator)(struct s_map *map, void *params);

typedef struct		s_params
{
  char			*name;
  int			longer;
  int			larger;
  int			begins;
  int			ends;
  bool			display;
  bool			see;

  t_creator		creator;
  t_creator_params	creator_params;
}			t_params;

int	read_params(struct s_params *params, int argc, char **argv);

#endif /* !PARAMS_H_ */

