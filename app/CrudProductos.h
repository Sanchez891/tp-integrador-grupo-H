#include <entidades.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void inicializarProducto(tProducto*);
tProducto CrearProducto(int,string,int,float,float);
void AltaProducto(tArbolProductos **, int,string,int,float,float);
void ModificarProducto(tArbolProductos *, int,string,int,float,float);
void BajaProducto(tArbolProductos **, int);
tArbolProductos *BuscarMenor(tArbolProductos *);

void inicializarProducto(tProducto * pProducto){
    pProducto->codigo = 0;
    strcpy(pProducto->nombre, " ");
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


void AltaProducto(tArbolProductos **pArbol, int pCodigo, string pNombre, int pCantidad, float pStock, float pPrecio){
    tProducto nuevoProducto = CrearProducto(pCodigo,pNombre,pCantidad,pStock,pPrecio);
    if(*pArbol == NULL){
        *pArbol = (tArbolProductos*)malloc(sizeof(tArbolProductos));
        if(*pArbol != NULL){
            (*pArbol)->info = nuevoProducto;
            (*pArbol)->nodoizq = NULL;
            (*pArbol)->nododer = NULL;
        }else{
            printf("Error con el almacenamiento de productos");
        }
    }else{
        if(pCodigo < (*pArbol)->info.codigo){
            AltaProducto(&(*pArbol)->nodoizq,pCodigo,pNombre,pCantidad,pStock,pPrecio);
        }else{
            if(pCodigo > (*pArbol)->info.codigo){
                AltaProducto(&(*pArbol)->nododer,pCodigo,pNombre,pCantidad,pStock,pPrecio);
            }else{
                printf("Producto con codigo existente");
            }
        }
    }
}

void ModificarProducto(tArbolProductos *pArbol, int pCodigo, string pNombre, int pCantidad, float pStock, float pPrecio){
    if(pArbol == NULL){
        printf("Producto inexistente");
    }else{
        if(pCodigo < pArbol->info.codigo){
            ModificarProducto(pArbol->nodoizq,pCodigo,pNombre,pCantidad,pStock,pPrecio);
        }else{
            if(pCodigo > pArbol->info.codigo){
                ModificarProducto(pArbol->nododer,pCodigo,pNombre,pCantidad,pStock,pPrecio);
            }else{
                // Actualizamos los datos del producto encontrado.
                strcpy(pArbol->info.nombre,pNombre);
                pArbol->info.cantidad = pCantidad;
                pArbol->info.stock = pStock;
                pArbol->info.precio = pPrecio;
                printf("Producto modificado correctamente");
            }
        }
    }
}

tArbolProductos *BuscarMenor(tArbolProductos *pArbol){
    if(pArbol->nodoizq == NULL){
        return pArbol;
    }else{
        return BuscarMenor(pArbol->nodoizq);
    }
}

void BajaProducto(tArbolProductos **pArbol, int pCodigo){
    tArbolProductos *auxiliar;
    if(*pArbol == NULL){
        printf("Producto inexistente");
    }else{
        if(pCodigo < (*pArbol)->info.codigo){
            BajaProducto(&(*pArbol)->nodoizq,pCodigo);
        }else{
            if(pCodigo > (*pArbol)->info.codigo){
                BajaProducto(&(*pArbol)->nododer,pCodigo);
            }else{
                // CASO 1: EL NODO NO TIENE HIJOS.
                if((*pArbol)->nodoizq == NULL && (*pArbol)->nododer == NULL){

                    free(*pArbol);
                    *pArbol = NULL;

                }else{
                    // CASO 2: EL NODO TIENE SOLAMENTE HIJO DERECHO.
                    if((*pArbol)->nodoizq == NULL){

                        auxiliar = *pArbol;
                        *pArbol = (*pArbol)->nododer;
                        free(auxiliar);
                    }else{
                        // CASO 2: EL NODO TIENE SOLAMENTE HIJO IZQUIERDO.
                        if((*pArbol)->nododer == NULL){

                            auxiliar = *pArbol;
                            *pArbol = (*pArbol)->nodoizq;
                            free(auxiliar);
                        }else{
                            // CASO 3: EL NODO TIENE DOS HIJOS.
                            auxiliar = BuscarMenor((*pArbol)->nododer);
                            // Reemplazamos la informacion por el sucesor.
                            (*pArbol)->info = auxiliar->info;
                            // Eliminamos el sucesor de su ubicacion original.
                            BajaProducto(&(*pArbol)->nododer,auxiliar->info.codigo);
                        }
                    }
                }
                printf("Producto dado de baja correctamente");
            }
        }
    }
}
