#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "jogo.cpp"
using namespace std;
 
int main(){
    int nivel = -1;
    Jogo j;
    int tamanho1 = 6;
    int tamanho2 = 9;
    int tamanho3 = 16;
    cout << "Selecione a dificuldade:\n1 - Nivel 1 (6x6 casas) 5 bombas\n2 - Nivel 2 (9x9) 12 bombas\n3 - Nivel 3 (16x16) 38 bombas\n";
    cin >> nivel;
    while(nivel != 1 and nivel != 2 && nivel != 3){
        cout << "Insira um valor entre 1 e 3\n";
        cout << "Selecione a dificuldade:\n1 - Nivel 1 (4x4 casas)\n2 - Nivel 2 (7x7)\n3 - Nivel 3 (10x10)\n";
        cin >> nivel;
    }
    if(nivel == 1){
        j.novoJogo(nivel,tamanho1);
    }else if(nivel == 2){
        j.novoJogo(nivel,tamanho2);
    }else{
        j.novoJogo(nivel,tamanho3);
    }   
}
