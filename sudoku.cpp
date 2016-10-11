
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "BlackGPIO.h"
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <cstdlib>

#define LINHAS 9
#define COLUNAS 9

using namespace std;
using namespace BlackLib;

int matriz[LINHAS][COLUNAS];
int verificacaoLinha[COLUNAS];
int verificacaoColuna[LINHAS];


void iniciar() {
    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS; j++) {
            matriz[i][j]  = 0;
        }
    }
}

bool verificarLinha(int linha) {
    for(int i = 0; i < COLUNAS; i++) {
        verificacaoLinha[i] = 0;
    }
    
    for(int i = 0; i < COLUNAS; i++) {
        if(matriz[linha][i] > 0) {
            if(verificacaoLinha[matriz[linha][i]] == 0) {
                verificacaoLinha[matriz[linha][i]] = matriz[linha][i];
            }
            else {
                return false;
            }
        }
    }
    
    return true;
}

bool verificarColuna(int coluna) {
    for(int i = 0; i < LINHAS; i++) {
        verificacaoColuna[i] = 0;
    }
    
    for(int i = 0; i < LINHAS; i++) {
        if(matriz[i][coluna] > 0) {
            if(verificacaoColuna[matriz[i][coluna]] == 0) {
                verificacaoColuna[matriz[i][coluna]] = matriz[i][coluna];
            }
            else {
                return false;
            }
        }
    }
    
    return true;
}
    
void imprimir() {
int markcol1=0, markcol2=0, marklin1=0, marklin2=0;;
    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS; j++) {
            if(matriz[i][j] > 0) 
                std::cout << matriz[i][j];
            else
                std::cout << " ";
            std::cout << "|";  
            if(markcol1++ ==(COLUNAS/2)-2){
			std::cout << ":|";
			
			}  
			if(markcol2++ ==(COLUNAS/2)+1){
			std::cout << ":|";
			
			} 
			
        }
        std::cout << std::endl;
        markcol1=0; markcol2=0;
		if(marklin1++ ==(LINHAS/2)-2){
			std::cout << "======================\n";
			
		}  
		if(marklin2++ ==(LINHAS/2)+1){
		std::cout << "======================\n";
		
		} 	
    }    	

    
    for(int i = 0; i < LINHAS; i++){
        if(!verificarLinha(i)) {
            std:: cout << "Linha " << i << " INCORRETA" << std::endl;
        }    
    }
    
    for(int i = 0; i < COLUNAS; i++){
        if(!verificarColuna(i)) {
            std:: cout << "Coluna " << i << " INCORRETA" << std::endl;
        }    
    }
}

bool verificaValoresIguais(int linha, int coluna, int valor){
	int i, c=coluna, l=linha;
	for(i=0;i<linha;i++){
		if(matriz[c][i]==valor || matriz[i][l]==valor){
				return true;
			}
		
		}
	return false;
}

void insereValor(int linha, int coluna){
	int  valor;
	std::cout << "Informe o valor: ";
    std::cin >> valor;
    if (valor<=COLUNAS){
	matriz[linha][coluna] = valor;	
	}
    else{
		cout << "valor inválido"<<endl;
		insereValor(linha,coluna);
		}
		
}


void jogar() {
    int linha, coluna;
    
    std::cout << "Informe a linha: ";
    std::cin >> linha;
    
    std::cout << "Informe a coluna: ";
    std::cin >> coluna;
    
    insereValor(linha,coluna);
   

}
void detectarAlarme(int sig){
	cout<<"Terminou o jogo"<<endl;
	kill(getpid(),SIGKILL);
	
}
void continuaJogo(int sig){

}

int main(int argc, char *argv[])
{
	BlackGPIO   ledR(GPIO_51,output, SecureMode);   
    BlackGPIO   ledG(GPIO_31,output, SecureMode);   
    BlackGPIO   ledB(GPIO_60,output, SecureMode);
	pid_t pid;
	cout<<"INICIO DO PROGRAMA\n"<<endl;
	cout<<"-----------------------\n"<<endl;
	pid = fork();
	
	
	/*instalar função para receber sinal*/
	signal(SIGALRM,detectarAlarme);
	
	switch(pid){
		case -1:
			printf("Erro!");
		break;
		case 1: /*Processo Filho reponsável pelo jogo*/			
				printf("Eu sou o filho PID %d | PPID %d",getpid(),getppid());
				
				iniciar();
    
				imprimir();
				
				while(true) {
					std::system("clear");
					imprimir();
					jogar();
				}	
		break;
		default:/*Processo Pai responsável pelo tempo do jogo*/
			ledB.setValue(low);
			ledG.setValue(low);
			ledR.setValue(low);
			unsigned int tempoRestanteAlarme;
			tempoRestanteAlarme=alarm(240);
				printf("Eu sou o paiPID %d | PPID %d",getpid(),getppid());
				if(tempoRestanteAlarme<80){
					cout<<"led verde acendeu"<<endl;
					ledG.setValue(high);
				}
				if(tempoRestanteAlarme>=80 || tempoRestanteAlarme <160){
					cout<<"led azul acendeu"<<endl;
					ledG.setValue(low);
					ledB.setValue(high);
				}
				if(tempoRestanteAlarme>=160 || tempoRestanteAlarme>0){
					cout<<"led vermelho acendeu"<<endl;
					ledB.setValue(low);
					ledG.setValue(low);
					ledR.setValue(high);
					if(tempoRestanteAlarme==230){
						while(1){
							cout<<"led vermelho ta piscando"<<endl;
							ledR.setValue(high);
							sleep(1);
							ledR.setValue(low);
						}
					}
				}
				if(tempoRestanteAlarme == 0){
						kill(pid,SIGUSR1);
						exit(1);
					}			
		break;

	}	
	return 0;
}

