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

#ifndef AOCL_OCLPLATFORM_H
#define AOCL_OCLPLATFORM_H


#include <vector>


#include "android_opencl/OclDevice.h"
#include "android_opencl/String.h"


using cl_platform_id = struct _cl_platform_id *;


namespace aocl {


class OclPlatform
{
public:
    OclPlatform() = default;
    OclPlatform(size_t index, cl_platform_id id) : m_id(id), m_index(index) {}

    static std::vector<OclPlatform> get();
    static void print();

    inline bool isValid() const      { return m_id != nullptr; }
    inline cl_platform_id id() const { return m_id; }
    inline size_t index() const      { return m_index; }

    rapidjson::Value toJSON(rapidjson::Document &doc) const;
    std::vector<OclDevice> devices() const;
    String extensions() const;
    String name() const;
    String profile() const;
    String vendor() const;
    String version() const;

private:
    cl_platform_id m_id = nullptr;
    size_t m_index      = 0;
};


} // namespace aocl


#endif /* AOCL_OCLPLATFORM_H */
