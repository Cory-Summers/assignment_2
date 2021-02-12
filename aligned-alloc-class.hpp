#ifndef ALIGNED_ALLOC_HPP
#define ALIGNED_ALLOC_HPP
#include <memory>
#ifdef _WIN32
#include <windows.h>
#else 
#include <cstdlib>
#endif//__WIN32
template<class T, std::size_t alignment = 1024ull>
class AlignedAllocator
{
  public:
    using value_type = T; 
    //Depricated in c++17
    using pointer =  T *;
    using const_pointer = const pointer;
    using void_pointer  = void *;
    using size_type     = std::size_t;
    using difference_type = std::ptrdiff_t;
  public:
    AlignedAllocator() noexcept;
    constexpr
    pointer allocate(size_type n, size_type align_to = alignment)
    {
      return _AllocFunction(n * sizeof(value_type), align_to);
    }
    //n required due to container requirements
    constexpr
    void deallocate(pointer p, size_type n) noexcept
    {
      free(p);
    }
    constexpr
    void destroy(pointer p)
    {
      std::destroy(p);
    }

    
  private:
  //Do system dependence
    inline constexpr
    pointer _AllocFunction(size_type size, size_type align)
    {
      return (pointer)
      #ifdef _WIN32
        _aligned_malloc(size, align)
      #else
        std::aligned_alloc(align, size);
      #endif//__WIN32
      ;
    }
    inline constexpr
    void _FreeFunction(pointer p)
    {
      #ifdef _WIN32
        _aligned_free(p);
      #else
        free(p);
      #endif//__WIN32
    }
};


#endif//ALIGNED_ALLOC_HPP