#ifndef STRUCT_LAYOUT_H
#define STRUCT_LAYOUT_H

/*
 * Helpers to describe the bytes of a struct that no code ever accesses, and to
 * pin the layout of a struct with compile-time checks.
 * See the "Struct layout" page of the book (book/src/struct-layout.md).
 *
 * - Bytes that the compiler inserts by itself (before an aligned member, or at
 *   the end of the struct, up to its alignment: agbcc aligns every struct and
 *   union to 4 bytes) are not declared: the layout is pinned with
 *   ASSERT_OFFSET (the members that follow the gap) and ASSERT_SIZE instead.
 * - UNUSED(n): n bytes that the original declared (the gap can't be explained by
 *   alignment), but that no code reads or writes.
 * - PADDING(n): n bytes of explicit padding by design (filling a struct to a
 *   fixed size, or placing the members of an overlay struct at an offset).
 * - UNUSED_BITS(type, n): n bits of a bit-field unit that no code accesses
 *   (an unnamed bit-field, so it takes no name).
 *
 * The members declared by UNUSED and PADDING get a unique name built from the
 * line number (_unused_<line>, _padding_<line>): they aren't meant to be used,
 * two of them can't be on the same line of a struct.
 */

#define STRUCT_LAYOUT_CONCAT_(a, b) a##b
#define STRUCT_LAYOUT_CONCAT(a, b) STRUCT_LAYOUT_CONCAT_(a, b)

#define UNUSED(n) unsigned char STRUCT_LAYOUT_CONCAT(_unused_, __LINE__)[n]
#define PADDING(n) unsigned char STRUCT_LAYOUT_CONCAT(_padding_, __LINE__)[n]
#define UNUSED_BITS(type, n) type : n

/*
 * Compile-time assertion, usable at file scope and in functions. A failure is a
 * "size of array `_static_assert_N' is negative" error. It declares a typedef
 * (no code or data); the name uses __COUNTER__ since redefining a typedef is an
 * error, even with the same type (two headers could assert on the same line).
 */
#define STATIC_ASSERT(cond) \
    typedef char STRUCT_LAYOUT_CONCAT(_static_assert_, __COUNTER__)[(cond) ? 1 : -1]

#define ASSERT_OFFSET(type, member, offset) STATIC_ASSERT((int)&((type*)0)->member == (offset))
#define ASSERT_SIZE(type, size) STATIC_ASSERT(sizeof(type) == (size))

#endif /* STRUCT_LAYOUT_H */
