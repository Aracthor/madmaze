#ifndef MOOVES_H_
# define MOOVES_H_

# include "coord.h"

# define MOOVES_NBR	(4)

typedef enum	e_moove
{
  up,
  down,
  right,
  left
}		t_moove;

void	empl_mooves_tab(coord *mooves);

#endif /* !MOOVES_H_ */

