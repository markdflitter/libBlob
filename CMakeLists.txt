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

add_executable (blob_distance_test tests/blob_distance.t.cpp)
target_link_libraries (blob_distance_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_canSmell_test tests/blob_canSmell.t.cpp)
target_link_libraries (blob_canSmell_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_inRange_test tests/blob_inRange.t.cpp)
target_link_libraries (blob_inRange_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_sameSquare_test tests/blob_sameSquare.t.cpp)
target_link_libraries (blob_sameSquare_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_angle_test tests/blob_angle.t.cpp)
target_link_libraries (blob_angle_test ${GTEST_LIBRARIES} pthread)

gtest_discover_tests (pt_test)
gtest_discover_tests (movement_test)
gtest_discover_tests (attack_test)
gtest_discover_tests (blob_test)
gtest_discover_tests (blob_distance_test)
gtest_discover_tests (blob_canSmell_test)
gtest_discover_tests (blob_inRange_test)
gtest_discover_tests (blob_sameSquare_test)
gtest_discover_tests (blob_angle_test)

