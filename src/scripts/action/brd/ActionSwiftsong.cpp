#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <random>

using namespace Sapphire::World::Action;

class ActionSwiftsong : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionSwiftsong() : Sapphire::ScriptAPI::ActionScript( Swiftsong )
  {
  }

  static constexpr auto Potency = 150;

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();

    if( !pSource->isPlayer() )
      return;

    pSource->replaceSingleStatusEffectById( SwiftsongBuff );
    action.getActionResultBuilder()->applyStatusEffectSelf( SwiftsongBuff, 10000, 0, {}, 0, static_cast< uint32_t >(Sapphire::Common::StatusEffectFlag::Permanent) );

  }
};

EXPOSE_SCRIPT( ActionSwiftsong );