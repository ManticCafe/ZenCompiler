#include <stdio.h>
#include <Windows.h>
#include <string>
#include "FileFunction.h"

int main(int argc,char *argv[]) {
	FILE *sourceFile = NULL; // 源文件
	std::string sourceFileName; //源文件名
	bool isNode = false; // obj是否带注释

	// 检查参数数量
	if (argc == 1) {
		printf("too few parameters\ncan type \"--help\" to leanr more");
		return -1;
	}

	// 如果参数是源文件
	for (int i = 1; i < argc; i++) {
		if (isTS(argv[i]) && strcmp(argv[i - 1], "-o") != 0) {
			errno_t sourceFileError = fopen_s(&sourceFile, argv[i], "r");
			sourceFileName = getFileName(argv[i]);
			if (sourceFileError != 0) {
				printf("cannot find the source file");
				return -1;
			}
		}
		if (!isTS(argv[i]) && strcmp(argv[i - 1], "-o") != 0) {
			printf("\"%s\" is an unsupported file extension", getFileExtension(argv[i]).c_str());
			return -1;
		}
	}
	sourceFileName.append(".zs");
	std::string defaultOBJName = sourceFileName; // 默认目标文件名称

	// 判断参数是否带决定obj是否带注释
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-n") == 0) {
			isNode = true;
		}
	}

	// 判断参数是否是目标文件名
	for (int i = 1; i < argc; i++) { 
		if (strcmp(argv[i],"-o") == 0) {
			if (i + 1 >= argc) {
				printf("missing output file name after -o");
				return -1;
			}
			if (isTS(argv[i + 1])) {
				printf("%s is not a valid parameter", argv[i + 1]);
				return -1;
			}
			defaultOBJName = argv[i + 1];
			i++;
		}
	}

	// 判断是否是--help
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--help") == 0) {
			printf("\nZenCompiler [sourceFile] [-o outputName] [-n]\n");
			printf("sourceFile ---- your source file's path.\n");
			printf("-o outputName ---- the name of the target file,default to source file name.\n");
			printf("-n ---- target file with annotations.\n");
			return -2;
		}
	}
	
	// 创建源文件
	const char *objFileName = defaultOBJName.c_str();
	FILE* objFile = NULL;
	errno_t objFileError = fopen_s(&objFile, objFileName, "wt");
	if (objFileError != 0) {
		printf("cannot create directory");
		return -1;
	}

	// 关闭文件
	if (sourceFile != 0) {
		fclose(sourceFile);
	}
	if (objFile != 0) {
		fclose(objFile);
	}
	printf("compiler success");
	return 0;
}