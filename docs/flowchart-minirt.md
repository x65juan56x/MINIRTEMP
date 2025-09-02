# miniRT — Flowcharts y guía de enfoque

Este documento resume el pipeline de miniRT (mandatorio + bonus) y el flujo del parser de escenas `.rt`.

## Flowchart principal

```mermaid
flowchart TD
    A[Start] --> B[Args: ruta a .rt]
    B --> C[Leer archivo .rt]
    C --> D{Validar escena}
    D -- No --> E[Error\n<mensaje> y exit]
    D -- Sí --> F[Construir escena &#40A, C, L, objetos&#41]
    F --> G[Init MLX: ventana + imagen]
    G --> H[Render frame]
    H --> I[Loop por píxeles &#40x,y&#41]
    I --> J[Ray primario desde cámara -> píxel]
    J --> K[Intersecciones: t más cercano > ε]
    K --> L{¿Hit?}
    L -- No --> M[Color fondo]
    L -- Sí --> N[Shading]
    N --> N1[Ambiente &#40A&#41]
    N --> N2[Difuso &#40Lambert&#41 por luces visibles]
    N2 --> S1{Shadow ray bloqueado?}
    S1 -- Sí --> N3[Sólo ambiente]
    S1 -- No --> N4[Sumar difuso]
    N4 --> O[Escribir píxel]
    M --> O
    O --> P{¿Más píxeles?}
    P -- Sí --> I
    P -- No --> Q[Blit imagen a ventana]
    Q --> R[Event loop: ESC / Close -> cleanup -> exit]

    subgraph Intersections
        K --> IS[Sphere]
        K --> IP[Plane]
        K --> IC[Cylinder &#40cuerpo + tapas&#41]
        IS --> K
        IP --> K
        IC --> K
    end

    subgraph Transforms
        F --> T1[Aplicar traslación/rotaciones a objetos y cámara]
    end

    subgraph Bonus
        N --> B1[Specular &#40Phong&#41]
        N --> B2[Checkerboard / color disruption]
        F --> B3[Luces múltiples y coloreadas]
        K --> B4[Otro quad. &#40p.ej. Cone&#41]
        N --> B5[Bump mapping &#40perturbar normales&#41]
    end
```

Notas clave:
- Validación: A, C, L únicos; rangos válidos; vectores normalizados; colores 0–255; FOV 0–180.
- Transformaciones: esfera y luces sin rotación; resto sí. Usa sistema coherente (espacio mundo u objeto).
- Sombras duras: shadow ray con bias ε para evitar acne; bloquear si intersección en (ε, dist_luz).

## Flowchart del parser `.rt`

```mermaid
flowchart LR
    A[Línea .rt] --> B[Trim + skip vacías/comentarios]
    B --> C{Identificador}
    C -->|A| A1[ratio + color] --> V[Acumular y validar único]
    C -->|C| C1[pos + dir_norm + FOV] --> V
    C -->|L| L1[pos + intensidad + color?] --> V
    C -->|sp| S1[center + diámetro + color] --> V
    C -->|pl| P1[punto + normal_norm + color] --> V
    C -->|cy| Y1[center + axis_norm + diámetro + altura + color] --> V
    C -->|desconocido| E[Error]
    V --> D{Rangos/Norm/Format OK?}
    D -- No --> E[Error\n<mensaje>]
    D -- Sí --> F[Agregar a escena]
```

## Orden de implementación sugerido

1) Matemáticas base: vec3, dot, cross, normalización, ray.
2) Intersecciones: sphere, plane, cylinder (cuerpo + tapas) con ε, t_min/t_max.
3) Parser + validaciones + modelo de datos de escena.
4) Cámara: generación de rayos primarios y render scanline.
5) Iluminación: ambiente + difuso + sombras duras.
6) MLX: ventana, imagen, eventos (ESC/red cross), cleanup.

Bonus (en este orden práctico):
- Specular (Phong) y clamping de color.
- Checkerboard en `pl` (y opcional UV simples en `sp`/`cy`).
- Luces múltiples y coloreadas (sumatoria por luz con visibilidad).
- Nuevo objeto (cone): intersección + normal + tapas.
- Bump mapping: perturbar normal (mapa o procedural) antes del BRDF.

---
Sugerencia: añade un pequeño `ε = 1e-4` para evitar self-intersections y usa `t_min = ε`, `t_max = INF` en todas las pruebas de intersección y sombras.
