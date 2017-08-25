cmake_minimum_required(VERSION 3.5)
project(ECI2017_Concurrency_Exam)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(ECI2017_Concurrency_Exam_Ex1 ex1.cc)
target_link_libraries(ECI2017_Concurrency_Exam_Ex1 Threads::Threads)

add_executable(ECI2017_Concurrency_Exam_Ex2 ex2.cc)
target_link_libraries(ECI2017_Concurrency_Exam_Ex2 Threads::Threads)

add_executable(ECI2017_Concurrency_Exam_Ex2R ex2-relacy.cc)
target_link_libraries(ECI2017_Concurrency_Exam_Ex2R Threads::Threads)