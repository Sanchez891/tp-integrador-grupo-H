# TP Integrador – Sistema de Gestión de Ventas y Mercadería

## Descripción del proyecto

Este proyecto consiste en el desarrollo de un sistema de gestión de ventas y mercadería como parte del Trabajo Práctico Integrador de la asignatura **Algoritmos y Estructuras de Datos II**.

El objetivo es implementar un sistema que permita administrar productos, registrar ventas, controlar el stock y consultar información almacenada, aplicando estructuras de datos, tipos de datos abstractos (TDA) y persistencia mediante archivos binarios.

El caso de uso que vamos a utilizar es usando el rol de un pequeño de emprendedor de productos tecnologicos y esta herramienta le facilita la gestion de su negocio y le ayuda a llevar una trazabilidad de los datos y una organizacion mas profesional 
---

##  Alcance del proyecto

El sistema contempla las siguientes funcionalidades:

- Login ficticio para simular el acceso al sistema.
- Registrar ventas.
- Buscar y agregar productos mediante su código.
- Calcular subtotales y totales de las ventas.
- Registrar métodos de pago.
- Emitir comprobantes de venta.
- Consultar el historial de ventas.
- Registrar ingresos de mercadería.
- Consultar el stock disponible.
- Consultar el stock mínimo.

---

##  Estructuras de datos y herramientas

Para resolver las distintas funcionalidades del sistema se propone utilizar las siguientes estructuras:

| Estructura / Recurso | Aplicación |
|---|---|
| Árboles | Organización y búsqueda de productos por código. |
| Archivos binarios | Persistencia de productos, ventas y stock. |
| TDA | Modularización de ventas, stock y persistencia. |
| Colas | Administración del carrito de ventas. |
| Struct | Representación de entidades como productos y ventas. |

### Organización de los TDA

Se propone trabajar inicialmente con los siguientes módulos:

- `ventas.h` – Definición de operaciones relacionadas con las ventas.
- `stock.h` – Definición de operaciones relacionadas con el stock.
- `persistencia.h` – Operaciones de lectura y escritura de archivos binarios.
- `interfas.h` – formato de la informacion que se le va a entregar al usuario

La implementación de cada módulo se realizará en su correspondiente archivo `main.c`, donde se definira el flujo
del sistema

---

##  Priorización de módulos

El desarrollo se organizará en cuatro módulos principales, siguiendo el siguiente orden de prioridad:

### 1. Módulo de ventas

Responsable de gestionar las operaciones de venta.

Funcionalidades:
- Generar una venta.
- Buscar productos mediante su código.
- Agregar productos al carrito.
- Calcular subtotales y total.
- Registrar el método de pago.
- Emitir el comprobante de venta.

### 2. Módulo CRUD de mercadería

Responsable de administrar los productos y la mercadería disponible.

Funcionalidades:
- Alta de productos.
- Baja de productos.
- Modificación de productos.

### 3. Módulo de persistencia

Responsable de gestionar el almacenamiento de la información del sistema mediante archivos binarios.

Funcionalidades:
- Crear archivos binarios.
- Leer información almacenada.
- Modificar y actualizar los registros.
- Mantener archivos independientes para cada módulo.

### 4. Módulo de consulta de datos

Responsable de permitir la consulta de información registrada en el sistema.

Funcionalidades:
- Consultar historial de ventas.
- Consultar stock disponible.
- Consultar stock mínimo.

---

##  Reglas y convenciones de desarrollo

Para mantener un código organizado, modular y fácil de mantener, se establecen las siguientes reglas de trabajo:

### Representación de entidades

- Las entidades del sistema, como productos y ventas, se representarán mediante tipos de datos `struct` en lenguaje C.
- Los prototipos y las definiciones de estructuras se establecerán durante la etapa de diseño de cada módulo.

### Modularización y desacoplamiento

- Todas las funciones deberán estar desacopladas.
- Las funciones deberán recibir los parámetros necesarios y retornar un valor cuando corresponda.
- Se evitará el uso de dependencias innecesarias entre módulos.
- Cada módulo deberá tener responsabilidades claramente definidas.

### Responsabilidad de las funciones

- Se evitará mezclar responsabilidades diferentes dentro de una misma función.
- Como regla general, cada función deberá tener como máximo dos responsabilidades.
- Se permitirá una excepción cuando la función tenga como objetivo principal coordinar o definir un flujo de ejecución.

---

##  Tecnologías

- **Lenguaje:** C.
- **Estructuras de datos:** Árboles y colas.
- **Modularización:** Tipos de Datos Abstractos (TDA).
- **Persistencia:** Archivos binarios.
- **Control de versiones:** Git y GitHub.
- **Organizacion de tareas:** Trello.

---

##  Organización del proyecto

La estructura de directorios y archivos se definirá durante la implementación, respetando la separación entre módulos, interfaces (`.h`) e implementaciones (`.c`).

---

##  Trabajo en equipo

El desarrollo se realizará de manera colaborativa, respetando las convenciones establecidas y manteniendo una organización modular que facilite la integración de los distintos componentes del sistema.

---

##  Contexto académico

**Asignatura:** Algoritmos y Estructuras de Datos II (AED2).

**Trabajo:** Trabajo Práctico Integrador.

**Lenguaje de programación:** C.

**Institución:** FACENA – Universidad Nacional del Nordeste (UNNE).
