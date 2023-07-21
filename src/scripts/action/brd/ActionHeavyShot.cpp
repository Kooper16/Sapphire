#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <random>

using namespace Sapphire::World::Action;

class ActionHeavyShot : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionHeavyShot() : Sapphire::ScriptAPI::ActionScript( HeavyShot )
  {
  }

  static constexpr auto Potency = 150;

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();

    if( !pSource->isPlayer() )
      return;

    auto dmg = action.calcDamage( Potency );
    action.getActionResultBuilder()->damage( pSource, pTarget, dmg.first, dmg.second );

    if( dmg.first > 0 )
      pTarget->onActionHostile( pSource );

    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<> distr( 1, 100 );

    if( distr( gen ) <= 20 )
    {
      uint32_t duration = 10000;

      //pSource->replaceSingleStatusEffectById( StraightShotReady );
      action.getActionResultBuilder()->applyStatusEffectSelf( StraightShotReady, duration, 0, true );
    }

  }
};

EXPOSE_SCRIPT( ActionHeavyShot );