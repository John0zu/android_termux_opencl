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

#ifndef AOCL_OCLERROR_H
#define AOCL_OCLERROR_H


#include "android_opencl/cl.h"


#define OCL_ERR_SUCCESS    (0)
#define OCL_ERR_API        (2)
#define OCL_ERR_BAD_PARAMS (1)


namespace aocl {


class OclError
{
public:
    static const char *toString(cl_int ret);
};


} // namespace aocl


#endif /* AOCL_OCLERROR_H */
