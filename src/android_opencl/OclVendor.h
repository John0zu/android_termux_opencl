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

#ifndef AOCL_OCLVENDOR_H
#define AOCL_OCLVENDOR_H


namespace aocl {


enum OclVendor : unsigned {
    OCL_VENDOR_UNKNOWN,
    OCL_VENDOR_AMD,
    OCL_VENDOR_NVIDIA,
    OCL_VENDOR_INTEL,
    OCL_VENDOR_APPLE,
    OCL_VENDOR_QUALCOMM,
};


} // namespace aocl


#endif /* AOCL_OCLVENDOR_H */
