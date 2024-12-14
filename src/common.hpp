#ifndef HK_POMODORO_COMMON_HPP
#define HK_POMODORO_COMMON_HPP

template <typename To, typename From>
auto as(const From& from) {
  return static_cast<To>(from);
}

template <typename To, typename FromR, typename FromP>
requires requires(To value) {
  { std::chrono::duration{value} } -> std::same_as<To>;
}
auto as(const std::chrono::duration<FromR, FromP>& from) {
  return std::chrono::duration_cast<To>(from);
}

#endif
