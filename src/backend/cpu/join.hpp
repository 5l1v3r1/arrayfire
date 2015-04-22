/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <af/array.h>
#include <Array.hpp>

namespace cpu
{
    template<typename Tx, typename Ty>
    Array<Tx> join(const int dim, const Array<Tx> &first, const Array<Ty> &second);

    template<typename T>
    Array<T> join(const int dim, const Array<T> &first, const Array<T> &second,
                  const Array<T> &third);

    template<typename T>
    Array<T> join(const int dim, const Array<T> &first, const Array<T> &second,
                  const Array<T> &third, const Array<T> &fourth);
}
