# Trafico
[English](#english) · [Español](#español)

## English


> [!WARNING]
> **Status: Legacy.** Archived Win32 exercise that runs with simulated cars and roads.

Legacy Windows simulation of cars, road intersections and traffic light timing

### Overview

Trafico helps a learner see how the rules at an intersection affect the cars approaching it. The scene draws roads, vehicles and signal colours on screen. The May release initializes a small grid of roads and sends simulated cars between positions. Its counters show how many still have to finish and how many arrived.

### Features

- Shows cars moving through the simulated road network.
- Draws green and red signals and updates counters as the simulation advances.
- Routes cars between positions and counts the ones that reach their destinations.

### Requirements

- Windows desktop, Visual Studio Community 2026 18.10.3, MSVC v145, MFC x86 and Windows SDK 10.0.26100.0. Build for Win32. The simulation uses the Windows graphics APIs.

### Getting started

In Developer PowerShell for Visual Studio, run the following from the repository root.

```powershell
MSBuild Trafico.sln /m:2 /nr:false /t:Rebuild /p:Configuration=Release /p:Platform=Win32
.\bin\Release\Trafico.exe
```

### Usage

Launch `Trafico.exe`. The roads, vehicles and traffic lights start moving as soon as the window opens. Watch **Faltan** (cars still travelling) and **Llegaron** (cars that arrived).

### Project structure

`TraficoView.cpp` draws the scene and advances the simulation. `Carretera` describes a road and `Semaforo` implements a signal. `Ruta` and `Nodo` describe paths and places where they connect.

### Support

Describe the commit, toolchain, window size and junction when reporting a problem. Use a copy of the recovered project for the steps to reproduce it.

### Contributing

Build the Win32 solution and compare vehicle motion and signal settings before making changes to the model. Keep the original archive dates and credits with historical revisions.

### History

The latest source entries in `Traficov1.rar` are dated 19 May 2006. The timestamp uses that date at 12:00 UTC because the archive does not record a Git commit time.

### License

The project’s own code and documentation use the [MIT license](LICENSE).

---

## Español


> [!WARNING]
> **Estado: Legado.** Ejercicio Win32 archivado con autos y calles simulados.

Legado de Windows para simular autos, cruces y tiempos de semáforos

### Descripción general

Trafico permite observar cómo las reglas de un cruce afectan a los autos que se acercan. Dibuja las calles, los vehículos y el color de cada semáforo en la pantalla. La versión de mayo prepara una cuadrícula de calles y mueve autos ficticios entre distintos puntos. Los contadores muestran cuántos faltan por llegar y cuántos llegaron.

### Funciones

- Muestra autos que avanzan por una red de calles ficticia.
- Dibuja las señales en verde y rojo y actualiza los contadores mientras avanza.
- Traza rutas entre posiciones y cuenta los autos que llegan a su destino.

### Requisitos

- Windows de escritorio, Visual Studio Community 2026 18.10.3, MSVC v145, MFC x86 y el SDK de Windows 10.0.26100.0. Compila para Win32. La simulación usa las funciones gráficas de Windows.

### Cómo empezar

En Developer PowerShell para Visual Studio, ejecuta lo siguiente desde la raíz del repositorio.

```powershell
MSBuild Trafico.sln /m:2 /nr:false /t:Rebuild /p:Configuration=Release /p:Platform=Win32
.\bin\Release\Trafico.exe
```

### Uso

Abre `Trafico.exe`. Las calles, autos y semáforos aparecen al iniciar la ventana. Observa **Faltan**, que cuenta los autos aún en camino, y **Llegaron**, que cuenta los que terminaron la ruta.

### Estructura del proyecto

`TraficoView.cpp` dibuja la escena y hace avanzar la simulación. `Carretera` describe una calle y `Semaforo` implementa una señal. `Ruta` y `Nodo` describen los recorridos y los puntos donde se conectan.

### Soporte

Indica el commit, las herramientas, el tamaño de la ventana y el cruce cuando reportes un problema. Usa una copia del proyecto recuperado para reproducirlo.

### Contribuir

Compila la solución Win32 y compara el movimiento de los autos y los ajustes de los semáforos antes de cambiar el modelo. Conserva las fechas de respaldo y las atribuciones de las revisiones históricas.

### Historial

Los archivos fuente más recientes de `Traficov1.rar` son del 19 de mayo de 2006. Se usó esa fecha a las 12:00 UTC porque el respaldo no conserva una hora de commit en Git.

### Licencia

El código y la documentación propios se rigen por la [licencia MIT](LICENSE).
