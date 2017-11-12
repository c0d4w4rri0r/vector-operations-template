//
//  example.cpp
//  
//
//  Created by peter clark on 2017/11/12.
//
//

// needs -std=c++14 should have -O1 or better to optomise results of inlines

#include "VecOp.h"

constexpr int foo (int a)
{
    zeroVectorOps::blockAxis myAxis = {.width=3,.step=2};
    zeroVectorOps::blockOffset myOffset = {.fromStart=0, .fromEnd=0};
    zeroVectorOps::blockAxis myAxisArray[] = {myAxis};
    zeroVectorOps::blockOffset myOffsetArray[] = {myOffset};
    return zeroVectorOps::indexTemplate(myAxisArray,myOffsetArray,a,1);
}

int templatedot(int *a, int *b)
{
    return twoVecOps<2,foo,foo,int>::dotProd(a,b);
}

int hardcodedot(int *a, int *b)
{
    return a[0]*b[0]+a[2]*b[2]+a[4]*b[4];
}

int main()
{
    int a[]={1,2,3,4,5};
    int b[]={1,2,3,4,5};
    return templatedot(a, b)*hardcodedot(a, b);
}
