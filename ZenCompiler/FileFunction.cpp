#include "FileFunction.h"

bool isTS(char* file) {
	char dot = '.';
	const char* lastDot = strrchr(file, (int)dot);
	if (!lastDot || lastDot == file) {
		return false;
	}
	if (strcmp(lastDot + 1, "ts") == 0 || strcmp(lastDot + 1, "TS") == 0) {
		return true;
	} else {
		return false;
	}
}

std::string getFileExtension(char* fileName) {
	char dot = '.';
	const char* lastDot = strrchr(fileName, (int)dot);
	if (!lastDot || lastDot == fileName) {
		return NULL;
	}
	return std::string(lastDot);
}

std::string getFileName(char* fileName) {
	const char* lastSeparator = strrchr(fileName, '\\');
	if (!lastSeparator) {
		lastSeparator = strrchr(fileName, '/');
		if (!lastSeparator) {
			lastSeparator = fileName - 1;
		}
	}
	const char* nameStart = lastSeparator + 1;
	const char* lastDot = strrchr(nameStart, '.');
	if (!lastDot || lastDot == nameStart) {
		return std::string(nameStart);
	}
	return std::string(nameStart, lastDot);
}