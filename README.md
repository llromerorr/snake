# 🐍 Snake Game en C++ con MiniWin  
*Un clásico reinventado: Implementación eficiente con técnicas modernas de C++*

![Demo del Juego](https://github.com/llromerorr/snake/blob/master/Resource/img1.gif)

## 🚀 Características Principales
- **Motor gráfico ligero** usando MiniWin para renderizado rápido
- **Sistema de colisiones avanzado**: Wrap-around en bordes y detección cuerpo-cabeza
- **Generación inteligente de comida**: Evita spawn en el cuerpo de la serpiente
- **Control de tiempo preciso**: Lógica de actualización a 60 FPS
- **Arquitectura modular**: Clases independientes para fácil mantenimiento

## 🧩 Estructura del Proyecto
```
src/
├── headers/
│   ├── Game.hpp          // Control central del juego
│   ├── Snake.hpp         // Lógica de movimiento y crecimiento
│   ├── FoodGenerator.hpp // Generación procedural de comida
│   ├── Screen.hpp        // Abstracción gráfica con MiniWin
│   ├── Pixel.hpp         // Sistema de renderizado de elementos
│   ├── HandleInput.hpp   // Gestión de entradas de usuario
│   └── Root.hpp          // Clases base (Position, Color)
├── main.cpp              // Inicialización y loop principal
└── random.hpp           // Sistema avanzado de aleatoriedad

Recursos/
├── icon.rc              // Configuración del ícono
└── icon.o               // Icono compilado
```

## 🛠️ Tecnologías Clave
- **Lenguaje**: C++17 (Features modernos como templates y STL)
- **Bibliotecas**:
  - MiniWin (Gestión de ventanas/input)
  - STL (`vector`, algoritmos, iteradores)
- **Paradigmas**:
  - Programación orientada a objetos
  - Gestión manual de memoria
  - Sistema de coordenadas personalizado
- **Compatibilidad**: Windows (Compilado con MinGW)

## 🔧 Compilación y Ejecución
1. **Requisitos**:
   - Compilador C++17 (MinGW recomendado)
   - Windows SDK básico

2. **Compilar proyecto**:
```
windres Resource/icon.rc Resource/icon.o && g++ main.cpp miniwin.cpp -static Resource/icon.o -mwindows -o Snak3
```

3. **Ejecutar**:
```bash
Snak3.exe
```

## 🎮 Controles
- **Flechas direccionales**: Movimiento de la serpiente
- **ESC**: Menú de pausa/salida
- **Clic izquierdo**: Interacción en menús

## 📌 Próximas Mejoras
- [ ] Sistema de puntuación con tabla de records
- [ ] Diferentes niveles de dificultad
- [ ] Efectos visuales adicionales
- [ ] Soporte para más sistemas operativos

---

🛠️ **Dependencias principales**:  
- [MiniWin](https://github.com/pauek/MiniWin) por @pauek  
- [Random](https://github.com/effolkronium/random) por effolkronium

📥 **Descarga para Windows**:  
[Última versión estable](https://github.com/CreyTuning/Snake/releases)