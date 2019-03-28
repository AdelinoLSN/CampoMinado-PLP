#include "campo.cpp"
#include "util.cpp"
#include "time.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "ia.cpp"
using namespace std;

class Jogo{
	public:
		void novoJogo(int nivel, int tamanho){
			Util u;
			IA ia;
			int** matrizBombas = alocarBombas(tamanho);
			int** matrizOpen = u.criarMatriz(tamanho);
			int** matrizN2 = u.criarMatriz(tamanho);
			float** matrizN3 = u.criarMatrizF(tamanho);
			Campo c;
			c.tamanho = tamanho; 
			c.matrizBombas = matrizBombas;
			c.matrizOpen = matrizOpen;
			bool dimas = true;
			int continua = 1;
			int coluna,linha;
			while(continua == 1){
				if(dimas == true){ 
					u.printMatriz(c);
					cout << "Digite a linha:\n";
					cin >> linha;
					cout << "Digite a coluna:\n";
					cin >> coluna;
					linha--;
					coluna--;
					if(linha>=0 && linha < c.tamanho && coluna >= 0 && coluna<tamanho && c.matrizOpen[linha][coluna] == 0){
						continua = jogar(c,linha,coluna);
						dimas = false;	
					}else{
						dimas = true;
					}
				}else{
					u.printMatriz(c);											
					if(nivel==1){
						continua = jogarBotN1(c);
					}else if(nivel==2){
						matrizN2 = ia.nivel2(matrizN2,c);
						continua = jogarBotN2(c,matrizN2);
					}else{
						matrizN3 = ia.nivel3(matrizN3,c);
						//cout << "\n";
						//u.printMatrizF(matrizN3,c.tamanho);						
						continua = jogarBotN3(c,matrizN3);
					}
					dimas = true;
				}
				if(soRestaBombas(c)==true && continua==1){
					continua = 2;
					break;
				}
			}
			u.printMatrizFim(c);
			if(continua == 0){
				if(dimas == true){
					cout << "Voce ganhou!\n";
				}else{
					cout << "Voce perdeu!\n";
				}
			}else{
				cout << "Empate!\n";
			}
		}

		bool soRestaBombas(Campo c){
			int tam = c.tamanho;
			int i, j;
			for(i=0;i<tam;i++){
				for(j=0;j<tam;j++){
					if(c.matrizOpen[i][j] == 0 && c.matrizBombas[i][j] != -1){
						return false;
					}
				}
			}
			return true;
		}

		int jogarBotN1(Campo c){
			srand((unsigned)time(NULL));
			int i = rand()%c.tamanho;
			int j = rand()%c.tamanho;
			while(c.matrizOpen[i][j]==1){
				i = rand()%c.tamanho;
				j = rand()%c.tamanho;
			}
			cout << "LINHA: " << i+1 << " COLUNA: " << j+1 <<"\n";
			return jogar(c,i,j);
		}

		int jogarBotN2(Campo c, int** matrizN2){
			srand((unsigned)time(NULL));
			int i = rand()%c.tamanho;
			int j = rand()%c.tamanho;
			while(c.matrizOpen[i][j]==1 || matrizN2[i][j] == 1){
				i = rand()%c.tamanho;
				j = rand()%c.tamanho;
			}
			cout << "LINHA: " << i+1 << " COLUNA: " << j+1 <<"\n";
			return jogar(c,i,j);
		}

		int jogarBotN3(Campo c, float** mCerteza){
			srand((unsigned)time(NULL));
			int i,j;
			float min = menor(mCerteza,c);
			if(min==0){
				for(i=0;i<c.tamanho;i++){
					for(j=0;j<c.tamanho;j++){
						if(mCerteza[i][j] == 0 and c.matrizOpen[i][j] == 0){
							cout << "LINHA: " << i+1 << " COLUNA: " << j+1 <<"\n";
							int retorno = jogar(c,i,j);
							return retorno;					
						}
					}
				}
			}else{
				i = rand()%c.tamanho;
				j = rand()%c.tamanho;
				while(mCerteza[i][j] != min or c.matrizOpen[i][j]==1){
					i = rand()%c.tamanho;
					j = rand()%c.tamanho;
				}
				cout << "LINHA: " << i+1 << " COLUNA: " << j+1 <<"\n";
				int retorno = jogar(c,i,j);
				return retorno;
			}
		}

		float menor(float** m, Campo c){
			float min = 10.0;
			int t = c.tamanho;
			int i, j;
			for(i=0;i<t;i++){
				for(j=0;j<t;j++){
					if(m[i][j] < min && c.matrizOpen[i][j] == 0){
						min=m[i][j];
					}
				}
			}
			return min;
		}

		int jogar(Campo c, int linha,int coluna){
			if(ehBomba(c.matrizBombas,c.tamanho,linha,coluna) == 1){
				c.matrizOpen[linha][coluna] = 1;
				return 0;
			}else{
				abrirRecursivo(c,linha,coluna);
				return 1;
			}
		}

		void abrirRecursivo(Campo c, int linha, int coluna){
			if(linha >= 0 && linha < c.tamanho && coluna >= 0 && coluna < c.tamanho){
				if(c.matrizOpen[linha][coluna]==0){
					c.matrizOpen[linha][coluna]=1;
					if(c.matrizBombas[linha][coluna]==0){
						abrirRecursivo(c,linha+1,coluna);
						abrirRecursivo(c,linha+1,coluna+1);
						abrirRecursivo(c,linha+1,coluna-1);
						abrirRecursivo(c,linha-1,coluna);
						abrirRecursivo(c,linha-1,coluna+1);
						abrirRecursivo(c,linha-1,coluna-1);
						abrirRecursivo(c,linha,coluna+1);
						abrirRecursivo(c,linha,coluna-1);
					}
				}
			}
		}

		int** alocarBombas(int tamanho){
			Util u;
			int** m = u.criarMatriz(tamanho);
			int quantidade = (tamanho*tamanho)*0.15;
			srand((unsigned)time(NULL));
		    while(quantidade!=0){ 
		        int linha = rand()%tamanho;
		        int coluna = rand()%tamanho;
		        if(m[linha][coluna]==-1){
		            while(m[linha][coluna]==-1){
		                linha = rand()%tamanho;
		                coluna = rand()%tamanho;
		            }
		        }else{
		            m[linha][coluna] = -1;
		            quantidade--;
		        }
		    }
		    return vizinhos(m,tamanho);
		}

		int** vizinhos(int** m, int tamanho){ 
			int i;
		    int j;
		    for(i=0;i<tamanho;i++){
		        for(j=0;j<tamanho;j++){
		            if(m[i][j]!=-1){
		                m[i][j]=ehBomba(m,tamanho,i+1,j) + ehBomba(m,tamanho,i+1,j+1) +
		                		ehBomba(m,tamanho,i+1,j-1) + ehBomba(m,tamanho,i,j+1) +
		                		ehBomba(m,tamanho,i,j-1) + ehBomba(m,tamanho,i-1,j) +
		                		ehBomba(m,tamanho,i-1,j+1) + ehBomba(m,tamanho,i-1,j-1);
		            }
		        }
		    }
		    return m;
		}

		int ehBomba(int** m, int tam, int line, int col){
			if(line>=0 && line<tam && col>= 0 && col < tam){
				if(m[line][col] == -1){
					return 1;
				}else{
					return 0;
				}
			}
			return 0;
		}
};