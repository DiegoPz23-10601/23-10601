#include "KMeans.h"
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>

KMeans::KMeans(int clusterCount) : k(clusterCount) {
    std::srand(42); // Semilla fija para asegurar reproducibilidad en las pruebas
}

double KMeans::computeDistance(const Coord_3D& p1, const Coord_3D& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + 
                     std::pow(p1.y - p2.y, 2) + 
                     std::pow(p1.z - p2.z, 2)); // Distancia Euclidiana
}

/*
 * CONDICIÓN DE PARADA ENCAPSULADA
 * Explicación de parámetros:
 * - oldCentroids / newCentroids: vectores de posiciones de los centros en la iteración t y t-1.
 * - tolerance: umbral mínimo de cambio geométrico permitido.
 * - iteration / maxIterations: contadores de control para evitar bucles infinitos.
 *
 * Justificación de por qué es una buena condición:
 * Garantiza eficiencia y convergencia estable. Si el desplazamiento de TODOS los centroides es
 * menor que la tolerancia (e.g., 1e-6), significa que el algoritmo alcanzó un óptimo local y continuar
 * iterando gastaría ciclos de CPU innecesariamente sin alterar la clasificación. El límite máximo de
 * iteraciones actúa como salvaguarda matemática.
 */
bool KMeans::hasConverged(const std::vector<Coord_3D>& oldCentroids, 
                          const std::vector<Coord_3D>& newCentroids, 
                          double tolerance, int iteration, int maxIterations) {
    if (iteration >= maxIterations) return true;
    if (oldCentroids.size() != newCentroids.size()) return false;
    
    for (size_t i = 0; i < oldCentroids.size(); ++i) {
        if (computeDistance(oldCentroids[i], newCentroids[i]) > tolerance) {
            return false; // Al menos un centroide se movió significativamente
        }
    }
    return true; // Todos los centroides se mantuvieron estables
}

void KMeans::run(const std::vector<Coord_3D>& data, 
                 std::vector<Labeled>& outLabeledData, 
                 std::vector<ClusterInfo>& outSummary) {
    
    if (data.empty() || k <= 0) return;

    // 1. Inicialización de Centroides (Método Forgy Simplificado)
    std::vector<Coord_3D> centroids(k);
    for (int i = 0; i < k; ++i) {
        centroids[i] = data[(i * (data.size() / k)) % data.size()];
    }

    std::vector<int> assignments(data.size(), -1);
    std::vector<Coord_3D> oldCentroids;
    
    int iteration = 0;
    int maxIterations = 300;
    double tolerance = 1e-6;

    // Bucle principal de optimización
    while (!hasConverged(oldCentroids, centroids, tolerance, iteration, maxIterations)) {
        oldCentroids = centroids;
        iteration++;

        // Paso de Asignación: Buscar centroide más cercano
        for (size_t i = 0; i < data.size(); ++i) {
            double minDistance = std::numeric_limits<double>::max();
            int bestCluster = 0;
            
            for (int j = 0; j < k; ++j) {
                double dist = computeDistance(data[i], centroids[j]);
                if (dist < minDistance) {
                    minDistance = dist;
                    bestCluster = j;
                }
            }
            assignments[i] = bestCluster;
        }

        // Paso de Actualización: Recalcular medias aritméticas
        std::vector<Coord_3D> sumCentroids(k, {0.0, 0.0, 0.0});
        std::vector<int> counts(k, 0);

        for (size_t i = 0; i < data.size(); ++i) {
            int clusterIdx = assignments[i];
            sumCentroids[clusterIdx].x += data[i].x;
            sumCentroids[clusterIdx].y += data[i].y;
            sumCentroids[clusterIdx].z += data[i].z;
            counts[clusterIdx]++;
        }

        for (int j = 0; j < k; ++j) {
            if (counts[j] > 0) {
                centroids[j].x = sumCentroids[j].x / counts[j];
                centroids[j].y = sumCentroids[j].y / counts[j];
                centroids[j].z = sumCentroids[j].z / counts[j];
            }
        }
    }

    // 2. Empaquetar resultados finales en las estructuras de salida
    outLabeledData.clear();
    for (size_t i = 0; i < data.size(); ++i) {
        Labeled lblPoint;
        lblPoint.coord = data[i];
        lblPoint.label = static_cast<char>('A' + assignments[i]); // Asigna 'A', 'B', etc.
        outLabeledData.push_back(lblPoint);
    }

    // Calcular las Métricas de Dispersión (MD = WCSS) finales por clúster
    outSummary.resize(k);
    for (int j = 0; j < k; ++j) {
        outSummary[j].label = static_cast<char>('A' + j);
        outSummary[j].centroid = centroids[j];
        outSummary[j].pointCount = 0;
        outSummary[j].dispersion = 0.0;
    }

    for (size_t i = 0; i < data.size(); ++i) {
        int idx = assignments[i];
        outSummary[idx].pointCount++;
        double d = computeDistance(data[i], centroids[idx]);
        outSummary[idx].dispersion += (d * d); // Suma de distancias al cuadrado
    }
}
