#ifndef LIB_INCLUDE_TICK_ARRAY_PROMOTE_H_
#define LIB_INCLUDE_TICK_ARRAY_PROMOTE_H_

// License: BSD 3 clause

/**
 * @file This file provides the promote<T> type trait class that for floating
 * point and unsigned/signed integer types provides a type that will safely
 * contain a reasonably sized sum of type values.
 */

namespace tick {

template <typename T>
struct promote {
  using type = T;
};

template <>
struct promote<float> {
  using type = double;
};


template <>
struct promote<half_float::half> {
  using type = double;
};

template <>
struct promote<std::uint8_t> {
  using type = std::uint64_t;
};
template <>
struct promote<std::uint16_t> {
  using type = std::uint64_t;
};
template <>
struct promote<std::uint32_t> {
  using type = std::uint64_t;
};

template <>
struct promote<std::int8_t> {
  using type = std::int64_t;
};
template <>
struct promote<std::int16_t> {
  using type = std::int64_t;
};
template <>
struct promote<std::int32_t> {
  using type = std::int64_t;
};

template <typename T>
using promote_t = typename promote<T>::type;

}  // namespace tick

//inline void operator+=(double& d, HalfFloat f){
//  d = d + f.GetBits();
//}

#endif  // LIB_INCLUDE_TICK_ARRAY_PROMOTE_H_
