
add_executable(Pthread_test Pthread_test.cc)
target_link_libraries(Pthread_test tesla_base)

add_executable(Mutex_test Mutex_test.cc)
target_link_libraries(Mutex_test tesla_base)

add_executable(Condition_test Condition_test.cc)
target_link_libraries(Condition_test tesla_base)

add_executable(CountDownLatch CountDownLatch_test.cc)
target_link_libraries(CountDownLatch tesla_base)

add_executable(Log_test Log_test.cc)
target_link_libraries(Log_test tesla_base)

add_executable(LogFile_test LogFile_test.cc)
target_link_libraries(LogFile_test tesla_base)

add_executable(AsyncFileAppender_test AsyncFileAppender_test.cc)
target_link_libraries(AsyncFileAppender_test tesla_base)

