#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <StatusEffect/StatusEffect.h>
#include <random>

using namespace Sapphire::World::Action;

class ActionStraightShot : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionStraightShot() : Sapphire::ScriptAPI::ActionScript( StraightShot )
  {
  }

  static constexpr auto Potency = 140;

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();

    if( !pSource->isPlayer() )
      return;

    if( auto status = pSource->getStatusEffectById( StraightShotReady ); status )
      status->setModifier( Sapphire::Common::ParamModifier::CriticalHitPercent, 100 );

    auto dmg = action.calcDamage( Potency );
    pSource->removeSingleStatusEffectById( StraightShotReady );
    action.getActionResultBuilder()->damage( pSource, pTarget, dmg.first, dmg.second );

    if( dmg.first > 0 )
      pTarget->onActionHostile( pSource );


    uint32_t duration = 20000;
    pSource->replaceSingleStatusEffectById( StraightShotBuff );
    action.getActionResultBuilder()->applyStatusEffectSelf( StraightShotBuff, duration, 0, { Sapphire::World::Action::StatusModifier{ Sapphire::Common::ParamModifier::CriticalHitPercent, 10 } }, 0, false );
  }
};

EXPOSE_SCRIPT( ActionStraightShot );