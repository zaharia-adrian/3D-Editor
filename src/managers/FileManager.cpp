#include "FileManager.hpp"



bool FileManager::loadSceneFromFile(std::string filePath) {

	FILE *fptr = fopen(filePath.c_str(), "r");

	if (fptr == nullptr) {
		std::cerr << "File not found!";
		return false;
	}

	Scene *scene = Scene::getInstance();
	

	char line[256];
	int idx0, idx1, idx2;
	float x, y, z;

	while (fgets(line, sizeof(line), fptr)) {
		if (line[0] == 'v'){
			if (sscanf(line, "v %f %f %f", &x, &y, &z) == 3) {
				if (scene->objects.empty()) scene->objects.emplace_back();
				scene->objects.back().addVertex(x, y, z,
					scene->objects.size() - 1,
					scene->objects.back().vertices.size()
				);
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
		else if (line[0] == 'p' && line[1] == 'o' && line[2] == 's') {
			if (sscanf(line, "pos %f %f %f", &x, &y, &z) == 3) {
				if (scene->objects.empty()) scene->objects.emplace_back();
				scene->objects.back().pos = Vec3d(x, y, z);
				scene->objects.back().updateWorldMat();
			}
			else {
				std::cerr << "Invalid position line: " << line << std::endl;
			}
		}
		else if (line[0] == 'r' && line[1] == 'o' && line[2] == 't') {
			if (sscanf(line, "rot %f %f %f", &x, &y, &z) == 3) {
				if (scene->objects.empty()) scene->objects.emplace_back();
				scene->objects.back().rot = Vec3d(x, y, z);
				scene->objects.back().updateWorldMat();
			}
			else {
				std::cerr << "Invalid rotation line: " << line << std::endl;
			}
		}
		else if (line[0] == 's' && line[1] == 'c' && line[2] == 'l') {
			if (sscanf(line, "scl %f %f %f", &x, &y, &z) == 3) {
				if (scene->objects.empty()) scene->objects.emplace_back();
				scene->objects.back().scl = Vec3d(x, y, z);
				scene->objects.back().updateWorldMat();
			}
			else {
				std::cerr << "Invalid scale line: " << line << std::endl;
			}
		}
		else if (line[0] == 'o') {
			char name[256];
			scene->objects.emplace_back();
			if (sscanf(line, "o %s", &name) == 1) {
				scene->objects.back().name = name;
			}
			else {
				std::cerr << "Invalid oject name line: " << line << std::endl;
			}
		}
	}
	fclose(fptr);
	return true;
}

void FileManager::saveSceneToFile(std::string filePath) {
	FILE* fptr = fopen(filePath.c_str(), "w");

	Scene* scene = Scene::getInstance();

	for (Object &o : scene->objects) {
		fprintf(fptr, "o %s\n", o.name.c_str());
		fprintf(fptr, "pos %f %f %f\n", o.pos.x, o.pos.y, o.pos.z);
		fprintf(fptr, "rot %f %f %f\n", o.rot.x, o.rot.y, o.rot.z);
		fprintf(fptr, "scl %f %f %f\n", o.scl.x, o.scl.y, o.scl.z);
		for (Object::vertex &vertex : o.vertices) 
			fprintf(fptr, "v %f %f %f\n", vertex.v.x, vertex.v.y, vertex.v.z);
		
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
bool FileManager::selectFileDialog(std::string &filePath) {

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
		filePath = fileName;
		return true;
	}
	///No file selected or dialog canceled.
	return false;
}

std::vector<std::string> FileManager::getPredefinedObjectsList() {
	std::string folderPath = "../../../predefinedObjects";

	std::vector<std::string> filesList;
	for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
		filesList.emplace_back(entry.path().filename().string());
	}
	return filesList;
};

