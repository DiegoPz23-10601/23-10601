#ifndef DATAWRITER_H
#define DATAWRITER_H

#include <vector>
#include <string>
#include "Coord3D.h"
#include "KMeans.h"

class DataWriter {
public:
    // Genera el reporte CSV estructurado
    static void writeClassifiedCSV(const std::string& filename, const std::vector<Labeled>& labeledData);
    
    // Genera el molde exacto txt solicitado
    static void writeSummaryTXT(const std::string& filename, const std::vector<ClusterInfo>& summary);
};

#endif
