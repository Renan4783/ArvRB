/*
 * Main.c
 *
 *  Created on: 28 de fev de 2016
 *      Author: Renan
 */

#include<stdio.h>
#include<stdlib.h>

struct no {
	int info;
	char cor;
	struct no *Llink, *Rlink, *Pai;
};

void Preordem(struct no **Raiz);
void RotacaoEsquerda(struct no **Raiz, struct no *x);
void RotacaoDireita(struct no **Raiz, struct no *y);
void InsereFixUp(struct no **Raiz, struct no *z);
void insere(struct no **Raiz, int valor);

int main() {
	struct no *a1 = NULL;
	insere(&a1, 10);
	insere(&a1, 12);
	insere(&a1, 9);
	insere(&a1, 18);
	insere(&a1, 20);
	printf("Emordem : ");
	Preordem(&a1);

	return 0;
}

void RotacaoEsquerda(struct no **Raiz, struct no *x) {
	struct no *y = x->Rlink;

	x->Rlink = y->Llink;

	if (x->Rlink != NULL)
		x->Rlink->Pai = x;

	y->Pai = x->Pai;

	if (x->Pai == NULL)
		(*Raiz) = y;

	else if (x == x->Pai->Llink)
		x->Pai->Llink = y;
	else
		x->Pai->Rlink = y;

	y->Llink = x;

	x->Pai = y;
}

void RotacaoDireita(struct no **Raiz, struct no *y) {
	struct no *x = y->Llink;
	y->Llink = x->Rlink;
	if (x->Rlink != NULL)
		x->Rlink->Pai = y;
	x->Pai = y->Pai;
	if (x->Pai == NULL)
		(*Raiz) = x;
	else if (y == y->Pai->Llink)
		y->Pai->Llink = x;
	else
		y->Pai->Rlink = x;
	x->Rlink = y;
	y->Pai = x;
}

void InsereFixUp(struct no **Raiz, struct no *z) {
	while (z != *Raiz && z->Pai->cor == 'R') {
		struct no *y;

		// Find uncle and store uncle in y
		if (z->Pai == z->Pai->Pai->Llink)
			y = z->Pai->Pai->Rlink;
		else
			y = z->Pai->Pai->Llink;

		if (y != NULL) {
			if (y->cor == 'R') {
				y->cor = 'B';
				z->Pai->cor = 'B';
				z->Pai->Pai->cor = 'R';
				z = z->Pai->Pai;
			} else {
				return;
			}
		}

		else {
			if (z->Pai == z->Pai->Pai->Llink && z == z->Pai->Llink) {
				char ch = z->Pai->cor;
				z->Pai->cor = z->Pai->Pai->cor;
				z->Pai->Pai->cor = ch;
				RotacaoDireita(Raiz, z->Pai->Pai);
			}

			else if (z->Pai == z->Pai->Pai->Llink && z == z->Pai->Rlink) {
				char ch = z->cor;
				z->cor = z->Pai->Pai->cor;
				z->Pai->Pai->cor = ch;
				RotacaoEsquerda(Raiz, z->Pai);
				RotacaoDireita(Raiz, z->Pai);
			}

			else if (z->Pai == z->Pai->Pai->Rlink && z == z->Pai->Rlink) {
				char ch = z->Pai->cor;
				z->Pai->cor = z->Pai->Pai->cor;
				z->Pai->Pai->cor = ch;
				RotacaoEsquerda(Raiz, z->Pai->Pai);
			}

			else if (z->Pai == z->Pai->Pai->Rlink && z == z->Pai->Llink) {
				char ch = z->cor;
				z->cor = z->Pai->Pai->cor;
				z->Pai->Pai->cor = ch;
				RotacaoDireita(Raiz, z->Pai);
				RotacaoEsquerda(Raiz, z->Pai);
			}
		}
	}
	(*Raiz)->cor = 'B';
}

void insere(struct no **Raiz, int valor) {
	struct no *z = (struct no*) malloc(sizeof(struct no));
	z->info = valor;
	z->Llink = NULL;
	z->Rlink = NULL;
	z->Pai = NULL;

	if (*Raiz == NULL) {
		z->cor = 'B';
		(*Raiz) = z;
	} else {
		struct no *y = NULL;
		struct no *x = (*Raiz);

		while (x != NULL) {
			y = x;
			if ((z->info) < (x->info))
				x = x->Llink;
			else
				x = x->Rlink;
		}
		z->Pai = y;
		if (z->info > y->info)
			y->Rlink = z;
		else
			y->Llink = z;
		z->cor = 'R';

		InsereFixUp(Raiz, z);
	}
}

void Preordem(struct no **Raiz) {
	if (*Raiz == NULL) {
		return;
	} else {
		printf(" %d(%c) ", (*Raiz)->info, (*Raiz)->cor);
		Preordem(&(*Raiz)->Llink);
		Preordem(&(*Raiz)->Rlink);
	}
}

