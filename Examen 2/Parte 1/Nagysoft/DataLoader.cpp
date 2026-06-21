#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool load_csv_data(const std::string& filename, std::vector<Coord_3D>& data_vector) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error corporativo: No se pudo abrir el archivo: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue; // Evita líneas en blanco al final

        std::stringstream ss(line);
        std::string valX, valY, valZ;

        // Procesa el formato separado por comas puro
        if (std::getline(ss, valX, ',') && 
            std::getline(ss, valY, ',') && 
            std::getline(ss, valZ, ',')) {
            
            Coord_3D point;
            point.x = std::stod(valX);
            point.y = std::stod(valY);
            point.z = std::stod(valZ);
            
            data_vector.push_back(point);
        }
    }

    file.close();
    return true;
}
