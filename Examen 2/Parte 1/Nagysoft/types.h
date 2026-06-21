#ifndef TYPES_H
#define TYPES_H

// Estructura corporativa obligatoria para puntos en 3D
struct Coord_3D {
    double x;
    double y;
    double z;
};

// Estructura sugerida para manejar los puntos etiquetados
struct Labeled {
    Coord_3D coord;
    char label;
};

#endif // TYPES_H
