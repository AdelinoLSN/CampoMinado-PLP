

class IA{
	public:
		int** nivel2(int** matriz, Campo c){
			int i, j;
			for(i=0;i<c.tamanho;i++){
				for(j=0;j<c.tamanho;j++){
					if(c.matrizOpen[i][j] == 1){
						if(c.matrizBombas[i][j] == vizinhoFechados(c,i,j)){
							if(estaFechado(c,i+1,j+1) == 1){
								matriz[i+1][j+1]=1;
							}
							if(estaFechado(c,i+1,j-1) == 1){
								matriz[i+1][j-1]=1;
							}
							if(estaFechado(c,i+1,j) == 1){
								matriz[i+1][j]=1;
							}
							if(estaFechado(c,i-1,j+1) == 1){
								matriz[i-1][j+1]=1;
							}
							if(estaFechado(c,i-1,j-1) == 1){
								matriz[i-1][j-1]=1;
							}
							if(estaFechado(c,i-1,j) == 1){
								matriz[i-1][j]=1;
							}
							if(estaFechado(c,i,j+1) == 1){
								matriz[i][j+1]=1;
							}
							if(estaFechado(c,i,j-1) == 1){
								matriz[i][j-1]=1;
							}
						}
					}
				}
			}
			return matriz;
		}

		int vizinhoFechados(Campo c, int i, int j){
			int saida;
			saida = estaFechado(c,i+1,j+1) + estaFechado(c,i-1,j+1) +
					estaFechado(c,i+1,j-1) + estaFechado(c,i-1,j-1) +
					estaFechado(c,i+1,j) + estaFechado(c,i-1,j) +
					estaFechado(c,i,j+1) + estaFechado(c,i,j-1);
			return saida;
		}

		int estaFechado(Campo c, int i, int j){
			if(i>=0 && i<c.tamanho && j>=0 && j<c.tamanho){
				if(c.matrizOpen[i][j] == 1){
					return 0;
				}else{
					return 1;
				}
			}return 0;
		}

		float** nivel3(float** m, Campo c){
			m = abertasMarcar(c,m);
			int quantBombasTotal = c.tamanho*c.tamanho*0.15;
			int i,j;
			for(i=0;i<c.tamanho; i++){
				for(j=0;j<c.tamanho; j++){
					if(m[i][j] == -1){
						m[i][j] = float(quantBombasTotal) / (c.tamanho*c.tamanho);
					}
				}
			}
			m = abertasMarcar(c,m);
			
			Util u;
			
			for(i=0;i<c.tamanho; i++){
				for(j=0;j<c.tamanho; j++){
					if(c.matrizOpen[i][j] == 1 && casasFechadasAoRedor(c,i,j) == c.matrizBombas[i][j]){
						m = saoBombasAoRedor(m,i,j,c.tamanho);
					}
				}
			}
			for(i=0;i<c.tamanho; i++){
				for(j=0;j<c.tamanho; j++){
					if(c.matrizOpen[i][j] == 0 && m[i][j] == 1){
						if(i>=0 && i<c.tamanho && j>=0 && j<c.tamanho){							
							if(i+1>=0 && i+1<c.tamanho && j+1>=0 && j+1<c.tamanho){
								if(c.matrizOpen[i+1][j+1]==1 && c.matrizBombas[i+1][j+1]==1){
									m = marcarNaoBombasAoRedor(m,i+1,j+1,c.tamanho,i,j);
								}
							}
							if(i+1>=0 && i+1<c.tamanho && j-1>=0 && j-1<c.tamanho){
								if(c.matrizOpen[i+1][j-1]==1 && c.matrizBombas[i+1][j-1]==1){
									m = marcarNaoBombasAoRedor(m,i+1,j-1,c.tamanho,i,j);
								}
							}
							if(i+1>=0 && i+1<c.tamanho && j>=0 && j<c.tamanho){
								if(c.matrizOpen[i+1][j]==1 && c.matrizBombas[i+1][j]==1){
									m = marcarNaoBombasAoRedor(m,i+1,j,c.tamanho,i,j);
								}
							}
							if(i-1>=0 && i-1<c.tamanho && j+1>=0 && j+1<c.tamanho){
								if(c.matrizOpen[i-1][j+1]==1 && c.matrizBombas[i-1][j+1]==1){
									m = marcarNaoBombasAoRedor(m,i-1,j+1,c.tamanho,i,j);
								}
							}
							if(i-1>=0 && i-1<c.tamanho && j-1>=0 && j-1<c.tamanho){
								if(c.matrizOpen[i-1][j-1]==1 && c.matrizBombas[i-1][j-1]==1){
									m = marcarNaoBombasAoRedor(m,i-1,j-1,c.tamanho,i,j);
								}
							}
							if(i-1>=0 && i-1<c.tamanho && j>=0 && j<c.tamanho){
								if(c.matrizOpen[i-1][j]==1 && c.matrizBombas[i-1][j]==1){
									m = marcarNaoBombasAoRedor(m,i-1,j,c.tamanho,i,j);
								}
							}
							if(i>=0 && i<c.tamanho && j+1>=0 && j+1<c.tamanho){
								if(c.matrizOpen[i][j+1]==1 && c.matrizBombas[i][j+1]==1){
									m = marcarNaoBombasAoRedor(m,i,j+1,c.tamanho,i,j);
								}
							}
							if(i>=0 && i<c.tamanho && j-1>=0 && j-1<c.tamanho){
								if(c.matrizOpen[i][j-1]==1 && c.matrizBombas[i][j-1]==1){
									m = marcarNaoBombasAoRedor(m,i,j-1,c.tamanho,i,j);
								}
							}												
						}
					}
				}
			}
			int bombasDesc = bombasDescobertas(m,c.tamanho);
			int casasSeguras = casasSegurasFunc(m,c.tamanho);			
			float probabilidadeBasica;
			probabilidadeBasica = float((quantBombasTotal-bombasDesc)) / float(casasFechadas(c)-casasSeguras);
			for(i=0;i<c.tamanho; i++){
				for(j=0;j<c.tamanho; j++){
					if(c.matrizOpen[i][j] == 0 && m[i][j] !=  0 && m[i][j] != 1){
						if(probabilidadeBasica > m[i][j]){
							m[i][j] = probabilidadeBasica;
						}
					}
				}
			}
			//Util u;
			for(i=0;i<c.tamanho;i++){
				for(j=0;j<c.tamanho;j++){
					if(c.matrizOpen[i][j]==1 && c.matrizBombas[i][j] > 1){
						m = marcarNovasProbabilidades(c,m,i,j);
					}
				}
			}
			m = abertasMarcar(c,m);
			return m;

		}

		int casasFechadasAoRedor(Campo c, int i, int j){
			int result = estaFechado(c,i+1,j+1) + estaFechado(c,i-1,j+1) +
					 	 estaFechado(c,i+1,j-1) + estaFechado(c,i-1,j-1) +
					 	 estaFechado(c,i+1,j) + estaFechado(c,i-1,j) +
					 	 estaFechado(c,i,j+1) + estaFechado(c,i,j-1);
			return result;
		}


		float** marcarNovasProbabilidades(Campo c, float** m, int i, int j){
			int vizBomba = vizinhosBomba(m,c.tamanho,i,j);
			int dividendo = (vizinhoFechados(c,i,j)-vizBomba-casasSegurasAoRedor(m,i,j,c.tamanho));
			if(dividendo > 0){
				float prob = float(c.matrizBombas[i][j]-vizBomba)/dividendo;
				if(i+1>=0 && i+1<c.tamanho && j+1>=0 && j+1<c.tamanho){
					if(prob > m[i+1][j+1]){
						m[i+1][j+1]=prob;
					}
				}
				if(i+1>=0 && i+1<c.tamanho && j-1>=0 && j-1<c.tamanho){
					if(prob > m[i+1][j-1]){
						m[i+1][j-1]=prob;
					}
				}
				if(i+1>=0 && i+1<c.tamanho && j>=0 && j<c.tamanho){
					if(prob > m[i+1][j]){
						m[i+1][j]=prob;
					}
				}
				if(i-1>=0 && i-1<c.tamanho && j+1>=0 && j+1<c.tamanho){
					if(prob > m[i-1][j+1]){
						m[i-1][j+1]=prob;
					}
				}
				if(i-1>=0 && i-1<c.tamanho && j-1>=0 && j-1<c.tamanho){
					if(prob > m[i-1][j-1]){
						m[i-1][j-1]=prob;
					}
				}
				if(i-1>=0 && i-1<c.tamanho && j>=0 && j<c.tamanho){
					if(prob > m[i-1][j]){
						m[i-1][j]=prob;
					}
				}
				if(i>=0 && i<c.tamanho && j+1>=0 && j+1<c.tamanho){
					if(prob > m[i][j+1]){
						m[i][j+1]=prob;
					}
				}
				if(i>=0 && i<c.tamanho && j-1>=0 && j-1<c.tamanho){
					if(prob > m[i][j]){
						m[i][j-1]=prob;
					}
				}
			}
			return m;
		}

		int casasSegurasAoRedor(float** m, int i, int j, int tamanho){
			int result = 0;
			if(i+1>=0 && i+1<tamanho && j+1>=0 && j+1<tamanho){
				if(m[i+1][j+1] == 0){
					result++;
				}
			}
			if(i+1>=0 && i+1<tamanho && j-1>=0 && j-1<tamanho){
				if(m[i+1][j-1] == 0){
					result++;
				}
			}
			if(i+1>=0 && i+1<tamanho && j>=0 && j<tamanho){
				if(m[i+1][j] == 0){
					result++;
				}
			}
			if(i-1>=0 && i-1<tamanho && j+1>=0 && j+1<tamanho){
				if(m[i-1][j+1] == 0){
					result++;
				}
			}
			if(i-1>=0 && i-1<tamanho && j-1>=0 && j-1<tamanho){
				if(m[i-1][j-1] == 0){
					result++;
				}
			}
			if(i-1>=0 && i-1<tamanho && j>=0 && j<tamanho){
				if(m[i-1][j] == 0){
					result++;
				}
			}
			if(i>=0 && i<tamanho && j+1>=0 && j+1<tamanho){
				if(m[i][j+1]==0){
					result++;
				}
			}
			if(i>=0 && i<tamanho && j-1>=0 && j-1<tamanho){
				if(m[i][j]==0){
					result++;
				}
			}
			return result;
		}

		int vizinhosBomba(float** m,int tamanho, int i, int j){
			int result = 0;
			if(i+1>=0 && i+1<tamanho && j+1>=0 && j+1<tamanho){
				if(m[i+1][j+1] == 1){
					result++;
				}
			}
			if(i+1>=0 && i+1<tamanho && j-1>=0 && j-1<tamanho){
				if(m[i+1][j-1] == 1){
					result++;
				}
			}
			if(i+1>=0 && i+1<tamanho && j>=0 && j<tamanho){
				if(m[i+1][j] == 1){
					result++;
				}
			}
			if(i-1>=0 && i-1<tamanho && j+1>=0 && j+1<tamanho){
				if(m[i-1][j+1] == 1){
					result++;
				}
			}
			if(i-1>=0 && i-1<tamanho && j-1>=0 && j-1<tamanho){
				if(m[i-1][j-1] == 1){
					result++;
				}
			}
			if(i-1>=0 && i-1<tamanho && j>=0 && j<tamanho){
				if(m[i-1][j] == 1){
					result++;
				}
			}
			if(i>=0 && i<tamanho && j+1>=0 && j+1<tamanho){
				if(m[i][j+1] == 1){
					result++;
				}
			}
			if(i>=0 && i<tamanho && j-1>=0 && j-1<tamanho){
				if(m[i][j-1] == 1){
					result++;
				}
			}
			return result;
		}

		float** abertasMarcar(Campo c, float** m){
			int i,j;
			for (i=0;i<c.tamanho;i++){
				for(j=0;j<c.tamanho; j++){
					if(c.matrizOpen[i][j]==1){
						m[i][j]=2;
					}
				}
			}
			return m;
		}

		float** marcarNaoBombasAoRedor(float** m, int i, int j, int t, int linicial, int cinicial){
			if(i+1>=0 && i+1<t && j+1 >= 0 && j+1<t && i+1 != linicial && cinicial != j+1){
				m[i+1][j+1] = 0;
			}
			if(i+1>=0 && i+1<t && j-1 >= 0 && j-1<t && i+1 != linicial && cinicial != j-1){
				m[i+1][j-1] = 0;
			}
			if(i+1>=0 && i+1<t && j >= 0 && j<t && i+1 != linicial && cinicial != j){
				m[i+1][j] = 0;
			}
			if(i-1>=0 && i-1<t && j+1 >= 0 && j+1<t && i-1 != linicial && cinicial != j+1){
				m[i-1][j+1] = 0;
			}
			if(i-1>=0 && i-1<t && j-1 >= 0 && j-1<t && i-1 != linicial && cinicial != j-1){
				m[i-1][j-1] = 0;
			}
			if(i-1>=0 && i-1<t && j >= 0 && j<t && i-1 != linicial && cinicial != j){
				m[i-1][j] = 0;
			}
			if(i>=0 && i<t && j+1 >= 0 && j-1<t && i != linicial && cinicial != j+1){
				m[i][j+1] = 0;
			}
			if(i>=0 && i<t && j-1 >= 0 && j-1<t && i != linicial && cinicial != j-1){
				m[i][j-1] = 0;
			}
			return m;
		}

		float** saoBombasAoRedor(float** m,int i, int j,int tamanho){
			if(i+1>=0 && i+1<tamanho && j>=0 && j<tamanho && m[i+1][j]!= 0 && m[i+1][j]!= 2){
				m[i+1][j] = 1.0;
			}if(i+1>=0 && i+1<tamanho && j+1>=0 && j+1<tamanho && m[i+1][j+1]!= 0 && m[i+1][j+1]!= 2){
				m[i+1][j+1] = 1.0;
			}if(i+1>=0 && i+1<tamanho && j-1>=0 && j-1<tamanho && m[i+1][j-1]!= 0 && m[i+1][j-1]!= 2){
				m[i+1][j-1] = 1.0;
			}if(i-1>=0 && i-1<tamanho && j>=0 && j<tamanho && m[i-1][j]!= 0 && m[i-1][j]!= 2){
				m[i-1][j] = 1.0;
			}if(i-1>=0 && i-1<tamanho && j+1>=0 && j+1<tamanho && m[i-1][j+1]!= 0 && m[i-1][j+1]!= 2){
				m[i-1][j+1] = 1.0;
			}if(i-1>=0 && i-1<tamanho && j-1>=0 && j-1<tamanho && m[i-1][j-1]!= 0 && m[i-1][j-1]!= 2){
				m[i-1][j-1] = 1.0;
			}if(i>=0 && i<tamanho && j+1>=0 && j+1<tamanho && m[i][j+1]!= 0 && m[i][j+1]!= 2){
				m[i][j+1] = 1.0;
			}if(i>=0 && i<tamanho && j-1>=0 && j-1<tamanho && m[i][j-1]!= 0 && m[i][j-1]!= 2){
				m[i][j-1] = 1.0;
			}
			return m;
		}

		int casasSegurasFunc(float** m, int t){
			int i, j;
			int result = 0;
			for(i=0;i<t;i++){
				for(j=0;j<t;j++){
					if(m[i][j] == 0){
						result++;
					}
				}
			}
			return result;
		}

		int bombasDescobertas(float** m, int t){
			int i, j;
			int result = 0;
			for(i=0;i<t;i++){
				for(j=0;j<t;j++){
					if(m[i][j] == 1.0){
						result++;
					}
				}
			}
			return result;
		}

		int casasFechadas(Campo c){
			int i, j;
			int result = 0;
			for(i=0;i<c.tamanho; i++){
				for(j=0;j<c.tamanho; j++){
					if(c.matrizOpen[i][j] == 0){
						result++;
					}
				}
			}
			return result;
		}

		int casasAbertas(Campo c){
			int i, j;
			int result = 0;
			for(i=0;i<c.tamanho; i++){
				for(j=0;j<c.tamanho; j++){
					if(c.matrizOpen[i][j] == 1){
						result++;
					}
				}
			}
			return result;
		}
};