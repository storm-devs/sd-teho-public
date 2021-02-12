#define GOLD					"gold"
#define GOLD_ITEM               "jewelry5"

//TEMP
#define BLADE_SABER				"blade_11"
#define BLADE_SHORT				"blade_05"// boal 27.03.2004
#define BLADE_NORMAL			"blade_12"// boal 27.03.2004
#define BLADE_LONG				"blade_07"// boal 27.03.2004

#define GUN_COMMON				"pistol1"
#define CHEAP_SPYGLASS			"spyglass1"
#define COMMON_SPYGLASS			"spyglass2"
#define GOOD_SPYGLASS			"spyglass3"
#define SUPERIOR_SPYGLASS		"spyglass4"
#define POTION					"potion1"
#define INVALID_SUIT			"NoSuit" // Warship 25.10.08

// items group id
#define GUN_ITEM_TYPE			"gun"		
#define BLADE_ITEM_TYPE			"blade"		
#define SPYGLASS_ITEM_TYPE		"spyglass"	
#define PATENT_ITEM_TYPE        "patent"	
#define CIRASS_ITEM_TYPE		"cirass"	
#define MAPS_ITEM_TYPE		    "maps"		
#define TOOL_ITEM_TYPE			"tool"		
#define TALISMAN_ITEM_TYPE 		"talisman"	
#define ITEM_SLOT_TYPE			"slot"		
#define SPECIAL_ITEM_TYPE		"special" 	// Jason, спецпредметы, не отн. к прочим группам
#define AMMO_ITEM_TYPE			"ammo" 		// Боеприпас

#define ITEM_SLOT1_TYPE			"slot1"		
#define ITEM_SLOT2_TYPE			"slot2"		
#define ITEM_SLOT3_TYPE			"slot3"	

#define ITEM_INDIAN				1
#define ITEM_AMULET				2
#define ITEM_OBEREG				3	
#define ITEM_TOTEM				4

#define SLOT_NOT_USED			""

#define ITEM_TRADE_NORMAL		0
#define ITEM_TRADE_JEWELRY		1
#define	ITEM_TRADE_POTION		2
#define ITEM_TRADE_AMMUNITION	3
#define ITEM_TRADE_ARTEFACT		4
#define ITEM_TRADE_MAP			5

// indexes for items` array
#define TOTAL_ITEMS				  1000 // Warship 08.05.09 - Новая система предметов
#define ITEMS_QUANTITY			  500  // не забываем менять номер
#define MAX_BUTTONS               64
#define RANDITEMS_QUANTITY    	  52
#define BUTTON_ACTIVATION_TIME	  1000
#define ITEMS_LAYER				  65549
#define MAX_LOADED_RANDITEMS      10
#define MAX_HANDLED_BOXES 		  25
#define ITEM_PROBABILITY		  0.5
#define OBJECTS_IN_BOX			  9
#define MAPS_IN_ATLAS			  23 // ugeen 21.06.09  -не забываем увеличивать при появлении новых карт 	

// blade defines - некоторые константы для клинков
// типы холодного оружия
#define FencingL			      0 // рапиры и шпаги - легкое оружие
#define FencingS			      1 // сабли - среднее оружие
#define FencingH    			  2 // палаши и тесаки - тяжелое оружие

// качественные группы
#define B_POOR                	  0 // плохое
#define B_ORDINARY                1 // обычное
#define B_GOOD                    2 // хорошее
#define B_EXCELLENT               3 // отличное
#define B_UNIQUE				  4 // уникальное

// целевые группы
#define TGT_QUEST                 0 // квестовое оружие
#define TGT_YANKEE                1 // рабы, бунтовщики, каторжники
#define TGT_NATIVE                2 // мезоамерика
#define TGT_MARGINAL              3 // маргиналы - низкуровневые пираты, граждане, бандиты
#define TGT_SOLDIER               4 // солдаты, пираты
#define TGT_OFFICER               5 // офицерское оружие, капитаны
#define TGT_PERSIAN               6 // индо-персидские клинки    

#define FencingL_MaxAttack        60.0    // максимальная атака для легих клинков
#define FencingS_MaxAttack        80.0    // максимальная атака для средних клинков
#define FencingH_MaxAttack        100.0   // максимальная атака для тяжелых клинков

object Items[TOTAL_ITEMS];
object RandItems[RANDITEMS_QUANTITY];