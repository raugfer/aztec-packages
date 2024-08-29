// AUTOGENERATED FILE
#pragma once

#include "barretenberg/relations/relation_parameters.hpp"
#include "barretenberg/relations/relation_types.hpp"

namespace bb::Avm_vm {

template <typename FF_> class range_checkImpl {
  public:
    using FF = FF_;

    static constexpr std::array<size_t, 20> SUBRELATION_PARTIAL_LENGTHS = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 2,
                                                                            4, 2, 3, 2, 2, 2, 2, 2, 2, 2 };

    template <typename ContainerOverSubrelations, typename AllEntities>
    void static accumulate(ContainerOverSubrelations& evals,
                           const AllEntities& new_term,
                           [[maybe_unused]] const RelationParameters<FF>&,
                           [[maybe_unused]] const FF& scaling_factor)
    {
        const auto range_check_X_0 = (new_term.range_check_is_lte_u16 * new_term.range_check_u16_r7);
        const auto range_check_X_1 = (new_term.range_check_is_lte_u32 *
                                      (new_term.range_check_u16_r0 + (new_term.range_check_u16_r7 * FF(65536))));
        const auto range_check_X_2 = (new_term.range_check_is_lte_u48 *
                                      ((new_term.range_check_u16_r0 + (new_term.range_check_u16_r1 * FF(65536))) +
                                       (new_term.range_check_u16_r7 * FF(4294967296UL))));
        const auto range_check_X_3 = (new_term.range_check_is_lte_u64 *
                                      (((new_term.range_check_u16_r0 + (new_term.range_check_u16_r1 * FF(65536))) +
                                        (new_term.range_check_u16_r2 * FF(4294967296UL))) +
                                       (new_term.range_check_u16_r7 * FF(281474976710656UL))));
        const auto range_check_X_4 = (new_term.range_check_is_lte_u80 *
                                      ((((new_term.range_check_u16_r0 + (new_term.range_check_u16_r1 * FF(65536))) +
                                         (new_term.range_check_u16_r2 * FF(4294967296UL))) +
                                        (new_term.range_check_u16_r3 * FF(281474976710656UL))) +
                                       (new_term.range_check_u16_r7 * FF(uint256_t{ 0UL, 1UL, 0UL, 0UL }))));
        const auto range_check_X_5 = (new_term.range_check_is_lte_u96 *
                                      (((((new_term.range_check_u16_r0 + (new_term.range_check_u16_r1 * FF(65536))) +
                                          (new_term.range_check_u16_r2 * FF(4294967296UL))) +
                                         (new_term.range_check_u16_r3 * FF(281474976710656UL))) +
                                        (new_term.range_check_u16_r4 * FF(uint256_t{ 0UL, 1UL, 0UL, 0UL }))) +
                                       (new_term.range_check_u16_r7 * FF(uint256_t{ 0UL, 65536UL, 0UL, 0UL }))));
        const auto range_check_X_6 = (new_term.range_check_is_lte_u112 *
                                      ((((((new_term.range_check_u16_r0 + (new_term.range_check_u16_r1 * FF(65536))) +
                                           (new_term.range_check_u16_r2 * FF(4294967296UL))) +
                                          (new_term.range_check_u16_r3 * FF(281474976710656UL))) +
                                         (new_term.range_check_u16_r4 * FF(uint256_t{ 0UL, 1UL, 0UL, 0UL }))) +
                                        (new_term.range_check_u16_r5 * FF(uint256_t{ 0UL, 65536UL, 0UL, 0UL }))) +
                                       (new_term.range_check_u16_r7 * FF(uint256_t{ 0UL, 4294967296UL, 0UL, 0UL }))));
        const auto range_check_X_7 =
            (new_term.range_check_is_lte_u128 *
             (((((((new_term.range_check_u16_r0 + (new_term.range_check_u16_r1 * FF(65536))) +
                   (new_term.range_check_u16_r2 * FF(4294967296UL))) +
                  (new_term.range_check_u16_r3 * FF(281474976710656UL))) +
                 (new_term.range_check_u16_r4 * FF(uint256_t{ 0UL, 1UL, 0UL, 0UL }))) +
                (new_term.range_check_u16_r5 * FF(uint256_t{ 0UL, 65536UL, 0UL, 0UL }))) +
               (new_term.range_check_u16_r6 * FF(uint256_t{ 0UL, 4294967296UL, 0UL, 0UL }))) +
              (new_term.range_check_u16_r7 * FF(uint256_t{ 0UL, 281474976710656UL, 0UL, 0UL }))));
        const auto range_check_RESULT =
            (((((((range_check_X_0 + range_check_X_1) + range_check_X_2) + range_check_X_3) + range_check_X_4) +
               range_check_X_5) +
              range_check_X_6) +
             range_check_X_7);

        {
            using Accumulator = typename std::tuple_element_t<0, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_sel_rng_chk * (FF(1) - new_term.range_check_sel_rng_chk));
            tmp *= scaling_factor;
            std::get<0>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<1, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_is_lte_u16 * (FF(1) - new_term.range_check_is_lte_u16));
            tmp *= scaling_factor;
            std::get<1>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<2, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_is_lte_u32 * (FF(1) - new_term.range_check_is_lte_u32));
            tmp *= scaling_factor;
            std::get<2>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<3, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_is_lte_u48 * (FF(1) - new_term.range_check_is_lte_u48));
            tmp *= scaling_factor;
            std::get<3>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<4, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_is_lte_u64 * (FF(1) - new_term.range_check_is_lte_u64));
            tmp *= scaling_factor;
            std::get<4>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<5, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_is_lte_u80 * (FF(1) - new_term.range_check_is_lte_u80));
            tmp *= scaling_factor;
            std::get<5>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<6, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_is_lte_u96 * (FF(1) - new_term.range_check_is_lte_u96));
            tmp *= scaling_factor;
            std::get<6>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<7, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_is_lte_u112 * (FF(1) - new_term.range_check_is_lte_u112));
            tmp *= scaling_factor;
            std::get<7>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<8, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_is_lte_u128 * (FF(1) - new_term.range_check_is_lte_u128));
            tmp *= scaling_factor;
            std::get<8>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<9, ContainerOverSubrelations>;
            auto tmp = ((((((((new_term.range_check_is_lte_u16 + new_term.range_check_is_lte_u32) +
                              new_term.range_check_is_lte_u48) +
                             new_term.range_check_is_lte_u64) +
                            new_term.range_check_is_lte_u80) +
                           new_term.range_check_is_lte_u96) +
                          new_term.range_check_is_lte_u112) +
                         new_term.range_check_is_lte_u128) -
                        new_term.range_check_sel_rng_chk);
            tmp *= scaling_factor;
            std::get<9>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<10, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_sel_rng_chk * (range_check_RESULT - new_term.range_check_value));
            tmp *= scaling_factor;
            std::get<10>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<11, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_dyn_rng_chk_bits -
                        (((((((new_term.range_check_rng_chk_bits - (new_term.range_check_is_lte_u32 * FF(16))) -
                              (new_term.range_check_is_lte_u48 * FF(32))) -
                             (new_term.range_check_is_lte_u64 * FF(48))) -
                            (new_term.range_check_is_lte_u80 * FF(64))) -
                           (new_term.range_check_is_lte_u96 * FF(80))) -
                          (new_term.range_check_is_lte_u112 * FF(96))) -
                         (new_term.range_check_is_lte_u128 * FF(112))));
            tmp *= scaling_factor;
            std::get<11>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<12, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_sel_rng_chk *
                        (new_term.range_check_dyn_diff -
                         ((new_term.range_check_dyn_rng_chk_pow_2 - new_term.range_check_u16_r7) - FF(1))));
            tmp *= scaling_factor;
            std::get<12>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<13, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_sel_lookup_0 -
                        ((((((new_term.range_check_is_lte_u32 + new_term.range_check_is_lte_u48) +
                             new_term.range_check_is_lte_u64) +
                            new_term.range_check_is_lte_u80) +
                           new_term.range_check_is_lte_u96) +
                          new_term.range_check_is_lte_u112) +
                         new_term.range_check_is_lte_u128));
            tmp *= scaling_factor;
            std::get<13>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<14, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_sel_lookup_1 -
                        (((((new_term.range_check_is_lte_u48 + new_term.range_check_is_lte_u64) +
                            new_term.range_check_is_lte_u80) +
                           new_term.range_check_is_lte_u96) +
                          new_term.range_check_is_lte_u112) +
                         new_term.range_check_is_lte_u128));
            tmp *= scaling_factor;
            std::get<14>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<15, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_sel_lookup_2 -
                        ((((new_term.range_check_is_lte_u64 + new_term.range_check_is_lte_u80) +
                           new_term.range_check_is_lte_u96) +
                          new_term.range_check_is_lte_u112) +
                         new_term.range_check_is_lte_u128));
            tmp *= scaling_factor;
            std::get<15>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<16, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_sel_lookup_3 -
                        (((new_term.range_check_is_lte_u80 + new_term.range_check_is_lte_u96) +
                          new_term.range_check_is_lte_u112) +
                         new_term.range_check_is_lte_u128));
            tmp *= scaling_factor;
            std::get<16>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<17, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_sel_lookup_4 -
                        ((new_term.range_check_is_lte_u96 + new_term.range_check_is_lte_u112) +
                         new_term.range_check_is_lte_u128));
            tmp *= scaling_factor;
            std::get<17>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<18, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_sel_lookup_5 -
                        (new_term.range_check_is_lte_u112 + new_term.range_check_is_lte_u128));
            tmp *= scaling_factor;
            std::get<18>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<19, ContainerOverSubrelations>;
            auto tmp = (new_term.range_check_sel_lookup_6 - new_term.range_check_is_lte_u128);
            tmp *= scaling_factor;
            std::get<19>(evals) += typename Accumulator::View(tmp);
        }
    }
};

template <typename FF> class range_check : public Relation<range_checkImpl<FF>> {
  public:
    static constexpr const char* NAME = "range_check";

    static std::string get_subrelation_label(size_t index)
    {
        switch (index) {
        case 10:
            return "CHECK_RECOMPOSITION";
        }
        return std::to_string(index);
    }
};

} // namespace bb::Avm_vm