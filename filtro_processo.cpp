#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fstream>
#include <string>

using namespace std;

float valores[1001];

void filtrar(int N){
    float filtrados[1001];
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
    file.open("filtrados"+to_string(N)+".txt", fstream::in | fstream::out | fstream::app);
    for (int i = 0; i < 1001; ++i)
    {
        file << filtrados[i];
        file << "\n";
    }
}

int main (void) {
    string s;
    ifstream file("input.txt");
    
    if(file.is_open()){
        int i = 0;
        while(!file.eof()){
            file >> s;//valor da primeira coluna
            file >> s;//valor da segunda coluna
            file >> s;//valor da terceira coluna
            valores[i] = stof(s);
            cout << i << " " << valores[i] << endl;
            i++;
        }
    }
    
    file.close();//fechar arquivo
    
    pid_t pid1, pid2, pid3, pid4;//pids de processos que serão criados
    
    if ((pid1 = fork()) == 0) {//-------------------------FORK 1
        filtrar(3);
    } else if (pid1 < 0) {
        perror("fork 1 error");
    } else {
        if ((pid2 = fork()) == 0) {//---------------------FORK 2
            filtrar(6);
        } else if (pid2 < 0) {
            perror("fork 2 error");
        } else {
            if ((pid3 = fork()) == 0) {//-----------------FORK 3
                filtrar(10);
            } else if (pid1 < 0) {
                perror("fork 3 error");
            } else {
                if ((pid4 = fork()) == 0) {//-------------FORK 4
                    filtrar(20);
                } else if (pid4 < 0) {
                    perror("fork 4 error");
                } else {
                }
            }
        }
    }
    wait(NULL);
    return EXIT_FAILURE;
}
