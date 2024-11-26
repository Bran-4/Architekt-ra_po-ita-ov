#define _USE_MATH_DEFINES
#include <stdio.h>
#include <float.h>
#include <math.h>
 
float sinus(float,float);
int binary(int);
int hexa(int);
int uloha4_dbl();


//uloha1
int uloha1(){
    int a=33777;
    int b='x';
    printf("Cislo %d je v desiatkovej sustave\n",a);
    printf("ascii kod pismena %c v desiatkovej sustave je %d\n",b,b);
    binary(a);
    binary(b);
    hexa(a);
    hexa(b);
    return 0;
}

int binary(int dnum){
    printf("binarne cislo z cisla %d je ",dnum);
    int zvys;
    char bnum[16];
    int itr=15;
    for (int i = 0; i<17;i++) {
        bnum[i] = 'N';
    }
    while(dnum!=0){
        zvys=dnum%2;
        bnum[itr]=zvys+48; 
        dnum/=2;
        itr-=1;
    }
    for (int  i =0;i<17;i++){
        if (bnum[i]!='N'){
            printf("%c",bnum[i]);
        }
    }
    printf("\n");
    return 0;
}

int hexa(int dnum){
    printf("hexa cislo z cisla %d je ",dnum);
    int zvys;
    char hnum[9];
    int itr=8;
    for (int i = 0; i<9;i++) {
        hnum[i] = 'N';
    }
    while(dnum!=0){
        zvys=dnum%16;
        if(zvys<10){
            hnum[itr]=zvys+48; 
        }
        else{
            hnum[itr]=zvys+55;
        }
        dnum/=16;
        itr-=1;
    }
    for (int  i =0;i<16;i++){
        if (hnum[i]!='N'){
            printf("%c",hnum[i]);
        }
    }
    printf("\n");
    return 0;
}


//uloha2
int uloha2(){
    int cislo;
    int i=0;
    char *rimske[]={"C","XC","L","XL","X","IX","V","IV","I"};
    int arabske[]={100,90,50,40,10,9,5,4,1};
    printf("daj cislo\n");
    scanf("%d",&cislo);
    while(cislo!=0){
        if(cislo>100){
            printf("mimo rozsahu");
            return 0;
        }
        if(arabske[i]<=cislo){
            cislo-=arabske[i];
            printf("%s",rimske[i]);
        }   
        else if (cislo<arabske[i])
        {
            i+=1;
        }
        }
    return 0;
}


//uloha3
int uloha3(){
    int cislo;
    int prve=1;
    int druhe=1;
    int k;
    printf("zadaj cislo");
    scanf("%d",&k);
    printf("1 1 ");
    while(1){
        cislo=prve+druhe;
        if (cislo>k){
            return 0;
        }
        prve=druhe;
        druhe=cislo;
        printf("%d ",cislo);

    }   
}

//uloha4
int uloha4(){
    printf("%e\n",FLT_EPSILON);
    float cislo=1;
    float novecislo=1;
    while(1){
        cislo/=2;
        if (cislo+1==1){
            break;
        }
        novecislo=cislo;
    }
    printf("%e",novecislo);
    return 0;
}

int uloha4_dbl(){
    printf("%e\n",DBL_EPSILON);
    double cislo=1;
    double novecislo=1;
    while(1){
        cislo/=2;
        if (cislo+1==1){
            break;
        }
        novecislo=cislo;
    }
    printf("%e",novecislo);
    return 0;
}

 //uloha 5
float faktorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * faktorial(n - 1);
}

float dostredu(float a){
    if(a>0){
        while(1){
            if (a-2*M_PI<0){
                return a;
            }
            a-=2*M_PI;
        }
    }
    if(a<0){
        while(1){
            if (a+2*M_PI>0){
                return a;
            }
            a+=2*M_PI;
        }
    }
    return 0;
}

float sinus(float rad,float epsilon){
    float cislo=2;
    float odhad=0;
    int n=0;
    rad=dostredu(rad);
    while(fabs(cislo)>epsilon){
        cislo=((pow(-1,n))*(pow(rad,2*n+1)))/(faktorial(2*n+1));
        odhad+=cislo;
        n+=1;
    }
    printf("%f",odhad);
    return odhad;
}

//spustanie
int main()
{
    float radiany=45;
    float presnost=0.000000001;
    //sinus(a,b);
    uloha1();
    uloha2();
    uloha3();
    uloha4();
    uloha4_dbl();
    sinus(radiany,presnost);
    //uloha4_dbl();
    return 0;
}


