#ifndef PERSISTENCIAVENTAS_H
#define PERSISTENCIAVENTAS_H


#include <stdio.h>
#include "entidades.h"

void guardarVenta(tVentas pVenta);
void listarVentas(void);

void guardarVenta(tVentas pVenta) {
    FILE *archivo = fopen("ventas.dat", "ab");
    if (archivo == NULL) {
        return;
    }
    if (fwrite(&pVenta, sizeof(tVentas), 1, archivo) != 1) {
        printf("Error al guardar la venta\n");
    }
    fclose(archivo);
}

void listarVentas(void) {
    FILE *archivo = fopen("ventas.dat", "rb");
    tVentas venta;
    if (archivo == NULL) {
        printf("No hay ventas registradas.\n");
        return;
    }
    printf("\n========== HISTORIAL DE VENTAS ==========\n");
    while (fread(&venta, sizeof(tVentas), 1, archivo) == 1) {
        printf("\nFecha: %s", venta.fecha);
        printf("\nProductos: %d", venta.canProductos);
        printf("\nTotal: $%.2f", venta.total);
        printf("\nMetodo de pago: %d", venta.metodoPago);
        printf("\n-----------------------------------------\n");
    }
    fclose(archivo);
}

#endif
