#include "pch.h"
#include "CppUnitTest.h"
#include "../HtmlDecode/HtmlDecode.cpp"//TODO: Добавить в проект

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HtmlDecodeTest
{
	TEST_CLASS(HtmlDecodeTest)
	{
	public:
		
		TEST_METHOD(HtmlDecodeCasualString)
		{
			std::string html = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
			std::string actual = HtmlDecode(html);
			std::string expected = "Cat <says> \"Meow\". M&M's";

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(HtmlDecodeWithoutHtmlTempaltes)
		{
			std::string html = "Cat <says> \"Meow\". M&M's";
			std::string actual = HtmlDecode(html);
			std::string expected = "Cat <says> \"Meow\". M&M's";

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(HtmlDecodeWithEmptyString)
		{
			std::string html;
			std::string actual = HtmlDecode(html);
			std::string expected;

			Assert::AreEqual(expected, actual);
		}
	};
}
