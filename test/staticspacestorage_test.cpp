#include "sealib/staticspacestorage.h"
#include <gtest/gtest.h>

using Sealib::StaticSpaceStorage;

TEST(StaticSpaceStorageTest, insertAndGet) {
    std::vector<uint> b = {3, 1, 4, 30};
    StaticSpaceStorage s(StaticSpaceStorage::makeBitVector(&b));
    s.insert(0, 5);
    EXPECT_EQ(s.get(0), 5);
    s.insert(1, 1);
    EXPECT_EQ(s.get(1), 1);
    s.insert(2, 15);
    EXPECT_EQ(s.get(2), 15);
    s.insert(3, 1);
    EXPECT_EQ(s.get(3), 1);
}
