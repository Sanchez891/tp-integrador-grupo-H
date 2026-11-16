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

typedef struct Nodo{
    tProducto info;
    struct Nodo * nodoizq;
    struct Nodo * nododer;
}tArbolProductos;