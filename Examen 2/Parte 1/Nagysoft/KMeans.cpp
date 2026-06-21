#include "KMeans.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

double calculate_distance(const Coord_3D& p1, const Coord_3D& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + 
                     std::pow(p1.y - p2.y, 2) + 
                     std::pow(p1.z - p2.z, 2));
}

/**
 * CONDICIÓN DE PARADA ENCAPSULADA
 * - Parámetros: Centroides viejos, nuevos, iteración actual y límite máximo.
 * - Justificación Técnica: Evalúa si el desplazamiento de los centros cayó por debajo
 * de un umbral de tolerancia mínimo (0.0001). Si ya no se mueven, continuar ejecutando
 * ciclos desperdiciaría CPU. Incluye un límite máximo por seguridad ante oscilaciones.
 */
bool should_stop(const std::vector<Coord_3D>& old_centroids, 
                 const std::vector<Coord_3D>& new_centroids, 
                 int current_iteration, 
                 int max_iterations) {
    if (current_iteration >= max_iterations) return true;
    if (old_centroids.empty()) return false;

    double tolerance = 1e-4; 
    for (size_t i = 0; i < old_centroids.size(); ++i) {
        if (calculate_distance(old_centroids[i], new_centroids[i]) > tolerance) {
            return false; 
        }
    }
    return true; 
}

std::vector<Cluster> run_kmeans(const std::vector<Coord_3D>& data, int k, int max_iterations) {
    int n = data.size();
    std::vector<Cluster> clusters(k);
    std::vector<Coord_3D> centroids(k);

    std::srand(std::time(0));
    for (int i = 0; i < k; ++i) {
        centroids[i] = data[std::rand() % n];
    }

    int iteration = 0;
    std::vector<Coord_3D> old_centroids;

    while (!should_stop(old_centroids, centroids, iteration, max_iterations)) {
        old_centroids = centroids;

        for (int i = 0; i < k; ++i) {
            clusters[i].points.clear();
        }

        // Asignación de puntos
        for (const auto& point : data) {
            int best_cluster = 0;
            double min_dist = calculate_distance(point, centroids[0]);

            for (int i = 1; i < k; ++i) {
                double dist = calculate_distance(point, centroids[i]);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_cluster = i;
                }
            }
            clusters[best_cluster].points.push_back(point);
        }

        // Actualización de centroides
        for (int i = 0; i < k; ++i) {
            if (clusters[i].points.empty()) continue;

            double sum_x = 0, sum_y = 0, sum_z = 0;
            for (const auto& p : clusters[i].points) {
                sum_x += p.x; sum_y += p.y; sum_z += p.z;
            }
            size_t num_points = clusters[i].points.size();
            centroids[i].x = sum_x / num_points;
            centroids[i].y = sum_y / num_points;
            centroids[i].z = sum_z / num_points;
            clusters[i].centroid = centroids[i];
        }

        iteration++;
    }

    // Medida de dispersión estadística (MD) final
    for (int i = 0; i < k; ++i) {
        if (clusters[i].points.empty()) {
            clusters[i].dispersion = 0.0;
            continue;
        }
        double total_dist = 0.0;
        for (const auto& p : clusters[i].points) {
            total_dist += calculate_distance(p, clusters[i].centroid);
        }
        clusters[i].dispersion = total_dist / clusters[i].points.size();
    }

    std::cout << "Algoritmo finalizado de forma limpia en " << iteration << " iteraciones." << std::endl;
    return clusters;
