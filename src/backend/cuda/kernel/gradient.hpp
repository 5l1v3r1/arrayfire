/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#pragma once

#include <Param.hpp>
#include <common/dispatch.hpp>
#include <debug_cuda.hpp>
#include <nvrtc/cache.hpp>
#include <nvrtc_kernel_headers/gradient_cuh.hpp>

#include <string>

namespace cuda {
namespace kernel {

template<typename T>
void gradient(Param<T> grad0, Param<T> grad1, CParam<T> in) {
    constexpr unsigned TX = 32;
    constexpr unsigned TY = 8;

    static const std::string source(gradient_cuh, gradient_cuh_len);

    auto gradient = getKernel("cuda::gradient", source, {TemplateTypename<T>()},
                              {DefineValue(TX), DefineValue(TY)});

    dim3 threads(TX, TY, 1);

    int blocksPerMatX = divup(in.dims[0], TX);
    int blocksPerMatY = divup(in.dims[1], TY);
    dim3 blocks(blocksPerMatX * in.dims[2], blocksPerMatY * in.dims[3], 1);

    const int maxBlocksY =
        cuda::getDeviceProp(cuda::getActiveDeviceId()).maxGridSize[1];
    blocks.z = divup(blocks.y, maxBlocksY);
    blocks.y = divup(blocks.y, blocks.z);

    EnqueueArgs qArgs(blocks, threads, getActiveStream());

    gradient(qArgs, grad0, grad1, in, blocksPerMatX, blocksPerMatY);
    POST_LAUNCH_CHECK();
}

}  // namespace kernel
}  // namespace cuda
