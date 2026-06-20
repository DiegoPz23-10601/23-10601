#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

std::vector<Coord_3D> DataLoader::loadCSV(const std::string& filename) {
    std::vector<Coord_3D> data;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Error: No se pudo abrir el archivo " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string valX, valY, valZ;
        
        if (std::getline(ss, valX, ',') && 
            std::getline(ss, valY, ',') && 
            std::getline(ss, valZ, ',')) {
            
            Coord_3D pt;
            pt.x = std::stod(valX);
            pt.y = std::stod(valY);
            pt.z = std::stod(valZ);
            data.push_back(pt);
        }
    }
    file.close();
    return data;
}
