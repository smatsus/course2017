#include "definition.h"

void smatrix_print(const smatrix *X){
  slobj *tail;
  int i;
  printf("n and d: %d, %d\n", X->n, X->d);
  for(i=0;i<X->n;++i){
    printf("%d ",i);        
    for(tail=X->v[i]->head; tail!=NULL; tail=tail->next){
      printf("%d:%lf ", tail->j, tail->v);      
    }
    printf("\n");    
  }
}
void dvector_print(const dvector *y){
  int i;
  printf("size: %d \n", y->d);   
  for(i=0;i<y->d;++i){ 
    printf("%lf \n", y->v[i]); 
  }
}
smatrix *smatrix_new(const int n, const int d){
  int i;
  slist *L;
  smatrix *X;
  mymalloc(X,1);
  X->n=n;X->d=d;
  mymalloc(X->v, X->n);  
  for(i=0; i<X->n; ++i){
    mymalloc(L,1);
    X->v[i] = L;
    X->v[i]->head = NULL;
  }
  return X;
}
dvector *dvector_new(const int d){
  int i;
  dvector *y;
  mymalloc(y,1);
  y->d=d;
  mymalloc(y->v, y->d);
  for(i=0;i<y->d;++i)
    y->v[i]=0.0;
  return y;  
}
smatrix *smatrix_read(const char* filename){
  /* Assuming input format of sparse matrix file to be*/
  /* n d            */
  /* j v j v .. -1  */
  /* j v j v .. -1  */
  /* ...            */
  /* where j ranges from 1..d */ 
  
  smatrix *X;
  FILE *fp;
  int i,j,n,d;
  slobj *tail,*p;
  double xij;

  if ((fp = fopen(filename, "r")) == NULL) {
    printf("error: can't read file \"%s\"\n", filename);
    exit(EXIT_FAILURE);
  }
  
  fscanf(fp, "%d %d", &n, &d);
  X=smatrix_new(n,d);
  
  for(i=0;i<X->n;++i){    
    fscanf(fp, "%d", &j);
    while(j != -1){
      if(j > X->d){
        printf("error : some index is larger than d. d:%d, j:%d\n", X->d, j);
        exit(EXIT_FAILURE);
      }else{
        fscanf(fp, "%lf", &xij);
        mymalloc(p,1);p->j=j;p->v=xij;p->next=NULL;

        if(X->v[i]->head == NULL){
          X->v[i]->head=p;
          tail=p;
        }else{        
          tail->next=p;
          tail=p;
        }

        fscanf(fp, "%d", &j);        
      }
    }
  }
  return X;
}
dvector *dvector_read(const char *filename){
  /* Assuming input format of dense vector file to be*/
  /* d  */
  /* v  */
  /* v  */
  /* ...*/

  dvector *y;
  FILE *fp;
  int i,d;

  if ((fp = fopen(filename, "r")) == NULL) {
    printf("error: can't read file \"%s\"\n", filename);
    exit(EXIT_FAILURE);
  }

  fscanf(fp, "%d", &d);
  y=dvector_new(d);
  for(i=0; i<y->d; ++i){
    fscanf(fp, "%lf", &y->v[i]);
  }

  fgetc(fp);
  while(fgetc(fp) != EOF) {
    printf("error: vector file contains more lines than specified\n"); 
  }
  return y;
}
double product(const smatrix *X,const int i,const dvector *w){
/* return <w, xi> */
  slobj *p;
  double ret;  
  
  ret = 0.0;
  for(p = X->v[i]->head; p != NULL; p=p->next){
    if(p->j > w->d){
      printf("error in product: X[%d][%d] = %lf, size of w is %d\n", i, p->j, p->v, w->d);
//      printf("size of X, %d by %d \n", X->n, X->d);
      exit(EXIT_FAILURE);
    }

    ret += p->v * w->v[p->j-1];
  }
  return ret;
}

void add(dvector *a, const double b, const dvector *c){
/* a <- a + b * c */
  int i;
  double *a_;
  const double *c_;
  a_=a->v;c_=c->v;
  if(a->d != c->d){
    printf("error: dvector size is different");
    exit(EXIT_FAILURE);
  }
  for(i=0;i<a->d;++i){
    a_[i] += b*c_[i];    
  }

}

void addX(dvector *a, const double b, const smatrix *X, const int i){
/* a <- a + b * xi */
  slobj *p;
  double *a_;  
  a_ = a->v;
  for(p = X->v[i]->head; p != NULL; p = p->next){
    if(p->j > a->d){
      printf("error\n");
      exit(EXIT_FAILURE);
    }
    a_[p->j-1] += b * p->v ;
  }
}
  
double evaluate_rr(const smatrix *X, const dvector *y, const dvector *w, const double lambda){
  int i,j;
  double wTxi, yi, term1, wj, term2;

  term1=0.0;
  for(i=0;i<X->n;++i){
    wTxi = product(X,i,w);
    yi = y->v[i];
    term1 += (wTxi - yi) * (wTxi - yi);
  }

  term2=0.0;
  for(j=0;j<w->d;++j){
    wj = w->v[j]; 
    term2 += wj * wj;
  }

  return term1+0.5*lambda*term2;
}
