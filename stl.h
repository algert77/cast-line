#ifndef STL_H
#define STL_H

template<class InputIterator, class Function>
  Function for_each1(InputIterator first, InputIterator last, Function fn)
{
  while (first!=last) {
    fn (first);
    ++first;
  }
  return fn;      // or, since C++11: return move(fn);
}


template<class InputIterator, class Function>
Function for_each2(InputIterator first, InputIterator last, int index, Function fn)
{
  while (first!=last) {
    fn ( first , index);
    ++first;
  }
  return fn;      // or, since C++11: return move(fn);
}


template<class InputIterator, class UnaryPredicate>
InputIterator find_if2 (InputIterator first, InputIterator last, int index  ,UnaryPredicate pred)
{
  while (first!=last) {
    if (pred(first, index)) return first;
    ++first;
  }
  return last;
}


#endif 
