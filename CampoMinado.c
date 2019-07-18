#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//comentário
/*Project CampoMinado
auhtor andrenascimento*/
void _vizinho(int i, int j,char jogo[10][10]){
    int a,b;
    for(a=0;a<10;a++){
        for(b=0;b<10;b++){
            if(jogo[a][b]==' '){
                jogo[a][b]=48;
            }
        }
    }
    if(i==0 && j==0){
        jogo[i][j+1]++;
        jogo[i+1][j]++;
        jogo[i+1][j+1]++;
    }
    else{
        if(i==0 || j==0){
            if(i==0){
                jogo[i][j-1]++;
                jogo[i][j+1]++;
                jogo[i+1][j-1]++;
                jogo[i+1][j]++;
                jogo[i+1][j+1]++;
            }
            else{
                jogo[i-1][j]++;
                jogo[i-1][j+1]++;
                jogo[i][j+1]++;
                jogo[i+1][j]++;
                jogo[i+1][j+1]++;
            }
        }
        else{
            if(i==9 || j==9){
                if(i==9){
                    jogo[i-1][j-1]++;
                    jogo[i-1][j]++;
                    jogo[i-1][j+1]++;
                    jogo[i][j-1]++;
                    jogo[i][j+1]++;
                }
                else{
                    jogo[i-1][j-1]++;
                    jogo[i][j-1]++;
                    jogo[i+1][j-1]++;
                    jogo[i-1][j]++;
                    jogo[i+1][j]++;
                }
            }
            else{
                jogo[i-1][j-1]++;
                jogo[i-1][j]++;
                jogo[i-1][j+1]++;
                jogo[i][j-1]++;
                jogo[i][j+1]++;
                jogo[i+1][j-1]++;
                jogo[i+1][j]++;
                jogo[i+1][j+1]++;
            }

        }
    }
    for(a=0;a<10;a++){
        for(b=0;b<10;b++){
            if(jogo[a][b]==48){
                jogo[a][b]=' ';
            }
            if(jogo[a][b]==43){
                jogo[a][b]='*';
            }
        }
    }
}
int main(int argc, char* argv[]){
    char visual[10][10],jogo[10][10];
    int i,j,c=0,x,y,cont=0,cr=0,repete[2][90],rep_c=0,rep_cr,z=0;
    float prog=0.0;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            jogo[i][j]=' ';
        }
    }
    srand(time(NULL));
    do{
        i=rand()%10;
        j=rand()%10;
        if(jogo[i][j]!='*'){
            jogo[i][j]='*';
            c++;
        }
    }while(c!=10);
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            if(jogo[i][j]=='*'){
                _vizinho(i,j,jogo);
            }
        }
    }
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            visual[i][j]=63;
        }
    }
    for(i=0;i<2;i++){
        for(j=0;j<90;j++){
            repete[i][j]=-1;
        }
    }
    do{
        printf("=====CAMPO MINADO=====\n\n");
        printf("  0 1 2 3 4 5 6 7 8 9\n  -------------------\n");
        for(i=0;i<10;i++){
            printf("%d|",i);
            for(j=0;j<10;j++){
                printf("%-2c",visual[i][j]);
            }
            printf("\n");
        }
        do{
            prog=(cont-rep_c)*10.0/9.0;
            printf("\nJogadas: %d   Progresso: %.2f%%\n",cont-rep_c,prog);
            printf("Digite uma coordenada(linha coluna): ");
            scanf("%d %d",&x,&y);
            if(x>9 || x<0 || y>9 || y<0){
            printf("\nEssa coordenada nao existe! ");
            rep_c++;
            }
            rep_cr=0;
            for(i=0;i<cr+1;i++){
                if(x==repete[0][i] && y==repete[1][i]){
                    rep_c++;
                    rep_cr++;
                    break;
                }
            }
            if(rep_cr==0 && x<=9 && x>=0 && y<=9 && y>=0){
                repete[0][cr]=x;
                repete[1][cr]=y;
                cr++;
            }
            cont++;
        }while(x>9 || x<0 || y>9 || y<0);
        if(jogo[x][y]==42){
            printf("\n======FIM DE JOGO======\n");
            printf("  0 1 2 3 4 5 6 7 8 9\n  -------------------\n");
            for(i=0;i<10;i++){
                printf("%d|",i);
                for(j=0;j<10;j++){
                    printf("%-2c",jogo[i][j]);
                }
                printf("\n");
            }
            printf("Jogadas: %d   Progresso: %.2f%%",cont-rep_c,prog);
            printf("\n\n============================\n========(Feito por)=========\n=====(Andre Nascimento)=====\n============================\n");
            break;
        }
        else{
            visual[x][y]=jogo[x][y];
            system("cls");
        }
        if(cont-rep_c==90){
            printf("========PARABENS========\n");
            printf("  0 1 2 3 4 5 6 7 8 9\n  -------------------\n");
            for(i=0;i<10;i++){
                printf("%d|",i);
                for(j=0;j<10;j++){
                    printf("%-2c",visual[i][j]);
                }
                printf("\n");
            }
            printf("\nJogadas: %d   Progresso: 100%%",cont-rep_c);
            printf("\n\n============================\n=========(Feito por)========\n=====(Andre Nascimento)=====\n============================\n");
            break;
        }
    }while(z==0);
return 0;
}
