#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include <vector>
#include <string>
#include "KMeans.h"

bool save_classified_csv(const std::string& filename, const std::vector<Cluster>& clusters);
bool save_summary_txt(const std::string& filename, const std::vector<Cluster>& clusters);

#endif // OUTPUTHANDLER_H
