#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// BUSCAR PRODUCTO EN EL ABB
tProducto *BuscarProducto(tArbolProductos *pArbol, int pCodigo) {
    // Si llegamos a un nodo NULL, el producto no existe.
    if (pArbol == NULL) {
        return NULL;
    }
    // Si el código es menor, buscamos por izquierda.
    if (pCodigo < pArbol->info.codigo) {
        return BuscarProducto(pArbol->nodoizq, pCodigo);
    }
    // Si el código es mayor, buscamos por derecha.
    if (pCodigo > pArbol->info.codigo) {
        return BuscarProducto(pArbol->nododer, pCodigo);
    }
    // Encontramos el producto.
    return &pArbol->info;
}

bool AgregarAlCarrito(tNodoCarrito **pCarrito,tArbolProductos *pArbol,int pCodigo,int pCantidad) {
    tProducto *producto;
    tNodoCarrito *nuevoNodo;
    // Validamos la cantidad solicitada.
    if (pCantidad <= 0) {
        printf("Cantidad invalida\n");
        return false;
    }
    // Buscamos el producto en el ABB.
    producto = BuscarProducto(pArbol, pCodigo);
    if (producto == NULL) {
        printf("Producto inexistente\n");
        return false;
    }
    // Buscamos si el producto ya está en el carrito.
    while (*pCarrito != NULL && (*pCarrito)->info.codigo != pCodigo) {
        pCarrito = &(*pCarrito)->sig;
    }
    // Si ya existe, acumulamos la cantidad.
    if (*pCarrito != NULL) {
        if ((*pCarrito)->info.cantidad + pCantidad > producto->stock) {
            printf("Stock insuficiente\n");
            return false;
        }
        (*pCarrito)->info.cantidad += pCantidad;
        (*pCarrito)->info.subtotal =
            (*pCarrito)->info.cantidad * producto->precio;
        return true;
    }
    // Si no existe, creamos un nuevo nodo.
    if (pCantidad > producto->stock) {
        printf("Stock insuficiente\n");
        return false;
    }
    nuevoNodo = (tNodoCarrito*)malloc(sizeof(tNodoCarrito));
    if (nuevoNodo == NULL) {
        printf("Error al reservar memoria para el carrito\n");
        return false;
    }
    // Copiamos los datos del producto al detalle de venta.
    nuevoNodo->info.codigo = producto->codigo;
    strcpy(nuevoNodo->info.nombre, producto->nombre);
    nuevoNodo->info.cantidad = pCantidad;
    nuevoNodo->info.precioUnitario = producto->precio;
    nuevoNodo->info.subtotal = pCantidad * producto->precio;
    nuevoNodo->sig = NULL;
    *pCarrito = nuevoNodo;

    return true;
}

void obtenerFecha(char fecha[]) {
    time_t tiempoActual;
    struct tm *fechaActual;

    time(&tiempoActual);
    fechaActual = localtime(&tiempoActual);

    strftime(fecha, 20, "%d/%m/%Y %H:%M:%S", fechaActual);
}

tVentas GenerarVenta(tNodoCarrito *pCarrito,int pMetodoPago,string pFecha) {
    tVentas nuevaVenta;
    nuevaVenta.canProductos = 0;
    nuevaVenta.total = 0;
    nuevaVenta.metodoPago = pMetodoPago;
    if (pFecha != NULL && pFecha[0] != '\0') {
        strcpy(nuevaVenta.fecha, pFecha);
    } else {
        obtenerFecha(nuevaVenta.fecha);
    }
    // Recorremos el carrito.
    while (pCarrito != NULL) {
        nuevaVenta.canProductos++;
        nuevaVenta.total += pCarrito->info.subtotal;
        pCarrito = pCarrito->sig;
    }
    return nuevaVenta;
}

void GenerarComprobante(tVentas pVenta,tNodoCarrito *pCarrito) {
    printf("\n====================================\n");
    printf("          COMPROBANTE DE VENTA      \n");
    printf("====================================\n");
    printf("Fecha: %s\n", pVenta.fecha);
    printf("------------------------------------\n");
    printf("PRODUCTOS:\n");
    while (pCarrito != NULL) {
        printf("\nProducto: %s\n",pCarrito->info.nombre);
        printf("Codigo: %d\n",pCarrito->info.codigo);
        printf("Cantidad: %d\n",pCarrito->info.cantidad);
        printf("Precio unitario: $%.2f\n", pCarrito->info.precioUnitario);
        printf("Subtotal: $%.2f\n",pCarrito->info.subtotal);
        pCarrito = pCarrito->sig;
    }
    printf("\n------------------------------------\n");
    printf("Cantidad de productos: %d\n", pVenta.canProductos);
    printf("Metodo de pago: %d\n",pVenta.metodoPago);
    printf("TOTAL: $%.2f\n", pVenta.total);
    printf("====================================\n");
    printf("       GRACIAS POR SU COMPRA        \n");
    printf("====================================\n");
}

void DescontarStock(tArbolProductos *pArbol, tNodoCarrito *pCarrito) {
    tProducto *producto;
    while (pCarrito != NULL) {
        producto = BuscarProducto(pArbol, pCarrito->info.codigo);
        if (producto != NULL) {
            producto->stock -= pCarrito->info.cantidad;
        }
        pCarrito = pCarrito->sig;
    }
}

void LiberarCarrito(tNodoCarrito **pCarrito) {
    tNodoCarrito *auxiliar;
    while (*pCarrito != NULL) {
        auxiliar = *pCarrito;
        *pCarrito = (*pCarrito)->sig;
        free(auxiliar);
    }
}
