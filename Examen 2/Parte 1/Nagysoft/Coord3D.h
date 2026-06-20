#ifndef COORD3D_H
#define COORD3D_H

// Estructura obligatoria requerida por el Dr. Szilard
struct Coord_3D {
    double x;
    double y;
    double z;
};

// Estructura opcional pero recomendada para la salida etiquetada
struct Labeled {
    Coord_3D coord;
    char label;
};

#endif
