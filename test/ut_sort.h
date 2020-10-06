#include "../src/sort.h"

class QuickSort : public ::testing::Test {
protected:
void SetUp () override
{
        rectangle3l4h = new Rectangle (3, 4);
        rectangle2l2h = new Rectangle (2, 2);
        rectangle5l10h = new Rectangle (5, 10);
}

void TearDown () override
{
        delete rectangle3l4h;
        delete rectangle2l2h;
        delete rectangle5l10h;
}

Shape * rectangle3l4h;
Shape * rectangle2l2h;
Shape * rectangle5l10h;
};

TEST_F (QuickSort, SubtypePolymorphism){
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        ASSERT_EQ (12, shapes [0]->area ());
        ASSERT_EQ (4, shapes [1]->area ());
        ASSERT_EQ (50, shapes [2]->area ());
}

TEST_F (QuickSort, areaAscendingByLambda) {
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        quickSort (shapes, shapes + 3, [] (Shape * a, Shape * b) {
                return a->area () < b->area ();
        });
        ASSERT_EQ (4, shapes [0]->area ());
        ASSERT_EQ (12, shapes [1]->area ());
        ASSERT_EQ (50, shapes [2]->area ());
}

TEST_F (QuickSort, areaDescendingByLambda) {
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        quickSort (shapes, shapes + 3, [] (Shape * a, Shape * b) {
                return a->area () > b->area ();
        });
        ASSERT_EQ (50, shapes [0]->area ());
        ASSERT_EQ (12, shapes [1]->area ());
        ASSERT_EQ (4, shapes [2]->area ());
}

TEST_F (QuickSort, perimeterAscendingByLambda) {
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        quickSort (shapes, shapes + 3, [] (Shape * a, Shape * b) {
                return a->perimeter () < b->perimeter ();
        });
        ASSERT_EQ (8, shapes [0]->perimeter ());
        ASSERT_EQ (14, shapes [1]->perimeter ());
        ASSERT_EQ (30, shapes [2]->perimeter ());
}

TEST_F (QuickSort, perimeterDescendingByLambda) {
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        quickSort (shapes, shapes + 3, [] (Shape * a, Shape * b) {
                return a->perimeter () > b->perimeter ();
        });
        ASSERT_EQ (30, shapes [0]->perimeter ());
        ASSERT_EQ (14, shapes [1]->perimeter ());
        ASSERT_EQ (8, shapes [2]->perimeter ());
}

TEST_F (QuickSort, areaAscendingByFuntion) {
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        quickSort (shapes, shapes + 3, areaAscendingCompare);
        ASSERT_EQ (4, shapes [0]->area ());
        ASSERT_EQ (12, shapes [1]->area ());
        ASSERT_EQ (50, shapes [2]->area ());
}

TEST_F (QuickSort, areaDescendingByFuntion) {
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        quickSort (shapes, shapes + 3, areaDescendingCompare);
        ASSERT_EQ (50, shapes [0]->area ());
        ASSERT_EQ (12, shapes [1]->area ());
        ASSERT_EQ (4, shapes [2]->area ());
}

TEST_F (QuickSort, perimeterAscendingByFuntion) {
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        quickSort (shapes, shapes + 3, perimeterAscendingCompare);
        ASSERT_EQ (8, shapes [0]->perimeter ());
        ASSERT_EQ (14, shapes [1]->perimeter ());
        ASSERT_EQ (30, shapes [2]->perimeter ());
}

TEST_F (QuickSort, perimeterDescendingByFuntion) {
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        quickSort (shapes, shapes + 3, perimeterDescendingCompare);
        ASSERT_EQ (30, shapes [0]->perimeter ());
        ASSERT_EQ (14, shapes [1]->perimeter ());
        ASSERT_EQ (8, shapes [2]->perimeter ());
}

TEST_F (QuickSort, areaAscendingByObject) {
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        quickSort (shapes, shapes + 3, AscendingCompare ("area"));
        ASSERT_EQ (4, shapes [0]->area ());
        ASSERT_EQ (12, shapes [1]->area ());
        ASSERT_EQ (50, shapes [2]->area ());
}

TEST_F (QuickSort, areaDescendingByObject) {
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        quickSort (shapes, shapes + 3, DescendingCompare ("area"));
        ASSERT_EQ (50, shapes [0]->area ());
        ASSERT_EQ (12, shapes [1]->area ());
        ASSERT_EQ (4, shapes [2]->area ());
}

TEST_F (QuickSort, perimeterAscendingByObject) {
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        quickSort (shapes, shapes + 3, AscendingCompare ("perimeter"));
        ASSERT_EQ (8, shapes [0]->perimeter ());
        ASSERT_EQ (14, shapes [1]->perimeter ());
        ASSERT_EQ (30, shapes [2]->perimeter ());
}

TEST_F (QuickSort, perimeterDescendingByObject) {
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        quickSort (shapes, shapes + 3, DescendingCompare ("perimeter"));
        ASSERT_EQ (30, shapes [0]->perimeter ());
        ASSERT_EQ (14, shapes [1]->perimeter ());
        ASSERT_EQ (8, shapes [2]->perimeter ());
}

TEST_F (QuickSort, AscendingCompareFeatureInvalid) {
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        try {
                quickSort (shapes, shapes + 3, AscendingCompare ("test"));
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Feature is invalid!", e);
        }
}

TEST_F (QuickSort, DescendingCompareFeatureInvalid) {
        Shape * shapes[3] = { rectangle3l4h, rectangle2l2h, rectangle5l10h };

        try {
                quickSort (shapes, shapes + 3, AscendingCompare ("test"));
                FAIL ();
        } catch (string e) {
                ASSERT_EQ ("Feature is invalid!", e);
        }
}
