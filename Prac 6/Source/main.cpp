#include "libMatrix2D.h"

using namespace std;

int main()
{
    Matrix2D objmatrix(10,10,{7});

objmatrix(2,6)={7};

cout<<"Original Object"<<endl;
cout<<objmatrix<<endl;

Matrix2D objClone=objmatrix;
cout<<"cloned Object"<<endl;
cout<<objClone;

cout<<endl;
cout<<"incrementing"<<endl;
++objmatrix;

cout<<++objmatrix;
cout<<endl;
    return 0;
}
