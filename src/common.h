#ifndef COMMON_H
#define COMMON_H

#pragma comment (lib, "opengl32.lib")
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <exception>
#include <stdint.h>
#include <thread>
#include <chrono>
#include <random>
#include <string>

namespace sb {
	void init();
	void run();
	void terminate();

	//exit the program in case of an error
	void exitProgram(std::exception& ex);
}

#endif //COMMON_H
