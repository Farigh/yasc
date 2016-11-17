# Get Gcc version
execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion
                OUTPUT_VARIABLE GXX_VERSION)

# Use C++ 2011 standard
set(CMAKE_CXX_FLAGS "-std=c++11")

# Add debug flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -ggdb3 -O0")

# Enable UndefinedBehaviorSanitizer (undefined behavior detection)
if (GXX_VERSION VERSION_GREATER 5.0 OR GXX_VERSION VERSION_EQUAL 5.0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

# Enable -Wall warnings
#  (includes the following for C++ :
#       -Waddress                     (warn if a pointer/fonction is used in a comparaison,
#                                      example "void func(void); if (func) ..." ou "if (x == "abc") ...")
#       -Warray-bounds=1              (only with -O2 and above
#                                      warn if an array is always accessed out of bounds)
#       -Wbool-compare                (warn about boolean expression compared with an integer value different from true/false)
#       -Wc++11-compat                (warn about C++ constructs whose meaning differs between ISO C++ 1998 and ISO C++ 2011)
#       -Wc++14-compat                (warn about C++ constructs whose meaning differs between ISO C++ 2011 and ISO C++ 2014)
#       -Wchar-subscripts             (warn if an array index if of char type (signed on some hardware))
#       -Wcomment                     (warn if comments are oppend within a comment)
#       -Wenum-compare                (warn about a comparison between values of different enumerated types)
#       -Wformat                      (warn if calls to printf and scanf, etc., supplied arguments haven't appropriate types compaired
#                                      to the format string specified, and that the conversions specified in the format string make sense)
#       -Wlogical-not-parentheses     (warn about logical not used on the left hand side operand of a comparison)
#       -Wmaybe-uninitialized         (warn if a variable in not initialized in every possible scope it is used in)
#       -Wnonnull                     (warn about passing a null pointer for arguments marked as requiring a non-null value by the
#                                      nonnull function attribute)
#       -Wopenmp-simd                 (warn if the vectorizer cost model overrides the OpenMP or the Cilk Plus simd directive set by user)
#       -Wparentheses                 (warn if parentheses are omitted in certain contexts
#                                      example "x<=y<=z" is equivalent to "(x<=y ? 1 : 0) <= z")
#                                              which is a different interpretation from that of ordinary mathematical notation)
#       -Wpointer-sign                (warn for pointer argument passing or assignment with different signedness)
#       -Wreorder                     (warn if the compiler reorder variables initialisation. It occures when variables are
#                                      initialized in a different order than they are declared.
#                                      example : "struct A {
#                                                    int i;
#                                                    int j;
#                                                    A() : j(0), i(j) { }
#                                                 };"
#                                      i and j initialisation will be modified to "i(j), j(0)" and i will probably not initialized to 0.)
#       -Wreturn-type                 (warn whenever a function is defined with a return type that defaults to int)
#       -Wsequence-point              (warn about code that may have undefined semantics because of violations of sequence point rules
#                                      in the C and C++ standards
#                                      exemple : "a = a++;", "a[n] = b[n++]" or "a[i++] = i;")
#       -Wsign-compare                (warn when a comparison between signed and unsigned values could produce an incorrect result when
#                                      the signed value is converted to unsigned)
#       -Wstrict-aliasing             (this option is only active when -fstrict-aliasing is active)
#       -Wstrict-overflow=1           (this option is only active when -fstrict-aliasing is active)
#       -Wswitch                      (warn whenever a switch statement has an index of enumerated type and lacks a case for one or more of
#                                      the named codes of that enumeration (The presence of a default label prevents this warning))
#       -Wtrigraphs                   (warn if any trigraphs are encountered that might change the meaning of the program)
#       -Wuninitialized               (warn if an automatic variable is used without first being initialized)
#       -Wunknown-pragmas             (warn when a "#pragma" directive is encountered that is not understood by GCC)
#       -Wunused-but-set-variable     (warn whenever a local variable is assigned to, but otherwise unused (aside from its declaration))
#       -Wunused-function             (warn whenever a static function is declared but not defined or a non-inline static function is unused)
#       -Wunused-label                (warn whenever a label is declared but not used)
#       -Wunused-local-typedefs       (warn when a typedef locally defined in a function is not used)
#       -Wunused-value                (warn whenever a statement computes a result that is explicitly not used)
#       -Wunused-variable             (warn whenever a local variable or non-constant static variable is unused aside from its declaration)
#       -Wvolatile-register-var       (warn if a register variable is declared volatile)
#  )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Set associated Werror separately to avoid errors on new warnings added in Wall in further gcc version
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=array-bounds")
if (GXX_VERSION VERSION_GREATER 5.0 OR GXX_VERSION VERSION_EQUAL 5.0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=bool-compare")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=c++11-compat")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=char-subscripts")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=comment")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=enum-compare")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=format")
if (GXX_VERSION VERSION_GREATER 5.0 OR GXX_VERSION VERSION_EQUAL 5.0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=logical-not-parentheses")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=nonnull")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=parentheses")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=pointer-sign")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=reorder")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=return-type")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=sequence-point")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=sign-compare")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=strict-aliasing")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=switch")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=trigraphs")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=uninitialized")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=unknown-pragmas")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=unused-but-set-variable")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=unused-function")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=unused-label")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=unused-local-typedefs")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=unused-value")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=unused-variable")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=volatile-register-var")

# Enable -Wextra warnings
#  (includes the following for C++ :
#       -Wclobbered                   (warn for variables that might be changed by longjmp or vfork)
#       -Wempty-body                  (warn if an empty body occurs in an 'if', 'else' or 'do while' statement)
#       -Wignored-qualifiers          (warn if the return type of a function is a scalar types or void and has a type qualifier such as 'const')
#       -Wmissing-field-initializers  (warn if a structure's initializer has some fields missing)
#       -Wtype-limits                 (warn if a comparison is always true or always false due to the limited range of the data type)
#       -Wuninitialized               (warn if an automatic variable is used without first being initialized or if a variable may be clobbered by a setjmp call)
#       -Wunused-parameter            (warn whenever a function parameter is unused aside from its declaration)
#       -Wunused-but-set-parameter    (warn whenever a function parameter is assigned to, but otherwise unused)
#  )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")

# Set associated Werror
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=clobbered")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=empty-body")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=ignored-qualifiers")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=missing-field-initializers")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=type-limits")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=uninitialized")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=unused-parameter")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=unused-but-set-parameter")

# The option -Wextra also prints warning messages for the following cases:
# - A pointer is compared against integer zero with <, <=, >, or >=.
# - (C++ only) An enumerator and a non-enumerator both appear in a conditional expression.
# - (C++ only) Ambiguous virtual bases.
# - (C++ only) Subscripting an array that has been declared register.
# - (C++ only) Taking the address of a variable that has been declared register.
# - (C++ only) A base class is not initialized in a derived class's copy constructor.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=extra")

### Add even more warnings

# Warn whenever a pointer is cast such that the required alignment of the target is increased
# Example: char * => int * on machines where integers can only be accessed at two- or four-byte boundaries
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=cast-align")

# Warn whenever a pointer is cast so as to remove a type qualifier from the target type, example : const char* => char*
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=cast-qual")

# Warn for conditionally-supported (C++11 [intro.defs]) constructs.
if (GXX_VERSION VERSION_GREATER 5.0 OR GXX_VERSION VERSION_EQUAL 5.0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=conditionally-supported")
endif()

# Warn for implicit conversions that may alter a value, example : int => uint
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=conversion")

# Warn when a class seems unusable because all the constructors or destructors in that class are private, and it has neither friends nor public static member functions.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=ctor-dtor-privacy")

# Warn when a value of type float is implicitly promoted to double
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=double-promotion")

# Check printf-like format so variable type matched the specified format
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2 -Werror=format-security")

# Warn about uninitialized variables that are initialized with themselves, example : "int i = i;"
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=init-self")

# Warn about suspicious uses of logical operators in expressions (&&, || instead of &, |)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=logical-op")

# Warn if a user-supplied include directory via "-I<include_dir>" does not exist
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=missing-include-dirs")

# Warn if an old-style (C-style) cast to a non-void type is used within a C++ program.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=old-style-cast")

# Warn when a function declaration hides virtual functions from a base class.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=overloaded-virtual")

# Warn about anything that depends on the “size of” a function type or of void.
# In C++, warn also when an arithmetic operation involves NULL.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=pointer-arith")

# Warn if anything is declared more than once in the same scope, even in cases where multiple declaration is valid and changes nothing.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=redundant-decls")

# Warn whenever a local variable or type declaration shadows another variable, parameter, type, or class member (in C++), or
# whenever a built-in function is shadowed, example : "int class =1;"
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=shadow")

# Warn for implicit conversions that may change the sign of an integer value, like assigning a signed integer
# expression to an unsigned integer variable. An explicit cast silences the warning
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=sign-conversion")

# This option is only active when -fstack-protector is active.
# Warns about functions that are not protected against stack smashing.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=stack-protector")

# Warn about functions that might be candidates for attributes pure, const or noreturn
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=suggest-attribute=noreturn")

# Warn about overriding virtual functions that are not marked with the override keyword.
# Note: suggest-final-types and suggest-final-methods are pointless with libraries
if (GXX_VERSION VERSION_GREATER 5.0 OR GXX_VERSION VERSION_EQUAL 5.0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=suggest-override")  # Not available with GCC 4.8.4
endif()

# Warn whenever a switch statement does not have a 'default' case
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=switch-default")

# Warn whenever a switch statement has an index of enumerated type and lacks a case for one or more of the named codes of
# that enumeration
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=switch-enum")

# Warn when an expression is casted to its own type.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=useless-cast")

# Warn when a literal '0' is used as null pointer constant. This can be useful to facilitate the conversion to nullptr in C++11.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=zero-as-null-pointer-constant")

# Gcc compiler enables many warning by default, convert them all to errors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=attributes")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=conversion-null")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=coverage-mismatch")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=cpp")
if (GXX_VERSION VERSION_GREATER 5.0 OR GXX_VERSION VERSION_EQUAL 5.0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=delete-incomplete")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=deprecated")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=deprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=div-by-zero")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=free-nonheap-object")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=implicit-function-declaration")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=inherited-variadic-ctor")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=int-to-pointer-cast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=invalid-memory-model")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=invalid-offsetof")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=main")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=narrowing")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=non-template-friend")
if (GXX_VERSION VERSION_GREATER 5.0 OR GXX_VERSION VERSION_EQUAL 5.0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=normalized")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=overflow")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=packed-bitfield-compat")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=pragmas")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=property-assign-default")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=protocol")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=pmf-conversions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=pointer-to-int-cast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=return-local-addr")
if (GXX_VERSION VERSION_GREATER 5.0 OR GXX_VERSION VERSION_EQUAL 5.0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=shift-count-negative")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=shift-count-overflow")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=sizeof-array-argument")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=sync-nand")
if (GXX_VERSION VERSION_GREATER 5.0 OR GXX_VERSION VERSION_EQUAL 5.0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=switch-bool")  # Not available with GCC 4.8.4
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=unused-result")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=varargs")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=virtual-move-assign")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=volatile-register-var")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=vla")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=write-strings")

# Cross compilling only warning
if (CMAKE_CROSSCOMPILING)
    if (GXX_VERSION VERSION_GREATER 5.0 OR GXX_VERSION VERSION_EQUAL 5.0)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=poison-system-directories")
    endif()
endif()

# Enable gcc colors
if (GXX_VERSION VERSION_GREATER 4.9 OR GXX_VERSION VERSION_EQUAL 4.9)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=auto")
endif()