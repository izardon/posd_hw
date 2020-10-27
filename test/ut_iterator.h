#include "../src/shape.h"
#include "../src/iterator.h"
#include "../src/null_iterator.h"

class IteratorTest : public ::testing::Test {
protected:
void SetUp () override
{
        rectangle1i3l4h = new Rectangle ("r1", 3, 4);
        rectangle2i2l2h = new Rectangle ("r2", 2, 2);

        // shapes01 = new vector<Shape *>();
}

void TearDown () override
{
        delete rectangle1i3l4h;
        // delete shapes01;
}

Shape * rectangle1i3l4h;
Shape * rectangle2i2l2h;
list<Shape *> shapes01;
};

TEST_F (IteratorTest, ConstructorNullIteratorNoException) {
        ASSERT_NO_THROW (rectangle1i3l4h->createIterator ());
}

TEST_F (IteratorTest, FirstOnNullIterator) {
        try {
                rectangle1i3l4h->createIterator ()->first ();
        } catch (string e) {
                ASSERT_EQ ("No child member!", e);
        }
}

TEST_F (IteratorTest, NextOnNullIterator) {
        try {
                rectangle1i3l4h->createIterator ()->next ();
        } catch (string e) {
                ASSERT_EQ ("No child member!", e);
        }
}

TEST_F (IteratorTest, isDoneOnNullIterator) {
        ASSERT_TRUE (rectangle1i3l4h->createIterator ()->isDone ());
}

TEST_F (IteratorTest, currentItemOnNullIterator) {
        try {
                rectangle1i3l4h->createIterator ()->isDone ();
        } catch (string e) {
                ASSERT_EQ ("No child member!", e);
        }
}

TEST_F (IteratorTest, ConstructorShapeIteratorNoException) {
        shapes01.push_back (rectangle1i3l4h);
        Shape * compoundShape = new CompoundShape ("c1", shapes01);

        ASSERT_NO_THROW (compoundShape->createIterator ());
}

TEST_F (IteratorTest, FirstOnShapeIterator) {
        shapes01.push_back (rectangle1i3l4h);
        shapes01.push_back (rectangle2i2l2h);
        Shape * compoundShape = new CompoundShape ("c1", shapes01);
        Iterator * it = compoundShape->createIterator ();

        it->first ();
        ASSERT_EQ (rectangle1i3l4h, it->currentItem ());
}

TEST_F (IteratorTest, NextOnShapeIterator) {
        shapes01.push_back (rectangle1i3l4h);
        shapes01.push_back (rectangle2i2l2h);
        Shape * compoundShape = new CompoundShape ("c1", shapes01);
        Iterator * it = compoundShape->createIterator ();

        ASSERT_EQ (rectangle1i3l4h, it->currentItem ());
        it->next ();
        ASSERT_EQ (rectangle2i2l2h, it->currentItem ());
}

TEST_F (IteratorTest, NextMoveOverOnShapeIterator) {
        shapes01.push_back (rectangle1i3l4h);
        shapes01.push_back (rectangle2i2l2h);
        Shape * compoundShape = new CompoundShape ("c1", shapes01);
        Iterator * it = compoundShape->createIterator ();

        it->next ();
        it->next ();
        ASSERT_TRUE (it->isDone ());

        try {
                it->next ();
        } catch (string e) {
                ASSERT_EQ ("Moving past the end!", e);
        }
}

TEST_F (IteratorTest, isDoneOnShapeIterator) {
        shapes01.push_back (rectangle1i3l4h);
        shapes01.push_back (rectangle2i2l2h);
        Shape * compoundShape = new CompoundShape ("c1", shapes01);
        Iterator * it = compoundShape->createIterator ();

        it->next ();
        it->next ();
        ASSERT_TRUE (it->isDone ());
}

TEST_F (IteratorTest, currentItemOnShapeIterator) {
        shapes01.push_back (rectangle1i3l4h);
        shapes01.push_back (rectangle2i2l2h);
        Shape * compoundShape = new CompoundShape ("c1", shapes01);
        Iterator * it = compoundShape->createIterator ();

        ASSERT_EQ (rectangle1i3l4h, it->currentItem ());
        it->next ();
        ASSERT_EQ (rectangle2i2l2h, it->currentItem ());
}
