#include <gtest/gtest.h>
#include <test.h>

TEST(TestCase1, T1) {
	ASSERT_EQ(2, 2);
}


TEST(TestCase1, T2) {
	ASSERT_EQ(2, 2);
}


TEST(TestCase2, T1) {
	ASSERT_EQ(2, 2);
}

TEST(TestCase3, T1) {
	ASSERT_EQ(2, 2);
}



class TestFix : public testing::Test {
protected:
	MyTest * test;

	void SetUp() {
		test = new MyTest;
	}

	void TearDown() {
		delete test;
	}
};

TEST_F(TestFix, test1) {
	ASSERT_TRUE(test->pass(true));
	ASSERT_FALSE(test->pass(false));
}

