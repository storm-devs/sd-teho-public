// Warship. Методы для работы с числами
// Большую часть попереносил из других файлов, чтобы все в одном месте было

#define PI 3.14159265
#define PIm2 6.28318530
#define PId2 1.57079632

float FRAND(float _x)
{
	return rand(32768) / 32768.0 * _x;
}

// boal
float frandSmall(float _x)
{
	return rand(32) / 32.0 * _x;
}

// Warship 30.07.09. -->
// Рандом 0.0 ... 1.0
float Random()
{
	return rand(32768) / 32768.0; // 65536
}

// Љоммент - не нравится мне cRand() - он возвращает не псевдослучайное число,
// а зависящее от конкретного дня месяца, да еще и подряд может быть несколько
// одинаковых числе, например, cRand(5) будет давать 5 дней подряд одно и тоже.
// Функция ниже вернет псевдослучайное число, потом запоминает его в PChar и пока не наступит
// новый день будет возвращать его-же. PChar.dayRandom устанавливается в первом шаге обновления дня
int dRand(int _max)
{
	if (_max == 0) { // mitrokosta увидел кучу использований drand(n) где n вполне может быть 0 в LSC_Q2Utilite...
		return 0;
	}

	float dayRandom;
	
	if(CheckAttribute(PChar, "dayRandom"))
	{
		dayRandom = stf(PChar.dayRandom);
		return MakeInt(dayRandom * _max + 1.0 / (_max + 1)); // 1.0 / (_max + 1) - для округления, иначе _max не выпадет никогда
	}
	
	dayRandom = Random();
	PChar.dayRandom = dayRandom;
	
	return MakeInt(dayRandom * _max + 1.0 / (_max + 1));
}
// <-- Warship 30.07.09

// cRand() - античитовый рандом Эдди. Юзать не рекомендуется, за место него - dRand()
//античитовый рендом
int cRand(int num)
{
	if (num < 1) return 0;
	if (num > 30) return rand(num);
	int sResult = num;
	int iData = GetDataDay();

	int iDel = 30.0 / (num + 1) + 0.5; //делитель месяца
	int step = iDel; //шаг увеличения уровня сравнения в месяце

	for (i=0; i<num; i++)
	{
		if (iData < iDel) 
		{
			sResult = i;
			break;
		}
		else iDel += step;
	}
	return sResult;
}

// Радианы в градусы
float Radian2Degree(float _rad) 
{
	return 180 / PI * _rad;
}

int func_max(int a, int b)
{
	if (a > b) return a;
	return b;
}

int func_min(int a, int b)
{
	if (a > b) return b;
	return a;
}

int iClamp(int min, int max, int val)
{
	if(val < min) val = min;
	else
	{
		if(val > max) val = max;
	}
	return val;
}

int iabs(int num)
{
	if (num < 0)
		return -num;
	else
		return num;
}

// код ниже взят из Новых Горизонтов с разрешения Питера Боелена дабы самому не изобретать велосипед
// Natural logarithm
// Useful for normally distributed random numbers among other calcs
float logN(float num)
{
	float e = 2.71828;			// limit of accuracy to keep calcs reasonable
	if (num <= 0) return 0.0;	// can't do logs of negative numbers or zero
	float exp = 0.0;
	while (num > 1.6)			// optimize a bit, probably 1.6 is best here.  Near 2.5 it crashes.
	{
		num = num / e;
		exp = exp + 1.0;
	}
	while (num < 0.2)
	{
		num = num * e;
		exp = exp - 1.0;
	}
	float x = num - 1.0;
	float y = x;
	int i;
	float n = 2.0;
	float z;
	for ( i=1 ; i<100 ; i++ )		// arbitrarily high limit just for safety, normally never goes over 28
	{
		z = y;
		y = y - pow(x,n)/n;
		n = n + 1.0;
		y = y + pow(x,n)/n;
		n = n + 1.0;
		if (z == y) break;
	}
	return y + exp;
}

float log10(float num)
{
	return logN(num) / 2.302585093;	// for log base 10, divide by logN(10)
}

//  Return a normally distributed random number with specified mean and standard deviation
//  68% of samples will be within 1 stdev of mean, 95% within 2 stdev's, 99% within 3 stdev's.
//  100% should be within 4.56 stdev's due to frnd() and accuracy of math in this system
//  This is the standard "bell curve"
float randnorm2 = 9999.0;
float randnorm(float mean, float stdev)
{
    float  r, u;
    float  randnorm1;

	if (randnorm2 != 9999.0)
	{
		float rc = randnorm2 * stdev + mean;
		randnorm2 = 9999.0;
		return rc;
	}

	r = sqrt(-2.0 * logN(frnd()));	// .000030519 is lowest frnd() (besides zero, 1.2 occurences in 30,000), 4.5601 is largest r
	u = frnd();
	randnorm1 = r * sin(PIm2 * u);
	randnorm2 = r * cos(PIm2 * u);

	return ( randnorm1 * stdev + mean );
}
