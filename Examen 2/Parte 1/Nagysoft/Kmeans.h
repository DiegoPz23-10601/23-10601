#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include "Coord3D.h"

struct ClusterInfo {
    char label;
    Coord_3D centroid;
    int pointCount;
    double dispersion; // Representa nuestra MD escogida
};

class KMeans {
private:
    int k;
    double computeDistance(const Coord_3D& p1, const Coord_3D& p2);
    
    // Condición de parada encapsulada en una función
    bool hasConverged(const std::vector<Coord_3D>& oldCentroids, 
                      const std::vector<Coord_3D>& newCentroids, 
                      double tolerance, int iteration, int maxIterations);

public:
    KMeans(int clusterCount);
    
    // Ejecuta el algoritmo pasando el vector de datos por referencia constante
    void run(const std::vector<Coord_3D>& data, 
             std::vector<Labeled>& outLabeledData, 
             std::vector<ClusterInfo>& outSummary);
};

#endif
