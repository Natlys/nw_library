#include <nwl_pch.hpp>
#include "nwl_random.h"

std::mt19937 NWL::Random::s_RandEngine(time(nullptr));

namespace NW
{
}