cmake_minimum_required (VERSION 2.6)
project (libBlob)

INCLUDE_DIRECTORIES (./include)

include (GoogleTest)

find_package (GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()

add_executable (pt_test tests/pt.t.cpp)
target_link_libraries (pt_test ${GTEST_LIBRARIES} pthread)

add_executable (movement_test tests/movement.t.cpp)
target_link_libraries (movement_test ${GTEST_LIBRARIES} pthread)

add_executable (attack_test tests/attack.t.cpp)
target_link_libraries (attack_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_test tests/blob.t.cpp)
target_link_libraries (blob_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_history_test tests/blob_history.t.cpp)
target_link_libraries (blob_history_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_distance_test tests/blob_distance.t.cpp)
target_link_libraries (blob_distance_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_is_in_range_test tests/blob_is_in_range.t.cpp)
target_link_libraries (blob_is_in_range_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_is_in_same_square_test tests/blob_is_in_same_square.t.cpp)
target_link_libraries (blob_is_in_same_square_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_canSmell_test tests/blob_canSmell.t.cpp)
target_link_libraries (blob_canSmell_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_angle_test tests/blob_angle.t.cpp)
target_link_libraries (blob_angle_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_kill_test tests/blob_kill.t.cpp)
target_link_libraries (blob_kill_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_attack_test tests/blob_attack.t.cpp)
target_link_libraries (blob_attack_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_move_test tests/blob_move.t.cpp)
target_link_libraries (blob_move_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_wandersFixedAngle_test tests/blob_wandersFixedAngle.t.cpp)
target_link_libraries (blob_wandersFixedAngle_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_wandersRandomAngle_test tests/blob_wandersRandomAngle.t.cpp)
target_link_libraries (blob_wandersRandomAngle_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_hunt_test tests/blob_hunt.t.cpp)
target_link_libraries (blob_hunt_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_flee_test tests/blob_flee.t.cpp)
target_link_libraries (blob_flee_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_tired_test tests/blob_tired.t.cpp)
target_link_libraries (blob_tired_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_dead_test tests/blob_dead.t.cpp)
target_link_libraries (blob_dead_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_chooseAction_test tests/blob_chooseAction.t.cpp)
target_link_libraries (blob_chooseAction_test ${GTEST_LIBRARIES} pthread)

gtest_discover_tests (pt_test)
gtest_discover_tests (movement_test)
gtest_discover_tests (attack_test)
gtest_discover_tests (blob_test)
gtest_discover_tests (blob_distance_test)
gtest_discover_tests (blob_history_test)
gtest_discover_tests (blob_is_in_range_test)
gtest_discover_tests (blob_is_in_same_square_test)
gtest_discover_tests (blob_canSmell_test)
gtest_discover_tests (blob_angle_test)
gtest_discover_tests (blob_kill_test)
gtest_discover_tests (blob_attack_test)
gtest_discover_tests (blob_move_test)
gtest_discover_tests (blob_wandersFixedAngle_test)
gtest_discover_tests (blob_wandersRandomAngle_test)
gtest_discover_tests (blob_hunt_test)
gtest_discover_tests (blob_flee_test)
gtest_discover_tests (blob_tired_test)
gtest_discover_tests (blob_dead_test)
gtest_discover_tests (blob_chooseAction_test)

