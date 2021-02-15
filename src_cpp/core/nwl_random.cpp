#include <nwl_pch.hpp>
#include "nwl_random.h"

std::mt19937 NWL::Random::s_RandEngine(static_cast<unsigned int>(time(nullptr)));

namespace NW
{
}