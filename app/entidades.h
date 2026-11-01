typedef char string[60];

typedef struct{
    int codigo;
    string nombre;
    int cantidad;
    float stock;
}tProducto;

typedef struct{
    int canProductos;
    float total;
    int metodoPago;
    string fecha;
}tVentas;
