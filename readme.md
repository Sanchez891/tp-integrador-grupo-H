# TP Integrador – Sistema de Gestión de Ventas y Mercadería

## Descripción del proyecto

Este proyecto consiste en el desarrollo de un sistema de gestión de ventas y mercadería como parte del Trabajo Práctico Integrador de la asignatura **Algoritmos y Estructuras de Datos II**.

El sistema permite administrar productos, registrar ventas, controlar el stock y consultar la información almacenada, aplicando estructuras de datos, tipos de datos abstractos (TDA) y persistencia mediante archivos binarios.

El caso de uso es el de un pequeño emprendedor de productos tecnológicos: la herramienta le facilita la gestión de su negocio, le permite llevar la trazabilidad de los datos y le da una organización más profesional.

---

## Compilación y ejecución

El programa es de consola y se compila con `gcc` desde la carpeta `app`:

```bash
cd app
gcc main.c -o gestion.exe
./gestion.exe
```

Al iniciar, el sistema carga los productos guardados en `productos.dat`. Si el archivo no existe (primer uso), arranca sin productos. Los archivos de datos se crean en la carpeta desde donde se ejecuta el programa.

---

## Funcionalidades

| Funcionalidad | Estado |
|---|---|
| Alta, baja y modificación de productos | ✅ Implementada |
| Buscar productos por código | ✅ Implementada |
| Agregar productos al carrito (valida cantidad y stock disponible) | ✅ Implementada |
| Calcular subtotales y total de la venta | ✅ Implementada |
| Registrar el método de pago | ✅ Implementada |
| Emitir el comprobante de venta | ✅ Implementada |
| Descontar el stock al confirmar la venta | ✅ Implementada |
| Consultar el historial de ventas | ✅ Implementada |
| Consultar el stock de un producto | ✅ Implementada |
| Consultar productos en stock mínimo | ✅ Implementada |
| Registrar ingresos de mercadería (sumar stock a un producto existente) | ⏳ Pendiente (por ahora se hace desde "Modificar producto") |
| Guardar el detalle de productos de cada venta | ⏳ Pendiente (se guarda solo el resumen: fecha, cantidad de productos, total y método de pago) |

---

## Flujo del sistema

```
Bienvenida
  └ Menú principal
     ├ 1. Nueva venta
     │    ├ 1. Agregar producto (código y cantidad)
     │    ├ 2. Confirmar venta → método de pago → comprobante
     │    └ 0. Cancelar venta (pide confirmación si el carrito tiene productos)
     ├ 2. Gestión de productos
     │    ├ 1. Alta de producto
     │    ├ 2. Baja de producto (muestra el producto y pide confirmación)
     │    ├ 3. Modificar producto
     │    └ 0. Volver
     ├ 3. Consultas
     │    ├ 1. Historial de ventas
     │    ├ 2. Stock de un producto
     │    ├ 3. Productos con stock mínimo
     │    └ 0. Volver
     └ 0. Salir (guarda los productos y libera la memoria)
```

Al confirmar una venta se descuenta el stock, se guarda la venta en `ventas.dat`, se actualiza `productos.dat` y se emite el comprobante. Los productos también se guardan después de cada alta, baja o modificación.

Las pantallas validan los datos ingresados: si se escribe un texto donde se espera un número, o se elige una opción inexistente, se vuelve a pedir el dato.

### Datos de un producto

| Campo | Descripción |
|---|---|
| Código | Identificador único (clave del árbol). |
| Nombre | Hasta 59 caracteres; si es más largo se recorta. |
| Stock actual | Unidades disponibles para la venta. |
| Stock mínimo | Por debajo o igual a este valor, el producto aparece en la consulta de stock mínimo. Si no se indica (0), se usa el valor por defecto `STOCKMIN` (8). |
| Precio unitario | Precio de venta. |

No se aceptan valores negativos en el alta ni en la modificación.

### Métodos de pago

1. Efectivo
2. Tarjeta de débito
3. Tarjeta de crédito
4. Transferencia

---

## Estructuras de datos y herramientas

| Estructura / Recurso | Aplicación |
|---|---|
| Árbol binario de búsqueda (ABB) | Almacenamiento y búsqueda de productos por código. |
| Lista enlazada | Carrito de la venta en curso (si un producto ya está en el carrito, se acumula la cantidad). |
| Archivos binarios | Persistencia de productos (`productos.dat`) y ventas (`ventas.dat`). |
| TDA | Modularización de productos, ventas, persistencia y pantallas. |
| Struct | Representación de entidades como productos, ventas y detalle de venta. |

El árbol se guarda en el archivo con un recorrido **preorden** y marcas de nodo vacío, de modo que al recuperarlo se reconstruye con la misma forma que tenía.

---

## Organización del proyecto

```
app/
├── main.c                  Flujo principal: coordina menús, ventas, productos y consultas.
├── entidades.h             Definición de los structs: tProducto, tVentas, tDetalleVenta,
│                           tArbolProductos (nodo del ABB) y tNodoCarrito.
├── CrudProductos.h         Alta, baja, modificación, consulta de stock, stock mínimo
│                           y liberación del árbol.
├── Ventas.h                Búsqueda de productos, carrito, generación de la venta,
│                           comprobante, descuento de stock y liberación del carrito.
├── persistenciaProductos.h Guardar y recuperar el ABB en archivo binario.
├── persistenciaVentas.h    Guardar ventas y listar el historial.
└── pantallas.h             Menús, formularios y lectura validada de datos.
```

Todos los `.h` tienen *include guard*, por lo que pueden incluirse en cualquier orden.

### Funciones principales por módulo

**CrudProductos.h**
- `AltaProducto`, `BajaProducto`, `ModificarProducto`
- `ConsultarStock`, `ConsultarStockMinimo`
- `LiberarArbol`

**Ventas.h**
- `BuscarProducto`, `AgregarAlCarrito`
- `GenerarVenta` (si recibe una fecha vacía usa la fecha y hora actual), `GenerarComprobante`
- `DescontarStock`, `LiberarCarrito`

**persistenciaProductos.h / persistenciaVentas.h**
- `guardarProductos`, `recuperarProductos`
- `guardarVenta`, `listarVentas`

**pantallas.h**
- Menús: `PantallaMenuPrincipal`, `PantallaMenuProductos`, `PantallaMenuConsultas`
- Productos: `PantallaFormularioProducto`, `PantallaPedirCodigo`
- Ventas: `PantallaVenta`, `PantallaCarrito`, `PantallaAgregarProducto`, `PantallaMetodoPago`
- Utilidades: `LeerEntero`, `LeerFloat`, `LeerTexto`, `PantallaConfirmar`, `PantallaMensaje`

Las pantallas solo muestran información y leen datos; no modifican el árbol, el carrito ni los archivos. Es `main.c` quien decide qué hacer con lo que devuelve cada pantalla.

---

## Reglas y convenciones de desarrollo

Para mantener un código organizado, modular y fácil de mantener, se establecen las siguientes reglas de trabajo:

### Representación de entidades

- Las entidades del sistema, como productos y ventas, se representan mediante tipos de datos `struct` en lenguaje C, definidos en `entidades.h`.

### Modularización y desacoplamiento

- Todas las funciones deberán estar desacopladas.
- Las funciones deberán recibir los parámetros necesarios y retornar un valor cuando corresponda.
- Se evitará el uso de dependencias innecesarias entre módulos.
- Cada módulo deberá tener responsabilidades claramente definidas.

### Responsabilidad de las funciones

- Se evitará mezclar responsabilidades diferentes dentro de una misma función.
- Como regla general, cada función deberá tener como máximo dos responsabilidades.
- Se permitirá una excepción cuando la función tenga como objetivo principal coordinar o definir un flujo de ejecución (por ejemplo, `FlujoVenta`, `FlujoProductos` y `FlujoConsultas` en `main.c`).

---

## Tecnologías

- **Lenguaje:** C.
- **Compilador:** GCC.
- **Estructuras de datos:** Árbol binario de búsqueda y lista enlazada.
- **Modularización:** Tipos de Datos Abstractos (TDA).
- **Persistencia:** Archivos binarios.
- **Control de versiones:** Git y GitHub.
- **Organización de tareas:** Trello.

---

## Trabajo en equipo

El desarrollo se realiza de manera colaborativa, respetando las convenciones establecidas y manteniendo una organización modular que facilite la integración de los distintos componentes del sistema.

---

## Contexto académico

**Asignatura:** Algoritmos y Estructuras de Datos II (AED2).

**Trabajo:** Trabajo Práctico Integrador.

**Lenguaje de programación:** C.

**Institución:** FACENA – Universidad Nacional del Nordeste (UNNE).
