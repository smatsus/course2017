#ifndef DEFINITION_H
#define DEFINITION_H
#include <stdio.h>
#include <stdlib.h>

#define mymalloc(p,n) {p = malloc((n)*sizeof(*p));if ((p)==NULL) {printf("not enough memory\n"); exit(EXIT_FAILURE);};}

/* type definition */

typedef struct slobj_ {
  struct slobj_ *next;
  int j;
  double v;
} slobj; /* singly linked list object*/
typedef struct {
  slobj *head;
} slist; /* singly linked list*/
typedef struct {
  int n,d;
  slist **v;
} smatrix; /* sparse matrix*/
void smatrix_print(const smatrix *X);
  /* print for debug */ 
smatrix *smatrix_new(const int n, const int d);
  /* create zero matrix */
smatrix *smatrix_read(const char* filename);
  /* Assuming input format of sparse matrix file to be*/
  /* n d            */
  /* j v j v .. -1  */
  /* j v j v .. -1  */
  /* ...            */
  /* where j ranges from 1..d */ 

typedef struct {
  int d;
  double *v;
} dvector; /* dense vector*/

void dvector_print(const dvector *y);
  /* print for debug */ 
dvector *dvector_new(const int d);
  /* create zero vector */
dvector *dvector_read(const char *filename);
  /* Assuming input format of dense vector file to be*/
  /* d  */
  /* v  */
  /* v  */
  /* ...*/


/* computation */

double product(const smatrix *X,const int i,const dvector *w);
/* return <w, xi> */
void add(dvector *a, const double b, const dvector *c);
/* a <- a + b * c */
void addX(dvector *a, const double b, const smatrix *X, const int i);
/* a <- a + b * xi */

double evaluate_rr(const smatrix *X, const dvector *y, const dvector *w, const double lambda);
/* ridge regression */

#endif

