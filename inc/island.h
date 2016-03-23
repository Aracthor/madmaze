#ifndef ISLAND_H_
# define ISLAND_H_

# include "beach.h"

typedef struct		s_island
{
  int			size;
  coord			pos;
  t_beach	*beach;
}			t_island;

void	create_island(struct s_map *map, struct s_island *island,
		      coord pos, enum e_case case_type);
void	destroy_island(struct s_island *island);

#endif /* !ISLAND_H_ */

