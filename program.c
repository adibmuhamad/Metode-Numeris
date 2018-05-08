#include<stdio.h>

float metodeLiebmann(int platKiri, int platKanan, int platAtas, int platBawah, float lamda, float es);
float metodeExplicit(float k, int jumlahT, int Tawal, int Takhir, float panjangX, int Troad, float deltaX, float deltaT);

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

