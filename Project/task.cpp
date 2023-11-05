#include "v2.h"
#include<Windows.h>
using namespace std;
int main(){
cout<<"Random Matrix"<<endl;
Matrix<int> C(2,4,1,17);
Matrix<float> F(2,3,1.54,18.22);
cout<<C<<endl<<F<<endl;
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
cout<<"tr A"<<endl;
cout<<A.tr()<<endl;
int scalar1=12;
cout<<"A*scalar:"<<endl;
cout<<A*scalar1<<endl;
int scalar2=2;
cout<<"A/scalar:"<<endl;
cout<<A/scalar2<<endl;
cout<<"Lower triangular type matrix B:"<<endl;
cout<<LU_decomposition(B)<<endl;
Matrix<complex<float>> complex1(2,2,complex<float>(1.0f,2.0f),complex<float>(2.0f,3.0f));
cout<<"Complex matrix A"<<endl<<complex1<<endl;
Matrix<complex<float>> complex2(2,2,complex<float>(2.0f,3.0f),complex<float>(0.0f,1.0f));
cout<<"Complex matrix B"<<endl<<complex2<<endl;
cout<<"complex +"<<endl<<complex1+complex2<<endl;
cout<<"complex -"<<endl<<complex1-complex2<<endl;
cout<<"complex *"<<endl<<complex1*complex2<<endl;
cout<<"complex * scalar"<<endl<<complex1*scalar2<<endl;
cout<<"Lower triangular type complex A"<<endl<<LU_decomposition(complex1)<<endl;
}

