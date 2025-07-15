# Sistema de Recomendaciones - Tienda en Línea

Este proyecto es una aplicación de escritorio desarrollada en C++ y Qt que simula una tienda en línea con sistema de recomendaciones personalizadas para los usuarios.

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

### 2. Tabla de Funciones Asociadas a las Estructuras

| Estructura de Datos | Funciones Asociadas |
| :------------------ | :------------------ |
| `ArbolUsuarios`     | `insertar(const perfil_usuario& perfil)`: Inserta un perfil de usuario en el árbol.<br>`buscar(const std::string& nombreUsuario)`: Busca un usuario por nombre de usuario.<br>`destruir(NodoUsuario* nodo)`: Destruye recursivamente los nodos del árbol (usado por el destructor).<br>`~ArbolUsuarios()`: Destructor, libera la memoria del árbol. |
| `ListaEnlazadaString` | `ListaEnlazadaString()`: Constructor por defecto.<br>`ListaEnlazadaString(const ListaEnlazadaString& other)`: Constructor de copia.<br>`operator=(const ListaEnlazadaString& other)`: Operador de asignación de copia.<br>`agregar(const std::string& v)`: Añade un valor de cadena a la lista.<br>`limpiar()`: Limpia todos los elementos de la lista y libera la memoria.<br>`~ListaEnlazadaString()`: Destructor, libera la memoria de la lista. |
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
│   ├── dialogo_registro_nuevo.h
│   ├── filtros.h
│   ├── lista_productos.h
│   ├── nodo_string.h
│   ├── perfil_usuario.h
│   ├── preferencias_producto.h
│   ├── producto.h
│   ├── recomendaciones.h
│   ├── registro_dialog.h
│   ├── ventana_inicial.h
│   ├── ventana_perfil.h
│   ├── ventana_principal.h
│   └── catch.hpp
├── src/                    # Archivos fuente (.cpp)
│   ├── arbol_usuarios.cpp
│   ├── dialogo_registro_nuevo.cpp
│   ├── main.cpp
│   ├── registro_dialog.cpp
│   ├── test_filtros.cpp
│   ├── ventana_inicial.cpp
│   ├── ventana_perfil.cpp
│   └── ventana_principal.cpp
├── CMakeLists.txt          # Configuración de compilación
├── README.md               # Este archivo
└── ...
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

## Créditos

- Desarrollado por Abraham Orta, Isaac Maluenga y Jhonatan Rodríguez.
- Proyecto académico para la materia Técnicas De Programacion II.

## Licencia

Este proyecto es de uso académico y educativo.