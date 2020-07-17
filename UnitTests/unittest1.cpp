#include "stdafx.h"
#include "CppUnitTest.h"

#include"../Chess/Bishop.h"
#include"../Chess/Board.h"
#include"../Chess/Figure.h"
#include"../Chess/King.h"
#include"../Chess/Knight.h"
#include"../Chess/Pawn.h"
#include"../Chess/Queen.h"
#include"../Chess/Rook.h"
#include"../Chess/Square.h"

#include"../Chess/Board.cpp"
#include"../Chess/Square.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(ValidityTest)
		{
			Board board;
			Assert::IsTrue(board.isValidMove(0, 1, 0, 2));
			Assert::IsFalse(board.isValidMove(0, 1, 0, 1));
		}

		TEST_METHOD(FreePathTest)
		{
			Board board;
			Assert::IsFalse(board.isPathFree(2, 0, 0, 2));
			Assert::IsTrue(board.isPathFree(6, 0, 7, 2));
			Assert::IsFalse(board.isFreeDiagonally(5, 0, 3, 2));
			Assert::IsTrue(board.isFreeStraight(4, 1, 4, 2));

		}

	};
}
