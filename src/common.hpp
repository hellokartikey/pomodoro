#ifndef HK_POMODORO_COMMON_HPP
#define HK_POMODORO_COMMON_HPP

template <typename To, typename From>
To as(const From& from) {
  return static_cast<To>(from);
}

#endif
