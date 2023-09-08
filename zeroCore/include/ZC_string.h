#pragma once

#include <ZC_Config.h>

#ifdef _WIN32
	#include <string>
#endif
#ifdef ZC_API_android
	#include <string>
#else
	#include <memory>
#endif