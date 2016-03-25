#include "mooves.h"

void	empl_mooves_tab(coord *mooves)
{
  mooves[up] = coordonne(0, -1);
  mooves[down] = coordonne(0, 1);
  mooves[right] = coordonne(1, 0);
  mooves[left] = coordonne(-1, 0);
}

