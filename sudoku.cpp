
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


using namespace std;
using namespace BlackLib;

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

