#include "duckx.hpp"
#include "thirdparty/zip/zip.h"

namespace duckx {
Run::Run(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void Run::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:r");
}

void Run::set_current(pugi::xml_node node) { this->current = node; }

std::string Run::get_text() const {
    return this->current.child("w:t").text().get();
}

bool Run::set_text(const std::string &text) const {
    return this->current.child("w:t").text().set(text.c_str());
}

bool Run::set_text(const char *text) const {
    return this->current.child("w:t").text().set(text);
}

Run &Run::next() {
    this->current = this->current.next_sibling();
    return *this;
}

bool Run::has_next() const { return this->current != 0; }

// Paragraphs
Paragraph::Paragraph(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void Paragraph::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:p");

    this->run.set_parent(this->current);
}

void Paragraph::set_current(pugi::xml_node node) { this->current = node; }

Paragraph &Paragraph::next() {
    this->current = this->current.next_sibling();
    this->run.set_parent(this->current);
    return *this;
}

bool Paragraph::has_next() const { return this->current != 0; }

Run &Paragraph::runs() {
    this->run.set_parent(this->current);
    return this->run;
}

Run &Paragraph::add_run(const std::string &text, formatting_flag f) {
    return this->add_run(text.c_str(), f);
}

Run &Paragraph::add_run(const char *text, formatting_flag f) {
    // Add new run
    pugi::xml_node new_run = this->current.append_child("w:r");
    // Insert meta to new run
    pugi::xml_node meta = new_run.append_child("w:rPr");

    if (f & BOLD) {
        meta.append_child("w:b");
    }

    if (f & ITALIC) {
        meta.append_child("w:i");
    }

    if (f & UNDERLINE) {
        meta.append_child("w:u").append_attribute("w:val").set_value("single");
    }

    if (f & STRIKETHROUGH) {
        meta.append_child("w:strike")
            .append_attribute("w:val")
            .set_value("true");
    }

    if (f & SUPERSCRIPT) {
        meta.append_child("w:vertAlign")
            .append_attribute("w:val")
            .set_value("superscript");
    } else if (f & SUBSCRIPT) {
        meta.append_child("w:vertAlign")
            .append_attribute("w:val")
            .set_value("subscript");
    }

    if (f & SMALLCAPS) {
        meta.append_child("w:smallCaps")
            .append_attribute("w:val")
            .set_value("true");
    }

    if (f & SHADOW) {
        meta.append_child("w:shadow")
            .append_attribute("w:val")
            .set_value("true");
    }

    pugi::xml_node new_run_text = new_run.append_child("w:t");
    // If the run starts or ends with whitespace characters, preserve them using
    // the xml:space attribute
    if (*text != 0 && (isspace(text[0]) || isspace(text[strlen(text) - 1]))) {
        new_run_text.append_attribute("xml:space").set_value("preserve");
    }
    new_run_text.text().set(text);

    return *new Run(this->current, new_run);
}

Paragraph &Paragraph::insert_paragraph_after(const std::string &text,
                                             formatting_flag f) {
    pugi::xml_node new_para =
        this->parent.insert_child_after("w:p", this->current);

    Paragraph *p = new Paragraph();
    p->set_current(new_para);
    p->add_run(text, f);

    return *p;
}

// Table cells
TableCell::TableCell(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void TableCell::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:tc");

    this->paragraph.set_parent(this->current);
}

void TableCell::set_current(pugi::xml_node node) { this->current = node; }

Paragraph &TableCell::paragraphs() {
    this->paragraph.set_parent(this->current);
    return this->paragraph;
}

TableCell &TableCell::next() {
    this->current = this->current.next_sibling();
    return *this;
}

bool TableCell::has_next() const { return this->current != 0; }

// Table rows
TableRow::TableRow(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void TableRow::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:tr");

    this->cell.set_parent(this->current);
}

void TableRow::set_current(pugi::xml_node node) { this->current = node; }

TableCell &TableRow::cells() {
    this->cell.set_parent(this->current);
    return this->cell;
}

TableRow &TableRow::next() {
    this->current = this->current.next_sibling();
    return *this;
}

bool TableRow::has_next() const { return this->current != 0; }

// Tables
Table::Table(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void Table::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:tbl");

    this->row.set_parent(this->current);
}

void Table::set_current(pugi::xml_node node) { this->current = node; }

Table &Table::next() {
    this->current = this->current.next_sibling();
    this->row.set_parent(this->current);
    return *this;
}

bool Table::has_next() const { return this->current != 0; }

TableRow &Table::rows() {
    this->row.set_parent(this->current);
    return this->row;
}

// Document
Document::Document(const std::string &filename) { this->filename = filename; }

void Document::file(const std::string &filename) { this->filename = filename; }

void Document::open() {
    void *buf = NULL;
    size_t bufsize;

    // Open file and load "xml" content to the document variable
    zip_t *zip =
        zip_open(this->filename.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');

    if (!zip) {
        this->flag_is_open = false;
        return;
    }
    this->flag_is_open = true;

    zip_entry_open(zip, "word/document.xml");
    zip_entry_read(zip, &buf, &bufsize);

    zip_entry_close(zip);
    zip_close(zip);

    this->document.load_buffer(buf, bufsize);

    free(buf);

    this->paragraph.set_parent(document.child("w:document").child("w:body"));
}

void Document::save() const {
    // minizip only supports appending or writing to new files
    // so we must
    // - make a new file
    // - write any new files
    // - copy the old files
    // - delete old docx
    // - rename new file to old file

    if (!this->is_open()) {
        // if file is not existing, save() will make no sense
        return;
    }

    // Hack on pugixml
    // We need to write xml to std string (or char *)
    // So overload the write function
    struct xml_string_writer : pugi::xml_writer {
        std::string result;

        virtual void write(const void *data, size_t size) {
            result.append(static_cast<const char *>(data), size);
        }
    } writer;
    // Read document buffer
    this->document.print(writer);

    // Open file and replace "xml" content
    std::string original_file = this->filename;
    std::string temp_file = this->filename + ".tmp";

    // Create the new file
    zip_t *new_zip =
        zip_open(temp_file.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');

    // Write out document.xml
    zip_entry_open(new_zip, "word/document.xml");

    const char *buf = writer.result.c_str();

    zip_entry_write(new_zip, buf, writer.result.length());
    zip_entry_close(new_zip);

    // Open the original zip and copy all files which are not replaced by duckX
    zip_t *orig_zip =
        zip_open(original_file.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');

    // Loop & copy each relevant entry in the original zip
    int orig_zip_entry_ct = zip_entries_total(orig_zip);
    for (int i = 0; i < orig_zip_entry_ct; i++) {
        zip_entry_openbyindex(orig_zip, i);
        const char *name = zip_entry_name(orig_zip);

        // Skip copying the original file
        if (std::string(name) != "word/document.xml") {
            // Read the old content
            void *entry_buf;
            size_t entry_buf_size;
            zip_entry_read(orig_zip, &entry_buf, &entry_buf_size);

            // Write into new zip
            zip_entry_open(new_zip, name);
            zip_entry_write(new_zip, entry_buf, entry_buf_size);
            zip_entry_close(new_zip);

            free(entry_buf);
        }

        zip_entry_close(orig_zip);
    }

    // Close both zips
    zip_close(orig_zip);
    zip_close(new_zip);

    // Remove original zip, rename new to correct name
    remove(original_file.c_str());
    rename(temp_file.c_str(), original_file.c_str());
}

bool Document::is_open() const { return this->flag_is_open; }

Paragraph &Document::paragraphs() {
    this->paragraph.set_parent(document.child("w:document").child("w:body"));
    return this->paragraph;
}

Table &Document::tables() {
    this->table.set_parent(document.child("w:document").child("w:body"));
    return this->table;
}
} // namespace duckx
