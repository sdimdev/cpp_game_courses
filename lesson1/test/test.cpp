#include <gtest/gtest.h>
#include "printSlow.cpp"
#include "../printFast.cpp"
#include "../scanFast.cpp"

constexpr auto CONTROL_TIME = 0.2; //s
constexpr auto EXEC_TIMES = 1000000;
constexpr auto WRITING_NUMBER = -345789;

void printFastValueTest(int val)
{
    //https://stackoverflow.com/questions/3803465/how-to-capture-stdout-stderr-with-googletest
    //GIVEN
    testing::internal::CaptureStdout();

    //WHEN
    printFast(val);

    //THEN
    std::string text = testing::internal::GetCapturedStdout();
    ASSERT_EQ(std::to_string(val), text) << "The value " << val << "not equal " << text;
}

TEST(PrintSlow, Slow)
{
    //GIVEN
    clock_t t = clock();
    testing::internal::CaptureStdout();

    //WHEN
    for (int i = 0; i < EXEC_TIMES; i++)
        printSlow(WRITING_NUMBER);

    //THEN
    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    testing::internal::GetCapturedStdout();
    ASSERT_TRUE(work_time >= CONTROL_TIME) << "Work time: " << work_time;
}

TEST(PrintFast, Fast)
{
    //GIVEN
    testing::internal::CaptureStdout();
    clock_t t = clock();

    //WHEN
    for (int i = 0; i < EXEC_TIMES; i++)
        printFast(WRITING_NUMBER);
    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    testing::internal::GetCapturedStdout();

    //THEN
    ASSERT_TRUE(work_time <= CONTROL_TIME) << "Work time is " << work_time;
}

TEST(PrintFast, Long_Fast)
{
    //GIVEN
    long number = -3454564l;
    testing::internal::CaptureStdout();
    clock_t t = clock();

    //WHEN
    for (int i = 0; i < EXEC_TIMES; i++)
        printFast(number);
    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    testing::internal::GetCapturedStdout();

    //THEN
    ASSERT_TRUE(work_time <= CONTROL_TIME) << "Work time is " << work_time;
}

/* //todo doesn't work
TEST(PrintFast, Double_Fast)
{
    //GIVEN
    double number = -3454564.090;
    testing::internal::CaptureStdout();
    clock_t t = clock();

    //WHEN
    for (int i = 0; i < EXEC_TIMES; i++)
        printFast(number);
    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    testing::internal::GetCapturedStdout();

    //THEN
    ASSERT_TRUE(work_time <= CONTROL_TIME) << "Work time is " << work_time;
}
*/

//todo
/*TEST(ScanFast, Fast)
{
    //GIVEN
    clock_t t = clock();

    //WHEN
    int num = 0;
    for (int i = 0; i < EXEC_TIMES; i++)
    {
        num = scanFast();
    }
    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);

    //THEN
    ASSERT_TRUE(work_time <= CONTROL_TIME) << "Work time is " << work_time;
}*/

TEST(PrintFast, PotentialErrorValues)
{
    printFastValueTest(INT32_MAX);
    printFastValueTest(INT32_MIN);
    printFastValueTest(0);
    printFastValueTest(-1);
    printFastValueTest(1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

