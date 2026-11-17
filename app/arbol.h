#ifndef ARBOL_H
#define ARBOL_H

#include "entidades.h"


typedef struct nodoArbol{
    tProducto datos;
    struct nodoArbol * izquierdo;
    struct nodoArbol * derecho;
}tNodoArbol;


int insertarProducto(tNodoArbol**, tProducto);


tNodoArbol * buscarProducto(tNodoArbol*, int);

#endif