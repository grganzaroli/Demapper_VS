#include "stdafx.h"
#include <iostream>
#include <cmath>
#include "demap.h"

#pragma warning	(disable: 4996)

using namespace std;

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

//------------- A BIBLIOTECA GR_COMPLEX DEVE SER DELETADA PARA USO NO GRC	 ----------------------

void demap::init(int s, int ms, int r, gr_complex *t)
{
	size = s;
	mod_size = ms;
	rate = r;
	M = sqrt(mod_size);

	aux_r = new float[mod_size]; //aux real
	aux_i = new float[mod_size]; //aux imag
	aux = new float[mod_size]; //aux dist euclidiana

	tab = new gr_complex[mod_size];

	for(int i = 0; i < mod_size/4; i++)
	{
		tab[i].set(t[i].real(), t[i].imag());
	}

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

}

void demap::demapper_soft(gr_complex *i, float *o)
{

	for(int ii = 0; ii < size; ii++) //cada simbolo recebido
	{
		int a;

		//dist. real e imag
		for(int j = 0; j < mod_size; j++) //cada simbolo possivel
		{
			aux_r[j] = i[ii].real() - tab[j].real();
			aux_i[j] = i[ii].imag() - tab[j].imag();
		}

		//dist. euclidiana
		for(int j = 0; j < mod_size; j++) //cada simbolo possivel
			aux[j] = sqrt(aux_r[j]*aux_r[j] + aux_i[j]*aux_i[j]);

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

			o[ii*M+M-j] = -(1/var)*(D[1]-D[0]); //saida LLR do bit
		}
	}
}

void demap::demapper_hard(gr_complex *i, unsigned char *o)
{

	for(int ii = 0; ii < size; ii++) //cada simbolo recebido
	{
		int out_hard = 0;

		//dist. real e imag
		for(int j = 0; j < mod_size; j++) //cada simbolo possivel
		{
			aux_r[j] = i[ii].real() - tab[j].real();
			aux_i[j] = i[ii].imag() - tab[j].imag();
		}

		//dist. euclidiana
		for(int j = 0; j < mod_size; j++) //cada simbolo possivel
			aux[j] = sqrt(aux_r[j]*aux_r[j] + aux_i[j]*aux_i[j]);

		for(int j = 1; j < mod_size; j++) //cada simbolo possivel
		{
			if(aux[j] < aux[out_hard])
				out_hard = j; //(falta separar os bits)
		}

		for(int j = 1; j <= M; j++) //cada bit do simbolo
		{
			if(j == 1)
				o[ii*M+M-j] = out_hard%(int)(pow(2,j));//isolar bit
			else
				o[ii*M+M-j] = (out_hard%(int)(pow(2,j)))/(pow(2,(j-1))); //isolar bit
		}
	}
}