#include "gtest/gtest.h"

#include "Unicode.h"
#include <sstream>

#include "Log.h"

// Test is based on: http://www.cl.cam.ac.uk/~mgk25/ucs/examples/UTF-8-test.txt

TEST(UnicodeTest, ValidUtf8) {
	const char* inputs[] = {
	    // 1.  correct UTF-8 text
	    "κ",
	    "ό",
	    "σ",
	    "μ",
	    "ε",
	    "幸",
	    "运",
	    "Б",
	    "ъ",
	    "л",
	    "г",
	    "а",
	    "р",
	    "с",
	    "к",
	    "и",

	    // 2.  boundary condition test cases
	    // 2.1 first possible sequence of range
	    "\x00",
	    "\xc2\x80",
	    "\xe0\xa0\x80",
	    "\xe1\x80\x80",
	    "\xf0\x90\x80\x80",
	    "\xf1\x80\x80\x80",
	    "\xf4\x80\x80\x80",

	    // 2.2 last possible sequence of range
	    "\x7f",
	    "\xdf\xbf"
	    "\xe0\xbf\xbf",
	    "\xef\xbf\xbf",
	    "\xf0\xbf\xbf\xbf",
	    "\xf3\xbf\xbf\xbf",
	    "\xf4\x8f\xbf\xbf",

	    // 2.3 other boundry conditions
	    "\xed\x9f\xbf",
	    "\xee\x80\x80",
	    "\xef\xbf\xbd",
	    "\xf4\x8f\x80\x80"
	};

	size_t len = sizeof(inputs) / sizeof(inputs[0]);
	for (size_t i = 0; i < len; i++) {
		std::stringstream ss;
		ss << "inputs[" << i << "]";
		SCOPED_TRACE(ss.str());

		EXPECT_TRUE(isValidUtf8Char(inputs[i]));
	}
}

TEST(UnicodeTest, InvalidUtf8) {
	const char* inputs[] = {
	    // 3   malformed sequences
	    // 3.1 unexpected continuation bytes
	    "\x80",
	    "\xbf",

	    // 3.2 lonely start characters
	    "\xc0 ",
	    "\xdf ",
	    "\xe0 ",
	    "\xef ",
	    "\xf0 ",
	    "\xf7 ",
	    "\xf8 ",
	    "\xfb ",
	    "\xfc ",
	    "\xfd ",

	    // 3.3 sequences with last continuation byte missing
	    "\xc2",
	    "\xe0\xa0",
	    "\xe1\x80",
	    "\xf0\x90\x80",
	    "\xf1\x80\x80",
	    "\xf4\x80\x80",
	    "\xdf",
	    "\xe0\xbf",
	    "\xef\xbf",
	    "\xf0\xbf\xbf",
	    "\xf3\xbf\xbf",
	    "\xf4\x8f\xbf",

	    // 3.5 impossible bytes
	    "\xfe",
	    "\xff",
	    "\xfe\xfe\xff\xff",

	    // 4.1 examples of an overlong ascii character
	    "\xc0\xaf",
	    "\xe0\x80\xaf",
	    "\xf0\x80\x80\xaf",

	    // 4.2 maximum overlong sequences
	    "\xc1\xbf",
	    "\xe0\x9f\xbf",
	    "\xf0\x8f\xbf\xbf",

	    // 4.3 overlong representation of the NUL character
	    "\xc0\x80",
	    "\xe0\x80\x80",
	    "\xf0\x80\x80",

	    /// @todo support for the rest of the test cases

	};

	size_t len = sizeof(inputs) / sizeof(inputs[0]);
	for (size_t i = 0; i < len; i++) {
		std::stringstream ss;
		ss << "inputs[" << i << "]";
		SCOPED_TRACE(ss.str());
		EXPECT_FALSE(isValidUtf8Char(inputs[i]));
	}
}
