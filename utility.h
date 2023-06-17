#include <fstream>
#include <string>

inline std::ifstream GetOpenFileHandle(const std::string &file_name) {
  std::ifstream file_handle(file_name, std::ios::binary | std::ios::in);
  if (!file_handle.is_open()) {
    throw std::ios_base::failure("Failed to open file: " + file_name);
  }
  return file_handle;
}

