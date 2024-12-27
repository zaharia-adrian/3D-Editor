#include "FileManager.hpp"



bool FileManager::loadSceneFromFile(std::string filePath) {

	FILE *fptr = fopen(filePath.c_str(), "r");
	if (fptr == nullptr) {
		std::cerr << "File not found!";
		return false;
	}

	Scene *scene = Scene::getInstance();
	scene->filePath = filePath;

	char line[256];
	int idx0, idx1, idx2;
	float x, y, z;

	while (fgets(line, sizeof(line), fptr)) {
		if (line[0] == 'v'){
			if (sscanf(line, "v %f %f %f", &x, &y, &z) == 3) {
				if (scene->objects.empty()) scene->objects.emplace_back();
				scene->objects.back().addVertex(x, y, z);
			}
			else {
				std::cerr << "Invalid vertex line: " << line << std::endl;
			}
		}
		else if (line[0] == 'f') {
			if (sscanf(line, "f %d %d %d", &idx0, &idx1, &idx2) == 3) {
				if (scene->objects.empty()) scene->objects.emplace_back();
				scene->objects.back().addTriangle(idx0 - 1, idx1 - 1, idx2 - 1,
					scene->objects.size() - 1,
					scene->objects.back().triangles.size()
				);
			}
			else {
				std::cerr << "Invalid face line: " << line << std::endl;
			}
		}
		else if (line[0] == 'o') {
			scene->objects.emplace_back();
		}
	}
	fclose(fptr);
	return true;
}

void FileManager::saveSceneToFile(std::string filePath) {
	FILE* fptr = fopen(filePath.c_str(), "w");

	Scene* scene = Scene::getInstance();
	scene->filePath = "";

	for (Object &o : scene->objects) {
		fprintf(fptr, "o \n");
		for (Vec3d& v : o.vertices) 
			fprintf(fptr, "v %f %f %f\n", v.x, v.y, v.z);
		
		for (Object::triangle& t : o.triangles) 
			fprintf(fptr, "f %d %d %d\n", t.idx[0] + 1, t.idx[1] + 1, t.idx[2] + 1);

	}
	fclose(fptr);
}

std::vector<std::string> FileManager::getFilesList() {
	std::string folderPath = "../../../localProjects";

	std::vector<std::string> filesList;
	for (const auto &entry : std::filesystem::directory_iterator(folderPath)) {
		filesList.emplace_back(entry.path().filename().string());
	}
	return filesList;
}

bool FileManager::loadSceneFromFileDialog() {

	///https://cplusplus.com/forum/windows/169960/

	char fileName[MAX_PATH] = "";

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);  
	ofn.hwndOwner = NULL;      
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = sizeof(fileName); 
	ofn.lpstrFilter = ".OBJ\0*.*\0Text Files\0*.TXT\0";  
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	
	if (GetOpenFileName(&ofn)) { // Open the dialog
		return loadSceneFromFile(fileName);
	}
	///No file selected or dialog canceled.
	return false;
}