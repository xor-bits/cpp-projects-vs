#pragma once

#include <string>

namespace oe {

	class GL {
	public:
		static int checkGLErrors();

		static void enableBlending();
		static void disableBlending();

		static void enableDepth();
		static void disableDepth();

		/*Also known as VSync*/
		static void setSwapInterval(unsigned int interval);
		static void setBackFaceCulling(bool on);

		static void setLineWidth(float w);
		static void setPointRadius(float w);

		static std::string getRenderer();
		static std::string getVendor();

	};

}