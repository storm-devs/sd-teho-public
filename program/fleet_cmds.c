/* на будущее ! не стирать! ugeen
В режиме 'море'
- 5: ядра всем
- 6: картечь всем
- 7: книпеля всем 
- 8: бомбы всем
- O: уплыть всем (letter "O").
- L: паруса в боевой режим всем
- P: защищать флагмана всем
*/

bool FLT_CdreCommand = false;			

void FLT_SendCommand(string sComm)
{
	int nShipType;
	ref rChr;
	int i;

	FLT_CdreCommand = true;						

	for (i = 1; i < COMPANION_MAX; i++)
	{
		int cn;									
		cn = GetCompanionIndex(pchar, i);
		if (cn == -1) continue;
		makeref(rChr, Characters[cn]);			
		nShipType = GetCharacterShipType(rChr);
		if (nShipType == SHIP_NOTUSED) continue;

		switch (sComm)
		{
			case "FLT_LoadBalls"	:
/*			
                if (!CheckAttribute(rChr, "Ship.Cannons.ChargeOverride") || rChr.Ship.Cannons.ChargeOverride != GOOD_BALLS)
                {
                    Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 1, "");
                }
*/				
			break;
			case "FLT_LoadGrapes"	:
/*			
                if (!CheckAttribute(rChr, "Ship.Cannons.ChargeOverride") || rChr.Ship.Cannons.ChargeOverride != GOOD_GRAPES)
                {
                    Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 2, "");
                }
*/				
			break;
			case "FLT_LoadChain"	:
/*			
                if (!CheckAttribute(rChr, "Ship.Cannons.ChargeOverride") || rChr.Ship.Cannons.ChargeOverride != GOOD_KNIPPELS)
                {
                    Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 3, "");
                }
*/				
			break;
			case "FLT_LoadBombs"	:
/*			
                if (!CheckAttribute(rChr, "Ship.Cannons.ChargeOverride") || rChr.Ship.Cannons.ChargeOverride != GOOD_BOMBS)
                {
                    Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 4, "");
                }
*/				
			break;
			case "FLT_SailAway"		:
				Event("BI_LaunchCommand","lsls", cn, "BI_SailAway", -1, "");
			break;
			case "FLT_LowerSails"	:
				Event("BI_LaunchCommand","lsls", cn, "BI_HeaveToDrift", -1, "");
			break;
			case "FLT_ProtFlagship"	:
				Event("BI_LaunchCommand","lsls", cn, "BI_Defend", GetMainCharacterIndex(), "");
			break;
		}
	}
	FLT_CdreCommand = false;
}
