#ifndef GRIMLY_GEN_H_
# define GRIMLY_GEN_H_

# include "coord.h"

# define CASE_TYPES_NBR	(4)

typedef enum	e_case
{
  empty,
  wall,
  begin,
  end
}		t_case;

typedef struct	s_chars
{
  char		wall;
  char		empty;
  char		begin;
  char		end;
}		t_chars;

typedef struct		s_map
{
  int			width;
  int			height;
  enum e_case**		cases;
  struct s_chars	chars;
}			t_map;

#endif /* GRIMLY_GEN_H_ */

