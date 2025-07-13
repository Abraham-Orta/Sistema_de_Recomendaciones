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
