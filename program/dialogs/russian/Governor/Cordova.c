// дон Хуан де Кордова - генерал-губернатор испанских колоний
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What would you like?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}