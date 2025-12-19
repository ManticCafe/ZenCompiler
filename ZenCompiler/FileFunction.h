#pragma once

#include <stdio.h>
#include <Windows.h>
#include <string>

// 检查是否为ts类型文件
bool isTS(char* file);

// 获取文件拓展名
std::string getFileExtension(char* fileName);

// 获取文件名
std::string getFileName(char* fileName);