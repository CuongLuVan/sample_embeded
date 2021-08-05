#include <stdio.h>
#include <conio.h>

int i,j,na,n;
double asa[7][7],bsb[7][7],csc[7][7];

void CongMaTran(int m, int n) {
 for(int i = 0; i<m; i++)
  for(int j = 0; j<n; j++)
   asa[i][j] = asa[i][j]+bsb[i][j];
	
	
}
// matran m*n nhan matran n*p
void NhanMaTran(int m,int n,int p){ 
 for(int i = 0; i<m; i++)
  for(int k = 0; k<p; k++) {
   csc[i][k]=0;
   for(int j = 0; j<n; j++)
   csc[i][k] = csc[i][k]+asa[i][j]*bsb[j][k];
  }
}

void matranchuyenvi(int n)
{ 
  int i,j;
   for(i=0;i<n;i++)
    for(j=0;j<n;j++)
     bsb[i][j]=asa[j][i];
  return(b);
}

void doicho(int i1,int i2)
{ int j;
  double tg;
  for(j=1;j<=na;j++)
  { tg=a[i1][j];
    a[i1][j]=a[i2][j];
    a[i2][j]=tg;
  }
}
void MatAlgebra(int t) {
/ Tinh dinh thuc cua a
	int i,j,k,sign = 1;
	double det,temp;
	det=0;
{
    for (i = 0; i < t; i++) // T?o ra b là ma tr?n don v? dó
        for (j = 0; j < t; j++)
        if (i==j) bsb[i][j] = 1; else bsb[i][j] = 0;
 
    for (i = 0; i < t; i++) // X? lý t? hàng d?u d?n hàng cu?i
        {
            if (asa[i][i] == 0) // N?u g?p ph?n t? trên du?ng chéo chính b?ng 0 thì d?i hàng
                {
                    k = i+1;
                    while (k < t && asa[k][i] == 0) k++;
                    for (j = 0; j < t; j++) // Ð?i hàng dó c?a a dó, c? v?i ma tr?n b n?a
                        {
                            temp = asa[i][j];
                            asa[i][j] = asa[k][j];
                            asa[k][j] = temp;
                            temp = bsb[i][j];
                            bsb[i][j] = bsb[k][j];
                            bsb[k][j] = temp;
                        }
                }
 
            temp = asa[i][i];
            for (j = i; j < t; j++) asa[i][j] /= temp;
            for (j = 0; j < t; j++) bsb[i][j] /= temp;
 
            for (j = i+1; j < t; j++)
                {
                    temp = -asa[j][i];
                    for (k = i; k < t; k++) asa[j][k] += temp*asa[i][k];
                    for (k = 0; k < t; k++) bsb[j][k] += temp*bsb[i][k];
                }
        }// K?t thúc quá trình Gauss
 
    for (i = t-1; i > 0; i--) // B?t d?u quá trình Jordan
        for (j = i-1; j >=0; j--)
            {
                temp = -asa[j][i];
                for (k = t-1; k >= i; k--)  asa[j][k] += temp*asa[i][k];
                for (k = 0; k < t; k++) bsb[j][k] += temp*bsb[i][k];
            }
 

}
