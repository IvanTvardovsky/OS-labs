#include <gtest/gtest.h>

#include <array>
#include <filesystem>
#include <fstream>
#include <memory>

namespace fs = std::filesystem;

extern "C" {
    #include <parent.h>
    #include <utils.h>
}

TEST(SecondLabTests, GeneralSimpleTest) {
    const char* fileWithInput = "input.txt";
    const char* fileWithOutput = "output.txt";

    constexpr int inputSize = 4;

    std::array<const char*, inputSize> input = {
            "8.0 2.0 -4.0 -1.0",
            "0.0 3.2 2.09",
            "-10.0 -10.0 -10.0",
            "1337.0 137"
    };

    std::array<float, inputSize> expectedOutput = {
            1, 0, -0.1, 9.75
    };

    {
        auto inFile = std::ofstream(fileWithInput);

        inFile << fileWithOutput << '\n';

        for(const auto& line : input) {
            inFile << line << '\n';
        }
    }

    auto deleter = [](FILE* file) {
        fclose(file);
    };

    std::unique_ptr<FILE, decltype(deleter)> inFile(fopen(fileWithInput, "r"), deleter);

    ParentRoutine(stdin);

    auto outFile = std::ifstream(fileWithOutput);

    ASSERT_TRUE(outFile.good());

    float result;

    for(float i : expectedOutput) {
        outFile >> result;
        EXPECT_EQ(result, i);
    }

    auto removeIfExists = [](const char* path) {
        if (fs::exists(path)) {
            fs::remove(path);
        }
    };

    removeIfExists(fileWithInput);
    removeIfExists(fileWithOutput);
}