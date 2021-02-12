#ifndef GET_OPT_CLASS_HPP
#define GET_OPT_CLASS_HPP
#include <memory>
#include <optional>
#include <string>
#include <stdexcept>
#include <vector>
template<
  typename CharT,
  typename Traits = std::char_traits<CharT>,
  typename Allocator = std::allocator<CharT>
>
class GetOpt
{
public:
  using allocator_type  = Allocator;
  using value_type      = CharT;
  using traits_type     = Traits;
  using size_type       = typename std::allocator_traits<Allocator>::size_type;
  using difference_type = typename std::allocator_traits<Allocator>::difference_type;
  using string_type     = std::basic_string<value_type, traits_type, allocator_type>;
  struct Opt
  {
    Opt() : value(-1), arg() {}
    Opt(std::size_t const& v) : value(v), arg() {}
    Opt(std::size_t const & v, std::string const& s) : value(v), arg(s) {}
    Opt( const std::size_t v, std::string const& s) : value(v), arg(s) {}
    Opt(std::string const& s) : value(0), arg(s) {}
    std::size_t value;
    std::string arg;
    operator char() { return static_cast<char>(value); } 
  };
  
  typedef typename std::vector<Opt, allocator_type>::iterator iterator;
private:
  typedef typename std::vector<string_type, allocator_type> in_vector_type;
  using string_cref     = string_type const&;
  using opt_vector_type = std::vector<Opt, allocator_type>;
public:
  GetOpt() {}
  GetOpt(int const&, value_type **);
  GetOpt(
    int const&, 
    value_type**, 
    string_cref const&
  );
  typename iterator Parse();
  typename iterator begin() { return m_output.begin(); }
  typename iterator end()   { return m_output.end(); }
  typename iterator operator() (int const&, value_type**, string_cref const&);
  void SetArguments(int const&, value_type**);
  void SetOptions(string_cref const& opt_string);
private:
  void PushBadArgument(string_cref, std::size_t code = std::size_t('?'));
  void ParseParameter(typename in_vector_type::iterator & it);
  in_vector_type  m_input;
  string_type     m_opt_string;
  opt_vector_type m_output;
};

template<typename CharT, typename Traits, typename Allocator>
inline GetOpt<CharT, Traits, Allocator>::GetOpt(int const& argc, value_type** argv)
  : m_input()
  , m_opt_string()
{

}

template<typename CharT, typename Traits, typename Allocator>
inline GetOpt<CharT, Traits, Allocator>::GetOpt(
  int const& argc, 
  value_type** argv, 
  string_cref const& opt_string)
  : m_opt_string(opt_string)
  , m_input({ argv + 1, argv + argc })
{
  Parse();
}
/*Based on https://www.tuhs.org/Usenet/mod.std.unix/1985-November/000057.html by John Quarterman */
template<typename CharT, typename Traits, typename Allocator>
inline typename GetOpt<CharT, Traits, Allocator>::iterator GetOpt<CharT, Traits, Allocator>::Parse()
{
  std::vector<Opt> parameters;
  for(auto iter = m_input.begin(); iter < m_input.end(); ++iter)
  {
      //Parameter                        vvvvvvvvvvv
      if ((*iter)[0] != '-') // ie ./c-  test-file.c -o 
        parameters.emplace_back(*iter);
      else if ((*iter)[1] == '\0' )
      {
        throw std::logic_error("Missing Argument Type");
      }
      // else if((*iter)[1] == ':')
      // {
      //   throw std::logic_error("")
      // }
      else
        ParseParameter(iter);
  }
  //Attempting to assure a single new allocation
  m_output.reserve(parameters.size());
  m_output.insert(std::end(m_output), std::begin(parameters), std::end(parameters));
  return m_output.begin();
}

template<typename CharT, typename Traits, typename Allocator>
inline void GetOpt<CharT, Traits, Allocator>::SetArguments(int const& argc, value_type** argv)
{
  m_input = in_vector_type(argc);
  for (int i = 0; i < argc; ++i)
    m_input.emplace_back(argv[i]);
}

template<typename CharT, typename Traits, typename Allocator>
inline void GetOpt<CharT, Traits, Allocator>::SetOptions(string_cref const& opt_string)
{
  m_opt_string = opt_string;
}

template<typename CharT, typename Traits, typename Allocator>
inline void GetOpt<CharT, Traits, Allocator>::ParseParameter(typename in_vector_type::iterator & it)
{
  Opt opt;
  int optional_flag = false;
  auto opt_id = m_opt_string.find((*it)[1]);
  if (opt_id == string_type::npos)
  {
    PushBadArgument(*it);
    throw std::logic_error(std::string("Bad Argument ") + (*it));
  }
  opt.value = static_cast<std::size_t>((*it)[1]);
  if (m_opt_string[opt_id + 1] == ':')
  {
    
    if (m_opt_string[opt_id + 2] == ':')
    {
      optional_flag == true;
    }
    if ((it + 1) == m_input.back() || (*(it + 1))[0] == '-' && optional_flag != true)
    {
      PushBadArgument(*it, std::size_t(':'));
      throw std::logic_error(std::string("Missing Argument ") + (*it));
    }
    else {
      opt.arg = *(++it);
    }
  }
  m_output.push_back(opt);
}


template<typename CharT, typename Traits, typename Allocator>
inline void GetOpt<CharT, Traits, Allocator>::PushBadArgument(string_cref str, std::size_t code)
{
  m_output.emplace_back(Opt::kBadOpt, code, str);
}

#endif GET_OPT_CLASS_HPP