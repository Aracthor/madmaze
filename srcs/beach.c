#include <stdlib.h>

#include "beach.h"
#include "boolean.h"
#include "map.h"
#include "mooves.h"

struct s_coord_list	*add_coord_to_list(struct s_coord_list *list,
					   coord pos)
{
  struct s_coord_list	*elem;

  elem = malloc(sizeof(struct s_coord_list));
  elem->pos = pos;
  elem->next = list;
  list = elem;

  return (list);
}

t_beach		*add_case_to_beach(struct s_map *map,
				   t_beach *beach, coord pos)
{
  t_beach	*elem;
  coord		mooves[MOOVES_NBR];
  coord		pos_to_check;
  int		i;

  empl_mooves_tab(mooves);
  MAP_CASE(map, pos) = empty;

  for (i = 0; i < MOOVES_NBR; ++i)
    {
      pos_to_check = coord_sum(pos, mooves[i]);
      if (is_surrounded(map, pos_to_check))
	beach = delete_case_from_beach(beach, pos_to_check);
    }

  if (!is_surrounded(map, pos))
    {
      elem = malloc(sizeof(t_beach));
      elem->pos = pos;
      elem->next = beach;
      beach = elem;
    }

  return (beach);
}

int	beach_size(t_beach *beach)
{
  int	size;

  size = 0;
  for (; beach != NULL; beach = beach->next)
    ++size;

  return (size);
}

coord	get_random_beach(t_beach *beach)
{
  int	id;
  int	i;

  id = random() % beach_size(beach);
  for (i = 0; i < id; ++i)
    beach = beach->next;

  return (beach->pos);
}

t_beach		*delete_case_from_beach(t_beach *beach, coord pos)
{
  t_beach	*copy;
  t_beach	*elem = NULL;

  if (beach != NULL && coord_distance(beach->pos, pos) == 0)
    {
      elem = beach;
      beach = beach->next;
    }
  else if (beach != NULL)
    {
      for (copy = beach;
	   copy->next != NULL && coord_distance(copy->next->pos, pos) > 0;
	   copy = copy->next);
      if (copy->next != NULL)
	{
	  elem = copy->next;
	  copy->next = copy->next->next;
	}
    }

  if (elem)
    free(elem);
  return (beach);
}

void			destroy_coord_list(struct s_coord_list *list)
{
  struct s_coord_list	*elem;

  while (list != NULL)
    {
      elem = list;
      list = list->next;
      free(elem);
    }
}

