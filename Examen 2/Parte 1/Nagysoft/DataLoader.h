#ifndef DATALOADER_H
#define DATALOADER_H

#include <vector>
#include <string>
#include "Coord3D.h"

class DataLoader {
public:
    // Carga los datos desde un archivo CSV a un vector de forma segura
    static std::vector<Coord_3D> loadCSV(const std::string& filename);
};

#endif
