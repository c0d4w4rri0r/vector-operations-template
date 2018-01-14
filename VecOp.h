//
//  VecOp.h
//  
//
//  Created by peter clark on 2017/11/12.
//
//

// needs -std=c++14 should have -O1 or better to optomise results of inlines

class zeroVectorOps {
public:
    struct blockAxis {
        int width;
        int step;
    };
    struct blockOffset {
        int fromStart;
        int fromEnd;
    };
    static constexpr int indexTemplate(blockAxis axis[], blockOffset offset[], int x, int length)
    {
        int i=0,j=x,k=0,y=0;
        for (y=0;y<length;y++)
        {
            i=j%(axis[y].width-offset[y].fromStart-offset[y].fromEnd);
            k+=(i+offset[y].fromStart)*axis[y].step;
            j=(j-i)/(axis[y].width-offset[y].fromStart-offset[y].fromEnd);
        }
        return k;
    }
};

template<unsigned int n, int (*F)(int), typename T>
class oneVecOps {
public:
    static __attribute__((always_inline)) T sum(T a[])
    {
        constexpr int ia=F(n);
        return a[ia]+oneVecOps<n-1,F,T>::sum(a);
    }
    static __attribute__((always_inline)) T sum(T a[], int off)
    {
        constexpr int ia=F(n);
        return a[ia+off]+oneVecOps<n-1,F,T>::sum(a,off);
    }
    static __attribute__((always_inline)) void CumSum(T a[], T b)
    {
        constexpr int ia=F(n);
        a[ia]+=b;
        oneVecOps<n-1,F,T>::CumSum(a,a[ia]);
    }
    static __attribute__((always_inline)) void CumSum(T a[], T b, int off)
    {
        constexpr int ia=F(n);
        a[ia+off]+=b;
        oneVecOps<n-1,F,T>::CumSum(a,a[ia],off);
    }
    static __attribute__((always_inline)) T prod(T a[])
    {
        constexpr int ia=F(n);
        return a[ia]*oneVecOps<n-1,F,T>::prod(a);
    }
    static __attribute__((always_inline)) T prod(T a[], int off)
    {
        constexpr int ia=F(n);
        return a[ia+off]*oneVecOps<n-1,F,T>::prod(a,off);
    }
    static __attribute__((always_inline)) void CumProd(T a[], T b)
    {
        constexpr int ia=F(n);
        a[ia]*=b;
        oneVecOps<n-1,F,T>::CumProd(a,a[ia]);
    }
    static __attribute__((always_inline)) void CumProd(T a[], T b, int off)
    {
        constexpr int ia=F(n);
        a[ia+off]*=b;
        oneVecOps<n-1,F,T>::CumProd(a,a[ia],off);
    }
    static __attribute__((always_inline)) T shiftForward(T a[],T b)
    {
        constexpr int ia=F(n);
        T temp=a[ia];
        a[ia]=b;
        return oneVecOps<n-1,F,T>::shiftForward(a,temp);
    }
    static __attribute__((always_inline)) T shiftForward(T a[],T b, int off)
    {
        constexpr int ia=F(n);
        T temp=a[ia+off];
        a[ia+off]=b;
        return oneVecOps<n-1,F,T>::shiftForward(a,temp,off);
    }
    static __attribute__((always_inline)) T shiftBack(T a[],T b)
    {
        constexpr int ia=F(n);
        T temp=a[ia];
        a[ia]=oneVecOps<n-1,F,T>::shiftBack(a,b);
        return temp;
    }
    static __attribute__((always_inline)) T shiftBack(T a[],T b, int off)
    {
        constexpr int ia=F(n);
        T temp=a[ia+off];
        a[ia+off]=oneVecOps<n-1,F,T>::shiftBack(a,b,off);
        return temp;
    }
    static __attribute__((always_inline)) void scaleAss(T a[], T b)
    {
        constexpr int ia=F(n);
        a[ia]*=b;
        oneVecOps<n-1,F,T>::scaleAss(a,b);
    }
    static __attribute__((always_inline)) void scaleAss(T a[], T b, int off)
    {
        constexpr int ia=F(n);
        a[ia+off]*=b;
        oneVecOps<n-1,F,T>::scaleAss(a,b,off);
    }
    static __attribute__((always_inline)) void sumAss(T a[], T b)
    {
        constexpr int ia=F(n);
        a[ia]+=b;
        oneVecOps<n-1,F,T>::sumAss(a,b);
    }
    static __attribute__((always_inline)) void sumAss(T a[], T b, int off)
    {
        constexpr int ia=F(n);
        a[ia+off]+=b;
        oneVecOps<n-1,F,T>::sumAss(a,b,off);
    }
};

template<int (*F)(int), typename T>
class oneVecOps<0,F,T> {
public:
    static __attribute__((always_inline)) T sum(T a[])
    {
        constexpr int ia=F(0);
        return a[ia];
    }
    static __attribute__((always_inline)) T sum(T a[], int off)
    {
        constexpr int ia=F(0);
        return a[ia+off];
    }
    static __attribute__((always_inline)) void CumSum(T a[], T b)
    {
        constexpr int ia=F(0);
        a[ia]+=b;
    }
    static __attribute__((always_inline)) void CumSum(T a[], T b, int off)
    {
        constexpr int ia=F(0);
        a[ia+off]+=b;
    }
    static __attribute__((always_inline)) T prod(T a[])
    {
        constexpr int ia=F(0);
        return a[ia];
    }
    static __attribute__((always_inline)) T prod(T a[], int off)
    {
        constexpr int ia=F(0);
        return a[ia+off];
    }
    static __attribute__((always_inline)) void CumProd(T a[], T b)
    {
        constexpr int ia=F(0);
        a[ia]*=b;
    }
    static __attribute__((always_inline)) void CumProd(T a[], T b, int off)
    {
        constexpr int ia=F(0);
        a[ia+off]*=b;
    }
    static __attribute__((always_inline)) T shiftForward(T a[],T b)
    {
        constexpr int ia=F(0);
        T temp=a[ia];
        a[ia]=b;
        return temp;
    }
    static __attribute__((always_inline)) T shiftForward(T a[],T b, int off)
    {
        constexpr int ia=F(0);
        T temp=a[ia+off];
        a[ia+off]=b;
        return temp;
    }
    static __attribute__((always_inline)) T shiftBack(T a[],T b)
    {
        constexpr int ia=F(0);
        T temp=a[ia];
        a[ia]=b;
        return temp;
    }
    static __attribute__((always_inline)) T shiftBack(T a[],T b,int off)
    {
        constexpr int ia=F(0);
        T temp=a[ia+off];
        a[ia+off]=b;
        return temp;
    }
    static __attribute__((always_inline)) void scaleAss(T a[], T b)
    {
        constexpr int ia=F(0);
        a[ia]*=b;
    }
    static __attribute__((always_inline)) void scaleAss(T a[], T b, int off)
    {
        constexpr int ia=F(0);
        a[ia+off]*=b;
    }
    static __attribute__((always_inline)) void sumAss(T a[], T b)
    {
        constexpr int ia=F(0);
        a[ia]+=b;
    }
    static __attribute__((always_inline)) void sumAss(T a[], T b, int off)
    {
        constexpr int ia=F(0);
        a[ia+off]+=b;
    }
};

template<unsigned int n, int (*F)(int), int (*G)(int), typename T>
class twoVecOps {
public:
    static __attribute__((always_inline)) void move(T a[], T b[])
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        b[ib]=a[ia];
        twoVecOps<n-1,F,G,T>::move(a,b);
    }
    static __attribute__((always_inline)) void move(T a[], T b[], int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        b[ib+off]=a[ia+off];
        twoVecOps<n-1,F,G,T>::move(a,b,off);
    }
    static __attribute__((always_inline)) void scaleAss(T a[], T b[], T c)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        b[ib]=c*a[ia];
        twoVecOps<n-1,F,G,T>::scaleAss(a,b,c);
    }
    static __attribute__((always_inline)) void scaleAss(T a[], T b[], T c, int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        b[ib+off]=c*a[ia+off];
        twoVecOps<n-1,F,G,T>::scaleAss(a,b,c,off);
    }
    static __attribute__((always_inline)) void sumAss(T a[], T b[])
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        b[ib]+=a[ia];
        twoVecOps<n-1,F,G,T>::sumAss(a,b);
    }
    static __attribute__((always_inline)) void sumAss(T a[], T b[],int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        b[ib+off]+=a[ia+off];
        twoVecOps<n-1,F,G,T>::sumAss(a,b,off);
    }
    static __attribute__((always_inline)) void scaleSumAss(T a[], T b[], T c)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        b[ib]+=c*a[ia];
        twoVecOps<n-1,F,G,T>::scaleSumAss(a,b,c);
    }
    static __attribute__((always_inline)) void scaleSumAss(T a[], T b[], T c, int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        b[ib+off]+=c*a[ia+off];
        twoVecOps<n-1,F,G,T>::scaleSumAss(a,b,c,off);
    }
    static __attribute__((always_inline)) T dotProd(T a[], T b[])
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        return b[ib]*a[ia]+twoVecOps<n-1,F,G,T>::dotProd(a,b);
    }
    static __attribute__((always_inline)) T dotProd(T a[], T b[], int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        return b[ib+off]*a[ia+off]+twoVecOps<n-1,F,G,T>::dotProd(a,b,off);
    }
    static __attribute__((always_inline)) void subAss(T a[], T b[])
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        b[ib]-=a[ia];
        twoVecOps<n-1,F,G,T>::subAss(a,b);
    }
    static __attribute__((always_inline)) void subAss(T a[], T b[], int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        b[ib+off]-=a[ia+off];
        twoVecOps<n-1,F,G,T>::subAss(a,b,off);
    }
    static __attribute__((always_inline)) void prodAss(T a[], T b[])
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        a[ia]*=b[ib];
        twoVecOps<n-1,F,G,T>::prodAss(a,b);
    }
    static __attribute__((always_inline)) void prodAss(T a[], T b[], int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        a[ia+off]*=b[ib+off];
        twoVecOps<n-1,F,G,T>::prodAss(a,b,off);
    }
    static __attribute__((always_inline)) void divAss(T a[], T b[])
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        a[ia]/=b[ib];
        twoVecOps<n-1,F,G,T>::divAss(a,b);
    }
    static __attribute__((always_inline)) void divAss(T a[], T b[], int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        a[ia+off]/=b[ib+off];
        twoVecOps<n-1,F,G,T>::divAss(a,b,off);
    }
};

template<int (*F)(int), int (*G)(int), typename T>
class twoVecOps<0,F,G,T> {
public:
    static __attribute__((always_inline)) void move(T a[], T b[])
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        b[ib]=a[ia];
    }
    static __attribute__((always_inline)) void move(T a[], T b[], int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        b[ib+off]=a[ia+off];
    }
    static __attribute__((always_inline)) void scaleAss(T a[], T b[], T c)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        b[ib]=c*a[ia];
    }
    static __attribute__((always_inline)) void scaleAss(T a[], T b[], T c, int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        b[ib+off]=c*a[ia+off];
    }
    static __attribute__((always_inline)) void sumAss(T a[], T b[])
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        b[ib]+=a[ia];
    }
    static __attribute__((always_inline)) void sumAss(T a[], T b[], int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        b[ib+off]+=a[ia+off];
    }
    static __attribute__((always_inline)) void scaleSumAss(T a[], T b[], T c)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        b[ib]+=c*a[ia];
    }
    static __attribute__((always_inline)) void scaleSumAss(T a[], T b[], T c, int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        b[ib+off]+=c*a[ia+off];
    }
    static __attribute__((always_inline)) T dotProd(T a[], T b[])
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        return b[ib]*a[ia];
    }
    static __attribute__((always_inline)) T dotProd(T a[], T b[], int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        return b[ib+off]*a[ia+off];
    }
    static __attribute__((always_inline)) void subAss(T a[], T b[])
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        b[ib]-=a[ia];
    }
    static __attribute__((always_inline)) void subAss(T a[], T b[], int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        b[ib+off]-=a[ia+off];
    }
    static __attribute__((always_inline)) void prodAss(T a[], T b[])
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        a[ia]*=b[ib];
    }
    static __attribute__((always_inline)) void prodAss(T a[], T b[], int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        a[ia+off]*=b[ib+off];
    }
    static __attribute__((always_inline)) void divAss(T a[], T b[])
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        a[ia]/=b[ib];
    }
    static __attribute__((always_inline)) void divAss(T a[], T b[], int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        a[ia+off]/=b[ib+off];
    }
};

template<unsigned int n, int (*F)(int), int (*G)(int), int (*H)(int), typename T>
class threeVecOps {
public:
    static __attribute__((always_inline)) void sumAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic]=a[ia]+b[ib];
        threeVecOps<n-1,F,G,H,T>::sumAss(a,b,c);
    }
    static __attribute__((always_inline)) void sumAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic+off]=a[ia+off]+b[ib+off];
        threeVecOps<n-1,F,G,H,T>::sumAss(a,b,c,off);
    }
    static __attribute__((always_inline)) void prodAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic]=a[ia]*b[ib];
        threeVecOps<n-1,F,G,H,T>::prodAss(a,b,c);
    }
    static __attribute__((always_inline)) void prodAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic+off]=a[ia+off]*b[ib+off];
        threeVecOps<n-1,F,G,H,T>::prodAss(a,b,c,off);
    }
    static __attribute__((always_inline)) void subAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic]=a[ia]-b[ib];
        threeVecOps<n-1,F,G,H,T>::subAss(a,b,c);
    }
    static __attribute__((always_inline)) void subAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic+off]=a[ia+off]-b[ib+off];
        threeVecOps<n-1,F,G,H,T>::subAss(a,b,c,off);
    }
    static __attribute__((always_inline)) void divAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic]=a[ia]/b[ib];
        threeVecOps<n-1,F,G,H,T>::divAss(a,b,c);
    }
    static __attribute__((always_inline)) void divAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic+off]=a[ia+off]/b[ib+off];
        threeVecOps<n-1,F,G,H,T>::divAss(a,b,c,off);
    }
    static __attribute__((always_inline)) void prodSumAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic]+=a[ia]*b[ib];
        threeVecOps<n-1,F,G,H,T>::prodSumAss(a,b,c);
    }
    static __attribute__((always_inline)) void prodSumAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic+off]+=a[ia+off]*b[ib+off];
        threeVecOps<n-1,F,G,H,T>::prodSumAss(a,b,c,off);
    }
    static __attribute__((always_inline)) void prodSubAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic]-=a[ia]*b[ib];
        threeVecOps<n-1,F,G,H,T>::prodSubAss(a,b,c);
    }
    static __attribute__((always_inline)) void prodSubAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic+off]-=a[ia+off]*b[ib+off];
        threeVecOps<n-1,F,G,H,T>::prodSubAss(a,b,c,off);
    }
    static __attribute__((always_inline)) void divSumAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic]+=a[ia]/b[ib];
        threeVecOps<n-1,F,G,H,T>::divSumAss(a,b,c);
    }
    static __attribute__((always_inline)) void divSumAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic+off]+=a[ia+off]/b[ib+off];
        threeVecOps<n-1,F,G,H,T>::divSumAss(a,b,c,off);
    }
    static __attribute__((always_inline)) void divSubAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic]-=a[ia]/b[ib];
        threeVecOps<n-1,F,G,H,T>::divSubAss(a,b,c);
    }
    static __attribute__((always_inline)) void divSubAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(n);
        constexpr int ib=G(n);
        constexpr int ic=H(n);
        c[ic+off]-=a[ia+off]/b[ib+off];
        threeVecOps<n-1,F,G,H,T>::divSubAss(a,b,c,off);
    }
};

template<int (*F)(int), int (*G)(int), int (*H)(int), typename T>
class threeVecOps<0,F,G,H,T> {
public:
    static __attribute__((always_inline)) void sumAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic]=a[ia]+b[ib];
    }
    static __attribute__((always_inline)) void sumAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic+off]=a[ia+off]+b[ib+off];
    }
    static __attribute__((always_inline)) void prodAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic]=a[ia]*b[ib];
    }
    static __attribute__((always_inline)) void prodAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic+off]=a[ia+off]*b[ib+off];
    }
    static __attribute__((always_inline)) void subAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic]=a[ia]-b[ib];
    }
    static __attribute__((always_inline)) void subAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic+off]=a[ia+off]-b[ib+off];
    }
    static __attribute__((always_inline)) void divAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic]=a[ia]/b[ib];
    }
    static __attribute__((always_inline)) void divAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic+off]=a[ia+off]/b[ib+off];
    }
    static __attribute__((always_inline)) void prodSumAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic]+=a[ia]*b[ib];
    }
    static __attribute__((always_inline)) void prodSumAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic+off]+=a[ia+off]*b[ib+off];
    }
    static __attribute__((always_inline)) void prodSubAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic]-=a[ia]*b[ib];
    }
    static __attribute__((always_inline)) void prodSubAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic+off]-=a[ia+off]*b[ib+off];
    }
    static __attribute__((always_inline)) void divSumAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic]+=a[ia]/b[ib];
    }
    static __attribute__((always_inline)) void divSumAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic+off]+=a[ia+off]/b[ib+off];
    }
    static __attribute__((always_inline)) void divSubAss(T a[], T b[], T c[])
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic]-=a[ia]/b[ib];
    }
    static __attribute__((always_inline)) void divSubAss(T a[], T b[], T c[], int off)
    {
        constexpr int ia=F(0);
        constexpr int ib=G(0);
        constexpr int ic=H(0);
        c[ic+off]-=a[ia+off]/b[ib+off];
    }
};
