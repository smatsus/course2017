#include "gradient_descent.h"

void iterate_gd(const smatrix *X,
                const dvector *y,
                dvector *w,
                const double lambda,
                const double stepsize){
  int i;
  double wTxi, yi;
  dvector *grad;

  grad = dvector_new(w->d);
  for(i=0;i<X->n;++i){
    wTxi = product(X,i,w);
    yi = y->v[i];
    
    addX(grad, wTxi - yi , X, i);
/*   grad <- grad + (wTxi - yi) xi */
  }
  add(grad, lambda, w);
/* grad <- grad + lambda * w */

  add(w, -stepsize, grad);
/* w <- w + (-stepsize) * grad */
  
  return;
}

