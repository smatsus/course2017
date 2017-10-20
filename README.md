## 数理情報工学演習第二B:松島担当分

### Compile:
```
cd code
gcc -O3 main.c definition.c gradient_descent.c stochastic_gradient_descent.c -o [実行ファイル名]
```

### Usage: 

` ./[実行ファイル名] [algorithm ID] [lambda] [stepsize] [inner iteration] [max iteration] `

##### algorithm ID
 1: gradient descent
 2: stochastic gradient descent
