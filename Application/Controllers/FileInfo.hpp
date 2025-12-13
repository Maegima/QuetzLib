/**
 * @file FileInfo.hpp
 * @author André Lucas Maegima
 * @brief Class to extract file infomations.
 * @version 0.4
 * @date 2025-11-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _FILEINFO_HPP_
#define _FILEINFO_HPP_

#include <string>
#include <filesystem>

enum FileType { Directory, File };

class FileInfo {
  private:
    uint32_t md5sum[4];
    long created;
    long modified;
    long accessed;

  public:
    off_t size;
    std::filesystem::path path;
    FileType type;

    FileInfo(std::filesystem::directory_entry entry, bool with_hash = true);
    std::string to_string() const;
    std::string md5sumString() const;
    std::string size_str() const;
    std::string created_str() const;
    std::string modified_str() const;
    std::string accessed_str() const;
    std::string type_str() const;
    const std::string operator[](const std::string &idx) const;
    const std::string get_value(const std::string &expression) const;
};

std::ostream &operator<<(std::ostream &os, const FileInfo &file);

#endif
