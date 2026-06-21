#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "types.h"
#include "DataLoader.h"
#include "KMeans.h"
#include "OutputHandler.h"

int main(int argc, char* argv[]) {
    // Validación estricta de parámetros
    if (argc != 3) {
        std::cerr << "Uso reglamentario: " << argv[0] << " <k> <archivo_datos>" << std::endl;
        return 1;
    }

    int k = std::atoi(argv[1]);
    std::string filename = argv[2];

    if (k < 1 || k > 6) {
        std::cerr << "Error: El numero de clusters k debe estar entre 1 y 6." << std::endl;
        return 1;
    }

    std::vector<Coord_3D> original_data;
    std::cout << "Iniciando carga de datos..." << std::endl;
    if (!load_csv_data(filename, original_data)) {
        return 1;
    }
    std::cout << "Dataset cargado con exito. Puntos leidos: " << original_data.size() << std::endl;

    std::cout << "Corriendo algoritmo clustering K-Means..." << std::endl;
    std::vector<Cluster> result_clusters = run_kmeans(original_data, k);

    std::cout << "Exportando artefactos de salida..." << std::endl;
    if (save_classified_csv("clasificados.csv", result_clusters) &&
        save_summary_txt("summary.txt", result_clusters)) {
        std::cout << ">> PROCESO CORPORATIVO EXITOSO. Archivos creados correctamente." << std::endl;
    } else {
        std::cerr << "Error critico al guardar los resultados." << std::endl;
        return 1;
    }

    return 0;
}