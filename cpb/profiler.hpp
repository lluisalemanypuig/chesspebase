#pragma once

#if defined USE_INSTRUMENTATION

#include <profiler/profiler.hpp>

#else

#define PROFILER_START_SESSION(filename, id)
#define PROFILER_END_SESSION()

#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION

#define PROFILE_PARALLEL_SCOPE(name, N)
#define PROFILE_PARALLEL_FUNCTION(N)

#endif
