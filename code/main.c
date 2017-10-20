#include "definition.h"
#include "gradient_descent.h"
#include "stochastic_gradient_descent.h"

void run(const char algorithm,
         const int inner_iteration,
         smatrix *X,
         dvector *y,
         dvector *w,
         double lambda,
         double stepsize
         ){
  int i;
  for(i=0;i<inner_iteration;++i){
    if(algorithm == '1')
      iterate_gd(X,y,w,lambda,stepsize);
    else if(algorithm == '2')
      iterate_sgd(X,y,w,lambda,stepsize);
    /* else if(algorithm == '3') */
    /*   iterate_svrg(X,y,w,lambda,stepsize); */
  }
}

int main(int argc, char **argv){
  char algorithmID;
  double lambda, stepsize;
  int inner_iteration, max_iteration;
  if(argc != 6){
    fprintf(stdout,"Error in arguments. Usage: %s [algorithm ID] [lambda] [stepsize] [inner iteration] [max iteration] \n", argv[0]);    
    fprintf(stdout, "[algorithm ID]\n");
    fprintf(stdout, "1: gradient descent\n");
    fprintf(stdout, "2: stochastic gradient descent\n");
    exit(EXIT_FAILURE);
  }
  algorithmID = argv[1][0];
  lambda  = atof(argv[2]);
  stepsize = atof(argv[3]);
  inner_iteration = atoi(argv[4]);
  max_iteration = atoi(argv[5]);
    
  if(algorithmID != '1' && algorithmID != '2'){
      fprintf(stdout, "algorithm ID is not correctly specified.\n");
      fprintf(stdout, "1: gradient descent\n");
      fprintf(stdout, "2: stochastic gradient descent\n");
      /* fprintf(stdout,"3: "); */
      exit(EXIT_FAILURE);
  }else if(algorithmID == '1'){
    fprintf(stdout, "Gradient Descent \n");
  }
  else if (algorithmID == '2'){
    fprintf(stdout, "Stochastic Gradient Descent \n");
  }

  smatrix *X;
  dvector *y,*w;
  X = smatrix_read("X_example.txt");
  y = dvector_read("y_example.txt");
  w = dvector_new(X->d);
//  smatrix_print(X);
//  dvector_print(y);
  
  double obj;
  int i;  
  fprintf(stdout,"iteration obj\n");
  for(i=0;i<max_iteration;++i){
    obj = evaluate_rr(X, y, w, lambda);
    fprintf(stdout,"%9d %12lf\n", i, obj);
    run(algorithmID, inner_iteration, X, y, w, lambda, stepsize);
  }  
  obj = evaluate_rr(X, y, w, lambda);
  fprintf(stdout,"%9d %12lf\n", i, obj);

  return 0;
}
