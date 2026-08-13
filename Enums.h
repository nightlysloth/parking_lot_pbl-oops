#ifndef ENUMS_H
#define ENUMS_H

#include <string>

enum class vehicletype { car, bike, truck };
enum class slotstatus { reserved, vacant };
enum class ticketstatus { active, done };

std::string vehicleTypeToString(vehicletype type);
std::string slotStatusToString(slotstatus status);
std::string ticketStatusToString(ticketstatus status);

#endif
