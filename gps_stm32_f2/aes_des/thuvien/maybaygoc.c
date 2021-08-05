#include "MPU_6050.h"
#include "i2c_mpu_6050.h"
double x_t[6][6],x[6][6],w[6][6],u[6][6],A_t[6][6],xm[6][6],zk[6][6];
double P[6][6],PE[6][6],Pi[6][6],P_t[6][6],Pm[6][6];
//x=A*x(k-1)+Bu
// P=AP(k-1)At+Q
//Kk=P*Ht*(H*P*Ht+R)-1
//xm=x+Kk(zk-H*x)
//Pm=(I-Kk*H)*P
int k;
double R[6][6]={
{0.1,  0,  0,  0,  0,  0 },
{0,  0.1,  0,  0,  0,   0 },
{0,  0,  0.1,  0,  0,   0 },
{0,  0,  0,  0.1,  0,  0  },
{0,  0,  0,  0,  0.1,   0 },
{0,  0,  0,  0,  0,   0.1 }
};
double Q[6][6]={
{0.1,  0,  0.05,  0,  0,  0 },
{0,  0.1,  0,  0,  0.02,   0    },
{0,  0,  0.1,  0,  0.050,   0   },
{0,  0,  0,  0.1,  0,  0   },
{0,  0,  0,  0,  0.1,   0    },
{0,  0,  0,  0,  0,   0.1 }
};
double Kk[6][6]={
{1,  0,  0,  0,  0,   0 },
{0,  1,  0,  0,  0,   0 },
{0,  0,  1,  0,  0,   0 },
{0,  0,  0,  1,  0,   0 },
{0,  0,  0,  0,  1,   0 },
{0,  0,  0,  0,  0,   1 }
};
double A[6][6]={
{1.004,    0.0001,  0.001,    0.0014,    0.0000,  -0.0003  },
{0.000,    1.000,     -0.00,      0.0000,    0.0019,   0   },
{0.0004,  0.0002,  1.002,    0.0003,    0.0001,   0.0015   },
{0.2028,  0.0481,  0.0433,  0.7114,   -0.0166,  -0.1458    },
{0.0080,  0.0021, -0.0020, -0.0224,    0.9289,   0.005     },
{0.1895,  0.1009,  0.1101, -0.1602,    0.0621,   0.7404    }
};
double I[6][6]={
{1,  0,  0,  0,  0,  0 },
{0,  1,  0,  0,  0,  0 },
{0,  0,  1,  0,  0,  0 },
{0,  0,  0,  1,  0,  0 },
{0,  0,  0,  0,  1,  0 },
{0,  0,  0,  0,  0,  1 }
};


double B[6][3] = {
{0.0000,   0.0000 ,  0.0000  },
{0.0000,   0.0000,  -0.0000  },
{0.0000,  -0.0000,   0.0000  },
{0.007,    -0.0000,   0.0005 },
{0.0001,   0.0000,  -0.0000  },
{0.0003,  -0.0000,   0.0008  }
};
double H[6][6]={
{1,  0,  0,  0,  0,  0 },
{0,  1,  0,  0,  0,  0 },
{0,  0,  1,  0,  0,  0 },
{0,  0,  0,  1,  0,  0 },
{0,  0,  0,  0,  1,  0 },
{0,  0,  0,  0,  0,  1 }
};
double Ht[6][6];
double outH[6][6];


double asa[6][6],bsb[6][6],csc[6][6];
double bonho1[6][6],bonho2[6][6],bonho3[6][6];

void TruMaTran(double *A,double *B,int m, int n,int dai) {
	int i,j;
 for(i = 0; i<m; i++)
  for(j = 0; j<n; j++)
   asa[i][j] = *(A+i*dai+j)-*(B+i*dai+j);
}

void CongMaTran(double *A,double *B,int m, int n ,int dai) {
 int i,j;
	for(i = 0; i<m; i++)
  for(j = 0; j<n; j++)
    asa[i][j] = *(A+i*dai+j)+*(B+i*dai+j);
}
//matran mxn vs nxp---
void NhanMaTran(double *A,double *B,int m,int n,int p,int dai,int dai2){ 
	double so1,so2;
	int i,j,k;
 for(i = 0; i<m; i++)
  for(k = 0; k<p; k++) {
   csc[i][k]=0;
   for(j = 0; j<n; j++){
	   so1=*(A+i*dai+j);
   so2=*(B+j*dai2+k);
   csc[i][k] = csc[i][k]+so1*so2;
   }
  }
}

void coppymatran(double *A,double *B,int m,int n,int dai)
{
  int i,j;
   for(i=0;i<m;i++)
    for(j=0;j<n;j++)
     *(A+i*dai+j)=*(B+i*dai+j);
}




void matranchuyenvi_matranA(double *A,int n,int dai)
{ 
  int i,j;
   for(i=0;i<n;i++)
    for(j=0;j<n;j++)
     bsb[i][j]=*(A+dai*j+i);
}




void ngichdao(int t) {
// Tinh dinh thuc cua asa sang bsb la ma tran dao
	int k,i,j,sign = 1;
	double det,temp;
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
}


void tinhtoancongthuc1(void) //x=A*x(k-1)+Bu
{
	NhanMaTran(&A[0][0],&x_t[0][0],6,6,1,6,6); 
coppymatran(&bonho1[0][0],&csc[0][0],6,1,6);
	NhanMaTran(B[0],u[0],6,3,1,6,6);
	CongMaTran(&csc[0][0],&bonho1[0][0],6,1,6);
coppymatran(&x[0][0],&asa[0][0],6,1,6);	
}

void tinhtoancongthuc2(void) // P=AP(k-1)At+Q
{	NhanMaTran(&A[0][0],&P_t[0][0],6,6,6,6,6); 
coppymatran(&bonho1[0][0],&csc[0][0],6,6,6);
	matranchuyenvi_matranA(&A[0][0],6,6);
	NhanMaTran(&bonho1[0][0],&bsb[0][0],6,6,6,6,6);
	CongMaTran(&csc[0][0],&Q[0][0],6,6,6);
coppymatran(&P[0][0],&asa[0][0],6,6,6);	

}


 void tinhtoancongthuc3(void) //Kk=P*Ht*(H*P*Ht+R)-1
{
	matranchuyenvi_matranA(&H[0][0],6,6);
	NhanMaTran(&P[0][0],&bsb[0][0],6,6,6,6,6); 
coppymatran(&bonho1[0][0],&csc[0][0],6,6,6);
	NhanMaTran(&H[0][0],&P[0][0],6,6,6,6,6);
coppymatran(&bonho2[0][0],&csc[0][0],6,6,6);	
	NhanMaTran(&bonho2[0][0],&bsb[0][0],6,6,6,6,6);
	CongMaTran(&csc[0][0],&R[0][0],6,6,6);
coppymatran(&asa[0][0],&csc[0][0],6,6,6);	
	ngichdao(6);
	NhanMaTran(&bonho1[0][0],&bsb[0][0],6,6,6,6,6);
coppymatran(&Kk[0][0],&csc[0][0],6,6,6);
}


void tinhtoancongthuc4(void) //xm=x+Kk(zk-H*x)
{
NhanMaTran(&H[0][0],&x[0][0],6,6,1,6,6); 
	TruMaTran(&zk[0][0],&csc[0][0],6,1,6);
	NhanMaTran(&Kk[0][0],&asa[0][0],6,6,1,6,6);
	CongMaTran(&x[0][0],&csc[0][0],6,1,6);
coppymatran(&xm[0][0],&asa[0][0],6,1,6);	
}
void tinhtoancongthuc5(void) //Pm=(I-Kk*H)*P
{
	NhanMaTran(&Kk[0][0],&H[0][0],6,6,6,6,6); 
	TruMaTran(&I[0][0],&csc[0][0],6,6,6);	
	NhanMaTran(&asa[0][0],&P[0][0],6,6,6,6,6);
coppymatran(&Pm[0][0],&csc[0][0],6,6,6);	
}	



int caculatorangle(unsigned int t){
	int out_print;
	out_print=t/180;
	if(out_print>180) out_print-=360;
	return out_print;
}
