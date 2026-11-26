#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define STOCKMIN 8

void inicializarProducto(tProducto*);
tProducto CrearProducto(int,string,int,float,float);
void AltaProducto(tArbolProductos **, int,string,int,float,float);
void ModificarProducto(tArbolProductos *, int,string,int,float,float);
void BajaProducto(tArbolProductos **, int);
tArbolProductos *BuscarMenor(tArbolProductos *);
void ConsultarStock(tArbolProductos *pArbol, int pCodigo);
void ConsultarStockMinimo(tArbolProductos *pArbol);
void LiberarArbol(tArbolProductos **pArbol);

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
    }else{
        nuevoProducto.cantidad = STOCKMIN;
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
            printf("Producto dado de alta correctamente");
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
                if(pCantidad < 0 || pStock < 0 || pPrecio < 0){
                    printf("Datos invalidos: no se permiten valores negativos");
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
                    printf("Producto dado de baja correctamente");

                }else{
                    // CASO 2: EL NODO TIENE SOLAMENTE HIJO DERECHO.
                    if((*pArbol)->nodoizq == NULL){

                        auxiliar = *pArbol;
                        *pArbol = (*pArbol)->nododer;
                        free(auxiliar);
                        printf("Producto dado de baja correctamente");
                    }else{
                        // CASO 2: EL NODO TIENE SOLAMENTE HIJO IZQUIERDO.
                        if((*pArbol)->nododer == NULL){

                            auxiliar = *pArbol;
                            *pArbol = (*pArbol)->nodoizq;
                            free(auxiliar);
                            printf("Producto dado de baja correctamente");
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
            }
        }
    }
}

void ConsultarStock(tArbolProductos *pArbol, int pCodigo) {
    if (pArbol == NULL) {
        printf("Producto inexistente.\n");
    } else {
        if (pCodigo < pArbol->info.codigo) {
            ConsultarStock(pArbol->nodoizq, pCodigo);
        } else {
            if (pCodigo > pArbol->info.codigo) {
                ConsultarStock(pArbol->nododer, pCodigo);
            } else {
                printf("\nProducto: %s", pArbol->info.nombre);
                printf("\nCodigo: %d", pArbol->info.codigo);
                printf("\nStock disponible: %.2f\n", pArbol->info.stock);
            }
        }
    }
}

void ConsultarStockMinimo(tArbolProductos *pArbol) {
    if (pArbol != NULL) {
        ConsultarStockMinimo(pArbol->nodoizq);
        if (pArbol->info.stock <= pArbol->info.cantidad) {
            printf("\nProducto: %s", pArbol->info.nombre);
            printf("\nCodigo: %d", pArbol->info.codigo);
            printf("\nStock actual: %.2f", pArbol->info.stock);
            printf("\nStock minimo: %d", pArbol->info.cantidad);
            printf("\n-----------------------------");
        }
        ConsultarStockMinimo(pArbol->nododer);
    }
}

void LiberarArbol(tArbolProductos **pArbol) {
    if (*pArbol != NULL) {
        LiberarArbol(&(*pArbol)->nodoizq);
        LiberarArbol(&(*pArbol)->nododer);
        free(*pArbol);
        *pArbol = NULL;
    }
}
