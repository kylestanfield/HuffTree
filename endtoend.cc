#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <cstdio>
#include <stdlib.h>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


TEST(EndToEnd, Hello1) {
    system("./compress test1.txt test1.c");
    system("./decompress test1.c test1.d");
    std::string result = exec("diff test1.txt test1.d");
    EXPECT_TRUE(result == "");
}

TEST(EndToEnd, Hello2) {
    system("./compress test2.txt test2.c");
    system("./decompress test2.c test2.d");
    std::string result = exec("diff test2.txt test2.d");
    EXPECT_TRUE(result == "");
}

TEST(EndToEnd, Hello3) {
    system("./compress test3.txt test3.c");
    system("./decompress test3.c test3.d");
    std::string result = exec("diff test3.txt test3.d");
    EXPECT_TRUE(result == "");
}

TEST(EndToEnd, LesMis) {
    system("./compress les_mis.txt les_mis.c");
    system("./decompress les_mis.c les_mis.d");
    std::string result = exec("diff les_mis.txt les_mis.d");
    EXPECT_TRUE(result == "");
}

TEST(EndToEnd, HelloNEQ) {
    system("./compress test1.txt test1.c");
    system("./compress test2.txt test2.c");
    std::string result = exec("diff test1.c test2.c");
    EXPECT_FALSE(result == "");
}
