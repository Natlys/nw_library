#include "nwl_random.h"

#include <nwlib/nwl_time.h>

std::mt19937 NWL::Random::s_RandEngine(time(nullptr));

namespace NW
{
}