cmake_minimum_required (VERSION 2.6)
project (libBlob)

INCLUDE_DIRECTORIES (./include)

include (GoogleTest)

find_package (GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()

add_executable (test_00_00_template tests/00_00_template.t.cpp)
target_link_libraries (test_00_00_template ${GTEST_LIBRARIES} pthread)

add_executable (test_01_00_pt tests/01_00_pt.t.cpp)
target_link_libraries (test_01_00_pt ${GTEST_LIBRARIES} pthread)

add_executable (test_02_00_movement tests/02_00_movement.t.cpp)
target_link_libraries (test_02_00_movement ${GTEST_LIBRARIES} pthread)

add_executable (test_02_01_fight tests/02_01_fight.t.cpp)
target_link_libraries (test_02_01_fight ${GTEST_LIBRARIES} pthread)

add_executable (test_03_00_blob tests/03_00_blob.t.cpp)
target_link_libraries (test_03_00_blob ${GTEST_LIBRARIES} pthread)

add_executable (test_03_01_blob_history tests/03_01_blob_history.t.cpp)
target_link_libraries (test_03_01_blob_history ${GTEST_LIBRARIES} pthread)

add_executable (test_04_00_blob_distance tests/04_00_blob_distance.t.cpp)
target_link_libraries (test_04_00_blob_distance ${GTEST_LIBRARIES} pthread)

add_executable (test_05_00_blob_isInRange tests/05_00_blob_isInRange.t.cpp)
target_link_libraries (test_05_00_blob_isInRange ${GTEST_LIBRARIES} pthread)

add_executable (test_05_01_blob_isInSameSquare tests/05_01_blob_isInSameSquare.t.cpp)
target_link_libraries (test_05_01_blob_isInSameSquare ${GTEST_LIBRARIES} pthread)

add_executable (test_05_02_blob_canSmell tests/05_02_blob_canSmell.t.cpp)
target_link_libraries (test_05_02_blob_canSmell ${GTEST_LIBRARIES} pthread)

add_executable (test_06_00_blob_angle tests/06_00_blob_angle.t.cpp)
target_link_libraries (test_06_00_blob_angle ${GTEST_LIBRARIES} pthread)

add_executable (test_07_00_blob_kill tests/07_00_blob_kill.t.cpp)
target_link_libraries (test_07_00_blob_kill ${GTEST_LIBRARIES} pthread)

add_executable (test_07_01_blob_move tests/07_01_blob_move.t.cpp)
target_link_libraries (test_07_01_blob_move ${GTEST_LIBRARIES} pthread)

add_executable (test_07_02_blob_fight tests/07_02_blob_fight.t.cpp)
target_link_libraries (test_07_02_blob_fight ${GTEST_LIBRARIES} pthread)

add_executable (test_07_03_blob_attack tests/07_03_blob_attack.t.cpp)
target_link_libraries (test_07_03_blob_attack ${GTEST_LIBRARIES} pthread)

add_executable (test_08_00_blob_age tests/08_00_blob_age.t.cpp)
target_link_libraries (test_08_00_blob_age ${GTEST_LIBRARIES} pthread)

add_executable (test_09_00_blob_flee tests/09_00_blob_flee.t.cpp)
target_link_libraries (test_09_00_blob_flee ${GTEST_LIBRARIES} pthread)

add_executable (test_09_01_blob_hunt tests/09_01_blob_hunt.t.cpp)
target_link_libraries (test_09_01_blob_hunt ${GTEST_LIBRARIES} pthread)

add_executable (test_09_02_blob_wander tests/09_02_blob_wander.t.cpp)
target_link_libraries (test_09_02_blob_wander ${GTEST_LIBRARIES} pthread)

add_executable (test_10_00_blob_relativeDifference tests/10_00_blob_relativeDifference.t.cpp)
target_link_libraries (test_10_00_blob_relativeDifference ${GTEST_LIBRARIES} pthread)

add_executable (test_10_01_blob_distanceWeight tests/10_01_blob_distanceWeight.t.cpp)
target_link_libraries (test_10_01_blob_distanceWeight ${GTEST_LIBRARIES} pthread)

add_executable (test_10_02_blob_inflictDamageWeightForAttacking tests/10_02_blob_inflictDamageWeightForAttacking.t.cpp)
target_link_libraries (test_10_02_blob_inflictDamageWeightForAttacking ${GTEST_LIBRARIES} pthread)

add_executable (test_10_03_blob_avoidDamageWeightForFleeing tests/10_03_blob_avoidDamageWeightForFleeing.t.cpp)
target_link_libraries (test_10_03_blob_avoidDamageWeightForFleeing ${GTEST_LIBRARIES} pthread)

add_executable (test_11_00_blob_chooseNextAction_weights tests/11_00_blob_chooseNextAction_weights.t.cpp)
target_link_libraries (test_11_00_blob_chooseNextAction_weights ${GTEST_LIBRARIES} pthread)

add_executable (test_11_01_blob_chooseNextAction_findOptions tests/11_01_blob_chooseNextAction_findOptions.t.cpp)
target_link_libraries (test_11_01_blob_chooseNextAction_findOptions ${GTEST_LIBRARIES} pthread)

add_executable (test_11_02_blob_chooseNextAction_prioritiseOptions tests/11_02_blob_chooseNextAction_prioritiseOptions.t.cpp)
target_link_libraries (test_11_02_blob_chooseNextAction_prioritiseOptions ${GTEST_LIBRARIES} pthread)

add_executable (test_11_03_blob_chooseNextAction_selectBestOption_same_square tests/11_03_blob_chooseNextAction_selectBestOption_same_square.t.cpp)
target_link_libraries (test_11_03_blob_chooseNextAction_selectBestOption_same_square ${GTEST_LIBRARIES} pthread)

add_executable (test_11_04_blob_chooseNextAction_selectBestOption_in_range tests/11_04_blob_chooseNextAction_selectBestOption_in_range.t.cpp)
target_link_libraries (test_11_04_blob_chooseNextAction_selectBestOption_in_range ${GTEST_LIBRARIES} pthread)

add_executable (test_11_05_blob_chooseNextAction_chooseNextAction tests/11_05_blob_chooseNextAction_chooseNextAction.t.cpp)
target_link_libraries (test_11_05_blob_chooseNextAction_chooseNextAction ${GTEST_LIBRARIES} pthread)

add_executable (test_11_06_blob_chooseNextAction_dead tests/11_06_blob_chooseNextAction_dead.t.cpp)
target_link_libraries (test_11_06_blob_chooseNextAction_dead ${GTEST_LIBRARIES} pthread)

add_executable (test_11_07_blob_chooseNextAction_wander tests/11_07_blob_chooseNextAction_wander.t.cpp)
target_link_libraries (test_11_07_blob_chooseNextAction_wander ${GTEST_LIBRARIES} pthread)

add_executable (test_12_00_blob_tired tests/12_00_blob_tired.t.cpp)
target_link_libraries (test_12_00_blob_tired ${GTEST_LIBRARIES} pthread)

gtest_discover_tests (test_00_00_template)
gtest_discover_tests (test_01_00_pt)
gtest_discover_tests (test_02_00_movement)
gtest_discover_tests (test_02_01_fight)
gtest_discover_tests (test_03_00_blob)
gtest_discover_tests (test_03_01_blob_history)
gtest_discover_tests (test_04_00_blob_distance)
gtest_discover_tests (test_05_00_blob_isInRange)
gtest_discover_tests (test_05_01_blob_isInSameSquare)
gtest_discover_tests (test_05_02_blob_canSmell)
gtest_discover_tests (test_06_00_blob_angle)
gtest_discover_tests (test_07_00_blob_kill)
gtest_discover_tests (test_07_01_blob_move)
gtest_discover_tests (test_07_02_blob_fight)
gtest_discover_tests (test_07_03_blob_attack)
gtest_discover_tests (test_08_00_blob_age)
gtest_discover_tests (test_09_00_blob_flee)
gtest_discover_tests (test_09_01_blob_hunt)
gtest_discover_tests (test_09_02_blob_wander)
gtest_discover_tests (test_10_00_blob_relativeDifference)
gtest_discover_tests (test_10_01_blob_distanceWeight)
gtest_discover_tests (test_10_02_blob_inflictDamageWeightForAttacking)
gtest_discover_tests (test_10_03_blob_avoidDamageWeightForFleeing)
gtest_discover_tests (test_11_00_blob_chooseNextAction_weights)
gtest_discover_tests (test_11_01_blob_chooseNextAction_findOptions)
gtest_discover_tests (test_11_02_blob_chooseNextAction_prioritiseOptions)
gtest_discover_tests (test_11_03_blob_chooseNextAction_selectBestOption_same_square)
gtest_discover_tests (test_11_04_blob_chooseNextAction_selectBestOption_in_range)
gtest_discover_tests (test_11_05_blob_chooseNextAction_chooseNextAction)
gtest_discover_tests (test_11_06_blob_chooseNextAction_dead)
gtest_discover_tests (test_11_07_blob_chooseNextAction_wander)
gtest_discover_tests (test_12_00_blob_tired)
