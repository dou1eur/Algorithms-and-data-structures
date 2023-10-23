#include "v2.h"
#include<Windows.h>
using namespace std;
int main(){
Matrix<double> A(3,3);
cout<<"Matrix A:"<<endl;
A(0,0)=1.0;A(0,1)=3.0;A(0,2)=7.0;
A(1,0)=0.0;A(1,1)=2.0;A(1,2)=4.0;
A(2,0)=1.0;A(2,1)=2.0;A(2,2)=0.0;
cout<<A;
cout<<"Matrix B:"<<endl;
Matrix<double> B(3,3);
B(0,0)=1.0;B(0,1)=2.0;B(0,2)=2.0;
B(1,0)=0.0;B(1,1)=4.0;B(1,2)=2.0;
B(2,0)=-1.0;B(2,1)=6.0;B(2,2)=0.0;
cout<<B;
cout<<"A+B"<<endl;
cout<<A+B;
cout<<"A-B"<<endl;
cout<<A-B;
cout<<"A*B"<<endl;
cout<<A*B;
int scalar1=12;
cout<<"A*scalar:"<<endl;
cout<<A*scalar1<<endl;
int scalar2=2;
cout<<"A/scalar:"<<endl;
cout<<A/scalar2<<endl;
cout<<"Let us reduce to lower triangular type matrix B:"<<endl;
cout<<LU_decomposition(B)<<endl;
}
