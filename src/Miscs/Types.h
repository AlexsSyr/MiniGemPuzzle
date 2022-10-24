#pragma once
#include <string>
#include <vector>
#include <source_location>
#include <filesystem>

typedef int int32;
typedef unsigned int uint32;

typedef long long int int64;
typedef unsigned long long int uint64;

typedef std::string String;
typedef std::source_location SourceLocation;

typedef std::filesystem::path Path;

template<typename T>
using Vector = std::vector<T>;