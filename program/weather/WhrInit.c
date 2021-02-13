#include "Weather\Init\Common.c"
#include "Weather\Init\Day.c"
#include "Weather\Init\Evening.c"
#include "Weather\Init\Morning.c"
#include "Weather\Init\Night.c"
#include "Weather\Init\DayStorm.c"
#include "Weather\Init\Special.c"
#include "Weather\Init\Rain.c"

int InitWeather()
{
    int n = 0;

    n = Whr_InitNight(n);
    n = Whr_InitMorning(n);
    n = Whr_InitDay(n);
    n = Whr_InitEvening(n);
    n = Whr_InitDayStorm(n);
    n = Whr_InitSpecial(n);
    //n = Whr_InitRain(n);

    Whr_InitCommon();

    Trace("Init weathers complete. " + n + " weathers found.");

    for (int i = 0; i < n; i++)
    {
        if (!CheckAttribute(&Weathers[i], "Stars.Enable"))
        {
            Weathers[i].Stars.Enable = false;
        };
        if (!CheckAttribute(&Weathers[i], "Stars.Texture"))
        {
            Weathers[i].Stars.Texture = "weather\astronomy\stars.tga.tx";
        };
        if (!CheckAttribute(&Weathers[i], "Stars.Color"))
        {
            Weathers[i].Stars.Color = argb(255, 255, 255, 255);
        };
        if (!CheckAttribute(&Weathers[i], "Stars.Radius"))
        {
            Weathers[i].Stars.Radius = 2000.0;
        };
        if (!CheckAttribute(&Weathers[i], "Stars.Size"))
        {
            Weathers[i].Stars.Size = 15.0;
        };
        if (!CheckAttribute(&Weathers[i], "Stars.HeightFade"))
        {
            Weathers[i].Stars.HeightFade = 200.0;
        };
        if (!CheckAttribute(&Weathers[i], "Stars.SunFade"))
        {
            Weathers[i].Stars.SunFade = 1.0;
        };
        if (!CheckAttribute(&Weathers[i], "Stars.VisualMagnitude"))
        {
            Weathers[i].Stars.VisualMagnitude = 8.0;
        };

        if (!CheckAttribute(&Weathers[i], "Planets.Enable"))
        {
            Weathers[i].Planets.Enable = false;
        };
        if (!CheckAttribute(&Weathers[i], "Sounds.Sea.Postfix"))
        {
            Weathers[i].Sounds.Sea.Postfix = "_storm";
        };
        if (!CheckAttribute(&Weathers[i], "Sun.Moon"))
        {
            Weathers[i].Sun.Moon = false;
        };
        if (!CheckAttribute(&Weathers[i], "Sun.Reflection.Enable"))
        {
            Weathers[i].Sun.Reflection.Enable = false;
        }
        if (!CheckAttribute(&Weathers[i], "Lightning.Enable"))
        {
            Weathers[i].Lightning.Enable = false;
        };
        if (!CheckAttribute(&Weathers[i], "Rainbow.Enable"))
        {
            Weathers[i].Rainbow.Enable = false;
        };
        if (!CheckAttribute(&Weathers[i], "Rainbow.Texture"))
        {
            Weathers[i].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";
        };

        if (!CheckAttribute(&Weathers[i], "Sun.Overflow.Enable"))
        {
            Weathers[i].Sun.Overflow.Enable = false;
        };
        if (!CheckAttribute(&Weathers[i], "Sun.Overflow.Texture"))
        {
            Weathers[i].Sun.Overflow.Texture = "weather\lightning\flash.tga.tx";
        };
        if (!CheckAttribute(&Weathers[i], "Sun.Overflow.Color"))
        {
            Weathers[i].Sun.Overflow.Color = argb(255, 25, 25, 25);
        };
        if (!CheckAttribute(&Weathers[i], "Sun.Overflow.Size"))
        {
            Weathers[i].Sun.Overflow.Size = 5500.0;
        };
        if (!CheckAttribute(&Weathers[i], "Sun.Overflow.Technique"))
        {
            Weathers[i].Sun.Overflow.Technique = "sunoverflow";
        };
        if (!CheckAttribute(&Weathers[i], "Sun.Overflow.Start"))
        {
            Weathers[i].Sun.Overflow.Start = 0.7;
        };

        if (!CheckAttribute(&Weathers[i], "Rain.NumDrops"))
        {
            Weathers[i].Rain.NumDrops = 0;
        };
        if (!CheckAttribute(&Weathers[i], "Rain.Color"))
        {
            Weathers[i].Rain.Color = argb(0, 73, 73, 73);
        };
        if (!CheckAttribute(&Weathers[i], "Rain.DropLength"))
        {
            Weathers[i].Rain.DropLength = 2.12;
        };
        if (!CheckAttribute(&Weathers[i], "Rain.Height"))
        {
            Weathers[i].Rain.Height = 30.0;
        };
        if (!CheckAttribute(&Weathers[i], "Rain.Radius"))
        {
            Weathers[i].Rain.Radius = 30.0;
        };
        if (!CheckAttribute(&Weathers[i], "Rain.Speed"))
        {
            Weathers[i].Rain.Speed = 18.0;
        };
        if (!CheckAttribute(&Weathers[i], "Rain.Jitter"))
        {
            Weathers[i].Rain.Jitter = 0.4;
        };
        if (!CheckAttribute(&Weathers[i], "Rain.WindSpeedJitter"))
        {
            Weathers[i].Rain.WindSpeedJitter = 0.5;
        };
        if (!CheckAttribute(&Weathers[i], "Rain.MaxBlend"))
        {
            Weathers[i].Rain.MaxBlend = 49;
        };
        if (!CheckAttribute(&Weathers[i], "Rain.TimeBlend"))
        {
            Weathers[i].Rain.TimeBlend = 2000;
        };

        if (!CheckAttribute(&Weathers[i], "Rain.DropsNearNum"))
        {
            Weathers[i].Rain.DropsNearNum = 500;
        };
        if (!CheckAttribute(&Weathers[i], "Rain.DropsFarNum"))
        {
            Weathers[i].Rain.DropsFarNum = 500;
        };
        if (!CheckAttribute(&Weathers[i], "Rain.DropsNearRadius"))
        {
            Weathers[i].Rain.DropsNearRadius = 25.0;
        };
        if (!CheckAttribute(&Weathers[i], "Rain.DropsFarRadius"))
        {
            Weathers[i].Rain.DropsFarRadius = 75.0;
        };
        if (!CheckAttribute(&Weathers[i], "Rain.DropsLifeTime"))
        {
            Weathers[i].Rain.DropsLifeTime = 0.25;
        };
        if (!CheckAttribute(&Weathers[i], "Rain.DropsSize"))
        {
            Weathers[i].Rain.DropsSize = 0.06;
        };
        if (!CheckAttribute(&Weathers[i], "Rain.DropsTexture"))
        {
            Weathers[i].Rain.DropsTexture = "weather\rain_drops.tga.tx";
        };
        if (!CheckAttribute(&Weathers[i], "Rain.DropsColor"))
        {
            Weathers[i].Rain.DropsColor = argb(63, 255, 255, 255);
        };

        if (!CheckAttribute(&Weathers[i], "Sea.GF2MX.Water.Color"))
        {
            Weathers[i].Sea.GF2MX.Sky.Color = argb(0, 160, 210, 255);
        };
        if (!CheckAttribute(&Weathers[i], "Sea.GF2MX.Water.Color"))
        {
            Weathers[i].Sea.GF2MX.Water.Color = argb(0, 25, 55, 80);
        };
        if (!CheckAttribute(&Weathers[i], "Sea.GF2MX.Bump.Tile"))
        {
            Weathers[i].Sea.GF2MX.Bump.Tile = 0.05;
        };
        if (!CheckAttribute(&Weathers[i], "Sea.GF2MX.Bump.AnimSpeed"))
        {
            Weathers[i].Sea.GF2MX.Bump.AnimSpeed = 7.0;
        };
        if (!CheckAttribute(&Weathers[i], "Sea.GF2MX.Bump.Dir"))
        {
            Weathers[i].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\"; };

                if (!CheckAttribute(&Weathers[i], "Sea.Transparency"))
            {
                Weathers[i].Sea.Transparency = 0.9;
            };
            if (!CheckAttribute(&Weathers[i], "Sea.FrenelCoefficient"))
            {
                Weathers[i].Sea.FrenelCoefficient = 0.5;
            };
            if (!CheckAttribute(&Weathers[i], "Sea.WaterReflection"))
            {
                Weathers[i].Sea.WaterReflection = 0.9;
            };
            if (!CheckAttribute(&Weathers[i], "Sea.WaterAttenuation"))
            {
                Weathers[i].Sea.WaterAttenuation = 0.2;
            };
            if (!CheckAttribute(&Weathers[i], "Sea.Sky.Color"))
            {
                Weathers[i].Sea.Sky.Color = argb(0, 190, 190, 190);
            };
            if (!CheckAttribute(&Weathers[i], "Sea.Water.Color"))
            {
                Weathers[i].Sea.Water.Color = argb(0, 25, 55, 80);
            };
            if (!CheckAttribute(&Weathers[i], "Sea.Pena.Color"))
            {
                Weathers[i].Sea.Pena.Color = argb(0, 175, 175, 155);
            };
            if (!CheckAttribute(&Weathers[i], "Sea.Bump.Dir"))
            {
                Weathers[i].Sea.Bump.Dir = "textures\weather\sea\bump_g3\"; };
                    if (!CheckAttribute(&Weathers[i], "Sea.Bump.Tile"))
                {
                    Weathers[i].Sea.Bump.Tile = 0.04;
                };
                if (!CheckAttribute(&Weathers[i], "Sea.Bump.Ang"))
                {
                    Weathers[i].Sea.Bump.Ang = 0.0;
                };
                if (!CheckAttribute(&Weathers[i], "Sea.Bump.Speed"))
                {
                    Weathers[i].Sea.Bump.Speed = 0.01;
                };
                if (!CheckAttribute(&Weathers[i], "Sea.Bump.AnimSpeed"))
                {
                    Weathers[i].Sea.Bump.AnimSpeed = 15.0;
                };
                if (!CheckAttribute(&Weathers[i], "Sea.Bump.Scale"))
                {
                    Weathers[i].Sea.Bump.Scale = 2.0;
                };

                if (!CheckAttribute(&Weathers[i], "Sea2.FoamEnable"))
                {
                    Weathers[i].Sea2.FoamEnable = true;
                };
                if (!CheckAttribute(&Weathers[i], "Sea2.FoamK"))
                {
                    Weathers[i].Sea2.FoamK = 0.1;
                };
                if (!CheckAttribute(&Weathers[i], "Sea2.FoamV"))
                {
                    Weathers[i].Sea2.FoamV = 5.0;
                };
                if (!CheckAttribute(&Weathers[i], "Sea2.FoamUV"))
                {
                    Weathers[i].Sea2.FoamUV = 0.05;
                };
                if (!CheckAttribute(&Weathers[i], "Sea2.FoamTexDisturb"))
                {
                    Weathers[i].Sea2.FoamTexDisturb = 0.7;
                };
            }

            return n;
        }
