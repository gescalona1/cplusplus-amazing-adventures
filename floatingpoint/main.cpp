#include <bit>
#include <bitset>
#include <iostream>
#include <ranges>
#include <type_traits>

#define FLOAT_SIZE 32 // size of float in C++ is 32 bits
#define BIAS 127

constexpr std::array<unsigned int, 3> find_sizes() {
  const unsigned int dtype_size = 8 * sizeof(float);
  const unsigned int exponent_size = [&](void) -> unsigned int { return 8; }();
  const unsigned int mantissa_size = dtype_size - exponent_size - 1;
  return {dtype_size, exponent_size, mantissa_size};
}

constexpr std::string get_binary_extension(const float f,
                                           const unsigned int dtype_size,
                                           const unsigned int exponent_size,
                                           const unsigned int mantissa_size) {
  const unsigned int bits = std::bit_cast<unsigned int>(f);

  const unsigned int sign = bits >> (dtype_size - 1);
  const unsigned int exponent =
      (bits >> (dtype_size - exponent_size - 1)) & ((1 << exponent_size) - 1);
  const unsigned int mantissa = bits & ((1 << mantissa_size) - 1);
  const auto bitset_mantissa = std::bitset<128>(mantissa);

  return std::format("(-1)^{} * 1.{} * 2^{}", sign, bitset_mantissa.to_string(),
                     ((int)exponent) - BIAS);
}

int main(int argc, char *argv[]) {
  int N;
  float f;
  std::cin >> N;

  std::ranges::for_each(std::views::iota(0, N), [&](int) {
    std::cin >> f;
    auto [dtype_size, exponent_size, mantissa_size] = find_sizes();
    auto binary_extension =
        get_binary_extension(f, dtype_size, exponent_size, mantissa_size);
    std::cout << binary_extension << '\n';
  });
  return 0;
}
