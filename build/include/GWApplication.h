#pragma once
#include "GWObject.h"

namespace GW 
{
	class GW_CORE_EXPORT GWApplication : public GWObject
	{
	public:
		GWApplication(int argc, char** argv);
		~GWApplication();

		int exec();
	};
}
