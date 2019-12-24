#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <vector>


//Algoritimo em c++
//Jaime Dantas - Sistemas Operacionais

//variaveis globais
std::vector<float> sinal_entrada;
//leitura e escrita de arquivos
//Arquivos de saida
std::ofstream saida_1("saida_1.txt");
std::ofstream saida_2("saida_2.txt");
std::ofstream saida_3("saida_3.txt");
std::ofstream saida_4("saida_4.txt");


//funcao do filho 
void doFiltering(int _N){
	std::vector<float> saida;
	//primeiros valores
	for (int i = 0; i<=_N-1; i++){
		saida.push_back(sinal_entrada[i]);
		//saida[i] = sinal_entrada[i];
	}
	for(int i = _N-1; i < sinal_entrada.size(); i++){
		saida.push_back(sinal_entrada[i]);//primeiro termo
		//saida[i] = sinal_entrada[i];
		for (int j = i-1; j != i-_N; j--){
			saida[i] = saida[i] + sinal_entrada[j];
		}
		saida[i] = saida[i]/_N;
	}
	//GRAVA NOS ARQUIVOS
	if(_N==3){
		for(int i=0; i<sinal_entrada.size(); i++){
			saida_1<<saida[i]<<"\n";
		}
		saida_1.close();
	}		
	else if(_N==6){
		for(int i=0; i<sinal_entrada.size(); i++){
			saida_2<<saida[i]<<"\n";
		}
		saida_2.close();
	}		
	else if(_N==10){
		for(int i=0; i<sinal_entrada.size(); i++){
			saida_3<<saida[i]<<"\n";
		}
		saida_3.close();
	}		
	else if(_N==20){
		for(int i=0; i<sinal_entrada.size(); i++){
			saida_4<<saida[i]<<"\n";
		}
		saida_4.close();
	}		

	//std::cout<<"Filtragem Finalizada!\n";
	//sleep(5);
}

int main (int argc, char *argv[]){
	//as entradas e saidas serao armazenadas em um vetor e em arquivos
	float row_1, row_2, row_3;
	int N;
	
	//Arquivos de entrada
	std::ifstream entrada("input.dat");
	
	if (entrada.is_open() == true){
		while(!entrada.eof()){
			entrada>>row_1>>row_2>>row_3;//vai armezenar os valores das colunas
			sinal_entrada.push_back(row_3);//somente a coluna 3 contem os valores q queremos
		}
		//std::cout<<"Primeiro valor: "<<sinal_entrada.front()<<std::endl;
		std::cout<<"Arquvo aberto com sucesso!\n";
	}
	entrada.close();//fechar o arquivo de entrada

	std::cout<<"Processamento iniciado!\n";
	//mostra a id do processo pai
	std::cout<<"Eu sou o processo pai n = "<<(int)getpid()<<std::endl;
	//cria os processos filhos

	//******************* FILHO 1 *********************
	pid_t filho_1 = fork();
	N = 3;
	//caso processo nao seja criado
	if (filho_1 < 0){
		std::cout<<"Erro na criacao do processo filho 1!\n";
	}
	//caso seja o filho
	else if(filho_1 == 0){
		std::cout<<"Sou o processo filho n = "<<(int)getpid()<<std::endl;
		//execucao do processo filho
		doFiltering(N);//funcao q contem o codigo de execucao do filho com n = 4
		//sleep(5);
		std::cout<<"Filho 1 termindando!\n";
		exit(0);//return valor
	}
	//wait(NULL);
	//******************* FILHO 2 *********************
	pid_t filho_2 = fork();
	N = 6;
	//caso processo nao seja criado
	if (filho_2 < 0){
		std::cout<<"Erro na criacao do processo filho 2!\n";
	}
	//caso seja o filho
	else if(filho_2 == 0){
		std::cout<<"Sou o processo filho n = "<<(int)getpid()<<std::endl;
		//execucao do processo filho
		doFiltering(N);//funcao q contem o codigo de execucao do filho com n = 4
		//sleep(5);
	std::cout<<"Filho 2 termindando!\n";
		exit(0);//return valor
	}
	//wait(NULL);

	//******************* FILHO 3 *********************
	pid_t filho_3 = fork();
	N = 10;
	//caso processo nao seja criado
	if (filho_3 < 0){
		std::cout<<"Erro na criacao do processo filho 3!\n";
	}
	//caso seja o filho
	else if(filho_3 == 0){
		std::cout<<"Sou o processo filho n = "<<(int)getpid()<<std::endl;
		//execucao do processo filho
		doFiltering(N);//funcao q contem o codigo de execucao do filho com n = 4
		//sleep(5);
		std::cout<<"Filho 3 termindando!\n";
		exit(0);//return valor
	}
	//wait(NULL);

	//******************* FILHO 4 *********************
	pid_t filho_4 = fork();
	N = 20;
	//caso processo nao seja criado
	if (filho_4 < 0){
		std::cout<<"Erro na criacao do processo filho 4!\n";
	}
	//caso seja o filho
	else if(filho_4 == 0){
		std::cout<<"Sou o processo filho n = "<<(int)getpid()<<std::endl;
		//execucao do processo filho
		doFiltering(N);//funcao q contem o codigo de execucao do filho com n = 4
		//sleep(5);
		std::cout<<"Filho 4 termindando!\n";
		exit(0);//return valor
	}
	//vai fechar os precessos filhos quando eles terminares
	wait(NULL);
	//fecha os arquivos abertos
	return 0;
}
