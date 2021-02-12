#define SAILS_COLOR_QUANTITY				9
#define SHIP_TYPES_QUANTITY					50
#define SHIP_TYPES_QUANTITY_WITH_FORT		51	// must be (SHIP_TYPES_QUANTITY + 1)

#define SHIP_TARTANE			0   // баркас			- 6-ой класс 	(SEFH)
#define SHIP_WAR_TARTANE		1	// тартана			- 6-ой класс	(SEFHP)

#define SHIP_BARQUE				2	// барк			- торговец 5-ый класс	(SEFH)
#define SHIP_SCHOONER			3	// торговая шхуна	- торговец 4-ый класс	(SEFH)
#define SHIP_BARKENTINE			4	// баркентина		- торговец 4-ый класс	(SEFH)
#define SHIP_SHNYAVA			5	// шнява			- торговец 4-ый класс	(SEFH)
#define SHIP_FLEUT				6	// флейт			- торговец 4-ый класс	(SEFH)
#define SHIP_CARAVEL			7	// каравелла		- торговец 3-ий класс	(SEFH)
#define SHIP_PINNACE			8	// пинасс			- торговец 3-ий класс	(SEFH)
#define SHIP_CARACCA			9	// каракка			- торговец 3-ий класс	(SEFH)
#define SHIP_NAVIO				10	// навио			- торговец 2-ой класс	(SEFH)
#define SHIP_EASTINDIAMAN		11	// ост-индец		- торговец 2-ой класс	(SEFH)

#define SHIP_CAREERLUGGER       12	// курьерский люггер	- военный 5-ый класс	(SEFH)
#define SHIP_LUGGER				13	// люггер			- военный 5-ый класс	(SEFHP)
#define SHIP_SLOOP				14	// шлюп			- военный 5-ый класс	(SEFHP)
#define SHIP_BRIGANTINE			15	// бригантина		- военный 4-ый класс	(SP)
#define SHIP_BRIG				16	// бриг			- военный 4-ый класс	(EP)
#define SHIP_SCHOONER_W			17	// военная шхуна	- военный 4-ый класс	(FHP)
#define SHIP_GALEON_L			18	// галеон			- военный 3-ий класс	(SEFHP)
#define SHIP_CORVETTE			19	// корвет			- военный 3-ий класс	(EFP)
#define SHIP_XebekVML			20	// шебека			- военный 3-ий класс	(SH)
#define SHIP_POLACRE			21	// полакр			- военный 3-ий класс	(SF)

#define SHIP_GALEON_H			22	// тяжелый галеон	- военный 2-ой класс	(SP)
#define SHIP_FRIGATE			23	// фрегат			- военный 2-ой класс	(EFH)
#define SHIP_FRIGATE_H			24	// тяжелый фрегат	- военный 2-ой класс	(SEFH)

#define SHIP_LINESHIP			25	// военный корабль	- военный 1-ый класс	(SEFHP)
#define SHIP_LSHIP_FRA			26	// линейный корабль	- военный 1-ый класс (Франция)	(F)
#define SHIP_LSHIP_HOL			27	// линейный корабль	- военный 1-ый класс (Голландия)	(H)
#define SHIP_LSHIP_SPA			28	// линейный корабль	- военный 1-ый класс (Испания)	(S)
#define SHIP_LSHIP_ENG			29	// линейный корабль	- военный 1-ый класс (Англия)	(E)

// квестовые
#define SHIP_MAYFANG			30 	// Мэйфэнг 			- легкая шебека			- 4-ый класс
#define SHIP_MIRAGE				31	// Мираж			- приватирский кеч	 	- 4-ый класс
#define SHIP_VALCIRIA			32	// Валькирия		- патрульный бриг	 	- 4-ый класс

#define SHIP_CORVETTE_QUEST		33	// Гриффондор		- малый фрегат			- 3-ий класс
#define SHIP_POLACRE_QUEST		34	// Тореро			- полакр		    	- 3-ий класс
#define SHIP_FRIGATE_L			35	// Фрегат "Акула"	- быстрый фрегат		- 2-ой класс

// --> квестовые - заглушки !!!!
#define SHIP_QUEST0				36  // квестовый №0 - 6-ый класс <-- специально для Михаила :)
#define SHIP_QUEST1				37  // квестовый №1 - 5-ый класс
#define SHIP_QUEST2             38  // квестовый №2 - 4-ый класс
#define SHIP_QUEST3             39  // квестовый №3 - 4-ый класс
#define SHIP_QUEST4             40  // квестовый №4 - 3-ый класс
#define SHIP_QUEST5				41  // квестовый №5 - 3-ый класс
#define SHIP_QUEST6				42  // квестовый №6 - 2-ый класс
#define SHIP_QUEST7				43  // квестовый №7 - 2-ый класс
#define SHIP_QUEST8				44  // квестовый №8 - 1-ый класс
// <-- квестовые - заглушки !!!!

#define SHIP_CURSED_FDM			45	// Проклятый Калеуче	- военный корабль		- 1-ый класс
#define SHIP_FDM				46	// Копия Калеуче	- военный корабль	    	- 1-ый класс

#define SHIP_LSHIP_QUEST		47	// "Реус де Сан-Педро" - линейный корабль		- 1-ый класс

#define SHIP_BOAT               48	// лодка у берега
#define SHIP_FORT               49	// форт

#define SHIP_NOTUSED			 1000
#define SHIP_NOTUSED_TYPE_NAME	"Not Used"
#define SHIP_NAME_NOTUSED		"Noname"

object  ShipsTypes[SHIP_TYPES_QUANTITY_WITH_FORT];  // RealShips
object	SailsColors[SAILS_COLOR_QUANTITY];

ref GetShipByType(int iType) { return &ShipsTypes[iType]; }  // пользовать GetRealShip
