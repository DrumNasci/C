
/*Autor:   @andrenascimento*/
/*Projeto: Resta 1*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
int _possib(char visual[7][7]){                                        //verifica a quantidade de movimentos possiveis antes de cada movimento
    int i,j,prob;
    prob=0;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(visual[i][j]=='1'){
                if((visual[i+2][j]=='0')&&(visual[i+1][j]=='1')){
                    prob++;
                }
                if((visual[i-2][j]=='0')&&(visual[i-1][j]=='1')){
                    prob++;
                }
                if((visual[i][j+2]=='0')&&(visual[i][j+1]=='1')){
                    prob++;
                }
                if((visual[i][j-2]=='0')&&(visual[i][j-1]=='1')){
                    prob++;
                }
            }
        }
    }
return prob;
}
void _waitForIt(int t){                                                //determina um tempo para qualquer coisa
    double inicio,fim,dif;
    inicio=clock();
    fim=clock();
    dif=(fim-inicio)/CLOCKS_PER_SEC;
    while(dif<t){   //faz a tela congelar pelo tempo recebido na funcao
        fim=clock();
        dif=(fim-inicio)/CLOCKS_PER_SEC;
    }
    system("cls");
}
int _permissao(int x,int y,int modo,int xo,int yo,char visual[7][7]){  //verifica se o movimento e valido
    int r=1;
    if(x<0 || x>6 || y<0 || y>6){
        r=0;
    }
    else{
        if(modo==1){ //modo = 1, recebe coordenadas iniciais
            if(visual[x][y]!='1'){
            r=0;
            }
        }
        if(modo==2){ //modo = 2, recebe tambem coordenadas finais
            if(((abs(x-xo)!=2) && (y==yo)) || ((abs(y-yo)!=2) && (x==xo)) || (visual[x][y]!='0') || (x!=xo && y!=yo)){
                r=0;
            }
        }
    }
    return r;
}
int _automatico(char visual[7][7],int x,int y){                        //funcao responsavel por fazer movimentos automaticos
    int c=0,i,j,i1,j1,caso;
    if(x>=0&&x<=1&&y>=2&&y<=4){
        caso=1; //extremidade superior
    }
    else{
        if(x>=2&&x<=4&&y>=0&&y<=1){
            caso=2; //extremidade lateral esquerda
        }
        else{
            if(x>=2&&x<=4&&y>=5&&y<=6){
                caso=3; //extremidade lateral direita
            }
            else{
                if(x>=5&&x<=6&&y>=2&&y<=4){
                    caso=4; //extremidade inferior
                }
                else{
                    caso=5; //centro do tabuleiro
                }
            }
        }
    }
    if(caso==1||caso==2||caso==3||caso==5){             //Inicio (verificacao de movimentos possiveis)
        if(visual[x+2][y]=='0'&&visual[x+1][y]=='1'){
            c++;
            i=x+2;
            i1=x+1;
            j=y;
            j1=y;
        }
    }
    if(caso==2||caso==3||caso==4||caso==5){
        if(visual[x-2][y]=='0'&&visual[x-1][y]=='1'){
            c++;
            i=x-2;
            i1=x-1;
            j=y;
            j1=y;
        }
    }
    if(caso==1||caso==2||caso==4||caso==5){
        if(visual[x][y+2]=='0'&&visual[x][y+1]=='1'){
            c++;
            i=x;
            i1=x;
            j=y+2;
            j1=y+1;
        }
    }
    if(caso==1||caso==3||caso==4||caso==5){
        if(visual[x][y-2]=='0'&&visual[x][y-1]=='1'){
            c++;
            i=x;
            i1=x;
            j=y-2;
            j1=y-1;
        }
    }                                               //FIM (verificacao de movimentos possiveis)
    if(c==1){
        visual[x][y]='0';
        visual[i][j]='1';
        visual[i1][j1]='0';
        return 1;       //apenas um movimento possivel
    }
    else{
        if(c==0){
            return 0;   //nenhum movimento possivel
        }
        else{
            return -1;  //mais de um movimento possivel
        }
    }
}
void _imprimeMatriz(char visual[7][7],int jogadas[1],int cor_v[2],int op_v[3]){                     //mostra o que está na tela durante o jogo
    int i,j;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    SetConsoleTextAttribute(hConsole, cor_v[0]);
    if(op_v[1]==1){ //1 = ativado, imprime o progresso na tela
        printf("\n\n Progresso: %.2f%%\n\n",jogadas[0]*100/31.0);
    }
    printf("              0      1      2      3      4      5      6\n"); //imprime coordenadas superiores
    SetConsoleTextAttribute(hConsole, saved_attributes);
    printf("                           ");
    SetConsoleTextAttribute(hConsole, cor_v[1]);
    printf("                 \n");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    for(i=0;i<7;i++){
        SetConsoleTextAttribute(hConsole, cor_v[0]);
        printf("         %d ",i);
        SetConsoleTextAttribute(hConsole, saved_attributes);
        for(j=0;j<7;j++){
            if((i<2 &&(j>1&&j<5))||(i>=2&&i<=4)||(i>=5&&(j>1&&j<5))){
                SetConsoleTextAttribute(hConsole, cor_v[1]);
                printf("  (%c)  ",visual[i][j]); //imprime pecas
                SetConsoleTextAttribute(hConsole, saved_attributes);
            }
            else{
                printf("   %c   ",visual[i][j]); //imprime asteriscos
            }
        }
        SetConsoleTextAttribute(hConsole, cor_v[0]);
        printf(" %d",i); //coordenadas laterais na direita
        SetConsoleTextAttribute(hConsole, saved_attributes);  //inicio forma inferior tabuleiro
        if(i==0||i==5){
            printf("\n                         ");
            SetConsoleTextAttribute(hConsole, cor_v[1]);
            printf("                     ");
            SetConsoleTextAttribute(hConsole, saved_attributes);
            printf("\n                         ");
            SetConsoleTextAttribute(hConsole, cor_v[1]);
            printf("                     \n");
            SetConsoleTextAttribute(hConsole, saved_attributes);
        }
        else{
            if(i==1){
                printf("\n                         ");
                SetConsoleTextAttribute(hConsole, cor_v[1]);
                printf("                     \n");
                SetConsoleTextAttribute(hConsole, saved_attributes);
                printf("             ");
                SetConsoleTextAttribute(hConsole, cor_v[1]);
                printf("                                             \n");
                SetConsoleTextAttribute(hConsole, saved_attributes);
            }
            else{
                if(i==2||i==3){
                    SetConsoleTextAttribute(hConsole, saved_attributes);
                    printf("\n           ",i);
                    SetConsoleTextAttribute(hConsole, cor_v[1]);
                    printf("                                                 \n");
                    SetConsoleTextAttribute(hConsole, saved_attributes);
                    printf("           ");
                    SetConsoleTextAttribute(hConsole, cor_v[1]);
                    printf("                                                 \n");
                    SetConsoleTextAttribute(hConsole, saved_attributes);
                }
                else{
                    if(i==4){
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                        printf("\n             ");
                        SetConsoleTextAttribute(hConsole, cor_v[1]);
                        printf("                                             \n");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                        printf("                         ");
                        SetConsoleTextAttribute(hConsole, cor_v[1]);
                        printf("                     \n");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                    }
                    else{
                        printf("\n                           ");
                        SetConsoleTextAttribute(hConsole, cor_v[1]);
                        printf("                 \n");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                    }
                }
            }
        }
    }  //fim forma inferior tabuleiro
    SetConsoleTextAttribute(hConsole, cor_v[0]);
    printf("              0      1      2      3      4      5      6\n\n");  //imprime coordenadas inferiores
    if(op_v[3]==1){
        printf(" Pontos: %d                                       ",jogadas[0]); //1 = ativado, mostra pontos na tela
    }
    if(op_v[2]==1){
        printf(" Jogadas possiveis: %d\n\n",_possib(visual)); //1 = ativado, mostra jogadas possiveis na tela
    }
    SetConsoleTextAttribute(hConsole, saved_attributes);
}
void _jogo(char visual[7][7],int op_v[3],int cor_v[2],int partidas[4],int mode,int jogadas[1]){     //onde o jogo acontece
    int i,j,xf,xo,yf,yo,prob,ativ;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    system("cls");
    char resp_s;
    if(mode==1){
        jogadas[0]=0; //mode 1 -> novo jogo, zera jogadas
    }
    do{
        prob=_possib(visual);
        if(prob==0){
            partidas[2]++;  //partidas perdidas +1
            SetConsoleTextAttribute(hConsole, 12);  //texto fim de jogo
            printf("\n\n\n\n\n\n\n\n\n\n                  ___   ___   __  __     ___    ___ \n                 | __| |_ _| |  \\/  |   |   \\  | __|\n                 | _|   | |  | |\\/| |   | |) | | _|\n                 |_|   |___| |_|  |_|   |___/  |___|\n                     _    ___     ___    ___    _ \n                  _ | |  / _ \\   / __|  / _ \\  | |\n                 | || | | (_) | | (_ | | (_) | |_|\n                  \\__/   \\___/   \\___|  \\___/  (_)\n");
            printf("\n            ");
            SetConsoleTextAttribute(hConsole, saved_attributes);
            system("pause");
            system("cls");
            _imprimeMatriz(visual,jogadas,cor_v,op_v);
            printf("\n");
            system("pause");
            break;
        }
        _imprimeMatriz(visual,jogadas,cor_v,op_v);
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf("\nDigite as coordenadas de origem (linha coluna): ");
        scanf("%d %d",&xo,&yo);
        if(xo==0 && yo==0){  //opcao de sair do jogo
            do{
                system("cls");
                printf("\n\n\n\n\n\n\n\n\n\n\n\n          Tem certeza que deseja sair da partida? (S/N) ");
                resp_s=getchar();
            }while(resp_s!='S' && resp_s!='N');
            if(resp_s=='S'){
                    partidas[1]++;      //partidas abandonadas +1
                    break;
            }
        }
        if(_permissao(xo,yo,1,0,0,visual)==1){      //permissao = 1, permissao concedida
            if(op_v[0]==1){     //op_v[0] -> jogadas automaticas, 1 -> ligado
                if(_automatico(visual,xo,yo)==1){
                    jogadas[0]++;
                    system("cls");
                    continue;
                }
                else{
                    if(_automatico(visual,xo,yo)==0){
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 12);
                        printf(" Coordenadas invalidas!                          ");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                        continue;
                    }
                }
            }
            printf("Digite as coordenadas finais (linha coluna): ");
            scanf("%d %d",&xf,&yf);
            if(_permissao(xf,yf,2,xo,yo,visual)==1){    //permissao = 1, permissao concedida
                visual[xo][yo]='0';
                visual[xf][yf]='1';
                if(xo==xf){
                    visual[xo][(yo+yf)/2]='0';
                }
                else{
                    visual[(xo+xf)/2][yo]='0';
                }
                jogadas[0]++;
                system("cls");
            }
            else{
                system("cls");
                SetConsoleTextAttribute(hConsole, 12);
                printf(" Movimento invalido!                      ");
                SetConsoleTextAttribute(hConsole, saved_attributes);
            }
        }
        else{
            system("cls");
            SetConsoleTextAttribute(hConsole, 12);
            printf(" Coordenadas invalidas!                           ");
            SetConsoleTextAttribute(hConsole, saved_attributes);
        }
    }while(jogadas[0]!=31); //condicao para ganhar o jogo
    if(jogadas[0]==31){
        SetConsoleTextAttribute(hConsole, 10);   //texto parabens
        printf("\n\n\n\n\n\n\n\n\n\n\n\n         ___     _     ___     _     ___   ___   _  _   ___   _ \n        | _ \\   /_\\   | _ \\   /_\\   | _ ) | __| | \\| | / __| | |\n        |  _/  / _ \\  |   /  / _ \\  | _ \\ | _|  | .` | \\__ \\ |_|\n        |_|   /_/ \\_\\ |_|_\\ /_/ \\_\\ |___/ |___| |_|\\_| |___/ (_)\n");
        printf("\n         ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        system("pause");
        system("cls");
        _imprimeMatriz(visual,jogadas,cor_v,op_v);
        partidas[0]++;   //partidas ganhas +1
        printf("\n");
        system("pause");
    }
}
void _defaultOpcoes(int op_v[4]){                                      //preset padrao de opcoes
    op_v[0]=1;
    op_v[1]=1;
    op_v[2]=1;
    op_v[3]=1;
}
void _defaultCores(int cor_v[2]){                                      //preset padrao de cores
    cor_v[0]=14;
    cor_v[1]=112;
}
void _imprimeOpcoes(int v[4],int n){                                   //imprime o estado da opcao no submenu de opcoes
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    if(v[n]==1){  //1 = opcao ativa
        SetConsoleTextAttribute(hConsole, 10); //verde
        printf("SIM");
        SetConsoleTextAttribute(hConsole, saved_attributes);
    }
    else{
        SetConsoleTextAttribute(hConsole, 12); //vermelho
        printf("NAO");
        SetConsoleTextAttribute(hConsole, saved_attributes);
    }
}
int _mudaOp(int op){                                                   //muda uma determinada opcao no submenu de opcoes
    if(op==0){
        return 1;
    }
    else{
        return 0;
    }
}
int _mudaCor(int v_cor[2],int n){                                      //muda uma determinada cor no submenu de opcoes
    if(n==0){
        if(v_cor[n]==14){
            return 10;
        }
        else{
            return (v_cor[n]+1);
        }
    }
    else{
        if(v_cor[n]==112){
            return 47;
        }
        else{
            if(v_cor[n]==111){
                return 112;
            }
            else{
                return (v_cor[n]+16);
            }
        }
    }
}
void _imprimeCor(int cor_v[2],int n){                                  //imprime a cor no submenu de opcoes
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    if(n==0){
        if(cor_v[n]==10){
            printf(".....");
            SetConsoleTextAttribute(hConsole, 10);
            printf("VERDE");
            SetConsoleTextAttribute(hConsole, saved_attributes);
        }
        else{
            if(cor_v[n]==11){
                printf("......");
                SetConsoleTextAttribute(hConsole, 11);
                printf("AZUL");
                SetConsoleTextAttribute(hConsole, saved_attributes);
            }
            else{
                if(cor_v[n]==12){
                    printf("..");
                    SetConsoleTextAttribute(hConsole, 12);
                    printf("VERMELHO");
                    SetConsoleTextAttribute(hConsole, saved_attributes);
                }
                else{
                    if(cor_v[n]==13){
                        printf("......");
                        SetConsoleTextAttribute(hConsole, 13);
                        printf("ROSA");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                    }
                    else{
                        if(cor_v[n]==14){
                            printf("...");
                            SetConsoleTextAttribute(hConsole, 14);
                            printf("AMARELO");
                            SetConsoleTextAttribute(hConsole, saved_attributes);
                        }
                    }
                }
            }
        }
    }
    else{
         if(cor_v[n]==47){
            printf("......");
            SetConsoleTextAttribute(hConsole, 47);
            printf("VERDE");
            SetConsoleTextAttribute(hConsole, saved_attributes);
        }
        else{
            if(cor_v[n]==63){
                printf(".......");
                SetConsoleTextAttribute(hConsole, 63);
                printf("AZUL");
                SetConsoleTextAttribute(hConsole, saved_attributes);
            }
            else{
                if(cor_v[n]==79){
                    printf("...");
                    SetConsoleTextAttribute(hConsole, 79);
                    printf("VERMELHO");
                    SetConsoleTextAttribute(hConsole, saved_attributes);
                }
                else{
                    if(cor_v[n]==95){
                        printf(".......");
                        SetConsoleTextAttribute(hConsole, 95);
                        printf("ROSA");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                    }
                    else{
                        if(cor_v[n]==111){
                            printf("....");
                            SetConsoleTextAttribute(hConsole, 111);
                            printf("AMARELO");
                            SetConsoleTextAttribute(hConsole, saved_attributes);
                        }
                        else{
                            if(cor_v[n]==112){
                                printf(".....");
                                SetConsoleTextAttribute(hConsole, 112);
                                printf("BRANCO");
                                SetConsoleTextAttribute(hConsole, saved_attributes);
                            }
                        }
                    }
                }
            }
        }
    }
}
void _inicializaJogo(char visual[7][7]){                               //inicializa/reinicia a matriz do jogo
    int i,j;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            visual[i][j]='*';
        }
    }
    for(i=0;i<3;i++){
        for(j=0;j<7;j++){
            visual[i+2][j]='1';
        }
    }
    for(i=0;i<7;i++){
        for(j=0;j<3;j++){
            visual[i][j+2]='1';
        }
    }
    visual[3][3]='0';
}
void _instrucoes(){                                                    //mostra as instrucoes do jogo na tela
    system("cls");
    printf("        ___               _                                      \n       |_ _|  _ _    ___ | |_   _ _   _  _   __   ___   ___   ___\n        | |  | ' \\  (_-< |  _| | '_| | || | / _| / _ \\ / -_) (_-<\n       |___| |_||_| /__/  \\__| |_|    \\_,_| \\__| \\___/ \\___| /__/\n");
    printf("\n\n   (ATENCAO) ESSE TUTORIAL SO APARECERA UMA VEZ, LEIA-0 ATENTAMENTE!\n\n  O jogo consiste em um tabuleiro com 32 pecas e o objetivo e restar \napenas uma ao final do jogo. Um movimento valido consiste em pegar uma \npeca e faze-la \"saltar\" sobre outra peca, sempre na horizontal ou na \nvertical, terminando em um espaco vazio. A peca que foi \"saltada\" sera \nautomaticamente retirada do tabuleiro. \n  O simbolo '*' indica uma posicao que nao forma o tabuleiro. O simbolo\n'1' indica uma posicao com peca. O simbolo '0' indica uma posicao sem \npeca.\n  Um exemplo de movimento valido: movimentacao da peca da posicao 6 4 \n(linha 6 e coluna 4) para a posicao 4 4 (linha 4 e coluna 4). Digita-se\ndesta forma, apenas com um espaco entre as coordenadas x e y, seguido \nda tecla enter. Se houver apenas um movimento possivel ele sera feito \nautomaticamente. O jogo acaba quando restar 1 peça no tabuleiro.\n\nSe desejar sair no meio da partida, digite a posicao [0 0].\n\n- Bom jogo! :)\n\n\n\n\n\n\n\n");
    system("pause");
}
int main(int argc,char *argv[]){                                       //int main
    int i,j,a=0,jogadas[1]={0},prob,op_menu,n=0,op_v[4],op,cor_v[2],partidas[4]={0,0,0,0},cont=0;
    char visual[7][7];
    double inicio,fim,dif;
    _defaultOpcoes(op_v);
    _defaultCores(cor_v);
    _inicializaJogo(visual);
    printf("|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|      Ajuste as bordas da janela para uma melhor experiencia!        |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n|                                                                     |\n");
    system("pause");
    system("cls");
    printf("                      #####     #####     #####                       \n ##   ##   ##   ##   ##   ##   ##   ##   ##   ##   ##   ##   ##   ##  \n  ## ##     ## ##   ##     ## ##     ## ##     ##   ## ##     ## ##   \n######### ######### ##     ## ##     ## ##     ## ######### ######### \n  ## ##     ## ##   ##     ## ##     ## ##     ##   ## ##     ## ##   \n ##   ##   ##   ##   ##   ##   ##   ##   ##   ##   ##   ##   ##   ##  \n                      #####     #####     #####                       \n         ::::::::::::::::::::::::::::::::::::::::::::::::::::         \n  #####  '########::'########::'######::'########::::'###::::  #####  \n ##   ##  ##.... ##: ##.....::'##... ##:... ##..::::'## ##::: ##   ## \n##     ## ##:::: ##: ##::::::: ##:::..::::: ##:::::'##:. ##::##     ##\n##     ## ########:: ######:::. ######::::: ##::::'##:::. ##:##     ##\n##     ## ##.. ##::: ##...:::::..... ##:::: ##:::: #########:##     ##  \n ##   ##  ##::. ##:: ##:::::::'##::: ##:::: ##:::: ##.... ##: ##   ##\n  #####	  ##:::. ##: ########:. ######::::: ##:::: ##:::: ##:  #####\n         ..:::::..::........:::......::::::..:::::..:::::..::\n  #####     #####     #####   :::'##::::   #####     #####     #####\n ##   ##   ##   ##   ##   ##  :'####::::  ##   ##   ##   ##   ##   ##\n##     ## ##     ## ##     ## :.. ##:::: ##     ## ##     ## ##     ##\n##     ## ##     ## ##     ## ::: ##:::: ##     ## ##     ## ##     ##\n##     ## ##     ## ##     ## ::: ##:::: ##     ## ##     ## ##     ##\n ##   ##   ##   ##   ##   ##  ::: ##::::  ##   ##   ##   ##   ##   ##\n  #####     #####     #####   :'######::   #####     #####     ##### \n 			      :......:::\n  #####     #####     #####     #####      #####     #####     #####   \n ##   ##   ##   ##   ##   ##   ##   ##    ##   ##   ##   ##   ##   ##  \n##     ## ##     ## ##     ## ##     ##  ##     ## ##     ## ##     ## \n##     ## ##     ## ##     ## ##     ##  ##     ## ##     ## ##     ## \n##     ## ##     ## ##     ## ##     ##  ##     ## ##     ## ##     ## \n ##   ##   ##   ##   ##   ##   ##   ##    ##   ##   ##   ##   ##   ##  \n  #####     #####     #####     #####      #####     #####     #####   \n\n");
    system("pause");
    system("cls");
    _waitForIt(1);
    printf("\n    ______          _    __                                            \n   / ____/  ___    (_)  / /_  ____            ____   ____    _____   _ \n  / /_     / _ \\  / /  / __/ / __ \\          / __ \\ / __ \\  / ___/  (_)\n / __/    /  __/ / /  / /_  / /_/ /         / /_/ // /_/ / / /     _   \n/_/       \\___/ /_/   \\__/  \\____/         / .___/ \\____/ /_/     (_)  \n                                          /_/                          ");
    printf("\n\n\n\n\n\n\n\n\n\n\n     \\                  |               \n    _ \\     __ \\     _` |    __|    _ \\ \n   ___ \\    |   |   (   |   |       __/ \n _/    _\\  _|  _|  \\__,_|  _|     \\___| \n\n     \\                                     |           \n    _ \\     |   |    _` |   |   |    __|   __|    _ \\  \n   ___ \\    |   |   (   |   |   |  \\__ \\   |     (   | \n _/    _\\  \\__,_|  \\__, |  \\__,_|  ____/  \\__|  \\___/  \n                   |___/                               ");
    _waitForIt(1);
    do{    //menu do jogo
        system("cls");
        printf("\n\n\n\n                /'\\_/`\\                              \n               /\\      \\      __     ___     __  __  \n               \\ \\ \\__\\ \\   /'__`\\ /' _ `\\  /\\ \\/\\ \\ \n                \\ \\ \\_/\\ \\ /\\  __/ /\\ \\/\\ \\ \\ \\ \\_\\ \\\n                 \\ \\_\\\\ \\_\\\\ \\____\\\\ \\_\\ \\_\\ \\ \\____/\n                  \\/_/ \\/_/ \\/____/ \\/_/\\/_/  \\/___/ \n\n");
        if(n==(partidas[0]+partidas[2])){
            printf("\n\n\n                           1.  Novo Jogo .1\n                           2.   Opcoes   .2\n                           3.  Historia  .3\n                           4.  Creditos  .4\n                           5.    Sair    .5\n\n\n\n\n                          Digite uma opcao: ");
            n=(partidas[0]+partidas[2]);
        }
        else{
            printf("\n\n\n                           0.  Continuar .0\n                           1.  Novo Jogo .1\n                           2.   Opcoes   .2\n                           3.  Historia  .3\n                           4.  Creditos  .4\n                           5.    Sair    .5\n\n\n\n\n                          Digite uma opcao: ");
            if(n-(partidas[0]+partidas[2])==2){
                n=(partidas[0]+partidas[2])+1;
            }
        }
        scanf("%d",&op_menu);
        switch(op_menu){
            case 0:     //continuar o jogo
                _jogo(visual,op_v,cor_v,partidas,0,jogadas);
                continue;
            case 1:     //novo jogo
                if(n==0){
                    _instrucoes();
                }
                n++;
                _inicializaJogo(visual);
                _jogo(visual,op_v,cor_v,partidas,1,jogadas);
                continue;
            case 2:     //submenu de opcoes
                do{
                    do{
                        system("cls");
                        printf("                   ___                               \n                  / _ \\   _ __   __   ___   ___   ___\n                 | (_) | | '_ \\ / _| / _ \\ / -_) (_-<\n                  \\___/  | .__/ \\__| \\___/ \\___| /__/\n                         |_|                          \n");
                        printf("\n\n                 1. Jogadas Automaticas...........");
                        _imprimeOpcoes(op_v,0);
                        printf("\n                 2. Mostrar progresso.............");
                        _imprimeOpcoes(op_v,1);
                        printf("\n                 3. Num. de jogadas possiveis.....");
                        _imprimeOpcoes(op_v,2);
                        printf("\n                 4. Mostrar pontos................");
                        _imprimeOpcoes(op_v,3);
                        printf("\n                 5. Cor do tabuleiro......");
                        _imprimeCor(cor_v,1);
                        printf("\n                 6. Cor das coordenadas/inf");
                        _imprimeCor(cor_v,0);
                        printf("\n                 7. Default");
                        printf("\n                 0. Voltar\n");
                        printf("\n\n               Digite o numero da opcao que quer mudar: ");
                        scanf("%d",&op);
                    }while(op!=0&&op!=1&&op!=2&&op!=3&&op!=4&&op!=5&&op!=6&&op!=7);
                    if(op>0&&op<5){
                        op_v[op-1]=_mudaOp(op_v[op-1]);
                    }
                    else{
                        if(op==5){
                            cor_v[1]=_mudaCor(cor_v,1);
                        }
                        else{
                            if(op==6){
                                cor_v[0]=_mudaCor(cor_v,0);
                            }
                            else{
                                if(op==7){
                                    _defaultOpcoes(op_v);
                                    _defaultCores(cor_v);
                                }
                            }
                        }

                    }
                }while(op!=0);
                continue;
            case 3:     //historia
                system("cls");
                printf("          _  _   _        _                 _        \n         | || | (_)  ___ | |_   ___   _ _  (_)  __ _ \n         | __ | | | (_-< |  _| / _ \\ | '_| | | / _` |\n         |_||_| |_| /__/  \\__| \\___/ |_|   |_| \\__,_|\n\n\n");
                printf("    O Resta 1, tambem conhecido como Solitarie (solitario), possui\ndiversas versoes da historia de sua origem. A mais comum delas, ainda\nque nao confirmada, remete ao frances Pellison, que teria vivido no\nseculo 18. Encarcerado pelo rei Luis XIV na Bastilha, o nobre teria\ninventado o jogo como um alivio para seu tedio.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                system("pause");
                continue;
            case 4:     //creditos
                system("cls");
                printf("          ___                  _   _   _              \n         / __|  _ _   ___   __| | (_) | |_   ___   ___\n        | (__  | '_| / -_) / _` | | | |  _| / _ \\ (_-<\n         \\___| |_|   \\___| \\__,_| |_|  \\__| \\___/ /__/\n\n\n");
                printf("  O trabalho, proposto em 10/04/2018, consiste em implementar o jogo \n\"Resta 1\" na linguagem C. Codigo escrito pelo aluno Andre Augusto Cesar\ndo Nascimento no primeiro periodo de Engenharia de Computacao (UNIFEI).\nInfluencias e referencias em jogos de SNES e jogos antigos de celular.\nFontes diferenciadas foram retiradas do site www.messletters.com e\nadaptadas pelo autor do codigo.\n\nProfessores:\n- Thatyana de Faria Piola Seraphim\n- Rafael Moreira\n\nHistoria do jogo retirada de:\n-https://super.abril.com.br/comportamento/jogo-resta-um/\n-http://educarepersone.blogspot.com/2010/11/didatica-da-matematica-jogo-resta-um.html\n\n\n\n\n\n\n\n\n\n\n\n");
                system("pause");
                continue;
            case 5:     //sair
                break;
            default:
                continue;
        }
        break;
    }while(a==0);
    system("cls");      //tela final
    printf("\n\n\n\n\n\n\n\n\n\n                       Obrigado por jogar! :)\n\n");
    printf("         Nesta sessao: (%d)Ganhas (%d)Abandonadas  (%d)Perdidas\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                       ©Andre Nascimento\n                 https://github.com/AndreNasci\n",partidas[0],partidas[1],partidas[2]);
return 0;
}
