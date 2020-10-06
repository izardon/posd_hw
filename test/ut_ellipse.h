#include "../src/ellipse.h"

using namespace std;

TEST(Ellipse, ConstructorNoException) {
        ASSERT_NO_THROW(Ellipse ellipse(2, 1));
}

TEST(Ellipse, ExceptionForSemiMajorAxesIsZero) {
        try {
                Ellipse ellipse(0, 1);
                FAIL();
        } catch(string e) {
                ASSERT_EQ("This is not an ellipse!", e);
        }
}

TEST(Ellipse, ExceptionForSemiMinorAxesIsZero) {
        try {
                Ellipse ellipse(1, 0);
                FAIL();
        } catch(string e) {
                ASSERT_EQ("This is not an ellipse!", e);
        }
}

TEST(Ellipse, ExceptionForSemiMajorAxesLessThanZero) {
        try {
                Ellipse ellipse(0, -1);
                FAIL();
        } catch(string e) {
                ASSERT_EQ("This is not an ellipse!", e);
        }
}

TEST(Ellipse, ExceptionForSemiMinorAxesLessThanZero) {
        try {
                Ellipse ellipse(-1, 0);
                FAIL();
        } catch(string e) {
                ASSERT_EQ("This is not an ellipse!", e);
        }
}

TEST(Ellipse, ExceptionForSemiMajorAxesLessThanSemiMinorAxes) {
        try {
                Ellipse ellipse(1, 2);
                FAIL();
        } catch(string e) {
                ASSERT_EQ("This is not an ellipse!", e);
        }
}

TEST(Ellipse, AreaInt) {
        Ellipse ellipse(5, 4);

        ASSERT_NEAR(62.831, ellipse.area(), 0.001);
}

TEST(Ellipse, AreaDouble) {
        Ellipse ellipse(5.2, 4.3);

        ASSERT_NEAR(70.246, ellipse.area(), 0.001);
}

TEST(Ellipse, PerimeterInt) {
        Ellipse ellipse(3, 2);

        ASSERT_NEAR(16.566, ellipse.perimeter(), 0.001);
}

TEST(Ellipse, PerimeterDouble) {
        Ellipse ellipse(3.2, 2.8);

        ASSERT_NEAR(19.192, ellipse.perimeter(), 0.001);
}

TEST(Ellipse, Info) {
        Ellipse ellipse(6, 5);

        ASSERT_EQ("Ellipse (6.000, 5.000)", ellipse.info());
}
