// AUTOGENERATED FILE
#pragma once

#include "barretenberg/relations/relation_parameters.hpp"
#include "barretenberg/relations/relation_types.hpp"

namespace bb::avm2 {

template <typename FF_> class aluImpl {
  public:
    using FF = FF_;

    static constexpr std::array<size_t, 2> SUBRELATION_PARTIAL_LENGTHS = { 3, 2 };

    template <typename ContainerOverSubrelations, typename AllEntities>
    void static accumulate(ContainerOverSubrelations& evals,
                           const AllEntities& new_term,
                           [[maybe_unused]] const RelationParameters<FF>&,
                           [[maybe_unused]] const FF& scaling_factor)
    {

        {
            using Accumulator = typename std::tuple_element_t<0, ContainerOverSubrelations>;
            auto tmp = (new_term.alu_sel_op_add * (FF(1) - new_term.alu_sel_op_add));
            tmp *= scaling_factor;
            std::get<0>(evals) += typename Accumulator::View(tmp);
        }
        {
            using Accumulator = typename std::tuple_element_t<1, ContainerOverSubrelations>;
            auto tmp = ((new_term.alu_ia + new_term.alu_ib) - new_term.alu_ic);
            tmp *= scaling_factor;
            std::get<1>(evals) += typename Accumulator::View(tmp);
        }
    }
};

template <typename FF> class alu : public Relation<aluImpl<FF>> {
  public:
    static constexpr const char* NAME = "alu";

    static std::string get_subrelation_label(size_t index)
    {
        switch (index) {
        case 0:
            return "SEL_ADD_BINARY";
        case 1:
            return "ALU_ADD";
        }
        return std::to_string(index);
    }

    // Subrelation indices constants, to be used in tests.
    static constexpr size_t SR_SEL_ADD_BINARY = 0;
    static constexpr size_t SR_ALU_ADD = 1;
};

} // namespace bb::avm2