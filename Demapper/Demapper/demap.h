#ifndef DEMAP_H
#define DEMAP_H

class gr_complex
{
private:
	float re, im;
	int var;
public:
	void set(float r, float i);
	float real();
	float imag();
};

//------------- A BIBLIOTECA GR_COMPLEX DEVE SER DELETADA PARA USO NO GRC	 ----------------------

class demap
{
private:
	int size; //tamanho do frame
	int mod_size; //modulação
	int rate; //taxa de codificação
	int M; //bits por simbolo
	float D[2]; //distancia bit 0 e bit 1
	gr_complex *tab; //tabela dos pontos da moduçlação
	float var; //variancia do ruido
	float *aux_r; //aux real
	float *aux_i; //aux imag
	float *aux; //aux dist euclidiana

public:
	void init(int s, int ms, int r, gr_complex *t); //inicializa variavais

	void demapper_soft(gr_complex *i, float *o); // faz o demap de i em o (LLR)
	void demapper_hard(gr_complex *i, unsigned char *o); // faz o demap de i em o (bit)

};

#endif
