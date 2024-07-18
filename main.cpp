#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

class CPlate {
public:
    CPlate(const fs::path& p_dir) : m_dir_path(p_dir) {}

    void createClangFormat();
    void createMainSrc();
    void createCMakeFile();
    void createBuildDir();

private:
    bool clangFormatExist();
    bool cmakeFileExist();
    bool mainFileExist();
    fs::path m_dir_path;
    fs::path m_clang_path;
    fs::path m_cmake_path;
    fs::path m_mainsrc_path;
};

bool CPlate::clangFormatExist() {
    m_clang_path = m_dir_path / ".clang-format";
    return fs::exists(m_clang_path);
}

bool CPlate::cmakeFileExist() {
    m_cmake_path = m_dir_path / "CMakeLists.txt";
    return fs::exists(m_cmake_path);
}

bool CPlate::mainFileExist() {
    m_mainsrc_path = m_dir_path / "main.cpp";
    return fs::exists(m_mainsrc_path);
}

void CPlate::createClangFormat() {
    std::string option;

    if (clangFormatExist()) {
        return;
    }

    std::cout << ".clang-format does not exist in " << m_dir_path << "\n";
    std::cout << "Create one? [Y/N]:";
    std::cin >> option;

    if (option != "Y" && option != "y") {
        return;
    }

    std::ofstream file(m_clang_path);

    if (!file.is_open()) {
        std::cerr << "Failed to create .clang-format file.\n";
        return;
    }

    file << "BasedOnStyle: Google\n"
         << "IndentWidth: 4\n"
         << "UseTab: Always\n"
         << "TabWidth: 4\n";

    std::cout << "Creating .clang-format success.\n";
}

void CPlate::createMainSrc() {
    std::string option;

    if (mainFileExist()) {
        return;
    }

    std::cout << "main.cpp does not exist in " << m_dir_path << "\n";
    std::cout << "Create one? [Y/N]:";
    std::cin >> option;

    if (option != "Y" && option != "y") {
        return;
    }

    std::ofstream file(m_mainsrc_path);

    if (!file.is_open()) {
        std::cerr << "Failed to create main.cpp file.\n";
        return;
    }

    file << "int main (int argc, char *argv[]){\n"
         << "return 0;\n"
         << "}\n";

    std::cout << "Creating main.cpp success.\n";
}

void CPlate::createCMakeFile() {
    std::string option;

    if (cmakeFileExist()) {
        return;
    }

    std::cout << "CMakeLists.txt does not exist in " << m_dir_path << "\n";
    std::cout << "Create one? [Y/N]:";
    std::cin >> option;

    if (option != "Y" && option != "y") {
        return;
    }

    std::ofstream file(m_cmake_path);

    if (!file.is_open()) {
        std::cerr << "Failed to create CMakeLists.txt file.\n";
        return;
    }

    file << "cmake_minimum_required(VERSION 3.10)\n"
         << "# Your project name.\n"
         << "project(testproject)\n\n"
         << "# This will create compile_commands.json.\n"
         << "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n\n"
         << "# Specify C++17 standard\n"
         << "set(CMAKE_CXX_STANDARD 17)\n"
         << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n"
         << "# Add your .exe target\n"
         << "add_executable(testproject main.cpp)\n";

    std::cout << "Creating CMakeLists.txt success.\n";
}

void CPlate::createBuildDir() {
    fs::path build_dir = m_dir_path / "build";
    try {
        if (!fs::exists(build_dir)) {
            fs::create_directory(build_dir);
            std::cout << "Build directory created: " << build_dir << std::endl;
        } else {
            std::cout << "Build directory already exists: " << build_dir << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& ex) {
        std::cerr << "Failed to create build directory: " << ex.what() << std::endl;
    }
}

int main() {
    fs::path current_path = fs::current_path();

    CPlate cplate(current_path);
    cplate.createClangFormat();
    cplate.createMainSrc();
    cplate.createCMakeFile();
    cplate.createBuildDir();

    return 0;
}
