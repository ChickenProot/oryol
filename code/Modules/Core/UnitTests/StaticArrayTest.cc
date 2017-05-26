//------------------------------------------------------------------------------
//  StaticArrayTest.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "UnitTest++/src/UnitTest++.h"
#include "Core/Containers/StaticArray.h"

using namespace Oryol;

TEST(StaticArrayTest) {

    StaticArray<int, 16> array0;
    StaticArray<int, 16> array1;
    CHECK(array0.Size() == 16);
    CHECK(array1.Size() == 16);
    array0.Fill(1);
    for (int v : array0) {
        CHECK(v == 1);
    }
    for (int i = 0; i < 16; i++) {
        CHECK(array0[0] == 1);
    }
    for (int i = 0; i < 16; i++) {
        array1[i] = i;
    }
    int i = 0;
    for (int v : array1) {
        CHECK(v == i++);
    }
    array0 = array1;
    for (i = 0; i < 16; i++) {
        CHECK(array0[i] == array1[i]);
        CHECK(array0[i] == i);
    }
    array1.Fill(2);
    for (int v : array1) {
        CHECK(v == 2);
    }
    array1 = std::move(array0);
    for (i = 0; i < 16; i++) {
        CHECK(array1[i] == i);
    }
    StaticArray<int, 16> array2(array0);
    StaticArray<int, 16> array3(std::move(array0));
    for (i = 0; i < 16; i++) {
        CHECK(array2[i] == i);
        CHECK(array3[i] == i);
    }

    ArrayView<int> view = array2.View(2, 5);
    CHECK(view.Size() == 5);
    CHECK(view[0] == 2);
    CHECK(view[1] == 3);
    CHECK(view[2] == 4);
    CHECK(view[3] == 5);
    CHECK(view[4] == 6);

    view = array2.View(0, array2.Size());
    CHECK(view.Size() == 16);
    CHECK(view[0] == 0);
    CHECK(view[15] == 15);
}
