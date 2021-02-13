
#define REAL_SHIPS_QUANTITY 900

object RealShips[REAL_SHIPS_QUANTITY];
#define SAILSCOLOR_PRICE_RATE 0.1
#define SAILSGERALD_PRICE_RATE 0.2

#define SAIL_COST_PERCENT 10
#define HULL_COST_PERCENT 20

ref GetRealShip(int iType)
{
    if (iType >= REAL_SHIPS_QUANTITY)
    {
        trace("--- Wrong Ship Index. iType is " + iType);
        Log_TestInfo("--- Wrong Ship Index. iType is " + iType);
        return &ShipsTypes[SHIP_TYPES_QUANTITY + 1]; // для отлова
    }
    return &RealShips[iType];
}

// isLock - рудимент, можно выкидывать (26.05.06 boal)
// новая жизнь isLock (04.07.06) теперь это признак ворованности (те цены на верфи)
// если 1 - ворованный, цена копеешная, 0 - честно купленный - можно перепродать.
int GenerateShip(int iBaseType, bool isLock)
{
    int iShip = CreateBaseShip(iBaseType);

    if (iShip == -1)
    {
        return SHIP_NOTUSED;
    }

    ref rRealShip = GetRealShip(iShip);
    ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
    // boal 26/05/06 изменим
    rRealShip.ship.upgrades.hull = 1 + rand(2);  //признак корабля теперь
    rRealShip.ship.upgrades.sails = 1 + rand(2); // только визуальная разница

    if (!CheckAttribute(rRealShip, "isFort"))
    {
        int iCaliber = sti(rRealShip.MaxCaliber);
        //string sCannonType = GetCannonType(rRealShip.Cannon);
        if (sti(rRealShip.Class) != 6)
        { // чтоб не было баркаса с 16ф
            switch (iCaliber)
            {
            case 3:
                iCaliber = 0;
                break;
            case 6:
                iCaliber = 1;
                break;
            case 8:
                iCaliber = 2;
                break;
            case 12:
                iCaliber = 3;
                break;
            case 16:
                iCaliber = 4;
                break;
            case 18:
                iCaliber = 5;
                break;
            case 20:
                iCaliber = 6;
                break;
            case 24:
                iCaliber = 7;
                break;
            case 32:
                iCaliber = 8;
                break;
            case 36:
                iCaliber = 9;
                break;
            case 42:
                iCaliber = 10;
                break;
            }
            iCaliber = iCaliber - rand(1); // фикс перебора калибра орудий
            if (iCaliber < 0)
                iCaliber = 0;
            if (sti(rRealShip.Class) == 1)
            {
                if (iCaliber > 10)
                    iCaliber = 10;
            }
            else
            {
                if (iCaliber > 9)
                    iCaliber = 9;
            }
            switch (iCaliber)
            {
            case 0:
                iCaliber = 3;
                break;
            case 1:
                iCaliber = 6;
                break;
            case 2:
                iCaliber = 8;
                break;
            case 3:
                iCaliber = 12;
                break;
            case 4:
                iCaliber = 16;
                break;
            case 5:
                iCaliber = 18;
                break;
            case 6:
                iCaliber = 20;
                break;
            case 7:
                iCaliber = 24;
                break;
            case 8:
                iCaliber = 32;
                break;
            case 9:
                iCaliber = 36;
                break;
            case 10:
                iCaliber = 42;
                break;
            }
            rRealShip.MaxCaliber = iCaliber;
        }
        rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + frandSmall(stf(rRealShip.SpeedRate) / 5.0) - stf(rRealShip.SpeedRate) / 10.0;
        rRealShip.TurnRate = stf(rRealShip.TurnRate) + frandSmall(stf(rRealShip.TurnRate) / 5.0) - stf(rRealShip.TurnRate) / 10.0;
        //rRealShip.Price            = sti(rRealShip.Price) + rand(makeint(sti(rRealShip.Price)/2)) - makeint(sti(rRealShip.Price)/4);
        rRealShip.HP = sti(rRealShip.HP) + rand(makeint(sti(rRealShip.HP) / 5)) - makeint(sti(rRealShip.HP) / 10);
        rRealShip.WindAgainstSpeed = stf(rRealShip.WindAgainstSpeed) + frandSmall(stf(rRealShip.WindAgainstSpeed) / 5.0) - stf(rRealShip.WindAgainstSpeed) / 10.0;
    }
    rRealShip.Capacity = sti(rRealShip.Capacity) + rand(makeint(sti(rRealShip.Capacity) / 4)) - makeint(sti(rRealShip.Capacity) / 8);
    rRealShip.OptCrew = makeint(sti(rRealShip.OptCrew) + rand(makeint(sti(rRealShip.OptCrew) / 3)) - makeint(sti(rRealShip.OptCrew) / 6));
    rRealShip.MaxCrew = makeint(sti(rRealShip.OptCrew) * 1.25 + 0.5); // 25% перегруза
    rRealShip.MinCrew = makeint(sti(rRealShip.MinCrew) + rand(makeint(sti(rRealShip.MinCrew) / 3)) - makeint(sti(rRealShip.MinCrew) / 6));

    rRealShip.Weight = sti(rRealShip.Weight) + rand(sti(rRealShip.Weight) / 20) - rand(sti(rRealShip.Weight) / 20);
    rRealShip.BaseHP = sti(rRealShip.HP);

    // to_do del -->
    rRealShip.BoardingCrew = 0;
    rRealShip.GunnerCrew = 0;
    rRealShip.CannonerCrew = 0;
    rRealShip.SailorCrew = sti(rRealShip.OptCrew);
    // to_do del <--

    int iDiffWeight = sti(rRealShip.Weight) - sti(rBaseShip.Weight);
    int iDiffCapacity = sti(rRealShip.Capacity) - sti(rBaseShip.Capacity);
    int iDiffMaxCrew = sti(rRealShip.MaxCrew) - sti(rBaseShip.MaxCrew);
    int iDiffMinCrew = sti(rRealShip.MinCrew) - sti(rBaseShip.MinCrew);
    float fDiffSpeedRate = stf(rRealShip.SpeedRate) - stf(rBaseShip.SpeedRate);
    int iDiffTurnRate = sti(rRealShip.TurnRate) - sti(rBaseShip.TurnRate);
    int iDiffHP = sti(rRealShip.HP) - sti(rBaseShip.HP);

    rRealShip.Price = (iDiffWeight + iDiffCapacity + iDiffMaxCrew * 2 + iDiffMinCrew + fDiffSpeedRate * 2 + iDiffTurnRate * 2 + iDiffHP) * 5 + sti(rRealShip.Price);

    if (sti(rRealShip.Price) <= 0)
        rRealShip.Price = 100;

    rRealShip.Stolen = isLock; // ворованность

    return iShip;
}

// -> added by ugeen 25.01.09 (на основе GenerateShip(.....)) - рандомизируем кол-во стволов на борту
// 31.01.09 - добавил бонусы к корабельным статам если кол-во орудий на борту < базового
int GenerateShipExt(int iBaseType, bool isLock, ref chr)
{
    string attr, sCity;
    int i;
    aref refShip;
    float Кdckyrd = 1.0;
    bool isShipyard = false;

    int iShip = CreateBaseShip(iBaseType);

    if (iShip == -1)
    {
        return SHIP_NOTUSED;
    }

    ref rRealShip = GetRealShip(iShip);
    ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
    // boal 26/05/06 изменим
    rRealShip.ship.upgrades.hull = 1 + rand(2);  //признак корабля теперь
    rRealShip.ship.upgrades.sails = 1 + rand(4); // только визуальная разница

    rRealShip.Bonus_Capacity = 0;
    rRealShip.Bonus_HP = 0;
    rRealShip.Bonus_SpeedRate = 0.0;
    rRealShip.Bonus_TurnRate = 0.0;

    // ugeen --> если кораблик генерится на верфи, разброс статов более узкий
    if (CheckAttribute(chr, "City"))
    {
        sCity = chr.City;
        if (CheckCharacterID(chr, sCity + "_shipyarder"))
        {
            Кdckyrd = 0.8;
            isShipyard = true;
        }
    }
    // ugeen

    if (!CheckAttribute(rRealShip, "isFort"))
    {
        int iCaliber = sti(rRealShip.MaxCaliber);
        if (sti(rRealShip.Class) != 6 && !CheckAttribute(rRealShip, "QuestShip"))
        { // чтоб не было баркаса с 16ф
            switch (iCaliber)
            {
            case 3:
                iCaliber = 0;
                break;
            case 6:
                iCaliber = 1;
                break;
            case 8:
                iCaliber = 2;
                break;
            case 12:
                iCaliber = 3;
                break;
            case 16:
                iCaliber = 4;
                break;
            case 18:
                iCaliber = 5;
                break;
            case 20:
                iCaliber = 6;
                break;
            case 24:
                iCaliber = 7;
                break;
            case 32:
                iCaliber = 8;
                break;
            case 36:
                iCaliber = 9;
                break;
            case 42:
                iCaliber = 10;
                break;
            }
            //iCaliber = iCaliber + rand(2) - 1;
            iCaliber = iCaliber - rand(1); //Jason: согласно новой системе орудий калибр должен быть постоянен, но пока поставим рандом на единицу меньше, а больше - нельзя по определению, на рез. тестов решим, фиксировать или рандомить
            if (iCaliber < 0)
                iCaliber = 0;
            if (sti(rRealShip.Class) == 1)
            {
                if (iCaliber > 10)
                    iCaliber = 10;
            }
            else
            {
                if (iCaliber > 9)
                    iCaliber = 9;
            }
            switch (iCaliber)
            {
            case 0:
                iCaliber = 3;
                break;
            case 1:
                iCaliber = 6;
                break;
            case 2:
                iCaliber = 8;
                break;
            case 3:
                iCaliber = 12;
                break;
            case 4:
                iCaliber = 16;
                break;
            case 5:
                iCaliber = 18;
                break;
            case 6:
                iCaliber = 20;
                break;
            case 7:
                iCaliber = 24;
                break;
            case 8:
                iCaliber = 32;
                break;
            case 9:
                iCaliber = 36;
                break;
            case 10:
                iCaliber = 42;
                break;
            }
            rRealShip.MaxCaliber = iCaliber;
        }

        int iCannonDiff = 0;
        int iDiffClass = 5 - makeint(sti(rRealShip.Class) / 2);

        switch (rRealShip.BaseName)
        {
        case "Barque":
            iCannonDiff = rand(1); //  14,12   (0,2,6,6) (0,2,5,5)
            break;
        case "Schooner":
            iCannonDiff = rand(1); // 12, 10     (5-ый класс)
            break;
        case "Barkentine":
            iCannonDiff = rand(1); // 14, 12   (4-ый класс)
            break;
        case "Shnyava":
            iCannonDiff = rand(1);
            break;
        case "Fleut":
            iCannonDiff = rand(1); // 18, 16    (4-ый класс)
            break;
        case "Caravel":
            iCannonDiff = rand(1); // 20, 18, (3-ый класс)
            break;
        case "Pinnace":
            iCannonDiff = rand(1); // 18, 16   (3-ий класс)
            break;
        case "Caracca":
            iCannonDiff = rand(1); // 18, 16   (3-ий класс)
            break;
        case "LuggerQuest":
            iCannonDiff = rand(1); // 12, 10      (6-ой класс)
            break;
        case "Lugger":
            iCannonDiff = rand(1); // 12, 10      (6-ой класс)
            break;
        case "Sloop":
            iCannonDiff = rand(1); // 14, 12      (6-ой класс)
            break;
        case "Brigantine":
            iCannonDiff = rand(1); // 14, 12       (4-ый класс)
            break;
        case "Brig":
            iCannonDiff = rand(1); // 16, 14    (4-ый класс)
            break;
        case "Schooner_W":
            iCannonDiff = rand(1); // 20, 18, 16     (5-ый класс)
            break;
        case "Galeon_l":
            iCannonDiff = rand(1); // 20, 18    (4-ый класс)
            break;
        case "Corvette":
            iCannonDiff = rand(1); // 20, 18
            break;
        case "XebekVML":
            iCannonDiff = rand(1); // 32, 30, 28     (3-ий класс)
            break;
        case "Polacre":
            iCannonDiff = rand(2); // 22, 20, 18     (3-ий класс)
            break;
        case "Navio":
            iCannonDiff = rand(2); // 36, 34, 32    (3-ий класс)
            break;
        case "EastIndiaMan":
            iCannonDiff = rand(2); // 36, 34, 32    (3-ий класс)
            break;
        case "Galeon_h":
            iCannonDiff = rand(4); // 54, 52, 50, 48, 46    (3-ий класс)
            break;
        case "Frigate":
            iCannonDiff = rand(3); // 46, 44, 42, 40    (2-ой класс)
            break;
        case "Frigate_h":
            iCannonDiff = rand(3); // 46, 44, 42, 40    (2-ой класс)
            break;
        case "Lineship":
            iCannonDiff = rand(4); // 56, 54, 52, 50, 48    (2-ой класс)
            break;
        case "Warship":
            iCannonDiff = rand(4); // 66, 64, 62, 60, 58   (1-ый класс)
            break;
        case "Battleship":
            iCannonDiff = rand(5); // 80, 78, 76, 74, 72, 70   (1-ый класс)
            break;
        case "Manowar":
            iCannonDiff = rand(5); // 102, 100, 98, 96, 94, 92  (1-ый класс)
            break;
        case "Manowar_e":
            iCannonDiff = rand(5); // 102, 100, 98, 96, 94, 92  (1-ый класс)
            break;
        }

        if (CheckAttribute(rRealShip, "QuestShip") || isShipyard)
            iCannonDiff = 0;

        // ---> собственно сам рэндом стволов
        makearef(refShip, chr.Ship);
        ResetShipCannonsDamages(chr);

        // куда-нить запишем максимально возможное и минимальное кол-во орудий (потом нужно будет, если захотим проапгрейдиться на этот счет)
        rRealShip.CannonsQuantityMax = sti(rRealShip.CannonsQuantity);
        refShip.CannonsQuantityMax = sti(rRealShip.CannonsQuantity);
        refShip.CannonsQuantityMin = sti(rRealShip.CannonsQuantityMin);
        refShip.CannonDiff = iCannonDiff;

        for (i = 0; i < sti(rRealShip.cannonr); i++)
        {
            attr = "c" + i;
            refShip.Cannons.Borts.cannonr.damages.(attr) = 0.0;
            if (iCannonDiff > 0 && i >= sti(rRealShip.cannonr) - iCannonDiff)
            {
                refShip.Cannons.Borts.cannonr.damages.(attr) = 2.0;
            }
        }
        for (i = 0; i < sti(rRealShip.cannonl); i++)
        {
            attr = "c" + i;
            refShip.Cannons.Borts.cannonl.damages.(attr) = 0.0;
            if (iCannonDiff > 0 && i >= sti(rRealShip.cannonl) - iCannonDiff)
            {
                refShip.Cannons.Borts.cannonl.damages.(attr) = 2.0;
            }
        }
        for (i = 0; i < sti(rRealShip.cannonf); i++)
        {
            attr = "c" + i;
            refShip.Cannons.borts.cannonf.damages.(attr) = 0.0;
        }
        for (i = 0; i < sti(rRealShip.cannonb); i++)
        {
            attr = "c" + i;
            refShip.Cannons.borts.cannonb.damages.(attr) = 0.0;
        }

        rRealShip.Cannons = sti(refShip.CannonsQuantityMax) - iCannonDiff * 2;
        rRealShip.CannonsQuantity = sti(rRealShip.Cannons);
        rRealShip.CannonDiff = iCannonDiff;
        refShip.Cannons = sti(rRealShip.Cannons);
        // <--- собственно сам рэндом стволов

        if (!CheckAttribute(rRealShip, "QuestShip"))
        {
            rRealShip.Bonus_Capacity = makeint((sti(rRealShip.Capacity) * iCannonDiff) / (15 * iDiffClass));
            rRealShip.Bonus_HP = makeint((sti(rRealShip.HP) * iCannonDiff) / (15 * iDiffClass));
            rRealShip.Bonus_SpeedRate = (stf(rRealShip.SpeedRate) * iCannonDiff) / (15 * iDiffClass);
            rRealShip.Bonus_TurnRate = (stf(rRealShip.TurnRate) * iCannonDiff) / (15 * iDiffClass);

            rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + Кdckyrd * (frandSmall(stf(rRealShip.SpeedRate) / 5.0) - stf(rRealShip.SpeedRate) / 10.0);
            rRealShip.TurnRate = stf(rRealShip.TurnRate) + Кdckyrd * (frandSmall(stf(rRealShip.TurnRate) / 5.0) - stf(rRealShip.TurnRate) / 10.0);
            rRealShip.HP = sti(rRealShip.HP) + makeint(Кdckyrd * (rand(makeint(sti(rRealShip.HP) / 5)) - makeint(sti(rRealShip.HP) / 10)));
            rRealShip.WindAgainstSpeed = stf(rRealShip.WindAgainstSpeed) + Кdckyrd * (frandSmall(stf(rRealShip.WindAgainstSpeed) / 5.0) - stf(rRealShip.WindAgainstSpeed) / 10.0);
        }
    }

    if (!CheckAttribute(rRealShip, "QuestShip"))
    {
        rRealShip.Capacity = sti(rRealShip.Capacity) + makeint(Кdckyrd * (rand(makeint(sti(rRealShip.Capacity) / 4)) - makeint(sti(rRealShip.Capacity) / 8)));
        rRealShip.OptCrew = makeint(sti(rRealShip.OptCrew) + Кdckyrd * (rand(makeint(sti(rRealShip.OptCrew) / 3)) - makeint(sti(rRealShip.OptCrew) / 6)));
        rRealShip.MaxCrew = makeint(sti(rRealShip.OptCrew) * 1.25 + 0.5); // 25% перегруза
        rRealShip.MinCrew = makeint(sti(rRealShip.MinCrew) + Кdckyrd * (rand(makeint(sti(rRealShip.MinCrew) / 3)) - makeint(sti(rRealShip.MinCrew) / 6)));
        rRealShip.Weight = sti(rRealShip.Weight) + makeint(Кdckyrd * (rand(sti(rRealShip.Weight) / 20) - rand(sti(rRealShip.Weight) / 20)));
    }

    // to_do del -->
    rRealShip.BoardingCrew = 0;
    rRealShip.GunnerCrew = 0;
    rRealShip.CannonerCrew = 0;
    rRealShip.SailorCrew = sti(rRealShip.OptCrew);
    // to_do del <--

    if (sti(rRealShip.CannonsQuantityMin) > 0) // баркасы не учитываем
    {
        if (sti(rRealShip.CannonsQuantityMax) == sti(rRealShip.CannonsQuantity)) // это в основном квестовые корабли, но мало ли .....
        {
            rRealShip.Capacity = sti(rRealShip.Capacity) + makeint(sti(rRealShip.Capacity) / 5);
            rRealShip.Tuning.Capacity = true;
        }
    }

    if (!CheckAttribute(rRealShip, "QuestShip"))
    {
        rRealShip.Capacity = sti(rRealShip.Capacity) + sti(rRealShip.Bonus_Capacity);
        rRealShip.HP = sti(rRealShip.HP) + sti(rRealShip.Bonus_HP);
        rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + stf(rRealShip.Bonus_SpeedRate);
        rRealShip.TurnRate = stf(rRealShip.TurnRate) + stf(rRealShip.Bonus_TurnRate);
    }

    rRealShip.BaseHP = sti(rRealShip.HP); // неизменяемая база

    int iDiffWeight = sti(rRealShip.Weight) - sti(rBaseShip.Weight);
    int iDiffCapacity = sti(rRealShip.Capacity) - sti(rBaseShip.Capacity);
    int iDiffMaxCrew = sti(rRealShip.MaxCrew) - sti(rBaseShip.MaxCrew);
    int iDiffMinCrew = sti(rRealShip.MinCrew) - sti(rBaseShip.MinCrew);
    float fDiffSpeedRate = stf(rRealShip.SpeedRate) - stf(rBaseShip.SpeedRate);
    int iDiffTurnRate = sti(rRealShip.TurnRate) - sti(rBaseShip.TurnRate);
    int iDiffHP = sti(rRealShip.HP) - sti(rBaseShip.HP);

    rRealShip.Price = (iDiffWeight + iDiffCapacity + iDiffMaxCrew * 2 + iDiffMinCrew + fDiffSpeedRate * 2 + iDiffTurnRate * 2 + iDiffHP) * 5 + sti(rRealShip.Price);

    if (sti(rRealShip.Price) <= 0)
        rRealShip.Price = 100;

    rRealShip.Stolen = isLock; // ворованность

    return iShip;
}
// -> ugeen

//Jason, генерация корабля с заданными статами; кроме числа орудий - всегда макс.
int GenerateShipHand(ref chr, int iType, int cc, int cp, int cr, int hp, int pr, float sr, float tr, float aw)
{
    aref refShip;

    int iShip = CreateBaseShip(iType);

    if (iShip == -1)
        return SHIP_NOTUSED;

    ref rRealShip = GetRealShip(iShip);
    ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
    rRealShip.ship.upgrades.hull = 1;  //всегда первый
    rRealShip.ship.upgrades.sails = 3; // всегда хлопок

    rRealShip.MaxCaliber = cc;
    rRealShip.SpeedRate = sr;
    rRealShip.TurnRate = tr;
    rRealShip.HP = hp;
    rRealShip.BaseHP = hp;
    rRealShip.WindAgainstSpeed = aw;
    rRealShip.Capacity = cp;
    rRealShip.OptCrew = cr;
    rRealShip.MaxCrew = makeint(sti(rRealShip.OptCrew) * 1.25 + 0.5);
    rRealShip.MinCrew = makeint(sti(rRealShip.MinCrew) + makeint(sti(rRealShip.MinCrew) / 4)) - makeint(sti(rRealShip.MinCrew) / 7);
    rRealShip.Weight = sti(rRealShip.Weight) + sti(rRealShip.Weight) / 20 - sti(rRealShip.Weight) / 20;
    rRealShip.Price = pr;

    makearef(refShip, chr.Ship);
    ResetShipCannonsDamages(chr);
    rRealShip.CannonsQuantityMax = sti(rRealShip.CannonsQuantity);

    refShip.CannonsQuantityMax = sti(rRealShip.CannonsQuantity);
    refShip.CannonsQuantityMin = sti(rRealShip.CannonsQuantityMin);
    refShip.CannonDiff = 0;

    rRealShip.Cannons = sti(refShip.CannonsQuantityMax);
    rRealShip.CannonsQuantity = sti(rRealShip.Cannons);
    refShip.Cannons = sti(rRealShip.Cannons);

    // to_do del -->
    rRealShip.BoardingCrew = 0;
    rRealShip.GunnerCrew = 0;
    rRealShip.CannonerCrew = 0;
    rRealShip.SailorCrew = sti(rRealShip.OptCrew);
    // to_do del <--

    if (sti(rRealShip.Price) <= 0)
        rRealShip.Price = 100;

    rRealShip.Stolen = false;

    return iShip;
}

int CreateBaseShip(int iBaseType)
{
    int iShip = FindFirstEmptyShip();

    if (iShip == -1)
    {
        trace("Can not find empty ship slot");
        return SHIP_NOTUSED;
    }

    ref rBaseShip = GetShipByType(iBaseType);
    ref rRealShip = GetRealShip(iShip);
    DeleteAttribute(rRealShip, "");
    CopyAttributes(rRealShip, rBaseShip);
    rRealShip.index = iShip;
    rRealShip.BaseType = iBaseType;
    if (!CheckAttribute(rRealShip, "ship.upgrades.hull")) // если задано в базе, то квестовый тип, не перебивать
    {
        rRealShip.ship.upgrades.hull = 1; //признак корабля теперь
    }
    rRealShip.ship.upgrades.sails = 1;

    rRealShip.BaseName = rRealShip.name;                      // запоминалка для нужд, тк далее идет "странное"
    if (rRealShip.name != "Fort" && rRealShip.name != "Boat") // не знаю зачем :(
    {
        rRealShip.name = rRealShip.name + "1"; // без этого вылет, но почему!!!!!!!!!!!!!!
                                               // выяснил - папка с моделью имеет на конце 1, вот и ответ
    }
    rRealShip.Stolen = 0; // ворованность - честный

    if (iArcadeSails == 0) // момент инерции ниже для тактики
    {
        rRealShip.InertiaAccelerationY = stf(rRealShip.InertiaAccelerationY) / 2.0;
    }

    return iShip;
}

void ResetShipCannonsDamages(ref refCharacter)
{
    aref refShip;

    makearef(refShip, refCharacter.Ship);
    refShip.Cannons.Borts = "";
    if (CheckAttribute(refShip, "Cannons.Borts.cannonf.damages"))
    {
        DeleteAttribute(refShip, "Cannons.Borts.cannonf.damages");
    }
    if (CheckAttribute(refShip, "Cannons.Borts.cannonb.damages"))
    {
        DeleteAttribute(refShip, "Cannons.Borts.cannonb.damages");
    }
    if (CheckAttribute(refShip, "Cannons.Borts.cannonl.damages"))
    {
        DeleteAttribute(refShip, "Cannons.Borts.cannonl.damages");
    }
    if (CheckAttribute(refShip, "Cannons.Borts.cannonr.damages"))
    {
        DeleteAttribute(refShip, "Cannons.Borts.cannonr.damages");
    }
}

void SetShipCannonsDamagesNull(ref refCharacter)
{
    int i;
    aref refShip;
    string attr;

    makearef(refShip, refCharacter.Ship);
    int nShipType = sti(refCharacter.Ship.type);
    if (nShipType == SHIP_NOTUSED)
    {
        trace("Character " + refCharacter.id + " have invalid ship!");
        return;
    }
    ref rRealShip = GetRealShip(nShipType);

    refShip.CannonsQuantityMax = sti(rRealShip.CannonsQuantity);
    refShip.CannonsQuantityMin = sti(rRealShip.CannonsQuantityMin);
    refShip.CannonDiff = 0;

    for (i = 0; i < sti(rRealShip.cannonr); i++)
    {
        attr = "c" + i;
        refShip.Cannons.Borts.cannonr.damages.(attr) = 0.0;
    }
    for (i = 0; i < sti(rRealShip.cannonl); i++)
    {
        attr = "c" + i;
        refShip.Cannons.Borts.cannonl.damages.(attr) = 0.0;
    }
    for (i = 0; i < sti(rRealShip.cannonf); i++)
    {
        attr = "c" + i;
        refShip.Cannons.borts.cannonf.damages.(attr) = 0.0;
    }
    for (i = 0; i < sti(rRealShip.cannonb); i++)
    {
        attr = "c" + i;
        refShip.Cannons.borts.cannonb.damages.(attr) = 0.0;
    }

    rRealShip.Cannons = sti(refShip.CannonsQuantityMax);
    rRealShip.CannonsQuantity = sti(rRealShip.Cannons);
    refShip.Cannons = sti(rRealShip.Cannons);
}

// Генерация корабля для верфи
int GenerateStoreShip(int iBaseType)
{
    int iShip = GenerateShip(iBaseType, 0); // честный

    if (iShip == -1)
    {
        return SHIP_NOTUSED;
    }

    ref rRealShip = GetRealShip(iShip);
    rRealShip.StoreShip = true; // корабль на верфи, трется отдельным методом

    return iShip;
}

// -> ugeen 25.01.09 -> для верфи
int GenerateStoreShipExt(int iBaseType, ref chr)
{
    int iShip = GenerateShipExt(iBaseType, 0, chr); // честный

    if (iShip == -1)
    {
        return SHIP_NOTUSED;
    }

    ref rRealShip = GetRealShip(iShip);
    rRealShip.StoreShip = true; // корабль на верфи, трется отдельным методом

    return iShip;
}
// <- ugeen

// переработка метода 26.05.06 boal
// идея: трем все корабли, где нет НПС-владельца, все галки пофиг
void EmptyAllFantomShips()
{
    int i;
    ref chr;
    // оптимальный код - два прохода, а не вложенный цикл. В начале всем сносим флаг удаляемости, потом проставляем, где есть НПС
    for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
    {
        DeleteAttribute(&RealShips[i], "lock");
    }
    // лодку ставим, тк он имеет индекс НПС за пределами MAX_CHARACTERS
    //RealShips[sti(Characters[BOAT_CHARACTER].ship.type)].lock = true;
    // теперь НПС-кэпы
    for (i = 0; i < MAX_CHARACTERS; i++)
    {
        chr = &Characters[i];
        if (CheckAttribute(chr, "ship.type") && chr.ship.type != SHIP_NOTUSED)
        {
            RealShips[sti(chr.ship.type)].lock = true;
        }
        // очистка для верфи
        if (CheckAttribute(chr, "shipyard"))
        {
            FreeShipFromShipyard(chr);
        }
    }
    for (i = FANTOM_CHARACTERS; i < TOTAL_CHARACTERS; i++) // фантомы в море
    {
        chr = &Characters[i];
        if (CheckAttribute(chr, "ship.type") && chr.ship.type != SHIP_NOTUSED)
        {
            RealShips[sti(chr.ship.type)].lock = true;
        }
        else
        {
            InitCharacter(&Characters[i], i); //ugeen : чистим нафиг все атрибуты пустых фантомов (переиничиваем)
        }
    }
    // теперь сборка мусора
    for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
    {
        if (!CheckAttribute(&RealShips[i], "lock") && !CheckAttribute(&RealShips[i], "StoreShip")) // на верфи корабли не трем
        {
            DeleteAttribute(&RealShips[i], "");
        }
    }
}

int GetRealShipsCount()
{ // метод для отладки
    int result = 0;

    for (int i = 0; i < REAL_SHIPS_QUANTITY; i++)
    {
        if (checkAttribute(&RealShips[i], "name"))
        {
            result++;
        }
    }

    return result;
}

// поиск пустого слота
int FindFirstEmptyShip()
{
    for (int i = 0; i < REAL_SHIPS_QUANTITY; i++)
    {
        if (!checkAttribute(&RealShips[i], "name"))
        {
            return i;
        }
    }

    return -1;
}

float FindShipSpeed(aref refCharacter)
{
    if (!CheckAttribute(refCharacter, "Ship.type"))
    {
        trace("Character " + refCharacter.id + " have no ship!");
        return 0.0;
    }
    int nShipType = sti(refCharacter.ship.type);
    if (nShipType == SHIP_NOTUSED)
    {
        trace("Character " + refCharacter.id + " have invalid ship!");
        return 1.0;
    }
    ref rShip = GetRealShip(nShipType);

    float fMaxSpeedZ = stf(rShip.SpeedRate); // базовая скорость
    float fShipHp = stf(refCharacter.ship.hp);
    float fShipMaxHp = stf(rShip.HP);
    float fSpeedFromHp = fShipHp / fShipMaxHp;
    fSpeedFromHp = 0.8 + fSpeedFromHp * 0.3;

    if (fSpeedFromHp > 1.0) // некий запас перед снижением скорости
    {
        fSpeedFromHp = 1.0;
    }

    fMaxSpeedZ = fMaxSpeedZ * AIShip_isPerksUse(CheckCharacterPerk(refCharacter, "MapMaker"), 1.0, 1.05) * isEquippedArtefactUse(refCharacter, "obereg_9", 1.0, 1.15);

    float fSailsDamage = stf(refCharacter.ship.sp);

    float fTRFromSailDamage = Bring2Range(0.1, 1.0, 0.1, 100.0, fSailsDamage); //0.3

    float fTRFromShipState = fSpeedFromHp * fTRFromSailDamage;

    float fLoad = Clampf(stf(refCharacter.Ship.Cargo.Load) / stf(rShip.Capacity));
    float fTRFromWeight = Clampf(1.03 - stf(rShip.SpeedDependWeight) * fLoad);
    float fTRFromSkill = SpeedBySkill(refCharacter);
    // от команды
    float fCrewMax = stf(rShip.MaxCrew);
    float fCrewOpt = stf(rShip.OptCrew);
    float fCrewCur = stf(refCharacter.Ship.Crew.Quantity);
    if (fCrewCur > fCrewMax)
    {
        fCrewCur = fCrewMax;
    }
    float fTRFromPeople;
    fTRFromPeople = 0.85 + ((GetCrewExp(refCharacter, "Sailors") * fCrewCur) / (fCrewOpt * GetCrewExpRate())) * 0.15;
    if (fTRFromPeople > 1)
        fTRFromPeople = 1;

    fMaxSpeedZ = fMaxSpeedZ * fTRFromWeight * fTRFromSkill * fTRFromShipState * fTRFromPeople;

    return fMaxSpeedZ;
}

float SpeedBySkill(aref refCharacter)
{
    float fSpeedPerk;

    float fSkill = GetSummonSkillFromNameToOld(refCharacter, SKILL_SAILING);
    float fTRFromSkill = 0.7 + (0.03 * fSkill);

    fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "ShipSpeedUp"), 1.0, 1.15); //slib
    fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "SailingProfessional"), fSpeedPerk, 1.20);

    return fTRFromSKill * fSpeedPerk;
}

float FindShipWindAgainstSpeed(aref refCharacter)
{
    if (!CheckAttribute(refCharacter, "Ship.type"))
    {
        trace("Character " + refCharacter.id + " have no ship!");
        return 0.0;
    }
    int nShipType = sti(refCharacter.ship.type);
    if (nShipType == SHIP_NOTUSED)
    {
        trace("Character " + refCharacter.id + " have invalid ship!");
        return 1.0;
    }
    ref rShip = GetRealShip(nShipType);

    float fWindAgainstSpeed = stf(rShip.WindAgainstSpeed) * isEquippedArtefactUse(refCharacter, "obereg_11", 1.0, 1.15);

    return fWindAgainstSpeed;
}

float FindShipTurnRate(aref refCharacter)
{
    if (!CheckAttribute(refCharacter, "Ship.type"))
    {
        trace("Character " + refCharacter.id + " have no ship!");
        return 0.0;
    }
    int nShipType = sti(refCharacter.ship.type);
    if (nShipType == SHIP_NOTUSED)
    {
        trace("Character " + refCharacter.id + " have invalid ship!");
        return 1.0;
    }
    ref rShip = GetRealShip(nShipType);

    float fShipHp = stf(refCharacter.ship.hp);
    float fShipMaxHp = stf(rShip.HP);
    float fSpeedFromHp = fShipHp / fShipMaxHp;
    fSpeedFromHp = 0.7 + fSpeedFromHp * 0.3;

    float fLoad = Clampf(stf(refCharacter.Ship.Cargo.Load) / stf(rShip.Capacity));
    float fTRFromWeight;
    if (iArcadeSails == 1)
    {
        fTRFromWeight = Clampf(1.03 - stf(rShip.TurnDependWeight) * fLoad);
    }
    else
    {
        fTRFromWeight = Clampf(1.03 - 2.0 * stf(rShip.TurnDependWeight) * fLoad); // влияние веса больше
    }
    // не реализовано, всегда 1 float fTRFromSpeed = 1.0 - stf(rShip.TurnDependSpeed);
    // от команды
    //float fCrewMin = stf(rShip.MinCrew);
    float fCrewMax = stf(rShip.MaxCrew);
    float fCrewOpt = stf(rShip.OptCrew);
    float fCrewCur = stf(refCharacter.Ship.Crew.Quantity);
    if (fCrewCur > fCrewMax)
    {
        fCrewCur = fCrewMax;
    }
    float fTRFromPeople;
    if (iArcadeSails == 1)
    {
        fTRFromPeople = 0.3 + ((GetCrewExp(refCharacter, "Sailors") * fCrewCur) / (fCrewOpt * GetCrewExpRate())) * 0.7;
    }
    else
    {
        fTRFromPeople = 0.05 + ((GetCrewExp(refCharacter, "Sailors") * fCrewCur) / (fCrewOpt * GetCrewExpRate())) * 0.95;
    }
    if (fTRFromPeople > 1)
        fTRFromPeople = 1;

    float fTRFromSKill = TurnBySkill(refCharacter);

    float fTRFromSailDamage = Bring2Range(0.05, 1.0, 0.1, 100.0, stf(refCharacter.ship.sp));

    float fTurn = fTRFromWeight * fTRFromSkill * fTRFromPeople * fTRFromSailDamage * fSpeedFromHp * isEquippedArtefactUse(refCharacter, "obereg_10", 1.0, 1.15);

    fTurn = fTurn * isEquippedArtefactUse(refCharacter, "amulet_5", 1.0, 0.9); // гаденыш Согбо belamour

    if (CheckAttribute(refCharacter, "Ship.hulls.baller_destroyed"))
        fTurn *= 0.3; // потеряли руль - уменьшаем маневренность
    //Log_info(refCharacter.id + "  " + fTurn);
    return fTurn;
}

float TurnBySkill(aref refCharacter)
{
    float fSkill = GetSummonSkillFromNameToOld(refCharacter, SKILL_SAILING);
    float fTRFromSKill;

    if (iArcadeSails == 1)
    {
        fTRFromSKill = 0.5 + (0.05 * fSkill);
    }
    else
    {
        fTRFromSKill = 0.3 + (0.07 * fSkill);
    }

    float fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "ShipTurnRateUp"), 1.0, 1.15); //slib
    fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "SailingProfessional"), fSpeedPerk, 1.20);
    float fFastTurn180 = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "Turn180"), 1.0, 4.0);

    return fTRFromSKill * fSpeedPerk * fFastTurn180;
}

int GetCannonsNum(aref chr)
{
    int nShipType = sti(chr.ship.type);
    ref refBaseShip = GetRealShip(nShipType);

    int iCannons = GetBortIntactCannonsNum(chr, "cannonf", sti(refBaseShip.fcannon)) +
                   GetBortIntactCannonsNum(chr, "cannonb", sti(refBaseShip.bcannon)) +
                   GetBortIntactCannonsNum(chr, "cannonl", sti(refBaseShip.lcannon)) +
                   GetBortIntactCannonsNum(chr, "cannonr", sti(refBaseShip.rcannon));
    return iCannons;
}

int GetBortCannonsBaseQty(ref chr, string sBort)
{
    int nShipType = sti(chr.ship.type);
    ref rRealShip = GetRealShip(nShipType);
    ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));

    int iCannons = sti(rBaseShip.(sBort));
    return iCannons;
}

int GetBortCannonsQty(aref chr, string sBort)
{
    int iCannonsMax = GetBortCannonsQtyMax(chr, sBort);
    return GetBortIntactCannonsNum(chr, sBort, iCannonsMax);
}

///////////////////////  ВЕРФИ //////////////////////
void SetShipyardStore(ref NPChar)
{
    int iTest_ship, i;
    string attrName;

    if (CheckAttribute(NPChar, "shipyard"))
        return; // еще есть корабли с того раза

    SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // дата заполнения верфи

    if (bBettaTestMode)
    {
        for (i = 1; i <= SHIP_TYPES_QUANTITY; i++)
        {
            attrName = "ship" + i;
            FillShipParamShipyard(NPChar, GenerateStoreShipExt(i - 1, NPChar), attrName);
        }
        return;
    }

    if (sti(NPChar.nation) == ENGLAND || sti(NPChar.nation) == FRANCE || sti(NPChar.nation) == SPAIN || sti(NPChar.nation) == HOLLAND)
    {
        FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1");

        iTest_ship = rand(2);
        if (iTest_ship == 1)
            FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_WAR_TARTANE, NPChar), "ship2");
        if (iTest_ship == 2)
            FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship2");

        iTest_ship = rand(2);
        if (iTest_ship == 1)
            FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship3");
        if (iTest_ship == 2)
            FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SLOOP, NPChar), "ship3");

        iTest_ship = rand(3);
        if (iTest_ship == 1)
            FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SLOOP, NPChar), "ship4");
        if (iTest_ship == 2)
            FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship4");
        if (iTest_ship == 3)
            FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CAREERLUGGER, NPChar), "ship4");

        if (sti(PChar.rank) > 1)
        {
            iTest_ship = rand(4);
            if (iTest_ship == 1)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONER, NPChar), "ship5");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BARQUE, NPChar), "ship5");

            iTest_ship = rand(4);
            if (iTest_ship == 1)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONER, NPChar), "ship6");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BARQUE, NPChar), "ship6");
        }

        if (sti(PChar.rank) > 3)
        {
            iTest_ship = rand(6);
            if (iTest_ship == 1)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CARAVEL, NPChar), "ship8");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SHNYAVA, NPChar), "ship8");

            iTest_ship = rand(6);
            if (iTest_ship == 1)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FLEUT, NPChar), "ship9");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CARAVEL, NPChar), "ship9");

            iTest_ship = rand(6);
            if (iTest_ship == 1)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FLEUT, NPChar), "ship10");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CARAVEL, NPChar), "ship10");
            if (iTest_ship == 3)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BARKENTINE, NPChar), "ship10");
            if (iTest_ship == 4)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SHNYAVA, NPChar), "ship10");
        }

        if (sti(PChar.rank) > 5)
        {
            iTest_ship = rand(8);
            if (iTest_ship == 1 && sti(NPChar.nation) == ENGLAND)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIG, NPChar), "ship11");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FLEUT, NPChar), "ship11");
            if (iTest_ship == 3)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BARKENTINE, NPChar), "ship11");
            if (iTest_ship == 4 && sti(NPChar.nation) == FRANCE)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONER_W, NPChar), "ship11");
            if (iTest_ship == 5 && sti(NPChar.nation) == HOLLAND)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONER_W, NPChar), "ship11");

            iTest_ship = rand(8);
            if (iTest_ship == 1 && sti(NPChar.nation) == ENGLAND)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIG, NPChar), "ship12");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_L, NPChar), "ship12");
            if (iTest_ship == 3 && sti(NPChar.nation) == SPAIN)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIGANTINE, NPChar), "ship12");
            if (iTest_ship == 4 && sti(NPChar.nation) == FRANCE)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONER_W, NPChar), "ship12");
            if (iTest_ship == 5 && sti(NPChar.nation) == HOLLAND)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONER_W, NPChar), "ship12");

            iTest_ship = rand(8);
            if (iTest_ship == 1 && sti(NPChar.nation) == ENGLAND)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIG, NPChar), "ship13");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_L, NPChar), "ship13");
            if (iTest_ship == 3 && sti(NPChar.nation) == SPAIN)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIGANTINE, NPChar), "ship13");
            if (iTest_ship == 4 && sti(NPChar.nation) == FRANCE)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONER_W, NPChar), "ship13");
            if (iTest_ship == 5 && sti(NPChar.nation) == HOLLAND)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONER_W, NPChar), "ship13");
        }

        if (sti(PChar.rank) > 8)
        {
            iTest_ship = rand(30);
            if (iTest_ship == 1)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_L, NPChar), "ship14");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CORVETTE, NPChar), "ship14");
            if (iTest_ship == 3 && sti(NPChar.nation) == FRANCE)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CORVETTE, NPChar), "ship14");
            if (iTest_ship == 4)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CARACCA, NPChar), "ship14");

            if (iTest_ship == 5 && sti(NPChar.nation) == SPAIN)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_XebekVML, NPChar), "ship14");
            if (iTest_ship == 6 && sti(NPChar.nation) == HOLLAND)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_XebekVML, NPChar), "ship14");

            if (iTest_ship == 7 && sti(NPChar.nation) == SPAIN)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_POLACRE, NPChar), "ship14");
            if (iTest_ship == 6 && sti(NPChar.nation) == FRANCE)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_POLACRE, NPChar), "ship14");

            iTest_ship = rand(40);
            if (iTest_ship == 1 && sti(NPChar.nation) == SPAIN)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_H, NPChar), "ship15");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PINNACE, NPChar), "ship15");
            if (iTest_ship == 3 && sti(NPChar.nation) == ENGLAND)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CORVETTE, NPChar), "ship15");
            if (iTest_ship == 4 && sti(NPChar.nation) == FRANCE)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CORVETTE, NPChar), "ship15");

            if (iTest_ship == 5 && sti(NPChar.nation) == SPAIN)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_XebekVML, NPChar), "ship15");
            if (iTest_ship == 6 && sti(NPChar.nation) == HOLLAND)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_XebekVML, NPChar), "ship15");

            if (iTest_ship == 7 && sti(NPChar.nation) == SPAIN)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_POLACRE, NPChar), "ship15");
            if (iTest_ship == 6 && sti(NPChar.nation) == FRANCE)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_POLACRE, NPChar), "ship15");
        }
        if (sti(PChar.rank) > 12)
        {
            iTest_ship = rand(30);
            if (iTest_ship == 1)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PINNACE, NPChar), "ship16");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_NAVIO, NPChar), "ship16");
            if (iTest_ship == 3)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_EASTINDIAMAN, NPChar), "ship16");
            if (iTest_ship == 4 && sti(NPChar.nation) == SPAIN)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_H, NPChar), "ship16");
            if (iTest_ship == 5 && sti(NPChar.nation) == ENGLAND)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATE, NPChar), "ship16");
            if (iTest_ship == 6 && sti(NPChar.nation) == FRANCE)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATE, NPChar), "ship16");
            if (iTest_ship == 7 && sti(NPChar.nation) == FRANCE)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CORVETTE, NPChar), "ship16");
            if (iTest_ship == 8)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATE_H, NPChar), "ship16");
        }
    }
    else
    {
        iTest_ship = rand(2);
        if (iTest_ship == 1)
            FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_WAR_TARTANE, NPChar), "ship2");
        if (iTest_ship == 2)
            FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship2");

        iTest_ship = rand(2);
        if (iTest_ship == 1)
            FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship3");
        if (iTest_ship == 2)
            FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SLOOP, NPChar), "ship3");

        iTest_ship = rand(3);
        if (iTest_ship == 1)
            FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SLOOP, NPChar), "ship4");
        if (iTest_ship == 2)
            FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship4");

        if (sti(PChar.rank) > 5)
        {
            iTest_ship = rand(8);
            if (iTest_ship == 1)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIG, NPChar), "ship11");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONER_W, NPChar), "ship11");

            iTest_ship = rand(8);
            if (iTest_ship == 1)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIG, NPChar), "ship12");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_L, NPChar), "ship12");
            if (iTest_ship == 3)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIGANTINE, NPChar), "ship12");
            if (iTest_ship == 4)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONER_W, NPChar), "ship12");

            iTest_ship = rand(8);
            if (iTest_ship == 1)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIG, NPChar), "ship13");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_L, NPChar), "ship13");
            if (iTest_ship == 3)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIGANTINE, NPChar), "ship13");
            if (iTest_ship == 4)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONER_W, NPChar), "ship13");
        }

        if (sti(PChar.rank) > 8)
        {
            iTest_ship = rand(30);
            if (iTest_ship == 1)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_L, NPChar), "ship14");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CORVETTE, NPChar), "ship14");

            iTest_ship = rand(40);
            if (iTest_ship == 1)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_H, NPChar), "ship15");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CORVETTE, NPChar), "ship15");
        }
        if (sti(PChar.rank) > 12)
        {
            iTest_ship = rand(30);
            if (iTest_ship == 1)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_NAVIO, NPChar), "ship16");
            if (iTest_ship == 2)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_EASTINDIAMAN, NPChar), "ship16");
            if (iTest_ship == 3)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_H, NPChar), "ship16");
            if (iTest_ship == 4)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATE, NPChar), "ship16");
            if (iTest_ship == 5)
                FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATE_H, NPChar), "ship16");
        }
    }
}

void FreeShipFromShipyard(ref NPChar)
{
    if (GetNpcQuestPastDayParam(NPChar, "shipyardDate") > (3 + rand(6)))
    {
        aref arDest, arImt;
        string sAttr;
        int iNum, i, iShip;
        makearef(arDest, NPChar.shipyard);
        iNum = GetAttributesNum(arDest);

        for (i = 0; i < iNum; i++)
        {
            arImt = GetAttributeN(arDest, i);
            iShip = sti(arImt.Type);                         //GetAttributeValue(arImt));
            DeleteAttribute(&RealShips[iShip], "StoreShip"); // можно тереть
        }
        DeleteAttribute(NPChar, "shipyard");
    }
}

void RemoveCannonsFromBortShipyard(ref chr, string sBort)
{
    int maxQty = GetBortCannonsQtyMax(chr, sBort);
    // нулим кол-во пушек на борту
    for (int i = 0; i < maxQty; i++)
    {
        string attr = "c" + i;
        chr.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0; // поломана на 100%, не палит, те нет ее
    }
    RecalculateCargoLoad(chr); // пересчет, тк пушки снялись
}

void RemoveAllCannonsShipyardShip(ref NPChar)
{
    RemoveCannonsFromBortShipyard(NPChar, "cannonf");
    RemoveCannonsFromBortShipyard(NPChar, "cannonb");
    RemoveCannonsFromBortShipyard(NPChar, "cannonr");
    RemoveCannonsFromBortShipyard(NPChar, "cannonl");
}

void FillShipParamShipyard(ref NPChar, int _iType, string _sShipNum)
{
    aref arTo, arFrom;

    DeleteAttribute(NPChar, "ship");
    NPChar.Ship.Type = _iType;

    SetRandomNameToShip(NPChar);

    SetBaseShipData(NPChar);
    SetCrewQuantity(NPChar, 0);
    if (sti(NPChar.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
    {
        NPChar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6; // to_do переделать на продажу без орудий вообще
    }
    RemoveAllCannonsShipyardShip(NPChar);  //нулим пушки .. сами покупайте какие надо
    DeleteAttribute(NPChar, "Ship.Cargo"); //пустой трюм
    SetGoodsInitNull(NPChar);
    RecalculateCargoLoad(NPChar);

    FillShipyardShipBack(NPChar, _sShipNum);
}

void FillShipyardShip(ref NPChar, string _sShipNum)
{
    aref arTo, arFrom;

    DeleteAttribute(NPChar, "ship");

    makearef(arFrom, NPChar.shipyard.(_sShipNum));
    NPChar.Ship = "";
    makearef(arTo, NPChar.Ship);
    CopyAttributes(arTo, arFrom);
}

void FillShipyardShipBack(ref NPChar, string _sShipNum)
{
    aref arTo, arFrom;

    DeleteAttribute(NPChar, "shipyard." + _sShipNum);
    NPChar.shipyard.(_sShipNum) = "";
    makearef(arTo, NPChar.shipyard.(_sShipNum));
    makearef(arFrom, NPChar.Ship);
    CopyAttributes(arTo, arFrom);
}

int GetSailsTuningPrice(ref _chr, ref _shipyard, float _rate)
{
    int st = GetCharacterShipType(_chr);
    ref shref;

    if (st == SHIP_NOTUSED)
        return 0;
    shref = GetRealShip(st);

    return makeint(stf(_shipyard.ShipCostRate) * sti(shref.Price) * _rate / 10) * 10; // кратно 10
}

// Warship 26.07.09 Вынес сюда
// int st - GetCharacterShipType(_character)
// ref _shipyard - референс на верфиста
int GetShipPriceByType(int st, ref _shipyard)
{
    if (st == SHIP_NOTUSED)
        return 0;
    ref shref = GetRealShip(st);

    return makeint(stf(_shipyard.ShipCostRate) * sti(shref.Price));
}

// Метод вернет цену продажи корабля персонажа с учетом всех скилов (для верфи)
int GetShipSellPrice(ref _chr, ref _shipyard)
{
    int st = GetCharacterShipType(_chr);
    int price = GetShipPriceByType(st, _shipyard);
    price = makeint(price - 1.5 * GetSailRepairCost(st, GetSailDamagePercent(_chr), _shipyard));
    price = makeint(price - 1.5 * GetHullRepairCost(st, GetHullDamagePercent(_chr), _shipyard));

    float nCommerce = GetSummonSkillFromNameToOld(GetMainCharacter(), SKILL_COMMERCE) + 0.001;

    if (CheckOfficersPerk(pchar, "AdvancedCommerce"))
    {
        nCommerce += 4;
    }
    else
    {
        if (CheckOfficersPerk(pchar, "BasicCommerce"))
        {
            nCommerce += 2;
        }
    }

    price = price - price / (nCommerce * 10.5);

    ref rRealShip = GetRealShip(st);

    if (sti(rRealShip.Stolen) == true) //проверка на ворованный
    {
        price = makeint(price / 3);
    }
    if (price < 100 && sti(_chr.Ship.Type) != SHIP_NOTUSED)
    {
        price = 100; // символическая цена в 100 песо
    }

    return price;
}

// Метод вернет цену покупки корабля персонажа с учетом всех скилов (для верфи)
int GetShipBuyPrice(int iType, ref _shipyard)
{
    // boal учет скилов торговли 22.01.2004 -->
    float nCommerce = GetSummonSkillFromNameToOld(GetMainCharacter(), SKILL_COMMERCE);

    if (CheckOfficersPerk(pchar, "AdvancedCommerce"))
    {
        nCommerce += 4;
    }
    else
    {
        if (CheckOfficersPerk(pchar, "BasicCommerce"))
        {
            nCommerce += 2;
        }
    }
    ref shref = GetRealShip(iType);
    return makeint(GetShipPriceByType(iType, _shipyard) + GetShipPriceByType(iType, _shipyard) / (nCommerce * 10)) * (7 - sti(shref.Class));
    // boal 22.01.2004 <--
}

int GetSailRepairCost(int shipType, int repairPercent, ref _shipyard)
{
    int SailRepairCoeff = makeint(3.0 + MOD_SKILL_ENEMY_RATE / 10.0);
    int shipPrice = GetShipPriceByType(shipType, _shipyard);
    if (shipPrice <= 0)
        return 0;
    ref shref = GetRealShip(shipType);
    if (CheckAttribute(shref, "Tuning.GhostShip"))
        SailRepairCoeff *= 3;
    float scost = SailRepairCoeff * (shipPrice * SAIL_COST_PERCENT + 99.0) / 100.0;
    return makeint((scost * repairPercent + 99.0) / 100.0);
}

int GetHullRepairCost(int shipType, int repairPercent, ref _shipyard)
{
    int HullRepairCoeff = makeint(3.0 + MOD_SKILL_ENEMY_RATE / 10.0);
    int shipPrice = GetShipPriceByType(shipType, _shipyard);
    if (shipPrice <= 0)
        return 0;
    ref shref = GetRealShip(shipType);
    if (CheckAttribute(shref, "Tuning.GhostShip"))
        HullRepairCoeff *= 3;
    float scost = HullRepairCoeff * (shipPrice * HULL_COST_PERCENT + 99.0) / 100.0;
    return makeint((scost * repairPercent + 99.0) / 100.0);
}

int GetSailDamagePercent(ref _chr)
{
    return 100 - MakeInt(GetSailPercent(_chr));
}

int GetHullDamagePercent(ref _chr)
{
    return 100 - MakeInt(GetHullPercent(_chr));
}
///////////////////////////////////////////////////////////////   ВЕРФИ  <--
// палуба от типа корабля
string GetShip_deck(ref chr, bool map2sea)
{
    string ret, add;

    int iType = sti(chr.Ship.Type);
    if (map2sea)
    {
        ret = "Ship_deck_";
    }
    else
    {
        ret = "Deck_Near_Ship_";
    }
    add = "Low"; // если нет типа
    if (iType != SHIP_NOTUSED)
    {
        ref rRealShip = GetRealShip(iType);

        add = rRealShip.DeckType;
    }
    if (chr.id == "GOT_boatsvanDega")
        return "Deck_Galeon_Ship"; // Jason
    return ret + add;
}

void MakeCloneShipDeck(ref chr, bool map2sea)
{
    ref rOrg, rClone;
    int iOrg, iClone;
    string locId, toLocId;

    locId = GetShip_deck(chr, map2sea);
    if (map2sea)
    {
        toLocId = "Ship_deck";
    }
    else
    {
        toLocId = "Deck_Near_Ship";
    }

    iOrg = FindLocation(locId);
    iClone = FindLocation(toLocId);

    makeref(rOrg, Locations[iOrg]);
    makeref(rClone, Locations[iClone]);

    DeleteAttribute(rClone, "");
    CopyAttributes(rClone, rOrg);
    rClone.id = toLocId;
    rClone.index = iClone;
}

void MakeCloneFortBoarding(string fromLocId)
{
    ref rOrg, rClone;
    int iOrg, iClone;
    string toLocId;

    toLocId = "BOARDING_FORT";

    iOrg = FindLocation(fromLocId);
    iClone = FindLocation(toLocId);

    makeref(rOrg, Locations[iOrg]);
    makeref(rClone, Locations[iClone]);

    DeleteAttribute(rClone, "");
    CopyAttributes(rClone, rOrg);
    rClone.id = toLocId;
    rClone.index = iClone;

    rClone.type = "fort_attack";
    LAi_LocationFantomsGen(rClone, false);
    DeleteAttribute(rClone, "reload");
    //это подкручивание другого файла локаторов. там нет goto, soldiers и пр. есть rld и дополн.сундуки
    if (rClone.models.always.locators == "fortV_locators")
    {
        rClone.models.always.locators = "fortV_lAttack";
        rClone.models.always.fortV = "fortV_attack";
    }
    else
    {
        rClone.models.always.locators = "fortVRight_lAttack";
        rClone.models.always.fortV = "fortVRight_attack";
    }
    rClone.boarding.locatorNum = 25;
    rClone.boarding = "false";
    rClone.boarding.nextdeck = "Boarding_fortyard"; // Jason
    rClone.image = "loading\FortShturm_" + rand(2) + ".tga";
}

int GetPortManPrice(int Price, ref NPChar)
{
    if (!CheckAttribute(NPChar, "PortManPrice"))
    {
        NPChar.PortManPrice = (0.06 + frnd() * 0.1);
    }
    return makeint(Price * stf(NPChar.PortManPrice) / 10) * 10;
}

// ugeen --> альтернативный расчет стоянки корабля в ПУ
int GetPortManPriceExt(ref NPChar, ref chref)
{
    /*  --> оставим для хардкорного патча если он будет, не вытирать!!!! 
    float fLeadership     = 1.5 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/120.0;     // учитываем авторитет
    float fCommerce     = 1.5 - GetSummonSkillFromName(pchar, SKILL_COMMERCE)/120.0;     // учитываем торговлю
    float fRelation     = 1.0;                                                             // учитываем  - родная нация или нет
    
    if(sti(NPChar.nation) == GetBaseHeroNation()) fRelation = 0.5;                         // если нация родная- снижаем цену в два раза
    int price = makeint(200 * MOD_SKILL_ENEMY_RATE * 1.56 * sqr(6.7 - sti(RealShips[sti(chref.Ship.Type)].Class)) * (1 + 0.5 * GetNationRelation2MainCharacter(sti(NPChar.nation))) * fRelation * fLeadership * fCommerce);
*/
    int price = makeint(sti(RealShips[sti(chref.Ship.Type)].Price) * (5 + MOD_SKILL_ENEMY_RATE) * (3 + GetNationRelation2MainCharacter(sti(NPChar.nation))) / 360.0);

    return price;
}
//<-- альтернативный расчет стоянки корабля в ПУ

// Warship 31.05.09 Установка на корабль персонажа определенного паруса
// Путь относительно папки Textures
bool SetShipSailsFromFile(ref _char, String _sailTexturePath)
{
    ref realShip;
    int shipType = sti(_char.Ship.Type);

    if (shipType == SHIP_NOTUSED) // Есть ли корабль вообще
    {
        return false;
    }

    realShip = GetRealShip(shipType);

    realShip.EmblemedSails.normalTex = _sailTexturePath;

    return true;
}

string GetLocalShipAttrib(ref ship, string attrib)
{
    if (CheckAttribute(ship, attrib))
        return ship.(attrib);
    return "";
}

bool CheckShipAttribute(ref ship, string attrib)
{
    if (CheckAttribute(ship, attrib))
        return true;
    return false;
}

string GetBaseShipParamFromType(int iType, string _param)
{
    object rBaseShip = GetShipByType(iType);
    return rBaseShip.(_param);
}

int GetShipMastsQuantity(ref chr)
{
    if (!CheckAttribute(chr, "ship.type"))
        return 0;
    int iShip = sti(chr.ship.type);
    if (iShip == SHIP_NOTUSED)
        return 0;
    if (CheckAttribute(chr, "Ship.MastsQty"))
        return sti(chr.Ship.MastsQty);
    else
    {
        if (CheckAttribute(chr, "Ship.Masts"))
        {
            aref arMasts;
            makearef(arMasts, chr.Ship.Masts);
            return GetAttributesNum(arMasts);
        }
    }
    return 0;
}

int GetShipFallMastsQuantity(ref chr)
{
    int ret = 0;
    if (!CheckAttribute(chr, "ship.type"))
        return 0;
    int iShip = sti(chr.ship.type);
    if (iShip == SHIP_NOTUSED)
        return 0;
    if (CheckAttribute(chr, "Ship.Masts"))
    {
        aref arMasts;
        makearef(arMasts, chr.Ship.Masts);
        int nMasts = GetAttributesNum(arMasts);
        for (int i = 0; i < nMasts; i++)
        {
            string sMast = GetAttributeName(GetAttributeN(arMasts, i));
            if (chr.Ship.Masts.(sMast) == 1)
                ret++;
        }
    }
    return ret;
}
