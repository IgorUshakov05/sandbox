#ifndef INPUT_H
#define INPUT_H

#include "utilities/vec2d.hpp"

namespace sb {
	class Input {
	public:
		Input() = delete;
		Input(const Input&) = delete;
		void operator =(const Input&) = delete;

		static void init();
		static void terminate();
		static void update();

		static sb::Vec2d<double> getMousePosition();
		static bool isLBPressed();
		static bool isRBPressed();

	private:
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	};
}

#endif // INPUT_H
