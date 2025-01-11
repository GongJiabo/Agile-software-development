cmake_minimum_required(VERSION 3.20.0)
project(PayRollSystem VERSION 0.1.0 LANGUAGES C CXX)

# 添加gtest源码目录
add_subdirectory(third_party/googletest)

# 定义各个模块的源文件
aux_source_directory(utility SRC_UTILITY)
aux_source_directory(affiliation SRC_AFFILIATION)
aux_source_directory(classification SRC_CLASSIFICATION)
aux_source_directory(paymentmethod SRC_PAYMENTMETHOD)
aux_source_directory(schedule SRC_SCHEDULE)
aux_source_directory(transactions SRC_TRANSACTIONS)



# 添加可执行文件
add_executable(SalarySystemTest unittest/PayrollTest.cpp ${SRC_UTILITY} ${SRC_AFFILIATION}
${SRC_CLASSIFICATION} ${SRC_PAYMENTMETHOD} ${SRC_SCHEDULE} ${SRC_TRANSACTIONS})

# 链接gtest库
target_link_libraries(SalarySystemTest GTest::gtest GTest::gtest_main)
target_include_directories(SalarySystemTest PUBLIC
    ${PROJECT_SOURCE_DIR}/third_party/googletest/googletest/include
)