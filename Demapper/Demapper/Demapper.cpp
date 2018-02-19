// Demapper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>

class gr_complex
{
private:
	float re, im;
	int val;
public:
	void set(float r, float i);
	float real();
	float imag();
};

void gr_complex::set(float r, float i)
{
	re = r;
	im = i;
}

float gr_complex::real()
{
	return re;
}

float gr_complex::imag()
{
	return im;
}


#define size 16200 //short frame
#define mod_size 16 // 16-QAM
#define rate 6 // 6/15

int _tmain(int argc, _TCHAR* argv[])
{
	int M = sqrt(mod_size);
	gr_complex tab[mod_size];
	int D[2];


	gr_complex in[size]; //entrada IQ
	float aux_r[mod_size]; //aux real
	float aux_i[mod_size]; //aux imag
	float aux[mod_size]; //aux dist euclidiana
	int out[size]; //saida int





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






	//DEMAPPER

	for(int i = 0; i < size; i++)
	{
		//dist. real e imag
		for(int j = 0; j < mod_size; j++)
		{
			aux_r[j] = in[i].real() - tab[j].real();
			aux_i[j] = in[i].imag() - tab[j].imag();
		}

		//dist. euclidiana
		for(int j = 0; j < mod_size; j++)
			aux[j] = sqrt(aux_r[j]*aux_r[j] + aux_i[j]*aux_i[j]);

		out[i] = 0;	
		for(int j = 1; j < mod_size; j++)
		{
			if(aux[j] < aux[out[i]])
				out[i] = j; //decisao hard-decision (falta separar os bits)
		}














	}








	printf("");
	return 0;
}

