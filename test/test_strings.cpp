#include <catch.hpp>

#include <string>
#include <vector>

// If you fill a string with nulls, what happens?
TEST_CASE("Filling a String with all nulls")
{
	// Fill our string with all nulls.
	std::vector<uint8_t> bytes(256, 0);
	std::string str(bytes.begin(), bytes.end());
    REQUIRE(bytes.size() == 256);

	// The string data itself is full of all nulls.
	REQUIRE(str.size() == 256);

	// The C-string returned is just empty.
	REQUIRE(strnlen(str.c_str(), 1024) == 0);

	for (size_t i = 0; i < bytes.size(); ++i) {
		REQUIRE(str[i] == '\0');
	}
}

TEST_CASE("Filling a string with a null in the middle")
{
    const std::string foo = "foo";
	const std::string bar = "bar";

	std::vector<uint8_t> bytes;
	bytes.insert(bytes.end(), foo.begin(), foo.end());

	// No null was inserted
	REQUIRE(bytes.size() == 3);

	bytes.push_back('\0');
	bytes.insert(bytes.end(), bar.begin(), bar.end());

	// 0123456
	// foo bar
	//    ^
	//    +--- null, '\0'
    REQUIRE(bytes.size() == 7);

    std::string str(bytes.begin(), bytes.end());
	// Now we have:
	// "foo\0bar" in str
	REQUIRE(str.size() == 7);
	REQUIRE(strnlen(str.c_str(), bytes.size()) == 3);
	REQUIRE(strncmp(str.c_str(), "foo", bytes.size()) == 0);
}