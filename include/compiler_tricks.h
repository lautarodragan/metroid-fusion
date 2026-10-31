#ifndef COMPILER_TRICKS_H
#define COMPILER_TRICKS_H

/*
 * Compiler matching tricks.
 *
 * Every macro in this file is a matching artifact: it exists only to coax agbcc
 * into emitting the same instructions as the original ROM. None of them changes
 * what the game does; most of them do nothing at all at runtime.
 *
 * Routing these tricks through named macros (instead of writing them inline with
 * a comment) makes them easy to spot and to grep for, and a typo in a macro name
 * breaks the build where a typo in a comment would go unnoticed.
 *
 * If you find a natural way to write a function that still matches, remove the
 * macro call. See the "Matching tricks" page of the book for the list of call
 * sites and the background on each kind of trick.
 */

/**
 * @brief Wraps statements in a "do { } while (0)" block
 *
 * The extra (empty) loop level changes the order in which agbcc allocates
 * registers and schedules the enclosed statements, without changing what they
 * do. Takes the statements without the final semicolon.
 */
#define FAKE_MATCH_BLOCK(...) do { __VA_ARGS__; } while (0)

/**
 * @brief Assigns a variable to itself
 *
 * A no-op that forces a load and store of the variable, which perturbs
 * register allocation around it.
 */
#define FAKE_MATCH_SELF_ASSIGN(x) ((x) = (x))

/**
 * @brief ORs zero into a variable
 *
 * A no-op that forces a read-modify-write of the variable (for a global: a load
 * and a store), which shifts the instruction schedule around it.
 */
#define FAKE_MATCH_NOP_OR(x) ((x) |= 0)

/**
 * @brief Adds zero to a variable
 *
 * A no-op that makes the variable "used" (and, for a memory location, read and
 * written back) at this point, which shifts register allocation around it.
 */
#define FAKE_MATCH_NOP_ADD(x) ((x) += 0)

/**
 * @brief Increments then decrements a variable
 *
 * A no-op that agbcc folds away, but only after it has changed how the
 * variable is assigned to a register (or how a constant is materialized).
 */
#define FAKE_MATCH_INC_DEC(x) ((x)++, (x)--)

/**
 * @brief Stores a value into a variable that is never read
 *
 * The dead store is removed by agbcc, but taking the value (for example the
 * address of a global) early changes register allocation and constant pool
 * usage in the code that follows.
 */
#define FAKE_MATCH_DEAD_STORE(var, value) ((var) = (value))

/**
 * @brief Copies a value into an extra local variable, used in its place
 *
 * The code would be equivalent using the source directly; the extra local
 * gets its own pseudo-register, which changes register allocation.
 */
#define FAKE_MATCH_COPY(dst, src) ((dst) = (src))

/**
 * @brief Declares a local pinned to a hard register and keeps it live
 *
 * Declares "register type name asm(reg) = value" and passes it through an
 * empty asm statement that claims to read and modify it, so agbcc must
 * materialize the value in that exact register at this point. Use it at the
 * start of a block (it is a declaration).
 *
 * This is the strongest of the tricks: it forces a specific register instead
 * of nudging the allocator, so it is the most likely to hide the original form.
 */
#define FAKE_MATCH_PIN_REG(type, name, reg, value) \
    register type name asm(reg) = (value);         \
    asm("" : "+r"(name))

#endif /* COMPILER_TRICKS_H */
