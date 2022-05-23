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

#ifdef WIN32
#   include <winsock2.h>
#   include <windows.h>
#endif


#include <algorithm>
#include <cassert>
#include <cstring>
#include <ctime>
#include <mutex>
#include <string>
#include <uv.h>
#include <vector>

#include "android_opencl/Chrono.h"
#include "android_opencl/Log.h"



namespace aocl {


static const char *colors_map[] = {
    RED_BOLD_S,    // EMERG
    RED_BOLD_S,    // ALERT
    RED_BOLD_S,    // CRIT
    RED_S,         // ERR
    YELLOW_S,      // WARNING
    WHITE_BOLD_S,  // NOTICE
    nullptr,       // INFO
#   ifdef WIN32
    BLACK_BOLD_S   // DEBUG
#   else
    BRIGHT_BLACK_S // DEBUG
#   endif
};



uint32_t Log::m_verbose     = 0;

void aocl::Log::destroy()
{

}



static char m_buf[Log::kMaxBufferSize]{};
static std::mutex m_mutex;
static inline void endl(size_t &size)
    {
#       ifdef _WIN32
        memcpy(m_buf + size, CLEAR "\r\n", 7);
        size += 6;
#       else
        memcpy(m_buf + size, CLEAR "\n", 6);
        size += 5;
#       endif
}
static inline uint64_t timestamp(Log::Level level, size_t &size, size_t &offset)
    {
        const uint64_t ms = Chrono::currentMSecsSinceEpoch();

        if (level == Log::NONE) {
            return ms;
        }

        time_t now = ms / 1000;
        tm stime{};

#       ifdef _WIN32
        localtime_s(&stime, &now);
#       else
        localtime_r(&now, &stime);
#       endif

        const int rc = snprintf(m_buf, sizeof(m_buf) - 1, "[%d-%02d-%02d %02d:%02d:%02d" BLACK_BOLD(".%03d") "] ",
                                stime.tm_year + 1900,
                                stime.tm_mon + 1,
                                stime.tm_mday,
                                stime.tm_hour,
                                stime.tm_min,
                                stime.tm_sec,
                                static_cast<int>(ms % 1000)
                                );

        if (rc > 0) {
            size = offset = static_cast<size_t>(rc);
        }

        return ms;
    }
void aocl::Log::print(const char *fmt, ...)
{
	va_list args{};
    va_start(args, fmt);

    aocl::Log::print(NONE, fmt, args);

    va_end(args);
}


void aocl::Log::print(Level level, const char *fmt, ...)
{
	if(level > m_verbose)
	{
		return;
	}
	size_t size   = 0;
	size_t offset = 0;
	va_list args{};
    va_start(args, fmt);
	
	std::lock_guard<std::mutex> lock(m_mutex);
	const uint64_t ts = timestamp(level, size, offset);
	//color(level, size);

	const int rc = vsnprintf(m_buf + size, sizeof (m_buf) - offset - 32, fmt, args);
	if (rc < 0) {
		return;
	}

	size += std::min(static_cast<size_t>(rc), sizeof (m_buf) - offset - 32);
	endl(size);


	fputs(m_buf,stdout);

	va_end(args);
}
};