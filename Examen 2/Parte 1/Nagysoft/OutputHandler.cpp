#include "OutputHandler.h"
#include <fstream>
#include <iostream>
#include <iomanip>

bool save_classified_csv(const std::string& filename, const std::vector<Cluster>& clusters) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    char labels[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    for (size_t i = 0; i < clusters.size(); ++i) {
        char current_label = labels[i % 6];
        for (const auto& point : clusters[i].points) {
            file << point.x << "," << point.y << "," << point.z << "," << current_label << "\n";
        }
    }
    file.close();
    return true;
}

bool save_summary_txt(const std::string& filename, const std::vector<Cluster>& clusters) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    char labels[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    file << std::fixed << std::setprecision(5);

    // Formato exacto de Molde Empresarial: Letra: N, (x, y, z), MD
    for (size_t i = 0; i < clusters.size(); ++i) {
        char current_label = labels[i % 6];
        size_t n_points = clusters[i].points.size();
        Coord_3D c = clusters[i].centroid;
        double md = clusters[i].dispersion;

        file << current_label << ": " << n_points << ", (" 
             << c.x << ", " << c.y << ", " << c.z << "), " << md << "\n";
    }

    file.close();
    return true;
}
