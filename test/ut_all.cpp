#include <gtest/gtest.h>
#include "Iterator_test.h"
#include "dfsIterator_test.h"
#include "bfsIterator_test.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
