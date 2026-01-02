/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * DuckX is a free library to work with docx files.
 */

#ifndef DUCKX_H
#define DUCKX_H

#define DUCKX_VERSION "1.2.3"

#include "thirdparty/pugixml/pugixml.hpp"

namespace duckx {
// Cihan SARI start
/*
 * Under MIT license
 * Author: Cihan SARI (@CihanSari)
 * DuckX is a free library to work with docx files.
 */

template <class T, class P, class C = P> class Iterator {
  private:
    P parent{0};
    C current{0};
    mutable T buffer{};

  public:
    Iterator() = default;

    Iterator(P parent, C current) : parent(parent), current(current) {}

    constexpr bool operator!=(const Iterator &other) const {
        return parent != other.parent || current != other.current;
    }

    constexpr bool operator==(const Iterator &other) const {
        return parent == other.parent || current == other.current;
    }

    Iterator &operator++() {
        this->current = this->current.next_sibling();
        return *this;
    }

    const T &operator*() const {
        // Only update the buffer when the user wants to accces to the data
        buffer.set_parent(parent);
        buffer.set_current(current);
        return buffer;
    }

    const T *operator->() const { return &(this->operator*()); }
};

class IteratorHelper {
  private:
    using P = pugi::xml_node;
    template <class T>
    static constexpr Iterator<T, P> make_begin(T const &obj) {
        return Iterator<T, P>(obj.parent, obj.current);
    }

    template <class T> static constexpr Iterator<T, P> make_end(T const &obj) {
        return Iterator<T, P>(obj.parent,
                              static_cast<decltype(obj.current)>(0));
    }

    template <class T> friend constexpr Iterator<T, P> begin(T const &obj);
    template <class T> friend constexpr Iterator<T, P> end(T const &obj);
};

// Entry point
template <class T> constexpr Iterator<T, pugi::xml_node> begin(T const &obj) {
    return IteratorHelper::make_begin(obj);
}

template <class T> constexpr Iterator<T, pugi::xml_node> end(T const &obj) {
    return IteratorHelper::make_end(obj);
}
// Cihan SARI end

// TODO: Use container-iterator design pattern!

// constants.hpp start
// text-formatting flags
enum formatting_flag {
    NONE = 0,
    BOLD = 1 << 0,
    ITALIC = 1 << 1,
    UNDERLINE = 1 << 2,
    STRIKETHROUGH = 1 << 3,
    SUPERSCRIPT = 1 << 4,
    SUBSCRIPT = 1 << 5,
    SMALLCAPS = 1 << 6,
    SHADOW = 1 << 7,
};
// constants.hpp end

// Run contains runs in a paragraph
class Run {
  private:
    friend class IteratorHelper;
    // Store the parent node (a paragraph)
    pugi::xml_node parent;
    // And store current node also
    pugi::xml_node current;

  public:
    Run() = default;
    Run(pugi::xml_node parent, pugi::xml_node current);
    void set_parent(pugi::xml_node node);
    void set_current(pugi::xml_node node);

    std::string get_text() const;
    bool set_text(const std::string &text) const;
    bool set_text(const char *text) const;

    Run &next();
    bool has_next() const;
};

// Paragraph contains a paragraph
// and stores runs
class Paragraph {
  private:
    friend class IteratorHelper;
    // Store parent node (usually the body node)
    pugi::xml_node parent;
    // And store current node also
    pugi::xml_node current;
    // A paragraph consists of runs
    Run run;

  public:
    Paragraph() = default;
    Paragraph(pugi::xml_node parent, pugi::xml_node current);
    void set_parent(pugi::xml_node node);
    void set_current(pugi::xml_node node);

    Paragraph &next();
    bool has_next() const;

    Run &runs();
    Run &add_run(const std::string &text, formatting_flag f = NONE);
    Run &add_run(const char *text, formatting_flag f = NONE);
    Paragraph &insert_paragraph_after(const std::string &text,
                                      formatting_flag f = NONE);
};

// TableCell contains one or more paragraphs
class TableCell {
  private:
    friend class IteratorHelper;
    pugi::xml_node parent;
    pugi::xml_node current;

    Paragraph paragraph;

  public:
    TableCell() = default;
    TableCell(pugi::xml_node parent, pugi::xml_node current);

    void set_parent(pugi::xml_node node);
    void set_current(pugi::xml_node node);

    Paragraph &paragraphs();

    TableCell &next();
    bool has_next() const;
};

// TableRow consists of one or more TableCells
class TableRow {
    friend class IteratorHelper;
    pugi::xml_node parent;
    pugi::xml_node current;

    TableCell cell;

  public:
    TableRow() = default;
    TableRow(pugi::xml_node parent, pugi::xml_node current);
    void set_parent(pugi::xml_node node);
    void set_current(pugi::xml_node node);

    TableCell &cells();

    bool has_next() const;
    TableRow &next();
};

// Table consists of one or more TableRow objects
class Table {
  private:
    friend class IteratorHelper;
    pugi::xml_node parent;
    pugi::xml_node current;

    TableRow row;

  public:
    Table() = default;
    Table(pugi::xml_node parent, pugi::xml_node current);
    void set_parent(pugi::xml_node node);
    void set_current(pugi::xml_node node);

    Table &next();
    bool has_next() const;

    TableRow &rows();
};

// Document contains whole the docx file
// and stores paragraphs
class Document {
  private:
    friend class IteratorHelper;
    std::string filename;
    Paragraph paragraph;
    Table table;
    pugi::xml_document document;
    bool flag_is_open;

  public:
    Document() = default;
    Document(const std::string &filename);
    void file(const std::string &filename);
    void open();
    void save() const;
    bool is_open() const;

    Paragraph &paragraphs();
    Table &tables();
};
} // namespace duckx
#endif
