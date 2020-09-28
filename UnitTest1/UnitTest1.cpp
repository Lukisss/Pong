#include "pch.h"
#include "CppUnitTest.h"
#include "../PongRefactored/PongRefactored.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int humanPoints = 4;
			int compPoints = 2;
			bool gameContiniues = TRUE;
			Assert::AreEqual(gameContiniues,noWinner(humanPoints, compPoints));
		}

		TEST_METHOD(TestMethod2)
		{
			int humanPoints = 1;
			int compPoints = 5;
			bool gameContiniues = FALSE;
			Assert::AreEqual(gameContiniues, noWinner(humanPoints, compPoints));
		}

		TEST_METHOD(TestMethod3)
		{
			int humanPoints = 5;
			int compPoints = 2;
			string humanWon = "YOU";
			Assert::AreSame(humanWon, checkWinner(humanPoints, compPoints));

		}
	};
}
