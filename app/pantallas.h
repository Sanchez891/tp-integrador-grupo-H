#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PAGO_EFECTIVO 1
#define PAGO_DEBITO 2
#define PAGO_CREDITO 3
#define PAGO_TRANSFERENCIA 4

void Pausar(void);
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


void Pausar(void) {
    printf("\n");
    system("pause");
}

void MostrarTitulo(const char *pTitulo) {
    system("cls");
    printf("============================================\n");
    printf("  %s\n", pTitulo);
    printf("============================================\n\n");
}

void PantallaMensaje(const char *pMensaje) {
    printf("\n%s\n", pMensaje);
    Pausar();
}

bool PantallaConfirmar(const char *pPregunta) {
    char respuesta;
    printf("\n%s (s/n): ", pPregunta);
    scanf(" %c", &respuesta);
    return respuesta == 's' || respuesta == 'S';
}


void PantallaBienvenida(void) {
    MostrarTitulo("SISTEMA DE GESTION DE VENTAS Y MERCADERIA");
    printf("  Bienvenido/a.\n");
    printf("  Gestione sus productos, ventas y stock.\n");
    Pausar();
}


int PantallaMenuPrincipal(void) {
    int opcion;
    MostrarTitulo("MENU PRINCIPAL");
    printf("  1. Nueva venta\n");
    printf("  2. Gestion de productos\n");
    printf("  3. Consultas\n");
    printf("  0. Salir\n\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

int PantallaMenuProductos(void) {
    int opcion;
    MostrarTitulo("GESTION DE PRODUCTOS");
    printf("  1. Alta de producto\n");
    printf("  2. Baja de producto\n");
    printf("  3. Modificar producto\n");
    printf("  0. Volver\n\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

int PantallaMenuConsultas(void) {
    int opcion;
    MostrarTitulo("CONSULTAS");
    printf("  1. Historial de ventas\n");
    printf("  2. Stock de un producto\n");
    printf("  3. Productos con stock minimo\n");
    printf("  0. Volver\n\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}


void PantallaFormularioProducto(const char *pTitulo, tProducto *pProducto, bool pPedirCodigo) {
    MostrarTitulo(pTitulo);
    if (pPedirCodigo) {
        printf("Codigo: ");
        scanf("%d", &pProducto->codigo);
    } else {
        printf("Codigo: %d\n", pProducto->codigo);
    }
    printf("Nombre: ");
    scanf(" %[^\n]", pProducto->nombre);
    printf("Stock actual: ");
    scanf("%f", &pProducto->stock);
    printf("Stock minimo: ");
    scanf("%d", &pProducto->cantidad);
    printf("Precio unitario: $");
    scanf("%f", &pProducto->precio);
}

int PantallaPedirCodigo(const char *pTitulo) {
    int codigo;
    MostrarTitulo(pTitulo);
    printf("Ingrese el codigo del producto: ");
    scanf("%d", &codigo);
    return codigo;
}


void PantallaCarrito(tNodoCarrito *pCarrito) {
    float total = 0;
    printf("CARRITO:\n");
    if (pCarrito == NULL) {
        printf("El carrito esta vacio\n");
    }
    while (pCarrito != NULL) {
        printf("\nProducto: %s\n", pCarrito->info.nombre);
        printf("Codigo: %d\n", pCarrito->info.codigo);
        printf("Cantidad: %d\n", pCarrito->info.cantidad);
        printf("Precio unitario: $%.2f\n", pCarrito->info.precioUnitario);
        printf("Subtotal: $%.2f\n", pCarrito->info.subtotal);
        total += pCarrito->info.subtotal;
        pCarrito = pCarrito->sig;
    }
    printf("\n------------------------------------\n");
    printf("TOTAL: $%.2f\n", total);
}

int PantallaVenta(tNodoCarrito *pCarrito) {
    int opcion;
    MostrarTitulo("NUEVA VENTA");
    PantallaCarrito(pCarrito);
    printf("\n  1. Agregar producto\n");
    printf("  2. Confirmar venta\n");
    printf("  0. Cancelar venta\n\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

void PantallaAgregarProducto(int *pCodigo, int *pCantidad) {
    printf("\n--- Agregar producto al carrito ---\n");
    printf("Codigo del producto: ");
    scanf("%d", pCodigo);
    printf("Cantidad: ");
    scanf("%d", pCantidad);
}

int PantallaMetodoPago(void) {
    int opcion;
    printf("\n--- Metodo de pago ---\n");
    printf("  %d. %s\n", PAGO_EFECTIVO, NombreMetodoPago(PAGO_EFECTIVO));
    printf("  %d. %s\n", PAGO_DEBITO, NombreMetodoPago(PAGO_DEBITO));
    printf("  %d. %s\n", PAGO_CREDITO, NombreMetodoPago(PAGO_CREDITO));
    printf("  %d. %s\n", PAGO_TRANSFERENCIA, NombreMetodoPago(PAGO_TRANSFERENCIA));
    do {
        printf("Seleccione el metodo de pago: ");
        scanf("%d", &opcion);
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
