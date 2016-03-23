#ifndef BEACH_H_
# define BEACH_H_

# include "grimly_gen.h"

typedef struct		s_coord_list
{
  coord			pos;
  struct s_coord_list	*next;
}			t_coord_list;

typedef t_coord_list	t_beach;

struct s_coord_list	*add_coord_to_list(struct s_coord_list *list,
					   coord pos);
t_beach			*add_case_to_beach(struct s_map *map,
					   t_beach *beach, coord pos);
int			beach_size(t_beach *beach);
coord			get_random_beach(t_beach *beach);
t_beach			*delete_case_from_beach(t_beach *beach, coord pos);
void			destroy_coord_list(struct s_coord_list *list);

#endif /* !BEACH_H_ */

