#include "pch.h"
#include "CppUnitTest.h"
#include "../lab 11.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::string testFilename = "test_trains.txt";

			// Видалення файлу, якщо він існує
			std::remove(testFilename.c_str());

			// Виклик функції створення файлу
			createOrAppendFile(testFilename);

			// Перевірка, чи файл створено
			std::ifstream file(testFilename);
			Assert::IsTrue(file.good(), L"Файл повинен бути створений");
			file.close();

		}
	};
}
