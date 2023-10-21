#include "v2.h"
#include<Windows.h>
using namespace std;
int main(){
Matrix<int> A(3,3);
cout<<"Matrix A:"<<endl;
A(0,0)=1;A(0,1)=3;A(0,2)=7;
A(1,0)=0;A(1,1)=2;A(1,2)=4;
A(2,0)=1;A(2,1)=2;A(2,2)=0;
cout<<A;
cout<<"Matrix B:"<<endl;
Matrix<int> B(3,3);
B(0,0)=1;B(0,1)=4;B(0,2)=2;
B(1,0)=0;B(1,1)=4;B(1,2)=2;
B(2,0)=-1;B(2,1)=6;B(2,2)=0;
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
lower_triangular_matrix(B);
cout<<B<<endl;
}
