#pragma once

#include <vector>
#include <string>

std::vector<std::string> get_network_interfaces();
void capture_packets(const std::string& interface);