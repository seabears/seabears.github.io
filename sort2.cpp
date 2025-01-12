#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

namespace fs = std::filesystem;

const std::string POSTS_DIR = "_posts_copy";
const std::vector<std::string> EXCLUDE_FOLDERS = {"start(no_use)", "z_No_post", "z_template"};

bool isExcluded(const std::string& folderName) {
    return std::find(EXCLUDE_FOLDERS.begin(), EXCLUDE_FOLDERS.end(), folderName) != EXCLUDE_FOLDERS.end();
}

void updateMarkdownFile(const fs::path& filePath, const std::string& categoryName) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    std::string content;
    std::string line;
    bool categoriesFound = false;
    bool categoryExists = false;
    std::regex categoryRegex("-\\s*" + categoryName);

    while (std::getline(inFile, line)) {
        if (line.find("categories:") != std::string::npos) {
            categoriesFound = true;
        } else if (categoriesFound && std::regex_search(line, categoryRegex)) {
            categoryExists = true;
        }
        content += line + "\n";
    }
    inFile.close();

    if (!categoriesFound) {
        // Add categories section if it doesn't exist
        content = "categories:\n  - " + categoryName + "\n" + content;
    } else if (!categoryExists) {
        // Append the category to the categories list
        size_t pos = content.find("categories:");
        if (pos != std::string::npos) {
            size_t nextLinePos = content.find("\n", pos);
            content.insert(nextLinePos + 1, "  - " + categoryName + "\n");
        }
    } else {
        return; // No changes needed
    }

    // Write back the updated content
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Failed to write to file: " << filePath << std::endl;
        return;
    }
    outFile << content;
    outFile.close();

    std::cout << "Updated categories in " << filePath << " to include " << categoryName << std::endl;
}

int main() {
    for (const auto& entry : fs::directory_iterator(POSTS_DIR)) {
        if (!entry.is_directory()) continue;

        std::string categoryName = entry.path().filename().string();
        if (isExcluded(categoryName)) {
            std::cout << "Skipping folder: " << categoryName << std::endl;
            continue;
        }

        for (const auto& file : fs::directory_iterator(entry)) {
            if (file.path().extension() == ".md") {
                updateMarkdownFile(file.path(), categoryName);
            }
        }
    }

    return 0;
}
