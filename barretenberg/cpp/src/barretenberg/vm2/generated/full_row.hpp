// AUTOGENERATED FILE
#pragma once

#include <sstream>
#include <string>
#include <vector>

#include "barretenberg/common/ref_vector.hpp"
#include "columns.hpp"

namespace bb::avm2 {

template <typename FF_> struct AvmFullRow {
    using FF = FF_;

    FF AVM2_ALL_ENTITIES;

    RefVector<const FF> as_vector() const;
    static std::vector<std::string> names();
    static constexpr size_t SIZE = 48;

    // Risky but oh so efficient.
    FF& get_column(ColumnAndShifts col)
    {
        static_assert(sizeof(*this) == sizeof(FF) * static_cast<size_t>(ColumnAndShifts::NUM_COLUMNS));
        return reinterpret_cast<FF*>(this)[static_cast<size_t>(col)];
    }

    const FF& get_column(ColumnAndShifts col) const
    {
        static_assert(sizeof(*this) == sizeof(FF) * static_cast<size_t>(ColumnAndShifts::NUM_COLUMNS));
        return reinterpret_cast<const FF*>(this)[static_cast<size_t>(col)];
    }
};

template <typename FF> std::ostream& operator<<(std::ostream& os, AvmFullRow<FF> const& row);

} // namespace bb::avm2

namespace bb {

// Expose this in the bb namespace. For compatibility with the old witgen.
using avm2::AvmFullRow;

} // namespace bb