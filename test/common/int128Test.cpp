// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2024 Second State INC

#include "common/int128.h"
#include "fmt/format.h"

#include <cstdint>
#include <gtest/gtest.h>

namespace {
using namespace std::literals;

TEST(Int128Test, Int128OutputTest) {
  {
    const WasmEdge::uint128_t Value = 0U;
    EXPECT_EQ(fmt::format("{}"sv, WasmEdge::uint128(Value)), "0");
    EXPECT_EQ(fmt::format("{:x}"sv, WasmEdge::uint128(Value)), "0");
    EXPECT_EQ(fmt::format("{:#x}"sv, WasmEdge::uint128(Value)), "0x0");
    EXPECT_EQ(fmt::format("{:b}"sv, WasmEdge::uint128(Value)), "0");
    EXPECT_EQ(fmt::format("{:#b}"sv, WasmEdge::uint128(Value)), "0b0");
    EXPECT_EQ(fmt::format("{:o}"sv, WasmEdge::uint128(Value)), "0");
  }

  {
    const WasmEdge::uint128_t Value = WasmEdge::uint128_t(1U) << 69U;
    EXPECT_EQ(fmt::format("{}"sv, WasmEdge::uint128(Value)),
              "590295810358705651712");
    EXPECT_EQ(fmt::format("{:x}"sv, WasmEdge::uint128(Value)),
              "200000000000000000");
  }

  {
    const WasmEdge::uint128_t Value = WasmEdge::uint128_t(1U) << 127U;
    EXPECT_EQ(fmt::format("{}"sv, WasmEdge::uint128(Value)),
              "170141183460469231731687303715884105728");
    EXPECT_EQ(fmt::format("{:x}"sv, WasmEdge::uint128(Value)),
              "80000000000000000000000000000000");
  }

  {
    const WasmEdge::uint128_t Value = ~WasmEdge::uint128_t(0U);
    EXPECT_EQ(fmt::format("{}"sv, WasmEdge::uint128(Value)),
              "340282366920938463463374607431768211455");
    EXPECT_EQ(fmt::format("{:x}"sv, WasmEdge::uint128(Value)),
              "ffffffffffffffffffffffffffffffff");
    EXPECT_EQ(fmt::format("{:#X}"sv, WasmEdge::uint128(Value)),
              "0XFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
  }

  {
    const WasmEdge::uint128_t P10(10000000000000U);
    const WasmEdge::uint128_t Value =
        WasmEdge::uint128_t(1234567890123U) * P10 * P10 +
        WasmEdge::uint128_t(1234567890123U);
    EXPECT_EQ(fmt::format("{}"sv, WasmEdge::uint128(Value)),
              "123456789012300000000000001234567890123");
    EXPECT_EQ(fmt::format("{:x}"sv, WasmEdge::uint128(Value)),
              "5ce0e9a55ff035e3783f03ea3dfb04cb");
    EXPECT_EQ(
        fmt::format("{:b}"sv, WasmEdge::uint128(Value)),
        "1011100111000001110100110100101010111111111000000110101111000110111100"
        "000111111000000111110101000111101111110110000010011001011");
  }

  {
    const WasmEdge::uint128_t P10(10000000000000U);
    const WasmEdge::uint128_t Value =
        WasmEdge::uint128_t(1234567890123U) * P10 * P10;
    EXPECT_EQ(fmt::format("{}"sv, WasmEdge::uint128(Value)),
              "123456789012300000000000000000000000000");
    EXPECT_EQ(fmt::format("{:o}"sv, WasmEdge::uint128(Value)),
              "1347016464527770065706740770054531400000000");
  }

  {
    const WasmEdge::uint128_t P10(10000000000000U);
    const WasmEdge::uint128_t Value =
        WasmEdge::uint128_t(1234567890123U) * P10 * P10 +
        WasmEdge::uint128_t(1234567890123U) * P10;
    EXPECT_EQ(fmt::format("{}"sv, WasmEdge::uint128(Value)),
              "123456789012312345678901230000000000000");
  }

  {
    auto Convert = [](WasmEdge::uint128_t V) -> fmt::detail::uint128_t {
      return (fmt::detail::uint128_t(static_cast<uint64_t>(V >> 64U)) << 64U) |
             fmt::detail::uint128_t(static_cast<uint64_t>(V));
    };
    std::string S0 = "1"s;
    std::string S9;
    WasmEdge::uint128_t X(1U);
    for (unsigned int I = 1U; I <= 38U; ++I) {
      X *= 10U;
      const auto Y = X - WasmEdge::uint128_t(1U);
      EXPECT_EQ(fmt::detail::count_digits(Convert(Y - WasmEdge::uint128_t(1U))),
                I);
      EXPECT_EQ(fmt::detail::count_digits(Convert(Y)), I);
      EXPECT_EQ(fmt::detail::count_digits(Convert(X)), I + 1);
      EXPECT_EQ(fmt::detail::count_digits(Convert(X + WasmEdge::uint128_t(1U))),
                I + 1);
      S0 += '0';
      S9 += '9';
      EXPECT_EQ(fmt::format("{}"sv, WasmEdge::uint128(X)), S0);
      EXPECT_EQ(fmt::format("{}"sv, WasmEdge::uint128(Y)), S9);
    }
  }
}
} // namespace
