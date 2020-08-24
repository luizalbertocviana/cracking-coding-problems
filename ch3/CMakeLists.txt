add_executable(ch3-q1 q1.cpp)
target_link_libraries(ch3-q1 PRIVATE StackSequence range)

add_executable(ch3-q2 q2.cpp)
target_link_libraries(ch3-q2 PRIVATE args StackMin)

add_executable(ch3-q3 q3.cpp)
target_link_libraries(ch3-q3 PRIVATE StackSet range)

add_executable(ch3-q4 q4.cpp)
target_link_libraries(ch3-q4 PRIVATE range)

add_executable(ch3-q5 q5.cpp)
target_link_libraries(ch3-q5 PRIVATE args)

add_executable(ch3-q6 q6.cpp)
target_link_libraries(ch3-q6 PRIVATE Identity QueueSet range)
