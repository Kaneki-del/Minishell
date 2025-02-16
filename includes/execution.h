#ifndef EXECUTION_H
#define EXECUTION_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_gc {
  void *adress;
  struct s_gc *next;
} t_gc;
#endif
