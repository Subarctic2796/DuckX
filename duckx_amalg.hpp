#ifndef DUCKX_AMALG_HPP
#define DUCKX_AMALG_HPP

/**
 * pugixml parser - version 1.15
 * --------------------------------------------------------
 * Report bugs and download new versions at https://pugixml.org/
 *
 * SPDX-FileCopyrightText: Copyright (C) 2006-2025, by Arseny Kapoulkine
 * (arseny.kapoulkine@gmail.com) SPDX-License-Identifier: MIT
 *
 * See LICENSE.md or notice at the end of this file.
 */

#ifndef HEADER_PUGICONFIG_HPP
#define HEADER_PUGICONFIG_HPP

// Uncomment this to enable wchar_t mode
// #define PUGIXML_WCHAR_MODE

// Uncomment this to enable compact mode
// #define PUGIXML_COMPACT

// Uncomment this to disable XPath
// #define PUGIXML_NO_XPATH

// Uncomment this to disable STL
// #define PUGIXML_NO_STL

// Uncomment this to disable exceptions
// #define PUGIXML_NO_EXCEPTIONS

// Set this to control attributes for public classes/functions, i.e.:
// #define PUGIXML_API __declspec(dllexport) // to export all public symbols
// from DLL #define PUGIXML_CLASS __declspec(dllimport) // to import all classes
// from DLL #define PUGIXML_FUNCTION __fastcall // to set calling conventions to
// all public functions to fastcall In absence of PUGIXML_CLASS/PUGIXML_FUNCTION
// definitions PUGIXML_API is used instead

// Tune these constants to adjust memory-related behavior
// #define PUGIXML_MEMORY_PAGE_SIZE 32768
// #define PUGIXML_MEMORY_OUTPUT_STACK 10240
// #define PUGIXML_MEMORY_XPATH_PAGE_SIZE 4096

// Tune this constant to adjust max nesting for XPath queries
// #define PUGIXML_XPATH_DEPTH_LIMIT 1024

// Uncomment this to switch to header-only version
#define PUGIXML_HEADER_ONLY

// Uncomment this to enable long long support (usually enabled automatically)
// #define PUGIXML_HAS_LONG_LONG

// Uncomment this to enable support for std::string_view (usually enabled
// automatically) #define PUGIXML_HAS_STRING_VIEW

#endif

/**
 * Copyright (c) 2006-2025 Arseny Kapoulkine
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * pugixml parser - version 1.15
 * --------------------------------------------------------
 * Report bugs and download new versions at https://pugixml.org/
 *
 * SPDX-FileCopyrightText: Copyright (C) 2006-2025, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
 * SPDX-License-Identifier: MIT
 *
 * See LICENSE.md or notice at the end of this file.
 */

// Define version macro; evaluates to major * 1000 + minor * 10 + patch so that it's safe to use in less-than comparisons
// Note: pugixml used major * 100 + minor * 10 + patch format up until 1.9 (which had version identifier 190); starting from pugixml 1.10, the minor version number is two digits
#ifndef PUGIXML_VERSION
#	define PUGIXML_VERSION 1150 // 1.15
#endif

// Include user configuration file (this can define various configuration macros)


#ifndef HEADER_PUGIXML_HPP
#define HEADER_PUGIXML_HPP

// Include stddef.h for size_t and ptrdiff_t
#include <stddef.h>

// Include exception header for XPath
#if !defined(PUGIXML_NO_XPATH) && !defined(PUGIXML_NO_EXCEPTIONS)
#	include <exception>
#endif

// Include STL headers
#ifndef PUGIXML_NO_STL
#	include <iterator>
#	include <iosfwd>
#	include <string>
#endif

// Check if std::string_view is available
#if !defined(PUGIXML_HAS_STRING_VIEW) && !defined(PUGIXML_NO_STL)
#	if __cplusplus >= 201703L
#		define PUGIXML_HAS_STRING_VIEW
#	elif defined(_MSVC_LANG) && _MSVC_LANG >= 201703L
#		define PUGIXML_HAS_STRING_VIEW
#	endif
#endif

// Include string_view if appropriate
#ifdef PUGIXML_HAS_STRING_VIEW
#	include <string_view>
#endif

// Macro for deprecated features
#ifndef PUGIXML_DEPRECATED
#	if defined(__GNUC__)
#		define PUGIXML_DEPRECATED __attribute__((deprecated))
#	elif defined(_MSC_VER) && _MSC_VER >= 1300
#		define PUGIXML_DEPRECATED __declspec(deprecated)
#	else
#		define PUGIXML_DEPRECATED
#	endif
#endif

// If no API is defined, assume default
#ifndef PUGIXML_API
#	define PUGIXML_API
#endif

// If no API for classes is defined, assume default
#ifndef PUGIXML_CLASS
#	define PUGIXML_CLASS PUGIXML_API
#endif

// If no API for functions is defined, assume default
#ifndef PUGIXML_FUNCTION
#	define PUGIXML_FUNCTION PUGIXML_API
#endif

// If the platform is known to have long long support, enable long long functions
#ifndef PUGIXML_HAS_LONG_LONG
#	if __cplusplus >= 201103
#		define PUGIXML_HAS_LONG_LONG
#	elif defined(_MSC_VER) && _MSC_VER >= 1400
#		define PUGIXML_HAS_LONG_LONG
#	endif
#endif

// If the platform is known to have move semantics support, compile move ctor/operator implementation
#ifndef PUGIXML_HAS_MOVE
#	if __cplusplus >= 201103
#		define PUGIXML_HAS_MOVE
#	elif defined(_MSC_VER) && _MSC_VER >= 1600
#		define PUGIXML_HAS_MOVE
#	endif
#endif

// If C++ is 2011 or higher, use 'noexcept' specifiers
#ifndef PUGIXML_NOEXCEPT
#	if __cplusplus >= 201103
#		define PUGIXML_NOEXCEPT noexcept
#	elif defined(_MSC_VER) && _MSC_VER >= 1900
#		define PUGIXML_NOEXCEPT noexcept
#	else
#		define PUGIXML_NOEXCEPT throw()
#	endif
#endif

// Some functions can not be noexcept in compact mode
#ifdef PUGIXML_COMPACT
#	define PUGIXML_NOEXCEPT_IF_NOT_COMPACT
#else
#	define PUGIXML_NOEXCEPT_IF_NOT_COMPACT PUGIXML_NOEXCEPT
#endif

// If C++ is 2011 or higher, add 'override' qualifiers
#ifndef PUGIXML_OVERRIDE
#	if __cplusplus >= 201103
#		define PUGIXML_OVERRIDE override
#	elif defined(_MSC_VER) && _MSC_VER >= 1700
#		define PUGIXML_OVERRIDE override
#	else
#		define PUGIXML_OVERRIDE
#	endif
#endif

// If C++ is 2011 or higher, use 'nullptr'
#ifndef PUGIXML_NULL
#	if __cplusplus >= 201103
#		define PUGIXML_NULL nullptr
#	elif defined(_MSC_VER) && _MSC_VER >= 1600
#		define PUGIXML_NULL nullptr
#	else
#		define PUGIXML_NULL 0
#	endif
#endif

// Character interface macros
#ifdef PUGIXML_WCHAR_MODE
#	define PUGIXML_TEXT(t) L ## t
#	define PUGIXML_CHAR wchar_t
#else
#	define PUGIXML_TEXT(t) t
#	define PUGIXML_CHAR char
#endif

namespace pugi
{
	// Character type used for all internal storage and operations; depends on PUGIXML_WCHAR_MODE
	typedef PUGIXML_CHAR char_t;

#ifndef PUGIXML_NO_STL
	// String type used for operations that work with STL string; depends on PUGIXML_WCHAR_MODE
	typedef std::basic_string<PUGIXML_CHAR> string_t;
#endif

#ifdef PUGIXML_HAS_STRING_VIEW
	// String view type used for operations that can work with a length delimited string; depends on PUGIXML_WCHAR_MODE
	typedef std::basic_string_view<PUGIXML_CHAR> string_view_t;
#endif
}

// The PugiXML namespace
namespace pugi
{
	// Tree node types
	enum xml_node_type
	{
		node_null,			// Empty (null) node handle
		node_document,		// A document tree's absolute root
		node_element,		// Element tag, i.e. '<node/>'
		node_pcdata,		// Plain character data, i.e. 'text'
		node_cdata,			// Character data, i.e. '<![CDATA[text]]>'
		node_comment,		// Comment tag, i.e. '<!-- text -->'
		node_pi,			// Processing instruction, i.e. '<?name?>'
		node_declaration,	// Document declaration, i.e. '<?xml version="1.0"?>'
		node_doctype		// Document type declaration, i.e. '<!DOCTYPE doc>'
	};

	// Parsing options

	// Minimal parsing mode (equivalent to turning all other flags off).
	// Only elements and PCDATA sections are added to the DOM tree, no text conversions are performed.
	const unsigned int parse_minimal = 0x0000;

	// This flag determines if processing instructions (node_pi) are added to the DOM tree. This flag is off by default.
	const unsigned int parse_pi = 0x0001;

	// This flag determines if comments (node_comment) are added to the DOM tree. This flag is off by default.
	const unsigned int parse_comments = 0x0002;

	// This flag determines if CDATA sections (node_cdata) are added to the DOM tree. This flag is on by default.
	const unsigned int parse_cdata = 0x0004;

	// This flag determines if plain character data (node_pcdata) that consist only of whitespace are added to the DOM tree.
	// This flag is off by default; turning it on usually results in slower parsing and more memory consumption.
	const unsigned int parse_ws_pcdata = 0x0008;

	// This flag determines if character and entity references are expanded during parsing. This flag is on by default.
	const unsigned int parse_escapes = 0x0010;

	// This flag determines if EOL characters are normalized (converted to #xA) during parsing. This flag is on by default.
	const unsigned int parse_eol = 0x0020;

	// This flag determines if attribute values are normalized using CDATA normalization rules during parsing. This flag is on by default.
	const unsigned int parse_wconv_attribute = 0x0040;

	// This flag determines if attribute values are normalized using NMTOKENS normalization rules during parsing. This flag is off by default.
	const unsigned int parse_wnorm_attribute = 0x0080;

	// This flag determines if document declaration (node_declaration) is added to the DOM tree. This flag is off by default.
	const unsigned int parse_declaration = 0x0100;

	// This flag determines if document type declaration (node_doctype) is added to the DOM tree. This flag is off by default.
	const unsigned int parse_doctype = 0x0200;

	// This flag determines if plain character data (node_pcdata) that is the only child of the parent node and that consists only
	// of whitespace is added to the DOM tree.
	// This flag is off by default; turning it on may result in slower parsing and more memory consumption.
	const unsigned int parse_ws_pcdata_single = 0x0400;

	// This flag determines if leading and trailing whitespace is to be removed from plain character data. This flag is off by default.
	const unsigned int parse_trim_pcdata = 0x0800;

	// This flag determines if plain character data that does not have a parent node is added to the DOM tree, and if an empty document
	// is a valid document. This flag is off by default.
	const unsigned int parse_fragment = 0x1000;

	// This flag determines if plain character data is be stored in the parent element's value. This significantly changes the structure of
	// the document; this flag is only recommended for parsing documents with many PCDATA nodes in memory-constrained environments.
	// This flag is off by default.
	const unsigned int parse_embed_pcdata = 0x2000;

	// This flag determines whether determines whether the the two pcdata should be merged or not, if no intermediatory data are parsed in the document.
	// This flag is off by default.
	const unsigned int parse_merge_pcdata = 0x4000;

	// The default parsing mode.
	// Elements, PCDATA and CDATA sections are added to the DOM tree, character/reference entities are expanded,
	// End-of-Line characters are normalized, attribute values are normalized using CDATA normalization rules.
	const unsigned int parse_default = parse_cdata | parse_escapes | parse_wconv_attribute | parse_eol;

	// The full parsing mode.
	// Nodes of all types are added to the DOM tree, character/reference entities are expanded,
	// End-of-Line characters are normalized, attribute values are normalized using CDATA normalization rules.
	const unsigned int parse_full = parse_default | parse_pi | parse_comments | parse_declaration | parse_doctype;

	// These flags determine the encoding of input data for XML document
	enum xml_encoding
	{
		encoding_auto,		// Auto-detect input encoding using BOM or < / <? detection; use UTF8 if BOM is not found
		encoding_utf8,		// UTF8 encoding
		encoding_utf16_le,	// Little-endian UTF16
		encoding_utf16_be,	// Big-endian UTF16
		encoding_utf16,		// UTF16 with native endianness
		encoding_utf32_le,	// Little-endian UTF32
		encoding_utf32_be,	// Big-endian UTF32
		encoding_utf32,		// UTF32 with native endianness
		encoding_wchar,		// The same encoding wchar_t has (either UTF16 or UTF32)
		encoding_latin1
	};

	// Formatting flags

	// Indent the nodes that are written to output stream with as many indentation strings as deep the node is in DOM tree. This flag is on by default.
	const unsigned int format_indent = 0x01;

	// Write encoding-specific BOM to the output stream. This flag is off by default.
	const unsigned int format_write_bom = 0x02;

	// Use raw output mode (no indentation and no line breaks are written). This flag is off by default.
	const unsigned int format_raw = 0x04;

	// Omit default XML declaration even if there is no declaration in the document. This flag is off by default.
	const unsigned int format_no_declaration = 0x08;

	// Don't escape attribute values and PCDATA contents. This flag is off by default.
	const unsigned int format_no_escapes = 0x10;

	// Open file using text mode in xml_document::save_file. This enables special character (i.e. new-line) conversions on some systems. This flag is off by default.
	const unsigned int format_save_file_text = 0x20;

	// Write every attribute on a new line with appropriate indentation. This flag is off by default.
	const unsigned int format_indent_attributes = 0x40;

	// Don't output empty element tags, instead writing an explicit start and end tag even if there are no children. This flag is off by default.
	const unsigned int format_no_empty_element_tags = 0x80;

	// Skip characters belonging to range [0; 32) instead of "&#xNN;" encoding. This flag is off by default.
	const unsigned int format_skip_control_chars = 0x100;

	// Use single quotes ' instead of double quotes " for enclosing attribute values. This flag is off by default.
	const unsigned int format_attribute_single_quote = 0x200;

	// The default set of formatting flags.
	// Nodes are indented depending on their depth in DOM tree, a default declaration is output if document has none.
	const unsigned int format_default = format_indent;

	const int default_double_precision = 17;
	const int default_float_precision = 9;

	// Forward declarations
	struct xml_attribute_struct;
	struct xml_node_struct;

	class xml_node_iterator;
	class xml_attribute_iterator;
	class xml_named_node_iterator;

	class xml_tree_walker;

	struct xml_parse_result;

	class xml_node;

	class xml_text;

	#ifndef PUGIXML_NO_XPATH
	class xpath_node;
	class xpath_node_set;
	class xpath_query;
	class xpath_variable_set;
	#endif

	// Range-based for loop support
	template <typename It> class xml_object_range
	{
	public:
		typedef It const_iterator;
		typedef It iterator;

		xml_object_range(It b, It e): _begin(b), _end(e)
		{
		}

		It begin() const { return _begin; }
		It end() const { return _end; }

		bool empty() const { return _begin == _end; }

	private:
		It _begin, _end;
	};

	// Writer interface for node printing (see xml_node::print)
	class PUGIXML_CLASS xml_writer
	{
	public:
		virtual ~xml_writer();

		// Write memory chunk into stream/file/whatever
		virtual void write(const void* data, size_t size) = 0;
	};

	// xml_writer implementation for FILE*
	class PUGIXML_CLASS xml_writer_file: public xml_writer
	{
	public:
		// Construct writer from a FILE* object; void* is used to avoid header dependencies on stdio
		xml_writer_file(void* file);

		virtual void write(const void* data, size_t size) PUGIXML_OVERRIDE;

	private:
		void* file;
	};

	#ifndef PUGIXML_NO_STL
	// xml_writer implementation for streams
	class PUGIXML_CLASS xml_writer_stream: public xml_writer
	{
	public:
		// Construct writer from an output stream object
		xml_writer_stream(std::basic_ostream<char>& stream);
		xml_writer_stream(std::basic_ostream<wchar_t>& stream);

		virtual void write(const void* data, size_t size) PUGIXML_OVERRIDE;

	private:
		std::basic_ostream<char>* narrow_stream;
		std::basic_ostream<wchar_t>* wide_stream;
	};
	#endif

	// A light-weight handle for manipulating attributes in DOM tree
	class PUGIXML_CLASS xml_attribute
	{
		friend class xml_attribute_iterator;
		friend class xml_node;

	private:
		xml_attribute_struct* _attr;

		typedef void (*unspecified_bool_type)(xml_attribute***);

	public:
		// Default constructor. Constructs an empty attribute.
		xml_attribute();

		// Constructs attribute from internal pointer
		explicit xml_attribute(xml_attribute_struct* attr);

		// Safe bool conversion operator
		operator unspecified_bool_type() const;

		// Borland C++ workaround
		bool operator!() const;

		// Comparison operators (compares wrapped attribute pointers)
		bool operator==(const xml_attribute& r) const;
		bool operator!=(const xml_attribute& r) const;
		bool operator<(const xml_attribute& r) const;
		bool operator>(const xml_attribute& r) const;
		bool operator<=(const xml_attribute& r) const;
		bool operator>=(const xml_attribute& r) const;

		// Check if attribute is empty (null)
		bool empty() const;

		// Get attribute name/value, or "" if attribute is empty
		const char_t* name() const;
		const char_t* value() const;

		// Get attribute value, or the default value if attribute is empty
		const char_t* as_string(const char_t* def = PUGIXML_TEXT("")) const;

		// Get attribute value as a number, or the default value if conversion did not succeed or attribute is empty
		int as_int(int def = 0) const;
		unsigned int as_uint(unsigned int def = 0) const;
		double as_double(double def = 0) const;
		float as_float(float def = 0) const;

	#ifdef PUGIXML_HAS_LONG_LONG
		long long as_llong(long long def = 0) const;
		unsigned long long as_ullong(unsigned long long def = 0) const;
	#endif

		// Get attribute value as bool (returns true if first character is in '1tTyY' set), or the default value if attribute is empty
		bool as_bool(bool def = false) const;

		// Set attribute name/value (returns false if attribute is empty or there is not enough memory)
		bool set_name(const char_t* rhs);
		bool set_name(const char_t* rhs, size_t size);
	#ifdef PUGIXML_HAS_STRING_VIEW
		bool set_name(string_view_t rhs);
	#endif
		bool set_value(const char_t* rhs);
		bool set_value(const char_t* rhs, size_t size);
	#ifdef PUGIXML_HAS_STRING_VIEW
		bool set_value(string_view_t rhs);
	#endif

		// Set attribute value with type conversion (numbers are converted to strings, boolean is converted to "true"/"false")
		bool set_value(int rhs);
		bool set_value(unsigned int rhs);
		bool set_value(long rhs);
		bool set_value(unsigned long rhs);
		bool set_value(double rhs);
		bool set_value(double rhs, int precision);
		bool set_value(float rhs);
		bool set_value(float rhs, int precision);
		bool set_value(bool rhs);

	#ifdef PUGIXML_HAS_LONG_LONG
		bool set_value(long long rhs);
		bool set_value(unsigned long long rhs);
	#endif

		// Set attribute value (equivalent to set_value without error checking)
		xml_attribute& operator=(const char_t* rhs);
		xml_attribute& operator=(int rhs);
		xml_attribute& operator=(unsigned int rhs);
		xml_attribute& operator=(long rhs);
		xml_attribute& operator=(unsigned long rhs);
		xml_attribute& operator=(double rhs);
		xml_attribute& operator=(float rhs);
		xml_attribute& operator=(bool rhs);

	#ifdef PUGIXML_HAS_STRING_VIEW
		xml_attribute& operator=(string_view_t rhs);
	#endif

	#ifdef PUGIXML_HAS_LONG_LONG
		xml_attribute& operator=(long long rhs);
		xml_attribute& operator=(unsigned long long rhs);
	#endif

		// Get next/previous attribute in the attribute list of the parent node
		xml_attribute next_attribute() const;
		xml_attribute previous_attribute() const;

		// Get hash value (unique for handles to the same object)
		size_t hash_value() const;

		// Get internal pointer
		xml_attribute_struct* internal_object() const;
	};

#ifdef __BORLANDC__
	// Borland C++ workaround
	bool PUGIXML_FUNCTION operator&&(const xml_attribute& lhs, bool rhs);
	bool PUGIXML_FUNCTION operator||(const xml_attribute& lhs, bool rhs);
#endif

	// A light-weight handle for manipulating nodes in DOM tree
	class PUGIXML_CLASS xml_node
	{
		friend class xml_attribute_iterator;
		friend class xml_node_iterator;
		friend class xml_named_node_iterator;

	protected:
		xml_node_struct* _root;

		typedef void (*unspecified_bool_type)(xml_node***);

	public:
		// Default constructor. Constructs an empty node.
		xml_node();

		// Constructs node from internal pointer
		explicit xml_node(xml_node_struct* p);

		// Safe bool conversion operator
		operator unspecified_bool_type() const;

		// Borland C++ workaround
		bool operator!() const;

		// Comparison operators (compares wrapped node pointers)
		bool operator==(const xml_node& r) const;
		bool operator!=(const xml_node& r) const;
		bool operator<(const xml_node& r) const;
		bool operator>(const xml_node& r) const;
		bool operator<=(const xml_node& r) const;
		bool operator>=(const xml_node& r) const;

		// Check if node is empty (null)
		bool empty() const;

		// Get node type
		xml_node_type type() const;

		// Get node name, or "" if node is empty or it has no name
		const char_t* name() const;

		// Get node value, or "" if node is empty or it has no value
		// Note: For <node>text</node> node.value() does not return "text"! Use child_value() or text() methods to access text inside nodes.
		const char_t* value() const;

		// Get attribute list
		xml_attribute first_attribute() const;
		xml_attribute last_attribute() const;

		// Get children list
		xml_node first_child() const;
		xml_node last_child() const;

		// Get next/previous sibling in the children list of the parent node
		xml_node next_sibling() const;
		xml_node previous_sibling() const;

		// Get parent node
		xml_node parent() const;

		// Get root of DOM tree this node belongs to
		xml_node root() const;

		// Get text object for the current node
		xml_text text() const;

		// Get child, attribute or next/previous sibling with the specified name
		xml_node child(const char_t* name) const;
		xml_attribute attribute(const char_t* name) const;
		xml_node next_sibling(const char_t* name) const;
		xml_node previous_sibling(const char_t* name) const;
	#ifdef PUGIXML_HAS_STRING_VIEW
		xml_node child(string_view_t name) const;
		xml_attribute attribute(string_view_t name) const;
		xml_node next_sibling(string_view_t name) const;
		xml_node previous_sibling(string_view_t name) const;
	#endif

		// Get attribute, starting the search from a hint (and updating hint so that searching for a sequence of attributes is fast)
		xml_attribute attribute(const char_t* name, xml_attribute& hint) const;
	#ifdef PUGIXML_HAS_STRING_VIEW
		xml_attribute attribute(string_view_t name, xml_attribute& hint) const;
	#endif

		// Get child value of current node; that is, value of the first child node of type PCDATA/CDATA
		const char_t* child_value() const;

		// Get child value of child with specified name. Equivalent to child(name).child_value().
		const char_t* child_value(const char_t* name) const;

		// Set node name/value (returns false if node is empty, there is not enough memory, or node can not have name/value)
		bool set_name(const char_t* rhs);
		bool set_name(const char_t* rhs, size_t size);
	#ifdef PUGIXML_HAS_STRING_VIEW
		bool set_name(string_view_t rhs);
	#endif
		bool set_value(const char_t* rhs);
		bool set_value(const char_t* rhs, size_t size);
	#ifdef PUGIXML_HAS_STRING_VIEW
		bool set_value(string_view_t rhs);
	#endif

		// Add attribute with specified name. Returns added attribute, or empty attribute on errors.
		xml_attribute append_attribute(const char_t* name);
		xml_attribute prepend_attribute(const char_t* name);
		xml_attribute insert_attribute_after(const char_t* name, const xml_attribute& attr);
		xml_attribute insert_attribute_before(const char_t* name, const xml_attribute& attr);
	#ifdef PUGIXML_HAS_STRING_VIEW
		xml_attribute append_attribute(string_view_t name);
		xml_attribute prepend_attribute(string_view_t name);
		xml_attribute insert_attribute_after(string_view_t name, const xml_attribute& attr);
		xml_attribute insert_attribute_before(string_view_t name, const xml_attribute& attr);
	#endif

		// Add a copy of the specified attribute. Returns added attribute, or empty attribute on errors.
		xml_attribute append_copy(const xml_attribute& proto);
		xml_attribute prepend_copy(const xml_attribute& proto);
		xml_attribute insert_copy_after(const xml_attribute& proto, const xml_attribute& attr);
		xml_attribute insert_copy_before(const xml_attribute& proto, const xml_attribute& attr);

		// Add child node with specified type. Returns added node, or empty node on errors.
		xml_node append_child(xml_node_type type = node_element);
		xml_node prepend_child(xml_node_type type = node_element);
		xml_node insert_child_after(xml_node_type type, const xml_node& node);
		xml_node insert_child_before(xml_node_type type, const xml_node& node);

		// Add child element with specified name. Returns added node, or empty node on errors.
		xml_node append_child(const char_t* name);
		xml_node prepend_child(const char_t* name);
		xml_node insert_child_after(const char_t* name, const xml_node& node);
		xml_node insert_child_before(const char_t* name, const xml_node& node);
	#ifdef PUGIXML_HAS_STRING_VIEW
		xml_node append_child(string_view_t name);
		xml_node prepend_child(string_view_t name);
		xml_node insert_child_after(string_view_t, const xml_node& node);
		xml_node insert_child_before(string_view_t name, const xml_node& node);
	#endif

		// Add a copy of the specified node as a child. Returns added node, or empty node on errors.
		xml_node append_copy(const xml_node& proto);
		xml_node prepend_copy(const xml_node& proto);
		xml_node insert_copy_after(const xml_node& proto, const xml_node& node);
		xml_node insert_copy_before(const xml_node& proto, const xml_node& node);

		// Move the specified node to become a child of this node. Returns moved node, or empty node on errors.
		xml_node append_move(const xml_node& moved);
		xml_node prepend_move(const xml_node& moved);
		xml_node insert_move_after(const xml_node& moved, const xml_node& node);
		xml_node insert_move_before(const xml_node& moved, const xml_node& node);

		// Remove specified attribute
		bool remove_attribute(const xml_attribute& a);
		bool remove_attribute(const char_t* name);
	#ifdef PUGIXML_HAS_STRING_VIEW
		bool remove_attribute(string_view_t name);
	#endif

		// Remove all attributes
		bool remove_attributes();

		// Remove specified child
		bool remove_child(const xml_node& n);
		bool remove_child(const char_t* name);
	#ifdef PUGIXML_HAS_STRING_VIEW
		bool remove_child(string_view_t name);
	#endif

		// Remove all children
		bool remove_children();

		// Parses buffer as an XML document fragment and appends all nodes as children of the current node.
		// Copies/converts the buffer, so it may be deleted or changed after the function returns.
		// Note: append_buffer allocates memory that has the lifetime of the owning document; removing the appended nodes does not immediately reclaim that memory.
		xml_parse_result append_buffer(const void* contents, size_t size, unsigned int options = parse_default, xml_encoding encoding = encoding_auto);

		// Find attribute using predicate. Returns first attribute for which predicate returned true.
		template <typename Predicate> xml_attribute find_attribute(Predicate pred) const
		{
			if (!_root) return xml_attribute();

			for (xml_attribute attrib = first_attribute(); attrib; attrib = attrib.next_attribute())
				if (pred(attrib))
					return attrib;

			return xml_attribute();
		}

		// Find child node using predicate. Returns first child for which predicate returned true.
		template <typename Predicate> xml_node find_child(Predicate pred) const
		{
			if (!_root) return xml_node();

			for (xml_node node = first_child(); node; node = node.next_sibling())
				if (pred(node))
					return node;

			return xml_node();
		}

		// Find node from subtree using predicate. Returns first node from subtree (depth-first), for which predicate returned true.
		template <typename Predicate> xml_node find_node(Predicate pred) const
		{
			if (!_root) return xml_node();

			xml_node cur = first_child();

			while (cur._root && cur._root != _root)
			{
				if (pred(cur)) return cur;

				if (cur.first_child()) cur = cur.first_child();
				else if (cur.next_sibling()) cur = cur.next_sibling();
				else
				{
					while (!cur.next_sibling() && cur._root != _root) cur = cur.parent();

					if (cur._root != _root) cur = cur.next_sibling();
				}
			}

			return xml_node();
		}

		// Find child node by attribute name/value
		xml_node find_child_by_attribute(const char_t* name, const char_t* attr_name, const char_t* attr_value) const;
		xml_node find_child_by_attribute(const char_t* attr_name, const char_t* attr_value) const;

	#ifndef PUGIXML_NO_STL
		// Get the absolute node path from root as a text string.
		string_t path(char_t delimiter = '/') const;
	#endif

		// Search for a node by path consisting of node names and . or .. elements.
		xml_node first_element_by_path(const char_t* path, char_t delimiter = '/') const;

		// Recursively traverse subtree with xml_tree_walker
		bool traverse(xml_tree_walker& walker);

	#ifndef PUGIXML_NO_XPATH
		// Select single node by evaluating XPath query. Returns first node from the resulting node set.
		xpath_node select_node(const char_t* query, xpath_variable_set* variables = PUGIXML_NULL) const;
		xpath_node select_node(const xpath_query& query) const;

		// Select node set by evaluating XPath query
		xpath_node_set select_nodes(const char_t* query, xpath_variable_set* variables = PUGIXML_NULL) const;
		xpath_node_set select_nodes(const xpath_query& query) const;

		// (deprecated: use select_node instead) Select single node by evaluating XPath query.
		PUGIXML_DEPRECATED xpath_node select_single_node(const char_t* query, xpath_variable_set* variables = PUGIXML_NULL) const;
		PUGIXML_DEPRECATED xpath_node select_single_node(const xpath_query& query) const;

	#endif

		// Print subtree using a writer object
		void print(xml_writer& writer, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default, xml_encoding encoding = encoding_auto, unsigned int depth = 0) const;

	#ifndef PUGIXML_NO_STL
		// Print subtree to stream
		void print(std::basic_ostream<char>& os, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default, xml_encoding encoding = encoding_auto, unsigned int depth = 0) const;
		void print(std::basic_ostream<wchar_t>& os, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default, unsigned int depth = 0) const;
	#endif

		// Child nodes iterators
		typedef xml_node_iterator iterator;

		iterator begin() const;
		iterator end() const;

		// Attribute iterators
		typedef xml_attribute_iterator attribute_iterator;

		attribute_iterator attributes_begin() const;
		attribute_iterator attributes_end() const;

		// Range-based for support
		xml_object_range<xml_node_iterator> children() const;
		xml_object_range<xml_attribute_iterator> attributes() const;

		// Range-based for support for all children with the specified name
		// Note: name pointer must have a longer lifetime than the returned object; be careful with passing temporaries!
		xml_object_range<xml_named_node_iterator> children(const char_t* name) const;

		// Get node offset in parsed file/string (in char_t units) for debugging purposes
		ptrdiff_t offset_debug() const;

		// Get hash value (unique for handles to the same object)
		size_t hash_value() const;

		// Get internal pointer
		xml_node_struct* internal_object() const;
	};

#ifdef __BORLANDC__
	// Borland C++ workaround
	bool PUGIXML_FUNCTION operator&&(const xml_node& lhs, bool rhs);
	bool PUGIXML_FUNCTION operator||(const xml_node& lhs, bool rhs);
#endif

	// A helper for working with text inside PCDATA nodes
	class PUGIXML_CLASS xml_text
	{
		friend class xml_node;

		xml_node_struct* _root;

		typedef void (*unspecified_bool_type)(xml_text***);

		explicit xml_text(xml_node_struct* root);

		xml_node_struct* _data_new();
		xml_node_struct* _data() const;

	public:
		// Default constructor. Constructs an empty object.
		xml_text();

		// Safe bool conversion operator
		operator unspecified_bool_type() const;

		// Borland C++ workaround
		bool operator!() const;

		// Check if text object is empty (null)
		bool empty() const;

		// Get text, or "" if object is empty
		const char_t* get() const;

		// Get text, or the default value if object is empty
		const char_t* as_string(const char_t* def = PUGIXML_TEXT("")) const;

		// Get text as a number, or the default value if conversion did not succeed or object is empty
		int as_int(int def = 0) const;
		unsigned int as_uint(unsigned int def = 0) const;
		double as_double(double def = 0) const;
		float as_float(float def = 0) const;

	#ifdef PUGIXML_HAS_LONG_LONG
		long long as_llong(long long def = 0) const;
		unsigned long long as_ullong(unsigned long long def = 0) const;
	#endif

		// Get text as bool (returns true if first character is in '1tTyY' set), or the default value if object is empty
		bool as_bool(bool def = false) const;

		// Set text (returns false if object is empty or there is not enough memory)
		bool set(const char_t* rhs);
		bool set(const char_t* rhs, size_t size);
	#ifdef PUGIXML_HAS_STRING_VIEW
		bool set(string_view_t rhs);
	#endif

		// Set text with type conversion (numbers are converted to strings, boolean is converted to "true"/"false")
		bool set(int rhs);
		bool set(unsigned int rhs);
		bool set(long rhs);
		bool set(unsigned long rhs);
		bool set(double rhs);
		bool set(double rhs, int precision);
		bool set(float rhs);
		bool set(float rhs, int precision);
		bool set(bool rhs);

	#ifdef PUGIXML_HAS_LONG_LONG
		bool set(long long rhs);
		bool set(unsigned long long rhs);
	#endif

		// Set text (equivalent to set without error checking)
		xml_text& operator=(const char_t* rhs);
		xml_text& operator=(int rhs);
		xml_text& operator=(unsigned int rhs);
		xml_text& operator=(long rhs);
		xml_text& operator=(unsigned long rhs);
		xml_text& operator=(double rhs);
		xml_text& operator=(float rhs);
		xml_text& operator=(bool rhs);

	#ifdef PUGIXML_HAS_STRING_VIEW
		xml_text& operator=(string_view_t rhs);
	#endif

	#ifdef PUGIXML_HAS_LONG_LONG
		xml_text& operator=(long long rhs);
		xml_text& operator=(unsigned long long rhs);
	#endif

		// Get the data node (node_pcdata or node_cdata) for this object
		xml_node data() const;
	};

#ifdef __BORLANDC__
	// Borland C++ workaround
	bool PUGIXML_FUNCTION operator&&(const xml_text& lhs, bool rhs);
	bool PUGIXML_FUNCTION operator||(const xml_text& lhs, bool rhs);
#endif

	// Child node iterator (a bidirectional iterator over a collection of xml_node)
	class PUGIXML_CLASS xml_node_iterator
	{
		friend class xml_node;

	private:
		mutable xml_node _wrap;
		xml_node _parent;

		xml_node_iterator(xml_node_struct* ref, xml_node_struct* parent);

	public:
		// Iterator traits
		typedef ptrdiff_t difference_type;
		typedef xml_node value_type;
		typedef xml_node* pointer;
		typedef xml_node& reference;

	#ifndef PUGIXML_NO_STL
		typedef std::bidirectional_iterator_tag iterator_category;
	#endif

		// Default constructor
		xml_node_iterator();

		// Construct an iterator which points to the specified node
		xml_node_iterator(const xml_node& node);

		// Iterator operators
		bool operator==(const xml_node_iterator& rhs) const;
		bool operator!=(const xml_node_iterator& rhs) const;

		xml_node& operator*() const;
		xml_node* operator->() const;

		xml_node_iterator& operator++();
		xml_node_iterator operator++(int);

		xml_node_iterator& operator--();
		xml_node_iterator operator--(int);
	};

	// Attribute iterator (a bidirectional iterator over a collection of xml_attribute)
	class PUGIXML_CLASS xml_attribute_iterator
	{
		friend class xml_node;

	private:
		mutable xml_attribute _wrap;
		xml_node _parent;

		xml_attribute_iterator(xml_attribute_struct* ref, xml_node_struct* parent);

	public:
		// Iterator traits
		typedef ptrdiff_t difference_type;
		typedef xml_attribute value_type;
		typedef xml_attribute* pointer;
		typedef xml_attribute& reference;

	#ifndef PUGIXML_NO_STL
		typedef std::bidirectional_iterator_tag iterator_category;
	#endif

		// Default constructor
		xml_attribute_iterator();

		// Construct an iterator which points to the specified attribute
		xml_attribute_iterator(const xml_attribute& attr, const xml_node& parent);

		// Iterator operators
		bool operator==(const xml_attribute_iterator& rhs) const;
		bool operator!=(const xml_attribute_iterator& rhs) const;

		xml_attribute& operator*() const;
		xml_attribute* operator->() const;

		xml_attribute_iterator& operator++();
		xml_attribute_iterator operator++(int);

		xml_attribute_iterator& operator--();
		xml_attribute_iterator operator--(int);
	};

	// Named node range helper
	class PUGIXML_CLASS xml_named_node_iterator
	{
		friend class xml_node;

	public:
		// Iterator traits
		typedef ptrdiff_t difference_type;
		typedef xml_node value_type;
		typedef xml_node* pointer;
		typedef xml_node& reference;

	#ifndef PUGIXML_NO_STL
		typedef std::bidirectional_iterator_tag iterator_category;
	#endif

		// Default constructor
		xml_named_node_iterator();

		// Construct an iterator which points to the specified node
		// Note: name pointer is stored in the iterator and must have a longer lifetime than iterator itself
		xml_named_node_iterator(const xml_node& node, const char_t* name);

		// Iterator operators
		bool operator==(const xml_named_node_iterator& rhs) const;
		bool operator!=(const xml_named_node_iterator& rhs) const;

		xml_node& operator*() const;
		xml_node* operator->() const;

		xml_named_node_iterator& operator++();
		xml_named_node_iterator operator++(int);

		xml_named_node_iterator& operator--();
		xml_named_node_iterator operator--(int);

	private:
		mutable xml_node _wrap;
		xml_node _parent;
		const char_t* _name;

		xml_named_node_iterator(xml_node_struct* ref, xml_node_struct* parent, const char_t* name);
	};

	// Abstract tree walker class (see xml_node::traverse)
	class PUGIXML_CLASS xml_tree_walker
	{
		friend class xml_node;

	private:
		int _depth;

	protected:
		// Get current traversal depth
		int depth() const;

	public:
		xml_tree_walker();
		virtual ~xml_tree_walker();

		// Callback that is called when traversal begins
		virtual bool begin(xml_node& node);

		// Callback that is called for each node traversed
		virtual bool for_each(xml_node& node) = 0;

		// Callback that is called when traversal ends
		virtual bool end(xml_node& node);
	};

	// Parsing status, returned as part of xml_parse_result object
	enum xml_parse_status
	{
		status_ok = 0,				// No error

		status_file_not_found,		// File was not found during load_file()
		status_io_error,			// Error reading from file/stream
		status_out_of_memory,		// Could not allocate memory
		status_internal_error,		// Internal error occurred

		status_unrecognized_tag,	// Parser could not determine tag type

		status_bad_pi,				// Parsing error occurred while parsing document declaration/processing instruction
		status_bad_comment,			// Parsing error occurred while parsing comment
		status_bad_cdata,			// Parsing error occurred while parsing CDATA section
		status_bad_doctype,			// Parsing error occurred while parsing document type declaration
		status_bad_pcdata,			// Parsing error occurred while parsing PCDATA section
		status_bad_start_element,	// Parsing error occurred while parsing start element tag
		status_bad_attribute,		// Parsing error occurred while parsing element attribute
		status_bad_end_element,		// Parsing error occurred while parsing end element tag
		status_end_element_mismatch,// There was a mismatch of start-end tags (closing tag had incorrect name, some tag was not closed or there was an excessive closing tag)

		status_append_invalid_root,	// Unable to append nodes since root type is not node_element or node_document (exclusive to xml_node::append_buffer)

		status_no_document_element	// Parsing resulted in a document without element nodes
	};

	// Parsing result
	struct PUGIXML_CLASS xml_parse_result
	{
		// Parsing status (see xml_parse_status)
		xml_parse_status status;

		// Last parsed offset (in char_t units from start of input data)
		ptrdiff_t offset;

		// Source document encoding
		xml_encoding encoding;

		// Default constructor, initializes object to failed state
		xml_parse_result();

		// Cast to bool operator
		operator bool() const;

		// Get error description
		const char* description() const;
	};

	// Document class (DOM tree root)
	class PUGIXML_CLASS xml_document: public xml_node
	{
	private:
		char_t* _buffer;

		char _memory[192];

		// Non-copyable semantics
		xml_document(const xml_document&);
		xml_document& operator=(const xml_document&);

		void _create();
		void _destroy();
		void _move(xml_document& rhs) PUGIXML_NOEXCEPT_IF_NOT_COMPACT;

	public:
		// Default constructor, makes empty document
		xml_document();

		// Destructor, invalidates all node/attribute handles to this document
		~xml_document();

	#ifdef PUGIXML_HAS_MOVE
		// Move semantics support
		xml_document(xml_document&& rhs) PUGIXML_NOEXCEPT_IF_NOT_COMPACT;
		xml_document& operator=(xml_document&& rhs) PUGIXML_NOEXCEPT_IF_NOT_COMPACT;
	#endif

		// Removes all nodes, leaving the empty document
		void reset();

		// Removes all nodes, then copies the entire contents of the specified document
		void reset(const xml_document& proto);

	#ifndef PUGIXML_NO_STL
		// Load document from stream.
		xml_parse_result load(std::basic_istream<char>& stream, unsigned int options = parse_default, xml_encoding encoding = encoding_auto);
		xml_parse_result load(std::basic_istream<wchar_t>& stream, unsigned int options = parse_default);
	#endif

		// (deprecated: use load_string instead) Load document from zero-terminated string. No encoding conversions are applied.
		PUGIXML_DEPRECATED xml_parse_result load(const char_t* contents, unsigned int options = parse_default);

		// Load document from zero-terminated string. No encoding conversions are applied.
		xml_parse_result load_string(const char_t* contents, unsigned int options = parse_default);

		// Load document from file
		xml_parse_result load_file(const char* path, unsigned int options = parse_default, xml_encoding encoding = encoding_auto);
		xml_parse_result load_file(const wchar_t* path, unsigned int options = parse_default, xml_encoding encoding = encoding_auto);

		// Load document from buffer. Copies/converts the buffer, so it may be deleted or changed after the function returns.
		xml_parse_result load_buffer(const void* contents, size_t size, unsigned int options = parse_default, xml_encoding encoding = encoding_auto);

		// Load document from buffer, using the buffer for in-place parsing (the buffer is modified and used for storage of document data).
		// You should ensure that buffer data will persist throughout the document's lifetime, and free the buffer memory manually once document is destroyed.
		xml_parse_result load_buffer_inplace(void* contents, size_t size, unsigned int options = parse_default, xml_encoding encoding = encoding_auto);

		// Load document from buffer, using the buffer for in-place parsing (the buffer is modified and used for storage of document data).
		// You should allocate the buffer with pugixml allocation function; document will free the buffer when it is no longer needed (you can't use it anymore).
		xml_parse_result load_buffer_inplace_own(void* contents, size_t size, unsigned int options = parse_default, xml_encoding encoding = encoding_auto);

		// Save XML document to writer (semantics is slightly different from xml_node::print, see documentation for details).
		void save(xml_writer& writer, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default, xml_encoding encoding = encoding_auto) const;

	#ifndef PUGIXML_NO_STL
		// Save XML document to stream (semantics is slightly different from xml_node::print, see documentation for details).
		void save(std::basic_ostream<char>& stream, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default, xml_encoding encoding = encoding_auto) const;
		void save(std::basic_ostream<wchar_t>& stream, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default) const;
	#endif

		// Save XML to file
		bool save_file(const char* path, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default, xml_encoding encoding = encoding_auto) const;
		bool save_file(const wchar_t* path, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default, xml_encoding encoding = encoding_auto) const;

		// Get document element
		xml_node document_element() const;
	};

#ifndef PUGIXML_NO_XPATH
	// XPath query return type
	enum xpath_value_type
	{
		xpath_type_none,	  // Unknown type (query failed to compile)
		xpath_type_node_set,  // Node set (xpath_node_set)
		xpath_type_number,	  // Number
		xpath_type_string,	  // String
		xpath_type_boolean	  // Boolean
	};

	// XPath parsing result
	struct PUGIXML_CLASS xpath_parse_result
	{
		// Error message (0 if no error)
		const char* error;

		// Last parsed offset (in char_t units from string start)
		ptrdiff_t offset;

		// Default constructor, initializes object to failed state
		xpath_parse_result();

		// Cast to bool operator
		operator bool() const;

		// Get error description
		const char* description() const;
	};

	// A single XPath variable
	class PUGIXML_CLASS xpath_variable
	{
		friend class xpath_variable_set;

	protected:
		xpath_value_type _type;
		xpath_variable* _next;

		xpath_variable(xpath_value_type type);

		// Non-copyable semantics
		xpath_variable(const xpath_variable&);
		xpath_variable& operator=(const xpath_variable&);

	public:
		// Get variable name
		const char_t* name() const;

		// Get variable type
		xpath_value_type type() const;

		// Get variable value; no type conversion is performed, default value (false, NaN, empty string, empty node set) is returned on type mismatch error
		bool get_boolean() const;
		double get_number() const;
		const char_t* get_string() const;
		const xpath_node_set& get_node_set() const;

		// Set variable value; no type conversion is performed, false is returned on type mismatch error
		bool set(bool value);
		bool set(double value);
		bool set(const char_t* value);
		bool set(const xpath_node_set& value);
	};

	// A set of XPath variables
	class PUGIXML_CLASS xpath_variable_set
	{
	private:
		xpath_variable* _data[64];

		void _assign(const xpath_variable_set& rhs);
		void _swap(xpath_variable_set& rhs);

		xpath_variable* _find(const char_t* name) const;

		static bool _clone(xpath_variable* var, xpath_variable** out_result);
		static void _destroy(xpath_variable* var);

	public:
		// Default constructor/destructor
		xpath_variable_set();
		~xpath_variable_set();

		// Copy constructor/assignment operator
		xpath_variable_set(const xpath_variable_set& rhs);
		xpath_variable_set& operator=(const xpath_variable_set& rhs);

	#ifdef PUGIXML_HAS_MOVE
		// Move semantics support
		xpath_variable_set(xpath_variable_set&& rhs) PUGIXML_NOEXCEPT;
		xpath_variable_set& operator=(xpath_variable_set&& rhs) PUGIXML_NOEXCEPT;
	#endif

		// Add a new variable or get the existing one, if the types match
		xpath_variable* add(const char_t* name, xpath_value_type type);

		// Set value of an existing variable; no type conversion is performed, false is returned if there is no such variable or if types mismatch
		bool set(const char_t* name, bool value);
		bool set(const char_t* name, double value);
		bool set(const char_t* name, const char_t* value);
		bool set(const char_t* name, const xpath_node_set& value);

		// Get existing variable by name
		xpath_variable* get(const char_t* name);
		const xpath_variable* get(const char_t* name) const;
	};

	// A compiled XPath query object
	class PUGIXML_CLASS xpath_query
	{
	private:
		void* _impl;
		xpath_parse_result _result;

		typedef void (*unspecified_bool_type)(xpath_query***);

		// Non-copyable semantics
		xpath_query(const xpath_query&);
		xpath_query& operator=(const xpath_query&);

	public:
		// Construct a compiled object from XPath expression.
		// If PUGIXML_NO_EXCEPTIONS is not defined, throws xpath_exception on compilation errors.
		explicit xpath_query(const char_t* query, xpath_variable_set* variables = PUGIXML_NULL);

		// Constructor
		xpath_query();

		// Destructor
		~xpath_query();

	#ifdef PUGIXML_HAS_MOVE
		// Move semantics support
		xpath_query(xpath_query&& rhs) PUGIXML_NOEXCEPT;
		xpath_query& operator=(xpath_query&& rhs) PUGIXML_NOEXCEPT;
	#endif

		// Get query expression return type
		xpath_value_type return_type() const;

		// Evaluate expression as boolean value in the specified context; performs type conversion if necessary.
		// If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
		bool evaluate_boolean(const xpath_node& n) const;

		// Evaluate expression as double value in the specified context; performs type conversion if necessary.
		// If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
		double evaluate_number(const xpath_node& n) const;

	#ifndef PUGIXML_NO_STL
		// Evaluate expression as string value in the specified context; performs type conversion if necessary.
		// If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
		string_t evaluate_string(const xpath_node& n) const;
	#endif

		// Evaluate expression as string value in the specified context; performs type conversion if necessary.
		// At most capacity characters are written to the destination buffer, full result size is returned (includes terminating zero).
		// If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
		// If PUGIXML_NO_EXCEPTIONS is defined, returns empty  set instead.
		size_t evaluate_string(char_t* buffer, size_t capacity, const xpath_node& n) const;

		// Evaluate expression as node set in the specified context.
		// If PUGIXML_NO_EXCEPTIONS is not defined, throws xpath_exception on type mismatch and std::bad_alloc on out of memory errors.
		// If PUGIXML_NO_EXCEPTIONS is defined, returns empty node set instead.
		xpath_node_set evaluate_node_set(const xpath_node& n) const;

		// Evaluate expression as node set in the specified context.
		// Return first node in document order, or empty node if node set is empty.
		// If PUGIXML_NO_EXCEPTIONS is not defined, throws xpath_exception on type mismatch and std::bad_alloc on out of memory errors.
		// If PUGIXML_NO_EXCEPTIONS is defined, returns empty node instead.
		xpath_node evaluate_node(const xpath_node& n) const;

		// Get parsing result (used to get compilation errors in PUGIXML_NO_EXCEPTIONS mode)
		const xpath_parse_result& result() const;

		// Safe bool conversion operator
		operator unspecified_bool_type() const;

		// Borland C++ workaround
		bool operator!() const;
	};

	#ifndef PUGIXML_NO_EXCEPTIONS
        #if defined(_MSC_VER)
          // C4275 can be ignored in Visual C++ if you are deriving
          // from a type in the Standard C++ Library
          #pragma warning(push)
          #pragma warning(disable: 4275)
        #endif
	// XPath exception class
	class PUGIXML_CLASS xpath_exception: public std::exception
	{
	private:
		xpath_parse_result _result;

	public:
		// Construct exception from parse result
		explicit xpath_exception(const xpath_parse_result& result);

		// Get error message
		virtual const char* what() const PUGIXML_NOEXCEPT PUGIXML_OVERRIDE;

		// Get parse result
		const xpath_parse_result& result() const;
	};
        #if defined(_MSC_VER)
          #pragma warning(pop)
        #endif
	#endif

	// XPath node class (either xml_node or xml_attribute)
	class PUGIXML_CLASS xpath_node
	{
	private:
		xml_node _node;
		xml_attribute _attribute;

		typedef void (*unspecified_bool_type)(xpath_node***);

	public:
		// Default constructor; constructs empty XPath node
		xpath_node();

		// Construct XPath node from XML node/attribute
		xpath_node(const xml_node& node);
		xpath_node(const xml_attribute& attribute, const xml_node& parent);

		// Get node/attribute, if any
		xml_node node() const;
		xml_attribute attribute() const;

		// Get parent of contained node/attribute
		xml_node parent() const;

		// Safe bool conversion operator
		operator unspecified_bool_type() const;

		// Borland C++ workaround
		bool operator!() const;

		// Comparison operators
		bool operator==(const xpath_node& n) const;
		bool operator!=(const xpath_node& n) const;
	};

#ifdef __BORLANDC__
	// Borland C++ workaround
	bool PUGIXML_FUNCTION operator&&(const xpath_node& lhs, bool rhs);
	bool PUGIXML_FUNCTION operator||(const xpath_node& lhs, bool rhs);
#endif

	// A fixed-size collection of XPath nodes
	class PUGIXML_CLASS xpath_node_set
	{
	public:
		// Collection type
		enum type_t
		{
			type_unsorted,			// Not ordered
			type_sorted,			// Sorted by document order (ascending)
			type_sorted_reverse		// Sorted by document order (descending)
		};

		// Constant iterator type
		typedef const xpath_node* const_iterator;

		// We define non-constant iterator to be the same as constant iterator so that various generic algorithms (i.e. boost foreach) work
		typedef const xpath_node* iterator;

		// Default constructor. Constructs empty set.
		xpath_node_set();

		// Constructs a set from iterator range; data is not checked for duplicates and is not sorted according to provided type, so be careful
		xpath_node_set(const_iterator begin, const_iterator end, type_t type = type_unsorted);

		// Destructor
		~xpath_node_set();

		// Copy constructor/assignment operator
		xpath_node_set(const xpath_node_set& ns);
		xpath_node_set& operator=(const xpath_node_set& ns);

	#ifdef PUGIXML_HAS_MOVE
		// Move semantics support
		xpath_node_set(xpath_node_set&& rhs) PUGIXML_NOEXCEPT;
		xpath_node_set& operator=(xpath_node_set&& rhs) PUGIXML_NOEXCEPT;
	#endif

		// Get collection type
		type_t type() const;

		// Get collection size
		size_t size() const;

		// Indexing operator
		const xpath_node& operator[](size_t index) const;

		// Collection iterators
		const_iterator begin() const;
		const_iterator end() const;

		// Sort the collection in ascending/descending order by document order
		void sort(bool reverse = false);

		// Get first node in the collection by document order
		xpath_node first() const;

		// Check if collection is empty
		bool empty() const;

	private:
		type_t _type;

		xpath_node _storage[1];

		xpath_node* _begin;
		xpath_node* _end;

		void _assign(const_iterator begin, const_iterator end, type_t type);
		void _move(xpath_node_set& rhs) PUGIXML_NOEXCEPT;
	};
#endif

#ifndef PUGIXML_NO_STL
	// Convert wide string to UTF8
	std::basic_string<char> PUGIXML_FUNCTION as_utf8(const wchar_t* str);
	std::basic_string<char> PUGIXML_FUNCTION as_utf8(const std::basic_string<wchar_t>& str);

	// Convert UTF8 to wide string
	std::basic_string<wchar_t> PUGIXML_FUNCTION as_wide(const char* str);
	std::basic_string<wchar_t> PUGIXML_FUNCTION as_wide(const std::basic_string<char>& str);
#endif

	// Memory allocation function interface; returns pointer to allocated memory or NULL on failure
	typedef void* (*allocation_function)(size_t size);

	// Memory deallocation function interface
	typedef void (*deallocation_function)(void* ptr);

	// Override default memory management functions. All subsequent allocations/deallocations will be performed via supplied functions.
	void PUGIXML_FUNCTION set_memory_management_functions(allocation_function allocate, deallocation_function deallocate);

	// Get current memory management functions
	allocation_function PUGIXML_FUNCTION get_memory_allocation_function();
	deallocation_function PUGIXML_FUNCTION get_memory_deallocation_function();
}

#if !defined(PUGIXML_NO_STL) && (defined(_MSC_VER) || defined(__ICC))
namespace std
{
	// Workarounds for (non-standard) iterator category detection for older versions (MSVC7/IC8 and earlier)
	std::bidirectional_iterator_tag PUGIXML_FUNCTION _Iter_cat(const pugi::xml_node_iterator&);
	std::bidirectional_iterator_tag PUGIXML_FUNCTION _Iter_cat(const pugi::xml_attribute_iterator&);
	std::bidirectional_iterator_tag PUGIXML_FUNCTION _Iter_cat(const pugi::xml_named_node_iterator&);
}
#endif

#if !defined(PUGIXML_NO_STL) && defined(__SUNPRO_CC)
namespace std
{
	// Workarounds for (non-standard) iterator category detection
	std::bidirectional_iterator_tag PUGIXML_FUNCTION __iterator_category(const pugi::xml_node_iterator&);
	std::bidirectional_iterator_tag PUGIXML_FUNCTION __iterator_category(const pugi::xml_attribute_iterator&);
	std::bidirectional_iterator_tag PUGIXML_FUNCTION __iterator_category(const pugi::xml_named_node_iterator&);
}
#endif

#endif

// Make sure implementation is included in header-only mode
// Use macro expansion in #include to work around QMake (QTBUG-11923)
#if defined(PUGIXML_HEADER_ONLY) && !defined(PUGIXML_SOURCE)
#	define PUGIXML_SOURCE "pugixml.cpp"
/**
 * pugixml parser - version 1.15
 * --------------------------------------------------------
 * Report bugs and download new versions at https://pugixml.org/
 *
 * SPDX-FileCopyrightText: Copyright (C) 2006-2025, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
 * SPDX-License-Identifier: MIT
 *
 * See LICENSE.md or notice at the end of this file.
 */

#ifndef SOURCE_PUGIXML_CPP
#define SOURCE_PUGIXML_CPP



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#ifdef PUGIXML_WCHAR_MODE
#	include <wchar.h>
#endif

#ifndef PUGIXML_NO_XPATH
#	include <math.h>
#	include <float.h>
#endif

#ifndef PUGIXML_NO_STL
#	include <istream>
#	include <ostream>
#	include <string>
#endif

// For placement new
#include <new>

// For load_file
#if defined(__linux__) || defined(__APPLE__)
#include <sys/stat.h>
#endif

#ifdef _MSC_VER
#	pragma warning(push)
#	pragma warning(disable: 4127) // conditional expression is constant
#	pragma warning(disable: 4324) // structure was padded due to __declspec(align())
#	pragma warning(disable: 4702) // unreachable code
#	pragma warning(disable: 4996) // this function or variable may be unsafe
#endif

#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant" // NULL as null pointer constant
#endif

#if defined(_MSC_VER) && defined(__c2__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wdeprecated" // this function or variable may be unsafe
#endif

#ifdef __INTEL_COMPILER
#	pragma warning(disable: 177) // function was declared but never referenced
#	pragma warning(disable: 279) // controlling expression is constant
#	pragma warning(disable: 1478 1786) // function was declared "deprecated"
#	pragma warning(disable: 1684) // conversion from pointer to same-sized integral type
#endif

#if defined(__BORLANDC__) && defined(PUGIXML_HEADER_ONLY)
#	pragma warn -8080 // symbol is declared but never used; disabling this inside push/pop bracket does not make the warning go away
#endif

#ifdef __BORLANDC__
#	pragma option push
#	pragma warn -8008 // condition is always false
#	pragma warn -8066 // unreachable code
#endif

#ifdef __SNC__
// Using diag_push/diag_pop does not disable the warnings inside templates due to a compiler bug
#	pragma diag_suppress=178 // function was declared but never referenced
#	pragma diag_suppress=237 // controlling expression is constant
#endif

#ifdef __TI_COMPILER_VERSION__
#	pragma diag_suppress 179 // function was declared but never referenced
#endif

// Inlining controls
#if defined(_MSC_VER) && _MSC_VER >= 1300
#	define PUGI_IMPL_NO_INLINE __declspec(noinline)
#elif defined(__GNUC__)
#	define PUGI_IMPL_NO_INLINE __attribute__((noinline))
#else
#	define PUGI_IMPL_NO_INLINE
#endif

// Branch weight controls
#if defined(__GNUC__) && !defined(__c2__)
#	define PUGI_IMPL_UNLIKELY(cond) __builtin_expect(cond, 0)
#else
#	define PUGI_IMPL_UNLIKELY(cond) (cond)
#endif

// Simple static assertion
#define PUGI_IMPL_STATIC_ASSERT(cond) { static const char condition_failed[(cond) ? 1 : -1] = {0}; (void)condition_failed[0]; }

// Digital Mars C++ bug workaround for passing char loaded from memory via stack
#ifdef __DMC__
#	define PUGI_IMPL_DMC_VOLATILE volatile
#else
#	define PUGI_IMPL_DMC_VOLATILE
#endif

// Integer sanitizer workaround; we only apply this for clang since gcc8 has no_sanitize but not unsigned-integer-overflow and produces "attribute directive ignored" warnings
#if defined(__clang__) && defined(__has_attribute)
#	if __has_attribute(no_sanitize)
#		define PUGI_IMPL_UNSIGNED_OVERFLOW __attribute__((no_sanitize("unsigned-integer-overflow")))
#	else
#		define PUGI_IMPL_UNSIGNED_OVERFLOW
#	endif
#else
#	define PUGI_IMPL_UNSIGNED_OVERFLOW
#endif

// Borland C++ bug workaround for not defining ::memcpy depending on header include order (can't always use std::memcpy because some compilers don't have it at all)
#if defined(__BORLANDC__) && !defined(__MEM_H_USING_LIST)
using std::memcpy;
using std::memmove;
using std::memset;
#endif

// Old versions of GCC do not define ::malloc and ::free depending on header include order
#if defined(__GNUC__) && (__GNUC__ < 3 || (__GNUC__ == 3 && __GNUC_MINOR__ < 4))
using std::malloc;
using std::free;
#endif

// Some MinGW/GCC versions have headers that erroneously omit LLONG_MIN/LLONG_MAX/ULLONG_MAX definitions from limits.h in some configurations
#if defined(PUGIXML_HAS_LONG_LONG) && defined(__GNUC__) && !defined(LLONG_MAX) && !defined(LLONG_MIN) && !defined(ULLONG_MAX)
#	define LLONG_MIN (-LLONG_MAX - 1LL)
#	define LLONG_MAX __LONG_LONG_MAX__
#	define ULLONG_MAX (LLONG_MAX * 2ULL + 1ULL)
#endif

// In some environments MSVC is a compiler but the CRT lacks certain MSVC-specific features
#if defined(_MSC_VER) && !defined(__S3E__) && !defined(_WIN32_WCE)
#	define PUGI_IMPL_MSVC_CRT_VERSION _MSC_VER
#elif defined(_WIN32_WCE)
#	define PUGI_IMPL_MSVC_CRT_VERSION 1310 // MSVC7.1
#endif

// Not all platforms have snprintf; we define a wrapper that uses snprintf if possible. This only works with buffers with a known size.
#if __cplusplus >= 201103
#	define PUGI_IMPL_SNPRINTF(buf, ...) snprintf(buf, sizeof(buf), __VA_ARGS__)
#elif defined(PUGI_IMPL_MSVC_CRT_VERSION) && PUGI_IMPL_MSVC_CRT_VERSION >= 1400
#	define PUGI_IMPL_SNPRINTF(buf, ...) _snprintf_s(buf, _countof(buf), _TRUNCATE, __VA_ARGS__)
#elif defined(__APPLE__) && __clang_major__ >= 14 // Xcode 14 marks sprintf as deprecated while still using C++98 by default
#	define PUGI_IMPL_SNPRINTF(buf, fmt, arg1, arg2) snprintf(buf, sizeof(buf), fmt, arg1, arg2)
#else
#	define PUGI_IMPL_SNPRINTF sprintf
#endif

// We put implementation details into an anonymous namespace in source mode, but have to keep it in non-anonymous namespace in header-only mode to prevent binary bloat.
#ifdef PUGIXML_HEADER_ONLY
#	define PUGI_IMPL_NS_BEGIN namespace pugi { namespace impl {
#	define PUGI_IMPL_NS_END } }
#	define PUGI_IMPL_FN inline
#	define PUGI_IMPL_FN_NO_INLINE inline
#else
#	if defined(_MSC_VER) && _MSC_VER < 1300 // MSVC6 seems to have an amusing bug with anonymous namespaces inside namespaces
#		define PUGI_IMPL_NS_BEGIN namespace pugi { namespace impl {
#		define PUGI_IMPL_NS_END } }
#	else
#		define PUGI_IMPL_NS_BEGIN namespace pugi { namespace impl { namespace {
#		define PUGI_IMPL_NS_END } } }
#	endif
#	define PUGI_IMPL_FN
#	define PUGI_IMPL_FN_NO_INLINE PUGI_IMPL_NO_INLINE
#endif

// uintptr_t
#if (defined(_MSC_VER) && _MSC_VER < 1600) || (defined(__BORLANDC__) && __BORLANDC__ < 0x561)
namespace pugi
{
#	ifndef _UINTPTR_T_DEFINED
	typedef size_t uintptr_t;
#	endif

	typedef unsigned __int8 uint8_t;
	typedef unsigned __int16 uint16_t;
	typedef unsigned __int32 uint32_t;
}
#else
#	include <stdint.h>
#endif

// Memory allocation
PUGI_IMPL_NS_BEGIN
	PUGI_IMPL_FN void* default_allocate(size_t size)
	{
		return malloc(size);
	}

	PUGI_IMPL_FN void default_deallocate(void* ptr)
	{
		free(ptr);
	}

	template <typename T>
	struct xml_memory_management_function_storage
	{
		static allocation_function allocate;
		static deallocation_function deallocate;
	};

	// Global allocation functions are stored in class statics so that in header mode linker deduplicates them
	// Without a template<> we'll get multiple definitions of the same static
	template <typename T> allocation_function xml_memory_management_function_storage<T>::allocate = default_allocate;
	template <typename T> deallocation_function xml_memory_management_function_storage<T>::deallocate = default_deallocate;

	typedef xml_memory_management_function_storage<int> xml_memory;
PUGI_IMPL_NS_END

// String utilities
PUGI_IMPL_NS_BEGIN
	// Get string length
	PUGI_IMPL_FN size_t strlength(const char_t* s)
	{
		assert(s);

	#ifdef PUGIXML_WCHAR_MODE
		return wcslen(s);
	#else
		return strlen(s);
	#endif
	}

	// Compare two strings
	PUGI_IMPL_FN bool strequal(const char_t* src, const char_t* dst)
	{
		assert(src && dst);

	#ifdef PUGIXML_WCHAR_MODE
		return wcscmp(src, dst) == 0;
	#else
		return strcmp(src, dst) == 0;
	#endif
	}

#ifdef PUGIXML_HAS_STRING_VIEW
	// Check if the null-terminated dst string is equal to the entire contents of srcview
	PUGI_IMPL_FN bool stringview_equal(string_view_t srcview, const char_t* dst)
	{
		// std::basic_string_view::compare(const char*) has the right behavior, but it performs an
		// extra traversal of dst to compute its length.
		assert(dst);
		const char_t* src = srcview.data();
		size_t srclen = srcview.size();

		while (srclen && *dst && *src == *dst)
		{
			--srclen; ++dst; ++src;
		}
		return srclen == 0 && *dst == 0;
	}
#endif

	// Compare lhs with [rhs_begin, rhs_end)
	PUGI_IMPL_FN bool strequalrange(const char_t* lhs, const char_t* rhs, size_t count)
	{
		for (size_t i = 0; i < count; ++i)
			if (lhs[i] != rhs[i])
				return false;

		return lhs[count] == 0;
	}

	// Get length of wide string, even if CRT lacks wide character support
	PUGI_IMPL_FN size_t strlength_wide(const wchar_t* s)
	{
		assert(s);

	#ifdef PUGIXML_WCHAR_MODE
		return wcslen(s);
	#else
		const wchar_t* end = s;
		while (*end) end++;
		return static_cast<size_t>(end - s);
	#endif
	}
PUGI_IMPL_NS_END

// auto_ptr-like object for exception recovery
PUGI_IMPL_NS_BEGIN
	template <typename T> struct auto_deleter
	{
		typedef void (*D)(T*);

		T* data;
		D deleter;

		auto_deleter(T* data_, D deleter_): data(data_), deleter(deleter_)
		{
		}

		~auto_deleter()
		{
			if (data) deleter(data);
		}

		T* release()
		{
			T* result = data;
			data = NULL;
			return result;
		}
	};
PUGI_IMPL_NS_END

#ifdef PUGIXML_COMPACT
PUGI_IMPL_NS_BEGIN
	class compact_hash_table
	{
	public:
		compact_hash_table(): _items(NULL), _capacity(0), _count(0)
		{
		}

		void clear()
		{
			if (_items)
			{
				xml_memory::deallocate(_items);
				_items = NULL;
				_capacity = 0;
				_count = 0;
			}
		}

		void* find(const void* key)
		{
			if (_capacity == 0) return NULL;

			item_t* item = get_item(key);
			assert(item);
			assert(item->key == key || (item->key == NULL && item->value == NULL));

			return item->value;
		}

		void insert(const void* key, void* value)
		{
			assert(_capacity != 0 && _count < _capacity - _capacity / 4);

			item_t* item = get_item(key);
			assert(item);

			if (item->key == NULL)
			{
				_count++;
				item->key = key;
			}

			item->value = value;
		}

		bool reserve(size_t extra = 16)
		{
			if (_count + extra >= _capacity - _capacity / 4)
				return rehash(_count + extra);

			return true;
		}

	private:
		struct item_t
		{
			const void* key;
			void* value;
		};

		item_t* _items;
		size_t _capacity;

		size_t _count;

		bool rehash(size_t count);

		item_t* get_item(const void* key)
		{
			assert(key);
			assert(_capacity > 0);

			size_t hashmod = _capacity - 1;
			size_t bucket = hash(key) & hashmod;

			for (size_t probe = 0; probe <= hashmod; ++probe)
			{
				item_t& probe_item = _items[bucket];

				if (probe_item.key == key || probe_item.key == NULL)
					return &probe_item;

				// hash collision, quadratic probing
				bucket = (bucket + probe + 1) & hashmod;
			}

			assert(false && "Hash table is full"); // unreachable
			return NULL;
		}

		static PUGI_IMPL_UNSIGNED_OVERFLOW unsigned int hash(const void* key)
		{
			unsigned int h = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(key) & 0xffffffff);

			// MurmurHash3 32-bit finalizer
			h ^= h >> 16;
			h *= 0x85ebca6bu;
			h ^= h >> 13;
			h *= 0xc2b2ae35u;
			h ^= h >> 16;

			return h;
		}
	};

	PUGI_IMPL_FN_NO_INLINE bool compact_hash_table::rehash(size_t count)
	{
		size_t capacity = 32;
		while (count >= capacity - capacity / 4)
			capacity *= 2;

		compact_hash_table rt;
		rt._capacity = capacity;
		rt._items = static_cast<item_t*>(xml_memory::allocate(sizeof(item_t) * capacity));

		if (!rt._items)
			return false;

		memset(rt._items, 0, sizeof(item_t) * capacity);

		for (size_t i = 0; i < _capacity; ++i)
			if (_items[i].key)
				rt.insert(_items[i].key, _items[i].value);

		if (_items)
			xml_memory::deallocate(_items);

		_capacity = capacity;
		_items = rt._items;

		assert(_count == rt._count);

		return true;
	}

PUGI_IMPL_NS_END
#endif

PUGI_IMPL_NS_BEGIN
#ifdef PUGIXML_COMPACT
	static const uintptr_t xml_memory_block_alignment = 4;
#else
	static const uintptr_t xml_memory_block_alignment = sizeof(void*);
#endif

	// extra metadata bits
	static const uintptr_t xml_memory_page_contents_shared_mask = 64;
	static const uintptr_t xml_memory_page_name_allocated_mask = 32;
	static const uintptr_t xml_memory_page_value_allocated_mask = 16;
	static const uintptr_t xml_memory_page_type_mask = 15;

	// combined masks for string uniqueness
	static const uintptr_t xml_memory_page_name_allocated_or_shared_mask = xml_memory_page_name_allocated_mask | xml_memory_page_contents_shared_mask;
	static const uintptr_t xml_memory_page_value_allocated_or_shared_mask = xml_memory_page_value_allocated_mask | xml_memory_page_contents_shared_mask;

#ifdef PUGIXML_COMPACT
	#define PUGI_IMPL_GETHEADER_IMPL(object, page, flags) // unused
	#define PUGI_IMPL_GETPAGE_IMPL(header) (header).get_page()
#else
	#define PUGI_IMPL_GETHEADER_IMPL(object, page, flags) (((reinterpret_cast<char*>(object) - reinterpret_cast<char*>(page)) << 8) | (flags))
	// this macro casts pointers through void* to avoid 'cast increases required alignment of target type' warnings
	#define PUGI_IMPL_GETPAGE_IMPL(header) static_cast<impl::xml_memory_page*>(const_cast<void*>(static_cast<const void*>(reinterpret_cast<const char*>(&header) - (header >> 8))))
#endif

	#define PUGI_IMPL_GETPAGE(n) PUGI_IMPL_GETPAGE_IMPL((n)->header)
	#define PUGI_IMPL_NODETYPE(n) static_cast<xml_node_type>((n)->header & impl::xml_memory_page_type_mask)

	struct xml_allocator;

	struct xml_memory_page
	{
		static xml_memory_page* construct(void* memory)
		{
			xml_memory_page* result = static_cast<xml_memory_page*>(memory);

			result->allocator = NULL;
			result->prev = NULL;
			result->next = NULL;
			result->busy_size = 0;
			result->freed_size = 0;

		#ifdef PUGIXML_COMPACT
			result->compact_string_base = NULL;
			result->compact_shared_parent = NULL;
			result->compact_page_marker = NULL;
		#endif

			return result;
		}

		xml_allocator* allocator;

		xml_memory_page* prev;
		xml_memory_page* next;

		size_t busy_size;
		size_t freed_size;

	#ifdef PUGIXML_COMPACT
		char_t* compact_string_base;
		void* compact_shared_parent;
		uint32_t* compact_page_marker;
	#endif
	};

	static const size_t xml_memory_page_size =
	#ifdef PUGIXML_MEMORY_PAGE_SIZE
		(PUGIXML_MEMORY_PAGE_SIZE)
	#else
		32768
	#endif
		- sizeof(xml_memory_page);

	struct xml_memory_string_header
	{
		uint16_t page_offset; // offset from page->data
		uint16_t full_size; // 0 if string occupies whole page
	};

	struct xml_allocator
	{
		xml_allocator(xml_memory_page* root): _root(root), _busy_size(root->busy_size)
		{
		#ifdef PUGIXML_COMPACT
			_hash = NULL;
		#endif
		}

		xml_memory_page* allocate_page(size_t data_size)
		{
			size_t size = sizeof(xml_memory_page) + data_size;

			// allocate block with some alignment, leaving memory for worst-case padding
			void* memory = xml_memory::allocate(size);
			if (!memory) return NULL;

			// prepare page structure
			xml_memory_page* page = xml_memory_page::construct(memory);
			assert(page);

			assert(this == _root->allocator);
			page->allocator = this;

			return page;
		}

		static void deallocate_page(xml_memory_page* page)
		{
			xml_memory::deallocate(page);
		}

		void* allocate_memory_oob(size_t size, xml_memory_page*& out_page);

		void* allocate_memory(size_t size, xml_memory_page*& out_page)
		{
			if (PUGI_IMPL_UNLIKELY(_busy_size + size > xml_memory_page_size))
				return allocate_memory_oob(size, out_page);

			void* buf = reinterpret_cast<char*>(_root) + sizeof(xml_memory_page) + _busy_size;

			_busy_size += size;

			out_page = _root;

			return buf;
		}

	#ifdef PUGIXML_COMPACT
		void* allocate_object(size_t size, xml_memory_page*& out_page)
		{
			void* result = allocate_memory(size + sizeof(uint32_t), out_page);
			if (!result) return NULL;

			// adjust for marker
			ptrdiff_t offset = static_cast<char*>(result) - reinterpret_cast<char*>(out_page->compact_page_marker);

			if (PUGI_IMPL_UNLIKELY(static_cast<uintptr_t>(offset) >= 256 * xml_memory_block_alignment))
			{
				// insert new marker
				uint32_t* marker = static_cast<uint32_t*>(result);

				*marker = static_cast<uint32_t>(reinterpret_cast<char*>(marker) - reinterpret_cast<char*>(out_page));
				out_page->compact_page_marker = marker;

				// since we don't reuse the page space until we reallocate it, we can just pretend that we freed the marker block
				// this will make sure deallocate_memory correctly tracks the size
				out_page->freed_size += sizeof(uint32_t);

				return marker + 1;
			}
			else
			{
				// roll back uint32_t part
				_busy_size -= sizeof(uint32_t);

				return result;
			}
		}
	#else
		void* allocate_object(size_t size, xml_memory_page*& out_page)
		{
			return allocate_memory(size, out_page);
		}
	#endif

		void deallocate_memory(void* ptr, size_t size, xml_memory_page* page)
		{
			if (page == _root) page->busy_size = _busy_size;

			assert(ptr >= reinterpret_cast<char*>(page) + sizeof(xml_memory_page) && ptr < reinterpret_cast<char*>(page) + sizeof(xml_memory_page) + page->busy_size);
			(void)!ptr;

			page->freed_size += size;
			assert(page->freed_size <= page->busy_size);

			if (page->freed_size == page->busy_size)
			{
				if (page->next == NULL)
				{
					assert(_root == page);

					// top page freed, just reset sizes
					page->busy_size = 0;
					page->freed_size = 0;

				#ifdef PUGIXML_COMPACT
					// reset compact state to maximize efficiency
					page->compact_string_base = NULL;
					page->compact_shared_parent = NULL;
					page->compact_page_marker = NULL;
				#endif

					_busy_size = 0;
				}
				else
				{
					assert(_root != page);
					assert(page->prev);

					// remove from the list
					page->prev->next = page->next;
					page->next->prev = page->prev;

					// deallocate
					deallocate_page(page);
				}
			}
		}

		char_t* allocate_string(size_t length)
		{
			static const size_t max_encoded_offset = (1 << 16) * xml_memory_block_alignment;

			PUGI_IMPL_STATIC_ASSERT(xml_memory_page_size <= max_encoded_offset);

			// allocate memory for string and header block
			size_t size = sizeof(xml_memory_string_header) + length * sizeof(char_t);

			// round size up to block alignment boundary
			size_t full_size = (size + (xml_memory_block_alignment - 1)) & ~(xml_memory_block_alignment - 1);

			xml_memory_page* page;
			xml_memory_string_header* header = static_cast<xml_memory_string_header*>(allocate_memory(full_size, page));

			if (!header) return NULL;

			// setup header
			ptrdiff_t page_offset = reinterpret_cast<char*>(header) - reinterpret_cast<char*>(page) - sizeof(xml_memory_page);

			assert(page_offset % xml_memory_block_alignment == 0);
			assert(page_offset >= 0 && static_cast<size_t>(page_offset) < max_encoded_offset);
			header->page_offset = static_cast<uint16_t>(static_cast<size_t>(page_offset) / xml_memory_block_alignment);

			// full_size == 0 for large strings that occupy the whole page
			assert(full_size % xml_memory_block_alignment == 0);
			assert(full_size < max_encoded_offset || (page->busy_size == full_size && page_offset == 0));
			header->full_size = static_cast<uint16_t>(full_size < max_encoded_offset ? full_size / xml_memory_block_alignment : 0);

			// round-trip through void* to avoid 'cast increases required alignment of target type' warning
			// header is guaranteed a pointer-sized alignment, which should be enough for char_t
			return static_cast<char_t*>(static_cast<void*>(header + 1));
		}

		void deallocate_string(char_t* string)
		{
			// this function casts pointers through void* to avoid 'cast increases required alignment of target type' warnings
			// we're guaranteed the proper (pointer-sized) alignment on the input string if it was allocated via allocate_string

			// get header
			xml_memory_string_header* header = static_cast<xml_memory_string_header*>(static_cast<void*>(string)) - 1;
			assert(header);

			// deallocate
			size_t page_offset = sizeof(xml_memory_page) + header->page_offset * xml_memory_block_alignment;
			xml_memory_page* page = reinterpret_cast<xml_memory_page*>(static_cast<void*>(reinterpret_cast<char*>(header) - page_offset));

			// if full_size == 0 then this string occupies the whole page
			size_t full_size = header->full_size == 0 ? page->busy_size : header->full_size * xml_memory_block_alignment;

			deallocate_memory(header, full_size, page);
		}

		bool reserve()
		{
		#ifdef PUGIXML_COMPACT
			return _hash->reserve();
		#else
			return true;
		#endif
		}

		xml_memory_page* _root;
		size_t _busy_size;

	#ifdef PUGIXML_COMPACT
		compact_hash_table* _hash;
	#endif
	};

	PUGI_IMPL_FN_NO_INLINE void* xml_allocator::allocate_memory_oob(size_t size, xml_memory_page*& out_page)
	{
		const size_t large_allocation_threshold = xml_memory_page_size / 4;

		xml_memory_page* page = allocate_page(size <= large_allocation_threshold ? xml_memory_page_size : size);
		out_page = page;

		if (!page) return NULL;

		if (size <= large_allocation_threshold)
		{
			_root->busy_size = _busy_size;

			// insert page at the end of linked list
			page->prev = _root;
			_root->next = page;
			_root = page;

			_busy_size = size;
		}
		else
		{
			// insert page before the end of linked list, so that it is deleted as soon as possible
			// the last page is not deleted even if it's empty (see deallocate_memory)
			assert(_root->prev);

			page->prev = _root->prev;
			page->next = _root;

			_root->prev->next = page;
			_root->prev = page;

			page->busy_size = size;
		}

		return reinterpret_cast<char*>(page) + sizeof(xml_memory_page);
	}
PUGI_IMPL_NS_END

#ifdef PUGIXML_COMPACT
PUGI_IMPL_NS_BEGIN
	static const uintptr_t compact_alignment_log2 = 2;
	static const uintptr_t compact_alignment = 1 << compact_alignment_log2;

	class compact_header
	{
	public:
		compact_header(xml_memory_page* page, unsigned int flags)
		{
			PUGI_IMPL_STATIC_ASSERT(xml_memory_block_alignment == compact_alignment);

			ptrdiff_t offset = (reinterpret_cast<char*>(this) - reinterpret_cast<char*>(page->compact_page_marker));
			assert(offset % compact_alignment == 0 && static_cast<uintptr_t>(offset) < 256 * compact_alignment);

			_page = static_cast<unsigned char>(offset >> compact_alignment_log2);
			_flags = static_cast<unsigned char>(flags);
		}

		void operator&=(uintptr_t mod)
		{
			_flags &= static_cast<unsigned char>(mod);
		}

		void operator|=(uintptr_t mod)
		{
			_flags |= static_cast<unsigned char>(mod);
		}

		uintptr_t operator&(uintptr_t mod) const
		{
			return _flags & mod;
		}

		xml_memory_page* get_page() const
		{
			// round-trip through void* to silence 'cast increases required alignment of target type' warnings
			const char* page_marker = reinterpret_cast<const char*>(this) - (_page << compact_alignment_log2);
			const char* page = page_marker - *reinterpret_cast<const uint32_t*>(static_cast<const void*>(page_marker));

			return const_cast<xml_memory_page*>(reinterpret_cast<const xml_memory_page*>(static_cast<const void*>(page)));
		}

	private:
		unsigned char _page;
		unsigned char _flags;
	};

	PUGI_IMPL_FN xml_memory_page* compact_get_page(const void* object, int header_offset)
	{
		const compact_header* header = reinterpret_cast<const compact_header*>(static_cast<const char*>(object) - header_offset);

		return header->get_page();
	}

	template <int header_offset, typename T> PUGI_IMPL_FN_NO_INLINE T* compact_get_value(const void* object)
	{
		return static_cast<T*>(compact_get_page(object, header_offset)->allocator->_hash->find(object));
	}

	template <int header_offset, typename T> PUGI_IMPL_FN_NO_INLINE void compact_set_value(const void* object, T* value)
	{
		compact_get_page(object, header_offset)->allocator->_hash->insert(object, value);
	}

	template <typename T, int header_offset, int start = -126> class compact_pointer
	{
	public:
		compact_pointer(): _data(0)
		{
		}

		void operator=(const compact_pointer& rhs)
		{
			*this = rhs + 0;
		}

		void operator=(T* value)
		{
			if (value)
			{
				// value is guaranteed to be compact-aligned; 'this' is not
				// our decoding is based on 'this' aligned to compact alignment downwards (see operator T*)
				// so for negative offsets (e.g. -3) we need to adjust the diff by compact_alignment - 1 to
				// compensate for arithmetic shift rounding for negative values
				ptrdiff_t diff = reinterpret_cast<char*>(value) - reinterpret_cast<char*>(this);
				ptrdiff_t offset = ((diff + int(compact_alignment - 1)) >> compact_alignment_log2) - start;

				if (static_cast<uintptr_t>(offset) <= 253)
					_data = static_cast<unsigned char>(offset + 1);
				else
				{
					compact_set_value<header_offset>(this, value);

					_data = 255;
				}
			}
			else
				_data = 0;
		}

		operator T*() const
		{
			if (_data)
			{
				if (_data < 255)
				{
					uintptr_t base = reinterpret_cast<uintptr_t>(this) & ~(compact_alignment - 1);

					return reinterpret_cast<T*>(base + (_data - 1 + start) * compact_alignment);
				}
				else
					return compact_get_value<header_offset, T>(this);
			}
			else
				return NULL;
		}

		T* operator->() const
		{
			return *this;
		}

	private:
		unsigned char _data;
	};

	template <typename T, int header_offset> class compact_pointer_parent
	{
	public:
		compact_pointer_parent(): _data(0)
		{
		}

		void operator=(const compact_pointer_parent& rhs)
		{
			*this = rhs + 0;
		}

		void operator=(T* value)
		{
			if (value)
			{
				// value is guaranteed to be compact-aligned; 'this' is not
				// our decoding is based on 'this' aligned to compact alignment downwards (see operator T*)
				// so for negative offsets (e.g. -3) we need to adjust the diff by compact_alignment - 1 to
				// compensate for arithmetic shift behavior for negative values
				ptrdiff_t diff = reinterpret_cast<char*>(value) - reinterpret_cast<char*>(this);
				ptrdiff_t offset = ((diff + int(compact_alignment - 1)) >> compact_alignment_log2) + 65533;

				if (static_cast<uintptr_t>(offset) <= 65533)
				{
					_data = static_cast<unsigned short>(offset + 1);
				}
				else
				{
					xml_memory_page* page = compact_get_page(this, header_offset);

					if (PUGI_IMPL_UNLIKELY(page->compact_shared_parent == NULL))
						page->compact_shared_parent = value;

					if (page->compact_shared_parent == value)
					{
						_data = 65534;
					}
					else
					{
						compact_set_value<header_offset>(this, value);

						_data = 65535;
					}
				}
			}
			else
			{
				_data = 0;
			}
		}

		operator T*() const
		{
			if (_data)
			{
				if (_data < 65534)
				{
					uintptr_t base = reinterpret_cast<uintptr_t>(this) & ~(compact_alignment - 1);

					return reinterpret_cast<T*>(base + (_data - 1 - 65533) * compact_alignment);
				}
				else if (_data == 65534)
					return static_cast<T*>(compact_get_page(this, header_offset)->compact_shared_parent);
				else
					return compact_get_value<header_offset, T>(this);
			}
			else
				return NULL;
		}

		T* operator->() const
		{
			return *this;
		}

	private:
		uint16_t _data;
	};

	template <int header_offset, int base_offset> class compact_string
	{
	public:
		compact_string(): _data(0)
		{
		}

		void operator=(const compact_string& rhs)
		{
			*this = rhs + 0;
		}

		void operator=(char_t* value)
		{
			if (value)
			{
				xml_memory_page* page = compact_get_page(this, header_offset);

				if (PUGI_IMPL_UNLIKELY(page->compact_string_base == NULL))
					page->compact_string_base = value;

				ptrdiff_t offset = value - page->compact_string_base;

				if (static_cast<uintptr_t>(offset) < (65535 << 7))
				{
					// round-trip through void* to silence 'cast increases required alignment of target type' warnings
					uint16_t* base = reinterpret_cast<uint16_t*>(static_cast<void*>(reinterpret_cast<char*>(this) - base_offset));

					if (*base == 0)
					{
						*base = static_cast<uint16_t>((offset >> 7) + 1);
						_data = static_cast<unsigned char>((offset & 127) + 1);
					}
					else
					{
						ptrdiff_t remainder = offset - ((*base - 1) << 7);

						if (static_cast<uintptr_t>(remainder) <= 253)
						{
							_data = static_cast<unsigned char>(remainder + 1);
						}
						else
						{
							compact_set_value<header_offset>(this, value);

							_data = 255;
						}
					}
				}
				else
				{
					compact_set_value<header_offset>(this, value);

					_data = 255;
				}
			}
			else
			{
				_data = 0;
			}
		}

		operator char_t*() const
		{
			if (_data)
			{
				if (_data < 255)
				{
					xml_memory_page* page = compact_get_page(this, header_offset);

					// round-trip through void* to silence 'cast increases required alignment of target type' warnings
					const uint16_t* base = reinterpret_cast<const uint16_t*>(static_cast<const void*>(reinterpret_cast<const char*>(this) - base_offset));
					assert(*base);

					ptrdiff_t offset = ((*base - 1) << 7) + (_data - 1);

					return page->compact_string_base + offset;
				}
				else
				{
					return compact_get_value<header_offset, char_t>(this);
				}
			}
			else
				return NULL;
		}

	private:
		unsigned char _data;
	};
PUGI_IMPL_NS_END
#endif

#ifdef PUGIXML_COMPACT
namespace pugi
{
	struct xml_attribute_struct
	{
		xml_attribute_struct(impl::xml_memory_page* page): header(page, 0), namevalue_base(0)
		{
			PUGI_IMPL_STATIC_ASSERT(sizeof(xml_attribute_struct) == 8);
		}

		impl::compact_header header;

		uint16_t namevalue_base;

		impl::compact_string<4, 2> name;
		impl::compact_string<5, 3> value;

		impl::compact_pointer<xml_attribute_struct, 6> prev_attribute_c;
		impl::compact_pointer<xml_attribute_struct, 7, 0> next_attribute;
	};

	struct xml_node_struct
	{
		xml_node_struct(impl::xml_memory_page* page, xml_node_type type): header(page, type), namevalue_base(0)
		{
			PUGI_IMPL_STATIC_ASSERT(sizeof(xml_node_struct) == 12);
		}

		impl::compact_header header;

		uint16_t namevalue_base;

		impl::compact_string<4, 2> name;
		impl::compact_string<5, 3> value;

		impl::compact_pointer_parent<xml_node_struct, 6> parent;

		impl::compact_pointer<xml_node_struct, 8, 0> first_child;

		impl::compact_pointer<xml_node_struct,  9>    prev_sibling_c;
		impl::compact_pointer<xml_node_struct, 10, 0> next_sibling;

		impl::compact_pointer<xml_attribute_struct, 11, 0> first_attribute;
	};
}
#else
namespace pugi
{
	struct xml_attribute_struct
	{
		xml_attribute_struct(impl::xml_memory_page* page): name(NULL), value(NULL), prev_attribute_c(NULL), next_attribute(NULL)
		{
			header = PUGI_IMPL_GETHEADER_IMPL(this, page, 0);
		}

		uintptr_t header;

		char_t*	name;
		char_t*	value;

		xml_attribute_struct* prev_attribute_c;
		xml_attribute_struct* next_attribute;
	};

	struct xml_node_struct
	{
		xml_node_struct(impl::xml_memory_page* page, xml_node_type type): name(NULL), value(NULL), parent(NULL), first_child(NULL), prev_sibling_c(NULL), next_sibling(NULL), first_attribute(NULL)
		{
			header = PUGI_IMPL_GETHEADER_IMPL(this, page, type);
		}

		uintptr_t header;

		char_t* name;
		char_t* value;

		xml_node_struct* parent;

		xml_node_struct* first_child;

		xml_node_struct* prev_sibling_c;
		xml_node_struct* next_sibling;

		xml_attribute_struct* first_attribute;
	};
}
#endif

PUGI_IMPL_NS_BEGIN
	struct xml_extra_buffer
	{
		char_t* buffer;
		xml_extra_buffer* next;
	};

	struct xml_document_struct: public xml_node_struct, public xml_allocator
	{
		xml_document_struct(xml_memory_page* page): xml_node_struct(page, node_document), xml_allocator(page), buffer(NULL), extra_buffers(NULL)
		{
		}

		const char_t* buffer;

		xml_extra_buffer* extra_buffers;

	#ifdef PUGIXML_COMPACT
		compact_hash_table hash;
	#endif
	};

	template <typename Object> inline xml_allocator& get_allocator(const Object* object)
	{
		assert(object);

		return *PUGI_IMPL_GETPAGE(object)->allocator;
	}

	template <typename Object> inline xml_document_struct& get_document(const Object* object)
	{
		assert(object);

		return *static_cast<xml_document_struct*>(PUGI_IMPL_GETPAGE(object)->allocator);
	}
PUGI_IMPL_NS_END

// Low-level DOM operations
PUGI_IMPL_NS_BEGIN
	inline xml_attribute_struct* allocate_attribute(xml_allocator& alloc)
	{
		xml_memory_page* page;
		void* memory = alloc.allocate_object(sizeof(xml_attribute_struct), page);
		if (!memory) return NULL;

		return new (memory) xml_attribute_struct(page);
	}

	inline xml_node_struct* allocate_node(xml_allocator& alloc, xml_node_type type)
	{
		xml_memory_page* page;
		void* memory = alloc.allocate_object(sizeof(xml_node_struct), page);
		if (!memory) return NULL;

		return new (memory) xml_node_struct(page, type);
	}

	inline void destroy_attribute(xml_attribute_struct* a, xml_allocator& alloc)
	{
		if (a->header & impl::xml_memory_page_name_allocated_mask)
			alloc.deallocate_string(a->name);

		if (a->header & impl::xml_memory_page_value_allocated_mask)
			alloc.deallocate_string(a->value);

		alloc.deallocate_memory(a, sizeof(xml_attribute_struct), PUGI_IMPL_GETPAGE(a));
	}

	inline void destroy_node(xml_node_struct* n, xml_allocator& alloc)
	{
		if (n->header & impl::xml_memory_page_name_allocated_mask)
			alloc.deallocate_string(n->name);

		if (n->header & impl::xml_memory_page_value_allocated_mask)
			alloc.deallocate_string(n->value);

		for (xml_attribute_struct* attr = n->first_attribute; attr; )
		{
			xml_attribute_struct* next = attr->next_attribute;

			destroy_attribute(attr, alloc);

			attr = next;
		}

		for (xml_node_struct* child = n->first_child; child; )
		{
			xml_node_struct* next = child->next_sibling;

			destroy_node(child, alloc);

			child = next;
		}

		alloc.deallocate_memory(n, sizeof(xml_node_struct), PUGI_IMPL_GETPAGE(n));
	}

	inline void append_node(xml_node_struct* child, xml_node_struct* node)
	{
		child->parent = node;

		xml_node_struct* head = node->first_child;

		if (head)
		{
			xml_node_struct* tail = head->prev_sibling_c;

			tail->next_sibling = child;
			child->prev_sibling_c = tail;
			head->prev_sibling_c = child;
		}
		else
		{
			node->first_child = child;
			child->prev_sibling_c = child;
		}
	}

	inline void prepend_node(xml_node_struct* child, xml_node_struct* node)
	{
		child->parent = node;

		xml_node_struct* head = node->first_child;

		if (head)
		{
			child->prev_sibling_c = head->prev_sibling_c;
			head->prev_sibling_c = child;
		}
		else
			child->prev_sibling_c = child;

		child->next_sibling = head;
		node->first_child = child;
	}

	inline void insert_node_after(xml_node_struct* child, xml_node_struct* node)
	{
		xml_node_struct* parent = node->parent;

		child->parent = parent;

		xml_node_struct* next = node->next_sibling;

		if (next)
			next->prev_sibling_c = child;
		else
			parent->first_child->prev_sibling_c = child;

		child->next_sibling = next;
		child->prev_sibling_c = node;

		node->next_sibling = child;
	}

	inline void insert_node_before(xml_node_struct* child, xml_node_struct* node)
	{
		xml_node_struct* parent = node->parent;

		child->parent = parent;

		xml_node_struct* prev = node->prev_sibling_c;

		if (prev->next_sibling)
			prev->next_sibling = child;
		else
			parent->first_child = child;

		child->prev_sibling_c = prev;
		child->next_sibling = node;

		node->prev_sibling_c = child;
	}

	inline void remove_node(xml_node_struct* node)
	{
		xml_node_struct* parent = node->parent;

		xml_node_struct* next = node->next_sibling;
		xml_node_struct* prev = node->prev_sibling_c;

		if (next)
			next->prev_sibling_c = prev;
		else
			parent->first_child->prev_sibling_c = prev;

		if (prev->next_sibling)
			prev->next_sibling = next;
		else
			parent->first_child = next;

		node->parent = NULL;
		node->prev_sibling_c = NULL;
		node->next_sibling = NULL;
	}

	inline void append_attribute(xml_attribute_struct* attr, xml_node_struct* node)
	{
		xml_attribute_struct* head = node->first_attribute;

		if (head)
		{
			xml_attribute_struct* tail = head->prev_attribute_c;

			tail->next_attribute = attr;
			attr->prev_attribute_c = tail;
			head->prev_attribute_c = attr;
		}
		else
		{
			node->first_attribute = attr;
			attr->prev_attribute_c = attr;
		}
	}

	inline void prepend_attribute(xml_attribute_struct* attr, xml_node_struct* node)
	{
		xml_attribute_struct* head = node->first_attribute;

		if (head)
		{
			attr->prev_attribute_c = head->prev_attribute_c;
			head->prev_attribute_c = attr;
		}
		else
			attr->prev_attribute_c = attr;

		attr->next_attribute = head;
		node->first_attribute = attr;
	}

	inline void insert_attribute_after(xml_attribute_struct* attr, xml_attribute_struct* place, xml_node_struct* node)
	{
		xml_attribute_struct* next = place->next_attribute;

		if (next)
			next->prev_attribute_c = attr;
		else
			node->first_attribute->prev_attribute_c = attr;

		attr->next_attribute = next;
		attr->prev_attribute_c = place;
		place->next_attribute = attr;
	}

	inline void insert_attribute_before(xml_attribute_struct* attr, xml_attribute_struct* place, xml_node_struct* node)
	{
		xml_attribute_struct* prev = place->prev_attribute_c;

		if (prev->next_attribute)
			prev->next_attribute = attr;
		else
			node->first_attribute = attr;

		attr->prev_attribute_c = prev;
		attr->next_attribute = place;
		place->prev_attribute_c = attr;
	}

	inline void remove_attribute(xml_attribute_struct* attr, xml_node_struct* node)
	{
		xml_attribute_struct* next = attr->next_attribute;
		xml_attribute_struct* prev = attr->prev_attribute_c;

		if (next)
			next->prev_attribute_c = prev;
		else
			node->first_attribute->prev_attribute_c = prev;

		if (prev->next_attribute)
			prev->next_attribute = next;
		else
			node->first_attribute = next;

		attr->prev_attribute_c = NULL;
		attr->next_attribute = NULL;
	}

	PUGI_IMPL_FN_NO_INLINE xml_node_struct* append_new_node(xml_node_struct* node, xml_allocator& alloc, xml_node_type type = node_element)
	{
		if (!alloc.reserve()) return NULL;

		xml_node_struct* child = allocate_node(alloc, type);
		if (!child) return NULL;

		append_node(child, node);

		return child;
	}

	PUGI_IMPL_FN_NO_INLINE xml_attribute_struct* append_new_attribute(xml_node_struct* node, xml_allocator& alloc)
	{
		if (!alloc.reserve()) return NULL;

		xml_attribute_struct* attr = allocate_attribute(alloc);
		if (!attr) return NULL;

		append_attribute(attr, node);

		return attr;
	}
PUGI_IMPL_NS_END

// Helper classes for code generation
PUGI_IMPL_NS_BEGIN
	struct opt_false
	{
		enum { value = 0 };
	};

	struct opt_true
	{
		enum { value = 1 };
	};
PUGI_IMPL_NS_END

// Unicode utilities
PUGI_IMPL_NS_BEGIN
	inline uint16_t endian_swap(uint16_t value)
	{
		return static_cast<uint16_t>(((value & 0xff) << 8) | (value >> 8));
	}

	inline uint32_t endian_swap(uint32_t value)
	{
		return ((value & 0xff) << 24) | ((value & 0xff00) << 8) | ((value & 0xff0000) >> 8) | (value >> 24);
	}

	struct utf8_counter
	{
		typedef size_t value_type;

		static value_type low(value_type result, uint32_t ch)
		{
			// U+0000..U+007F
			if (ch < 0x80) return result + 1;
			// U+0080..U+07FF
			else if (ch < 0x800) return result + 2;
			// U+0800..U+FFFF
			else return result + 3;
		}

		static value_type high(value_type result, uint32_t)
		{
			// U+10000..U+10FFFF
			return result + 4;
		}
	};

	struct utf8_writer
	{
		typedef uint8_t* value_type;

		static value_type low(value_type result, uint32_t ch)
		{
			// U+0000..U+007F
			if (ch < 0x80)
			{
				*result = static_cast<uint8_t>(ch);
				return result + 1;
			}
			// U+0080..U+07FF
			else if (ch < 0x800)
			{
				result[0] = static_cast<uint8_t>(0xC0 | (ch >> 6));
				result[1] = static_cast<uint8_t>(0x80 | (ch & 0x3F));
				return result + 2;
			}
			// U+0800..U+FFFF
			else
			{
				result[0] = static_cast<uint8_t>(0xE0 | (ch >> 12));
				result[1] = static_cast<uint8_t>(0x80 | ((ch >> 6) & 0x3F));
				result[2] = static_cast<uint8_t>(0x80 | (ch & 0x3F));
				return result + 3;
			}
		}

		static value_type high(value_type result, uint32_t ch)
		{
			// U+10000..U+10FFFF
			result[0] = static_cast<uint8_t>(0xF0 | (ch >> 18));
			result[1] = static_cast<uint8_t>(0x80 | ((ch >> 12) & 0x3F));
			result[2] = static_cast<uint8_t>(0x80 | ((ch >> 6) & 0x3F));
			result[3] = static_cast<uint8_t>(0x80 | (ch & 0x3F));
			return result + 4;
		}

		static value_type any(value_type result, uint32_t ch)
		{
			return (ch < 0x10000) ? low(result, ch) : high(result, ch);
		}
	};

	struct utf16_counter
	{
		typedef size_t value_type;

		static value_type low(value_type result, uint32_t)
		{
			return result + 1;
		}

		static value_type high(value_type result, uint32_t)
		{
			return result + 2;
		}
	};

	struct utf16_writer
	{
		typedef uint16_t* value_type;

		static value_type low(value_type result, uint32_t ch)
		{
			*result = static_cast<uint16_t>(ch);

			return result + 1;
		}

		static value_type high(value_type result, uint32_t ch)
		{
			uint32_t msh = (ch - 0x10000U) >> 10;
			uint32_t lsh = (ch - 0x10000U) & 0x3ff;

			result[0] = static_cast<uint16_t>(0xD800 + msh);
			result[1] = static_cast<uint16_t>(0xDC00 + lsh);

			return result + 2;
		}

		static value_type any(value_type result, uint32_t ch)
		{
			return (ch < 0x10000) ? low(result, ch) : high(result, ch);
		}
	};

	struct utf32_counter
	{
		typedef size_t value_type;

		static value_type low(value_type result, uint32_t)
		{
			return result + 1;
		}

		static value_type high(value_type result, uint32_t)
		{
			return result + 1;
		}
	};

	struct utf32_writer
	{
		typedef uint32_t* value_type;

		static value_type low(value_type result, uint32_t ch)
		{
			*result = ch;

			return result + 1;
		}

		static value_type high(value_type result, uint32_t ch)
		{
			*result = ch;

			return result + 1;
		}

		static value_type any(value_type result, uint32_t ch)
		{
			*result = ch;

			return result + 1;
		}
	};

	struct latin1_writer
	{
		typedef uint8_t* value_type;

		static value_type low(value_type result, uint32_t ch)
		{
			*result = static_cast<uint8_t>(ch > 255 ? '?' : ch);

			return result + 1;
		}

		static value_type high(value_type result, uint32_t ch)
		{
			(void)ch;

			*result = '?';

			return result + 1;
		}
	};

	struct utf8_decoder
	{
		typedef uint8_t type;

		template <typename Traits> static inline typename Traits::value_type process(const uint8_t* data, size_t size, typename Traits::value_type result, Traits)
		{
			const uint8_t utf8_byte_mask = 0x3f;

			while (size)
			{
				uint8_t lead = *data;

				// 0xxxxxxx -> U+0000..U+007F
				if (lead < 0x80)
				{
					result = Traits::low(result, lead);
					data += 1;
					size -= 1;

					// process aligned single-byte (ascii) blocks
					if ((reinterpret_cast<uintptr_t>(data) & 3) == 0)
					{
						// round-trip through void* to silence 'cast increases required alignment of target type' warnings
						while (size >= 4 && (*static_cast<const uint32_t*>(static_cast<const void*>(data)) & 0x80808080) == 0)
						{
							result = Traits::low(result, data[0]);
							result = Traits::low(result, data[1]);
							result = Traits::low(result, data[2]);
							result = Traits::low(result, data[3]);
							data += 4;
							size -= 4;
						}
					}
				}
				// 110xxxxx -> U+0080..U+07FF
				else if (static_cast<unsigned int>(lead - 0xC0) < 0x20 && size >= 2 && (data[1] & 0xc0) == 0x80)
				{
					result = Traits::low(result, ((lead & ~0xC0) << 6) | (data[1] & utf8_byte_mask));
					data += 2;
					size -= 2;
				}
				// 1110xxxx -> U+0800-U+FFFF
				else if (static_cast<unsigned int>(lead - 0xE0) < 0x10 && size >= 3 && (data[1] & 0xc0) == 0x80 && (data[2] & 0xc0) == 0x80)
				{
					result = Traits::low(result, ((lead & ~0xE0) << 12) | ((data[1] & utf8_byte_mask) << 6) | (data[2] & utf8_byte_mask));
					data += 3;
					size -= 3;
				}
				// 11110xxx -> U+10000..U+10FFFF
				else if (static_cast<unsigned int>(lead - 0xF0) < 0x08 && size >= 4 && (data[1] & 0xc0) == 0x80 && (data[2] & 0xc0) == 0x80 && (data[3] & 0xc0) == 0x80)
				{
					result = Traits::high(result, ((lead & ~0xF0) << 18) | ((data[1] & utf8_byte_mask) << 12) | ((data[2] & utf8_byte_mask) << 6) | (data[3] & utf8_byte_mask));
					data += 4;
					size -= 4;
				}
				// 10xxxxxx or 11111xxx -> invalid
				else
				{
					data += 1;
					size -= 1;
				}
			}

			return result;
		}
	};

	template <typename opt_swap> struct utf16_decoder
	{
		typedef uint16_t type;

		template <typename Traits> static inline typename Traits::value_type process(const uint16_t* data, size_t size, typename Traits::value_type result, Traits)
		{
			while (size)
			{
				uint16_t lead = opt_swap::value ? endian_swap(*data) : *data;

				// U+0000..U+D7FF
				if (lead < 0xD800)
				{
					result = Traits::low(result, lead);
					data += 1;
					size -= 1;
				}
				// U+E000..U+FFFF
				else if (static_cast<unsigned int>(lead - 0xE000) < 0x2000)
				{
					result = Traits::low(result, lead);
					data += 1;
					size -= 1;
				}
				// surrogate pair lead
				else if (static_cast<unsigned int>(lead - 0xD800) < 0x400 && size >= 2)
				{
					uint16_t next = opt_swap::value ? endian_swap(data[1]) : data[1];

					if (static_cast<unsigned int>(next - 0xDC00) < 0x400)
					{
						result = Traits::high(result, 0x10000 + ((lead & 0x3ff) << 10) + (next & 0x3ff));
						data += 2;
						size -= 2;
					}
					else
					{
						data += 1;
						size -= 1;
					}
				}
				else
				{
					data += 1;
					size -= 1;
				}
			}

			return result;
		}
	};

	template <typename opt_swap> struct utf32_decoder
	{
		typedef uint32_t type;

		template <typename Traits> static inline typename Traits::value_type process(const uint32_t* data, size_t size, typename Traits::value_type result, Traits)
		{
			while (size)
			{
				uint32_t lead = opt_swap::value ? endian_swap(*data) : *data;

				// U+0000..U+FFFF
				if (lead < 0x10000)
				{
					result = Traits::low(result, lead);
					data += 1;
					size -= 1;
				}
				// U+10000..U+10FFFF
				else
				{
					result = Traits::high(result, lead);
					data += 1;
					size -= 1;
				}
			}

			return result;
		}
	};

	struct latin1_decoder
	{
		typedef uint8_t type;

		template <typename Traits> static inline typename Traits::value_type process(const uint8_t* data, size_t size, typename Traits::value_type result, Traits)
		{
			while (size)
			{
				result = Traits::low(result, *data);
				data += 1;
				size -= 1;
			}

			return result;
		}
	};

	template <size_t size> struct wchar_selector;

	template <> struct wchar_selector<2>
	{
		typedef uint16_t type;
		typedef utf16_counter counter;
		typedef utf16_writer writer;
		typedef utf16_decoder<opt_false> decoder;
	};

	template <> struct wchar_selector<4>
	{
		typedef uint32_t type;
		typedef utf32_counter counter;
		typedef utf32_writer writer;
		typedef utf32_decoder<opt_false> decoder;
	};

	typedef wchar_selector<sizeof(wchar_t)>::counter wchar_counter;
	typedef wchar_selector<sizeof(wchar_t)>::writer wchar_writer;

	struct wchar_decoder
	{
		typedef wchar_t type;

		template <typename Traits> static inline typename Traits::value_type process(const wchar_t* data, size_t size, typename Traits::value_type result, Traits traits)
		{
			typedef wchar_selector<sizeof(wchar_t)>::decoder decoder;

			return decoder::process(reinterpret_cast<const typename decoder::type*>(data), size, result, traits);
		}
	};

#ifdef PUGIXML_WCHAR_MODE
	PUGI_IMPL_FN void convert_wchar_endian_swap(wchar_t* result, const wchar_t* data, size_t length)
	{
		for (size_t i = 0; i < length; ++i)
			result[i] = static_cast<wchar_t>(endian_swap(static_cast<wchar_selector<sizeof(wchar_t)>::type>(data[i])));
	}
#endif
PUGI_IMPL_NS_END

PUGI_IMPL_NS_BEGIN
	enum chartype_t
	{
		ct_parse_pcdata = 1,	// \0, &, \r, <
		ct_parse_attr = 2,		// \0, &, \r, ', "
		ct_parse_attr_ws = 4,	// \0, &, \r, ', ", \n, tab
		ct_space = 8,			// \r, \n, space, tab
		ct_parse_cdata = 16,	// \0, ], >, \r
		ct_parse_comment = 32,	// \0, -, >, \r
		ct_symbol = 64,			// Any symbol > 127, a-z, A-Z, 0-9, _, :, -, .
		ct_start_symbol = 128	// Any symbol > 127, a-z, A-Z, _, :
	};

	static const unsigned char chartype_table[256] =
	{
		55,  0,   0,   0,   0,   0,   0,   0,      0,   12,  12,  0,   0,   63,  0,   0,   // 0-15
		0,   0,   0,   0,   0,   0,   0,   0,      0,   0,   0,   0,   0,   0,   0,   0,   // 16-31
		8,   0,   6,   0,   0,   0,   7,   6,      0,   0,   0,   0,   0,   96,  64,  0,   // 32-47
		64,  64,  64,  64,  64,  64,  64,  64,     64,  64,  192, 0,   1,   0,   48,  0,   // 48-63
		0,   192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192, // 64-79
		192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 0,   0,   16,  0,   192, // 80-95
		0,   192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192, // 96-111
		192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 0, 0, 0, 0, 0,           // 112-127

		192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192, // 128+
		192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
		192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
		192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
		192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
		192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
		192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
		192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192
	};

	enum chartypex_t
	{
		ctx_special_pcdata = 1,   // Any symbol >= 0 and < 32 (except \t, \r, \n), &, <, >
		ctx_special_attr = 2,     // Any symbol >= 0 and < 32, &, <, ", '
		ctx_start_symbol = 4,	  // Any symbol > 127, a-z, A-Z, _
		ctx_digit = 8,			  // 0-9
		ctx_symbol = 16			  // Any symbol > 127, a-z, A-Z, 0-9, _, -, .
	};

	static const unsigned char chartypex_table[256] =
	{
		3,  3,  3,  3,  3,  3,  3,  3,     3,  2,  2,  3,  3,  2,  3,  3,     // 0-15
		3,  3,  3,  3,  3,  3,  3,  3,     3,  3,  3,  3,  3,  3,  3,  3,     // 16-31
		0,  0,  2,  0,  0,  0,  3,  2,     0,  0,  0,  0,  0, 16, 16,  0,     // 32-47
		24, 24, 24, 24, 24, 24, 24, 24,    24, 24, 0,  0,  3,  0,  1,  0,     // 48-63

		0,  20, 20, 20, 20, 20, 20, 20,    20, 20, 20, 20, 20, 20, 20, 20,    // 64-79
		20, 20, 20, 20, 20, 20, 20, 20,    20, 20, 20, 0,  0,  0,  0,  20,    // 80-95
		0,  20, 20, 20, 20, 20, 20, 20,    20, 20, 20, 20, 20, 20, 20, 20,    // 96-111
		20, 20, 20, 20, 20, 20, 20, 20,    20, 20, 20, 0,  0,  0,  0,  0,     // 112-127

		20, 20, 20, 20, 20, 20, 20, 20,    20, 20, 20, 20, 20, 20, 20, 20,    // 128+
		20, 20, 20, 20, 20, 20, 20, 20,    20, 20, 20, 20, 20, 20, 20, 20,
		20, 20, 20, 20, 20, 20, 20, 20,    20, 20, 20, 20, 20, 20, 20, 20,
		20, 20, 20, 20, 20, 20, 20, 20,    20, 20, 20, 20, 20, 20, 20, 20,
		20, 20, 20, 20, 20, 20, 20, 20,    20, 20, 20, 20, 20, 20, 20, 20,
		20, 20, 20, 20, 20, 20, 20, 20,    20, 20, 20, 20, 20, 20, 20, 20,
		20, 20, 20, 20, 20, 20, 20, 20,    20, 20, 20, 20, 20, 20, 20, 20,
		20, 20, 20, 20, 20, 20, 20, 20,    20, 20, 20, 20, 20, 20, 20, 20
	};

#ifdef PUGIXML_WCHAR_MODE
	#define PUGI_IMPL_IS_CHARTYPE_IMPL(c, ct, table) ((static_cast<unsigned int>(c) < 128 ? table[static_cast<unsigned int>(c)] : table[128]) & (ct))
#else
	#define PUGI_IMPL_IS_CHARTYPE_IMPL(c, ct, table) (table[static_cast<unsigned char>(c)] & (ct))
#endif

	#define PUGI_IMPL_IS_CHARTYPE(c, ct) PUGI_IMPL_IS_CHARTYPE_IMPL(c, ct, chartype_table)
	#define PUGI_IMPL_IS_CHARTYPEX(c, ct) PUGI_IMPL_IS_CHARTYPE_IMPL(c, ct, chartypex_table)

	PUGI_IMPL_FN bool is_little_endian()
	{
		unsigned int ui = 1;

		return *reinterpret_cast<unsigned char*>(&ui) == 1;
	}

	PUGI_IMPL_FN xml_encoding get_wchar_encoding()
	{
		PUGI_IMPL_STATIC_ASSERT(sizeof(wchar_t) == 2 || sizeof(wchar_t) == 4);

		if (sizeof(wchar_t) == 2)
			return is_little_endian() ? encoding_utf16_le : encoding_utf16_be;
		else
			return is_little_endian() ? encoding_utf32_le : encoding_utf32_be;
	}

	PUGI_IMPL_FN bool parse_declaration_encoding(const uint8_t* data, size_t size, const uint8_t*& out_encoding, size_t& out_length)
	{
	#define PUGI_IMPL_SCANCHAR(ch) { if (offset >= size || data[offset] != ch) return false; offset++; }
	#define PUGI_IMPL_SCANCHARTYPE(ct) { while (offset < size && PUGI_IMPL_IS_CHARTYPE(data[offset], ct)) offset++; }

		// check if we have a non-empty XML declaration
		if (size < 6 || !((data[0] == '<') & (data[1] == '?') & (data[2] == 'x') & (data[3] == 'm') & (data[4] == 'l') && PUGI_IMPL_IS_CHARTYPE(data[5], ct_space)))
			return false;

		// scan XML declaration until the encoding field
		for (size_t i = 6; i + 1 < size; ++i)
		{
			// declaration can not contain ? in quoted values
			if (data[i] == '?')
				return false;

			if (data[i] == 'e' && data[i + 1] == 'n')
			{
				size_t offset = i;

				// encoding follows the version field which can't contain 'en' so this has to be the encoding if XML is well formed
				PUGI_IMPL_SCANCHAR('e'); PUGI_IMPL_SCANCHAR('n'); PUGI_IMPL_SCANCHAR('c'); PUGI_IMPL_SCANCHAR('o');
				PUGI_IMPL_SCANCHAR('d'); PUGI_IMPL_SCANCHAR('i'); PUGI_IMPL_SCANCHAR('n'); PUGI_IMPL_SCANCHAR('g');

				// S? = S?
				PUGI_IMPL_SCANCHARTYPE(ct_space);
				PUGI_IMPL_SCANCHAR('=');
				PUGI_IMPL_SCANCHARTYPE(ct_space);

				// the only two valid delimiters are ' and "
				uint8_t delimiter = (offset < size && data[offset] == '"') ? '"' : '\'';

				PUGI_IMPL_SCANCHAR(delimiter);

				size_t start = offset;

				out_encoding = data + offset;

				PUGI_IMPL_SCANCHARTYPE(ct_symbol);

				out_length = offset - start;

				PUGI_IMPL_SCANCHAR(delimiter);

				return true;
			}
		}

		return false;

	#undef PUGI_IMPL_SCANCHAR
	#undef PUGI_IMPL_SCANCHARTYPE
	}

	PUGI_IMPL_FN xml_encoding guess_buffer_encoding(const uint8_t* data, size_t size)
	{
		// skip encoding autodetection if input buffer is too small
		if (size < 4) return encoding_utf8;

		uint8_t d0 = data[0], d1 = data[1], d2 = data[2], d3 = data[3];

		// look for BOM in first few bytes
		if (d0 == 0 && d1 == 0 && d2 == 0xfe && d3 == 0xff) return encoding_utf32_be;
		if (d0 == 0xff && d1 == 0xfe && d2 == 0 && d3 == 0) return encoding_utf32_le;
		if (d0 == 0xfe && d1 == 0xff) return encoding_utf16_be;
		if (d0 == 0xff && d1 == 0xfe) return encoding_utf16_le;
		if (d0 == 0xef && d1 == 0xbb && d2 == 0xbf) return encoding_utf8;

		// look for <, <? or <?xm in various encodings
		if (d0 == 0 && d1 == 0 && d2 == 0 && d3 == 0x3c) return encoding_utf32_be;
		if (d0 == 0x3c && d1 == 0 && d2 == 0 && d3 == 0) return encoding_utf32_le;
		if (d0 == 0 && d1 == 0x3c && d2 == 0 && d3 == 0x3f) return encoding_utf16_be;
		if (d0 == 0x3c && d1 == 0 && d2 == 0x3f && d3 == 0) return encoding_utf16_le;

		// look for utf16 < followed by node name (this may fail, but is better than utf8 since it's zero terminated so early)
		if (d0 == 0 && d1 == 0x3c) return encoding_utf16_be;
		if (d0 == 0x3c && d1 == 0) return encoding_utf16_le;

		// no known BOM detected; parse declaration
		const uint8_t* enc = NULL;
		size_t enc_length = 0;

		if (d0 == 0x3c && d1 == 0x3f && d2 == 0x78 && d3 == 0x6d && parse_declaration_encoding(data, size, enc, enc_length))
		{
			// iso-8859-1 (case-insensitive)
			if (enc_length == 10
				&& (enc[0] | ' ') == 'i' && (enc[1] | ' ') == 's' && (enc[2] | ' ') == 'o'
				&& enc[3] == '-' && enc[4] == '8' && enc[5] == '8' && enc[6] == '5' && enc[7] == '9'
				&& enc[8] == '-' && enc[9] == '1')
				return encoding_latin1;

			// latin1 (case-insensitive)
			if (enc_length == 6
				&& (enc[0] | ' ') == 'l' && (enc[1] | ' ') == 'a' && (enc[2] | ' ') == 't'
				&& (enc[3] | ' ') == 'i' && (enc[4] | ' ') == 'n'
				&& enc[5] == '1')
				return encoding_latin1;
		}

		return encoding_utf8;
	}

	PUGI_IMPL_FN xml_encoding get_buffer_encoding(xml_encoding encoding, const void* contents, size_t size)
	{
		// replace wchar encoding with utf implementation
		if (encoding == encoding_wchar) return get_wchar_encoding();

		// replace utf16 encoding with utf16 with specific endianness
		if (encoding == encoding_utf16) return is_little_endian() ? encoding_utf16_le : encoding_utf16_be;

		// replace utf32 encoding with utf32 with specific endianness
		if (encoding == encoding_utf32) return is_little_endian() ? encoding_utf32_le : encoding_utf32_be;

		// only do autodetection if no explicit encoding is requested
		if (encoding != encoding_auto) return encoding;

		// try to guess encoding (based on XML specification, Appendix F.1)
		const uint8_t* data = static_cast<const uint8_t*>(contents);

		return guess_buffer_encoding(data, size);
	}

	PUGI_IMPL_FN bool get_mutable_buffer(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, bool is_mutable)
	{
		size_t length = size / sizeof(char_t);

		if (is_mutable)
		{
			out_buffer = static_cast<char_t*>(const_cast<void*>(contents));
			out_length = length;
		}
		else
		{
			char_t* buffer = static_cast<char_t*>(xml_memory::allocate((length + 1) * sizeof(char_t)));
			if (!buffer) return false;

			if (contents)
				memcpy(buffer, contents, length * sizeof(char_t));
			else
				assert(length == 0);

			buffer[length] = 0;

			out_buffer = buffer;
			out_length = length + 1;
		}

		return true;
	}

#ifdef PUGIXML_WCHAR_MODE
	PUGI_IMPL_FN bool need_endian_swap_utf(xml_encoding le, xml_encoding re)
	{
		return (le == encoding_utf16_be && re == encoding_utf16_le) || (le == encoding_utf16_le && re == encoding_utf16_be) ||
			   (le == encoding_utf32_be && re == encoding_utf32_le) || (le == encoding_utf32_le && re == encoding_utf32_be);
	}

	PUGI_IMPL_FN bool convert_buffer_endian_swap(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, bool is_mutable)
	{
		const char_t* data = static_cast<const char_t*>(contents);
		size_t length = size / sizeof(char_t);

		if (is_mutable)
		{
			char_t* buffer = const_cast<char_t*>(data);

			convert_wchar_endian_swap(buffer, data, length);

			out_buffer = buffer;
			out_length = length;
		}
		else
		{
			char_t* buffer = static_cast<char_t*>(xml_memory::allocate((length + 1) * sizeof(char_t)));
			if (!buffer) return false;

			convert_wchar_endian_swap(buffer, data, length);
			buffer[length] = 0;

			out_buffer = buffer;
			out_length = length + 1;
		}

		return true;
	}

	template <typename D> PUGI_IMPL_FN bool convert_buffer_generic(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, D)
	{
		const typename D::type* data = static_cast<const typename D::type*>(contents);
		size_t data_length = size / sizeof(typename D::type);

		// first pass: get length in wchar_t units
		size_t length = D::process(data, data_length, 0, wchar_counter());

		// allocate buffer of suitable length
		char_t* buffer = static_cast<char_t*>(xml_memory::allocate((length + 1) * sizeof(char_t)));
		if (!buffer) return false;

		// second pass: convert utf16 input to wchar_t
		wchar_writer::value_type obegin = reinterpret_cast<wchar_writer::value_type>(buffer);
		wchar_writer::value_type oend = D::process(data, data_length, obegin, wchar_writer());

		assert(oend == obegin + length);
		*oend = 0;

		out_buffer = buffer;
		out_length = length + 1;

		return true;
	}

	PUGI_IMPL_FN bool convert_buffer(char_t*& out_buffer, size_t& out_length, xml_encoding encoding, const void* contents, size_t size, bool is_mutable)
	{
		// get native encoding
		xml_encoding wchar_encoding = get_wchar_encoding();

		// fast path: no conversion required
		if (encoding == wchar_encoding)
			return get_mutable_buffer(out_buffer, out_length, contents, size, is_mutable);

		// only endian-swapping is required
		if (need_endian_swap_utf(encoding, wchar_encoding))
			return convert_buffer_endian_swap(out_buffer, out_length, contents, size, is_mutable);

		// source encoding is utf8
		if (encoding == encoding_utf8)
			return convert_buffer_generic(out_buffer, out_length, contents, size, utf8_decoder());

		// source encoding is utf16
		if (encoding == encoding_utf16_be || encoding == encoding_utf16_le)
		{
			xml_encoding native_encoding = is_little_endian() ? encoding_utf16_le : encoding_utf16_be;

			return (native_encoding == encoding) ?
				convert_buffer_generic(out_buffer, out_length, contents, size, utf16_decoder<opt_false>()) :
				convert_buffer_generic(out_buffer, out_length, contents, size, utf16_decoder<opt_true>());
		}

		// source encoding is utf32
		if (encoding == encoding_utf32_be || encoding == encoding_utf32_le)
		{
			xml_encoding native_encoding = is_little_endian() ? encoding_utf32_le : encoding_utf32_be;

			return (native_encoding == encoding) ?
				convert_buffer_generic(out_buffer, out_length, contents, size, utf32_decoder<opt_false>()) :
				convert_buffer_generic(out_buffer, out_length, contents, size, utf32_decoder<opt_true>());
		}

		// source encoding is latin1
		if (encoding == encoding_latin1)
			return convert_buffer_generic(out_buffer, out_length, contents, size, latin1_decoder());

		assert(false && "Invalid encoding"); // unreachable
		return false;
	}
#else
	template <typename D> PUGI_IMPL_FN bool convert_buffer_generic(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, D)
	{
		const typename D::type* data = static_cast<const typename D::type*>(contents);
		size_t data_length = size / sizeof(typename D::type);

		// first pass: get length in utf8 units
		size_t length = D::process(data, data_length, 0, utf8_counter());

		// allocate buffer of suitable length
		char_t* buffer = static_cast<char_t*>(xml_memory::allocate((length + 1) * sizeof(char_t)));
		if (!buffer) return false;

		// second pass: convert utf16 input to utf8
		uint8_t* obegin = reinterpret_cast<uint8_t*>(buffer);
		uint8_t* oend = D::process(data, data_length, obegin, utf8_writer());

		assert(oend == obegin + length);
		*oend = 0;

		out_buffer = buffer;
		out_length = length + 1;

		return true;
	}

	PUGI_IMPL_FN size_t get_latin1_7bit_prefix_length(const uint8_t* data, size_t size)
	{
		for (size_t i = 0; i < size; ++i)
			if (data[i] > 127)
				return i;

		return size;
	}

	PUGI_IMPL_FN bool convert_buffer_latin1(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, bool is_mutable)
	{
		const uint8_t* data = static_cast<const uint8_t*>(contents);
		size_t data_length = size;

		// get size of prefix that does not need utf8 conversion
		size_t prefix_length = get_latin1_7bit_prefix_length(data, data_length);
		assert(prefix_length <= data_length);

		const uint8_t* postfix = data + prefix_length;
		size_t postfix_length = data_length - prefix_length;

		// if no conversion is needed, just return the original buffer
		if (postfix_length == 0) return get_mutable_buffer(out_buffer, out_length, contents, size, is_mutable);

		// first pass: get length in utf8 units
		size_t length = prefix_length + latin1_decoder::process(postfix, postfix_length, 0, utf8_counter());

		// allocate buffer of suitable length
		char_t* buffer = static_cast<char_t*>(xml_memory::allocate((length + 1) * sizeof(char_t)));
		if (!buffer) return false;

		// second pass: convert latin1 input to utf8
		memcpy(buffer, data, prefix_length);

		uint8_t* obegin = reinterpret_cast<uint8_t*>(buffer);
		uint8_t* oend = latin1_decoder::process(postfix, postfix_length, obegin + prefix_length, utf8_writer());

		assert(oend == obegin + length);
		*oend = 0;

		out_buffer = buffer;
		out_length = length + 1;

		return true;
	}

	PUGI_IMPL_FN bool convert_buffer(char_t*& out_buffer, size_t& out_length, xml_encoding encoding, const void* contents, size_t size, bool is_mutable)
	{
		// fast path: no conversion required
		if (encoding == encoding_utf8)
			return get_mutable_buffer(out_buffer, out_length, contents, size, is_mutable);

		// source encoding is utf16
		if (encoding == encoding_utf16_be || encoding == encoding_utf16_le)
		{
			xml_encoding native_encoding = is_little_endian() ? encoding_utf16_le : encoding_utf16_be;

			return (native_encoding == encoding) ?
				convert_buffer_generic(out_buffer, out_length, contents, size, utf16_decoder<opt_false>()) :
				convert_buffer_generic(out_buffer, out_length, contents, size, utf16_decoder<opt_true>());
		}

		// source encoding is utf32
		if (encoding == encoding_utf32_be || encoding == encoding_utf32_le)
		{
			xml_encoding native_encoding = is_little_endian() ? encoding_utf32_le : encoding_utf32_be;

			return (native_encoding == encoding) ?
				convert_buffer_generic(out_buffer, out_length, contents, size, utf32_decoder<opt_false>()) :
				convert_buffer_generic(out_buffer, out_length, contents, size, utf32_decoder<opt_true>());
		}

		// source encoding is latin1
		if (encoding == encoding_latin1)
			return convert_buffer_latin1(out_buffer, out_length, contents, size, is_mutable);

		assert(false && "Invalid encoding"); // unreachable
		return false;
	}
#endif

	PUGI_IMPL_FN size_t as_utf8_begin(const wchar_t* str, size_t length)
	{
		// get length in utf8 characters
		return wchar_decoder::process(str, length, 0, utf8_counter());
	}

	PUGI_IMPL_FN void as_utf8_end(char* buffer, size_t size, const wchar_t* str, size_t length)
	{
		// convert to utf8
		uint8_t* begin = reinterpret_cast<uint8_t*>(buffer);
		uint8_t* end = wchar_decoder::process(str, length, begin, utf8_writer());

		assert(begin + size == end);
		(void)!end;
		(void)!size;
	}

#ifndef PUGIXML_NO_STL
	PUGI_IMPL_FN std::string as_utf8_impl(const wchar_t* str, size_t length)
	{
		// first pass: get length in utf8 characters
		size_t size = as_utf8_begin(str, length);

		// allocate resulting string
		std::string result;
		result.resize(size);

		// second pass: convert to utf8
		if (size > 0) as_utf8_end(&result[0], size, str, length);

		return result;
	}

	PUGI_IMPL_FN std::basic_string<wchar_t> as_wide_impl(const char* str, size_t size)
	{
		const uint8_t* data = reinterpret_cast<const uint8_t*>(str);

		// first pass: get length in wchar_t units
		size_t length = utf8_decoder::process(data, size, 0, wchar_counter());

		// allocate resulting string
		std::basic_string<wchar_t> result;
		result.resize(length);

		// second pass: convert to wchar_t
		if (length > 0)
		{
			wchar_writer::value_type begin = reinterpret_cast<wchar_writer::value_type>(&result[0]);
			wchar_writer::value_type end = utf8_decoder::process(data, size, begin, wchar_writer());

			assert(begin + length == end);
			(void)!end;
		}

		return result;
	}
#endif

	template <typename Header>
	inline bool strcpy_insitu_allow(size_t length, const Header& header, uintptr_t header_mask, char_t* target)
	{
		// never reuse shared memory
		if (header & xml_memory_page_contents_shared_mask) return false;

		size_t target_length = strlength(target);

		// always reuse document buffer memory if possible
		if ((header & header_mask) == 0) return target_length >= length;

		// reuse heap memory if waste is not too great
		const size_t reuse_threshold = 32;

		return target_length >= length && (target_length < reuse_threshold || target_length - length < target_length / 2);
	}

	template <typename String, typename Header>
	PUGI_IMPL_FN bool strcpy_insitu(String& dest, Header& header, uintptr_t header_mask, const char_t* source, size_t source_length)
	{
		assert((header & header_mask) == 0 || dest); // header bit indicates whether dest was previously allocated

		if (source_length == 0)
		{
			// empty string and null pointer are equivalent, so just deallocate old memory
			xml_allocator* alloc = PUGI_IMPL_GETPAGE_IMPL(header)->allocator;

			if (header & header_mask) alloc->deallocate_string(dest);

			// mark the string as not allocated
			dest = NULL;
			header &= ~header_mask;

			return true;
		}
		else if (dest && strcpy_insitu_allow(source_length, header, header_mask, dest))
		{
			// we can reuse old buffer, so just copy the new data (including zero terminator)
			memcpy(dest, source, source_length * sizeof(char_t));
			dest[source_length] = 0;

			return true;
		}
		else
		{
			xml_allocator* alloc = PUGI_IMPL_GETPAGE_IMPL(header)->allocator;

			if (!alloc->reserve()) return false;

			// allocate new buffer
			char_t* buf = alloc->allocate_string(source_length + 1);
			if (!buf) return false;

			// copy the string (including zero terminator)
			memcpy(buf, source, source_length * sizeof(char_t));
			buf[source_length] = 0;

			// deallocate old buffer (*after* the above to protect against overlapping memory and/or allocation failures)
			if (header & header_mask) alloc->deallocate_string(dest);

			// the string is now allocated, so set the flag
			dest = buf;
			header |= header_mask;

			return true;
		}
	}

	struct gap
	{
		char_t* end;
		size_t size;

		gap(): end(NULL), size(0)
		{
		}

		// Push new gap, move s count bytes further (skipping the gap).
		// Collapse previous gap.
		void push(char_t*& s, size_t count)
		{
			if (end) // there was a gap already; collapse it
			{
				// Move [old_gap_end, new_gap_start) to [old_gap_start, ...)
				assert(s >= end);
				memmove(end - size, end, (s - end) * sizeof(char_t));
			}

			s += count; // end of current gap

			// "merge" two gaps
			end = s;
			size += count;
		}

		// Collapse all gaps, return past-the-end pointer
		char_t* flush(char_t* s)
		{
			if (end)
			{
				// Move [old_gap_end, current_pos) to [old_gap_start, ...)
				assert(s >= end);
				memmove(end - size, end, (s - end) * sizeof(char_t));

				return s - size;
			}
			else return s;
		}
	};

	PUGI_IMPL_FN char_t* strconv_escape(char_t* s, gap& g)
	{
		char_t* stre = s + 1;

		switch (*stre)
		{
			case '#':	// &#...
			{
				unsigned int ucsc = 0;

				if (stre[1] == 'x') // &#x... (hex code)
				{
					stre += 2;

					char_t ch = *stre;

					if (ch == ';') return stre;

					for (;;)
					{
						if (static_cast<unsigned int>(ch - '0') <= 9)
							ucsc = 16 * ucsc + (ch - '0');
						else if (static_cast<unsigned int>((ch | ' ') - 'a') <= 5)
							ucsc = 16 * ucsc + ((ch | ' ') - 'a' + 10);
						else if (ch == ';')
							break;
						else // cancel
							return stre;

						ch = *++stre;
					}

					++stre;
				}
				else	// &#... (dec code)
				{
					char_t ch = *++stre;

					if (ch == ';') return stre;

					for (;;)
					{
						if (static_cast<unsigned int>(ch - '0') <= 9)
							ucsc = 10 * ucsc + (ch - '0');
						else if (ch == ';')
							break;
						else // cancel
							return stre;

						ch = *++stre;
					}

					++stre;
				}

			#ifdef PUGIXML_WCHAR_MODE
				s = reinterpret_cast<char_t*>(wchar_writer::any(reinterpret_cast<wchar_writer::value_type>(s), ucsc));
			#else
				s = reinterpret_cast<char_t*>(utf8_writer::any(reinterpret_cast<uint8_t*>(s), ucsc));
			#endif

				g.push(s, stre - s);
				return stre;
			}

			case 'a':	// &a
			{
				++stre;

				if (*stre == 'm') // &am
				{
					if (*++stre == 'p' && *++stre == ';') // &amp;
					{
						*s++ = '&';
						++stre;

						g.push(s, stre - s);
						return stre;
					}
				}
				else if (*stre == 'p') // &ap
				{
					if (*++stre == 'o' && *++stre == 's' && *++stre == ';') // &apos;
					{
						*s++ = '\'';
						++stre;

						g.push(s, stre - s);
						return stre;
					}
				}
				break;
			}

			case 'g': // &g
			{
				if (*++stre == 't' && *++stre == ';') // &gt;
				{
					*s++ = '>';
					++stre;

					g.push(s, stre - s);
					return stre;
				}
				break;
			}

			case 'l': // &l
			{
				if (*++stre == 't' && *++stre == ';') // &lt;
				{
					*s++ = '<';
					++stre;

					g.push(s, stre - s);
					return stre;
				}
				break;
			}

			case 'q': // &q
			{
				if (*++stre == 'u' && *++stre == 'o' && *++stre == 't' && *++stre == ';') // &quot;
				{
					*s++ = '"';
					++stre;

					g.push(s, stre - s);
					return stre;
				}
				break;
			}

			default:
				break;
		}

		return stre;
	}

	// Parser utilities
	#define PUGI_IMPL_ENDSWITH(c, e)        ((c) == (e) || ((c) == 0 && endch == (e)))
	#define PUGI_IMPL_SKIPWS()              { while (PUGI_IMPL_IS_CHARTYPE(*s, ct_space)) ++s; }
	#define PUGI_IMPL_OPTSET(OPT)           ( optmsk & (OPT) )
	#define PUGI_IMPL_PUSHNODE(TYPE)        { cursor = append_new_node(cursor, *alloc, TYPE); if (!cursor) PUGI_IMPL_THROW_ERROR(status_out_of_memory, s); }
	#define PUGI_IMPL_POPNODE()             { cursor = cursor->parent; }
	#define PUGI_IMPL_SCANFOR(X)            { while (*s != 0 && !(X)) ++s; }
	#define PUGI_IMPL_SCANWHILE(X)          { while (X) ++s; }
	#define PUGI_IMPL_SCANWHILE_UNROLL(X)   { for (;;) { char_t ss = s[0]; if (PUGI_IMPL_UNLIKELY(!(X))) { break; } ss = s[1]; if (PUGI_IMPL_UNLIKELY(!(X))) { s += 1; break; } ss = s[2]; if (PUGI_IMPL_UNLIKELY(!(X))) { s += 2; break; } ss = s[3]; if (PUGI_IMPL_UNLIKELY(!(X))) { s += 3; break; } s += 4; } }
	#define PUGI_IMPL_ENDSEG()              { ch = *s; *s = 0; ++s; }
	#define PUGI_IMPL_THROW_ERROR(err, m)   return error_offset = m, error_status = err, static_cast<char_t*>(NULL)
	#define PUGI_IMPL_CHECK_ERROR(err, m)   { if (*s == 0) PUGI_IMPL_THROW_ERROR(err, m); }

	PUGI_IMPL_FN char_t* strconv_comment(char_t* s, char_t endch)
	{
		gap g;

		while (true)
		{
			PUGI_IMPL_SCANWHILE_UNROLL(!PUGI_IMPL_IS_CHARTYPE(ss, ct_parse_comment));

			if (*s == '\r') // Either a single 0x0d or 0x0d 0x0a pair
			{
				*s++ = '\n'; // replace first one with 0x0a

				if (*s == '\n') g.push(s, 1);
			}
			else if (s[0] == '-' && s[1] == '-' && PUGI_IMPL_ENDSWITH(s[2], '>')) // comment ends here
			{
				*g.flush(s) = 0;

				return s + (s[2] == '>' ? 3 : 2);
			}
			else if (*s == 0)
			{
				return NULL;
			}
			else ++s;
		}
	}

	PUGI_IMPL_FN char_t* strconv_cdata(char_t* s, char_t endch)
	{
		gap g;

		while (true)
		{
			PUGI_IMPL_SCANWHILE_UNROLL(!PUGI_IMPL_IS_CHARTYPE(ss, ct_parse_cdata));

			if (*s == '\r') // Either a single 0x0d or 0x0d 0x0a pair
			{
				*s++ = '\n'; // replace first one with 0x0a

				if (*s == '\n') g.push(s, 1);
			}
			else if (s[0] == ']' && s[1] == ']' && PUGI_IMPL_ENDSWITH(s[2], '>')) // CDATA ends here
			{
				*g.flush(s) = 0;

				return s + 1;
			}
			else if (*s == 0)
			{
				return NULL;
			}
			else ++s;
		}
	}

	typedef char_t* (*strconv_pcdata_t)(char_t*);

	template <typename opt_trim, typename opt_eol, typename opt_escape> struct strconv_pcdata_impl
	{
		static char_t* parse(char_t* s)
		{
			gap g;

			char_t* begin = s;

			while (true)
			{
				PUGI_IMPL_SCANWHILE_UNROLL(!PUGI_IMPL_IS_CHARTYPE(ss, ct_parse_pcdata));

				if (*s == '<') // PCDATA ends here
				{
					char_t* end = g.flush(s);

					if (opt_trim::value)
						while (end > begin && PUGI_IMPL_IS_CHARTYPE(end[-1], ct_space))
							--end;

					*end = 0;

					return s + 1;
				}
				else if (opt_eol::value && *s == '\r') // Either a single 0x0d or 0x0d 0x0a pair
				{
					*s++ = '\n'; // replace first one with 0x0a

					if (*s == '\n') g.push(s, 1);
				}
				else if (opt_escape::value && *s == '&')
				{
					s = strconv_escape(s, g);
				}
				else if (*s == 0)
				{
					char_t* end = g.flush(s);

					if (opt_trim::value)
						while (end > begin && PUGI_IMPL_IS_CHARTYPE(end[-1], ct_space))
							--end;

					*end = 0;

					return s;
				}
				else ++s;
			}
		}
	};

	PUGI_IMPL_FN strconv_pcdata_t get_strconv_pcdata(unsigned int optmask)
	{
		PUGI_IMPL_STATIC_ASSERT(parse_escapes == 0x10 && parse_eol == 0x20 && parse_trim_pcdata == 0x0800);

		switch (((optmask >> 4) & 3) | ((optmask >> 9) & 4)) // get bitmask for flags (trim eol escapes); this simultaneously checks 3 options from assertion above
		{
		case 0: return strconv_pcdata_impl<opt_false, opt_false, opt_false>::parse;
		case 1: return strconv_pcdata_impl<opt_false, opt_false, opt_true>::parse;
		case 2: return strconv_pcdata_impl<opt_false, opt_true, opt_false>::parse;
		case 3: return strconv_pcdata_impl<opt_false, opt_true, opt_true>::parse;
		case 4: return strconv_pcdata_impl<opt_true, opt_false, opt_false>::parse;
		case 5: return strconv_pcdata_impl<opt_true, opt_false, opt_true>::parse;
		case 6: return strconv_pcdata_impl<opt_true, opt_true, opt_false>::parse;
		case 7: return strconv_pcdata_impl<opt_true, opt_true, opt_true>::parse;
		default: assert(false); return NULL; // unreachable
		}
	}

	typedef char_t* (*strconv_attribute_t)(char_t*, char_t);

	template <typename opt_escape> struct strconv_attribute_impl
	{
		static char_t* parse_wnorm(char_t* s, char_t end_quote)
		{
			gap g;

			// trim leading whitespaces
			if (PUGI_IMPL_IS_CHARTYPE(*s, ct_space))
			{
				char_t* str = s;

				do ++str;
				while (PUGI_IMPL_IS_CHARTYPE(*str, ct_space));

				g.push(s, str - s);
			}

			while (true)
			{
				PUGI_IMPL_SCANWHILE_UNROLL(!PUGI_IMPL_IS_CHARTYPE(ss, ct_parse_attr_ws | ct_space));

				if (*s == end_quote)
				{
					char_t* str = g.flush(s);

					do *str-- = 0;
					while (PUGI_IMPL_IS_CHARTYPE(*str, ct_space));

					return s + 1;
				}
				else if (PUGI_IMPL_IS_CHARTYPE(*s, ct_space))
				{
					*s++ = ' ';

					if (PUGI_IMPL_IS_CHARTYPE(*s, ct_space))
					{
						char_t* str = s + 1;
						while (PUGI_IMPL_IS_CHARTYPE(*str, ct_space)) ++str;

						g.push(s, str - s);
					}
				}
				else if (opt_escape::value && *s == '&')
				{
					s = strconv_escape(s, g);
				}
				else if (!*s)
				{
					return NULL;
				}
				else ++s;
			}
		}

		static char_t* parse_wconv(char_t* s, char_t end_quote)
		{
			gap g;

			while (true)
			{
				PUGI_IMPL_SCANWHILE_UNROLL(!PUGI_IMPL_IS_CHARTYPE(ss, ct_parse_attr_ws));

				if (*s == end_quote)
				{
					*g.flush(s) = 0;

					return s + 1;
				}
				else if (PUGI_IMPL_IS_CHARTYPE(*s, ct_space))
				{
					if (*s == '\r')
					{
						*s++ = ' ';

						if (*s == '\n') g.push(s, 1);
					}
					else *s++ = ' ';
				}
				else if (opt_escape::value && *s == '&')
				{
					s = strconv_escape(s, g);
				}
				else if (!*s)
				{
					return NULL;
				}
				else ++s;
			}
		}

		static char_t* parse_eol(char_t* s, char_t end_quote)
		{
			gap g;

			while (true)
			{
				PUGI_IMPL_SCANWHILE_UNROLL(!PUGI_IMPL_IS_CHARTYPE(ss, ct_parse_attr));

				if (*s == end_quote)
				{
					*g.flush(s) = 0;

					return s + 1;
				}
				else if (*s == '\r')
				{
					*s++ = '\n';

					if (*s == '\n') g.push(s, 1);
				}
				else if (opt_escape::value && *s == '&')
				{
					s = strconv_escape(s, g);
				}
				else if (!*s)
				{
					return NULL;
				}
				else ++s;
			}
		}

		static char_t* parse_simple(char_t* s, char_t end_quote)
		{
			gap g;

			while (true)
			{
				PUGI_IMPL_SCANWHILE_UNROLL(!PUGI_IMPL_IS_CHARTYPE(ss, ct_parse_attr));

				if (*s == end_quote)
				{
					*g.flush(s) = 0;

					return s + 1;
				}
				else if (opt_escape::value && *s == '&')
				{
					s = strconv_escape(s, g);
				}
				else if (!*s)
				{
					return NULL;
				}
				else ++s;
			}
		}
	};

	PUGI_IMPL_FN strconv_attribute_t get_strconv_attribute(unsigned int optmask)
	{
		PUGI_IMPL_STATIC_ASSERT(parse_escapes == 0x10 && parse_eol == 0x20 && parse_wconv_attribute == 0x40 && parse_wnorm_attribute == 0x80);

		switch ((optmask >> 4) & 15) // get bitmask for flags (wnorm wconv eol escapes); this simultaneously checks 4 options from assertion above
		{
		case 0:  return strconv_attribute_impl<opt_false>::parse_simple;
		case 1:  return strconv_attribute_impl<opt_true>::parse_simple;
		case 2:  return strconv_attribute_impl<opt_false>::parse_eol;
		case 3:  return strconv_attribute_impl<opt_true>::parse_eol;
		case 4:  return strconv_attribute_impl<opt_false>::parse_wconv;
		case 5:  return strconv_attribute_impl<opt_true>::parse_wconv;
		case 6:  return strconv_attribute_impl<opt_false>::parse_wconv;
		case 7:  return strconv_attribute_impl<opt_true>::parse_wconv;
		case 8:  return strconv_attribute_impl<opt_false>::parse_wnorm;
		case 9:  return strconv_attribute_impl<opt_true>::parse_wnorm;
		case 10: return strconv_attribute_impl<opt_false>::parse_wnorm;
		case 11: return strconv_attribute_impl<opt_true>::parse_wnorm;
		case 12: return strconv_attribute_impl<opt_false>::parse_wnorm;
		case 13: return strconv_attribute_impl<opt_true>::parse_wnorm;
		case 14: return strconv_attribute_impl<opt_false>::parse_wnorm;
		case 15: return strconv_attribute_impl<opt_true>::parse_wnorm;
		default: assert(false); return NULL; // unreachable
		}
	}

	inline xml_parse_result make_parse_result(xml_parse_status status, ptrdiff_t offset = 0)
	{
		xml_parse_result result;
		result.status = status;
		result.offset = offset;

		return result;
	}

	struct xml_parser
	{
		xml_allocator* alloc;
		char_t* error_offset;
		xml_parse_status error_status;

		xml_parser(xml_allocator* alloc_): alloc(alloc_), error_offset(NULL), error_status(status_ok)
		{
		}

		// DOCTYPE consists of nested sections of the following possible types:
		// <!-- ... -->, <? ... ?>, "...", '...'
		// <![...]]>
		// <!...>
		// First group can not contain nested groups
		// Second group can contain nested groups of the same type
		// Third group can contain all other groups
		char_t* parse_doctype_primitive(char_t* s)
		{
			if (*s == '"' || *s == '\'')
			{
				// quoted string
				char_t ch = *s++;
				PUGI_IMPL_SCANFOR(*s == ch);
				if (!*s) PUGI_IMPL_THROW_ERROR(status_bad_doctype, s);

				s++;
			}
			else if (s[0] == '<' && s[1] == '?')
			{
				// <? ... ?>
				s += 2;
				PUGI_IMPL_SCANFOR(s[0] == '?' && s[1] == '>'); // no need for ENDSWITH because ?> can't terminate proper doctype
				if (!*s) PUGI_IMPL_THROW_ERROR(status_bad_doctype, s);

				s += 2;
			}
			else if (s[0] == '<' && s[1] == '!' && s[2] == '-' && s[3] == '-')
			{
				s += 4;
				PUGI_IMPL_SCANFOR(s[0] == '-' && s[1] == '-' && s[2] == '>'); // no need for ENDSWITH because --> can't terminate proper doctype
				if (!*s) PUGI_IMPL_THROW_ERROR(status_bad_doctype, s);

				s += 3;
			}
			else PUGI_IMPL_THROW_ERROR(status_bad_doctype, s);

			return s;
		}

		char_t* parse_doctype_ignore(char_t* s)
		{
			size_t depth = 0;

			assert(s[0] == '<' && s[1] == '!' && s[2] == '[');
			s += 3;

			while (*s)
			{
				if (s[0] == '<' && s[1] == '!' && s[2] == '[')
				{
					// nested ignore section
					s += 3;
					depth++;
				}
				else if (s[0] == ']' && s[1] == ']' && s[2] == '>')
				{
					// ignore section end
					s += 3;

					if (depth == 0)
						return s;

					depth--;
				}
				else s++;
			}

			PUGI_IMPL_THROW_ERROR(status_bad_doctype, s);
		}

		char_t* parse_doctype_group(char_t* s, char_t endch)
		{
			size_t depth = 0;

			assert((s[0] == '<' || s[0] == 0) && s[1] == '!');
			s += 2;

			while (*s)
			{
				if (s[0] == '<' && s[1] == '!' && s[2] != '-')
				{
					if (s[2] == '[')
					{
						// ignore
						s = parse_doctype_ignore(s);
						if (!s) return s;
					}
					else
					{
						// some control group
						s += 2;
						depth++;
					}
				}
				else if (s[0] == '<' || s[0] == '"' || s[0] == '\'')
				{
					// unknown tag (forbidden), or some primitive group
					s = parse_doctype_primitive(s);
					if (!s) return s;
				}
				else if (*s == '>')
				{
					if (depth == 0)
						return s;

					depth--;
					s++;
				}
				else s++;
			}

			if (depth != 0 || endch != '>') PUGI_IMPL_THROW_ERROR(status_bad_doctype, s);

			return s;
		}

		char_t* parse_exclamation(char_t* s, xml_node_struct* cursor, unsigned int optmsk, char_t endch)
		{
			// parse node contents, starting with exclamation mark
			++s;

			if (*s == '-') // '<!-...'
			{
				++s;

				if (*s == '-') // '<!--...'
				{
					++s;

					if (PUGI_IMPL_OPTSET(parse_comments))
					{
						PUGI_IMPL_PUSHNODE(node_comment); // Append a new node on the tree.
						cursor->value = s; // Save the offset.
					}

					if (PUGI_IMPL_OPTSET(parse_eol) && PUGI_IMPL_OPTSET(parse_comments))
					{
						s = strconv_comment(s, endch);

						if (!s) PUGI_IMPL_THROW_ERROR(status_bad_comment, cursor->value);
					}
					else
					{
						// Scan for terminating '-->'.
						PUGI_IMPL_SCANFOR(s[0] == '-' && s[1] == '-' && PUGI_IMPL_ENDSWITH(s[2], '>'));
						PUGI_IMPL_CHECK_ERROR(status_bad_comment, s);

						if (PUGI_IMPL_OPTSET(parse_comments))
							*s = 0; // Zero-terminate this segment at the first terminating '-'.

						s += (s[2] == '>' ? 3 : 2); // Step over the '\0->'.
					}
				}
				else PUGI_IMPL_THROW_ERROR(status_bad_comment, s);
			}
			else if (*s == '[')
			{
				// '<![CDATA[...'
				if (*++s=='C' && *++s=='D' && *++s=='A' && *++s=='T' && *++s=='A' && *++s == '[')
				{
					++s;

					if (PUGI_IMPL_OPTSET(parse_cdata))
					{
						PUGI_IMPL_PUSHNODE(node_cdata); // Append a new node on the tree.
						cursor->value = s; // Save the offset.

						if (PUGI_IMPL_OPTSET(parse_eol))
						{
							s = strconv_cdata(s, endch);

							if (!s) PUGI_IMPL_THROW_ERROR(status_bad_cdata, cursor->value);
						}
						else
						{
							// Scan for terminating ']]>'.
							PUGI_IMPL_SCANFOR(s[0] == ']' && s[1] == ']' && PUGI_IMPL_ENDSWITH(s[2], '>'));
							PUGI_IMPL_CHECK_ERROR(status_bad_cdata, s);

							*s++ = 0; // Zero-terminate this segment.
						}
					}
					else // Flagged for discard, but we still have to scan for the terminator.
					{
						// Scan for terminating ']]>'.
						PUGI_IMPL_SCANFOR(s[0] == ']' && s[1] == ']' && PUGI_IMPL_ENDSWITH(s[2], '>'));
						PUGI_IMPL_CHECK_ERROR(status_bad_cdata, s);

						++s;
					}

					s += (s[1] == '>' ? 2 : 1); // Step over the last ']>'.
				}
				else PUGI_IMPL_THROW_ERROR(status_bad_cdata, s);
			}
			else if (s[0] == 'D' && s[1] == 'O' && s[2] == 'C' && s[3] == 'T' && s[4] == 'Y' && s[5] == 'P' && PUGI_IMPL_ENDSWITH(s[6], 'E'))
			{
				s -= 2;

				if (cursor->parent) PUGI_IMPL_THROW_ERROR(status_bad_doctype, s);

				char_t* mark = s + 9;

				s = parse_doctype_group(s, endch);
				if (!s) return s;

				assert((*s == 0 && endch == '>') || *s == '>');
				if (*s) *s++ = 0;

				if (PUGI_IMPL_OPTSET(parse_doctype))
				{
					while (PUGI_IMPL_IS_CHARTYPE(*mark, ct_space)) ++mark;

					PUGI_IMPL_PUSHNODE(node_doctype);

					cursor->value = mark;
				}
			}
			else if (*s == 0 && endch == '-') PUGI_IMPL_THROW_ERROR(status_bad_comment, s);
			else if (*s == 0 && endch == '[') PUGI_IMPL_THROW_ERROR(status_bad_cdata, s);
			else PUGI_IMPL_THROW_ERROR(status_unrecognized_tag, s);

			return s;
		}

		char_t* parse_question(char_t* s, xml_node_struct*& ref_cursor, unsigned int optmsk, char_t endch)
		{
			// load into registers
			xml_node_struct* cursor = ref_cursor;
			char_t ch = 0;

			// parse node contents, starting with question mark
			++s;

			// read PI target
			char_t* target = s;

			if (!PUGI_IMPL_IS_CHARTYPE(*s, ct_start_symbol)) PUGI_IMPL_THROW_ERROR(status_bad_pi, s);

			PUGI_IMPL_SCANWHILE(PUGI_IMPL_IS_CHARTYPE(*s, ct_symbol));
			PUGI_IMPL_CHECK_ERROR(status_bad_pi, s);

			// determine node type; stricmp / strcasecmp is not portable
			bool declaration = (target[0] | ' ') == 'x' && (target[1] | ' ') == 'm' && (target[2] | ' ') == 'l' && target + 3 == s;

			if (declaration ? PUGI_IMPL_OPTSET(parse_declaration) : PUGI_IMPL_OPTSET(parse_pi))
			{
				if (declaration)
				{
					// disallow non top-level declarations
					if (cursor->parent) PUGI_IMPL_THROW_ERROR(status_bad_pi, s);

					PUGI_IMPL_PUSHNODE(node_declaration);
				}
				else
				{
					PUGI_IMPL_PUSHNODE(node_pi);
				}

				cursor->name = target;

				PUGI_IMPL_ENDSEG();

				// parse value/attributes
				if (ch == '?')
				{
					// empty node
					if (!PUGI_IMPL_ENDSWITH(*s, '>')) PUGI_IMPL_THROW_ERROR(status_bad_pi, s);
					s += (*s == '>');

					PUGI_IMPL_POPNODE();
				}
				else if (PUGI_IMPL_IS_CHARTYPE(ch, ct_space))
				{
					PUGI_IMPL_SKIPWS();

					// scan for tag end
					char_t* value = s;

					PUGI_IMPL_SCANFOR(s[0] == '?' && PUGI_IMPL_ENDSWITH(s[1], '>'));
					PUGI_IMPL_CHECK_ERROR(status_bad_pi, s);

					if (declaration)
					{
						// replace ending ? with / so that 'element' terminates properly
						*s = '/';

						// we exit from this function with cursor at node_declaration, which is a signal to parse() to go to LOC_ATTRIBUTES
						s = value;
					}
					else
					{
						// store value and step over >
						cursor->value = value;

						PUGI_IMPL_POPNODE();

						PUGI_IMPL_ENDSEG();

						s += (*s == '>');
					}
				}
				else PUGI_IMPL_THROW_ERROR(status_bad_pi, s);
			}
			else
			{
				// scan for tag end
				PUGI_IMPL_SCANFOR(s[0] == '?' && PUGI_IMPL_ENDSWITH(s[1], '>'));
				PUGI_IMPL_CHECK_ERROR(status_bad_pi, s);

				s += (s[1] == '>' ? 2 : 1);
			}

			// store from registers
			ref_cursor = cursor;

			return s;
		}

		char_t* parse_tree(char_t* s, xml_node_struct* root, unsigned int optmsk, char_t endch)
		{
			strconv_attribute_t strconv_attribute = get_strconv_attribute(optmsk);
			strconv_pcdata_t strconv_pcdata = get_strconv_pcdata(optmsk);

			char_t ch = 0;
			xml_node_struct* cursor = root;
			char_t* mark = s;
			char_t* merged_pcdata = s;

			while (*s != 0)
			{
				if (*s == '<')
				{
					++s;

				LOC_TAG:
					if (PUGI_IMPL_IS_CHARTYPE(*s, ct_start_symbol)) // '<#...'
					{
						PUGI_IMPL_PUSHNODE(node_element); // Append a new node to the tree.

						cursor->name = s;

						PUGI_IMPL_SCANWHILE_UNROLL(PUGI_IMPL_IS_CHARTYPE(ss, ct_symbol)); // Scan for a terminator.
						PUGI_IMPL_ENDSEG(); // Save char in 'ch', terminate & step over.

						if (ch == '>')
						{
							// end of tag
						}
						else if (PUGI_IMPL_IS_CHARTYPE(ch, ct_space))
						{
						LOC_ATTRIBUTES:
							while (true)
							{
								PUGI_IMPL_SKIPWS(); // Eat any whitespace.

								if (PUGI_IMPL_IS_CHARTYPE(*s, ct_start_symbol)) // <... #...
								{
									xml_attribute_struct* a = append_new_attribute(cursor, *alloc); // Make space for this attribute.
									if (!a) PUGI_IMPL_THROW_ERROR(status_out_of_memory, s);

									a->name = s; // Save the offset.

									PUGI_IMPL_SCANWHILE_UNROLL(PUGI_IMPL_IS_CHARTYPE(ss, ct_symbol)); // Scan for a terminator.
									PUGI_IMPL_ENDSEG(); // Save char in 'ch', terminate & step over.

									if (PUGI_IMPL_IS_CHARTYPE(ch, ct_space))
									{
										PUGI_IMPL_SKIPWS(); // Eat any whitespace.

										ch = *s;
										++s;
									}

									if (ch == '=') // '<... #=...'
									{
										PUGI_IMPL_SKIPWS(); // Eat any whitespace.

										if (*s == '"' || *s == '\'') // '<... #="...'
										{
											ch = *s; // Save quote char to avoid breaking on "''" -or- '""'.
											++s; // Step over the quote.
											a->value = s; // Save the offset.

											s = strconv_attribute(s, ch);

											if (!s) PUGI_IMPL_THROW_ERROR(status_bad_attribute, a->value);

											// After this line the loop continues from the start;
											// Whitespaces, / and > are ok, symbols and EOF are wrong,
											// everything else will be detected
											if (PUGI_IMPL_IS_CHARTYPE(*s, ct_start_symbol)) PUGI_IMPL_THROW_ERROR(status_bad_attribute, s);
										}
										else PUGI_IMPL_THROW_ERROR(status_bad_attribute, s);
									}
									else PUGI_IMPL_THROW_ERROR(status_bad_attribute, s);
								}
								else if (*s == '/')
								{
									++s;

									if (*s == '>')
									{
										PUGI_IMPL_POPNODE();
										s++;
										break;
									}
									else if (*s == 0 && endch == '>')
									{
										PUGI_IMPL_POPNODE();
										break;
									}
									else PUGI_IMPL_THROW_ERROR(status_bad_start_element, s);
								}
								else if (*s == '>')
								{
									++s;

									break;
								}
								else if (*s == 0 && endch == '>')
								{
									break;
								}
								else PUGI_IMPL_THROW_ERROR(status_bad_start_element, s);
							}

							// !!!
						}
						else if (ch == '/') // '<#.../'
						{
							if (!PUGI_IMPL_ENDSWITH(*s, '>')) PUGI_IMPL_THROW_ERROR(status_bad_start_element, s);

							PUGI_IMPL_POPNODE(); // Pop.

							s += (*s == '>');
						}
						else if (ch == 0)
						{
							// we stepped over null terminator, backtrack & handle closing tag
							--s;

							if (endch != '>') PUGI_IMPL_THROW_ERROR(status_bad_start_element, s);
						}
						else PUGI_IMPL_THROW_ERROR(status_bad_start_element, s);
					}
					else if (*s == '/')
					{
						++s;

						mark = s;

						char_t* name = cursor->name;
						if (!name) PUGI_IMPL_THROW_ERROR(status_end_element_mismatch, mark);

						while (PUGI_IMPL_IS_CHARTYPE(*s, ct_symbol))
						{
							if (*s++ != *name++) PUGI_IMPL_THROW_ERROR(status_end_element_mismatch, mark);
						}

						if (*name)
						{
							if (*s == 0 && name[0] == endch && name[1] == 0) PUGI_IMPL_THROW_ERROR(status_bad_end_element, s);
							else PUGI_IMPL_THROW_ERROR(status_end_element_mismatch, mark);
						}

						PUGI_IMPL_POPNODE(); // Pop.

						PUGI_IMPL_SKIPWS();

						if (*s == 0)
						{
							if (endch != '>') PUGI_IMPL_THROW_ERROR(status_bad_end_element, s);
						}
						else
						{
							if (*s != '>') PUGI_IMPL_THROW_ERROR(status_bad_end_element, s);
							++s;
						}
					}
					else if (*s == '?') // '<?...'
					{
						s = parse_question(s, cursor, optmsk, endch);
						if (!s) return s;

						assert(cursor);
						if (PUGI_IMPL_NODETYPE(cursor) == node_declaration) goto LOC_ATTRIBUTES;
					}
					else if (*s == '!') // '<!...'
					{
						s = parse_exclamation(s, cursor, optmsk, endch);
						if (!s) return s;
					}
					else if (*s == 0 && endch == '?') PUGI_IMPL_THROW_ERROR(status_bad_pi, s);
					else PUGI_IMPL_THROW_ERROR(status_unrecognized_tag, s);
				}
				else
				{
					mark = s; // Save this offset while searching for a terminator.

					PUGI_IMPL_SKIPWS(); // Eat whitespace if no genuine PCDATA here.

					if (*s == '<' || !*s)
					{
						// We skipped some whitespace characters because otherwise we would take the tag branch instead of PCDATA one
						assert(mark != s);

						if (!PUGI_IMPL_OPTSET(parse_ws_pcdata | parse_ws_pcdata_single) || PUGI_IMPL_OPTSET(parse_trim_pcdata))
						{
							continue;
						}
						else if (PUGI_IMPL_OPTSET(parse_ws_pcdata_single))
						{
							if (s[0] != '<' || s[1] != '/' || cursor->first_child) continue;
						}
					}

					if (!PUGI_IMPL_OPTSET(parse_trim_pcdata))
						s = mark;

					if (cursor->parent || PUGI_IMPL_OPTSET(parse_fragment))
					{
						char_t* parsed_pcdata = s;

						s = strconv_pcdata(s);

						if (PUGI_IMPL_OPTSET(parse_embed_pcdata) && cursor->parent && !cursor->first_child && !cursor->value)
						{
							cursor->value = parsed_pcdata; // Save the offset.
						}
						else if (PUGI_IMPL_OPTSET(parse_merge_pcdata) && cursor->first_child && PUGI_IMPL_NODETYPE(cursor->first_child->prev_sibling_c) == node_pcdata)
						{
							assert(merged_pcdata >= cursor->first_child->prev_sibling_c->value);

							// Catch up to the end of last parsed value; only needed for the first fragment.
							merged_pcdata += strlength(merged_pcdata);

							size_t length = strlength(parsed_pcdata);

							// Must use memmove instead of memcpy as this move may overlap
							memmove(merged_pcdata, parsed_pcdata, (length + 1) * sizeof(char_t));
							merged_pcdata += length;
						}
						else
						{
							xml_node_struct* prev_cursor = cursor;
							PUGI_IMPL_PUSHNODE(node_pcdata); // Append a new node on the tree.

							cursor->value = parsed_pcdata; // Save the offset.
							merged_pcdata = parsed_pcdata; // Used for parse_merge_pcdata above, cheaper to save unconditionally

							cursor = prev_cursor; // Pop since this is a standalone.
						}

						if (!*s) break;
					}
					else
					{
						PUGI_IMPL_SCANFOR(*s == '<'); // '...<'
						if (!*s) break;

						++s;
					}

					// We're after '<'
					goto LOC_TAG;
				}
			}

			// check that last tag is closed
			if (cursor != root) PUGI_IMPL_THROW_ERROR(status_end_element_mismatch, s);

			return s;
		}

	#ifdef PUGIXML_WCHAR_MODE
		static char_t* parse_skip_bom(char_t* s)
		{
			unsigned int bom = 0xfeff;
			return (s[0] == static_cast<wchar_t>(bom)) ? s + 1 : s;
		}
	#else
		static char_t* parse_skip_bom(char_t* s)
		{
			return (s[0] == '\xef' && s[1] == '\xbb' && s[2] == '\xbf') ? s + 3 : s;
		}
	#endif

		static bool has_element_node_siblings(xml_node_struct* node)
		{
			while (node)
			{
				if (PUGI_IMPL_NODETYPE(node) == node_element) return true;

				node = node->next_sibling;
			}

			return false;
		}

		static xml_parse_result parse(char_t* buffer, size_t length, xml_document_struct* xmldoc, xml_node_struct* root, unsigned int optmsk)
		{
			// early-out for empty documents
			if (length == 0)
				return make_parse_result(PUGI_IMPL_OPTSET(parse_fragment) ? status_ok : status_no_document_element);

			// get last child of the root before parsing
			xml_node_struct* last_root_child = root->first_child ? root->first_child->prev_sibling_c + 0 : NULL;

			// create parser on stack
			xml_parser parser(static_cast<xml_allocator*>(xmldoc));

			// save last character and make buffer zero-terminated (speeds up parsing)
			char_t endch = buffer[length - 1];
			buffer[length - 1] = 0;

			// skip BOM to make sure it does not end up as part of parse output
			char_t* buffer_data = parse_skip_bom(buffer);

			// perform actual parsing
			parser.parse_tree(buffer_data, root, optmsk, endch);

			xml_parse_result result = make_parse_result(parser.error_status, parser.error_offset ? parser.error_offset - buffer : 0);
			assert(result.offset >= 0 && static_cast<size_t>(result.offset) <= length);

			if (result)
			{
				// since we removed last character, we have to handle the only possible false positive (stray <)
				if (endch == '<')
					return make_parse_result(status_unrecognized_tag, length - 1);

				// check if there are any element nodes parsed
				xml_node_struct* first_root_child_parsed = last_root_child ? last_root_child->next_sibling + 0 : root->first_child + 0;

				if (!PUGI_IMPL_OPTSET(parse_fragment) && !has_element_node_siblings(first_root_child_parsed))
					return make_parse_result(status_no_document_element, length - 1);
			}
			else
			{
				// roll back offset if it occurs on a null terminator in the source buffer
				if (result.offset > 0 && static_cast<size_t>(result.offset) == length - 1 && endch == 0)
					result.offset--;
			}

			return result;
		}
	};

	// Output facilities
	PUGI_IMPL_FN xml_encoding get_write_native_encoding()
	{
	#ifdef PUGIXML_WCHAR_MODE
		return get_wchar_encoding();
	#else
		return encoding_utf8;
	#endif
	}

	PUGI_IMPL_FN xml_encoding get_write_encoding(xml_encoding encoding)
	{
		// replace wchar encoding with utf implementation
		if (encoding == encoding_wchar) return get_wchar_encoding();

		// replace utf16 encoding with utf16 with specific endianness
		if (encoding == encoding_utf16) return is_little_endian() ? encoding_utf16_le : encoding_utf16_be;

		// replace utf32 encoding with utf32 with specific endianness
		if (encoding == encoding_utf32) return is_little_endian() ? encoding_utf32_le : encoding_utf32_be;

		// only do autodetection if no explicit encoding is requested
		if (encoding != encoding_auto) return encoding;

		// assume utf8 encoding
		return encoding_utf8;
	}

	template <typename D, typename T> PUGI_IMPL_FN size_t convert_buffer_output_generic(typename T::value_type dest, const char_t* data, size_t length, D, T)
	{
		PUGI_IMPL_STATIC_ASSERT(sizeof(char_t) == sizeof(typename D::type));

		typename T::value_type end = D::process(reinterpret_cast<const typename D::type*>(data), length, dest, T());

		return static_cast<size_t>(end - dest) * sizeof(*dest);
	}

	template <typename D, typename T> PUGI_IMPL_FN size_t convert_buffer_output_generic(typename T::value_type dest, const char_t* data, size_t length, D, T, bool opt_swap)
	{
		PUGI_IMPL_STATIC_ASSERT(sizeof(char_t) == sizeof(typename D::type));

		typename T::value_type end = D::process(reinterpret_cast<const typename D::type*>(data), length, dest, T());

		if (opt_swap)
		{
			for (typename T::value_type i = dest; i != end; ++i)
				*i = endian_swap(*i);
		}

		return static_cast<size_t>(end - dest) * sizeof(*dest);
	}

#ifdef PUGIXML_WCHAR_MODE
	PUGI_IMPL_FN size_t get_valid_length(const char_t* data, size_t length)
	{
		if (length < 1) return 0;

		// discard last character if it's the lead of a surrogate pair
		return (sizeof(wchar_t) == 2 && static_cast<unsigned int>(static_cast<uint16_t>(data[length - 1]) - 0xD800) < 0x400) ? length - 1 : length;
	}

	PUGI_IMPL_FN size_t convert_buffer_output(char_t* r_char, uint8_t* r_u8, uint16_t* r_u16, uint32_t* r_u32, const char_t* data, size_t length, xml_encoding encoding)
	{
		// only endian-swapping is required
		if (need_endian_swap_utf(encoding, get_wchar_encoding()))
		{
			convert_wchar_endian_swap(r_char, data, length);

			return length * sizeof(char_t);
		}

		// convert to utf8
		if (encoding == encoding_utf8)
			return convert_buffer_output_generic(r_u8, data, length, wchar_decoder(), utf8_writer());

		// convert to utf16
		if (encoding == encoding_utf16_be || encoding == encoding_utf16_le)
		{
			xml_encoding native_encoding = is_little_endian() ? encoding_utf16_le : encoding_utf16_be;

			return convert_buffer_output_generic(r_u16, data, length, wchar_decoder(), utf16_writer(), native_encoding != encoding);
		}

		// convert to utf32
		if (encoding == encoding_utf32_be || encoding == encoding_utf32_le)
		{
			xml_encoding native_encoding = is_little_endian() ? encoding_utf32_le : encoding_utf32_be;

			return convert_buffer_output_generic(r_u32, data, length, wchar_decoder(), utf32_writer(), native_encoding != encoding);
		}

		// convert to latin1
		if (encoding == encoding_latin1)
			return convert_buffer_output_generic(r_u8, data, length, wchar_decoder(), latin1_writer());

		assert(false && "Invalid encoding"); // unreachable
		return 0;
	}
#else
	PUGI_IMPL_FN size_t get_valid_length(const char_t* data, size_t length)
	{
		if (length < 5) return 0;

		for (size_t i = 1; i <= 4; ++i)
		{
			uint8_t ch = static_cast<uint8_t>(data[length - i]);

			// either a standalone character or a leading one
			if ((ch & 0xc0) != 0x80) return length - i;
		}

		// there are four non-leading characters at the end, sequence tail is broken so might as well process the whole chunk
		return length;
	}

	PUGI_IMPL_FN size_t convert_buffer_output(char_t* /* r_char */, uint8_t* r_u8, uint16_t* r_u16, uint32_t* r_u32, const char_t* data, size_t length, xml_encoding encoding)
	{
		if (encoding == encoding_utf16_be || encoding == encoding_utf16_le)
		{
			xml_encoding native_encoding = is_little_endian() ? encoding_utf16_le : encoding_utf16_be;

			return convert_buffer_output_generic(r_u16, data, length, utf8_decoder(), utf16_writer(), native_encoding != encoding);
		}

		if (encoding == encoding_utf32_be || encoding == encoding_utf32_le)
		{
			xml_encoding native_encoding = is_little_endian() ? encoding_utf32_le : encoding_utf32_be;

			return convert_buffer_output_generic(r_u32, data, length, utf8_decoder(), utf32_writer(), native_encoding != encoding);
		}

		if (encoding == encoding_latin1)
			return convert_buffer_output_generic(r_u8, data, length, utf8_decoder(), latin1_writer());

		assert(false && "Invalid encoding"); // unreachable
		return 0;
	}
#endif

	class xml_buffered_writer
	{
		xml_buffered_writer(const xml_buffered_writer&);
		xml_buffered_writer& operator=(const xml_buffered_writer&);

	public:
		xml_buffered_writer(xml_writer& writer_, xml_encoding user_encoding): writer(writer_), bufsize(0), encoding(get_write_encoding(user_encoding))
		{
			PUGI_IMPL_STATIC_ASSERT(bufcapacity >= 8);
		}

		size_t flush()
		{
			flush(buffer, bufsize);
			bufsize = 0;
			return 0;
		}

		void flush(const char_t* data, size_t size)
		{
			if (size == 0) return;

			// fast path, just write data
			if (encoding == get_write_native_encoding())
				writer.write(data, size * sizeof(char_t));
			else
			{
				// convert chunk
				size_t result = convert_buffer_output(scratch.data_char, scratch.data_u8, scratch.data_u16, scratch.data_u32, data, size, encoding);
				assert(result <= sizeof(scratch));

				// write data
				writer.write(scratch.data_u8, result);
			}
		}

		void write_direct(const char_t* data, size_t length)
		{
			// flush the remaining buffer contents
			flush();

			// handle large chunks
			if (length > bufcapacity)
			{
				if (encoding == get_write_native_encoding())
				{
					// fast path, can just write data chunk
					writer.write(data, length * sizeof(char_t));
					return;
				}

				// need to convert in suitable chunks
				while (length > bufcapacity)
				{
					// get chunk size by selecting such number of characters that are guaranteed to fit into scratch buffer
					// and form a complete codepoint sequence (i.e. discard start of last codepoint if necessary)
					size_t chunk_size = get_valid_length(data, bufcapacity);
					assert(chunk_size);

					// convert chunk and write
					flush(data, chunk_size);

					// iterate
					data += chunk_size;
					length -= chunk_size;
				}

				// small tail is copied below
				bufsize = 0;
			}

			memcpy(buffer + bufsize, data, length * sizeof(char_t));
			bufsize += length;
		}

		void write_buffer(const char_t* data, size_t length)
		{
			size_t offset = bufsize;

			if (offset + length <= bufcapacity)
			{
				memcpy(buffer + offset, data, length * sizeof(char_t));
				bufsize = offset + length;
			}
			else
			{
				write_direct(data, length);
			}
		}

		void write_string(const char_t* data)
		{
			// write the part of the string that fits in the buffer
			size_t offset = bufsize;

			while (*data && offset < bufcapacity)
				buffer[offset++] = *data++;

			// write the rest
			if (offset < bufcapacity)
			{
				bufsize = offset;
			}
			else
			{
				// backtrack a bit if we have split the codepoint
				size_t length = offset - bufsize;
				size_t extra = length - get_valid_length(data - length, length);

				bufsize = offset - extra;

				write_direct(data - extra, strlength(data) + extra);
			}
		}

		void write(char_t d0)
		{
			size_t offset = bufsize;
			if (offset > bufcapacity - 1) offset = flush();

			buffer[offset + 0] = d0;
			bufsize = offset + 1;
		}

		void write(char_t d0, char_t d1)
		{
			size_t offset = bufsize;
			if (offset > bufcapacity - 2) offset = flush();

			buffer[offset + 0] = d0;
			buffer[offset + 1] = d1;
			bufsize = offset + 2;
		}

		void write(char_t d0, char_t d1, char_t d2)
		{
			size_t offset = bufsize;
			if (offset > bufcapacity - 3) offset = flush();

			buffer[offset + 0] = d0;
			buffer[offset + 1] = d1;
			buffer[offset + 2] = d2;
			bufsize = offset + 3;
		}

		void write(char_t d0, char_t d1, char_t d2, char_t d3)
		{
			size_t offset = bufsize;
			if (offset > bufcapacity - 4) offset = flush();

			buffer[offset + 0] = d0;
			buffer[offset + 1] = d1;
			buffer[offset + 2] = d2;
			buffer[offset + 3] = d3;
			bufsize = offset + 4;
		}

		void write(char_t d0, char_t d1, char_t d2, char_t d3, char_t d4)
		{
			size_t offset = bufsize;
			if (offset > bufcapacity - 5) offset = flush();

			buffer[offset + 0] = d0;
			buffer[offset + 1] = d1;
			buffer[offset + 2] = d2;
			buffer[offset + 3] = d3;
			buffer[offset + 4] = d4;
			bufsize = offset + 5;
		}

		void write(char_t d0, char_t d1, char_t d2, char_t d3, char_t d4, char_t d5)
		{
			size_t offset = bufsize;
			if (offset > bufcapacity - 6) offset = flush();

			buffer[offset + 0] = d0;
			buffer[offset + 1] = d1;
			buffer[offset + 2] = d2;
			buffer[offset + 3] = d3;
			buffer[offset + 4] = d4;
			buffer[offset + 5] = d5;
			bufsize = offset + 6;
		}

		// utf8 maximum expansion: x4 (-> utf32)
		// utf16 maximum expansion: x2 (-> utf32)
		// utf32 maximum expansion: x1
		enum
		{
			bufcapacitybytes =
			#ifdef PUGIXML_MEMORY_OUTPUT_STACK
				PUGIXML_MEMORY_OUTPUT_STACK
			#else
				10240
			#endif
			,
			bufcapacity = bufcapacitybytes / (sizeof(char_t) + 4)
		};

		char_t buffer[bufcapacity];

		union
		{
			uint8_t data_u8[4 * bufcapacity];
			uint16_t data_u16[2 * bufcapacity];
			uint32_t data_u32[bufcapacity];
			char_t data_char[bufcapacity];
		} scratch;

		xml_writer& writer;
		size_t bufsize;
		xml_encoding encoding;
	};

	PUGI_IMPL_FN void text_output_escaped(xml_buffered_writer& writer, const char_t* s, chartypex_t type, unsigned int flags)
	{
		while (*s)
		{
			const char_t* prev = s;

			// While *s is a usual symbol
			PUGI_IMPL_SCANWHILE_UNROLL(!PUGI_IMPL_IS_CHARTYPEX(ss, type));

			writer.write_buffer(prev, static_cast<size_t>(s - prev));

			switch (*s)
			{
				case 0: break;
				case '&':
					writer.write('&', 'a', 'm', 'p', ';');
					++s;
					break;
				case '<':
					writer.write('&', 'l', 't', ';');
					++s;
					break;
				case '>':
					writer.write('&', 'g', 't', ';');
					++s;
					break;
				case '"':
					if (flags & format_attribute_single_quote)
						writer.write('"');
					else
						writer.write('&', 'q', 'u', 'o', 't', ';');
					++s;
					break;
				case '\'':
					if (flags & format_attribute_single_quote)
						writer.write('&', 'a', 'p', 'o', 's', ';');
					else
						writer.write('\'');
					++s;
					break;
				default: // s is not a usual symbol
				{
					unsigned int ch = static_cast<unsigned int>(*s++);
					assert(ch < 32);

					if (!(flags & format_skip_control_chars))
						writer.write('&', '#', static_cast<char_t>((ch / 10) + '0'), static_cast<char_t>((ch % 10) + '0'), ';');
				}
			}
		}
	}

	PUGI_IMPL_FN void text_output(xml_buffered_writer& writer, const char_t* s, chartypex_t type, unsigned int flags)
	{
		if (flags & format_no_escapes)
			writer.write_string(s);
		else
			text_output_escaped(writer, s, type, flags);
	}

	PUGI_IMPL_FN void text_output_cdata(xml_buffered_writer& writer, const char_t* s)
	{
		do
		{
			writer.write('<', '!', '[', 'C', 'D');
			writer.write('A', 'T', 'A', '[');

			const char_t* prev = s;

			// look for ]]> sequence - we can't output it as is since it terminates CDATA
			while (*s && !(s[0] == ']' && s[1] == ']' && s[2] == '>')) ++s;

			// skip ]] if we stopped at ]]>, > will go to the next CDATA section
			if (*s) s += 2;

			writer.write_buffer(prev, static_cast<size_t>(s - prev));

			writer.write(']', ']', '>');
		}
		while (*s);
	}

	PUGI_IMPL_FN void text_output_indent(xml_buffered_writer& writer, const char_t* indent, size_t indent_length, unsigned int depth)
	{
		switch (indent_length)
		{
		case 1:
		{
			for (unsigned int i = 0; i < depth; ++i)
				writer.write(indent[0]);
			break;
		}

		case 2:
		{
			for (unsigned int i = 0; i < depth; ++i)
				writer.write(indent[0], indent[1]);
			break;
		}

		case 3:
		{
			for (unsigned int i = 0; i < depth; ++i)
				writer.write(indent[0], indent[1], indent[2]);
			break;
		}

		case 4:
		{
			for (unsigned int i = 0; i < depth; ++i)
				writer.write(indent[0], indent[1], indent[2], indent[3]);
			break;
		}

		default:
		{
			for (unsigned int i = 0; i < depth; ++i)
				writer.write_buffer(indent, indent_length);
		}
		}
	}

	PUGI_IMPL_FN void node_output_comment(xml_buffered_writer& writer, const char_t* s)
	{
		writer.write('<', '!', '-', '-');

		while (*s)
		{
			const char_t* prev = s;

			// look for -\0 or -- sequence - we can't output it since -- is illegal in comment body
			while (*s && !(s[0] == '-' && (s[1] == '-' || s[1] == 0))) ++s;

			writer.write_buffer(prev, static_cast<size_t>(s - prev));

			if (*s)
			{
				assert(*s == '-');

				writer.write('-', ' ');
				++s;
			}
		}

		writer.write('-', '-', '>');
	}

	PUGI_IMPL_FN void node_output_pi_value(xml_buffered_writer& writer, const char_t* s)
	{
		while (*s)
		{
			const char_t* prev = s;

			// look for ?> sequence - we can't output it since ?> terminates PI
			while (*s && !(s[0] == '?' && s[1] == '>')) ++s;

			writer.write_buffer(prev, static_cast<size_t>(s - prev));

			if (*s)
			{
				assert(s[0] == '?' && s[1] == '>');

				writer.write('?', ' ', '>');
				s += 2;
			}
		}
	}

	PUGI_IMPL_FN void node_output_attributes(xml_buffered_writer& writer, xml_node_struct* node, const char_t* indent, size_t indent_length, unsigned int flags, unsigned int depth)
	{
		const char_t* default_name = PUGIXML_TEXT(":anonymous");
		const char_t enquotation_char = (flags & format_attribute_single_quote) ? '\'' : '"';

		for (xml_attribute_struct* a = node->first_attribute; a; a = a->next_attribute)
		{
			if ((flags & (format_indent_attributes | format_raw)) == format_indent_attributes)
			{
				writer.write('\n');

				text_output_indent(writer, indent, indent_length, depth + 1);
			}
			else
			{
				writer.write(' ');
			}

			writer.write_string(a->name ? a->name + 0 : default_name);
			writer.write('=', enquotation_char);

			if (a->value)
				text_output(writer, a->value, ctx_special_attr, flags);

			writer.write(enquotation_char);
		}
	}

	PUGI_IMPL_FN bool node_output_start(xml_buffered_writer& writer, xml_node_struct* node, const char_t* indent, size_t indent_length, unsigned int flags, unsigned int depth)
	{
		const char_t* default_name = PUGIXML_TEXT(":anonymous");
		const char_t* name = node->name ? node->name + 0 : default_name;

		writer.write('<');
		writer.write_string(name);

		if (node->first_attribute)
			node_output_attributes(writer, node, indent, indent_length, flags, depth);

		// element nodes can have value if parse_embed_pcdata was used
		if (!node->value)
		{
			if (!node->first_child)
			{
				if (flags & format_no_empty_element_tags)
				{
					writer.write('>', '<', '/');
					writer.write_string(name);
					writer.write('>');

					return false;
				}
				else
				{
					if ((flags & format_raw) == 0)
						writer.write(' ');

					writer.write('/', '>');

					return false;
				}
			}
			else
			{
				writer.write('>');

				return true;
			}
		}
		else
		{
			writer.write('>');

			text_output(writer, node->value, ctx_special_pcdata, flags);

			if (!node->first_child)
			{
				writer.write('<', '/');
				writer.write_string(name);
				writer.write('>');

				return false;
			}
			else
			{
				return true;
			}
		}
	}

	PUGI_IMPL_FN void node_output_end(xml_buffered_writer& writer, xml_node_struct* node)
	{
		const char_t* default_name = PUGIXML_TEXT(":anonymous");
		const char_t* name = node->name ? node->name + 0 : default_name;

		writer.write('<', '/');
		writer.write_string(name);
		writer.write('>');
	}

	PUGI_IMPL_FN void node_output_simple(xml_buffered_writer& writer, xml_node_struct* node, unsigned int flags)
	{
		const char_t* default_name = PUGIXML_TEXT(":anonymous");

		switch (PUGI_IMPL_NODETYPE(node))
		{
			case node_pcdata:
				text_output(writer, node->value ? node->value + 0 : PUGIXML_TEXT(""), ctx_special_pcdata, flags);
				break;

			case node_cdata:
				text_output_cdata(writer, node->value ? node->value + 0 : PUGIXML_TEXT(""));
				break;

			case node_comment:
				node_output_comment(writer, node->value ? node->value + 0 : PUGIXML_TEXT(""));
				break;

			case node_pi:
				writer.write('<', '?');
				writer.write_string(node->name ? node->name + 0 : default_name);

				if (node->value)
				{
					writer.write(' ');
					node_output_pi_value(writer, node->value);
				}

				writer.write('?', '>');
				break;

			case node_declaration:
				writer.write('<', '?');
				writer.write_string(node->name ? node->name + 0 : default_name);
				node_output_attributes(writer, node, PUGIXML_TEXT(""), 0, flags | format_raw, 0);
				writer.write('?', '>');
				break;

			case node_doctype:
				writer.write('<', '!', 'D', 'O', 'C');
				writer.write('T', 'Y', 'P', 'E');

				if (node->value)
				{
					writer.write(' ');
					writer.write_string(node->value);
				}

				writer.write('>');
				break;

			default:
				assert(false && "Invalid node type"); // unreachable
		}
	}

	enum indent_flags_t
	{
		indent_newline = 1,
		indent_indent = 2
	};

	PUGI_IMPL_FN void node_output(xml_buffered_writer& writer, xml_node_struct* root, const char_t* indent, unsigned int flags, unsigned int depth)
	{
		size_t indent_length = ((flags & (format_indent | format_indent_attributes)) && (flags & format_raw) == 0) ? strlength(indent) : 0;
		unsigned int indent_flags = indent_indent;

		xml_node_struct* node = root;

		do
		{
			assert(node);

			// begin writing current node
			if (PUGI_IMPL_NODETYPE(node) == node_pcdata || PUGI_IMPL_NODETYPE(node) == node_cdata)
			{
				node_output_simple(writer, node, flags);

				indent_flags = 0;
			}
			else
			{
				if ((indent_flags & indent_newline) && (flags & format_raw) == 0)
					writer.write('\n');

				if ((indent_flags & indent_indent) && indent_length)
					text_output_indent(writer, indent, indent_length, depth);

				if (PUGI_IMPL_NODETYPE(node) == node_element)
				{
					indent_flags = indent_newline | indent_indent;

					if (node_output_start(writer, node, indent, indent_length, flags, depth))
					{
						// element nodes can have value if parse_embed_pcdata was used
						if (node->value)
							indent_flags = 0;

						node = node->first_child;
						depth++;
						continue;
					}
				}
				else if (PUGI_IMPL_NODETYPE(node) == node_document)
				{
					indent_flags = indent_indent;

					if (node->first_child)
					{
						node = node->first_child;
						continue;
					}
				}
				else
				{
					node_output_simple(writer, node, flags);

					indent_flags = indent_newline | indent_indent;
				}
			}

			// continue to the next node
			while (node != root)
			{
				if (node->next_sibling)
				{
					node = node->next_sibling;
					break;
				}

				node = node->parent;

				// write closing node
				if (PUGI_IMPL_NODETYPE(node) == node_element)
				{
					depth--;

					if ((indent_flags & indent_newline) && (flags & format_raw) == 0)
						writer.write('\n');

					if ((indent_flags & indent_indent) && indent_length)
						text_output_indent(writer, indent, indent_length, depth);

					node_output_end(writer, node);

					indent_flags = indent_newline | indent_indent;
				}
			}
		}
		while (node != root);

		if ((indent_flags & indent_newline) && (flags & format_raw) == 0)
			writer.write('\n');
	}

	PUGI_IMPL_FN bool has_declaration(xml_node_struct* node)
	{
		for (xml_node_struct* child = node->first_child; child; child = child->next_sibling)
		{
			xml_node_type type = PUGI_IMPL_NODETYPE(child);

			if (type == node_declaration) return true;
			if (type == node_element) return false;
		}

		return false;
	}

	PUGI_IMPL_FN bool is_attribute_of(xml_attribute_struct* attr, xml_node_struct* node)
	{
		for (xml_attribute_struct* a = node->first_attribute; a; a = a->next_attribute)
			if (a == attr)
				return true;

		return false;
	}

	PUGI_IMPL_FN bool allow_insert_attribute(xml_node_type parent)
	{
		return parent == node_element || parent == node_declaration;
	}

	PUGI_IMPL_FN bool allow_insert_child(xml_node_type parent, xml_node_type child)
	{
		if (parent != node_document && parent != node_element) return false;
		if (child == node_document || child == node_null) return false;
		if (parent != node_document && (child == node_declaration || child == node_doctype)) return false;

		return true;
	}

	PUGI_IMPL_FN bool allow_move(xml_node parent, xml_node child)
	{
		// check that child can be a child of parent
		if (!allow_insert_child(parent.type(), child.type()))
			return false;

		// check that node is not moved between documents
		if (parent.root() != child.root())
			return false;

		// check that new parent is not in the child subtree
		xml_node cur = parent;

		while (cur)
		{
			if (cur == child)
				return false;

			cur = cur.parent();
		}

		return true;
	}

	template <typename String, typename Header>
	PUGI_IMPL_FN void node_copy_string(String& dest, Header& header, uintptr_t header_mask, char_t* source, Header& source_header, xml_allocator* alloc)
	{
		assert(!dest && (header & header_mask) == 0); // copies are performed into fresh nodes

		if (source)
		{
			if (alloc && (source_header & header_mask) == 0)
			{
				dest = source;

				// since strcpy_insitu can reuse document buffer memory we need to mark both source and dest as shared
				header |= xml_memory_page_contents_shared_mask;
				source_header |= xml_memory_page_contents_shared_mask;
			}
			else
			{
				// if strcpy_insitu fails (out of memory) we just leave the destination name/value empty
				(void)strcpy_insitu(dest, header, header_mask, source, strlength(source));
			}
		}
	}

	PUGI_IMPL_FN void node_copy_contents(xml_node_struct* dn, xml_node_struct* sn, xml_allocator* shared_alloc)
	{
		node_copy_string(dn->name, dn->header, xml_memory_page_name_allocated_mask, sn->name, sn->header, shared_alloc);
		node_copy_string(dn->value, dn->header, xml_memory_page_value_allocated_mask, sn->value, sn->header, shared_alloc);

		for (xml_attribute_struct* sa = sn->first_attribute; sa; sa = sa->next_attribute)
		{
			xml_attribute_struct* da = append_new_attribute(dn, get_allocator(dn));

			if (da)
			{
				node_copy_string(da->name, da->header, xml_memory_page_name_allocated_mask, sa->name, sa->header, shared_alloc);
				node_copy_string(da->value, da->header, xml_memory_page_value_allocated_mask, sa->value, sa->header, shared_alloc);
			}
		}
	}

	PUGI_IMPL_FN void node_copy_tree(xml_node_struct* dn, xml_node_struct* sn)
	{
		xml_allocator& alloc = get_allocator(dn);
		xml_allocator* shared_alloc = (&alloc == &get_allocator(sn)) ? &alloc : NULL;

		node_copy_contents(dn, sn, shared_alloc);

		xml_node_struct* dit = dn;
		xml_node_struct* sit = sn->first_child;

		while (sit && sit != sn)
		{
			// loop invariant: dit is inside the subtree rooted at dn
			assert(dit);

			// when a tree is copied into one of the descendants, we need to skip that subtree to avoid an infinite loop
			if (sit != dn)
			{
				xml_node_struct* copy = append_new_node(dit, alloc, PUGI_IMPL_NODETYPE(sit));

				if (copy)
				{
					node_copy_contents(copy, sit, shared_alloc);

					if (sit->first_child)
					{
						dit = copy;
						sit = sit->first_child;
						continue;
					}
				}
			}

			// continue to the next node
			do
			{
				if (sit->next_sibling)
				{
					sit = sit->next_sibling;
					break;
				}

				sit = sit->parent;
				dit = dit->parent;

				// loop invariant: dit is inside the subtree rooted at dn while sit is inside sn
				assert(sit == sn || dit);
			}
			while (sit != sn);
		}

		assert(!sit || dit == dn->parent);
	}

	PUGI_IMPL_FN void node_copy_attribute(xml_attribute_struct* da, xml_attribute_struct* sa)
	{
		xml_allocator& alloc = get_allocator(da);
		xml_allocator* shared_alloc = (&alloc == &get_allocator(sa)) ? &alloc : NULL;

		node_copy_string(da->name, da->header, xml_memory_page_name_allocated_mask, sa->name, sa->header, shared_alloc);
		node_copy_string(da->value, da->header, xml_memory_page_value_allocated_mask, sa->value, sa->header, shared_alloc);
	}

	inline bool is_text_node(xml_node_struct* node)
	{
		xml_node_type type = PUGI_IMPL_NODETYPE(node);

		return type == node_pcdata || type == node_cdata;
	}

	// get value with conversion functions
	template <typename U> PUGI_IMPL_FN PUGI_IMPL_UNSIGNED_OVERFLOW U string_to_integer(const char_t* value, U minv, U maxv)
	{
		U result = 0;
		const char_t* s = value;

		while (PUGI_IMPL_IS_CHARTYPE(*s, ct_space))
			s++;

		bool negative = (*s == '-');

		s += (*s == '+' || *s == '-');

		bool overflow = false;

		if (s[0] == '0' && (s[1] | ' ') == 'x')
		{
			s += 2;

			// since overflow detection relies on length of the sequence skip leading zeros
			while (*s == '0')
				s++;

			const char_t* start = s;

			for (;;)
			{
				if (static_cast<unsigned>(*s - '0') < 10)
					result = result * 16 + (*s - '0');
				else if (static_cast<unsigned>((*s | ' ') - 'a') < 6)
					result = result * 16 + ((*s | ' ') - 'a' + 10);
				else
					break;

				s++;
			}

			size_t digits = static_cast<size_t>(s - start);

			overflow = digits > sizeof(U) * 2;
		}
		else
		{
			// since overflow detection relies on length of the sequence skip leading zeros
			while (*s == '0')
				s++;

			const char_t* start = s;

			for (;;)
			{
				if (static_cast<unsigned>(*s - '0') < 10)
					result = result * 10 + (*s - '0');
				else
					break;

				s++;
			}

			size_t digits = static_cast<size_t>(s - start);

			PUGI_IMPL_STATIC_ASSERT(sizeof(U) == 8 || sizeof(U) == 4 || sizeof(U) == 2);

			const size_t max_digits10 = sizeof(U) == 8 ? 20 : sizeof(U) == 4 ? 10 : 5;
			const char_t max_lead = sizeof(U) == 8 ? '1' : sizeof(U) == 4 ? '4' : '6';
			const size_t high_bit = sizeof(U) * 8 - 1;

			overflow = digits >= max_digits10 && !(digits == max_digits10 && (*start < max_lead || (*start == max_lead && result >> high_bit)));
		}

		if (negative)
		{
			// Workaround for crayc++ CC-3059: Expected no overflow in routine.
		#ifdef _CRAYC
			return (overflow || result > ~minv + 1) ? minv : ~result + 1;
		#else
			return (overflow || result > 0 - minv) ? minv : 0 - result;
		#endif
		}
		else
			return (overflow || result > maxv) ? maxv : result;
	}

	PUGI_IMPL_FN int get_value_int(const char_t* value)
	{
		return string_to_integer<unsigned int>(value, static_cast<unsigned int>(INT_MIN), INT_MAX);
	}

	PUGI_IMPL_FN unsigned int get_value_uint(const char_t* value)
	{
		return string_to_integer<unsigned int>(value, 0, UINT_MAX);
	}

	PUGI_IMPL_FN double get_value_double(const char_t* value)
	{
	#ifdef PUGIXML_WCHAR_MODE
		return wcstod(value, NULL);
	#else
		return strtod(value, NULL);
	#endif
	}

	PUGI_IMPL_FN float get_value_float(const char_t* value)
	{
	#ifdef PUGIXML_WCHAR_MODE
		return static_cast<float>(wcstod(value, NULL));
	#else
		return static_cast<float>(strtod(value, NULL));
	#endif
	}

	PUGI_IMPL_FN bool get_value_bool(const char_t* value)
	{
		// only look at first char
		char_t first = *value;

		// 1*, t* (true), T* (True), y* (yes), Y* (YES)
		return (first == '1' || first == 't' || first == 'T' || first == 'y' || first == 'Y');
	}

#ifdef PUGIXML_HAS_LONG_LONG
	PUGI_IMPL_FN long long get_value_llong(const char_t* value)
	{
		return string_to_integer<unsigned long long>(value, static_cast<unsigned long long>(LLONG_MIN), LLONG_MAX);
	}

	PUGI_IMPL_FN unsigned long long get_value_ullong(const char_t* value)
	{
		return string_to_integer<unsigned long long>(value, 0, ULLONG_MAX);
	}
#endif

	template <typename U> PUGI_IMPL_FN PUGI_IMPL_UNSIGNED_OVERFLOW char_t* integer_to_string(char_t* begin, char_t* end, U value, bool negative)
	{
		char_t* result = end - 1;
		U rest = negative ? 0 - value : value;

		do
		{
			*result-- = static_cast<char_t>('0' + (rest % 10));
			rest /= 10;
		}
		while (rest);

		assert(result >= begin);
		(void)begin;

		*result = '-';

		return result + !negative;
	}

	// set value with conversion functions
	template <typename String, typename Header>
	PUGI_IMPL_FN bool set_value_ascii(String& dest, Header& header, uintptr_t header_mask, char* buf)
	{
	#ifdef PUGIXML_WCHAR_MODE
		char_t wbuf[128];
		assert(strlen(buf) < sizeof(wbuf) / sizeof(wbuf[0]));

		size_t offset = 0;
		for (; buf[offset]; ++offset) wbuf[offset] = buf[offset];

		return strcpy_insitu(dest, header, header_mask, wbuf, offset);
	#else
		return strcpy_insitu(dest, header, header_mask, buf, strlen(buf));
	#endif
	}

	template <typename U, typename String, typename Header>
	PUGI_IMPL_FN bool set_value_integer(String& dest, Header& header, uintptr_t header_mask, U value, bool negative)
	{
		char_t buf[64];
		char_t* end = buf + sizeof(buf) / sizeof(buf[0]);
		char_t* begin = integer_to_string(buf, end, value, negative);

		return strcpy_insitu(dest, header, header_mask, begin, end - begin);
	}

	template <typename String, typename Header>
	PUGI_IMPL_FN bool set_value_convert(String& dest, Header& header, uintptr_t header_mask, float value, int precision)
	{
		char buf[128];
		PUGI_IMPL_SNPRINTF(buf, "%.*g", precision, double(value));

		return set_value_ascii(dest, header, header_mask, buf);
	}

	template <typename String, typename Header>
	PUGI_IMPL_FN bool set_value_convert(String& dest, Header& header, uintptr_t header_mask, double value, int precision)
	{
		char buf[128];
		PUGI_IMPL_SNPRINTF(buf, "%.*g", precision, value);

		return set_value_ascii(dest, header, header_mask, buf);
	}

	template <typename String, typename Header>
	PUGI_IMPL_FN bool set_value_bool(String& dest, Header& header, uintptr_t header_mask, bool value)
	{
		return strcpy_insitu(dest, header, header_mask, value ? PUGIXML_TEXT("true") : PUGIXML_TEXT("false"), value ? 4 : 5);
	}

	PUGI_IMPL_FN xml_parse_result load_buffer_impl(xml_document_struct* doc, xml_node_struct* root, void* contents, size_t size, unsigned int options, xml_encoding encoding, bool is_mutable, bool own, char_t** out_buffer)
	{
		// check input buffer
		if (!contents && size) return make_parse_result(status_io_error);

		// get actual encoding
		xml_encoding buffer_encoding = impl::get_buffer_encoding(encoding, contents, size);

		// if convert_buffer below throws bad_alloc, we still need to deallocate contents if we own it
		auto_deleter<void> contents_guard(own ? contents : NULL, xml_memory::deallocate);

		// early-out for empty documents to avoid buffer allocation overhead
		if (size == 0) return make_parse_result((options & parse_fragment) ? status_ok : status_no_document_element);

		// get private buffer
		char_t* buffer = NULL;
		size_t length = 0;

		if (!impl::convert_buffer(buffer, length, buffer_encoding, contents, size, is_mutable)) return impl::make_parse_result(status_out_of_memory);

		// after this we either deallocate contents (below) or hold on to it via doc->buffer, so we don't need to guard it
		contents_guard.release();

		// delete original buffer if we performed a conversion
		if (own && buffer != contents && contents) impl::xml_memory::deallocate(contents);

		// grab onto buffer if it's our buffer, user is responsible for deallocating contents himself
		if (own || buffer != contents) *out_buffer = buffer;

		// store buffer for offset_debug
		doc->buffer = buffer;

		// parse
		xml_parse_result res = impl::xml_parser::parse(buffer, length, doc, root, options);

		// remember encoding
		res.encoding = buffer_encoding;

		return res;
	}

	template <typename T> PUGI_IMPL_FN xml_parse_status convert_file_size(T length, size_t& out_result)
	{
		// check for I/O errors
		if (length < 0) return status_io_error;

		// check for overflow
		size_t result = static_cast<size_t>(length);

		if (static_cast<T>(result) != length) return status_out_of_memory;

		out_result = result;
		return status_ok;
	}

	// we need to get length of entire file to load it in memory; the only (relatively) sane way to do it is via seek/tell trick
	PUGI_IMPL_FN xml_parse_status get_file_size(FILE* file, size_t& out_result)
	{
	#if defined(__linux__) || defined(__APPLE__)
		// this simultaneously retrieves the file size and file mode (to guard against loading non-files)
		struct stat st;
		if (fstat(fileno(file), &st) != 0) return status_io_error;

		// anything that's not a regular file doesn't have a coherent length
		if (!S_ISREG(st.st_mode)) return status_io_error;

		xml_parse_status status = convert_file_size(st.st_size, out_result);
	#elif defined(PUGI_IMPL_MSVC_CRT_VERSION) && PUGI_IMPL_MSVC_CRT_VERSION >= 1400
		// there are 64-bit versions of fseek/ftell, let's use them
		_fseeki64(file, 0, SEEK_END);
		__int64 length = _ftelli64(file);
		_fseeki64(file, 0, SEEK_SET);

		xml_parse_status status = convert_file_size(length, out_result);
	#elif defined(__MINGW32__) && !defined(__NO_MINGW_LFS) && (!defined(__STRICT_ANSI__) || defined(__MINGW64_VERSION_MAJOR))
		// there are 64-bit versions of fseek/ftell, let's use them
		fseeko64(file, 0, SEEK_END);
		off64_t length = ftello64(file);
		fseeko64(file, 0, SEEK_SET);

		xml_parse_status status = convert_file_size(length, out_result);
	#else
		// if this is a 32-bit OS, long is enough; if this is a unix system, long is 64-bit, which is enough; otherwise we can't do anything anyway.
		fseek(file, 0, SEEK_END);
		long length = ftell(file);
		fseek(file, 0, SEEK_SET);

		xml_parse_status status = convert_file_size(length, out_result);
	#endif

		return status;
	}

	// This function assumes that buffer has extra sizeof(char_t) writable bytes after size
	PUGI_IMPL_FN size_t zero_terminate_buffer(void* buffer, size_t size, xml_encoding encoding)
	{
		// We only need to zero-terminate if encoding conversion does not do it for us
	#ifdef PUGIXML_WCHAR_MODE
		xml_encoding wchar_encoding = get_wchar_encoding();

		if (encoding == wchar_encoding || need_endian_swap_utf(encoding, wchar_encoding))
		{
			size_t length = size / sizeof(char_t);

			static_cast<char_t*>(buffer)[length] = 0;
			return (length + 1) * sizeof(char_t);
		}
	#else
		if (encoding == encoding_utf8)
		{
			static_cast<char*>(buffer)[size] = 0;
			return size + 1;
		}
	#endif

		return size;
	}

	PUGI_IMPL_FN xml_parse_result load_file_impl(xml_document_struct* doc, FILE* file, unsigned int options, xml_encoding encoding, char_t** out_buffer)
	{
		if (!file) return make_parse_result(status_file_not_found);

		// get file size (can result in I/O errors)
		size_t size = 0;
		xml_parse_status size_status = get_file_size(file, size);
		if (size_status != status_ok) return make_parse_result(size_status);

		size_t max_suffix_size = sizeof(char_t);

		// allocate buffer for the whole file
		char* contents = static_cast<char*>(xml_memory::allocate(size + max_suffix_size));
		if (!contents) return make_parse_result(status_out_of_memory);

		// read file in memory
		size_t read_size = fread(contents, 1, size, file);

		if (read_size != size)
		{
			xml_memory::deallocate(contents);
			return make_parse_result(status_io_error);
		}

		xml_encoding real_encoding = get_buffer_encoding(encoding, contents, size);

		return load_buffer_impl(doc, doc, contents, zero_terminate_buffer(contents, size, real_encoding), options, real_encoding, true, true, out_buffer);
	}

	PUGI_IMPL_FN void close_file(FILE* file)
	{
		fclose(file);
	}

#ifndef PUGIXML_NO_STL
	template <typename T> struct xml_stream_chunk
	{
		static xml_stream_chunk* create()
		{
			void* memory = xml_memory::allocate(sizeof(xml_stream_chunk));
			if (!memory) return NULL;

			return new (memory) xml_stream_chunk();
		}

		static void destroy(xml_stream_chunk* chunk)
		{
			// free chunk chain
			while (chunk)
			{
				xml_stream_chunk* next_ = chunk->next;

				xml_memory::deallocate(chunk);

				chunk = next_;
			}
		}

		xml_stream_chunk(): next(NULL), size(0)
		{
		}

		xml_stream_chunk* next;
		size_t size;

		T data[xml_memory_page_size / sizeof(T)];
	};

	template <typename T> PUGI_IMPL_FN xml_parse_status load_stream_data_noseek(std::basic_istream<T>& stream, void** out_buffer, size_t* out_size)
	{
		auto_deleter<xml_stream_chunk<T> > chunks(NULL, xml_stream_chunk<T>::destroy);

		// read file to a chunk list
		size_t total = 0;
		xml_stream_chunk<T>* last = NULL;

		while (!stream.eof())
		{
			// allocate new chunk
			xml_stream_chunk<T>* chunk = xml_stream_chunk<T>::create();
			if (!chunk) return status_out_of_memory;

			// append chunk to list
			if (last) last = last->next = chunk;
			else chunks.data = last = chunk;

			// read data to chunk
			stream.read(chunk->data, static_cast<std::streamsize>(sizeof(chunk->data) / sizeof(T)));
			chunk->size = static_cast<size_t>(stream.gcount()) * sizeof(T);

			// read may set failbit | eofbit in case gcount() is less than read length, so check for other I/O errors
			if (stream.bad() || (!stream.eof() && stream.fail())) return status_io_error;

			// guard against huge files (chunk size is small enough to make this overflow check work)
			if (total + chunk->size < total) return status_out_of_memory;
			total += chunk->size;
		}

		size_t max_suffix_size = sizeof(char_t);

		// copy chunk list to a contiguous buffer
		char* buffer = static_cast<char*>(xml_memory::allocate(total + max_suffix_size));
		if (!buffer) return status_out_of_memory;

		char* write = buffer;

		for (xml_stream_chunk<T>* chunk = chunks.data; chunk; chunk = chunk->next)
		{
			assert(write + chunk->size <= buffer + total);
			memcpy(write, chunk->data, chunk->size);
			write += chunk->size;
		}

		assert(write == buffer + total);

		// return buffer
		*out_buffer = buffer;
		*out_size = total;

		return status_ok;
	}

	template <typename T> PUGI_IMPL_FN xml_parse_status load_stream_data_seek(std::basic_istream<T>& stream, void** out_buffer, size_t* out_size)
	{
		// get length of remaining data in stream
		typename std::basic_istream<T>::pos_type pos = stream.tellg();
		stream.seekg(0, std::ios::end);
		std::streamoff length = stream.tellg() - pos;
		stream.seekg(pos);

		if (stream.fail() || pos < 0) return status_io_error;

		// guard against huge files
		size_t read_length = static_cast<size_t>(length);

		if (static_cast<std::streamsize>(read_length) != length || length < 0) return status_out_of_memory;

		size_t max_suffix_size = sizeof(char_t);

		// read stream data into memory (guard against stream exceptions with buffer holder)
		auto_deleter<void> buffer(xml_memory::allocate(read_length * sizeof(T) + max_suffix_size), xml_memory::deallocate);
		if (!buffer.data) return status_out_of_memory;

		stream.read(static_cast<T*>(buffer.data), static_cast<std::streamsize>(read_length));

		// read may set failbit | eofbit in case gcount() is less than read_length (i.e. line ending conversion), so check for other I/O errors
		if (stream.bad() || (!stream.eof() && stream.fail())) return status_io_error;

		// return buffer
		size_t actual_length = static_cast<size_t>(stream.gcount());
		assert(actual_length <= read_length);

		*out_buffer = buffer.release();
		*out_size = actual_length * sizeof(T);

		return status_ok;
	}

	template <typename T> PUGI_IMPL_FN xml_parse_result load_stream_impl(xml_document_struct* doc, std::basic_istream<T>& stream, unsigned int options, xml_encoding encoding, char_t** out_buffer)
	{
		void* buffer = NULL;
		size_t size = 0;
		xml_parse_status status = status_ok;

		// if stream has an error bit set, bail out (otherwise tellg() can fail and we'll clear error bits)
		if (stream.fail()) return make_parse_result(status_io_error);

		// load stream to memory (using seek-based implementation if possible, since it's faster and takes less memory)
		if (stream.tellg() < 0)
		{
			stream.clear(); // clear error flags that could be set by a failing tellg
			status = load_stream_data_noseek(stream, &buffer, &size);
		}
		else
			status = load_stream_data_seek(stream, &buffer, &size);

		if (status != status_ok) return make_parse_result(status);

		xml_encoding real_encoding = get_buffer_encoding(encoding, buffer, size);

		return load_buffer_impl(doc, doc, buffer, zero_terminate_buffer(buffer, size, real_encoding), options, real_encoding, true, true, out_buffer);
	}
#endif

#if defined(PUGI_IMPL_MSVC_CRT_VERSION) || defined(__BORLANDC__) || (defined(__MINGW32__) && (!defined(__STRICT_ANSI__) || defined(__MINGW64_VERSION_MAJOR)))
	PUGI_IMPL_FN FILE* open_file_wide(const wchar_t* path, const wchar_t* mode)
	{
#ifdef PUGIXML_NO_STL
		// ensure these symbols are consistently referenced to avoid 'unreferenced function' warnings
		// note that generally these functions are used in STL builds, but PUGIXML_NO_STL leaves the only usage in convert_path_heap
		(void)&as_utf8_begin;
		(void)&as_utf8_end;
		(void)&strlength_wide;
#endif

#if defined(PUGI_IMPL_MSVC_CRT_VERSION) && PUGI_IMPL_MSVC_CRT_VERSION >= 1400
		FILE* file = NULL;
		return _wfopen_s(&file, path, mode) == 0 ? file : NULL;
#else
		return _wfopen(path, mode);
#endif
	}
#else
	PUGI_IMPL_FN char* convert_path_heap(const wchar_t* str)
	{
		assert(str);

		// first pass: get length in utf8 characters
		size_t length = strlength_wide(str);
		size_t size = as_utf8_begin(str, length);

		// allocate resulting string
		char* result = static_cast<char*>(xml_memory::allocate(size + 1));
		if (!result) return NULL;

		// second pass: convert to utf8
		as_utf8_end(result, size, str, length);

		// zero-terminate
		result[size] = 0;

		return result;
	}

	PUGI_IMPL_FN FILE* open_file_wide(const wchar_t* path, const wchar_t* mode)
	{
		// there is no standard function to open wide paths, so our best bet is to try utf8 path
		char* path_utf8 = convert_path_heap(path);
		if (!path_utf8) return NULL;

		// convert mode to ASCII (we mirror _wfopen interface)
		char mode_ascii[4] = {0};
		for (size_t i = 0; mode[i]; ++i) mode_ascii[i] = static_cast<char>(mode[i]);

		// try to open the utf8 path
		FILE* result = fopen(path_utf8, mode_ascii);

		// free dummy buffer
		xml_memory::deallocate(path_utf8);

		return result;
	}
#endif

	PUGI_IMPL_FN FILE* open_file(const char* path, const char* mode)
	{
#if defined(PUGI_IMPL_MSVC_CRT_VERSION) && PUGI_IMPL_MSVC_CRT_VERSION >= 1400
		FILE* file = NULL;
		return fopen_s(&file, path, mode) == 0 ? file : NULL;
#else
		return fopen(path, mode);
#endif
	}

	PUGI_IMPL_FN bool save_file_impl(const xml_document& doc, FILE* file, const char_t* indent, unsigned int flags, xml_encoding encoding)
	{
		if (!file) return false;

		xml_writer_file writer(file);
		doc.save(writer, indent, flags, encoding);

		return fflush(file) == 0 && ferror(file) == 0;
	}

	struct name_null_sentry
	{
		xml_node_struct* node;
		char_t* name;

		name_null_sentry(xml_node_struct* node_): node(node_), name(node_->name)
		{
			node->name = NULL;
		}

		~name_null_sentry()
		{
			node->name = name;
		}
	};
PUGI_IMPL_NS_END

namespace pugi
{
	PUGI_IMPL_FN xml_writer::~xml_writer()
	{
	}

	PUGI_IMPL_FN xml_writer_file::xml_writer_file(void* file_): file(file_)
	{
	}

	PUGI_IMPL_FN void xml_writer_file::write(const void* data, size_t size)
	{
		size_t result = fwrite(data, 1, size, static_cast<FILE*>(file));
		(void)!result; // unfortunately we can't do proper error handling here
	}

#ifndef PUGIXML_NO_STL
	PUGI_IMPL_FN xml_writer_stream::xml_writer_stream(std::basic_ostream<char>& stream): narrow_stream(&stream), wide_stream(NULL)
	{
	}

	PUGI_IMPL_FN xml_writer_stream::xml_writer_stream(std::basic_ostream<wchar_t>& stream): narrow_stream(NULL), wide_stream(&stream)
	{
	}

	PUGI_IMPL_FN void xml_writer_stream::write(const void* data, size_t size)
	{
		if (narrow_stream)
		{
			assert(!wide_stream);
			narrow_stream->write(reinterpret_cast<const char*>(data), static_cast<std::streamsize>(size));
		}
		else
		{
			assert(wide_stream);
			assert(size % sizeof(wchar_t) == 0);

			wide_stream->write(reinterpret_cast<const wchar_t*>(data), static_cast<std::streamsize>(size / sizeof(wchar_t)));
		}
	}
#endif

	PUGI_IMPL_FN xml_tree_walker::xml_tree_walker(): _depth(0)
	{
	}

	PUGI_IMPL_FN xml_tree_walker::~xml_tree_walker()
	{
	}

	PUGI_IMPL_FN int xml_tree_walker::depth() const
	{
		return _depth;
	}

	PUGI_IMPL_FN bool xml_tree_walker::begin(xml_node&)
	{
		return true;
	}

	PUGI_IMPL_FN bool xml_tree_walker::end(xml_node&)
	{
		return true;
	}

	PUGI_IMPL_FN xml_attribute::xml_attribute(): _attr(NULL)
	{
	}

	PUGI_IMPL_FN xml_attribute::xml_attribute(xml_attribute_struct* attr): _attr(attr)
	{
	}

	PUGI_IMPL_FN static void unspecified_bool_xml_attribute(xml_attribute***)
	{
	}

	PUGI_IMPL_FN xml_attribute::operator xml_attribute::unspecified_bool_type() const
	{
		return _attr ? unspecified_bool_xml_attribute : NULL;
	}

	PUGI_IMPL_FN bool xml_attribute::operator!() const
	{
		return !_attr;
	}

	PUGI_IMPL_FN bool xml_attribute::operator==(const xml_attribute& r) const
	{
		return (_attr == r._attr);
	}

	PUGI_IMPL_FN bool xml_attribute::operator!=(const xml_attribute& r) const
	{
		return (_attr != r._attr);
	}

	PUGI_IMPL_FN bool xml_attribute::operator<(const xml_attribute& r) const
	{
		return (_attr < r._attr);
	}

	PUGI_IMPL_FN bool xml_attribute::operator>(const xml_attribute& r) const
	{
		return (_attr > r._attr);
	}

	PUGI_IMPL_FN bool xml_attribute::operator<=(const xml_attribute& r) const
	{
		return (_attr <= r._attr);
	}

	PUGI_IMPL_FN bool xml_attribute::operator>=(const xml_attribute& r) const
	{
		return (_attr >= r._attr);
	}

	PUGI_IMPL_FN xml_attribute xml_attribute::next_attribute() const
	{
		if (!_attr) return xml_attribute();
		return xml_attribute(_attr->next_attribute);
	}

	PUGI_IMPL_FN xml_attribute xml_attribute::previous_attribute() const
	{
		if (!_attr) return xml_attribute();
		xml_attribute_struct* prev = _attr->prev_attribute_c;
		return prev->next_attribute ? xml_attribute(prev) : xml_attribute();
	}

	PUGI_IMPL_FN const char_t* xml_attribute::as_string(const char_t* def) const
	{
		if (!_attr) return def;
		const char_t* value = _attr->value;
		return value ? value : def;
	}

	PUGI_IMPL_FN int xml_attribute::as_int(int def) const
	{
		if (!_attr) return def;
		const char_t* value = _attr->value;
		return value ? impl::get_value_int(value) : def;
	}

	PUGI_IMPL_FN unsigned int xml_attribute::as_uint(unsigned int def) const
	{
		if (!_attr) return def;
		const char_t* value = _attr->value;
		return value ? impl::get_value_uint(value) : def;
	}

	PUGI_IMPL_FN double xml_attribute::as_double(double def) const
	{
		if (!_attr) return def;
		const char_t* value = _attr->value;
		return value ? impl::get_value_double(value) : def;
	}

	PUGI_IMPL_FN float xml_attribute::as_float(float def) const
	{
		if (!_attr) return def;
		const char_t* value = _attr->value;
		return value ? impl::get_value_float(value) : def;
	}

	PUGI_IMPL_FN bool xml_attribute::as_bool(bool def) const
	{
		if (!_attr) return def;
		const char_t* value = _attr->value;
		return value ? impl::get_value_bool(value) : def;
	}

#ifdef PUGIXML_HAS_LONG_LONG
	PUGI_IMPL_FN long long xml_attribute::as_llong(long long def) const
	{
		if (!_attr) return def;
		const char_t* value = _attr->value;
		return value ? impl::get_value_llong(value) : def;
	}

	PUGI_IMPL_FN unsigned long long xml_attribute::as_ullong(unsigned long long def) const
	{
		if (!_attr) return def;
		const char_t* value = _attr->value;
		return value ? impl::get_value_ullong(value) : def;
	}
#endif

	PUGI_IMPL_FN bool xml_attribute::empty() const
	{
		return !_attr;
	}

	PUGI_IMPL_FN const char_t* xml_attribute::name() const
	{
		if (!_attr) return PUGIXML_TEXT("");
		const char_t* name = _attr->name;
		return name ? name : PUGIXML_TEXT("");
	}

	PUGI_IMPL_FN const char_t* xml_attribute::value() const
	{
		if (!_attr) return PUGIXML_TEXT("");
		const char_t* value = _attr->value;
		return value ? value : PUGIXML_TEXT("");
	}

	PUGI_IMPL_FN size_t xml_attribute::hash_value() const
	{
		return reinterpret_cast<uintptr_t>(_attr) / sizeof(xml_attribute_struct);
	}

	PUGI_IMPL_FN xml_attribute_struct* xml_attribute::internal_object() const
	{
		return _attr;
	}

	PUGI_IMPL_FN xml_attribute& xml_attribute::operator=(const char_t* rhs)
	{
		set_value(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_attribute& xml_attribute::operator=(int rhs)
	{
		set_value(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_attribute& xml_attribute::operator=(unsigned int rhs)
	{
		set_value(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_attribute& xml_attribute::operator=(long rhs)
	{
		set_value(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_attribute& xml_attribute::operator=(unsigned long rhs)
	{
		set_value(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_attribute& xml_attribute::operator=(double rhs)
	{
		set_value(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_attribute& xml_attribute::operator=(float rhs)
	{
		set_value(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_attribute& xml_attribute::operator=(bool rhs)
	{
		set_value(rhs);
		return *this;
	}

#ifdef PUGIXML_HAS_STRING_VIEW
	PUGI_IMPL_FN xml_attribute& xml_attribute::operator=(string_view_t rhs)
	{
		set_value(rhs);
		return *this;
	}
#endif

#ifdef PUGIXML_HAS_LONG_LONG
	PUGI_IMPL_FN xml_attribute& xml_attribute::operator=(long long rhs)
	{
		set_value(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_attribute& xml_attribute::operator=(unsigned long long rhs)
	{
		set_value(rhs);
		return *this;
	}
#endif

	PUGI_IMPL_FN bool xml_attribute::set_name(const char_t* rhs)
	{
		if (!_attr) return false;

		return impl::strcpy_insitu(_attr->name, _attr->header, impl::xml_memory_page_name_allocated_mask, rhs, impl::strlength(rhs));
	}

	PUGI_IMPL_FN bool xml_attribute::set_name(const char_t* rhs, size_t size)
	{
		if (!_attr) return false;

		return impl::strcpy_insitu(_attr->name, _attr->header, impl::xml_memory_page_name_allocated_mask, rhs, size);
	}

#ifdef PUGIXML_HAS_STRING_VIEW
	PUGI_IMPL_FN bool xml_attribute::set_name(string_view_t rhs)
	{
		if (!_attr) return false;

		return impl::strcpy_insitu(_attr->name, _attr->header, impl::xml_memory_page_name_allocated_mask, rhs.data(), rhs.size());
	}
#endif

	PUGI_IMPL_FN bool xml_attribute::set_value(const char_t* rhs)
	{
		if (!_attr) return false;

		return impl::strcpy_insitu(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs, impl::strlength(rhs));
	}

	PUGI_IMPL_FN bool xml_attribute::set_value(const char_t* rhs, size_t size)
	{
		if (!_attr) return false;

		return impl::strcpy_insitu(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs, size);
	}

#ifdef PUGIXML_HAS_STRING_VIEW
	PUGI_IMPL_FN bool xml_attribute::set_value(string_view_t rhs)
	{
		if (!_attr) return false;

		return impl::strcpy_insitu(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs.data(), rhs.size());
	}
#endif

	PUGI_IMPL_FN bool xml_attribute::set_value(int rhs)
	{
		if (!_attr) return false;

		return impl::set_value_integer<unsigned int>(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs, rhs < 0);
	}

	PUGI_IMPL_FN bool xml_attribute::set_value(unsigned int rhs)
	{
		if (!_attr) return false;

		return impl::set_value_integer<unsigned int>(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs, false);
	}

	PUGI_IMPL_FN bool xml_attribute::set_value(long rhs)
	{
		if (!_attr) return false;

		return impl::set_value_integer<unsigned long>(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs, rhs < 0);
	}

	PUGI_IMPL_FN bool xml_attribute::set_value(unsigned long rhs)
	{
		if (!_attr) return false;

		return impl::set_value_integer<unsigned long>(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs, false);
	}

	PUGI_IMPL_FN bool xml_attribute::set_value(double rhs)
	{
		if (!_attr) return false;

		return impl::set_value_convert(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs, default_double_precision);
	}

	PUGI_IMPL_FN bool xml_attribute::set_value(double rhs, int precision)
	{
		if (!_attr) return false;

		return impl::set_value_convert(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs, precision);
	}

	PUGI_IMPL_FN bool xml_attribute::set_value(float rhs)
	{
		if (!_attr) return false;

		return impl::set_value_convert(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs, default_float_precision);
	}

	PUGI_IMPL_FN bool xml_attribute::set_value(float rhs, int precision)
	{
		if (!_attr) return false;

		return impl::set_value_convert(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs, precision);
	}

	PUGI_IMPL_FN bool xml_attribute::set_value(bool rhs)
	{
		if (!_attr) return false;

		return impl::set_value_bool(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs);
	}

#ifdef PUGIXML_HAS_LONG_LONG
	PUGI_IMPL_FN bool xml_attribute::set_value(long long rhs)
	{
		if (!_attr) return false;

		return impl::set_value_integer<unsigned long long>(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs, rhs < 0);
	}

	PUGI_IMPL_FN bool xml_attribute::set_value(unsigned long long rhs)
	{
		if (!_attr) return false;

		return impl::set_value_integer<unsigned long long>(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs, false);
	}
#endif

#ifdef __BORLANDC__
	PUGI_IMPL_FN bool operator&&(const xml_attribute& lhs, bool rhs)
	{
		return (bool)lhs && rhs;
	}

	PUGI_IMPL_FN bool operator||(const xml_attribute& lhs, bool rhs)
	{
		return (bool)lhs || rhs;
	}
#endif

	PUGI_IMPL_FN xml_node::xml_node(): _root(NULL)
	{
	}

	PUGI_IMPL_FN xml_node::xml_node(xml_node_struct* p): _root(p)
	{
	}

	PUGI_IMPL_FN static void unspecified_bool_xml_node(xml_node***)
	{
	}

	PUGI_IMPL_FN xml_node::operator xml_node::unspecified_bool_type() const
	{
		return _root ? unspecified_bool_xml_node : NULL;
	}

	PUGI_IMPL_FN bool xml_node::operator!() const
	{
		return !_root;
	}

	PUGI_IMPL_FN xml_node::iterator xml_node::begin() const
	{
		return iterator(_root ? _root->first_child + 0 : NULL, _root);
	}

	PUGI_IMPL_FN xml_node::iterator xml_node::end() const
	{
		return iterator(NULL, _root);
	}

	PUGI_IMPL_FN xml_node::attribute_iterator xml_node::attributes_begin() const
	{
		return attribute_iterator(_root ? _root->first_attribute + 0 : NULL, _root);
	}

	PUGI_IMPL_FN xml_node::attribute_iterator xml_node::attributes_end() const
	{
		return attribute_iterator(NULL, _root);
	}

	PUGI_IMPL_FN xml_object_range<xml_node_iterator> xml_node::children() const
	{
		return xml_object_range<xml_node_iterator>(begin(), end());
	}

	PUGI_IMPL_FN xml_object_range<xml_named_node_iterator> xml_node::children(const char_t* name_) const
	{
		return xml_object_range<xml_named_node_iterator>(xml_named_node_iterator(child(name_)._root, _root, name_), xml_named_node_iterator(NULL, _root, name_));
	}

	PUGI_IMPL_FN xml_object_range<xml_attribute_iterator> xml_node::attributes() const
	{
		return xml_object_range<xml_attribute_iterator>(attributes_begin(), attributes_end());
	}

	PUGI_IMPL_FN bool xml_node::operator==(const xml_node& r) const
	{
		return (_root == r._root);
	}

	PUGI_IMPL_FN bool xml_node::operator!=(const xml_node& r) const
	{
		return (_root != r._root);
	}

	PUGI_IMPL_FN bool xml_node::operator<(const xml_node& r) const
	{
		return (_root < r._root);
	}

	PUGI_IMPL_FN bool xml_node::operator>(const xml_node& r) const
	{
		return (_root > r._root);
	}

	PUGI_IMPL_FN bool xml_node::operator<=(const xml_node& r) const
	{
		return (_root <= r._root);
	}

	PUGI_IMPL_FN bool xml_node::operator>=(const xml_node& r) const
	{
		return (_root >= r._root);
	}

	PUGI_IMPL_FN bool xml_node::empty() const
	{
		return !_root;
	}

	PUGI_IMPL_FN const char_t* xml_node::name() const
	{
		if (!_root) return PUGIXML_TEXT("");
		const char_t* name = _root->name;
		return name ? name : PUGIXML_TEXT("");
	}

	PUGI_IMPL_FN xml_node_type xml_node::type() const
	{
		return _root ? PUGI_IMPL_NODETYPE(_root) : node_null;
	}

	PUGI_IMPL_FN const char_t* xml_node::value() const
	{
		if (!_root) return PUGIXML_TEXT("");
		const char_t* value = _root->value;
		return value ? value : PUGIXML_TEXT("");
	}

	PUGI_IMPL_FN xml_node xml_node::child(const char_t* name_) const
	{
		if (!_root) return xml_node();

		for (xml_node_struct* i = _root->first_child; i; i = i->next_sibling)
		{
			const char_t* iname = i->name;
			if (iname && impl::strequal(name_, iname))
				return xml_node(i);
		}

		return xml_node();
	}

	PUGI_IMPL_FN xml_attribute xml_node::attribute(const char_t* name_) const
	{
		if (!_root) return xml_attribute();

		for (xml_attribute_struct* i = _root->first_attribute; i; i = i->next_attribute)
		{
			const char_t* iname = i->name;
			if (iname && impl::strequal(name_, iname))
				return xml_attribute(i);
		}

		return xml_attribute();
	}

	PUGI_IMPL_FN xml_node xml_node::next_sibling(const char_t* name_) const
	{
		if (!_root) return xml_node();

		for (xml_node_struct* i = _root->next_sibling; i; i = i->next_sibling)
		{
			const char_t* iname = i->name;
			if (iname && impl::strequal(name_, iname))
				return xml_node(i);
		}

		return xml_node();
	}

	PUGI_IMPL_FN xml_node xml_node::next_sibling() const
	{
		return _root ? xml_node(_root->next_sibling) : xml_node();
	}

	PUGI_IMPL_FN xml_node xml_node::previous_sibling(const char_t* name_) const
	{
		if (!_root) return xml_node();

		for (xml_node_struct* i = _root->prev_sibling_c; i->next_sibling; i = i->prev_sibling_c)
		{
			const char_t* iname = i->name;
			if (iname && impl::strequal(name_, iname))
				return xml_node(i);
		}

		return xml_node();
	}

#ifdef PUGIXML_HAS_STRING_VIEW
	PUGI_IMPL_FN xml_node xml_node::child(string_view_t name_) const
	{
		if (!_root) return xml_node();

		for (xml_node_struct* i = _root->first_child; i; i = i->next_sibling)
		{
			const char_t* iname = i->name;
			if (iname && impl::stringview_equal(name_, iname))
				return xml_node(i);
		}

		return xml_node();
	}

	PUGI_IMPL_FN xml_attribute xml_node::attribute(string_view_t name_) const
	{
		if (!_root) return xml_attribute();

		for (xml_attribute_struct* i = _root->first_attribute; i; i = i->next_attribute)
		{
			const char_t* iname = i->name;
			if (iname && impl::stringview_equal(name_, iname))
				return xml_attribute(i);
		}

		return xml_attribute();
	}

	PUGI_IMPL_FN xml_node xml_node::next_sibling(string_view_t name_) const
	{
		if (!_root) return xml_node();

		for (xml_node_struct* i = _root->next_sibling; i; i = i->next_sibling)
		{
			const char_t* iname = i->name;
			if (iname && impl::stringview_equal(name_, iname))
				return xml_node(i);
		}

		return xml_node();
	}

	PUGI_IMPL_FN xml_node xml_node::previous_sibling(string_view_t name_) const
	{
		if (!_root) return xml_node();

		for (xml_node_struct* i = _root->prev_sibling_c; i->next_sibling; i = i->prev_sibling_c)
		{
			const char_t* iname = i->name;
			if (iname && impl::stringview_equal(name_, iname))
				return xml_node(i);
		}

		return xml_node();
	}
#endif

	PUGI_IMPL_FN xml_attribute xml_node::attribute(const char_t* name_, xml_attribute& hint_) const
	{
		xml_attribute_struct* hint = hint_._attr;

		// if hint is not an attribute of node, behavior is not defined
		assert(!hint || (_root && impl::is_attribute_of(hint, _root)));

		if (!_root) return xml_attribute();

		// optimistically search from hint up until the end
		for (xml_attribute_struct* i = hint; i; i = i->next_attribute)
		{
			const char_t* iname = i->name;
			if (iname && impl::strequal(name_, iname))
			{
				// update hint to maximize efficiency of searching for consecutive attributes
				hint_._attr = i->next_attribute;

				return xml_attribute(i);
			}
		}

		// wrap around and search from the first attribute until the hint
		// 'j' null pointer check is technically redundant, but it prevents a crash in case the assertion above fails
		for (xml_attribute_struct* j = _root->first_attribute; j && j != hint; j = j->next_attribute)
		{
			const char_t* jname = j->name;
			if (jname && impl::strequal(name_, jname))
			{
				// update hint to maximize efficiency of searching for consecutive attributes
				hint_._attr = j->next_attribute;

				return xml_attribute(j);
			}
		}

		return xml_attribute();
	}

#ifdef PUGIXML_HAS_STRING_VIEW
	PUGI_IMPL_FN xml_attribute xml_node::attribute(string_view_t name_, xml_attribute& hint_) const
	{
		xml_attribute_struct* hint = hint_._attr;

		// if hint is not an attribute of node, behavior is not defined
		assert(!hint || (_root && impl::is_attribute_of(hint, _root)));

		if (!_root) return xml_attribute();

		// optimistically search from hint up until the end
		for (xml_attribute_struct* i = hint; i; i = i->next_attribute)
		{
			const char_t* iname = i->name;
			if (iname && impl::stringview_equal(name_, iname))
			{
				// update hint to maximize efficiency of searching for consecutive attributes
				hint_._attr = i->next_attribute;

				return xml_attribute(i);
			}
		}

		// wrap around and search from the first attribute until the hint
		// 'j' null pointer check is technically redundant, but it prevents a crash in case the assertion above fails
		for (xml_attribute_struct* j = _root->first_attribute; j && j != hint; j = j->next_attribute)
		{
			const char_t* jname = j->name;
			if (jname && impl::stringview_equal(name_, jname))
			{
				// update hint to maximize efficiency of searching for consecutive attributes
				hint_._attr = j->next_attribute;

				return xml_attribute(j);
			}
		}

		return xml_attribute();
	}
#endif

	PUGI_IMPL_FN xml_node xml_node::previous_sibling() const
	{
		if (!_root) return xml_node();
		xml_node_struct* prev = _root->prev_sibling_c;
		return prev->next_sibling ? xml_node(prev) : xml_node();
	}

	PUGI_IMPL_FN xml_node xml_node::parent() const
	{
		return _root ? xml_node(_root->parent) : xml_node();
	}

	PUGI_IMPL_FN xml_node xml_node::root() const
	{
		return _root ? xml_node(&impl::get_document(_root)) : xml_node();
	}

	PUGI_IMPL_FN xml_text xml_node::text() const
	{
		return xml_text(_root);
	}

	PUGI_IMPL_FN const char_t* xml_node::child_value() const
	{
		if (!_root) return PUGIXML_TEXT("");

		// element nodes can have value if parse_embed_pcdata was used
		if (PUGI_IMPL_NODETYPE(_root) == node_element && _root->value)
			return _root->value;

		for (xml_node_struct* i = _root->first_child; i; i = i->next_sibling)
		{
			const char_t* ivalue = i->value;
			if (impl::is_text_node(i) && ivalue)
				return ivalue;
		}

		return PUGIXML_TEXT("");
	}

	PUGI_IMPL_FN const char_t* xml_node::child_value(const char_t* name_) const
	{
		return child(name_).child_value();
	}

	PUGI_IMPL_FN xml_attribute xml_node::first_attribute() const
	{
		if (!_root) return xml_attribute();
		return xml_attribute(_root->first_attribute);
	}

	PUGI_IMPL_FN xml_attribute xml_node::last_attribute() const
	{
		if (!_root) return xml_attribute();
		xml_attribute_struct* first = _root->first_attribute;
		return first ? xml_attribute(first->prev_attribute_c) : xml_attribute();
	}

	PUGI_IMPL_FN xml_node xml_node::first_child() const
	{
		if (!_root) return xml_node();
		return xml_node(_root->first_child);
	}

	PUGI_IMPL_FN xml_node xml_node::last_child() const
	{
		if (!_root) return xml_node();
		xml_node_struct* first = _root->first_child;
		return first ? xml_node(first->prev_sibling_c) : xml_node();
	}

	PUGI_IMPL_FN bool xml_node::set_name(const char_t* rhs)
	{
		xml_node_type type_ = _root ? PUGI_IMPL_NODETYPE(_root) : node_null;

		if (type_ != node_element && type_ != node_pi && type_ != node_declaration)
			return false;

		return impl::strcpy_insitu(_root->name, _root->header, impl::xml_memory_page_name_allocated_mask, rhs, impl::strlength(rhs));
	}

	PUGI_IMPL_FN bool xml_node::set_name(const char_t* rhs, size_t size)
	{
		xml_node_type type_ = _root ? PUGI_IMPL_NODETYPE(_root) : node_null;

		if (type_ != node_element && type_ != node_pi && type_ != node_declaration)
			return false;

		return impl::strcpy_insitu(_root->name, _root->header, impl::xml_memory_page_name_allocated_mask, rhs, size);
	}

#ifdef PUGIXML_HAS_STRING_VIEW
	PUGI_IMPL_FN bool xml_node::set_name(string_view_t rhs)
	{
		xml_node_type type_ = _root ? PUGI_IMPL_NODETYPE(_root) : node_null;

		if (type_ != node_element && type_ != node_pi && type_ != node_declaration)
			return false;

		return impl::strcpy_insitu(_root->name, _root->header, impl::xml_memory_page_name_allocated_mask, rhs.data(), rhs.size());
	}
#endif

	PUGI_IMPL_FN bool xml_node::set_value(const char_t* rhs)
	{
		xml_node_type type_ = _root ? PUGI_IMPL_NODETYPE(_root) : node_null;

		if (type_ != node_pcdata && type_ != node_cdata && type_ != node_comment && type_ != node_pi && type_ != node_doctype)
			return false;

		return impl::strcpy_insitu(_root->value, _root->header, impl::xml_memory_page_value_allocated_mask, rhs, impl::strlength(rhs));
	}

	PUGI_IMPL_FN bool xml_node::set_value(const char_t* rhs, size_t size)
	{
		xml_node_type type_ = _root ? PUGI_IMPL_NODETYPE(_root) : node_null;

		if (type_ != node_pcdata && type_ != node_cdata && type_ != node_comment && type_ != node_pi && type_ != node_doctype)
			return false;

		return impl::strcpy_insitu(_root->value, _root->header, impl::xml_memory_page_value_allocated_mask, rhs, size);
	}

#ifdef PUGIXML_HAS_STRING_VIEW
	PUGI_IMPL_FN bool xml_node::set_value(string_view_t rhs)
	{
		xml_node_type type_ = _root ? PUGI_IMPL_NODETYPE(_root) : node_null;

		if (type_ != node_pcdata && type_ != node_cdata && type_ != node_comment && type_ != node_pi && type_ != node_doctype)
			return false;

		return impl::strcpy_insitu(_root->value, _root->header, impl::xml_memory_page_value_allocated_mask, rhs.data(), rhs.size());
	}
#endif

	PUGI_IMPL_FN xml_attribute xml_node::append_attribute(const char_t* name_)
	{
		if (!impl::allow_insert_attribute(type())) return xml_attribute();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_attribute();

		xml_attribute a(impl::allocate_attribute(alloc));
		if (!a) return xml_attribute();

		impl::append_attribute(a._attr, _root);

		a.set_name(name_);

		return a;
	}

	PUGI_IMPL_FN xml_attribute xml_node::prepend_attribute(const char_t* name_)
	{
		if (!impl::allow_insert_attribute(type())) return xml_attribute();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_attribute();

		xml_attribute a(impl::allocate_attribute(alloc));
		if (!a) return xml_attribute();

		impl::prepend_attribute(a._attr, _root);

		a.set_name(name_);

		return a;
	}

	PUGI_IMPL_FN xml_attribute xml_node::insert_attribute_after(const char_t* name_, const xml_attribute& attr)
	{
		if (!impl::allow_insert_attribute(type())) return xml_attribute();
		if (!attr || !impl::is_attribute_of(attr._attr, _root)) return xml_attribute();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_attribute();

		xml_attribute a(impl::allocate_attribute(alloc));
		if (!a) return xml_attribute();

		impl::insert_attribute_after(a._attr, attr._attr, _root);

		a.set_name(name_);

		return a;
	}

	PUGI_IMPL_FN xml_attribute xml_node::insert_attribute_before(const char_t* name_, const xml_attribute& attr)
	{
		if (!impl::allow_insert_attribute(type())) return xml_attribute();
		if (!attr || !impl::is_attribute_of(attr._attr, _root)) return xml_attribute();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_attribute();

		xml_attribute a(impl::allocate_attribute(alloc));
		if (!a) return xml_attribute();

		impl::insert_attribute_before(a._attr, attr._attr, _root);

		a.set_name(name_);

		return a;
	}

#ifdef PUGIXML_HAS_STRING_VIEW
	PUGI_IMPL_FN xml_attribute xml_node::append_attribute(string_view_t name_)
	{
		if (!impl::allow_insert_attribute(type())) return xml_attribute();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_attribute();

		xml_attribute a(impl::allocate_attribute(alloc));
		if (!a) return xml_attribute();

		impl::append_attribute(a._attr, _root);

		a.set_name(name_);

		return a;
	}

	PUGI_IMPL_FN xml_attribute xml_node::prepend_attribute(string_view_t name_)
	{
		if (!impl::allow_insert_attribute(type())) return xml_attribute();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_attribute();

		xml_attribute a(impl::allocate_attribute(alloc));
		if (!a) return xml_attribute();

		impl::prepend_attribute(a._attr, _root);

		a.set_name(name_);

		return a;
	}

	PUGI_IMPL_FN xml_attribute xml_node::insert_attribute_after(string_view_t name_, const xml_attribute& attr)
	{
		if (!impl::allow_insert_attribute(type())) return xml_attribute();
		if (!attr || !impl::is_attribute_of(attr._attr, _root)) return xml_attribute();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_attribute();

		xml_attribute a(impl::allocate_attribute(alloc));
		if (!a) return xml_attribute();

		impl::insert_attribute_after(a._attr, attr._attr, _root);

		a.set_name(name_);

		return a;
	}

	PUGI_IMPL_FN xml_attribute xml_node::insert_attribute_before(string_view_t name_, const xml_attribute& attr)
	{
		if (!impl::allow_insert_attribute(type())) return xml_attribute();
		if (!attr || !impl::is_attribute_of(attr._attr, _root)) return xml_attribute();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_attribute();

		xml_attribute a(impl::allocate_attribute(alloc));
		if (!a) return xml_attribute();

		impl::insert_attribute_before(a._attr, attr._attr, _root);

		a.set_name(name_);

		return a;
	}
#endif

	PUGI_IMPL_FN xml_attribute xml_node::append_copy(const xml_attribute& proto)
	{
		if (!proto) return xml_attribute();
		if (!impl::allow_insert_attribute(type())) return xml_attribute();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_attribute();

		xml_attribute a(impl::allocate_attribute(alloc));
		if (!a) return xml_attribute();

		impl::append_attribute(a._attr, _root);
		impl::node_copy_attribute(a._attr, proto._attr);

		return a;
	}

	PUGI_IMPL_FN xml_attribute xml_node::prepend_copy(const xml_attribute& proto)
	{
		if (!proto) return xml_attribute();
		if (!impl::allow_insert_attribute(type())) return xml_attribute();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_attribute();

		xml_attribute a(impl::allocate_attribute(alloc));
		if (!a) return xml_attribute();

		impl::prepend_attribute(a._attr, _root);
		impl::node_copy_attribute(a._attr, proto._attr);

		return a;
	}

	PUGI_IMPL_FN xml_attribute xml_node::insert_copy_after(const xml_attribute& proto, const xml_attribute& attr)
	{
		if (!proto) return xml_attribute();
		if (!impl::allow_insert_attribute(type())) return xml_attribute();
		if (!attr || !impl::is_attribute_of(attr._attr, _root)) return xml_attribute();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_attribute();

		xml_attribute a(impl::allocate_attribute(alloc));
		if (!a) return xml_attribute();

		impl::insert_attribute_after(a._attr, attr._attr, _root);
		impl::node_copy_attribute(a._attr, proto._attr);

		return a;
	}

	PUGI_IMPL_FN xml_attribute xml_node::insert_copy_before(const xml_attribute& proto, const xml_attribute& attr)
	{
		if (!proto) return xml_attribute();
		if (!impl::allow_insert_attribute(type())) return xml_attribute();
		if (!attr || !impl::is_attribute_of(attr._attr, _root)) return xml_attribute();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_attribute();

		xml_attribute a(impl::allocate_attribute(alloc));
		if (!a) return xml_attribute();

		impl::insert_attribute_before(a._attr, attr._attr, _root);
		impl::node_copy_attribute(a._attr, proto._attr);

		return a;
	}

	PUGI_IMPL_FN xml_node xml_node::append_child(xml_node_type type_)
	{
		if (!impl::allow_insert_child(type(), type_)) return xml_node();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_node();

		xml_node n(impl::allocate_node(alloc, type_));
		if (!n) return xml_node();

		impl::append_node(n._root, _root);

		if (type_ == node_declaration) n.set_name(PUGIXML_TEXT("xml"));

		return n;
	}

	PUGI_IMPL_FN xml_node xml_node::prepend_child(xml_node_type type_)
	{
		if (!impl::allow_insert_child(type(), type_)) return xml_node();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_node();

		xml_node n(impl::allocate_node(alloc, type_));
		if (!n) return xml_node();

		impl::prepend_node(n._root, _root);

		if (type_ == node_declaration) n.set_name(PUGIXML_TEXT("xml"));

		return n;
	}

	PUGI_IMPL_FN xml_node xml_node::insert_child_before(xml_node_type type_, const xml_node& node)
	{
		if (!impl::allow_insert_child(type(), type_)) return xml_node();
		if (!node._root || node._root->parent != _root) return xml_node();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_node();

		xml_node n(impl::allocate_node(alloc, type_));
		if (!n) return xml_node();

		impl::insert_node_before(n._root, node._root);

		if (type_ == node_declaration) n.set_name(PUGIXML_TEXT("xml"));

		return n;
	}

	PUGI_IMPL_FN xml_node xml_node::insert_child_after(xml_node_type type_, const xml_node& node)
	{
		if (!impl::allow_insert_child(type(), type_)) return xml_node();
		if (!node._root || node._root->parent != _root) return xml_node();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_node();

		xml_node n(impl::allocate_node(alloc, type_));
		if (!n) return xml_node();

		impl::insert_node_after(n._root, node._root);

		if (type_ == node_declaration) n.set_name(PUGIXML_TEXT("xml"));

		return n;
	}

	PUGI_IMPL_FN xml_node xml_node::append_child(const char_t* name_)
	{
		xml_node result = append_child(node_element);

		result.set_name(name_);

		return result;
	}

	PUGI_IMPL_FN xml_node xml_node::prepend_child(const char_t* name_)
	{
		xml_node result = prepend_child(node_element);

		result.set_name(name_);

		return result;
	}

	PUGI_IMPL_FN xml_node xml_node::insert_child_after(const char_t* name_, const xml_node& node)
	{
		xml_node result = insert_child_after(node_element, node);

		result.set_name(name_);

		return result;
	}

	PUGI_IMPL_FN xml_node xml_node::insert_child_before(const char_t* name_, const xml_node& node)
	{
		xml_node result = insert_child_before(node_element, node);

		result.set_name(name_);

		return result;
	}

#ifdef PUGIXML_HAS_STRING_VIEW
	PUGI_IMPL_FN xml_node xml_node::append_child(string_view_t name_)
	{
		xml_node result = append_child(node_element);

		result.set_name(name_);

		return result;
	}

	PUGI_IMPL_FN xml_node xml_node::prepend_child(string_view_t name_)
	{
		xml_node result = prepend_child(node_element);

		result.set_name(name_);

		return result;
	}

	PUGI_IMPL_FN xml_node xml_node::insert_child_after(string_view_t name_, const xml_node& node)
	{
		xml_node result = insert_child_after(node_element, node);

		result.set_name(name_);

		return result;
	}

	PUGI_IMPL_FN xml_node xml_node::insert_child_before(string_view_t name_, const xml_node& node)
	{
		xml_node result = insert_child_before(node_element, node);

		result.set_name(name_);

		return result;
	}
#endif

	PUGI_IMPL_FN xml_node xml_node::append_copy(const xml_node& proto)
	{
		xml_node_type type_ = proto.type();
		if (!impl::allow_insert_child(type(), type_)) return xml_node();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_node();

		xml_node n(impl::allocate_node(alloc, type_));
		if (!n) return xml_node();

		impl::append_node(n._root, _root);
		impl::node_copy_tree(n._root, proto._root);

		return n;
	}

	PUGI_IMPL_FN xml_node xml_node::prepend_copy(const xml_node& proto)
	{
		xml_node_type type_ = proto.type();
		if (!impl::allow_insert_child(type(), type_)) return xml_node();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_node();

		xml_node n(impl::allocate_node(alloc, type_));
		if (!n) return xml_node();

		impl::prepend_node(n._root, _root);
		impl::node_copy_tree(n._root, proto._root);

		return n;
	}

	PUGI_IMPL_FN xml_node xml_node::insert_copy_after(const xml_node& proto, const xml_node& node)
	{
		xml_node_type type_ = proto.type();
		if (!impl::allow_insert_child(type(), type_)) return xml_node();
		if (!node._root || node._root->parent != _root) return xml_node();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_node();

		xml_node n(impl::allocate_node(alloc, type_));
		if (!n) return xml_node();

		impl::insert_node_after(n._root, node._root);
		impl::node_copy_tree(n._root, proto._root);

		return n;
	}

	PUGI_IMPL_FN xml_node xml_node::insert_copy_before(const xml_node& proto, const xml_node& node)
	{
		xml_node_type type_ = proto.type();
		if (!impl::allow_insert_child(type(), type_)) return xml_node();
		if (!node._root || node._root->parent != _root) return xml_node();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_node();

		xml_node n(impl::allocate_node(alloc, type_));
		if (!n) return xml_node();

		impl::insert_node_before(n._root, node._root);
		impl::node_copy_tree(n._root, proto._root);

		return n;
	}

	PUGI_IMPL_FN xml_node xml_node::append_move(const xml_node& moved)
	{
		if (!impl::allow_move(*this, moved)) return xml_node();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_node();

		// disable document_buffer_order optimization since moving nodes around changes document order without changing buffer pointers
		impl::get_document(_root).header |= impl::xml_memory_page_contents_shared_mask;

		impl::remove_node(moved._root);
		impl::append_node(moved._root, _root);

		return moved;
	}

	PUGI_IMPL_FN xml_node xml_node::prepend_move(const xml_node& moved)
	{
		if (!impl::allow_move(*this, moved)) return xml_node();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_node();

		// disable document_buffer_order optimization since moving nodes around changes document order without changing buffer pointers
		impl::get_document(_root).header |= impl::xml_memory_page_contents_shared_mask;

		impl::remove_node(moved._root);
		impl::prepend_node(moved._root, _root);

		return moved;
	}

	PUGI_IMPL_FN xml_node xml_node::insert_move_after(const xml_node& moved, const xml_node& node)
	{
		if (!impl::allow_move(*this, moved)) return xml_node();
		if (!node._root || node._root->parent != _root) return xml_node();
		if (moved._root == node._root) return xml_node();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_node();

		// disable document_buffer_order optimization since moving nodes around changes document order without changing buffer pointers
		impl::get_document(_root).header |= impl::xml_memory_page_contents_shared_mask;

		impl::remove_node(moved._root);
		impl::insert_node_after(moved._root, node._root);

		return moved;
	}

	PUGI_IMPL_FN xml_node xml_node::insert_move_before(const xml_node& moved, const xml_node& node)
	{
		if (!impl::allow_move(*this, moved)) return xml_node();
		if (!node._root || node._root->parent != _root) return xml_node();
		if (moved._root == node._root) return xml_node();

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return xml_node();

		// disable document_buffer_order optimization since moving nodes around changes document order without changing buffer pointers
		impl::get_document(_root).header |= impl::xml_memory_page_contents_shared_mask;

		impl::remove_node(moved._root);
		impl::insert_node_before(moved._root, node._root);

		return moved;
	}

	PUGI_IMPL_FN bool xml_node::remove_attribute(const char_t* name_)
	{
		return remove_attribute(attribute(name_));
	}

#ifdef PUGIXML_HAS_STRING_VIEW
	PUGI_IMPL_FN bool xml_node::remove_attribute(string_view_t name_)
	{
		return remove_attribute(attribute(name_));
	}
#endif

	PUGI_IMPL_FN bool xml_node::remove_attribute(const xml_attribute& a)
	{
		if (!_root || !a._attr) return false;
		if (!impl::is_attribute_of(a._attr, _root)) return false;

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return false;

		impl::remove_attribute(a._attr, _root);
		impl::destroy_attribute(a._attr, alloc);

		return true;
	}

	PUGI_IMPL_FN bool xml_node::remove_attributes()
	{
		if (!_root) return false;

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return false;

		for (xml_attribute_struct* attr = _root->first_attribute; attr; )
		{
			xml_attribute_struct* next = attr->next_attribute;

			impl::destroy_attribute(attr, alloc);

			attr = next;
		}

		_root->first_attribute = NULL;

		return true;
	}

	PUGI_IMPL_FN bool xml_node::remove_child(const char_t* name_)
	{
		return remove_child(child(name_));
	}

#ifdef PUGIXML_HAS_STRING_VIEW
	PUGI_IMPL_FN bool xml_node::remove_child(string_view_t name_)
	{
		return remove_child(child(name_));
	}
#endif

	PUGI_IMPL_FN bool xml_node::remove_child(const xml_node& n)
	{
		if (!_root || !n._root || n._root->parent != _root) return false;

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return false;

		impl::remove_node(n._root);
		impl::destroy_node(n._root, alloc);

		return true;
	}

	PUGI_IMPL_FN bool xml_node::remove_children()
	{
		if (!_root) return false;

		impl::xml_allocator& alloc = impl::get_allocator(_root);
		if (!alloc.reserve()) return false;

		for (xml_node_struct* cur = _root->first_child; cur; )
		{
			xml_node_struct* next = cur->next_sibling;

			impl::destroy_node(cur, alloc);

			cur = next;
		}

		_root->first_child = NULL;

		return true;
	}

	PUGI_IMPL_FN xml_parse_result xml_node::append_buffer(const void* contents, size_t size, unsigned int options, xml_encoding encoding)
	{
		// append_buffer is only valid for elements/documents
		if (!impl::allow_insert_child(type(), node_element)) return impl::make_parse_result(status_append_invalid_root);

		// append buffer can not merge PCDATA into existing PCDATA nodes
		if ((options & parse_merge_pcdata) != 0 && last_child().type() == node_pcdata) return impl::make_parse_result(status_append_invalid_root);

		// get document node
		impl::xml_document_struct* doc = &impl::get_document(_root);

		// disable document_buffer_order optimization since in a document with multiple buffers comparing buffer pointers does not make sense
		doc->header |= impl::xml_memory_page_contents_shared_mask;

		// get extra buffer element (we'll store the document fragment buffer there so that we can deallocate it later)
		impl::xml_memory_page* page = NULL;
		impl::xml_extra_buffer* extra = static_cast<impl::xml_extra_buffer*>(doc->allocate_memory(sizeof(impl::xml_extra_buffer) + sizeof(void*), page));
		(void)page;

		if (!extra) return impl::make_parse_result(status_out_of_memory);

	#ifdef PUGIXML_COMPACT
		// align the memory block to a pointer boundary; this is required for compact mode where memory allocations are only 4b aligned
		// note that this requires up to sizeof(void*)-1 additional memory, which the allocation above takes into account
		extra = reinterpret_cast<impl::xml_extra_buffer*>((reinterpret_cast<uintptr_t>(extra) + (sizeof(void*) - 1)) & ~(sizeof(void*) - 1));
	#endif

		// add extra buffer to the list
		extra->buffer = NULL;
		extra->next = doc->extra_buffers;
		doc->extra_buffers = extra;

		// name of the root has to be NULL before parsing - otherwise closing node mismatches will not be detected at the top level
		impl::name_null_sentry sentry(_root);

		return impl::load_buffer_impl(doc, _root, const_cast<void*>(contents), size, options, encoding, false, false, &extra->buffer);
	}

	PUGI_IMPL_FN xml_node xml_node::find_child_by_attribute(const char_t* name_, const char_t* attr_name, const char_t* attr_value) const
	{
		if (!_root) return xml_node();

		for (xml_node_struct* i = _root->first_child; i; i = i->next_sibling)
		{
			const char_t* iname = i->name;
			if (iname && impl::strequal(name_, iname))
			{
				for (xml_attribute_struct* a = i->first_attribute; a; a = a->next_attribute)
				{
					const char_t* aname = a->name;
					if (aname && impl::strequal(attr_name, aname))
					{
						const char_t* avalue = a->value;
						if (impl::strequal(attr_value, avalue ? avalue : PUGIXML_TEXT("")))
							return xml_node(i);
					}
				}
			}
		}

		return xml_node();
	}

	PUGI_IMPL_FN xml_node xml_node::find_child_by_attribute(const char_t* attr_name, const char_t* attr_value) const
	{
		if (!_root) return xml_node();

		for (xml_node_struct* i = _root->first_child; i; i = i->next_sibling)
			for (xml_attribute_struct* a = i->first_attribute; a; a = a->next_attribute)
			{
				const char_t* aname = a->name;
				if (aname && impl::strequal(attr_name, aname))
				{
					const char_t* avalue = a->value;
					if (impl::strequal(attr_value, avalue ? avalue : PUGIXML_TEXT("")))
						return xml_node(i);
				}
			}

		return xml_node();
	}

#ifndef PUGIXML_NO_STL
	PUGI_IMPL_FN string_t xml_node::path(char_t delimiter) const
	{
		if (!_root) return string_t();

		size_t offset = 0;

		for (xml_node_struct* i = _root; i; i = i->parent)
		{
			const char_t* iname = i->name;
			offset += (i != _root);
			offset += iname ? impl::strlength(iname) : 0;
		}

		string_t result;
		result.resize(offset);

		for (xml_node_struct* j = _root; j; j = j->parent)
		{
			if (j != _root)
				result[--offset] = delimiter;

			const char_t* jname = j->name;
			if (jname)
			{
				size_t length = impl::strlength(jname);

				offset -= length;
				memcpy(&result[offset], jname, length * sizeof(char_t));
			}
		}

		assert(offset == 0);

		return result;
	}
#endif

	PUGI_IMPL_FN xml_node xml_node::first_element_by_path(const char_t* path_, char_t delimiter) const
	{
		xml_node context = path_[0] == delimiter ? root() : *this;

		if (!context._root) return xml_node();

		const char_t* path_segment = path_;

		while (*path_segment == delimiter) ++path_segment;

		const char_t* path_segment_end = path_segment;

		while (*path_segment_end && *path_segment_end != delimiter) ++path_segment_end;

		if (path_segment == path_segment_end) return context;

		const char_t* next_segment = path_segment_end;

		while (*next_segment == delimiter) ++next_segment;

		if (*path_segment == '.' && path_segment + 1 == path_segment_end)
			return context.first_element_by_path(next_segment, delimiter);
		else if (*path_segment == '.' && *(path_segment+1) == '.' && path_segment + 2 == path_segment_end)
			return context.parent().first_element_by_path(next_segment, delimiter);
		else
		{
			for (xml_node_struct* j = context._root->first_child; j; j = j->next_sibling)
			{
				const char_t* jname = j->name;
				if (jname && impl::strequalrange(jname, path_segment, static_cast<size_t>(path_segment_end - path_segment)))
				{
					xml_node subsearch = xml_node(j).first_element_by_path(next_segment, delimiter);

					if (subsearch) return subsearch;
				}
			}

			return xml_node();
		}
	}

	PUGI_IMPL_FN bool xml_node::traverse(xml_tree_walker& walker)
	{
		walker._depth = -1;

		xml_node arg_begin(_root);
		if (!walker.begin(arg_begin)) return false;

		xml_node_struct* cur = _root ? _root->first_child + 0 : NULL;

		if (cur)
		{
			++walker._depth;

			do
			{
				xml_node arg_for_each(cur);
				if (!walker.for_each(arg_for_each))
					return false;

				if (cur->first_child)
				{
					++walker._depth;
					cur = cur->first_child;
				}
				else if (cur->next_sibling)
					cur = cur->next_sibling;
				else
				{
					while (!cur->next_sibling && cur != _root && cur->parent)
					{
						--walker._depth;
						cur = cur->parent;
					}

					if (cur != _root)
						cur = cur->next_sibling;
				}
			}
			while (cur && cur != _root);
		}

		assert(walker._depth == -1);

		xml_node arg_end(_root);
		return walker.end(arg_end);
	}

	PUGI_IMPL_FN size_t xml_node::hash_value() const
	{
		return reinterpret_cast<uintptr_t>(_root) / sizeof(xml_node_struct);
	}

	PUGI_IMPL_FN xml_node_struct* xml_node::internal_object() const
	{
		return _root;
	}

	PUGI_IMPL_FN void xml_node::print(xml_writer& writer, const char_t* indent, unsigned int flags, xml_encoding encoding, unsigned int depth) const
	{
		if (!_root) return;

		impl::xml_buffered_writer buffered_writer(writer, encoding);

		impl::node_output(buffered_writer, _root, indent, flags, depth);

		buffered_writer.flush();
	}

#ifndef PUGIXML_NO_STL
	PUGI_IMPL_FN void xml_node::print(std::basic_ostream<char>& stream, const char_t* indent, unsigned int flags, xml_encoding encoding, unsigned int depth) const
	{
		xml_writer_stream writer(stream);

		print(writer, indent, flags, encoding, depth);
	}

	PUGI_IMPL_FN void xml_node::print(std::basic_ostream<wchar_t>& stream, const char_t* indent, unsigned int flags, unsigned int depth) const
	{
		xml_writer_stream writer(stream);

		print(writer, indent, flags, encoding_wchar, depth);
	}
#endif

	PUGI_IMPL_FN ptrdiff_t xml_node::offset_debug() const
	{
		if (!_root) return -1;

		impl::xml_document_struct& doc = impl::get_document(_root);

		// we can determine the offset reliably only if there is exactly once parse buffer
		if (!doc.buffer || doc.extra_buffers) return -1;

		switch (type())
		{
		case node_document:
			return 0;

		case node_element:
		case node_declaration:
		case node_pi:
			return _root->name && (_root->header & impl::xml_memory_page_name_allocated_or_shared_mask) == 0 ? _root->name - doc.buffer : -1;

		case node_pcdata:
		case node_cdata:
		case node_comment:
		case node_doctype:
			return _root->value && (_root->header & impl::xml_memory_page_value_allocated_or_shared_mask) == 0 ? _root->value - doc.buffer : -1;

		default:
			assert(false && "Invalid node type"); // unreachable
			return -1;
		}
	}

#ifdef __BORLANDC__
	PUGI_IMPL_FN bool operator&&(const xml_node& lhs, bool rhs)
	{
		return (bool)lhs && rhs;
	}

	PUGI_IMPL_FN bool operator||(const xml_node& lhs, bool rhs)
	{
		return (bool)lhs || rhs;
	}
#endif

	PUGI_IMPL_FN xml_text::xml_text(xml_node_struct* root): _root(root)
	{
	}

	PUGI_IMPL_FN xml_node_struct* xml_text::_data() const
	{
		if (!_root || impl::is_text_node(_root)) return _root;

		// element nodes can have value if parse_embed_pcdata was used
		if (PUGI_IMPL_NODETYPE(_root) == node_element && _root->value)
			return _root;

		for (xml_node_struct* node = _root->first_child; node; node = node->next_sibling)
			if (impl::is_text_node(node))
				return node;

		return NULL;
	}

	PUGI_IMPL_FN xml_node_struct* xml_text::_data_new()
	{
		xml_node_struct* d = _data();
		if (d) return d;

		return xml_node(_root).append_child(node_pcdata).internal_object();
	}

	PUGI_IMPL_FN xml_text::xml_text(): _root(NULL)
	{
	}

	PUGI_IMPL_FN static void unspecified_bool_xml_text(xml_text***)
	{
	}

	PUGI_IMPL_FN xml_text::operator xml_text::unspecified_bool_type() const
	{
		return _data() ? unspecified_bool_xml_text : NULL;
	}

	PUGI_IMPL_FN bool xml_text::operator!() const
	{
		return !_data();
	}

	PUGI_IMPL_FN bool xml_text::empty() const
	{
		return _data() == NULL;
	}

	PUGI_IMPL_FN const char_t* xml_text::get() const
	{
		xml_node_struct* d = _data();
		if (!d) return PUGIXML_TEXT("");
		const char_t* value = d->value;
		return value ? value : PUGIXML_TEXT("");
	}

	PUGI_IMPL_FN const char_t* xml_text::as_string(const char_t* def) const
	{
		xml_node_struct* d = _data();
		if (!d) return def;
		const char_t* value = d->value;
		return value ? value : def;
	}

	PUGI_IMPL_FN int xml_text::as_int(int def) const
	{
		xml_node_struct* d = _data();
		if (!d) return def;
		const char_t* value = d->value;
		return value ? impl::get_value_int(value) : def;
	}

	PUGI_IMPL_FN unsigned int xml_text::as_uint(unsigned int def) const
	{
		xml_node_struct* d = _data();
		if (!d) return def;
		const char_t* value = d->value;
		return value ? impl::get_value_uint(value) : def;
	}

	PUGI_IMPL_FN double xml_text::as_double(double def) const
	{
		xml_node_struct* d = _data();
		if (!d) return def;
		const char_t* value = d->value;
		return value ? impl::get_value_double(value) : def;
	}

	PUGI_IMPL_FN float xml_text::as_float(float def) const
	{
		xml_node_struct* d = _data();
		if (!d) return def;
		const char_t* value = d->value;
		return value ? impl::get_value_float(value) : def;
	}

	PUGI_IMPL_FN bool xml_text::as_bool(bool def) const
	{
		xml_node_struct* d = _data();
		if (!d) return def;
		const char_t* value = d->value;
		return value ? impl::get_value_bool(value) : def;
	}

#ifdef PUGIXML_HAS_LONG_LONG
	PUGI_IMPL_FN long long xml_text::as_llong(long long def) const
	{
		xml_node_struct* d = _data();
		if (!d) return def;
		const char_t* value = d->value;
		return value ? impl::get_value_llong(value) : def;
	}

	PUGI_IMPL_FN unsigned long long xml_text::as_ullong(unsigned long long def) const
	{
		xml_node_struct* d = _data();
		if (!d) return def;
		const char_t* value = d->value;
		return value ? impl::get_value_ullong(value) : def;
	}
#endif

	PUGI_IMPL_FN bool xml_text::set(const char_t* rhs)
	{
		xml_node_struct* dn = _data_new();

		return dn ? impl::strcpy_insitu(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs, impl::strlength(rhs)) : false;
	}

	PUGI_IMPL_FN bool xml_text::set(const char_t* rhs, size_t size)
	{
		xml_node_struct* dn = _data_new();

		return dn ? impl::strcpy_insitu(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs, size) : false;
	}

#ifdef PUGIXML_HAS_STRING_VIEW
	PUGI_IMPL_FN bool xml_text::set(string_view_t rhs)
	{
		xml_node_struct* dn = _data_new();

		return dn ? impl::strcpy_insitu(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs.data(), rhs.size()) : false;
	}
#endif

	PUGI_IMPL_FN bool xml_text::set(int rhs)
	{
		xml_node_struct* dn = _data_new();

		return dn ? impl::set_value_integer<unsigned int>(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs, rhs < 0) : false;
	}

	PUGI_IMPL_FN bool xml_text::set(unsigned int rhs)
	{
		xml_node_struct* dn = _data_new();

		return dn ? impl::set_value_integer<unsigned int>(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs, false) : false;
	}

	PUGI_IMPL_FN bool xml_text::set(long rhs)
	{
		xml_node_struct* dn = _data_new();

		return dn ? impl::set_value_integer<unsigned long>(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs, rhs < 0) : false;
	}

	PUGI_IMPL_FN bool xml_text::set(unsigned long rhs)
	{
		xml_node_struct* dn = _data_new();

		return dn ? impl::set_value_integer<unsigned long>(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs, false) : false;
	}

	PUGI_IMPL_FN bool xml_text::set(float rhs)
	{
		xml_node_struct* dn = _data_new();

		return dn ? impl::set_value_convert(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs, default_float_precision) : false;
	}

	PUGI_IMPL_FN bool xml_text::set(float rhs, int precision)
	{
		xml_node_struct* dn = _data_new();

		return dn ? impl::set_value_convert(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs, precision) : false;
	}

	PUGI_IMPL_FN bool xml_text::set(double rhs)
	{
		xml_node_struct* dn = _data_new();

		return dn ? impl::set_value_convert(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs, default_double_precision) : false;
	}

	PUGI_IMPL_FN bool xml_text::set(double rhs, int precision)
	{
		xml_node_struct* dn = _data_new();

		return dn ? impl::set_value_convert(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs, precision) : false;
	}

	PUGI_IMPL_FN bool xml_text::set(bool rhs)
	{
		xml_node_struct* dn = _data_new();

		return dn ? impl::set_value_bool(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs) : false;
	}

#ifdef PUGIXML_HAS_LONG_LONG
	PUGI_IMPL_FN bool xml_text::set(long long rhs)
	{
		xml_node_struct* dn = _data_new();

		return dn ? impl::set_value_integer<unsigned long long>(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs, rhs < 0) : false;
	}

	PUGI_IMPL_FN bool xml_text::set(unsigned long long rhs)
	{
		xml_node_struct* dn = _data_new();

		return dn ? impl::set_value_integer<unsigned long long>(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs, false) : false;
	}
#endif

	PUGI_IMPL_FN xml_text& xml_text::operator=(const char_t* rhs)
	{
		set(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_text& xml_text::operator=(int rhs)
	{
		set(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_text& xml_text::operator=(unsigned int rhs)
	{
		set(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_text& xml_text::operator=(long rhs)
	{
		set(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_text& xml_text::operator=(unsigned long rhs)
	{
		set(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_text& xml_text::operator=(double rhs)
	{
		set(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_text& xml_text::operator=(float rhs)
	{
		set(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_text& xml_text::operator=(bool rhs)
	{
		set(rhs);
		return *this;
	}

#ifdef PUGIXML_HAS_STRING_VIEW
	PUGI_IMPL_FN xml_text& xml_text::operator=(string_view_t rhs)
	{
		set(rhs);
		return *this;
	}
#endif

#ifdef PUGIXML_HAS_LONG_LONG
	PUGI_IMPL_FN xml_text& xml_text::operator=(long long rhs)
	{
		set(rhs);
		return *this;
	}

	PUGI_IMPL_FN xml_text& xml_text::operator=(unsigned long long rhs)
	{
		set(rhs);
		return *this;
	}
#endif

	PUGI_IMPL_FN xml_node xml_text::data() const
	{
		return xml_node(_data());
	}

#ifdef __BORLANDC__
	PUGI_IMPL_FN bool operator&&(const xml_text& lhs, bool rhs)
	{
		return (bool)lhs && rhs;
	}

	PUGI_IMPL_FN bool operator||(const xml_text& lhs, bool rhs)
	{
		return (bool)lhs || rhs;
	}
#endif

	PUGI_IMPL_FN xml_node_iterator::xml_node_iterator()
	{
	}

	PUGI_IMPL_FN xml_node_iterator::xml_node_iterator(const xml_node& node): _wrap(node), _parent(node.parent())
	{
	}

	PUGI_IMPL_FN xml_node_iterator::xml_node_iterator(xml_node_struct* ref, xml_node_struct* parent): _wrap(ref), _parent(parent)
	{
	}

	PUGI_IMPL_FN bool xml_node_iterator::operator==(const xml_node_iterator& rhs) const
	{
		return _wrap._root == rhs._wrap._root && _parent._root == rhs._parent._root;
	}

	PUGI_IMPL_FN bool xml_node_iterator::operator!=(const xml_node_iterator& rhs) const
	{
		return _wrap._root != rhs._wrap._root || _parent._root != rhs._parent._root;
	}

	PUGI_IMPL_FN xml_node& xml_node_iterator::operator*() const
	{
		assert(_wrap._root);
		return _wrap;
	}

	PUGI_IMPL_FN xml_node* xml_node_iterator::operator->() const
	{
		assert(_wrap._root);
		return &_wrap;
	}

	PUGI_IMPL_FN xml_node_iterator& xml_node_iterator::operator++()
	{
		assert(_wrap._root);
		_wrap._root = _wrap._root->next_sibling;
		return *this;
	}

	PUGI_IMPL_FN xml_node_iterator xml_node_iterator::operator++(int)
	{
		xml_node_iterator temp = *this;
		++*this;
		return temp;
	}

	PUGI_IMPL_FN xml_node_iterator& xml_node_iterator::operator--()
	{
		_wrap = _wrap._root ? _wrap.previous_sibling() : _parent.last_child();
		return *this;
	}

	PUGI_IMPL_FN xml_node_iterator xml_node_iterator::operator--(int)
	{
		xml_node_iterator temp = *this;
		--*this;
		return temp;
	}

	PUGI_IMPL_FN xml_attribute_iterator::xml_attribute_iterator()
	{
	}

	PUGI_IMPL_FN xml_attribute_iterator::xml_attribute_iterator(const xml_attribute& attr, const xml_node& parent): _wrap(attr), _parent(parent)
	{
	}

	PUGI_IMPL_FN xml_attribute_iterator::xml_attribute_iterator(xml_attribute_struct* ref, xml_node_struct* parent): _wrap(ref), _parent(parent)
	{
	}

	PUGI_IMPL_FN bool xml_attribute_iterator::operator==(const xml_attribute_iterator& rhs) const
	{
		return _wrap._attr == rhs._wrap._attr && _parent._root == rhs._parent._root;
	}

	PUGI_IMPL_FN bool xml_attribute_iterator::operator!=(const xml_attribute_iterator& rhs) const
	{
		return _wrap._attr != rhs._wrap._attr || _parent._root != rhs._parent._root;
	}

	PUGI_IMPL_FN xml_attribute& xml_attribute_iterator::operator*() const
	{
		assert(_wrap._attr);
		return _wrap;
	}

	PUGI_IMPL_FN xml_attribute* xml_attribute_iterator::operator->() const
	{
		assert(_wrap._attr);
		return &_wrap;
	}

	PUGI_IMPL_FN xml_attribute_iterator& xml_attribute_iterator::operator++()
	{
		assert(_wrap._attr);
		_wrap._attr = _wrap._attr->next_attribute;
		return *this;
	}

	PUGI_IMPL_FN xml_attribute_iterator xml_attribute_iterator::operator++(int)
	{
		xml_attribute_iterator temp = *this;
		++*this;
		return temp;
	}

	PUGI_IMPL_FN xml_attribute_iterator& xml_attribute_iterator::operator--()
	{
		_wrap = _wrap._attr ? _wrap.previous_attribute() : _parent.last_attribute();
		return *this;
	}

	PUGI_IMPL_FN xml_attribute_iterator xml_attribute_iterator::operator--(int)
	{
		xml_attribute_iterator temp = *this;
		--*this;
		return temp;
	}

	PUGI_IMPL_FN xml_named_node_iterator::xml_named_node_iterator(): _name(NULL)
	{
	}

	PUGI_IMPL_FN xml_named_node_iterator::xml_named_node_iterator(const xml_node& node, const char_t* name): _wrap(node), _parent(node.parent()), _name(name)
	{
	}

	PUGI_IMPL_FN xml_named_node_iterator::xml_named_node_iterator(xml_node_struct* ref, xml_node_struct* parent, const char_t* name): _wrap(ref), _parent(parent), _name(name)
	{
	}

	PUGI_IMPL_FN bool xml_named_node_iterator::operator==(const xml_named_node_iterator& rhs) const
	{
		return _wrap._root == rhs._wrap._root && _parent._root == rhs._parent._root;
	}

	PUGI_IMPL_FN bool xml_named_node_iterator::operator!=(const xml_named_node_iterator& rhs) const
	{
		return _wrap._root != rhs._wrap._root || _parent._root != rhs._parent._root;
	}

	PUGI_IMPL_FN xml_node& xml_named_node_iterator::operator*() const
	{
		assert(_wrap._root);
		return _wrap;
	}

	PUGI_IMPL_FN xml_node* xml_named_node_iterator::operator->() const
	{
		assert(_wrap._root);
		return &_wrap;
	}

	PUGI_IMPL_FN xml_named_node_iterator& xml_named_node_iterator::operator++()
	{
		assert(_wrap._root);
		_wrap = _wrap.next_sibling(_name);
		return *this;
	}

	PUGI_IMPL_FN xml_named_node_iterator xml_named_node_iterator::operator++(int)
	{
		xml_named_node_iterator temp = *this;
		++*this;
		return temp;
	}

	PUGI_IMPL_FN xml_named_node_iterator& xml_named_node_iterator::operator--()
	{
		if (_wrap._root)
			_wrap = _wrap.previous_sibling(_name);
		else
		{
			_wrap = _parent.last_child();

			if (!impl::strequal(_wrap.name(), _name))
				_wrap = _wrap.previous_sibling(_name);
		}

		return *this;
	}

	PUGI_IMPL_FN xml_named_node_iterator xml_named_node_iterator::operator--(int)
	{
		xml_named_node_iterator temp = *this;
		--*this;
		return temp;
	}

	PUGI_IMPL_FN xml_parse_result::xml_parse_result(): status(status_internal_error), offset(0), encoding(encoding_auto)
	{
	}

	PUGI_IMPL_FN xml_parse_result::operator bool() const
	{
		return status == status_ok;
	}

	PUGI_IMPL_FN const char* xml_parse_result::description() const
	{
		switch (status)
		{
		case status_ok: return "No error";

		case status_file_not_found: return "File was not found";
		case status_io_error: return "Error reading from file/stream";
		case status_out_of_memory: return "Could not allocate memory";
		case status_internal_error: return "Internal error occurred";

		case status_unrecognized_tag: return "Could not determine tag type";

		case status_bad_pi: return "Error parsing document declaration/processing instruction";
		case status_bad_comment: return "Error parsing comment";
		case status_bad_cdata: return "Error parsing CDATA section";
		case status_bad_doctype: return "Error parsing document type declaration";
		case status_bad_pcdata: return "Error parsing PCDATA section";
		case status_bad_start_element: return "Error parsing start element tag";
		case status_bad_attribute: return "Error parsing element attribute";
		case status_bad_end_element: return "Error parsing end element tag";
		case status_end_element_mismatch: return "Start-end tags mismatch";

		case status_append_invalid_root: return "Unable to append nodes: root is not an element or document";

		case status_no_document_element: return "No document element found";

		default: return "Unknown error";
		}
	}

	PUGI_IMPL_FN xml_document::xml_document(): _buffer(NULL)
	{
		_create();
	}

	PUGI_IMPL_FN xml_document::~xml_document()
	{
		_destroy();
	}

#ifdef PUGIXML_HAS_MOVE
	PUGI_IMPL_FN xml_document::xml_document(xml_document&& rhs) PUGIXML_NOEXCEPT_IF_NOT_COMPACT: _buffer(NULL)
	{
		_create();
		_move(rhs);
	}

	PUGI_IMPL_FN xml_document& xml_document::operator=(xml_document&& rhs) PUGIXML_NOEXCEPT_IF_NOT_COMPACT
	{
		if (this == &rhs) return *this;

		_destroy();
		_create();
		_move(rhs);

		return *this;
	}
#endif

	PUGI_IMPL_FN void xml_document::reset()
	{
		_destroy();
		_create();
	}

	PUGI_IMPL_FN void xml_document::reset(const xml_document& proto)
	{
		reset();

		impl::node_copy_tree(_root, proto._root);
	}

	PUGI_IMPL_FN void xml_document::_create()
	{
		assert(!_root);

	#ifdef PUGIXML_COMPACT
		// space for page marker for the first page (uint32_t), rounded up to pointer size; assumes pointers are at least 32-bit
		const size_t page_offset = sizeof(void*);
	#else
		const size_t page_offset = 0;
	#endif

		// initialize sentinel page
		PUGI_IMPL_STATIC_ASSERT(sizeof(impl::xml_memory_page) + sizeof(impl::xml_document_struct) + page_offset <= sizeof(_memory));

		// prepare page structure
		impl::xml_memory_page* page = impl::xml_memory_page::construct(_memory);
		assert(page);

		page->busy_size = impl::xml_memory_page_size;

		// setup first page marker
	#ifdef PUGIXML_COMPACT
		// round-trip through void* to avoid 'cast increases required alignment of target type' warning
		page->compact_page_marker = reinterpret_cast<uint32_t*>(static_cast<void*>(reinterpret_cast<char*>(page) + sizeof(impl::xml_memory_page)));
		*page->compact_page_marker = sizeof(impl::xml_memory_page);
	#endif

		// allocate new root
		_root = new (reinterpret_cast<char*>(page) + sizeof(impl::xml_memory_page) + page_offset) impl::xml_document_struct(page);
		_root->prev_sibling_c = _root;

		// setup sentinel page
		page->allocator = static_cast<impl::xml_document_struct*>(_root);

		// setup hash table pointer in allocator
	#ifdef PUGIXML_COMPACT
		page->allocator->_hash = &static_cast<impl::xml_document_struct*>(_root)->hash;
	#endif

		// verify the document allocation
		assert(reinterpret_cast<char*>(_root) + sizeof(impl::xml_document_struct) <= _memory + sizeof(_memory));
	}

	PUGI_IMPL_FN void xml_document::_destroy()
	{
		assert(_root);

		// destroy static storage
		if (_buffer)
		{
			impl::xml_memory::deallocate(_buffer);
			_buffer = NULL;
		}

		// destroy extra buffers (note: no need to destroy linked list nodes, they're allocated using document allocator)
		for (impl::xml_extra_buffer* extra = static_cast<impl::xml_document_struct*>(_root)->extra_buffers; extra; extra = extra->next)
		{
			if (extra->buffer) impl::xml_memory::deallocate(extra->buffer);
		}

		// destroy dynamic storage, leave sentinel page (it's in static memory)
		impl::xml_memory_page* root_page = PUGI_IMPL_GETPAGE(_root);
		assert(root_page && !root_page->prev);
		assert(reinterpret_cast<char*>(root_page) >= _memory && reinterpret_cast<char*>(root_page) < _memory + sizeof(_memory));

		for (impl::xml_memory_page* page = root_page->next; page; )
		{
			impl::xml_memory_page* next = page->next;

			impl::xml_allocator::deallocate_page(page);

			page = next;
		}

	#ifdef PUGIXML_COMPACT
		// destroy hash table
		static_cast<impl::xml_document_struct*>(_root)->hash.clear();
	#endif

		_root = NULL;
	}

#ifdef PUGIXML_HAS_MOVE
	PUGI_IMPL_FN void xml_document::_move(xml_document& rhs) PUGIXML_NOEXCEPT_IF_NOT_COMPACT
	{
		impl::xml_document_struct* doc = static_cast<impl::xml_document_struct*>(_root);
		impl::xml_document_struct* other = static_cast<impl::xml_document_struct*>(rhs._root);

		// save first child pointer for later; this needs hash access
		xml_node_struct* other_first_child = other->first_child;

	#ifdef PUGIXML_COMPACT
		// reserve space for the hash table up front; this is the only operation that can fail
		// if it does, we have no choice but to throw (if we have exceptions)
		if (other_first_child)
		{
			size_t other_children = 0;
			for (xml_node_struct* node = other_first_child; node; node = node->next_sibling)
				other_children++;

			// in compact mode, each pointer assignment could result in a hash table request
			// during move, we have to relocate document first_child and parents of all children
			// normally there's just one child and its parent has a pointerless encoding but
			// we assume the worst here
			if (!other->_hash->reserve(other_children + 1))
			{
			#ifdef PUGIXML_NO_EXCEPTIONS
				return;
			#else
				throw std::bad_alloc();
			#endif
			}
		}
	#endif

		// move allocation state
		// note that other->_root may point to the embedded document page, in which case we should keep original (empty) state
		if (other->_root != PUGI_IMPL_GETPAGE(other))
		{
			doc->_root = other->_root;
			doc->_busy_size = other->_busy_size;
		}

		// move buffer state
		doc->buffer = other->buffer;
		doc->extra_buffers = other->extra_buffers;
		_buffer = rhs._buffer;

	#ifdef PUGIXML_COMPACT
		// move compact hash; note that the hash table can have pointers to other but they will be "inactive", similarly to nodes removed with remove_child
		doc->hash = other->hash;
		doc->_hash = &doc->hash;

		// make sure we don't access other hash up until the end when we reinitialize other document
		other->_hash = NULL;
	#endif

		// move page structure
		impl::xml_memory_page* doc_page = PUGI_IMPL_GETPAGE(doc);
		assert(doc_page && !doc_page->prev && !doc_page->next);

		impl::xml_memory_page* other_page = PUGI_IMPL_GETPAGE(other);
		assert(other_page && !other_page->prev);

		// relink pages since root page is embedded into xml_document
		if (impl::xml_memory_page* page = other_page->next)
		{
			assert(page->prev == other_page);

			page->prev = doc_page;

			doc_page->next = page;
			other_page->next = NULL;
		}

		// make sure pages point to the correct document state
		for (impl::xml_memory_page* page = doc_page->next; page; page = page->next)
		{
			assert(page->allocator == other);

			page->allocator = doc;

		#ifdef PUGIXML_COMPACT
			// this automatically migrates most children between documents and prevents ->parent assignment from allocating
			if (page->compact_shared_parent == other)
				page->compact_shared_parent = doc;
		#endif
		}

		// move tree structure
		assert(!doc->first_child);

		doc->first_child = other_first_child;

		for (xml_node_struct* node = other_first_child; node; node = node->next_sibling)
		{
		#ifdef PUGIXML_COMPACT
			// most children will have migrated when we reassigned compact_shared_parent
			assert(node->parent == other || node->parent == doc);

			node->parent = doc;
		#else
			assert(node->parent == other);
			node->parent = doc;
		#endif
		}

		// reset other document
		new (other) impl::xml_document_struct(PUGI_IMPL_GETPAGE(other));
		rhs._buffer = NULL;
	}
#endif

#ifndef PUGIXML_NO_STL
	PUGI_IMPL_FN xml_parse_result xml_document::load(std::basic_istream<char>& stream, unsigned int options, xml_encoding encoding)
	{
		reset();

		return impl::load_stream_impl(static_cast<impl::xml_document_struct*>(_root), stream, options, encoding, &_buffer);
	}

	PUGI_IMPL_FN xml_parse_result xml_document::load(std::basic_istream<wchar_t>& stream, unsigned int options)
	{
		reset();

		return impl::load_stream_impl(static_cast<impl::xml_document_struct*>(_root), stream, options, encoding_wchar, &_buffer);
	}
#endif

	PUGI_IMPL_FN xml_parse_result xml_document::load_string(const char_t* contents, unsigned int options)
	{
		// Force native encoding (skip autodetection)
	#ifdef PUGIXML_WCHAR_MODE
		xml_encoding encoding = encoding_wchar;
	#else
		xml_encoding encoding = encoding_utf8;
	#endif

		return load_buffer(contents, impl::strlength(contents) * sizeof(char_t), options, encoding);
	}

	PUGI_IMPL_FN xml_parse_result xml_document::load(const char_t* contents, unsigned int options)
	{
		return load_string(contents, options);
	}

	PUGI_IMPL_FN xml_parse_result xml_document::load_file(const char* path_, unsigned int options, xml_encoding encoding)
	{
		reset();

		using impl::auto_deleter; // MSVC7 workaround
		auto_deleter<FILE> file(impl::open_file(path_, "rb"), impl::close_file);

		return impl::load_file_impl(static_cast<impl::xml_document_struct*>(_root), file.data, options, encoding, &_buffer);
	}

	PUGI_IMPL_FN xml_parse_result xml_document::load_file(const wchar_t* path_, unsigned int options, xml_encoding encoding)
	{
		reset();

		using impl::auto_deleter; // MSVC7 workaround
		auto_deleter<FILE> file(impl::open_file_wide(path_, L"rb"), impl::close_file);

		return impl::load_file_impl(static_cast<impl::xml_document_struct*>(_root), file.data, options, encoding, &_buffer);
	}

	PUGI_IMPL_FN xml_parse_result xml_document::load_buffer(const void* contents, size_t size, unsigned int options, xml_encoding encoding)
	{
		reset();

		return impl::load_buffer_impl(static_cast<impl::xml_document_struct*>(_root), _root, const_cast<void*>(contents), size, options, encoding, false, false, &_buffer);
	}

	PUGI_IMPL_FN xml_parse_result xml_document::load_buffer_inplace(void* contents, size_t size, unsigned int options, xml_encoding encoding)
	{
		reset();

		return impl::load_buffer_impl(static_cast<impl::xml_document_struct*>(_root), _root, contents, size, options, encoding, true, false, &_buffer);
	}

	PUGI_IMPL_FN xml_parse_result xml_document::load_buffer_inplace_own(void* contents, size_t size, unsigned int options, xml_encoding encoding)
	{
		reset();

		return impl::load_buffer_impl(static_cast<impl::xml_document_struct*>(_root), _root, contents, size, options, encoding, true, true, &_buffer);
	}

	PUGI_IMPL_FN void xml_document::save(xml_writer& writer, const char_t* indent, unsigned int flags, xml_encoding encoding) const
	{
		impl::xml_buffered_writer buffered_writer(writer, encoding);

		if ((flags & format_write_bom) && buffered_writer.encoding != encoding_latin1)
		{
			// BOM always represents the codepoint U+FEFF, so just write it in native encoding
		#ifdef PUGIXML_WCHAR_MODE
			unsigned int bom = 0xfeff;
			buffered_writer.write(static_cast<wchar_t>(bom));
		#else
			buffered_writer.write('\xef', '\xbb', '\xbf');
		#endif
		}

		if (!(flags & format_no_declaration) && !impl::has_declaration(_root))
		{
			buffered_writer.write_string(PUGIXML_TEXT("<?xml version=\"1.0\""));
			if (buffered_writer.encoding == encoding_latin1) buffered_writer.write_string(PUGIXML_TEXT(" encoding=\"ISO-8859-1\""));
			buffered_writer.write('?', '>');
			if (!(flags & format_raw)) buffered_writer.write('\n');
		}

		impl::node_output(buffered_writer, _root, indent, flags, 0);

		buffered_writer.flush();
	}

#ifndef PUGIXML_NO_STL
	PUGI_IMPL_FN void xml_document::save(std::basic_ostream<char>& stream, const char_t* indent, unsigned int flags, xml_encoding encoding) const
	{
		xml_writer_stream writer(stream);

		save(writer, indent, flags, encoding);
	}

	PUGI_IMPL_FN void xml_document::save(std::basic_ostream<wchar_t>& stream, const char_t* indent, unsigned int flags) const
	{
		xml_writer_stream writer(stream);

		save(writer, indent, flags, encoding_wchar);
	}
#endif

	PUGI_IMPL_FN bool xml_document::save_file(const char* path_, const char_t* indent, unsigned int flags, xml_encoding encoding) const
	{
		using impl::auto_deleter; // MSVC7 workaround
		auto_deleter<FILE> file(impl::open_file(path_, (flags & format_save_file_text) ? "w" : "wb"), impl::close_file);

		return impl::save_file_impl(*this, file.data, indent, flags, encoding) && fclose(file.release()) == 0;
	}

	PUGI_IMPL_FN bool xml_document::save_file(const wchar_t* path_, const char_t* indent, unsigned int flags, xml_encoding encoding) const
	{
		using impl::auto_deleter; // MSVC7 workaround
		auto_deleter<FILE> file(impl::open_file_wide(path_, (flags & format_save_file_text) ? L"w" : L"wb"), impl::close_file);

		return impl::save_file_impl(*this, file.data, indent, flags, encoding) && fclose(file.release()) == 0;
	}

	PUGI_IMPL_FN xml_node xml_document::document_element() const
	{
		assert(_root);

		for (xml_node_struct* i = _root->first_child; i; i = i->next_sibling)
			if (PUGI_IMPL_NODETYPE(i) == node_element)
				return xml_node(i);

		return xml_node();
	}

#ifndef PUGIXML_NO_STL
	PUGI_IMPL_FN std::string PUGIXML_FUNCTION as_utf8(const wchar_t* str)
	{
		assert(str);

		return impl::as_utf8_impl(str, impl::strlength_wide(str));
	}

	PUGI_IMPL_FN std::string PUGIXML_FUNCTION as_utf8(const std::basic_string<wchar_t>& str)
	{
		return impl::as_utf8_impl(str.c_str(), str.size());
	}

	PUGI_IMPL_FN std::basic_string<wchar_t> PUGIXML_FUNCTION as_wide(const char* str)
	{
		assert(str);

		return impl::as_wide_impl(str, strlen(str));
	}

	PUGI_IMPL_FN std::basic_string<wchar_t> PUGIXML_FUNCTION as_wide(const std::string& str)
	{
		return impl::as_wide_impl(str.c_str(), str.size());
	}
#endif

	PUGI_IMPL_FN void PUGIXML_FUNCTION set_memory_management_functions(allocation_function allocate, deallocation_function deallocate)
	{
		impl::xml_memory::allocate = allocate;
		impl::xml_memory::deallocate = deallocate;
	}

	PUGI_IMPL_FN allocation_function PUGIXML_FUNCTION get_memory_allocation_function()
	{
		return impl::xml_memory::allocate;
	}

	PUGI_IMPL_FN deallocation_function PUGIXML_FUNCTION get_memory_deallocation_function()
	{
		return impl::xml_memory::deallocate;
	}
}

#if !defined(PUGIXML_NO_STL) && (defined(_MSC_VER) || defined(__ICC))
namespace std
{
	// Workarounds for (non-standard) iterator category detection for older versions (MSVC7/IC8 and earlier)
	PUGI_IMPL_FN std::bidirectional_iterator_tag _Iter_cat(const pugi::xml_node_iterator&)
	{
		return std::bidirectional_iterator_tag();
	}

	PUGI_IMPL_FN std::bidirectional_iterator_tag _Iter_cat(const pugi::xml_attribute_iterator&)
	{
		return std::bidirectional_iterator_tag();
	}

	PUGI_IMPL_FN std::bidirectional_iterator_tag _Iter_cat(const pugi::xml_named_node_iterator&)
	{
		return std::bidirectional_iterator_tag();
	}
}
#endif

#if !defined(PUGIXML_NO_STL) && defined(__SUNPRO_CC)
namespace std
{
	// Workarounds for (non-standard) iterator category detection
	PUGI_IMPL_FN std::bidirectional_iterator_tag __iterator_category(const pugi::xml_node_iterator&)
	{
		return std::bidirectional_iterator_tag();
	}

	PUGI_IMPL_FN std::bidirectional_iterator_tag __iterator_category(const pugi::xml_attribute_iterator&)
	{
		return std::bidirectional_iterator_tag();
	}

	PUGI_IMPL_FN std::bidirectional_iterator_tag __iterator_category(const pugi::xml_named_node_iterator&)
	{
		return std::bidirectional_iterator_tag();
	}
}
#endif

#ifndef PUGIXML_NO_XPATH
// STL replacements
PUGI_IMPL_NS_BEGIN
	struct equal_to
	{
		template <typename T> bool operator()(const T& lhs, const T& rhs) const
		{
			return lhs == rhs;
		}
	};

	struct not_equal_to
	{
		template <typename T> bool operator()(const T& lhs, const T& rhs) const
		{
			return lhs != rhs;
		}
	};

	struct less
	{
		template <typename T> bool operator()(const T& lhs, const T& rhs) const
		{
			return lhs < rhs;
		}
	};

	struct less_equal
	{
		template <typename T> bool operator()(const T& lhs, const T& rhs) const
		{
			return lhs <= rhs;
		}
	};

	template <typename T> inline void swap(T& lhs, T& rhs)
	{
		T temp = lhs;
		lhs = rhs;
		rhs = temp;
	}

	template <typename I, typename Pred> PUGI_IMPL_FN I min_element(I begin, I end, const Pred& pred)
	{
		I result = begin;

		for (I it = begin + 1; it != end; ++it)
			if (pred(*it, *result))
				result = it;

		return result;
	}

	template <typename I> PUGI_IMPL_FN void reverse(I begin, I end)
	{
		while (end - begin > 1)
			swap(*begin++, *--end);
	}

	template <typename I> PUGI_IMPL_FN I unique(I begin, I end)
	{
		// fast skip head
		while (end - begin > 1 && *begin != *(begin + 1))
			begin++;

		if (begin == end)
			return begin;

		// last written element
		I write = begin++;

		// merge unique elements
		while (begin != end)
		{
			if (*begin != *write)
				*++write = *begin++;
			else
				begin++;
		}

		// past-the-end (write points to live element)
		return write + 1;
	}

	template <typename T, typename Pred> PUGI_IMPL_FN void insertion_sort(T* begin, T* end, const Pred& pred)
	{
		if (begin == end)
			return;

		for (T* it = begin + 1; it != end; ++it)
		{
			T val = *it;
			T* hole = it;

			// move hole backwards
			while (hole > begin && pred(val, *(hole - 1)))
			{
				*hole = *(hole - 1);
				hole--;
			}

			// fill hole with element
			*hole = val;
		}
	}

	template <typename I, typename Pred> inline I median3(I first, I middle, I last, const Pred& pred)
	{
		if (pred(*middle, *first))
			swap(middle, first);
		if (pred(*last, *middle))
			swap(last, middle);
		if (pred(*middle, *first))
			swap(middle, first);

		return middle;
	}

	template <typename T, typename Pred> PUGI_IMPL_FN void partition3(T* begin, T* end, T pivot, const Pred& pred, T** out_eqbeg, T** out_eqend)
	{
		// invariant: array is split into 4 groups: = < ? > (each variable denotes the boundary between the groups)
		T* eq = begin;
		T* lt = begin;
		T* gt = end;

		while (lt < gt)
		{
			if (pred(*lt, pivot))
				lt++;
			else if (*lt == pivot)
				swap(*eq++, *lt++);
			else
				swap(*lt, *--gt);
		}

		// we now have just 4 groups: = < >; move equal elements to the middle
		T* eqbeg = gt;

		for (T* it = begin; it != eq; ++it)
			swap(*it, *--eqbeg);

		*out_eqbeg = eqbeg;
		*out_eqend = gt;
	}

	template <typename I, typename Pred> PUGI_IMPL_FN void sort(I begin, I end, const Pred& pred)
	{
		// sort large chunks
		while (end - begin > 16)
		{
			// find median element
			I middle = begin + (end - begin) / 2;
			I median = median3(begin, middle, end - 1, pred);

			// partition in three chunks (< = >)
			I eqbeg, eqend;
			partition3(begin, end, *median, pred, &eqbeg, &eqend);

			// loop on larger half
			if (eqbeg - begin > end - eqend)
			{
				sort(eqend, end, pred);
				end = eqbeg;
			}
			else
			{
				sort(begin, eqbeg, pred);
				begin = eqend;
			}
		}

		// insertion sort small chunk
		insertion_sort(begin, end, pred);
	}

	PUGI_IMPL_FN bool hash_insert(const void** table, size_t size, const void* key)
	{
		assert(key);

		unsigned int h = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(key));

		// MurmurHash3 32-bit finalizer
		h ^= h >> 16;
		h *= 0x85ebca6bu;
		h ^= h >> 13;
		h *= 0xc2b2ae35u;
		h ^= h >> 16;

		size_t hashmod = size - 1;
		size_t bucket = h & hashmod;

		for (size_t probe = 0; probe <= hashmod; ++probe)
		{
			if (table[bucket] == NULL)
			{
				table[bucket] = key;
				return true;
			}

			if (table[bucket] == key)
				return false;

			// hash collision, quadratic probing
			bucket = (bucket + probe + 1) & hashmod;
		}

		assert(false && "Hash table is full"); // unreachable
		return false;
	}
PUGI_IMPL_NS_END

// Allocator used for AST and evaluation stacks
PUGI_IMPL_NS_BEGIN
	static const size_t xpath_memory_page_size =
	#ifdef PUGIXML_MEMORY_XPATH_PAGE_SIZE
		PUGIXML_MEMORY_XPATH_PAGE_SIZE
	#else
		4096
	#endif
		;

	static const uintptr_t xpath_memory_block_alignment = sizeof(double) > sizeof(void*) ? sizeof(double) : sizeof(void*);

	struct xpath_memory_block
	{
		xpath_memory_block* next;
		size_t capacity;

		union
		{
			char data[xpath_memory_page_size];
			double alignment;
		};
	};

	struct xpath_allocator
	{
		xpath_memory_block* _root;
		size_t _root_size;
		bool* _error;

		xpath_allocator(xpath_memory_block* root, bool* error = NULL): _root(root), _root_size(0), _error(error)
		{
		}

		void* allocate(size_t size)
		{
			// round size up to block alignment boundary
			size = (size + xpath_memory_block_alignment - 1) & ~(xpath_memory_block_alignment - 1);

			if (_root_size + size <= _root->capacity)
			{
				void* buf = &_root->data[0] + _root_size;
				_root_size += size;
				return buf;
			}
			else
			{
				// make sure we have at least 1/4th of the page free after allocation to satisfy subsequent allocation requests
				size_t block_capacity_base = sizeof(_root->data);
				size_t block_capacity_req = size + block_capacity_base / 4;
				size_t block_capacity = (block_capacity_base > block_capacity_req) ? block_capacity_base : block_capacity_req;

				size_t block_size = block_capacity + offsetof(xpath_memory_block, data);

				xpath_memory_block* block = static_cast<xpath_memory_block*>(xml_memory::allocate(block_size));
				if (!block)
				{
					if (_error) *_error = true;
					return NULL;
				}

				block->next = _root;
				block->capacity = block_capacity;

				_root = block;
				_root_size = size;

				return block->data;
			}
		}

		void* reallocate(void* ptr, size_t old_size, size_t new_size)
		{
			// round size up to block alignment boundary
			old_size = (old_size + xpath_memory_block_alignment - 1) & ~(xpath_memory_block_alignment - 1);
			new_size = (new_size + xpath_memory_block_alignment - 1) & ~(xpath_memory_block_alignment - 1);

			// we can only reallocate the last object
			assert(ptr == NULL || static_cast<char*>(ptr) + old_size == &_root->data[0] + _root_size);

			// try to reallocate the object inplace
			if (ptr && _root_size - old_size + new_size <= _root->capacity)
			{
				_root_size = _root_size - old_size + new_size;
				return ptr;
			}

			// allocate a new block
			void* result = allocate(new_size);
			if (!result) return NULL;

			// we have a new block
			if (ptr)
			{
				// copy old data (we only support growing)
				assert(new_size >= old_size);
				memcpy(result, ptr, old_size);

				// free the previous page if it had no other objects
				assert(_root->data == result);
				assert(_root->next);

				if (_root->next->data == ptr)
				{
					// deallocate the whole page, unless it was the first one
					xpath_memory_block* next = _root->next->next;

					if (next)
					{
						xml_memory::deallocate(_root->next);
						_root->next = next;
					}
				}
			}

			return result;
		}

		void revert(const xpath_allocator& state)
		{
			// free all new pages
			xpath_memory_block* cur = _root;

			while (cur != state._root)
			{
				xpath_memory_block* next = cur->next;

				xml_memory::deallocate(cur);

				cur = next;
			}

			// restore state
			_root = state._root;
			_root_size = state._root_size;
		}

		void release()
		{
			xpath_memory_block* cur = _root;
			assert(cur);

			while (cur->next)
			{
				xpath_memory_block* next = cur->next;

				xml_memory::deallocate(cur);

				cur = next;
			}
		}
	};

	struct xpath_allocator_capture
	{
		xpath_allocator_capture(xpath_allocator* alloc): _target(alloc), _state(*alloc)
		{
		}

		~xpath_allocator_capture()
		{
			_target->revert(_state);
		}

		xpath_allocator* _target;
		xpath_allocator _state;
	};

	struct xpath_stack
	{
		xpath_allocator* result;
		xpath_allocator* temp;
	};

	struct xpath_stack_data
	{
		xpath_memory_block blocks[2];
		xpath_allocator result;
		xpath_allocator temp;
		xpath_stack stack;
		bool oom;

		xpath_stack_data(): result(blocks + 0, &oom), temp(blocks + 1, &oom), oom(false)
		{
			blocks[0].next = blocks[1].next = NULL;
			blocks[0].capacity = blocks[1].capacity = sizeof(blocks[0].data);

			stack.result = &result;
			stack.temp = &temp;
		}

		~xpath_stack_data()
		{
			result.release();
			temp.release();
		}
	};
PUGI_IMPL_NS_END

// String class
PUGI_IMPL_NS_BEGIN
	class xpath_string
	{
		const char_t* _buffer;
		bool _uses_heap;
		size_t _length_heap;

		static char_t* duplicate_string(const char_t* string, size_t length, xpath_allocator* alloc)
		{
			char_t* result = static_cast<char_t*>(alloc->allocate((length + 1) * sizeof(char_t)));
			if (!result) return NULL;

			memcpy(result, string, length * sizeof(char_t));
			result[length] = 0;

			return result;
		}

		xpath_string(const char_t* buffer, bool uses_heap_, size_t length_heap): _buffer(buffer), _uses_heap(uses_heap_), _length_heap(length_heap)
		{
		}

	public:
		static xpath_string from_const(const char_t* str)
		{
			return xpath_string(str, false, 0);
		}

		static xpath_string from_heap_preallocated(const char_t* begin, const char_t* end)
		{
			assert(begin <= end && *end == 0);

			return xpath_string(begin, true, static_cast<size_t>(end - begin));
		}

		static xpath_string from_heap(const char_t* begin, const char_t* end, xpath_allocator* alloc)
		{
			assert(begin <= end);

			if (begin == end)
				return xpath_string();

			size_t length = static_cast<size_t>(end - begin);
			const char_t* data = duplicate_string(begin, length, alloc);

			return data ? xpath_string(data, true, length) : xpath_string();
		}

		xpath_string(): _buffer(PUGIXML_TEXT("")), _uses_heap(false), _length_heap(0)
		{
		}

		void append(const xpath_string& o, xpath_allocator* alloc)
		{
			// skip empty sources
			if (!*o._buffer) return;

			// fast append for constant empty target and constant source
			if (!*_buffer && !_uses_heap && !o._uses_heap)
			{
				_buffer = o._buffer;
			}
			else
			{
				// need to make heap copy
				size_t target_length = length();
				size_t source_length = o.length();
				size_t result_length = target_length + source_length;

				// allocate new buffer
				char_t* result = static_cast<char_t*>(alloc->reallocate(_uses_heap ? const_cast<char_t*>(_buffer) : NULL, (target_length + 1) * sizeof(char_t), (result_length + 1) * sizeof(char_t)));
				if (!result) return;

				// append first string to the new buffer in case there was no reallocation
				if (!_uses_heap) memcpy(result, _buffer, target_length * sizeof(char_t));

				// append second string to the new buffer
				memcpy(result + target_length, o._buffer, source_length * sizeof(char_t));
				result[result_length] = 0;

				// finalize
				_buffer = result;
				_uses_heap = true;
				_length_heap = result_length;
			}
		}

		const char_t* c_str() const
		{
			return _buffer;
		}

		size_t length() const
		{
			return _uses_heap ? _length_heap : strlength(_buffer);
		}

		char_t* data(xpath_allocator* alloc)
		{
			// make private heap copy
			if (!_uses_heap)
			{
				size_t length_ = strlength(_buffer);
				const char_t* data_ = duplicate_string(_buffer, length_, alloc);

				if (!data_) return NULL;

				_buffer = data_;
				_uses_heap = true;
				_length_heap = length_;
			}

			return const_cast<char_t*>(_buffer);
		}

		bool empty() const
		{
			return *_buffer == 0;
		}

		bool operator==(const xpath_string& o) const
		{
			return strequal(_buffer, o._buffer);
		}

		bool operator!=(const xpath_string& o) const
		{
			return !strequal(_buffer, o._buffer);
		}

		bool uses_heap() const
		{
			return _uses_heap;
		}
	};
PUGI_IMPL_NS_END

PUGI_IMPL_NS_BEGIN
	PUGI_IMPL_FN bool starts_with(const char_t* string, const char_t* pattern)
	{
		while (*pattern && *string == *pattern)
		{
			string++;
			pattern++;
		}

		return *pattern == 0;
	}

	PUGI_IMPL_FN const char_t* find_char(const char_t* s, char_t c)
	{
	#ifdef PUGIXML_WCHAR_MODE
		return wcschr(s, c);
	#else
		return strchr(s, c);
	#endif
	}

	PUGI_IMPL_FN const char_t* find_substring(const char_t* s, const char_t* p)
	{
	#ifdef PUGIXML_WCHAR_MODE
		// MSVC6 wcsstr bug workaround (if s is empty it always returns 0)
		return (*p == 0) ? s : wcsstr(s, p);
	#else
		return strstr(s, p);
	#endif
	}

	// Converts symbol to lower case, if it is an ASCII one
	PUGI_IMPL_FN char_t tolower_ascii(char_t ch)
	{
		return static_cast<unsigned int>(ch - 'A') < 26 ? static_cast<char_t>(ch | ' ') : ch;
	}

	PUGI_IMPL_FN xpath_string string_value(const xpath_node& na, xpath_allocator* alloc)
	{
		if (na.attribute())
			return xpath_string::from_const(na.attribute().value());
		else
		{
			xml_node n = na.node();

			switch (n.type())
			{
			case node_pcdata:
			case node_cdata:
			case node_comment:
			case node_pi:
				return xpath_string::from_const(n.value());

			case node_document:
			case node_element:
			{
				xpath_string result;

				// element nodes can have value if parse_embed_pcdata was used
				if (n.value()[0])
					result.append(xpath_string::from_const(n.value()), alloc);

				xml_node cur = n.first_child();

				while (cur && cur != n)
				{
					if (cur.type() == node_pcdata || cur.type() == node_cdata)
						result.append(xpath_string::from_const(cur.value()), alloc);

					if (cur.first_child())
						cur = cur.first_child();
					else if (cur.next_sibling())
						cur = cur.next_sibling();
					else
					{
						while (!cur.next_sibling() && cur != n)
							cur = cur.parent();

						if (cur != n) cur = cur.next_sibling();
					}
				}

				return result;
			}

			default:
				return xpath_string();
			}
		}
	}

	PUGI_IMPL_FN bool node_is_before_sibling(xml_node_struct* ln, xml_node_struct* rn)
	{
		assert(ln->parent == rn->parent);

		// there is no common ancestor (the shared parent is null), nodes are from different documents
		if (!ln->parent) return ln < rn;

		// determine sibling order
		xml_node_struct* ls = ln;
		xml_node_struct* rs = rn;

		while (ls && rs)
		{
			if (ls == rn) return true;
			if (rs == ln) return false;

			ls = ls->next_sibling;
			rs = rs->next_sibling;
		}

		// if rn sibling chain ended ln must be before rn
		return !rs;
	}

	PUGI_IMPL_FN bool node_is_before(xml_node_struct* ln, xml_node_struct* rn)
	{
		// find common ancestor at the same depth, if any
		xml_node_struct* lp = ln;
		xml_node_struct* rp = rn;

		while (lp && rp && lp->parent != rp->parent)
		{
			lp = lp->parent;
			rp = rp->parent;
		}

		// parents are the same!
		if (lp && rp) return node_is_before_sibling(lp, rp);

		// nodes are at different depths, need to normalize heights
		bool left_higher = !lp;

		while (lp)
		{
			lp = lp->parent;
			ln = ln->parent;
		}

		while (rp)
		{
			rp = rp->parent;
			rn = rn->parent;
		}

		// one node is the ancestor of the other
		if (ln == rn) return left_higher;

		// find common ancestor... again
		while (ln->parent != rn->parent)
		{
			ln = ln->parent;
			rn = rn->parent;
		}

		return node_is_before_sibling(ln, rn);
	}

	PUGI_IMPL_FN bool node_is_ancestor(xml_node_struct* parent, xml_node_struct* node)
	{
		while (node && node != parent) node = node->parent;

		return parent && node == parent;
	}

	PUGI_IMPL_FN const void* document_buffer_order(const xpath_node& xnode)
	{
		xml_node_struct* node = xnode.node().internal_object();

		if (node)
		{
			if ((get_document(node).header & xml_memory_page_contents_shared_mask) == 0)
			{
				if (node->name && (node->header & impl::xml_memory_page_name_allocated_or_shared_mask) == 0) return node->name;
				if (node->value && (node->header & impl::xml_memory_page_value_allocated_or_shared_mask) == 0) return node->value;
			}

			return NULL;
		}

		xml_attribute_struct* attr = xnode.attribute().internal_object();

		if (attr)
		{
			if ((get_document(attr).header & xml_memory_page_contents_shared_mask) == 0)
			{
				if ((attr->header & impl::xml_memory_page_name_allocated_or_shared_mask) == 0) return attr->name;
				if ((attr->header & impl::xml_memory_page_value_allocated_or_shared_mask) == 0) return attr->value;
			}

			return NULL;
		}

		return NULL;
	}

	struct document_order_comparator
	{
		bool operator()(const xpath_node& lhs, const xpath_node& rhs) const
		{
			// optimized document order based check
			const void* lo = document_buffer_order(lhs);
			const void* ro = document_buffer_order(rhs);

			if (lo && ro) return lo < ro;

			// slow comparison
			xml_node ln = lhs.node(), rn = rhs.node();

			// compare attributes
			if (lhs.attribute() && rhs.attribute())
			{
				// shared parent
				if (lhs.parent() == rhs.parent())
				{
					// determine sibling order
					for (xml_attribute a = lhs.attribute(); a; a = a.next_attribute())
						if (a == rhs.attribute())
							return true;

					return false;
				}

				// compare attribute parents
				ln = lhs.parent();
				rn = rhs.parent();
			}
			else if (lhs.attribute())
			{
				// attributes go after the parent element
				if (lhs.parent() == rhs.node()) return false;

				ln = lhs.parent();
			}
			else if (rhs.attribute())
			{
				// attributes go after the parent element
				if (rhs.parent() == lhs.node()) return true;

				rn = rhs.parent();
			}

			if (ln == rn) return false;

			if (!ln || !rn) return ln < rn;

			return node_is_before(ln.internal_object(), rn.internal_object());
		}
	};

	PUGI_IMPL_FN double gen_nan()
	{
	#if defined(__STDC_IEC_559__) || ((FLT_RADIX - 0 == 2) && (FLT_MAX_EXP - 0 == 128) && (FLT_MANT_DIG - 0 == 24))
		PUGI_IMPL_STATIC_ASSERT(sizeof(float) == sizeof(uint32_t));
		typedef uint32_t UI; // BCC5 workaround
		union { float f; UI i; } u;
		u.i = 0x7fc00000;
		return double(u.f);
	#else
		// fallback
		const volatile double zero = 0.0;
		return zero / zero;
	#endif
	}

	PUGI_IMPL_FN bool is_nan(double value)
	{
	#if defined(PUGI_IMPL_MSVC_CRT_VERSION) || defined(__BORLANDC__)
		return !!_isnan(value);
	#elif defined(fpclassify) && defined(FP_NAN)
		return fpclassify(value) == FP_NAN;
	#else
		// fallback
		const volatile double v = value;
		return v != v;
	#endif
	}

	PUGI_IMPL_FN const char_t* convert_number_to_string_special(double value)
	{
	#if defined(PUGI_IMPL_MSVC_CRT_VERSION) || defined(__BORLANDC__)
		if (_finite(value)) return (value == 0) ? PUGIXML_TEXT("0") : 0;
		if (_isnan(value)) return PUGIXML_TEXT("NaN");
		return value > 0 ? PUGIXML_TEXT("Infinity") : PUGIXML_TEXT("-Infinity");
	#elif defined(fpclassify) && defined(FP_NAN) && defined(FP_INFINITE) && defined(FP_ZERO)
		switch (fpclassify(value))
		{
		case FP_NAN:
			return PUGIXML_TEXT("NaN");

		case FP_INFINITE:
			return value > 0 ? PUGIXML_TEXT("Infinity") : PUGIXML_TEXT("-Infinity");

		case FP_ZERO:
			return PUGIXML_TEXT("0");

		default:
			return 0;
		}
	#else
		// fallback
		const volatile double v = value;

		if (v == 0) return PUGIXML_TEXT("0");
		if (v != v) return PUGIXML_TEXT("NaN");
		if (v * 2 == v) return value > 0 ? PUGIXML_TEXT("Infinity") : PUGIXML_TEXT("-Infinity");
		return NULL;
	#endif
	}

	PUGI_IMPL_FN bool convert_number_to_boolean(double value)
	{
		return (value != 0 && !is_nan(value));
	}

	PUGI_IMPL_FN void truncate_zeros(char* begin, char* end)
	{
		while (begin != end && end[-1] == '0') end--;

		*end = 0;
	}

	// gets mantissa digits in the form of 0.xxxxx with 0. implied and the exponent
#if defined(PUGI_IMPL_MSVC_CRT_VERSION) && PUGI_IMPL_MSVC_CRT_VERSION >= 1400
	PUGI_IMPL_FN void convert_number_to_mantissa_exponent(double value, char (&buffer)[32], char** out_mantissa, int* out_exponent)
	{
		// get base values
		int sign, exponent;
		_ecvt_s(buffer, sizeof(buffer), value, DBL_DIG + 1, &exponent, &sign);

		// truncate redundant zeros
		truncate_zeros(buffer, buffer + strlen(buffer));

		// fill results
		*out_mantissa = buffer;
		*out_exponent = exponent;
	}
#else
	PUGI_IMPL_FN void convert_number_to_mantissa_exponent(double value, char (&buffer)[32], char** out_mantissa, int* out_exponent)
	{
		// get a scientific notation value with IEEE DBL_DIG decimals
		PUGI_IMPL_SNPRINTF(buffer, "%.*e", DBL_DIG, value);

		// get the exponent (possibly negative)
		char* exponent_string = strchr(buffer, 'e');
		assert(exponent_string);

		int exponent = atoi(exponent_string + 1);

		// extract mantissa string: skip sign
		char* mantissa = buffer[0] == '-' ? buffer + 1 : buffer;
		assert(mantissa[0] != '0' && (mantissa[1] == '.' || mantissa[1] == ','));

		// divide mantissa by 10 to eliminate integer part
		mantissa[1] = mantissa[0];
		mantissa++;
		exponent++;

		// remove extra mantissa digits and zero-terminate mantissa
		truncate_zeros(mantissa, exponent_string);

		// fill results
		*out_mantissa = mantissa;
		*out_exponent = exponent;
	}
#endif

	PUGI_IMPL_FN xpath_string convert_number_to_string(double value, xpath_allocator* alloc)
	{
		// try special number conversion
		const char_t* special = convert_number_to_string_special(value);
		if (special) return xpath_string::from_const(special);

		// get mantissa + exponent form
		char mantissa_buffer[32];

		char* mantissa;
		int exponent;
		convert_number_to_mantissa_exponent(value, mantissa_buffer, &mantissa, &exponent);

		// allocate a buffer of suitable length for the number
		size_t result_size = strlen(mantissa_buffer) + (exponent > 0 ? exponent : -exponent) + 4;
		char_t* result = static_cast<char_t*>(alloc->allocate(sizeof(char_t) * result_size));
		if (!result) return xpath_string();

		// make the number!
		char_t* s = result;

		// sign
		if (value < 0) *s++ = '-';

		// integer part
		if (exponent <= 0)
		{
			*s++ = '0';
		}
		else
		{
			while (exponent > 0)
			{
				assert(*mantissa == 0 || static_cast<unsigned int>(*mantissa - '0') <= 9);
				*s++ = *mantissa ? *mantissa++ : '0';
				exponent--;
			}
		}

		// fractional part
		if (*mantissa)
		{
			// decimal point
			*s++ = '.';

			// extra zeroes from negative exponent
			while (exponent < 0)
			{
				*s++ = '0';
				exponent++;
			}

			// extra mantissa digits
			while (*mantissa)
			{
				assert(static_cast<unsigned int>(*mantissa - '0') <= 9);
				*s++ = *mantissa++;
			}
		}

		// zero-terminate
		assert(s < result + result_size);
		*s = 0;

		return xpath_string::from_heap_preallocated(result, s);
	}

	PUGI_IMPL_FN bool check_string_to_number_format(const char_t* string)
	{
		// parse leading whitespace
		while (PUGI_IMPL_IS_CHARTYPE(*string, ct_space)) ++string;

		// parse sign
		if (*string == '-') ++string;

		if (!*string) return false;

		// if there is no integer part, there should be a decimal part with at least one digit
		if (!PUGI_IMPL_IS_CHARTYPEX(string[0], ctx_digit) && (string[0] != '.' || !PUGI_IMPL_IS_CHARTYPEX(string[1], ctx_digit))) return false;

		// parse integer part
		while (PUGI_IMPL_IS_CHARTYPEX(*string, ctx_digit)) ++string;

		// parse decimal part
		if (*string == '.')
		{
			++string;

			while (PUGI_IMPL_IS_CHARTYPEX(*string, ctx_digit)) ++string;
		}

		// parse trailing whitespace
		while (PUGI_IMPL_IS_CHARTYPE(*string, ct_space)) ++string;

		return *string == 0;
	}

	PUGI_IMPL_FN double convert_string_to_number(const char_t* string)
	{
		// check string format
		if (!check_string_to_number_format(string)) return gen_nan();

		// parse string
	#ifdef PUGIXML_WCHAR_MODE
		return wcstod(string, NULL);
	#else
		return strtod(string, NULL);
	#endif
	}

	PUGI_IMPL_FN bool convert_string_to_number_scratch(char_t (&buffer)[32], const char_t* begin, const char_t* end, double* out_result)
	{
		size_t length = static_cast<size_t>(end - begin);
		char_t* scratch = buffer;

		if (length >= sizeof(buffer) / sizeof(buffer[0]))
		{
			// need to make dummy on-heap copy
			scratch = static_cast<char_t*>(xml_memory::allocate((length + 1) * sizeof(char_t)));
			if (!scratch) return false;
		}

		// copy string to zero-terminated buffer and perform conversion
		memcpy(scratch, begin, length * sizeof(char_t));
		scratch[length] = 0;

		*out_result = convert_string_to_number(scratch);

		// free dummy buffer
		if (scratch != buffer) xml_memory::deallocate(scratch);

		return true;
	}

	PUGI_IMPL_FN double round_nearest(double value)
	{
		return floor(value + 0.5);
	}

	PUGI_IMPL_FN double round_nearest_nzero(double value)
	{
		// same as round_nearest, but returns -0 for [-0.5, -0]
		// ceil is used to differentiate between +0 and -0 (we return -0 for [-0.5, -0] and +0 for +0)
		return (value >= -0.5 && value <= 0) ? ceil(value) : floor(value + 0.5);
	}

	PUGI_IMPL_FN const char_t* qualified_name(const xpath_node& node)
	{
		return node.attribute() ? node.attribute().name() : node.node().name();
	}

	PUGI_IMPL_FN const char_t* local_name(const xpath_node& node)
	{
		const char_t* name = qualified_name(node);
		const char_t* p = find_char(name, ':');

		return p ? p + 1 : name;
	}

	struct namespace_uri_predicate
	{
		const char_t* prefix;
		size_t prefix_length;

		namespace_uri_predicate(const char_t* name)
		{
			const char_t* pos = find_char(name, ':');

			prefix = pos ? name : NULL;
			prefix_length = pos ? static_cast<size_t>(pos - name) : 0;
		}

		bool operator()(xml_attribute a) const
		{
			const char_t* name = a.name();

			if (!starts_with(name, PUGIXML_TEXT("xmlns"))) return false;

			return prefix ? name[5] == ':' && strequalrange(name + 6, prefix, prefix_length) : name[5] == 0;
		}
	};

	PUGI_IMPL_FN const char_t* namespace_uri(xml_node node)
	{
		namespace_uri_predicate pred = node.name();

		xml_node p = node;

		while (p)
		{
			xml_attribute a = p.find_attribute(pred);

			if (a) return a.value();

			p = p.parent();
		}

		return PUGIXML_TEXT("");
	}

	PUGI_IMPL_FN const char_t* namespace_uri(xml_attribute attr, xml_node parent)
	{
		namespace_uri_predicate pred = attr.name();

		// Default namespace does not apply to attributes
		if (!pred.prefix) return PUGIXML_TEXT("");

		xml_node p = parent;

		while (p)
		{
			xml_attribute a = p.find_attribute(pred);

			if (a) return a.value();

			p = p.parent();
		}

		return PUGIXML_TEXT("");
	}

	PUGI_IMPL_FN const char_t* namespace_uri(const xpath_node& node)
	{
		return node.attribute() ? namespace_uri(node.attribute(), node.parent()) : namespace_uri(node.node());
	}

	PUGI_IMPL_FN char_t* normalize_space(char_t* buffer)
	{
		char_t* write = buffer;

		for (char_t* it = buffer; *it; )
		{
			char_t ch = *it++;

			if (PUGI_IMPL_IS_CHARTYPE(ch, ct_space))
			{
				// replace whitespace sequence with single space
				while (PUGI_IMPL_IS_CHARTYPE(*it, ct_space)) it++;

				// avoid leading spaces
				if (write != buffer) *write++ = ' ';
			}
			else *write++ = ch;
		}

		// remove trailing space
		if (write != buffer && PUGI_IMPL_IS_CHARTYPE(write[-1], ct_space)) write--;

		// zero-terminate
		*write = 0;

		return write;
	}

	PUGI_IMPL_FN char_t* translate(char_t* buffer, const char_t* from, const char_t* to, size_t to_length)
	{
		char_t* write = buffer;

		while (*buffer)
		{
			PUGI_IMPL_DMC_VOLATILE char_t ch = *buffer++;

			const char_t* pos = find_char(from, ch);

			if (!pos)
				*write++ = ch; // do not process
			else if (static_cast<size_t>(pos - from) < to_length)
				*write++ = to[pos - from]; // replace
		}

		// zero-terminate
		*write = 0;

		return write;
	}

	PUGI_IMPL_FN unsigned char* translate_table_generate(xpath_allocator* alloc, const char_t* from, const char_t* to)
	{
		unsigned char table[128] = {0};

		while (*from)
		{
			unsigned int fc = static_cast<unsigned int>(*from);
			unsigned int tc = static_cast<unsigned int>(*to);

			if (fc >= 128 || tc >= 128)
				return NULL;

			// code=128 means "skip character"
			if (!table[fc])
				table[fc] = static_cast<unsigned char>(tc ? tc : 128);

			from++;
			if (tc) to++;
		}

		for (int i = 0; i < 128; ++i)
			if (!table[i])
				table[i] = static_cast<unsigned char>(i);

		void* result = alloc->allocate(sizeof(table));
		if (!result) return NULL;

		memcpy(result, table, sizeof(table));

		return static_cast<unsigned char*>(result);
	}

	PUGI_IMPL_FN char_t* translate_table(char_t* buffer, const unsigned char* table)
	{
		char_t* write = buffer;

		while (*buffer)
		{
			char_t ch = *buffer++;
			unsigned int index = static_cast<unsigned int>(ch);

			if (index < 128)
			{
				unsigned char code = table[index];

				// code=128 means "skip character" (table size is 128 so 128 can be a special value)
				// this code skips these characters without extra branches
				*write = static_cast<char_t>(code);
				write += 1 - (code >> 7);
			}
			else
			{
				*write++ = ch;
			}
		}

		// zero-terminate
		*write = 0;

		return write;
	}

	inline bool is_xpath_attribute(const char_t* name)
	{
		return !(starts_with(name, PUGIXML_TEXT("xmlns")) && (name[5] == 0 || name[5] == ':'));
	}

	struct xpath_variable_boolean: xpath_variable
	{
		xpath_variable_boolean(): xpath_variable(xpath_type_boolean), value(false)
		{
		}

		bool value;
		char_t name[1];
	};

	struct xpath_variable_number: xpath_variable
	{
		xpath_variable_number(): xpath_variable(xpath_type_number), value(0)
		{
		}

		double value;
		char_t name[1];
	};

	struct xpath_variable_string: xpath_variable
	{
		xpath_variable_string(): xpath_variable(xpath_type_string), value(NULL)
		{
		}

		~xpath_variable_string()
		{
			if (value) xml_memory::deallocate(value);
		}

		char_t* value;
		char_t name[1];
	};

	struct xpath_variable_node_set: xpath_variable
	{
		xpath_variable_node_set(): xpath_variable(xpath_type_node_set)
		{
		}

		xpath_node_set value;
		char_t name[1];
	};

	PUGI_IMPL_FN PUGI_IMPL_UNSIGNED_OVERFLOW unsigned int hash_string(const char_t* str)
	{
		// Jenkins one-at-a-time hash (http://en.wikipedia.org/wiki/Jenkins_hash_function#one-at-a-time)
		unsigned int result = 0;

		while (*str)
		{
			result += static_cast<unsigned int>(*str++);
			result += result << 10;
			result ^= result >> 6;
		}

		result += result << 3;
		result ^= result >> 11;
		result += result << 15;

		return result;
	}

	template <typename T> PUGI_IMPL_FN T* new_xpath_variable(const char_t* name)
	{
		size_t length = strlength(name);
		if (length == 0) return NULL; // empty variable names are invalid

		// $$ we can't use offsetof(T, name) because T is non-POD, so we just allocate additional length characters
		void* memory = xml_memory::allocate(sizeof(T) + length * sizeof(char_t));
		if (!memory) return NULL;

		T* result = new (memory) T();

		memcpy(result->name, name, (length + 1) * sizeof(char_t));

		return result;
	}

	PUGI_IMPL_FN xpath_variable* new_xpath_variable(xpath_value_type type, const char_t* name)
	{
		switch (type)
		{
		case xpath_type_node_set:
			return new_xpath_variable<xpath_variable_node_set>(name);

		case xpath_type_number:
			return new_xpath_variable<xpath_variable_number>(name);

		case xpath_type_string:
			return new_xpath_variable<xpath_variable_string>(name);

		case xpath_type_boolean:
			return new_xpath_variable<xpath_variable_boolean>(name);

		default:
			return NULL;
		}
	}

	template <typename T> PUGI_IMPL_FN void delete_xpath_variable(T* var)
	{
		var->~T();
		xml_memory::deallocate(var);
	}

	PUGI_IMPL_FN void delete_xpath_variable(xpath_value_type type, xpath_variable* var)
	{
		switch (type)
		{
		case xpath_type_node_set:
			delete_xpath_variable(static_cast<xpath_variable_node_set*>(var));
			break;

		case xpath_type_number:
			delete_xpath_variable(static_cast<xpath_variable_number*>(var));
			break;

		case xpath_type_string:
			delete_xpath_variable(static_cast<xpath_variable_string*>(var));
			break;

		case xpath_type_boolean:
			delete_xpath_variable(static_cast<xpath_variable_boolean*>(var));
			break;

		default:
			assert(false && "Invalid variable type"); // unreachable
		}
	}

	PUGI_IMPL_FN bool copy_xpath_variable(xpath_variable* lhs, const xpath_variable* rhs)
	{
		switch (rhs->type())
		{
		case xpath_type_node_set:
			return lhs->set(static_cast<const xpath_variable_node_set*>(rhs)->value);

		case xpath_type_number:
			return lhs->set(static_cast<const xpath_variable_number*>(rhs)->value);

		case xpath_type_string:
			return lhs->set(static_cast<const xpath_variable_string*>(rhs)->value);

		case xpath_type_boolean:
			return lhs->set(static_cast<const xpath_variable_boolean*>(rhs)->value);

		default:
			assert(false && "Invalid variable type"); // unreachable
			return false;
		}
	}

	PUGI_IMPL_FN bool get_variable_scratch(char_t (&buffer)[32], xpath_variable_set* set, const char_t* begin, const char_t* end, xpath_variable** out_result)
	{
		size_t length = static_cast<size_t>(end - begin);
		char_t* scratch = buffer;

		if (length >= sizeof(buffer) / sizeof(buffer[0]))
		{
			// need to make dummy on-heap copy
			scratch = static_cast<char_t*>(xml_memory::allocate((length + 1) * sizeof(char_t)));
			if (!scratch) return false;
		}

		// copy string to zero-terminated buffer and perform lookup
		memcpy(scratch, begin, length * sizeof(char_t));
		scratch[length] = 0;

		*out_result = set->get(scratch);

		// free dummy buffer
		if (scratch != buffer) xml_memory::deallocate(scratch);

		return true;
	}
PUGI_IMPL_NS_END

// Internal node set class
PUGI_IMPL_NS_BEGIN
	PUGI_IMPL_FN xpath_node_set::type_t xpath_get_order(const xpath_node* begin, const xpath_node* end)
	{
		if (end - begin < 2)
			return xpath_node_set::type_sorted;

		document_order_comparator cmp;

		bool first = cmp(begin[0], begin[1]);

		for (const xpath_node* it = begin + 1; it + 1 < end; ++it)
			if (cmp(it[0], it[1]) != first)
				return xpath_node_set::type_unsorted;

		return first ? xpath_node_set::type_sorted : xpath_node_set::type_sorted_reverse;
	}

	PUGI_IMPL_FN xpath_node_set::type_t xpath_sort(xpath_node* begin, xpath_node* end, xpath_node_set::type_t type, bool rev)
	{
		xpath_node_set::type_t order = rev ? xpath_node_set::type_sorted_reverse : xpath_node_set::type_sorted;

		if (type == xpath_node_set::type_unsorted)
		{
			xpath_node_set::type_t sorted = xpath_get_order(begin, end);

			if (sorted == xpath_node_set::type_unsorted)
			{
				sort(begin, end, document_order_comparator());

				type = xpath_node_set::type_sorted;
			}
			else
				type = sorted;
		}

		if (type != order) reverse(begin, end);

		return order;
	}

	PUGI_IMPL_FN xpath_node xpath_first(const xpath_node* begin, const xpath_node* end, xpath_node_set::type_t type)
	{
		if (begin == end) return xpath_node();

		switch (type)
		{
		case xpath_node_set::type_sorted:
			return *begin;

		case xpath_node_set::type_sorted_reverse:
			return *(end - 1);

		case xpath_node_set::type_unsorted:
			return *min_element(begin, end, document_order_comparator());

		default:
			assert(false && "Invalid node set type"); // unreachable
			return xpath_node();
		}
	}

	class xpath_node_set_raw
	{
		xpath_node_set::type_t _type;

		xpath_node* _begin;
		xpath_node* _end;
		xpath_node* _eos;

	public:
		xpath_node_set_raw(): _type(xpath_node_set::type_unsorted), _begin(NULL), _end(NULL), _eos(NULL)
		{
		}

		xpath_node* begin() const
		{
			return _begin;
		}

		xpath_node* end() const
		{
			return _end;
		}

		bool empty() const
		{
			return _begin == _end;
		}

		size_t size() const
		{
			return static_cast<size_t>(_end - _begin);
		}

		xpath_node first() const
		{
			return xpath_first(_begin, _end, _type);
		}

		void push_back_grow(const xpath_node& node, xpath_allocator* alloc);

		void push_back(const xpath_node& node, xpath_allocator* alloc)
		{
			if (_end != _eos)
				*_end++ = node;
			else
				push_back_grow(node, alloc);
		}

		void append(const xpath_node* begin_, const xpath_node* end_, xpath_allocator* alloc)
		{
			if (begin_ == end_) return;

			size_t size_ = static_cast<size_t>(_end - _begin);
			size_t capacity = static_cast<size_t>(_eos - _begin);
			size_t count = static_cast<size_t>(end_ - begin_);

			if (size_ + count > capacity)
			{
				// reallocate the old array or allocate a new one
				xpath_node* data = static_cast<xpath_node*>(alloc->reallocate(_begin, capacity * sizeof(xpath_node), (size_ + count) * sizeof(xpath_node)));
				if (!data) return;

				// finalize
				_begin = data;
				_end = data + size_;
				_eos = data + size_ + count;
			}

			memcpy(_end, begin_, count * sizeof(xpath_node));
			_end += count;
		}

		void sort_do()
		{
			_type = xpath_sort(_begin, _end, _type, false);
		}

		void truncate(xpath_node* pos)
		{
			assert(_begin <= pos && pos <= _end);

			_end = pos;
		}

		void remove_duplicates(xpath_allocator* alloc)
		{
			if (_type == xpath_node_set::type_unsorted && _end - _begin > 2)
			{
				xpath_allocator_capture cr(alloc);

				size_t size_ = static_cast<size_t>(_end - _begin);

				size_t hash_size = 1;
				while (hash_size < size_ + size_ / 2) hash_size *= 2;

				const void** hash_data = static_cast<const void**>(alloc->allocate(hash_size * sizeof(void*)));
				if (!hash_data) return;

				memset(hash_data, 0, hash_size * sizeof(void*));

				xpath_node* write = _begin;

				for (xpath_node* it = _begin; it != _end; ++it)
				{
					const void* attr = it->attribute().internal_object();
					const void* node = it->node().internal_object();
					const void* key = attr ? attr : node;

					if (key && hash_insert(hash_data, hash_size, key))
					{
						*write++ = *it;
					}
				}

				_end = write;
			}
			else
			{
				_end = unique(_begin, _end);
			}
		}

		xpath_node_set::type_t type() const
		{
			return _type;
		}

		void set_type(xpath_node_set::type_t value)
		{
			_type = value;
		}
	};

	PUGI_IMPL_FN_NO_INLINE void xpath_node_set_raw::push_back_grow(const xpath_node& node, xpath_allocator* alloc)
	{
		size_t capacity = static_cast<size_t>(_eos - _begin);

		// get new capacity (1.5x rule)
		size_t new_capacity = capacity + capacity / 2 + 1;

		// reallocate the old array or allocate a new one
		xpath_node* data = static_cast<xpath_node*>(alloc->reallocate(_begin, capacity * sizeof(xpath_node), new_capacity * sizeof(xpath_node)));
		if (!data) return;

		// finalize
		_begin = data;
		_end = data + capacity;
		_eos = data + new_capacity;

		// push
		*_end++ = node;
	}
PUGI_IMPL_NS_END

PUGI_IMPL_NS_BEGIN
	struct xpath_context
	{
		xpath_node n;
		size_t position, size;

		xpath_context(const xpath_node& n_, size_t position_, size_t size_): n(n_), position(position_), size(size_)
		{
		}
	};

	enum lexeme_t
	{
		lex_none = 0,
		lex_equal,
		lex_not_equal,
		lex_less,
		lex_greater,
		lex_less_or_equal,
		lex_greater_or_equal,
		lex_plus,
		lex_minus,
		lex_multiply,
		lex_union,
		lex_var_ref,
		lex_open_brace,
		lex_close_brace,
		lex_quoted_string,
		lex_number,
		lex_slash,
		lex_double_slash,
		lex_open_square_brace,
		lex_close_square_brace,
		lex_string,
		lex_comma,
		lex_axis_attribute,
		lex_dot,
		lex_double_dot,
		lex_double_colon,
		lex_eof
	};

	struct xpath_lexer_string
	{
		const char_t* begin;
		const char_t* end;

		xpath_lexer_string(): begin(NULL), end(NULL)
		{
		}

		bool operator==(const char_t* other) const
		{
			size_t length = static_cast<size_t>(end - begin);

			return strequalrange(other, begin, length);
		}
	};

	class xpath_lexer
	{
		const char_t* _cur;
		const char_t* _cur_lexeme_pos;
		xpath_lexer_string _cur_lexeme_contents;

		lexeme_t _cur_lexeme;

	public:
		explicit xpath_lexer(const char_t* query): _cur(query)
		{
			next();
		}

		const char_t* state() const
		{
			return _cur;
		}

		void next()
		{
			const char_t* cur = _cur;

			while (PUGI_IMPL_IS_CHARTYPE(*cur, ct_space)) ++cur;

			// save lexeme position for error reporting
			_cur_lexeme_pos = cur;

			switch (*cur)
			{
			case 0:
				_cur_lexeme = lex_eof;
				break;

			case '>':
				if (*(cur+1) == '=')
				{
					cur += 2;
					_cur_lexeme = lex_greater_or_equal;
				}
				else
				{
					cur += 1;
					_cur_lexeme = lex_greater;
				}
				break;

			case '<':
				if (*(cur+1) == '=')
				{
					cur += 2;
					_cur_lexeme = lex_less_or_equal;
				}
				else
				{
					cur += 1;
					_cur_lexeme = lex_less;
				}
				break;

			case '!':
				if (*(cur+1) == '=')
				{
					cur += 2;
					_cur_lexeme = lex_not_equal;
				}
				else
				{
					_cur_lexeme = lex_none;
				}
				break;

			case '=':
				cur += 1;
				_cur_lexeme = lex_equal;

				break;

			case '+':
				cur += 1;
				_cur_lexeme = lex_plus;

				break;

			case '-':
				cur += 1;
				_cur_lexeme = lex_minus;

				break;

			case '*':
				cur += 1;
				_cur_lexeme = lex_multiply;

				break;

			case '|':
				cur += 1;
				_cur_lexeme = lex_union;

				break;

			case '$':
				cur += 1;

				if (PUGI_IMPL_IS_CHARTYPEX(*cur, ctx_start_symbol))
				{
					_cur_lexeme_contents.begin = cur;

					while (PUGI_IMPL_IS_CHARTYPEX(*cur, ctx_symbol)) cur++;

					if (cur[0] == ':' && PUGI_IMPL_IS_CHARTYPEX(cur[1], ctx_symbol)) // qname
					{
						cur++; // :

						while (PUGI_IMPL_IS_CHARTYPEX(*cur, ctx_symbol)) cur++;
					}

					_cur_lexeme_contents.end = cur;

					_cur_lexeme = lex_var_ref;
				}
				else
				{
					_cur_lexeme = lex_none;
				}

				break;

			case '(':
				cur += 1;
				_cur_lexeme = lex_open_brace;

				break;

			case ')':
				cur += 1;
				_cur_lexeme = lex_close_brace;

				break;

			case '[':
				cur += 1;
				_cur_lexeme = lex_open_square_brace;

				break;

			case ']':
				cur += 1;
				_cur_lexeme = lex_close_square_brace;

				break;

			case ',':
				cur += 1;
				_cur_lexeme = lex_comma;

				break;

			case '/':
				if (*(cur+1) == '/')
				{
					cur += 2;
					_cur_lexeme = lex_double_slash;
				}
				else
				{
					cur += 1;
					_cur_lexeme = lex_slash;
				}
				break;

			case '.':
				if (*(cur+1) == '.')
				{
					cur += 2;
					_cur_lexeme = lex_double_dot;
				}
				else if (PUGI_IMPL_IS_CHARTYPEX(*(cur+1), ctx_digit))
				{
					_cur_lexeme_contents.begin = cur; // .

					++cur;

					while (PUGI_IMPL_IS_CHARTYPEX(*cur, ctx_digit)) cur++;

					_cur_lexeme_contents.end = cur;

					_cur_lexeme = lex_number;
				}
				else
				{
					cur += 1;
					_cur_lexeme = lex_dot;
				}
				break;

			case '@':
				cur += 1;
				_cur_lexeme = lex_axis_attribute;

				break;

			case '"':
			case '\'':
			{
				char_t terminator = *cur;

				++cur;

				_cur_lexeme_contents.begin = cur;
				while (*cur && *cur != terminator) cur++;
				_cur_lexeme_contents.end = cur;

				if (!*cur)
					_cur_lexeme = lex_none;
				else
				{
					cur += 1;
					_cur_lexeme = lex_quoted_string;
				}

				break;
			}

			case ':':
				if (*(cur+1) == ':')
				{
					cur += 2;
					_cur_lexeme = lex_double_colon;
				}
				else
				{
					_cur_lexeme = lex_none;
				}
				break;

			default:
				if (PUGI_IMPL_IS_CHARTYPEX(*cur, ctx_digit))
				{
					_cur_lexeme_contents.begin = cur;

					while (PUGI_IMPL_IS_CHARTYPEX(*cur, ctx_digit)) cur++;

					if (*cur == '.')
					{
						cur++;

						while (PUGI_IMPL_IS_CHARTYPEX(*cur, ctx_digit)) cur++;
					}

					_cur_lexeme_contents.end = cur;

					_cur_lexeme = lex_number;
				}
				else if (PUGI_IMPL_IS_CHARTYPEX(*cur, ctx_start_symbol))
				{
					_cur_lexeme_contents.begin = cur;

					while (PUGI_IMPL_IS_CHARTYPEX(*cur, ctx_symbol)) cur++;

					if (cur[0] == ':')
					{
						if (cur[1] == '*') // namespace test ncname:*
						{
							cur += 2; // :*
						}
						else if (PUGI_IMPL_IS_CHARTYPEX(cur[1], ctx_symbol)) // namespace test qname
						{
							cur++; // :

							while (PUGI_IMPL_IS_CHARTYPEX(*cur, ctx_symbol)) cur++;
						}
					}

					_cur_lexeme_contents.end = cur;

					_cur_lexeme = lex_string;
				}
				else
				{
					_cur_lexeme = lex_none;
				}
			}

			_cur = cur;
		}

		lexeme_t current() const
		{
			return _cur_lexeme;
		}

		const char_t* current_pos() const
		{
			return _cur_lexeme_pos;
		}

		const xpath_lexer_string& contents() const
		{
			assert(_cur_lexeme == lex_var_ref || _cur_lexeme == lex_number || _cur_lexeme == lex_string || _cur_lexeme == lex_quoted_string);

			return _cur_lexeme_contents;
		}
	};

	enum ast_type_t
	{
		ast_unknown,
		ast_op_or,						// left or right
		ast_op_and,						// left and right
		ast_op_equal,					// left = right
		ast_op_not_equal,				// left != right
		ast_op_less,					// left < right
		ast_op_greater,					// left > right
		ast_op_less_or_equal,			// left <= right
		ast_op_greater_or_equal,		// left >= right
		ast_op_add,						// left + right
		ast_op_subtract,				// left - right
		ast_op_multiply,				// left * right
		ast_op_divide,					// left / right
		ast_op_mod,						// left % right
		ast_op_negate,					// left - right
		ast_op_union,					// left | right
		ast_predicate,					// apply predicate to set; next points to next predicate
		ast_filter,						// select * from left where right
		ast_string_constant,			// string constant
		ast_number_constant,			// number constant
		ast_variable,					// variable
		ast_func_last,					// last()
		ast_func_position,				// position()
		ast_func_count,					// count(left)
		ast_func_id,					// id(left)
		ast_func_local_name_0,			// local-name()
		ast_func_local_name_1,			// local-name(left)
		ast_func_namespace_uri_0,		// namespace-uri()
		ast_func_namespace_uri_1,		// namespace-uri(left)
		ast_func_name_0,				// name()
		ast_func_name_1,				// name(left)
		ast_func_string_0,				// string()
		ast_func_string_1,				// string(left)
		ast_func_concat,				// concat(left, right, siblings)
		ast_func_starts_with,			// starts_with(left, right)
		ast_func_contains,				// contains(left, right)
		ast_func_substring_before,		// substring-before(left, right)
		ast_func_substring_after,		// substring-after(left, right)
		ast_func_substring_2,			// substring(left, right)
		ast_func_substring_3,			// substring(left, right, third)
		ast_func_string_length_0,		// string-length()
		ast_func_string_length_1,		// string-length(left)
		ast_func_normalize_space_0,		// normalize-space()
		ast_func_normalize_space_1,		// normalize-space(left)
		ast_func_translate,				// translate(left, right, third)
		ast_func_boolean,				// boolean(left)
		ast_func_not,					// not(left)
		ast_func_true,					// true()
		ast_func_false,					// false()
		ast_func_lang,					// lang(left)
		ast_func_number_0,				// number()
		ast_func_number_1,				// number(left)
		ast_func_sum,					// sum(left)
		ast_func_floor,					// floor(left)
		ast_func_ceiling,				// ceiling(left)
		ast_func_round,					// round(left)
		ast_step,						// process set left with step
		ast_step_root,					// select root node

		ast_opt_translate_table,		// translate(left, right, third) where right/third are constants
		ast_opt_compare_attribute		// @name = 'string'
	};

	enum axis_t
	{
		axis_ancestor,
		axis_ancestor_or_self,
		axis_attribute,
		axis_child,
		axis_descendant,
		axis_descendant_or_self,
		axis_following,
		axis_following_sibling,
		axis_namespace,
		axis_parent,
		axis_preceding,
		axis_preceding_sibling,
		axis_self
	};

	enum nodetest_t
	{
		nodetest_none,
		nodetest_name,
		nodetest_type_node,
		nodetest_type_comment,
		nodetest_type_pi,
		nodetest_type_text,
		nodetest_pi,
		nodetest_all,
		nodetest_all_in_namespace
	};

	enum predicate_t
	{
		predicate_default,
		predicate_posinv,
		predicate_constant,
		predicate_constant_one
	};

	enum nodeset_eval_t
	{
		nodeset_eval_all,
		nodeset_eval_any,
		nodeset_eval_first
	};

	template <axis_t N> struct axis_to_type
	{
		static const axis_t axis;
	};

	template <axis_t N> const axis_t axis_to_type<N>::axis = N;

	class xpath_ast_node
	{
	private:
		// node type
		char _type;
		char _rettype;

		// for ast_step
		char _axis;

		// for ast_step/ast_predicate/ast_filter
		char _test;

		// tree node structure
		xpath_ast_node* _left;
		xpath_ast_node* _right;
		xpath_ast_node* _next;

		union
		{
			// value for ast_string_constant
			const char_t* string;
			// value for ast_number_constant
			double number;
			// variable for ast_variable
			xpath_variable* variable;
			// node test for ast_step (node name/namespace/node type/pi target)
			const char_t* nodetest;
			// table for ast_opt_translate_table
			const unsigned char* table;
		} _data;

		xpath_ast_node(const xpath_ast_node&);
		xpath_ast_node& operator=(const xpath_ast_node&);

		template <class Comp> static bool compare_eq(xpath_ast_node* lhs, xpath_ast_node* rhs, const xpath_context& c, const xpath_stack& stack, const Comp& comp)
		{
			xpath_value_type lt = lhs->rettype(), rt = rhs->rettype();

			if (lt != xpath_type_node_set && rt != xpath_type_node_set)
			{
				if (lt == xpath_type_boolean || rt == xpath_type_boolean)
					return comp(lhs->eval_boolean(c, stack), rhs->eval_boolean(c, stack));
				else if (lt == xpath_type_number || rt == xpath_type_number)
					return comp(lhs->eval_number(c, stack), rhs->eval_number(c, stack));
				else if (lt == xpath_type_string || rt == xpath_type_string)
				{
					xpath_allocator_capture cr(stack.result);

					xpath_string ls = lhs->eval_string(c, stack);
					xpath_string rs = rhs->eval_string(c, stack);

					return comp(ls, rs);
				}
			}
			else if (lt == xpath_type_node_set && rt == xpath_type_node_set)
			{
				xpath_allocator_capture cr(stack.result);

				xpath_node_set_raw ls = lhs->eval_node_set(c, stack, nodeset_eval_all);
				xpath_node_set_raw rs = rhs->eval_node_set(c, stack, nodeset_eval_all);

				for (const xpath_node* li = ls.begin(); li != ls.end(); ++li)
					for (const xpath_node* ri = rs.begin(); ri != rs.end(); ++ri)
					{
						xpath_allocator_capture cri(stack.result);

						if (comp(string_value(*li, stack.result), string_value(*ri, stack.result)))
							return true;
					}

				return false;
			}
			else
			{
				if (lt == xpath_type_node_set)
				{
					swap(lhs, rhs);
					swap(lt, rt);
				}

				if (lt == xpath_type_boolean)
					return comp(lhs->eval_boolean(c, stack), rhs->eval_boolean(c, stack));
				else if (lt == xpath_type_number)
				{
					xpath_allocator_capture cr(stack.result);

					double l = lhs->eval_number(c, stack);
					xpath_node_set_raw rs = rhs->eval_node_set(c, stack, nodeset_eval_all);

					for (const xpath_node* ri = rs.begin(); ri != rs.end(); ++ri)
					{
						xpath_allocator_capture cri(stack.result);

						if (comp(l, convert_string_to_number(string_value(*ri, stack.result).c_str())))
							return true;
					}

					return false;
				}
				else if (lt == xpath_type_string)
				{
					xpath_allocator_capture cr(stack.result);

					xpath_string l = lhs->eval_string(c, stack);
					xpath_node_set_raw rs = rhs->eval_node_set(c, stack, nodeset_eval_all);

					for (const xpath_node* ri = rs.begin(); ri != rs.end(); ++ri)
					{
						xpath_allocator_capture cri(stack.result);

						if (comp(l, string_value(*ri, stack.result)))
							return true;
					}

					return false;
				}
			}

			assert(false && "Wrong types"); // unreachable
			return false;
		}

		static bool eval_once(xpath_node_set::type_t type, nodeset_eval_t eval)
		{
			return type == xpath_node_set::type_sorted ? eval != nodeset_eval_all : eval == nodeset_eval_any;
		}

		template <class Comp> static bool compare_rel(xpath_ast_node* lhs, xpath_ast_node* rhs, const xpath_context& c, const xpath_stack& stack, const Comp& comp)
		{
			xpath_value_type lt = lhs->rettype(), rt = rhs->rettype();

			if (lt != xpath_type_node_set && rt != xpath_type_node_set)
				return comp(lhs->eval_number(c, stack), rhs->eval_number(c, stack));
			else if (lt == xpath_type_node_set && rt == xpath_type_node_set)
			{
				xpath_allocator_capture cr(stack.result);

				xpath_node_set_raw ls = lhs->eval_node_set(c, stack, nodeset_eval_all);
				xpath_node_set_raw rs = rhs->eval_node_set(c, stack, nodeset_eval_all);

				for (const xpath_node* li = ls.begin(); li != ls.end(); ++li)
				{
					xpath_allocator_capture cri(stack.result);

					double l = convert_string_to_number(string_value(*li, stack.result).c_str());

					for (const xpath_node* ri = rs.begin(); ri != rs.end(); ++ri)
					{
						xpath_allocator_capture crii(stack.result);

						if (comp(l, convert_string_to_number(string_value(*ri, stack.result).c_str())))
							return true;
					}
				}

				return false;
			}
			else if (lt != xpath_type_node_set && rt == xpath_type_node_set)
			{
				xpath_allocator_capture cr(stack.result);

				double l = lhs->eval_number(c, stack);
				xpath_node_set_raw rs = rhs->eval_node_set(c, stack, nodeset_eval_all);

				for (const xpath_node* ri = rs.begin(); ri != rs.end(); ++ri)
				{
					xpath_allocator_capture cri(stack.result);

					if (comp(l, convert_string_to_number(string_value(*ri, stack.result).c_str())))
						return true;
				}

				return false;
			}
			else if (lt == xpath_type_node_set && rt != xpath_type_node_set)
			{
				xpath_allocator_capture cr(stack.result);

				xpath_node_set_raw ls = lhs->eval_node_set(c, stack, nodeset_eval_all);
				double r = rhs->eval_number(c, stack);

				for (const xpath_node* li = ls.begin(); li != ls.end(); ++li)
				{
					xpath_allocator_capture cri(stack.result);

					if (comp(convert_string_to_number(string_value(*li, stack.result).c_str()), r))
						return true;
				}

				return false;
			}
			else
			{
				assert(false && "Wrong types"); // unreachable
				return false;
			}
		}

		static void apply_predicate_boolean(xpath_node_set_raw& ns, size_t first, xpath_ast_node* expr, const xpath_stack& stack, bool once)
		{
			assert(ns.size() >= first);
			assert(expr->rettype() != xpath_type_number);

			size_t i = 1;
			size_t size = ns.size() - first;

			xpath_node* last = ns.begin() + first;

			// remove_if... or well, sort of
			for (xpath_node* it = last; it != ns.end(); ++it, ++i)
			{
				xpath_context c(*it, i, size);

				if (expr->eval_boolean(c, stack))
				{
					*last++ = *it;

					if (once) break;
				}
			}

			ns.truncate(last);
		}

		static void apply_predicate_number(xpath_node_set_raw& ns, size_t first, xpath_ast_node* expr, const xpath_stack& stack, bool once)
		{
			assert(ns.size() >= first);
			assert(expr->rettype() == xpath_type_number);

			size_t i = 1;
			size_t size = ns.size() - first;

			xpath_node* last = ns.begin() + first;

			// remove_if... or well, sort of
			for (xpath_node* it = last; it != ns.end(); ++it, ++i)
			{
				xpath_context c(*it, i, size);

				if (expr->eval_number(c, stack) == static_cast<double>(i))
				{
					*last++ = *it;

					if (once) break;
				}
			}

			ns.truncate(last);
		}

		static void apply_predicate_number_const(xpath_node_set_raw& ns, size_t first, xpath_ast_node* expr, const xpath_stack& stack)
		{
			assert(ns.size() >= first);
			assert(expr->rettype() == xpath_type_number);

			size_t size = ns.size() - first;

			xpath_node* last = ns.begin() + first;

			xpath_node cn;
			xpath_context c(cn, 1, size);

			double er = expr->eval_number(c, stack);

			if (er >= 1.0 && er <= static_cast<double>(size))
			{
				size_t eri = static_cast<size_t>(er);

				if (er == static_cast<double>(eri))
				{
					xpath_node r = last[eri - 1];

					*last++ = r;
				}
			}

			ns.truncate(last);
		}

		void apply_predicate(xpath_node_set_raw& ns, size_t first, const xpath_stack& stack, bool once)
		{
			if (ns.size() == first) return;

			assert(_type == ast_filter || _type == ast_predicate);

			if (_test == predicate_constant || _test == predicate_constant_one)
				apply_predicate_number_const(ns, first, _right, stack);
			else if (_right->rettype() == xpath_type_number)
				apply_predicate_number(ns, first, _right, stack, once);
			else
				apply_predicate_boolean(ns, first, _right, stack, once);
		}

		void apply_predicates(xpath_node_set_raw& ns, size_t first, const xpath_stack& stack, nodeset_eval_t eval)
		{
			if (ns.size() == first) return;

			bool last_once = eval_once(ns.type(), eval);

			for (xpath_ast_node* pred = _right; pred; pred = pred->_next)
				pred->apply_predicate(ns, first, stack, !pred->_next && last_once);
		}

		bool step_push(xpath_node_set_raw& ns, xml_attribute_struct* a, xml_node_struct* parent, xpath_allocator* alloc)
		{
			assert(a);

			const char_t* name = a->name ? a->name + 0 : PUGIXML_TEXT("");

			switch (_test)
			{
			case nodetest_name:
				if (strequal(name, _data.nodetest) && is_xpath_attribute(name))
				{
					ns.push_back(xpath_node(xml_attribute(a), xml_node(parent)), alloc);
					return true;
				}
				break;

			case nodetest_type_node:
			case nodetest_all:
				if (is_xpath_attribute(name))
				{
					ns.push_back(xpath_node(xml_attribute(a), xml_node(parent)), alloc);
					return true;
				}
				break;

			case nodetest_all_in_namespace:
				if (starts_with(name, _data.nodetest) && is_xpath_attribute(name))
				{
					ns.push_back(xpath_node(xml_attribute(a), xml_node(parent)), alloc);
					return true;
				}
				break;

			default:
				;
			}

			return false;
		}

		bool step_push(xpath_node_set_raw& ns, xml_node_struct* n, xpath_allocator* alloc)
		{
			assert(n);

			xml_node_type type = PUGI_IMPL_NODETYPE(n);

			switch (_test)
			{
			case nodetest_name:
				if (type == node_element && n->name && strequal(n->name, _data.nodetest))
				{
					ns.push_back(xml_node(n), alloc);
					return true;
				}
				break;

			case nodetest_type_node:
				ns.push_back(xml_node(n), alloc);
				return true;

			case nodetest_type_comment:
				if (type == node_comment)
				{
					ns.push_back(xml_node(n), alloc);
					return true;
				}
				break;

			case nodetest_type_text:
				if (type == node_pcdata || type == node_cdata)
				{
					ns.push_back(xml_node(n), alloc);
					return true;
				}
				break;

			case nodetest_type_pi:
				if (type == node_pi)
				{
					ns.push_back(xml_node(n), alloc);
					return true;
				}
				break;

			case nodetest_pi:
				if (type == node_pi && n->name && strequal(n->name, _data.nodetest))
				{
					ns.push_back(xml_node(n), alloc);
					return true;
				}
				break;

			case nodetest_all:
				if (type == node_element)
				{
					ns.push_back(xml_node(n), alloc);
					return true;
				}
				break;

			case nodetest_all_in_namespace:
				if (type == node_element && n->name && starts_with(n->name, _data.nodetest))
				{
					ns.push_back(xml_node(n), alloc);
					return true;
				}
				break;

			default:
				assert(false && "Unknown axis"); // unreachable
			}

			return false;
		}

		template <class T> void step_fill(xpath_node_set_raw& ns, xml_node_struct* n, xpath_allocator* alloc, bool once, T)
		{
			const axis_t axis = T::axis;

			switch (axis)
			{
			case axis_attribute:
			{
				for (xml_attribute_struct* a = n->first_attribute; a; a = a->next_attribute)
					if (step_push(ns, a, n, alloc) & once)
						return;

				break;
			}

			case axis_child:
			{
				for (xml_node_struct* c = n->first_child; c; c = c->next_sibling)
					if (step_push(ns, c, alloc) & once)
						return;

				break;
			}

			case axis_descendant:
			case axis_descendant_or_self:
			{
				if (axis == axis_descendant_or_self)
					if (step_push(ns, n, alloc) & once)
						return;

				xml_node_struct* cur = n->first_child;

				while (cur)
				{
					if (step_push(ns, cur, alloc) & once)
						return;

					if (cur->first_child)
						cur = cur->first_child;
					else
					{
						while (!cur->next_sibling)
						{
							cur = cur->parent;

							if (cur == n) return;
						}

						cur = cur->next_sibling;
					}
				}

				break;
			}

			case axis_following_sibling:
			{
				for (xml_node_struct* c = n->next_sibling; c; c = c->next_sibling)
					if (step_push(ns, c, alloc) & once)
						return;

				break;
			}

			case axis_preceding_sibling:
			{
				for (xml_node_struct* c = n->prev_sibling_c; c->next_sibling; c = c->prev_sibling_c)
					if (step_push(ns, c, alloc) & once)
						return;

				break;
			}

			case axis_following:
			{
				xml_node_struct* cur = n;

				// exit from this node so that we don't include descendants
				while (!cur->next_sibling)
				{
					cur = cur->parent;

					if (!cur) return;
				}

				cur = cur->next_sibling;

				while (cur)
				{
					if (step_push(ns, cur, alloc) & once)
						return;

					if (cur->first_child)
						cur = cur->first_child;
					else
					{
						while (!cur->next_sibling)
						{
							cur = cur->parent;

							if (!cur) return;
						}

						cur = cur->next_sibling;
					}
				}

				break;
			}

			case axis_preceding:
			{
				xml_node_struct* cur = n;

				// exit from this node so that we don't include descendants
				while (!cur->prev_sibling_c->next_sibling)
				{
					cur = cur->parent;

					if (!cur) return;
				}

				cur = cur->prev_sibling_c;

				while (cur)
				{
					if (cur->first_child)
						cur = cur->first_child->prev_sibling_c;
					else
					{
						// leaf node, can't be ancestor
						if (step_push(ns, cur, alloc) & once)
							return;

						while (!cur->prev_sibling_c->next_sibling)
						{
							cur = cur->parent;

							if (!cur) return;

							if (!node_is_ancestor(cur, n))
								if (step_push(ns, cur, alloc) & once)
									return;
						}

						cur = cur->prev_sibling_c;
					}
				}

				break;
			}

			case axis_ancestor:
			case axis_ancestor_or_self:
			{
				if (axis == axis_ancestor_or_self)
					if (step_push(ns, n, alloc) & once)
						return;

				xml_node_struct* cur = n->parent;

				while (cur)
				{
					if (step_push(ns, cur, alloc) & once)
						return;

					cur = cur->parent;
				}

				break;
			}

			case axis_self:
			{
				step_push(ns, n, alloc);

				break;
			}

			case axis_parent:
			{
				if (n->parent)
					step_push(ns, n->parent, alloc);

				break;
			}

			default:
				assert(false && "Unimplemented axis"); // unreachable
			}
		}

		template <class T> void step_fill(xpath_node_set_raw& ns, xml_attribute_struct* a, xml_node_struct* p, xpath_allocator* alloc, bool once, T v)
		{
			const axis_t axis = T::axis;

			switch (axis)
			{
			case axis_ancestor:
			case axis_ancestor_or_self:
			{
				if (axis == axis_ancestor_or_self && _test == nodetest_type_node) // reject attributes based on principal node type test
					if (step_push(ns, a, p, alloc) & once)
						return;

				xml_node_struct* cur = p;

				while (cur)
				{
					if (step_push(ns, cur, alloc) & once)
						return;

					cur = cur->parent;
				}

				break;
			}

			case axis_descendant_or_self:
			case axis_self:
			{
				if (_test == nodetest_type_node) // reject attributes based on principal node type test
					step_push(ns, a, p, alloc);

				break;
			}

			case axis_following:
			{
				xml_node_struct* cur = p;

				while (cur)
				{
					if (cur->first_child)
						cur = cur->first_child;
					else
					{
						while (!cur->next_sibling)
						{
							cur = cur->parent;

							if (!cur) return;
						}

						cur = cur->next_sibling;
					}

					if (step_push(ns, cur, alloc) & once)
						return;
				}

				break;
			}

			case axis_parent:
			{
				step_push(ns, p, alloc);

				break;
			}

			case axis_preceding:
			{
				// preceding:: axis does not include attribute nodes and attribute ancestors (they are the same as parent's ancestors), so we can reuse node preceding
				step_fill(ns, p, alloc, once, v);
				break;
			}

			default:
				assert(false && "Unimplemented axis"); // unreachable
			}
		}

		template <class T> void step_fill(xpath_node_set_raw& ns, const xpath_node& xn, xpath_allocator* alloc, bool once, T v)
		{
			const axis_t axis = T::axis;
			const bool axis_has_attributes = (axis == axis_ancestor || axis == axis_ancestor_or_self || axis == axis_descendant_or_self || axis == axis_following || axis == axis_parent || axis == axis_preceding || axis == axis_self);

			if (xn.node())
				step_fill(ns, xn.node().internal_object(), alloc, once, v);
			else if (axis_has_attributes && xn.attribute() && xn.parent())
				step_fill(ns, xn.attribute().internal_object(), xn.parent().internal_object(), alloc, once, v);
		}

		template <class T> xpath_node_set_raw step_do(const xpath_context& c, const xpath_stack& stack, nodeset_eval_t eval, T v)
		{
			const axis_t axis = T::axis;
			const bool axis_reverse = (axis == axis_ancestor || axis == axis_ancestor_or_self || axis == axis_preceding || axis == axis_preceding_sibling);
			const xpath_node_set::type_t axis_type = axis_reverse ? xpath_node_set::type_sorted_reverse : xpath_node_set::type_sorted;

			bool once =
				(axis == axis_attribute && _test == nodetest_name) ||
				(!_right && eval_once(axis_type, eval)) ||
			    // coverity[mixed_enums]
				(_right && !_right->_next && _right->_test == predicate_constant_one);

			xpath_node_set_raw ns;
			ns.set_type(axis_type);

			if (_left)
			{
				xpath_node_set_raw s = _left->eval_node_set(c, stack, nodeset_eval_all);

				// self axis preserves the original order
				if (axis == axis_self) ns.set_type(s.type());

				for (const xpath_node* it = s.begin(); it != s.end(); ++it)
				{
					size_t size = ns.size();

					// in general, all axes generate elements in a particular order, but there is no order guarantee if axis is applied to two nodes
					if (axis != axis_self && size != 0) ns.set_type(xpath_node_set::type_unsorted);

					step_fill(ns, *it, stack.result, once, v);
					if (_right) apply_predicates(ns, size, stack, eval);
				}
			}
			else
			{
				step_fill(ns, c.n, stack.result, once, v);
				if (_right) apply_predicates(ns, 0, stack, eval);
			}

			// child, attribute and self axes always generate unique set of nodes
			// for other axis, if the set stayed sorted, it stayed unique because the traversal algorithms do not visit the same node twice
			if (axis != axis_child && axis != axis_attribute && axis != axis_self && ns.type() == xpath_node_set::type_unsorted)
				ns.remove_duplicates(stack.temp);

			return ns;
		}

	public:
		xpath_ast_node(ast_type_t type, xpath_value_type rettype_, const char_t* value):
			_type(static_cast<char>(type)), _rettype(static_cast<char>(rettype_)), _axis(0), _test(0), _left(NULL), _right(NULL), _next(NULL)
		{
			assert(type == ast_string_constant);
			_data.string = value;
		}

		xpath_ast_node(ast_type_t type, xpath_value_type rettype_, double value):
			_type(static_cast<char>(type)), _rettype(static_cast<char>(rettype_)), _axis(0), _test(0), _left(NULL), _right(NULL), _next(NULL)
		{
			assert(type == ast_number_constant);
			_data.number = value;
		}

		xpath_ast_node(ast_type_t type, xpath_value_type rettype_, xpath_variable* value):
			_type(static_cast<char>(type)), _rettype(static_cast<char>(rettype_)), _axis(0), _test(0), _left(NULL), _right(NULL), _next(NULL)
		{
			assert(type == ast_variable);
			_data.variable = value;
		}

		xpath_ast_node(ast_type_t type, xpath_value_type rettype_, xpath_ast_node* left = NULL, xpath_ast_node* right = NULL):
			_type(static_cast<char>(type)), _rettype(static_cast<char>(rettype_)), _axis(0), _test(0), _left(left), _right(right), _next(NULL)
		{
		}

		xpath_ast_node(ast_type_t type, xpath_ast_node* left, axis_t axis, nodetest_t test, const char_t* contents):
			_type(static_cast<char>(type)), _rettype(xpath_type_node_set), _axis(static_cast<char>(axis)), _test(static_cast<char>(test)), _left(left), _right(NULL), _next(NULL)
		{
			assert(type == ast_step);
			_data.nodetest = contents;
		}

		xpath_ast_node(ast_type_t type, xpath_ast_node* left, xpath_ast_node* right, predicate_t test):
			_type(static_cast<char>(type)), _rettype(xpath_type_node_set), _axis(0), _test(static_cast<char>(test)), _left(left), _right(right), _next(NULL)
		{
			assert(type == ast_filter || type == ast_predicate);
		}

		void set_next(xpath_ast_node* value)
		{
			_next = value;
		}

		void set_right(xpath_ast_node* value)
		{
			_right = value;
		}

		bool eval_boolean(const xpath_context& c, const xpath_stack& stack)
		{
			switch (_type)
			{
			case ast_op_or:
				return _left->eval_boolean(c, stack) || _right->eval_boolean(c, stack);

			case ast_op_and:
				return _left->eval_boolean(c, stack) && _right->eval_boolean(c, stack);

			case ast_op_equal:
				return compare_eq(_left, _right, c, stack, equal_to());

			case ast_op_not_equal:
				return compare_eq(_left, _right, c, stack, not_equal_to());

			case ast_op_less:
				return compare_rel(_left, _right, c, stack, less());

			case ast_op_greater:
				return compare_rel(_right, _left, c, stack, less());

			case ast_op_less_or_equal:
				return compare_rel(_left, _right, c, stack, less_equal());

			case ast_op_greater_or_equal:
				return compare_rel(_right, _left, c, stack, less_equal());

			case ast_func_starts_with:
			{
				xpath_allocator_capture cr(stack.result);

				xpath_string lr = _left->eval_string(c, stack);
				xpath_string rr = _right->eval_string(c, stack);

				return starts_with(lr.c_str(), rr.c_str());
			}

			case ast_func_contains:
			{
				xpath_allocator_capture cr(stack.result);

				xpath_string lr = _left->eval_string(c, stack);
				xpath_string rr = _right->eval_string(c, stack);

				return find_substring(lr.c_str(), rr.c_str()) != NULL;
			}

			case ast_func_boolean:
				return _left->eval_boolean(c, stack);

			case ast_func_not:
				return !_left->eval_boolean(c, stack);

			case ast_func_true:
				return true;

			case ast_func_false:
				return false;

			case ast_func_lang:
			{
				if (c.n.attribute()) return false;

				xpath_allocator_capture cr(stack.result);

				xpath_string lang = _left->eval_string(c, stack);

				for (xml_node n = c.n.node(); n; n = n.parent())
				{
					xml_attribute a = n.attribute(PUGIXML_TEXT("xml:lang"));

					if (a)
					{
						const char_t* value = a.value();

						// strnicmp / strncasecmp is not portable
						for (const char_t* lit = lang.c_str(); *lit; ++lit)
						{
							if (tolower_ascii(*lit) != tolower_ascii(*value)) return false;
							++value;
						}

						return *value == 0 || *value == '-';
					}
				}

				return false;
			}

			case ast_opt_compare_attribute:
			{
				const char_t* value = (_right->_type == ast_string_constant) ? _right->_data.string : _right->_data.variable->get_string();

				xml_attribute attr = c.n.node().attribute(_left->_data.nodetest);

				return attr && strequal(attr.value(), value) && is_xpath_attribute(attr.name());
			}

			case ast_variable:
			{
				assert(_rettype == _data.variable->type());

				if (_rettype == xpath_type_boolean)
					return _data.variable->get_boolean();

				// variable needs to be converted to the correct type, this is handled by the fallthrough block below
				break;
			}

			default:
				;
			}

			// none of the ast types that return the value directly matched, we need to perform type conversion
			switch (_rettype)
			{
			case xpath_type_number:
				return convert_number_to_boolean(eval_number(c, stack));

			case xpath_type_string:
			{
				xpath_allocator_capture cr(stack.result);

				return !eval_string(c, stack).empty();
			}

			case xpath_type_node_set:
			{
				xpath_allocator_capture cr(stack.result);

				return !eval_node_set(c, stack, nodeset_eval_any).empty();
			}

			default:
				assert(false && "Wrong expression for return type boolean"); // unreachable
				return false;
			}
		}

		double eval_number(const xpath_context& c, const xpath_stack& stack)
		{
			switch (_type)
			{
			case ast_op_add:
				return _left->eval_number(c, stack) + _right->eval_number(c, stack);

			case ast_op_subtract:
				return _left->eval_number(c, stack) - _right->eval_number(c, stack);

			case ast_op_multiply:
				return _left->eval_number(c, stack) * _right->eval_number(c, stack);

			case ast_op_divide:
				return _left->eval_number(c, stack) / _right->eval_number(c, stack);

			case ast_op_mod:
				return fmod(_left->eval_number(c, stack), _right->eval_number(c, stack));

			case ast_op_negate:
				return -_left->eval_number(c, stack);

			case ast_number_constant:
				return _data.number;

			case ast_func_last:
				return static_cast<double>(c.size);

			case ast_func_position:
				return static_cast<double>(c.position);

			case ast_func_count:
			{
				xpath_allocator_capture cr(stack.result);

				return static_cast<double>(_left->eval_node_set(c, stack, nodeset_eval_all).size());
			}

			case ast_func_string_length_0:
			{
				xpath_allocator_capture cr(stack.result);

				return static_cast<double>(string_value(c.n, stack.result).length());
			}

			case ast_func_string_length_1:
			{
				xpath_allocator_capture cr(stack.result);

				return static_cast<double>(_left->eval_string(c, stack).length());
			}

			case ast_func_number_0:
			{
				xpath_allocator_capture cr(stack.result);

				return convert_string_to_number(string_value(c.n, stack.result).c_str());
			}

			case ast_func_number_1:
				return _left->eval_number(c, stack);

			case ast_func_sum:
			{
				xpath_allocator_capture cr(stack.result);

				double r = 0;

				xpath_node_set_raw ns = _left->eval_node_set(c, stack, nodeset_eval_all);

				for (const xpath_node* it = ns.begin(); it != ns.end(); ++it)
				{
					xpath_allocator_capture cri(stack.result);

					r += convert_string_to_number(string_value(*it, stack.result).c_str());
				}

				return r;
			}

			case ast_func_floor:
			{
				double r = _left->eval_number(c, stack);

				return r == r ? floor(r) : r;
			}

			case ast_func_ceiling:
			{
				double r = _left->eval_number(c, stack);

				return r == r ? ceil(r) : r;
			}

			case ast_func_round:
				return round_nearest_nzero(_left->eval_number(c, stack));

			case ast_variable:
			{
				assert(_rettype == _data.variable->type());

				if (_rettype == xpath_type_number)
					return _data.variable->get_number();

				// variable needs to be converted to the correct type, this is handled by the fallthrough block below
				break;
			}

			default:
				;
			}

			// none of the ast types that return the value directly matched, we need to perform type conversion
			switch (_rettype)
			{
			case xpath_type_boolean:
				return eval_boolean(c, stack) ? 1 : 0;

			case xpath_type_string:
			case xpath_type_node_set: // implicit conversion to string
			{
				xpath_allocator_capture cr(stack.result);

				return convert_string_to_number(eval_string(c, stack).c_str());
			}

			default:
				assert(false && "Wrong expression for return type number"); // unreachable
				return 0;
			}
		}

		xpath_string eval_string_concat(const xpath_context& c, const xpath_stack& stack)
		{
			assert(_type == ast_func_concat);

			xpath_allocator_capture ct(stack.temp);

			// count the string number
			size_t count = 1;
			for (xpath_ast_node* nc = _right; nc; nc = nc->_next) count++;

			// allocate a buffer for temporary string objects
			xpath_string* buffer = static_cast<xpath_string*>(stack.temp->allocate(count * sizeof(xpath_string)));
			if (!buffer) return xpath_string();

			// evaluate all strings to temporary stack
			xpath_stack swapped_stack = {stack.temp, stack.result};

			buffer[0] = _left->eval_string(c, swapped_stack);

			size_t pos = 1;
			for (xpath_ast_node* n = _right; n; n = n->_next, ++pos) buffer[pos] = n->eval_string(c, swapped_stack);
			assert(pos == count);

			// get total length
			size_t length = 0;
			for (size_t i = 0; i < count; ++i) length += buffer[i].length();

			// create final string
			char_t* result = static_cast<char_t*>(stack.result->allocate((length + 1) * sizeof(char_t)));
			if (!result) return xpath_string();

			char_t* ri = result;

			for (size_t j = 0; j < count; ++j)
				for (const char_t* bi = buffer[j].c_str(); *bi; ++bi)
					*ri++ = *bi;

			*ri = 0;

			return xpath_string::from_heap_preallocated(result, ri);
		}

		xpath_string eval_string(const xpath_context& c, const xpath_stack& stack)
		{
			switch (_type)
			{
			case ast_string_constant:
				return xpath_string::from_const(_data.string);

			case ast_func_local_name_0:
			{
				xpath_node na = c.n;

				return xpath_string::from_const(local_name(na));
			}

			case ast_func_local_name_1:
			{
				xpath_allocator_capture cr(stack.result);

				xpath_node_set_raw ns = _left->eval_node_set(c, stack, nodeset_eval_first);
				xpath_node na = ns.first();

				return xpath_string::from_const(local_name(na));
			}

			case ast_func_name_0:
			{
				xpath_node na = c.n;

				return xpath_string::from_const(qualified_name(na));
			}

			case ast_func_name_1:
			{
				xpath_allocator_capture cr(stack.result);

				xpath_node_set_raw ns = _left->eval_node_set(c, stack, nodeset_eval_first);
				xpath_node na = ns.first();

				return xpath_string::from_const(qualified_name(na));
			}

			case ast_func_namespace_uri_0:
			{
				xpath_node na = c.n;

				return xpath_string::from_const(namespace_uri(na));
			}

			case ast_func_namespace_uri_1:
			{
				xpath_allocator_capture cr(stack.result);

				xpath_node_set_raw ns = _left->eval_node_set(c, stack, nodeset_eval_first);
				xpath_node na = ns.first();

				return xpath_string::from_const(namespace_uri(na));
			}

			case ast_func_string_0:
				return string_value(c.n, stack.result);

			case ast_func_string_1:
				return _left->eval_string(c, stack);

			case ast_func_concat:
				return eval_string_concat(c, stack);

			case ast_func_substring_before:
			{
				xpath_allocator_capture cr(stack.temp);

				xpath_stack swapped_stack = {stack.temp, stack.result};

				xpath_string s = _left->eval_string(c, swapped_stack);
				xpath_string p = _right->eval_string(c, swapped_stack);

				const char_t* pos = find_substring(s.c_str(), p.c_str());

				return pos ? xpath_string::from_heap(s.c_str(), pos, stack.result) : xpath_string();
			}

			case ast_func_substring_after:
			{
				xpath_allocator_capture cr(stack.temp);

				xpath_stack swapped_stack = {stack.temp, stack.result};

				xpath_string s = _left->eval_string(c, swapped_stack);
				xpath_string p = _right->eval_string(c, swapped_stack);

				const char_t* pos = find_substring(s.c_str(), p.c_str());
				if (!pos) return xpath_string();

				const char_t* rbegin = pos + p.length();
				const char_t* rend = s.c_str() + s.length();

				return s.uses_heap() ? xpath_string::from_heap(rbegin, rend, stack.result) : xpath_string::from_const(rbegin);
			}

			case ast_func_substring_2:
			{
				xpath_allocator_capture cr(stack.temp);

				xpath_stack swapped_stack = {stack.temp, stack.result};

				xpath_string s = _left->eval_string(c, swapped_stack);
				size_t s_length = s.length();

				double first = round_nearest(_right->eval_number(c, stack));

				if (is_nan(first)) return xpath_string(); // NaN
				else if (first >= static_cast<double>(s_length + 1)) return xpath_string();

				size_t pos = first < 1 ? 1 : static_cast<size_t>(first);
				assert(1 <= pos && pos <= s_length + 1);

				const char_t* rbegin = s.c_str() + (pos - 1);
				const char_t* rend = s.c_str() + s.length();

				return s.uses_heap() ? xpath_string::from_heap(rbegin, rend, stack.result) : xpath_string::from_const(rbegin);
			}

			case ast_func_substring_3:
			{
				xpath_allocator_capture cr(stack.temp);

				xpath_stack swapped_stack = {stack.temp, stack.result};

				xpath_string s = _left->eval_string(c, swapped_stack);
				size_t s_length = s.length();

				double first = round_nearest(_right->eval_number(c, stack));
				double last = first + round_nearest(_right->_next->eval_number(c, stack));

				if (is_nan(first) || is_nan(last)) return xpath_string();
				else if (first >= static_cast<double>(s_length + 1)) return xpath_string();
				else if (first >= last) return xpath_string();
				else if (last < 1) return xpath_string();

				size_t pos = first < 1 ? 1 : static_cast<size_t>(first);
				size_t end = last >= static_cast<double>(s_length + 1) ? s_length + 1 : static_cast<size_t>(last);

				assert(1 <= pos && pos <= end && end <= s_length + 1);
				const char_t* rbegin = s.c_str() + (pos - 1);
				const char_t* rend = s.c_str() + (end - 1);

				return (end == s_length + 1 && !s.uses_heap()) ? xpath_string::from_const(rbegin) : xpath_string::from_heap(rbegin, rend, stack.result);
			}

			case ast_func_normalize_space_0:
			{
				xpath_string s = string_value(c.n, stack.result);

				char_t* begin = s.data(stack.result);
				if (!begin) return xpath_string();

				char_t* end = normalize_space(begin);

				return xpath_string::from_heap_preallocated(begin, end);
			}

			case ast_func_normalize_space_1:
			{
				xpath_string s = _left->eval_string(c, stack);

				char_t* begin = s.data(stack.result);
				if (!begin) return xpath_string();

				char_t* end = normalize_space(begin);

				return xpath_string::from_heap_preallocated(begin, end);
			}

			case ast_func_translate:
			{
				xpath_allocator_capture cr(stack.temp);

				xpath_stack swapped_stack = {stack.temp, stack.result};

				xpath_string s = _left->eval_string(c, stack);
				xpath_string from = _right->eval_string(c, swapped_stack);
				xpath_string to = _right->_next->eval_string(c, swapped_stack);

				char_t* begin = s.data(stack.result);
				if (!begin) return xpath_string();

				char_t* end = translate(begin, from.c_str(), to.c_str(), to.length());

				return xpath_string::from_heap_preallocated(begin, end);
			}

			case ast_opt_translate_table:
			{
				xpath_string s = _left->eval_string(c, stack);

				char_t* begin = s.data(stack.result);
				if (!begin) return xpath_string();

				char_t* end = translate_table(begin, _data.table);

				return xpath_string::from_heap_preallocated(begin, end);
			}

			case ast_variable:
			{
				assert(_rettype == _data.variable->type());

				if (_rettype == xpath_type_string)
					return xpath_string::from_const(_data.variable->get_string());

				// variable needs to be converted to the correct type, this is handled by the fallthrough block below
				break;
			}

			default:
				;
			}

			// none of the ast types that return the value directly matched, we need to perform type conversion
			switch (_rettype)
			{
			case xpath_type_boolean:
				return xpath_string::from_const(eval_boolean(c, stack) ? PUGIXML_TEXT("true") : PUGIXML_TEXT("false"));

			case xpath_type_number:
				return convert_number_to_string(eval_number(c, stack), stack.result);

			case xpath_type_node_set:
			{
				xpath_allocator_capture cr(stack.temp);

				xpath_stack swapped_stack = {stack.temp, stack.result};

				xpath_node_set_raw ns = eval_node_set(c, swapped_stack, nodeset_eval_first);
				return ns.empty() ? xpath_string() : string_value(ns.first(), stack.result);
			}

			default:
				assert(false && "Wrong expression for return type string"); // unreachable
				return xpath_string();
			}
		}

		xpath_node_set_raw eval_node_set(const xpath_context& c, const xpath_stack& stack, nodeset_eval_t eval)
		{
			switch (_type)
			{
			case ast_op_union:
			{
				xpath_allocator_capture cr(stack.temp);

				xpath_stack swapped_stack = {stack.temp, stack.result};

				xpath_node_set_raw ls = _left->eval_node_set(c, stack, eval);
				xpath_node_set_raw rs = _right->eval_node_set(c, swapped_stack, eval);

				// we can optimize merging two sorted sets, but this is a very rare operation, so don't bother
				ls.set_type(xpath_node_set::type_unsorted);

				ls.append(rs.begin(), rs.end(), stack.result);
				ls.remove_duplicates(stack.temp);

				return ls;
			}

			case ast_filter:
			{
				xpath_node_set_raw set = _left->eval_node_set(c, stack, _test == predicate_constant_one ? nodeset_eval_first : nodeset_eval_all);

				// either expression is a number or it contains position() call; sort by document order
				if (_test != predicate_posinv) set.sort_do();

				bool once = eval_once(set.type(), eval);

				apply_predicate(set, 0, stack, once);

				return set;
			}

			case ast_func_id:
				return xpath_node_set_raw();

			case ast_step:
			{
				switch (_axis)
				{
				case axis_ancestor:
					return step_do(c, stack, eval, axis_to_type<axis_ancestor>());

				case axis_ancestor_or_self:
					return step_do(c, stack, eval, axis_to_type<axis_ancestor_or_self>());

				case axis_attribute:
					return step_do(c, stack, eval, axis_to_type<axis_attribute>());

				case axis_child:
					return step_do(c, stack, eval, axis_to_type<axis_child>());

				case axis_descendant:
					return step_do(c, stack, eval, axis_to_type<axis_descendant>());

				case axis_descendant_or_self:
					return step_do(c, stack, eval, axis_to_type<axis_descendant_or_self>());

				case axis_following:
					return step_do(c, stack, eval, axis_to_type<axis_following>());

				case axis_following_sibling:
					return step_do(c, stack, eval, axis_to_type<axis_following_sibling>());

				case axis_namespace:
					// namespaced axis is not supported
					return xpath_node_set_raw();

				case axis_parent:
					return step_do(c, stack, eval, axis_to_type<axis_parent>());

				case axis_preceding:
					return step_do(c, stack, eval, axis_to_type<axis_preceding>());

				case axis_preceding_sibling:
					return step_do(c, stack, eval, axis_to_type<axis_preceding_sibling>());

				case axis_self:
					return step_do(c, stack, eval, axis_to_type<axis_self>());

				default:
					assert(false && "Unknown axis"); // unreachable
					return xpath_node_set_raw();
				}
			}

			case ast_step_root:
			{
				assert(!_right); // root step can't have any predicates

				xpath_node_set_raw ns;

				ns.set_type(xpath_node_set::type_sorted);

				if (c.n.node()) ns.push_back(c.n.node().root(), stack.result);
				else if (c.n.attribute()) ns.push_back(c.n.parent().root(), stack.result);

				return ns;
			}

			case ast_variable:
			{
				assert(_rettype == _data.variable->type());

				if (_rettype == xpath_type_node_set)
				{
					const xpath_node_set& s = _data.variable->get_node_set();

					xpath_node_set_raw ns;

					ns.set_type(s.type());
					ns.append(s.begin(), s.end(), stack.result);

					return ns;
				}

				// variable needs to be converted to the correct type, this is handled by the fallthrough block below
				break;
			}

			default:
				;
			}

			// none of the ast types that return the value directly matched, but conversions to node set are invalid
			assert(false && "Wrong expression for return type node set"); // unreachable
			return xpath_node_set_raw();
		}

		void optimize(xpath_allocator* alloc)
		{
			if (_left)
				_left->optimize(alloc);

			if (_right)
				_right->optimize(alloc);

			if (_next)
				_next->optimize(alloc);

			// coverity[var_deref_model]
			optimize_self(alloc);
		}

		void optimize_self(xpath_allocator* alloc)
		{
			// Rewrite [position()=expr] with [expr]
			// Note that this step has to go before classification to recognize [position()=1]
			if ((_type == ast_filter || _type == ast_predicate) &&
				_right && // workaround for clang static analyzer (_right is never null for ast_filter/ast_predicate)
				_right->_type == ast_op_equal && _right->_left->_type == ast_func_position && _right->_right->_rettype == xpath_type_number)
			{
				_right = _right->_right;
			}

			// Classify filter/predicate ops to perform various optimizations during evaluation
			if ((_type == ast_filter || _type == ast_predicate) && _right) // workaround for clang static analyzer (_right is never null for ast_filter/ast_predicate)
			{
				assert(_test == predicate_default);

				if (_right->_type == ast_number_constant && _right->_data.number == 1.0)
					_test = predicate_constant_one;
				else if (_right->_rettype == xpath_type_number && (_right->_type == ast_number_constant || _right->_type == ast_variable || _right->_type == ast_func_last))
					_test = predicate_constant;
				else if (_right->_rettype != xpath_type_number && _right->is_posinv_expr())
					_test = predicate_posinv;
			}

			// Rewrite descendant-or-self::node()/child::foo with descendant::foo
			// The former is a full form of //foo, the latter is much faster since it executes the node test immediately
			// Do a similar kind of rewrite for self/descendant/descendant-or-self axes
			// Note that we only rewrite positionally invariant steps (//foo[1] != /descendant::foo[1])
			if (_type == ast_step && (_axis == axis_child || _axis == axis_self || _axis == axis_descendant || _axis == axis_descendant_or_self) &&
				_left && _left->_type == ast_step && _left->_axis == axis_descendant_or_self && _left->_test == nodetest_type_node && !_left->_right &&
				is_posinv_step())
			{
				if (_axis == axis_child || _axis == axis_descendant)
					_axis = axis_descendant;
				else
					_axis = axis_descendant_or_self;

				_left = _left->_left;
			}

			// Use optimized lookup table implementation for translate() with constant arguments
			if (_type == ast_func_translate &&
				_right && // workaround for clang static analyzer (_right is never null for ast_func_translate)
				_right->_type == ast_string_constant && _right->_next->_type == ast_string_constant)
			{
				unsigned char* table = translate_table_generate(alloc, _right->_data.string, _right->_next->_data.string);

				if (table)
				{
					_type = ast_opt_translate_table;
					_data.table = table;
				}
			}

			// Use optimized path for @attr = 'value' or @attr = $value
			if (_type == ast_op_equal &&
				_left && _right && // workaround for clang static analyzer and Coverity (_left and _right are never null for ast_op_equal)
                // coverity[mixed_enums]
				_left->_type == ast_step && _left->_axis == axis_attribute && _left->_test == nodetest_name && !_left->_left && !_left->_right &&
				(_right->_type == ast_string_constant || (_right->_type == ast_variable && _right->_rettype == xpath_type_string)))
			{
				_type = ast_opt_compare_attribute;
			}
		}

		bool is_posinv_expr() const
		{
			switch (_type)
			{
			case ast_func_position:
			case ast_func_last:
				return false;

			case ast_string_constant:
			case ast_number_constant:
			case ast_variable:
				return true;

			case ast_step:
			case ast_step_root:
				return true;

			case ast_predicate:
			case ast_filter:
				return true;

			default:
				if (_left && !_left->is_posinv_expr()) return false;

				for (xpath_ast_node* n = _right; n; n = n->_next)
					if (!n->is_posinv_expr()) return false;

				return true;
			}
		}

		bool is_posinv_step() const
		{
			assert(_type == ast_step);

			for (xpath_ast_node* n = _right; n; n = n->_next)
			{
				assert(n->_type == ast_predicate);

				if (n->_test != predicate_posinv)
					return false;
			}

			return true;
		}

		xpath_value_type rettype() const
		{
			return static_cast<xpath_value_type>(_rettype);
		}
	};

	static const size_t xpath_ast_depth_limit =
	#ifdef PUGIXML_XPATH_DEPTH_LIMIT
		PUGIXML_XPATH_DEPTH_LIMIT
	#else
		1024
	#endif
		;

	struct xpath_parser
	{
		xpath_allocator* _alloc;
		xpath_lexer _lexer;

		const char_t* _query;
		xpath_variable_set* _variables;

		xpath_parse_result* _result;

		char_t _scratch[32];

		size_t _depth;

		xpath_ast_node* error(const char* message)
		{
			_result->error = message;
			_result->offset = _lexer.current_pos() - _query;

			return NULL;
		}

		xpath_ast_node* error_oom()
		{
			assert(_alloc->_error);
			*_alloc->_error = true;

			return NULL;
		}

		xpath_ast_node* error_rec()
		{
			return error("Exceeded maximum allowed query depth");
		}

		void* alloc_node()
		{
			return _alloc->allocate(sizeof(xpath_ast_node));
		}

		xpath_ast_node* alloc_node(ast_type_t type, xpath_value_type rettype, const char_t* value)
		{
			void* memory = alloc_node();
			return memory ? new (memory) xpath_ast_node(type, rettype, value) : NULL;
		}

		xpath_ast_node* alloc_node(ast_type_t type, xpath_value_type rettype, double value)
		{
			void* memory = alloc_node();
			return memory ? new (memory) xpath_ast_node(type, rettype, value) : NULL;
		}

		xpath_ast_node* alloc_node(ast_type_t type, xpath_value_type rettype, xpath_variable* value)
		{
			void* memory = alloc_node();
			return memory ? new (memory) xpath_ast_node(type, rettype, value) : NULL;
		}

		xpath_ast_node* alloc_node(ast_type_t type, xpath_value_type rettype, xpath_ast_node* left = NULL, xpath_ast_node* right = NULL)
		{
			void* memory = alloc_node();
			return memory ? new (memory) xpath_ast_node(type, rettype, left, right) : NULL;
		}

		xpath_ast_node* alloc_node(ast_type_t type, xpath_ast_node* left, axis_t axis, nodetest_t test, const char_t* contents)
		{
			void* memory = alloc_node();
			return memory ? new (memory) xpath_ast_node(type, left, axis, test, contents) : NULL;
		}

		xpath_ast_node* alloc_node(ast_type_t type, xpath_ast_node* left, xpath_ast_node* right, predicate_t test)
		{
			void* memory = alloc_node();
			return memory ? new (memory) xpath_ast_node(type, left, right, test) : NULL;
		}

		const char_t* alloc_string(const xpath_lexer_string& value)
		{
			if (!value.begin)
				return PUGIXML_TEXT("");

			size_t length = static_cast<size_t>(value.end - value.begin);

			char_t* c = static_cast<char_t*>(_alloc->allocate((length + 1) * sizeof(char_t)));
			if (!c) return NULL;

			memcpy(c, value.begin, length * sizeof(char_t));
			c[length] = 0;

			return c;
		}

		xpath_ast_node* parse_function(const xpath_lexer_string& name, size_t argc, xpath_ast_node* args[2])
		{
			switch (name.begin[0])
			{
			case 'b':
				if (name == PUGIXML_TEXT("boolean") && argc == 1)
					return alloc_node(ast_func_boolean, xpath_type_boolean, args[0]);

				break;

			case 'c':
				if (name == PUGIXML_TEXT("count") && argc == 1)
				{
					if (args[0]->rettype() != xpath_type_node_set) return error("Function has to be applied to node set");
					return alloc_node(ast_func_count, xpath_type_number, args[0]);
				}
				else if (name == PUGIXML_TEXT("contains") && argc == 2)
					return alloc_node(ast_func_contains, xpath_type_boolean, args[0], args[1]);
				else if (name == PUGIXML_TEXT("concat") && argc >= 2)
					return alloc_node(ast_func_concat, xpath_type_string, args[0], args[1]);
				else if (name == PUGIXML_TEXT("ceiling") && argc == 1)
					return alloc_node(ast_func_ceiling, xpath_type_number, args[0]);

				break;

			case 'f':
				if (name == PUGIXML_TEXT("false") && argc == 0)
					return alloc_node(ast_func_false, xpath_type_boolean);
				else if (name == PUGIXML_TEXT("floor") && argc == 1)
					return alloc_node(ast_func_floor, xpath_type_number, args[0]);

				break;

			case 'i':
				if (name == PUGIXML_TEXT("id") && argc == 1)
					return alloc_node(ast_func_id, xpath_type_node_set, args[0]);

				break;

			case 'l':
				if (name == PUGIXML_TEXT("last") && argc == 0)
					return alloc_node(ast_func_last, xpath_type_number);
				else if (name == PUGIXML_TEXT("lang") && argc == 1)
					return alloc_node(ast_func_lang, xpath_type_boolean, args[0]);
				else if (name == PUGIXML_TEXT("local-name") && argc <= 1)
				{
					if (argc == 1 && args[0]->rettype() != xpath_type_node_set) return error("Function has to be applied to node set");
					return alloc_node(argc == 0 ? ast_func_local_name_0 : ast_func_local_name_1, xpath_type_string, args[0]);
				}

				break;

			case 'n':
				if (name == PUGIXML_TEXT("name") && argc <= 1)
				{
					if (argc == 1 && args[0]->rettype() != xpath_type_node_set) return error("Function has to be applied to node set");
					return alloc_node(argc == 0 ? ast_func_name_0 : ast_func_name_1, xpath_type_string, args[0]);
				}
				else if (name == PUGIXML_TEXT("namespace-uri") && argc <= 1)
				{
					if (argc == 1 && args[0]->rettype() != xpath_type_node_set) return error("Function has to be applied to node set");
					return alloc_node(argc == 0 ? ast_func_namespace_uri_0 : ast_func_namespace_uri_1, xpath_type_string, args[0]);
				}
				else if (name == PUGIXML_TEXT("normalize-space") && argc <= 1)
					return alloc_node(argc == 0 ? ast_func_normalize_space_0 : ast_func_normalize_space_1, xpath_type_string, args[0], args[1]);
				else if (name == PUGIXML_TEXT("not") && argc == 1)
					return alloc_node(ast_func_not, xpath_type_boolean, args[0]);
				else if (name == PUGIXML_TEXT("number") && argc <= 1)
					return alloc_node(argc == 0 ? ast_func_number_0 : ast_func_number_1, xpath_type_number, args[0]);

				break;

			case 'p':
				if (name == PUGIXML_TEXT("position") && argc == 0)
					return alloc_node(ast_func_position, xpath_type_number);

				break;

			case 'r':
				if (name == PUGIXML_TEXT("round") && argc == 1)
					return alloc_node(ast_func_round, xpath_type_number, args[0]);

				break;

			case 's':
				if (name == PUGIXML_TEXT("string") && argc <= 1)
					return alloc_node(argc == 0 ? ast_func_string_0 : ast_func_string_1, xpath_type_string, args[0]);
				else if (name == PUGIXML_TEXT("string-length") && argc <= 1)
					return alloc_node(argc == 0 ? ast_func_string_length_0 : ast_func_string_length_1, xpath_type_number, args[0]);
				else if (name == PUGIXML_TEXT("starts-with") && argc == 2)
					return alloc_node(ast_func_starts_with, xpath_type_boolean, args[0], args[1]);
				else if (name == PUGIXML_TEXT("substring-before") && argc == 2)
					return alloc_node(ast_func_substring_before, xpath_type_string, args[0], args[1]);
				else if (name == PUGIXML_TEXT("substring-after") && argc == 2)
					return alloc_node(ast_func_substring_after, xpath_type_string, args[0], args[1]);
				else if (name == PUGIXML_TEXT("substring") && (argc == 2 || argc == 3))
					return alloc_node(argc == 2 ? ast_func_substring_2 : ast_func_substring_3, xpath_type_string, args[0], args[1]);
				else if (name == PUGIXML_TEXT("sum") && argc == 1)
				{
					if (args[0]->rettype() != xpath_type_node_set) return error("Function has to be applied to node set");
					return alloc_node(ast_func_sum, xpath_type_number, args[0]);
				}

				break;

			case 't':
				if (name == PUGIXML_TEXT("translate") && argc == 3)
					return alloc_node(ast_func_translate, xpath_type_string, args[0], args[1]);
				else if (name == PUGIXML_TEXT("true") && argc == 0)
					return alloc_node(ast_func_true, xpath_type_boolean);

				break;

			default:
				break;
			}

			return error("Unrecognized function or wrong parameter count");
		}

		axis_t parse_axis_name(const xpath_lexer_string& name, bool& specified)
		{
			specified = true;

			switch (name.begin[0])
			{
			case 'a':
				if (name == PUGIXML_TEXT("ancestor"))
					return axis_ancestor;
				else if (name == PUGIXML_TEXT("ancestor-or-self"))
					return axis_ancestor_or_self;
				else if (name == PUGIXML_TEXT("attribute"))
					return axis_attribute;

				break;

			case 'c':
				if (name == PUGIXML_TEXT("child"))
					return axis_child;

				break;

			case 'd':
				if (name == PUGIXML_TEXT("descendant"))
					return axis_descendant;
				else if (name == PUGIXML_TEXT("descendant-or-self"))
					return axis_descendant_or_self;

				break;

			case 'f':
				if (name == PUGIXML_TEXT("following"))
					return axis_following;
				else if (name == PUGIXML_TEXT("following-sibling"))
					return axis_following_sibling;

				break;

			case 'n':
				if (name == PUGIXML_TEXT("namespace"))
					return axis_namespace;

				break;

			case 'p':
				if (name == PUGIXML_TEXT("parent"))
					return axis_parent;
				else if (name == PUGIXML_TEXT("preceding"))
					return axis_preceding;
				else if (name == PUGIXML_TEXT("preceding-sibling"))
					return axis_preceding_sibling;

				break;

			case 's':
				if (name == PUGIXML_TEXT("self"))
					return axis_self;

				break;

			default:
				break;
			}

			specified = false;
			return axis_child;
		}

		nodetest_t parse_node_test_type(const xpath_lexer_string& name)
		{
			switch (name.begin[0])
			{
			case 'c':
				if (name == PUGIXML_TEXT("comment"))
					return nodetest_type_comment;

				break;

			case 'n':
				if (name == PUGIXML_TEXT("node"))
					return nodetest_type_node;

				break;

			case 'p':
				if (name == PUGIXML_TEXT("processing-instruction"))
					return nodetest_type_pi;

				break;

			case 't':
				if (name == PUGIXML_TEXT("text"))
					return nodetest_type_text;

				break;

			default:
				break;
			}

			return nodetest_none;
		}

		// PrimaryExpr ::= VariableReference | '(' Expr ')' | Literal | Number | FunctionCall
		xpath_ast_node* parse_primary_expression()
		{
			switch (_lexer.current())
			{
			case lex_var_ref:
			{
				xpath_lexer_string name = _lexer.contents();

				if (!_variables)
					return error("Unknown variable: variable set is not provided");

				xpath_variable* var = NULL;
				if (!get_variable_scratch(_scratch, _variables, name.begin, name.end, &var))
					return error_oom();

				if (!var)
					return error("Unknown variable: variable set does not contain the given name");

				_lexer.next();

				return alloc_node(ast_variable, var->type(), var);
			}

			case lex_open_brace:
			{
				_lexer.next();

				xpath_ast_node* n = parse_expression();
				if (!n) return NULL;

				if (_lexer.current() != lex_close_brace)
					return error("Expected ')' to match an opening '('");

				_lexer.next();

				return n;
			}

			case lex_quoted_string:
			{
				const char_t* value = alloc_string(_lexer.contents());
				if (!value) return NULL;

				_lexer.next();

				return alloc_node(ast_string_constant, xpath_type_string, value);
			}

			case lex_number:
			{
				double value = 0;

				if (!convert_string_to_number_scratch(_scratch, _lexer.contents().begin, _lexer.contents().end, &value))
					return error_oom();

				_lexer.next();

				return alloc_node(ast_number_constant, xpath_type_number, value);
			}

			case lex_string:
			{
				xpath_ast_node* args[2] = {NULL};
				size_t argc = 0;

				xpath_lexer_string function = _lexer.contents();
				_lexer.next();

				xpath_ast_node* last_arg = NULL;

				if (_lexer.current() != lex_open_brace)
					return error("Unrecognized function call");
				_lexer.next();

				size_t old_depth = _depth;

				while (_lexer.current() != lex_close_brace)
				{
					if (argc > 0)
					{
						if (_lexer.current() != lex_comma)
							return error("No comma between function arguments");
						_lexer.next();
					}

					if (++_depth > xpath_ast_depth_limit)
						return error_rec();

					xpath_ast_node* n = parse_expression();
					if (!n) return NULL;

					if (argc < 2) args[argc] = n;
					else last_arg->set_next(n);

					argc++;
					last_arg = n;
				}

				_lexer.next();

				_depth = old_depth;

				return parse_function(function, argc, args);
			}

			default:
				return error("Unrecognizable primary expression");
			}
		}

		// FilterExpr ::= PrimaryExpr | FilterExpr Predicate
		// Predicate ::= '[' PredicateExpr ']'
		// PredicateExpr ::= Expr
		xpath_ast_node* parse_filter_expression()
		{
			xpath_ast_node* n = parse_primary_expression();
			if (!n) return NULL;

			size_t old_depth = _depth;

			while (_lexer.current() == lex_open_square_brace)
			{
				_lexer.next();

				if (++_depth > xpath_ast_depth_limit)
					return error_rec();

				if (n->rettype() != xpath_type_node_set)
					return error("Predicate has to be applied to node set");

				xpath_ast_node* expr = parse_expression();
				if (!expr) return NULL;

				n = alloc_node(ast_filter, n, expr, predicate_default);
				if (!n) return NULL;

				if (_lexer.current() != lex_close_square_brace)
					return error("Expected ']' to match an opening '['");

				_lexer.next();
			}

			_depth = old_depth;

			return n;
		}

		// Step ::= AxisSpecifier NodeTest Predicate* | AbbreviatedStep
		// AxisSpecifier ::= AxisName '::' | '@'?
		// NodeTest ::= NameTest | NodeType '(' ')' | 'processing-instruction' '(' Literal ')'
		// NameTest ::= '*' | NCName ':' '*' | QName
		// AbbreviatedStep ::= '.' | '..'
		xpath_ast_node* parse_step(xpath_ast_node* set)
		{
			if (set && set->rettype() != xpath_type_node_set)
				return error("Step has to be applied to node set");

			bool axis_specified = false;
			axis_t axis = axis_child; // implied child axis

			if (_lexer.current() == lex_axis_attribute)
			{
				axis = axis_attribute;
				axis_specified = true;

				_lexer.next();
			}
			else if (_lexer.current() == lex_dot)
			{
				_lexer.next();

				if (_lexer.current() == lex_open_square_brace)
					return error("Predicates are not allowed after an abbreviated step");

				return alloc_node(ast_step, set, axis_self, nodetest_type_node, NULL);
			}
			else if (_lexer.current() == lex_double_dot)
			{
				_lexer.next();

				if (_lexer.current() == lex_open_square_brace)
					return error("Predicates are not allowed after an abbreviated step");

				return alloc_node(ast_step, set, axis_parent, nodetest_type_node, NULL);
			}

			nodetest_t nt_type = nodetest_none;
			xpath_lexer_string nt_name;

			if (_lexer.current() == lex_string)
			{
				// node name test
				nt_name = _lexer.contents();
				_lexer.next();

				// was it an axis name?
				if (_lexer.current() == lex_double_colon)
				{
					// parse axis name
					if (axis_specified)
						return error("Two axis specifiers in one step");

					axis = parse_axis_name(nt_name, axis_specified);

					if (!axis_specified)
						return error("Unknown axis");

					// read actual node test
					_lexer.next();

					if (_lexer.current() == lex_multiply)
					{
						nt_type = nodetest_all;
						nt_name = xpath_lexer_string();
						_lexer.next();
					}
					else if (_lexer.current() == lex_string)
					{
						nt_name = _lexer.contents();
						_lexer.next();
					}
					else
					{
						return error("Unrecognized node test");
					}
				}

				if (nt_type == nodetest_none)
				{
					// node type test or processing-instruction
					if (_lexer.current() == lex_open_brace)
					{
						_lexer.next();

						if (_lexer.current() == lex_close_brace)
						{
							_lexer.next();

							nt_type = parse_node_test_type(nt_name);

							if (nt_type == nodetest_none)
								return error("Unrecognized node type");

							nt_name = xpath_lexer_string();
						}
						else if (nt_name == PUGIXML_TEXT("processing-instruction"))
						{
							if (_lexer.current() != lex_quoted_string)
								return error("Only literals are allowed as arguments to processing-instruction()");

							nt_type = nodetest_pi;
							nt_name = _lexer.contents();
							_lexer.next();

							if (_lexer.current() != lex_close_brace)
								return error("Unmatched brace near processing-instruction()");
							_lexer.next();
						}
						else
						{
							return error("Unmatched brace near node type test");
						}
					}
					// QName or NCName:*
					else
					{
						if (nt_name.end - nt_name.begin > 2 && nt_name.end[-2] == ':' && nt_name.end[-1] == '*') // NCName:*
						{
							nt_name.end--; // erase *

							nt_type = nodetest_all_in_namespace;
						}
						else
						{
							nt_type = nodetest_name;
						}
					}
				}
			}
			else if (_lexer.current() == lex_multiply)
			{
				nt_type = nodetest_all;
				_lexer.next();
			}
			else
			{
				return error("Unrecognized node test");
			}

			const char_t* nt_name_copy = alloc_string(nt_name);
			if (!nt_name_copy) return NULL;

			xpath_ast_node* n = alloc_node(ast_step, set, axis, nt_type, nt_name_copy);
			if (!n) return NULL;

			size_t old_depth = _depth;

			xpath_ast_node* last = NULL;

			while (_lexer.current() == lex_open_square_brace)
			{
				_lexer.next();

				if (++_depth > xpath_ast_depth_limit)
					return error_rec();

				xpath_ast_node* expr = parse_expression();
				if (!expr) return NULL;

				xpath_ast_node* pred = alloc_node(ast_predicate, NULL, expr, predicate_default);
				if (!pred) return NULL;

				if (_lexer.current() != lex_close_square_brace)
					return error("Expected ']' to match an opening '['");
				_lexer.next();

				if (last) last->set_next(pred);
				else n->set_right(pred);

				last = pred;
			}

			_depth = old_depth;

			return n;
		}

		// RelativeLocationPath ::= Step | RelativeLocationPath '/' Step | RelativeLocationPath '//' Step
		xpath_ast_node* parse_relative_location_path(xpath_ast_node* set)
		{
			xpath_ast_node* n = parse_step(set);
			if (!n) return NULL;

			size_t old_depth = _depth;

			while (_lexer.current() == lex_slash || _lexer.current() == lex_double_slash)
			{
				lexeme_t l = _lexer.current();
				_lexer.next();

				if (l == lex_double_slash)
				{
					n = alloc_node(ast_step, n, axis_descendant_or_self, nodetest_type_node, NULL);
					if (!n) return NULL;

					++_depth;
				}

				if (++_depth > xpath_ast_depth_limit)
					return error_rec();

				n = parse_step(n);
				if (!n) return NULL;
			}

			_depth = old_depth;

			return n;
		}

		// LocationPath ::= RelativeLocationPath | AbsoluteLocationPath
		// AbsoluteLocationPath ::= '/' RelativeLocationPath? | '//' RelativeLocationPath
		xpath_ast_node* parse_location_path()
		{
			if (_lexer.current() == lex_slash)
			{
				_lexer.next();

				xpath_ast_node* n = alloc_node(ast_step_root, xpath_type_node_set);
				if (!n) return NULL;

				// relative location path can start from axis_attribute, dot, double_dot, multiply and string lexemes; any other lexeme means standalone root path
				lexeme_t l = _lexer.current();

				if (l == lex_string || l == lex_axis_attribute || l == lex_dot || l == lex_double_dot || l == lex_multiply)
					return parse_relative_location_path(n);
				else
					return n;
			}
			else if (_lexer.current() == lex_double_slash)
			{
				_lexer.next();

				xpath_ast_node* n = alloc_node(ast_step_root, xpath_type_node_set);
				if (!n) return NULL;

				n = alloc_node(ast_step, n, axis_descendant_or_self, nodetest_type_node, NULL);
				if (!n) return NULL;

				return parse_relative_location_path(n);
			}

			// else clause moved outside of if because of bogus warning 'control may reach end of non-void function being inlined' in gcc 4.0.1
			return parse_relative_location_path(NULL);
		}

		// PathExpr ::= LocationPath
		//				| FilterExpr
		//				| FilterExpr '/' RelativeLocationPath
		//				| FilterExpr '//' RelativeLocationPath
		// UnionExpr ::= PathExpr | UnionExpr '|' PathExpr
		// UnaryExpr ::= UnionExpr | '-' UnaryExpr
		xpath_ast_node* parse_path_or_unary_expression()
		{
			// Clarification.
			// PathExpr begins with either LocationPath or FilterExpr.
			// FilterExpr begins with PrimaryExpr
			// PrimaryExpr begins with '$' in case of it being a variable reference,
			// '(' in case of it being an expression, string literal, number constant or
			// function call.
			if (_lexer.current() == lex_var_ref || _lexer.current() == lex_open_brace ||
				_lexer.current() == lex_quoted_string || _lexer.current() == lex_number ||
				_lexer.current() == lex_string)
			{
				if (_lexer.current() == lex_string)
				{
					// This is either a function call, or not - if not, we shall proceed with location path
					const char_t* state = _lexer.state();

					while (PUGI_IMPL_IS_CHARTYPE(*state, ct_space)) ++state;

					if (*state != '(')
						return parse_location_path();

					// This looks like a function call; however this still can be a node-test. Check it.
					if (parse_node_test_type(_lexer.contents()) != nodetest_none)
						return parse_location_path();
				}

				xpath_ast_node* n = parse_filter_expression();
				if (!n) return NULL;

				if (_lexer.current() == lex_slash || _lexer.current() == lex_double_slash)
				{
					lexeme_t l = _lexer.current();
					_lexer.next();

					if (l == lex_double_slash)
					{
						if (n->rettype() != xpath_type_node_set)
							return error("Step has to be applied to node set");

						n = alloc_node(ast_step, n, axis_descendant_or_self, nodetest_type_node, NULL);
						if (!n) return NULL;
					}

					// select from location path
					return parse_relative_location_path(n);
				}

				return n;
			}
			else if (_lexer.current() == lex_minus)
			{
				_lexer.next();

				// precedence 7+ - only parses union expressions
				xpath_ast_node* n = parse_expression(7);
				if (!n) return NULL;

				return alloc_node(ast_op_negate, xpath_type_number, n);
			}
			else
			{
				return parse_location_path();
			}
		}

		struct binary_op_t
		{
			ast_type_t asttype;
			xpath_value_type rettype;
			int precedence;

			binary_op_t(): asttype(ast_unknown), rettype(xpath_type_none), precedence(0)
			{
			}

			binary_op_t(ast_type_t asttype_, xpath_value_type rettype_, int precedence_): asttype(asttype_), rettype(rettype_), precedence(precedence_)
			{
			}

			static binary_op_t parse(xpath_lexer& lexer)
			{
				switch (lexer.current())
				{
				case lex_string:
					if (lexer.contents() == PUGIXML_TEXT("or"))
						return binary_op_t(ast_op_or, xpath_type_boolean, 1);
					else if (lexer.contents() == PUGIXML_TEXT("and"))
						return binary_op_t(ast_op_and, xpath_type_boolean, 2);
					else if (lexer.contents() == PUGIXML_TEXT("div"))
						return binary_op_t(ast_op_divide, xpath_type_number, 6);
					else if (lexer.contents() == PUGIXML_TEXT("mod"))
						return binary_op_t(ast_op_mod, xpath_type_number, 6);
					else
						return binary_op_t();

				case lex_equal:
					return binary_op_t(ast_op_equal, xpath_type_boolean, 3);

				case lex_not_equal:
					return binary_op_t(ast_op_not_equal, xpath_type_boolean, 3);

				case lex_less:
					return binary_op_t(ast_op_less, xpath_type_boolean, 4);

				case lex_greater:
					return binary_op_t(ast_op_greater, xpath_type_boolean, 4);

				case lex_less_or_equal:
					return binary_op_t(ast_op_less_or_equal, xpath_type_boolean, 4);

				case lex_greater_or_equal:
					return binary_op_t(ast_op_greater_or_equal, xpath_type_boolean, 4);

				case lex_plus:
					return binary_op_t(ast_op_add, xpath_type_number, 5);

				case lex_minus:
					return binary_op_t(ast_op_subtract, xpath_type_number, 5);

				case lex_multiply:
					return binary_op_t(ast_op_multiply, xpath_type_number, 6);

				case lex_union:
					return binary_op_t(ast_op_union, xpath_type_node_set, 7);

				default:
					return binary_op_t();
				}
			}
		};

		xpath_ast_node* parse_expression_rec(xpath_ast_node* lhs, int limit)
		{
			binary_op_t op = binary_op_t::parse(_lexer);

			while (op.asttype != ast_unknown && op.precedence >= limit)
			{
				_lexer.next();

				if (++_depth > xpath_ast_depth_limit)
					return error_rec();

				xpath_ast_node* rhs = parse_path_or_unary_expression();
				if (!rhs) return NULL;

				binary_op_t nextop = binary_op_t::parse(_lexer);

				while (nextop.asttype != ast_unknown && nextop.precedence > op.precedence)
				{
					rhs = parse_expression_rec(rhs, nextop.precedence);
					if (!rhs) return NULL;

					nextop = binary_op_t::parse(_lexer);
				}

				if (op.asttype == ast_op_union && (lhs->rettype() != xpath_type_node_set || rhs->rettype() != xpath_type_node_set))
					return error("Union operator has to be applied to node sets");

				lhs = alloc_node(op.asttype, op.rettype, lhs, rhs);
				if (!lhs) return NULL;

				op = binary_op_t::parse(_lexer);
			}

			return lhs;
		}

		// Expr ::= OrExpr
		// OrExpr ::= AndExpr | OrExpr 'or' AndExpr
		// AndExpr ::= EqualityExpr | AndExpr 'and' EqualityExpr
		// EqualityExpr ::= RelationalExpr
		//					| EqualityExpr '=' RelationalExpr
		//					| EqualityExpr '!=' RelationalExpr
		// RelationalExpr ::= AdditiveExpr
		//					  | RelationalExpr '<' AdditiveExpr
		//					  | RelationalExpr '>' AdditiveExpr
		//					  | RelationalExpr '<=' AdditiveExpr
		//					  | RelationalExpr '>=' AdditiveExpr
		// AdditiveExpr ::= MultiplicativeExpr
		//					| AdditiveExpr '+' MultiplicativeExpr
		//					| AdditiveExpr '-' MultiplicativeExpr
		// MultiplicativeExpr ::= UnaryExpr
		//						  | MultiplicativeExpr '*' UnaryExpr
		//						  | MultiplicativeExpr 'div' UnaryExpr
		//						  | MultiplicativeExpr 'mod' UnaryExpr
		xpath_ast_node* parse_expression(int limit = 0)
		{
			size_t old_depth = _depth;

			if (++_depth > xpath_ast_depth_limit)
				return error_rec();

			xpath_ast_node* n = parse_path_or_unary_expression();
			if (!n) return NULL;

			n = parse_expression_rec(n, limit);

			_depth = old_depth;

			return n;
		}

		xpath_parser(const char_t* query, xpath_variable_set* variables, xpath_allocator* alloc, xpath_parse_result* result): _alloc(alloc), _lexer(query), _query(query), _variables(variables), _result(result), _depth(0)
		{
		}

		xpath_ast_node* parse()
		{
			xpath_ast_node* n = parse_expression();
			if (!n) return NULL;

			assert(_depth == 0);

			// check if there are unparsed tokens left
			if (_lexer.current() != lex_eof)
				return error("Incorrect query");

			return n;
		}

		static xpath_ast_node* parse(const char_t* query, xpath_variable_set* variables, xpath_allocator* alloc, xpath_parse_result* result)
		{
			xpath_parser parser(query, variables, alloc, result);

			return parser.parse();
		}
	};

	struct xpath_query_impl
	{
		static xpath_query_impl* create()
		{
			void* memory = xml_memory::allocate(sizeof(xpath_query_impl));
			if (!memory) return NULL;

			return new (memory) xpath_query_impl();
		}

		static void destroy(xpath_query_impl* impl)
		{
			// free all allocated pages
			impl->alloc.release();

			// free allocator memory (with the first page)
			xml_memory::deallocate(impl);
		}

		xpath_query_impl(): root(NULL), alloc(&block, &oom), oom(false)
		{
			block.next = NULL;
			block.capacity = sizeof(block.data);
		}

		xpath_ast_node* root;
		xpath_allocator alloc;
		xpath_memory_block block;
		bool oom;
	};

	PUGI_IMPL_FN impl::xpath_ast_node* evaluate_node_set_prepare(xpath_query_impl* impl)
	{
		if (!impl) return NULL;

		if (impl->root->rettype() != xpath_type_node_set)
		{
		#ifdef PUGIXML_NO_EXCEPTIONS
			return 0;
		#else
			xpath_parse_result res;
			res.error = "Expression does not evaluate to node set";

			throw xpath_exception(res);
		#endif
		}

		return impl->root;
	}
PUGI_IMPL_NS_END

namespace pugi
{
#ifndef PUGIXML_NO_EXCEPTIONS
	PUGI_IMPL_FN xpath_exception::xpath_exception(const xpath_parse_result& result_): _result(result_)
	{
		assert(_result.error);
	}

	PUGI_IMPL_FN const char* xpath_exception::what() const PUGIXML_NOEXCEPT
	{
		return _result.error;
	}

	PUGI_IMPL_FN const xpath_parse_result& xpath_exception::result() const
	{
		return _result;
	}
#endif

	PUGI_IMPL_FN xpath_node::xpath_node()
	{
	}

	PUGI_IMPL_FN xpath_node::xpath_node(const xml_node& node_): _node(node_)
	{
	}

	PUGI_IMPL_FN xpath_node::xpath_node(const xml_attribute& attribute_, const xml_node& parent_): _node(attribute_ ? parent_ : xml_node()), _attribute(attribute_)
	{
	}

	PUGI_IMPL_FN xml_node xpath_node::node() const
	{
		return _attribute ? xml_node() : _node;
	}

	PUGI_IMPL_FN xml_attribute xpath_node::attribute() const
	{
		return _attribute;
	}

	PUGI_IMPL_FN xml_node xpath_node::parent() const
	{
		return _attribute ? _node : _node.parent();
	}

	PUGI_IMPL_FN static void unspecified_bool_xpath_node(xpath_node***)
	{
	}

	PUGI_IMPL_FN xpath_node::operator xpath_node::unspecified_bool_type() const
	{
		return (_node || _attribute) ? unspecified_bool_xpath_node : NULL;
	}

	PUGI_IMPL_FN bool xpath_node::operator!() const
	{
		return !(_node || _attribute);
	}

	PUGI_IMPL_FN bool xpath_node::operator==(const xpath_node& n) const
	{
		return _node == n._node && _attribute == n._attribute;
	}

	PUGI_IMPL_FN bool xpath_node::operator!=(const xpath_node& n) const
	{
		return _node != n._node || _attribute != n._attribute;
	}

#ifdef __BORLANDC__
	PUGI_IMPL_FN bool operator&&(const xpath_node& lhs, bool rhs)
	{
		return (bool)lhs && rhs;
	}

	PUGI_IMPL_FN bool operator||(const xpath_node& lhs, bool rhs)
	{
		return (bool)lhs || rhs;
	}
#endif

	PUGI_IMPL_FN void xpath_node_set::_assign(const_iterator begin_, const_iterator end_, type_t type_)
	{
		assert(begin_ <= end_);

		size_t size_ = static_cast<size_t>(end_ - begin_);

		// use internal buffer for 0 or 1 elements, heap buffer otherwise
		xpath_node* storage = (size_ <= 1) ? _storage : static_cast<xpath_node*>(impl::xml_memory::allocate(size_ * sizeof(xpath_node)));

		if (!storage)
		{
		#ifdef PUGIXML_NO_EXCEPTIONS
			return;
		#else
			throw std::bad_alloc();
		#endif
		}

		// deallocate old buffer
		if (_begin != _storage)
			impl::xml_memory::deallocate(_begin);

		// size check is necessary because for begin_ = end_ = nullptr, memcpy is UB
		if (size_)
			memcpy(storage, begin_, size_ * sizeof(xpath_node));

		_begin = storage;
		_end = storage + size_;
		_type = type_;
	}

#ifdef PUGIXML_HAS_MOVE
	PUGI_IMPL_FN void xpath_node_set::_move(xpath_node_set& rhs) PUGIXML_NOEXCEPT
	{
		_type = rhs._type;
		_storage[0] = rhs._storage[0];
		_begin = (rhs._begin == rhs._storage) ? _storage : rhs._begin;
		_end = _begin + (rhs._end - rhs._begin);

		rhs._type = type_unsorted;
		rhs._begin = rhs._storage;
		rhs._end = rhs._storage;
	}
#endif

	PUGI_IMPL_FN xpath_node_set::xpath_node_set(): _type(type_unsorted), _begin(_storage), _end(_storage)
	{
	}

	PUGI_IMPL_FN xpath_node_set::xpath_node_set(const_iterator begin_, const_iterator end_, type_t type_): _type(type_unsorted), _begin(_storage), _end(_storage)
	{
		_assign(begin_, end_, type_);
	}

	PUGI_IMPL_FN xpath_node_set::~xpath_node_set()
	{
		if (_begin != _storage)
			impl::xml_memory::deallocate(_begin);
	}

	PUGI_IMPL_FN xpath_node_set::xpath_node_set(const xpath_node_set& ns): _type(type_unsorted), _begin(_storage), _end(_storage)
	{
		_assign(ns._begin, ns._end, ns._type);
	}

	PUGI_IMPL_FN xpath_node_set& xpath_node_set::operator=(const xpath_node_set& ns)
	{
		if (this == &ns) return *this;

		_assign(ns._begin, ns._end, ns._type);

		return *this;
	}

#ifdef PUGIXML_HAS_MOVE
	PUGI_IMPL_FN xpath_node_set::xpath_node_set(xpath_node_set&& rhs) PUGIXML_NOEXCEPT: _type(type_unsorted), _begin(_storage), _end(_storage)
	{
		_move(rhs);
	}

	PUGI_IMPL_FN xpath_node_set& xpath_node_set::operator=(xpath_node_set&& rhs) PUGIXML_NOEXCEPT
	{
		if (this == &rhs) return *this;

		if (_begin != _storage)
			impl::xml_memory::deallocate(_begin);

		_move(rhs);

		return *this;
	}
#endif

	PUGI_IMPL_FN xpath_node_set::type_t xpath_node_set::type() const
	{
		return _type;
	}

	PUGI_IMPL_FN size_t xpath_node_set::size() const
	{
		return _end - _begin;
	}

	PUGI_IMPL_FN bool xpath_node_set::empty() const
	{
		return _begin == _end;
	}

	PUGI_IMPL_FN const xpath_node& xpath_node_set::operator[](size_t index) const
	{
		assert(index < size());
		return _begin[index];
	}

	PUGI_IMPL_FN xpath_node_set::const_iterator xpath_node_set::begin() const
	{
		return _begin;
	}

	PUGI_IMPL_FN xpath_node_set::const_iterator xpath_node_set::end() const
	{
		return _end;
	}

	PUGI_IMPL_FN void xpath_node_set::sort(bool reverse)
	{
		_type = impl::xpath_sort(_begin, _end, _type, reverse);
	}

	PUGI_IMPL_FN xpath_node xpath_node_set::first() const
	{
		return impl::xpath_first(_begin, _end, _type);
	}

	PUGI_IMPL_FN xpath_parse_result::xpath_parse_result(): error("Internal error"), offset(0)
	{
	}

	PUGI_IMPL_FN xpath_parse_result::operator bool() const
	{
		return error == NULL;
	}

	PUGI_IMPL_FN const char* xpath_parse_result::description() const
	{
		return error ? error : "No error";
	}

	PUGI_IMPL_FN xpath_variable::xpath_variable(xpath_value_type type_): _type(type_), _next(NULL)
	{
	}

	PUGI_IMPL_FN const char_t* xpath_variable::name() const
	{
		switch (_type)
		{
		case xpath_type_node_set:
			return static_cast<const impl::xpath_variable_node_set*>(this)->name;

		case xpath_type_number:
			return static_cast<const impl::xpath_variable_number*>(this)->name;

		case xpath_type_string:
			return static_cast<const impl::xpath_variable_string*>(this)->name;

		case xpath_type_boolean:
			return static_cast<const impl::xpath_variable_boolean*>(this)->name;

		default:
			assert(false && "Invalid variable type"); // unreachable
			return NULL;
		}
	}

	PUGI_IMPL_FN xpath_value_type xpath_variable::type() const
	{
		return _type;
	}

	PUGI_IMPL_FN bool xpath_variable::get_boolean() const
	{
		return (_type == xpath_type_boolean) ? static_cast<const impl::xpath_variable_boolean*>(this)->value : false;
	}

	PUGI_IMPL_FN double xpath_variable::get_number() const
	{
		return (_type == xpath_type_number) ? static_cast<const impl::xpath_variable_number*>(this)->value : impl::gen_nan();
	}

	PUGI_IMPL_FN const char_t* xpath_variable::get_string() const
	{
		const char_t* value = (_type == xpath_type_string) ? static_cast<const impl::xpath_variable_string*>(this)->value : NULL;
		return value ? value : PUGIXML_TEXT("");
	}

	PUGI_IMPL_FN const xpath_node_set& xpath_variable::get_node_set() const
	{
		if (_type == xpath_type_node_set)
			return static_cast<const impl::xpath_variable_node_set*>(this)->value;
		static const xpath_node_set dummy_node_set;
		return dummy_node_set;
	}

	PUGI_IMPL_FN bool xpath_variable::set(bool value)
	{
		if (_type != xpath_type_boolean) return false;

		static_cast<impl::xpath_variable_boolean*>(this)->value = value;
		return true;
	}

	PUGI_IMPL_FN bool xpath_variable::set(double value)
	{
		if (_type != xpath_type_number) return false;

		static_cast<impl::xpath_variable_number*>(this)->value = value;
		return true;
	}

	PUGI_IMPL_FN bool xpath_variable::set(const char_t* value)
	{
		if (_type != xpath_type_string) return false;

		impl::xpath_variable_string* var = static_cast<impl::xpath_variable_string*>(this);

		// duplicate string
		size_t size = (impl::strlength(value) + 1) * sizeof(char_t);

		char_t* copy = static_cast<char_t*>(impl::xml_memory::allocate(size));
		if (!copy) return false;

		memcpy(copy, value, size);

		// replace old string
		if (var->value) impl::xml_memory::deallocate(var->value);
		var->value = copy;

		return true;
	}

	PUGI_IMPL_FN bool xpath_variable::set(const xpath_node_set& value)
	{
		if (_type != xpath_type_node_set) return false;

		static_cast<impl::xpath_variable_node_set*>(this)->value = value;
		return true;
	}

	PUGI_IMPL_FN xpath_variable_set::xpath_variable_set()
	{
		for (size_t i = 0; i < sizeof(_data) / sizeof(_data[0]); ++i)
			_data[i] = NULL;
	}

	PUGI_IMPL_FN xpath_variable_set::~xpath_variable_set()
	{
		for (size_t i = 0; i < sizeof(_data) / sizeof(_data[0]); ++i)
			_destroy(_data[i]);
	}

	PUGI_IMPL_FN xpath_variable_set::xpath_variable_set(const xpath_variable_set& rhs)
	{
		for (size_t i = 0; i < sizeof(_data) / sizeof(_data[0]); ++i)
			_data[i] = NULL;

		_assign(rhs);
	}

	PUGI_IMPL_FN xpath_variable_set& xpath_variable_set::operator=(const xpath_variable_set& rhs)
	{
		if (this == &rhs) return *this;

		_assign(rhs);

		return *this;
	}

#ifdef PUGIXML_HAS_MOVE
	PUGI_IMPL_FN xpath_variable_set::xpath_variable_set(xpath_variable_set&& rhs) PUGIXML_NOEXCEPT
	{
		for (size_t i = 0; i < sizeof(_data) / sizeof(_data[0]); ++i)
		{
			_data[i] = rhs._data[i];
			rhs._data[i] = NULL;
		}
	}

	PUGI_IMPL_FN xpath_variable_set& xpath_variable_set::operator=(xpath_variable_set&& rhs) PUGIXML_NOEXCEPT
	{
		for (size_t i = 0; i < sizeof(_data) / sizeof(_data[0]); ++i)
		{
			_destroy(_data[i]);

			_data[i] = rhs._data[i];
			rhs._data[i] = NULL;
		}

		return *this;
	}
#endif

	PUGI_IMPL_FN void xpath_variable_set::_assign(const xpath_variable_set& rhs)
	{
		xpath_variable_set temp;

		for (size_t i = 0; i < sizeof(_data) / sizeof(_data[0]); ++i)
			if (rhs._data[i] && !_clone(rhs._data[i], &temp._data[i]))
				return;

		_swap(temp);
	}

	PUGI_IMPL_FN void xpath_variable_set::_swap(xpath_variable_set& rhs)
	{
		for (size_t i = 0; i < sizeof(_data) / sizeof(_data[0]); ++i)
		{
			xpath_variable* chain = _data[i];

			_data[i] = rhs._data[i];
			rhs._data[i] = chain;
		}
	}

	PUGI_IMPL_FN xpath_variable* xpath_variable_set::_find(const char_t* name) const
	{
		const size_t hash_size = sizeof(_data) / sizeof(_data[0]);
		size_t hash = impl::hash_string(name) % hash_size;

		// look for existing variable
		for (xpath_variable* var = _data[hash]; var; var = var->_next)
		{
			const char_t* vn = var->name();
			if (vn && impl::strequal(vn, name))
				return var;
		}

		return NULL;
	}

	PUGI_IMPL_FN bool xpath_variable_set::_clone(xpath_variable* var, xpath_variable** out_result)
	{
		xpath_variable* last = NULL;

		while (var)
		{
			// allocate storage for new variable
			xpath_variable* nvar = impl::new_xpath_variable(var->_type, var->name());
			if (!nvar) return false;

			// link the variable to the result immediately to handle failures gracefully
			if (last)
				last->_next = nvar;
			else
				*out_result = nvar;

			last = nvar;

			// copy the value; this can fail due to out-of-memory conditions
			if (!impl::copy_xpath_variable(nvar, var)) return false;

			var = var->_next;
		}

		return true;
	}

	PUGI_IMPL_FN void xpath_variable_set::_destroy(xpath_variable* var)
	{
		while (var)
		{
			xpath_variable* next = var->_next;

			impl::delete_xpath_variable(var->_type, var);

			var = next;
		}
	}

	PUGI_IMPL_FN xpath_variable* xpath_variable_set::add(const char_t* name, xpath_value_type type)
	{
		const size_t hash_size = sizeof(_data) / sizeof(_data[0]);
		size_t hash = impl::hash_string(name) % hash_size;

		// look for existing variable
		for (xpath_variable* var = _data[hash]; var; var = var->_next)
		{
			const char_t* vn = var->name();
			if (vn && impl::strequal(vn, name))
				return var->type() == type ? var : NULL;
		}

		// add new variable
		xpath_variable* result = impl::new_xpath_variable(type, name);

		if (result)
		{
			result->_next = _data[hash];

			_data[hash] = result;
		}

		return result;
	}

	PUGI_IMPL_FN bool xpath_variable_set::set(const char_t* name, bool value)
	{
		xpath_variable* var = add(name, xpath_type_boolean);
		return var ? var->set(value) : false;
	}

	PUGI_IMPL_FN bool xpath_variable_set::set(const char_t* name, double value)
	{
		xpath_variable* var = add(name, xpath_type_number);
		return var ? var->set(value) : false;
	}

	PUGI_IMPL_FN bool xpath_variable_set::set(const char_t* name, const char_t* value)
	{
		xpath_variable* var = add(name, xpath_type_string);
		return var ? var->set(value) : false;
	}

	PUGI_IMPL_FN bool xpath_variable_set::set(const char_t* name, const xpath_node_set& value)
	{
		xpath_variable* var = add(name, xpath_type_node_set);
		return var ? var->set(value) : false;
	}

	PUGI_IMPL_FN xpath_variable* xpath_variable_set::get(const char_t* name)
	{
		return _find(name);
	}

	PUGI_IMPL_FN const xpath_variable* xpath_variable_set::get(const char_t* name) const
	{
		return _find(name);
	}

	PUGI_IMPL_FN xpath_query::xpath_query(const char_t* query, xpath_variable_set* variables): _impl(NULL)
	{
		impl::xpath_query_impl* qimpl = impl::xpath_query_impl::create();

		if (!qimpl)
		{
		#ifdef PUGIXML_NO_EXCEPTIONS
			_result.error = "Out of memory";
		#else
			throw std::bad_alloc();
		#endif
		}
		else
		{
			using impl::auto_deleter; // MSVC7 workaround
			auto_deleter<impl::xpath_query_impl> impl(qimpl, impl::xpath_query_impl::destroy);

			qimpl->root = impl::xpath_parser::parse(query, variables, &qimpl->alloc, &_result);

			if (qimpl->root)
			{
				qimpl->root->optimize(&qimpl->alloc);

				_impl = impl.release();
				_result.error = NULL;
			}
			else
			{
			#ifdef PUGIXML_NO_EXCEPTIONS
				if (qimpl->oom) _result.error = "Out of memory";
			#else
				if (qimpl->oom) throw std::bad_alloc();
				throw xpath_exception(_result);
			#endif
			}
		}
	}

	PUGI_IMPL_FN xpath_query::xpath_query(): _impl(NULL)
	{
	}

	PUGI_IMPL_FN xpath_query::~xpath_query()
	{
		if (_impl)
			impl::xpath_query_impl::destroy(static_cast<impl::xpath_query_impl*>(_impl));
	}

#ifdef PUGIXML_HAS_MOVE
	PUGI_IMPL_FN xpath_query::xpath_query(xpath_query&& rhs) PUGIXML_NOEXCEPT
	{
		_impl = rhs._impl;
		_result = rhs._result;
		rhs._impl = NULL;
		rhs._result = xpath_parse_result();
	}

	PUGI_IMPL_FN xpath_query& xpath_query::operator=(xpath_query&& rhs) PUGIXML_NOEXCEPT
	{
		if (this == &rhs) return *this;

		if (_impl)
			impl::xpath_query_impl::destroy(static_cast<impl::xpath_query_impl*>(_impl));

		_impl = rhs._impl;
		_result = rhs._result;
		rhs._impl = NULL;
		rhs._result = xpath_parse_result();

		return *this;
	}
#endif

	PUGI_IMPL_FN xpath_value_type xpath_query::return_type() const
	{
		if (!_impl) return xpath_type_none;

		return static_cast<impl::xpath_query_impl*>(_impl)->root->rettype();
	}

	PUGI_IMPL_FN bool xpath_query::evaluate_boolean(const xpath_node& n) const
	{
		if (!_impl) return false;

		impl::xpath_context c(n, 1, 1);
		impl::xpath_stack_data sd;

		bool r = static_cast<impl::xpath_query_impl*>(_impl)->root->eval_boolean(c, sd.stack);

		if (sd.oom)
		{
		#ifdef PUGIXML_NO_EXCEPTIONS
			return false;
		#else
			throw std::bad_alloc();
		#endif
		}

		return r;
	}

	PUGI_IMPL_FN double xpath_query::evaluate_number(const xpath_node& n) const
	{
		if (!_impl) return impl::gen_nan();

		impl::xpath_context c(n, 1, 1);
		impl::xpath_stack_data sd;

		double r = static_cast<impl::xpath_query_impl*>(_impl)->root->eval_number(c, sd.stack);

		if (sd.oom)
		{
		#ifdef PUGIXML_NO_EXCEPTIONS
			return impl::gen_nan();
		#else
			throw std::bad_alloc();
		#endif
		}

		return r;
	}

#ifndef PUGIXML_NO_STL
	PUGI_IMPL_FN string_t xpath_query::evaluate_string(const xpath_node& n) const
	{
		if (!_impl) return string_t();

		impl::xpath_context c(n, 1, 1);
		impl::xpath_stack_data sd;

		impl::xpath_string r = static_cast<impl::xpath_query_impl*>(_impl)->root->eval_string(c, sd.stack);

		if (sd.oom)
		{
		#ifdef PUGIXML_NO_EXCEPTIONS
			return string_t();
		#else
			throw std::bad_alloc();
		#endif
		}

		return string_t(r.c_str(), r.length());
	}
#endif

	PUGI_IMPL_FN size_t xpath_query::evaluate_string(char_t* buffer, size_t capacity, const xpath_node& n) const
	{
		impl::xpath_context c(n, 1, 1);
		impl::xpath_stack_data sd;

		impl::xpath_string r = _impl ? static_cast<impl::xpath_query_impl*>(_impl)->root->eval_string(c, sd.stack) : impl::xpath_string();

		if (sd.oom)
		{
		#ifdef PUGIXML_NO_EXCEPTIONS
			r = impl::xpath_string();
		#else
			throw std::bad_alloc();
		#endif
		}

		size_t full_size = r.length() + 1;

		if (capacity > 0)
		{
			size_t size = (full_size < capacity) ? full_size : capacity;
			assert(size > 0);

			memcpy(buffer, r.c_str(), (size - 1) * sizeof(char_t));
			buffer[size - 1] = 0;
		}

		return full_size;
	}

	PUGI_IMPL_FN xpath_node_set xpath_query::evaluate_node_set(const xpath_node& n) const
	{
		impl::xpath_ast_node* root = impl::evaluate_node_set_prepare(static_cast<impl::xpath_query_impl*>(_impl));
		if (!root) return xpath_node_set();

		impl::xpath_context c(n, 1, 1);
		impl::xpath_stack_data sd;

		impl::xpath_node_set_raw r = root->eval_node_set(c, sd.stack, impl::nodeset_eval_all);

		if (sd.oom)
		{
		#ifdef PUGIXML_NO_EXCEPTIONS
			return xpath_node_set();
		#else
			throw std::bad_alloc();
		#endif
		}

		return xpath_node_set(r.begin(), r.end(), r.type());
	}

	PUGI_IMPL_FN xpath_node xpath_query::evaluate_node(const xpath_node& n) const
	{
		impl::xpath_ast_node* root = impl::evaluate_node_set_prepare(static_cast<impl::xpath_query_impl*>(_impl));
		if (!root) return xpath_node();

		impl::xpath_context c(n, 1, 1);
		impl::xpath_stack_data sd;

		impl::xpath_node_set_raw r = root->eval_node_set(c, sd.stack, impl::nodeset_eval_first);

		if (sd.oom)
		{
		#ifdef PUGIXML_NO_EXCEPTIONS
			return xpath_node();
		#else
			throw std::bad_alloc();
		#endif
		}

		return r.first();
	}

	PUGI_IMPL_FN const xpath_parse_result& xpath_query::result() const
	{
		return _result;
	}

	PUGI_IMPL_FN static void unspecified_bool_xpath_query(xpath_query***)
	{
	}

	PUGI_IMPL_FN xpath_query::operator xpath_query::unspecified_bool_type() const
	{
		return _impl ? unspecified_bool_xpath_query : NULL;
	}

	PUGI_IMPL_FN bool xpath_query::operator!() const
	{
		return !_impl;
	}

	PUGI_IMPL_FN xpath_node xml_node::select_node(const char_t* query, xpath_variable_set* variables) const
	{
		xpath_query q(query, variables);
		return q.evaluate_node(*this);
	}

	PUGI_IMPL_FN xpath_node xml_node::select_node(const xpath_query& query) const
	{
		return query.evaluate_node(*this);
	}

	PUGI_IMPL_FN xpath_node_set xml_node::select_nodes(const char_t* query, xpath_variable_set* variables) const
	{
		xpath_query q(query, variables);
		return q.evaluate_node_set(*this);
	}

	PUGI_IMPL_FN xpath_node_set xml_node::select_nodes(const xpath_query& query) const
	{
		return query.evaluate_node_set(*this);
	}

	PUGI_IMPL_FN xpath_node xml_node::select_single_node(const char_t* query, xpath_variable_set* variables) const
	{
		xpath_query q(query, variables);
		return q.evaluate_node(*this);
	}

	PUGI_IMPL_FN xpath_node xml_node::select_single_node(const xpath_query& query) const
	{
		return query.evaluate_node(*this);
	}
}

#endif

#ifdef __BORLANDC__
#	pragma option pop
#endif

#if defined(_MSC_VER) && defined(__c2__)
#	pragma clang diagnostic pop
#endif

#if defined(__clang__)
#	pragma clang diagnostic pop
#endif

// Intel C++ does not properly keep warning state for function templates,
// so popping warning state at the end of translation unit leads to warnings in the middle.
#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
#	pragma warning(pop)
#endif

// Undefine all local macros (makes sure we're not leaking macros in header-only mode)
#undef PUGI_IMPL_NO_INLINE
#undef PUGI_IMPL_UNLIKELY
#undef PUGI_IMPL_STATIC_ASSERT
#undef PUGI_IMPL_DMC_VOLATILE
#undef PUGI_IMPL_UNSIGNED_OVERFLOW
#undef PUGI_IMPL_MSVC_CRT_VERSION
#undef PUGI_IMPL_SNPRINTF
#undef PUGI_IMPL_NS_BEGIN
#undef PUGI_IMPL_NS_END
#undef PUGI_IMPL_FN
#undef PUGI_IMPL_FN_NO_INLINE
#undef PUGI_IMPL_GETHEADER_IMPL
#undef PUGI_IMPL_GETPAGE_IMPL
#undef PUGI_IMPL_GETPAGE
#undef PUGI_IMPL_NODETYPE
#undef PUGI_IMPL_IS_CHARTYPE_IMPL
#undef PUGI_IMPL_IS_CHARTYPE
#undef PUGI_IMPL_IS_CHARTYPEX
#undef PUGI_IMPL_ENDSWITH
#undef PUGI_IMPL_SKIPWS
#undef PUGI_IMPL_OPTSET
#undef PUGI_IMPL_PUSHNODE
#undef PUGI_IMPL_POPNODE
#undef PUGI_IMPL_SCANFOR
#undef PUGI_IMPL_SCANWHILE
#undef PUGI_IMPL_SCANWHILE_UNROLL
#undef PUGI_IMPL_ENDSEG
#undef PUGI_IMPL_THROW_ERROR
#undef PUGI_IMPL_CHECK_ERROR

#endif

/**
 * Copyright (c) 2006-2025 Arseny Kapoulkine
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#endif

/**
 * Copyright (c) 2006-2025 Arseny Kapoulkine
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef MINIZ_EXPORT
#define MINIZ_EXPORT
#endif
/* miniz.c 3.0.2 - public domain deflate/inflate, zlib-subset, ZIP
   reading/writing/appending, PNG writing See "unlicense" statement at the end
   of this file. Rich Geldreich <richgel99@gmail.com>, last updated Oct. 13,
   2013 Implements RFC 1950: http://www.ietf.org/rfc/rfc1950.txt and RFC 1951:
   http://www.ietf.org/rfc/rfc1951.txt

   Most API's defined in miniz.c are optional. For example, to disable the
   archive related functions just define MINIZ_NO_ARCHIVE_APIS, or to get rid of
   all stdio usage define MINIZ_NO_STDIO (see the list below for more macros).

   * Low-level Deflate/Inflate implementation notes:

     Compression: Use the "tdefl" API's. The compressor supports raw, static,
   and dynamic blocks, lazy or greedy parsing, match length filtering, RLE-only,
   and Huffman-only streams. It performs and compresses approximately as well as
   zlib.

     Decompression: Use the "tinfl" API's. The entire decompressor is
   implemented as a single function coroutine: see tinfl_decompress(). It
   supports decompression into a 32KB (or larger power of 2) wrapping buffer, or
   into a memory block large enough to hold the entire file.

     The low-level tdefl/tinfl API's do not make any use of dynamic memory
   allocation.

   * zlib-style API notes:

     miniz.c implements a fairly large subset of zlib. There's enough
   functionality present for it to be a drop-in zlib replacement in many apps:
        The z_stream struct, optional memory allocation callbacks
        deflateInit/deflateInit2/deflate/deflateReset/deflateEnd/deflateBound
        inflateInit/inflateInit2/inflate/inflateReset/inflateEnd
        compress, compress2, compressBound, uncompress
        CRC-32, Adler-32 - Using modern, minimal code size, CPU cache friendly
   routines. Supports raw deflate streams or standard zlib streams with adler-32
   checking.

     Limitations:
      The callback API's are not implemented yet. No support for gzip headers or
   zlib static dictionaries. I've tried to closely emulate zlib's various
   flavors of stream flushing and return status codes, but there are no
   guarantees that miniz.c pulls this off perfectly.

   * PNG writing: See the tdefl_write_image_to_png_file_in_memory() function,
   originally written by Alex Evans. Supports 1-4 bytes/pixel images.

   * ZIP archive API notes:

     The ZIP archive API's where designed with simplicity and efficiency in
   mind, with just enough abstraction to get the job done with minimal fuss.
   There are simple API's to retrieve file information, read files from existing
   archives, create new archives, append new files to existing archives, or
   clone archive data from one archive to another. It supports archives located
   in memory or the heap, on disk (using stdio.h), or you can specify custom
   file read/write callbacks.

     - Archive reading: Just call this function to read a single file from a
   disk archive:

      void *mz_zip_extract_archive_file_to_heap(const char *pZip_filename, const
   char *pArchive_name, size_t *pSize, mz_uint zip_flags);

     For more complex cases, use the "mz_zip_reader" functions. Upon opening an
   archive, the entire central directory is located and read as-is into memory,
   and subsequent file access only occurs when reading individual files.

     - Archives file scanning: The simple way is to use this function to scan a
   loaded archive for a specific file:

     int mz_zip_reader_locate_file(mz_zip_archive *pZip, const char *pName,
   const char *pComment, mz_uint flags);

     The locate operation can optionally check file comments too, which (as one
   example) can be used to identify multiple versions of the same file in an
   archive. This function uses a simple linear search through the central
     directory, so it's not very fast.

     Alternately, you can iterate through all the files in an archive (using
   mz_zip_reader_get_num_files()) and retrieve detailed info on each file by
   calling mz_zip_reader_file_stat().

     - Archive creation: Use the "mz_zip_writer" functions. The ZIP writer
   immediately writes compressed file data to disk and builds an exact image of
   the central directory in memory. The central directory image is written all
   at once at the end of the archive file when the archive is finalized.

     The archive writer can optionally align each file's local header and file
   data to any power of 2 alignment, which can be useful when the archive will
   be read from optical media. Also, the writer supports placing arbitrary data
   blobs at the very beginning of ZIP archives. Archives written using either
   feature are still readable by any ZIP tool.

     - Archive appending: The simple way to add a single file to an archive is
   to call this function:

      mz_bool mz_zip_add_mem_to_archive_file_in_place(const char *pZip_filename,
   const char *pArchive_name, const void *pBuf, size_t buf_size, const void
   *pComment, mz_uint16 comment_size, mz_uint level_and_flags);

     The archive will be created if it doesn't already exist, otherwise it'll be
   appended to. Note the appending is done in-place and is not an atomic
   operation, so if something goes wrong during the operation it's possible the
   archive could be left without a central directory (although the local file
   headers and file data will be fine, so the archive will be recoverable).

     For more complex archive modification scenarios:
     1. The safest way is to use a mz_zip_reader to read the existing archive,
   cloning only those bits you want to preserve into a new archive using using
   the mz_zip_writer_add_from_zip_reader() function (which compiles the
     compressed file data as-is). When you're done, delete the old archive and
   rename the newly written archive, and you're done. This is safe but requires
   a bunch of temporary disk space or heap memory.

     2. Or, you can convert an mz_zip_reader in-place to an mz_zip_writer using
   mz_zip_writer_init_from_reader(), append new files as needed, then finalize
   the archive which will write an updated central directory to the original
   archive. (This is basically what mz_zip_add_mem_to_archive_file_in_place()
   does.) There's a possibility that the archive's central directory could be
   lost with this method if anything goes wrong, though.

     - ZIP archive support limitations:
     No spanning support. Extraction functions can only handle unencrypted,
   stored or deflated files. Requires streams capable of seeking.

   * This is a header file library, like stb_image.c. To get only a header file,
   either cut and paste the below header, or create miniz.h, #define
   MINIZ_HEADER_FILE_ONLY, and then include miniz.c from it.

   * Important: For best perf. be sure to customize the below macros for your
   target platform: #define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1 #define
   MINIZ_LITTLE_ENDIAN 1 #define MINIZ_HAS_64BIT_REGISTERS 1

   * On platforms using glibc, Be sure to "#define _LARGEFILE64_SOURCE 1" before
   including miniz.c to ensure miniz uses the 64-bit variants: fopen64(),
   stat64(), etc. Otherwise you won't be able to process large files (i.e.
   32-bit stat() fails for me on files > 0x7FFFFFFF bytes).
*/
#pragma once

/* Defines to completely disable specific portions of miniz.c:
   If all macros here are defined the only functionality remaining will be
   CRC-32 and adler-32. */

/* Define MINIZ_NO_STDIO to disable all usage and any functions which rely on
 * stdio for file I/O. */
/*#define MINIZ_NO_STDIO */

/* If MINIZ_NO_TIME is specified then the ZIP archive functions will not be able
 * to get the current time, or */
/* get/set file times, and the C run-time funcs that get/set times won't be
 * called. */
/* The current downside is the times written to your archives will be from 1979.
 */
/*#define MINIZ_NO_TIME */

/* Define MINIZ_NO_DEFLATE_APIS to disable all compression API's. */
/*#define MINIZ_NO_DEFLATE_APIS */

/* Define MINIZ_NO_INFLATE_APIS to disable all decompression API's. */
/*#define MINIZ_NO_INFLATE_APIS */

/* Define MINIZ_NO_ARCHIVE_APIS to disable all ZIP archive API's. */
/*#define MINIZ_NO_ARCHIVE_APIS */

/* Define MINIZ_NO_ARCHIVE_WRITING_APIS to disable all writing related ZIP
 * archive API's. */
/*#define MINIZ_NO_ARCHIVE_WRITING_APIS */

/* Define MINIZ_NO_ZLIB_APIS to remove all ZLIB-style compression/decompression
 * API's. */
/*#define MINIZ_NO_ZLIB_APIS */

/* Define MINIZ_NO_ZLIB_COMPATIBLE_NAME to disable zlib names, to prevent
 * conflicts against stock zlib. */
/*#define MINIZ_NO_ZLIB_COMPATIBLE_NAMES */

/* Define MINIZ_NO_MALLOC to disable all calls to malloc, free, and realloc.
   Note if MINIZ_NO_MALLOC is defined then the user must always provide custom
   user alloc/free/realloc callbacks to the zlib and archive API's, and a few
   stand-alone helper API's which don't provide custom user functions (such as
   tdefl_compress_mem_to_heap() and tinfl_decompress_mem_to_heap()) won't work.
 */
/*#define MINIZ_NO_MALLOC */

#ifdef MINIZ_NO_INFLATE_APIS
#define MINIZ_NO_ARCHIVE_APIS
#endif

#ifdef MINIZ_NO_DEFLATE_APIS
#define MINIZ_NO_ARCHIVE_WRITING_APIS
#endif

#if defined(__TINYC__) && (defined(__linux) || defined(__linux__))
/* TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc
 * on Linux */
#define MINIZ_NO_TIME
#endif

#include <stddef.h>

#if !defined(MINIZ_NO_TIME) && !defined(MINIZ_NO_ARCHIVE_APIS)
#include <time.h>
#endif

#if defined(_M_IX86) || defined(_M_X64) || defined(__i386__) ||                \
    defined(__i386) || defined(__i486__) || defined(__i486) ||                 \
    defined(i386) || defined(__ia64__) || defined(__x86_64__)
/* MINIZ_X86_OR_X64_CPU is only used to help set the below macros. */
#define MINIZ_X86_OR_X64_CPU 1
#else
#define MINIZ_X86_OR_X64_CPU 0
#endif

/* Set MINIZ_LITTLE_ENDIAN only if not set */
#if !defined(MINIZ_LITTLE_ENDIAN)
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__)

#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
/* Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian. */
#define MINIZ_LITTLE_ENDIAN 1
#else
#define MINIZ_LITTLE_ENDIAN 0
#endif

#else

#if MINIZ_X86_OR_X64_CPU
#define MINIZ_LITTLE_ENDIAN 1
#else
#define MINIZ_LITTLE_ENDIAN 0
#endif

#endif
#endif

/* Using unaligned loads and stores causes errors when using UBSan */
#if defined(__has_feature)
#if __has_feature(undefined_behavior_sanitizer)
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#endif
#endif

/* Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES only if not set */
#if !defined(MINIZ_USE_UNALIGNED_LOADS_AND_STORES)
#if MINIZ_X86_OR_X64_CPU
/* Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient
 * integer loads and stores from unaligned addresses. */
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#define MINIZ_UNALIGNED_USE_MEMCPY
#else
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#endif
#endif

#if defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) ||              \
    defined(_LP64) || defined(__LP64__) || defined(__ia64__) ||                \
    defined(__x86_64__)
/* Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are
 * reasonably fast (and don't involve compiler generated calls to helper
 * functions). */
#define MINIZ_HAS_64BIT_REGISTERS 1
#else
#define MINIZ_HAS_64BIT_REGISTERS 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------- zlib-style API Definitions. */

/* For more compatibility with zlib, miniz.c uses unsigned long for some
 * parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits! */
typedef unsigned long mz_ulong;

/* mz_free() internally uses the MZ_FREE() macro (which by default calls
 * free() unless you've modified the MZ_MALLOC macro) to release a block
 * allocated from the heap. */
MINIZ_EXPORT void mz_free(void *p);

#define MZ_ADLER32_INIT (1)
/* mz_adler32() returns the initial adler-32 value to use when called with
 * ptr==NULL. */
MINIZ_EXPORT mz_ulong mz_adler32(mz_ulong adler, const unsigned char *ptr,
                                 size_t buf_len);

#define MZ_CRC32_INIT (0)
/* mz_crc32() returns the initial CRC-32 value to use when called with
 * ptr==NULL. */
MINIZ_EXPORT mz_ulong mz_crc32(mz_ulong crc, const unsigned char *ptr,
                               size_t buf_len);

/* Compression strategies. */
enum {
  MZ_DEFAULT_STRATEGY = 0,
  MZ_FILTERED = 1,
  MZ_HUFFMAN_ONLY = 2,
  MZ_RLE = 3,
  MZ_FIXED = 4
};

/* Method */
#define MZ_DEFLATED 8

/* Heap allocation callbacks.
Note that mz_alloc_func parameter types purposely differ from zlib's:
items/size is size_t, not unsigned long. */
typedef void *(*mz_alloc_func)(void *opaque, size_t items, size_t size);
typedef void (*mz_free_func)(void *opaque, void *address);
typedef void *(*mz_realloc_func)(void *opaque, void *address, size_t items,
                                 size_t size);

/* Compression levels: 0-9 are the standard zlib-style levels, 10 is best
 * possible compression (not zlib compatible, and may be very slow),
 * MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL. */
enum {
  MZ_NO_COMPRESSION = 0,
  MZ_BEST_SPEED = 1,
  MZ_BEST_COMPRESSION = 9,
  MZ_UBER_COMPRESSION = 10,
  MZ_DEFAULT_LEVEL = 6,
  MZ_DEFAULT_COMPRESSION = -1
};

#define MZ_VERSION "11.0.2"
#define MZ_VERNUM 0xB002
#define MZ_VER_MAJOR 11
#define MZ_VER_MINOR 2
#define MZ_VER_REVISION 0
#define MZ_VER_SUBREVISION 0

#ifndef MINIZ_NO_ZLIB_APIS

/* Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH.
 * The other values are for advanced use (refer to the zlib docs). */
enum {
  MZ_NO_FLUSH = 0,
  MZ_PARTIAL_FLUSH = 1,
  MZ_SYNC_FLUSH = 2,
  MZ_FULL_FLUSH = 3,
  MZ_FINISH = 4,
  MZ_BLOCK = 5
};

/* Return status codes. MZ_PARAM_ERROR is non-standard. */
enum {
  MZ_OK = 0,
  MZ_STREAM_END = 1,
  MZ_NEED_DICT = 2,
  MZ_ERRNO = -1,
  MZ_STREAM_ERROR = -2,
  MZ_DATA_ERROR = -3,
  MZ_MEM_ERROR = -4,
  MZ_BUF_ERROR = -5,
  MZ_VERSION_ERROR = -6,
  MZ_PARAM_ERROR = -10000
};

/* Window bits */
#define MZ_DEFAULT_WINDOW_BITS 15

struct mz_internal_state;

/* Compression/decompression stream struct. */
typedef struct mz_stream_s {
  const unsigned char *next_in; /* pointer to next byte to read */
  unsigned int avail_in;        /* number of bytes available at next_in */
  mz_ulong total_in;            /* total number of bytes consumed so far */

  unsigned char *next_out; /* pointer to next byte to write */
  unsigned int avail_out;  /* number of bytes that can be written to next_out */
  mz_ulong total_out;      /* total number of bytes produced so far */

  char *msg; /* error msg (unused) */
  struct mz_internal_state
      *state; /* internal state, allocated by zalloc/zfree */

  mz_alloc_func
      zalloc; /* optional heap allocation function (defaults to malloc) */
  mz_free_func zfree; /* optional heap free function (defaults to free) */
  void *opaque;       /* heap alloc function user pointer */

  int data_type;     /* data_type (unused) */
  mz_ulong adler;    /* adler32 of the source or uncompressed data */
  mz_ulong reserved; /* not used */
} mz_stream;

typedef mz_stream *mz_streamp;

/* Returns the version string of miniz.c. */
MINIZ_EXPORT const char *mz_version(void);

#ifndef MINIZ_NO_DEFLATE_APIS

/* mz_deflateInit() initializes a compressor with default options: */
/* Parameters: */
/*  pStream must point to an initialized mz_stream struct. */
/*  level must be between [MZ_NO_COMPRESSION, MZ_BEST_COMPRESSION]. */
/*  level 1 enables a specially optimized compression function that's been
 * optimized purely for performance, not ratio. */
/*  (This special func. is currently only enabled when
 * MINIZ_USE_UNALIGNED_LOADS_AND_STORES and MINIZ_LITTLE_ENDIAN are defined.)
 */
/* Return values: */
/*  MZ_OK on success. */
/*  MZ_STREAM_ERROR if the stream is bogus. */
/*  MZ_PARAM_ERROR if the input parameters are bogus. */
/*  MZ_MEM_ERROR on out of memory. */
MINIZ_EXPORT int mz_deflateInit(mz_streamp pStream, int level);

/* mz_deflateInit2() is like mz_deflate(), except with more control: */
/* Additional parameters: */
/*   method must be MZ_DEFLATED */
/*   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream
 * with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw
 * deflate/no header or footer) */
/*   mem_level must be between [1, 9] (it's checked but ignored by miniz.c) */
MINIZ_EXPORT int mz_deflateInit2(mz_streamp pStream, int level, int method,
                                 int window_bits, int mem_level, int strategy);

/* Quickly resets a compressor without having to reallocate anything. Same as
 * calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2(). */
MINIZ_EXPORT int mz_deflateReset(mz_streamp pStream);

/* mz_deflate() compresses the input to output, consuming as much of the input
 * and producing as much output as possible. */
/* Parameters: */
/*   pStream is the stream to read from and write to. You must
 * initialize/update the next_in, avail_in, next_out, and avail_out members.
 */
/*   flush may be MZ_NO_FLUSH, MZ_PARTIAL_FLUSH/MZ_SYNC_FLUSH, MZ_FULL_FLUSH,
 * or MZ_FINISH. */
/* Return values: */
/*   MZ_OK on success (when flushing, or if more input is needed but not
 * available, and/or there's more output to be written but the output buffer
 * is full). */
/*   MZ_STREAM_END if all input has been consumed and all output bytes have
 * been written. Don't call mz_deflate() on the stream anymore. */
/*   MZ_STREAM_ERROR if the stream is bogus. */
/*   MZ_PARAM_ERROR if one of the parameters is invalid. */
/*   MZ_BUF_ERROR if no forward progress is possible because the input and/or
 * output buffers are empty. (Fill up the input buffer or free up some output
 * space and try again.) */
MINIZ_EXPORT int mz_deflate(mz_streamp pStream, int flush);

/* mz_deflateEnd() deinitializes a compressor: */
/* Return values: */
/*  MZ_OK on success. */
/*  MZ_STREAM_ERROR if the stream is bogus. */
MINIZ_EXPORT int mz_deflateEnd(mz_streamp pStream);

/* mz_deflateBound() returns a (very) conservative upper bound on the amount
 * of data that could be generated by deflate(), assuming flush is set to only
 * MZ_NO_FLUSH or MZ_FINISH. */
MINIZ_EXPORT mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len);

/* Single-call compression functions mz_compress() and mz_compress2(): */
/* Returns MZ_OK on success, or one of the error codes from mz_deflate() on
 * failure. */
MINIZ_EXPORT int mz_compress(unsigned char *pDest, mz_ulong *pDest_len,
                             const unsigned char *pSource, mz_ulong source_len);
MINIZ_EXPORT int mz_compress2(unsigned char *pDest, mz_ulong *pDest_len,
                              const unsigned char *pSource, mz_ulong source_len,
                              int level);

/* mz_compressBound() returns a (very) conservative upper bound on the amount
 * of data that could be generated by calling mz_compress(). */
MINIZ_EXPORT mz_ulong mz_compressBound(mz_ulong source_len);

#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ifndef MINIZ_NO_INFLATE_APIS

/* Initializes a decompressor. */
MINIZ_EXPORT int mz_inflateInit(mz_streamp pStream);

/* mz_inflateInit2() is like mz_inflateInit() with an additional option that
 * controls the window size and whether or not the stream has been wrapped
 * with a zlib header/footer: */
/* window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or
 * -MZ_DEFAULT_WINDOW_BITS (raw deflate). */
MINIZ_EXPORT int mz_inflateInit2(mz_streamp pStream, int window_bits);

/* Quickly resets a compressor without having to reallocate anything. Same as
 * calling mz_inflateEnd() followed by mz_inflateInit()/mz_inflateInit2(). */
MINIZ_EXPORT int mz_inflateReset(mz_streamp pStream);

/* Decompresses the input stream to the output, consuming only as much of the
 * input as needed, and writing as much to the output as possible. */
/* Parameters: */
/*   pStream is the stream to read from and write to. You must
 * initialize/update the next_in, avail_in, next_out, and avail_out members.
 */
/*   flush may be MZ_NO_FLUSH, MZ_SYNC_FLUSH, or MZ_FINISH. */
/*   On the first call, if flush is MZ_FINISH it's assumed the input and
 * output buffers are both sized large enough to decompress the entire stream
 * in a single call (this is slightly faster). */
/*   MZ_FINISH implies that there are no more source bytes available beside
 * what's already in the input buffer, and that the output buffer is large
 * enough to hold the rest of the decompressed data. */
/* Return values: */
/*   MZ_OK on success. Either more input is needed but not available, and/or
 * there's more output to be written but the output buffer is full. */
/*   MZ_STREAM_END if all needed input has been consumed and all output bytes
 * have been written. For zlib streams, the adler-32 of the decompressed data
 * has also been verified. */
/*   MZ_STREAM_ERROR if the stream is bogus. */
/*   MZ_DATA_ERROR if the deflate stream is invalid. */
/*   MZ_PARAM_ERROR if one of the parameters is invalid. */
/*   MZ_BUF_ERROR if no forward progress is possible because the input buffer
 * is empty but the inflater needs more input to continue, or if the output
 * buffer is not large enough. Call mz_inflate() again */
/*   with more input data, or with more room in the output buffer (except when
 * using single call decompression, described above). */
MINIZ_EXPORT int mz_inflate(mz_streamp pStream, int flush);

/* Deinitializes a decompressor. */
MINIZ_EXPORT int mz_inflateEnd(mz_streamp pStream);

/* Single-call decompression. */
/* Returns MZ_OK on success, or one of the error codes from mz_inflate() on
 * failure. */
MINIZ_EXPORT int mz_uncompress(unsigned char *pDest, mz_ulong *pDest_len,
                               const unsigned char *pSource,
                               mz_ulong source_len);
MINIZ_EXPORT int mz_uncompress2(unsigned char *pDest, mz_ulong *pDest_len,
                                const unsigned char *pSource,
                                mz_ulong *pSource_len);
#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/

/* Returns a string description of the specified error code, or NULL if the
 * error code is invalid. */
MINIZ_EXPORT const char *mz_error(int err);

/* Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used
 * as a drop-in replacement for the subset of zlib that miniz.c supports. */
/* Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you
 * use zlib in the same project. */
#ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES
typedef unsigned char Byte;
typedef unsigned int uInt;
typedef mz_ulong uLong;
typedef Byte Bytef;
typedef uInt uIntf;
typedef char charf;
typedef int intf;
typedef void *voidpf;
typedef uLong uLongf;
typedef void *voidp;
typedef void *const voidpc;
#define Z_NULL 0
#define Z_NO_FLUSH MZ_NO_FLUSH
#define Z_PARTIAL_FLUSH MZ_PARTIAL_FLUSH
#define Z_SYNC_FLUSH MZ_SYNC_FLUSH
#define Z_FULL_FLUSH MZ_FULL_FLUSH
#define Z_FINISH MZ_FINISH
#define Z_BLOCK MZ_BLOCK
#define Z_OK MZ_OK
#define Z_STREAM_END MZ_STREAM_END
#define Z_NEED_DICT MZ_NEED_DICT
#define Z_ERRNO MZ_ERRNO
#define Z_STREAM_ERROR MZ_STREAM_ERROR
#define Z_DATA_ERROR MZ_DATA_ERROR
#define Z_MEM_ERROR MZ_MEM_ERROR
#define Z_BUF_ERROR MZ_BUF_ERROR
#define Z_VERSION_ERROR MZ_VERSION_ERROR
#define Z_PARAM_ERROR MZ_PARAM_ERROR
#define Z_NO_COMPRESSION MZ_NO_COMPRESSION
#define Z_BEST_SPEED MZ_BEST_SPEED
#define Z_BEST_COMPRESSION MZ_BEST_COMPRESSION
#define Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
#define Z_DEFAULT_STRATEGY MZ_DEFAULT_STRATEGY
#define Z_FILTERED MZ_FILTERED
#define Z_HUFFMAN_ONLY MZ_HUFFMAN_ONLY
#define Z_RLE MZ_RLE
#define Z_FIXED MZ_FIXED
#define Z_DEFLATED MZ_DEFLATED
#define Z_DEFAULT_WINDOW_BITS MZ_DEFAULT_WINDOW_BITS
#define alloc_func mz_alloc_func
#define free_func mz_free_func
#define internal_state mz_internal_state
#define z_stream mz_stream

#ifndef MINIZ_NO_DEFLATE_APIS
#define deflateInit mz_deflateInit
#define deflateInit2 mz_deflateInit2
#define deflateReset mz_deflateReset
#define deflate mz_deflate
#define deflateEnd mz_deflateEnd
#define deflateBound mz_deflateBound
#define compress mz_compress
#define compress2 mz_compress2
#define compressBound mz_compressBound
#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ifndef MINIZ_NO_INFLATE_APIS
#define inflateInit mz_inflateInit
#define inflateInit2 mz_inflateInit2
#define inflateReset mz_inflateReset
#define inflate mz_inflate
#define inflateEnd mz_inflateEnd
#define uncompress mz_uncompress
#define uncompress2 mz_uncompress2
#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/

#define crc32 mz_crc32
#define adler32 mz_adler32
#define MAX_WBITS 15
#define MAX_MEM_LEVEL 9
#define zError mz_error
#define ZLIB_VERSION MZ_VERSION
#define ZLIB_VERNUM MZ_VERNUM
#define ZLIB_VER_MAJOR MZ_VER_MAJOR
#define ZLIB_VER_MINOR MZ_VER_MINOR
#define ZLIB_VER_REVISION MZ_VER_REVISION
#define ZLIB_VER_SUBREVISION MZ_VER_SUBREVISION
#define zlibVersion mz_version
#define zlib_version mz_version()
#endif /* #ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES */

#endif /* MINIZ_NO_ZLIB_APIS */

#ifdef __cplusplus
}
#endif

#pragma once
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* ------------------- Types and macros */
typedef unsigned char mz_uint8;
typedef signed short mz_int16;
typedef unsigned short mz_uint16;
typedef unsigned int mz_uint32;
typedef unsigned int mz_uint;
typedef int64_t mz_int64;
typedef uint64_t mz_uint64;
typedef int mz_bool;

#define MZ_FALSE (0)
#define MZ_TRUE (1)

/* Works around MSVC's spammy "warning C4127: conditional expression is
 * constant" message. */
#ifdef _MSC_VER
#define MZ_MACRO_END while (0, 0)
#else
#define MZ_MACRO_END while (0)
#endif

#ifdef MINIZ_NO_STDIO
#define MZ_FILE void *
#else
#include <stdio.h>
#define MZ_FILE FILE
#endif /* #ifdef MINIZ_NO_STDIO */

#ifdef MINIZ_NO_TIME
typedef struct mz_dummy_time_t_tag {
  mz_uint32 m_dummy1;
  mz_uint32 m_dummy2;
} mz_dummy_time_t;
#define MZ_TIME_T mz_dummy_time_t
#else
#define MZ_TIME_T time_t
#endif

#define MZ_ASSERT(x) assert(x)

#ifdef MINIZ_NO_MALLOC
#define MZ_MALLOC(x) NULL
#define MZ_FREE(x) (void)x, ((void)0)
#define MZ_REALLOC(p, x) NULL
#else
#define MZ_MALLOC(x) malloc(x)
#define MZ_FREE(x) free(x)
#define MZ_REALLOC(p, x) realloc(p, x)
#endif

#define MZ_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MZ_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MZ_CLEAR_OBJ(obj) memset(&(obj), 0, sizeof(obj))
#define MZ_CLEAR_ARR(obj) memset((obj), 0, sizeof(obj))
#define MZ_CLEAR_PTR(obj) memset((obj), 0, sizeof(*obj))

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
#define MZ_READ_LE16(p) *((const mz_uint16 *)(p))
#define MZ_READ_LE32(p) *((const mz_uint32 *)(p))
#else
#define MZ_READ_LE16(p)                                                        \
  ((mz_uint32)(((const mz_uint8 *)(p))[0]) |                                   \
   ((mz_uint32)(((const mz_uint8 *)(p))[1]) << 8U))
#define MZ_READ_LE32(p)                                                        \
  ((mz_uint32)(((const mz_uint8 *)(p))[0]) |                                   \
   ((mz_uint32)(((const mz_uint8 *)(p))[1]) << 8U) |                           \
   ((mz_uint32)(((const mz_uint8 *)(p))[2]) << 16U) |                          \
   ((mz_uint32)(((const mz_uint8 *)(p))[3]) << 24U))
#endif

#define MZ_READ_LE64(p)                                                        \
  (((mz_uint64)MZ_READ_LE32(p)) |                                              \
   (((mz_uint64)MZ_READ_LE32((const mz_uint8 *)(p) + sizeof(mz_uint32)))       \
    << 32U))

#ifdef _MSC_VER
#define MZ_FORCEINLINE __forceinline
#elif defined(__GNUC__)
#define MZ_FORCEINLINE __inline__ __attribute__((__always_inline__))
#else
#define MZ_FORCEINLINE inline
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern MINIZ_EXPORT void *miniz_def_alloc_func(void *opaque, size_t items,
                                               size_t size);
extern MINIZ_EXPORT void miniz_def_free_func(void *opaque, void *address);
extern MINIZ_EXPORT void *miniz_def_realloc_func(void *opaque, void *address,
                                                 size_t items, size_t size);

#define MZ_UINT16_MAX (0xFFFFU)
#define MZ_UINT32_MAX (0xFFFFFFFFU)

#ifdef __cplusplus
}
#endif
#pragma once

#ifndef MINIZ_NO_DEFLATE_APIS

#ifdef __cplusplus
extern "C" {
#endif
/* ------------------- Low-level Compression API Definitions */

/* Set TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly
 * slower, and raw/dynamic blocks will be output more frequently). */
#ifndef TDEFL_LESS_MEMORY
#define TDEFL_LESS_MEMORY 0
#endif

/* tdefl_init() compression flags logically OR'd together (low 12 bits contain
 * the max. number of probes per dictionary search): */
/* TDEFL_DEFAULT_MAX_PROBES: The compressor defaults to 128 dictionary probes
 * per dictionary search. 0=Huffman only, 1=Huffman+LZ (fastest/crap
 * compression), 4095=Huffman+LZ (slowest/best compression). */
enum {
  TDEFL_HUFFMAN_ONLY = 0,
  TDEFL_DEFAULT_MAX_PROBES = 128,
  TDEFL_MAX_PROBES_MASK = 0xFFF
};

/* TDEFL_WRITE_ZLIB_HEADER: If set, the compressor outputs a zlib header
 * before the deflate data, and the Adler-32 of the source data at the end.
 * Otherwise, you'll get raw deflate data. */
/* TDEFL_COMPUTE_ADLER32: Always compute the adler-32 of the input data (even
 * when not writing zlib headers). */
/* TDEFL_GREEDY_PARSING_FLAG: Set to use faster greedy parsing, instead of
 * more efficient lazy parsing. */
/* TDEFL_NONDETERMINISTIC_PARSING_FLAG: Enable to decrease the compressor's
 * initialization time to the minimum, but the output may vary from run to run
 * given the same input (depending on the contents of memory). */
/* TDEFL_RLE_MATCHES: Only look for RLE matches (matches with a distance of 1)
 */
/* TDEFL_FILTER_MATCHES: Discards matches <= 5 chars if enabled. */
/* TDEFL_FORCE_ALL_STATIC_BLOCKS: Disable usage of optimized Huffman tables.
 */
/* TDEFL_FORCE_ALL_RAW_BLOCKS: Only use raw (uncompressed) deflate blocks. */
/* The low 12 bits are reserved to control the max # of hash probes per
 * dictionary lookup (see TDEFL_MAX_PROBES_MASK). */
enum {
  TDEFL_WRITE_ZLIB_HEADER = 0x01000,
  TDEFL_COMPUTE_ADLER32 = 0x02000,
  TDEFL_GREEDY_PARSING_FLAG = 0x04000,
  TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
  TDEFL_RLE_MATCHES = 0x10000,
  TDEFL_FILTER_MATCHES = 0x20000,
  TDEFL_FORCE_ALL_STATIC_BLOCKS = 0x40000,
  TDEFL_FORCE_ALL_RAW_BLOCKS = 0x80000
};

/* High level compression functions: */
/* tdefl_compress_mem_to_heap() compresses a block in memory to a heap block
 * allocated via malloc(). */
/* On entry: */
/*  pSrc_buf, src_buf_len: Pointer and size of source block to compress. */
/*  flags: The max match finder probes (default is 128) logically OR'd against
 * the above flags. Higher probes are slower but improve compression. */
/* On return: */
/*  Function returns a pointer to the compressed data, or NULL on failure. */
/*  *pOut_len will be set to the compressed data's size, which could be larger
 * than src_buf_len on uncompressible data. */
/*  The caller must free() the returned block when it's no longer needed. */
MINIZ_EXPORT void *tdefl_compress_mem_to_heap(const void *pSrc_buf,
                                              size_t src_buf_len,
                                              size_t *pOut_len, int flags);

/* tdefl_compress_mem_to_mem() compresses a block in memory to another block
 * in memory. */
/* Returns 0 on failure. */
MINIZ_EXPORT size_t tdefl_compress_mem_to_mem(void *pOut_buf,
                                              size_t out_buf_len,
                                              const void *pSrc_buf,
                                              size_t src_buf_len, int flags);

/* Compresses an image to a compressed PNG file in memory. */
/* On entry: */
/*  pImage, w, h, and num_chans describe the image to compress. num_chans may
 * be 1, 2, 3, or 4. */
/*  The image pitch in bytes per scanline will be w*num_chans. The leftmost
 * pixel on the top scanline is stored first in memory. */
/*  level may range from [0,10], use MZ_NO_COMPRESSION, MZ_BEST_SPEED,
 * MZ_BEST_COMPRESSION, etc. or a decent default is MZ_DEFAULT_LEVEL */
/*  If flip is true, the image will be flipped on the Y axis (useful for
 * OpenGL apps). */
/* On return: */
/*  Function returns a pointer to the compressed data, or NULL on failure. */
/*  *pLen_out will be set to the size of the PNG image file. */
/*  The caller must mz_free() the returned heap block (which will typically be
 * larger than *pLen_out) when it's no longer needed. */
MINIZ_EXPORT void *
tdefl_write_image_to_png_file_in_memory_ex(const void *pImage, int w, int h,
                                           int num_chans, size_t *pLen_out,
                                           mz_uint level, mz_bool flip);
MINIZ_EXPORT void *tdefl_write_image_to_png_file_in_memory(const void *pImage,
                                                           int w, int h,
                                                           int num_chans,
                                                           size_t *pLen_out);

/* Output stream interface. The compressor uses this interface to write
 * compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time. */
typedef mz_bool (*tdefl_put_buf_func_ptr)(const void *pBuf, int len,
                                          void *pUser);

/* tdefl_compress_mem_to_output() compresses a block to an output stream. The
 * above helpers use this function internally. */
MINIZ_EXPORT mz_bool tdefl_compress_mem_to_output(
    const void *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func,
    void *pPut_buf_user, int flags);

enum {
  TDEFL_MAX_HUFF_TABLES = 3,
  TDEFL_MAX_HUFF_SYMBOLS_0 = 288,
  TDEFL_MAX_HUFF_SYMBOLS_1 = 32,
  TDEFL_MAX_HUFF_SYMBOLS_2 = 19,
  TDEFL_LZ_DICT_SIZE = 32768,
  TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1,
  TDEFL_MIN_MATCH_LEN = 3,
  TDEFL_MAX_MATCH_LEN = 258
};

/* TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed
 * output block (using static/fixed Huffman codes). */
#if TDEFL_LESS_MEMORY
enum {
  TDEFL_LZ_CODE_BUF_SIZE = 24 * 1024,
  TDEFL_OUT_BUF_SIZE = (TDEFL_LZ_CODE_BUF_SIZE * 13) / 10,
  TDEFL_MAX_HUFF_SYMBOLS = 288,
  TDEFL_LZ_HASH_BITS = 12,
  TDEFL_LEVEL1_HASH_SIZE_MASK = 4095,
  TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3,
  TDEFL_LZ_HASH_SIZE = 1 << TDEFL_LZ_HASH_BITS
};
#else
enum {
  TDEFL_LZ_CODE_BUF_SIZE = 64 * 1024,
  TDEFL_OUT_BUF_SIZE = (TDEFL_LZ_CODE_BUF_SIZE * 13) / 10,
  TDEFL_MAX_HUFF_SYMBOLS = 288,
  TDEFL_LZ_HASH_BITS = 15,
  TDEFL_LEVEL1_HASH_SIZE_MASK = 4095,
  TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3,
  TDEFL_LZ_HASH_SIZE = 1 << TDEFL_LZ_HASH_BITS
};
#endif

/* The low-level tdefl functions below may be used directly if the above
 * helper functions aren't flexible enough. The low-level functions don't make
 * any heap allocations, unlike the above helper functions. */
typedef enum {
  TDEFL_STATUS_BAD_PARAM = -2,
  TDEFL_STATUS_PUT_BUF_FAILED = -1,
  TDEFL_STATUS_OKAY = 0,
  TDEFL_STATUS_DONE = 1
} tdefl_status;

/* Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums */
typedef enum {
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_FULL_FLUSH = 3,
  TDEFL_FINISH = 4
} tdefl_flush;

/* tdefl's compression state structure. */
typedef struct {
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  void *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  int m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_size, m_dict_size;
  mz_uint8 *m_pLZ_code_buf, *m_pLZ_flags, *m_pOutput_buf, *m_pOutput_buf_end;
  mz_uint m_num_flags_left, m_total_lz_bytes, m_lz_code_buf_dict_pos, m_bits_in,
      m_bit_buffer;
  mz_uint m_saved_match_dist, m_saved_match_len, m_saved_lit,
      m_output_flush_ofs, m_output_flush_remaining, m_finished, m_block_index,
      m_wants_to_finish;
  tdefl_status m_prev_return_status;
  const void *m_pIn_buf;
  void *m_pOut_buf;
  size_t *m_pIn_buf_size, *m_pOut_buf_size;
  tdefl_flush m_flush;
  const mz_uint8 *m_pSrc;
  size_t m_src_buf_left, m_out_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_SIZE + TDEFL_MAX_MATCH_LEN - 1];
  mz_uint16 m_huff_count[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_huff_code_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE];
  mz_uint16 m_next[TDEFL_LZ_DICT_SIZE];
  mz_uint16 m_hash[TDEFL_LZ_HASH_SIZE];
  mz_uint8 m_output_buf[TDEFL_OUT_BUF_SIZE];
} tdefl_compressor;

/* Initializes the compressor. */
/* There is no corresponding deinit() function because the tdefl API's do not
 * dynamically allocate memory. */
/* pBut_buf_func: If NULL, output data will be supplied to the specified
 * callback. In this case, the user should call the tdefl_compress_buffer()
 * API for compression. */
/* If pBut_buf_func is NULL the user should always call the tdefl_compress()
 * API. */
/* flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER,
 * etc.) */
MINIZ_EXPORT tdefl_status tdefl_init(tdefl_compressor *d,
                                     tdefl_put_buf_func_ptr pPut_buf_func,
                                     void *pPut_buf_user, int flags);

/* Compresses a block of data, consuming as much of the specified input buffer
 * as possible, and writing as much compressed data to the specified output
 * buffer as possible. */
MINIZ_EXPORT tdefl_status tdefl_compress(tdefl_compressor *d,
                                         const void *pIn_buf,
                                         size_t *pIn_buf_size, void *pOut_buf,
                                         size_t *pOut_buf_size,
                                         tdefl_flush flush);

/* tdefl_compress_buffer() is only usable when the tdefl_init() is called with
 * a non-NULL tdefl_put_buf_func_ptr. */
/* tdefl_compress_buffer() always consumes the entire input buffer. */
MINIZ_EXPORT tdefl_status tdefl_compress_buffer(tdefl_compressor *d,
                                                const void *pIn_buf,
                                                size_t in_buf_size,
                                                tdefl_flush flush);

MINIZ_EXPORT tdefl_status tdefl_get_prev_return_status(tdefl_compressor *d);
MINIZ_EXPORT mz_uint32 tdefl_get_adler32(tdefl_compressor *d);

/* Create tdefl_compress() flags given zlib-style compression parameters. */
/* level may range from [0,10] (where 10 is absolute max compression, but may
 * be much slower on some files) */
/* window_bits may be -15 (raw deflate) or 15 (zlib) */
/* strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY,
 * MZ_RLE, or MZ_FIXED */
MINIZ_EXPORT mz_uint tdefl_create_comp_flags_from_zip_params(int level,
                                                             int window_bits,
                                                             int strategy);

#ifndef MINIZ_NO_MALLOC
/* Allocate the tdefl_compressor structure in C so that */
/* non-C language bindings to tdefl_ API don't need to worry about */
/* structure size and allocation mechanism. */
MINIZ_EXPORT tdefl_compressor *tdefl_compressor_alloc(void);
MINIZ_EXPORT void tdefl_compressor_free(tdefl_compressor *pComp);
#endif

#ifdef __cplusplus
}
#endif

#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/
#pragma once

/* ------------------- Low-level Decompression API Definitions */

#ifndef MINIZ_NO_INFLATE_APIS

#ifdef __cplusplus
extern "C" {
#endif
/* Decompression flags used by tinfl_decompress(). */
/* TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and
 * ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the
 * input is a raw deflate stream. */
/* TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available
 * beyond the end of the supplied input buffer. If clear, the input buffer
 * contains all remaining input. */
/* TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is
 * large enough to hold the entire decompressed stream. If clear, the output
 * buffer is at least the size of the dictionary (typically 32KB). */
/* TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the
 * decompressed bytes. */
enum {
  TINFL_FLAG_PARSE_ZLIB_HEADER = 1,
  TINFL_FLAG_HAS_MORE_INPUT = 2,
  TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF = 4,
  TINFL_FLAG_COMPUTE_ADLER32 = 8
};

/* High level decompression functions: */
/* tinfl_decompress_mem_to_heap() decompresses a block in memory to a heap
 * block allocated via malloc(). */
/* On entry: */
/*  pSrc_buf, src_buf_len: Pointer and size of the Deflate or zlib source data
 * to decompress. */
/* On return: */
/*  Function returns a pointer to the decompressed data, or NULL on failure.
 */
/*  *pOut_len will be set to the decompressed data's size, which could be
 * larger than src_buf_len on uncompressible data. */
/*  The caller must call mz_free() on the returned block when it's no longer
 * needed. */
MINIZ_EXPORT void *tinfl_decompress_mem_to_heap(const void *pSrc_buf,
                                                size_t src_buf_len,
                                                size_t *pOut_len, int flags);

/* tinfl_decompress_mem_to_mem() decompresses a block in memory to another block
 * in memory. */
/* Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes
 * written on success. */
#define TINFL_DECOMPRESS_MEM_TO_MEM_FAILED ((size_t)(-1))
MINIZ_EXPORT size_t tinfl_decompress_mem_to_mem(void *pOut_buf,
                                                size_t out_buf_len,
                                                const void *pSrc_buf,
                                                size_t src_buf_len, int flags);

/* tinfl_decompress_mem_to_callback() decompresses a block in memory to an
 * internal 32KB buffer, and a user provided callback function will be called
 * to flush the buffer. */
/* Returns 1 on success or 0 on failure. */
typedef int (*tinfl_put_buf_func_ptr)(const void *pBuf, int len, void *pUser);
MINIZ_EXPORT int
tinfl_decompress_mem_to_callback(const void *pIn_buf, size_t *pIn_buf_size,
                                 tinfl_put_buf_func_ptr pPut_buf_func,
                                 void *pPut_buf_user, int flags);

struct tinfl_decompressor_tag;
typedef struct tinfl_decompressor_tag tinfl_decompressor;

#ifndef MINIZ_NO_MALLOC
/* Allocate the tinfl_decompressor structure in C so that */
/* non-C language bindings to tinfl_ API don't need to worry about */
/* structure size and allocation mechanism. */
MINIZ_EXPORT tinfl_decompressor *tinfl_decompressor_alloc(void);
MINIZ_EXPORT void tinfl_decompressor_free(tinfl_decompressor *pDecomp);
#endif

/* Max size of LZ dictionary. */
#define TINFL_LZ_DICT_SIZE 32768

/* Return status. */
typedef enum {
  /* This flags indicates the inflator needs 1 or more input bytes to make
     forward progress, but the caller is indicating that no more are
     available. The compressed data */
  /* is probably corrupted. If you call the inflator again with more bytes
     it'll try to continue processing the input but this is a BAD sign (either
     the data is corrupted or you called it incorrectly). */
  /* If you call it again with no input you'll just get
     TINFL_STATUS_FAILED_CANNOT_MAKE_PROGRESS again. */
  TINFL_STATUS_FAILED_CANNOT_MAKE_PROGRESS = -4,

  /* This flag indicates that one or more of the input parameters was
     obviously bogus. (You can try calling it again, but if you get this error
     the calling code is wrong.) */
  TINFL_STATUS_BAD_PARAM = -3,

  /* This flags indicate the inflator is finished but the adler32 check of the
     uncompressed data didn't match. If you call it again it'll return
     TINFL_STATUS_DONE. */
  TINFL_STATUS_ADLER32_MISMATCH = -2,

  /* This flags indicate the inflator has somehow failed (bad code, corrupted
     input, etc.). If you call it again without resetting via tinfl_init() it
     it'll just keep on returning the same status failure code. */
  TINFL_STATUS_FAILED = -1,

  /* Any status code less than TINFL_STATUS_DONE must indicate a failure. */

  /* This flag indicates the inflator has returned every byte of uncompressed
     data that it can, has consumed every byte that it needed, has
     successfully reached the end of the deflate stream, and */
  /* if zlib headers and adler32 checking enabled that it has successfully
     checked the uncompressed data's adler32. If you call it again you'll just
     get TINFL_STATUS_DONE over and over again. */
  TINFL_STATUS_DONE = 0,

  /* This flag indicates the inflator MUST have more input data (even 1 byte)
     before it can make any more forward progress, or you need to clear the
     TINFL_FLAG_HAS_MORE_INPUT */
  /* flag on the next call if you don't have any more source data. If the
     source data was somehow corrupted it's also possible (but unlikely) for
     the inflator to keep on demanding input to */
  /* proceed, so be sure to properly set the TINFL_FLAG_HAS_MORE_INPUT flag.
   */
  TINFL_STATUS_NEEDS_MORE_INPUT = 1,

  /* This flag indicates the inflator definitely has 1 or more bytes of
     uncompressed data available, but it cannot write this data into the
     output buffer. */
  /* Note if the source compressed data was corrupted it's possible for the
     inflator to return a lot of uncompressed data to the caller. I've been
     assuming you know how much uncompressed data to expect */
  /* (either exact or worst case) and will stop calling the inflator and fail
     after receiving too much. In pure streaming scenarios where you have no
     idea how many bytes to expect this may not be possible */
  /* so I may need to add some code to address this. */
  TINFL_STATUS_HAS_MORE_OUTPUT = 2
} tinfl_status;

/* Initializes the decompressor to its initial state. */
#define tinfl_init(r)                                                          \
  do {                                                                         \
    (r)->m_state = 0;                                                          \
  }                                                                            \
  MZ_MACRO_END
#define tinfl_get_adler32(r) (r)->m_check_adler32

/* Main low-level decompressor coroutine function. This is the only function
 * actually needed for decompression. All the other functions are just
 * high-level helpers for improved usability. */
/* This is a universal API, i.e. it can be used as a building block to build
 * any desired higher level decompression API. In the limit case, it can be
 * called once per every byte input or output. */
MINIZ_EXPORT tinfl_status tinfl_decompress(
    tinfl_decompressor *r, const mz_uint8 *pIn_buf_next, size_t *pIn_buf_size,
    mz_uint8 *pOut_buf_start, mz_uint8 *pOut_buf_next, size_t *pOut_buf_size,
    const mz_uint32 decomp_flags);

/* Internal/private bits follow. */
enum {
  TINFL_MAX_HUFF_TABLES = 3,
  TINFL_MAX_HUFF_SYMBOLS_0 = 288,
  TINFL_MAX_HUFF_SYMBOLS_1 = 32,
  TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_BITS = 10,
  TINFL_FAST_LOOKUP_SIZE = 1 << TINFL_FAST_LOOKUP_BITS
};

#if MINIZ_HAS_64BIT_REGISTERS
#define TINFL_USE_64BIT_BITBUF 1
#else
#define TINFL_USE_64BIT_BITBUF 0
#endif

#if TINFL_USE_64BIT_BITBUF
typedef mz_uint64 tinfl_bit_buf_t;
#define TINFL_BITBUF_SIZE (64)
#else
typedef mz_uint32 tinfl_bit_buf_t;
#define TINFL_BITBUF_SIZE (32)
#endif

struct tinfl_decompressor_tag {
  mz_uint32 m_state, m_num_bits, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type,
      m_check_adler32, m_dist, m_counter, m_num_extra,
      m_table_sizes[TINFL_MAX_HUFF_TABLES];
  tinfl_bit_buf_t m_bit_buf;
  size_t m_dist_from_out_buf_start;
  mz_int16 m_look_up[TINFL_MAX_HUFF_TABLES][TINFL_FAST_LOOKUP_SIZE];
  mz_int16 m_tree_0[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
  mz_int16 m_tree_1[TINFL_MAX_HUFF_SYMBOLS_1 * 2];
  mz_int16 m_tree_2[TINFL_MAX_HUFF_SYMBOLS_2 * 2];
  mz_uint8 m_code_size_0[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_uint8 m_code_size_1[TINFL_MAX_HUFF_SYMBOLS_1];
  mz_uint8 m_code_size_2[TINFL_MAX_HUFF_SYMBOLS_2];
  mz_uint8 m_raw_header[4],
      m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
};

#ifdef __cplusplus
}
#endif

#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/

#pragma once

/* ------------------- ZIP archive reading/writing */

#ifndef MINIZ_NO_ARCHIVE_APIS

#ifdef __cplusplus
extern "C" {
#endif

enum {
  /* Note: These enums can be reduced as needed to save memory or stack space
     - they are pretty conservative. */
  MZ_ZIP_MAX_IO_BUF_SIZE = 64 * 1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE = 512,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE = 512
};

typedef struct {
  /* Central directory file index. */
  mz_uint32 m_file_index;

  /* Byte offset of this entry in the archive's central directory. Note we
   * currently only support up to UINT_MAX or less bytes in the central dir.
   */
  mz_uint64 m_central_dir_ofs;

  /* These fields are copied directly from the zip's central dir. */
  mz_uint16 m_version_made_by;
  mz_uint16 m_version_needed;
  mz_uint16 m_bit_flag;
  mz_uint16 m_method;

  /* CRC-32 of uncompressed data. */
  mz_uint32 m_crc32;

  /* File's compressed size. */
  mz_uint64 m_comp_size;

  /* File's uncompressed size. Note, I've seen some old archives where
   * directory entries had 512 bytes for their uncompressed sizes, but when
   * you try to unpack them you actually get 0 bytes. */
  mz_uint64 m_uncomp_size;

  /* Zip internal and external file attributes. */
  mz_uint16 m_internal_attr;
  mz_uint32 m_external_attr;

  /* Entry's local header file offset in bytes. */
  mz_uint64 m_local_header_ofs;

  /* Size of comment in bytes. */
  mz_uint32 m_comment_size;

  /* MZ_TRUE if the entry appears to be a directory. */
  mz_bool m_is_directory;

  /* MZ_TRUE if the entry uses encryption/strong encryption (which miniz_zip
   * doesn't support) */
  mz_bool m_is_encrypted;

  /* MZ_TRUE if the file is not encrypted, a patch file, and if it uses a
   * compression method we support. */
  mz_bool m_is_supported;

  /* Filename. If string ends in '/' it's a subdirectory entry. */
  /* Guaranteed to be zero terminated, may be truncated to fit. */
  char m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE];

  /* Comment field. */
  /* Guaranteed to be zero terminated, may be truncated to fit. */
  char m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE];

#ifdef MINIZ_NO_TIME
  MZ_TIME_T m_padding;
#else
  MZ_TIME_T m_time;
#endif
} mz_zip_archive_file_stat;

typedef size_t (*mz_file_read_func)(void *pOpaque, mz_uint64 file_ofs,
                                    void *pBuf, size_t n);
typedef size_t (*mz_file_write_func)(void *pOpaque, mz_uint64 file_ofs,
                                     const void *pBuf, size_t n);
typedef mz_bool (*mz_file_needs_keepalive)(void *pOpaque);

struct mz_zip_internal_state_tag;
typedef struct mz_zip_internal_state_tag mz_zip_internal_state;

typedef enum {
  MZ_ZIP_MODE_INVALID = 0,
  MZ_ZIP_MODE_READING = 1,
  MZ_ZIP_MODE_WRITING = 2,
  MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_mode;

typedef enum {
  MZ_ZIP_FLAG_CASE_SENSITIVE = 0x0100,
  MZ_ZIP_FLAG_IGNORE_PATH = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_DATA = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY = 0x0800,
  MZ_ZIP_FLAG_VALIDATE_LOCATE_FILE_FLAG =
      0x1000, /* if enabled, mz_zip_reader_locate_file() will be called on each
                 file as its validated to ensure the func finds the file in the
                 central dir (intended for testing) */
  MZ_ZIP_FLAG_VALIDATE_HEADERS_ONLY =
      0x2000, /* validate the local headers, but don't decompress the entire
                 file and check the crc32 */
  MZ_ZIP_FLAG_WRITE_ZIP64 =
      0x4000, /* always use the zip64 file format, instead of the original zip
                 file format with automatic switch to zip64. Use as flags
                 parameter with mz_zip_writer_init*_v2 */
  MZ_ZIP_FLAG_WRITE_ALLOW_READING = 0x8000,
  MZ_ZIP_FLAG_ASCII_FILENAME = 0x10000,
  /*After adding a compressed file, seek back
  to local file header and set the correct sizes*/
  MZ_ZIP_FLAG_WRITE_HEADER_SET_SIZE = 0x20000
} mz_zip_flags;

typedef enum {
  MZ_ZIP_TYPE_INVALID = 0,
  MZ_ZIP_TYPE_USER,
  MZ_ZIP_TYPE_MEMORY,
  MZ_ZIP_TYPE_HEAP,
  MZ_ZIP_TYPE_FILE,
  MZ_ZIP_TYPE_CFILE,
  MZ_ZIP_TOTAL_TYPES
} mz_zip_type;

/* miniz error codes. Be sure to update mz_zip_get_error_string() if you add
 * or modify this enum. */
typedef enum {
  MZ_ZIP_NO_ERROR = 0,
  MZ_ZIP_UNDEFINED_ERROR,
  MZ_ZIP_TOO_MANY_FILES,
  MZ_ZIP_FILE_TOO_LARGE,
  MZ_ZIP_UNSUPPORTED_METHOD,
  MZ_ZIP_UNSUPPORTED_ENCRYPTION,
  MZ_ZIP_UNSUPPORTED_FEATURE,
  MZ_ZIP_FAILED_FINDING_CENTRAL_DIR,
  MZ_ZIP_NOT_AN_ARCHIVE,
  MZ_ZIP_INVALID_HEADER_OR_CORRUPTED,
  MZ_ZIP_UNSUPPORTED_MULTIDISK,
  MZ_ZIP_DECOMPRESSION_FAILED,
  MZ_ZIP_COMPRESSION_FAILED,
  MZ_ZIP_UNEXPECTED_DECOMPRESSED_SIZE,
  MZ_ZIP_CRC_CHECK_FAILED,
  MZ_ZIP_UNSUPPORTED_CDIR_SIZE,
  MZ_ZIP_ALLOC_FAILED,
  MZ_ZIP_FILE_OPEN_FAILED,
  MZ_ZIP_FILE_CREATE_FAILED,
  MZ_ZIP_FILE_WRITE_FAILED,
  MZ_ZIP_FILE_READ_FAILED,
  MZ_ZIP_FILE_CLOSE_FAILED,
  MZ_ZIP_FILE_SEEK_FAILED,
  MZ_ZIP_FILE_STAT_FAILED,
  MZ_ZIP_INVALID_PARAMETER,
  MZ_ZIP_INVALID_FILENAME,
  MZ_ZIP_BUF_TOO_SMALL,
  MZ_ZIP_INTERNAL_ERROR,
  MZ_ZIP_FILE_NOT_FOUND,
  MZ_ZIP_ARCHIVE_TOO_LARGE,
  MZ_ZIP_VALIDATION_FAILED,
  MZ_ZIP_WRITE_CALLBACK_FAILED,
  MZ_ZIP_TOTAL_ERRORS
} mz_zip_error;

typedef struct {
  mz_uint64 m_archive_size;
  mz_uint64 m_central_directory_file_ofs;

  /* We only support up to UINT32_MAX files in zip64 mode. */
  mz_uint32 m_total_files;
  mz_zip_mode m_zip_mode;
  mz_zip_type m_zip_type;
  mz_zip_error m_last_error;

  mz_uint64 m_file_offset_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  void *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  mz_file_needs_keepalive m_pNeeds_keepalive;
  void *m_pIO_opaque;

  mz_zip_internal_state *m_pState;

} mz_zip_archive;

typedef struct {
  mz_zip_archive *pZip;
  mz_uint flags;

  int status;

  mz_uint64 read_buf_size, read_buf_ofs, read_buf_avail, comp_remaining,
      out_buf_ofs, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  void *pRead_buf;
  void *pWrite_buf;

  size_t out_blk_remain;

  tinfl_decompressor inflator;

#ifdef MINIZ_DISABLE_ZIP_READER_CRC32_CHECKS
  mz_uint padding;
#else
  mz_uint file_crc32;
#endif

} mz_zip_reader_extract_iter_state;

/* -------- ZIP reading */

/* Inits a ZIP archive reader. */
/* These functions read and validate the archive's central directory. */
MINIZ_EXPORT mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 size,
                                        mz_uint flags);

MINIZ_EXPORT mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip,
                                            const void *pMem, size_t size,
                                            mz_uint flags);

#ifndef MINIZ_NO_STDIO
/* Read a archive from a disk file. */
/* file_start_ofs is the file offset where the archive actually begins, or 0.
 */
/* actual_archive_size is the true total size of the archive, which may be
 * smaller than the file's actual size on disk. If zero the entire file is
 * treated as the archive. */
MINIZ_EXPORT mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip,
                                             const char *pFilename,
                                             mz_uint32 flags);
MINIZ_EXPORT mz_bool mz_zip_reader_init_file_v2(mz_zip_archive *pZip,
                                                const char *pFilename,
                                                mz_uint flags,
                                                mz_uint64 file_start_ofs,
                                                mz_uint64 archive_size);

/* Read an archive from an already opened FILE, beginning at the current file
 * position. */
/* The archive is assumed to be archive_size bytes long. If archive_size is 0,
 * then the entire rest of the file is assumed to contain the archive. */
/* The FILE will NOT be closed when mz_zip_reader_end() is called. */
MINIZ_EXPORT mz_bool mz_zip_reader_init_cfile(mz_zip_archive *pZip,
                                              MZ_FILE *pFile,
                                              mz_uint64 archive_size,
                                              mz_uint flags);
#endif

/* Ends archive reading, freeing all allocations, and closing the input
 * archive file if mz_zip_reader_init_file() was used. */
MINIZ_EXPORT mz_bool mz_zip_reader_end(mz_zip_archive *pZip);

/* -------- ZIP reading or writing */

/* Clears a mz_zip_archive struct to all zeros. */
/* Important: This must be done before passing the struct to any mz_zip
 * functions. */
MINIZ_EXPORT void mz_zip_zero_struct(mz_zip_archive *pZip);

MINIZ_EXPORT mz_zip_mode mz_zip_get_mode(mz_zip_archive *pZip);
MINIZ_EXPORT mz_zip_type mz_zip_get_type(mz_zip_archive *pZip);

/* Returns the total number of files in the archive. */
MINIZ_EXPORT mz_uint mz_zip_reader_get_num_files(mz_zip_archive *pZip);

MINIZ_EXPORT mz_uint64 mz_zip_get_archive_size(mz_zip_archive *pZip);
MINIZ_EXPORT mz_uint64
mz_zip_get_archive_file_start_offset(mz_zip_archive *pZip);
MINIZ_EXPORT MZ_FILE *mz_zip_get_cfile(mz_zip_archive *pZip);

/* Reads n bytes of raw archive data, starting at file offset file_ofs, to
 * pBuf.
 */
MINIZ_EXPORT size_t mz_zip_read_archive_data(mz_zip_archive *pZip,
                                             mz_uint64 file_ofs, void *pBuf,
                                             size_t n);

/* All mz_zip funcs set the m_last_error field in the mz_zip_archive struct.
 * These functions retrieve/manipulate this field. */
/* Note that the m_last_error functionality is not thread safe. */
MINIZ_EXPORT mz_zip_error mz_zip_set_last_error(mz_zip_archive *pZip,
                                                mz_zip_error err_num);
MINIZ_EXPORT mz_zip_error mz_zip_peek_last_error(mz_zip_archive *pZip);
MINIZ_EXPORT mz_zip_error mz_zip_clear_last_error(mz_zip_archive *pZip);
MINIZ_EXPORT mz_zip_error mz_zip_get_last_error(mz_zip_archive *pZip);
MINIZ_EXPORT const char *mz_zip_get_error_string(mz_zip_error mz_err);

/* MZ_TRUE if the archive file entry is a directory entry. */
MINIZ_EXPORT mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip,
                                                       mz_uint file_index);

/* MZ_TRUE if the file is encrypted/strong encrypted. */
MINIZ_EXPORT mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip,
                                                     mz_uint file_index);

/* MZ_TRUE if the compression method is supported, and the file is not
 * encrypted, and the file is not a compressed patch file. */
MINIZ_EXPORT mz_bool mz_zip_reader_is_file_supported(mz_zip_archive *pZip,
                                                     mz_uint file_index);

/* Retrieves the filename of an archive file entry. */
/* Returns the number of bytes written to pFilename, or if filename_buf_size
 * is 0 this function returns the number of bytes needed to fully store the
 * filename. */
MINIZ_EXPORT mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip,
                                                mz_uint file_index,
                                                char *pFilename,
                                                mz_uint filename_buf_size);

/* Attempts to locates a file in the archive's central directory. */
/* Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH */
/* Returns -1 if the file cannot be found. */
MINIZ_EXPORT int mz_zip_reader_locate_file(mz_zip_archive *pZip,
                                           const char *pName,
                                           const char *pComment, mz_uint flags);
MINIZ_EXPORT mz_bool mz_zip_reader_locate_file_v2(mz_zip_archive *pZip,
                                                  const char *pName,
                                                  const char *pComment,
                                                  mz_uint flags,
                                                  mz_uint32 *file_index);

/* Returns detailed information about an archive file entry. */
MINIZ_EXPORT mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip,
                                             mz_uint file_index,
                                             mz_zip_archive_file_stat *pStat);

/* MZ_TRUE if the file is in zip64 format. */
/* A file is considered zip64 if it contained a zip64 end of central directory
 * marker, or if it contained any zip64 extended file information fields in
 * the central directory. */
MINIZ_EXPORT mz_bool mz_zip_is_zip64(mz_zip_archive *pZip);

/* Returns the total central directory size in bytes. */
/* The current max supported size is <= MZ_UINT32_MAX. */
MINIZ_EXPORT size_t mz_zip_get_central_dir_size(mz_zip_archive *pZip);

/* Extracts a archive file to a memory buffer using no memory allocation. */
/* There must be at least enough room on the stack to store the inflator's
 * state
 * (~34KB or so). */
MINIZ_EXPORT mz_bool mz_zip_reader_extract_to_mem_no_alloc(
    mz_zip_archive *pZip, mz_uint file_index, void *pBuf, size_t buf_size,
    mz_uint flags, void *pUser_read_buf, size_t user_read_buf_size);
MINIZ_EXPORT mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(
    mz_zip_archive *pZip, const char *pFilename, void *pBuf, size_t buf_size,
    mz_uint flags, void *pUser_read_buf, size_t user_read_buf_size);

/* Extracts a archive file to a memory buffer. */
MINIZ_EXPORT mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip,
                                                  mz_uint file_index,
                                                  void *pBuf, size_t buf_size,
                                                  mz_uint flags);
MINIZ_EXPORT mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip,
                                                       const char *pFilename,
                                                       void *pBuf,
                                                       size_t buf_size,
                                                       mz_uint flags);

/* Extracts a archive file to a dynamically allocated heap buffer. */
/* The memory will be allocated via the mz_zip_archive's alloc/realloc
 * functions. */
/* Returns NULL and sets the last error on failure. */
MINIZ_EXPORT void *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip,
                                                 mz_uint file_index,
                                                 size_t *pSize, mz_uint flags);
MINIZ_EXPORT void *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip,
                                                      const char *pFilename,
                                                      size_t *pSize,
                                                      mz_uint flags);

/* Extracts a archive file using a callback function to output the file's
 * data.
 */
MINIZ_EXPORT mz_bool mz_zip_reader_extract_to_callback(
    mz_zip_archive *pZip, mz_uint file_index, mz_file_write_func pCallback,
    void *pOpaque, mz_uint flags);
MINIZ_EXPORT mz_bool mz_zip_reader_extract_file_to_callback(
    mz_zip_archive *pZip, const char *pFilename, mz_file_write_func pCallback,
    void *pOpaque, mz_uint flags);

/* Extract a file iteratively */
MINIZ_EXPORT mz_zip_reader_extract_iter_state *
mz_zip_reader_extract_iter_new(mz_zip_archive *pZip, mz_uint file_index,
                               mz_uint flags);
MINIZ_EXPORT mz_zip_reader_extract_iter_state *
mz_zip_reader_extract_file_iter_new(mz_zip_archive *pZip, const char *pFilename,
                                    mz_uint flags);
MINIZ_EXPORT size_t mz_zip_reader_extract_iter_read(
    mz_zip_reader_extract_iter_state *pState, void *pvBuf, size_t buf_size);
MINIZ_EXPORT mz_bool
mz_zip_reader_extract_iter_free(mz_zip_reader_extract_iter_state *pState);

#ifndef MINIZ_NO_STDIO
/* Extracts a archive file to a disk file and sets its last accessed and
 * modified times. */
/* This function only extracts files, not archive directory records. */
MINIZ_EXPORT mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip,
                                                   mz_uint file_index,
                                                   const char *pDst_filename,
                                                   mz_uint flags);
MINIZ_EXPORT mz_bool mz_zip_reader_extract_file_to_file(
    mz_zip_archive *pZip, const char *pArchive_filename,
    const char *pDst_filename, mz_uint flags);

/* Extracts a archive file starting at the current position in the destination
 * FILE stream. */
MINIZ_EXPORT mz_bool mz_zip_reader_extract_to_cfile(mz_zip_archive *pZip,
                                                    mz_uint file_index,
                                                    MZ_FILE *File,
                                                    mz_uint flags);
MINIZ_EXPORT mz_bool mz_zip_reader_extract_file_to_cfile(
    mz_zip_archive *pZip, const char *pArchive_filename, MZ_FILE *pFile,
    mz_uint flags);
#endif

#if 0
/* TODO */
	typedef void *mz_zip_streaming_extract_state_ptr;
	mz_zip_streaming_extract_state_ptr mz_zip_streaming_extract_begin(mz_zip_archive *pZip, mz_uint file_index, mz_uint flags);
	mz_uint64 mz_zip_streaming_extract_get_size(mz_zip_archive *pZip, mz_zip_streaming_extract_state_ptr pState);
	mz_uint64 mz_zip_streaming_extract_get_cur_ofs(mz_zip_archive *pZip, mz_zip_streaming_extract_state_ptr pState);
	mz_bool mz_zip_streaming_extract_seek(mz_zip_archive *pZip, mz_zip_streaming_extract_state_ptr pState, mz_uint64 new_ofs);
	size_t mz_zip_streaming_extract_read(mz_zip_archive *pZip, mz_zip_streaming_extract_state_ptr pState, void *pBuf, size_t buf_size);
	mz_bool mz_zip_streaming_extract_end(mz_zip_archive *pZip, mz_zip_streaming_extract_state_ptr pState);
#endif

/* This function compares the archive's local headers, the optional local
 * zip64 extended information block, and the optional descriptor following the
 * compressed data vs. the data in the central directory. */
/* It also validates that each file can be successfully uncompressed unless
 * the MZ_ZIP_FLAG_VALIDATE_HEADERS_ONLY is specified. */
MINIZ_EXPORT mz_bool mz_zip_validate_file(mz_zip_archive *pZip,
                                          mz_uint file_index, mz_uint flags);

/* Validates an entire archive by calling mz_zip_validate_file() on each file.
 */
MINIZ_EXPORT mz_bool mz_zip_validate_archive(mz_zip_archive *pZip,
                                             mz_uint flags);

/* Misc utils/helpers, valid for ZIP reading or writing */
MINIZ_EXPORT mz_bool mz_zip_validate_mem_archive(const void *pMem, size_t size,
                                                 mz_uint flags,
                                                 mz_zip_error *pErr);
#ifndef MINIZ_NO_STDIO
MINIZ_EXPORT mz_bool mz_zip_validate_file_archive(const char *pFilename,
                                                  mz_uint flags,
                                                  mz_zip_error *pErr);
#endif

/* Universal end function - calls either mz_zip_reader_end() or
 * mz_zip_writer_end(). */
MINIZ_EXPORT mz_bool mz_zip_end(mz_zip_archive *pZip);

/* -------- ZIP writing */

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

/* Inits a ZIP archive writer. */
/*Set pZip->m_pWrite (and pZip->m_pIO_opaque) before calling
 * mz_zip_writer_init or mz_zip_writer_init_v2*/
/*The output is streamable, i.e. file_ofs in mz_file_write_func always
 * increases only by n*/
MINIZ_EXPORT mz_bool mz_zip_writer_init(mz_zip_archive *pZip,
                                        mz_uint64 existing_size);
MINIZ_EXPORT mz_bool mz_zip_writer_init_v2(mz_zip_archive *pZip,
                                           mz_uint64 existing_size,
                                           mz_uint flags);

MINIZ_EXPORT mz_bool mz_zip_writer_init_heap(
    mz_zip_archive *pZip, size_t size_to_reserve_at_beginning,
    size_t initial_allocation_size);
MINIZ_EXPORT mz_bool mz_zip_writer_init_heap_v2(
    mz_zip_archive *pZip, size_t size_to_reserve_at_beginning,
    size_t initial_allocation_size, mz_uint flags);

#ifndef MINIZ_NO_STDIO
MINIZ_EXPORT mz_bool
mz_zip_writer_init_file(mz_zip_archive *pZip, const char *pFilename,
                        mz_uint64 size_to_reserve_at_beginning);
MINIZ_EXPORT mz_bool mz_zip_writer_init_file_v2(
    mz_zip_archive *pZip, const char *pFilename,
    mz_uint64 size_to_reserve_at_beginning, mz_uint flags);
MINIZ_EXPORT mz_bool mz_zip_writer_init_cfile(mz_zip_archive *pZip,
                                              MZ_FILE *pFile, mz_uint flags);
#endif

/* Converts a ZIP archive reader object into a writer object, to allow
 * efficient in-place file appends to occur on an existing archive. */
/* For archives opened using mz_zip_reader_init_file, pFilename must be the
 * archive's filename so it can be reopened for writing. If the file can't be
 * reopened, mz_zip_reader_end() will be called. */
/* For archives opened using mz_zip_reader_init_mem, the memory block must be
 * growable using the realloc callback (which defaults to realloc unless
 * you've overridden it). */
/* Finally, for archives opened using mz_zip_reader_init, the mz_zip_archive's
 * user provided m_pWrite function cannot be NULL. */
/* Note: In-place archive modification is not recommended unless you know what
 * you're doing, because if execution stops or something goes wrong before */
/* the archive is finalized the file's central directory will be hosed. */
MINIZ_EXPORT mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip,
                                                    const char *pFilename);
MINIZ_EXPORT mz_bool mz_zip_writer_init_from_reader_v2(mz_zip_archive *pZip,
                                                       const char *pFilename,
                                                       mz_uint flags);

/* Adds the contents of a memory buffer to an archive. These functions record
 * the current local time into the archive. */
/* To add a directory entry, call this method with an archive name ending in a
 * forwardslash with an empty buffer. */
/* level_and_flags - compression level (0-10, see MZ_BEST_SPEED,
 * MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags,
 * or just set to MZ_DEFAULT_COMPRESSION. */
MINIZ_EXPORT mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip,
                                           const char *pArchive_name,
                                           const void *pBuf, size_t buf_size,
                                           mz_uint level_and_flags);

/* Like mz_zip_writer_add_mem(), except you can specify a file comment field,
 * and optionally supply the function with already compressed data. */
/* uncomp_size/uncomp_crc32 are only used if the MZ_ZIP_FLAG_COMPRESSED_DATA
 * flag is specified. */
MINIZ_EXPORT mz_bool mz_zip_writer_add_mem_ex(
    mz_zip_archive *pZip, const char *pArchive_name, const void *pBuf,
    size_t buf_size, const void *pComment, mz_uint16 comment_size,
    mz_uint level_and_flags, mz_uint64 uncomp_size, mz_uint32 uncomp_crc32);

MINIZ_EXPORT mz_bool mz_zip_writer_add_mem_ex_v2(
    mz_zip_archive *pZip, const char *pArchive_name, const void *pBuf,
    size_t buf_size, const void *pComment, mz_uint16 comment_size,
    mz_uint level_and_flags, mz_uint64 uncomp_size, mz_uint32 uncomp_crc32,
    MZ_TIME_T *last_modified, const char *user_extra_data_local,
    mz_uint user_extra_data_local_len, const char *user_extra_data_central,
    mz_uint user_extra_data_central_len);

/* Adds the contents of a file to an archive. This function also records the
 * disk file's modified time into the archive. */
/* File data is supplied via a read callback function. User
 * mz_zip_writer_add_(c)file to add a file directly.*/
MINIZ_EXPORT mz_bool mz_zip_writer_add_read_buf_callback(
    mz_zip_archive *pZip, const char *pArchive_name,
    mz_file_read_func read_callback, void *callback_opaque, mz_uint64 max_size,
    const MZ_TIME_T *pFile_time, const void *pComment, mz_uint16 comment_size,
    mz_uint level_and_flags, mz_uint32 ext_attributes,
    const char *user_extra_data_local, mz_uint user_extra_data_local_len,
    const char *user_extra_data_central, mz_uint user_extra_data_central_len);

#ifndef MINIZ_NO_STDIO
/* Adds the contents of a disk file to an archive. This function also records
 * the disk file's modified time into the archive. */
/* level_and_flags - compression level (0-10, see MZ_BEST_SPEED,
 * MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags,
 * or just set to MZ_DEFAULT_COMPRESSION. */
MINIZ_EXPORT mz_bool mz_zip_writer_add_file(
    mz_zip_archive *pZip, const char *pArchive_name, const char *pSrc_filename,
    const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags,
    mz_uint32 ext_attributes);

/* Like mz_zip_writer_add_file(), except the file data is read from the
 * specified FILE stream. */
MINIZ_EXPORT mz_bool mz_zip_writer_add_cfile(
    mz_zip_archive *pZip, const char *pArchive_name, MZ_FILE *pSrc_file,
    mz_uint64 max_size, const MZ_TIME_T *pFile_time, const void *pComment,
    mz_uint16 comment_size, mz_uint level_and_flags, mz_uint32 ext_attributes,
    const char *user_extra_data_local, mz_uint user_extra_data_local_len,
    const char *user_extra_data_central, mz_uint user_extra_data_central_len);
#endif

/* Adds a file to an archive by fully cloning the data from another archive.
 */
/* This function fully clones the source file's compressed data (no
 * recompression), along with its full filename, extra data (it may add or
 * modify the zip64 local header extra data field), and the optional
 * descriptor following the compressed data. */
MINIZ_EXPORT mz_bool mz_zip_writer_add_from_zip_reader(
    mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint src_file_index);

/* Finalizes the archive by writing the central directory records followed by
 * the end of central directory record. */
/* After an archive is finalized, the only valid call on the mz_zip_archive
 * struct is mz_zip_writer_end(). */
/* An archive must be manually finalized by calling this function for it to be
 * valid. */
MINIZ_EXPORT mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);

/* Finalizes a heap archive, returning a pointer to the heap block and its
 * size.
 */
/* The heap block will be allocated using the mz_zip_archive's alloc/realloc
 * callbacks. */
MINIZ_EXPORT mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip,
                                                         void **ppBuf,
                                                         size_t *pSize);

/* Ends archive writing, freeing all allocations, and closing the output file
 * if mz_zip_writer_init_file() was used. */
/* Note for the archive to be valid, it *must* have been finalized before
 * ending (this function will not do it for you). */
MINIZ_EXPORT mz_bool mz_zip_writer_end(mz_zip_archive *pZip);

/* -------- Misc. high-level helper functions: */

/* mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically)
 * appends a memory blob to a ZIP archive. */
/* Note this is NOT a fully safe operation. If it crashes or dies in some way
 * your archive can be left in a screwed up state (without a central
 * directory).
 */
/* level_and_flags - compression level (0-10, see MZ_BEST_SPEED,
 * MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags,
 * or just set to MZ_DEFAULT_COMPRESSION. */
/* TODO: Perhaps add an option to leave the existing central dir in place in
 * case the add dies? We could then truncate the file (so the old central dir
 * would be at the end) if something goes wrong. */
MINIZ_EXPORT mz_bool mz_zip_add_mem_to_archive_file_in_place(
    const char *pZip_filename, const char *pArchive_name, const void *pBuf,
    size_t buf_size, const void *pComment, mz_uint16 comment_size,
    mz_uint level_and_flags);
MINIZ_EXPORT mz_bool mz_zip_add_mem_to_archive_file_in_place_v2(
    const char *pZip_filename, const char *pArchive_name, const void *pBuf,
    size_t buf_size, const void *pComment, mz_uint16 comment_size,
    mz_uint level_and_flags, mz_zip_error *pErr);

#ifndef MINIZ_NO_STDIO
/* Reads a single file from an archive into a heap block. */
/* If pComment is not NULL, only the file with the specified comment will be
 * extracted. */
/* Returns NULL on failure. */
MINIZ_EXPORT void *
mz_zip_extract_archive_file_to_heap(const char *pZip_filename,
                                    const char *pArchive_name, size_t *pSize,
                                    mz_uint flags);
MINIZ_EXPORT void *mz_zip_extract_archive_file_to_heap_v2(
    const char *pZip_filename, const char *pArchive_name, const char *pComment,
    size_t *pSize, mz_uint flags, mz_zip_error *pErr);
#endif

#endif /* #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS */

#ifdef __cplusplus
}
#endif

#endif /* MINIZ_NO_ARCHIVE_APIS */

#ifndef MINIZ_HEADER_FILE_ONLY
/**************************************************************************
 *
 * Copyright 2013-2014 RAD Game Tools and Valve Software
 * Copyright 2010-2014 Rich Geldreich and Tenacious Software LLC
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/

typedef unsigned char mz_validate_uint16[sizeof(mz_uint16) == 2 ? 1 : -1];
typedef unsigned char mz_validate_uint32[sizeof(mz_uint32) == 4 ? 1 : -1];
typedef unsigned char mz_validate_uint64[sizeof(mz_uint64) == 8 ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------- zlib-style API's */

mz_ulong mz_adler32(mz_ulong adler, const unsigned char *ptr, size_t buf_len) {
  mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16);
  size_t block_len = buf_len % 5552;
  if (!ptr)
    return MZ_ADLER32_INIT;
  while (buf_len) {
    for (i = 0; i + 7 < block_len; i += 8, ptr += 8) {
      s1 += ptr[0], s2 += s1;
      s1 += ptr[1], s2 += s1;
      s1 += ptr[2], s2 += s1;
      s1 += ptr[3], s2 += s1;
      s1 += ptr[4], s2 += s1;
      s1 += ptr[5], s2 += s1;
      s1 += ptr[6], s2 += s1;
      s1 += ptr[7], s2 += s1;
    }
    for (; i < block_len; ++i)
      s1 += *ptr++, s2 += s1;
    s1 %= 65521U, s2 %= 65521U;
    buf_len -= block_len;
    block_len = 5552;
  }
  return (s2 << 16) + s1;
}

/* Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C
 * implementation that balances processor cache usage against speed":
 * http://www.geocities.com/malbrain/ */
#if 0
    mz_ulong mz_crc32(mz_ulong crc, const mz_uint8 *ptr, size_t buf_len)
    {
        static const mz_uint32 s_crc32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
                                               0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
        mz_uint32 crcu32 = (mz_uint32)crc;
        if (!ptr)
            return MZ_CRC32_INIT;
        crcu32 = ~crcu32;
        while (buf_len--)
        {
            mz_uint8 b = *ptr++;
            crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b & 0xF)];
            crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b >> 4)];
        }
        return ~crcu32;
    }
#elif defined(USE_EXTERNAL_MZCRC)
/* If USE_EXTERNAL_CRC is defined, an external module will export the
 * mz_crc32() symbol for us to use, e.g. an SSE-accelerated version.
 * Depending on the impl, it may be necessary to ~ the input/output crc
 * values.
 */
mz_ulong mz_crc32(mz_ulong crc, const mz_uint8 *ptr, size_t buf_len);
#else
/* Faster, but larger CPU cache footprint.
 */
mz_ulong mz_crc32(mz_ulong crc, const mz_uint8 *ptr, size_t buf_len) {
  static const mz_uint32 s_crc_table[256] = {
      0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F,
      0xE963A535, 0x9E6495A3, 0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
      0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91, 0x1DB71064, 0x6AB020F2,
      0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
      0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9,
      0xFA0F3D63, 0x8D080DF5, 0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
      0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B, 0x35B5A8FA, 0x42B2986C,
      0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
      0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423,
      0xCFBA9599, 0xB8BDA50F, 0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
      0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D, 0x76DC4190, 0x01DB7106,
      0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
      0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D,
      0x91646C97, 0xE6635C01, 0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
      0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457, 0x65B0D9C6, 0x12B7E950,
      0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
      0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7,
      0xA4D1C46D, 0xD3D6F4FB, 0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
      0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9, 0x5005713C, 0x270241AA,
      0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
      0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81,
      0xB7BD5C3B, 0xC0BA6CAD, 0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
      0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683, 0xE3630B12, 0x94643B84,
      0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
      0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB,
      0x196C3671, 0x6E6B06E7, 0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
      0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5, 0xD6D6A3E8, 0xA1D1937E,
      0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
      0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55,
      0x316E8EEF, 0x4669BE79, 0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
      0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F, 0xC5BA3BBE, 0xB2BD0B28,
      0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
      0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F,
      0x72076785, 0x05005713, 0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
      0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21, 0x86D3D2D4, 0xF1D4E242,
      0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
      0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69,
      0x616BFFD3, 0x166CCF45, 0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
      0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB, 0xAED16A4A, 0xD9D65ADC,
      0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
      0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693,
      0x54DE5729, 0x23D967BF, 0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
      0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D};

  mz_uint32 crc32 = (mz_uint32)crc ^ 0xFFFFFFFF;
  const mz_uint8 *pByte_buf = (const mz_uint8 *)ptr;

  while (buf_len >= 4) {
    crc32 = (crc32 >> 8) ^ s_crc_table[(crc32 ^ pByte_buf[0]) & 0xFF];
    crc32 = (crc32 >> 8) ^ s_crc_table[(crc32 ^ pByte_buf[1]) & 0xFF];
    crc32 = (crc32 >> 8) ^ s_crc_table[(crc32 ^ pByte_buf[2]) & 0xFF];
    crc32 = (crc32 >> 8) ^ s_crc_table[(crc32 ^ pByte_buf[3]) & 0xFF];
    pByte_buf += 4;
    buf_len -= 4;
  }

  while (buf_len) {
    crc32 = (crc32 >> 8) ^ s_crc_table[(crc32 ^ pByte_buf[0]) & 0xFF];
    ++pByte_buf;
    --buf_len;
  }

  return ~crc32;
}
#endif

void mz_free(void *p) { MZ_FREE(p); }

MINIZ_EXPORT void *miniz_def_alloc_func(void *opaque, size_t items,
                                        size_t size) {
  (void)opaque, (void)items, (void)size;
  return MZ_MALLOC(items * size);
}
MINIZ_EXPORT void miniz_def_free_func(void *opaque, void *address) {
  (void)opaque, (void)address;
  MZ_FREE(address);
}
MINIZ_EXPORT void *miniz_def_realloc_func(void *opaque, void *address,
                                          size_t items, size_t size) {
  (void)opaque, (void)address, (void)items, (void)size;
  return MZ_REALLOC(address, items * size);
}

const char *mz_version(void) { return MZ_VERSION; }

#ifndef MINIZ_NO_ZLIB_APIS

#ifndef MINIZ_NO_DEFLATE_APIS

int mz_deflateInit(mz_streamp pStream, int level) {
  return mz_deflateInit2(pStream, level, MZ_DEFLATED, MZ_DEFAULT_WINDOW_BITS, 9,
                         MZ_DEFAULT_STRATEGY);
}

int mz_deflateInit2(mz_streamp pStream, int level, int method, int window_bits,
                    int mem_level, int strategy) {
  tdefl_compressor *pComp;
  mz_uint comp_flags =
      TDEFL_COMPUTE_ADLER32 |
      tdefl_create_comp_flags_from_zip_params(level, window_bits, strategy);

  if (!pStream)
    return MZ_STREAM_ERROR;
  if ((method != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) ||
      ((window_bits != MZ_DEFAULT_WINDOW_BITS) &&
       (-window_bits != MZ_DEFAULT_WINDOW_BITS)))
    return MZ_PARAM_ERROR;

  pStream->data_type = 0;
  pStream->adler = MZ_ADLER32_INIT;
  pStream->msg = NULL;
  pStream->reserved = 0;
  pStream->total_in = 0;
  pStream->total_out = 0;
  if (!pStream->zalloc)
    pStream->zalloc = miniz_def_alloc_func;
  if (!pStream->zfree)
    pStream->zfree = miniz_def_free_func;

  pComp = (tdefl_compressor *)pStream->zalloc(pStream->opaque, 1,
                                              sizeof(tdefl_compressor));
  if (!pComp)
    return MZ_MEM_ERROR;

  pStream->state = (struct mz_internal_state *)pComp;

  if (tdefl_init(pComp, NULL, NULL, comp_flags) != TDEFL_STATUS_OKAY) {
    mz_deflateEnd(pStream);
    return MZ_PARAM_ERROR;
  }

  return MZ_OK;
}

int mz_deflateReset(mz_streamp pStream) {
  if ((!pStream) || (!pStream->state) || (!pStream->zalloc) ||
      (!pStream->zfree))
    return MZ_STREAM_ERROR;
  pStream->total_in = pStream->total_out = 0;
  tdefl_init((tdefl_compressor *)pStream->state, NULL, NULL,
             ((tdefl_compressor *)pStream->state)->m_flags);
  return MZ_OK;
}

int mz_deflate(mz_streamp pStream, int flush) {
  size_t in_bytes, out_bytes;
  mz_ulong orig_total_in, orig_total_out;
  int mz_status = MZ_OK;

  if ((!pStream) || (!pStream->state) || (flush < 0) || (flush > MZ_FINISH) ||
      (!pStream->next_out))
    return MZ_STREAM_ERROR;
  if (!pStream->avail_out)
    return MZ_BUF_ERROR;

  if (flush == MZ_PARTIAL_FLUSH)
    flush = MZ_SYNC_FLUSH;

  if (((tdefl_compressor *)pStream->state)->m_prev_return_status ==
      TDEFL_STATUS_DONE)
    return (flush == MZ_FINISH) ? MZ_STREAM_END : MZ_BUF_ERROR;

  orig_total_in = pStream->total_in;
  orig_total_out = pStream->total_out;
  for (;;) {
    tdefl_status defl_status;
    in_bytes = pStream->avail_in;
    out_bytes = pStream->avail_out;

    defl_status = tdefl_compress((tdefl_compressor *)pStream->state,
                                 pStream->next_in, &in_bytes, pStream->next_out,
                                 &out_bytes, (tdefl_flush)flush);
    pStream->next_in += (mz_uint)in_bytes;
    pStream->avail_in -= (mz_uint)in_bytes;
    pStream->total_in += (mz_uint)in_bytes;
    pStream->adler = tdefl_get_adler32((tdefl_compressor *)pStream->state);

    pStream->next_out += (mz_uint)out_bytes;
    pStream->avail_out -= (mz_uint)out_bytes;
    pStream->total_out += (mz_uint)out_bytes;

    if (defl_status < 0) {
      mz_status = MZ_STREAM_ERROR;
      break;
    } else if (defl_status == TDEFL_STATUS_DONE) {
      mz_status = MZ_STREAM_END;
      break;
    } else if (!pStream->avail_out)
      break;
    else if ((!pStream->avail_in) && (flush != MZ_FINISH)) {
      if ((flush) || (pStream->total_in != orig_total_in) ||
          (pStream->total_out != orig_total_out))
        break;
      return MZ_BUF_ERROR; /* Can't make forward progress without some input.
                            */
    }
  }
  return mz_status;
}

int mz_deflateEnd(mz_streamp pStream) {
  if (!pStream)
    return MZ_STREAM_ERROR;
  if (pStream->state) {
    pStream->zfree(pStream->opaque, pStream->state);
    pStream->state = NULL;
  }
  return MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len) {
  (void)pStream;
  /* This is really over conservative. (And lame, but it's actually pretty
   * tricky to compute a true upper bound given the way tdefl's blocking
   * works.)
   */
  return MZ_MAX(128 + (source_len * 110) / 100,
                128 + source_len + ((source_len / (31 * 1024)) + 1) * 5);
}

int mz_compress2(unsigned char *pDest, mz_ulong *pDest_len,
                 const unsigned char *pSource, mz_ulong source_len, int level) {
  int status;
  mz_stream stream;
  memset(&stream, 0, sizeof(stream));

#if defined(__MINGW32__) || defined(__MINGW64__) || defined(__WATCOMC__)
  /* In case mz_ulong is 64-bits (argh I hate longs). */
#else
  if ((mz_uint64)(source_len | *pDest_len) > 0xFFFFFFFFU)
    return MZ_PARAM_ERROR;
#endif
  stream.next_in = pSource;
  stream.avail_in = (mz_uint32)source_len;
  stream.next_out = pDest;
  stream.avail_out = (mz_uint32)*pDest_len;

  status = mz_deflateInit(&stream, level);
  if (status != MZ_OK)
    return status;

  status = mz_deflate(&stream, MZ_FINISH);
  if (status != MZ_STREAM_END) {
    mz_deflateEnd(&stream);
    return (status == MZ_OK) ? MZ_BUF_ERROR : status;
  }

  *pDest_len = stream.total_out;
  return mz_deflateEnd(&stream);
}

int mz_compress(unsigned char *pDest, mz_ulong *pDest_len,
                const unsigned char *pSource, mz_ulong source_len) {
  return mz_compress2(pDest, pDest_len, pSource, source_len,
                      MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong source_len) {
  return mz_deflateBound(NULL, source_len);
}

#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ifndef MINIZ_NO_INFLATE_APIS

typedef struct {
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_first_call, m_has_flushed;
  int m_window_bits;
  mz_uint8 m_dict[TINFL_LZ_DICT_SIZE];
  tinfl_status m_last_status;
} inflate_state;

int mz_inflateInit2(mz_streamp pStream, int window_bits) {
  inflate_state *pDecomp;
  if (!pStream)
    return MZ_STREAM_ERROR;
  if ((window_bits != MZ_DEFAULT_WINDOW_BITS) &&
      (-window_bits != MZ_DEFAULT_WINDOW_BITS))
    return MZ_PARAM_ERROR;

  pStream->data_type = 0;
  pStream->adler = 0;
  pStream->msg = NULL;
  pStream->total_in = 0;
  pStream->total_out = 0;
  pStream->reserved = 0;
  if (!pStream->zalloc)
    pStream->zalloc = miniz_def_alloc_func;
  if (!pStream->zfree)
    pStream->zfree = miniz_def_free_func;

  pDecomp = (inflate_state *)pStream->zalloc(pStream->opaque, 1,
                                             sizeof(inflate_state));
  if (!pDecomp)
    return MZ_MEM_ERROR;

  pStream->state = (struct mz_internal_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_last_status = TINFL_STATUS_NEEDS_MORE_INPUT;
  pDecomp->m_first_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_window_bits = window_bits;

  return MZ_OK;
}

int mz_inflateInit(mz_streamp pStream) {
  return mz_inflateInit2(pStream, MZ_DEFAULT_WINDOW_BITS);
}

int mz_inflateReset(mz_streamp pStream) {
  inflate_state *pDecomp;
  if (!pStream)
    return MZ_STREAM_ERROR;

  pStream->data_type = 0;
  pStream->adler = 0;
  pStream->msg = NULL;
  pStream->total_in = 0;
  pStream->total_out = 0;
  pStream->reserved = 0;

  pDecomp = (inflate_state *)pStream->state;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_last_status = TINFL_STATUS_NEEDS_MORE_INPUT;
  pDecomp->m_first_call = 1;
  pDecomp->m_has_flushed = 0;
  /* pDecomp->m_window_bits = window_bits */;

  return MZ_OK;
}

int mz_inflate(mz_streamp pStream, int flush) {
  inflate_state *pState;
  mz_uint n, first_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  size_t in_bytes, out_bytes, orig_avail_in;
  tinfl_status status;

  if ((!pStream) || (!pStream->state))
    return MZ_STREAM_ERROR;
  if (flush == MZ_PARTIAL_FLUSH)
    flush = MZ_SYNC_FLUSH;
  if ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_FINISH))
    return MZ_STREAM_ERROR;

  pState = (inflate_state *)pStream->state;
  if (pState->m_window_bits > 0)
    decomp_flags |= TINFL_FLAG_PARSE_ZLIB_HEADER;
  orig_avail_in = pStream->avail_in;

  first_call = pState->m_first_call;
  pState->m_first_call = 0;
  if (pState->m_last_status < 0)
    return MZ_DATA_ERROR;

  if (pState->m_has_flushed && (flush != MZ_FINISH))
    return MZ_STREAM_ERROR;
  pState->m_has_flushed |= (flush == MZ_FINISH);

  if ((flush == MZ_FINISH) && (first_call)) {
    /* MZ_FINISH on the first call implies that the input and output buffers
     * are large enough to hold the entire compressed/decompressed file. */
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    in_bytes = pStream->avail_in;
    out_bytes = pStream->avail_out;
    status = tinfl_decompress(&pState->m_decomp, pStream->next_in, &in_bytes,
                              pStream->next_out, pStream->next_out, &out_bytes,
                              decomp_flags);
    pState->m_last_status = status;
    pStream->next_in += (mz_uint)in_bytes;
    pStream->avail_in -= (mz_uint)in_bytes;
    pStream->total_in += (mz_uint)in_bytes;
    pStream->adler = tinfl_get_adler32(&pState->m_decomp);
    pStream->next_out += (mz_uint)out_bytes;
    pStream->avail_out -= (mz_uint)out_bytes;
    pStream->total_out += (mz_uint)out_bytes;

    if (status < 0)
      return MZ_DATA_ERROR;
    else if (status != TINFL_STATUS_DONE) {
      pState->m_last_status = TINFL_STATUS_FAILED;
      return MZ_BUF_ERROR;
    }
    return MZ_STREAM_END;
  }
  /* flush != MZ_FINISH then we must assume there's more input. */
  if (flush != MZ_FINISH)
    decomp_flags |= TINFL_FLAG_HAS_MORE_INPUT;

  if (pState->m_dict_avail) {
    n = MZ_MIN(pState->m_dict_avail, pStream->avail_out);
    memcpy(pStream->next_out, pState->m_dict + pState->m_dict_ofs, n);
    pStream->next_out += n;
    pStream->avail_out -= n;
    pStream->total_out += n;
    pState->m_dict_avail -= n;
    pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_SIZE - 1);
    return ((pState->m_last_status == TINFL_STATUS_DONE) &&
            (!pState->m_dict_avail))
               ? MZ_STREAM_END
               : MZ_OK;
  }

  for (;;) {
    in_bytes = pStream->avail_in;
    out_bytes = TINFL_LZ_DICT_SIZE - pState->m_dict_ofs;

    status = tinfl_decompress(
        &pState->m_decomp, pStream->next_in, &in_bytes, pState->m_dict,
        pState->m_dict + pState->m_dict_ofs, &out_bytes, decomp_flags);
    pState->m_last_status = status;

    pStream->next_in += (mz_uint)in_bytes;
    pStream->avail_in -= (mz_uint)in_bytes;
    pStream->total_in += (mz_uint)in_bytes;
    pStream->adler = tinfl_get_adler32(&pState->m_decomp);

    pState->m_dict_avail = (mz_uint)out_bytes;

    n = MZ_MIN(pState->m_dict_avail, pStream->avail_out);
    memcpy(pStream->next_out, pState->m_dict + pState->m_dict_ofs, n);
    pStream->next_out += n;
    pStream->avail_out -= n;
    pStream->total_out += n;
    pState->m_dict_avail -= n;
    pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_SIZE - 1);

    if (status < 0)
      return MZ_DATA_ERROR; /* Stream is corrupted (there could be some
                               uncompressed data left in the output dictionary
                               - oh well). */
    else if ((status == TINFL_STATUS_NEEDS_MORE_INPUT) && (!orig_avail_in))
      return MZ_BUF_ERROR; /* Signal caller that we can't make forward
                              progress without supplying more input or by
                              setting flush to MZ_FINISH. */
    else if (flush == MZ_FINISH) {
      /* The output buffer MUST be large to hold the remaining uncompressed
       * data when flush==MZ_FINISH. */
      if (status == TINFL_STATUS_DONE)
        return pState->m_dict_avail ? MZ_BUF_ERROR : MZ_STREAM_END;
      /* status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's
       * at least 1 more byte on the way. If there's no more room left in the
       * output buffer then something is wrong. */
      else if (!pStream->avail_out)
        return MZ_BUF_ERROR;
    } else if ((status == TINFL_STATUS_DONE) || (!pStream->avail_in) ||
               (!pStream->avail_out) || (pState->m_dict_avail))
      break;
  }

  return ((status == TINFL_STATUS_DONE) && (!pState->m_dict_avail))
             ? MZ_STREAM_END
             : MZ_OK;
}

int mz_inflateEnd(mz_streamp pStream) {
  if (!pStream)
    return MZ_STREAM_ERROR;
  if (pStream->state) {
    pStream->zfree(pStream->opaque, pStream->state);
    pStream->state = NULL;
  }
  return MZ_OK;
}
int mz_uncompress2(unsigned char *pDest, mz_ulong *pDest_len,
                   const unsigned char *pSource, mz_ulong *pSource_len) {
  mz_stream stream;
  int status;
  memset(&stream, 0, sizeof(stream));

#if defined(__MINGW32__) || defined(__MINGW64__) || defined(__WATCOMC__)
  /* In case mz_ulong is 64-bits (argh I hate longs). */
#else
  if ((mz_uint64)(*pSource_len | *pDest_len) > 0xFFFFFFFFU)
    return MZ_PARAM_ERROR;
#endif
  stream.next_in = pSource;
  stream.avail_in = (mz_uint32)*pSource_len;
  stream.next_out = pDest;
  stream.avail_out = (mz_uint32)*pDest_len;

  status = mz_inflateInit(&stream);
  if (status != MZ_OK)
    return status;

  status = mz_inflate(&stream, MZ_FINISH);
  *pSource_len = *pSource_len - stream.avail_in;
  if (status != MZ_STREAM_END) {
    mz_inflateEnd(&stream);
    return ((status == MZ_BUF_ERROR) && (!stream.avail_in)) ? MZ_DATA_ERROR
                                                            : status;
  }
  *pDest_len = stream.total_out;

  return mz_inflateEnd(&stream);
}

int mz_uncompress(unsigned char *pDest, mz_ulong *pDest_len,
                  const unsigned char *pSource, mz_ulong source_len) {
  return mz_uncompress2(pDest, pDest_len, pSource, &source_len);
}

#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/

const char *mz_error(int err) {
  static struct {
    int m_err;
    const char *m_pDesc;
  } s_error_descs[] = {{MZ_OK, ""},
                       {MZ_STREAM_END, "stream end"},
                       {MZ_NEED_DICT, "need dictionary"},
                       {MZ_ERRNO, "file error"},
                       {MZ_STREAM_ERROR, "stream error"},
                       {MZ_DATA_ERROR, "data error"},
                       {MZ_MEM_ERROR, "out of memory"},
                       {MZ_BUF_ERROR, "buf error"},
                       {MZ_VERSION_ERROR, "version error"},
                       {MZ_PARAM_ERROR, "parameter error"}};
  mz_uint i;
  for (i = 0; i < sizeof(s_error_descs) / sizeof(s_error_descs[0]); ++i)
    if (s_error_descs[i].m_err == err)
      return s_error_descs[i].m_pDesc;
  return NULL;
}

#endif /*MINIZ_NO_ZLIB_APIS */

#ifdef __cplusplus
}
#endif

/*
  This is free and unencumbered software released into the public domain.

  Anyone is free to copy, modify, publish, use, compile, sell, or
  distribute this software, either in source code form or as a compiled
  binary, for any purpose, commercial or non-commercial, and by any
  means.

  In jurisdictions that recognize copyright laws, the author or authors
  of this software dedicate any and all copyright interest in the
  software to the public domain. We make this dedication for the benefit
  of the public at large and to the detriment of our heirs and
  successors. We intend this dedication to be an overt act of
  relinquishment in perpetuity of all present and future rights to this
  software under copyright law.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.

  For more information, please refer to <http://unlicense.org/>
*/
/**************************************************************************
 *
 * Copyright 2013-2014 RAD Game Tools and Valve Software
 * Copyright 2010-2014 Rich Geldreich and Tenacious Software LLC
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/

#ifndef MINIZ_NO_DEFLATE_APIS

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------- Low-level Compression (independent from all
 * decompression API's) */

/* Purposely making these tables static for faster init and thread safety. */
static const mz_uint16 s_tdefl_len_sym[256] = {
    257, 258, 259, 260, 261, 262, 263, 264, 265, 265, 266, 266, 267, 267, 268,
    268, 269, 269, 269, 269, 270, 270, 270, 270, 271, 271, 271, 271, 272, 272,
    272, 272, 273, 273, 273, 273, 273, 273, 273, 273, 274, 274, 274, 274, 274,
    274, 274, 274, 275, 275, 275, 275, 275, 275, 275, 275, 276, 276, 276, 276,
    276, 276, 276, 276, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277,
    277, 277, 277, 277, 277, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278,
    278, 278, 278, 278, 278, 278, 279, 279, 279, 279, 279, 279, 279, 279, 279,
    279, 279, 279, 279, 279, 279, 279, 280, 280, 280, 280, 280, 280, 280, 280,
    280, 280, 280, 280, 280, 280, 280, 280, 281, 281, 281, 281, 281, 281, 281,
    281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281,
    281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 282, 282, 282, 282, 282,
    282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282,
    282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 283, 283, 283,
    283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283,
    283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 284,
    284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284,
    284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284,
    285};

static const mz_uint8 s_tdefl_len_extra[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0};

static const mz_uint8 s_tdefl_small_dist_sym[512] = {
    0,  1,  2,  3,  4,  4,  5,  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,
    8,  8,  8,  8,  8,  9,  9,  9,  9,  9,  9,  9,  9,  10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17};

static const mz_uint8 s_tdefl_small_dist_extra[512] = {
    0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};

static const mz_uint8 s_tdefl_large_dist_sym[128] = {
    0,  0,  18, 19, 20, 20, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24,
    24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26,
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27,
    27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29};

static const mz_uint8 s_tdefl_large_dist_extra[128] = {
    0,  0,  8,  8,  9,  9,  9,  9,  10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11,
    11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13};

/* Radix sorts tdefl_sym_freq[] array by 16-bit key m_key. Returns ptr to
 * sorted values. */
typedef struct {
  mz_uint16 m_key, m_sym_index;
} tdefl_sym_freq;
static tdefl_sym_freq *tdefl_radix_sort_syms(mz_uint num_syms,
                                             tdefl_sym_freq *pSyms0,
                                             tdefl_sym_freq *pSyms1) {
  mz_uint32 total_passes = 2, pass_shift, pass, i, hist[256 * 2];
  tdefl_sym_freq *pCur_syms = pSyms0, *pNew_syms = pSyms1;
  MZ_CLEAR_ARR(hist);
  for (i = 0; i < num_syms; i++) {
    mz_uint freq = pSyms0[i].m_key;
    hist[freq & 0xFF]++;
    hist[256 + ((freq >> 8) & 0xFF)]++;
  }
  while ((total_passes > 1) && (num_syms == hist[(total_passes - 1) * 256]))
    total_passes--;
  for (pass_shift = 0, pass = 0; pass < total_passes; pass++, pass_shift += 8) {
    const mz_uint32 *pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    for (i = 0; i < 256; i++) {
      offsets[i] = cur_ofs;
      cur_ofs += pHist[i];
    }
    for (i = 0; i < num_syms; i++)
      pNew_syms[offsets[(pCur_syms[i].m_key >> pass_shift) & 0xFF]++] =
          pCur_syms[i];
    {
      tdefl_sym_freq *t = pCur_syms;
      pCur_syms = pNew_syms;
      pNew_syms = t;
    }
  }
  return pCur_syms;
}

/* tdefl_calculate_minimum_redundancy() originally written by: Alistair
 * Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November
 * 1996. */
static void tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, int n) {
  int root, leaf, next, avbl, used, dpth;
  if (n == 0)
    return;
  else if (n == 1) {
    A[0].m_key = 1;
    return;
  }
  A[0].m_key += A[1].m_key;
  root = 0;
  leaf = 2;
  for (next = 1; next < n - 1; next++) {
    if (leaf >= n || A[root].m_key < A[leaf].m_key) {
      A[next].m_key = A[root].m_key;
      A[root++].m_key = (mz_uint16)next;
    } else
      A[next].m_key = A[leaf++].m_key;
    if (leaf >= n || (root < next && A[root].m_key < A[leaf].m_key)) {
      A[next].m_key = (mz_uint16)(A[next].m_key + A[root].m_key);
      A[root++].m_key = (mz_uint16)next;
    } else
      A[next].m_key = (mz_uint16)(A[next].m_key + A[leaf++].m_key);
  }
  A[n - 2].m_key = 0;
  for (next = n - 3; next >= 0; next--)
    A[next].m_key = A[A[next].m_key].m_key + 1;
  avbl = 1;
  used = dpth = 0;
  root = n - 2;
  next = n - 1;
  while (avbl > 0) {
    while (root >= 0 && (int)A[root].m_key == dpth) {
      used++;
      root--;
    }
    while (avbl > used) {
      A[next--].m_key = (mz_uint16)(dpth);
      avbl--;
    }
    avbl = 2 * used;
    dpth++;
    used = 0;
  }
}

/* Limits canonical Huffman code table's max code size. */
enum { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
static void tdefl_huffman_enforce_max_code_size(int *pNum_codes,
                                                int code_list_len,
                                                int max_code_size) {
  int i;
  mz_uint32 total = 0;
  if (code_list_len <= 1)
    return;
  for (i = max_code_size + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++)
    pNum_codes[max_code_size] += pNum_codes[i];
  for (i = max_code_size; i > 0; i--)
    total += (((mz_uint32)pNum_codes[i]) << (max_code_size - i));
  while (total != (1UL << max_code_size)) {
    pNum_codes[max_code_size]--;
    for (i = max_code_size - 1; i > 0; i--)
      if (pNum_codes[i]) {
        pNum_codes[i]--;
        pNum_codes[i + 1] += 2;
        break;
      }
    total--;
  }
}

static void tdefl_optimize_huffman_table(tdefl_compressor *d, int table_num,
                                         int table_len, int code_size_limit,
                                         int static_table) {
  int i, j, l, num_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE];
  mz_uint next_code[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1];
  MZ_CLEAR_ARR(num_codes);
  if (static_table) {
    for (i = 0; i < table_len; i++)
      num_codes[d->m_huff_code_sizes[table_num][i]]++;
  } else {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS],
        *pSyms;
    int num_used_syms = 0;
    const mz_uint16 *pSym_count = &d->m_huff_count[table_num][0];
    for (i = 0; i < table_len; i++)
      if (pSym_count[i]) {
        syms0[num_used_syms].m_key = (mz_uint16)pSym_count[i];
        syms0[num_used_syms++].m_sym_index = (mz_uint16)i;
      }

    pSyms = tdefl_radix_sort_syms(num_used_syms, syms0, syms1);
    tdefl_calculate_minimum_redundancy(pSyms, num_used_syms);

    for (i = 0; i < num_used_syms; i++)
      num_codes[pSyms[i].m_key]++;

    tdefl_huffman_enforce_max_code_size(num_codes, num_used_syms,
                                        code_size_limit);

    MZ_CLEAR_ARR(d->m_huff_code_sizes[table_num]);
    MZ_CLEAR_ARR(d->m_huff_codes[table_num]);
    for (i = 1, j = num_used_syms; i <= code_size_limit; i++)
      for (l = num_codes[i]; l > 0; l--)
        d->m_huff_code_sizes[table_num][pSyms[--j].m_sym_index] = (mz_uint8)(i);
  }

  next_code[1] = 0;
  for (j = 0, i = 2; i <= code_size_limit; i++)
    next_code[i] = j = ((j + num_codes[i - 1]) << 1);

  for (i = 0; i < table_len; i++) {
    mz_uint rev_code = 0, code, code_size;
    if ((code_size = d->m_huff_code_sizes[table_num][i]) == 0)
      continue;
    code = next_code[code_size]++;
    for (l = code_size; l > 0; l--, code >>= 1)
      rev_code = (rev_code << 1) | (code & 1);
    d->m_huff_codes[table_num][i] = (mz_uint16)rev_code;
  }
}

#define TDEFL_PUT_BITS(b, l)                                                   \
  do {                                                                         \
    mz_uint bits = b;                                                          \
    mz_uint len = l;                                                           \
    MZ_ASSERT(bits <= ((1U << len) - 1U));                                     \
    d->m_bit_buffer |= (bits << d->m_bits_in);                                 \
    d->m_bits_in += len;                                                       \
    while (d->m_bits_in >= 8) {                                                \
      if (d->m_pOutput_buf < d->m_pOutput_buf_end)                             \
        *d->m_pOutput_buf++ = (mz_uint8)(d->m_bit_buffer);                     \
      d->m_bit_buffer >>= 8;                                                   \
      d->m_bits_in -= 8;                                                       \
    }                                                                          \
  }                                                                            \
  MZ_MACRO_END

#define TDEFL_RLE_PREV_CODE_SIZE()                                             \
  {                                                                            \
    if (rle_repeat_count) {                                                    \
      if (rle_repeat_count < 3) {                                              \
        d->m_huff_count[2][prev_code_size] =                                   \
            (mz_uint16)(d->m_huff_count[2][prev_code_size] +                   \
                        rle_repeat_count);                                     \
        while (rle_repeat_count--)                                             \
          packed_code_sizes[num_packed_code_sizes++] = prev_code_size;         \
      } else {                                                                 \
        d->m_huff_count[2][16] = (mz_uint16)(d->m_huff_count[2][16] + 1);      \
        packed_code_sizes[num_packed_code_sizes++] = 16;                       \
        packed_code_sizes[num_packed_code_sizes++] =                           \
            (mz_uint8)(rle_repeat_count - 3);                                  \
      }                                                                        \
      rle_repeat_count = 0;                                                    \
    }                                                                          \
  }

#define TDEFL_RLE_ZERO_CODE_SIZE()                                             \
  {                                                                            \
    if (rle_z_count) {                                                         \
      if (rle_z_count < 3) {                                                   \
        d->m_huff_count[2][0] =                                                \
            (mz_uint16)(d->m_huff_count[2][0] + rle_z_count);                  \
        while (rle_z_count--)                                                  \
          packed_code_sizes[num_packed_code_sizes++] = 0;                      \
      } else if (rle_z_count <= 10) {                                          \
        d->m_huff_count[2][17] = (mz_uint16)(d->m_huff_count[2][17] + 1);      \
        packed_code_sizes[num_packed_code_sizes++] = 17;                       \
        packed_code_sizes[num_packed_code_sizes++] =                           \
            (mz_uint8)(rle_z_count - 3);                                       \
      } else {                                                                 \
        d->m_huff_count[2][18] = (mz_uint16)(d->m_huff_count[2][18] + 1);      \
        packed_code_sizes[num_packed_code_sizes++] = 18;                       \
        packed_code_sizes[num_packed_code_sizes++] =                           \
            (mz_uint8)(rle_z_count - 11);                                      \
      }                                                                        \
      rle_z_count = 0;                                                         \
    }                                                                          \
  }

static const mz_uint8 s_tdefl_packed_code_size_syms_swizzle[] = {
    16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};

static void tdefl_start_dynamic_block(tdefl_compressor *d) {
  int num_lit_codes, num_dist_codes, num_bit_lengths;
  mz_uint i, total_code_sizes_to_pack, num_packed_code_sizes, rle_z_count,
      rle_repeat_count, packed_code_sizes_index;
  mz_uint8
      code_sizes_to_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1],
      packed_code_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1],
      prev_code_size = 0xFF;

  d->m_huff_count[0][256] = 1;

  tdefl_optimize_huffman_table(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_table(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  for (num_lit_codes = 286; num_lit_codes > 257; num_lit_codes--)
    if (d->m_huff_code_sizes[0][num_lit_codes - 1])
      break;
  for (num_dist_codes = 30; num_dist_codes > 1; num_dist_codes--)
    if (d->m_huff_code_sizes[1][num_dist_codes - 1])
      break;

  memcpy(code_sizes_to_pack, &d->m_huff_code_sizes[0][0], num_lit_codes);
  memcpy(code_sizes_to_pack + num_lit_codes, &d->m_huff_code_sizes[1][0],
         num_dist_codes);
  total_code_sizes_to_pack = num_lit_codes + num_dist_codes;
  num_packed_code_sizes = 0;
  rle_z_count = 0;
  rle_repeat_count = 0;

  memset(&d->m_huff_count[2][0], 0,
         sizeof(d->m_huff_count[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  for (i = 0; i < total_code_sizes_to_pack; i++) {
    mz_uint8 code_size = code_sizes_to_pack[i];
    if (!code_size) {
      TDEFL_RLE_PREV_CODE_SIZE();
      if (++rle_z_count == 138) {
        TDEFL_RLE_ZERO_CODE_SIZE();
      }
    } else {
      TDEFL_RLE_ZERO_CODE_SIZE();
      if (code_size != prev_code_size) {
        TDEFL_RLE_PREV_CODE_SIZE();
        d->m_huff_count[2][code_size] =
            (mz_uint16)(d->m_huff_count[2][code_size] + 1);
        packed_code_sizes[num_packed_code_sizes++] = code_size;
      } else if (++rle_repeat_count == 6) {
        TDEFL_RLE_PREV_CODE_SIZE();
      }
    }
    prev_code_size = code_size;
  }
  if (rle_repeat_count) {
    TDEFL_RLE_PREV_CODE_SIZE();
  } else {
    TDEFL_RLE_ZERO_CODE_SIZE();
  }

  tdefl_optimize_huffman_table(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_BITS(2, 2);

  TDEFL_PUT_BITS(num_lit_codes - 257, 5);
  TDEFL_PUT_BITS(num_dist_codes - 1, 5);

  for (num_bit_lengths = 18; num_bit_lengths >= 0; num_bit_lengths--)
    if (d->m_huff_code_sizes
            [2][s_tdefl_packed_code_size_syms_swizzle[num_bit_lengths]])
      break;
  num_bit_lengths = MZ_MAX(4, (num_bit_lengths + 1));
  TDEFL_PUT_BITS(num_bit_lengths - 4, 4);
  for (i = 0; (int)i < num_bit_lengths; i++)
    TDEFL_PUT_BITS(
        d->m_huff_code_sizes[2][s_tdefl_packed_code_size_syms_swizzle[i]], 3);

  for (packed_code_sizes_index = 0;
       packed_code_sizes_index < num_packed_code_sizes;) {
    mz_uint code = packed_code_sizes[packed_code_sizes_index++];
    MZ_ASSERT(code < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_BITS(d->m_huff_codes[2][code], d->m_huff_code_sizes[2][code]);
    if (code >= 16)
      TDEFL_PUT_BITS(packed_code_sizes[packed_code_sizes_index++],
                     "\02\03\07"[code - 16]);
  }
}

static void tdefl_start_static_block(tdefl_compressor *d) {
  mz_uint i;
  mz_uint8 *p = &d->m_huff_code_sizes[0][0];

  for (i = 0; i <= 143; ++i)
    *p++ = 8;
  for (; i <= 255; ++i)
    *p++ = 9;
  for (; i <= 279; ++i)
    *p++ = 7;
  for (; i <= 287; ++i)
    *p++ = 8;

  memset(d->m_huff_code_sizes[1], 5, 32);

  tdefl_optimize_huffman_table(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_table(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_BITS(1, 2);
}

static const mz_uint mz_bitmasks[17] = {
    0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF,
    0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF};

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN &&             \
    MINIZ_HAS_64BIT_REGISTERS
static mz_bool tdefl_compress_lz_codes(tdefl_compressor *d) {
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *pLZ_code_buf_end = d->m_pLZ_code_buf;
  mz_uint64 bit_buffer = d->m_bit_buffer;
  mz_uint bits_in = d->m_bits_in;

#define TDEFL_PUT_BITS_FAST(b, l)                                              \
  {                                                                            \
    bit_buffer |= (((mz_uint64)(b)) << bits_in);                               \
    bits_in += (l);                                                            \
  }

  flags = 1;
  for (pLZ_codes = d->m_lz_code_buf; pLZ_codes < pLZ_code_buf_end;
       flags >>= 1) {
    if (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    if (flags & 1) {
      mz_uint s0, s1, n0, n1, sym, num_extra_bits;
      mz_uint match_len = pLZ_codes[0];
      mz_uint match_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8));
      pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][s_tdefl_len_sym[match_len]],
                          d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS_FAST(match_len & mz_bitmasks[s_tdefl_len_extra[match_len]],
                          s_tdefl_len_extra[match_len]);

      /* This sequence coaxes MSVC into using cmov's vs. jmp's. */
      s0 = s_tdefl_small_dist_sym[match_dist & 511];
      n0 = s_tdefl_small_dist_extra[match_dist & 511];
      s1 = s_tdefl_large_dist_sym[match_dist >> 8];
      n1 = s_tdefl_large_dist_extra[match_dist >> 8];
      sym = (match_dist < 512) ? s0 : s1;
      num_extra_bits = (match_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[1][sym],
                          d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS_FAST(match_dist & mz_bitmasks[num_extra_bits],
                          num_extra_bits);
    } else {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit],
                          d->m_huff_code_sizes[0][lit]);

      if (((flags & 2) == 0) && (pLZ_codes < pLZ_code_buf_end)) {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
        TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit],
                            d->m_huff_code_sizes[0][lit]);

        if (((flags & 2) == 0) && (pLZ_codes < pLZ_code_buf_end)) {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
          TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit],
                              d->m_huff_code_sizes[0][lit]);
        }
      }
    }

    if (pOutput_buf >= d->m_pOutput_buf_end)
      return MZ_FALSE;

    memcpy(pOutput_buf, &bit_buffer, sizeof(mz_uint64));
    pOutput_buf += (bits_in >> 3);
    bit_buffer >>= (bits_in & ~7);
    bits_in &= 7;
  }

#undef TDEFL_PUT_BITS_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_bits_in = 0;
  d->m_bit_buffer = 0;

  while (bits_in) {
    mz_uint32 n = MZ_MIN(bits_in, 16);
    TDEFL_PUT_BITS((mz_uint)bit_buffer & mz_bitmasks[n], n);
    bit_buffer >>= n;
    bits_in -= n;
  }

  TDEFL_PUT_BITS(d->m_huff_codes[0][256], d->m_huff_code_sizes[0][256]);

  return (d->m_pOutput_buf < d->m_pOutput_buf_end);
}
#else
static mz_bool tdefl_compress_lz_codes(tdefl_compressor *d) {
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  for (pLZ_codes = d->m_lz_code_buf; pLZ_codes < d->m_pLZ_code_buf;
       flags >>= 1) {
    if (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    if (flags & 1) {
      mz_uint sym, num_extra_bits;
      mz_uint match_len = pLZ_codes[0],
              match_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8));
      pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS(d->m_huff_codes[0][s_tdefl_len_sym[match_len]],
                     d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS(match_len & mz_bitmasks[s_tdefl_len_extra[match_len]],
                     s_tdefl_len_extra[match_len]);

      if (match_dist < 512) {
        sym = s_tdefl_small_dist_sym[match_dist];
        num_extra_bits = s_tdefl_small_dist_extra[match_dist];
      } else {
        sym = s_tdefl_large_dist_sym[match_dist >> 8];
        num_extra_bits = s_tdefl_large_dist_extra[match_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS(d->m_huff_codes[1][sym], d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS(match_dist & mz_bitmasks[num_extra_bits], num_extra_bits);
    } else {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
      TDEFL_PUT_BITS(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);
    }
  }

  TDEFL_PUT_BITS(d->m_huff_codes[0][256], d->m_huff_code_sizes[0][256]);

  return (d->m_pOutput_buf < d->m_pOutput_buf_end);
}
#endif /* MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN &&       \
          MINIZ_HAS_64BIT_REGISTERS */

static mz_bool tdefl_compress_block(tdefl_compressor *d, mz_bool static_block) {
  if (static_block)
    tdefl_start_static_block(d);
  else
    tdefl_start_dynamic_block(d);
  return tdefl_compress_lz_codes(d);
}

static const mz_uint s_tdefl_num_probes[11] = {0,   1,   6,   32,  16,  32,
                                               128, 256, 512, 768, 1500};

static int tdefl_flush_block(tdefl_compressor *d, int flush) {
  mz_uint saved_bit_buf, saved_bits_in;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_block_succeeded = MZ_FALSE;
  int n, use_raw_block =
             ((d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS) != 0) &&
             (d->m_lookahead_pos - d->m_lz_code_buf_dict_pos) <= d->m_dict_size;
  mz_uint8 *pOutput_buf_start =
      ((d->m_pPut_buf_func == NULL) &&
       ((*d->m_pOut_buf_size - d->m_out_buf_ofs) >= TDEFL_OUT_BUF_SIZE))
          ? ((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs)
          : d->m_output_buf;

  d->m_pOutput_buf = pOutput_buf_start;
  d->m_pOutput_buf_end = d->m_pOutput_buf + TDEFL_OUT_BUF_SIZE - 16;

  MZ_ASSERT(!d->m_output_flush_remaining);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_remaining = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_num_flags_left);
  d->m_pLZ_code_buf -= (d->m_num_flags_left == 8);

  if ((d->m_flags & TDEFL_WRITE_ZLIB_HEADER) && (!d->m_block_index)) {
    const mz_uint8 cmf = 0x78;
    mz_uint8 flg, flevel = 3;
    mz_uint header, i, mz_un = sizeof(s_tdefl_num_probes) / sizeof(mz_uint);

    /* Determine compression level by reversing the process in
     * tdefl_create_comp_flags_from_zip_params() */
    for (i = 0; i < mz_un; i++)
      if (s_tdefl_num_probes[i] == (d->m_flags & 0xFFF))
        break;

    if (i < 2)
      flevel = 0;
    else if (i < 6)
      flevel = 1;
    else if (i == 6)
      flevel = 2;

    header = cmf << 8 | (flevel << 6);
    header += 31 - (header % 31);
    flg = header & 0xFF;

    TDEFL_PUT_BITS(cmf, 8);
    TDEFL_PUT_BITS(flg, 8);
  }

  TDEFL_PUT_BITS(flush == TDEFL_FINISH, 1);

  pSaved_output_buf = d->m_pOutput_buf;
  saved_bit_buf = d->m_bit_buffer;
  saved_bits_in = d->m_bits_in;

  if (!use_raw_block)
    comp_block_succeeded =
        tdefl_compress_block(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_BLOCKS) ||
                                    (d->m_total_lz_bytes < 48));

  /* If the block gets expanded, forget the current contents of the output
   * buffer and send a raw block instead. */
  if (((use_raw_block) ||
       ((d->m_total_lz_bytes) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >=
                                  d->m_total_lz_bytes))) &&
      ((d->m_lookahead_pos - d->m_lz_code_buf_dict_pos) <= d->m_dict_size)) {
    mz_uint i;
    d->m_pOutput_buf = pSaved_output_buf;
    d->m_bit_buffer = saved_bit_buf, d->m_bits_in = saved_bits_in;
    TDEFL_PUT_BITS(0, 2);
    if (d->m_bits_in) {
      TDEFL_PUT_BITS(0, 8 - d->m_bits_in);
    }
    for (i = 2; i; --i, d->m_total_lz_bytes ^= 0xFFFF) {
      TDEFL_PUT_BITS(d->m_total_lz_bytes & 0xFFFF, 16);
    }
    for (i = 0; i < d->m_total_lz_bytes; ++i) {
      TDEFL_PUT_BITS(
          d->m_dict[(d->m_lz_code_buf_dict_pos + i) & TDEFL_LZ_DICT_SIZE_MASK],
          8);
    }
  }
  /* Check for the extremely unlikely (if not impossible) case of the
     compressed block not fitting into the output buffer when using dynamic
     codes. */
  else if (!comp_block_succeeded) {
    d->m_pOutput_buf = pSaved_output_buf;
    d->m_bit_buffer = saved_bit_buf, d->m_bits_in = saved_bits_in;
    tdefl_compress_block(d, MZ_TRUE);
  }

  if (flush) {
    if (flush == TDEFL_FINISH) {
      if (d->m_bits_in) {
        TDEFL_PUT_BITS(0, 8 - d->m_bits_in);
      }
      if (d->m_flags & TDEFL_WRITE_ZLIB_HEADER) {
        mz_uint i, a = d->m_adler32;
        for (i = 0; i < 4; i++) {
          TDEFL_PUT_BITS((a >> 24) & 0xFF, 8);
          a <<= 8;
        }
      }
    } else {
      mz_uint i, z = 0;
      TDEFL_PUT_BITS(0, 3);
      if (d->m_bits_in) {
        TDEFL_PUT_BITS(0, 8 - d->m_bits_in);
      }
      for (i = 2; i; --i, z ^= 0xFFFF) {
        TDEFL_PUT_BITS(z & 0xFFFF, 16);
      }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_pOutput_buf_end);

  memset(&d->m_huff_count[0][0], 0,
         sizeof(d->m_huff_count[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_count[1][0], 0,
         sizeof(d->m_huff_count[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_pLZ_code_buf = d->m_lz_code_buf + 1;
  d->m_pLZ_flags = d->m_lz_code_buf;
  d->m_num_flags_left = 8;
  d->m_lz_code_buf_dict_pos += d->m_total_lz_bytes;
  d->m_total_lz_bytes = 0;
  d->m_block_index++;

  if ((n = (int)(d->m_pOutput_buf - pOutput_buf_start)) != 0) {
    if (d->m_pPut_buf_func) {
      *d->m_pIn_buf_size = d->m_pSrc - (const mz_uint8 *)d->m_pIn_buf;
      if (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        return (d->m_prev_return_status = TDEFL_STATUS_PUT_BUF_FAILED);
    } else if (pOutput_buf_start == d->m_output_buf) {
      int bytes_to_copy = (int)MZ_MIN(
          (size_t)n, (size_t)(*d->m_pOut_buf_size - d->m_out_buf_ofs));
      memcpy((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs, d->m_output_buf,
             bytes_to_copy);
      d->m_out_buf_ofs += bytes_to_copy;
      if ((n -= bytes_to_copy) != 0) {
        d->m_output_flush_ofs = bytes_to_copy;
        d->m_output_flush_remaining = n;
      }
    } else {
      d->m_out_buf_ofs += n;
    }
  }

  return d->m_output_flush_remaining;
}

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#ifdef MINIZ_UNALIGNED_USE_MEMCPY
static mz_uint16 TDEFL_READ_UNALIGNED_WORD(const mz_uint8 *p) {
  mz_uint16 ret;
  memcpy(&ret, p, sizeof(mz_uint16));
  return ret;
}
static mz_uint16 TDEFL_READ_UNALIGNED_WORD2(const mz_uint16 *p) {
  mz_uint16 ret;
  memcpy(&ret, p, sizeof(mz_uint16));
  return ret;
}
#else
#define TDEFL_READ_UNALIGNED_WORD(p) *(const mz_uint16 *)(p)
#define TDEFL_READ_UNALIGNED_WORD2(p) *(const mz_uint16 *)(p)
#endif
static MZ_FORCEINLINE void
tdefl_find_match(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist,
                 mz_uint max_match_len, mz_uint *pMatch_dist,
                 mz_uint *pMatch_len) {
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK,
                match_len = *pMatch_len, probe_pos = pos, next_probe_pos,
                probe_len;
  mz_uint num_probes_left = d->m_max_probes[match_len >= 32];
  const mz_uint16 *s = (const mz_uint16 *)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + match_len - 1]),
            s01 = TDEFL_READ_UNALIGNED_WORD2(s);
  MZ_ASSERT(max_match_len <= TDEFL_MAX_MATCH_LEN);
  if (max_match_len <= match_len)
    return;
  for (;;) {
    for (;;) {
      if (--num_probes_left == 0)
        return;
#define TDEFL_PROBE                                                            \
  next_probe_pos = d->m_next[probe_pos];                                       \
  if ((!next_probe_pos) ||                                                     \
      ((dist = (mz_uint16)(lookahead_pos - next_probe_pos)) > max_dist))       \
    return;                                                                    \
  probe_pos = next_probe_pos & TDEFL_LZ_DICT_SIZE_MASK;                        \
  if (TDEFL_READ_UNALIGNED_WORD(&d->m_dict[probe_pos + match_len - 1]) == c01) \
    break;
      TDEFL_PROBE;
      TDEFL_PROBE;
      TDEFL_PROBE;
    }
    if (!dist)
      break;
    q = (const mz_uint16 *)(d->m_dict + probe_pos);
    if (TDEFL_READ_UNALIGNED_WORD2(q) != s01)
      continue;
    p = s;
    probe_len = 32;
    do {
    } while (
        (TDEFL_READ_UNALIGNED_WORD2(++p) == TDEFL_READ_UNALIGNED_WORD2(++q)) &&
        (TDEFL_READ_UNALIGNED_WORD2(++p) == TDEFL_READ_UNALIGNED_WORD2(++q)) &&
        (TDEFL_READ_UNALIGNED_WORD2(++p) == TDEFL_READ_UNALIGNED_WORD2(++q)) &&
        (TDEFL_READ_UNALIGNED_WORD2(++p) == TDEFL_READ_UNALIGNED_WORD2(++q)) &&
        (--probe_len > 0));
    if (!probe_len) {
      *pMatch_dist = dist;
      *pMatch_len = MZ_MIN(max_match_len, (mz_uint)TDEFL_MAX_MATCH_LEN);
      break;
    } else if ((probe_len = ((mz_uint)(p - s) * 2) +
                            (mz_uint)(*(const mz_uint8 *)p ==
                                      *(const mz_uint8 *)q)) > match_len) {
      *pMatch_dist = dist;
      if ((*pMatch_len = match_len = MZ_MIN(max_match_len, probe_len)) ==
          max_match_len)
        break;
      c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + match_len - 1]);
    }
  }
}
#else
static MZ_FORCEINLINE void
tdefl_find_match(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist,
                 mz_uint max_match_len, mz_uint *pMatch_dist,
                 mz_uint *pMatch_len) {
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK,
                match_len = *pMatch_len, probe_pos = pos, next_probe_pos,
                probe_len;
  mz_uint num_probes_left = d->m_max_probes[match_len >= 32];
  const mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + match_len], c1 = d->m_dict[pos + match_len - 1];
  MZ_ASSERT(max_match_len <= TDEFL_MAX_MATCH_LEN);
  if (max_match_len <= match_len)
    return;
  for (;;) {
    for (;;) {
      if (--num_probes_left == 0)
        return;
#define TDEFL_PROBE                                                            \
  next_probe_pos = d->m_next[probe_pos];                                       \
  if ((!next_probe_pos) ||                                                     \
      ((dist = (mz_uint16)(lookahead_pos - next_probe_pos)) > max_dist))       \
    return;                                                                    \
  probe_pos = next_probe_pos & TDEFL_LZ_DICT_SIZE_MASK;                        \
  if ((d->m_dict[probe_pos + match_len] == c0) &&                              \
      (d->m_dict[probe_pos + match_len - 1] == c1))                            \
    break;
      TDEFL_PROBE;
      TDEFL_PROBE;
      TDEFL_PROBE;
    }
    if (!dist)
      break;
    p = s;
    q = d->m_dict + probe_pos;
    for (probe_len = 0; probe_len < max_match_len; probe_len++)
      if (*p++ != *q++)
        break;
    if (probe_len > match_len) {
      *pMatch_dist = dist;
      if ((*pMatch_len = match_len = probe_len) == max_match_len)
        return;
      c0 = d->m_dict[pos + match_len];
      c1 = d->m_dict[pos + match_len - 1];
    }
  }
}
#endif /* #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES */

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
#ifdef MINIZ_UNALIGNED_USE_MEMCPY
static mz_uint32 TDEFL_READ_UNALIGNED_WORD32(const mz_uint8 *p) {
  mz_uint32 ret;
  memcpy(&ret, p, sizeof(mz_uint32));
  return ret;
}
#else
#define TDEFL_READ_UNALIGNED_WORD32(p) *(const mz_uint32 *)(p)
#endif
static mz_bool tdefl_compress_fast(tdefl_compressor *d) {
  /* Faster, minimally featured LZRW1-style match+parse loop with better
   * register utilization. Intended for applications where raw throughput is
   * valued more highly than ratio. */
  mz_uint lookahead_pos = d->m_lookahead_pos,
          lookahead_size = d->m_lookahead_size, dict_size = d->m_dict_size,
          total_lz_bytes = d->m_total_lz_bytes,
          num_flags_left = d->m_num_flags_left;
  mz_uint8 *pLZ_code_buf = d->m_pLZ_code_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK;

  while ((d->m_src_buf_left) || ((d->m_flush) && (lookahead_size))) {
    const mz_uint TDEFL_COMP_FAST_LOOKAHEAD_SIZE = 4096;
    mz_uint dst_pos =
        (lookahead_pos + lookahead_size) & TDEFL_LZ_DICT_SIZE_MASK;
    mz_uint num_bytes_to_process = (mz_uint)MZ_MIN(
        d->m_src_buf_left, TDEFL_COMP_FAST_LOOKAHEAD_SIZE - lookahead_size);
    d->m_src_buf_left -= num_bytes_to_process;
    lookahead_size += num_bytes_to_process;

    while (num_bytes_to_process) {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_SIZE - dst_pos, num_bytes_to_process);
      memcpy(d->m_dict + dst_pos, d->m_pSrc, n);
      if (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
        memcpy(d->m_dict + TDEFL_LZ_DICT_SIZE + dst_pos, d->m_pSrc,
               MZ_MIN(n, (TDEFL_MAX_MATCH_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_SIZE_MASK;
      num_bytes_to_process -= n;
    }

    dict_size = MZ_MIN(TDEFL_LZ_DICT_SIZE - lookahead_size, dict_size);
    if ((!d->m_flush) && (lookahead_size < TDEFL_COMP_FAST_LOOKAHEAD_SIZE))
      break;

    while (lookahead_size >= 4) {
      mz_uint cur_match_dist, cur_match_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint first_trigram = TDEFL_READ_UNALIGNED_WORD32(pCur_dict) & 0xFFFFFF;
      mz_uint hash =
          (first_trigram ^ (first_trigram >> (24 - (TDEFL_LZ_HASH_BITS - 8)))) &
          TDEFL_LEVEL1_HASH_SIZE_MASK;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      if (((cur_match_dist = (mz_uint16)(lookahead_pos - probe_pos)) <=
           dict_size) &&
          ((TDEFL_READ_UNALIGNED_WORD32(
                d->m_dict + (probe_pos &= TDEFL_LZ_DICT_SIZE_MASK)) &
            0xFFFFFF) == first_trigram)) {
        const mz_uint16 *p = (const mz_uint16 *)pCur_dict;
        const mz_uint16 *q = (const mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        do {
        } while ((TDEFL_READ_UNALIGNED_WORD2(++p) ==
                  TDEFL_READ_UNALIGNED_WORD2(++q)) &&
                 (TDEFL_READ_UNALIGNED_WORD2(++p) ==
                  TDEFL_READ_UNALIGNED_WORD2(++q)) &&
                 (TDEFL_READ_UNALIGNED_WORD2(++p) ==
                  TDEFL_READ_UNALIGNED_WORD2(++q)) &&
                 (TDEFL_READ_UNALIGNED_WORD2(++p) ==
                  TDEFL_READ_UNALIGNED_WORD2(++q)) &&
                 (--probe_len > 0));
        cur_match_len = ((mz_uint)(p - (const mz_uint16 *)pCur_dict) * 2) +
                        (mz_uint)(*(const mz_uint8 *)p == *(const mz_uint8 *)q);
        if (!probe_len)
          cur_match_len = cur_match_dist ? TDEFL_MAX_MATCH_LEN : 0;

        if ((cur_match_len < TDEFL_MIN_MATCH_LEN) ||
            ((cur_match_len == TDEFL_MIN_MATCH_LEN) &&
             (cur_match_dist >= 8U * 1024U))) {
          cur_match_len = 1;
          *pLZ_code_buf++ = (mz_uint8)first_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_count[0][(mz_uint8)first_trigram]++;
        } else {
          mz_uint32 s0, s1;
          cur_match_len = MZ_MIN(cur_match_len, lookahead_size);

          MZ_ASSERT((cur_match_len >= TDEFL_MIN_MATCH_LEN) &&
                    (cur_match_dist >= 1) &&
                    (cur_match_dist <= TDEFL_LZ_DICT_SIZE));

          cur_match_dist--;

          pLZ_code_buf[0] = (mz_uint8)(cur_match_len - TDEFL_MIN_MATCH_LEN);
#ifdef MINIZ_UNALIGNED_USE_MEMCPY
          memcpy(&pLZ_code_buf[1], &cur_match_dist, sizeof(cur_match_dist));
#else
          *(mz_uint16 *)(&pLZ_code_buf[1]) = (mz_uint16)cur_match_dist;
#endif
          pLZ_code_buf += 3;
          *pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

          s0 = s_tdefl_small_dist_sym[cur_match_dist & 511];
          s1 = s_tdefl_large_dist_sym[cur_match_dist >> 8];
          d->m_huff_count[1][(cur_match_dist < 512) ? s0 : s1]++;

          d->m_huff_count[0][s_tdefl_len_sym[cur_match_len -
                                             TDEFL_MIN_MATCH_LEN]]++;
        }
      } else {
        *pLZ_code_buf++ = (mz_uint8)first_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_count[0][(mz_uint8)first_trigram]++;
      }

      if (--num_flags_left == 0) {
        num_flags_left = 8;
        pLZ_flags = pLZ_code_buf++;
      }

      total_lz_bytes += cur_match_len;
      lookahead_pos += cur_match_len;
      dict_size =
          MZ_MIN(dict_size + cur_match_len, (mz_uint)TDEFL_LZ_DICT_SIZE);
      cur_pos = (cur_pos + cur_match_len) & TDEFL_LZ_DICT_SIZE_MASK;
      MZ_ASSERT(lookahead_size >= cur_match_len);
      lookahead_size -= cur_match_len;

      if (pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8]) {
        int n;
        d->m_lookahead_pos = lookahead_pos;
        d->m_lookahead_size = lookahead_size;
        d->m_dict_size = dict_size;
        d->m_total_lz_bytes = total_lz_bytes;
        d->m_pLZ_code_buf = pLZ_code_buf;
        d->m_pLZ_flags = pLZ_flags;
        d->m_num_flags_left = num_flags_left;
        if ((n = tdefl_flush_block(d, 0)) != 0)
          return (n < 0) ? MZ_FALSE : MZ_TRUE;
        total_lz_bytes = d->m_total_lz_bytes;
        pLZ_code_buf = d->m_pLZ_code_buf;
        pLZ_flags = d->m_pLZ_flags;
        num_flags_left = d->m_num_flags_left;
      }
    }

    while (lookahead_size) {
      mz_uint8 lit = d->m_dict[cur_pos];

      total_lz_bytes++;
      *pLZ_code_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      if (--num_flags_left == 0) {
        num_flags_left = 8;
        pLZ_flags = pLZ_code_buf++;
      }

      d->m_huff_count[0][lit]++;

      lookahead_pos++;
      dict_size = MZ_MIN(dict_size + 1, (mz_uint)TDEFL_LZ_DICT_SIZE);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK;
      lookahead_size--;

      if (pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8]) {
        int n;
        d->m_lookahead_pos = lookahead_pos;
        d->m_lookahead_size = lookahead_size;
        d->m_dict_size = dict_size;
        d->m_total_lz_bytes = total_lz_bytes;
        d->m_pLZ_code_buf = pLZ_code_buf;
        d->m_pLZ_flags = pLZ_flags;
        d->m_num_flags_left = num_flags_left;
        if ((n = tdefl_flush_block(d, 0)) != 0)
          return (n < 0) ? MZ_FALSE : MZ_TRUE;
        total_lz_bytes = d->m_total_lz_bytes;
        pLZ_code_buf = d->m_pLZ_code_buf;
        pLZ_flags = d->m_pLZ_flags;
        num_flags_left = d->m_num_flags_left;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos;
  d->m_lookahead_size = lookahead_size;
  d->m_dict_size = dict_size;
  d->m_total_lz_bytes = total_lz_bytes;
  d->m_pLZ_code_buf = pLZ_code_buf;
  d->m_pLZ_flags = pLZ_flags;
  d->m_num_flags_left = num_flags_left;
  return MZ_TRUE;
}
#endif /* MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN */

static MZ_FORCEINLINE void tdefl_record_literal(tdefl_compressor *d,
                                                mz_uint8 lit) {
  d->m_total_lz_bytes++;
  *d->m_pLZ_code_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1);
  if (--d->m_num_flags_left == 0) {
    d->m_num_flags_left = 8;
    d->m_pLZ_flags = d->m_pLZ_code_buf++;
  }
  d->m_huff_count[0][lit]++;
}

static MZ_FORCEINLINE void
tdefl_record_match(tdefl_compressor *d, mz_uint match_len, mz_uint match_dist) {
  mz_uint32 s0, s1;

  MZ_ASSERT((match_len >= TDEFL_MIN_MATCH_LEN) && (match_dist >= 1) &&
            (match_dist <= TDEFL_LZ_DICT_SIZE));

  d->m_total_lz_bytes += match_len;

  d->m_pLZ_code_buf[0] = (mz_uint8)(match_len - TDEFL_MIN_MATCH_LEN);

  match_dist -= 1;
  d->m_pLZ_code_buf[1] = (mz_uint8)(match_dist & 0xFF);
  d->m_pLZ_code_buf[2] = (mz_uint8)(match_dist >> 8);
  d->m_pLZ_code_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80);
  if (--d->m_num_flags_left == 0) {
    d->m_num_flags_left = 8;
    d->m_pLZ_flags = d->m_pLZ_code_buf++;
  }

  s0 = s_tdefl_small_dist_sym[match_dist & 511];
  s1 = s_tdefl_large_dist_sym[(match_dist >> 8) & 127];
  d->m_huff_count[1][(match_dist < 512) ? s0 : s1]++;
  d->m_huff_count[0][s_tdefl_len_sym[match_len - TDEFL_MIN_MATCH_LEN]]++;
}

static mz_bool tdefl_compress_normal(tdefl_compressor *d) {
  const mz_uint8 *pSrc = d->m_pSrc;
  size_t src_buf_left = d->m_src_buf_left;
  tdefl_flush flush = d->m_flush;

  while ((src_buf_left) || ((flush) && (d->m_lookahead_size))) {
    mz_uint len_to_move, cur_match_dist, cur_match_len, cur_pos;
    /* Update dictionary and hash chains. Keeps the lookahead size equal to
     * TDEFL_MAX_MATCH_LEN. */
    if ((d->m_lookahead_size + d->m_dict_size) >= (TDEFL_MIN_MATCH_LEN - 1)) {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_size) &
                        TDEFL_LZ_DICT_SIZE_MASK,
              ins_pos = d->m_lookahead_pos + d->m_lookahead_size - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_SIZE_MASK]
                      << TDEFL_LZ_HASH_SHIFT) ^
                     d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK];
      mz_uint num_bytes_to_process = (mz_uint)MZ_MIN(
          src_buf_left, TDEFL_MAX_MATCH_LEN - d->m_lookahead_size);
      const mz_uint8 *pSrc_end = pSrc ? pSrc + num_bytes_to_process : NULL;
      src_buf_left -= num_bytes_to_process;
      d->m_lookahead_size += num_bytes_to_process;
      while (pSrc != pSrc_end) {
        mz_uint8 c = *pSrc++;
        d->m_dict[dst_pos] = c;
        if (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_SIZE + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_SHIFT) ^ c) & (TDEFL_LZ_HASH_SIZE - 1);
        d->m_next[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] = d->m_hash[hash];
        d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK;
        ins_pos++;
      }
    } else {
      while ((src_buf_left) && (d->m_lookahead_size < TDEFL_MAX_MATCH_LEN)) {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_size) &
                          TDEFL_LZ_DICT_SIZE_MASK;
        src_buf_left--;
        d->m_dict[dst_pos] = c;
        if (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_SIZE + dst_pos] = c;
        if ((++d->m_lookahead_size + d->m_dict_size) >= TDEFL_MIN_MATCH_LEN) {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_size - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_SIZE_MASK]
                           << (TDEFL_LZ_HASH_SHIFT * 2)) ^
                          (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK]
                           << TDEFL_LZ_HASH_SHIFT) ^
                          c) &
                         (TDEFL_LZ_HASH_SIZE - 1);
          d->m_next[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] = d->m_hash[hash];
          d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_size =
        MZ_MIN(TDEFL_LZ_DICT_SIZE - d->m_lookahead_size, d->m_dict_size);
    if ((!flush) && (d->m_lookahead_size < TDEFL_MAX_MATCH_LEN))
      break;

    /* Simple lazy/greedy parsing state machine. */
    len_to_move = 1;
    cur_match_dist = 0;
    cur_match_len =
        d->m_saved_match_len ? d->m_saved_match_len : (TDEFL_MIN_MATCH_LEN - 1);
    cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK;
    if (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_BLOCKS)) {
      if ((d->m_dict_size) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS))) {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_SIZE_MASK];
        cur_match_len = 0;
        while (cur_match_len < d->m_lookahead_size) {
          if (d->m_dict[cur_pos + cur_match_len] != c)
            break;
          cur_match_len++;
        }
        if (cur_match_len < TDEFL_MIN_MATCH_LEN)
          cur_match_len = 0;
        else
          cur_match_dist = 1;
      }
    } else {
      tdefl_find_match(d, d->m_lookahead_pos, d->m_dict_size,
                       d->m_lookahead_size, &cur_match_dist, &cur_match_len);
    }
    if (((cur_match_len == TDEFL_MIN_MATCH_LEN) &&
         (cur_match_dist >= 8U * 1024U)) ||
        (cur_pos == cur_match_dist) ||
        ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_match_len <= 5))) {
      cur_match_dist = cur_match_len = 0;
    }
    if (d->m_saved_match_len) {
      if (cur_match_len > d->m_saved_match_len) {
        tdefl_record_literal(d, (mz_uint8)d->m_saved_lit);
        if (cur_match_len >= 128) {
          tdefl_record_match(d, cur_match_len, cur_match_dist);
          d->m_saved_match_len = 0;
          len_to_move = cur_match_len;
        } else {
          d->m_saved_lit = d->m_dict[cur_pos];
          d->m_saved_match_dist = cur_match_dist;
          d->m_saved_match_len = cur_match_len;
        }
      } else {
        tdefl_record_match(d, d->m_saved_match_len, d->m_saved_match_dist);
        len_to_move = d->m_saved_match_len - 1;
        d->m_saved_match_len = 0;
      }
    } else if (!cur_match_dist)
      tdefl_record_literal(d,
                           d->m_dict[MZ_MIN(cur_pos, sizeof(d->m_dict) - 1)]);
    else if ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) ||
             (cur_match_len >= 128)) {
      tdefl_record_match(d, cur_match_len, cur_match_dist);
      len_to_move = cur_match_len;
    } else {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, sizeof(d->m_dict) - 1)];
      d->m_saved_match_dist = cur_match_dist;
      d->m_saved_match_len = cur_match_len;
    }
    /* Move the lookahead forward by len_to_move bytes. */
    d->m_lookahead_pos += len_to_move;
    MZ_ASSERT(d->m_lookahead_size >= len_to_move);
    d->m_lookahead_size -= len_to_move;
    d->m_dict_size =
        MZ_MIN(d->m_dict_size + len_to_move, (mz_uint)TDEFL_LZ_DICT_SIZE);
    /* Check if it's time to flush the current LZ codes to the internal output
     * buffer. */
    if ((d->m_pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8]) ||
        ((d->m_total_lz_bytes > 31 * 1024) &&
         (((((mz_uint)(d->m_pLZ_code_buf - d->m_lz_code_buf) * 115) >> 7) >=
           d->m_total_lz_bytes) ||
          (d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS)))) {
      int n;
      d->m_pSrc = pSrc;
      d->m_src_buf_left = src_buf_left;
      if ((n = tdefl_flush_block(d, 0)) != 0)
        return (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc;
  d->m_src_buf_left = src_buf_left;
  return MZ_TRUE;
}

static tdefl_status tdefl_flush_output_buffer(tdefl_compressor *d) {
  if (d->m_pIn_buf_size) {
    *d->m_pIn_buf_size = d->m_pSrc - (const mz_uint8 *)d->m_pIn_buf;
  }

  if (d->m_pOut_buf_size) {
    size_t n = MZ_MIN(*d->m_pOut_buf_size - d->m_out_buf_ofs,
                      d->m_output_flush_remaining);
    memcpy((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs,
           d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_remaining -= (mz_uint)n;
    d->m_out_buf_ofs += n;

    *d->m_pOut_buf_size = d->m_out_buf_ofs;
  }

  return (d->m_finished && !d->m_output_flush_remaining) ? TDEFL_STATUS_DONE
                                                         : TDEFL_STATUS_OKAY;
}

tdefl_status tdefl_compress(tdefl_compressor *d, const void *pIn_buf,
                            size_t *pIn_buf_size, void *pOut_buf,
                            size_t *pOut_buf_size, tdefl_flush flush) {
  if (!d) {
    if (pIn_buf_size)
      *pIn_buf_size = 0;
    if (pOut_buf_size)
      *pOut_buf_size = 0;
    return TDEFL_STATUS_BAD_PARAM;
  }

  d->m_pIn_buf = pIn_buf;
  d->m_pIn_buf_size = pIn_buf_size;
  d->m_pOut_buf = pOut_buf;
  d->m_pOut_buf_size = pOut_buf_size;
  d->m_pSrc = (const mz_uint8 *)(pIn_buf);
  d->m_src_buf_left = pIn_buf_size ? *pIn_buf_size : 0;
  d->m_out_buf_ofs = 0;
  d->m_flush = flush;

  if (((d->m_pPut_buf_func != NULL) ==
       ((pOut_buf != NULL) || (pOut_buf_size != NULL))) ||
      (d->m_prev_return_status != TDEFL_STATUS_OKAY) ||
      (d->m_wants_to_finish && (flush != TDEFL_FINISH)) ||
      (pIn_buf_size && *pIn_buf_size && !pIn_buf) ||
      (pOut_buf_size && *pOut_buf_size && !pOut_buf)) {
    if (pIn_buf_size)
      *pIn_buf_size = 0;
    if (pOut_buf_size)
      *pOut_buf_size = 0;
    return (d->m_prev_return_status = TDEFL_STATUS_BAD_PARAM);
  }
  d->m_wants_to_finish |= (flush == TDEFL_FINISH);

  if ((d->m_output_flush_remaining) || (d->m_finished))
    return (d->m_prev_return_status = tdefl_flush_output_buffer(d));

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  if (((d->m_flags & TDEFL_MAX_PROBES_MASK) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_BLOCKS |
                      TDEFL_RLE_MATCHES)) == 0)) {
    if (!tdefl_compress_fast(d))
      return d->m_prev_return_status;
  } else
#endif /* #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN */
  {
    if (!tdefl_compress_normal(d))
      return d->m_prev_return_status;
  }

  if ((d->m_flags & (TDEFL_WRITE_ZLIB_HEADER | TDEFL_COMPUTE_ADLER32)) &&
      (pIn_buf))
    d->m_adler32 =
        (mz_uint32)mz_adler32(d->m_adler32, (const mz_uint8 *)pIn_buf,
                              d->m_pSrc - (const mz_uint8 *)pIn_buf);

  if ((flush) && (!d->m_lookahead_size) && (!d->m_src_buf_left) &&
      (!d->m_output_flush_remaining)) {
    if (tdefl_flush_block(d, flush) < 0)
      return d->m_prev_return_status;
    d->m_finished = (flush == TDEFL_FINISH);
    if (flush == TDEFL_FULL_FLUSH) {
      MZ_CLEAR_ARR(d->m_hash);
      MZ_CLEAR_ARR(d->m_next);
      d->m_dict_size = 0;
    }
  }

  return (d->m_prev_return_status = tdefl_flush_output_buffer(d));
}

tdefl_status tdefl_compress_buffer(tdefl_compressor *d, const void *pIn_buf,
                                   size_t in_buf_size, tdefl_flush flush) {
  MZ_ASSERT(d->m_pPut_buf_func);
  return tdefl_compress(d, pIn_buf, &in_buf_size, NULL, NULL, flush);
}

tdefl_status tdefl_init(tdefl_compressor *d,
                        tdefl_put_buf_func_ptr pPut_buf_func,
                        void *pPut_buf_user, int flags) {
  d->m_pPut_buf_func = pPut_buf_func;
  d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags);
  d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3;
  d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  if (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG))
    MZ_CLEAR_ARR(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_size = d->m_dict_size =
      d->m_total_lz_bytes = d->m_lz_code_buf_dict_pos = d->m_bits_in = 0;
  d->m_output_flush_ofs = d->m_output_flush_remaining = d->m_finished =
      d->m_block_index = d->m_bit_buffer = d->m_wants_to_finish = 0;
  d->m_pLZ_code_buf = d->m_lz_code_buf + 1;
  d->m_pLZ_flags = d->m_lz_code_buf;
  *d->m_pLZ_flags = 0;
  d->m_num_flags_left = 8;
  d->m_pOutput_buf = d->m_output_buf;
  d->m_pOutput_buf_end = d->m_output_buf;
  d->m_prev_return_status = TDEFL_STATUS_OKAY;
  d->m_saved_match_dist = d->m_saved_match_len = d->m_saved_lit = 0;
  d->m_adler32 = 1;
  d->m_pIn_buf = NULL;
  d->m_pOut_buf = NULL;
  d->m_pIn_buf_size = NULL;
  d->m_pOut_buf_size = NULL;
  d->m_flush = TDEFL_NO_FLUSH;
  d->m_pSrc = NULL;
  d->m_src_buf_left = 0;
  d->m_out_buf_ofs = 0;
  if (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG))
    MZ_CLEAR_ARR(d->m_dict);
  memset(&d->m_huff_count[0][0], 0,
         sizeof(d->m_huff_count[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_count[1][0], 0,
         sizeof(d->m_huff_count[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  return TDEFL_STATUS_OKAY;
}

tdefl_status tdefl_get_prev_return_status(tdefl_compressor *d) {
  return d->m_prev_return_status;
}

mz_uint32 tdefl_get_adler32(tdefl_compressor *d) { return d->m_adler32; }

mz_bool tdefl_compress_mem_to_output(const void *pBuf, size_t buf_len,
                                     tdefl_put_buf_func_ptr pPut_buf_func,
                                     void *pPut_buf_user, int flags) {
  tdefl_compressor *pComp;
  mz_bool succeeded;
  if (((buf_len) && (!pBuf)) || (!pPut_buf_func))
    return MZ_FALSE;
  pComp = (tdefl_compressor *)MZ_MALLOC(sizeof(tdefl_compressor));
  if (!pComp)
    return MZ_FALSE;
  succeeded = (tdefl_init(pComp, pPut_buf_func, pPut_buf_user, flags) ==
               TDEFL_STATUS_OKAY);
  succeeded =
      succeeded && (tdefl_compress_buffer(pComp, pBuf, buf_len, TDEFL_FINISH) ==
                    TDEFL_STATUS_DONE);
  MZ_FREE(pComp);
  return succeeded;
}

typedef struct {
  size_t m_size, m_capacity;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_buffer;

static mz_bool tdefl_output_buffer_putter(const void *pBuf, int len,
                                          void *pUser) {
  tdefl_output_buffer *p = (tdefl_output_buffer *)pUser;
  size_t new_size = p->m_size + len;
  if (new_size > p->m_capacity) {
    size_t new_capacity = p->m_capacity;
    mz_uint8 *pNew_buf;
    if (!p->m_expandable)
      return MZ_FALSE;
    do {
      new_capacity = MZ_MAX(128U, new_capacity << 1U);
    } while (new_size > new_capacity);
    pNew_buf = (mz_uint8 *)MZ_REALLOC(p->m_pBuf, new_capacity);
    if (!pNew_buf)
      return MZ_FALSE;
    p->m_pBuf = pNew_buf;
    p->m_capacity = new_capacity;
  }
  memcpy((mz_uint8 *)p->m_pBuf + p->m_size, pBuf, len);
  p->m_size = new_size;
  return MZ_TRUE;
}

void *tdefl_compress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len,
                                 size_t *pOut_len, int flags) {
  tdefl_output_buffer out_buf;
  MZ_CLEAR_OBJ(out_buf);
  if (!pOut_len)
    return MZ_FALSE;
  else
    *pOut_len = 0;
  out_buf.m_expandable = MZ_TRUE;
  if (!tdefl_compress_mem_to_output(
          pSrc_buf, src_buf_len, tdefl_output_buffer_putter, &out_buf, flags))
    return NULL;
  *pOut_len = out_buf.m_size;
  return out_buf.m_pBuf;
}

size_t tdefl_compress_mem_to_mem(void *pOut_buf, size_t out_buf_len,
                                 const void *pSrc_buf, size_t src_buf_len,
                                 int flags) {
  tdefl_output_buffer out_buf;
  MZ_CLEAR_OBJ(out_buf);
  if (!pOut_buf)
    return 0;
  out_buf.m_pBuf = (mz_uint8 *)pOut_buf;
  out_buf.m_capacity = out_buf_len;
  if (!tdefl_compress_mem_to_output(
          pSrc_buf, src_buf_len, tdefl_output_buffer_putter, &out_buf, flags))
    return 0;
  return out_buf.m_size;
}

/* level may actually range from [0,10] (10 is a "hidden" max level, where we
 * want a bit more compression and it's fine if throughput to fall off a cliff
 * on some files). */
mz_uint tdefl_create_comp_flags_from_zip_params(int level, int window_bits,
                                                int strategy) {
  mz_uint comp_flags =
      s_tdefl_num_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] |
      ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  if (window_bits > 0)
    comp_flags |= TDEFL_WRITE_ZLIB_HEADER;

  if (!level)
    comp_flags |= TDEFL_FORCE_ALL_RAW_BLOCKS;
  else if (strategy == MZ_FILTERED)
    comp_flags |= TDEFL_FILTER_MATCHES;
  else if (strategy == MZ_HUFFMAN_ONLY)
    comp_flags &= ~TDEFL_MAX_PROBES_MASK;
  else if (strategy == MZ_FIXED)
    comp_flags |= TDEFL_FORCE_ALL_STATIC_BLOCKS;
  else if (strategy == MZ_RLE)
    comp_flags |= TDEFL_RLE_MATCHES;

  return comp_flags;
}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4204) /* nonstandard extension used : non-constant   \
                                   aggregate initializer (also supported by    \
                                   GNU C and C99, so no big deal) */
#endif

/* Simple PNG writer function by Alex Evans, 2011. Released into the public
 domain: https://gist.github.com/908299, more context at
 http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
 This is actually a modification of Alex's original code so PNG files
 generated by this function pass pngcheck. */
void *tdefl_write_image_to_png_file_in_memory_ex(const void *pImage, int w,
                                                 int h, int num_chans,
                                                 size_t *pLen_out,
                                                 mz_uint level, mz_bool flip) {
  /* Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was
   * defined. */
  static const mz_uint s_tdefl_png_num_probes[11] = {
      0, 1, 6, 32, 16, 32, 128, 256, 512, 768, 1500};
  tdefl_compressor *pComp =
      (tdefl_compressor *)MZ_MALLOC(sizeof(tdefl_compressor));
  tdefl_output_buffer out_buf;
  int i, bpl = w * num_chans, y, z;
  mz_uint32 c;
  *pLen_out = 0;
  if (!pComp)
    return NULL;
  MZ_CLEAR_OBJ(out_buf);
  out_buf.m_expandable = MZ_TRUE;
  out_buf.m_capacity = 57 + MZ_MAX(64, (1 + bpl) * h);
  if (NULL == (out_buf.m_pBuf = (mz_uint8 *)MZ_MALLOC(out_buf.m_capacity))) {
    MZ_FREE(pComp);
    return NULL;
  }
  /* write dummy header */
  for (z = 41; z; --z)
    tdefl_output_buffer_putter(&z, 1, &out_buf);
  /* compress image data */
  tdefl_init(pComp, tdefl_output_buffer_putter, &out_buf,
             s_tdefl_png_num_probes[MZ_MIN(10, level)] |
                 TDEFL_WRITE_ZLIB_HEADER);
  for (y = 0; y < h; ++y) {
    tdefl_compress_buffer(pComp, &z, 1, TDEFL_NO_FLUSH);
    tdefl_compress_buffer(pComp,
                          (mz_uint8 *)pImage + (flip ? (h - 1 - y) : y) * bpl,
                          bpl, TDEFL_NO_FLUSH);
  }
  if (tdefl_compress_buffer(pComp, NULL, 0, TDEFL_FINISH) !=
      TDEFL_STATUS_DONE) {
    MZ_FREE(pComp);
    MZ_FREE(out_buf.m_pBuf);
    return NULL;
  }
  /* write real header */
  *pLen_out = out_buf.m_size - 41;
  {
    static const mz_uint8 chans[] = {0x00, 0x00, 0x04, 0x02, 0x06};
    mz_uint8 pnghdr[41] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00,
                           0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                           0x00, 0x49, 0x44, 0x41, 0x54};
    pnghdr[18] = (mz_uint8)(w >> 8);
    pnghdr[19] = (mz_uint8)w;
    pnghdr[22] = (mz_uint8)(h >> 8);
    pnghdr[23] = (mz_uint8)h;
    pnghdr[25] = chans[num_chans];
    pnghdr[33] = (mz_uint8)(*pLen_out >> 24);
    pnghdr[34] = (mz_uint8)(*pLen_out >> 16);
    pnghdr[35] = (mz_uint8)(*pLen_out >> 8);
    pnghdr[36] = (mz_uint8)*pLen_out;
    c = (mz_uint32)mz_crc32(MZ_CRC32_INIT, pnghdr + 12, 17);
    for (i = 0; i < 4; ++i, c <<= 8)
      ((mz_uint8 *)(pnghdr + 29))[i] = (mz_uint8)(c >> 24);
    memcpy(out_buf.m_pBuf, pnghdr, 41);
  }
  /* write footer (IDAT CRC-32, followed by IEND chunk) */
  if (!tdefl_output_buffer_putter(
          "\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &out_buf)) {
    *pLen_out = 0;
    MZ_FREE(pComp);
    MZ_FREE(out_buf.m_pBuf);
    return NULL;
  }
  c = (mz_uint32)mz_crc32(MZ_CRC32_INIT, out_buf.m_pBuf + 41 - 4,
                          *pLen_out + 4);
  for (i = 0; i < 4; ++i, c <<= 8)
    (out_buf.m_pBuf + out_buf.m_size - 16)[i] = (mz_uint8)(c >> 24);
  /* compute final size of file, grab compressed data buffer and return */
  *pLen_out += 57;
  MZ_FREE(pComp);
  return out_buf.m_pBuf;
}
void *tdefl_write_image_to_png_file_in_memory(const void *pImage, int w, int h,
                                              int num_chans, size_t *pLen_out) {
  /* Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but
   * we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib
   * API's where #defined out) */
  return tdefl_write_image_to_png_file_in_memory_ex(pImage, w, h, num_chans,
                                                    pLen_out, 6, MZ_FALSE);
}

#ifndef MINIZ_NO_MALLOC
/* Allocate the tdefl_compressor and tinfl_decompressor structures in C so
 * that
 */
/* non-C language bindings to tdefL_ and tinfl_ API don't need to worry about
 */
/* structure size and allocation mechanism. */
tdefl_compressor *tdefl_compressor_alloc(void) {
  return (tdefl_compressor *)MZ_MALLOC(sizeof(tdefl_compressor));
}

void tdefl_compressor_free(tdefl_compressor *pComp) { MZ_FREE(pComp); }
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#ifdef __cplusplus
}
#endif

#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/
/**************************************************************************
 *
 * Copyright 2013-2014 RAD Game Tools and Valve Software
 * Copyright 2010-2014 Rich Geldreich and Tenacious Software LLC
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/

#ifndef MINIZ_NO_INFLATE_APIS

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------- Low-level Decompression (completely independent from
 * all compression API's) */

#define TINFL_MEMCPY(d, s, l) memcpy(d, s, l)
#define TINFL_MEMSET(p, c, l) memset(p, c, l)

#define TINFL_CR_BEGIN                                                         \
  switch (r->m_state) {                                                        \
  case 0:
#define TINFL_CR_RETURN(state_index, result)                                   \
  do {                                                                         \
    status = result;                                                           \
    r->m_state = state_index;                                                  \
    goto common_exit;                                                          \
  case state_index:;                                                           \
  }                                                                            \
  MZ_MACRO_END
#define TINFL_CR_RETURN_FOREVER(state_index, result)                           \
  do {                                                                         \
    for (;;) {                                                                 \
      TINFL_CR_RETURN(state_index, result);                                    \
    }                                                                          \
  }                                                                            \
  MZ_MACRO_END
#define TINFL_CR_FINISH }

#define TINFL_GET_BYTE(state_index, c)                                         \
  do {                                                                         \
    while (pIn_buf_cur >= pIn_buf_end) {                                       \
      TINFL_CR_RETURN(state_index,                                             \
                      (decomp_flags & TINFL_FLAG_HAS_MORE_INPUT)               \
                          ? TINFL_STATUS_NEEDS_MORE_INPUT                      \
                          : TINFL_STATUS_FAILED_CANNOT_MAKE_PROGRESS);         \
    }                                                                          \
    c = *pIn_buf_cur++;                                                        \
  }                                                                            \
  MZ_MACRO_END

#define TINFL_NEED_BITS(state_index, n)                                        \
  do {                                                                         \
    mz_uint c;                                                                 \
    TINFL_GET_BYTE(state_index, c);                                            \
    bit_buf |= (((tinfl_bit_buf_t)c) << num_bits);                             \
    num_bits += 8;                                                             \
  } while (num_bits < (mz_uint)(n))
#define TINFL_SKIP_BITS(state_index, n)                                        \
  do {                                                                         \
    if (num_bits < (mz_uint)(n)) {                                             \
      TINFL_NEED_BITS(state_index, n);                                         \
    }                                                                          \
    bit_buf >>= (n);                                                           \
    num_bits -= (n);                                                           \
  }                                                                            \
  MZ_MACRO_END
#define TINFL_GET_BITS(state_index, b, n)                                      \
  do {                                                                         \
    if (num_bits < (mz_uint)(n)) {                                             \
      TINFL_NEED_BITS(state_index, n);                                         \
    }                                                                          \
    b = bit_buf & ((1 << (n)) - 1);                                            \
    bit_buf >>= (n);                                                           \
    num_bits -= (n);                                                           \
  }                                                                            \
  MZ_MACRO_END

/* TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes
 * remaining in the input buffer falls below 2. */
/* It reads just enough bytes from the input stream that are needed to decode
 * the next Huffman code (and absolutely no more). It works by trying to fully
 * decode a */
/* Huffman code by using whatever bits are currently present in the bit buffer.
 * If this fails, it reads another byte, and tries again until it succeeds or
 * until the */
/* bit buffer contains >=15 bits (deflate's max. Huffman code size). */
#define TINFL_HUFF_BITBUF_FILL(state_index, pLookUp, pTree)                    \
  do {                                                                         \
    temp = pLookUp[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)];                    \
    if (temp >= 0) {                                                           \
      code_len = temp >> 9;                                                    \
      if ((code_len) && (num_bits >= code_len))                                \
        break;                                                                 \
    } else if (num_bits > TINFL_FAST_LOOKUP_BITS) {                            \
      code_len = TINFL_FAST_LOOKUP_BITS;                                       \
      do {                                                                     \
        temp = pTree[~temp + ((bit_buf >> code_len++) & 1)];                   \
      } while ((temp < 0) && (num_bits >= (code_len + 1)));                    \
      if (temp >= 0)                                                           \
        break;                                                                 \
    }                                                                          \
    TINFL_GET_BYTE(state_index, c);                                            \
    bit_buf |= (((tinfl_bit_buf_t)c) << num_bits);                             \
    num_bits += 8;                                                             \
  } while (num_bits < 15);

/* TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex
 * than you would initially expect because the zlib API expects the decompressor
 * to never read */
/* beyond the final byte of the deflate stream. (In other words, when this macro
 * wants to read another byte from the input, it REALLY needs another byte in
 * order to fully */
/* decode the next Huffman code.) Handling this properly is particularly
 * important on raw deflate (non-zlib) streams, which aren't followed by a byte
 * aligned adler-32. */
/* The slow path is only executed at the very end of the input buffer. */
/* v1.16: The original macro handled the case at the very end of the passed-in
 * input buffer, but we also need to handle the case where the user passes in
 * 1+zillion bytes */
/* following the deflate data and our non-conservative read-ahead path won't
 * kick in here on this code. This is much trickier. */
#define TINFL_HUFF_DECODE(state_index, sym, pLookUp, pTree)                    \
  do {                                                                         \
    int temp;                                                                  \
    mz_uint code_len, c;                                                       \
    if (num_bits < 15) {                                                       \
      if ((pIn_buf_end - pIn_buf_cur) < 2) {                                   \
        TINFL_HUFF_BITBUF_FILL(state_index, pLookUp, pTree);                   \
      } else {                                                                 \
        bit_buf |= (((tinfl_bit_buf_t)pIn_buf_cur[0]) << num_bits) |           \
                   (((tinfl_bit_buf_t)pIn_buf_cur[1]) << (num_bits + 8));      \
        pIn_buf_cur += 2;                                                      \
        num_bits += 16;                                                        \
      }                                                                        \
    }                                                                          \
    if ((temp = pLookUp[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >= 0)         \
      code_len = temp >> 9, temp &= 511;                                       \
    else {                                                                     \
      code_len = TINFL_FAST_LOOKUP_BITS;                                       \
      do {                                                                     \
        temp = pTree[~temp + ((bit_buf >> code_len++) & 1)];                   \
      } while (temp < 0);                                                      \
    }                                                                          \
    sym = temp;                                                                \
    bit_buf >>= code_len;                                                      \
    num_bits -= code_len;                                                      \
  }                                                                            \
  MZ_MACRO_END

static void tinfl_clear_tree(tinfl_decompressor *r) {
  if (r->m_type == 0)
    MZ_CLEAR_ARR(r->m_tree_0);
  else if (r->m_type == 1)
    MZ_CLEAR_ARR(r->m_tree_1);
  else
    MZ_CLEAR_ARR(r->m_tree_2);
}

tinfl_status tinfl_decompress(tinfl_decompressor *r,
                              const mz_uint8 *pIn_buf_next,
                              size_t *pIn_buf_size, mz_uint8 *pOut_buf_start,
                              mz_uint8 *pOut_buf_next, size_t *pOut_buf_size,
                              const mz_uint32 decomp_flags) {
  static const mz_uint16 s_length_base[31] = {
      3,  4,  5,  6,  7,  8,  9,  10,  11,  13,  15,  17,  19,  23, 27, 31,
      35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0,  0};
  static const mz_uint8 s_length_extra[31] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
                                              1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4,
                                              4, 4, 5, 5, 5, 5, 0, 0, 0};
  static const mz_uint16 s_dist_base[32] = {
      1,    2,    3,    4,    5,    7,     9,     13,    17,  25,   33,
      49,   65,   97,   129,  193,  257,   385,   513,   769, 1025, 1537,
      2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577, 0,   0};
  static const mz_uint8 s_dist_extra[32] = {
      0, 0, 0, 0, 1, 1, 2, 2,  3,  3,  4,  4,  5,  5,  6,
      6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};
  static const mz_uint8 s_length_dezigzag[19] = {
      16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
  static const mz_uint16 s_min_table_sizes[3] = {257, 1, 4};

  mz_int16 *pTrees[3];
  mz_uint8 *pCode_sizes[3];

  tinfl_status status = TINFL_STATUS_FAILED;
  mz_uint32 num_bits, dist, counter, num_extra;
  tinfl_bit_buf_t bit_buf;
  const mz_uint8 *pIn_buf_cur = pIn_buf_next, *const pIn_buf_end =
                                                  pIn_buf_next + *pIn_buf_size;
  mz_uint8 *pOut_buf_cur = pOut_buf_next, *const pOut_buf_end =
                                              pOut_buf_next ? pOut_buf_next +
                                                                  *pOut_buf_size
                                                            : NULL;
  size_t out_buf_size_mask =
             (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)
                 ? (size_t)-1
                 : ((pOut_buf_next - pOut_buf_start) + *pOut_buf_size) - 1,
         dist_from_out_buf_start;

  /* Ensure the output buffer's size is a power of 2, unless the output buffer
   * is large enough to hold the entire output file (in which case it doesn't
   * matter). */
  if (((out_buf_size_mask + 1) & out_buf_size_mask) ||
      (pOut_buf_next < pOut_buf_start)) {
    *pIn_buf_size = *pOut_buf_size = 0;
    return TINFL_STATUS_BAD_PARAM;
  }

  pTrees[0] = r->m_tree_0;
  pTrees[1] = r->m_tree_1;
  pTrees[2] = r->m_tree_2;
  pCode_sizes[0] = r->m_code_size_0;
  pCode_sizes[1] = r->m_code_size_1;
  pCode_sizes[2] = r->m_code_size_2;

  num_bits = r->m_num_bits;
  bit_buf = r->m_bit_buf;
  dist = r->m_dist;
  counter = r->m_counter;
  num_extra = r->m_num_extra;
  dist_from_out_buf_start = r->m_dist_from_out_buf_start;
  TINFL_CR_BEGIN

  bit_buf = num_bits = dist = counter = num_extra = r->m_zhdr0 = r->m_zhdr1 = 0;
  r->m_z_adler32 = r->m_check_adler32 = 1;
  if (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER) {
    TINFL_GET_BYTE(1, r->m_zhdr0);
    TINFL_GET_BYTE(2, r->m_zhdr1);
    counter = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) ||
               (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    if (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
      counter |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) ||
                  ((out_buf_size_mask + 1) <
                   (size_t)((size_t)1 << (8U + (r->m_zhdr0 >> 4)))));
    if (counter) {
      TINFL_CR_RETURN_FOREVER(36, TINFL_STATUS_FAILED);
    }
  }

  do {
    TINFL_GET_BITS(3, r->m_final, 3);
    r->m_type = r->m_final >> 1;
    if (r->m_type == 0) {
      TINFL_SKIP_BITS(5, num_bits & 7);
      for (counter = 0; counter < 4; ++counter) {
        if (num_bits)
          TINFL_GET_BITS(6, r->m_raw_header[counter], 8);
        else
          TINFL_GET_BYTE(7, r->m_raw_header[counter]);
      }
      if ((counter = (r->m_raw_header[0] | (r->m_raw_header[1] << 8))) !=
          (mz_uint)(0xFFFF ^
                    (r->m_raw_header[2] | (r->m_raw_header[3] << 8)))) {
        TINFL_CR_RETURN_FOREVER(39, TINFL_STATUS_FAILED);
      }
      while ((counter) && (num_bits)) {
        TINFL_GET_BITS(51, dist, 8);
        while (pOut_buf_cur >= pOut_buf_end) {
          TINFL_CR_RETURN(52, TINFL_STATUS_HAS_MORE_OUTPUT);
        }
        *pOut_buf_cur++ = (mz_uint8)dist;
        counter--;
      }
      while (counter) {
        size_t n;
        while (pOut_buf_cur >= pOut_buf_end) {
          TINFL_CR_RETURN(9, TINFL_STATUS_HAS_MORE_OUTPUT);
        }
        while (pIn_buf_cur >= pIn_buf_end) {
          TINFL_CR_RETURN(38, (decomp_flags & TINFL_FLAG_HAS_MORE_INPUT)
                                  ? TINFL_STATUS_NEEDS_MORE_INPUT
                                  : TINFL_STATUS_FAILED_CANNOT_MAKE_PROGRESS);
        }
        n = MZ_MIN(MZ_MIN((size_t)(pOut_buf_end - pOut_buf_cur),
                          (size_t)(pIn_buf_end - pIn_buf_cur)),
                   counter);
        TINFL_MEMCPY(pOut_buf_cur, pIn_buf_cur, n);
        pIn_buf_cur += n;
        pOut_buf_cur += n;
        counter -= (mz_uint)n;
      }
    } else if (r->m_type == 3) {
      TINFL_CR_RETURN_FOREVER(10, TINFL_STATUS_FAILED);
    } else {
      if (r->m_type == 1) {
        mz_uint8 *p = r->m_code_size_0;
        mz_uint i;
        r->m_table_sizes[0] = 288;
        r->m_table_sizes[1] = 32;
        TINFL_MEMSET(r->m_code_size_1, 5, 32);
        for (i = 0; i <= 143; ++i)
          *p++ = 8;
        for (; i <= 255; ++i)
          *p++ = 9;
        for (; i <= 279; ++i)
          *p++ = 7;
        for (; i <= 287; ++i)
          *p++ = 8;
      } else {
        for (counter = 0; counter < 3; counter++) {
          TINFL_GET_BITS(11, r->m_table_sizes[counter], "\05\05\04"[counter]);
          r->m_table_sizes[counter] += s_min_table_sizes[counter];
        }
        MZ_CLEAR_ARR(r->m_code_size_2);
        for (counter = 0; counter < r->m_table_sizes[2]; counter++) {
          mz_uint s;
          TINFL_GET_BITS(14, s, 3);
          r->m_code_size_2[s_length_dezigzag[counter]] = (mz_uint8)s;
        }
        r->m_table_sizes[2] = 19;
      }
      for (; (int)r->m_type >= 0; r->m_type--) {
        int tree_next, tree_cur;
        mz_int16 *pLookUp;
        mz_int16 *pTree;
        mz_uint8 *pCode_size;
        mz_uint i, j, used_syms, total, sym_index, next_code[17],
            total_syms[16];
        pLookUp = r->m_look_up[r->m_type];
        pTree = pTrees[r->m_type];
        pCode_size = pCode_sizes[r->m_type];
        MZ_CLEAR_ARR(total_syms);
        TINFL_MEMSET(pLookUp, 0, sizeof(r->m_look_up[0]));
        tinfl_clear_tree(r);
        for (i = 0; i < r->m_table_sizes[r->m_type]; ++i)
          total_syms[pCode_size[i]]++;
        used_syms = 0, total = 0;
        next_code[0] = next_code[1] = 0;
        for (i = 1; i <= 15; ++i) {
          used_syms += total_syms[i];
          next_code[i + 1] = (total = ((total + total_syms[i]) << 1));
        }
        if ((65536 != total) && (used_syms > 1)) {
          TINFL_CR_RETURN_FOREVER(35, TINFL_STATUS_FAILED);
        }
        for (tree_next = -1, sym_index = 0;
             sym_index < r->m_table_sizes[r->m_type]; ++sym_index) {
          mz_uint rev_code = 0, l, cur_code, code_size = pCode_size[sym_index];
          if (!code_size)
            continue;
          cur_code = next_code[code_size]++;
          for (l = code_size; l > 0; l--, cur_code >>= 1)
            rev_code = (rev_code << 1) | (cur_code & 1);
          if (code_size <= TINFL_FAST_LOOKUP_BITS) {
            mz_int16 k = (mz_int16)((code_size << 9) | sym_index);
            while (rev_code < TINFL_FAST_LOOKUP_SIZE) {
              pLookUp[rev_code] = k;
              rev_code += (1 << code_size);
            }
            continue;
          }
          if (0 ==
              (tree_cur = pLookUp[rev_code & (TINFL_FAST_LOOKUP_SIZE - 1)])) {
            pLookUp[rev_code & (TINFL_FAST_LOOKUP_SIZE - 1)] =
                (mz_int16)tree_next;
            tree_cur = tree_next;
            tree_next -= 2;
          }
          rev_code >>= (TINFL_FAST_LOOKUP_BITS - 1);
          for (j = code_size; j > (TINFL_FAST_LOOKUP_BITS + 1); j--) {
            tree_cur -= ((rev_code >>= 1) & 1);
            if (!pTree[-tree_cur - 1]) {
              pTree[-tree_cur - 1] = (mz_int16)tree_next;
              tree_cur = tree_next;
              tree_next -= 2;
            } else
              tree_cur = pTree[-tree_cur - 1];
          }
          tree_cur -= ((rev_code >>= 1) & 1);
          pTree[-tree_cur - 1] = (mz_int16)sym_index;
        }
        if (r->m_type == 2) {
          for (counter = 0;
               counter < (r->m_table_sizes[0] + r->m_table_sizes[1]);) {
            mz_uint s;
            TINFL_HUFF_DECODE(16, dist, r->m_look_up[2], r->m_tree_2);
            if (dist < 16) {
              r->m_len_codes[counter++] = (mz_uint8)dist;
              continue;
            }
            if ((dist == 16) && (!counter)) {
              TINFL_CR_RETURN_FOREVER(17, TINFL_STATUS_FAILED);
            }
            num_extra = "\02\03\07"[dist - 16];
            TINFL_GET_BITS(18, s, num_extra);
            s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + counter,
                         (dist == 16) ? r->m_len_codes[counter - 1] : 0, s);
            counter += s;
          }
          if ((r->m_table_sizes[0] + r->m_table_sizes[1]) != counter) {
            TINFL_CR_RETURN_FOREVER(21, TINFL_STATUS_FAILED);
          }
          TINFL_MEMCPY(r->m_code_size_0, r->m_len_codes, r->m_table_sizes[0]);
          TINFL_MEMCPY(r->m_code_size_1, r->m_len_codes + r->m_table_sizes[0],
                       r->m_table_sizes[1]);
        }
      }
      for (;;) {
        mz_uint8 *pSrc;
        for (;;) {
          if (((pIn_buf_end - pIn_buf_cur) < 4) ||
              ((pOut_buf_end - pOut_buf_cur) < 2)) {
            TINFL_HUFF_DECODE(23, counter, r->m_look_up[0], r->m_tree_0);
            if (counter >= 256)
              break;
            while (pOut_buf_cur >= pOut_buf_end) {
              TINFL_CR_RETURN(24, TINFL_STATUS_HAS_MORE_OUTPUT);
            }
            *pOut_buf_cur++ = (mz_uint8)counter;
          } else {
            int sym2;
            mz_uint code_len;
#if TINFL_USE_64BIT_BITBUF
            if (num_bits < 30) {
              bit_buf |=
                  (((tinfl_bit_buf_t)MZ_READ_LE32(pIn_buf_cur)) << num_bits);
              pIn_buf_cur += 4;
              num_bits += 32;
            }
#else
            if (num_bits < 15) {
              bit_buf |=
                  (((tinfl_bit_buf_t)MZ_READ_LE16(pIn_buf_cur)) << num_bits);
              pIn_buf_cur += 2;
              num_bits += 16;
            }
#endif
            if ((sym2 =
                     r->m_look_up[0][bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >=
                0)
              code_len = sym2 >> 9;
            else {
              code_len = TINFL_FAST_LOOKUP_BITS;
              do {
                sym2 = r->m_tree_0[~sym2 + ((bit_buf >> code_len++) & 1)];
              } while (sym2 < 0);
            }
            counter = sym2;
            bit_buf >>= code_len;
            num_bits -= code_len;
            if (counter & 256)
              break;

#if !TINFL_USE_64BIT_BITBUF
            if (num_bits < 15) {
              bit_buf |=
                  (((tinfl_bit_buf_t)MZ_READ_LE16(pIn_buf_cur)) << num_bits);
              pIn_buf_cur += 2;
              num_bits += 16;
            }
#endif
            if ((sym2 =
                     r->m_look_up[0][bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >=
                0)
              code_len = sym2 >> 9;
            else {
              code_len = TINFL_FAST_LOOKUP_BITS;
              do {
                sym2 = r->m_tree_0[~sym2 + ((bit_buf >> code_len++) & 1)];
              } while (sym2 < 0);
            }
            bit_buf >>= code_len;
            num_bits -= code_len;

            pOut_buf_cur[0] = (mz_uint8)counter;
            if (sym2 & 256) {
              pOut_buf_cur++;
              counter = sym2;
              break;
            }
            pOut_buf_cur[1] = (mz_uint8)sym2;
            pOut_buf_cur += 2;
          }
        }
        if ((counter &= 511) == 256)
          break;

        num_extra = s_length_extra[counter - 257];
        counter = s_length_base[counter - 257];
        if (num_extra) {
          mz_uint extra_bits;
          TINFL_GET_BITS(25, extra_bits, num_extra);
          counter += extra_bits;
        }

        TINFL_HUFF_DECODE(26, dist, r->m_look_up[1], r->m_tree_1);
        num_extra = s_dist_extra[dist];
        dist = s_dist_base[dist];
        if (num_extra) {
          mz_uint extra_bits;
          TINFL_GET_BITS(27, extra_bits, num_extra);
          dist += extra_bits;
        }

        dist_from_out_buf_start = pOut_buf_cur - pOut_buf_start;
        if ((dist == 0 || dist > dist_from_out_buf_start ||
             dist_from_out_buf_start == 0) &&
            (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) {
          TINFL_CR_RETURN_FOREVER(37, TINFL_STATUS_FAILED);
        }

        pSrc = pOut_buf_start +
               ((dist_from_out_buf_start - dist) & out_buf_size_mask);

        if ((MZ_MAX(pOut_buf_cur, pSrc) + counter) > pOut_buf_end) {
          while (counter--) {
            while (pOut_buf_cur >= pOut_buf_end) {
              TINFL_CR_RETURN(53, TINFL_STATUS_HAS_MORE_OUTPUT);
            }
            *pOut_buf_cur++ =
                pOut_buf_start[(dist_from_out_buf_start++ - dist) &
                               out_buf_size_mask];
          }
          continue;
        }
#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        else if ((counter >= 9) && (counter <= dist)) {
          const mz_uint8 *pSrc_end = pSrc + (counter & ~7);
          do {
#ifdef MINIZ_UNALIGNED_USE_MEMCPY
            memcpy(pOut_buf_cur, pSrc, sizeof(mz_uint32) * 2);
#else
            ((mz_uint32 *)pOut_buf_cur)[0] = ((const mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)pOut_buf_cur)[1] = ((const mz_uint32 *)pSrc)[1];
#endif
            pOut_buf_cur += 8;
          } while ((pSrc += 8) < pSrc_end);
          if ((counter &= 7) < 3) {
            if (counter) {
              pOut_buf_cur[0] = pSrc[0];
              if (counter > 1)
                pOut_buf_cur[1] = pSrc[1];
              pOut_buf_cur += counter;
            }
            continue;
          }
        }
#endif
        while (counter > 2) {
          pOut_buf_cur[0] = pSrc[0];
          pOut_buf_cur[1] = pSrc[1];
          pOut_buf_cur[2] = pSrc[2];
          pOut_buf_cur += 3;
          pSrc += 3;
          counter -= 3;
        }
        if (counter > 0) {
          pOut_buf_cur[0] = pSrc[0];
          if (counter > 1)
            pOut_buf_cur[1] = pSrc[1];
          pOut_buf_cur += counter;
        }
      }
    }
  } while (!(r->m_final & 1));

  /* Ensure byte alignment and put back any bytes from the bitbuf if we've
   * looked ahead too far on gzip, or other Deflate streams followed by
   * arbitrary data. */
  /* I'm being super conservative here. A number of simplifications can be
   * made to the byte alignment part, and the Adler32 check shouldn't ever
   * need to worry about reading from the bitbuf now. */
  TINFL_SKIP_BITS(32, num_bits & 7);
  while ((pIn_buf_cur > pIn_buf_next) && (num_bits >= 8)) {
    --pIn_buf_cur;
    num_bits -= 8;
  }
  bit_buf &= ~(~(tinfl_bit_buf_t)0 << num_bits);
  MZ_ASSERT(!num_bits); /* if this assert fires then we've read beyond the end
                           of non-deflate/zlib streams with following data
                           (such as gzip streams). */

  if (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER) {
    for (counter = 0; counter < 4; ++counter) {
      mz_uint s;
      if (num_bits)
        TINFL_GET_BITS(41, s, 8);
      else
        TINFL_GET_BYTE(42, s);
      r->m_z_adler32 = (r->m_z_adler32 << 8) | s;
    }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_STATUS_DONE);

  TINFL_CR_FINISH

common_exit:
  /* As long as we aren't telling the caller that we NEED more input to make
   * forward progress: */
  /* Put back any bytes from the bitbuf in case we've looked ahead too far on
   * gzip, or other Deflate streams followed by arbitrary data. */
  /* We need to be very careful here to NOT push back any bytes we definitely
   * know we need to make forward progress, though, or we'll lock the caller
   * up into an inf loop. */
  if ((status != TINFL_STATUS_NEEDS_MORE_INPUT) &&
      (status != TINFL_STATUS_FAILED_CANNOT_MAKE_PROGRESS)) {
    while ((pIn_buf_cur > pIn_buf_next) && (num_bits >= 8)) {
      --pIn_buf_cur;
      num_bits -= 8;
    }
  }
  r->m_num_bits = num_bits;
  r->m_bit_buf = bit_buf & ~(~(tinfl_bit_buf_t)0 << num_bits);
  r->m_dist = dist;
  r->m_counter = counter;
  r->m_num_extra = num_extra;
  r->m_dist_from_out_buf_start = dist_from_out_buf_start;
  *pIn_buf_size = pIn_buf_cur - pIn_buf_next;
  *pOut_buf_size = pOut_buf_cur - pOut_buf_next;
  if ((decomp_flags &
       (TINFL_FLAG_PARSE_ZLIB_HEADER | TINFL_FLAG_COMPUTE_ADLER32)) &&
      (status >= 0)) {
    const mz_uint8 *ptr = pOut_buf_next;
    size_t buf_len = *pOut_buf_size;
    mz_uint32 i, s1 = r->m_check_adler32 & 0xffff,
                 s2 = r->m_check_adler32 >> 16;
    size_t block_len = buf_len % 5552;
    while (buf_len) {
      for (i = 0; i + 7 < block_len; i += 8, ptr += 8) {
        s1 += ptr[0], s2 += s1;
        s1 += ptr[1], s2 += s1;
        s1 += ptr[2], s2 += s1;
        s1 += ptr[3], s2 += s1;
        s1 += ptr[4], s2 += s1;
        s1 += ptr[5], s2 += s1;
        s1 += ptr[6], s2 += s1;
        s1 += ptr[7], s2 += s1;
      }
      for (; i < block_len; ++i)
        s1 += *ptr++, s2 += s1;
      s1 %= 65521U, s2 %= 65521U;
      buf_len -= block_len;
      block_len = 5552;
    }
    r->m_check_adler32 = (s2 << 16) + s1;
    if ((status == TINFL_STATUS_DONE) &&
        (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER) &&
        (r->m_check_adler32 != r->m_z_adler32))
      status = TINFL_STATUS_ADLER32_MISMATCH;
  }
  return status;
}

/* Higher level helper functions. */
void *tinfl_decompress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len,
                                   size_t *pOut_len, int flags) {
  tinfl_decompressor decomp;
  void *pBuf = NULL, *pNew_buf;
  size_t src_buf_ofs = 0, out_buf_capacity = 0;
  *pOut_len = 0;
  tinfl_init(&decomp);
  for (;;) {
    size_t src_buf_size = src_buf_len - src_buf_ofs,
           dst_buf_size = out_buf_capacity - *pOut_len, new_out_buf_capacity;
    tinfl_status status = tinfl_decompress(
        &decomp, (const mz_uint8 *)pSrc_buf + src_buf_ofs, &src_buf_size,
        (mz_uint8 *)pBuf, pBuf ? (mz_uint8 *)pBuf + *pOut_len : NULL,
        &dst_buf_size,
        (flags & ~TINFL_FLAG_HAS_MORE_INPUT) |
            TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    if ((status < 0) || (status == TINFL_STATUS_NEEDS_MORE_INPUT)) {
      MZ_FREE(pBuf);
      *pOut_len = 0;
      return NULL;
    }
    src_buf_ofs += src_buf_size;
    *pOut_len += dst_buf_size;
    if (status == TINFL_STATUS_DONE)
      break;
    new_out_buf_capacity = out_buf_capacity * 2;
    if (new_out_buf_capacity < 128)
      new_out_buf_capacity = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_out_buf_capacity);
    if (!pNew_buf) {
      MZ_FREE(pBuf);
      *pOut_len = 0;
      return NULL;
    }
    pBuf = pNew_buf;
    out_buf_capacity = new_out_buf_capacity;
  }
  return pBuf;
}

size_t tinfl_decompress_mem_to_mem(void *pOut_buf, size_t out_buf_len,
                                   const void *pSrc_buf, size_t src_buf_len,
                                   int flags) {
  tinfl_decompressor decomp;
  tinfl_status status;
  tinfl_init(&decomp);
  status =
      tinfl_decompress(&decomp, (const mz_uint8 *)pSrc_buf, &src_buf_len,
                       (mz_uint8 *)pOut_buf, (mz_uint8 *)pOut_buf, &out_buf_len,
                       (flags & ~TINFL_FLAG_HAS_MORE_INPUT) |
                           TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  return (status != TINFL_STATUS_DONE) ? TINFL_DECOMPRESS_MEM_TO_MEM_FAILED
                                       : out_buf_len;
}

int tinfl_decompress_mem_to_callback(const void *pIn_buf, size_t *pIn_buf_size,
                                     tinfl_put_buf_func_ptr pPut_buf_func,
                                     void *pPut_buf_user, int flags) {
  int result = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8 *)MZ_MALLOC(TINFL_LZ_DICT_SIZE);
  size_t in_buf_ofs = 0, dict_ofs = 0;
  if (!pDict)
    return TINFL_STATUS_FAILED;
  memset(pDict, 0, TINFL_LZ_DICT_SIZE);
  tinfl_init(&decomp);
  for (;;) {
    size_t in_buf_size = *pIn_buf_size - in_buf_ofs,
           dst_buf_size = TINFL_LZ_DICT_SIZE - dict_ofs;
    tinfl_status status =
        tinfl_decompress(&decomp, (const mz_uint8 *)pIn_buf + in_buf_ofs,
                         &in_buf_size, pDict, pDict + dict_ofs, &dst_buf_size,
                         (flags & ~(TINFL_FLAG_HAS_MORE_INPUT |
                                    TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    in_buf_ofs += in_buf_size;
    if ((dst_buf_size) &&
        (!(*pPut_buf_func)(pDict + dict_ofs, (int)dst_buf_size, pPut_buf_user)))
      break;
    if (status != TINFL_STATUS_HAS_MORE_OUTPUT) {
      result = (status == TINFL_STATUS_DONE);
      break;
    }
    dict_ofs = (dict_ofs + dst_buf_size) & (TINFL_LZ_DICT_SIZE - 1);
  }
  MZ_FREE(pDict);
  *pIn_buf_size = in_buf_ofs;
  return result;
}

#ifndef MINIZ_NO_MALLOC
tinfl_decompressor *tinfl_decompressor_alloc(void) {
  tinfl_decompressor *pDecomp =
      (tinfl_decompressor *)MZ_MALLOC(sizeof(tinfl_decompressor));
  if (pDecomp)
    tinfl_init(pDecomp);
  return pDecomp;
}

void tinfl_decompressor_free(tinfl_decompressor *pDecomp) { MZ_FREE(pDecomp); }
#endif

#ifdef __cplusplus
}
#endif

#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/
/**************************************************************************
 *
 * Copyright 2013-2014 RAD Game Tools and Valve Software
 * Copyright 2010-2014 Rich Geldreich and Tenacious Software LLC
 * Copyright 2016 Martin Raiber
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/

#ifndef MINIZ_NO_ARCHIVE_APIS

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------- .ZIP archive reading */

#ifdef MINIZ_NO_STDIO
#define MZ_FILE void *
#else
#include <sys/stat.h>

#if defined(_MSC_VER) || defined(__MINGW64__) || defined(__MINGW32__)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef __cplusplus
#define MICROSOFT_WINDOWS_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS 0
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

static WCHAR *mz_utf8z_to_widechar(const char *str) {
  int reqChars = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
  WCHAR *wStr = (WCHAR *)malloc(reqChars * sizeof(WCHAR));
  MultiByteToWideChar(CP_UTF8, 0, str, -1, wStr, reqChars);
  return wStr;
}

static FILE *mz_fopen(const char *pFilename, const char *pMode) {
  WCHAR *wFilename = mz_utf8z_to_widechar(pFilename);
  WCHAR *wMode = mz_utf8z_to_widechar(pMode);
  FILE *pFile = NULL;
#ifdef ZIP_ENABLE_SHARABLE_FILE_OPEN
  pFile = _wfopen(wFilename, wMode);
#else
  errno_t err = _wfopen_s(&pFile, wFilename, wMode);
#endif
  free(wFilename);
  free(wMode);
#ifdef ZIP_ENABLE_SHARABLE_FILE_OPEN
  return pFile;
#else
  return err ? NULL : pFile;
#endif
}

static FILE *mz_freopen(const char *pPath, const char *pMode, FILE *pStream) {
  WCHAR *wPath = mz_utf8z_to_widechar(pPath);
  WCHAR *wMode = mz_utf8z_to_widechar(pMode);
  FILE *pFile = NULL;
#ifdef ZIP_ENABLE_SHARABLE_FILE_OPEN
  pFile = _wfreopen(wPath, wMode, pStream);
#else
  errno_t err = _wfreopen_s(&pFile, wPath, wMode, pStream);
#endif
  free(wPath);
  free(wMode);
#ifdef ZIP_ENABLE_SHARABLE_FILE_OPEN
  return pFile;
#else
  return err ? NULL : pFile;
#endif
}

#if defined(__MINGW32__)
static int mz_stat(const char *path, struct _stat *buffer) {
  WCHAR *wPath = mz_utf8z_to_widechar(path);
  int res = _wstat(wPath, buffer);
  free(wPath);
  return res;
}
#else
static int mz_stat64(const char *path, struct __stat64 *buffer) {
  WCHAR *wPath = mz_utf8z_to_widechar(path);
  int res = _wstat64(wPath, buffer);
  free(wPath);
  return res;
}
#endif

static int mz_mkdir(const char *pDirname) {
  WCHAR *wDirname = mz_utf8z_to_widechar(pDirname);
  int res = _wmkdir(wDirname);
  free(wDirname);
  return res;
}

#ifndef MINIZ_NO_TIME
#include <sys/utime.h>
#endif
#define MZ_FOPEN mz_fopen
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 _ftelli64
#define MZ_FSEEK64 _fseeki64
#if defined(__MINGW32__)
#define MZ_FILE_STAT_STRUCT _stat
#define MZ_FILE_STAT mz_stat
#else
#define MZ_FILE_STAT_STRUCT _stat64
#define MZ_FILE_STAT mz_stat64
#endif
#define MZ_FFLUSH fflush
#define MZ_FREOPEN mz_freopen
#define MZ_DELETE_FILE remove
#define MZ_MKDIR(d) mz_mkdir(d)

#elif defined(__MINGW32__) || defined(__WATCOMC__)
#ifndef MINIZ_NO_TIME
#include <sys/utime.h>
#endif
#define MZ_FOPEN(f, m) fopen(f, m)
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 _ftelli64
#define MZ_FSEEK64 _fseeki64
#define MZ_FILE_STAT_STRUCT stat
#define MZ_FILE_STAT stat
#define MZ_FFLUSH fflush
#define MZ_FREOPEN(f, m, s) freopen(f, m, s)
#define MZ_DELETE_FILE remove
#define MZ_MKDIR(d) _mkdir(d)

#elif defined(__TINYC__)
#ifndef MINIZ_NO_TIME
#include <sys/utime.h>
#endif
#define MZ_FOPEN(f, m) fopen(f, m)
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 ftell
#define MZ_FSEEK64 fseek
#define MZ_FILE_STAT_STRUCT stat
#define MZ_FILE_STAT stat
#define MZ_FFLUSH fflush
#define MZ_FREOPEN(f, m, s) freopen(f, m, s)
#define MZ_DELETE_FILE remove
#if defined(_WIN32) || defined(_WIN64)
#define MZ_MKDIR(d) _mkdir(d)
#else
#define MZ_MKDIR(d) mkdir(d, 0755)
#endif

#elif defined(__USE_LARGEFILE64) /* gcc, clang */
#ifndef MINIZ_NO_TIME
#include <utime.h>
#endif
#define MZ_FOPEN(f, m) fopen64(f, m)
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 ftello64
#define MZ_FSEEK64 fseeko64
#define MZ_FILE_STAT_STRUCT stat64
#define MZ_FILE_STAT stat64
#define MZ_FFLUSH fflush
#define MZ_FREOPEN(p, m, s) freopen64(p, m, s)
#define MZ_DELETE_FILE remove
#define MZ_MKDIR(d) mkdir(d, 0755)

#elif defined(__APPLE__) || defined(__FreeBSD__) ||                            \
    (defined(__linux__) && defined(__x86_64__))
#ifndef MINIZ_NO_TIME
#include <utime.h>
#endif
#define MZ_FOPEN(f, m) fopen(f, m)
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 ftello
#define MZ_FSEEK64 fseeko
#define MZ_FILE_STAT_STRUCT stat
#define MZ_FILE_STAT stat
#define MZ_FFLUSH fflush
#define MZ_FREOPEN(p, m, s) freopen(p, m, s)
#define MZ_DELETE_FILE remove
#define MZ_MKDIR(d) mkdir(d, 0755)

#else
#pragma message(                                                               \
    "Using fopen, ftello, fseeko, stat() etc. path for file I/O - this path may not support large files.")
#ifndef MINIZ_NO_TIME
#include <utime.h>
#endif
#define MZ_FOPEN(f, m) fopen(f, m)
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#ifdef __STRICT_ANSI__
#define MZ_FTELL64 ftell
#define MZ_FSEEK64 fseek
#else
#define MZ_FTELL64 ftello
#define MZ_FSEEK64 fseeko
#endif
#define MZ_FILE_STAT_STRUCT stat
#define MZ_FILE_STAT stat
#define MZ_FFLUSH fflush
#define MZ_FREOPEN(f, m, s) freopen(f, m, s)
#define MZ_DELETE_FILE remove
#define MZ_MKDIR(d) mkdir(d, 0755)
#endif /* #ifdef _MSC_VER */
#endif /* #ifdef MINIZ_NO_STDIO */

#ifndef CHMOD
// Upon successful completion, a value of 0 is returned.
// Otherwise, a value of -1 is returned and errno is set to indicate the error.
// int chmod(const char *path, mode_t mode);
#define CHMOD(f, m) chmod(f, m)
#endif

#define MZ_TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

/* Various ZIP archive enums. To completely avoid cross platform compiler
 * alignment and platform endian issues, miniz.c doesn't use structs for any
 * of this stuff. */
enum {
  /* ZIP archive identifiers and record sizes */
  MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG = 0x06054b50,
  MZ_ZIP_CENTRAL_DIR_HEADER_SIG = 0x02014b50,
  MZ_ZIP_LOCAL_DIR_HEADER_SIG = 0x04034b50,
  MZ_ZIP_LOCAL_DIR_HEADER_SIZE = 30,
  MZ_ZIP_CENTRAL_DIR_HEADER_SIZE = 46,
  MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE = 22,

  /* ZIP64 archive identifier and record sizes */
  MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIG = 0x06064b50,
  MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIG = 0x07064b50,
  MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE = 56,
  MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIZE = 20,
  MZ_ZIP64_EXTENDED_INFORMATION_FIELD_HEADER_ID = 0x0001,
  MZ_ZIP_DATA_DESCRIPTOR_ID = 0x08074b50,
  MZ_ZIP_DATA_DESCRIPTER_SIZE64 = 24,
  MZ_ZIP_DATA_DESCRIPTER_SIZE32 = 16,

  /* Central directory header record offsets */
  MZ_ZIP_CDH_SIG_OFS = 0,
  MZ_ZIP_CDH_VERSION_MADE_BY_OFS = 4,
  MZ_ZIP_CDH_VERSION_NEEDED_OFS = 6,
  MZ_ZIP_CDH_BIT_FLAG_OFS = 8,
  MZ_ZIP_CDH_METHOD_OFS = 10,
  MZ_ZIP_CDH_FILE_TIME_OFS = 12,
  MZ_ZIP_CDH_FILE_DATE_OFS = 14,
  MZ_ZIP_CDH_CRC32_OFS = 16,
  MZ_ZIP_CDH_COMPRESSED_SIZE_OFS = 20,
  MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS = 24,
  MZ_ZIP_CDH_FILENAME_LEN_OFS = 28,
  MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
  MZ_ZIP_CDH_COMMENT_LEN_OFS = 32,
  MZ_ZIP_CDH_DISK_START_OFS = 34,
  MZ_ZIP_CDH_INTERNAL_ATTR_OFS = 36,
  MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38,
  MZ_ZIP_CDH_LOCAL_HEADER_OFS = 42,

  /* Local directory header offsets */
  MZ_ZIP_LDH_SIG_OFS = 0,
  MZ_ZIP_LDH_VERSION_NEEDED_OFS = 4,
  MZ_ZIP_LDH_BIT_FLAG_OFS = 6,
  MZ_ZIP_LDH_METHOD_OFS = 8,
  MZ_ZIP_LDH_FILE_TIME_OFS = 10,
  MZ_ZIP_LDH_FILE_DATE_OFS = 12,
  MZ_ZIP_LDH_CRC32_OFS = 14,
  MZ_ZIP_LDH_COMPRESSED_SIZE_OFS = 18,
  MZ_ZIP_LDH_DECOMPRESSED_SIZE_OFS = 22,
  MZ_ZIP_LDH_FILENAME_LEN_OFS = 26,
  MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
  MZ_ZIP_LDH_BIT_FLAG_HAS_LOCATOR = 1 << 3,

  /* End of central directory offsets */
  MZ_ZIP_ECDH_SIG_OFS = 0,
  MZ_ZIP_ECDH_NUM_THIS_DISK_OFS = 4,
  MZ_ZIP_ECDH_NUM_DISK_CDIR_OFS = 6,
  MZ_ZIP_ECDH_CDIR_NUM_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS = 10,
  MZ_ZIP_ECDH_CDIR_SIZE_OFS = 12,
  MZ_ZIP_ECDH_CDIR_OFS_OFS = 16,
  MZ_ZIP_ECDH_COMMENT_SIZE_OFS = 20,

  /* ZIP64 End of central directory locator offsets */
  MZ_ZIP64_ECDL_SIG_OFS = 0,                    /* 4 bytes */
  MZ_ZIP64_ECDL_NUM_DISK_CDIR_OFS = 4,          /* 4 bytes */
  MZ_ZIP64_ECDL_REL_OFS_TO_ZIP64_ECDR_OFS = 8,  /* 8 bytes */
  MZ_ZIP64_ECDL_TOTAL_NUMBER_OF_DISKS_OFS = 16, /* 4 bytes */

  /* ZIP64 End of central directory header offsets */
  MZ_ZIP64_ECDH_SIG_OFS = 0,                       /* 4 bytes */
  MZ_ZIP64_ECDH_SIZE_OF_RECORD_OFS = 4,            /* 8 bytes */
  MZ_ZIP64_ECDH_VERSION_MADE_BY_OFS = 12,          /* 2 bytes */
  MZ_ZIP64_ECDH_VERSION_NEEDED_OFS = 14,           /* 2 bytes */
  MZ_ZIP64_ECDH_NUM_THIS_DISK_OFS = 16,            /* 4 bytes */
  MZ_ZIP64_ECDH_NUM_DISK_CDIR_OFS = 20,            /* 4 bytes */
  MZ_ZIP64_ECDH_CDIR_NUM_ENTRIES_ON_DISK_OFS = 24, /* 8 bytes */
  MZ_ZIP64_ECDH_CDIR_TOTAL_ENTRIES_OFS = 32,       /* 8 bytes */
  MZ_ZIP64_ECDH_CDIR_SIZE_OFS = 40,                /* 8 bytes */
  MZ_ZIP64_ECDH_CDIR_OFS_OFS = 48,                 /* 8 bytes */
  MZ_ZIP_VERSION_MADE_BY_DOS_FILESYSTEM_ID = 0,
  MZ_ZIP_DOS_DIR_ATTRIBUTE_BITFLAG = 0x10,
  MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_IS_ENCRYPTED = 1,
  MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_COMPRESSED_PATCH_FLAG = 32,
  MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_USES_STRONG_ENCRYPTION = 64,
  MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_LOCAL_DIR_IS_MASKED = 8192,
  MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_UTF8 = 1 << 11
};

typedef struct {
  void *m_p;
  size_t m_size, m_capacity;
  mz_uint m_element_size;
} mz_zip_array;

struct mz_zip_internal_state_tag {
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;

  /* The flags passed in when the archive is initially opened. */
  mz_uint32 m_init_flags;

  /* MZ_TRUE if the archive has a zip64 end of central directory headers, etc.
   */
  mz_bool m_zip64;

  /* MZ_TRUE if we found zip64 extended info in the central directory (m_zip64
   * will also be slammed to true too, even if we didn't find a zip64 end of
   * central dir header, etc.) */
  mz_bool m_zip64_has_extended_info_fields;

  /* These fields are used by the file, FILE, memory, and memory/heap
   * read/write helpers. */
  MZ_FILE *m_pFile;
  mz_uint64 m_file_archive_start_ofs;

  void *m_pMem;
  size_t m_mem_size;
  size_t m_mem_capacity;
};

#define MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(array_ptr, element_size)                 \
  (array_ptr)->m_element_size = element_size

#if defined(DEBUG) || defined(_DEBUG)
static MZ_FORCEINLINE mz_uint
mz_zip_array_range_check(const mz_zip_array *pArray, mz_uint index) {
  MZ_ASSERT(index < pArray->m_size);
  return index;
}
#define MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, index)                   \
  ((element_type *)((array_ptr)                                                \
                        ->m_p))[mz_zip_array_range_check(array_ptr, index)]
#else
#define MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, index)                   \
  ((element_type *)((array_ptr)->m_p))[index]
#endif

static MZ_FORCEINLINE void mz_zip_array_init(mz_zip_array *pArray,
                                             mz_uint32 element_size) {
  memset(pArray, 0, sizeof(mz_zip_array));
  pArray->m_element_size = element_size;
}

static MZ_FORCEINLINE void mz_zip_array_clear(mz_zip_archive *pZip,
                                              mz_zip_array *pArray) {
  pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
  memset(pArray, 0, sizeof(mz_zip_array));
}

static mz_bool mz_zip_array_ensure_capacity(mz_zip_archive *pZip,
                                            mz_zip_array *pArray,
                                            size_t min_new_capacity,
                                            mz_uint growing) {
  void *pNew_p;
  size_t new_capacity = min_new_capacity;
  MZ_ASSERT(pArray->m_element_size);
  if (pArray->m_capacity >= min_new_capacity)
    return MZ_TRUE;
  if (growing) {
    new_capacity = MZ_MAX(1, pArray->m_capacity);
    while (new_capacity < min_new_capacity)
      new_capacity *= 2;
  }
  if (NULL == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p,
                                         pArray->m_element_size, new_capacity)))
    return MZ_FALSE;
  pArray->m_p = pNew_p;
  pArray->m_capacity = new_capacity;
  return MZ_TRUE;
}

static MZ_FORCEINLINE mz_bool mz_zip_array_reserve(mz_zip_archive *pZip,
                                                   mz_zip_array *pArray,
                                                   size_t new_capacity,
                                                   mz_uint growing) {
  if (new_capacity > pArray->m_capacity) {
    if (!mz_zip_array_ensure_capacity(pZip, pArray, new_capacity, growing))
      return MZ_FALSE;
  }
  return MZ_TRUE;
}

static MZ_FORCEINLINE mz_bool mz_zip_array_resize(mz_zip_archive *pZip,
                                                  mz_zip_array *pArray,
                                                  size_t new_size,
                                                  mz_uint growing) {
  if (new_size > pArray->m_capacity) {
    if (!mz_zip_array_ensure_capacity(pZip, pArray, new_size, growing))
      return MZ_FALSE;
  }
  pArray->m_size = new_size;
  return MZ_TRUE;
}

static MZ_FORCEINLINE mz_bool mz_zip_array_ensure_room(mz_zip_archive *pZip,
                                                       mz_zip_array *pArray,
                                                       size_t n) {
  return mz_zip_array_reserve(pZip, pArray, pArray->m_size + n, MZ_TRUE);
}

static MZ_FORCEINLINE mz_bool mz_zip_array_push_back(mz_zip_archive *pZip,
                                                     mz_zip_array *pArray,
                                                     const void *pElements,
                                                     size_t n) {
  size_t orig_size = pArray->m_size;
  if (!mz_zip_array_resize(pZip, pArray, orig_size + n, MZ_TRUE))
    return MZ_FALSE;
  if (n > 0)
    memcpy((mz_uint8 *)pArray->m_p + orig_size * pArray->m_element_size,
           pElements, n * pArray->m_element_size);
  return MZ_TRUE;
}

#ifndef MINIZ_NO_TIME
static MZ_TIME_T mz_zip_dos_to_time_t(int dos_time, int dos_date) {
  struct tm tm;
  memset(&tm, 0, sizeof(tm));
  tm.tm_isdst = -1;
  tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900;
  tm.tm_mon = ((dos_date >> 5) & 15) - 1;
  tm.tm_mday = dos_date & 31;
  tm.tm_hour = (dos_time >> 11) & 31;
  tm.tm_min = (dos_time >> 5) & 63;
  tm.tm_sec = (dos_time << 1) & 62;
  return mktime(&tm);
}

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS
static void mz_zip_time_t_to_dos_time(MZ_TIME_T time, mz_uint16 *pDOS_time,
                                      mz_uint16 *pDOS_date) {
#ifdef _MSC_VER
  struct tm tm_struct;
  struct tm *tm = &tm_struct;
  errno_t err = localtime_s(tm, &time);
  if (err) {
    *pDOS_date = 0;
    *pDOS_time = 0;
    return;
  }
#else
  struct tm *tm = localtime(&time);
#endif /* #ifdef _MSC_VER */

  *pDOS_time = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) +
                           ((tm->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) +
                           ((tm->tm_mon + 1) << 5) + tm->tm_mday);
}
#endif /* MINIZ_NO_ARCHIVE_WRITING_APIS */

#ifndef MINIZ_NO_STDIO
#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS
static mz_bool mz_zip_get_file_modified_time(const char *pFilename,
                                             MZ_TIME_T *pTime) {
  struct MZ_FILE_STAT_STRUCT file_stat;

  /* On Linux with x86 glibc, this call will fail on large files (I think >=
   * 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh. */
  if (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    return MZ_FALSE;

  *pTime = file_stat.st_mtime;

  return MZ_TRUE;
}
#endif /* #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS*/

static mz_bool mz_zip_set_file_times(const char *pFilename,
                                     MZ_TIME_T access_time,
                                     MZ_TIME_T modified_time) {
  struct utimbuf t;

  memset(&t, 0, sizeof(t));
  t.actime = access_time;
  t.modtime = modified_time;

  return !utime(pFilename, &t);
}
#endif /* #ifndef MINIZ_NO_STDIO */
#endif /* #ifndef MINIZ_NO_TIME */

static MZ_FORCEINLINE mz_bool mz_zip_set_error(mz_zip_archive *pZip,
                                               mz_zip_error err_num) {
  if (pZip)
    pZip->m_last_error = err_num;
  return MZ_FALSE;
}

static mz_bool mz_zip_reader_init_internal(mz_zip_archive *pZip,
                                           mz_uint flags) {
  (void)flags;
  if ((!pZip) || (pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_INVALID))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  if (!pZip->m_pAlloc)
    pZip->m_pAlloc = miniz_def_alloc_func;
  if (!pZip->m_pFree)
    pZip->m_pFree = miniz_def_free_func;
  if (!pZip->m_pRealloc)
    pZip->m_pRealloc = miniz_def_realloc_func;

  pZip->m_archive_size = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_total_files = 0;
  pZip->m_last_error = MZ_ZIP_NO_ERROR;

  if (NULL == (pZip->m_pState = (mz_zip_internal_state *)pZip->m_pAlloc(
                   pZip->m_pAlloc_opaque, 1, sizeof(mz_zip_internal_state))))
    return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);

  memset(pZip->m_pState, 0, sizeof(mz_zip_internal_state));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir,
                                sizeof(mz_uint8));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir_offsets,
                                sizeof(mz_uint32));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_sorted_central_dir_offsets,
                                sizeof(mz_uint32));
  pZip->m_pState->m_init_flags = flags;
  pZip->m_pState->m_zip64 = MZ_FALSE;
  pZip->m_pState->m_zip64_has_extended_info_fields = MZ_FALSE;

  pZip->m_zip_mode = MZ_ZIP_MODE_READING;

  return MZ_TRUE;
}

static MZ_FORCEINLINE mz_bool
mz_zip_reader_filename_less(const mz_zip_array *pCentral_dir_array,
                            const mz_zip_array *pCentral_dir_offsets,
                            mz_uint l_index, mz_uint r_index) {
  const mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(
                     pCentral_dir_array, mz_uint8,
                     MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32,
                                          l_index)),
                 *pE;
  const mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(
      pCentral_dir_array, mz_uint8,
      MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_index));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS),
          r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
  pR += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
  pE = pL + MZ_MIN(l_len, r_len);
  while (pL < pE) {
    if ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      break;
    pL++;
    pR++;
  }
  return (pL == pE) ? (l_len < r_len) : (l < r);
}

#define MZ_SWAP_UINT32(a, b)                                                   \
  do {                                                                         \
    mz_uint32 t = a;                                                           \
    a = b;                                                                     \
    b = t;                                                                     \
  }                                                                            \
  MZ_MACRO_END

/* Heap sort of lowercased filenames, used to help accelerate plain central
 * directory searches by mz_zip_reader_locate_file(). (Could also use qsort(),
 * but it could allocate memory.) */
static void
mz_zip_reader_sort_central_dir_offsets_by_filename(mz_zip_archive *pZip) {
  mz_zip_internal_state *pState = pZip->m_pState;
  const mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  const mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices;
  mz_uint32 start, end;
  const mz_uint32 size = pZip->m_total_files;

  if (size <= 1U)
    return;

  pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets,
                                   mz_uint32, 0);

  start = (size - 2U) >> 1U;
  for (;;) {
    mz_uint64 child, root = start;
    for (;;) {
      if ((child = (root << 1U) + 1U) >= size)
        break;
      child += (((child + 1U) < size) &&
                (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets,
                                             pIndices[child],
                                             pIndices[child + 1U])));
      if (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets,
                                       pIndices[root], pIndices[child]))
        break;
      MZ_SWAP_UINT32(pIndices[root], pIndices[child]);
      root = child;
    }
    if (!start)
      break;
    start--;
  }

  end = size - 1;
  while (end > 0) {
    mz_uint64 child, root = 0;
    MZ_SWAP_UINT32(pIndices[end], pIndices[0]);
    for (;;) {
      if ((child = (root << 1U) + 1U) >= end)
        break;
      child +=
          (((child + 1U) < end) &&
           mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets,
                                       pIndices[child], pIndices[child + 1U]));
      if (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets,
                                       pIndices[root], pIndices[child]))
        break;
      MZ_SWAP_UINT32(pIndices[root], pIndices[child]);
      root = child;
    }
    end--;
  }
}

static mz_bool mz_zip_reader_locate_header_sig(mz_zip_archive *pZip,
                                               mz_uint32 record_sig,
                                               mz_uint32 record_size,
                                               mz_int64 *pOfs) {
  mz_int64 cur_file_ofs;
  mz_uint32 buf_u32[4096 / sizeof(mz_uint32)];
  mz_uint8 *pBuf = (mz_uint8 *)buf_u32;

  /* Basic sanity checks - reject files which are too small */
  if (pZip->m_archive_size < record_size)
    return MZ_FALSE;

  /* Find the record by scanning the file from the end towards the beginning.
   */
  cur_file_ofs =
      MZ_MAX((mz_int64)pZip->m_archive_size - (mz_int64)sizeof(buf_u32), 0);
  for (;;) {
    int i,
        n = (int)MZ_MIN(sizeof(buf_u32), pZip->m_archive_size - cur_file_ofs);

    if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      return MZ_FALSE;

    for (i = n - 4; i >= 0; --i) {
      mz_uint s = MZ_READ_LE32(pBuf + i);
      if (s == record_sig) {
        if ((pZip->m_archive_size - (cur_file_ofs + i)) >= record_size)
          break;
      }
    }

    if (i >= 0) {
      cur_file_ofs += i;
      break;
    }

    /* Give up if we've searched the entire file, or we've gone back "too far"
     * (~64kb) */
    if ((!cur_file_ofs) || ((pZip->m_archive_size - cur_file_ofs) >=
                            ((mz_uint64)(MZ_UINT16_MAX) + record_size)))
      return MZ_FALSE;

    cur_file_ofs = MZ_MAX(cur_file_ofs - (sizeof(buf_u32) - 3), 0);
  }

  *pOfs = cur_file_ofs;
  return MZ_TRUE;
}

static mz_bool mz_zip_reader_eocd64_valid(mz_zip_archive *pZip, uint64_t offset,
                                          uint8_t *buf) {
  if (pZip->m_pRead(pZip->m_pIO_opaque, offset, buf,
                    MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE) ==
      MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE) {
    if (MZ_READ_LE32(buf + MZ_ZIP64_ECDH_SIG_OFS) ==
        MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIG) {
      return MZ_TRUE;
    }
  }

  return MZ_FALSE;
}

static mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip,
                                              mz_uint flags) {
  mz_uint cdir_size = 0, cdir_entries_on_this_disk = 0, num_this_disk = 0,
          cdir_disk_index = 0;
  mz_uint64 cdir_ofs = 0, eocd_ofs = 0, archive_ofs = 0;
  mz_int64 cur_file_ofs = 0;
  const mz_uint8 *p;

  mz_uint32 buf_u32[4096 / sizeof(mz_uint32)];
  mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool sort_central_dir =
      ((flags & MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY) == 0);
  mz_uint32 zip64_end_of_central_dir_locator_u32
      [(MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIZE + sizeof(mz_uint32) - 1) /
       sizeof(mz_uint32)];
  mz_uint8 *pZip64_locator = (mz_uint8 *)zip64_end_of_central_dir_locator_u32;

  mz_uint32 zip64_end_of_central_dir_header_u32
      [(MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE + sizeof(mz_uint32) - 1) /
       sizeof(mz_uint32)];
  mz_uint8 *pZip64_end_of_central_dir =
      (mz_uint8 *)zip64_end_of_central_dir_header_u32;

  mz_uint64 zip64_end_of_central_dir_ofs = 0;

  /* Basic sanity checks - reject files which are too small, and check the
   * first 4 bytes of the file to make sure a local header is there. */
  if (pZip->m_archive_size < MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)
    return mz_zip_set_error(pZip, MZ_ZIP_NOT_AN_ARCHIVE);

  if (!mz_zip_reader_locate_header_sig(
          pZip, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG,
          MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE, &cur_file_ofs))
    return mz_zip_set_error(pZip, MZ_ZIP_FAILED_FINDING_CENTRAL_DIR);

  eocd_ofs = cur_file_ofs;
  /* Read and verify the end of central directory record. */
  if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf,
                    MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE) !=
      MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);

  if (MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) !=
      MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG)
    return mz_zip_set_error(pZip, MZ_ZIP_NOT_AN_ARCHIVE);

  if (cur_file_ofs >= (MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIZE +
                       MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE)) {
    if (pZip->m_pRead(pZip->m_pIO_opaque,
                      cur_file_ofs - MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIZE,
                      pZip64_locator,
                      MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIZE) ==
        MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIZE) {
      if (MZ_READ_LE32(pZip64_locator + MZ_ZIP64_ECDL_SIG_OFS) ==
          MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIG) {
        pZip->m_pState->m_zip64 = MZ_TRUE;
      }
    }
  }

  if (pZip->m_pState->m_zip64) {
    /* Try locating the EOCD64 right before the EOCD64 locator. This works
     * even when the effective start of the zip header is not yet known. */
    if (cur_file_ofs < MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIZE +
                           MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE)
      return mz_zip_set_error(pZip, MZ_ZIP_NOT_AN_ARCHIVE);

    zip64_end_of_central_dir_ofs = cur_file_ofs -
                                   MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIZE -
                                   MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE;

    if (!mz_zip_reader_eocd64_valid(pZip, zip64_end_of_central_dir_ofs,
                                    pZip64_end_of_central_dir)) {
      /* That failed, try reading where the locator tells us to. */
      zip64_end_of_central_dir_ofs = MZ_READ_LE64(
          pZip64_locator + MZ_ZIP64_ECDL_REL_OFS_TO_ZIP64_ECDR_OFS);

      if (zip64_end_of_central_dir_ofs >
          (pZip->m_archive_size - MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE))
        return mz_zip_set_error(pZip, MZ_ZIP_NOT_AN_ARCHIVE);

      if (!mz_zip_reader_eocd64_valid(pZip, zip64_end_of_central_dir_ofs,
                                      pZip64_end_of_central_dir))
        return mz_zip_set_error(pZip, MZ_ZIP_NOT_AN_ARCHIVE);
    }
  }

  pZip->m_total_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS);
  cdir_entries_on_this_disk =
      MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_NUM_ENTRIES_ON_DISK_OFS);
  num_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_NUM_THIS_DISK_OFS);
  cdir_disk_index = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_NUM_DISK_CDIR_OFS);
  cdir_size = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_SIZE_OFS);
  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);

  if (pZip->m_pState->m_zip64) {
    mz_uint32 zip64_total_num_of_disks =
        MZ_READ_LE32(pZip64_locator + MZ_ZIP64_ECDL_TOTAL_NUMBER_OF_DISKS_OFS);
    mz_uint64 zip64_cdir_total_entries = MZ_READ_LE64(
        pZip64_end_of_central_dir + MZ_ZIP64_ECDH_CDIR_TOTAL_ENTRIES_OFS);
    mz_uint64 zip64_cdir_total_entries_on_this_disk = MZ_READ_LE64(
        pZip64_end_of_central_dir + MZ_ZIP64_ECDH_CDIR_NUM_ENTRIES_ON_DISK_OFS);
    mz_uint64 zip64_size_of_end_of_central_dir_record = MZ_READ_LE64(
        pZip64_end_of_central_dir + MZ_ZIP64_ECDH_SIZE_OF_RECORD_OFS);
    mz_uint64 zip64_size_of_central_directory =
        MZ_READ_LE64(pZip64_end_of_central_dir + MZ_ZIP64_ECDH_CDIR_SIZE_OFS);

    if (zip64_size_of_end_of_central_dir_record <
        (MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE - 12))
      return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

    if (zip64_total_num_of_disks != 1U)
      return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_MULTIDISK);

    /* Check for miniz's practical limits */
    if (zip64_cdir_total_entries > MZ_UINT32_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_TOO_MANY_FILES);

    pZip->m_total_files = (mz_uint32)zip64_cdir_total_entries;

    if (zip64_cdir_total_entries_on_this_disk > MZ_UINT32_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_TOO_MANY_FILES);

    cdir_entries_on_this_disk =
        (mz_uint32)zip64_cdir_total_entries_on_this_disk;

    /* Check for miniz's current practical limits (sorry, this should be
     * enough for millions of files) */
    if (zip64_size_of_central_directory > MZ_UINT32_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_CDIR_SIZE);

    cdir_size = (mz_uint32)zip64_size_of_central_directory;

    num_this_disk = MZ_READ_LE32(pZip64_end_of_central_dir +
                                 MZ_ZIP64_ECDH_NUM_THIS_DISK_OFS);

    cdir_disk_index = MZ_READ_LE32(pZip64_end_of_central_dir +
                                   MZ_ZIP64_ECDH_NUM_DISK_CDIR_OFS);

    cdir_ofs =
        MZ_READ_LE64(pZip64_end_of_central_dir + MZ_ZIP64_ECDH_CDIR_OFS_OFS);
  }

  if (pZip->m_total_files != cdir_entries_on_this_disk)
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_MULTIDISK);

  if (((num_this_disk | cdir_disk_index) != 0) &&
      ((num_this_disk != 1) || (cdir_disk_index != 1)))
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_MULTIDISK);

  if (cdir_size <
      (mz_uint64)pZip->m_total_files * MZ_ZIP_CENTRAL_DIR_HEADER_SIZE)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

  if ((cdir_ofs + (mz_uint64)cdir_size) > pZip->m_archive_size)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

  if (eocd_ofs < cdir_ofs + cdir_size)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

  /* The end of central dir follows the central dir, unless the zip file has
   * some trailing data (e.g. it is appended to an executable file). */
  archive_ofs = eocd_ofs - (cdir_ofs + cdir_size);
  if (pZip->m_pState->m_zip64) {
    if (archive_ofs < MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE +
                          MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIZE)
      return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

    archive_ofs -= MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE +
                   MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIZE;
  }

  /* Update the archive start position, but only if not specified. */
  if ((pZip->m_zip_type == MZ_ZIP_TYPE_FILE ||
       pZip->m_zip_type == MZ_ZIP_TYPE_CFILE) &&
      pZip->m_pState->m_file_archive_start_ofs == 0) {
    pZip->m_pState->m_file_archive_start_ofs = archive_ofs;
    pZip->m_archive_size -= archive_ofs;
  }

  pZip->m_central_directory_file_ofs = cdir_ofs;

  if (pZip->m_total_files) {
    mz_uint i, n;
    /* Read the entire central directory into a heap block, and allocate
     * another heap block to hold the unsorted central dir file record
     * offsets, and possibly another to hold the sorted indices. */
    if ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_size,
                              MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets,
                              pZip->m_total_files, MZ_FALSE)))
      return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);

    if (sort_central_dir) {
      if (!mz_zip_array_resize(pZip,
                               &pZip->m_pState->m_sorted_central_dir_offsets,
                               pZip->m_total_files, MZ_FALSE))
        return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
    }

    if (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs,
                      pZip->m_pState->m_central_dir.m_p,
                      cdir_size) != cdir_size)
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);

    /* Now create an index into the central directory file records, do some
     * basic sanity checking on each record */
    p = (const mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    for (n = cdir_size, i = 0; i < pZip->m_total_files; ++i) {
      mz_uint total_header_size, disk_index, bit_flags, filename_size,
          ext_data_size;
      mz_uint64 comp_size, decomp_size, local_header_ofs;

      if ((n < MZ_ZIP_CENTRAL_DIR_HEADER_SIZE) ||
          (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_HEADER_SIG))
        return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32,
                           i) =
          (mz_uint32)(p - (const mz_uint8 *)pZip->m_pState->m_central_dir.m_p);

      if (sort_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets,
                             mz_uint32, i) = i;

      comp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);
      decomp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS);
      local_header_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS);
      filename_size = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
      ext_data_size = MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS);

      if ((!pZip->m_pState->m_zip64_has_extended_info_fields) &&
          (ext_data_size) &&
          (MZ_MAX(MZ_MAX(comp_size, decomp_size), local_header_ofs) ==
           MZ_UINT32_MAX)) {
        /* Attempt to find zip64 extended information field in the entry's
         * extra data */
        mz_uint32 extra_size_remaining = ext_data_size;

        if (extra_size_remaining) {
          const mz_uint8 *pExtra_data;
          void *buf = NULL;

          if (MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + filename_size + ext_data_size >
              n) {
            buf = MZ_MALLOC(ext_data_size);
            if (buf == NULL)
              return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);

            if (pZip->m_pRead(pZip->m_pIO_opaque,
                              cdir_ofs + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE +
                                  filename_size,
                              buf, ext_data_size) != ext_data_size) {
              MZ_FREE(buf);
              return mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);
            }

            pExtra_data = (mz_uint8 *)buf;
          } else {
            pExtra_data = p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + filename_size;
          }

          do {
            mz_uint32 field_id;
            mz_uint32 field_data_size;

            if (extra_size_remaining < (sizeof(mz_uint16) * 2)) {
              MZ_FREE(buf);
              return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);
            }

            field_id = MZ_READ_LE16(pExtra_data);
            field_data_size = MZ_READ_LE16(pExtra_data + sizeof(mz_uint16));

            if ((field_data_size + sizeof(mz_uint16) * 2) >
                extra_size_remaining) {
              MZ_FREE(buf);
              return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);
            }

            if (field_id == MZ_ZIP64_EXTENDED_INFORMATION_FIELD_HEADER_ID) {
              /* Ok, the archive didn't have any zip64 headers but it uses a
               * zip64 extended information field so mark it as zip64 anyway
               * (this can occur with infozip's zip util when it reads
               * compresses files from stdin). */
              pZip->m_pState->m_zip64 = MZ_TRUE;
              pZip->m_pState->m_zip64_has_extended_info_fields = MZ_TRUE;
              break;
            }

            pExtra_data += sizeof(mz_uint16) * 2 + field_data_size;
            extra_size_remaining =
                extra_size_remaining - sizeof(mz_uint16) * 2 - field_data_size;
          } while (extra_size_remaining);

          MZ_FREE(buf);
        }
      }

      /* I've seen archives that aren't marked as zip64 that uses zip64 ext
       * data, argh */
      if ((comp_size != MZ_UINT32_MAX) && (decomp_size != MZ_UINT32_MAX)) {
        if (((!MZ_READ_LE32(p + MZ_ZIP_CDH_METHOD_OFS)) &&
             (decomp_size != comp_size)) ||
            (decomp_size && !comp_size))
          return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);
      }

      disk_index = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_START_OFS);
      if ((disk_index == MZ_UINT16_MAX) ||
          ((disk_index != num_this_disk) && (disk_index != 1)))
        return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_MULTIDISK);

      if (comp_size != MZ_UINT32_MAX) {
        if (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS) +
             MZ_ZIP_LOCAL_DIR_HEADER_SIZE + comp_size) > pZip->m_archive_size)
          return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);
      }

      bit_flags = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
      if (bit_flags & MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_LOCAL_DIR_IS_MASKED)
        return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_ENCRYPTION);

      if ((total_header_size = MZ_ZIP_CENTRAL_DIR_HEADER_SIZE +
                               MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) +
                               MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) +
                               MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) >
          n)
        return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

      n -= total_header_size;
      p += total_header_size;
    }
  }

  if (sort_central_dir)
    mz_zip_reader_sort_central_dir_offsets_by_filename(pZip);

  return MZ_TRUE;
}

void mz_zip_zero_struct(mz_zip_archive *pZip) {
  if (pZip)
    MZ_CLEAR_PTR(pZip);
}

static mz_bool mz_zip_reader_end_internal(mz_zip_archive *pZip,
                                          mz_bool set_last_error) {
  mz_bool status = MZ_TRUE;

  if (!pZip)
    return MZ_FALSE;

  if ((!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) ||
      (pZip->m_zip_mode != MZ_ZIP_MODE_READING)) {
    if (set_last_error)
      pZip->m_last_error = MZ_ZIP_INVALID_PARAMETER;

    return MZ_FALSE;
  }

  if (pZip->m_pState) {
    mz_zip_internal_state *pState = pZip->m_pState;
    pZip->m_pState = NULL;

    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ifndef MINIZ_NO_STDIO
    if (pState->m_pFile) {
      if (pZip->m_zip_type == MZ_ZIP_TYPE_FILE) {
        if (MZ_FCLOSE(pState->m_pFile) == EOF) {
          if (set_last_error)
            pZip->m_last_error = MZ_ZIP_FILE_CLOSE_FAILED;
          status = MZ_FALSE;
        }
      }
      pState->m_pFile = NULL;
    }
#endif /* #ifndef MINIZ_NO_STDIO */

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_mode = MZ_ZIP_MODE_INVALID;

  return status;
}

mz_bool mz_zip_reader_end(mz_zip_archive *pZip) {
  return mz_zip_reader_end_internal(pZip, MZ_TRUE);
}
mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 size,
                           mz_uint flags) {
  if ((!pZip) || (!pZip->m_pRead))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  if (!mz_zip_reader_init_internal(pZip, flags))
    return MZ_FALSE;

  pZip->m_zip_type = MZ_ZIP_TYPE_USER;
  pZip->m_archive_size = size;

  if (!mz_zip_reader_read_central_dir(pZip, flags)) {
    mz_zip_reader_end_internal(pZip, MZ_FALSE);
    return MZ_FALSE;
  }

  return MZ_TRUE;
}

static size_t mz_zip_mem_read_func(void *pOpaque, mz_uint64 file_ofs,
                                   void *pBuf, size_t n) {
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  size_t s = (file_ofs >= pZip->m_archive_size)
                 ? 0
                 : (size_t)MZ_MIN(pZip->m_archive_size - file_ofs, n);
  memcpy(pBuf, (const mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  return s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, const void *pMem,
                               size_t size, mz_uint flags) {
  if (!pMem)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  if (size < MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)
    return mz_zip_set_error(pZip, MZ_ZIP_NOT_AN_ARCHIVE);

  if (!mz_zip_reader_init_internal(pZip, flags))
    return MZ_FALSE;

  pZip->m_zip_type = MZ_ZIP_TYPE_MEMORY;
  pZip->m_archive_size = size;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pNeeds_keepalive = NULL;

#ifdef __cplusplus
  pZip->m_pState->m_pMem = const_cast<void *>(pMem);
#else
  pZip->m_pState->m_pMem = (void *)pMem;
#endif

  pZip->m_pState->m_mem_size = size;

  if (!mz_zip_reader_read_central_dir(pZip, flags)) {
    mz_zip_reader_end_internal(pZip, MZ_FALSE);
    return MZ_FALSE;
  }

  return MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
static size_t mz_zip_file_read_func(void *pOpaque, mz_uint64 file_ofs,
                                    void *pBuf, size_t n) {
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);

  file_ofs += pZip->m_pState->m_file_archive_start_ofs;

  if (((mz_int64)file_ofs < 0) ||
      (((cur_ofs != (mz_int64)file_ofs)) &&
       (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    return 0;

  return MZ_FREAD(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, const char *pFilename,
                                mz_uint32 flags) {
  return mz_zip_reader_init_file_v2(pZip, pFilename, flags, 0, 0);
}

mz_bool mz_zip_reader_init_file_v2(mz_zip_archive *pZip, const char *pFilename,
                                   mz_uint flags, mz_uint64 file_start_ofs,
                                   mz_uint64 archive_size) {
  mz_uint64 file_size;
  MZ_FILE *pFile;

  if ((!pZip) || (!pFilename) ||
      ((archive_size) &&
       (archive_size < MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  pFile = MZ_FOPEN(pFilename, "rb");
  if (!pFile)
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_OPEN_FAILED);

  file_size = archive_size;
  if (!file_size) {
    if (MZ_FSEEK64(pFile, 0, SEEK_END)) {
      MZ_FCLOSE(pFile);
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_SEEK_FAILED);
    }

    file_size = MZ_FTELL64(pFile);
  }

  /* TODO: Better sanity check archive_size and the # of actual remaining
   * bytes
   */

  if (file_size < MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE) {
    MZ_FCLOSE(pFile);
    return mz_zip_set_error(pZip, MZ_ZIP_NOT_AN_ARCHIVE);
  }

  if (!mz_zip_reader_init_internal(pZip, flags)) {
    MZ_FCLOSE(pFile);
    return MZ_FALSE;
  }

  pZip->m_zip_type = MZ_ZIP_TYPE_FILE;
  pZip->m_pRead = mz_zip_file_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_size = file_size;
  pZip->m_pState->m_file_archive_start_ofs = file_start_ofs;

  if (!mz_zip_reader_read_central_dir(pZip, flags)) {
    mz_zip_reader_end_internal(pZip, MZ_FALSE);
    return MZ_FALSE;
  }

  return MZ_TRUE;
}

mz_bool mz_zip_reader_init_cfile(mz_zip_archive *pZip, MZ_FILE *pFile,
                                 mz_uint64 archive_size, mz_uint flags) {
  mz_uint64 cur_file_ofs;

  if ((!pZip) || (!pFile))
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_OPEN_FAILED);

  cur_file_ofs = MZ_FTELL64(pFile);

  if (!archive_size) {
    if (MZ_FSEEK64(pFile, 0, SEEK_END))
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_SEEK_FAILED);

    archive_size = MZ_FTELL64(pFile) - cur_file_ofs;

    if (archive_size < MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)
      return mz_zip_set_error(pZip, MZ_ZIP_NOT_AN_ARCHIVE);
  }

  if (!mz_zip_reader_init_internal(pZip, flags))
    return MZ_FALSE;

  pZip->m_zip_type = MZ_ZIP_TYPE_CFILE;
  pZip->m_pRead = mz_zip_file_read_func;

  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_size = archive_size;
  pZip->m_pState->m_file_archive_start_ofs = cur_file_ofs;

  if (!mz_zip_reader_read_central_dir(pZip, flags)) {
    mz_zip_reader_end_internal(pZip, MZ_FALSE);
    return MZ_FALSE;
  }

  return MZ_TRUE;
}

#endif /* #ifndef MINIZ_NO_STDIO */

static MZ_FORCEINLINE const mz_uint8 *mz_zip_get_cdh(mz_zip_archive *pZip,
                                                     mz_uint file_index) {
  if ((!pZip) || (!pZip->m_pState) || (file_index >= pZip->m_total_files))
    return NULL;
  return &MZ_ZIP_ARRAY_ELEMENT(
      &pZip->m_pState->m_central_dir, mz_uint8,
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32,
                           file_index));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip,
                                        mz_uint file_index) {
  mz_uint m_bit_flag;
  const mz_uint8 *p = mz_zip_get_cdh(pZip, file_index);
  if (!p) {
    mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);
    return MZ_FALSE;
  }

  m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
  return (m_bit_flag &
          (MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_IS_ENCRYPTED |
           MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_USES_STRONG_ENCRYPTION)) != 0;
}

mz_bool mz_zip_reader_is_file_supported(mz_zip_archive *pZip,
                                        mz_uint file_index) {
  mz_uint bit_flag;
  mz_uint method;

  const mz_uint8 *p = mz_zip_get_cdh(pZip, file_index);
  if (!p) {
    mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);
    return MZ_FALSE;
  }

  method = MZ_READ_LE16(p + MZ_ZIP_CDH_METHOD_OFS);
  bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);

  if ((method != 0) && (method != MZ_DEFLATED)) {
    mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_METHOD);
    return MZ_FALSE;
  }

  if (bit_flag & (MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_IS_ENCRYPTED |
                  MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_USES_STRONG_ENCRYPTION)) {
    mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_ENCRYPTION);
    return MZ_FALSE;
  }

  if (bit_flag & MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_COMPRESSED_PATCH_FLAG) {
    mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_FEATURE);
    return MZ_FALSE;
  }

  return MZ_TRUE;
}

mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip,
                                          mz_uint file_index) {
  mz_uint filename_len, attribute_mapping_id, external_attr;
  const mz_uint8 *p = mz_zip_get_cdh(pZip, file_index);
  if (!p) {
    mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);
    return MZ_FALSE;
  }

  filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  if (filename_len) {
    if (*(p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + filename_len - 1) == '/')
      return MZ_TRUE;
  }

  /* Bugfix: This code was also checking if the internal attribute was
   * non-zero, which wasn't correct. */
  /* Most/all zip writers (hopefully) set DOS file/directory attributes in the
   * low 16-bits, so check for the DOS directory flag and ignore the source OS
   * ID in the created by field. */
  /* FIXME: Remove this check? Is it necessary - we already check the
   * filename.
   */
  attribute_mapping_id = MZ_READ_LE16(p + MZ_ZIP_CDH_VERSION_MADE_BY_OFS) >> 8;
  (void)attribute_mapping_id;

  external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  if ((external_attr & MZ_ZIP_DOS_DIR_ATTRIBUTE_BITFLAG) != 0) {
    return MZ_TRUE;
  }

  return MZ_FALSE;
}

static mz_bool mz_zip_file_stat_internal(mz_zip_archive *pZip,
                                         mz_uint file_index,
                                         const mz_uint8 *pCentral_dir_header,
                                         mz_zip_archive_file_stat *pStat,
                                         mz_bool *pFound_zip64_extra_data) {
  mz_uint n;
  const mz_uint8 *p = pCentral_dir_header;

  if (pFound_zip64_extra_data)
    *pFound_zip64_extra_data = MZ_FALSE;

  if ((!p) || (!pStat))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  /* Extract fields from the central directory record. */
  pStat->m_file_index = file_index;
  pStat->m_central_dir_ofs = MZ_ZIP_ARRAY_ELEMENT(
      &pZip->m_pState->m_central_dir_offsets, mz_uint32, file_index);
  pStat->m_version_made_by = MZ_READ_LE16(p + MZ_ZIP_CDH_VERSION_MADE_BY_OFS);
  pStat->m_version_needed = MZ_READ_LE16(p + MZ_ZIP_CDH_VERSION_NEEDED_OFS);
  pStat->m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
  pStat->m_method = MZ_READ_LE16(p + MZ_ZIP_CDH_METHOD_OFS);
#ifndef MINIZ_NO_TIME
  pStat->m_time =
      mz_zip_dos_to_time_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_TIME_OFS),
                           MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#endif
  pStat->m_crc32 = MZ_READ_LE32(p + MZ_ZIP_CDH_CRC32_OFS);
  pStat->m_comp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);
  pStat->m_uncomp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS);
  pStat->m_internal_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_INTERNAL_ATTR_OFS);
  pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  pStat->m_local_header_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS);

  /* Copy as much of the filename and comment as possible. */
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE - 1);
  memcpy(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE, n);
  pStat->m_filename[n] = '\0';

  n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE - 1);
  pStat->m_comment_size = n;
  memcpy(pStat->m_comment,
         p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE +
             MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) +
             MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS),
         n);
  pStat->m_comment[n] = '\0';

  /* Set some flags for convienance */
  pStat->m_is_directory = mz_zip_reader_is_file_a_directory(pZip, file_index);
  pStat->m_is_encrypted = mz_zip_reader_is_file_encrypted(pZip, file_index);
  pStat->m_is_supported = mz_zip_reader_is_file_supported(pZip, file_index);

  /* See if we need to read any zip64 extended information fields. */
  /* Confusingly, these zip64 fields can be present even on non-zip64 archives
   * (Debian zip on a huge files from stdin piped to stdout creates them). */
  if (MZ_MAX(MZ_MAX(pStat->m_comp_size, pStat->m_uncomp_size),
             pStat->m_local_header_ofs) == MZ_UINT32_MAX) {
    /* Attempt to find zip64 extended information field in the entry's extra
     * data */
    mz_uint32 extra_size_remaining = MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS);

    if (extra_size_remaining) {
      const mz_uint8 *pExtra_data =
          p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE +
          MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);

      do {
        mz_uint32 field_id;
        mz_uint32 field_data_size;

        if (extra_size_remaining < (sizeof(mz_uint16) * 2))
          return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

        field_id = MZ_READ_LE16(pExtra_data);
        field_data_size = MZ_READ_LE16(pExtra_data + sizeof(mz_uint16));

        if ((field_data_size + sizeof(mz_uint16) * 2) > extra_size_remaining)
          return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

        if (field_id == MZ_ZIP64_EXTENDED_INFORMATION_FIELD_HEADER_ID) {
          const mz_uint8 *pField_data = pExtra_data + sizeof(mz_uint16) * 2;
          mz_uint32 field_data_remaining = field_data_size;

          if (pFound_zip64_extra_data)
            *pFound_zip64_extra_data = MZ_TRUE;

          if (pStat->m_uncomp_size == MZ_UINT32_MAX) {
            if (field_data_remaining < sizeof(mz_uint64))
              return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

            pStat->m_uncomp_size = MZ_READ_LE64(pField_data);
            pField_data += sizeof(mz_uint64);
            field_data_remaining -= sizeof(mz_uint64);
          }

          if (pStat->m_comp_size == MZ_UINT32_MAX) {
            if (field_data_remaining < sizeof(mz_uint64))
              return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

            pStat->m_comp_size = MZ_READ_LE64(pField_data);
            pField_data += sizeof(mz_uint64);
            field_data_remaining -= sizeof(mz_uint64);
          }

          if (pStat->m_local_header_ofs == MZ_UINT32_MAX) {
            if (field_data_remaining < sizeof(mz_uint64))
              return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

            pStat->m_local_header_ofs = MZ_READ_LE64(pField_data);
            pField_data += sizeof(mz_uint64);
            field_data_remaining -= sizeof(mz_uint64);
          }

          break;
        }

        pExtra_data += sizeof(mz_uint16) * 2 + field_data_size;
        extra_size_remaining =
            extra_size_remaining - sizeof(mz_uint16) * 2 - field_data_size;
      } while (extra_size_remaining);
    }
  }

  return MZ_TRUE;
}

static MZ_FORCEINLINE mz_bool mz_zip_string_equal(const char *pA,
                                                  const char *pB, mz_uint len,
                                                  mz_uint flags) {
  mz_uint i;
  if (flags & MZ_ZIP_FLAG_CASE_SENSITIVE)
    return 0 == memcmp(pA, pB, len);
  for (i = 0; i < len; ++i)
    if (MZ_TOLOWER(pA[i]) != MZ_TOLOWER(pB[i]))
      return MZ_FALSE;
  return MZ_TRUE;
}

static MZ_FORCEINLINE int
mz_zip_filename_compare(const mz_zip_array *pCentral_dir_array,
                        const mz_zip_array *pCentral_dir_offsets,
                        mz_uint l_index, const char *pR, mz_uint r_len) {
  const mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(
                     pCentral_dir_array, mz_uint8,
                     MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32,
                                          l_index)),
                 *pE;
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
  pE = pL + MZ_MIN(l_len, r_len);
  while (pL < pE) {
    if ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      break;
    pL++;
    pR++;
  }
  return (pL == pE) ? (int)(l_len - r_len) : (l - r);
}

static mz_bool mz_zip_locate_file_binary_search(mz_zip_archive *pZip,
                                                const char *pFilename,
                                                mz_uint32 *pIndex) {
  mz_zip_internal_state *pState = pZip->m_pState;
  const mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  const mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(
      &pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  const mz_uint32 size = pZip->m_total_files;
  const mz_uint filename_len = (mz_uint)strlen(pFilename);

  if (pIndex)
    *pIndex = 0;

  if (size) {
    /* yes I could use uint32_t's, but then we would have to add some special
     * case checks in the loop, argh, and */
    /* honestly the major expense here on 32-bit CPU's will still be the
     * filename compare */
    mz_int64 l = 0, h = (mz_int64)size - 1;

    while (l <= h) {
      mz_int64 m = l + ((h - l) >> 1);
      mz_uint32 file_index = pIndices[(mz_uint32)m];

      int comp = mz_zip_filename_compare(pCentral_dir, pCentral_dir_offsets,
                                         file_index, pFilename, filename_len);
      if (!comp) {
        if (pIndex)
          *pIndex = file_index;
        return MZ_TRUE;
      } else if (comp < 0)
        l = m + 1;
      else
        h = m - 1;
    }
  }

  return mz_zip_set_error(pZip, MZ_ZIP_FILE_NOT_FOUND);
}

int mz_zip_reader_locate_file(mz_zip_archive *pZip, const char *pName,
                              const char *pComment, mz_uint flags) {
  mz_uint32 index;
  if (!mz_zip_reader_locate_file_v2(pZip, pName, pComment, flags, &index))
    return -1;
  else
    return (int)index;
}

mz_bool mz_zip_reader_locate_file_v2(mz_zip_archive *pZip, const char *pName,
                                     const char *pComment, mz_uint flags,
                                     mz_uint32 *pIndex) {
  mz_uint file_index;
  size_t name_len, comment_len;

  if (pIndex)
    *pIndex = 0;

  if ((!pZip) || (!pZip->m_pState) || (!pName))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  /* See if we can use a binary search */
  if (((pZip->m_pState->m_init_flags &
        MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY) == 0) &&
      (pZip->m_zip_mode == MZ_ZIP_MODE_READING) &&
      ((flags & (MZ_ZIP_FLAG_IGNORE_PATH | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) &&
      (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_size)) {
    return mz_zip_locate_file_binary_search(pZip, pName, pIndex);
  }

  /* Locate the entry by scanning the entire central directory */
  name_len = strlen(pName);
  if (name_len > MZ_UINT16_MAX)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  comment_len = pComment ? strlen(pComment) : 0;
  if (comment_len > MZ_UINT16_MAX)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  for (file_index = 0; file_index < pZip->m_total_files; file_index++) {
    const mz_uint8 *pHeader = &MZ_ZIP_ARRAY_ELEMENT(
        &pZip->m_pState->m_central_dir, mz_uint8,
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32,
                             file_index));
    mz_uint filename_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    const char *pFilename =
        (const char *)pHeader + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
    if (filename_len < name_len)
      continue;
    if (comment_len) {
      mz_uint file_extra_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_EXTRA_LEN_OFS),
              file_comment_len =
                  MZ_READ_LE16(pHeader + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      const char *pFile_comment = pFilename + filename_len + file_extra_len;
      if ((file_comment_len != comment_len) ||
          (!mz_zip_string_equal(pComment, pFile_comment, file_comment_len,
                                flags)))
        continue;
    }
    if ((flags & MZ_ZIP_FLAG_IGNORE_PATH) && (filename_len)) {
      int ofs = filename_len - 1;
      do {
        if ((pFilename[ofs] == '/') || (pFilename[ofs] == '\\') ||
            (pFilename[ofs] == ':'))
          break;
      } while (--ofs >= 0);
      ofs++;
      pFilename += ofs;
      filename_len -= ofs;
    }
    if ((filename_len == name_len) &&
        (mz_zip_string_equal(pName, pFilename, filename_len, flags))) {
      if (pIndex)
        *pIndex = file_index;
      return MZ_TRUE;
    }
  }

  return mz_zip_set_error(pZip, MZ_ZIP_FILE_NOT_FOUND);
}

static mz_bool mz_zip_reader_extract_to_mem_no_alloc1(
    mz_zip_archive *pZip, mz_uint file_index, void *pBuf, size_t buf_size,
    mz_uint flags, void *pUser_read_buf, size_t user_read_buf_size,
    const mz_zip_archive_file_stat *st) {
  int status = TINFL_STATUS_DONE;
  mz_uint64 needed_size, cur_file_ofs, comp_remaining,
      out_buf_ofs = 0, read_buf_size, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  void *pRead_buf;
  mz_uint32
      local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + sizeof(mz_uint32) - 1) /
                       sizeof(mz_uint32)];
  mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
  tinfl_decompressor inflator;

  if ((!pZip) || (!pZip->m_pState) || ((buf_size) && (!pBuf)) ||
      ((user_read_buf_size) && (!pUser_read_buf)) || (!pZip->m_pRead))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  if (st) {
    file_stat = *st;
  } else if (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
    return MZ_FALSE;

  /* A directory or zero length file */
  if ((file_stat.m_is_directory) || (!file_stat.m_comp_size))
    return MZ_TRUE;

  /* Encryption and patch files are not supported. */
  if (file_stat.m_bit_flag &
      (MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_IS_ENCRYPTED |
       MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_USES_STRONG_ENCRYPTION |
       MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_COMPRESSED_PATCH_FLAG))
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_ENCRYPTION);

  /* This function only supports decompressing stored and deflate. */
  if ((!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (file_stat.m_method != 0) &&
      (file_stat.m_method != MZ_DEFLATED))
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_METHOD);

  /* Ensure supplied output buffer is large enough. */
  needed_size = (flags & MZ_ZIP_FLAG_COMPRESSED_DATA) ? file_stat.m_comp_size
                                                      : file_stat.m_uncomp_size;
  if (buf_size < needed_size)
    return mz_zip_set_error(pZip, MZ_ZIP_BUF_TOO_SMALL);

  /* Read and parse the local directory entry. */
  cur_file_ofs = file_stat.m_local_header_ofs;
  if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pLocal_header,
                    MZ_ZIP_LOCAL_DIR_HEADER_SIZE) !=
      MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);

  if (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

  cur_file_ofs += (mz_uint64)(MZ_ZIP_LOCAL_DIR_HEADER_SIZE) +
                  MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) +
                  MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  if ((cur_file_ofs + file_stat.m_comp_size) > pZip->m_archive_size)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

  if ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) || (!file_stat.m_method)) {
    /* The file is stored or the caller has requested the compressed data. */
    if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf,
                      (size_t)needed_size) != needed_size)
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);

#ifndef MINIZ_DISABLE_ZIP_READER_CRC32_CHECKS
    if ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) == 0) {
      if (mz_crc32(MZ_CRC32_INIT, (const mz_uint8 *)pBuf,
                   (size_t)file_stat.m_uncomp_size) != file_stat.m_crc32)
        return mz_zip_set_error(pZip, MZ_ZIP_CRC_CHECK_FAILED);
    }
#endif

    return MZ_TRUE;
  }

  /* Decompress the file either directly from memory or from a file input
   * buffer. */
  tinfl_init(&inflator);

  if (pZip->m_pState->m_pMem) {
    /* Read directly from the archive in memory. */
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_size = read_buf_avail = file_stat.m_comp_size;
    comp_remaining = 0;
  } else if (pUser_read_buf) {
    /* Use a user provided read buffer. */
    if (!user_read_buf_size)
      return MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_size = user_read_buf_size;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_size;
  } else {
    /* Temporarily allocate a read buffer. */
    read_buf_size =
        MZ_MIN(file_stat.m_comp_size, (mz_uint64)MZ_ZIP_MAX_IO_BUF_SIZE);
    if (((sizeof(size_t) == sizeof(mz_uint32))) && (read_buf_size > 0x7FFFFFFF))
      return mz_zip_set_error(pZip, MZ_ZIP_INTERNAL_ERROR);

    if (NULL == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1,
                                            (size_t)read_buf_size)))
      return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);

    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_size;
  }

  do {
    /* The size_t cast here should be OK because we've verified that the
     * output buffer is >= file_stat.m_uncomp_size above */
    size_t in_buf_size,
        out_buf_size = (size_t)(file_stat.m_uncomp_size - out_buf_ofs);
    if ((!read_buf_avail) && (!pZip->m_pState->m_pMem)) {
      read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
      if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf,
                        (size_t)read_buf_avail) != read_buf_avail) {
        status = TINFL_STATUS_FAILED;
        mz_zip_set_error(pZip, MZ_ZIP_DECOMPRESSION_FAILED);
        break;
      }
      cur_file_ofs += read_buf_avail;
      comp_remaining -= read_buf_avail;
      read_buf_ofs = 0;
    }
    in_buf_size = (size_t)read_buf_avail;
    status = tinfl_decompress(
        &inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &in_buf_size,
        (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + out_buf_ofs, &out_buf_size,
        TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF |
            (comp_remaining ? TINFL_FLAG_HAS_MORE_INPUT : 0));
    read_buf_avail -= in_buf_size;
    read_buf_ofs += in_buf_size;
    out_buf_ofs += out_buf_size;
  } while (status == TINFL_STATUS_NEEDS_MORE_INPUT);

  if (status == TINFL_STATUS_DONE) {
    /* Make sure the entire file was decompressed, and check its CRC. */
    if (out_buf_ofs != file_stat.m_uncomp_size) {
      mz_zip_set_error(pZip, MZ_ZIP_UNEXPECTED_DECOMPRESSED_SIZE);
      status = TINFL_STATUS_FAILED;
    }
#ifndef MINIZ_DISABLE_ZIP_READER_CRC32_CHECKS
    else if (mz_crc32(MZ_CRC32_INIT, (const mz_uint8 *)pBuf,
                      (size_t)file_stat.m_uncomp_size) != file_stat.m_crc32) {
      mz_zip_set_error(pZip, MZ_ZIP_CRC_CHECK_FAILED);
      status = TINFL_STATUS_FAILED;
    }
#endif
  }

  if ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  return status == TINFL_STATUS_DONE;
}

mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip,
                                              mz_uint file_index, void *pBuf,
                                              size_t buf_size, mz_uint flags,
                                              void *pUser_read_buf,
                                              size_t user_read_buf_size) {
  return mz_zip_reader_extract_to_mem_no_alloc1(pZip, file_index, pBuf,
                                                buf_size, flags, pUser_read_buf,
                                                user_read_buf_size, NULL);
}

mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(
    mz_zip_archive *pZip, const char *pFilename, void *pBuf, size_t buf_size,
    mz_uint flags, void *pUser_read_buf, size_t user_read_buf_size) {
  mz_uint32 file_index;
  if (!mz_zip_reader_locate_file_v2(pZip, pFilename, NULL, flags, &file_index))
    return MZ_FALSE;
  return mz_zip_reader_extract_to_mem_no_alloc1(pZip, file_index, pBuf,
                                                buf_size, flags, pUser_read_buf,
                                                user_read_buf_size, NULL);
}

mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_index,
                                     void *pBuf, size_t buf_size,
                                     mz_uint flags) {
  return mz_zip_reader_extract_to_mem_no_alloc1(pZip, file_index, pBuf,
                                                buf_size, flags, NULL, 0, NULL);
}

mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip,
                                          const char *pFilename, void *pBuf,
                                          size_t buf_size, mz_uint flags) {
  return mz_zip_reader_extract_file_to_mem_no_alloc(pZip, pFilename, pBuf,
                                                    buf_size, flags, NULL, 0);
}

void *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_index,
                                    size_t *pSize, mz_uint flags) {
  mz_zip_archive_file_stat file_stat;
  mz_uint64 alloc_size;
  void *pBuf;

  if (pSize)
    *pSize = 0;

  if (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
    return NULL;

  alloc_size = (flags & MZ_ZIP_FLAG_COMPRESSED_DATA) ? file_stat.m_comp_size
                                                     : file_stat.m_uncomp_size;
  if (((sizeof(size_t) == sizeof(mz_uint32))) && (alloc_size > 0x7FFFFFFF)) {
    mz_zip_set_error(pZip, MZ_ZIP_INTERNAL_ERROR);
    return NULL;
  }

  if (NULL ==
      (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_size))) {
    mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
    return NULL;
  }

  if (!mz_zip_reader_extract_to_mem_no_alloc1(pZip, file_index, pBuf,
                                              (size_t)alloc_size, flags, NULL,
                                              0, &file_stat)) {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    return NULL;
  }

  if (pSize)
    *pSize = (size_t)alloc_size;
  return pBuf;
}

void *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip,
                                         const char *pFilename, size_t *pSize,
                                         mz_uint flags) {
  mz_uint32 file_index;
  if (!mz_zip_reader_locate_file_v2(pZip, pFilename, NULL, flags,
                                    &file_index)) {
    if (pSize)
      *pSize = 0;
    return MZ_FALSE;
  }
  return mz_zip_reader_extract_to_heap(pZip, file_index, pSize, flags);
}

mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip,
                                          mz_uint file_index,
                                          mz_file_write_func pCallback,
                                          void *pOpaque, mz_uint flags) {
  int status = TINFL_STATUS_DONE;
#ifndef MINIZ_DISABLE_ZIP_READER_CRC32_CHECKS
  mz_uint file_crc32 = MZ_CRC32_INIT;
#endif
  mz_uint64 read_buf_size, read_buf_ofs = 0, read_buf_avail, comp_remaining,
                           out_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  void *pRead_buf = NULL;
  void *pWrite_buf = NULL;
  mz_uint32
      local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + sizeof(mz_uint32) - 1) /
                       sizeof(mz_uint32)];
  mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;

  if ((!pZip) || (!pZip->m_pState) || (!pCallback) || (!pZip->m_pRead))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  if (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
    return MZ_FALSE;

  /* A directory or zero length file */
  if ((file_stat.m_is_directory) || (!file_stat.m_comp_size))
    return MZ_TRUE;

  /* Encryption and patch files are not supported. */
  if (file_stat.m_bit_flag &
      (MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_IS_ENCRYPTED |
       MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_USES_STRONG_ENCRYPTION |
       MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_COMPRESSED_PATCH_FLAG))
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_ENCRYPTION);

  /* This function only supports decompressing stored and deflate. */
  if ((!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (file_stat.m_method != 0) &&
      (file_stat.m_method != MZ_DEFLATED))
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_METHOD);

  /* Read and do some minimal validation of the local directory entry (this
   * doesn't crack the zip64 stuff, which we already have from the central
   * dir)
   */
  cur_file_ofs = file_stat.m_local_header_ofs;
  if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pLocal_header,
                    MZ_ZIP_LOCAL_DIR_HEADER_SIZE) !=
      MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);

  if (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

  cur_file_ofs += (mz_uint64)(MZ_ZIP_LOCAL_DIR_HEADER_SIZE) +
                  MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) +
                  MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  if ((cur_file_ofs + file_stat.m_comp_size) > pZip->m_archive_size)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

  /* Decompress the file either directly from memory or from a file input
   * buffer. */
  if (pZip->m_pState->m_pMem) {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_size = read_buf_avail = file_stat.m_comp_size;
    comp_remaining = 0;
  } else {
    read_buf_size =
        MZ_MIN(file_stat.m_comp_size, (mz_uint64)MZ_ZIP_MAX_IO_BUF_SIZE);
    if (NULL == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1,
                                            (size_t)read_buf_size)))
      return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);

    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_size;
  }

  if ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) || (!file_stat.m_method)) {
    /* The file is stored or the caller has requested the compressed data. */
    if (pZip->m_pState->m_pMem) {
      if (((sizeof(size_t) == sizeof(mz_uint32))) &&
          (file_stat.m_comp_size > MZ_UINT32_MAX))
        return mz_zip_set_error(pZip, MZ_ZIP_INTERNAL_ERROR);

      if (pCallback(pOpaque, out_buf_ofs, pRead_buf,
                    (size_t)file_stat.m_comp_size) != file_stat.m_comp_size) {
        mz_zip_set_error(pZip, MZ_ZIP_WRITE_CALLBACK_FAILED);
        status = TINFL_STATUS_FAILED;
      } else if (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) {
#ifndef MINIZ_DISABLE_ZIP_READER_CRC32_CHECKS
        file_crc32 =
            (mz_uint32)mz_crc32(file_crc32, (const mz_uint8 *)pRead_buf,
                                (size_t)file_stat.m_comp_size);
#endif
      }

      cur_file_ofs += file_stat.m_comp_size;
      out_buf_ofs += file_stat.m_comp_size;
      comp_remaining = 0;
    } else {
      while (comp_remaining) {
        read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
        if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf,
                          (size_t)read_buf_avail) != read_buf_avail) {
          mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);
          status = TINFL_STATUS_FAILED;
          break;
        }

#ifndef MINIZ_DISABLE_ZIP_READER_CRC32_CHECKS
        if (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) {
          file_crc32 = (mz_uint32)mz_crc32(
              file_crc32, (const mz_uint8 *)pRead_buf, (size_t)read_buf_avail);
        }
#endif

        if (pCallback(pOpaque, out_buf_ofs, pRead_buf,
                      (size_t)read_buf_avail) != read_buf_avail) {
          mz_zip_set_error(pZip, MZ_ZIP_WRITE_CALLBACK_FAILED);
          status = TINFL_STATUS_FAILED;
          break;
        }

        cur_file_ofs += read_buf_avail;
        out_buf_ofs += read_buf_avail;
        comp_remaining -= read_buf_avail;
      }
    }
  } else {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    if (NULL == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1,
                                             TINFL_LZ_DICT_SIZE))) {
      mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
      status = TINFL_STATUS_FAILED;
    } else {
      do {
        mz_uint8 *pWrite_buf_cur =
            (mz_uint8 *)pWrite_buf + (out_buf_ofs & (TINFL_LZ_DICT_SIZE - 1));
        size_t in_buf_size,
            out_buf_size =
                TINFL_LZ_DICT_SIZE - (out_buf_ofs & (TINFL_LZ_DICT_SIZE - 1));
        if ((!read_buf_avail) && (!pZip->m_pState->m_pMem)) {
          read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
          if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf,
                            (size_t)read_buf_avail) != read_buf_avail) {
            mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);
            status = TINFL_STATUS_FAILED;
            break;
          }
          cur_file_ofs += read_buf_avail;
          comp_remaining -= read_buf_avail;
          read_buf_ofs = 0;
        }

        in_buf_size = (size_t)read_buf_avail;
        status = tinfl_decompress(
            &inflator, (const mz_uint8 *)pRead_buf + read_buf_ofs, &in_buf_size,
            (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &out_buf_size,
            comp_remaining ? TINFL_FLAG_HAS_MORE_INPUT : 0);
        read_buf_avail -= in_buf_size;
        read_buf_ofs += in_buf_size;

        if (out_buf_size) {
          if (pCallback(pOpaque, out_buf_ofs, pWrite_buf_cur, out_buf_size) !=
              out_buf_size) {
            mz_zip_set_error(pZip, MZ_ZIP_WRITE_CALLBACK_FAILED);
            status = TINFL_STATUS_FAILED;
            break;
          }

#ifndef MINIZ_DISABLE_ZIP_READER_CRC32_CHECKS
          file_crc32 =
              (mz_uint32)mz_crc32(file_crc32, pWrite_buf_cur, out_buf_size);
#endif
          if ((out_buf_ofs += out_buf_size) > file_stat.m_uncomp_size) {
            mz_zip_set_error(pZip, MZ_ZIP_DECOMPRESSION_FAILED);
            status = TINFL_STATUS_FAILED;
            break;
          }
        }
      } while ((status == TINFL_STATUS_NEEDS_MORE_INPUT) ||
               (status == TINFL_STATUS_HAS_MORE_OUTPUT));
    }
  }

  if ((status == TINFL_STATUS_DONE) &&
      (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA))) {
    /* Make sure the entire file was decompressed, and check its CRC. */
    if (out_buf_ofs != file_stat.m_uncomp_size) {
      mz_zip_set_error(pZip, MZ_ZIP_UNEXPECTED_DECOMPRESSED_SIZE);
      status = TINFL_STATUS_FAILED;
    }
#ifndef MINIZ_DISABLE_ZIP_READER_CRC32_CHECKS
    else if (file_crc32 != file_stat.m_crc32) {
      mz_zip_set_error(pZip, MZ_ZIP_DECOMPRESSION_FAILED);
      status = TINFL_STATUS_FAILED;
    }
#endif
  }

  if (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  if (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  return status == TINFL_STATUS_DONE;
}

mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip,
                                               const char *pFilename,
                                               mz_file_write_func pCallback,
                                               void *pOpaque, mz_uint flags) {
  mz_uint32 file_index;
  if (!mz_zip_reader_locate_file_v2(pZip, pFilename, NULL, flags, &file_index))
    return MZ_FALSE;

  return mz_zip_reader_extract_to_callback(pZip, file_index, pCallback, pOpaque,
                                           flags);
}

mz_zip_reader_extract_iter_state *
mz_zip_reader_extract_iter_new(mz_zip_archive *pZip, mz_uint file_index,
                               mz_uint flags) {
  mz_zip_reader_extract_iter_state *pState;
  mz_uint32
      local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + sizeof(mz_uint32) - 1) /
                       sizeof(mz_uint32)];
  mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;

  /* Argument sanity check */
  if ((!pZip) || (!pZip->m_pState))
    return NULL;

  /* Allocate an iterator status structure */
  pState = (mz_zip_reader_extract_iter_state *)pZip->m_pAlloc(
      pZip->m_pAlloc_opaque, 1, sizeof(mz_zip_reader_extract_iter_state));
  if (!pState) {
    mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
    return NULL;
  }

  /* Fetch file details */
  if (!mz_zip_reader_file_stat(pZip, file_index, &pState->file_stat)) {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
    return NULL;
  }

  /* Encryption and patch files are not supported. */
  if (pState->file_stat.m_bit_flag &
      (MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_IS_ENCRYPTED |
       MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_USES_STRONG_ENCRYPTION |
       MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_COMPRESSED_PATCH_FLAG)) {
    mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_ENCRYPTION);
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
    return NULL;
  }

  /* This function only supports decompressing stored and deflate. */
  if ((!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) &&
      (pState->file_stat.m_method != 0) &&
      (pState->file_stat.m_method != MZ_DEFLATED)) {
    mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_METHOD);
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
    return NULL;
  }

  /* Init state - save args */
  pState->pZip = pZip;
  pState->flags = flags;

  /* Init state - reset variables to defaults */
  pState->status = TINFL_STATUS_DONE;
#ifndef MINIZ_DISABLE_ZIP_READER_CRC32_CHECKS
  pState->file_crc32 = MZ_CRC32_INIT;
#endif
  pState->read_buf_ofs = 0;
  pState->out_buf_ofs = 0;
  pState->pRead_buf = NULL;
  pState->pWrite_buf = NULL;
  pState->out_blk_remain = 0;

  /* Read and parse the local directory entry. */
  pState->cur_file_ofs = pState->file_stat.m_local_header_ofs;
  if (pZip->m_pRead(pZip->m_pIO_opaque, pState->cur_file_ofs, pLocal_header,
                    MZ_ZIP_LOCAL_DIR_HEADER_SIZE) !=
      MZ_ZIP_LOCAL_DIR_HEADER_SIZE) {
    mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
    return NULL;
  }

  if (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG) {
    mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
    return NULL;
  }

  pState->cur_file_ofs +=
      (mz_uint64)(MZ_ZIP_LOCAL_DIR_HEADER_SIZE) +
      MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) +
      MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  if ((pState->cur_file_ofs + pState->file_stat.m_comp_size) >
      pZip->m_archive_size) {
    mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
    return NULL;
  }

  /* Decompress the file either directly from memory or from a file input
   * buffer. */
  if (pZip->m_pState->m_pMem) {
    pState->pRead_buf =
        (mz_uint8 *)pZip->m_pState->m_pMem + pState->cur_file_ofs;
    pState->read_buf_size = pState->read_buf_avail =
        pState->file_stat.m_comp_size;
    pState->comp_remaining = pState->file_stat.m_comp_size;
  } else {
    if (!((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) ||
          (!pState->file_stat.m_method))) {
      /* Decompression required, therefore intermediate read buffer required
       */
      pState->read_buf_size = MZ_MIN(pState->file_stat.m_comp_size,
                                     (mz_uint64)MZ_ZIP_MAX_IO_BUF_SIZE);
      if (NULL ==
          (pState->pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1,
                                              (size_t)pState->read_buf_size))) {
        mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
        return NULL;
      }
    } else {
      /* Decompression not required - we will be reading directly into user
       * buffer, no temp buf required */
      pState->read_buf_size = 0;
    }
    pState->read_buf_avail = 0;
    pState->comp_remaining = pState->file_stat.m_comp_size;
  }

  if (!((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) ||
        (!pState->file_stat.m_method))) {
    /* Decompression required, init decompressor */
    tinfl_init(&pState->inflator);

    /* Allocate write buffer */
    if (NULL == (pState->pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1,
                                                     TINFL_LZ_DICT_SIZE))) {
      mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
      if (pState->pRead_buf)
        pZip->m_pFree(pZip->m_pAlloc_opaque, pState->pRead_buf);
      pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
      return NULL;
    }
  }

  return pState;
}

mz_zip_reader_extract_iter_state *
mz_zip_reader_extract_file_iter_new(mz_zip_archive *pZip, const char *pFilename,
                                    mz_uint flags) {
  mz_uint32 file_index;

  /* Locate file index by name */
  if (!mz_zip_reader_locate_file_v2(pZip, pFilename, NULL, flags, &file_index))
    return NULL;

  /* Construct iterator */
  return mz_zip_reader_extract_iter_new(pZip, file_index, flags);
}

size_t mz_zip_reader_extract_iter_read(mz_zip_reader_extract_iter_state *pState,
                                       void *pvBuf, size_t buf_size) {
  size_t copied_to_caller = 0;

  /* Argument sanity check */
  if ((!pState) || (!pState->pZip) || (!pState->pZip->m_pState) || (!pvBuf))
    return 0;

  if ((pState->flags & MZ_ZIP_FLAG_COMPRESSED_DATA) ||
      (!pState->file_stat.m_method)) {
    /* The file is stored or the caller has requested the compressed data,
     * calc amount to return. */
    copied_to_caller = (size_t)MZ_MIN(buf_size, pState->comp_remaining);

    /* Zip is in memory....or requires reading from a file? */
    if (pState->pZip->m_pState->m_pMem) {
      /* Copy data to caller's buffer */
      memcpy(pvBuf, pState->pRead_buf, copied_to_caller);
      pState->pRead_buf = ((mz_uint8 *)pState->pRead_buf) + copied_to_caller;
    } else {
      /* Read directly into caller's buffer */
      if (pState->pZip->m_pRead(pState->pZip->m_pIO_opaque,
                                pState->cur_file_ofs, pvBuf,
                                copied_to_caller) != copied_to_caller) {
        /* Failed to read all that was asked for, flag failure and alert user
         */
        mz_zip_set_error(pState->pZip, MZ_ZIP_FILE_READ_FAILED);
        pState->status = TINFL_STATUS_FAILED;
        copied_to_caller = 0;
      }
    }

#ifndef MINIZ_DISABLE_ZIP_READER_CRC32_CHECKS
    /* Compute CRC if not returning compressed data only */
    if (!(pState->flags & MZ_ZIP_FLAG_COMPRESSED_DATA))
      pState->file_crc32 = (mz_uint32)mz_crc32(
          pState->file_crc32, (const mz_uint8 *)pvBuf, copied_to_caller);
#endif

    /* Advance offsets, dec counters */
    pState->cur_file_ofs += copied_to_caller;
    pState->out_buf_ofs += copied_to_caller;
    pState->comp_remaining -= copied_to_caller;
  } else {
    do {
      /* Calc ptr to write buffer - given current output pos and block size */
      mz_uint8 *pWrite_buf_cur =
          (mz_uint8 *)pState->pWrite_buf +
          (pState->out_buf_ofs & (TINFL_LZ_DICT_SIZE - 1));

      /* Calc max output size - given current output pos and block size */
      size_t in_buf_size,
          out_buf_size = TINFL_LZ_DICT_SIZE -
                         (pState->out_buf_ofs & (TINFL_LZ_DICT_SIZE - 1));

      if (!pState->out_blk_remain) {
        /* Read more data from file if none available (and reading from file)
         */
        if ((!pState->read_buf_avail) && (!pState->pZip->m_pState->m_pMem)) {
          /* Calc read size */
          pState->read_buf_avail =
              MZ_MIN(pState->read_buf_size, pState->comp_remaining);
          if (pState->pZip->m_pRead(pState->pZip->m_pIO_opaque,
                                    pState->cur_file_ofs, pState->pRead_buf,
                                    (size_t)pState->read_buf_avail) !=
              pState->read_buf_avail) {
            mz_zip_set_error(pState->pZip, MZ_ZIP_FILE_READ_FAILED);
            pState->status = TINFL_STATUS_FAILED;
            break;
          }

          /* Advance offsets, dec counters */
          pState->cur_file_ofs += pState->read_buf_avail;
          pState->comp_remaining -= pState->read_buf_avail;
          pState->read_buf_ofs = 0;
        }

        /* Perform decompression */
        in_buf_size = (size_t)pState->read_buf_avail;
        pState->status = tinfl_decompress(
            &pState->inflator,
            (const mz_uint8 *)pState->pRead_buf + pState->read_buf_ofs,
            &in_buf_size, (mz_uint8 *)pState->pWrite_buf, pWrite_buf_cur,
            &out_buf_size,
            pState->comp_remaining ? TINFL_FLAG_HAS_MORE_INPUT : 0);
        pState->read_buf_avail -= in_buf_size;
        pState->read_buf_ofs += in_buf_size;

        /* Update current output block size remaining */
        pState->out_blk_remain = out_buf_size;
      }

      if (pState->out_blk_remain) {
        /* Calc amount to return. */
        size_t to_copy =
            MZ_MIN((buf_size - copied_to_caller), pState->out_blk_remain);

        /* Copy data to caller's buffer */
        memcpy((mz_uint8 *)pvBuf + copied_to_caller, pWrite_buf_cur, to_copy);

#ifndef MINIZ_DISABLE_ZIP_READER_CRC32_CHECKS
        /* Perform CRC */
        pState->file_crc32 =
            (mz_uint32)mz_crc32(pState->file_crc32, pWrite_buf_cur, to_copy);
#endif

        /* Decrement data consumed from block */
        pState->out_blk_remain -= to_copy;

        /* Inc output offset, while performing sanity check */
        if ((pState->out_buf_ofs += to_copy) >
            pState->file_stat.m_uncomp_size) {
          mz_zip_set_error(pState->pZip, MZ_ZIP_DECOMPRESSION_FAILED);
          pState->status = TINFL_STATUS_FAILED;
          break;
        }

        /* Increment counter of data copied to caller */
        copied_to_caller += to_copy;
      }
    } while ((copied_to_caller < buf_size) &&
             ((pState->status == TINFL_STATUS_NEEDS_MORE_INPUT) ||
              (pState->status == TINFL_STATUS_HAS_MORE_OUTPUT)));
  }

  /* Return how many bytes were copied into user buffer */
  return copied_to_caller;
}

mz_bool
mz_zip_reader_extract_iter_free(mz_zip_reader_extract_iter_state *pState) {
  int status;

  /* Argument sanity check */
  if ((!pState) || (!pState->pZip) || (!pState->pZip->m_pState))
    return MZ_FALSE;

  /* Was decompression completed and requested? */
  if ((pState->status == TINFL_STATUS_DONE) &&
      (!(pState->flags & MZ_ZIP_FLAG_COMPRESSED_DATA))) {
    /* Make sure the entire file was decompressed, and check its CRC. */
    if (pState->out_buf_ofs != pState->file_stat.m_uncomp_size) {
      mz_zip_set_error(pState->pZip, MZ_ZIP_UNEXPECTED_DECOMPRESSED_SIZE);
      pState->status = TINFL_STATUS_FAILED;
    }
#ifndef MINIZ_DISABLE_ZIP_READER_CRC32_CHECKS
    else if (pState->file_crc32 != pState->file_stat.m_crc32) {
      mz_zip_set_error(pState->pZip, MZ_ZIP_DECOMPRESSION_FAILED);
      pState->status = TINFL_STATUS_FAILED;
    }
#endif
  }

  /* Free buffers */
  if (!pState->pZip->m_pState->m_pMem)
    pState->pZip->m_pFree(pState->pZip->m_pAlloc_opaque, pState->pRead_buf);
  if (pState->pWrite_buf)
    pState->pZip->m_pFree(pState->pZip->m_pAlloc_opaque, pState->pWrite_buf);

  /* Save status */
  status = pState->status;

  /* Free context */
  pState->pZip->m_pFree(pState->pZip->m_pAlloc_opaque, pState);

  return status == TINFL_STATUS_DONE;
}

#ifndef MINIZ_NO_STDIO
static size_t mz_zip_file_write_callback(void *pOpaque, mz_uint64 ofs,
                                         const void *pBuf, size_t n) {
  (void)ofs;

  return MZ_FWRITE(pBuf, 1, n, (MZ_FILE *)pOpaque);
}

mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_index,
                                      const char *pDst_filename,
                                      mz_uint flags) {
  mz_bool status;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;

  if (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
    return MZ_FALSE;

  if ((file_stat.m_is_directory) || (!file_stat.m_is_supported))
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_FEATURE);

  pFile = MZ_FOPEN(pDst_filename, "wb");
  if (!pFile)
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_OPEN_FAILED);

  status = mz_zip_reader_extract_to_callback(
      pZip, file_index, mz_zip_file_write_callback, pFile, flags);

  if (MZ_FCLOSE(pFile) == EOF) {
    if (status)
      mz_zip_set_error(pZip, MZ_ZIP_FILE_CLOSE_FAILED);

    status = MZ_FALSE;
  }

#if !defined(MINIZ_NO_TIME) && !defined(MINIZ_NO_STDIO)
  if (status)
    mz_zip_set_file_times(pDst_filename, file_stat.m_time, file_stat.m_time);
#endif

  return status;
}

mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip,
                                           const char *pArchive_filename,
                                           const char *pDst_filename,
                                           mz_uint flags) {
  mz_uint32 file_index;
  if (!mz_zip_reader_locate_file_v2(pZip, pArchive_filename, NULL, flags,
                                    &file_index))
    return MZ_FALSE;

  return mz_zip_reader_extract_to_file(pZip, file_index, pDst_filename, flags);
}

mz_bool mz_zip_reader_extract_to_cfile(mz_zip_archive *pZip, mz_uint file_index,
                                       MZ_FILE *pFile, mz_uint flags) {
  mz_zip_archive_file_stat file_stat;

  if (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
    return MZ_FALSE;

  if ((file_stat.m_is_directory) || (!file_stat.m_is_supported))
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_FEATURE);

  return mz_zip_reader_extract_to_callback(
      pZip, file_index, mz_zip_file_write_callback, pFile, flags);
}

mz_bool mz_zip_reader_extract_file_to_cfile(mz_zip_archive *pZip,
                                            const char *pArchive_filename,
                                            MZ_FILE *pFile, mz_uint flags) {
  mz_uint32 file_index;
  if (!mz_zip_reader_locate_file_v2(pZip, pArchive_filename, NULL, flags,
                                    &file_index))
    return MZ_FALSE;

  return mz_zip_reader_extract_to_cfile(pZip, file_index, pFile, flags);
}
#endif /* #ifndef MINIZ_NO_STDIO */

static size_t mz_zip_compute_crc32_callback(void *pOpaque, mz_uint64 file_ofs,
                                            const void *pBuf, size_t n) {
  mz_uint32 *p = (mz_uint32 *)pOpaque;
  (void)file_ofs;
  *p = (mz_uint32)mz_crc32(*p, (const mz_uint8 *)pBuf, n);
  return n;
}

mz_bool mz_zip_validate_file(mz_zip_archive *pZip, mz_uint file_index,
                             mz_uint flags) {
  mz_zip_archive_file_stat file_stat;
  mz_zip_internal_state *pState;
  const mz_uint8 *pCentral_dir_header;
  mz_bool found_zip64_ext_data_in_cdir = MZ_FALSE;
  mz_bool found_zip64_ext_data_in_ldir = MZ_FALSE;
  mz_uint32
      local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + sizeof(mz_uint32) - 1) /
                       sizeof(mz_uint32)];
  mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
  mz_uint64 local_header_ofs = 0;
  mz_uint32 local_header_filename_len, local_header_extra_len,
      local_header_crc32;
  mz_uint64 local_header_comp_size, local_header_uncomp_size;
  mz_uint32 uncomp_crc32 = MZ_CRC32_INIT;
  mz_bool has_data_descriptor;
  mz_uint32 local_header_bit_flags;

  mz_zip_array file_data_array;
  mz_zip_array_init(&file_data_array, 1);

  if ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) ||
      (!pZip->m_pRead))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  if (file_index > pZip->m_total_files)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  pState = pZip->m_pState;

  pCentral_dir_header = mz_zip_get_cdh(pZip, file_index);

  if (!mz_zip_file_stat_internal(pZip, file_index, pCentral_dir_header,
                                 &file_stat, &found_zip64_ext_data_in_cdir))
    return MZ_FALSE;

  /* A directory or zero length file */
  if ((file_stat.m_is_directory) || (!file_stat.m_uncomp_size))
    return MZ_TRUE;

  /* Encryption and patch files are not supported. */
  if (file_stat.m_is_encrypted)
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_ENCRYPTION);

  /* This function only supports stored and deflate. */
  if ((file_stat.m_method != 0) && (file_stat.m_method != MZ_DEFLATED))
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_METHOD);

  if (!file_stat.m_is_supported)
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_FEATURE);

  /* Read and parse the local directory entry. */
  local_header_ofs = file_stat.m_local_header_ofs;
  if (pZip->m_pRead(pZip->m_pIO_opaque, local_header_ofs, pLocal_header,
                    MZ_ZIP_LOCAL_DIR_HEADER_SIZE) !=
      MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);

  if (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

  local_header_filename_len =
      MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS);
  local_header_extra_len =
      MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  local_header_comp_size =
      MZ_READ_LE32(pLocal_header + MZ_ZIP_LDH_COMPRESSED_SIZE_OFS);
  local_header_uncomp_size =
      MZ_READ_LE32(pLocal_header + MZ_ZIP_LDH_DECOMPRESSED_SIZE_OFS);
  local_header_crc32 = MZ_READ_LE32(pLocal_header + MZ_ZIP_LDH_CRC32_OFS);
  local_header_bit_flags =
      MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_BIT_FLAG_OFS);
  has_data_descriptor = (local_header_bit_flags & 8) != 0;

  if (local_header_filename_len != strlen(file_stat.m_filename))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

  if ((local_header_ofs + MZ_ZIP_LOCAL_DIR_HEADER_SIZE +
       local_header_filename_len + local_header_extra_len +
       file_stat.m_comp_size) > pZip->m_archive_size)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

  if (!mz_zip_array_resize(
          pZip, &file_data_array,
          MZ_MAX(local_header_filename_len, local_header_extra_len),
          MZ_FALSE)) {
    mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
    goto handle_failure;
  }

  if (local_header_filename_len) {
    if (pZip->m_pRead(pZip->m_pIO_opaque,
                      local_header_ofs + MZ_ZIP_LOCAL_DIR_HEADER_SIZE,
                      file_data_array.m_p,
                      local_header_filename_len) != local_header_filename_len) {
      mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);
      goto handle_failure;
    }

    /* I've seen 1 archive that had the same pathname, but used backslashes in
     * the local dir and forward slashes in the central dir. Do we care about
     * this? For now, this case will fail validation. */
    if (memcmp(file_stat.m_filename, file_data_array.m_p,
               local_header_filename_len) != 0) {
      mz_zip_set_error(pZip, MZ_ZIP_VALIDATION_FAILED);
      goto handle_failure;
    }
  }

  if ((local_header_extra_len) &&
      ((local_header_comp_size == MZ_UINT32_MAX) ||
       (local_header_uncomp_size == MZ_UINT32_MAX))) {
    mz_uint32 extra_size_remaining = local_header_extra_len;
    const mz_uint8 *pExtra_data = (const mz_uint8 *)file_data_array.m_p;

    if (pZip->m_pRead(pZip->m_pIO_opaque,
                      local_header_ofs + MZ_ZIP_LOCAL_DIR_HEADER_SIZE +
                          local_header_filename_len,
                      file_data_array.m_p,
                      local_header_extra_len) != local_header_extra_len) {
      mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);
      goto handle_failure;
    }

    do {
      mz_uint32 field_id, field_data_size, field_total_size;

      if (extra_size_remaining < (sizeof(mz_uint16) * 2)) {
        mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);
        goto handle_failure;
      }

      field_id = MZ_READ_LE16(pExtra_data);
      field_data_size = MZ_READ_LE16(pExtra_data + sizeof(mz_uint16));
      field_total_size = field_data_size + sizeof(mz_uint16) * 2;

      if (field_total_size > extra_size_remaining) {
        mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);
        goto handle_failure;
      }

      if (field_id == MZ_ZIP64_EXTENDED_INFORMATION_FIELD_HEADER_ID) {
        const mz_uint8 *pSrc_field_data = pExtra_data + sizeof(mz_uint32);

        if (field_data_size < sizeof(mz_uint64) * 2) {
          mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);
          goto handle_failure;
        }

        local_header_uncomp_size = MZ_READ_LE64(pSrc_field_data);
        local_header_comp_size =
            MZ_READ_LE64(pSrc_field_data + sizeof(mz_uint64));

        found_zip64_ext_data_in_ldir = MZ_TRUE;
        break;
      }

      pExtra_data += field_total_size;
      extra_size_remaining -= field_total_size;
    } while (extra_size_remaining);
  }

  /* TODO: parse local header extra data when local_header_comp_size is
   * 0xFFFFFFFF! (big_descriptor.zip) */
  /* I've seen zips in the wild with the data descriptor bit set, but proper
   * local header values and bogus data descriptors */
  if ((has_data_descriptor) && (!local_header_comp_size) &&
      (!local_header_crc32)) {
    mz_uint8 descriptor_buf[32];
    mz_bool has_id;
    const mz_uint8 *pSrc;
    mz_uint32 file_crc32;
    mz_uint64 comp_size = 0, uncomp_size = 0;

    mz_uint32 num_descriptor_uint32s =
        ((pState->m_zip64) || (found_zip64_ext_data_in_ldir)) ? 6 : 4;

    if (pZip->m_pRead(pZip->m_pIO_opaque,
                      local_header_ofs + MZ_ZIP_LOCAL_DIR_HEADER_SIZE +
                          local_header_filename_len + local_header_extra_len +
                          file_stat.m_comp_size,
                      descriptor_buf,
                      sizeof(mz_uint32) * num_descriptor_uint32s) !=
        (sizeof(mz_uint32) * num_descriptor_uint32s)) {
      mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);
      goto handle_failure;
    }

    has_id = (MZ_READ_LE32(descriptor_buf) == MZ_ZIP_DATA_DESCRIPTOR_ID);
    pSrc = has_id ? (descriptor_buf + sizeof(mz_uint32)) : descriptor_buf;

    file_crc32 = MZ_READ_LE32(pSrc);

    if ((pState->m_zip64) || (found_zip64_ext_data_in_ldir)) {
      comp_size = MZ_READ_LE64(pSrc + sizeof(mz_uint32));
      uncomp_size = MZ_READ_LE64(pSrc + sizeof(mz_uint32) + sizeof(mz_uint64));
    } else {
      comp_size = MZ_READ_LE32(pSrc + sizeof(mz_uint32));
      uncomp_size = MZ_READ_LE32(pSrc + sizeof(mz_uint32) + sizeof(mz_uint32));
    }

    if ((file_crc32 != file_stat.m_crc32) ||
        (comp_size != file_stat.m_comp_size) ||
        (uncomp_size != file_stat.m_uncomp_size)) {
      mz_zip_set_error(pZip, MZ_ZIP_VALIDATION_FAILED);
      goto handle_failure;
    }
  } else {
    if ((local_header_crc32 != file_stat.m_crc32) ||
        (local_header_comp_size != file_stat.m_comp_size) ||
        (local_header_uncomp_size != file_stat.m_uncomp_size)) {
      mz_zip_set_error(pZip, MZ_ZIP_VALIDATION_FAILED);
      goto handle_failure;
    }
  }

  mz_zip_array_clear(pZip, &file_data_array);

  if ((flags & MZ_ZIP_FLAG_VALIDATE_HEADERS_ONLY) == 0) {
    if (!mz_zip_reader_extract_to_callback(
            pZip, file_index, mz_zip_compute_crc32_callback, &uncomp_crc32, 0))
      return MZ_FALSE;

    /* 1 more check to be sure, although the extract checks too. */
    if (uncomp_crc32 != file_stat.m_crc32) {
      mz_zip_set_error(pZip, MZ_ZIP_VALIDATION_FAILED);
      return MZ_FALSE;
    }
  }

  return MZ_TRUE;

handle_failure:
  mz_zip_array_clear(pZip, &file_data_array);
  return MZ_FALSE;
}

mz_bool mz_zip_validate_archive(mz_zip_archive *pZip, mz_uint flags) {
  mz_zip_internal_state *pState;
  mz_uint32 i;

  if ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) ||
      (!pZip->m_pRead))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  pState = pZip->m_pState;

  /* Basic sanity checks */
  if (!pState->m_zip64) {
    if (pZip->m_total_files > MZ_UINT16_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_ARCHIVE_TOO_LARGE);

    if (pZip->m_archive_size > MZ_UINT32_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_ARCHIVE_TOO_LARGE);
  } else {
    if (pState->m_central_dir.m_size >= MZ_UINT32_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_ARCHIVE_TOO_LARGE);
  }

  for (i = 0; i < pZip->m_total_files; i++) {
    if (MZ_ZIP_FLAG_VALIDATE_LOCATE_FILE_FLAG & flags) {
      mz_uint32 found_index;
      mz_zip_archive_file_stat stat;

      if (!mz_zip_reader_file_stat(pZip, i, &stat))
        return MZ_FALSE;

      if (!mz_zip_reader_locate_file_v2(pZip, stat.m_filename, NULL, 0,
                                        &found_index))
        return MZ_FALSE;

      /* This check can fail if there are duplicate filenames in the archive
       * (which we don't check for when writing - that's up to the user) */
      if (found_index != i)
        return mz_zip_set_error(pZip, MZ_ZIP_VALIDATION_FAILED);
    }

    if (!mz_zip_validate_file(pZip, i, flags))
      return MZ_FALSE;
  }

  return MZ_TRUE;
}

mz_bool mz_zip_validate_mem_archive(const void *pMem, size_t size,
                                    mz_uint flags, mz_zip_error *pErr) {
  mz_bool success = MZ_TRUE;
  mz_zip_archive zip;
  mz_zip_error actual_err = MZ_ZIP_NO_ERROR;

  if ((!pMem) || (!size)) {
    if (pErr)
      *pErr = MZ_ZIP_INVALID_PARAMETER;
    return MZ_FALSE;
  }

  mz_zip_zero_struct(&zip);

  if (!mz_zip_reader_init_mem(&zip, pMem, size, flags)) {
    if (pErr)
      *pErr = zip.m_last_error;
    return MZ_FALSE;
  }

  if (!mz_zip_validate_archive(&zip, flags)) {
    actual_err = zip.m_last_error;
    success = MZ_FALSE;
  }

  if (!mz_zip_reader_end_internal(&zip, success)) {
    if (!actual_err)
      actual_err = zip.m_last_error;
    success = MZ_FALSE;
  }

  if (pErr)
    *pErr = actual_err;

  return success;
}

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_validate_file_archive(const char *pFilename, mz_uint flags,
                                     mz_zip_error *pErr) {
  mz_bool success = MZ_TRUE;
  mz_zip_archive zip;
  mz_zip_error actual_err = MZ_ZIP_NO_ERROR;

  if (!pFilename) {
    if (pErr)
      *pErr = MZ_ZIP_INVALID_PARAMETER;
    return MZ_FALSE;
  }

  mz_zip_zero_struct(&zip);

  if (!mz_zip_reader_init_file_v2(&zip, pFilename, flags, 0, 0)) {
    if (pErr)
      *pErr = zip.m_last_error;
    return MZ_FALSE;
  }

  if (!mz_zip_validate_archive(&zip, flags)) {
    actual_err = zip.m_last_error;
    success = MZ_FALSE;
  }

  if (!mz_zip_reader_end_internal(&zip, success)) {
    if (!actual_err)
      actual_err = zip.m_last_error;
    success = MZ_FALSE;
  }

  if (pErr)
    *pErr = actual_err;

  return success;
}
#endif /* #ifndef MINIZ_NO_STDIO */

/* ------------------- .ZIP archive writing */

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

static MZ_FORCEINLINE void mz_write_le16(mz_uint8 *p, mz_uint16 v) {
  p[0] = (mz_uint8)v;
  p[1] = (mz_uint8)(v >> 8);
}
static MZ_FORCEINLINE void mz_write_le32(mz_uint8 *p, mz_uint32 v) {
  p[0] = (mz_uint8)v;
  p[1] = (mz_uint8)(v >> 8);
  p[2] = (mz_uint8)(v >> 16);
  p[3] = (mz_uint8)(v >> 24);
}
static MZ_FORCEINLINE void mz_write_le64(mz_uint8 *p, mz_uint64 v) {
  mz_write_le32(p, (mz_uint32)v);
  mz_write_le32(p + sizeof(mz_uint32), (mz_uint32)(v >> 32));
}

#define MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#define MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))
#define MZ_WRITE_LE64(p, v) mz_write_le64((mz_uint8 *)(p), (mz_uint64)(v))

static size_t mz_zip_heap_write_func(void *pOpaque, mz_uint64 file_ofs,
                                     const void *pBuf, size_t n) {
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_internal_state *pState = pZip->m_pState;
  mz_uint64 new_size = MZ_MAX(file_ofs + n, pState->m_mem_size);

  if (!n)
    return 0;

  /* An allocation this big is likely to just fail on 32-bit systems, so don't
   * even go there. */
  if ((sizeof(size_t) == sizeof(mz_uint32)) && (new_size > 0x7FFFFFFF)) {
    mz_zip_set_error(pZip, MZ_ZIP_FILE_TOO_LARGE);
    return 0;
  }

  if (new_size > pState->m_mem_capacity) {
    void *pNew_block;
    size_t new_capacity = MZ_MAX(64, pState->m_mem_capacity);

    while (new_capacity < new_size)
      new_capacity *= 2;

    if (NULL == (pNew_block = pZip->m_pRealloc(
                     pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_capacity))) {
      mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
      return 0;
    }

    pState->m_pMem = pNew_block;
    pState->m_mem_capacity = new_capacity;
  }
  memcpy((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_size = (size_t)new_size;
  return n;
}

static mz_bool mz_zip_writer_end_internal(mz_zip_archive *pZip,
                                          mz_bool set_last_error) {
  mz_zip_internal_state *pState;
  mz_bool status = MZ_TRUE;

  if ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) ||
      ((pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) &&
       (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED))) {
    if (set_last_error)
      mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);
    return MZ_FALSE;
  }

  pState = pZip->m_pState;
  pZip->m_pState = NULL;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ifndef MINIZ_NO_STDIO
  if (pState->m_pFile) {
    if (pZip->m_zip_type == MZ_ZIP_TYPE_FILE) {
      if (MZ_FCLOSE(pState->m_pFile) == EOF) {
        if (set_last_error)
          mz_zip_set_error(pZip, MZ_ZIP_FILE_CLOSE_FAILED);
        status = MZ_FALSE;
      }
    }

    pState->m_pFile = NULL;
  }
#endif /* #ifndef MINIZ_NO_STDIO */

  if ((pZip->m_pWrite == mz_zip_heap_write_func) && (pState->m_pMem)) {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = NULL;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_mode = MZ_ZIP_MODE_INVALID;
  return status;
}

mz_bool mz_zip_writer_init_v2(mz_zip_archive *pZip, mz_uint64 existing_size,
                              mz_uint flags) {
  mz_bool zip64 = (flags & MZ_ZIP_FLAG_WRITE_ZIP64) != 0;

  if ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) ||
      (pZip->m_zip_mode != MZ_ZIP_MODE_INVALID))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  if (flags & MZ_ZIP_FLAG_WRITE_ALLOW_READING) {
    if (!pZip->m_pRead)
      return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);
  }

  if (pZip->m_file_offset_alignment) {
    /* Ensure user specified file offset alignment is a power of 2. */
    if (pZip->m_file_offset_alignment & (pZip->m_file_offset_alignment - 1))
      return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);
  }

  if (!pZip->m_pAlloc)
    pZip->m_pAlloc = miniz_def_alloc_func;
  if (!pZip->m_pFree)
    pZip->m_pFree = miniz_def_free_func;
  if (!pZip->m_pRealloc)
    pZip->m_pRealloc = miniz_def_realloc_func;

  pZip->m_archive_size = existing_size;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_total_files = 0;

  if (NULL == (pZip->m_pState = (mz_zip_internal_state *)pZip->m_pAlloc(
                   pZip->m_pAlloc_opaque, 1, sizeof(mz_zip_internal_state))))
    return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);

  memset(pZip->m_pState, 0, sizeof(mz_zip_internal_state));

  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir,
                                sizeof(mz_uint8));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir_offsets,
                                sizeof(mz_uint32));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_sorted_central_dir_offsets,
                                sizeof(mz_uint32));

  pZip->m_pState->m_zip64 = zip64;
  pZip->m_pState->m_zip64_has_extended_info_fields = zip64;

  pZip->m_zip_type = MZ_ZIP_TYPE_USER;
  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING;

  return MZ_TRUE;
}

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_size) {
  return mz_zip_writer_init_v2(pZip, existing_size, 0);
}

mz_bool mz_zip_writer_init_heap_v2(mz_zip_archive *pZip,
                                   size_t size_to_reserve_at_beginning,
                                   size_t initial_allocation_size,
                                   mz_uint flags) {
  pZip->m_pWrite = mz_zip_heap_write_func;
  pZip->m_pNeeds_keepalive = NULL;

  if (flags & MZ_ZIP_FLAG_WRITE_ALLOW_READING)
    pZip->m_pRead = mz_zip_mem_read_func;

  pZip->m_pIO_opaque = pZip;

  if (!mz_zip_writer_init_v2(pZip, size_to_reserve_at_beginning, flags))
    return MZ_FALSE;

  pZip->m_zip_type = MZ_ZIP_TYPE_HEAP;

  if (0 != (initial_allocation_size = MZ_MAX(initial_allocation_size,
                                             size_to_reserve_at_beginning))) {
    if (NULL == (pZip->m_pState->m_pMem = pZip->m_pAlloc(
                     pZip->m_pAlloc_opaque, 1, initial_allocation_size))) {
      mz_zip_writer_end_internal(pZip, MZ_FALSE);
      return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
    }
    pZip->m_pState->m_mem_capacity = initial_allocation_size;
  }

  return MZ_TRUE;
}

mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip,
                                size_t size_to_reserve_at_beginning,
                                size_t initial_allocation_size) {
  return mz_zip_writer_init_heap_v2(pZip, size_to_reserve_at_beginning,
                                    initial_allocation_size, 0);
}

#ifndef MINIZ_NO_STDIO
static size_t mz_zip_file_write_func(void *pOpaque, mz_uint64 file_ofs,
                                     const void *pBuf, size_t n) {
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);

  file_ofs += pZip->m_pState->m_file_archive_start_ofs;

  if (((mz_int64)file_ofs < 0) ||
      (((cur_ofs != (mz_int64)file_ofs)) &&
       (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET)))) {
    mz_zip_set_error(pZip, MZ_ZIP_FILE_SEEK_FAILED);
    return 0;
  }

  return MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, const char *pFilename,
                                mz_uint64 size_to_reserve_at_beginning) {
  return mz_zip_writer_init_file_v2(pZip, pFilename,
                                    size_to_reserve_at_beginning, 0);
}

mz_bool mz_zip_writer_init_file_v2(mz_zip_archive *pZip, const char *pFilename,
                                   mz_uint64 size_to_reserve_at_beginning,
                                   mz_uint flags) {
  MZ_FILE *pFile;

  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pNeeds_keepalive = NULL;

  if (flags & MZ_ZIP_FLAG_WRITE_ALLOW_READING)
    pZip->m_pRead = mz_zip_file_read_func;

  pZip->m_pIO_opaque = pZip;

  if (!mz_zip_writer_init_v2(pZip, size_to_reserve_at_beginning, flags))
    return MZ_FALSE;

  if (NULL == (pFile = MZ_FOPEN(
                   pFilename,
                   (flags & MZ_ZIP_FLAG_WRITE_ALLOW_READING) ? "w+b" : "wb"))) {
    mz_zip_writer_end(pZip);
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_OPEN_FAILED);
  }

  pZip->m_pState->m_pFile = pFile;
  pZip->m_zip_type = MZ_ZIP_TYPE_FILE;

  if (size_to_reserve_at_beginning) {
    mz_uint64 cur_ofs = 0;
    char buf[4096];

    MZ_CLEAR_ARR(buf);

    do {
      size_t n = (size_t)MZ_MIN(sizeof(buf), size_to_reserve_at_beginning);
      if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n) {
        mz_zip_writer_end(pZip);
        return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);
      }
      cur_ofs += n;
      size_to_reserve_at_beginning -= n;
    } while (size_to_reserve_at_beginning);
  }

  return MZ_TRUE;
}

mz_bool mz_zip_writer_init_cfile(mz_zip_archive *pZip, MZ_FILE *pFile,
                                 mz_uint flags) {
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pNeeds_keepalive = NULL;

  if (flags & MZ_ZIP_FLAG_WRITE_ALLOW_READING)
    pZip->m_pRead = mz_zip_file_read_func;

  pZip->m_pIO_opaque = pZip;

  if (!mz_zip_writer_init_v2(pZip, 0, flags))
    return MZ_FALSE;

  pZip->m_pState->m_pFile = pFile;
  pZip->m_pState->m_file_archive_start_ofs =
      MZ_FTELL64(pZip->m_pState->m_pFile);
  pZip->m_zip_type = MZ_ZIP_TYPE_CFILE;

  return MZ_TRUE;
}
#endif /* #ifndef MINIZ_NO_STDIO */

mz_bool mz_zip_writer_init_from_reader_v2(mz_zip_archive *pZip,
                                          const char *pFilename,
                                          mz_uint flags) {
  mz_zip_internal_state *pState;

  if ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  if (flags & MZ_ZIP_FLAG_WRITE_ZIP64) {
    /* We don't support converting a non-zip64 file to zip64 - this seems like
     * more trouble than it's worth. (What about the existing 32-bit data
     * descriptors that could follow the compressed data?) */
    if (!pZip->m_pState->m_zip64)
      return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);
  }

  /* No sense in trying to write to an archive that's already at the support
   * max size */
  if (pZip->m_pState->m_zip64) {
    if (pZip->m_total_files == MZ_UINT32_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_TOO_MANY_FILES);
  } else {
    if (pZip->m_total_files == MZ_UINT16_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_TOO_MANY_FILES);

    if ((pZip->m_archive_size + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE +
         MZ_ZIP_LOCAL_DIR_HEADER_SIZE) > MZ_UINT32_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_TOO_LARGE);
  }

  pState = pZip->m_pState;

  if (pState->m_pFile) {
#ifdef MINIZ_NO_STDIO
    (void)pFilename;
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);
#else
    if (pZip->m_pIO_opaque != pZip)
      return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

    if (pZip->m_zip_type == MZ_ZIP_TYPE_FILE) {
      if (!pFilename)
        return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

      /* Archive is being read from stdio and was originally opened only for
       * reading. Try to reopen as writable. */
      if (NULL ==
          (pState->m_pFile = MZ_FREOPEN(pFilename, "r+b", pState->m_pFile))) {
        /* The mz_zip_archive is now in a bogus state because pState->m_pFile
         * is NULL, so just close it. */
        mz_zip_reader_end_internal(pZip, MZ_FALSE);
        return mz_zip_set_error(pZip, MZ_ZIP_FILE_OPEN_FAILED);
      }
    }

    pZip->m_pWrite = mz_zip_file_write_func;
    pZip->m_pNeeds_keepalive = NULL;
#endif /* #ifdef MINIZ_NO_STDIO */
  } else if (pState->m_pMem) {
    /* Archive lives in a memory block. Assume it's from the heap that we can
     * resize using the realloc callback. */
    if (pZip->m_pIO_opaque != pZip)
      return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

    pState->m_mem_capacity = pState->m_mem_size;
    pZip->m_pWrite = mz_zip_heap_write_func;
    pZip->m_pNeeds_keepalive = NULL;
  }
  /* Archive is being read via a user provided read function - make sure the
     user has specified a write function too. */
  else if (!pZip->m_pWrite)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  /* Start writing new files at the archive's current central directory
   * location. */
  /* TODO: We could add a flag that lets the user start writing immediately
   * AFTER the existing central dir - this would be safer. */
  pZip->m_archive_size = pZip->m_central_directory_file_ofs;
  pZip->m_central_directory_file_ofs = 0;

  /* Clear the sorted central dir offsets, they aren't useful or maintained
   * now.
   */
  /* Even though we're now in write mode, files can still be extracted and
   * verified, but file locates will be slow. */
  /* TODO: We could easily maintain the sorted central directory offsets. */
  mz_zip_array_clear(pZip, &pZip->m_pState->m_sorted_central_dir_offsets);

  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING;

  return MZ_TRUE;
}

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip,
                                       const char *pFilename) {
  return mz_zip_writer_init_from_reader_v2(pZip, pFilename, 0);
}

/* TODO: pArchive_name is a terrible name here! */
mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, const char *pArchive_name,
                              const void *pBuf, size_t buf_size,
                              mz_uint level_and_flags) {
  return mz_zip_writer_add_mem_ex(pZip, pArchive_name, pBuf, buf_size, NULL, 0,
                                  level_and_flags, 0, 0);
}

typedef struct {
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_size;
} mz_zip_writer_add_state;

static mz_bool mz_zip_writer_add_put_buf_callback(const void *pBuf, int len,
                                                  void *pUser) {
  mz_zip_writer_add_state *pState = (mz_zip_writer_add_state *)pUser;
  if ((int)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque,
                                    pState->m_cur_archive_file_ofs, pBuf,
                                    len) != len)
    return MZ_FALSE;

  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_size += len;
  return MZ_TRUE;
}

#define MZ_ZIP64_MAX_LOCAL_EXTRA_FIELD_SIZE                                    \
  (sizeof(mz_uint16) * 2 + sizeof(mz_uint64) * 2)
#define MZ_ZIP64_MAX_CENTRAL_EXTRA_FIELD_SIZE                                  \
  (sizeof(mz_uint16) * 2 + sizeof(mz_uint64) * 3)
static mz_uint32
mz_zip_writer_create_zip64_extra_data(mz_uint8 *pBuf, mz_uint64 *pUncomp_size,
                                      mz_uint64 *pComp_size,
                                      mz_uint64 *pLocal_header_ofs) {
  mz_uint8 *pDst = pBuf;
  mz_uint32 field_size = 0;

  MZ_WRITE_LE16(pDst + 0, MZ_ZIP64_EXTENDED_INFORMATION_FIELD_HEADER_ID);
  MZ_WRITE_LE16(pDst + 2, 0);
  pDst += sizeof(mz_uint16) * 2;

  if (pUncomp_size) {
    MZ_WRITE_LE64(pDst, *pUncomp_size);
    pDst += sizeof(mz_uint64);
    field_size += sizeof(mz_uint64);
  }

  if (pComp_size) {
    MZ_WRITE_LE64(pDst, *pComp_size);
    pDst += sizeof(mz_uint64);
    field_size += sizeof(mz_uint64);
  }

  if (pLocal_header_ofs) {
    MZ_WRITE_LE64(pDst, *pLocal_header_ofs);
    pDst += sizeof(mz_uint64);
    field_size += sizeof(mz_uint64);
  }

  MZ_WRITE_LE16(pBuf + 2, field_size);

  return (mz_uint32)(pDst - pBuf);
}

static mz_bool mz_zip_writer_create_local_dir_header(
    mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_size,
    mz_uint16 extra_size, mz_uint64 uncomp_size, mz_uint64 comp_size,
    mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags,
    mz_uint16 dos_time, mz_uint16 dos_date) {
  (void)pZip;
  memset(pDst, 0, MZ_ZIP_LOCAL_DIR_HEADER_SIZE);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_VERSION_NEEDED_OFS, method ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_BIT_FLAG_OFS, bit_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_METHOD_OFS, method);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_TIME_OFS, dos_time);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_CRC32_OFS, uncomp_crc32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_SIZE_OFS,
                MZ_MIN(comp_size, MZ_UINT32_MAX));
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_SIZE_OFS,
                MZ_MIN(uncomp_size, MZ_UINT32_MAX));
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_size);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_size);
  return MZ_TRUE;
}

static mz_bool mz_zip_writer_create_central_dir_header(
    mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_size,
    mz_uint16 extra_size, mz_uint16 comment_size, mz_uint64 uncomp_size,
    mz_uint64 comp_size, mz_uint32 uncomp_crc32, mz_uint16 method,
    mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date,
    mz_uint64 local_header_ofs, mz_uint32 ext_attributes) {
  (void)pZip;
  memset(pDst, 0, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_VERSION_MADE_BY_OFS, 0x031E);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_VERSION_NEEDED_OFS, method ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_BIT_FLAG_OFS, bit_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_METHOD_OFS, method);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_TIME_OFS, dos_time);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_CRC32_OFS, uncomp_crc32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS,
                MZ_MIN(comp_size, MZ_UINT32_MAX));
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS,
                MZ_MIN(uncomp_size, MZ_UINT32_MAX));
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_size);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_size);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_size);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_attributes);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_HEADER_OFS,
                MZ_MIN(local_header_ofs, MZ_UINT32_MAX));
  return MZ_TRUE;
}

static mz_bool mz_zip_writer_add_to_central_dir(
    mz_zip_archive *pZip, const char *pFilename, mz_uint16 filename_size,
    const void *pExtra, mz_uint16 extra_size, const void *pComment,
    mz_uint16 comment_size, mz_uint64 uncomp_size, mz_uint64 comp_size,
    mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags,
    mz_uint16 dos_time, mz_uint16 dos_date, mz_uint64 local_header_ofs,
    mz_uint32 ext_attributes, const char *user_extra_data,
    mz_uint user_extra_data_len) {
  mz_zip_internal_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_size;
  size_t orig_central_dir_size = pState->m_central_dir.m_size;
  mz_uint8 central_dir_header[MZ_ZIP_CENTRAL_DIR_HEADER_SIZE];

  if (!pZip->m_pState->m_zip64) {
    if (local_header_ofs > 0xFFFFFFFF)
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_TOO_LARGE);
  }

  /* miniz doesn't support central dirs >= MZ_UINT32_MAX bytes yet */
  if (((mz_uint64)pState->m_central_dir.m_size +
       MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + filename_size + extra_size +
       user_extra_data_len + comment_size) >= MZ_UINT32_MAX)
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_CDIR_SIZE);

  if (!mz_zip_writer_create_central_dir_header(
          pZip, central_dir_header, filename_size,
          (mz_uint16)(extra_size + user_extra_data_len), comment_size,
          uncomp_size, comp_size, uncomp_crc32, method, bit_flags, dos_time,
          dos_date, local_header_ofs, ext_attributes))
    return mz_zip_set_error(pZip, MZ_ZIP_INTERNAL_ERROR);

  if ((!mz_zip_array_push_back(pZip, &pState->m_central_dir, central_dir_header,
                               MZ_ZIP_CENTRAL_DIR_HEADER_SIZE)) ||
      (!mz_zip_array_push_back(pZip, &pState->m_central_dir, pFilename,
                               filename_size)) ||
      (!mz_zip_array_push_back(pZip, &pState->m_central_dir, pExtra,
                               extra_size)) ||
      (!mz_zip_array_push_back(pZip, &pState->m_central_dir, user_extra_data,
                               user_extra_data_len)) ||
      (!mz_zip_array_push_back(pZip, &pState->m_central_dir, pComment,
                               comment_size)) ||
      (!mz_zip_array_push_back(pZip, &pState->m_central_dir_offsets,
                               &central_dir_ofs, 1))) {
    /* Try to resize the central directory array back into its original state.
     */
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size,
                        MZ_FALSE);
    return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
  }

  return MZ_TRUE;
}

static mz_bool mz_zip_writer_validate_archive_name(const char *pArchive_name) {
  /* Basic ZIP archive filename validity checks: Valid filenames cannot start
   * with a forward slash, cannot contain a drive letter, and cannot use
   * DOS-style backward slashes. */
  if (*pArchive_name == '/')
    return MZ_FALSE;

  /* Making sure the name does not contain drive letters or DOS style backward
   * slashes is the responsibility of the program using miniz*/

  return MZ_TRUE;
}

static mz_uint
mz_zip_writer_compute_padding_needed_for_file_alignment(mz_zip_archive *pZip) {
  mz_uint32 n;
  if (!pZip->m_file_offset_alignment)
    return 0;
  n = (mz_uint32)(pZip->m_archive_size & (pZip->m_file_offset_alignment - 1));
  return (mz_uint)((pZip->m_file_offset_alignment - n) &
                   (pZip->m_file_offset_alignment - 1));
}

static mz_bool mz_zip_writer_write_zeros(mz_zip_archive *pZip,
                                         mz_uint64 cur_file_ofs, mz_uint32 n) {
  char buf[4096];
  memset(buf, 0, MZ_MIN(sizeof(buf), n));
  while (n) {
    mz_uint32 s = MZ_MIN(sizeof(buf), n);
    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_file_ofs, buf, s) != s)
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

    cur_file_ofs += s;
    n -= s;
  }
  return MZ_TRUE;
}

mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip,
                                 const char *pArchive_name, const void *pBuf,
                                 size_t buf_size, const void *pComment,
                                 mz_uint16 comment_size,
                                 mz_uint level_and_flags, mz_uint64 uncomp_size,
                                 mz_uint32 uncomp_crc32) {
  return mz_zip_writer_add_mem_ex_v2(
      pZip, pArchive_name, pBuf, buf_size, pComment, comment_size,
      level_and_flags, uncomp_size, uncomp_crc32, NULL, NULL, 0, NULL, 0);
}

mz_bool mz_zip_writer_add_mem_ex_v2(
    mz_zip_archive *pZip, const char *pArchive_name, const void *pBuf,
    size_t buf_size, const void *pComment, mz_uint16 comment_size,
    mz_uint level_and_flags, mz_uint64 uncomp_size, mz_uint32 uncomp_crc32,
    MZ_TIME_T *last_modified, const char *user_extra_data,
    mz_uint user_extra_data_len, const char *user_extra_data_central,
    mz_uint user_extra_data_central_len) {
  mz_uint16 method = 0, dos_time = 0, dos_date = 0;
  mz_uint level, ext_attributes = 0, num_alignment_padding_bytes;
  mz_uint64 local_dir_header_ofs = pZip->m_archive_size,
            cur_archive_file_ofs = pZip->m_archive_size, comp_size = 0;
  size_t archive_name_size;
  mz_uint8 local_dir_header[MZ_ZIP_LOCAL_DIR_HEADER_SIZE];
  tdefl_compressor *pComp = NULL;
  mz_bool store_data_uncompressed;
  mz_zip_internal_state *pState;
  mz_uint8 *pExtra_data = NULL;
  mz_uint32 extra_size = 0;
  mz_uint8 extra_data[MZ_ZIP64_MAX_CENTRAL_EXTRA_FIELD_SIZE];
  mz_uint16 bit_flags = 0;

  if ((int)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;

  if (uncomp_size ||
      (buf_size && !(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)))
    bit_flags |= MZ_ZIP_LDH_BIT_FLAG_HAS_LOCATOR;

  if (!(level_and_flags & MZ_ZIP_FLAG_ASCII_FILENAME))
    bit_flags |= MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_UTF8;

  level = level_and_flags & 0xF;
  store_data_uncompressed =
      ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA));

  if ((!pZip) || (!pZip->m_pState) ||
      (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || ((buf_size) && (!pBuf)) ||
      (!pArchive_name) || ((comment_size) && (!pComment)) ||
      (level > MZ_UBER_COMPRESSION))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  pState = pZip->m_pState;

  if (pState->m_zip64) {
    if (pZip->m_total_files == MZ_UINT32_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_TOO_MANY_FILES);
  } else {
    if (pZip->m_total_files == MZ_UINT16_MAX) {
      pState->m_zip64 = MZ_TRUE;
      /*return mz_zip_set_error(pZip, MZ_ZIP_TOO_MANY_FILES); */
    }
    if (((mz_uint64)buf_size > 0xFFFFFFFF) || (uncomp_size > 0xFFFFFFFF)) {
      pState->m_zip64 = MZ_TRUE;
      /*return mz_zip_set_error(pZip, MZ_ZIP_ARCHIVE_TOO_LARGE); */
    }
  }

  if ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (uncomp_size))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  if (!mz_zip_writer_validate_archive_name(pArchive_name))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_FILENAME);

#ifndef MINIZ_NO_TIME
  if (last_modified != NULL) {
    mz_zip_time_t_to_dos_time(*last_modified, &dos_time, &dos_date);
  } else {
    MZ_TIME_T cur_time;
    time(&cur_time);
    mz_zip_time_t_to_dos_time(cur_time, &dos_time, &dos_date);
  }
#else
  (void)last_modified;
#endif /* #ifndef MINIZ_NO_TIME */

  if (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) {
    uncomp_crc32 =
        (mz_uint32)mz_crc32(MZ_CRC32_INIT, (const mz_uint8 *)pBuf, buf_size);
    uncomp_size = buf_size;
    if (uncomp_size <= 3) {
      level = 0;
      store_data_uncompressed = MZ_TRUE;
    }
  }

  archive_name_size = strlen(pArchive_name);
  if (archive_name_size > MZ_UINT16_MAX)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_FILENAME);

  num_alignment_padding_bytes =
      mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  /* miniz doesn't support central dirs >= MZ_UINT32_MAX bytes yet */
  if (((mz_uint64)pState->m_central_dir.m_size +
       MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + archive_name_size +
       MZ_ZIP64_MAX_CENTRAL_EXTRA_FIELD_SIZE + comment_size) >= MZ_UINT32_MAX)
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_CDIR_SIZE);

  if (!pState->m_zip64) {
    /* Bail early if the archive would obviously become too large */
    if ((pZip->m_archive_size + num_alignment_padding_bytes +
         MZ_ZIP_LOCAL_DIR_HEADER_SIZE + archive_name_size +
         MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + archive_name_size + comment_size +
         user_extra_data_len + pState->m_central_dir.m_size +
         MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE + user_extra_data_central_len +
         MZ_ZIP_DATA_DESCRIPTER_SIZE32) > 0xFFFFFFFF) {
      pState->m_zip64 = MZ_TRUE;
      /*return mz_zip_set_error(pZip, MZ_ZIP_ARCHIVE_TOO_LARGE); */
    }
  }

  if ((archive_name_size) && (pArchive_name[archive_name_size - 1] == '/')) {
    /* Set DOS Subdirectory attribute bit. */
    ext_attributes |= MZ_ZIP_DOS_DIR_ATTRIBUTE_BITFLAG;

    /* Subdirectories cannot contain data. */
    if ((buf_size) || (uncomp_size))
      return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);
  }

  /* Try to do any allocations before writing to the archive, so if an
   * allocation fails the file remains unmodified. (A good idea if we're doing
   * an in-place modification.) */
  if ((!mz_zip_array_ensure_room(
          pZip, &pState->m_central_dir,
          MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + archive_name_size + comment_size +
              (pState->m_zip64 ? MZ_ZIP64_MAX_CENTRAL_EXTRA_FIELD_SIZE : 0))) ||
      (!mz_zip_array_ensure_room(pZip, &pState->m_central_dir_offsets, 1)))
    return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);

  if ((!store_data_uncompressed) && (buf_size)) {
    if (NULL == (pComp = (tdefl_compressor *)pZip->m_pAlloc(
                     pZip->m_pAlloc_opaque, 1, sizeof(tdefl_compressor))))
      return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
  }

  if (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs,
                                 num_alignment_padding_bytes)) {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    return MZ_FALSE;
  }

  local_dir_header_ofs += num_alignment_padding_bytes;
  if (pZip->m_file_offset_alignment) {
    MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) ==
              0);
  }
  cur_archive_file_ofs += num_alignment_padding_bytes;

  MZ_CLEAR_ARR(local_dir_header);

  if (!store_data_uncompressed ||
      (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) {
    method = MZ_DEFLATED;
  }

  if (pState->m_zip64) {
    if (uncomp_size >= MZ_UINT32_MAX || local_dir_header_ofs >= MZ_UINT32_MAX) {
      pExtra_data = extra_data;
      extra_size = mz_zip_writer_create_zip64_extra_data(
          extra_data, (uncomp_size >= MZ_UINT32_MAX) ? &uncomp_size : NULL,
          (uncomp_size >= MZ_UINT32_MAX) ? &comp_size : NULL,
          (local_dir_header_ofs >= MZ_UINT32_MAX) ? &local_dir_header_ofs
                                                  : NULL);
    }

    if (!mz_zip_writer_create_local_dir_header(
            pZip, local_dir_header, (mz_uint16)archive_name_size,
            (mz_uint16)(extra_size + user_extra_data_len), 0, 0, 0, method,
            bit_flags, dos_time, dos_date))
      return mz_zip_set_error(pZip, MZ_ZIP_INTERNAL_ERROR);

    if (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_header_ofs,
                       local_dir_header,
                       sizeof(local_dir_header)) != sizeof(local_dir_header))
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

    cur_archive_file_ofs += sizeof(local_dir_header);

    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name,
                       archive_name_size) != archive_name_size) {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);
    }
    cur_archive_file_ofs += archive_name_size;

    if (pExtra_data != NULL) {
      if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, extra_data,
                         extra_size) != extra_size)
        return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

      cur_archive_file_ofs += extra_size;
    }
  } else {
    if ((comp_size > MZ_UINT32_MAX) || (cur_archive_file_ofs > MZ_UINT32_MAX))
      return mz_zip_set_error(pZip, MZ_ZIP_ARCHIVE_TOO_LARGE);
    if (!mz_zip_writer_create_local_dir_header(
            pZip, local_dir_header, (mz_uint16)archive_name_size,
            (mz_uint16)user_extra_data_len, 0, 0, 0, method, bit_flags,
            dos_time, dos_date))
      return mz_zip_set_error(pZip, MZ_ZIP_INTERNAL_ERROR);

    if (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_header_ofs,
                       local_dir_header,
                       sizeof(local_dir_header)) != sizeof(local_dir_header))
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

    cur_archive_file_ofs += sizeof(local_dir_header);

    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name,
                       archive_name_size) != archive_name_size) {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);
    }
    cur_archive_file_ofs += archive_name_size;
  }

  if (user_extra_data_len > 0) {
    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs,
                       user_extra_data,
                       user_extra_data_len) != user_extra_data_len)
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

    cur_archive_file_ofs += user_extra_data_len;
  }

  if (store_data_uncompressed) {
    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf,
                       buf_size) != buf_size) {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);
    }

    cur_archive_file_ofs += buf_size;
    comp_size = buf_size;
  } else if (buf_size) {
    mz_zip_writer_add_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_size = 0;

    if ((tdefl_init(pComp, mz_zip_writer_add_put_buf_callback, &state,
                    tdefl_create_comp_flags_from_zip_params(
                        level, -15, MZ_DEFAULT_STRATEGY)) !=
         TDEFL_STATUS_OKAY) ||
        (tdefl_compress_buffer(pComp, pBuf, buf_size, TDEFL_FINISH) !=
         TDEFL_STATUS_DONE)) {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      return mz_zip_set_error(pZip, MZ_ZIP_COMPRESSION_FAILED);
    }

    comp_size = state.m_comp_size;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = NULL;

  if (uncomp_size) {
    mz_uint8 local_dir_footer[MZ_ZIP_DATA_DESCRIPTER_SIZE64];
    mz_uint32 local_dir_footer_size = MZ_ZIP_DATA_DESCRIPTER_SIZE32;

    MZ_ASSERT(bit_flags & MZ_ZIP_LDH_BIT_FLAG_HAS_LOCATOR);

    MZ_WRITE_LE32(local_dir_footer + 0, MZ_ZIP_DATA_DESCRIPTOR_ID);
    MZ_WRITE_LE32(local_dir_footer + 4, uncomp_crc32);
    if (pExtra_data == NULL) {
      if (comp_size > MZ_UINT32_MAX)
        return mz_zip_set_error(pZip, MZ_ZIP_ARCHIVE_TOO_LARGE);

      MZ_WRITE_LE32(local_dir_footer + 8, comp_size);
      MZ_WRITE_LE32(local_dir_footer + 12, uncomp_size);
    } else {
      MZ_WRITE_LE64(local_dir_footer + 8, comp_size);
      MZ_WRITE_LE64(local_dir_footer + 16, uncomp_size);
      local_dir_footer_size = MZ_ZIP_DATA_DESCRIPTER_SIZE64;
    }

    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs,
                       local_dir_footer,
                       local_dir_footer_size) != local_dir_footer_size)
      return MZ_FALSE;

    cur_archive_file_ofs += local_dir_footer_size;
  }

  if (pExtra_data != NULL) {
    extra_size = mz_zip_writer_create_zip64_extra_data(
        extra_data, (uncomp_size >= MZ_UINT32_MAX) ? &uncomp_size : NULL,
        (uncomp_size >= MZ_UINT32_MAX) ? &comp_size : NULL,
        (local_dir_header_ofs >= MZ_UINT32_MAX) ? &local_dir_header_ofs : NULL);
  }

  if (!mz_zip_writer_add_to_central_dir(
          pZip, pArchive_name, (mz_uint16)archive_name_size, pExtra_data,
          (mz_uint16)extra_size, pComment, comment_size, uncomp_size, comp_size,
          uncomp_crc32, method, bit_flags, dos_time, dos_date,
          local_dir_header_ofs, ext_attributes, user_extra_data_central,
          user_extra_data_central_len))
    return MZ_FALSE;

  pZip->m_total_files++;
  pZip->m_archive_size = cur_archive_file_ofs;

  return MZ_TRUE;
}

mz_bool mz_zip_writer_add_read_buf_callback(
    mz_zip_archive *pZip, const char *pArchive_name,
    mz_file_read_func read_callback, void *callback_opaque, mz_uint64 max_size,
    const MZ_TIME_T *pFile_time, const void *pComment, mz_uint16 comment_size,
    mz_uint level_and_flags, mz_uint32 ext_attributes,
    const char *user_extra_data, mz_uint user_extra_data_len,
    const char *user_extra_data_central, mz_uint user_extra_data_central_len) {
  mz_uint16 gen_flags;
  mz_uint uncomp_crc32 = MZ_CRC32_INIT, level, num_alignment_padding_bytes;
  mz_uint16 method = 0, dos_time = 0, dos_date = 0;
  mz_uint64 local_dir_header_ofs, cur_archive_file_ofs = pZip->m_archive_size,
                                  uncomp_size = 0, comp_size = 0;
  size_t archive_name_size;
  mz_uint8 local_dir_header[MZ_ZIP_LOCAL_DIR_HEADER_SIZE];
  mz_uint8 *pExtra_data = NULL;
  mz_uint32 extra_size = 0;
  mz_uint8 extra_data[MZ_ZIP64_MAX_CENTRAL_EXTRA_FIELD_SIZE];
  mz_zip_internal_state *pState;
  mz_uint64 file_ofs = 0, cur_archive_header_file_ofs;

  if ((int)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  gen_flags = (level_and_flags & MZ_ZIP_FLAG_WRITE_HEADER_SET_SIZE)
                  ? 0
                  : MZ_ZIP_LDH_BIT_FLAG_HAS_LOCATOR;

  if (!(level_and_flags & MZ_ZIP_FLAG_ASCII_FILENAME))
    gen_flags |= MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_UTF8;

  /* Sanity checks */
  if ((!pZip) || (!pZip->m_pState) ||
      (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || (!pArchive_name) ||
      ((comment_size) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  pState = pZip->m_pState;

  if ((!pState->m_zip64) && (max_size > MZ_UINT32_MAX)) {
    /* Source file is too large for non-zip64 */
    /*return mz_zip_set_error(pZip, MZ_ZIP_ARCHIVE_TOO_LARGE); */
    pState->m_zip64 = MZ_TRUE;
  }

  /* We could support this, but why? */
  if (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  if (!mz_zip_writer_validate_archive_name(pArchive_name))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_FILENAME);

  if (pState->m_zip64) {
    if (pZip->m_total_files == MZ_UINT32_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_TOO_MANY_FILES);
  } else {
    if (pZip->m_total_files == MZ_UINT16_MAX) {
      pState->m_zip64 = MZ_TRUE;
      /*return mz_zip_set_error(pZip, MZ_ZIP_TOO_MANY_FILES); */
    }
  }

  archive_name_size = strlen(pArchive_name);
  if (archive_name_size > MZ_UINT16_MAX)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_FILENAME);

  num_alignment_padding_bytes =
      mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  /* miniz doesn't support central dirs >= MZ_UINT32_MAX bytes yet */
  if (((mz_uint64)pState->m_central_dir.m_size +
       MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + archive_name_size +
       MZ_ZIP64_MAX_CENTRAL_EXTRA_FIELD_SIZE + comment_size) >= MZ_UINT32_MAX)
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_CDIR_SIZE);

  if (!pState->m_zip64) {
    /* Bail early if the archive would obviously become too large */
    if ((pZip->m_archive_size + num_alignment_padding_bytes +
         MZ_ZIP_LOCAL_DIR_HEADER_SIZE + archive_name_size +
         MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + archive_name_size + comment_size +
         user_extra_data_len + pState->m_central_dir.m_size +
         MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE + 1024 +
         MZ_ZIP_DATA_DESCRIPTER_SIZE32 + user_extra_data_central_len) >
        0xFFFFFFFF) {
      pState->m_zip64 = MZ_TRUE;
      /*return mz_zip_set_error(pZip, MZ_ZIP_ARCHIVE_TOO_LARGE); */
    }
  }

#ifndef MINIZ_NO_TIME
  if (pFile_time) {
    mz_zip_time_t_to_dos_time(*pFile_time, &dos_time, &dos_date);
  }
#else
  (void)pFile_time;
#endif

  if (max_size <= 3)
    level = 0;

  if (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs,
                                 num_alignment_padding_bytes)) {
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);
  }

  cur_archive_file_ofs += num_alignment_padding_bytes;
  local_dir_header_ofs = cur_archive_file_ofs;

  if (pZip->m_file_offset_alignment) {
    MZ_ASSERT((cur_archive_file_ofs & (pZip->m_file_offset_alignment - 1)) ==
              0);
  }

  if (max_size && level) {
    method = MZ_DEFLATED;
  }

  MZ_CLEAR_ARR(local_dir_header);
  if (pState->m_zip64) {
    if (max_size >= MZ_UINT32_MAX || local_dir_header_ofs >= MZ_UINT32_MAX) {
      pExtra_data = extra_data;
      if (level_and_flags & MZ_ZIP_FLAG_WRITE_HEADER_SET_SIZE)
        extra_size = mz_zip_writer_create_zip64_extra_data(
            extra_data, (max_size >= MZ_UINT32_MAX) ? &uncomp_size : NULL,
            (max_size >= MZ_UINT32_MAX) ? &comp_size : NULL,
            (local_dir_header_ofs >= MZ_UINT32_MAX) ? &local_dir_header_ofs
                                                    : NULL);
      else
        extra_size = mz_zip_writer_create_zip64_extra_data(
            extra_data, NULL, NULL,
            (local_dir_header_ofs >= MZ_UINT32_MAX) ? &local_dir_header_ofs
                                                    : NULL);
    }

    if (!mz_zip_writer_create_local_dir_header(
            pZip, local_dir_header, (mz_uint16)archive_name_size,
            (mz_uint16)(extra_size + user_extra_data_len), 0, 0, 0, method,
            gen_flags, dos_time, dos_date))
      return mz_zip_set_error(pZip, MZ_ZIP_INTERNAL_ERROR);

    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs,
                       local_dir_header,
                       sizeof(local_dir_header)) != sizeof(local_dir_header))
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

    cur_archive_file_ofs += sizeof(local_dir_header);

    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name,
                       archive_name_size) != archive_name_size) {
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);
    }

    cur_archive_file_ofs += archive_name_size;

    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, extra_data,
                       extra_size) != extra_size)
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

    cur_archive_file_ofs += extra_size;
  } else {
    if ((comp_size > MZ_UINT32_MAX) || (cur_archive_file_ofs > MZ_UINT32_MAX))
      return mz_zip_set_error(pZip, MZ_ZIP_ARCHIVE_TOO_LARGE);
    if (!mz_zip_writer_create_local_dir_header(
            pZip, local_dir_header, (mz_uint16)archive_name_size,
            (mz_uint16)user_extra_data_len, 0, 0, 0, method, gen_flags,
            dos_time, dos_date))
      return mz_zip_set_error(pZip, MZ_ZIP_INTERNAL_ERROR);

    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs,
                       local_dir_header,
                       sizeof(local_dir_header)) != sizeof(local_dir_header))
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

    cur_archive_file_ofs += sizeof(local_dir_header);

    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name,
                       archive_name_size) != archive_name_size) {
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);
    }

    cur_archive_file_ofs += archive_name_size;
  }

  if (user_extra_data_len > 0) {
    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs,
                       user_extra_data,
                       user_extra_data_len) != user_extra_data_len)
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

    cur_archive_file_ofs += user_extra_data_len;
  }

  if (max_size) {
    void *pRead_buf =
        pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_SIZE);
    if (!pRead_buf) {
      return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
    }

    if (!level) {
      while (1) {
        size_t n = read_callback(callback_opaque, file_ofs, pRead_buf,
                                 MZ_ZIP_MAX_IO_BUF_SIZE);
        if (n == 0)
          break;

        if ((n > MZ_ZIP_MAX_IO_BUF_SIZE) || (file_ofs + n > max_size)) {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          return mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);
        }
        if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf,
                           n) != n) {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);
        }
        file_ofs += n;
        uncomp_crc32 =
            (mz_uint32)mz_crc32(uncomp_crc32, (const mz_uint8 *)pRead_buf, n);
        cur_archive_file_ofs += n;
      }
      uncomp_size = file_ofs;
      comp_size = uncomp_size;
    } else {
      mz_bool result = MZ_FALSE;
      mz_zip_writer_add_state state;
      tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(
          pZip->m_pAlloc_opaque, 1, sizeof(tdefl_compressor));
      if (!pComp) {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
      }

      state.m_pZip = pZip;
      state.m_cur_archive_file_ofs = cur_archive_file_ofs;
      state.m_comp_size = 0;

      if (tdefl_init(pComp, mz_zip_writer_add_put_buf_callback, &state,
                     tdefl_create_comp_flags_from_zip_params(
                         level, -15, MZ_DEFAULT_STRATEGY)) !=
          TDEFL_STATUS_OKAY) {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        return mz_zip_set_error(pZip, MZ_ZIP_INTERNAL_ERROR);
      }

      for (;;) {
        tdefl_status status;
        tdefl_flush flush = TDEFL_NO_FLUSH;

        size_t n = read_callback(callback_opaque, file_ofs, pRead_buf,
                                 MZ_ZIP_MAX_IO_BUF_SIZE);
        if ((n > MZ_ZIP_MAX_IO_BUF_SIZE) || (file_ofs + n > max_size)) {
          mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);
          break;
        }

        file_ofs += n;
        uncomp_crc32 =
            (mz_uint32)mz_crc32(uncomp_crc32, (const mz_uint8 *)pRead_buf, n);

        if (pZip->m_pNeeds_keepalive != NULL &&
            pZip->m_pNeeds_keepalive(pZip->m_pIO_opaque))
          flush = TDEFL_FULL_FLUSH;

        if (n == 0)
          flush = TDEFL_FINISH;

        status = tdefl_compress_buffer(pComp, pRead_buf, n, flush);
        if (status == TDEFL_STATUS_DONE) {
          result = MZ_TRUE;
          break;
        } else if (status != TDEFL_STATUS_OKAY) {
          mz_zip_set_error(pZip, MZ_ZIP_COMPRESSION_FAILED);
          break;
        }
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      if (!result) {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        return MZ_FALSE;
      }

      uncomp_size = file_ofs;
      comp_size = state.m_comp_size;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  if (!(level_and_flags & MZ_ZIP_FLAG_WRITE_HEADER_SET_SIZE)) {
    mz_uint8 local_dir_footer[MZ_ZIP_DATA_DESCRIPTER_SIZE64];
    mz_uint32 local_dir_footer_size = MZ_ZIP_DATA_DESCRIPTER_SIZE32;

    MZ_WRITE_LE32(local_dir_footer + 0, MZ_ZIP_DATA_DESCRIPTOR_ID);
    MZ_WRITE_LE32(local_dir_footer + 4, uncomp_crc32);
    if (pExtra_data == NULL) {
      if (comp_size > MZ_UINT32_MAX)
        return mz_zip_set_error(pZip, MZ_ZIP_ARCHIVE_TOO_LARGE);

      MZ_WRITE_LE32(local_dir_footer + 8, comp_size);
      MZ_WRITE_LE32(local_dir_footer + 12, uncomp_size);
    } else {
      MZ_WRITE_LE64(local_dir_footer + 8, comp_size);
      MZ_WRITE_LE64(local_dir_footer + 16, uncomp_size);
      local_dir_footer_size = MZ_ZIP_DATA_DESCRIPTER_SIZE64;
    }

    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs,
                       local_dir_footer,
                       local_dir_footer_size) != local_dir_footer_size)
      return MZ_FALSE;

    cur_archive_file_ofs += local_dir_footer_size;
  }

  if (level_and_flags & MZ_ZIP_FLAG_WRITE_HEADER_SET_SIZE) {
    if (pExtra_data != NULL) {
      extra_size = mz_zip_writer_create_zip64_extra_data(
          extra_data, (max_size >= MZ_UINT32_MAX) ? &uncomp_size : NULL,
          (max_size >= MZ_UINT32_MAX) ? &comp_size : NULL,
          (local_dir_header_ofs >= MZ_UINT32_MAX) ? &local_dir_header_ofs
                                                  : NULL);
    }

    if (!mz_zip_writer_create_local_dir_header(
            pZip, local_dir_header, (mz_uint16)archive_name_size,
            (mz_uint16)(extra_size + user_extra_data_len),
            (max_size >= MZ_UINT32_MAX) ? MZ_UINT32_MAX : uncomp_size,
            (max_size >= MZ_UINT32_MAX) ? MZ_UINT32_MAX : comp_size,
            uncomp_crc32, method, gen_flags, dos_time, dos_date))
      return mz_zip_set_error(pZip, MZ_ZIP_INTERNAL_ERROR);

    cur_archive_header_file_ofs = local_dir_header_ofs;

    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_header_file_ofs,
                       local_dir_header,
                       sizeof(local_dir_header)) != sizeof(local_dir_header))
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

    if (pExtra_data != NULL) {
      cur_archive_header_file_ofs += sizeof(local_dir_header);

      if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_header_file_ofs,
                         pArchive_name,
                         archive_name_size) != archive_name_size) {
        return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);
      }

      cur_archive_header_file_ofs += archive_name_size;

      if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_header_file_ofs,
                         extra_data, extra_size) != extra_size)
        return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

      cur_archive_header_file_ofs += extra_size;
    }
  }

  if (pExtra_data != NULL) {
    extra_size = mz_zip_writer_create_zip64_extra_data(
        extra_data, (uncomp_size >= MZ_UINT32_MAX) ? &uncomp_size : NULL,
        (uncomp_size >= MZ_UINT32_MAX) ? &comp_size : NULL,
        (local_dir_header_ofs >= MZ_UINT32_MAX) ? &local_dir_header_ofs : NULL);
  }

  if (!mz_zip_writer_add_to_central_dir(
          pZip, pArchive_name, (mz_uint16)archive_name_size, pExtra_data,
          (mz_uint16)extra_size, pComment, comment_size, uncomp_size, comp_size,
          uncomp_crc32, method, gen_flags, dos_time, dos_date,
          local_dir_header_ofs, ext_attributes, user_extra_data_central,
          user_extra_data_central_len))
    return MZ_FALSE;

  pZip->m_total_files++;
  pZip->m_archive_size = cur_archive_file_ofs;

  return MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO

static size_t mz_file_read_func_stdio(void *pOpaque, mz_uint64 file_ofs,
                                      void *pBuf, size_t n) {
  MZ_FILE *pSrc_file = (MZ_FILE *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pSrc_file);

  if (((mz_int64)file_ofs < 0) ||
      (((cur_ofs != (mz_int64)file_ofs)) &&
       (MZ_FSEEK64(pSrc_file, (mz_int64)file_ofs, SEEK_SET))))
    return 0;

  return MZ_FREAD(pBuf, 1, n, pSrc_file);
}

mz_bool mz_zip_writer_add_cfile(
    mz_zip_archive *pZip, const char *pArchive_name, MZ_FILE *pSrc_file,
    mz_uint64 max_size, const MZ_TIME_T *pFile_time, const void *pComment,
    mz_uint16 comment_size, mz_uint level_and_flags, mz_uint32 ext_attributes,
    const char *user_extra_data, mz_uint user_extra_data_len,
    const char *user_extra_data_central, mz_uint user_extra_data_central_len) {
  return mz_zip_writer_add_read_buf_callback(
      pZip, pArchive_name, mz_file_read_func_stdio, pSrc_file, max_size,
      pFile_time, pComment, comment_size, level_and_flags, ext_attributes,
      user_extra_data, user_extra_data_len, user_extra_data_central,
      user_extra_data_central_len);
}

mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, const char *pArchive_name,
                               const char *pSrc_filename, const void *pComment,
                               mz_uint16 comment_size, mz_uint level_and_flags,
                               mz_uint32 ext_attributes) {
  MZ_FILE *pSrc_file = NULL;
  mz_uint64 uncomp_size = 0;
  MZ_TIME_T file_modified_time;
  MZ_TIME_T *pFile_time = NULL;
  mz_bool status;

  memset(&file_modified_time, 0, sizeof(file_modified_time));

#if !defined(MINIZ_NO_TIME) && !defined(MINIZ_NO_STDIO)
  pFile_time = &file_modified_time;
  if (!mz_zip_get_file_modified_time(pSrc_filename, &file_modified_time))
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_STAT_FAILED);
#endif

  pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
  if (!pSrc_file)
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_OPEN_FAILED);

  MZ_FSEEK64(pSrc_file, 0, SEEK_END);
  uncomp_size = MZ_FTELL64(pSrc_file);
  MZ_FSEEK64(pSrc_file, 0, SEEK_SET);

  status = mz_zip_writer_add_cfile(
      pZip, pArchive_name, pSrc_file, uncomp_size, pFile_time, pComment,
      comment_size, level_and_flags, ext_attributes, NULL, 0, NULL, 0);

  MZ_FCLOSE(pSrc_file);

  return status;
}
#endif /* #ifndef MINIZ_NO_STDIO */

static mz_bool mz_zip_writer_update_zip64_extension_block(
    mz_zip_array *pNew_ext, mz_zip_archive *pZip, const mz_uint8 *pExt,
    mz_uint32 ext_len, mz_uint64 *pComp_size, mz_uint64 *pUncomp_size,
    mz_uint64 *pLocal_header_ofs, mz_uint32 *pDisk_start) {
  /* + 64 should be enough for any new zip64 data */
  if (!mz_zip_array_reserve(pZip, pNew_ext, ext_len + 64, MZ_FALSE))
    return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);

  mz_zip_array_resize(pZip, pNew_ext, 0, MZ_FALSE);

  if ((pUncomp_size) || (pComp_size) || (pLocal_header_ofs) || (pDisk_start)) {
    mz_uint8 new_ext_block[64];
    mz_uint8 *pDst = new_ext_block;
    mz_write_le16(pDst, MZ_ZIP64_EXTENDED_INFORMATION_FIELD_HEADER_ID);
    mz_write_le16(pDst + sizeof(mz_uint16), 0);
    pDst += sizeof(mz_uint16) * 2;

    if (pUncomp_size) {
      mz_write_le64(pDst, *pUncomp_size);
      pDst += sizeof(mz_uint64);
    }

    if (pComp_size) {
      mz_write_le64(pDst, *pComp_size);
      pDst += sizeof(mz_uint64);
    }

    if (pLocal_header_ofs) {
      mz_write_le64(pDst, *pLocal_header_ofs);
      pDst += sizeof(mz_uint64);
    }

    if (pDisk_start) {
      mz_write_le32(pDst, *pDisk_start);
      pDst += sizeof(mz_uint32);
    }

    mz_write_le16(new_ext_block + sizeof(mz_uint16),
                  (mz_uint16)((pDst - new_ext_block) - sizeof(mz_uint16) * 2));

    if (!mz_zip_array_push_back(pZip, pNew_ext, new_ext_block,
                                pDst - new_ext_block))
      return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
  }

  if ((pExt) && (ext_len)) {
    mz_uint32 extra_size_remaining = ext_len;
    const mz_uint8 *pExtra_data = pExt;

    do {
      mz_uint32 field_id, field_data_size, field_total_size;

      if (extra_size_remaining < (sizeof(mz_uint16) * 2))
        return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

      field_id = MZ_READ_LE16(pExtra_data);
      field_data_size = MZ_READ_LE16(pExtra_data + sizeof(mz_uint16));
      field_total_size = field_data_size + sizeof(mz_uint16) * 2;

      if (field_total_size > extra_size_remaining)
        return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

      if (field_id != MZ_ZIP64_EXTENDED_INFORMATION_FIELD_HEADER_ID) {
        if (!mz_zip_array_push_back(pZip, pNew_ext, pExtra_data,
                                    field_total_size))
          return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
      }

      pExtra_data += field_total_size;
      extra_size_remaining -= field_total_size;
    } while (extra_size_remaining);
  }

  return MZ_TRUE;
}

/* TODO: This func is now pretty freakin complex due to zip64, split it up? */
mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip,
                                          mz_zip_archive *pSource_zip,
                                          mz_uint src_file_index) {
  mz_uint n, bit_flags, num_alignment_padding_bytes,
      src_central_dir_following_data_size;
  mz_uint64 src_archive_bytes_remaining, local_dir_header_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32
      local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + sizeof(mz_uint32) - 1) /
                       sizeof(mz_uint32)];
  mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
  mz_uint8 new_central_header[MZ_ZIP_CENTRAL_DIR_HEADER_SIZE];
  size_t orig_central_dir_size;
  mz_zip_internal_state *pState;
  void *pBuf;
  const mz_uint8 *pSrc_central_header;
  mz_zip_archive_file_stat src_file_stat;
  mz_uint32 src_filename_len, src_comment_len, src_ext_len;
  mz_uint32 local_header_filename_size, local_header_extra_len;
  mz_uint64 local_header_comp_size, local_header_uncomp_size;
  mz_bool found_zip64_ext_data_in_ldir = MZ_FALSE;

  /* Sanity checks */
  if ((!pZip) || (!pZip->m_pState) ||
      (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || (!pSource_zip->m_pRead))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  pState = pZip->m_pState;

  /* Don't support copying files from zip64 archives to non-zip64, even though
   * in some cases this is possible */
  if ((pSource_zip->m_pState->m_zip64) && (!pZip->m_pState->m_zip64))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  /* Get pointer to the source central dir header and crack it */
  if (NULL ==
      (pSrc_central_header = mz_zip_get_cdh(pSource_zip, src_file_index)))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  if (MZ_READ_LE32(pSrc_central_header + MZ_ZIP_CDH_SIG_OFS) !=
      MZ_ZIP_CENTRAL_DIR_HEADER_SIG)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

  src_filename_len =
      MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  src_comment_len =
      MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  src_ext_len = MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_EXTRA_LEN_OFS);
  src_central_dir_following_data_size =
      src_filename_len + src_ext_len + src_comment_len;

  /* TODO: We don't support central dir's >= MZ_UINT32_MAX bytes right now
   * (+32 fudge factor in case we need to add more extra data) */
  if ((pState->m_central_dir.m_size + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE +
       src_central_dir_following_data_size + 32) >= MZ_UINT32_MAX)
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_CDIR_SIZE);

  num_alignment_padding_bytes =
      mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  if (!pState->m_zip64) {
    if (pZip->m_total_files == MZ_UINT16_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_TOO_MANY_FILES);
  } else {
    /* TODO: Our zip64 support still has some 32-bit limits that may not be
     * worth fixing. */
    if (pZip->m_total_files == MZ_UINT32_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_TOO_MANY_FILES);
  }

  if (!mz_zip_file_stat_internal(pSource_zip, src_file_index,
                                 pSrc_central_header, &src_file_stat, NULL))
    return MZ_FALSE;

  cur_src_file_ofs = src_file_stat.m_local_header_ofs;
  cur_dst_file_ofs = pZip->m_archive_size;

  /* Read the source archive's local dir header */
  if (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs,
                           pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_SIZE) !=
      MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);

  if (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);

  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE;

  /* Compute the total size we need to copy (filename+extra data+compressed
   * data) */
  local_header_filename_size =
      MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS);
  local_header_extra_len =
      MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  local_header_comp_size =
      MZ_READ_LE32(pLocal_header + MZ_ZIP_LDH_COMPRESSED_SIZE_OFS);
  local_header_uncomp_size =
      MZ_READ_LE32(pLocal_header + MZ_ZIP_LDH_DECOMPRESSED_SIZE_OFS);
  src_archive_bytes_remaining = src_file_stat.m_comp_size +
                                local_header_filename_size +
                                local_header_extra_len;

  /* Try to find a zip64 extended information field */
  if ((local_header_extra_len) &&
      ((local_header_comp_size == MZ_UINT32_MAX) ||
       (local_header_uncomp_size == MZ_UINT32_MAX))) {
    mz_zip_array file_data_array;
    const mz_uint8 *pExtra_data;
    mz_uint32 extra_size_remaining = local_header_extra_len;

    mz_zip_array_init(&file_data_array, 1);
    if (!mz_zip_array_resize(pZip, &file_data_array, local_header_extra_len,
                             MZ_FALSE)) {
      return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
    }

    if (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque,
                             src_file_stat.m_local_header_ofs +
                                 MZ_ZIP_LOCAL_DIR_HEADER_SIZE +
                                 local_header_filename_size,
                             file_data_array.m_p, local_header_extra_len) !=
        local_header_extra_len) {
      mz_zip_array_clear(pZip, &file_data_array);
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);
    }

    pExtra_data = (const mz_uint8 *)file_data_array.m_p;

    do {
      mz_uint32 field_id, field_data_size, field_total_size;

      if (extra_size_remaining < (sizeof(mz_uint16) * 2)) {
        mz_zip_array_clear(pZip, &file_data_array);
        return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);
      }

      field_id = MZ_READ_LE16(pExtra_data);
      field_data_size = MZ_READ_LE16(pExtra_data + sizeof(mz_uint16));
      field_total_size = field_data_size + sizeof(mz_uint16) * 2;

      if (field_total_size > extra_size_remaining) {
        mz_zip_array_clear(pZip, &file_data_array);
        return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);
      }

      if (field_id == MZ_ZIP64_EXTENDED_INFORMATION_FIELD_HEADER_ID) {
        const mz_uint8 *pSrc_field_data = pExtra_data + sizeof(mz_uint32);

        if (field_data_size < sizeof(mz_uint64) * 2) {
          mz_zip_array_clear(pZip, &file_data_array);
          return mz_zip_set_error(pZip, MZ_ZIP_INVALID_HEADER_OR_CORRUPTED);
        }

        local_header_uncomp_size = MZ_READ_LE64(pSrc_field_data);
        local_header_comp_size = MZ_READ_LE64(
            pSrc_field_data +
            sizeof(mz_uint64)); /* may be 0 if there's a descriptor */

        found_zip64_ext_data_in_ldir = MZ_TRUE;
        break;
      }

      pExtra_data += field_total_size;
      extra_size_remaining -= field_total_size;
    } while (extra_size_remaining);

    mz_zip_array_clear(pZip, &file_data_array);
  }

  if (!pState->m_zip64) {
    /* Try to detect if the new archive will most likely wind up too big and
     * bail early (+(sizeof(mz_uint32) * 4) is for the optional descriptor
     * which could be present, +64 is a fudge factor). */
    /* We also check when the archive is finalized so this doesn't need to be
     * perfect. */
    mz_uint64 approx_new_archive_size =
        cur_dst_file_ofs + num_alignment_padding_bytes +
        MZ_ZIP_LOCAL_DIR_HEADER_SIZE + src_archive_bytes_remaining +
        (sizeof(mz_uint32) * 4) + pState->m_central_dir.m_size +
        MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + src_central_dir_following_data_size +
        MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE + 64;

    if (approx_new_archive_size >= MZ_UINT32_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_ARCHIVE_TOO_LARGE);
  }

  /* Write dest archive padding */
  if (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs,
                                 num_alignment_padding_bytes))
    return MZ_FALSE;

  cur_dst_file_ofs += num_alignment_padding_bytes;

  local_dir_header_ofs = cur_dst_file_ofs;
  if (pZip->m_file_offset_alignment) {
    MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) ==
              0);
  }

  /* The original zip's local header+ext block doesn't change, even with
   * zip64, so we can just copy it over to the dest zip */
  if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pLocal_header,
                     MZ_ZIP_LOCAL_DIR_HEADER_SIZE) !=
      MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE;

  /* Copy over the source archive bytes to the dest archive, also ensure we
   * have enough buf space to handle optional data descriptor */
  if (NULL == (pBuf = pZip->m_pAlloc(
                   pZip->m_pAlloc_opaque, 1,
                   (size_t)MZ_MAX(32U, MZ_MIN((mz_uint64)MZ_ZIP_MAX_IO_BUF_SIZE,
                                              src_archive_bytes_remaining)))))
    return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);

  while (src_archive_bytes_remaining) {
    n = (mz_uint)MZ_MIN((mz_uint64)MZ_ZIP_MAX_IO_BUF_SIZE,
                        src_archive_bytes_remaining);
    if (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf,
                             n) != n) {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);
    }
    cur_src_file_ofs += n;

    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n) {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);
    }
    cur_dst_file_ofs += n;

    src_archive_bytes_remaining -= n;
  }

  /* Now deal with the optional data descriptor */
  bit_flags = MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_BIT_FLAG_OFS);
  if (bit_flags & 8) {
    /* Copy data descriptor */
    if ((pSource_zip->m_pState->m_zip64) || (found_zip64_ext_data_in_ldir)) {
      /* src is zip64, dest must be zip64 */

      /* name			uint32_t's */
      /* id				1 (optional in zip64?) */
      /* crc			1 */
      /* comp_size	2 */
      /* uncomp_size 2 */
      if (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs,
                               pBuf, (sizeof(mz_uint32) * 6)) !=
          (sizeof(mz_uint32) * 6)) {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
        return mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);
      }

      n = sizeof(mz_uint32) *
          ((MZ_READ_LE32(pBuf) == MZ_ZIP_DATA_DESCRIPTOR_ID) ? 6 : 5);
    } else {
      /* src is NOT zip64 */
      mz_bool has_id;

      if (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs,
                               pBuf, sizeof(mz_uint32) * 4) !=
          sizeof(mz_uint32) * 4) {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
        return mz_zip_set_error(pZip, MZ_ZIP_FILE_READ_FAILED);
      }

      has_id = (MZ_READ_LE32(pBuf) == MZ_ZIP_DATA_DESCRIPTOR_ID);

      if (pZip->m_pState->m_zip64) {
        /* dest is zip64, so upgrade the data descriptor */
        const mz_uint8 *pSrc_descriptor =
            (const mz_uint8 *)pBuf + (has_id ? sizeof(mz_uint32) : 0);
        const mz_uint32 src_crc32 = MZ_READ_LE32(pSrc_descriptor);
        const mz_uint64 src_comp_size =
            MZ_READ_LE32(pSrc_descriptor + sizeof(mz_uint32));
        const mz_uint64 src_uncomp_size =
            MZ_READ_LE32(pSrc_descriptor + 2 * sizeof(mz_uint32));

        mz_write_le32((mz_uint8 *)pBuf, MZ_ZIP_DATA_DESCRIPTOR_ID);
        mz_write_le32((mz_uint8 *)pBuf + sizeof(mz_uint32) * 1, src_crc32);
        mz_write_le64((mz_uint8 *)pBuf + sizeof(mz_uint32) * 2, src_comp_size);
        mz_write_le64((mz_uint8 *)pBuf + sizeof(mz_uint32) * 4,
                      src_uncomp_size);

        n = sizeof(mz_uint32) * 6;
      } else {
        /* dest is NOT zip64, just copy it as-is */
        n = sizeof(mz_uint32) * (has_id ? 4 : 3);
      }
    }

    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n) {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);
    }

    cur_src_file_ofs += n;
    cur_dst_file_ofs += n;
  }
  pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);

  /* Finally, add the new central dir header */
  orig_central_dir_size = pState->m_central_dir.m_size;

  memcpy(new_central_header, pSrc_central_header,
         MZ_ZIP_CENTRAL_DIR_HEADER_SIZE);

  if (pState->m_zip64) {
    /* This is the painful part: We need to write a new central dir header +
     * ext block with updated zip64 fields, and ensure the old fields (if any)
     * are not included. */
    const mz_uint8 *pSrc_ext =
        pSrc_central_header + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + src_filename_len;
    mz_zip_array new_ext_block;

    mz_zip_array_init(&new_ext_block, sizeof(mz_uint8));

    MZ_WRITE_LE32(new_central_header + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS,
                  MZ_UINT32_MAX);
    MZ_WRITE_LE32(new_central_header + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS,
                  MZ_UINT32_MAX);
    MZ_WRITE_LE32(new_central_header + MZ_ZIP_CDH_LOCAL_HEADER_OFS,
                  MZ_UINT32_MAX);

    if (!mz_zip_writer_update_zip64_extension_block(
            &new_ext_block, pZip, pSrc_ext, src_ext_len,
            &src_file_stat.m_comp_size, &src_file_stat.m_uncomp_size,
            &local_dir_header_ofs, NULL)) {
      mz_zip_array_clear(pZip, &new_ext_block);
      return MZ_FALSE;
    }

    MZ_WRITE_LE16(new_central_header + MZ_ZIP_CDH_EXTRA_LEN_OFS,
                  new_ext_block.m_size);

    if (!mz_zip_array_push_back(pZip, &pState->m_central_dir,
                                new_central_header,
                                MZ_ZIP_CENTRAL_DIR_HEADER_SIZE)) {
      mz_zip_array_clear(pZip, &new_ext_block);
      return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
    }

    if (!mz_zip_array_push_back(pZip, &pState->m_central_dir,
                                pSrc_central_header +
                                    MZ_ZIP_CENTRAL_DIR_HEADER_SIZE,
                                src_filename_len)) {
      mz_zip_array_clear(pZip, &new_ext_block);
      mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size,
                          MZ_FALSE);
      return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
    }

    if (!mz_zip_array_push_back(pZip, &pState->m_central_dir, new_ext_block.m_p,
                                new_ext_block.m_size)) {
      mz_zip_array_clear(pZip, &new_ext_block);
      mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size,
                          MZ_FALSE);
      return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
    }

    if (!mz_zip_array_push_back(pZip, &pState->m_central_dir,
                                pSrc_central_header +
                                    MZ_ZIP_CENTRAL_DIR_HEADER_SIZE +
                                    src_filename_len + src_ext_len,
                                src_comment_len)) {
      mz_zip_array_clear(pZip, &new_ext_block);
      mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size,
                          MZ_FALSE);
      return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
    }

    mz_zip_array_clear(pZip, &new_ext_block);
  } else {
    /* sanity checks */
    if (cur_dst_file_ofs > MZ_UINT32_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_ARCHIVE_TOO_LARGE);

    if (local_dir_header_ofs >= MZ_UINT32_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_ARCHIVE_TOO_LARGE);

    MZ_WRITE_LE32(new_central_header + MZ_ZIP_CDH_LOCAL_HEADER_OFS,
                  local_dir_header_ofs);

    if (!mz_zip_array_push_back(pZip, &pState->m_central_dir,
                                new_central_header,
                                MZ_ZIP_CENTRAL_DIR_HEADER_SIZE))
      return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);

    if (!mz_zip_array_push_back(pZip, &pState->m_central_dir,
                                pSrc_central_header +
                                    MZ_ZIP_CENTRAL_DIR_HEADER_SIZE,
                                src_central_dir_following_data_size)) {
      mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size,
                          MZ_FALSE);
      return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
    }
  }

  /* This shouldn't trigger unless we screwed up during the initial sanity
   * checks */
  if (pState->m_central_dir.m_size >= MZ_UINT32_MAX) {
    /* TODO: Support central dirs >= 32-bits in size */
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size,
                        MZ_FALSE);
    return mz_zip_set_error(pZip, MZ_ZIP_UNSUPPORTED_CDIR_SIZE);
  }

  n = (mz_uint32)orig_central_dir_size;
  if (!mz_zip_array_push_back(pZip, &pState->m_central_dir_offsets, &n, 1)) {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size,
                        MZ_FALSE);
    return mz_zip_set_error(pZip, MZ_ZIP_ALLOC_FAILED);
  }

  pZip->m_total_files++;
  pZip->m_archive_size = cur_dst_file_ofs;

  return MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip) {
  mz_zip_internal_state *pState;
  mz_uint64 central_dir_ofs, central_dir_size;
  mz_uint8 hdr[256];

  if ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  pState = pZip->m_pState;

  if (pState->m_zip64) {
    if ((mz_uint64)pState->m_central_dir.m_size >= MZ_UINT32_MAX)
      return mz_zip_set_error(pZip, MZ_ZIP_TOO_MANY_FILES);
  } else {
    if ((pZip->m_total_files > MZ_UINT16_MAX) ||
        ((pZip->m_archive_size + pState->m_central_dir.m_size +
          MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE) > MZ_UINT32_MAX))
      return mz_zip_set_error(pZip, MZ_ZIP_TOO_MANY_FILES);
  }

  central_dir_ofs = 0;
  central_dir_size = 0;
  if (pZip->m_total_files) {
    /* Write central directory */
    central_dir_ofs = pZip->m_archive_size;
    central_dir_size = pState->m_central_dir.m_size;
    pZip->m_central_directory_file_ofs = central_dir_ofs;
    if (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs,
                       pState->m_central_dir.m_p,
                       (size_t)central_dir_size) != central_dir_size)
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

    pZip->m_archive_size += central_dir_size;
  }

  if (pState->m_zip64) {
    /* Write zip64 end of central directory header */
    mz_uint64 rel_ofs_to_zip64_ecdr = pZip->m_archive_size;

    MZ_CLEAR_ARR(hdr);
    MZ_WRITE_LE32(hdr + MZ_ZIP64_ECDH_SIG_OFS,
                  MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIG);
    MZ_WRITE_LE64(hdr + MZ_ZIP64_ECDH_SIZE_OF_RECORD_OFS,
                  MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE - sizeof(mz_uint32) -
                      sizeof(mz_uint64));
    MZ_WRITE_LE16(hdr + MZ_ZIP64_ECDH_VERSION_MADE_BY_OFS,
                  0x031E); /* TODO: always Unix */
    MZ_WRITE_LE16(hdr + MZ_ZIP64_ECDH_VERSION_NEEDED_OFS, 0x002D);
    MZ_WRITE_LE64(hdr + MZ_ZIP64_ECDH_CDIR_NUM_ENTRIES_ON_DISK_OFS,
                  pZip->m_total_files);
    MZ_WRITE_LE64(hdr + MZ_ZIP64_ECDH_CDIR_TOTAL_ENTRIES_OFS,
                  pZip->m_total_files);
    MZ_WRITE_LE64(hdr + MZ_ZIP64_ECDH_CDIR_SIZE_OFS, central_dir_size);
    MZ_WRITE_LE64(hdr + MZ_ZIP64_ECDH_CDIR_OFS_OFS, central_dir_ofs);
    if (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_size, hdr,
                       MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE) !=
        MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE)
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

    pZip->m_archive_size += MZ_ZIP64_END_OF_CENTRAL_DIR_HEADER_SIZE;

    /* Write zip64 end of central directory locator */
    MZ_CLEAR_ARR(hdr);
    MZ_WRITE_LE32(hdr + MZ_ZIP64_ECDL_SIG_OFS,
                  MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIG);
    MZ_WRITE_LE64(hdr + MZ_ZIP64_ECDL_REL_OFS_TO_ZIP64_ECDR_OFS,
                  rel_ofs_to_zip64_ecdr);
    MZ_WRITE_LE32(hdr + MZ_ZIP64_ECDL_TOTAL_NUMBER_OF_DISKS_OFS, 1);
    if (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_size, hdr,
                       MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIZE) !=
        MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIZE)
      return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

    pZip->m_archive_size += MZ_ZIP64_END_OF_CENTRAL_DIR_LOCATOR_SIZE;
  }

  /* Write end of central directory record */
  MZ_CLEAR_ARR(hdr);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS,
                MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_NUM_ENTRIES_ON_DISK_OFS,
                MZ_MIN(MZ_UINT16_MAX, pZip->m_total_files));
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS,
                MZ_MIN(MZ_UINT16_MAX, pZip->m_total_files));
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_SIZE_OFS,
                MZ_MIN(MZ_UINT32_MAX, central_dir_size));
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS,
                MZ_MIN(MZ_UINT32_MAX, central_dir_ofs));

  if (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_size, hdr,
                     MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE) !=
      MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_WRITE_FAILED);

#ifndef MINIZ_NO_STDIO
  if ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
    return mz_zip_set_error(pZip, MZ_ZIP_FILE_CLOSE_FAILED);
#endif /* #ifndef MINIZ_NO_STDIO */

  pZip->m_archive_size += MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE;

  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED;
  return MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, void **ppBuf,
                                            size_t *pSize) {
  if ((!ppBuf) || (!pSize))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  *ppBuf = NULL;
  *pSize = 0;

  if ((!pZip) || (!pZip->m_pState))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  if (pZip->m_pWrite != mz_zip_heap_write_func)
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  if (!mz_zip_writer_finalize_archive(pZip))
    return MZ_FALSE;

  *ppBuf = pZip->m_pState->m_pMem;
  *pSize = pZip->m_pState->m_mem_size;
  pZip->m_pState->m_pMem = NULL;
  pZip->m_pState->m_mem_size = pZip->m_pState->m_mem_capacity = 0;

  return MZ_TRUE;
}

mz_bool mz_zip_writer_end(mz_zip_archive *pZip) {
  return mz_zip_writer_end_internal(pZip, MZ_TRUE);
}

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_add_mem_to_archive_file_in_place(
    const char *pZip_filename, const char *pArchive_name, const void *pBuf,
    size_t buf_size, const void *pComment, mz_uint16 comment_size,
    mz_uint level_and_flags) {
  return mz_zip_add_mem_to_archive_file_in_place_v2(
      pZip_filename, pArchive_name, pBuf, buf_size, pComment, comment_size,
      level_and_flags, NULL);
}

mz_bool mz_zip_add_mem_to_archive_file_in_place_v2(
    const char *pZip_filename, const char *pArchive_name, const void *pBuf,
    size_t buf_size, const void *pComment, mz_uint16 comment_size,
    mz_uint level_and_flags, mz_zip_error *pErr) {
  mz_bool status, created_new_archive = MZ_FALSE;
  mz_zip_archive zip_archive;
  struct MZ_FILE_STAT_STRUCT file_stat;
  mz_zip_error actual_err = MZ_ZIP_NO_ERROR;

  mz_zip_zero_struct(&zip_archive);
  if ((int)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;

  if ((!pZip_filename) || (!pArchive_name) || ((buf_size) && (!pBuf)) ||
      ((comment_size) && (!pComment)) ||
      ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION)) {
    if (pErr)
      *pErr = MZ_ZIP_INVALID_PARAMETER;
    return MZ_FALSE;
  }

  if (!mz_zip_writer_validate_archive_name(pArchive_name)) {
    if (pErr)
      *pErr = MZ_ZIP_INVALID_FILENAME;
    return MZ_FALSE;
  }

  /* Important: The regular non-64 bit version of stat() can fail here if the
   * file is very large, which could cause the archive to be overwritten. */
  /* So be sure to compile with _LARGEFILE64_SOURCE 1 */
  if (MZ_FILE_STAT(pZip_filename, &file_stat) != 0) {
    /* Create a new archive. */
    if (!mz_zip_writer_init_file_v2(&zip_archive, pZip_filename, 0,
                                    level_and_flags)) {
      if (pErr)
        *pErr = zip_archive.m_last_error;
      return MZ_FALSE;
    }

    created_new_archive = MZ_TRUE;
  } else {
    /* Append to an existing archive. */
    if (!mz_zip_reader_init_file_v2(
            &zip_archive, pZip_filename,
            level_and_flags | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY, 0,
            0)) {
      if (pErr)
        *pErr = zip_archive.m_last_error;
      return MZ_FALSE;
    }

    if (!mz_zip_writer_init_from_reader_v2(&zip_archive, pZip_filename,
                                           level_and_flags)) {
      if (pErr)
        *pErr = zip_archive.m_last_error;

      mz_zip_reader_end_internal(&zip_archive, MZ_FALSE);

      return MZ_FALSE;
    }
  }

  status =
      mz_zip_writer_add_mem_ex(&zip_archive, pArchive_name, pBuf, buf_size,
                               pComment, comment_size, level_and_flags, 0, 0);
  actual_err = zip_archive.m_last_error;

  /* Always finalize, even if adding failed for some reason, so we have a
   * valid central directory. (This may not always succeed, but we can try.)
   */
  if (!mz_zip_writer_finalize_archive(&zip_archive)) {
    if (!actual_err)
      actual_err = zip_archive.m_last_error;

    status = MZ_FALSE;
  }

  if (!mz_zip_writer_end_internal(&zip_archive, status)) {
    if (!actual_err)
      actual_err = zip_archive.m_last_error;

    status = MZ_FALSE;
  }

  if ((!status) && (created_new_archive)) {
    /* It's a new archive and something went wrong, so just delete it. */
    int ignoredStatus = MZ_DELETE_FILE(pZip_filename);
    (void)ignoredStatus;
  }

  if (pErr)
    *pErr = actual_err;

  return status;
}

void *mz_zip_extract_archive_file_to_heap_v2(const char *pZip_filename,
                                             const char *pArchive_name,
                                             const char *pComment,
                                             size_t *pSize, mz_uint flags,
                                             mz_zip_error *pErr) {
  mz_uint32 file_index;
  mz_zip_archive zip_archive;
  void *p = NULL;

  if (pSize)
    *pSize = 0;

  if ((!pZip_filename) || (!pArchive_name)) {
    if (pErr)
      *pErr = MZ_ZIP_INVALID_PARAMETER;

    return NULL;
  }

  mz_zip_zero_struct(&zip_archive);
  if (!mz_zip_reader_init_file_v2(
          &zip_archive, pZip_filename,
          flags | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY, 0, 0)) {
    if (pErr)
      *pErr = zip_archive.m_last_error;

    return NULL;
  }

  if (mz_zip_reader_locate_file_v2(&zip_archive, pArchive_name, pComment, flags,
                                   &file_index)) {
    p = mz_zip_reader_extract_to_heap(&zip_archive, file_index, pSize, flags);
  }

  mz_zip_reader_end_internal(&zip_archive, p != NULL);

  if (pErr)
    *pErr = zip_archive.m_last_error;

  return p;
}

void *mz_zip_extract_archive_file_to_heap(const char *pZip_filename,
                                          const char *pArchive_name,
                                          size_t *pSize, mz_uint flags) {
  return mz_zip_extract_archive_file_to_heap_v2(pZip_filename, pArchive_name,
                                                NULL, pSize, flags, NULL);
}

#endif /* #ifndef MINIZ_NO_STDIO */

#endif /* #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS */

/* ------------------- Misc utils */

mz_zip_mode mz_zip_get_mode(mz_zip_archive *pZip) {
  return pZip ? pZip->m_zip_mode : MZ_ZIP_MODE_INVALID;
}

mz_zip_type mz_zip_get_type(mz_zip_archive *pZip) {
  return pZip ? pZip->m_zip_type : MZ_ZIP_TYPE_INVALID;
}

mz_zip_error mz_zip_set_last_error(mz_zip_archive *pZip, mz_zip_error err_num) {
  mz_zip_error prev_err;

  if (!pZip)
    return MZ_ZIP_INVALID_PARAMETER;

  prev_err = pZip->m_last_error;

  pZip->m_last_error = err_num;
  return prev_err;
}

mz_zip_error mz_zip_peek_last_error(mz_zip_archive *pZip) {
  if (!pZip)
    return MZ_ZIP_INVALID_PARAMETER;

  return pZip->m_last_error;
}

mz_zip_error mz_zip_clear_last_error(mz_zip_archive *pZip) {
  return mz_zip_set_last_error(pZip, MZ_ZIP_NO_ERROR);
}

mz_zip_error mz_zip_get_last_error(mz_zip_archive *pZip) {
  mz_zip_error prev_err;

  if (!pZip)
    return MZ_ZIP_INVALID_PARAMETER;

  prev_err = pZip->m_last_error;

  pZip->m_last_error = MZ_ZIP_NO_ERROR;
  return prev_err;
}

const char *mz_zip_get_error_string(mz_zip_error mz_err) {
  switch (mz_err) {
  case MZ_ZIP_NO_ERROR:
    return "no error";
  case MZ_ZIP_UNDEFINED_ERROR:
    return "undefined error";
  case MZ_ZIP_TOO_MANY_FILES:
    return "too many files";
  case MZ_ZIP_FILE_TOO_LARGE:
    return "file too large";
  case MZ_ZIP_UNSUPPORTED_METHOD:
    return "unsupported method";
  case MZ_ZIP_UNSUPPORTED_ENCRYPTION:
    return "unsupported encryption";
  case MZ_ZIP_UNSUPPORTED_FEATURE:
    return "unsupported feature";
  case MZ_ZIP_FAILED_FINDING_CENTRAL_DIR:
    return "failed finding central directory";
  case MZ_ZIP_NOT_AN_ARCHIVE:
    return "not a ZIP archive";
  case MZ_ZIP_INVALID_HEADER_OR_CORRUPTED:
    return "invalid header or archive is corrupted";
  case MZ_ZIP_UNSUPPORTED_MULTIDISK:
    return "unsupported multidisk archive";
  case MZ_ZIP_DECOMPRESSION_FAILED:
    return "decompression failed or archive is corrupted";
  case MZ_ZIP_COMPRESSION_FAILED:
    return "compression failed";
  case MZ_ZIP_UNEXPECTED_DECOMPRESSED_SIZE:
    return "unexpected decompressed size";
  case MZ_ZIP_CRC_CHECK_FAILED:
    return "CRC-32 check failed";
  case MZ_ZIP_UNSUPPORTED_CDIR_SIZE:
    return "unsupported central directory size";
  case MZ_ZIP_ALLOC_FAILED:
    return "allocation failed";
  case MZ_ZIP_FILE_OPEN_FAILED:
    return "file open failed";
  case MZ_ZIP_FILE_CREATE_FAILED:
    return "file create failed";
  case MZ_ZIP_FILE_WRITE_FAILED:
    return "file write failed";
  case MZ_ZIP_FILE_READ_FAILED:
    return "file read failed";
  case MZ_ZIP_FILE_CLOSE_FAILED:
    return "file close failed";
  case MZ_ZIP_FILE_SEEK_FAILED:
    return "file seek failed";
  case MZ_ZIP_FILE_STAT_FAILED:
    return "file stat failed";
  case MZ_ZIP_INVALID_PARAMETER:
    return "invalid parameter";
  case MZ_ZIP_INVALID_FILENAME:
    return "invalid filename";
  case MZ_ZIP_BUF_TOO_SMALL:
    return "buffer too small";
  case MZ_ZIP_INTERNAL_ERROR:
    return "internal error";
  case MZ_ZIP_FILE_NOT_FOUND:
    return "file not found";
  case MZ_ZIP_ARCHIVE_TOO_LARGE:
    return "archive is too large";
  case MZ_ZIP_VALIDATION_FAILED:
    return "validation failed";
  case MZ_ZIP_WRITE_CALLBACK_FAILED:
    return "write callback failed";
  case MZ_ZIP_TOTAL_ERRORS:
    return "total errors";
  default:
    break;
  }

  return "unknown error";
}

/* Note: Just because the archive is not zip64 doesn't necessarily mean it
 * doesn't have Zip64 extended information extra field, argh. */
mz_bool mz_zip_is_zip64(mz_zip_archive *pZip) {
  if ((!pZip) || (!pZip->m_pState))
    return MZ_FALSE;

  return pZip->m_pState->m_zip64;
}

size_t mz_zip_get_central_dir_size(mz_zip_archive *pZip) {
  if ((!pZip) || (!pZip->m_pState))
    return 0;

  return pZip->m_pState->m_central_dir.m_size;
}

mz_uint mz_zip_reader_get_num_files(mz_zip_archive *pZip) {
  return pZip ? pZip->m_total_files : 0;
}

mz_uint64 mz_zip_get_archive_size(mz_zip_archive *pZip) {
  if (!pZip)
    return 0;
  return pZip->m_archive_size;
}

mz_uint64 mz_zip_get_archive_file_start_offset(mz_zip_archive *pZip) {
  if ((!pZip) || (!pZip->m_pState))
    return 0;
  return pZip->m_pState->m_file_archive_start_ofs;
}

MZ_FILE *mz_zip_get_cfile(mz_zip_archive *pZip) {
  if ((!pZip) || (!pZip->m_pState))
    return 0;
  return pZip->m_pState->m_pFile;
}

size_t mz_zip_read_archive_data(mz_zip_archive *pZip, mz_uint64 file_ofs,
                                void *pBuf, size_t n) {
  if ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!pZip->m_pRead))
    return mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);

  return pZip->m_pRead(pZip->m_pIO_opaque, file_ofs, pBuf, n);
}

mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_index,
                                   char *pFilename, mz_uint filename_buf_size) {
  mz_uint n;
  const mz_uint8 *p = mz_zip_get_cdh(pZip, file_index);
  if (!p) {
    if (filename_buf_size)
      pFilename[0] = '\0';
    mz_zip_set_error(pZip, MZ_ZIP_INVALID_PARAMETER);
    return 0;
  }
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  if (filename_buf_size) {
    n = MZ_MIN(n, filename_buf_size - 1);
    memcpy(pFilename, p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE, n);
    pFilename[n] = '\0';
  }
  return n + 1;
}

mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_index,
                                mz_zip_archive_file_stat *pStat) {
  return mz_zip_file_stat_internal(
      pZip, file_index, mz_zip_get_cdh(pZip, file_index), pStat, NULL);
}

mz_bool mz_zip_end(mz_zip_archive *pZip) {
  if (!pZip)
    return MZ_FALSE;

  if (pZip->m_zip_mode == MZ_ZIP_MODE_READING)
    return mz_zip_reader_end(pZip);
#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS
  else if ((pZip->m_zip_mode == MZ_ZIP_MODE_WRITING) ||
           (pZip->m_zip_mode == MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED))
    return mz_zip_writer_end(pZip);
#endif

  return MZ_FALSE;
}

#ifdef __cplusplus
}
#endif

#endif /*#ifndef MINIZ_NO_ARCHIVE_APIS*/

#endif // MINIZ_HEADER_FILE_ONLY

/*
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#ifndef ZIP_H
#define ZIP_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#ifndef ZIP_SHARED
#define ZIP_EXPORT
#else
#ifdef _WIN32
#ifdef ZIP_BUILD_SHARED
#define ZIP_EXPORT __declspec(dllexport)
#else
#define ZIP_EXPORT __declspec(dllimport)
#endif
#else
#define ZIP_EXPORT __attribute__((visibility("default")))
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_POSIX_C_SOURCE) && defined(_MSC_VER)
// 64-bit Windows is the only mainstream platform
// where sizeof(long) != sizeof(void*)
#ifdef _WIN64
typedef long long ssize_t; /* byte count or error */
#else
typedef long ssize_t; /* byte count or error */
#endif
#endif

/**
 * @mainpage
 *
 * Documentation for @ref zip.
 */

/**
 * @addtogroup zip
 * @{
 */

/**
 * Default zip compression level.
 */
#define ZIP_DEFAULT_COMPRESSION_LEVEL 6

/**
 * Error codes
 */
#define ZIP_ENOINIT -1      // not initialized
#define ZIP_EINVENTNAME -2  // invalid entry name
#define ZIP_ENOENT -3       // entry not found
#define ZIP_EINVMODE -4     // invalid zip mode
#define ZIP_EINVLVL -5      // invalid compression level
#define ZIP_ENOSUP64 -6     // no zip 64 support
#define ZIP_EMEMSET -7      // memset error
#define ZIP_EWRTENT -8      // cannot write data to entry
#define ZIP_ETDEFLINIT -9   // cannot initialize tdefl compressor
#define ZIP_EINVIDX -10     // invalid index
#define ZIP_ENOHDR -11      // header not found
#define ZIP_ETDEFLBUF -12   // cannot flush tdefl buffer
#define ZIP_ECRTHDR -13     // cannot create entry header
#define ZIP_EWRTHDR -14     // cannot write entry header
#define ZIP_EWRTDIR -15     // cannot write to central dir
#define ZIP_EOPNFILE -16    // cannot open file
#define ZIP_EINVENTTYPE -17 // invalid entry type
#define ZIP_EMEMNOALLOC -18 // extracting data using no memory allocation
#define ZIP_ENOFILE -19     // file not found
#define ZIP_ENOPERM -20     // no permission
#define ZIP_EOOMEM -21      // out of memory
#define ZIP_EINVZIPNAME -22 // invalid zip archive name
#define ZIP_EMKDIR -23      // make dir error
#define ZIP_ESYMLINK -24    // symlink error
#define ZIP_ECLSZIP -25     // close archive error
#define ZIP_ECAPSIZE -26    // capacity size too small
#define ZIP_EFSEEK -27      // fseek error
#define ZIP_EFREAD -28      // fread error
#define ZIP_EFWRITE -29     // fwrite error
#define ZIP_ERINIT -30      // cannot initialize reader
#define ZIP_EWINIT -31      // cannot initialize writer
#define ZIP_EWRINIT -32     // cannot initialize writer from reader
#define ZIP_EINVAL -33      // invalid argument
#define ZIP_ENORITER -34    // cannot initialize reader iterator

/**
 * Looks up the error message string corresponding to an error number.
 * @param errnum error number
 * @return error message string corresponding to errnum or NULL if error is
 * not found.
 */
extern ZIP_EXPORT const char *zip_strerror(int errnum);

/**
 * @struct zip_t
 *
 * This data structure is used throughout the library to represent zip archive
 * - forward declaration.
 */
struct zip_t;

/**
 * Opens zip archive with compression level using the given mode.
 *
 * @param zipname zip archive file name.
 * @param level compression level (0-9 are the standard zlib-style levels).
 * @param mode file access mode.
 *        - 'r': opens a file for reading/extracting (the file must exists).
 *        - 'w': creates an empty file for writing.
 *        - 'a': appends to an existing archive.
 *
 * @return the zip archive handler or NULL on error
 */
extern ZIP_EXPORT struct zip_t *zip_open(const char *zipname, int level,
                                         char mode);

/**
 * Opens zip archive with compression level using the given mode.
 * The function additionally returns @param errnum -
 *
 * @param zipname zip archive file name.
 * @param level compression level (0-9 are the standard zlib-style levels).
 * @param mode file access mode.
 *        - 'r': opens a file for reading/extracting (the file must exists).
 *        - 'w': creates an empty file for writing.
 *        - 'a': appends to an existing archive.
 * @param errnum 0 on success, negative number (< 0) on error.
 *
 * @return the zip archive handler or NULL on error
 */
extern ZIP_EXPORT struct zip_t *
zip_openwitherror(const char *zipname, int level, char mode, int *errnum);

/**
 * Closes the zip archive, releases resources - always finalize.
 *
 * @param zip zip archive handler.
 */
extern ZIP_EXPORT void zip_close(struct zip_t *zip);

/**
 * Determines if the archive has a zip64 end of central directory headers.
 *
 * @param zip zip archive handler.
 *
 * @return the return code - 1 (true), 0 (false), negative number (< 0) on
 *         error.
 */
extern ZIP_EXPORT int zip_is64(struct zip_t *zip);

/**
 * Returns the offset in the stream where the zip header is located.
 *
 * @param zip zip archive handler.
 * @param offset zip header offset.
 *
 * @return the return code - 0 if successful, negative number (< 0) on error.
 */
extern ZIP_EXPORT int zip_offset(struct zip_t *zip, uint64_t *offset);

/**
 * Opens an entry by name in the zip archive.
 *
 * For zip archive opened in 'w' or 'a' mode the function will append
 * a new entry. In readonly mode the function tries to locate the entry
 * in global dictionary.
 *
 * @param zip zip archive handler.
 * @param entryname an entry name in local dictionary.
 *
 * @return the return code - 0 on success, negative number (< 0) on error.
 */
extern ZIP_EXPORT int zip_entry_open(struct zip_t *zip, const char *entryname);

/**
 * Opens an entry by name in the zip archive.
 *
 * For zip archive opened in 'w' or 'a' mode the function will append
 * a new entry. In readonly mode the function tries to locate the entry
 * in global dictionary (case sensitive).
 *
 * @param zip zip archive handler.
 * @param entryname an entry name in local dictionary (case sensitive).
 *
 * @return the return code - 0 on success, negative number (< 0) on error.
 */
extern ZIP_EXPORT int zip_entry_opencasesensitive(struct zip_t *zip,
                                                  const char *entryname);

/**
 * Opens a new entry by index in the zip archive.
 *
 * This function is only valid if zip archive was opened in 'r' (readonly)
 * mode.
 *
 * @param zip zip archive handler.
 * @param index index in local dictionary.
 *
 * @return the return code - 0 on success, negative number (< 0) on error.
 */
extern ZIP_EXPORT int zip_entry_openbyindex(struct zip_t *zip, size_t index);

/**
 * Closes a zip entry, flushes buffer and releases resources.
 *
 * @param zip zip archive handler.
 *
 * @return the return code - 0 on success, negative number (< 0) on error.
 */
extern ZIP_EXPORT int zip_entry_close(struct zip_t *zip);

/**
 * Returns a local name of the current zip entry.
 *
 * The main difference between user's entry name and local entry name
 * is optional relative path.
 * Following .ZIP File Format Specification - the path stored MUST not contain
 * a drive or device letter, or a leading slash.
 * All slashes MUST be forward slashes '/' as opposed to backwards slashes '\'
 * for compatibility with Amiga and UNIX file systems etc.
 *
 * @param zip: zip archive handler.
 *
 * @return the pointer to the current zip entry name, or NULL on error.
 */
extern ZIP_EXPORT const char *zip_entry_name(struct zip_t *zip);

/**
 * Returns an index of the current zip entry.
 *
 * @param zip zip archive handler.
 *
 * @return the index on success, negative number (< 0) on error.
 */
extern ZIP_EXPORT ssize_t zip_entry_index(struct zip_t *zip);

/**
 * Determines if the current zip entry is a directory entry.
 *
 * @param zip zip archive handler.
 *
 * @return the return code - 1 (true), 0 (false), negative number (< 0) on
 *         error.
 */
extern ZIP_EXPORT int zip_entry_isdir(struct zip_t *zip);

/**
 * Returns the uncompressed size of the current zip entry.
 * Alias for zip_entry_uncomp_size (for backward compatibility).
 *
 * @param zip zip archive handler.
 *
 * @return the uncompressed size in bytes.
 */
extern ZIP_EXPORT unsigned long long zip_entry_size(struct zip_t *zip);

/**
 * Returns the uncompressed size of the current zip entry.
 *
 * @param zip zip archive handler.
 *
 * @return the uncompressed size in bytes.
 */
extern ZIP_EXPORT unsigned long long zip_entry_uncomp_size(struct zip_t *zip);

/**
 * Returns the compressed size of the current zip entry.
 *
 * @param zip zip archive handler.
 *
 * @return the compressed size in bytes.
 */
extern ZIP_EXPORT unsigned long long zip_entry_comp_size(struct zip_t *zip);

/**
 * Returns CRC-32 checksum of the current zip entry.
 *
 * @param zip zip archive handler.
 *
 * @return the CRC-32 checksum.
 */
extern ZIP_EXPORT unsigned int zip_entry_crc32(struct zip_t *zip);

/**
 * Returns byte offset of the current zip entry
 * in the archive's central directory.
 *
 * @param zip zip archive handler.
 *
 * @return the offset in bytes.
 */
extern ZIP_EXPORT unsigned long long zip_entry_dir_offset(struct zip_t *zip);

/**
 * Returns the current zip entry's local header file offset in bytes.
 *
 * @param zip zip archive handler.
 *
 * @return the entry's local header file offset in bytes.
 */
extern ZIP_EXPORT unsigned long long zip_entry_header_offset(struct zip_t *zip);

/**
 * Compresses an input buffer for the current zip entry.
 *
 * @param zip zip archive handler.
 * @param buf input buffer.
 * @param bufsize input buffer size (in bytes).
 *
 * @return the return code - 0 on success, negative number (< 0) on error.
 */
extern ZIP_EXPORT int zip_entry_write(struct zip_t *zip, const void *buf,
                                      size_t bufsize);

/**
 * Compresses a file for the current zip entry.
 *
 * @param zip zip archive handler.
 * @param filename input file.
 *
 * @return the return code - 0 on success, negative number (< 0) on error.
 */
extern ZIP_EXPORT int zip_entry_fwrite(struct zip_t *zip, const char *filename);

/**
 * Extracts the current zip entry into output buffer.
 *
 * The function allocates sufficient memory for a output buffer.
 *
 * @param zip zip archive handler.
 * @param buf output buffer.
 * @param bufsize output buffer size (in bytes).
 *
 * @note remember to release memory allocated for a output buffer.
 *       for large entries, please take a look at zip_entry_extract function.
 *
 * @return the return code - the number of bytes actually read on success.
 *         Otherwise a negative number (< 0) on error.
 */
extern ZIP_EXPORT ssize_t zip_entry_read(struct zip_t *zip, void **buf,
                                         size_t *bufsize);

/**
 * Extracts the current zip entry into a memory buffer using no memory
 * allocation.
 *
 * @param zip zip archive handler.
 * @param buf preallocated output buffer.
 * @param bufsize output buffer size (in bytes).
 *
 * @note ensure supplied output buffer is large enough.
 *       zip_entry_size function (returns uncompressed size for the current
 *       entry) can be handy to estimate how big buffer is needed.
 *       For large entries, please take a look at zip_entry_extract function.
 *
 * @return the return code - the number of bytes actually read on success.
 *         Otherwise a negative number (< 0) on error (e.g. bufsize is not
 * large enough).
 */
extern ZIP_EXPORT ssize_t zip_entry_noallocread(struct zip_t *zip, void *buf,
                                                size_t bufsize);

/**
 * Extracts the part of the current zip entry into a memory buffer using no
 * memory allocation for the buffer.
 *
 * @param zip zip archive handler.
 * @param offset the offset of the entry (in bytes).
 * @param size requested number of bytes (in bytes).
 * @param buf preallocated output buffer.
 *
 * @note the iterator api uses an allocation to create its state
 * @note each call will iterate from the start of the entry
 *
 * @return the return code - the number of bytes actually read on success.
 *         Otherwise a negative number (< 0) on error (e.g. offset is too
 * large).
 */
extern ZIP_EXPORT ssize_t zip_entry_noallocreadwithoffset(struct zip_t *zip,
                                                          size_t offset,
                                                          size_t size,
                                                          void *buf);

/**
 * Extracts the current zip entry into output file.
 *
 * @param zip zip archive handler.
 * @param filename output file.
 *
 * @return the return code - 0 on success, negative number (< 0) on error.
 */
extern ZIP_EXPORT int zip_entry_fread(struct zip_t *zip, const char *filename);

/**
 * Extracts the current zip entry using a callback function (on_extract).
 *
 * @param zip zip archive handler.
 * @param on_extract callback function.
 * @param arg opaque pointer (optional argument, which you can pass to the
 *        on_extract callback)
 *
 * @return the return code - 0 on success, negative number (< 0) on error.
 */
extern ZIP_EXPORT int
zip_entry_extract(struct zip_t *zip,
                  size_t (*on_extract)(void *arg, uint64_t offset,
                                       const void *data, size_t size),
                  void *arg);

/**
 * Returns the number of all entries (files and directories) in the zip
 * archive.
 *
 * @param zip zip archive handler.
 *
 * @return the return code - the number of entries on success, negative number
 *         (< 0) on error.
 */
extern ZIP_EXPORT ssize_t zip_entries_total(struct zip_t *zip);

/**
 * Deletes zip archive entries.
 *
 * @param zip zip archive handler.
 * @param entries array of zip archive entries to be deleted.
 * @param len the number of entries to be deleted.
 * @return the number of deleted entries, or negative number (< 0) on error.
 */
extern ZIP_EXPORT ssize_t zip_entries_delete(struct zip_t *zip,
                                             char *const entries[], size_t len);

/**
 * Deletes zip archive entries.
 *
 * @param zip zip archive handler.
 * @param entries array of zip archive entries indices to be deleted.
 * @param len the number of entries to be deleted.
 * @return the number of deleted entries, or negative number (< 0) on error.
 */
extern ZIP_EXPORT ssize_t zip_entries_deletebyindex(struct zip_t *zip,
                                                    size_t entries[],
                                                    size_t len);

/**
 * Extracts a zip archive stream into directory.
 *
 * If on_extract is not NULL, the callback will be called after
 * successfully extracted each zip entry.
 * Returning a negative value from the callback will cause abort and return an
 * error. The last argument (void *arg) is optional, which you can use to pass
 * data to the on_extract callback.
 *
 * @param stream zip archive stream.
 * @param size stream size.
 * @param dir output directory.
 * @param on_extract on extract callback.
 * @param arg opaque pointer.
 *
 * @return the return code - 0 on success, negative number (< 0) on error.
 */
extern ZIP_EXPORT int
zip_stream_extract(const char *stream, size_t size, const char *dir,
                   int (*on_extract)(const char *filename, void *arg),
                   void *arg);

/**
 * Opens zip archive stream into memory.
 *
 * @param stream zip archive stream.
 * @param size stream size.
 * @param level compression level (0-9 are the standard zlib-style levels).
 * @param mode file access mode.
 *        - 'r': opens a file for reading/extracting (the file must exists).
 *        - 'w': creates an empty file for writing.
 *        - 'a': appends to an existing archive.
 *
 * @return the zip archive handler or NULL on error
 */
extern ZIP_EXPORT struct zip_t *zip_stream_open(const char *stream, size_t size,
                                                int level, char mode);

/**
 * Opens zip archive stream into memory.
 * The function additionally returns @param errnum -
 *
 * @param stream zip archive stream.
 * @param size stream size.*
 * @param level compression level (0-9 are the standard zlib-style levels).
 * @param mode file access mode.
 *        - 'r': opens a file for reading/extracting (the file must exists).
 *        - 'w': creates an empty file for writing.
 *        - 'a': appends to an existing archive.
 * @param errnum 0 on success, negative number (< 0) on error.
 *
 * @return the zip archive handler or NULL on error
 */
extern ZIP_EXPORT struct zip_t *zip_stream_openwitherror(const char *stream,
                                                         size_t size, int level,
                                                         char mode,
                                                         int *errnum);

/**
 * Copy zip archive stream output buffer.
 *
 * @param zip zip archive handler.
 * @param buf output buffer. User should free buf.
 * @param bufsize output buffer size (in bytes).
 *
 * @return copy size
 */
extern ZIP_EXPORT ssize_t zip_stream_copy(struct zip_t *zip, void **buf,
                                          size_t *bufsize);

/**
 * Close zip archive releases resources.
 *
 * @param zip zip archive handler.
 *
 * @return
 */
extern ZIP_EXPORT void zip_stream_close(struct zip_t *zip);

/**
 * Opens zip archive from existing FILE stream with compression level using
 * the given mode. The stream will not be closed when calling zip_close.
 *
 * @param stream C FILE stream.
 * @param level compression level (0-9 are the standard zlib-style levels).
 * @param mode file access mode. This mode should be equivalent to the mode
 * provided when opening the file.
 *        - 'r': opens a file for reading/extracting (the file must exists).
 *        - 'w': creates an empty file for writing.
 *        - 'a': appends to an existing archive.
 *
 * @return the zip archive handler or NULL on error
 */
extern ZIP_EXPORT struct zip_t *zip_cstream_open(FILE *stream, int level,
                                                 char mode);

/**
 * Opens zip archive from existing FILE stream with compression level using
 * the given mode. The function additionally returns @param errnum - The
 * stream will not be closed when calling zip_close.
 *
 * @param stream C FILE stream.
 * @param level compression level (0-9 are the standard zlib-style levels).
 * @param mode file access mode.
 *        - 'r': opens a file for reading/extracting (the file must exists).
 *        - 'w': creates an empty file for writing.
 *        - 'a': appends to an existing archive.
 * @param errnum 0 on success, negative number (< 0) on error.
 *
 * @return the zip archive handler or NULL on error
 */
extern ZIP_EXPORT struct zip_t *
zip_cstream_openwitherror(FILE *stream, int level, char mode, int *errnum);

/**
 * Closes the zip archive, releases resources - always finalize.
 * This function is an alias for zip_close function.
 *
 * @param zip zip archive handler.
 */
extern ZIP_EXPORT void zip_cstream_close(struct zip_t *zip);

/**
 * Creates a new archive and puts files into a single zip archive.
 *
 * @param zipname zip archive file.
 * @param filenames input files.
 * @param len: number of input files.
 *
 * @return the return code - 0 on success, negative number (< 0) on error.
 */
extern ZIP_EXPORT int zip_create(const char *zipname, const char *filenames[],
                                 size_t len);

/**
 * Extracts a zip archive file into directory.
 *
 * If on_extract_entry is not NULL, the callback will be called after
 * successfully extracted each zip entry.
 * Returning a negative value from the callback will cause abort and return an
 * error. The last argument (void *arg) is optional, which you can use to pass
 * data to the on_extract_entry callback.
 *
 * @param zipname zip archive file.
 * @param dir output directory.
 * @param on_extract_entry on extract callback.
 * @param arg opaque pointer.
 *
 * @return the return code - 0 on success, negative number (< 0) on error.
 */
extern ZIP_EXPORT int zip_extract(const char *zipname, const char *dir,
                                  int (*on_extract_entry)(const char *filename,
                                                          void *arg),
                                  void *arg);
/** @} */
#ifdef __cplusplus
}
#endif

#endif

#ifdef __cplusplus
extern "C" {
#endif
/*
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#define __STDC_WANT_LIB_EXT1__ 1

#include <errno.h>
#include <sys/stat.h>
#include <time.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(_MSC_VER) ||              \
    defined(__MINGW32__)
/* Win32, DOS, MSVC, MSVS */
#include <direct.h>

#define HAS_DEVICE(P)                                                          \
  ((((P)[0] >= 'A' && (P)[0] <= 'Z') || ((P)[0] >= 'a' && (P)[0] <= 'z')) &&   \
   (P)[1] == ':')
#define FILESYSTEM_PREFIX_LEN(P) (HAS_DEVICE(P) ? 2 : 0)

#else

#include <unistd.h> // needed for symlink()

#endif

#ifdef __MINGW32__
#include <sys/types.h>
#include <unistd.h>
#endif




#ifdef _MSC_VER
#include <io.h>

#define ftruncate(fd, sz) (-(_chsize_s((fd), (sz)) != 0))
#define fileno _fileno
#endif

#if defined(__TINYC__) && (defined(_WIN32) || defined(_WIN64))
#include <io.h>

#define ftruncate(fd, sz) (-(_chsize_s((fd), (sz)) != 0))
#define fileno _fileno
#endif

#ifndef HAS_DEVICE
#define HAS_DEVICE(P) 0
#endif

#ifndef FILESYSTEM_PREFIX_LEN
#define FILESYSTEM_PREFIX_LEN(P) 0
#endif

#ifndef ISSLASH
#define ISSLASH(C) ((C) == '/' || (C) == '\\')
#endif

#define CLEANUP(ptr)                                                           \
  do {                                                                         \
    if (ptr) {                                                                 \
      free((void *)ptr);                                                       \
      ptr = NULL;                                                              \
    }                                                                          \
  } while (0)

#define UNX_IFDIR 0040000  /* Unix directory */
#define UNX_IFREG 0100000  /* Unix regular file */
#define UNX_IFSOCK 0140000 /* Unix socket (BSD, not SysV or Amiga) */
#define UNX_IFLNK 0120000  /* Unix symbolic link (not SysV, Amiga) */
#define UNX_IFBLK 0060000  /* Unix block special       (not Amiga) */
#define UNX_IFCHR 0020000  /* Unix character special   (not Amiga) */
#define UNX_IFIFO 0010000  /* Unix fifo    (BCC, not MSC or Amiga) */

struct zip_entry_t {
  ssize_t index;
  char *name;
  mz_uint64 uncomp_size;
  mz_uint64 comp_size;
  mz_uint32 uncomp_crc32;
  mz_uint64 dir_offset;
  mz_uint8 header[MZ_ZIP_LOCAL_DIR_HEADER_SIZE];
  mz_uint64 header_offset;
  mz_uint16 method;
  mz_zip_writer_add_state state;
  tdefl_compressor comp;
  mz_uint32 external_attr;
  time_t m_time;
};

struct zip_t {
  mz_zip_archive archive;
  mz_uint level;
  struct zip_entry_t entry;
};

enum zip_modify_t {
  MZ_KEEP = 0,
  MZ_DELETE = 1,
  MZ_MOVE = 2,
};

struct zip_entry_mark_t {
  ssize_t file_index;
  enum zip_modify_t type;
  mz_uint64 m_local_header_ofs;
  size_t lf_length;
};

static const char *const zip_errlist[35] = {
    NULL,
    "not initialized\0",
    "invalid entry name\0",
    "entry not found\0",
    "invalid zip mode\0",
    "invalid compression level\0",
    "no zip 64 support\0",
    "memset error\0",
    "cannot write data to entry\0",
    "cannot initialize tdefl compressor\0",
    "invalid index\0",
    "header not found\0",
    "cannot flush tdefl buffer\0",
    "cannot write entry header\0",
    "cannot create entry header\0",
    "cannot write to central dir\0",
    "cannot open file\0",
    "invalid entry type\0",
    "extracting data using no memory allocation\0",
    "file not found\0",
    "no permission\0",
    "out of memory\0",
    "invalid zip archive name\0",
    "make dir error\0",
    "symlink error\0",
    "close archive error\0",
    "capacity size too small\0",
    "fseek error\0",
    "fread error\0",
    "fwrite error\0",
    "cannot initialize reader\0",
    "cannot initialize writer\0",
    "cannot initialize writer from reader\0",
    "invalid argument\0",
    "cannot initialize reader iterator\0",
};

const char *zip_strerror(int errnum) {
  errnum = -errnum;
  if (errnum <= 0 || errnum >= 33) {
    return NULL;
  }

  return zip_errlist[errnum];
}

static const char *zip_basename(const char *name) {
  char const *p;
  char const *base = name += FILESYSTEM_PREFIX_LEN(name);
  int all_slashes = 1;

  for (p = name; *p; p++) {
    if (ISSLASH(*p))
      base = p + 1;
    else
      all_slashes = 0;
  }

  /* If NAME is all slashes, arrange to return `/'. */
  if (*base == '\0' && ISSLASH(*name) && all_slashes)
    --base;

  return base;
}

static int zip_mkpath(char *path) {
  char *p;
  char npath[MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE + 1];
  int len = 0;
  int has_device = HAS_DEVICE(path);

  memset(npath, 0, MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE + 1);
  if (has_device) {
    // only on windows
    npath[0] = path[0];
    npath[1] = path[1];
    len = 2;
  }
  for (p = path + len; *p && len < MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE; p++) {
    if (ISSLASH(*p) && ((!has_device && len > 0) || (has_device && len > 2))) {
#if defined(_WIN32) || defined(__WIN32__) || defined(_MSC_VER) ||              \
    defined(__MINGW32__)
#else
      if ('\\' == *p) {
        *p = '/';
      }
#endif

      if (MZ_MKDIR(npath) == -1) {
        if (errno != EEXIST) {
          return ZIP_EMKDIR;
        }
      }
    }
    npath[len++] = *p;
  }

  return 0;
}

static char *zip_strclone(const char *str, size_t n) {
  char c;
  size_t i;
  char *rpl = (char *)calloc((1 + n), sizeof(char));
  char *begin = rpl;
  if (!rpl) {
    return NULL;
  }

  for (i = 0; (i < n) && (c = *str++); ++i) {
    *rpl++ = c;
  }

  return begin;
}

static char *zip_strrpl(const char *str, size_t n, char oldchar, char newchar) {
  char c;
  size_t i;
  char *rpl = (char *)calloc((1 + n), sizeof(char));
  char *begin = rpl;
  if (!rpl) {
    return NULL;
  }

  for (i = 0; (i < n) && (c = *str++); ++i) {
    if (c == oldchar) {
      c = newchar;
    }
    *rpl++ = c;
  }

  return begin;
}

static inline int zip_strchr_match(const char *const str, size_t len, char c) {
  size_t i;
  for (i = 0; i < len; ++i) {
    if (str[i] != c) {
      return 0;
    }
  }

  return 1;
}

static char *zip_name_normalize(char *name, char *const nname, size_t len) {
  size_t offn = 0, ncpy = 0;
  char c;

  if (name == NULL || nname == NULL || len <= 0) {
    return NULL;
  }
  // skip trailing '/'
  while (ISSLASH(*name)) {
    name++;
  }

  while ((c = *name++)) {
    if (ISSLASH(c)) {
      if (ncpy > 0 && !zip_strchr_match(&nname[offn], ncpy, '.')) {
        offn += ncpy;
        nname[offn++] = c; // append '/'
      }
      ncpy = 0;
    } else {
      nname[offn + ncpy] = c;
      if (c) {
        ncpy++;
      }
    }
  }

  if (!zip_strchr_match(&nname[offn], ncpy, '.')) {
    nname[offn + ncpy] = '\0';
  } else {
    nname[offn] = '\0';
  }

  return nname;
}

static int zip_archive_truncate(mz_zip_archive *pzip) {
  mz_zip_internal_state *pState = pzip->m_pState;
  mz_uint64 file_size = pzip->m_archive_size;
  if ((pzip->m_pWrite == mz_zip_heap_write_func) && (pState->m_pMem)) {
    return 0;
  }
  if (pzip->m_zip_mode == MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED) {
    if (pState->m_pFile) {
      int fd = fileno(pState->m_pFile);
      return ftruncate(fd, pState->m_file_archive_start_ofs + file_size);
    }
  }
  return 0;
}

static int zip_archive_extract(mz_zip_archive *zip_archive, const char *dir,
                               int (*on_extract)(const char *filename,
                                                 void *arg),
                               void *arg) {
  int err = 0;
  mz_uint i, n;
  char path[MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE + 1];
  char symlink_to[MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE + 1];
  mz_zip_archive_file_stat info;
  size_t dirlen = 0, filename_size = MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE;
  mz_uint32 xattr = 0;

  memset(path, 0, sizeof(path));
  memset(symlink_to, 0, sizeof(symlink_to));

  dirlen = strlen(dir);
  if (dirlen + 1 > MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE) {
    return ZIP_EINVENTNAME;
  }

  memset((void *)&info, 0, sizeof(mz_zip_archive_file_stat));

#if defined(_MSC_VER)
  strcpy_s(path, MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE, dir);
#else
  strncpy(path, dir, MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE);
#endif

  if (!ISSLASH(path[dirlen - 1])) {
#if defined(_WIN32) || defined(__WIN32__)
    path[dirlen] = '\\';
#else
    path[dirlen] = '/';
#endif
    ++dirlen;
  }

  if (filename_size > MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE - dirlen) {
    filename_size = MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE - dirlen;
  }
  // Get and print information about each file in the archive.
  n = mz_zip_reader_get_num_files(zip_archive);
  for (i = 0; i < n; ++i) {
    if (!mz_zip_reader_file_stat(zip_archive, i, &info)) {
      // Cannot get information about zip archive;
      err = ZIP_ENOENT;
      goto out;
    }

    if (!zip_name_normalize(info.m_filename, info.m_filename,
                            strlen(info.m_filename))) {
      // Cannot normalize file name;
      err = ZIP_EINVENTNAME;
      goto out;
    }

#if defined(_MSC_VER)
    strncpy_s(&path[dirlen], filename_size, info.m_filename, filename_size);
#else
    strncpy(&path[dirlen], info.m_filename, filename_size);
#endif
    err = zip_mkpath(path);
    if (err < 0) {
      // Cannot make a path
      goto out;
    }

    if ((((info.m_version_made_by >> 8) == 3) ||
         ((info.m_version_made_by >> 8) ==
          19)) // if zip is produced on Unix or macOS (3 and 19 from
               // section 4.4.2.2 of zip standard)
        && info.m_external_attr &
               (0x20 << 24)) { // and has sym link attribute (0x80 is file,
                               // 0x40 is directory)
#if defined(_WIN32) || defined(__WIN32__) || defined(_MSC_VER) ||              \
    defined(__MINGW32__)
#else
      if (info.m_uncomp_size > MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE ||
          !mz_zip_reader_extract_to_mem_no_alloc(
              zip_archive, i, symlink_to, MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE, 0,
              NULL, 0)) {
        err = ZIP_EMEMNOALLOC;
        goto out;
      }
      symlink_to[info.m_uncomp_size] = '\0';
      if (symlink(symlink_to, path) != 0) {
        err = ZIP_ESYMLINK;
        goto out;
      }
#endif
    } else {
      if (!mz_zip_reader_is_file_a_directory(zip_archive, i)) {
        if (!mz_zip_reader_extract_to_file(zip_archive, i, path, 0)) {
          // Cannot extract zip archive to file
          err = ZIP_ENOFILE;
          goto out;
        }
      }

#if defined(_MSC_VER) || defined(PS4)
      (void)xattr; // unused
#else
      xattr = (info.m_external_attr >> 16) & 0xFFFF;
      if (xattr > 0 && xattr <= MZ_UINT16_MAX) {
        if (CHMOD(path, (mode_t)xattr) < 0) {
          err = ZIP_ENOPERM;
          goto out;
        }
      }
#endif
    }

    if (on_extract) {
      if (on_extract(path, arg) < 0) {
        goto out;
      }
    }
  }

out:
  // Close the archive, freeing any resources it was using
  if (!mz_zip_reader_end(zip_archive)) {
    // Cannot end zip reader
    err = ZIP_ECLSZIP;
  }
  return err;
}

static inline void zip_archive_finalize(mz_zip_archive *pzip) {
  mz_zip_writer_finalize_archive(pzip);
  zip_archive_truncate(pzip);
}

static ssize_t zip_entry_mark(struct zip_t *zip,
                              struct zip_entry_mark_t *entry_mark,
                              const size_t n, char *const entries[],
                              const size_t len) {
  size_t i = 0;
  ssize_t err = 0;
  if (!zip || !entry_mark || !entries) {
    return ZIP_ENOINIT;
  }

  mz_zip_archive_file_stat file_stat;
  mz_uint64 d_pos = UINT64_MAX;
  for (i = 0; i < n; ++i) {
    if ((err = zip_entry_openbyindex(zip, i))) {
      return (ssize_t)err;
    }

    mz_bool name_matches = MZ_FALSE;
    {
      size_t j;
      for (j = 0; j < len; ++j) {
        if (strcmp(zip->entry.name, entries[j]) == 0) {
          name_matches = MZ_TRUE;
          break;
        }
      }
    }
    if (name_matches) {
      entry_mark[i].type = MZ_DELETE;
    } else {
      entry_mark[i].type = MZ_KEEP;
    }

    if (!mz_zip_reader_file_stat(&zip->archive, (mz_uint)i, &file_stat)) {
      return ZIP_ENOENT;
    }

    zip_entry_close(zip);

    entry_mark[i].m_local_header_ofs = file_stat.m_local_header_ofs;
    entry_mark[i].file_index = (ssize_t)-1;
    entry_mark[i].lf_length = 0;
    if ((entry_mark[i].type) == MZ_DELETE &&
        (d_pos > entry_mark[i].m_local_header_ofs)) {
      d_pos = entry_mark[i].m_local_header_ofs;
    }
  }

  for (i = 0; i < n; ++i) {
    if ((entry_mark[i].m_local_header_ofs > d_pos) &&
        (entry_mark[i].type != MZ_DELETE)) {
      entry_mark[i].type = MZ_MOVE;
    }
  }
  return err;
}

static ssize_t zip_entry_markbyindex(struct zip_t *zip,
                                     struct zip_entry_mark_t *entry_mark,
                                     const size_t n, size_t entries[],
                                     const size_t len) {
  size_t i = 0;
  ssize_t err = 0;
  if (!zip || !entry_mark || !entries) {
    return ZIP_ENOINIT;
  }

  mz_zip_archive_file_stat file_stat;
  mz_uint64 d_pos = UINT64_MAX;
  for (i = 0; i < n; ++i) {
    if ((err = zip_entry_openbyindex(zip, i))) {
      return (ssize_t)err;
    }

    mz_bool matches = MZ_FALSE;
    {
      size_t j;
      for (j = 0; j < len; ++j) {
        if (i == entries[j]) {
          matches = MZ_TRUE;
          break;
        }
      }
    }
    if (matches) {
      entry_mark[i].type = MZ_DELETE;
    } else {
      entry_mark[i].type = MZ_KEEP;
    }

    if (!mz_zip_reader_file_stat(&zip->archive, (mz_uint)i, &file_stat)) {
      return ZIP_ENOENT;
    }

    zip_entry_close(zip);

    entry_mark[i].m_local_header_ofs = file_stat.m_local_header_ofs;
    entry_mark[i].file_index = (ssize_t)-1;
    entry_mark[i].lf_length = 0;
    if ((entry_mark[i].type) == MZ_DELETE &&
        (d_pos > entry_mark[i].m_local_header_ofs)) {
      d_pos = entry_mark[i].m_local_header_ofs;
    }
  }

  for (i = 0; i < n; ++i) {
    if ((entry_mark[i].m_local_header_ofs > d_pos) &&
        (entry_mark[i].type != MZ_DELETE)) {
      entry_mark[i].type = MZ_MOVE;
    }
  }
  return err;
}
static ssize_t zip_index_next(mz_uint64 *local_header_ofs_array,
                              ssize_t cur_index) {
  ssize_t new_index = 0, i;
  for (i = cur_index - 1; i >= 0; --i) {
    if (local_header_ofs_array[cur_index] > local_header_ofs_array[i]) {
      new_index = i + 1;
      return new_index;
    }
  }
  return new_index;
}

static ssize_t zip_sort(mz_uint64 *local_header_ofs_array, ssize_t cur_index) {
  ssize_t nxt_index = zip_index_next(local_header_ofs_array, cur_index);

  if (nxt_index != cur_index) {
    mz_uint64 temp = local_header_ofs_array[cur_index];
    ssize_t i;
    for (i = cur_index; i > nxt_index; i--) {
      local_header_ofs_array[i] = local_header_ofs_array[i - 1];
    }
    local_header_ofs_array[nxt_index] = temp;
  }
  return nxt_index;
}

static int zip_index_update(struct zip_entry_mark_t *entry_mark,
                            ssize_t last_index, ssize_t nxt_index) {
  ssize_t j;
  for (j = 0; j < last_index; j++) {
    if (entry_mark[j].file_index >= nxt_index) {
      entry_mark[j].file_index += 1;
    }
  }
  entry_mark[nxt_index].file_index = last_index;
  return 0;
}

static int zip_entry_finalize(struct zip_t *zip,
                              struct zip_entry_mark_t *entry_mark,
                              const size_t n) {
  size_t i = 0;
  mz_uint64 *local_header_ofs_array = (mz_uint64 *)calloc(n, sizeof(mz_uint64));
  if (!local_header_ofs_array) {
    return ZIP_EOOMEM;
  }

  for (i = 0; i < n; ++i) {
    local_header_ofs_array[i] = entry_mark[i].m_local_header_ofs;
    ssize_t index = zip_sort(local_header_ofs_array, i);

    if ((size_t)index != i) {
      zip_index_update(entry_mark, i, index);
    }
    entry_mark[i].file_index = index;
  }

  size_t *length = (size_t *)calloc(n, sizeof(size_t));
  if (!length) {
    CLEANUP(local_header_ofs_array);
    return ZIP_EOOMEM;
  }
  for (i = 0; i < n - 1; i++) {
    length[i] =
        (size_t)(local_header_ofs_array[i + 1] - local_header_ofs_array[i]);
  }
  length[n - 1] =
      (size_t)(zip->archive.m_archive_size - local_header_ofs_array[n - 1]);

  for (i = 0; i < n; i++) {
    entry_mark[i].lf_length = length[entry_mark[i].file_index];
  }

  CLEANUP(length);
  CLEANUP(local_header_ofs_array);
  return 0;
}

static ssize_t zip_entry_set(struct zip_t *zip,
                             struct zip_entry_mark_t *entry_mark, size_t n,
                             char *const entries[], const size_t len) {
  ssize_t err = 0;

  if ((err = zip_entry_mark(zip, entry_mark, n, entries, len)) < 0) {
    return err;
  }
  if ((err = zip_entry_finalize(zip, entry_mark, n)) < 0) {
    return err;
  }
  return 0;
}

static ssize_t zip_entry_setbyindex(struct zip_t *zip,
                                    struct zip_entry_mark_t *entry_mark,
                                    size_t n, size_t entries[],
                                    const size_t len) {
  ssize_t err = 0;

  if ((err = zip_entry_markbyindex(zip, entry_mark, n, entries, len)) < 0) {
    return err;
  }
  if ((err = zip_entry_finalize(zip, entry_mark, n)) < 0) {
    return err;
  }
  return 0;
}

static ssize_t zip_mem_move(void *pBuf, size_t bufSize, const mz_uint64 to,
                            const mz_uint64 from, const size_t length) {
  uint8_t *dst = NULL, *src = NULL, *end = NULL;

  if (!pBuf) {
    return ZIP_EINVIDX;
  }

  end = (uint8_t *)pBuf + bufSize;

  if (to > bufSize) {
    return ZIP_EINVIDX;
  }

  if (from > bufSize) {
    return ZIP_EINVIDX;
  }

  dst = (uint8_t *)pBuf + to;
  src = (uint8_t *)pBuf + from;

  if (((dst + length) > end) || ((src + length) > end)) {
    return ZIP_EINVIDX;
  }

  memmove(dst, src, length);
  return length;
}

static ssize_t zip_file_move(MZ_FILE *m_pFile, const mz_uint64 to,
                             const mz_uint64 from, const size_t length,
                             mz_uint8 *move_buf, const size_t capacity_size) {
  if (length > capacity_size) {
    return ZIP_ECAPSIZE;
  }
  if (MZ_FSEEK64(m_pFile, from, SEEK_SET)) {
    return ZIP_EFSEEK;
  }
  if (fread(move_buf, 1, length, m_pFile) != length) {
    return ZIP_EFREAD;
  }
  if (MZ_FSEEK64(m_pFile, to, SEEK_SET)) {
    return ZIP_EFSEEK;
  }
  if (fwrite(move_buf, 1, length, m_pFile) != length) {
    return ZIP_EFWRITE;
  }
  return (ssize_t)length;
}

static ssize_t zip_files_move(struct zip_t *zip, mz_uint64 writen_num,
                              mz_uint64 read_num, size_t length) {
  ssize_t n = 0;
  const size_t page_size = 1 << 12; // 4K
  mz_zip_internal_state *pState = zip->archive.m_pState;

  mz_uint8 *move_buf = (mz_uint8 *)calloc(1, page_size);
  if (!move_buf) {
    return ZIP_EOOMEM;
  }

  ssize_t moved_length = 0;
  ssize_t move_count = 0;
  while ((mz_int64)length > 0) {
    move_count = (length >= page_size) ? page_size : length;

    if (pState->m_pFile) {
      n = zip_file_move(pState->m_pFile, writen_num, read_num, move_count,
                        move_buf, page_size);
    } else if (pState->m_pMem) {
      n = zip_mem_move(pState->m_pMem, pState->m_mem_size, writen_num, read_num,
                       move_count);
    } else {
      CLEANUP(move_buf);
      return ZIP_ENOFILE;
    }

    if (n < 0) {
      moved_length = n;
      goto cleanup;
    }

    if (n != move_count) {
      goto cleanup;
    }

    writen_num += move_count;
    read_num += move_count;
    length -= move_count;
    moved_length += move_count;
  }

cleanup:
  CLEANUP(move_buf);
  return moved_length;
}

static int zip_central_dir_move(mz_zip_internal_state *pState, int begin,
                                int end, int entry_num) {
  if (begin == entry_num) {
    return 0;
  }

  size_t l_size = 0;
  size_t r_size = 0;
  mz_uint32 d_size = 0;
  mz_uint8 *next = NULL;
  mz_uint8 *deleted = &MZ_ZIP_ARRAY_ELEMENT(
      &pState->m_central_dir, mz_uint8,
      MZ_ZIP_ARRAY_ELEMENT(&pState->m_central_dir_offsets, mz_uint32, begin));
  l_size = (size_t)(deleted - (mz_uint8 *)(pState->m_central_dir.m_p));
  if (end == entry_num) {
    r_size = 0;
  } else {
    next = &MZ_ZIP_ARRAY_ELEMENT(
        &pState->m_central_dir, mz_uint8,
        MZ_ZIP_ARRAY_ELEMENT(&pState->m_central_dir_offsets, mz_uint32, end));
    r_size = pState->m_central_dir.m_size -
             (mz_uint32)(next - (mz_uint8 *)(pState->m_central_dir.m_p));
    d_size = (mz_uint32)(next - deleted);
  }

  if (next && l_size == 0) {
    memmove(pState->m_central_dir.m_p, next, r_size);
    pState->m_central_dir.m_p = MZ_REALLOC(pState->m_central_dir.m_p, r_size);
    {
      int i;
      for (i = end; i < entry_num; i++) {
        MZ_ZIP_ARRAY_ELEMENT(&pState->m_central_dir_offsets, mz_uint32, i) -=
            d_size;
      }
    }
  }

  if (next && l_size * r_size != 0) {
    memmove(deleted, next, r_size);
    {
      int i;
      for (i = end; i < entry_num; i++) {
        MZ_ZIP_ARRAY_ELEMENT(&pState->m_central_dir_offsets, mz_uint32, i) -=
            d_size;
      }
    }
  }

  pState->m_central_dir.m_size = l_size + r_size;
  return 0;
}

static int zip_central_dir_delete(mz_zip_internal_state *pState,
                                  int *deleted_entry_index_array,
                                  int entry_num) {
  int i = 0;
  int begin = 0;
  int end = 0;
  int d_num = 0;
  while (i < entry_num) {
    while ((i < entry_num) && (!deleted_entry_index_array[i])) {
      i++;
    }
    begin = i;

    while ((i < entry_num) && (deleted_entry_index_array[i])) {
      i++;
    }
    end = i;
    zip_central_dir_move(pState, begin, end, entry_num);
  }

  i = 0;
  while (i < entry_num) {
    while ((i < entry_num) && (!deleted_entry_index_array[i])) {
      i++;
    }
    begin = i;
    if (begin == entry_num) {
      break;
    }
    while ((i < entry_num) && (deleted_entry_index_array[i])) {
      i++;
    }
    end = i;
    int k = 0, j;
    for (j = end; j < entry_num; j++) {
      MZ_ZIP_ARRAY_ELEMENT(&pState->m_central_dir_offsets, mz_uint32,
                           begin + k) =
          (mz_uint32)MZ_ZIP_ARRAY_ELEMENT(&pState->m_central_dir_offsets,
                                          mz_uint32, j);
      k++;
    }
    d_num += end - begin;
  }

  pState->m_central_dir_offsets.m_size =
      sizeof(mz_uint32) * (entry_num - d_num);
  return 0;
}

static ssize_t zip_entries_delete_mark(struct zip_t *zip,
                                       struct zip_entry_mark_t *entry_mark,
                                       int entry_num) {
  mz_uint64 writen_num = 0;
  mz_uint64 read_num = 0;
  size_t deleted_length = 0;
  size_t move_length = 0;
  int i = 0;
  size_t deleted_entry_num = 0;
  ssize_t n = 0;

  mz_bool *deleted_entry_flag_array =
      (mz_bool *)calloc(entry_num, sizeof(mz_bool));
  if (deleted_entry_flag_array == NULL) {
    return ZIP_EOOMEM;
  }

  mz_zip_internal_state *pState = zip->archive.m_pState;
  zip->archive.m_zip_mode = MZ_ZIP_MODE_WRITING;

  if (pState->m_pFile) {
    if (MZ_FSEEK64(pState->m_pFile, 0, SEEK_SET)) {
      CLEANUP(deleted_entry_flag_array);
      return ZIP_ENOENT;
    }
  }

  while (i < entry_num) {
    while ((i < entry_num) && (entry_mark[i].type == MZ_KEEP)) {
      writen_num += entry_mark[i].lf_length;
      read_num = writen_num;
      i++;
    }

    while ((i < entry_num) && (entry_mark[i].type == MZ_DELETE)) {
      deleted_entry_flag_array[i] = MZ_TRUE;
      read_num += entry_mark[i].lf_length;
      deleted_length += entry_mark[i].lf_length;
      i++;
      deleted_entry_num++;
    }

    while ((i < entry_num) && (entry_mark[i].type == MZ_MOVE)) {
      move_length += entry_mark[i].lf_length;
      mz_uint8 *p = &MZ_ZIP_ARRAY_ELEMENT(
          &pState->m_central_dir, mz_uint8,
          MZ_ZIP_ARRAY_ELEMENT(&pState->m_central_dir_offsets, mz_uint32, i));
      if (!p) {
        CLEANUP(deleted_entry_flag_array);
        return ZIP_ENOENT;
      }
      mz_uint32 offset = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS);
      offset -= (mz_uint32)deleted_length;
      MZ_WRITE_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS, offset);
      i++;
    }

    n = zip_files_move(zip, writen_num, read_num, move_length);
    if (n != (ssize_t)move_length) {
      CLEANUP(deleted_entry_flag_array);
      return n;
    }
    writen_num += move_length;
    read_num += move_length;
  }

  zip->archive.m_archive_size -= (mz_uint64)deleted_length;
  zip->archive.m_total_files =
      (mz_uint32)entry_num - (mz_uint32)deleted_entry_num;

  zip_central_dir_delete(pState, deleted_entry_flag_array, entry_num);
  CLEANUP(deleted_entry_flag_array);

  return (ssize_t)deleted_entry_num;
}

struct zip_t *zip_open(const char *zipname, int level, char mode) {
  int errnum = 0;
  return zip_openwitherror(zipname, level, mode, &errnum);
}

struct zip_t *zip_openwitherror(const char *zipname, int level, char mode,
                                int *errnum) {
  struct zip_t *zip = NULL;
  *errnum = 0;

  if (!zipname || strlen(zipname) < 1) {
    // zip_t archive name is empty or NULL
    *errnum = ZIP_EINVZIPNAME;
    goto cleanup;
  }

  if (level < 0)
    level = MZ_DEFAULT_LEVEL;
  if ((level & 0xF) > MZ_UBER_COMPRESSION) {
    // Wrong compression level
    *errnum = ZIP_EINVLVL;
    goto cleanup;
  }

  zip = (struct zip_t *)calloc((size_t)1, sizeof(struct zip_t));
  if (!zip) {
    // out of memory
    *errnum = ZIP_EOOMEM;
    goto cleanup;
  }

  zip->level = (mz_uint)level;
  zip->entry.index = -1;
  switch (mode) {
  case 'w':
    // Create a new archive.
    if (!mz_zip_writer_init_file_v2(&(zip->archive), zipname, 0,
                                    MZ_ZIP_FLAG_WRITE_ZIP64)) {
      // Cannot initialize zip_archive writer
      *errnum = ZIP_EWINIT;
      goto cleanup;
    }
    break;

  case 'r':
    if (!mz_zip_reader_init_file_v2(
            &(zip->archive), zipname,
            zip->level | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY, 0, 0)) {
      // An archive file does not exist or cannot initialize
      // zip_archive reader
      *errnum = ZIP_ERINIT;
      goto cleanup;
    }
    break;

  case 'a':
  case 'd': {
    MZ_FILE *fp = MZ_FOPEN(zipname, "r+b");
    if (!fp) {
      *errnum = ZIP_EOPNFILE;
      goto cleanup;
    }
    if (!mz_zip_reader_init_cfile(
            &(zip->archive), fp, 0,
            zip->level | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY)) {
      // An archive file does not exist or cannot initialize zip_archive
      // reader
      *errnum = ZIP_ERINIT;
      fclose(fp);
      goto cleanup;
    }
    if (!mz_zip_writer_init_from_reader_v2(&(zip->archive), zipname, 0)) {
      *errnum = ZIP_EWRINIT;
      fclose(fp);
      mz_zip_reader_end(&(zip->archive));
      goto cleanup;
    }
    // The file pointer is now owned by the archive object.
    zip->archive.m_zip_type = MZ_ZIP_TYPE_FILE;
  } break;

  default:
    *errnum = ZIP_EINVMODE;
    goto cleanup;
  }

  return zip;

cleanup:
  CLEANUP(zip);
  return NULL;
}

void zip_close(struct zip_t *zip) {
  if (zip) {
    mz_zip_archive *pZip = &(zip->archive);
    // Always finalize, even if adding failed for some reason, so we have a
    // valid central directory.
    if (pZip->m_zip_mode == MZ_ZIP_MODE_WRITING) {
      mz_zip_writer_finalize_archive(pZip);
    }

    if (pZip->m_zip_mode == MZ_ZIP_MODE_WRITING ||
        pZip->m_zip_mode == MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED) {
      zip_archive_truncate(pZip);
      mz_zip_writer_end(pZip);
    }
    if (pZip->m_zip_mode == MZ_ZIP_MODE_READING) {
      mz_zip_reader_end(pZip);
    }

    CLEANUP(zip);
  }
}

int zip_is64(struct zip_t *zip) {
  if (!zip || !zip->archive.m_pState) {
    // zip_t handler or zip state is not initialized
    return ZIP_ENOINIT;
  }

  return (int)zip->archive.m_pState->m_zip64;
}

int zip_offset(struct zip_t *zip, uint64_t *offset) {
  if (!zip || !zip->archive.m_pState) {
    // zip_t handler or zip state is not initialized
    return ZIP_ENOINIT;
  }

  *offset = mz_zip_get_archive_file_start_offset(&zip->archive);
  return 0;
}

static int _zip_entry_open(struct zip_t *zip, const char *entryname,
                           int case_sensitive) {
  size_t entrylen = 0;
  mz_zip_archive *pzip = NULL;
  mz_uint num_alignment_padding_bytes, level;
  mz_zip_archive_file_stat stats;
  int err = 0;
  mz_uint16 dos_time = 0, dos_date = 0;
  mz_uint32 extra_size = 0;
  mz_uint8 extra_data[MZ_ZIP64_MAX_CENTRAL_EXTRA_FIELD_SIZE];
  mz_uint64 local_dir_header_ofs = 0;

  if (!zip) {
    return ZIP_ENOINIT;
  }

  local_dir_header_ofs = zip->archive.m_archive_size;

  if (!entryname) {
    return ZIP_EINVENTNAME;
  }

  entrylen = strlen(entryname);
  if (entrylen == 0) {
    return ZIP_EINVENTNAME;
  }

  if (zip->entry.name) {
    CLEANUP(zip->entry.name);
  }

  pzip = &(zip->archive);
  if (pzip->m_zip_mode == MZ_ZIP_MODE_READING) {
    zip->entry.name = zip_strclone(entryname, entrylen);
    if (!zip->entry.name) {
      // Cannot parse zip entry name
      return ZIP_EINVENTNAME;
    }

    zip->entry.index = (ssize_t)mz_zip_reader_locate_file(
        pzip, zip->entry.name, NULL,
        case_sensitive ? MZ_ZIP_FLAG_CASE_SENSITIVE : 0);
    if (zip->entry.index < (ssize_t)0) {
      err = ZIP_ENOENT;
      goto cleanup;
    }

    if (!mz_zip_reader_file_stat(pzip, (mz_uint)zip->entry.index, &stats)) {
      err = ZIP_ENOENT;
      goto cleanup;
    }

    zip->entry.comp_size = stats.m_comp_size;
    zip->entry.uncomp_size = stats.m_uncomp_size;
    zip->entry.uncomp_crc32 = stats.m_crc32;
    zip->entry.dir_offset = stats.m_central_dir_ofs;
    zip->entry.header_offset = stats.m_local_header_ofs;
    zip->entry.method = stats.m_method;
    zip->entry.external_attr = stats.m_external_attr;
#ifndef MINIZ_NO_TIME
    zip->entry.m_time = stats.m_time;
#endif

    return 0;
  }

  /*
    .ZIP File Format Specification Version: 6.3.3

    4.4.17.1 The name of the file, with optional relative path.
    The path stored MUST not contain a drive or
    device letter, or a leading slash.  All slashes
    MUST be forward slashes '/' as opposed to
    backwards slashes '\' for compatibility with Amiga
    and UNIX file systems etc.  If input came from standard
    input, there is no file name field.
  */
  zip->entry.name = zip_strrpl(entryname, entrylen, '\\', '/');
  if (!zip->entry.name) {
    // Cannot parse zip entry name
    return ZIP_EINVENTNAME;
  }

  level = zip->level & 0xF;

  zip->entry.index = (ssize_t)zip->archive.m_total_files;
  zip->entry.comp_size = 0;
  zip->entry.uncomp_size = 0;
  zip->entry.uncomp_crc32 = MZ_CRC32_INIT;
  zip->entry.dir_offset = zip->archive.m_archive_size;
  zip->entry.header_offset = zip->archive.m_archive_size;
  memset(zip->entry.header, 0, MZ_ZIP_LOCAL_DIR_HEADER_SIZE * sizeof(mz_uint8));
  zip->entry.method = level ? MZ_DEFLATED : 0;

  // UNIX or APPLE
#if MZ_PLATFORM == 3 || MZ_PLATFORM == 19
  // regular file with rw-r--r-- permissions
  zip->entry.external_attr = (mz_uint32)(0100644) << 16;
#else
  zip->entry.external_attr = 0;
#endif

  num_alignment_padding_bytes =
      mz_zip_writer_compute_padding_needed_for_file_alignment(pzip);

  if (!pzip->m_pState || (pzip->m_zip_mode != MZ_ZIP_MODE_WRITING)) {
    // Invalid zip mode
    err = ZIP_EINVMODE;
    goto cleanup;
  }
  if (zip->level & MZ_ZIP_FLAG_COMPRESSED_DATA) {
    // Invalid zip compression level
    err = ZIP_EINVLVL;
    goto cleanup;
  }

  if (!mz_zip_writer_write_zeros(pzip, zip->entry.dir_offset,
                                 num_alignment_padding_bytes)) {
    // Cannot memset zip entry header
    err = ZIP_EMEMSET;
    goto cleanup;
  }
  local_dir_header_ofs += num_alignment_padding_bytes;

  zip->entry.m_time = time(NULL);
#ifndef MINIZ_NO_TIME
  mz_zip_time_t_to_dos_time(zip->entry.m_time, &dos_time, &dos_date);
#endif

  // ZIP64 header with NULL sizes (sizes will be in the data descriptor, just
  // after file data)
  extra_size = mz_zip_writer_create_zip64_extra_data(
      extra_data, NULL, NULL,
      (local_dir_header_ofs >= MZ_UINT32_MAX) ? &local_dir_header_ofs : NULL);

  if (!mz_zip_writer_create_local_dir_header(
          pzip, zip->entry.header, (mz_uint16)entrylen, (mz_uint16)extra_size,
          0, 0, 0, zip->entry.method,
          MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_UTF8 |
              MZ_ZIP_LDH_BIT_FLAG_HAS_LOCATOR,
          dos_time, dos_date)) {
    // Cannot create zip entry header
    err = ZIP_EMEMSET;
    goto cleanup;
  }

  zip->entry.header_offset =
      zip->entry.dir_offset + num_alignment_padding_bytes;

  if (pzip->m_pWrite(pzip->m_pIO_opaque, zip->entry.header_offset,
                     zip->entry.header,
                     sizeof(zip->entry.header)) != sizeof(zip->entry.header)) {
    // Cannot write zip entry header
    err = ZIP_EMEMSET;
    goto cleanup;
  }

  if (pzip->m_file_offset_alignment) {
    MZ_ASSERT(
        (zip->entry.header_offset & (pzip->m_file_offset_alignment - 1)) == 0);
  }
  zip->entry.dir_offset +=
      num_alignment_padding_bytes + sizeof(zip->entry.header);

  if (pzip->m_pWrite(pzip->m_pIO_opaque, zip->entry.dir_offset, zip->entry.name,
                     entrylen) != entrylen) {
    // Cannot write data to zip entry
    err = ZIP_EWRTENT;
    goto cleanup;
  }

  zip->entry.dir_offset += entrylen;

  if (pzip->m_pWrite(pzip->m_pIO_opaque, zip->entry.dir_offset, extra_data,
                     extra_size) != extra_size) {
    // Cannot write ZIP64 data to zip entry
    err = ZIP_EWRTENT;
    goto cleanup;
  }
  zip->entry.dir_offset += extra_size;

  if (level) {
    zip->entry.state.m_pZip = pzip;
    zip->entry.state.m_cur_archive_file_ofs = zip->entry.dir_offset;
    zip->entry.state.m_comp_size = 0;

    if (tdefl_init(&(zip->entry.comp), mz_zip_writer_add_put_buf_callback,
                   &(zip->entry.state),
                   (int)tdefl_create_comp_flags_from_zip_params(
                       (int)level, -15, MZ_DEFAULT_STRATEGY)) !=
        TDEFL_STATUS_OKAY) {
      // Cannot initialize the zip compressor
      err = ZIP_ETDEFLINIT;
      goto cleanup;
    }
  }

  return 0;

cleanup:
  CLEANUP(zip->entry.name);
  return err;
}

int zip_entry_open(struct zip_t *zip, const char *entryname) {
  return _zip_entry_open(zip, entryname, 0);
}

int zip_entry_opencasesensitive(struct zip_t *zip, const char *entryname) {
  return _zip_entry_open(zip, entryname, 1);
}

int zip_entry_openbyindex(struct zip_t *zip, size_t index) {
  mz_zip_archive *pZip = NULL;
  mz_zip_archive_file_stat stats;
  mz_uint namelen;
  const mz_uint8 *pHeader;
  const char *pFilename;

  if (!zip) {
    // zip_t handler is not initialized
    return ZIP_ENOINIT;
  }

  pZip = &(zip->archive);
  if (pZip->m_zip_mode != MZ_ZIP_MODE_READING) {
    // open by index requires readonly mode
    return ZIP_EINVMODE;
  }

  if (index >= (size_t)pZip->m_total_files) {
    // index out of range
    return ZIP_EINVIDX;
  }

  if (!(pHeader = &MZ_ZIP_ARRAY_ELEMENT(
            &pZip->m_pState->m_central_dir, mz_uint8,
            MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets,
                                 mz_uint32, (mz_uint)index)))) {
    // cannot find header in central directory
    return ZIP_ENOHDR;
  }

  namelen = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  pFilename = (const char *)pHeader + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;

  if (zip->entry.name) {
    CLEANUP(zip->entry.name);
  }

  zip->entry.name = zip_strclone(pFilename, namelen);
  if (!zip->entry.name) {
    // local entry name is NULL
    return ZIP_EINVENTNAME;
  }

  if (!mz_zip_reader_file_stat(pZip, (mz_uint)index, &stats)) {
    return ZIP_ENOENT;
  }

  zip->entry.index = (ssize_t)index;
  zip->entry.comp_size = stats.m_comp_size;
  zip->entry.uncomp_size = stats.m_uncomp_size;
  zip->entry.uncomp_crc32 = stats.m_crc32;
  zip->entry.dir_offset = stats.m_central_dir_ofs;
  zip->entry.header_offset = stats.m_local_header_ofs;
  zip->entry.method = stats.m_method;
  zip->entry.external_attr = stats.m_external_attr;
#ifndef MINIZ_NO_TIME
  zip->entry.m_time = stats.m_time;
#endif

  return 0;
}

int zip_entry_close(struct zip_t *zip) {
  mz_zip_archive *pzip = NULL;
  mz_uint level;
  tdefl_status done;
  mz_uint16 entrylen;
  mz_uint16 dos_time = 0, dos_date = 0;
  int err = 0;
  mz_uint8 *pExtra_data = NULL;
  mz_uint32 extra_size = 0;
  mz_uint8 extra_data[MZ_ZIP64_MAX_CENTRAL_EXTRA_FIELD_SIZE];
  mz_uint8 local_dir_footer[MZ_ZIP_DATA_DESCRIPTER_SIZE64];
  mz_uint32 local_dir_footer_size = MZ_ZIP_DATA_DESCRIPTER_SIZE64;

  if (!zip) {
    // zip_t handler is not initialized
    err = ZIP_ENOINIT;
    goto cleanup;
  }

  pzip = &(zip->archive);
  if (pzip->m_zip_mode == MZ_ZIP_MODE_READING) {
    goto cleanup;
  }

  level = zip->level & 0xF;
  if (level) {
    done = tdefl_compress_buffer(&(zip->entry.comp), "", 0, TDEFL_FINISH);
    if (done != TDEFL_STATUS_DONE && done != TDEFL_STATUS_OKAY) {
      // Cannot flush compressed buffer
      err = ZIP_ETDEFLBUF;
      goto cleanup;
    }
    zip->entry.comp_size = zip->entry.state.m_comp_size;
    zip->entry.dir_offset = zip->entry.state.m_cur_archive_file_ofs;
    zip->entry.method = MZ_DEFLATED;
  }

  entrylen = (mz_uint16)strlen(zip->entry.name);
#ifndef MINIZ_NO_TIME
  mz_zip_time_t_to_dos_time(zip->entry.m_time, &dos_time, &dos_date);
#endif

  MZ_WRITE_LE32(local_dir_footer + 0, MZ_ZIP_DATA_DESCRIPTOR_ID);
  MZ_WRITE_LE32(local_dir_footer + 4, zip->entry.uncomp_crc32);
  MZ_WRITE_LE64(local_dir_footer + 8, zip->entry.comp_size);
  MZ_WRITE_LE64(local_dir_footer + 16, zip->entry.uncomp_size);

  if (pzip->m_pWrite(pzip->m_pIO_opaque, zip->entry.dir_offset,
                     local_dir_footer,
                     local_dir_footer_size) != local_dir_footer_size) {
    // Cannot write zip entry header
    err = ZIP_EWRTHDR;
    goto cleanup;
  }
  zip->entry.dir_offset += local_dir_footer_size;

  pExtra_data = extra_data;
  extra_size = mz_zip_writer_create_zip64_extra_data(
      extra_data,
      (zip->entry.uncomp_size >= MZ_UINT32_MAX) ? &zip->entry.uncomp_size
                                                : NULL,
      (zip->entry.comp_size >= MZ_UINT32_MAX) ? &zip->entry.comp_size : NULL,
      (zip->entry.header_offset >= MZ_UINT32_MAX) ? &zip->entry.header_offset
                                                  : NULL);

  if ((entrylen) && ISSLASH(zip->entry.name[entrylen - 1]) &&
      !zip->entry.uncomp_size) {
    /* Set DOS Subdirectory attribute bit. */
    zip->entry.external_attr |= MZ_ZIP_DOS_DIR_ATTRIBUTE_BITFLAG;
  }

  if (!mz_zip_writer_add_to_central_dir(
          pzip, zip->entry.name, entrylen, pExtra_data, (mz_uint16)extra_size,
          "", 0, zip->entry.uncomp_size, zip->entry.comp_size,
          zip->entry.uncomp_crc32, zip->entry.method,
          MZ_ZIP_GENERAL_PURPOSE_BIT_FLAG_UTF8 |
              MZ_ZIP_LDH_BIT_FLAG_HAS_LOCATOR,
          dos_time, dos_date, zip->entry.header_offset,
          zip->entry.external_attr, NULL, 0)) {
    // Cannot write to zip central dir
    err = ZIP_EWRTDIR;
    goto cleanup;
  }

  pzip->m_total_files++;
  pzip->m_archive_size = zip->entry.dir_offset;

cleanup:
  if (zip) {
    zip->entry.m_time = 0;
    zip->entry.index = -1;
    CLEANUP(zip->entry.name);
  }
  return err;
}

const char *zip_entry_name(struct zip_t *zip) {
  if (!zip) {
    // zip_t handler is not initialized
    return NULL;
  }
  return zip->entry.name;
}

ssize_t zip_entry_index(struct zip_t *zip) {
  if (!zip) {
    // zip_t handler is not initialized
    return (ssize_t)ZIP_ENOINIT;
  }

  return zip->entry.index;
}

int zip_entry_isdir(struct zip_t *zip) {
  mz_uint16 entrylen;
  if (!zip) {
    // zip_t handler is not initialized
    return ZIP_ENOINIT;
  }

  if (zip->entry.index < (ssize_t)0) {
    // zip entry is not opened
    return ZIP_EINVIDX;
  }

  entrylen = (mz_uint16)strlen(zip->entry.name);
  return ISSLASH(zip->entry.name[entrylen - 1]);
}

unsigned long long zip_entry_size(struct zip_t *zip) {
  return zip_entry_uncomp_size(zip);
}

unsigned long long zip_entry_uncomp_size(struct zip_t *zip) {
  return zip ? zip->entry.uncomp_size : 0;
}

unsigned long long zip_entry_comp_size(struct zip_t *zip) {
  return zip ? zip->entry.comp_size : 0;
}

unsigned int zip_entry_crc32(struct zip_t *zip) {
  return zip ? zip->entry.uncomp_crc32 : 0;
}

unsigned long long zip_entry_dir_offset(struct zip_t *zip) {
  return zip ? zip->entry.dir_offset : 0;
}

unsigned long long zip_entry_header_offset(struct zip_t *zip) {
  return zip ? zip->entry.header_offset : 0;
}

int zip_entry_write(struct zip_t *zip, const void *buf, size_t bufsize) {
  mz_uint level;
  mz_zip_archive *pzip = NULL;
  tdefl_status status;

  if (!zip) {
    // zip_t handler is not initialized
    return ZIP_ENOINIT;
  }

  pzip = &(zip->archive);
  if (buf && bufsize > 0) {
    zip->entry.uncomp_size += bufsize;
    zip->entry.uncomp_crc32 = (mz_uint32)mz_crc32(
        zip->entry.uncomp_crc32, (const mz_uint8 *)buf, bufsize);

    level = zip->level & 0xF;
    if (!level) {
      if ((pzip->m_pWrite(pzip->m_pIO_opaque, zip->entry.dir_offset, buf,
                          bufsize) != bufsize)) {
        // Cannot write buffer
        return ZIP_EWRTENT;
      }
      zip->entry.dir_offset += bufsize;
      zip->entry.comp_size += bufsize;
    } else {
      status = tdefl_compress_buffer(&(zip->entry.comp), buf, bufsize,
                                     TDEFL_NO_FLUSH);
      if (status != TDEFL_STATUS_DONE && status != TDEFL_STATUS_OKAY) {
        // Cannot compress buffer
        return ZIP_ETDEFLBUF;
      }
    }
  }

  return 0;
}

int zip_entry_fwrite(struct zip_t *zip, const char *filename) {
  int err = 0;
  size_t n = 0;
  MZ_FILE *stream = NULL;
  mz_uint8 buf[MZ_ZIP_MAX_IO_BUF_SIZE];
  struct MZ_FILE_STAT_STRUCT file_stat;
  mz_uint16 modes;

  if (!zip) {
    // zip_t handler is not initialized
    return ZIP_ENOINIT;
  }

  memset(buf, 0, MZ_ZIP_MAX_IO_BUF_SIZE);
  memset((void *)&file_stat, 0, sizeof(struct MZ_FILE_STAT_STRUCT));
  if (MZ_FILE_STAT(filename, &file_stat) != 0) {
    // problem getting information - check errno
    return ZIP_ENOENT;
  }

#if defined(_WIN32) || defined(__WIN32__) || defined(DJGPP)
  (void)modes; // unused
#else
  /* Initialize with permission bits--which are not implementation-optional */
  modes = file_stat.st_mode &
          (S_IRWXU | S_IRWXG | S_IRWXO | S_ISUID | S_ISGID | S_ISVTX);
  if (S_ISDIR(file_stat.st_mode))
    modes |= UNX_IFDIR;
  if (S_ISREG(file_stat.st_mode))
    modes |= UNX_IFREG;
  if (S_ISLNK(file_stat.st_mode))
    modes |= UNX_IFLNK;
  if (S_ISBLK(file_stat.st_mode))
    modes |= UNX_IFBLK;
  if (S_ISCHR(file_stat.st_mode))
    modes |= UNX_IFCHR;
  if (S_ISFIFO(file_stat.st_mode))
    modes |= UNX_IFIFO;
  if (S_ISSOCK(file_stat.st_mode))
    modes |= UNX_IFSOCK;
  zip->entry.external_attr = (modes << 16) | !(file_stat.st_mode & S_IWUSR);
  if ((file_stat.st_mode & S_IFMT) == S_IFDIR) {
    zip->entry.external_attr |= MZ_ZIP_DOS_DIR_ATTRIBUTE_BITFLAG;
  }
#endif

  zip->entry.m_time = file_stat.st_mtime;

  if (!(stream = MZ_FOPEN(filename, "rb"))) {
    // Cannot open filename
    return ZIP_EOPNFILE;
  }

  while ((n = fread(buf, sizeof(mz_uint8), MZ_ZIP_MAX_IO_BUF_SIZE, stream)) >
         0) {
    if (zip_entry_write(zip, buf, n) < 0) {
      err = ZIP_EWRTENT;
      break;
    }
  }
  fclose(stream);

  return err;
}

ssize_t zip_entry_read(struct zip_t *zip, void **buf, size_t *bufsize) {
  mz_zip_archive *pzip = NULL;
  mz_uint idx;
  size_t size = 0;

  if (!zip) {
    // zip_t handler is not initialized
    return (ssize_t)ZIP_ENOINIT;
  }

  pzip = &(zip->archive);
  if (pzip->m_zip_mode != MZ_ZIP_MODE_READING ||
      zip->entry.index < (ssize_t)0) {
    // the entry is not found or we do not have read access
    return (ssize_t)ZIP_ENOENT;
  }

  idx = (mz_uint)zip->entry.index;
  if (mz_zip_reader_is_file_a_directory(pzip, idx)) {
    // the entry is a directory
    return (ssize_t)ZIP_EINVENTTYPE;
  }

  *buf = mz_zip_reader_extract_to_heap(pzip, idx, &size, 0);
  if (*buf && bufsize) {
    *bufsize = size;
  }
  return (ssize_t)size;
}

ssize_t zip_entry_noallocread(struct zip_t *zip, void *buf, size_t bufsize) {
  mz_zip_archive *pzip = NULL;

  if (!zip) {
    // zip_t handler is not initialized
    return (ssize_t)ZIP_ENOINIT;
  }

  pzip = &(zip->archive);
  if (pzip->m_zip_mode != MZ_ZIP_MODE_READING ||
      zip->entry.index < (ssize_t)0) {
    // the entry is not found or we do not have read access
    return (ssize_t)ZIP_ENOENT;
  }

  if (!mz_zip_reader_extract_to_mem_no_alloc(pzip, (mz_uint)zip->entry.index,
                                             buf, bufsize, 0, NULL, 0)) {
    return (ssize_t)ZIP_EMEMNOALLOC;
  }

  return (ssize_t)zip->entry.uncomp_size;
}

ssize_t zip_entry_noallocreadwithoffset(struct zip_t *zip, size_t offset,
                                        size_t size, void *buf) {
  mz_zip_archive *pzip = NULL;

  if (!zip) {
    // zip_t handler is not initialized
    return (ssize_t)ZIP_ENOINIT;
  }

  if (offset >= (size_t)zip->entry.uncomp_size) {
    return (ssize_t)ZIP_EINVAL;
  }

  if ((offset + size) > (size_t)zip->entry.uncomp_size) {
    size = (ssize_t)zip->entry.uncomp_size - offset;
  }

  pzip = &(zip->archive);
  if (pzip->m_zip_mode != MZ_ZIP_MODE_READING ||
      zip->entry.index < (ssize_t)0) {
    // the entry is not found or we do not have read access
    return (ssize_t)ZIP_ENOENT;
  }

  mz_zip_reader_extract_iter_state *iter =
      mz_zip_reader_extract_iter_new(pzip, (mz_uint)zip->entry.index, 0);
  if (!iter) {
    return (ssize_t)ZIP_ENORITER;
  }

  mz_uint8 *writebuf = (mz_uint8 *)buf;
  size_t file_offset = 0;
  size_t write_cursor = 0;
  size_t to_read = size;

  // iterate until the requested offset is in range
  while (file_offset < zip->entry.uncomp_size && to_read > 0) {
    size_t nread = mz_zip_reader_extract_iter_read(
        iter, (void *)&writebuf[write_cursor], to_read);

    if (nread == 0)
      break;

    if (offset < (file_offset + nread)) {
      size_t read_cursor = offset - file_offset;
      MZ_ASSERT(read_cursor < size);
      size_t read_size = nread - read_cursor;

      if (to_read < read_size)
        read_size = to_read;
      MZ_ASSERT(read_size <= size);

      // If it's an unaligned read (i.e. the first one)
      if (read_cursor != 0) {
        memmove(&writebuf[write_cursor], &writebuf[read_cursor], read_size);
      }

      write_cursor += read_size;
      offset += read_size;
      to_read -= read_size;
    }

    file_offset += nread;
  }

  mz_zip_reader_extract_iter_free(iter);
  return (ssize_t)write_cursor;
}

int zip_entry_fread(struct zip_t *zip, const char *filename) {
  mz_zip_archive *pzip = NULL;
  mz_uint idx;
  mz_uint32 xattr = 0;
  mz_zip_archive_file_stat info;

  if (!zip) {
    // zip_t handler is not initialized
    return ZIP_ENOINIT;
  }

  memset((void *)&info, 0, sizeof(mz_zip_archive_file_stat));
  pzip = &(zip->archive);
  if (pzip->m_zip_mode != MZ_ZIP_MODE_READING ||
      zip->entry.index < (ssize_t)0) {
    // the entry is not found or we do not have read access
    return ZIP_ENOENT;
  }

  idx = (mz_uint)zip->entry.index;
  if (mz_zip_reader_is_file_a_directory(pzip, idx)) {
    // the entry is a directory
    return ZIP_EINVENTTYPE;
  }

  if (!mz_zip_reader_extract_to_file(pzip, idx, filename, 0)) {
    return ZIP_ENOFILE;
  }

#if defined(_MSC_VER) || defined(PS4)
  (void)xattr; // unused
#else
  if (!mz_zip_reader_file_stat(pzip, idx, &info)) {
    // Cannot get information about zip archive;
    return ZIP_ENOFILE;
  }

  xattr = (info.m_external_attr >> 16) & 0xFFFF;
  if (xattr > 0 && xattr <= MZ_UINT16_MAX) {
    if (CHMOD(filename, (mode_t)xattr) < 0) {
      return ZIP_ENOPERM;
    }
  }
#endif

  return 0;
}

int zip_entry_extract(struct zip_t *zip,
                      size_t (*on_extract)(void *arg, uint64_t offset,
                                           const void *buf, size_t bufsize),
                      void *arg) {
  mz_zip_archive *pzip = NULL;
  mz_uint idx;

  if (!zip) {
    // zip_t handler is not initialized
    return ZIP_ENOINIT;
  }

  pzip = &(zip->archive);
  if (pzip->m_zip_mode != MZ_ZIP_MODE_READING ||
      zip->entry.index < (ssize_t)0) {
    // the entry is not found or we do not have read access
    return ZIP_ENOENT;
  }

  idx = (mz_uint)zip->entry.index;
  return (mz_zip_reader_extract_to_callback(pzip, idx, on_extract, arg, 0))
             ? 0
             : ZIP_EINVIDX;
}

ssize_t zip_entries_total(struct zip_t *zip) {
  if (!zip) {
    // zip_t handler is not initialized
    return ZIP_ENOINIT;
  }

  return (ssize_t)zip->archive.m_total_files;
}

ssize_t zip_entries_delete(struct zip_t *zip, char *const entries[],
                           size_t len) {
  ssize_t n = 0;
  ssize_t err = 0;
  struct zip_entry_mark_t *entry_mark = NULL;

  if (zip == NULL || (entries == NULL && len != 0)) {
    return ZIP_ENOINIT;
  }

  if (entries == NULL && len == 0) {
    return 0;
  }

  n = zip_entries_total(zip);
  if (n < 0) {
    return n;
  }

  entry_mark = (struct zip_entry_mark_t *)calloc(
      (size_t)n, sizeof(struct zip_entry_mark_t));
  if (!entry_mark) {
    return ZIP_EOOMEM;
  }

  zip->archive.m_zip_mode = MZ_ZIP_MODE_READING;

  err = zip_entry_set(zip, entry_mark, (size_t)n, entries, len);
  if (err < 0) {
    CLEANUP(entry_mark);
    return err;
  }

  err = zip_entries_delete_mark(zip, entry_mark, (int)n);
  CLEANUP(entry_mark);
  return err;
}

ssize_t zip_entries_deletebyindex(struct zip_t *zip, size_t entries[],
                                  size_t len) {
  ssize_t n = 0;
  ssize_t err = 0;
  struct zip_entry_mark_t *entry_mark = NULL;

  if (zip == NULL || (entries == NULL && len != 0)) {
    return ZIP_ENOINIT;
  }

  if (entries == NULL && len == 0) {
    return 0;
  }

  n = zip_entries_total(zip);
  if (n < 0) {
    return n;
  }

  entry_mark = (struct zip_entry_mark_t *)calloc(
      (size_t)n, sizeof(struct zip_entry_mark_t));
  if (!entry_mark) {
    return ZIP_EOOMEM;
  }

  zip->archive.m_zip_mode = MZ_ZIP_MODE_READING;

  err = zip_entry_setbyindex(zip, entry_mark, (size_t)n, entries, len);
  if (err < 0) {
    CLEANUP(entry_mark);
    return err;
  }

  err = zip_entries_delete_mark(zip, entry_mark, (int)n);
  CLEANUP(entry_mark);
  return err;
}

int zip_stream_extract(const char *stream, size_t size, const char *dir,
                       int (*on_extract)(const char *filename, void *arg),
                       void *arg) {
  mz_zip_archive zip_archive;
  if (!stream || !dir) {
    // Cannot parse zip archive stream
    return ZIP_ENOINIT;
  }
  if (!memset(&zip_archive, 0, sizeof(mz_zip_archive))) {
    // Cannot memset zip archive
    return ZIP_EMEMSET;
  }
  if (!mz_zip_reader_init_mem(&zip_archive, stream, size, 0)) {
    // Cannot initialize zip_archive reader
    return ZIP_ENOINIT;
  }

  return zip_archive_extract(&zip_archive, dir, on_extract, arg);
}

struct zip_t *zip_stream_open(const char *stream, size_t size, int level,
                              char mode) {
  int errnum = 0;
  return zip_stream_openwitherror(stream, size, level, mode, &errnum);
}

struct zip_t *zip_stream_openwitherror(const char *stream, size_t size,
                                       int level, char mode, int *errnum) {
  struct zip_t *zip = (struct zip_t *)calloc((size_t)1, sizeof(struct zip_t));
  if (!zip) {
    // out of memory
    *errnum = ZIP_EOOMEM;
    return NULL;
  }

  if (level < 0) {
    level = MZ_DEFAULT_LEVEL;
  }
  if ((level & 0xF) > MZ_UBER_COMPRESSION) {
    // Wrong compression level
    *errnum = ZIP_EINVLVL;
    goto cleanup;
  }
  zip->level = (mz_uint)level;

  if ((stream != NULL) && (size > 0) && (mode == 'r')) {
    if (!mz_zip_reader_init_mem(&(zip->archive), stream, size, 0)) {
      *errnum = ZIP_ERINIT;
      goto cleanup;
    }
  } else if ((stream == NULL) && (size == 0) && (mode == 'w')) {
    // Create a new archive.
    if (!mz_zip_writer_init_heap(&(zip->archive), 0, 1024)) {
      // Cannot initialize zip_archive writer
      *errnum = ZIP_EWINIT;
      goto cleanup;
    }
  } else {
    *errnum = ZIP_EINVMODE;
    goto cleanup;
  }

  *errnum = 0;
  return zip;

cleanup:
  CLEANUP(zip);
  return NULL;
}

ssize_t zip_stream_copy(struct zip_t *zip, void **buf, size_t *bufsize) {
  size_t n;

  if (!zip) {
    return (ssize_t)ZIP_ENOINIT;
  }
  zip_archive_finalize(&(zip->archive));

  n = (size_t)zip->archive.m_archive_size;
  if (bufsize != NULL) {
    *bufsize = n;
  }

  *buf = calloc(n, sizeof(unsigned char));
  memcpy(*buf, zip->archive.m_pState->m_pMem, n);

  return (ssize_t)n;
}

void zip_stream_close(struct zip_t *zip) {
  if (zip) {
    mz_zip_writer_end(&(zip->archive));
    mz_zip_reader_end(&(zip->archive));
    CLEANUP(zip);
  }
}

struct zip_t *zip_cstream_open(FILE *stream, int level, char mode) {
  int errnum = 0;
  return zip_cstream_openwitherror(stream, level, mode, &errnum);
}

struct zip_t *zip_cstream_openwitherror(FILE *stream, int level, char mode,
                                        int *errnum) {
  struct zip_t *zip = NULL;
  *errnum = 0;
  if (!stream) {
    // zip archive stream is NULL
    *errnum = ZIP_ENOFILE;
    goto cleanup;
  }

  if (level < 0)
    level = MZ_DEFAULT_LEVEL;
  if ((level & 0xF) > MZ_UBER_COMPRESSION) {
    // Wrong compression level
    *errnum = ZIP_EINVLVL;
    goto cleanup;
  }

  zip = (struct zip_t *)calloc((size_t)1, sizeof(struct zip_t));
  if (!zip) {
    // out of memory
    *errnum = ZIP_EOOMEM;
    goto cleanup;
  }

  zip->level = (mz_uint)level;
  switch (mode) {
  case 'w':
    // Create a new archive.
    if (!mz_zip_writer_init_cfile(&(zip->archive), stream,
                                  MZ_ZIP_FLAG_WRITE_ZIP64)) {
      // Cannot initialize zip_archive writer
      *errnum = ZIP_EWINIT;
      goto cleanup;
    }
    break;

  case 'r':
    if (!mz_zip_reader_init_cfile(
            &(zip->archive), stream, 0,
            zip->level | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY)) {
      // An archive file does not exist or cannot initialize
      // zip_archive reader
      *errnum = ZIP_ERINIT;
      goto cleanup;
    }
    break;

  case 'a':
  case 'd':
    if (!mz_zip_reader_init_cfile(
            &(zip->archive), stream, 0,
            zip->level | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY)) {
      // An archive file does not exist or cannot initialize
      // zip_archive reader
      *errnum = ZIP_ERINIT;
      goto cleanup;
    }
    if ((mode == 'a' || mode == 'd')) {
      if (!mz_zip_writer_init_from_reader_v2(&(zip->archive), NULL, 0)) {
        *errnum = ZIP_EWRINIT;
        mz_zip_reader_end(&(zip->archive));
        goto cleanup;
      }
    }
    break;

  default:
    *errnum = ZIP_EINVMODE;
    goto cleanup;
  }

  return zip;

cleanup:
  CLEANUP(zip);
  return NULL;
}

void zip_cstream_close(struct zip_t *zip) { zip_close(zip); }

int zip_create(const char *zipname, const char *filenames[], size_t len) {
  int err = 0;
  size_t i;
  mz_zip_archive zip_archive;
  struct MZ_FILE_STAT_STRUCT file_stat;
  mz_uint32 ext_attributes = 0;
  mz_uint16 modes;

  if (!zipname || strlen(zipname) < 1) {
    // zip_t archive name is empty or NULL
    return ZIP_EINVZIPNAME;
  }

  // Create a new archive.
  if (!memset(&(zip_archive), 0, sizeof(zip_archive))) {
    // Cannot memset zip archive
    return ZIP_EMEMSET;
  }

  if (!mz_zip_writer_init_file(&zip_archive, zipname, 0)) {
    // Cannot initialize zip_archive writer
    return ZIP_ENOINIT;
  }

  if (!memset((void *)&file_stat, 0, sizeof(struct MZ_FILE_STAT_STRUCT))) {
    return ZIP_EMEMSET;
  }

  for (i = 0; i < len; ++i) {
    const char *name = filenames[i];
    if (!name) {
      err = ZIP_EINVENTNAME;
      break;
    }

    if (MZ_FILE_STAT(name, &file_stat) != 0) {
      // problem getting information - check errno
      err = ZIP_ENOFILE;
      break;
    }

#if defined(_WIN32) || defined(__WIN32__) || defined(DJGPP)
    (void)modes; // unused
#else

    /* Initialize with permission bits--which are not implementation-optional */
    modes = file_stat.st_mode &
            (S_IRWXU | S_IRWXG | S_IRWXO | S_ISUID | S_ISGID | S_ISVTX);
    if (S_ISDIR(file_stat.st_mode))
      modes |= UNX_IFDIR;
    if (S_ISREG(file_stat.st_mode))
      modes |= UNX_IFREG;
    if (S_ISLNK(file_stat.st_mode))
      modes |= UNX_IFLNK;
    if (S_ISBLK(file_stat.st_mode))
      modes |= UNX_IFBLK;
    if (S_ISCHR(file_stat.st_mode))
      modes |= UNX_IFCHR;
    if (S_ISFIFO(file_stat.st_mode))
      modes |= UNX_IFIFO;
    if (S_ISSOCK(file_stat.st_mode))
      modes |= UNX_IFSOCK;
    ext_attributes = (modes << 16) | !(file_stat.st_mode & S_IWUSR);
    if ((file_stat.st_mode & S_IFMT) == S_IFDIR) {
      ext_attributes |= MZ_ZIP_DOS_DIR_ATTRIBUTE_BITFLAG;
    }
#endif

    if (!mz_zip_writer_add_file(&zip_archive, zip_basename(name), name, "", 0,
                                ZIP_DEFAULT_COMPRESSION_LEVEL,
                                ext_attributes)) {
      // Cannot add file to zip_archive
      err = ZIP_ENOFILE;
      break;
    }
  }

  mz_zip_writer_finalize_archive(&zip_archive);
  mz_zip_writer_end(&zip_archive);
  return err;
}

int zip_extract(const char *zipname, const char *dir,
                int (*on_extract)(const char *filename, void *arg), void *arg) {
  mz_zip_archive zip_archive;

  if (!zipname || !dir) {
    // Cannot parse zip archive name
    return ZIP_EINVZIPNAME;
  }

  if (!memset(&zip_archive, 0, sizeof(mz_zip_archive))) {
    // Cannot memset zip archive
    return ZIP_EMEMSET;
  }

  // Now try to open the archive.
  if (!mz_zip_reader_init_file(&zip_archive, zipname, 0)) {
    // Cannot initialize zip_archive reader
    return ZIP_ENOINIT;
  }

  return zip_archive_extract(&zip_archive, dir, on_extract, arg);
}

#ifdef __cplusplus
}
#endif
/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * DuckX is a free library to work with docx files.
 */

#ifndef DUCKX_H
#define DUCKX_H

#define DUCKX_VERSION "1.2.3"



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

#ifdef DUCKX_IMPLEMENTATION



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
#endif // DUCKX_IMPLEMENTATION

#endif // DUCKX_AMALG_HPP
