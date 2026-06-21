#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include "types.h"

// Estructura interna para almacenar clusters
struct Cluster {
    Coord_3D centroid;
    std::vector<Coord_3D> points;
    double dispersion; 
};

double calculate_distance(const Coord_3D& p1, const Coord_3D& p2);

// Condición de parada encapsulada exigida por el Dr. Szilard
bool should_stop(const std::vector<Coord_3D>& old_centroids, 
                 const std::vector<Coord_3D>& new_centroids, 
                 int current_iteration, 
                 int max_iterations);

std::vector<Cluster> run_kmeans(const std::vector<Coord_3D>& data, int k, int max_iterations = 100);

#endif // KMEANS_H
