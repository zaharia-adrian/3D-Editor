#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP
#define NOMINMAX
#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>
#include <commdlg.h>
#include "../src/feature/Scene.hpp"


class FileManager {
public:
	static bool loadSceneFromFile(std::string); 
	static void saveSceneToFile(std::string);  
	static bool loadSceneFromFileDialog();
	static std::vector<std::string> getFilesList(); /// localProjects files list
};

#endif
