add_executable(ch1-q1 q1.cpp)
target_link_libraries(ch1-q1 PRIVATE args)

add_executable(ch1-q2 q2.cpp)
target_link_libraries(ch1-q2 PRIVATE args)

add_executable(ch1-q3 q3.cpp)

add_executable(ch1-q4 q4.cpp)
target_link_libraries(ch1-q4 PRIVATE args)

add_executable(ch1-q5 q5.cpp)
target_link_libraries(ch1-q5 PRIVATE args)

add_executable(ch1-q6 q6.cpp)
target_link_libraries(ch1-q6 PRIVATE args)

add_executable(ch1-q7 q7.cpp)
add_executable(ch1-q8 q8.cpp)

add_executable(ch1-q9 q9.cpp)
target_link_libraries(ch1-q9 PRIVATE args range)
