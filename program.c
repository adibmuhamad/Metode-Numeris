#include<stdio.h>

float metodeLiebmann(int platKiri, int platKanan, int platAtas, int platBawah, float lamda, float es);
float metodeExplicit(float k, int jumlahT, int Tawal, int Takhir, float panjangX, int Troad, float deltaX, float deltaT);
float metodeImplicit(float k, int jumlahT, int Tawal, int Takhir, float panjangX, int Troad, float deltaX, float deltaT);

int main(void){

    float k = 0.835 ;

    int pilihan;

    //Input Metode Liebmann
    int platKiri;
    int platKanan;
    int platAtas;
    int platBawah;
    float lamda;
    float es;
    
    //Input Metode Explicit & Implicit
    int jumlahT;
    int Tawal;
    int Takhir;
    int Troad;
    float panjangX;
    float deltaX;
    float deltaT;
    
     printf("***********************************************\n");
    printf("Program PDE dengan FDM (elliptic & parabolic) \n");
    printf("dengan metode Liebmann, metode Explicit, dan metode Implicit\n");
    printf("***********************************************\n");

    printf("Masukkan pilihan penyelesaian PDE\n ");
    printf("1. Metode Liebmann\n ");
    printf("2. Metode Explicit\n ");
    printf("1. Metode Implicit\n ");
    printf("Pilihan anda (Tekan 1/2/3) : ");
    scanf("%d",&pilihan);

    switch(pilihan){
        case 1:
            printf("Masukkan temperatur plat kiri :");
            scanf("%d",&platKiri);
            printf("Masukkan temperatur plat kanan :");
            scanf("%d",&platKanan);
            printf("Masukkan temperatur plat atas :");
            scanf("%d",&platAtas);
            printf("Masukkan temperatur plat bawah :");
            scanf("%d",&platBawah);
            printf("Masukkan lamda (weighting factor)  :");
            scanf("%f",&lamda);
            printf("Masukkan estimasi error (dalam persen)  :");
            scanf("%f",&es);
            metodeLiebmann(platKiri, platKanan, platAtas, platBawah, lamda, es);
            break;
        case 2:
            printf("Masukkan berapa jumlah T :");
            scanf("%d",&jumlahT);
            printf("Masukkan Temperature awal :  ");
            scanf("%d",&Tawal);
            printf("Masukkan Temperature ke %d :  ", jumlahT);
            scanf("%d",&Takhir);
            printf("Masukkan Temperature of road :  ");
            scanf("%d",&Troad);
            printf("Masukkan panjang road :  ");
            scanf("%f",&panjangX);
            printf("Masukkan delta X :  ");
            scanf("%f",&deltaX);
            printf("Masukkan delta T :  ");
            scanf("%f",&deltaT);
            metodeExplicit(k,jumlahT,Tawal,Takhir,panjangX,Troad,deltaX,deltaT);
            break;
        case 3:
            printf("Masukkan berapa jumlah T :");
            scanf("%d",&jumlahT);
            printf("Masukkan Temperature awal :  ");
            scanf("%d",&Tawal);
            printf("Masukkan Temperature ke %d :  ", jumlahT);
            scanf("%d",&Takhir);
            printf("Masukkan Temperature of road :  ");
            scanf("%d",&Troad);
            printf("Masukkan panjang road :  ");
            scanf("%f",&panjangX);
            printf("Masukkan delta X :  ");
            scanf("%f",&deltaX);
            printf("Masukkan delta T :  ");
            scanf("%f",&deltaT);
            metodeImplicit(k,jumlahT,Tawal,Takhir,panjangX,Troad,deltaX,deltaT);
            break;
        default:
            printf("Menu tidak ditemukan. \n");
            return main();
       
    }

    return 0;
}

float metodeLiebmann(int platKiri, int platKanan, int platAtas, int platBawah, float lamda, float es){
    //Rumus Metode Liebman Ti+1,j + Ti−1,j + Ti,j+1 + Ti,j−1 = 4Ti,jnew 

    int stopIteration;
    float T[5][5];
    float temp;
    float estimasi;

    float iterasi;

    for(int i = 1; i < 5; i++){
        T[0][i] = platKiri;
        T[i][0] = platBawah;
        T[4][i] = platKanan;
        T[i][4] = platAtas;
    }

    iterasi = es/100;



    for(int a = 1; a < 4; a++){
        for(int b = 1; b < 4; b++){
            T[a][b] = 0;
            
        }
    }
    for(int infinity = 0; infinity <1000; infinity++){
        for(int j =1; j <4; j++){
            temp = T[j][1];
            T[j][1] = (T[j+1][1] + T[j-1][1] + T[j][2] + T[j][0])/4;
            T[j][1] = lamda*(T[j][1]) + (1-lamda)*temp;
    
            estimasi = (T[j][1]-temp)/T[j][1];
            
            if(estimasi < iterasi){
                
                break;
            }
    
        }
        for(int j =1; j <4; j++){
            temp = T[j][2];
            T[j][2] = (T[j+1][2] + T[j-1][2] + T[j][3] + T[j][1])/4;
            T[j][2] = lamda*(T[j][2]) + (1-lamda)*temp;
        }
    
        for(int j =1; j <4; j++){
            temp = T[j][3];
            T[j][3] = (T[j+1][3] + T[j-1][3] + T[j][4] + T[j][2])/4;
            T[j][3] = lamda*(T[j][3]) + (1-lamda)*temp;
        }
    
        if(estimasi < 0){
            estimasi = -estimasi;
        }
    }

    for(int l = 1; l < 4; l++){
        for(int m =1; m < 4; m++){
           printf("T[%d][%d] : %f \n", l,m,T[l][m]);
        }
    }
}

float metodeExplicit(float k, int jumlahT, int Tawal, int Takhir, float panjangX, int Troad, float deltaX, float deltaT){
    float lamda;
    int node;
    int iterasi;

    lamda = k*deltaT/(deltaX*deltaX);
    node = (panjangX-0)/deltaX;
    iterasi = (jumlahT-0)/deltaT;

    float T[iterasi][node];

    printf("|=========================================================================|\n");
    printf("| Iterasi Ke-       |   T0  |   T1  |   T2  |   T3  |   T4  |   T5  |\n");
    printf("|=========================================================================|");
    
    //Rumus Metode Explicit : Ti,j+1 = Ti,j +lamda(Ti+1,j-2Ti,j+Ti-i,j)
    for(int j = 0; j < iterasi; j++ ){
        for(int i = 1; i <= node; i++ ){
            T[j][0] = Tawal;
            T[0][i] = Troad;
            T[j][node] = Takhir;
            
            T[j+1][i] = T[j][i] + lamda*(T[j][i+1]-2*T[j][i]+T[j][i-1]);
        }
        printf("\n| %d      |   %f  |   %f  |   %f  |   %f  |   %f  |   %f  |", j,T[j][0],T[j][1],T[j][2],T[j][3],T[j][4],T[j][5]);
        printf("\n");
    }

    printf("Hasilnya adalah : \n");
    for(int b = 1;b <node; b++){
        printf("T[2][%d] : %f", b,T[2][b] );
        printf("\n");
    }
}

float metodeImplicit(float k, int jumlahT, int Tawal, int Takhir, float panjangX, int Troad, float deltaX, float deltaT){
    float lamda;
    int node;
    int iterasi;
    
    lamda = k*deltaT/(deltaX*deltaX);
    node = (panjangX-0)/deltaX;
    iterasi = (jumlahT-0)/deltaT;
  
    
    float T[iterasi][node+1];
  
    float A[5][5];

    float c;
    float x[6];
    float sum=0.0;

    for(int j = 0; j < iterasi; j++ ){
        for(int i = 1; i <node; i++ ){
            T[j][0] = Tawal;
            T[0][i] = Troad;
            T[j][node] = Takhir;
            
        }
        
    }
    for(int z = 0; z < iterasi; z++ ){
        
            A[1][1] = 1+(2*lamda);
            A[1][2] = -lamda;
            A[1][3] = 0;
            A[1][4] = 0;
            A[1][5] = T[z][1]-((-lamda)*T[z+1][0]);

            A[2][1] = -lamda;
            A[2][2] = 1+(2*lamda);
            A[2][3] = -lamda;
            A[2][4] = 0;
            A[2][5] = T[z][2];

            A[3][1] = 0;
            A[3][2] = -lamda;
            A[3][3] = 1+(2*lamda);
            A[3][4] = -lamda;
            A[3][5] = T[z][3];

            A[4][1] = 0;
            A[4][2] = 0;
            A[4][3] = -lamda;
            A[4][4] = 1+(2*lamda);
            A[4][5] = T[z][1]-((-lamda)*T[z+1][5]);

            
            
        //Eliminasi Gauss
        //Looping untuk menghasilkan matriks segitiga
        for(int j=1; j<=4; j++) 
        {
            for(int i=1; i<=4; i++)
            {
                if(i>j)
                {
                    c=A[i][j]/A[j][j];
                    for(int k=1; k<=5; k++)
                    {
                        A[i][k]=A[i][k]-c*A[j][k];
                    }
                }
            }
        }
        
        x[4]=A[4][5]/A[4][4];
        /* Looping untuk backward substitution*/
        for(int i=3; i>=1; i--)
        {
            sum=0;
            for(int j=i+1; j<=4; j++)
            {
                sum=sum+A[i][j]*x[j];
            }
            x[i]=(A[i][5]-sum)/A[i][i];
            
            
        }
        printf("Iterasi ke %d \n", z+1);
        for(int i = 1; i <=4; i++){
            T[z+1][i] = x[i];
        }
        
        for(int i=0; i<=5; i++)
        {
            x[0] = Tawal;
            x[node] = Takhir;
            printf("T[%d] : %f \n",i,x[i]); 
            
        }
    }
}
