#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "DataLoader.h"
#include "KMeans.h"
#include "DataWriter.h"

int main(int argc, char* argv[]) {
    // Validación rigurosa de los parámetros de invocación de línea de comandos
    if (argc < 3) {
        std::cerr << "Uso correcto: " << argv[0] << " <k> <datos>\n"; // Ejemplo: cluster 3 datos.csv
        return 1;
    }

    int k = std::atoi(argv[1]);
    std::string dataFile = argv[2];

    if (k <= 0 || k > 6) { // Regla de negocio restrictiva del Dr. Szilard
        std::cerr << "Error: El número de clusters (k) debe estar entre 1 y 6.\n";
        return 1;
    }

    try {
        // 1. Carga de datos aislada
        std::vector<Coord_3D> dataset = DataLoader::loadCSV(dataFile);
        
        // 2. Ejecución del algoritmo
        KMeans engine(k);
        std::vector<Labeled> results;
        std::vector<ClusterInfo> summaryData;
        
        engine.run(dataset, results, summaryData);
        
        // 3. Serialización y salida en archivos independientes
        DataWriter::writeClassifiedCSV("clasificados.csv", results); //
        DataWriter::writeSummaryTXT("summary.txt", summaryData);     //
        
        std::cout << "Proceso completado exitosamente con k=" << k << ".\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Excepción atrapada en ejecución: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
