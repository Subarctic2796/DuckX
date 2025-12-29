// #include <duckx.hpp>
#include "../src/duckx.hpp"
#include <sstream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("checks contents of my_test.docx with iterator") {
    duckx::Document doc("my_test.docx");
    doc.open();

    std::ostringstream ss;

    for (duckx::Paragraph p : doc.paragraphs()) {
        for (duckx::Run r : p.runs()) {
            ss << r.get_text() << std::endl;
            // std::puts(r.get_text().c_str());
        }
    }
    std::puts(ss.str().c_str());
    CHECK_EQ("This is a test\nokay?\n", ss.str());
}

namespace duckx {
struct TestObject final {
    int current = 42;
    int parent = 1;
    int j = 86;
    TestObject(int parent, int current) : parent(parent), current(current) {}
    TestObject() = default;
    TestObject &next() {
        ++current;
        return *this;
    }
    bool has_next() const { return current != j; }
    bool operator==(TestObject const &other) const {
        return other.current == current && other.j == j;
    }
};
// Entry point
Iterator<TestObject, int> begin(TestObject const &obj) {
    return Iterator<TestObject, int, int>(obj.parent, obj.current);
}

Iterator<TestObject, int> end(TestObject const &obj) {
    return Iterator<TestObject, int, int>(obj.parent, 0);
}
} // namespace duckx

TEST_CASE("Check equality in") {
    auto const testObj = duckx::TestObject{};
    auto p1 = begin(testObj);
    auto p2 = begin(testObj);
    CHECK_EQ(p1, p2);
    duckx::Document doc("my_test.docx");
    doc.open();

    CHECK_EQ(begin(doc.paragraphs()), begin(doc.paragraphs()));
}
