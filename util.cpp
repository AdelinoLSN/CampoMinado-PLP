#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
using namespace std;

class Util{
	public:
		int** criarMatriz(int tamanho){
			//cout << tamanho;
			int** m = new int*[tamanho];
		    int i; 
		    int j;
		    for(i=0;i<tamanho;i++){
		        m[i]=new int[tamanho];
		    }
		    for(i=0;i<tamanho;i++){
		        for(j=0;j<tamanho;j++){
		            m[i][j]=0;
		        }
		    }
		    return m;
		}

		float** criarMatrizF(int tamanho){
			float** m = new float*[tamanho];
		    int i; 
		    int j;
		    for(i=0;i<tamanho;i++){
		        m[i]=new float[i];
		    }
		    for(i=0;i<tamanho;i++){
		        for(j=0;j<tamanho;j++){
		            m[i][j]=-1.0;
		        }
		    }
		    return m;
		}

		void printMatriz(Campo c){
			cout << "\n";
			int tam = c.tamanho;
			int i, j;
			for(i=0;i<tam;i++){
				if(i+1 < 10){
					cout << "0"<< i+1 << " ";
				}
				else{
					cout << i+1 << " ";
				}
				for(j=0;j<tam;j++){
					//cout << j;
					if(c.matrizOpen[i][j] == 0){
						cout << " #";
					}else{
						cout << c.matrizBombas[i][j] << " ";
					}
				}
				cout << "\n";
			}
			cout<<"\n";
		}

		void printMatrizFim(Campo c){
			int tam = c.tamanho;
			int i, j;
			for(i=0;i<tam;i++){
				for(j=0;j<tam;j++){
					if(c.matrizBombas[i][j]==-1){
						cout << "X ";
					}else if(c.matrizOpen[i][j]==1 && c.matrizBombas[i][j]!=-1){
						cout << c.matrizBombas[i][j] << " ";
					}else if(c.matrizOpen[i][j]==0){
						cout << "# ";
					}
				}
				cout << "\n";
			}
			cout<<"\n";
		}

		void printMatrizF(float** m,int tam){
			int i, j;
			for(i=0;i<tam;i++){
				for(j=0;j<tam;j++){
					cerr << m[i][j] << " ";
				}
				cout << "\n";
			}
			cout<<"\n";
		}

		void printMatrizes(Campo c){
			int tam = c.tamanho;
			int i, j;
			for(i=0;i<tam;i++){
				for(j=0;j<tam;j++){
					if(c.matrizBombas[i][j]==-1){
						cout << "X ";
					}else{
						cout << c.matrizBombas[i][j] << " ";
					}
				}
				cout << "\n";
			}
		}

};