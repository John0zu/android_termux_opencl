/* 
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */



#include "android_opencl/OclError.h"
#include "android_opencl/OclKernel.h"
#include "android_opencl/OclLib.h"
#include "android_opencl/Log.h"


#include <stdexcept>


aocl::OclKernel::OclKernel(cl_program program, const char *name) :
    m_name(name)
{
    m_kernel = OclLib::createKernel(program, name);
}


aocl::OclKernel::~OclKernel()
{
    OclLib::release(m_kernel);
}


void aocl::OclKernel::enqueueNDRange(cl_command_queue queue, uint32_t work_dim, const size_t *global_work_offset, const size_t *global_work_size, const size_t *local_work_size)
{
    const cl_int ret = OclLib::enqueueNDRangeKernel(queue, m_kernel, work_dim, global_work_offset, global_work_size, local_work_size, 0, nullptr, nullptr);
    if (ret != CL_SUCCESS) {
        LOG_ERR("%s" RED(" error ") RED_BOLD("%s") RED(" when calling ") RED_BOLD("clEnqueueNDRangeKernel") RED(" for kernel ") RED_BOLD("%s"),
                ocl_tag(), OclError::toString(ret), name().data());

        throw std::runtime_error(OclError::toString(ret));
    }
}


void aocl::OclKernel::setArg(uint32_t index, size_t size, const void *value)
{
    const cl_int ret = OclLib::setKernelArg(m_kernel, index, size, value);
    if (ret != CL_SUCCESS) {
        LOG_ERR("%s" RED(" error ") RED_BOLD("%s") RED(" when calling ") RED_BOLD("clSetKernelArg") RED(" for kernel ") RED_BOLD("%s")
                RED(" argument ") RED_BOLD("%u") RED(" size ") RED_BOLD("%zu"),
                ocl_tag(), OclError::toString(ret), name().data(), index, size);

        throw std::runtime_error(OclError::toString(ret));
    }
}
