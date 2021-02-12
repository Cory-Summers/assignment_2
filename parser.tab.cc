// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "parser.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

// //                    "%code requires" blocks.
#line 6 "parser.y" // lalr1.cc:408

  #include "scanner-token.hpp"
  #include "print-values.hpp"

  namespace parser
  {
    struct Context; //Forward Decl
    struct Token //I hate it but it works
    {
      Token() : token() {}
      scanner::Token token;
    };
  }
  namespace scanner
  {
    class TokenLexer; //Forward Decl
  };


#line 68 "parser.tab.cc" // lalr1.cc:408


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

#line 3 "parser.y" // lalr1.cc:408
namespace parser {
#line 138 "parser.tab.cc" // lalr1.cc:408

  template <class T, class S = std::vector<T> >
  class stack
  {
  public:
    // Hide our reversed order.
    typedef typename S::reverse_iterator iterator;
    typedef typename S::const_reverse_iterator const_iterator;

    stack ()
      : seq_ ()
    {
      seq_.reserve (200);
    }

    stack (unsigned int n)
      : seq_ (n)
    {}

    inline
    T&
    operator[] (unsigned int i)
    {
      return seq_[seq_.size () - 1 - i];
    }

    inline
    const T&
    operator[] (unsigned int i) const
    {
      return seq_[seq_.size () - 1 - i];
    }

    /// Steal the contents of \a t.
    ///
    /// Close to move-semantics.
    inline
    void
    push (T& t)
    {
      seq_.push_back (T());
      operator[](0).move (t);
    }

    inline
    void
    pop (unsigned int n = 1)
    {
      for (; n; --n)
        seq_.pop_back ();
    }

    void
    clear ()
    {
      seq_.clear ();
    }

    inline
    typename S::size_type
    size () const
    {
      return seq_.size ();
    }

    inline
    const_iterator
    begin () const
    {
      return seq_.rbegin ();
    }

    inline
    const_iterator
    end () const
    {
      return seq_.rend ();
    }

  private:
    stack (const stack&);
    stack& operator= (const stack&);
    /// The wrapped container.
    S seq_;
  };

  /// Present a slice of the top of a stack.
  template <class T, class S = stack<T> >
  class slice
  {
  public:
    slice (const S& stack, unsigned int range)
      : stack_ (stack)
      , range_ (range)
    {}

    inline
    const T&
    operator [] (unsigned int i) const
    {
      return stack_[range_ - i];
    }

  private:
    const S& stack_;
    unsigned int range_;
  };

  /// Abstract a position.
  class position
  {
  public:
    /// Construct a position.
    explicit position (std::string* f = YY_NULLPTR,
                       unsigned int l = 1u,
                       unsigned int c = 1u)
      : filename (f)
      , line (l)
      , column (c)
    {
    }


    /// Initialization.
    void initialize (std::string* fn = YY_NULLPTR,
                     unsigned int l = 1u,
                     unsigned int c = 1u)
    {
      filename = fn;
      line = l;
      column = c;
    }

    /** \name Line and Column related manipulators
     ** \{ */
    /// (line related) Advance to the COUNT next lines.
    void lines (int count = 1)
    {
      if (count)
        {
          column = 1u;
          line = add_ (line, count, 1);
        }
    }

    /// (column related) Advance to the COUNT next columns.
    void columns (int count = 1)
    {
      column = add_ (column, count, 1);
    }
    /** \} */

    /// File name to which this position refers.
    std::string* filename;
    /// Current line number.
    unsigned int line;
    /// Current column number.
    unsigned int column;

  private:
    /// Compute max(min, lhs+rhs) (provided min <= lhs).
    static unsigned int add_ (unsigned int lhs, int rhs, unsigned int min)
    {
      return (0 < rhs || -static_cast<unsigned int>(rhs) < lhs
              ? rhs + lhs
              : min);
    }
  };

  /// Add \a width columns, in place.
  inline position&
  operator+= (position& res, int width)
  {
    res.columns (width);
    return res;
  }

  /// Add \a width columns.
  inline position
  operator+ (position res, int width)
  {
    return res += width;
  }

  /// Subtract \a width columns, in place.
  inline position&
  operator-= (position& res, int width)
  {
    return res += -width;
  }

  /// Subtract \a width columns.
  inline position
  operator- (position res, int width)
  {
    return res -= width;
  }

  /// Compare two position objects.
  inline bool
  operator== (const position& pos1, const position& pos2)
  {
    return (pos1.line == pos2.line
            && pos1.column == pos2.column
            && (pos1.filename == pos2.filename
                || (pos1.filename && pos2.filename
                    && *pos1.filename == *pos2.filename)));
  }

  /// Compare two position objects.
  inline bool
  operator!= (const position& pos1, const position& pos2)
  {
    return !(pos1 == pos2);
  }

  /** \brief Intercept output stream redirection.
   ** \param ostr the destination output stream
   ** \param pos a reference to the position to redirect
   */
  template <typename YYChar>
  inline std::basic_ostream<YYChar>&
  operator<< (std::basic_ostream<YYChar>& ostr, const position& pos)
  {
    if (pos.filename)
      ostr << *pos.filename << ':';
    return ostr << pos.line << '.' << pos.column;
  }

  /// Abstract a location.
  class location
  {
  public:

    /// Construct a location from \a b to \a e.
    location (const position& b, const position& e)
      : begin (b)
      , end (e)
    {
    }

    /// Construct a 0-width location in \a p.
    explicit location (const position& p = position ())
      : begin (p)
      , end (p)
    {
    }

    /// Construct a 0-width location in \a f, \a l, \a c.
    explicit location (std::string* f,
                       unsigned int l = 1u,
                       unsigned int c = 1u)
      : begin (f, l, c)
      , end (f, l, c)
    {
    }


    /// Initialization.
    void initialize (std::string* f = YY_NULLPTR,
                     unsigned int l = 1u,
                     unsigned int c = 1u)
    {
      begin.initialize (f, l, c);
      end = begin;
    }

    /** \name Line and Column related manipulators
     ** \{ */
  public:
    /// Reset initial location to final location.
    void step ()
    {
      begin = end;
    }

    /// Extend the current location to the COUNT next columns.
    void columns (int count = 1)
    {
      end += count;
    }

    /// Extend the current location to the COUNT next lines.
    void lines (int count = 1)
    {
      end.lines (count);
    }
    /** \} */


  public:
    /// Beginning of the located region.
    position begin;
    /// End of the located region.
    position end;
  };

  /// Join two locations, in place.
  inline location& operator+= (location& res, const location& end)
  {
    res.end = end.end;
    return res;
  }

  /// Join two locations.
  inline location operator+ (location res, const location& end)
  {
    return res += end;
  }

  /// Add \a width columns to the end position, in place.
  inline location& operator+= (location& res, int width)
  {
    res.columns (width);
    return res;
  }

  /// Add \a width columns to the end position.
  inline location operator+ (location res, int width)
  {
    return res += width;
  }

  /// Subtract \a width columns to the end position, in place.
  inline location& operator-= (location& res, int width)
  {
    return res += -width;
  }

  /// Subtract \a width columns to the end position.
  inline location operator- (location res, int width)
  {
    return res -= width;
  }

  /// Compare two location objects.
  inline bool
  operator== (const location& loc1, const location& loc2)
  {
    return loc1.begin == loc2.begin && loc1.end == loc2.end;
  }

  /// Compare two location objects.
  inline bool
  operator!= (const location& loc1, const location& loc2)
  {
    return !(loc1 == loc2);
  }

  /** \brief Intercept output stream redirection.
   ** \param ostr the destination output stream
   ** \param loc a reference to the location to redirect
   **
   ** Avoid duplicate information.
   */
  template <typename YYChar>
  inline std::basic_ostream<YYChar>&
  operator<< (std::basic_ostream<YYChar>& ostr, const location& loc)
  {
    unsigned int end_col = 0 < loc.end.column ? loc.end.column - 1 : 0;
    ostr << loc.begin;
    if (loc.end.filename
        && (!loc.begin.filename
            || *loc.begin.filename != *loc.end.filename))
      ostr << '-' << loc.end.filename << ':' << loc.end.line << '.' << end_col;
    else if (loc.begin.line < loc.end.line)
      ostr << '-' << loc.end.line << '.' << end_col;
    else if (loc.begin.column < end_col)
      ostr << '-' << end_col;
    return ostr;
  }




  /// A Bison parser.
  class  CMinParser 
  {
  public:
#ifndef YYSTYPE
    /// Symbol semantic values.

#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        TYPE_INT = 258,
        TYPE_CHAR = 259,
        TYPE_BOOL = 260,
        T_DECL_SEP = 261,
        T_COLON = 262,
        T_LHS_BRACK = 263,
        T_RHS_BRACK = 264,
        T_END_STMT = 265,
        T_LHS_PAREN = 266,
        T_RHS_PAREN = 267,
        T_LHS_BRACE = 268,
        T_RHS_BRACE = 269,
        T_OP_ASSIGN = 270,
        T_KEY_IF = 271,
        T_KEY_THEN = 272,
        T_KEY_ELSE = 273,
        T_KEY_WHILE = 274,
        T_KEY_DO = 275,
        T_KEY_FOR = 276,
        T_KEY_BY = 277,
        T_KEY_RETURN = 278,
        T_KEY_IN = 279,
        T_KEY_BREAK = 280,
        T_KEY_OR = 281,
        T_KEY_AND = 282,
        T_KEY_STATIC = 283,
        T_KEY_NOT = 284,
        T_DECREMENT = 285,
        T_INCREMENT = 286,
        T_OP_LES_EQ = 287,
        T_OP_LESS = 288,
        T_OP_GREAT = 289,
        T_OP_GRE_EQ = 290,
        T_OP_EQUALIVE = 291,
        T_OP_NOT_EQUAL = 292,
        T_OP_COMP_ASG = 293,
        T_OP_MAX = 294,
        T_OP_MIN = 295,
        T_OP_MINUS = 296,
        T_OP_PLUS = 297,
        T_OP_MULTI = 298,
        T_OP_DIVIDE = 299,
        T_OP_MODULO = 300,
        T_OP_GENERATOR = 301,
        T_OP_ADDASS = 302,
        T_OP_MINASS = 303,
        T_OP_MULASS = 304,
        T_OP_DIVASS = 305,
        T_STRINGCONST = 306,
        T_NUMCONST = 307,
        T_CHARCONST = 308,
        T_BOOLCONST = 309,
        T_IDENTIFIER = 310
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols.
      basic_symbol (typename Base::kind_type t,
                    const location_type& l);

      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;


    /// Build a parser object.
     CMinParser  (scanner::TokenLexer & scanner_yyarg, parser::Context & context_yyarg);
    virtual ~ CMinParser  ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
     CMinParser  (const  CMinParser &);
     CMinParser & operator= (const  CMinParser &);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short int yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (int t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned char yytable_[];

  static const short int yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


#if YYDEBUG
    /// For a symbol, its name in clear.
    static const char* const yytname_[];

  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 219,     ///< Last index in yytable_.
      yynnts_ = 49,  ///< Number of nonterminal symbols.
      yyfinal_ = 12, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 67  ///< Number of tokens.
    };


    // User arguments.
    scanner::TokenLexer & scanner;
    parser::Context & context;
  };


#line 3 "parser.y" // lalr1.cc:408
} // parser
#line 913 "parser.tab.cc" // lalr1.cc:408





// User implementation prologue.

#line 921 "parser.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 28 "parser.y" // lalr1.cc:413

  #include "driver-class.hpp"
  #include "context-class.hpp"
  #undef yylex
  #define yylex scanner.yylex
%

#line 931 "parser.tab.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 3 "parser.y" // lalr1.cc:479
namespace parser {
#line 1017 "parser.tab.cc" // lalr1.cc:479

  /// Build a parser object.
   CMinParser :: CMinParser  (scanner::TokenLexer & scanner_yyarg, parser::Context & context_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      context (context_yyarg)
  {}

   CMinParser ::~ CMinParser  ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
   CMinParser ::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
   CMinParser ::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
   CMinParser ::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
   CMinParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
   CMinParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
   CMinParser ::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
   CMinParser ::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
   CMinParser ::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
   CMinParser ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
   CMinParser ::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
   CMinParser ::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
   CMinParser ::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
   CMinParser ::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
   CMinParser ::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
   CMinParser ::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
   CMinParser ::by_state::by_state ()
    : state (empty_state)
  {}

  inline
   CMinParser ::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
   CMinParser ::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
   CMinParser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
   CMinParser ::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
   CMinParser ::symbol_number_type
   CMinParser ::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
   CMinParser ::stack_symbol_type::stack_symbol_type ()
  {}


  inline
   CMinParser ::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
   CMinParser ::stack_symbol_type&
   CMinParser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
   CMinParser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
   CMinParser ::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
   CMinParser ::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
   CMinParser ::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
   CMinParser ::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   CMinParser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   CMinParser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   CMinParser ::debug_level_type
   CMinParser ::debug_level () const
  {
    return yydebug_;
  }

  void
   CMinParser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline  CMinParser ::state_type
   CMinParser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
   CMinParser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
   CMinParser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   CMinParser ::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, context));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 74 "parser.y" // lalr1.cc:859
    {}
#line 1460 "parser.tab.cc" // lalr1.cc:859
    break;


#line 1464 "parser.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
   CMinParser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
   CMinParser ::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const short int  CMinParser ::yypact_ninf_ = -132;

  const signed char  CMinParser ::yytable_ninf_ = -1;

  const short int
   CMinParser ::yypact_[] =
  {
       6,  -132,  -132,  -132,    -5,    26,     6,  -132,  -132,   -18,
    -132,    69,  -132,  -132,    14,     8,  -132,    35,    -3,    37,
      48,  -132,     4,    69,     2,  -132,   154,    65,    62,  -132,
     139,    69,    64,    59,    70,  -132,   154,   154,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,    23,    47,    49,  -132,  -132,
      84,   -10,    36,  -132,    58,  -132,  -132,  -132,  -132,  -132,
      85,    -3,  -132,  -132,   154,   154,    34,    31,    86,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,    87,    47,
     -12,  -132,  -132,   139,    88,  -132,   154,   154,   154,   154,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,    58,
      58,  -132,  -132,    58,  -132,  -132,  -132,    58,  -132,  -132,
    -132,    16,    -9,     7,    78,  -132,    89,  -132,  -132,   154,
    -132,  -132,   154,  -132,  -132,    92,  -132,    91,    99,    49,
    -132,     0,   -10,    36,  -132,    69,  -132,     2,   124,   139,
     139,   154,  -132,  -132,  -132,  -132,  -132,   154,     2,    15,
    -132,  -132,    80,  -132,    94,   -31,  -132,    17,  -132,   139,
     139,   154,  -132,  -132,  -132,    19,   154,    47
  };

  const unsigned char
   CMinParser ::yydefact_[] =
  {
       0,    16,    17,    18,     0,     0,     2,     4,     5,     0,
       6,    21,     1,     3,    14,     0,    11,    13,     0,     0,
      22,    24,     0,    21,     0,     7,     0,    28,    25,    27,
       0,     0,     0,     0,    14,    10,     0,     0,    90,    91,
      92,   107,   105,   106,   108,    95,    12,    61,    63,    65,
      67,    76,    80,    84,     0,    89,    94,    93,    98,    99,
       0,     0,    37,    39,     0,     0,     0,     0,     0,    20,
      30,    31,    32,    43,    44,    33,    34,    35,     0,    59,
      94,    23,    15,     0,     0,    64,     0,   101,     0,     0,
      68,    69,    70,    71,    72,    73,    74,    78,    77,     0,
       0,    82,    81,     0,    85,    86,    87,     0,    88,    29,
      26,    41,     0,     0,     0,    52,     0,    54,    36,     0,
      58,    57,     0,    19,    97,     0,   104,     0,   102,    60,
      62,    66,    75,    79,    83,     0,    40,     0,     0,     0,
       0,     0,    53,    55,    56,    96,   100,     0,     0,     0,
      38,    42,    46,    47,     0,    49,   103,     0,     9,     0,
       0,     0,     8,    45,    48,    50,     0,    51
  };

  const short int
   CMinParser ::yypgoto_[] =
  {
    -132,  -132,  -132,   136,  -132,  -132,  -131,   119,  -132,     1,
    -132,   121,  -132,   115,  -132,    90,   -80,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,   -34,   -26,
      60,   -21,  -132,  -132,    50,  -132,    52,  -132,    55,  -132,
     -50,  -132,  -132,   -22,  -132,  -132,  -132,  -132,  -132
  };

  const short int
   CMinParser ::yydefgoto_[] =
  {
      -1,     5,     6,     7,     8,   136,    15,    16,    17,    18,
      10,    19,    20,    21,    28,    29,    69,    70,    71,   111,
     138,    72,    73,    74,    75,   154,    76,    77,    78,    79,
      47,    48,    49,    99,    50,   100,    51,   103,    52,   107,
      53,    54,    55,    56,    57,    58,   127,   128,    59
  };

  const unsigned char
   CMinParser ::yytable_[] =
  {
      46,     9,    84,   123,   108,    88,   149,     9,    80,     1,
       2,     3,    11,   119,    80,    24,    85,   157,   139,     1,
       2,     3,    24,    25,    24,    22,    12,    88,   120,   121,
     158,    23,   162,   116,    86,   161,   122,   140,   112,   113,
      87,   101,   102,    88,    26,    80,   115,    14,    36,    97,
      98,   166,   125,   126,   135,    88,    30,   134,   151,   152,
     153,    80,    27,    31,    80,    80,    32,    34,   130,    61,
      37,     4,     1,     2,     3,    36,    60,    82,    83,   163,
     164,    22,    38,    88,    39,   143,    89,    40,   144,   104,
     105,   106,    41,    42,    43,    44,    45,    80,   109,   114,
      80,   117,   118,   141,   142,   145,   147,   124,   159,    38,
     146,    39,   137,   156,    40,   155,    80,    80,    80,    41,
      42,    43,    44,    45,   160,    80,    90,    91,    92,    93,
      94,    95,    96,    97,    98,   165,   148,    80,    80,    62,
     167,    36,    13,    35,    33,    63,    81,   150,   129,   131,
      64,   110,   132,    65,    62,    66,    36,    67,   133,    68,
      63,     0,     0,    37,     0,    64,     0,     0,    65,     0,
      66,    36,    67,     0,    68,    38,     0,    39,    37,     0,
      40,     0,     0,     0,     0,    41,    42,    43,    44,    45,
      38,     0,    39,    37,     0,    40,     0,     0,     0,     0,
      41,    42,    43,    44,    45,    38,     0,    39,     0,     0,
      40,     0,     0,     0,     0,    41,    42,    43,    44,    45
  };

  const short int
   CMinParser ::yycheck_[] =
  {
      26,     0,    36,    83,    54,    36,   137,     6,    30,     3,
       4,     5,    17,    25,    36,     7,    37,   148,    27,     3,
       4,     5,     7,    15,     7,    11,     0,    36,    40,    41,
      15,    17,    15,    67,    11,    66,    48,    30,    64,    65,
      17,    51,    52,    36,     9,    67,    15,    65,    17,    49,
      50,    32,    86,    87,    38,    36,    19,   107,   138,   139,
     140,    83,    65,    15,    86,    87,    62,    65,    89,     7,
      39,    65,     3,     4,     5,    17,    11,    13,    19,   159,
     160,    11,    51,    36,    53,   119,    37,    56,   122,    53,
      54,    55,    61,    62,    63,    64,    65,   119,    13,    65,
     122,    15,    15,    25,    15,    13,     7,    19,    28,    51,
      19,    53,   111,   147,    56,   141,   138,   139,   140,    61,
      62,    63,    64,    65,    30,   147,    42,    43,    44,    45,
      46,    47,    48,    49,    50,   161,   135,   159,   160,    15,
     166,    17,     6,    24,    23,    21,    31,    23,    88,    99,
      26,    61,   100,    29,    15,    31,    17,    33,   103,    35,
      21,    -1,    -1,    39,    -1,    26,    -1,    -1,    29,    -1,
      31,    17,    33,    -1,    35,    51,    -1,    53,    39,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      51,    -1,    53,    39,    -1,    56,    -1,    -1,    -1,    -1,
      61,    62,    63,    64,    65,    51,    -1,    53,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65
  };

  const unsigned char
   CMinParser ::yystos_[] =
  {
       0,     3,     4,     5,    65,    68,    69,    70,    71,    76,
      77,    17,     0,    70,    65,    73,    74,    75,    76,    78,
      79,    80,    11,    17,     7,    15,     9,    65,    81,    82,
      19,    15,    62,    78,    65,    74,    17,    39,    51,    53,
      56,    61,    62,    63,    64,    65,    96,    97,    98,    99,
     101,   103,   105,   107,   108,   109,   110,   111,   112,   115,
      11,     7,    15,    21,    26,    29,    31,    33,    35,    83,
      84,    85,    88,    89,    90,    91,    93,    94,    95,    96,
     110,    80,    13,    19,    95,    98,    11,    17,    36,    37,
      42,    43,    44,    45,    46,    47,    48,    49,    50,   100,
     102,    51,    52,   104,    53,    54,    55,   106,   107,    13,
      82,    86,    96,    96,    65,    15,    95,    15,    15,    25,
      40,    41,    48,    83,    19,    95,    95,   113,   114,    97,
      98,   101,   103,   105,   107,    38,    72,    76,    87,    27,
      30,    25,    15,    95,    95,    13,    19,     7,    76,    73,
      23,    83,    83,    83,    92,    96,    95,    73,    15,    28,
      30,    66,    15,    83,    83,    96,    32,    96
  };

  const unsigned char
   CMinParser ::yyr1_[] =
  {
       0,    67,    68,    69,    69,    70,    70,    71,    72,    72,
      73,    73,    74,    74,    75,    75,    76,    76,    76,    77,
      77,    78,    78,    79,    79,    80,    81,    81,    82,    82,
      83,    83,    83,    83,    83,    83,    84,    84,    85,    86,
      86,    87,    87,    88,    88,    89,    90,    91,    91,    92,
      92,    92,    93,    93,    94,    95,    95,    95,    95,    95,
      96,    96,    97,    97,    98,    98,    99,    99,   100,   100,
     100,   100,   100,   100,   100,   101,   101,   102,   102,   103,
     103,   104,   104,   105,   105,   106,   106,   106,   107,   107,
     108,   108,   108,   109,   109,   110,   110,   111,   111,   111,
     112,   113,   113,   114,   114,   115,   115,   115,   115
  };

  const unsigned char
   CMinParser ::yyr2_[] =
  {
       0,     2,     1,     2,     1,     1,     1,     3,     4,     3,
       3,     1,     3,     1,     1,     4,     1,     1,     1,     6,
       5,     0,     1,     3,     1,     2,     3,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     2,     1,     4,     0,
       2,     0,     2,     1,     1,     6,     4,     4,     6,     1,
       3,     5,     2,     3,     2,     3,     3,     2,     2,     1,
       3,     1,     3,     1,     2,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     4,     3,     1,     1,
       4,     0,     1,     3,     1,     1,     1,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  CMinParser ::yytname_[] =
  {
  "$end", "error", "$undefined", "TYPE_INT", "TYPE_CHAR", "TYPE_BOOL",
  "T_DECL_SEP", "','", "T_COLON", "':'", "T_LHS_BRACK", "'['",
  "T_RHS_BRACK", "']'", "T_END_STMT", "';'", "T_LHS_PAREN", "'('",
  "T_RHS_PAREN", "')'", "T_LHS_BRACE", "'{'", "T_RHS_BRACE", "'}'",
  "T_OP_ASSIGN", "'='", "\"if\"", "\"then\"", "\"else\"", "\"while\"",
  "\"do\"", "\"for\"", "\"by\"", "\"return\"", "\"in\"", "\"break\"",
  "\"or\"", "\"and\"", "\"static\"", "\"not\"", "\"--\"", "\"++\"",
  "T_OP_LES_EQ", "T_OP_LESS", "T_OP_GREAT", "T_OP_GRE_EQ", "T_OP_EQUALIVE",
  "T_OP_NOT_EQUAL", "T_OP_COMP_ASG", "T_OP_MAX", "T_OP_MIN", "T_OP_MINUS",
  "T_OP_PLUS", "T_OP_MULTI", "T_OP_DIVIDE", "T_OP_MODULO",
  "T_OP_GENERATOR", "T_OP_ADDASS", "T_OP_MINASS", "T_OP_MULASS",
  "T_OP_DIVASS", "T_STRINGCONST", "T_NUMCONST", "T_CHARCONST",
  "T_BOOLCONST", "T_IDENTIFIER", "\"to\"", "$accept", "Program",
  "DeclList", "Decl", "VariableDecl", "ScopedVariableDecl",
  "VariableDeclList", "VariableDeclInit", "VariableDeclID",
  "TypeSpecifier", "FunctionDecl", "Parameters", "ParameterList",
  "ParameterTypeList", "ParameterIDList", "ParameterID", "Statement",
  "ExpressionStmt", "CompoundStmt", "LocalDecls", "StatementList",
  "ConditionStmt", "CompleteCondition", "IncompleteCondition",
  "IteratorStmt", "IteratorRange", "ReturnStmt", "BreakStmt", "Expression",
  "SimpleExpression", "AndExpr", "UnaryReletiveExpr", "ReletiveExpr",
  "ReletiveOper", "MinMaxExp", "MinMaxOper", "SumExpr", "SumOper",
  "MulExp", "MulOp", "UnaryExpr", "UnaryOper", "Factor", "Mutable",
  "Immutable", "Call", "Arguments", "ArgumentList", "Constant", YY_NULLPTR
  };


  const unsigned short int
   CMinParser ::yyrline_[] =
  {
       0,    74,    74,    76,    77,    80,    81,    85,    88,    89,
      92,    93,    96,    97,   100,   101,   104,   105,   106,   110,
     111,   114,   115,   118,   119,   122,   125,   126,   129,   130,
     134,   135,   136,   137,   138,   139,   144,   145,   148,   151,
     152,   155,   156,   159,   160,   163,   166,   169,   170,   173,
     174,   175,   178,   179,   182,   186,   187,   188,   189,   190,
     193,   194,   197,   198,   201,   202,   205,   206,   209,   210,
     211,   212,   213,   214,   215,   218,   219,   222,   223,   226,
     227,   230,   231,   234,   235,   238,   239,   240,   243,   244,
     247,   248,   249,   252,   253,   256,   257,   260,   261,   262,
     265,   268,   269,   272,   273,   276,   277,   278,   279
  };

  // Print the state stack on the debug stream.
  void
   CMinParser ::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
   CMinParser ::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
   CMinParser ::token_number_type
   CMinParser ::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      17,    19,     2,     2,     7,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     9,    15,
       2,    25,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    11,     2,    13,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    21,     2,    23,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     8,    10,    12,    14,    16,    18,    20,    22,
      24,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
    };
    const unsigned int user_token_number_max_ = 311;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 3 "parser.y" // lalr1.cc:1167
} // parser
#line 1940 "parser.tab.cc" // lalr1.cc:1167
#line 281 "parser.y" // lalr1.cc:1168


void parser::CMinParser::error(const location_type &l, const std::string & error_message)
{
  std::cerr << "Error: " << error_message << " at " << l << "\n";
}
