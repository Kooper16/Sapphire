#include "Warrior.h"

#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <Actor/Player.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

void Warrior::onAction( Entity::Player& player, Action& action )
{
  switch( action.getId() )
  {
    case Maim:
    case StormsEye:
    case StormsPath:
    case SkullSunder:
    case ButchersBlock:
    {
      if( action.isComboAction() && !action.isCorrectCombo() )
        break;

      if( player.hasStatusEffect( Defiance ) )
        handleWrath( player, action );
      break;
    }
  }
}

void Warrior::handleWrath( Entity::Player& player, Action& action )
{
  auto effectToApply = Wrath;
  auto parry = 2;
  auto asChara = player.getAsChara();
  int8_t slotId = -1;

  if( player.hasStatusEffect( Wrath ) )
  {
    slotId = player.getStatusEffectSlotWithId( Wrath );
    effectToApply = WrathII;
    parry += 2;
  }
  else if( player.hasStatusEffect( WrathII ) )
  {
    slotId = player.getStatusEffectSlotWithId( WrathII );
    effectToApply = WrathIII;
    parry += 4;
  }
  else if( player.hasStatusEffect( WrathIII ) )
  {
    slotId = player.getStatusEffectSlotWithId( WrathIII );
    effectToApply = WrathIV;
    parry += 6;
  }
  else if( player.hasStatusEffect( WrathIV ) )
  {
    slotId = player.getStatusEffectSlotWithId( WrathIV );
    effectToApply = Infuriated;
    parry += 8;
  }
  else if( player.hasStatusEffect( Infuriated ) )
  {
    slotId = player.getStatusEffectSlotWithId( Infuriated );
    effectToApply = Infuriated;
    parry += 8;
  }

  action.getActionResultBuilder()->applyStatusEffectSelf( effectToApply, 30000, 0, { StatusModifier{ Common::ParamModifier::ParryPercent, parry } }, 0, slotId );
}