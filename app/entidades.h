typedef char string[60];

typedef struct{
    int codigo;
    string nombre;
    int cantidad;
    float stock;
    float precio;
}tProducto;

typedef struct{
    int canProductos;
    float total;
    int metodoPago;
    string fecha;
}tVentas;

typedef struct {
    int codigo;
    string nombre;
    int cantidad;
    float precioUnitario;
    float subtotal;
} tDetalleVenta;
typedef struct Nodo{
    tProducto info;
    struct Nodo * nodoizq;
    struct Nodo * nododer;
}tArbolProductos;

typedef struct NodoCarrito {
    tDetalleVenta info;
    struct NodoCarrito *sig;
} tNodoCarrito;
