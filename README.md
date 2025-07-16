# Sistema de Recomendaciones - Tienda en Línea

Este proyecto es una aplicación de escritorio que simula una tienda en línea con un sistema de recomendaciones personalizadas para los usuarios. La lógica del programa está desarrollada en C++ estándar, completamente separada de la interfaz de usuario. Qt se ha utilizado exclusivamente para la implementación de la interfaz gráfica de usuario (GUI).


## Créditos

- Desarrollado por Abraham Orta, Isaac Maluenga y Jhonatan Rodríguez.
- Proyecto académico para la materia Técnicas De Programacion II.


## Características principales

- **Registro e inicio de sesión de usuarios**
- **Gestión de usuarios con árbol binario de búsqueda**
- **Preferencias de productos**: categorías y marcas favoritas por usuario (listas enlazadas propias)
- **Historial de interacciones**: productos comprados y vistos (lista enlazada propia)
- **Catálogo de productos**: más de 100 productos de distintas categorías
- **Filtrado de productos por categoría**
- **Sistema de recomendaciones** basado en historial y preferencias
- **Funcionalidad de "me gusta" y compras**
- **Interfaz gráfica moderna con Qt**
- **Pruebas unitarias con Catch2**


---

## Estructuras de Datos y Funciones Asociadas

### 1. Estructuras de Datos Usadas

Aquí se detallan las principales estructuras de datos personalizadas utilizadas en el proyecto:

*   **`NodoUsuario`**:
    *   **Propósito**: Representa un nodo individual dentro del `ArbolUsuarios`. Cada nodo almacena un `perfil_usuario` y punteros a sus hijos izquierdo y derecho.
    *   **Campos clave**: `perfil_usuario perfil`, `NodoUsuario* izquierda`, `NodoUsuario* derecha`.

*   **`ArbolUsuarios`**:
    *   **Propósito**: Implementa un árbol binario de búsqueda para gestionar de manera eficiente los perfiles de usuario registrados, permitiendo búsquedas, inserciones y eliminaciones rápidas.
    *   **Campos clave**: `NodoUsuario* raiz`.

*   **`NodoString`**:
    *   **Propósito**: Es el bloque fundamental de la `ListaEnlazadaString`. Cada nodo almacena un valor de tipo `std::string` y un puntero al siguiente nodo en la secuencia.
    *   **Campos clave**: `std::string valor`, `NodoString* siguiente`.

*   **`ListaEnlazadaString`**:
    *   **Propósito**: Una implementación propia de una lista enlazada simple diseñada para almacenar colecciones de cadenas de texto. Se utiliza para gestionar preferencias de usuario (categorías, marcas) y el historial de interacciones (productos comprados, productos favoritos, productos recomendados).
    *   **Campos clave**: `NodoString* cabeza`.

*   **`perfil_usuario`**:
    *   **Propósito**: Representa toda la información asociada a un usuario en el sistema. Incluye datos personales, sus preferencias de productos y sus historiales de interacción.
    *   **Campos clave**: `std::string nombre`, `std::string apellido`, `std::string id`, `std::string usuario`, `std::string contraseña`, `PreferenciasProducto preferencias`, `ListaEnlazadaString productos_comprados`, `ListaEnlazadaString productos_favoritos`, `ListaEnlazadaString productos_recomendados`.

*   **`PreferenciasProducto`**:
    *   **Propósito**: Agrupa las preferencias específicas del usuario relacionadas con productos, como sus categorías y marcas favoritas.
    *   **Campos clave**: `ListaEnlazadaString categorias`, `ListaEnlazadaString marcas`.

*   **`Producto`**:
    *   **Propósito**: Define la estructura de un producto disponible en la tienda. Contiene todos los atributos relevantes para la visualización y el sistema de recomendación.
    *   **Campos clave**: `std::string nombre`, `std::string descripcion`, `std::string marca`, `std::string categoria`, `std::string id`, `std::string ruta_imagen`, `double precio`, `int calificacion`.

*   **`ProductoPuntuado`**:
    *   **Propósito**: Estructura auxiliar utilizada en el algoritmo de recomendación para almacenar un producto junto con su puntuación calculada.
    *   **Campos clave**: `Producto producto`, `double puntuacion`.

### 2. Tabla de Funciones Asociadas a las Estructuras

| Estructura de Datos | Funciones Asociadas |
| :------------------ | :------------------ |
| `ArbolUsuarios`     | `insertar(const perfil_usuario& perfil)`: Inserta un perfil de usuario en el árbol.<br>`buscar(const std::string& nombreUsuario)`: Busca un usuario por nombre de usuario.<br>`~ArbolUsuarios()`: Destructor, libera la memoria del árbol. |
| `ListaEnlazadaString` | `ListaEnlazadaString()`: Constructor por defecto.<br>`ListaEnlazadaString(const ListaEnlazadaString& other)`: Constructor de copia.<br>`operator=(const ListaEnlazadaString& other)`: Operador de asignación de copia.<br>`agregar(const std::string& v)`: Añade un valor de cadena a la lista.<br>`limpiar()`: Limpia todos los elementos de la lista y libera la memoria.<br>`contiene(const std::string& valor) const`: Verifica si un valor ya existe en la lista.<br>`~ListaEnlazadaString()`: Destructor, libera la memoria de la lista. |
| `PreferenciasProducto` | `agregarCategoria(const std::string& categoria)`: Añade una categoría a la lista de categorías preferidas.<br>`agregarMarca(const std::string& marca)`: Añade una marca a la lista de marcas preferidas. |

### 3. Análisis de cómo implemento los algoritmos de recomendación por marca y por historial de interacciones.

La función `recomendarProductos` utiliza una estrategia de puntuación para generar recomendaciones personalizadas, combinando múltiples criterios de manera flexible y priorizando ciertos factores mediante pesos.

#### Requisitos y su Abordaje:

1.  **Recomendaciones por Marcas Preferidas (Prioridad Alta)**:
    *   **Implementación**: A cada producto de una marca que el usuario ha marcado como preferida (`preferencias.marcas`) se le asigna una puntuación base muy alta (`PESO_MARCA_PREFERIDA`). Esto asegura que estos productos siempre aparezcan entre las principales recomendaciones.

2.  **Recomendaciones por Historial de Interacciones**:
    *   **Misma Categoría**:
        *   **Implementación**: Se calcula la frecuencia de las categorías de los productos en el historial de compras y favoritos del usuario (`frecuencia_categoria_historial`). Los productos en categorías más frecuentes reciben una puntuación adicional (`PESO_CATEGORIA_HISTORIAL`), proporcional a la relevancia de esa categoría para el usuario.
    *   **Misma Marca**:
        *   **Implementación**: Similar a las categorías, se calcula la frecuencia de las marcas en el historial del usuario (`frecuencia_marca_historial`). Los productos de estas marcas reciben una puntuación adicional (`PESO_MARCA_HISTORIAL`).
    *   **Calidad Similar**:
        *   **Implementación**: Se calcula la calificación promedio de los productos en el historial del usuario (`calificacion_promedio_historial`). Los productos cuya calificación sea cercana a este promedio (dentro de un `UMBRAL_SIMILITUD_CALIDAD`) reciben una puntuación adicional (`PESO_SIMILITUD_CALIDAD`). El boost es mayor cuanto menor sea la diferencia de calidad.

#### Proceso General del Algoritmo:

1.  **Recopilación de Datos Históricos y Preferencias**: Se inicializan mapas para contar la frecuencia de categorías y marcas en el historial de compras y favoritos del usuario. También se calcula la calificación promedio de los productos en el historial.
2.  **Asignación de Puntuación a Productos**: Se itera sobre todos los productos disponibles. Para cada producto, se calcula una `puntuacion` inicial de 0.0. Luego, se aplican los siguientes criterios para aumentar la puntuación:
    *   Si el producto es de una marca preferida por el usuario, se le añade un `PESO_MARCA_PREFERIDA`.
    *   Si hay historial de interacciones, se aplican boosts basados en la frecuencia de la categoría y marca del producto en el historial del usuario, y en la similitud de calidad con el promedio del historial.
    *   Si no hay historial, se da un boost a los productos de categorías preferidas por el usuario.
    *   Los productos que ya han sido comprados o marcados como favoritos son omitidos de las recomendaciones.
3.  **Ordenamiento y Selección**: Los productos se ordenan en una lista (`productos_puntuados`) de forma descendente según su `puntuacion`. Finalmente, se seleccionan los `maxRecomendaciones` productos con las puntuaciones más altas y se añaden a la lista `recomendados`.

---

## Clases, Structs y Funciones principales

### Clases Qt (Interfaz gráfica)
- **VentanaInicial**: Ventana de bienvenida, permite iniciar sesión o registrarse.
- **RegistroDialog**: Diálogo para login de usuario.
- **VentanaPrincipal**: Ventana principal de la tienda, muestra productos, permite comprar, dar me gusta y ver recomendaciones.
- **VentanaPerfil**: Muestra la información del usuario registrado.
- **DialogoRegistroNuevo**: Diálogo para registrar un nuevo usuario.

### Structs y estructuras de datos
- **perfil_usuario**: Representa a un usuario, contiene datos personales, preferencias y listas enlazadas de productos comprados y favoritos.
- **Producto**: Representa un producto de la tienda (nombre, descripción, marca, categoría, id, precio, calificación).
- **NodoString / ListaEnlazadaString**: Implementación propia de lista enlazada simple para cadenas, usada en preferencias y en historial de interacciones.
- **PreferenciasProducto**: Engloba las listas enlazadas de categorías y marcas preferidas por el usuario.
- **NodoUsuario / ArbolUsuarios**: Árbol binario de búsqueda para gestionar usuarios registrados.

### Funciones principales
- **filtrarPorCategoria**: Filtra productos por categoría.
- **recomendarProductos**: Genera recomendaciones personalizadas según historial y preferencias del usuario.
- **insertarUsuario / buscarUsuario / destruirArbol**: Funciones para manipular el árbol de usuarios (en la versión sin métodos miembro) o métodos en el struct ArbolUsuarios (en la versión con métodos miembro).
- **Métodos de ListaEnlazadaString**: agregar, liberar memoria, recorrer, etc.
- **Métodos de PreferenciasProducto**: agregarCategoria, agregarMarca.

### Pruebas unitarias
- **test_filtros.cpp**: Pruebas para la función de filtrado de productos por categoría usando Catch2.

---

## Estructura del proyecto

```
├── include/                # Archivos de cabecera (.h)
│   ├── arbol_usuarios.h
│   ├── catch.hpp
│   ├── dialogo_registro_nuevo.h
│   ├── filtros.h
│   ├── lista_productos.h
│   ├── nodo_string.h
│   ├── perfil_usuario.h
│   ├── preferencias_dialogo.h
│   ├── preferencias_producto.h
│   ├── producto.h
│   ├── recomendaciones.h
│   ├── registro_dialog.h
│   ├── ventana_inicial.h
│   ├── ventana_perfil.h
│   └── ventana_principal.h
├── src/                    # Archivos fuente (.cpp)
│   ├── arbol_usuarios.cpp
│   ├── dialogo_registro_nuevo.cpp
│   ├── filtros.cpp
│   ├── main.cpp
│   ├── nodo_string.cpp
│   ├── preferencias_dialogo.cpp
│   ├── recomendaciones.cpp
│   ├── registro_dialog.cpp
│   ├── test_filtros.cpp
│   ├── ventana_inicial.cpp
│   ├── ventana_perfil.cpp
│   └── ventana_principal.cpp
├── img/                    # Imágenes de productos
│   ├── cuidado personal y belleza/
│   ├── deportes y aire libre/
│   ├── electronica/
│   ├── hogar y cocina/
│   └── moda y accesorios/
├── CMakeLists.txt          # Configuración de compilación
├── README.md               # Este archivo
├── resources.qrc           # Archivo de recursos de Qt
├── styles.qss              # Hoja de estilos para el tema oscuro
├── styles_light.qss        # Hoja de estilos para el tema claro
└── .git/                   # Repositorio Git
```

## Requisitos

- CMake >= 3.14
- Qt6 (Widgets)
- Compilador C++17 (g++ recomendado)

## Compilación y ejecución

1. Clona el repositorio:
   ```sh
   git clone git@github.com:Abraham-Orta/Sistema_de_Recomendaciones.git
   cd sistema_de_recomendaciones
   ```
2. Crea la carpeta de compilación y compila:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Ejecuta la aplicación:
   ```sh
   ./sistema_de_recomendaciones
   ```

## Pruebas unitarias

El proyecto incluye pruebas unitarias con Catch2:

```sh
./test_filtros
```

## Descripción Detallada del Código Fuente

A continuación se detalla la funcionalidad de los archivos de cabecera y fuente más importantes del proyecto.

### `arbol_usuarios.h` / `arbol_usuarios.cpp`
Gestiona los perfiles de usuario utilizando un árbol binario de búsqueda para un acceso y gestión eficientes.
- **`struct NodoUsuario`**: Representa un nodo en el árbol, conteniendo un `perfil_usuario` y punteros a los hijos.
- **`class ArbolUsuarios`**: El árbol de búsqueda binario.
    - `insertar(const perfil_usuario& perfil)`: Añade un nuevo usuario al árbol.
    - `buscar(const std::string& nombreUsuario)`: Busca un usuario por su nombre de usuario.
    - `destruir(NodoUsuario* nodo)`: Función auxiliar recursiva para liberar la memoria del árbol.
    - `~ArbolUsuarios()`: Destructor, libera la memoria del árbol.

### `filtros.h` / `filtros.cpp`
Contiene la lógica para filtrar productos por diversas características.
- `filtrarPorCategoria(const std::vector<Producto>& productos, const std::string& categoria)`: Devuelve un vector de productos que pertenecen a una categoría específica.
- `FiltrarPorPrecio(const std::vector<Producto>& productos, const std::string& rangoPrecio)`: Filtra productos basándose en rangos de precios predefinidos.
- `filtrarDescripcion(const std::vector<Producto>& productos, const std::string& filtroDescrip)`: Filtra productos buscando una cadena en su nombre, descripción o marca (búsqueda insensible a mayúsculas/minúsculas).

### `recomendaciones.h` / `recomendaciones.cpp`
Implementa el motor de recomendaciones.
- `bool estaEnLista(const ListaEnlazadaString& lista, const std::string& id)`: Función auxiliar que verifica si un ID de producto está presente en una `ListaEnlazadaString`.
- `recomendarProductos(ListaEnlazadaString& recomendados, const std::vector<Producto>& todos, const ListaEnlazadaString& comprados, const ListaEnlazadaString& favoritos, const PreferenciasProducto& preferencias, size_t maxRecomendaciones)`: Genera una lista de productos recomendados para un usuario basándose en su historial de compras, "me gusta" y preferencias.

### `nodo_string.h` / `nodo_string.cpp`
Implementa una lista enlazada simple para almacenar cadenas de texto.
- **`struct NodoString`**: Nodo de la lista, contiene un `std::string` y un puntero al siguiente nodo.
- **`class ListaEnlazadaString`**: La estructura de la lista enlazada.
    - `ListaEnlazadaString()`: Constructor por defecto.
    - `ListaEnlazadaString(const ListaEnlazadaString& other)`: Constructor de copia.
    - `ListaEnlazadaString& operator=(const ListaEnlazadaString& other)`: Operador de asignación de copia.
    - `~ListaEnlazadaString()`: Destructor, libera la memoria de la lista.
    - `agregar(const std::string& v)`: Añade un elemento al final de la lista.
    - `limpiar()`: Elimina todos los nodos de la lista.
    - `contiene(const std::string& valor) const`: Verifica si un valor ya existe en la lista.

### Clases de la Interfaz Gráfica (UI)

- **`VentanaInicial` (`ventana_inicial.h/.cpp`)**: Es la primera ventana que ve el usuario. Ofrece las opciones de iniciar sesión o registrarse.
    - `VentanaInicial(ArbolUsuarios* arbol, QWidget *parent = nullptr)`: Constructor que recibe el árbol de usuarios.
    - `abrirDialogoLogin()`: Abre el diálogo de inicio de sesión.
    - `abrirDialogoRegistro()`: Abre el diálogo de registro de nuevo usuario.
    - `toggleTema()`: Cambia entre el tema claro y oscuro de la aplicación.

- **`RegistroDialog` (`registro_dialog.h/.cpp`)**: Diálogo para que un usuario existente inicie sesión.
    - `RegistroDialog(ArbolUsuarios* arbol, QWidget *parent = nullptr)`: Constructor que recibe el árbol de usuarios.
    - `accept()`: Slot que se ejecuta al aceptar el diálogo, valida los campos.
    - `obtenerUsuario() const`: Devuelve el nombre de usuario ingresado.
    - `obtenerContraseña() const`: Devuelve la contraseña ingresada.

- **`DialogoRegistroNuevo` (`dialogo_registro_nuevo.h/.cpp`)**: Diálogo para registrar un nuevo usuario.
    - `DialogoRegistroNuevo(ArbolUsuarios* arbol, QWidget *parent = nullptr)`: Constructor que recibe el árbol de usuarios.
    - `accept()`: Slot que se ejecuta al aceptar el diálogo, valida los campos y registra el nuevo usuario.

- **`VentanaPrincipal` (`ventana_principal.h/.cpp`)**: La ventana principal de la aplicación, visible después de iniciar sesión. Muestra productos, permite filtrar, comprar, marcar como favorito y ver recomendaciones.
    - `VentanaPrincipal(perfil_usuario& usuario, QWidget *parent = nullptr)`: Constructor que recibe el perfil del usuario actual.
    - `mostrarProductos(const std::vector<Producto>& productosAMostrar)`: Actualiza la visualización de productos en el grid.
    - `actualizarRecomendaciones()`: Llama al motor de recomendaciones y actualiza la lista de productos recomendados del usuario.
    - `aplicarFiltrosYMostrarProductos()`: Aplica todos los filtros seleccionados (categoría, precio, descripción) y actualiza la vista de productos.
    - `toggleTema()`: Cambia entre el tema claro y oscuro de la aplicación.

- **`VentanaPerfil` (`ventana_perfil.h/.cpp`)**: Muestra la información detallada del perfil del usuario, incluyendo sus productos comprados y favoritos.
    - `VentanaPerfil(const perfil_usuario& perfil, const std::vector<Producto>& todosLosProductos, QWidget *parent = nullptr)`: Constructor que recibe el perfil del usuario y la lista completa de productos.
    - `llenarTabla(QTableWidget* tabla, const ListaEnlazadaString& idsProductos, const std::vector<Producto>& todosLosProductos)`: Función auxiliar para poblar las tablas de productos comprados y favoritos.

- **`PreferenciasDialogo` (`preferencias_dialogo.h/.cpp`)**: Permite al usuario seleccionar sus categorías y marcas preferidas.
    - `PreferenciasDialogo(QWidget *parent = nullptr)`: Constructor.
    - `getCategoriasSeleccionadas() const`: Devuelve un vector de las categorías seleccionadas por el usuario.
    - `getMarcasSeleccionadas() const`: Devuelve un vector de las marcas seleccionadas por el usuario.

### `main.cpp`
El punto de entrada de la aplicación.
- `main(int argc, char *argv[])`: Inicializa la aplicación Qt, carga la hoja de estilos, crea un usuario de prueba y muestra la `VentanaInicial`.

---

## Licencia

Este proyecto es de uso académico y educativo.
