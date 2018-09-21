cmake_minimum_required (VERSION 2.6)
project (libBlob)

INCLUDE_DIRECTORIES (./include)

include (GoogleTest)

find_package (GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()

add_executable (test_0_0_template tests/0_0_template.t.cpp)
target_link_libraries (test_0_0_template ${GTEST_LIBRARIES} pthread)

add_executable (test_1_0_pt tests/1_0_pt.t.cpp)
target_link_libraries (test_1_0_pt ${GTEST_LIBRARIES} pthread)

add_executable (test_2_0_movement tests/2_0_movement.t.cpp)
target_link_libraries (test_2_0_movement ${GTEST_LIBRARIES} pthread)

add_executable (test_2_1_fight tests/2_1_fight.t.cpp)
target_link_libraries (test_2_1_fight ${GTEST_LIBRARIES} pthread)

add_executable (test_3_0_blob tests/3_0_blob.t.cpp)
target_link_libraries (test_3_0_blob ${GTEST_LIBRARIES} pthread)

add_executable (test_3_1_blob_history tests/3_1_blob_history.t.cpp)
target_link_libraries (test_3_1_blob_history ${GTEST_LIBRARIES} pthread)

add_executable (test_4_0_blob_distance tests/4_0_blob_distance.t.cpp)
target_link_libraries (test_4_0_blob_distance ${GTEST_LIBRARIES} pthread)

add_executable (test_5_0_blob_is_in_range tests/5_0_blob_is_in_range.t.cpp)
target_link_libraries (test_5_0_blob_is_in_range ${GTEST_LIBRARIES} pthread)

add_executable (test_5_1_blob_is_in_same_square tests/5_1_blob_is_in_same_square.t.cpp)
target_link_libraries (test_5_1_blob_is_in_same_square ${GTEST_LIBRARIES} pthread)

add_executable (test_5_2_blob_can_smell tests/5_2_blob_can_smell.t.cpp)
target_link_libraries (test_5_2_blob_can_smell ${GTEST_LIBRARIES} pthread)

add_executable (blob_angle_test tests/blob_angle.t.cpp)
target_link_libraries (blob_angle_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_kill_test tests/blob_kill.t.cpp)
target_link_libraries (blob_kill_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_fight_test tests/blob_fight.t.cpp)
target_link_libraries (blob_fight_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_attack_test tests/blob_attack.t.cpp)
target_link_libraries (blob_attack_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_move_test tests/blob_move.t.cpp)
target_link_libraries (blob_move_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_wander_fixed_angle_test tests/blob_wander_fixed_angle.t.cpp)
target_link_libraries (blob_wander_fixed_angle_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_wander_random_angle_test tests/blob_wander_random_angle.t.cpp)
target_link_libraries (blob_wander_random_angle_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_hunt_test tests/blob_hunt.t.cpp)
target_link_libraries (blob_hunt_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_flee_test tests/blob_flee.t.cpp)
target_link_libraries (blob_flee_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_tired_test tests/blob_tired.t.cpp)
target_link_libraries (blob_tired_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_dead_test tests/blob_dead.t.cpp)
target_link_libraries (blob_dead_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_age_test tests/blob_age.t.cpp)
target_link_libraries (blob_age_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_relativeDifference_test tests/blob_relativeDifference.t.cpp)
target_link_libraries (blob_relativeDifference_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_inflictDamageWeightForAttacking_test tests/blob_inflictDamageWeightForAttacking.t.cpp)
target_link_libraries (blob_inflictDamageWeightForAttacking_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_avoidDamageWeightForAttacking_test tests/blob_avoidDamageWeightForAttacking.t.cpp)
target_link_libraries (blob_avoidDamageWeightForAttacking_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_avoidDamageWeightForFleeing_test tests/blob_avoidDamageWeightForFleeing.t.cpp)
target_link_libraries (blob_avoidDamageWeightForFleeing_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_distanceWeight_test tests/blob_distanceWeight.t.cpp)
target_link_libraries (blob_distanceWeight_test ${GTEST_LIBRARIES} pthread)

add_executable (blob_chooseNextAction_test tests/blob_chooseNextAction.t.cpp)
target_link_libraries (blob_chooseNextAction_test ${GTEST_LIBRARIES} pthread)

gtest_discover_tests (test_0_0_template)
gtest_discover_tests (test_1_0_pt)
gtest_discover_tests (test_2_0_movement)
gtest_discover_tests (test_2_1_fight)
gtest_discover_tests (test_3_0_blob)
gtest_discover_tests (test_3_1_blob_history)
gtest_discover_tests (test_4_0_blob_distance)
gtest_discover_tests (test_5_0_blob_is_in_range)
gtest_discover_tests (test_5_1_blob_is_in_same_square)
gtest_discover_tests (test_5_2_blob_can_smell)
gtest_discover_tests (blob_angle_test)
gtest_discover_tests (blob_kill_test)
gtest_discover_tests (blob_fight_test)
gtest_discover_tests (blob_attack_test)
gtest_discover_tests (blob_move_test)
gtest_discover_tests (blob_wander_fixed_angle_test)
gtest_discover_tests (blob_wander_random_angle_test)
gtest_discover_tests (blob_hunt_test)
gtest_discover_tests (blob_flee_test)
gtest_discover_tests (blob_tired_test)
gtest_discover_tests (blob_dead_test)
gtest_discover_tests (blob_age_test)
gtest_discover_tests (blob_relativeDifference_test)
gtest_discover_tests (blob_inflictDamageWeightForAttacking_test)
gtest_discover_tests (blob_avoidDamageWeightForAttacking_test)
gtest_discover_tests (blob_avoidDamageWeightForFleeing_test)
gtest_discover_tests (blob_distanceWeight_test)
gtest_discover_tests (blob_chooseNextAction_test)

