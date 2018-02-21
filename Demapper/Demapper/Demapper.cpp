// Demapper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>
#include "damap.h"

#define size 16200 //short frame
#define mod_size 16 // 16-QAM
#define rate 6 // 6/15

int _tmain(int argc, _TCHAR* argv[])
{
	gr_complex in[size]; //entrada de simbolos
	int *out_hard = new int[size*(int)sqrt(mod_size)]; //saida bits int
	float *out_soft = new float[size*(int)sqrt(mod_size)]; //saida bits LLR

	//teste in
	in[0].set(2,3);
	in[1].set(-2,3);
	in[2].set(2,-3);
	in[3].set(-2,-3);

	// ^^^^^^^^^^^^^^^^^^ VARIAVEIS QUE JA ESTARAO NO GRC

	tab = new gr_complex[mod_size/4];

	//TABELA DE PONTOS (norma)

	tab[0].set(0.5115, 1.2092);
	tab[1].set(1.2092, 0.5115);
	tab[2].set(0.2663, 0.4530);
	tab[3].set(0.4530, 0.2663);

	// ^^^^^^^^^^^^^^^^^^ VARIAVEIS QUE ESTARAO NO .H DO GRC

	demap.DEMAPPER;

	gr_complex *tab;


	DEMAPPER.init(size, mod_size, rate, tab);

	DEMAPPER.demapper_soft(in, out_soft);
	DEMAPPER.demapper_hard(in, out_hard);




	printf("");
	return 0;
}







//OLD
/*
{
	static int M = sqrt(mod_size);
	gr_complex tab[mod_size];
	float D[2];
	float var = 1; //variancia do ruido
	int opt = 1; // opção por demap hard ou soft


	gr_complex in[size]; //entrada IQ



	float aux_r[mod_size]; //aux real
	float aux_i[mod_size]; //aux imag
	float aux[mod_size]; //aux dist euclidiana



	int out_hard[size]; //saida hard int
	int *out = new int[size*M]; //saida bits int
	float *out_soft = new float[size*M]; //saida bits LLR



	//CRIAR TABELA DE PONTOS

	//norma
	tab[0].set(0.5115, 1.2092);
	tab[1].set(1.2092, 0.5115);
	tab[2].set(0.2663, 0.4530);
	tab[3].set(0.4530, 0.2663);

	for(int i = 1; i < 4; i++) //quadrantes
	{
		for(int j = 0; j < M; j++) //pontos
		{
			if(i == 1)
			{
				tab[j+M].set(-tab[j].real(), tab[j].imag());
			}
			else if(i == 2)
			{
				tab[j+2*M].set(tab[j].real(), -tab[j].imag());
			}
			else if(i == 3)
			{
				tab[j+3*M].set(-tab[j].real(), -tab[j].imag());
			}
		}
	}


	//teste in
	in[0].set(2,3);
	in[1].set(-2,3);
	in[2].set(2,-3);
	in[3].set(-2,-3);

	printf("");

	//DEMAPPER

	for(int i = 0; i < size; i++) //cada simbolo recebido
	{
		int a;

		//dist. real e imag
		for(int j = 0; j < mod_size; j++) //cada simbolo possivel
		{
			aux_r[j] = in[i].real() - tab[j].real();
			aux_i[j] = in[i].imag() - tab[j].imag();
		}

		//dist. euclidiana
		for(int j = 0; j < mod_size; j++) //cada simbolo possivel
			aux[j] = sqrt(aux_r[j]*aux_r[j] + aux_i[j]*aux_i[j]);


		if(opt == 0) // hard-decision
		{
			out_hard[i] = 0;	
			for(int j = 1; j < mod_size; j++) //cada simbolo possivel
			{
				if(aux[j] < aux[out_hard[i]])
					out_hard[i] = j; //(falta separar os bits)
			}

			for(int j = 1; j <= M; j++) //cada bit do simbolo
			{
				if(j == 1)
					out[i*M+M-j] = out_hard[i]%(int)(pow(2,j));//isolar bit
				else
					out[i*M+M-j] = (out_hard[i]%(int)(pow(2,j)))/(pow(2,(j-1))); //isolar bit

			}
		}
		else if(opt == 1)//soft-decision
		{
			for(int j = 1; j <= M; j++) //cada bit do simbolo
			{
				D[0] = 999;
				D[1] = 999;

				for(int k = 0; k < mod_size; k++) //cada simbolo possivel
				{

					if(j == 1)
						a = k%(int)(pow(2,j));//isolar bit
					else
						a = (k%(int)(pow(2,j)))/(pow(2,(j-1))); //isolar bit

					if(a == 0)//bit 0
					{
						if(aux[k] < D[0])
							D[0] = aux[k];
					}
					else if(a == 1)//bit 1
					{
						if(aux[k] < D[1])
							D[1] = aux[k];
					}
				}

				out_soft[i*M+M-j] = -(1/var)*(D[1]-D[0]); //saida LLR do bit
			}
		}
	}








	printf("");
	return 0;
}

*/