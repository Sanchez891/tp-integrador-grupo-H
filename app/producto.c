#include <string.h>
#include "producto.h"

void inicializarProducto(tProducto * pProducto){
    pProducto->codigo = 0;
    strcpy(pProducto->nombre, "");
    pProducto->cantidad = 0;
    pProducto->precio = 0.0;
    pProducto->stock = 0.0;
}

tProducto CrearProducto(int pCodigo, string pNombre, int pCantidad, float pStock, float pPrecio){
    tProducto nuevoProducto;
    inicializarProducto(&nuevoProducto);
    strcpy(nuevoProducto.nombre, pNombre);
    nuevoProducto.codigo = pCodigo;
    if(pCantidad > 0){
        nuevoProducto.cantidad = pCantidad;
    }
    if(pStock > 0){
        nuevoProducto.stock = pStock;
    }
    if(pPrecio > 0){
        nuevoProducto.precio = pPrecio;
    }
    return nuevoProducto;
}

int validarProducto(tProducto pProducto){
    int valido = 0;
    if(strlen(pProducto.nombre) > 0 && pProducto.precio > 0 &&
       pProducto.cantidad >= 0 && pProducto.stock >= 0){
        valido = 1;
    }
    return valido;
}
