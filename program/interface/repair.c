int nCurScrollNum = 0;
ref xi_refCharacter;
string sChrId;

int 	pAvail, sAvail;
float 	cur_pAvail, cur_sAvail;
int 	cur_SailMaximum;

void InitInterface_R(string iniName, ref rChar)
{
	xi_refCharacter = rChar;
	
	StartAboveForm(true);
			
	FillShipsScroll();
  
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
		
	SetDescription();

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("frame","ProcessFrame",0);
        
    SetNewGroupPicture("REPAIR_Hull_PIC", "REPAIR_STATE_ICONS", "Hull");
    SetNewGroupPicture("REPAIR_Sail_PIC", "REPAIR_STATE_ICONS", "Sail");
	SetNewGroupPicture("REPAIR_Mast_PIC", "REPAIR_STATE_ICONS", "Mast");
	
	SetNewGroupPicture("REPAIR_HULL_P_PIC",    "GOODS", "Planks");
	SetNewGroupPicture("REPAIR_MAST_P_PIC",    "GOODS", "Planks");
	SetNewGroupPicture("REPAIR_SAIL_S_PIC",    "GOODS", "SailCloth");
		
	EI_CreateFrame("BIG_PICTURE_BORDER", 78,178,722,480);
    EI_CreateHLine("BIG_PICTURE_BORDER", 82,280,718,1, 4);
	EI_CreateHLine("BIG_PICTURE_BORDER", 82,380,718,1, 4);
	
	SetRepairData();

	SetButtonsAccess();
}

void ProcessExitCancel()
{		
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	ref chr;
	ref mc = GetMainCharacter();
	int cn;

	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("frame","ProcessFrame");
	
	EndAboveForm(true);
    
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
	
	for (int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(mc,i);
		if( cn > 0 )
        {
			chr = GetCharacter(cn);
			if(CheckAttribute(chr, "repair")) DeleteAttribute(chr, "repair");
			GetAllSailsDamagePercent(chr);
		}	
	}		
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
	int mastFall = GetShipFallMastsQuantity(xi_refCharacter);
	
    switch(nodName)
	{		
		case "REPAIR_LEFT_H":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("hull", -1, xi_refCharacter, true);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("hull", -5, xi_refCharacter, true);
			}
		break;
		
		case "REPAIR_RIGHT_H":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("hull", 1, xi_refCharacter, true);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("hull", 5, xi_refCharacter, true);
			}
		break;
		
		case "REPAIR_LEFT_S":
			if (comName=="click" || comName=="activate")
			{
				ClickRepairArror("sail", -1, xi_refCharacter, true);
			}
			if (comName=="rclick")
			{
				ClickRepairArror("sail", -5, xi_refCharacter, true);
			}
		break;
		
		case "REPAIR_RIGHT_S":
			if (comName=="click" || comName=="activate")
			{				
				ClickRepairArror("sail", 1, xi_refCharacter, true);
			}
			if (comName=="rclick")
			{
				ClickRepairArror("sail", 5, xi_refCharacter, true);
			}
		break;
		
		case "REPAIR_LEFT_M":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("mast", -mastFall, xi_refCharacter, true);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("mast", -mastFall, xi_refCharacter, true);
			}
		break;
		
		case "REPAIR_RIGHT_M":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("mast", mastFall, xi_refCharacter, true);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("mast", mastFall, xi_refCharacter, true);
			}
		break;
		
		case "REPAIR_OK":
			if (comName=="click" || comName=="activate")
			{
				RepairOk();
				IDoExit(RC_INTERFACE_ANY_EXIT);
				if(CheckAttribute(pchar,"quest.waithours"))
				{
					DoQuestFunctionDelay("WaitNextHours", 0.1);
				}				
			}
		break;
		
		case "REPAIR_CANCEL":
			if (comName=="click" || comName=="activate")
			{
				IDoExit(RC_INTERFACE_ANY_EXIT);
			}
		break;		
		
		case "REPAIR_ALL_SHIP":
			if (comName=="click" || comName=="activate")
			{
			    RepairAll();
			}
		break;		
		
		case "REPAIR_ALL_SQUADRON":
			if (comName=="click" || comName=="activate")
			{
			    RepairAllSquadron();
			}
		break;		
	}
}

void FillShipsScroll()
{
	nCurScrollNum = -1;
	FillScrollImageWithCompanionShips("SHIPS_SCROLL", 5);

	if(!CheckAttribute(&GameInterface,"SHIPS_SCROLL.current"))
	{
		GameInterface.SHIPS_SCROLL.current = 0;
	}
}

void SetDescription()
{
 	if(GetCurrentNode() == "SHIPS_SCROLL")
	{	
		string attributeName = attributeName = "pic" + (nCurScrollNum+1);
		if(CheckAttribute(&GameInterface, "SHIPS_SCROLL." + attributeName))
		{
			int iCharacter = GameInterface.SHIPS_SCROLL.(attributeName).companionIndex;
			sChrId = characters[iCharacter].id;
//			trace("sChrId " + sChrId);
			xi_refCharacter = characterFromID(sChrId);
		}
	}
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\256\face_" + its(xi_refCharacter.FaceId) + ".tga");

	if (CheckAttribute(xi_refCharacter, "ship.name"))
	{
		SetFormatedText("REPAIR_SHIP_NAME", xi_refCharacter.ship.name);
	}
	else
	{
		SetFormatedText("REPAIR_SHIP_NAME", "");
	}
	
	SetFormatedText("NAME_STR", GetFullName(xi_refCharacter));
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"NAME_STR", 5 );

	SetFormatedText("LOCATION_STR", GetCurLocationName());
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"LOCATION_STR", 5 );	
}

void ProcessFrame()
{
	if(GetCurrentNode() == "SHIPS_SCROLL")
	{
		if(sti(GameInterface.SHIPS_SCROLL.current)!=nCurScrollNum)
		{			
			nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);
			SetDescription();
			SetButtonsAccess();
			
			RepairStatShow(xi_refCharacter, true);
		}
	}
}

int GetMaxRepairTime()
{
	ref chr;
	ref mc = GetMainCharacter();
	int tHull, tSail, tMast;
	int totalTime = 0;
	int cn;
	
	tHull = 0;
	tSail = 0; 
	tMast = 0;
	
	for (int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(mc,i);
		if( cn > 0 )
        {
	        chr = GetCharacter(cn); 
		
			if(CheckAttribute(chr,"repair"))
			{
				tHull = sti(chr.repair.time_hull);
				tMast = sti(chr.repair.time_mast);
				tSail = sti(chr.repair.time_sail);
				
//				trace("tHull " + tHull + " tMast " + tMast + " tSail " + tSail + " chr.id " + chr.id);

				if (tSail > 0 || tHull > 0 || tMast > 0)
				{
					chr.repair.totaltime = tHull/3.0 + tSail/5.0 + tMast;
					chr.repair.totaltime = makeint(stf(chr.repair.totaltime) * ( 1.75 - GetCrewQuantity(chr)/GetOptCrewQuantity(chr)));

//					trace( "totaltime " + totaltime);
//					trace( "CrewQuantity : " + GetCrewQuantity(chr) + " OptCrewQuantity : " + GetOptCrewQuantity(chr));
//					trace( "GetCrewQuantity()/GetOptCrewQuantity() " + GetCrewQuantity(chr)/GetOptCrewQuantity(chr));
//					trace( "totalTime " +  chr.repair.totaltime + " chr.id " + chr.id); 

					if(makeint(stf(chr.repair.totaltime)) > totalTime) totalTime = makeint(stf(chr.repair.totaltime));
					if(totalTime < 1) totalTime = 1;
				}
			}
		}	
	}	
//	trace("totaltime " + totaltime);
	return totalTime;	
}

int SetSailMaximum(ref rChar)
{
	int iSP = makeint(GetAllSailsDamagePercent(rChar));	
	if(sti(rChar.repair.mast) == GetShipFallMastsQuantity(rChar)) iSP = 100;		
	return iSP;
}

void SetRepairData()
{
	ref chr;
	ref mc = GetMainCharacter();
	int cn;	
	
	for (int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(mc,i);
        if( cn > 0 )
        {
	        chr = GetCharacter(cn); 
		
//			trace("Companion[" + i + "].chr.id = " + chr.id);
		
			chr.repair.hull = 0;
			chr.repair.mast = 0;		
			chr.repair.sail = 0;
		
			chr.repair.time_hull = 0;
			chr.repair.time_mast = 0;		
			chr.repair.time_sail = 0;
			
			chr.repair.hull_limit = 0;
			chr.repair.mast_limit = 0;		
			chr.repair.sail_limit = 0;
					
			chr.repair.preq = 0;
			chr.repair.sreq = 0;
			
			chr.repair.preq_max = 0;
			chr.repair.sreq_max = 0;
			
			chr.repair.sailmax = SetSailMaximum(chr);
		}
	}	
	
	pAvail 	= GetSquadronGoods(mc, GOOD_PLANKS);
	sAvail 	= GetSquadronGoods(mc, GOOD_SAILCLOTH);
	
	cur_pAvail = pAvail;
	cur_sAvail = sAvail;
	
 	RepairStatShow(xi_refCharacter, true);
}

void GetLimits(ref chr)
{
	int i;
	
	int hp = MakeInt(GetHullPercent(chr));
	int sp = makeint(stf(chr.ship.sailstatus.sailpow) - stf(chr.ship.sailstatus.saildmg));
	
	int mp = GetShipMastsQuantity(chr));
	int mf = GetShipFallMastsQuantity(chr);
	
	// hull
	i = cur_pAvail / GetHullRepairMathQty(chr, 1);
	if(i + hp >= 100) 						chr.repair.hull_limit = 100;
	else 									chr.repair.hull_limit = i + hp;	
	
	// sail
	i = cur_sAvail / GetSailRepairMathQty(chr, 1);
	if(i + sp >= sti(chr.repair.sailmax)) 	chr.repair.sail_limit = sti(chr.repair.sailmax);
	else 									chr.repair.sail_limit = i + sp;	
		
	// mast
	float 	repHMathQ, repSMathQ;
	repHMathQ = makeint(GetMastRepairMathQtyPPP(chr, mf));
	repSMathQ = makeint(GetMastRepairMathQtySPP(chr, mf, 100 - sti(chr.repair.sailmax)));
	if(cur_sAvail >= repSMathQ && cur_pAvail >= repHMathQ)
	{
		chr.repair.mast_limit = mp + "/" + mp; // :)
	}
}

void RepairStatShow(ref chr, bool isVisible)
{
    int hp = MakeInt(GetHullPercent(chr));
	int sp = makeint(stf(chr.ship.sailstatus.sailpow) - stf(chr.ship.sailstatus.saildmg));	
	int mp = GetShipMastsQuantity(chr) - GetShipFallMastsQuantity(chr);
	
	int rHull = sti(chr.repair.hull);
	int rMast = sti(chr.repair.mast); 
	int rSail = sti(chr.repair.sail);

	GetLimits(chr);
	
	if(isVisible)
	{
		string mpText = (mp + rMast) + "/" + GetShipMastsQuantity(chr);
		
		SetFormatedText("REPAIR_QTY_H", (hp + rHull) + "%");
		if((hp + rHull) == 100)
			SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_QTY_H", 8, 0, argb(255,128,255,255) );
		else	
			SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_QTY_H", 8, 0, argb(255,255,255,255) );
			
		SetFormatedText("REPAIR_QTY_S", (sp + rSail) + "%");
		if((sp + rSail) == sti(chr.repair.sailmax))
			SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_QTY_S", 8, 0, argb(255,128,255,255) );
		else	
			SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_QTY_S", 8, 0, argb(255,255,255,255) );
		
		SetFormatedText("REPAIR_QTY_M", mpText);
		if((mp + rMast) == GetShipMastsQuantity(chr))
			SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_QTY_M", 8, 0, argb(255,128,255,255) );
		else	
			SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_QTY_M", 8, 0, argb(255,255,255,255) );
				
		string sText;
		sText = " State: \n" + hp + "% \n Current limit \ n recovery: \n " + chr.repair.hull_limit + "% ";
		SetFormatedText("REPAIR_STATUS_HULL_STR", sText);
		SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_STATUS_HULL_STR", 5 );
		
		string mText = (mp) + "/" + GetShipMastsQuantity(chr);
		sText = " State: \n" + mText + "\n Current limit \ n recovery: \n " + chr.repair.mast_limit + " ";
		SetFormatedText("REPAIR_STATUS_MAST_STR", sText);
		SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_STATUS_MAST_STR", 5 );
		
		sText = " State: \n" + sp + "% \n Current limit \ n recovery: \n " + chr.repair.sail_limit + "% ";
		SetFormatedText("REPAIR_STATUS_SAIL_STR", sText);
		SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_STATUS_SAIL_STR", 5 );

		sText = " Running time :\n " + GetMaxRepairTime() + " hours. ";
		SetFormatedText("TIME_STR", sText);
		SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TIME_STR", 5 );
	}	
	RepairMatherialShow(chr, isVisible);
}

void RepairMatherialShow(ref chr, bool isVisible)
{
    int st = GetCharacterShipType(chr);
	string sText;
		
	int hp = MakeInt(GetHullPercent(chr));	
	int sp = makeint(stf(chr.ship.sailstatus.sailpow) - stf(chr.ship.sailstatus.saildmg));
	int mp = GetShipMastsQuantity(chr) - GetShipFallMastsQuantity(chr);
	
	int rHull = sti(chr.repair.hull);
	int rMast = sti(chr.repair.mast); 
	int rSail = sti(chr.repair.sail);
	
	chr.repair.preq = makeint(GetHullRepairMathQty(chr, rHull) + GetMastRepairMathQtyPPP(chr, rMast));
	chr.repair.sreq = makeint(GetSailRepairMathQty(chr, rSail) + GetMastRepairMathQtySPP(chr, rMast, 100 - sti(chr.repair.sailmax)));
	
	chr.repair.preq_max = makeint(GetHullRepairMathQty(chr, 100 - hp) + GetMastRepairMathQtyPPP(chr, rMast));
	chr.repair.sreq_max = makeint(GetSailRepairMathQty(chr, 100 - sp));
	
	if(isVisible)
	{	
		sText = " Available: \n" + makeint(cur_pAvail) + "/" + pAvail + " pcs \n Necessary for a \n complete repair: \n " + makeint(GetHullRepairMathQty(chr, 100 - hp)) + " pcs ";
		SetFormatedText("REPAIR_QTY_HULL_STR", sText);
		SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_QTY_HULL_STR", 5 );
		
		sText = " Available: \n" + makeint(cur_pAvail) + "/"  + pAvail + " pcs \n Necessary for a \n complete repair: \n " + makeint(GetMastRepairMathQtyPPP(chr, GetShipFallMastsQuantity(chr))) + " pcs ";
		SetFormatedText("REPAIR_QTY_MAST_STR", sText);
		SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_QTY_MAST_STR", 5 );
		
		sText = " Available: \n" + makeint(cur_sAvail) + "/"  + sAvail + " pcs \n Necessary for a \n complete repair: \n " + makeint(GetSailRepairMathQty(chr, 100 - sp)) + " pcs ";
		SetFormatedText("REPAIR_QTY_SAIL_STR", sText);
		SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_QTY_SAIL_STR", 5 );
	}
}

void SetButtonsAccess()
{
	SetSelectable("REPAIR_OK",  			false);
	SetSelectable("REPAIR_ALL_SHIP", 		false);
	SetSelectable("REPAIR_ALL_SQUADRON", 	false);
	
	ref chr;
	bool bOk = false;
	ref mc = GetMainCharacter();
	int cn;
	
	for (int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(mc,i);
        if( cn > 0 )
        {
			chr = GetCharacter(cn);
			if (GetHullPercent(chr) < 100 || GetSailPercent(chr) < sti(chr.repair.sailmax) || GetShipFallMastsQuantity(chr) > 0)
			{
				bOk = true; break;			
			}
		}	
	}	
	SetSelectable("REPAIR_OK",  		bOk);
	SetSelectable("REPAIR_ALL_SHIP", 	bOk);
	
	if(GetCompanionQuantity(mc) > 1 && bOk) SetSelectable("REPAIR_ALL_SQUADRON", bOk);
}

float GetSailRepairMathQty(ref rChar, int repairPercent)
{
	return repairPercent * GetSailSPP(rChar);
}

float GetHullRepairMathQty(ref rChar, int repairPercent)
{
	return repairPercent * GetHullPPP(rChar);
}

float GetMastRepairMathQtySPP(ref rChar, int mastQty, int repairPercent)
{
	if(mastQty > 0) 
	{
		return  GetSailRepairMathQty(rChar, repairPercent);
	}	
	return 0.0;
}

float GetMastRepairMathQtyPPP(ref rChar, int mastQty)
{
	return mastQty * GetHullRepairMathQty(rChar, 5);
}

void ClickRepairArror(string _type, int add, ref chr, bool isVisible)
{
    int st = GetCharacterShipType(chr);
    int i, j;
    int hp = MakeInt(GetHullPercent(chr));
	int sp = makeint(stf(chr.ship.sailstatus.sailpow) - stf(chr.ship.sailstatus.saildmg));
	int mp = GetShipMastsQuantity(chr) - GetShipFallMastsQuantity(chr);
	
	int rHull = sti(chr.repair.hull);
	int rMast = sti(chr.repair.mast); 
	int rSail = sti(chr.repair.sail);
	
	float repHMathQ, repSMathQ;
	
	if (_type == "hull")
	{
		j = rHull;
		if (add > 0)
		{
			if(cur_pAvail >= makeint(GetHullRepairMathQty(chr, rHull + add)))
		    {
		        rHull += add;
		    }
		    else
		    {
				i = cur_pAvail / GetHullRepairMathQty(chr, 1);
		        rHull += i;
		    }
		    if ((rHull + hp) > 100)  rHull = 100 - hp;
	    }
	    else
	    {
            rHull += add;
			if (rHull < 0)  rHull = 0;
	    }
		cur_pAvail 			   -= GetHullRepairMathQty(chr, rHull - j);		
		chr.repair.hull 		= rHull;
		chr.repair.time_hull 	= rHull * (8-GetCharacterShipClass(chr));
	}
	
	if (_type == "sail")
	{	
		j = rSail;
	    if (add > 0)
		{							
			if((rSail + add) <= sti(chr.repair.sailmax))
			{
				if(cur_sAvail >= makeint(GetSailRepairMathQty(chr, rSail + add)))
				{
					rSail += add;
				}
				else
				{
					i = cur_sAvail / GetSailRepairMathQty(chr, 1);
					rSail += i;
				}
				if ((rSail + sp) > sti(chr.repair.sailmax))  rSail = sti(chr.repair.sailmax) - sp;
			}				
	    }
	    else
	    {
            rSail = rSail + add;
			if (rSail < 0)  rSail = 0;
	    }
		cur_sAvail 			   -= GetSailRepairMathQty(chr, rSail - j);		
		chr.repair.sail 		= rSail;
		chr.repair.time_sail 	= rSail * (8-GetCharacterShipClass(chr));
	}
	
	if (_type == "mast")
	{
		if((rHull + hp) >= 85)
		{	
			j = rMast;
			if (add > 0)
			{				
				repHMathQ = makeint(GetMastRepairMathQtyPPP(chr, rMast + add));
				repSMathQ = makeint(GetMastRepairMathQtySPP(chr, rMast + add, 100 - sti(chr.repair.sailmax)));
				if(cur_sAvail >= repSMathQ && cur_pAvail >= repHMathQ)
				{
					rMast += add;
				}
				if((rMast + mp) > GetShipMastsQuantity(chr)) rMast = GetShipMastsQuantity(chr) - mp;
			}
			else
			{
				rMast = rMast + add;
				if (rMast < 0)  rMast = 0;
			}
			chr.repair.mast 		= rMast;
			chr.repair.time_mast 	= rMast * (11-GetCharacterShipClass(chr));
			cur_pAvail -= GetMastRepairMathQtyPPP(chr, rMast - j);		
			cur_sAvail -= GetMastRepairMathQtySPP(chr, rMast - j, 100 - sti(chr.repair.sailmax));	
		}
	}	
	RepairStatShow(chr, isVisible);
}

void RepairOk()
{
	ref chr;
	ref mc = GetMainCharacter();
	int cn;

	for (int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(mc,i);
        if( cn > 0 )
        {
			chr = GetCharacter(cn);

			int st = GetCharacterShipType(chr);
			int hp = MakeInt(GetHullPercent(chr));
			int sp = MakeInt(GetSailPercent(chr));
			float ret;
			
			int rHull = sti(chr.repair.hull);
			int rMast = sti(chr.repair.mast); 
			int rSail = sti(chr.repair.sail);
		
			if(rHull == 0 && rMast == 0 && rSail == 0) continue;
		
			if (rHull > 0)
			{
				chr.repair.time_hull = rHull * (8-GetCharacterShipClass(chr));
				AddCharacterExpToSkill(chr, "Repair", (rHull * (7-GetCharacterShipClass(chr)) / 2.5));
				ret = ProcessHullRepair(chr, stf(rHull));
			}
		
			if (rSail > 0)
			{
				chr.repair.time_sail = rSail * (8-GetCharacterShipClass(chr));
				AddCharacterExpToSkill(chr, "Repair", (rSail * (7-GetCharacterShipClass(chr)) / 3.5));
				ret = ProcessSailRepair(chr, stf(rSail));		
			}
		
			if (rMast > 0)
			{
				chr.repair.time_mast = rMast * (11-GetCharacterShipClass(xi_refCharacter));
				AddCharacterExpToSkill(chr, "Repair", (3 * rMast * (7-GetCharacterShipClass(chr)) / 3.5));
				DeleteAttribute(chr, "ship.masts");
			}
			
			if ((hp + rHull) >= 100)
			{
				chr.ship.hp = GetCharacterShipHP(chr);
				DeleteAttribute(chr, "ship.hulls");
				DeleteAttribute(chr, "ship.blots");		
			}
		
			if ((sp + rSail) >= sti(chr.repair.sailmax))
			{
				chr.ship.sp = GetCharacterShipSP(chr);
				DeleteAttribute(chr, "ship.sails");
			}
		
			if(sti(chr.repair.preq) > 0) RemoveCharacterGoods(pchar, GOOD_PLANKS,    sti(chr.repair.preq));
			if(sti(chr.repair.sreq) > 0) RemoveCharacterGoods(pchar, GOOD_SAILCLOTH, sti(chr.repair.sreq));
		}
	}

	ret = GetMaxRepairTime();
	if(ret > 0) 
	{
		mc.quest.waithours = ret;
	}	
	Achievment_SetStat(mc, 64, 1); // ugeen 2016
}

void RepairAll()
{  
	ClickRepairArror("hull", 100, xi_refCharacter, true);
	
	if(GetShipFallMastsQuantity(xi_refCharacter) > 0)
	{
		ClickRepairArror("mast", GetShipFallMastsQuantity(xi_refCharacter), xi_refCharacter, true);
	}			
	ClickRepairArror("sail", sti(xi_refCharacter.repair.sailmax), xi_refCharacter, true);    
}

void RepairAllSquadron()
{
	ref chr;
	ref mc = GetMainCharacter();
	int cn;
	bool isVisible;
	
	for (int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(mc,i);
        if( cn > 0 )
        {
			chr = GetCharacter(cn);
			if(chr.id == xi_refCharacter.id) 	isVisible = true;
			else								isVisible = false;
			
			ClickRepairArror("hull", 100, chr, isVisible);
		
			if(GetShipFallMastsQuantity(chr) > 0)
			{
				ClickRepairArror("mast", GetShipFallMastsQuantity(chr), chr, isVisible);
			}	
			ClickRepairArror("sail", sti(chr.repair.sailmax), chr, true);    
		}
	}	
}

