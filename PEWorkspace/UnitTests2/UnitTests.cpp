#include "C:\Users\aaron\Desktop\Schoolwork\CSCI_522\Milestone\PEWorkspace\UnitTests\pch.h"
#include "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\UnitTest\include\CppUnitTest.h"
#include "assert.h"

//extern "C" {
//#include "C:\Users\aaron\Desktop\Schoolwork\CSCI_522\Milestone\PEWorkspace\Code\lua_dist\src\lua.h"
//#include "C:\Users\aaron\Desktop\Schoolwork\CSCI_522\Milestone\PEWorkspace\Code\lua_dist\src\lualib.h"
//#include "C:\Users\aaron\Desktop\Schoolwork\CSCI_522\Milestone\PEWorkspace\Code\lua_dist\src\lauxlib.h"
//#include "C:\Users\aaron\Desktop\Schoolwork\CSCI_522\Milestone\PEWorkspace\Code\luasocket_dist\src\luasocket.h"
//}


//#include "C:\Users\aaron\Desktop\Schoolwork\CSCI_522\Milestone\PEWorkspace\Code\PrimeEngine\Lua\LuaEnvironment.h"
//#include "C:\Users\aaron\Desktop\Schoolwork\CSCI_522\Milestone\PEWorkspace\Code\PrimeEngine\Lua\EventGlue\EventDataCreators.h"
//#include "C:\Users\aaron\Desktop\Schoolwork\CSCI_522\Milestone\PEWorkspace\Code\PriorityQueue.h"
//#include "C:\Users\aaron\Desktop\Schoolwork\CSCI_522\Milestone\PEWorkspace\Code\lua_dist\src\lua.h"
// Lua Stuff

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
/*using namespace CharacterControl;
using namespace Events;
using namespace Components;*/

namespace PriorityQueueTests
{
	TEST_CLASS(UnitTests)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, 2);

			//return 0;
		}
		TEST_METHOD(TestMethod2)
		{
			Assert::AreEqual(2, 2);

			//return 0;
		}
	};
}
