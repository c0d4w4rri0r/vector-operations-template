# vector-operations-template
my first attempt at using template meta programming to make inline vector operation code for high performance computing.

So for example say you have an float x[a,b,c] and you want to compute z[3,4,2 to b+1]=x[0,1 to b,c-1]*y[0 to b-1]. well in fortran it wouldn't be that hard. But in C you use for loops, but will they be unrolled? Compilers don't always unroll the code you care about. Small loops that get run a lot particularly should be compleatly unrolled for high performance computing. So I've writen a template to do what loop unrolling should do. It also makes these sorts of operations much more readable.
