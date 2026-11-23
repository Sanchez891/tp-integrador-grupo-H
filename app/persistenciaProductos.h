#ifndef PERSISTENCIAPRODUCTOS_H
#define PERSISTENCIAPRODUCTOS_H

#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"

#define MARCA_NULO 0
#define MARCA_NODO 1


// GUARDAR ABB EN ARCHIVO BINARIO
// Utiliza recorrido preorden: raiz, izquierda, derecha.
void guardarProductos(tArbolProductos *pArbol, FILE *archivo) {
    int marca;
    // Si el nodo es NULL, guardamos la marca correspondiente.
    if (pArbol == NULL) {
        marca = MARCA_NULO;
        fwrite(&marca, sizeof(int), 1, archivo);
        return;
    }
    // Indicamos que existe un nodo.
    marca = MARCA_NODO;
    fwrite(&marca, sizeof(int), 1, archivo);
    // Guardamos la información del producto.
    fwrite(&(pArbol->info), sizeof(tProducto), 1, archivo);
    // Guardamos recursivamente el subárbol izquierdo.
    guardarProductos(pArbol->nodoizq, archivo);
    // Guardamos recursivamente el subárbol derecho.
    guardarProductos(pArbol->nododer, archivo);
}


// RECUPERAR ABB DESDE ARCHIVO BINARIO
void recuperarProductos(tArbolProductos **pArbol, FILE *archivo){
    int marca;
    // Leemos la marca que indica si existe un nodo.
    if (fread(&marca, sizeof(int), 1, archivo) != 1) {
        *pArbol = NULL;
        return;
    }
    // Si la marca es NULL, no existe un nodo en esta posición.
    if (marca == MARCA_NULO) {
        *pArbol = NULL;
        return;
    }
    // Reservamos memoria para el nuevo nodo.
    *pArbol = (tArbolProductos*)malloc(sizeof(tArbolProductos));
    if (*pArbol == NULL) {
        return;
    }
    // Recuperamos los datos del producto.
    if (fread(&((*pArbol)->info), sizeof(tProducto), 1, archivo) != 1) {
        free(*pArbol);
        *pArbol = NULL;
        return;
    }
    // Reconstruimos el subárbol izquierdo.
    recuperarProductos(&(*pArbol)->nodoizq, archivo);
    // Reconstruimos el subárbol derecho.
    recuperarProductos(&(*pArbol)->nododer, archivo);
}


#endif
