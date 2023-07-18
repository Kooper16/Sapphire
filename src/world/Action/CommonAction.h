#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace Sapphire::World::Action
{
  enum ActionSkill
  {
    // WAR
    SkullSunder = 35,
    Maim = 37,
    StormsPath = 42,
    StormsEye = 45,
    ButchersBlock = 47,

    //BRD
    HeavyShot = 97,
    StraightShot = 98,
    Swiftsong = 105
  };

  enum ActionStatus
  {
    // WAR
    Defiance = 91,
    Unchained = 92,
    Wrath = 93,
    WrathII = 94,
    WrathIII = 95,
    WrathIV = 96,
    Infuriated = 97,
    InnerBeast = 411,
    Deliverance = 729,

    //BRD
    StraightShotReady = 122,
    StraightShotBuff = 130,
    SwiftsongBuff = 133
  };
}