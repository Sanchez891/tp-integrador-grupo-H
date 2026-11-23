//ARCHIVO MAIN DEL PROYECTO

#include "entidades.h"
#include "CrudProductos.h"
#include "Ventas.h"
#include "persistenciaProductos.h"
#include "persistenciaVentas.h"
#include "pantallas.h"

#define ARCHIVO_PRODUCTOS "productos.dat"

#define OPCION_SALIR 0
#define OPCION_VENTA 1
#define OPCION_PRODUCTOS 2
#define OPCION_CONSULTAS 3

void CargarProductos(tArbolProductos **pArbol);
void GuardarProductos(tArbolProductos *pArbol);
void FlujoVenta(tArbolProductos *pArbol);
void FlujoProductos(tArbolProductos **pArbol);
void FlujoConsultas(tArbolProductos *pArbol);


void CargarProductos(tArbolProductos **pArbol) {
    FILE *archivo = fopen(ARCHIVO_PRODUCTOS, "rb");
    *pArbol = NULL;
    if (archivo != NULL) {
        recuperarProductos(pArbol, archivo);
        fclose(archivo);
    }
}

void GuardarProductos(tArbolProductos *pArbol) {
    FILE *archivo = fopen(ARCHIVO_PRODUCTOS, "wb");
    if (archivo == NULL) {
        printf("\nError: no se pudo guardar el archivo de productos.\n");
        return;
    }
    guardarProductos(pArbol, archivo);
    fclose(archivo);
}


void FlujoVenta(tArbolProductos *pArbol) {
    tNodoCarrito *carrito = NULL;
    tVentas venta;
    int opcion;
    int codigo;
    int cantidad;
    bool ventaTerminada = false;

    while (!ventaTerminada) {
        opcion = PantallaVenta(carrito);
        switch (opcion) {
            case 1:
                PantallaAgregarProducto(&codigo, &cantidad);
                if (!AgregarAlCarrito(&carrito, pArbol, codigo, cantidad)) {
                    Pausar();
                }
                break;

            case 2:
                if (carrito == NULL) {
                    PantallaMensaje("El carrito esta vacio, agregue al menos un producto.");
                } else {
                    venta = GenerarVenta(carrito, PantallaMetodoPago(), "");
                    DescontarStock(pArbol, carrito);
                    guardarVenta(venta);
                    GuardarProductos(pArbol);
                    GenerarComprobante(venta, carrito);
                    printf("Pago con: %s\n", NombreMetodoPago(venta.metodoPago));
                    Pausar();
                    ventaTerminada = true;
                }
                break;

            case 0:
                if (carrito == NULL || PantallaConfirmar("Seguro que desea cancelar la venta?")) {
                    ventaTerminada = true;
                }
                break;

            default:
                PantallaMensaje("Opcion invalida.");
        }
    }
    LiberarCarrito(&carrito);
}


void FlujoProductos(tArbolProductos **pArbol) {
    tProducto producto;
    int opcion;
    int codigo;

    do {
        opcion = PantallaMenuProductos();
        switch (opcion) {
            case 1:
                PantallaFormularioProducto("ALTA DE PRODUCTO", &producto, true);
                AltaProducto(pArbol, producto.codigo, producto.nombre, producto.cantidad,
                             producto.stock, producto.precio);
                GuardarProductos(*pArbol);
                Pausar();
                break;

            case 2:
                codigo = PantallaPedirCodigo("BAJA DE PRODUCTO");
                if (BuscarProducto(*pArbol, codigo) == NULL) {
                    printf("Producto inexistente");
                } else {
                    ConsultarStock(*pArbol, codigo);
                    if (PantallaConfirmar("Confirma la baja del producto?")) {
                        BajaProducto(pArbol, codigo);
                        GuardarProductos(*pArbol);
                    }
                }
                Pausar();
                break;

            case 3:
                codigo = PantallaPedirCodigo("MODIFICAR PRODUCTO");
                if (BuscarProducto(*pArbol, codigo) == NULL) {
                    printf("Producto inexistente");
                } else {
                    producto.codigo = codigo;
                    PantallaFormularioProducto("MODIFICAR PRODUCTO", &producto, false);
                    ModificarProducto(*pArbol, producto.codigo, producto.nombre, producto.cantidad,
                                      producto.stock, producto.precio);
                    GuardarProductos(*pArbol);
                }
                Pausar();
                break;

            case 0:
                break;

            default:
                PantallaMensaje("Opcion invalida.");
        }
    } while (opcion != 0);
}


void FlujoConsultas(tArbolProductos *pArbol) {
    int opcion;

    do {
        opcion = PantallaMenuConsultas();
        switch (opcion) {
            case 1:
                MostrarTitulo("HISTORIAL DE VENTAS");
                listarVentas();
                Pausar();
                break;

            case 2:
                ConsultarStock(pArbol, PantallaPedirCodigo("CONSULTAR STOCK"));
                Pausar();
                break;

            case 3:
                MostrarTitulo("PRODUCTOS CON STOCK MINIMO");
                if (pArbol == NULL) {
                    printf("No hay productos cargados.\n");
                } else {
                    ConsultarStockMinimo(pArbol);
                }
                Pausar();
                break;

            case 0:
                break;

            default:
                PantallaMensaje("Opcion invalida.");
        }
    } while (opcion != 0);
}


int main(void) {
    tArbolProductos *arbolProductos = NULL;
    int opcion;

    PantallaBienvenida();
    CargarProductos(&arbolProductos);

    do {
        opcion = PantallaMenuPrincipal();
        switch (opcion) {
            case OPCION_VENTA:
                FlujoVenta(arbolProductos);
                break;
            case OPCION_PRODUCTOS:
                FlujoProductos(&arbolProductos);
                break;
            case OPCION_CONSULTAS:
                FlujoConsultas(arbolProductos);
                break;
            case OPCION_SALIR:
                break;
            default:
                PantallaMensaje("Opcion invalida.");
        }
    } while (opcion != OPCION_SALIR);

    GuardarProductos(arbolProductos);
    LiberarArbol(&arbolProductos);
    PantallaDespedida();
    return 0;
}
