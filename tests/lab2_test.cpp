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

    constexpr int inputSize = 5;

    std::array<const char*, inputSize> input = {
            "8.0 2.0 -4.0 -1.0",
            "0.0 3.2 2.09",
            "-10.0 -10.0 -10.0",
            "1337.0 137.0",
            "1 1 1 1 1 1 1"
    };


    std::array<double, inputSize> expectedOutput = {
            1, 0, -0.1, 9.75, 1
    };

    {
        auto inFile = std::ofstream(fileWithInput);

        for (const auto& line : input) {
            inFile << line << '\n';
        }
    }

    ParentRoutine(stdin);

    auto outFile = std::ifstream(fileWithOutput);

    std::string line;
    std::ifstream in("output.txt");
    int i = 0;
    if (in.is_open()) {
        while (getline(in, line)) {
            std::cout << line << std::endl; 
            EXPECT_EQ(stod(line), expectedOutput[i]);
            ++i;
        }
    }
    in.close();

   ASSERT_TRUE(outFile.good());

    auto removeIfExists = [](const char* path) {
        if (fs::exists(path)) {
            fs::remove(path);
        }
    };

   removeIfExists(fileWithInput);
   removeIfExists(fileWithOutput);
}