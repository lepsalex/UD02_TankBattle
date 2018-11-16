// © Alexandru Lepsa 2018

using UnrealBuildTool;
using System.Collections.Generic;

public class TankBattleTarget : TargetRules
{
	public TankBattleTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "TankBattle" } );
	}
}
