#ifndef RGB_H
#define RGB_H


#include "common.h"


namespace sb {
	/// <summary>
	/// this class stores the color
	/// </summary>
	struct RGB {
		std::uint8_t r, g, b;
		RGB();
		RGB(std::uint8_t r, std::uint8_t g, std::uint8_t b);
	};
}


#endif //RGB_H