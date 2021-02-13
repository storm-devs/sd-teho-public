// Тичингиту - индеец-офицер
void ProcessDialogEvent()
{
    ref NPChar, sld, rItm, rItem;
    aref Link, NextDiag, rType;
    int i;
    string sAttr, sGun, sBullet, attrL;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    sAttr = Dialog.CurrentNode;
    if (findsubstr(sAttr, "SetGunBullets1_", 0) != -1)
    {
        i = findsubstr(sAttr, "_", 0);
        NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
        Dialog.CurrentNode = "SetGunBullets2";
    }

    switch (Dialog.CurrentNode)
    {
    case "First time":
        dialog.text = "Вы что-то хотели?";
        link.l1 = "Да нет, ничего.";
        link.l1.go = "exit";
        NextDiag.TempNode = "First time";
        break;

    case "Tichingitu":
        dialog.text = "Что ты хотеть, бледнолицый? У Тичингиту нет для тебя слов.";
        link.l1 = "Тебя зовут Тичингиту? Хм. Послушай, воин, я пришел не для того, чтобы пялить на тебя глаза, а чтобы спросить: зачем ты полез в дом к этому толстяку?";
        link.l1.go = "Tichingitu_1";
        break;

    case "Tichingitu_1":
        dialog.text = "";
        link.l1 = "Молчишь? Глупо. Тебя повесят за воровство и всего дел. Расскажи, зачем ты совершил этот поступок - быть может, я смогу тебе помочь.";
        link.l1.go = "Tichingitu_2";
        break;

    case "Tichingitu_2":
        dialog.text = "Тичингиту прийти в город бледнолицых через много-много дорог, через большой вода, из страны больших лесов и болот. Тичингиту устать и хотеть есть. Тичингиту умирать от голод. Никто не хотеть помочь Тичингиту, кричать - вон, краснокожий собака. Хозяин трактира выгнать индеец, как шелудивый пес. Тичингиту хотеть есть.";
        link.l1 = "Черт побери, но зачем ты тогда явился в это поселение из... своего леса?";
        link.l1.go = "Tichingitu_3";
        break;

    case "Tichingitu_3":
        dialog.text = "Тичингиту изгнать из его родной племя. Тичингиту ссориться шаман племя, шаман сказать вождь, шаман проклинать Тичингиту - Тичингиту уйти племя, прочь-прочь от родной становище. Тичингиту нет дома, нет оружия, нет ничего.";
        link.l1 = "Да, уж, не повезло тебе. Ну и зачем ты поссорился со своими людьми?";
        link.l1.go = "Tichingitu_4";
        break;

    case "Tichingitu_4":
        dialog.text = "Шаман наше племя - злой человек. Он сказать - мой жена вселиться злой дух, жена должен умереть. Мой жена просто болеть, дух не вселяться. Я лечить жена, шаман убить жена. Тичингиту встать против шаман, все встать против Тичингиту, Тичингиту уходить.";
        link.l1 = "Ты пытался спасти жену? Из-за этого тебя изгнали из деревни?";
        link.l1.go = "Tichingitu_5";
        break;

    case "Tichingitu_5":
        dialog.text = "Так, бледнолицый. У Тичингиту не быть выбор - или украсть, или умереть голод...";
        link.l1 = "Вот незадача... Из-за каких-то нескольких жалких монет на кусок еды вешать человека... Тичингиту, я попробую помочь тебе. Я знаю Фадея - того здоровяка, в дом которого ты залез. Может, мне удасться что-то сделать... Я сейчас поговорю с комендантом.";
        link.l1.go = "exit";
        NextDiag.TempNode = "Tichingitu_wait";
        pchar.questTemp.Sharlie.Tichingitu = "commandante";
        break;

    case "Tichingitu_wait":
        dialog.text = "Тичингиту ждать. Индеец не бояться смерти. Шаман проклясть Тичингиту - Тичингиту должен умереть.";
        link.l1 = "Еще не все потеряно. Я пытаюсь помочь...";
        link.l1.go = "exit";
        NextDiag.TempNode = "Tichingitu_wait";
        break;

    case "Tichingitu_6":
        dialog.text = "Тичингиту ждать. Индеец не бояться смерти. Шаман проклясть Тичингиту - Тичингиту должен умереть.";
        link.l1 = "Не будь таким пессимистом. Твои мытарства окончены. Я добился твоего освобождения.";
        link.l1.go = "Tichingitu_7";
        break;

    case "Tichingitu_7":
        dialog.text = "Бледнолицый шутить? Тичингиту свободен?";
        link.l1 = "Никаких шуток. Сейчас откроют твою камеру и выпустят тебя. Следуй за мной, я выведу тебя из тюрьмы.";
        link.l1.go = "Tichingitu_8";
        break;

    case "Tichingitu_8":
        DialogExit();
        chrDisableReloadToLocation = false;                                           //открыть локацию
        DoQuestReloadToLocation("BasTer_exittown", "rld", "aloc9", "TichingituFree"); // 170712
        pchar.quest.FreeTichingituOver.over = "yes";                                  //снять таймер
        break;

    case "Tichingitu_9":
        dialog.text = "";
        link.l1 = "Вот ты и снова на свободе. Гуляй, Тичингиту, смотри, не воруй и не попадайся больше! Лучше найди какую-нибудь индейскую деревню и живи со своими - не думаю, что они откажутся принять тебя.";
        link.l1.go = "Tichingitu_10";
        break;

    case "Tichingitu_10":
        dialog.text = "Тичингиту не идти. Господин спасти жизнь Тичингиту. Тичингиту оставаться. Жизнь Тичингиту принадлежит господину.";
        link.l1 = "Чего? Ты это о чем сейчас? Какой господин, какая жизнь? Ты разве не понял - ты свободен! Ступай!";
        link.l1.go = "Tichingitu_11";
        break;

    case "Tichingitu_11":
        dialog.text = "Индеец в долгу, белый господин. Тичингиту служить тебе верой и правдой. Тичингиту уметь сражаться. Тичингиту умереть в бою за свой господин. Он оставаться.";
        link.l1 = "Тьфу ты, черт... Да какой я тебе господин, Тичингиту? Я помог тебе не для того, чтобы превратить тебя в раба.";
        link.l1.go = "Tichingitu_12";
        break;

    case "Tichingitu_12":
        dialog.text = "Тичингиту не раб, белый господин. Тичингиту - свободный индеец. Тичингиту хотеть служить у тебя. Индеец уметь сражаться, любой пес умереть, прежде чем подойти к господин. Тичингиту уметь чистить и заряжать мушкет. Тичингиту уметь стрелять из мушкет.";
        link.l1 = "Хотя... Ты знаешь, Тичингиту, это неплохая идея. Мне нужны верные люди, а ты мне кажешься неплохим человеком. И из мушкета стрелять умеешь. Да и что ты будешь делать один? Опять попадешься на краже, тогда уж точно повесят... Хорошо, оставайся. Но учти: спокойной жизни со мной не будет.";
        link.l1.go = "Tichingitu_13";
        link.l2 = "Так, довольно. Ступай с миром, краснокожий брат. Да хранят тебя твои боги!";
        link.l2.go = "Tichingitu_exit";
        break;

    case "Tichingitu_exit":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10.0);
        npchar.lifeday = 0;
        DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
        break;

    case "Tichingitu_13":
        dialog.text = "Тичингиту не бояться ничего, белый господин. Тичингиту будет рад служить тебе. Тичингиту будет верен капитан до последний вздох.";
        link.l1 = "Хорошо. Добро пожаловать в команду, Тичингиту!";
        link.l1.go = "Tichingitu_hire";
        break;

    case "Tichingitu_hire":
        DialogExit();
        DeleteAttribute(npchar, "LifeDay");
        LAi_SetImmortal(npchar, false);
        npchar.quest.OfficerPrice = sti(pchar.rank) * 20;
        npchar.OfficerWantToGo.DontGo = true;
        npchar.CompanionDisable = true;
        npchar.loyality = MAX_LOYALITY;
        AddPassenger(pchar, npchar, false);
        SetCharacterRemovable(npchar, true);
        npchar.Payment = true;
        npchar.CanTakeMushket = true;
        LAi_SetOfficerType(npchar);
        NextDiag.CurrentNode = "Tichingitu_officer";
        LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
        SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
        DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
        break;

        //--> ----------------------------------- офицерский блок ------------------------------------------
    case "Tichingitu_officer":
        dialog.text = "Тичингиту слушать вас, капитан " + pchar.name + "!";
        if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
        {
            Link.l4 = "Тичингиту, я собираюсь отправиться в старый индейский город Тайясаль. Не буду скрывать: это крайне опасное путешествие, и более того - необычное: через телепортационный истукан. Ты... пойдешь со мной?";
            Link.l4.go = "tieyasal";
        }
        Link.l1 = "Слушай мой приказ!";
        Link.l1.go = "stay_follow";
        link.l2 = "Пока ничего. Вольно!";
        link.l2.go = "exit";
        NextDiag.TempNode = "Tichingitu_officer";
        break;

    case "stay_follow":
        dialog.Text = "Какие быть приказания?";
        if (CheckAttribute(npchar, "IsMushketer"))
        {
            Link.l4 = "Я хочу, чтобы ты держался на определенном расстоянии от цели.";
            Link.l4.go = "TargetDistance";
        }
        Link.l1 = "Стой здесь!";
        Link.l1.go = "Boal_Stay";
        Link.l2 = "Следуй за мной и не отставай!";
        Link.l2.go = "Boal_Follow";
        sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
        if (sGun != "")
        {
            rItm = ItemsFromID(sGun);
            if (CheckAttribute(NPChar, "chr_ai.bulletNum") && sti(NPChar.chr_ai.bulletNum) > 1)
            {
                Link.l3 = "Нужно изменить тип боеприпаса для твоего огнестрельного оружия.";
                Link.l3.go = "SetGunBullets";
            }
        }
        break;

    case "SetGunBullets":
        Dialog.Text = "Выбор типа боеприпаса:";
        sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
        rItm = ItemsFromID(sGun);
        makearef(rType, rItm.type);
        for (i = 0; i < sti(NPChar.chr_ai.bulletNum); i++)
        {
            sAttr = GetAttributeName(GetAttributeN(rType, i));
            sBullet = rItm.type.(sAttr).bullet;
            rItem = ItemsFromID(sBullet);
            attrL = "l" + i;
            Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
            Link.(attrL).go = "SetGunBullets1_" + i;
        }
        break;

    case "SetGunBullets2":
        i = sti(NPChar.SetGunBullets) + 1;
        sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
        rItm = ItemsFromID(sGun);
        sAttr = "t" + i;
        sBullet = rItm.type.(sAttr).bullet;
        LAi_SetCharacterUseBullet(NPChar, sBullet);
        LAi_GunSetUnload(NPChar);
        NextDiag.CurrentNode = NextDiag.TempNode;
        DeleteAttribute(NPChar, "SetGunBullets");
        DialogExit();
        break;

    case "Boal_Stay":
        Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
        AddDialogExitQuestFunction("LandEnc_OfficerStay");
        dialog.Text = "Есть изменить дислокация!";
        Link.l1 = "Вольно.";
        Link.l1.go = "Exit";
        Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;

    case "Boal_Follow":
        SetCharacterTask_FollowCharacter(Npchar, PChar);
        dialog.Text = "Есть изменить дислокация!";
        Link.l1 = "Вольно.";
        Link.l1.go = "Exit";
        break;

    //--> задать дистанцию стрельбы
    case "TargetDistance":
        dialog.text = "На какой именно, капитан? Указать Тичингиту в ярдах, но не больше, чем двадцать.";
        link.l1 = "";
        Link.l1.edit = 3;
        link.l1.go = "TargetDistance_1";
        break;

    case "TargetDistance_1":
        iTemp = sti(dialogEditStrings[3]);
        if (iTemp < 0)
        {
            dialog.text = "Капитан, простить Тичингиту, но я вас не понимать.";
            link.l1 = "Извини, ошибочка вышла...";
            link.l1.go = "exit";
            break;
        }
        if (iTemp == 0)
        {
            dialog.text = "Тичингиту быть стоять на месте, никуда не двигаться. Вы это хотеть, капитан?";
            link.l1 = "Да, именно это от тебя и требуется.";
            link.l1.go = "exit";
            npchar.MusketerDistance = 0;
            break;
        }
        if (iTemp > 20)
        {
            dialog.text = "Тичингиту не может встать от цель больше двадцать ярдов. Тогда он промахнуться.";
            link.l1 = "Хорошо, тогда держись на расстоянии в двадцать ярдов.";
            link.l1.go = "exit";
            npchar.MusketerDistance = 20.0;
            break;
        }
        dialog.text = "Тичингиту все понять. Тичингиту занимать позиция на указанный расстояние.";
        link.l1 = "Хорошо.";
        link.l1.go = "exit";
        npchar.MusketerDistance = iTemp;
        break;
        //<-- задать дистанцию стрельбы
        //<-- ----------------------------------- офицерский блок ----------------------------------------

        // на Тайясаль
    case "tieyasal":
        dialog.text = "Жизнь Тичингиту давно стать жизнью моего капитан. Индеец не забывать, что капитан сделать для Тичингиту. Тичингиту идти за ним, куда сказать капитан, без упрек и колебаний.";
        link.l1 = "Спасибо, друг Тичингиту! Я рад, что не ошибся в тебе.";
        link.l1.go = "tieyasal_1";
        break;

    case "tieyasal_1":
        dialog.text = "Когда мы отправляться?";
        link.l1 = "Немного позже. А пока мы подготовимся к походу.";
        link.l1.go = "tieyasal_2";
        break;

    case "tieyasal_2":
        DialogExit();
        AddQuestRecord("Tieyasal", "21");
        npchar.quest.Tieyasal = "teleport";
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;
    }
}