#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <pthread.h>

using namespace std;

#define NUM_THREADS     4

float valores[1001];

void *filtrar(void * num){
    float filtrados[1001];
    long N = (long) num;
    for (int i = 0; i < N+1; ++i){//para os primeiros N+1 elementos, que não serão afetados pelo filtro
        filtrados[i] = valores[i];
    }
    for (int i = N+1; i < 1001; ++i)//para todos os outros que serão filtrados
    {
        filtrados[i] = valores[i];//y(n) + ...
        for (int j = i-1; j != i-N-2; --j)
        {
            filtrados[i] += valores[j];//y(n-1) + y(n-2) + ... + y(n-N-1)
        }
        filtrados[i] /= N;//sum/N
    }
    fstream file;
    file.open("filtradosthread"+to_string(N)+".txt", fstream::in | fstream::out | fstream::app);
    for (int i = 0; i < 1001; ++i)
    {
        file << filtrados[i];
        file << "\n";
    }
    pthread_exit(NULL);//fechar thread quando terminar
}

int main ()
{
	string s;
    ifstream file("sinal_ruido.dat");
    if(file.is_open()){
        int i = 0;
        while(!file.eof()){
            file >> s;//valor da primeira coluna
            file >> s;//valor da segunda coluna
            file >> s;//valor da terceira coluna
            valores[i] = stof(s);
            i++;
        }
    }
    file.close();//fechar arquivo

	pthread_t threads[NUM_THREADS];
	int rc;
	long N[4] = {3,6,10,20};
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		rc  = pthread_create(&threads[i], NULL, filtrar, (void *)N[i]);
		if (rc){
	    	cout << "Erro:não foi possivel criar thread" << endl;
	    	exit(-1);
  		}
	}
  	pthread_exit(NULL);
}