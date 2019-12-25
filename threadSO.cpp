#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <pthread.h>
#include <array>
#include <chrono>
#include <thread>
#include <chrono>


//Algoritimo em c++ Thread
//Jaime Dantas - Sistemas Operacionais

//variaveis globais
std::vector<float> sinal_entrada;
std::vector<float> saida_11;
std::vector<float> saida_22;
std::vector<float> saida_33;
std::vector<float> saida_44;

//std::array<std::array<float, 1000>, 4> sinal_saida;

//_float teste[1000][4];
//leitura e escrita de arquivos
//Arquivos de saida
std::ofstream saida_TOTAL("saida_TOTAL.txt");

//O programa nao esta otimizado, foram criadas N funcoes para os N filhos.
//funcao dos filhos
void *doFiltering1(void * argumeto){
    long _N = (long) argumeto;
    std::cout<<"Executando funcao 1"<<std::endl;
    std::cout<<"N = "<<_N<<std::endl;
    //primeiros valores
    for (int i = 0; i<=_N-1; i++){
        saida_11.push_back(sinal_entrada[i]);
        //saida[i] = sinal_entrada[i];
    }
    for(int i = _N-1; i < sinal_entrada.size(); i++){
        saida_11.push_back(sinal_entrada[i]);//primeiro termo
        //saida[i] = sinal_entrada[i];
        for (int j = i-1; j != i-_N; j--){
            saida_11[i] = saida_11[i] + sinal_entrada[j];
        }
        saida_11[i] = saida_11[i]/_N;
    }
    std::cout<<"Thread 1 Finalizada!"<<std::endl;
    pthread_exit(0);
}
void *doFiltering2(void * argumeto){
    long _N = (long) argumeto;
    std::cout<<"Executando funcao 2"<<std::endl;
    std::cout<<"N = "<<_N<<std::endl;
    //primeiros valores
    for (int i = 0; i<=_N-1; i++){
        saida_22.push_back(sinal_entrada[i]);
        //saida[i] = sinal_entrada[i];
    }
    for(int i = _N-1; i < sinal_entrada.size(); i++){
        saida_22.push_back(sinal_entrada[i]);//primeiro termo
        //saida[i] = sinal_entrada[i];
        for (int j = i-1; j != i-_N; j--){
            saida_22[i] = saida_22[i] + sinal_entrada[j];
        }
        saida_22[i] = saida_22[i]/_N;
    }
    std::cout<<"Thread 2 Finalizada!"<<std::endl;
    
    pthread_exit(0);
}
void *doFiltering3(void * argumeto){
    long _N = (long) argumeto;
    std::cout<<"\nExecutando funcao 3"<<std::endl;
    std::cout<<"\nN = "<<_N<<std::endl;
    //primeiros valores
    for (int i = 0; i<=_N-1; i++){
        saida_33.push_back(sinal_entrada[i]);
        //saida[i] = sinal_entrada[i];
    }
    for(int i = _N-1; i < sinal_entrada.size(); i++){
        saida_33.push_back(sinal_entrada[i]);//primeiro termo
        //saida[i] = sinal_entrada[i];
        for (int j = i-1; j != i-_N; j--){
            saida_33[i] = saida_33[i] + sinal_entrada[j];
        }
        saida_33[i] = saida_33[i]/_N;
    }
    std::cout<<"Thread 3 Finalizada!"<<std::endl;
    
    pthread_exit(0);
}
void *doFiltering4(void * argumeto){
    long _N = (long) argumeto;
    std::cout<<"\nExecutando funcao 4"<<std::endl;
    std::cout<<"\nN = "<<_N<<std::endl;
    //primeiros valores
    for (int i = 0; i<=_N-1; i++){
        saida_44.push_back(sinal_entrada[i]);
        //saida[i] = sinal_entrada[i];
    }
    for(int i = _N-1; i < sinal_entrada.size(); i++){
        saida_44.push_back(sinal_entrada[i]);//primeiro termo
        //saida[i] = sinal_entrada[i];
        for (int j = i-1; j != i-_N; j--){
            saida_44[i] = saida_44[i] + sinal_entrada[j];
        }
        saida_44[i] = saida_44[i]/_N;
    }
    std::cout<<"Thread 4 Finalizada!"<<std::endl;
    
    pthread_exit(0);
}

int main(int argc, char *argv[]){
    //as entradas e saidas serao armazenadas em um vetor e em arquivos
    auto t1 = std::chrono::high_resolution_clock::now();
    
    float row_1, row_2, row_3;
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
    
    std::cout<<"Processamento de Thread iniciado!\n";
    
    //******************* THREAD 1 *********************
    //std::cout<<"THREAD 1 criada!!\n";
    //ID da thread
    pthread_t tid_1;
    //criacao de atributos
    //pthread_attr_t attr;
    //pthread_attr_init(&attr);
    long N=3;
    pthread_create(&tid_1, NULL, doFiltering1, (void *)N);//criacao de thread
    //******************* THREAD 2 *********************
    //std::cout<<"THREAD 2 criada!!\n";
    //ID da thread
    pthread_t tid_2;
    //criacao de atributos
    //pthread_attr_t attr;
    //pthread_attr_init(&attr);
    N=6;
    pthread_create(&tid_2, NULL, doFiltering2, (void *)N);//criacao de thread
    //******************* THREAD 3 *********************
    //std::cout<<"THREAD 3 criada!!\n";
    //ID da thread
    pthread_t tid_3;
    //criacao de atributos
    //pthread_attr_t attr;
    //pthread_attr_init(&attr);
    N=10;
    pthread_create(&tid_3, NULL, doFiltering3, (void *)N);//criacao de thread
    //******************* THREAD 4 *********************
    //std::cout<<"THREAD 4 criada!!\n";
    //ID da thread
    pthread_t tid_4;
    //criacao de atributos
    //pthread_attr_t attr;
    //pthread_attr_init(&attr);
    N=20;
    pthread_create(&tid_4, NULL, doFiltering4, (void *)N);//criacao de thread
    //espera thread acabar
    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);
    pthread_join(tid_3, NULL);
    pthread_join(tid_4, NULL);
    std::cout<<"Processamento terminado!\n";
    //salva em um arquivo
    for(int i=0; i<sinal_entrada.size(); i++){
        //saida_TOTAL<<saida_11[i]<<"\t"<<saida_22<<"\t"<<saida_33<<"\t"<<saida_44<<"\n";
        saida_TOTAL<<saida_11[i]<<"\t\t"<<saida_22[i]<<"\t\t"<<saida_33[i]<<"\t\t"<<saida_44[i]<<"\n";
    }
    saida_TOTAL.close();
    std::cout<<"Arquivo criado!\n";
    
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    
    std::cout <<"time: "<< duration;
    
    return 0;
}
