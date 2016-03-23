#ifndef GRIMLY_GEN_H_
# define GRIMLY_GEN_H_

# include "coord.h"

/* DEBUG ONLY */
# include <stdio.h>

# define CASE_TYPES_NBR	(4)

typedef enum	e_case
{
  empty,
  wall,
  begin,
  end
}		t_case;

typedef struct	s_map
{
  int		longer;
  int		larger;
  enum e_case	**cases;
}		t_map;

#endif /* GRIMLY_GEN_H_ */

