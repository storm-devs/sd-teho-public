// espkk # ActiveMap 1.2 # 30/Mar/2017
// configuration file for ActiveMap

/* Show region boundaries on map
 * 0 - disabled
 * 1 - enabled
 */
#define SHOW_BOUNDARIES 1

/* Boundaries opacity(1-100) and RGB(0-255) settings
 * Used when SHOW_BOUNDARIES is set to 1
 */
#define BOUNDARIES_OPACITY  65

#define BOUNDARIES_R 		0
#define BOUNDARIES_G		206
#define BOUNDARIES_B		209

/* Modes for displaying time to travel
 * 0 - display approximate time interval in days
 * 1 - display distance in nautical miles. useful when sailing on board to be able to calculate remaining time according to current speed
 * 2 - display distance in average hours. useful when sailing on board to get approximate time in hours calculated with average speed. requires average speed to be set below
 */
#define TRAVELTIME_MODE 0

/* Average speed for calculation of the time to travel. Only used when TRAVELTIME_MODE is set to 2
 * Default: 4.5
 */
#define TRAVELTIME_AVERAGE_SPEED 4.5

/* Modes for trade assitant
 * 0 - use only tradebook data
 * 1 - use actual data
 * Warning! Setting this to 1 is kinda cheating. I advise you not to change it
 */
#define TRADEASSISTANT_MODE 0