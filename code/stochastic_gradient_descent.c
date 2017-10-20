#include "stochastic_gradient_descent.h"

void iterate_sgd(const smatrix *X,
                 const dvector *y,
                 dvector *w,
                 const double lambda,
                 const double stepsize){
  int i,s;
  double wTxi, yi;
  dvector *grad;
  grad = dvector_new(w->d);

  for(s=0;s<X->n;++s){
    i=rand()%X->n;
    wTxi = product(X,i,w);
    yi = y->v[i];
    
    addX(grad, X->n*(wTxi - yi) , X, i);
/*  grad <- grad + n(wTxi - yi) xi */
    add(grad, lambda, w);
/*  grad <- grad + lambda * w */
    add(w, -stepsize, grad);
/*  w <- w + (-stepsize) * grad */
  }
  
  return;
}
