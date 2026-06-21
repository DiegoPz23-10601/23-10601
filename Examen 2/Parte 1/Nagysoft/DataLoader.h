#ifndef DATALOADER_H
#define DATALOADER_H

#include <vector>
#include <string>
#include "types.h"

// Firma del cargador modular por referencia
bool load_csv_data(const std::string& filename, std::vector<Coord_3D>& data_vector);

#endif // DATALOADER_H
