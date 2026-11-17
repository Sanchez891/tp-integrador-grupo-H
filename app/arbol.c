#include <stdlib.h>
#include "arbol.h"

int insertarProducto(tNodoArbol ** pArbol, tProducto pProducto){
    int insertado = 0;
    if(*pArbol == NULL){
        *pArbol = (tNodoArbol*) malloc(sizeof(tNodoArbol));
        if(*pArbol != NULL){
            (*pArbol)->datos = pProducto;
            (*pArbol)->izquierdo = NULL;
            (*pArbol)->derecho = NULL;
            insertado = 1;
        }
    }else if(pProducto.codigo < (*pArbol)->datos.codigo){
        insertado = insertarProducto(&(*pArbol)->izquierdo, pProducto);
    }else if(pProducto.codigo > (*pArbol)->datos.codigo){
        insertado = insertarProducto(&(*pArbol)->derecho, pProducto);
    }
    return insertado;
}

tNodoArbol * buscarProducto(tNodoArbol * pArbol, int pCodigo){
    tNodoArbol * encontrado = NULL;
    if(pArbol != NULL){
        if(pCodigo == pArbol->datos.codigo){
            encontrado = pArbol;
        }else if(pCodigo < pArbol->datos.codigo){
            encontrado = buscarProducto(pArbol->izquierdo, pCodigo);
        }else{
            encontrado = buscarProducto(pArbol->derecho, pCodigo);
        }
    }
    return encontrado;
}