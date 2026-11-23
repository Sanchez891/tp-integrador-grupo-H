#ifndef PANTALLAS_H
#define PANTALLAS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "entidades.h"

#define PAGO_EFECTIVO 1
#define PAGO_DEBITO 2
#define PAGO_CREDITO 3
#define PAGO_TRANSFERENCIA 4

void LimpiarPantalla(void);
void Pausar(void);
void LeerTexto(const char *pMensaje, char *pDestino, int pTamanio);
int LeerEntero(const char *pMensaje);
float LeerFloat(const char *pMensaje);
void MostrarTitulo(const char *pTitulo);
void PantallaMensaje(const char *pMensaje);
bool PantallaConfirmar(const char *pPregunta);

void PantallaBienvenida(void);

int PantallaMenuPrincipal(void);
int PantallaMenuProductos(void);
int PantallaMenuConsultas(void);

void PantallaFormularioProducto(const char *pTitulo, tProducto *pProducto, bool pPedirCodigo);
int PantallaPedirCodigo(const char *pTitulo);

void PantallaCarrito(tNodoCarrito *pCarrito);
int PantallaVenta(tNodoCarrito *pCarrito);
void PantallaAgregarProducto(int *pCodigo, int *pCantidad);
int PantallaMetodoPago(void);
const char *NombreMetodoPago(int pMetodo);

void PantallaDespedida(void);


void LimpiarPantalla(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Pausar(void) {
    char buffer[8];
    printf("\nPresione ENTER para continuar...");
    fgets(buffer, sizeof(buffer), stdin);
}

void LeerTexto(const char *pMensaje, char *pDestino, int pTamanio) {
    int largo;
    printf("%s", pMensaje);
    if (fgets(pDestino, pTamanio, stdin) == NULL) {
        pDestino[0] = '\0';
        return;
    }
    largo = strlen(pDestino);
    if (largo > 0 && pDestino[largo - 1] == '\n') {
        pDestino[largo - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
}

int LeerEntero(const char *pMensaje) {
    char buffer[32];
    char *fin;
    long valor;
    while (true) {
        LeerTexto(pMensaje, buffer, sizeof(buffer));
        valor = strtol(buffer, &fin, 10);
        if (fin != buffer && *fin == '\0') {
            return (int)valor;
        }
        printf("  Valor invalido, ingrese un numero entero.\n");
    }
}

float LeerFloat(const char *pMensaje) {
    char buffer[32];
    char *fin;
    float valor;
    while (true) {
        LeerTexto(pMensaje, buffer, sizeof(buffer));
        valor = strtof(buffer, &fin);
        if (fin != buffer && *fin == '\0') {
            return valor;
        }
        printf("  Valor invalido, ingrese un numero.\n");
    }
}

void MostrarTitulo(const char *pTitulo) {
    LimpiarPantalla();
    printf("============================================\n");
    printf("  %s\n", pTitulo);
    printf("============================================\n\n");
}

void PantallaMensaje(const char *pMensaje) {
    printf("\n%s\n", pMensaje);
    Pausar();
}

bool PantallaConfirmar(const char *pPregunta) {
    char respuesta[8];
    printf("\n%s (s/n): ", pPregunta);
    LeerTexto("", respuesta, sizeof(respuesta));
    return respuesta[0] == 's' || respuesta[0] == 'S';
}


void PantallaBienvenida(void) {
    MostrarTitulo("SISTEMA DE GESTION DE VENTAS Y MERCADERIA");
    printf("  Bienvenido/a.\n");
    printf("  Gestione sus productos, ventas y stock.\n");
    Pausar();
}


int PantallaMenuPrincipal(void) {
    MostrarTitulo("MENU PRINCIPAL");
    printf("  1. Nueva venta\n");
    printf("  2. Gestion de productos\n");
    printf("  3. Consultas\n");
    printf("  0. Salir\n\n");
    return LeerEntero("Seleccione una opcion: ");
}

int PantallaMenuProductos(void) {
    MostrarTitulo("GESTION DE PRODUCTOS");
    printf("  1. Alta de producto\n");
    printf("  2. Baja de producto\n");
    printf("  3. Modificar producto\n");
    printf("  0. Volver\n\n");
    return LeerEntero("Seleccione una opcion: ");
}

int PantallaMenuConsultas(void) {
    MostrarTitulo("CONSULTAS");
    printf("  1. Historial de ventas\n");
    printf("  2. Stock de un producto\n");
    printf("  3. Productos con stock minimo\n");
    printf("  0. Volver\n\n");
    return LeerEntero("Seleccione una opcion: ");
}


void PantallaFormularioProducto(const char *pTitulo, tProducto *pProducto, bool pPedirCodigo) {
    MostrarTitulo(pTitulo);
    if (pPedirCodigo) {
        pProducto->codigo = LeerEntero("Codigo:           ");
    } else {
        printf("Codigo:           %d\n", pProducto->codigo);
    }
    LeerTexto("Nombre:           ", pProducto->nombre, sizeof(pProducto->nombre));
    pProducto->stock = LeerFloat("Stock actual:     ");
    pProducto->cantidad = LeerEntero("Stock minimo:     ");
    pProducto->precio = LeerFloat("Precio unitario:  $");
}

int PantallaPedirCodigo(const char *pTitulo) {
    MostrarTitulo(pTitulo);
    return LeerEntero("Ingrese el codigo del producto: ");
}


void PantallaCarrito(tNodoCarrito *pCarrito) {
    float total = 0;
    printf("%-8s %-22s %6s %12s %12s\n", "Codigo", "Producto", "Cant.", "P. Unit.", "Subtotal");
    printf("----------------------------------------------------------------\n");
    if (pCarrito == NULL) {
        printf("  (el carrito esta vacio)\n");
    }
    while (pCarrito != NULL) {
        printf("%-8d %-22.22s %6d %12.2f %12.2f\n",
               pCarrito->info.codigo, pCarrito->info.nombre, pCarrito->info.cantidad,
               pCarrito->info.precioUnitario, pCarrito->info.subtotal);
        total += pCarrito->info.subtotal;
        pCarrito = pCarrito->sig;
    }
    printf("----------------------------------------------------------------\n");
    printf("%51s %12.2f\n", "TOTAL: $", total);
}

int PantallaVenta(tNodoCarrito *pCarrito) {
    MostrarTitulo("NUEVA VENTA");
    PantallaCarrito(pCarrito);
    printf("\n  1. Agregar producto\n");
    printf("  2. Confirmar venta\n");
    printf("  0. Cancelar venta\n\n");
    return LeerEntero("Seleccione una opcion: ");
}

void PantallaAgregarProducto(int *pCodigo, int *pCantidad) {
    printf("\n--- Agregar producto al carrito ---\n");
    *pCodigo = LeerEntero("Codigo del producto: ");
    *pCantidad = LeerEntero("Cantidad:            ");
}

int PantallaMetodoPago(void) {
    int opcion;
    printf("\n--- Metodo de pago ---\n");
    printf("  %d. %s\n", PAGO_EFECTIVO, NombreMetodoPago(PAGO_EFECTIVO));
    printf("  %d. %s\n", PAGO_DEBITO, NombreMetodoPago(PAGO_DEBITO));
    printf("  %d. %s\n", PAGO_CREDITO, NombreMetodoPago(PAGO_CREDITO));
    printf("  %d. %s\n", PAGO_TRANSFERENCIA, NombreMetodoPago(PAGO_TRANSFERENCIA));
    do {
        opcion = LeerEntero("Seleccione el metodo de pago: ");
    } while (opcion < PAGO_EFECTIVO || opcion > PAGO_TRANSFERENCIA);
    return opcion;
}

const char *NombreMetodoPago(int pMetodo) {
    switch (pMetodo) {
        case PAGO_EFECTIVO:      return "Efectivo";
        case PAGO_DEBITO:        return "Tarjeta de debito";
        case PAGO_CREDITO:       return "Tarjeta de credito";
        case PAGO_TRANSFERENCIA: return "Transferencia";
        default:                 return "Desconocido";
    }
}


void PantallaDespedida(void) {
    MostrarTitulo("HASTA LUEGO");
    printf("  Los datos fueron guardados correctamente.\n\n");
}

#endif
