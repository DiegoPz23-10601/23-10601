#include "DataWriter.h"
#include <fstream>
#include <iomanip>
#include <iostream>

void DataWriter::writeClassifiedCSV(const std::string& filename, const std::vector<Labeled>& labeledData) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << std::fixed << std::setprecision(6);
    for (const auto& pt : labeledData) {
        file << pt.coord.x << "," << pt.coord.y << "," << pt.coord.z << "," << pt.label << "\n"; // Con etiqueta
    }
    file.close();
}

void DataWriter::writeSummaryTXT(const std::string& filename, const std::vector<ClusterInfo>& summary) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << std::fixed << std::setprecision(6);
    for (const auto& info : summary) {
        // Cumple de manera idéntica con el formato: Letra: N, (x, y, z), MD
        file << info.label << ": " 
             << info.pointCount << ", (" 
             << info.centroid.x << ", " 
             << info.centroid.y << ", " 
             << info.centroid.z << "), " 
             << info.dispersion << "\n";
    }
    file.close();
}
