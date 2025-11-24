/**
 * @file FileInfo.cpp
 * @author André Lucas Maegima
 * @brief Class to extract file infomations.
 * @version 0.4
 * @date 2025-11-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <string>
#include <filesystem>
#include <sys/stat.h>
#include "md5/md5.hpp"
#include "FileInfo.hpp"
#include "Algorithm.hpp"
#include <regex>

FileInfo::FileInfo(filesystem::directory_entry entry, bool with_hash) {
    path = entry.path();
    struct stat f_stat;
    stat(path.c_str(), &f_stat);
    type = S_ISDIR(f_stat.st_mode) ? FileType::Directory : FileType::File;
    size = f_stat.st_size;
    created = f_stat.st_ctim.tv_sec;
    modified = f_stat.st_mtim.tv_sec;
    accessed = f_stat.st_atim.tv_sec;
    Hash *hash = new Hash();
    Digest result(0, 0, 0, 0);
    if(type == FileType::File && with_hash) {
        fstream file(path, std::ios::binary | std::ios::in);
        if(file) result = hash->md5(&file, size);
    }
    md5sum[0] = result.A;
    md5sum[1] = result.B;
    md5sum[2] = result.C;
    md5sum[3] = result.D;
}

std::string FileInfo::size_str() const {
    std::stringstream ss;
    ss << setfill(' ');
    if(size >= 1000000000) {
        ss << setw(4) << setprecision(3) << (float)size/1000000000 << "GB";
    } else if(size >= 1000000) {
        ss << setw(4) << setprecision(3) << (float)size/1000000 << "MB";
    } else if(size >= 5000) {
        ss << setw(4) << setprecision(3) << (float)size/1000 << "KB";
    } else {
        ss << setw(5) << size << "B";
    }
    return ss.str();
}

std::string FileInfo::created_str() const {
    char buff[20];
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&created));
    return std::string(buff);
}

std::string FileInfo::modified_str() const {
    char buff[20];
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&modified));
    return std::string(buff);
}

std::string FileInfo::accessed_str() const {
    char buff[20];
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&accessed));
    return std::string(buff);
}

std::string FileInfo::type_str() const {
    return type == FileType::Directory ? "Directory" : "File";
}

string FileInfo::md5sumString() const {
    std::stringstream ss;
    unsigned char *p = (unsigned char *)md5sum;
    for(int i = 0; i < 16; ++i)
        ss << setfill('0') << setw(2) << std::hex << (int)p[i];
    return ss.str();
}

const std::string FileInfo::operator[](const std::string &idx) const {
    if(idx == "Name") return this->path.filename();
    if(idx == "Path") return this->path;
    if(idx == "Size") return this->size_str();
    if(idx == "Created") return this->created_str();
    if(idx == "Modified") return this->modified_str();
    if(idx == "Accessed") return this->accessed_str();
    if(idx == "Type") return this->type_str();
    if(idx == "MD5SUM") return this->md5sumString();
    return "<null>";
}

const std::string FileInfo::get_value(const std::string &expression) const {
    auto parts = Algorithm::split<std::vector>(expression, ',');
    std::string value = expression;
    if(parts.size() > 0 && parts[0].size() > 7 && parts[0].substr(0, 6) == "<file." && parts[0].back() == '>') {
        value = (*this)[parts[0].substr(6, parts[0].size()-7)];
    }
    if(parts.size() > 2) {
        std::regex re(parts[1], std::regex::egrep);
        std::string display = parts[2];
        std::smatch match;
        std::regex_search(value, match, re);
        for(size_t i = 0; i < match.size(); i++) {
            std::string needle = "(" + std::to_string(i) + ")";
            size_t idx = display.find(needle);
            if(idx != std::string::npos) {
                display.replace(idx, needle.size(), match[i].str());
            }
        }
        value = match.empty() ? "<null>" : display;
    }
    return value;
}

string FileInfo::to_string() const {
    return created_str() + " " + modified_str() + " " + accessed_str() +
           " " + md5sumString() + " " + size_str() + " " + type_str() + " " + path.string();
}

ostream &operator<<(ostream &os, const FileInfo &file) {
    return os << file.to_string();
}