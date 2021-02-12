int Whr_InitDay(int n)
{
// Day1
	Weathers[n].id = "11 Hour";
	Weathers[n].Hour.Min = 11;
	Weathers[n].Hour.Max = 11;
	Weathers[n].Lighting = "day11";
	Weathers[n].LightingLm = "day1";
	Weathers[n].InsideBack = "d";
	//Weathers[n].Sounds.Sea.Postfix = "_day";

	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = true;
	Weathers[n].Lights = 0;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1;
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "weather\skies\11\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 2048.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 150;
	Weathers[n].Fog.Start = 10;
	Weathers[n].Fog.Density = 0.0003;
	Weathers[n].Fog.IslandDensity = 0.0003;
	Weathers[n].Fog.SeaDensity = 0.00006;
	//Weathers[n].Fog.Color = argb(0,115,140,155);
	Weathers[n].Fog.Color = argb(0,135,168,205);

	Weathers[n].Rain.NumDrops = 0;
	Weathers[n].Rain.Color = argb(0,73,73,73);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.06;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(63, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,130,130,100);
	Weathers[n].Sun.Ambient = argb(0,105,105,90);
	//Weathers[n].Sun.AzimuthAngle = Degree2Radian(150.0);
	//Weathers[n].Sun.HeightAngle = 0.70;
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(91.0);
	Weathers[n].Sun.HeightAngle = 56.0;
	Weathers[n].Sun.Glow.Enable = true;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,255,255,255);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	//#20190721-01
	Weathers[n].Sun.Overflow.Size = 2000; //5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunglow_z";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(0, 200, 200, 200);
	Weathers[n].Sun.Flare.Enable = true;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,25,55,80);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.05;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 7.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.9;
	Weathers[n].Sea.FrenelCoefficient = 0.5;
	Weathers[n].Sea.WaterReflection = 0.9;
	Weathers[n].Sea.WaterAttenuation = 0.2;
	Weathers[n].Sea.Sky.Color = argb(0,190,190,190);
	Weathers[n].Sea.Water.Color = argb(0,25,55,80);
	Weathers[n].Sea.Pena.Color = argb(0,175,175,155);
	Weathers[n].Sea.Bump.Dir = "textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.04;
	Weathers[n].Sea.Bump.Ang = 0.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 15.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 0.99;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,128,55,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,200,150);
	Weathers[n].Sea.SunRoad.Power = 0.2;

	Weathers[n].Sea.Harmonics.h1 = "0.0, 2.5, 3.0, 0.0, 10.00";
	Weathers[n].Sea.Harmonics.h2 = "90.0, 5.0, 1.5, 0.0, 50.00";
	Weathers[n].Sea.Harmonics.h3 = "45.0, 8.0, 2.5, 0.0, 200.00";
	Weathers[n].Sea.Harmonics.h4 = "13.0, 6.0, 1.0, 0.0, 150.00";
	Weathers[n].Sea.Harmonics.h5 = "90.0, 50.0, 0.2, 0.0, 20.00";

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.05;
	Weathers[n].Sea2.PosShift = 0.0;

	//Weathers[n].Sea2.WaterColor = argb(0, 10, 90, 120);
	//Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.WaterColor = argb(0, 25, 55, 80);
	Weathers[n].Sea2.SkyColor = argb(0, 205, 255, 255);

	Weathers[n].Sea2.Reflection = 0.9;
	Weathers[n].Sea2.Transparency = 0.9;
	Weathers[n].Sea2.Frenel = 0.45;
	Weathers[n].Sea2.Attenuation = 0.3;

	Weathers[n].Sea2.Amp1 = 7.0;
	Weathers[n].Sea2.AnimSpeed1 = 2.0;
	Weathers[n].Sea2.Scale1 = 0.30;
	Weathers[n].Sea2.MoveSpeed1 = "2.0, 0.0, 0.0";

	Weathers[n].Sea2.Amp2 = 1.1;
	Weathers[n].Sea2.AnimSpeed2 = 19.0;
	Weathers[n].Sea2.Scale2 = 3;
	Weathers[n].Sea2.MoveSpeed2 = "1.0, 0.0, 1.0";

	Weathers[n].Sea2.FoamEnable = true;
	Weathers[n].Sea2.FoamK = 0.2;
	Weathers[n].Sea2.FoamV = 2.5;
	Weathers[n].Sea2.FoamUV = 0.5;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;

	Weathers[n].Sea2.LodScale = 0.22;
	Weathers[n].Sea2.GridStep = 0.08;

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 4.0;
	Weathers[n].Wind.Speed.Max = 7.0;

	n++;

// Day12
	Weathers[n].id = "12 Hour";
	Weathers[n].Hour.Min = 12;
	Weathers[n].Hour.Max = 12;
	Weathers[n].Lighting = "day12";
	Weathers[n].LightingLm = "day1";
	Weathers[n].InsideBack = "d";

	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = true;
	Weathers[n].Lights = 0;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1;
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "weather\skies\12\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 2048.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Fog.Enable = false;
	Weathers[n].Fog.Height = 150;
	Weathers[n].Fog.Start = 10;
	Weathers[n].Fog.Density = 0.0003;
	Weathers[n].Fog.IslandDensity = 0.0003;
	Weathers[n].Fog.SeaDensity = 0.00006;
	//Weathers[n].Fog.Color = argb(0,115,140,155);
	Weathers[n].Fog.Color = argb(0,135,168,205);

	Weathers[n].Rain.NumDrops = 0;
	Weathers[n].Rain.Color = argb(0,73,73,73);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.06;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(65, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,130,130,100);
	Weathers[n].Sun.Ambient = argb(0,105,105,90);
	//Weathers[n].Sun.AzimuthAngle = Degree2Radian(150.0);
	//Weathers[n].Sun.HeightAngle = 0.70;
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(100.0);
	Weathers[n].Sun.HeightAngle = 70.0;
	Weathers[n].Sun.Glow.Enable = true;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,255,255,255);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	//#20190721-01
	Weathers[n].Sun.Overflow.Size = 2000; //5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunglow_z";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(0, 200, 200, 200);
	Weathers[n].Sun.Flare.Enable = true;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,5,10);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.05;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 7.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.9;
	Weathers[n].Sea.FrenelCoefficient = 0.5;
	Weathers[n].Sea.WaterReflection = 0.9;
	Weathers[n].Sea.WaterAttenuation = 0.2;
	Weathers[n].Sea.Sky.Color = argb(0,190,190,190);
	Weathers[n].Sea.Water.Color = argb(0,25,55,80);
	Weathers[n].Sea.Pena.Color = argb(0,175,175,155);
	Weathers[n].Sea.Bump.Dir = "textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.04;
	Weathers[n].Sea.Bump.Ang = 0.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 15.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 0.99;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,128,55,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,200,150);
	Weathers[n].Sea.SunRoad.Power = 0.2;

	Weathers[n].Sea.Harmonics.h1 = "0.0, 2.5, 3.0, 0.0, 10.00";
	Weathers[n].Sea.Harmonics.h2 = "90.0, 5.0, 1.5, 0.0, 50.00";
	Weathers[n].Sea.Harmonics.h3 = "45.0, 8.0, 2.5, 0.0, 200.00";
	Weathers[n].Sea.Harmonics.h4 = "13.0, 6.0, 1.0, 0.0, 150.00";
	Weathers[n].Sea.Harmonics.h5 = "90.0, 50.0, 0.2, 0.0, 20.00";

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.05;
	Weathers[n].Sea2.PosShift = 2.0;

	//Weathers[n].Sea2.WaterColor = argb(0, 25, 55, 80);
	//Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.WaterColor = argb(0, 25, 55, 80);
	Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.Reflection = 0.9;
	Weathers[n].Sea2.Transparency = 0.9;
	Weathers[n].Sea2.Frenel = 0.35;
	Weathers[n].Sea2.Attenuation = 0.3;

	Weathers[n].Sea2.Amp1 = 7.0;
	Weathers[n].Sea2.AnimSpeed1 = 2.0;
	Weathers[n].Sea2.Scale1 = 0.30;
	Weathers[n].Sea2.MoveSpeed1 = "2.0, 0.0, 0.0";

	Weathers[n].Sea2.Amp2 = 1.1;
	Weathers[n].Sea2.AnimSpeed2 = 19.0;
	Weathers[n].Sea2.Scale2 = 3;
	Weathers[n].Sea2.MoveSpeed2 = "1.0, 0.0, 1.0";


    Weathers[n].Sea2.FoamEnable = true;
	Weathers[n].Sea2.FoamK = 0.1;
	Weathers[n].Sea2.FoamV = 3.0;
	Weathers[n].Sea2.FoamUV = 0.5;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 4.0;
	Weathers[n].Wind.Speed.Max = 7.0;

	n++;

// Day2 13
	Weathers[n].id = "13 Hour";
	Weathers[n].Hour.Min = 13;
	Weathers[n].Hour.Max = 13;
	Weathers[n].Lighting = "day13";
	Weathers[n].LightingLm = "day2";
	Weathers[n].InsideBack = "d";

	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = true;
	Weathers[n].Lights = 0;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1;
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "weather\skies\13\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 2048.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 150;
	Weathers[n].Fog.Start = 10;
	Weathers[n].Fog.Density = 0.00025;
	Weathers[n].Fog.IslandDensity = 0.00025;
	Weathers[n].Fog.SeaDensity = 0.00025;
	//Weathers[n].Fog.Color = argb(0,85,155,190);
	Weathers[n].Fog.Color = argb(0,85,145,190);

	Weathers[n].Rain.NumDrops = 0;
	Weathers[n].Rain.Color = argb(0,73,73,73);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.06;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(61, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,214,214,208);
	Weathers[n].Sun.Ambient = argb(0,100,100,90);
	//Weathers[n].Sun.AzimuthAngle = Degree2Radian(88.0);
	//Weathers[n].Sun.HeightAngle = 0.85;
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(130.0);
	Weathers[n].Sun.HeightAngle = 82.0;
	Weathers[n].Sun.Glow.Enable = true;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,255,255,255);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	//#20190721-01
	Weathers[n].Sun.Overflow.Size = 2000; //5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = true;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,5,10);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.05;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 7.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.9;
	Weathers[n].Sea.FrenelCoefficient = 0.5;
	Weathers[n].Sea.WaterReflection = 0.9;
	Weathers[n].Sea.WaterAttenuation = 0.2;
	Weathers[n].Sea.Sky.Color = argb(0,210,210,210);
	Weathers[n].Sea.Water.Color = argb(0,25,55,80);
	Weathers[n].Sea.Pena.Color = argb(0,175,175,155);
	Weathers[n].Sea.Bump.Dir = "textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.04;
	Weathers[n].Sea.Bump.Ang = 0.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 15.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 0.99;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,128,55,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,200,150);
	Weathers[n].Sea.SunRoad.Power = 0.2;

	Weathers[n].Sea.Harmonics.h1 = "0.0, 1.5, 3.0, 0.0, 10.0";
	Weathers[n].Sea.Harmonics.h2 = "0.0, 3.5, 2.0, 0.0, 20.0";
	Weathers[n].Sea.Harmonics.h3 = "90.0, 2.5, 4.0, 0.0, 15.0";
	Weathers[n].Sea.Harmonics.h4 = "90.0, 1.5, 1.5, 0.0, 15.0";
	Weathers[n].Sea.Harmonics.h5 = "240.0, 15.0, 1.0, 10.0, 85.0";
	Weathers[n].Sea.Harmonics.h6 = "120.0, 18.0, 0.8, 30.0, 125.0";

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.05;
	Weathers[n].Sea2.PosShift = 0.001; //2.5;

	Weathers[n].Sea2.WaterColor = argb(0, 25, 55, 80);
	Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.Reflection = 0.9;
	Weathers[n].Sea2.Transparency = 0.9;
	Weathers[n].Sea2.Frenel = 0.3;
	Weathers[n].Sea2.Attenuation = 0.3;

	Weathers[n].Sea2.Amp1 = 6.0;
	Weathers[n].Sea2.AnimSpeed1 = 10.0;
	Weathers[n].Sea2.Scale1 = 0.8;
	Weathers[n].Sea2.MoveSpeed1 = "0.0, 0.0, 3.0";

	Weathers[n].Sea2.Amp2 = 0.001; //1.0;
	Weathers[n].Sea2.AnimSpeed2 = 19.0;
	Weathers[n].Sea2.Scale2 = 0.001; //2.0;
	Weathers[n].Sea2.MoveSpeed2 = "-2.0, 0.0, 0.0";

	Weathers[n].Sea2.FoamEnable = true;
	Weathers[n].Sea2.FoamK = 0.3;
	Weathers[n].Sea2.FoamV = 2.8;
	Weathers[n].Sea2.FoamUV = 1.0;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;

	//#20180103-03 Sea LODScale/GridStep
	Weathers[n].Sea2.LodScale = 0.22;
	Weathers[n].Sea2.GridStep = 0.13;

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 7.0;
	Weathers[n].Wind.Speed.Max = 14.5;

	n++;

// Day2 14
	Weathers[n].id = "14 Hour";
	Weathers[n].Hour.Min = 14;
	Weathers[n].Hour.Max = 14;
	Weathers[n].Lighting = "day14";
	Weathers[n].LightingLm = "day2";
	Weathers[n].InsideBack = "d";

	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = true;
	Weathers[n].Lights = 0;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1;
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "weather\skies\14\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 2048.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 150;
	Weathers[n].Fog.Start = 10;
	Weathers[n].Fog.Density = 0.00025;
	Weathers[n].Fog.IslandDensity = 0.00025;
	Weathers[n].Fog.SeaDensity = 0.00025;
	//Weathers[n].Fog.Color = argb(0,85,155,190);
	Weathers[n].Fog.Color = argb(0,85,145,190);

	Weathers[n].Rain.NumDrops = 0;
	Weathers[n].Rain.Color = argb(0,73,73,73);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.06;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(59, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,234,234,218);
	Weathers[n].Sun.Ambient = argb(0,100,100,80);
	//Weathers[n].Sun.AzimuthAngle = Degree2Radian(88.0);
	//Weathers[n].Sun.HeightAngle = 0.85;
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(238.0);
	Weathers[n].Sun.HeightAngle = 81.0;
	Weathers[n].Sun.Glow.Enable = true;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,255,255,255);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	//#20190721-01
	Weathers[n].Sun.Overflow.Size = 2000; //5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = true;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,5,10);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.05;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 7.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.9;
	Weathers[n].Sea.FrenelCoefficient = 0.5;
	Weathers[n].Sea.WaterReflection = 0.9;
	Weathers[n].Sea.WaterAttenuation = 0.2;
	Weathers[n].Sea.Sky.Color = argb(0,210,210,210);
	Weathers[n].Sea.Water.Color = argb(0,25,55,80);
	Weathers[n].Sea.Pena.Color = argb(0,175,175,155);
	Weathers[n].Sea.Bump.Dir = "textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.04;
	Weathers[n].Sea.Bump.Ang = 0.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 15.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 0.99;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,128,55,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,200,150);
	Weathers[n].Sea.SunRoad.Power = 0.2;

	Weathers[n].Sea.Harmonics.h1 = "0.0, 1.5, 3.0, 0.0, 10.0";
	Weathers[n].Sea.Harmonics.h2 = "0.0, 3.5, 2.0, 0.0, 20.0";
	Weathers[n].Sea.Harmonics.h3 = "90.0, 2.5, 4.0, 0.0, 15.0";
	Weathers[n].Sea.Harmonics.h4 = "90.0, 1.5, 1.5, 0.0, 15.0";
	Weathers[n].Sea.Harmonics.h5 = "240.0, 15.0, 1.0, 10.0, 85.0";
	Weathers[n].Sea.Harmonics.h6 = "120.0, 18.0, 0.8, 30.0, 125.0";

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.05;
	Weathers[n].Sea2.PosShift = 0.5; //2.5;

	Weathers[n].Sea2.WaterColor = argb(0, 25, 55, 80);
	Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.Reflection = 0.9;
	Weathers[n].Sea2.Transparency = 0.9;
	Weathers[n].Sea2.Frenel = 0.3;
	Weathers[n].Sea2.Attenuation = 0.3;

	Weathers[n].Sea2.Amp1 = 6.0;
	Weathers[n].Sea2.AnimSpeed1 = 10.0;
	Weathers[n].Sea2.Scale1 = 0.8;
	Weathers[n].Sea2.MoveSpeed1 = "0.0, 0.0, 3.0";

	Weathers[n].Sea2.Amp2 = 0.001; //1.0;
	Weathers[n].Sea2.AnimSpeed2 = 19.0;
	Weathers[n].Sea2.Scale2 = 0.001; //2.0;
	Weathers[n].Sea2.MoveSpeed2 = "-2.0, 0.0, 0.0";

	Weathers[n].Sea2.FoamEnable = true;
	Weathers[n].Sea2.FoamK = 0.3;
	Weathers[n].Sea2.FoamV = 3.0;
	Weathers[n].Sea2.FoamUV = 1.0;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;

	//#20180103-03 Sea LODScale/GridStep
	Weathers[n].Sea2.LodScale = 0.22;
	Weathers[n].Sea2.GridStep = 0.08;

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 7.0;
	Weathers[n].Wind.Speed.Max = 10.5;

	n++;

// Day3 15
	Weathers[n].id = "15 Hour";
	Weathers[n].Hour.Min = 15;
	Weathers[n].Hour.Max = 15;
	Weathers[n].Lighting = "day15";
	Weathers[n].LightingLm = "day3";
	Weathers[n].InsideBack = "d";

	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = true;
	Weathers[n].Lights = 0;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1;
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "weather\skies\15\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 2048.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 150;
	Weathers[n].Fog.Start = 10;
	Weathers[n].Fog.Density = 0.0009;
	Weathers[n].Fog.IslandDensity = 0.0003;
	Weathers[n].Fog.SeaDensity = 0.0003;
	//Weathers[n].Fog.Color = argb(0,60,125,150);
	Weathers[n].Fog.Color = argb(0,90,145,180);

	Weathers[n].Rain.NumDrops = 0;
	Weathers[n].Rain.Color = argb(0,73,73,73);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.06;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(55, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,126,124,104);
	Weathers[n].Sun.Ambient = argb(0,105,105,95);
	//Weathers[n].Sun.AzimuthAngle = Degree2Radian(5.0);
	//Weathers[n].Sun.HeightAngle = 1.07;
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(261.0);
	Weathers[n].Sun.HeightAngle = 68.0;
	Weathers[n].Sun.Glow.Enable = true;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,255,255,255);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	//#20190721-01
	Weathers[n].Sun.Overflow.Size = 2000; //5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = true;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,5,10);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.05;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 7.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.9;
	Weathers[n].Sea.FrenelCoefficient = 0.5;
	Weathers[n].Sea.WaterReflection = 0.9;
	Weathers[n].Sea.WaterAttenuation = 0.2;
	Weathers[n].Sea.Sky.Color = argb(0,210,210,210);
	Weathers[n].Sea.Water.Color = argb(0,25,55,80);
	Weathers[n].Sea.Pena.Color = argb(0,175,175,155);
	Weathers[n].Sea.Bump.Dir = "textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.04;
	Weathers[n].Sea.Bump.Ang = 0.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 15.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 0.99;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,128,55,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,200,150);
	Weathers[n].Sea.SunRoad.Power = 0.2;

	Weathers[n].Sea.Harmonics.h1 = "90.0, 2.0, 4.5, 0.0, 10.0";
	Weathers[n].Sea.Harmonics.h2 = "45.0, 1.0, 6.0, 0.0, 50.0";
	Weathers[n].Sea.Harmonics.h2 = "0.0, 4.0, 2.0, 0.0, 150.0";
	Weathers[n].Sea.Harmonics.h2 = "180.0, 5.0, 1.0, 0.0, 150.0";

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.05;
	Weathers[n].Sea2.PosShift = 0.0;

	Weathers[n].Sea2.WaterColor = argb(0, 25, 55, 80);
	Weathers[n].Sea2.SkyColor = argb(0, 175, 255, 255);


	Weathers[n].Sea2.Reflection = 0.9;
	Weathers[n].Sea2.Transparency = 0.9;
	Weathers[n].Sea2.Frenel = 0.5;
	Weathers[n].Sea2.Attenuation = 0.3;

	Weathers[n].Sea2.Amp1 = 25.0;
	Weathers[n].Sea2.AnimSpeed1 = 1.0;
	Weathers[n].Sea2.Scale1 = 0.15;
	Weathers[n].Sea2.MoveSpeed1 = "1.0, 0.0, 6.0";

	Weathers[n].Sea2.Amp2 = 0.8;
	Weathers[n].Sea2.AnimSpeed2 = 19.0;
	Weathers[n].Sea2.Scale2 = 4.0;
	Weathers[n].Sea2.MoveSpeed2 = "0.0, 0.0, 1.0";

	Weathers[n].Sea2.FoamEnable = true;
	Weathers[n].Sea2.FoamK = 0.04;
	Weathers[n].Sea2.FoamV = 7.5;
	Weathers[n].Sea2.FoamUV = 0.5;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 7.0;
	Weathers[n].Wind.Speed.Max = 12.0;

	n++;

// Day3 16
	Weathers[n].id = "16 Hour";
	Weathers[n].Hour.Min = 16;
	Weathers[n].Hour.Max = 16;
	Weathers[n].Lighting = "day16";
	Weathers[n].LightingLm = "day3";
	Weathers[n].InsideBack = "d";

	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = true;
	Weathers[n].Lights = 0;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1;
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "weather\skies\16\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 2048.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 150;
	Weathers[n].Fog.Start = 10;
	Weathers[n].Fog.Density = 0.0009;
	Weathers[n].Fog.IslandDensity = 0.0003;
	Weathers[n].Fog.SeaDensity = 0.0003;
	//Weathers[n].Fog.Color = argb(0,60,125,150);
	Weathers[n].Fog.Color = argb(0,90,145,180);

	Weathers[n].Rain.NumDrops = 0;
	Weathers[n].Rain.Color = argb(0,73,73,73);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.06;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(50, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,126,124,104);
	Weathers[n].Sun.Ambient = argb(0,105,105,95);
	//Weathers[n].Sun.AzimuthAngle = Degree2Radian(5.0);
	//Weathers[n].Sun.HeightAngle = 1.07;
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(270.0);
	Weathers[n].Sun.HeightAngle = 55.0;
	Weathers[n].Sun.Glow.Enable = true;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,255,255,255);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	//#20190721-01
	Weathers[n].Sun.Overflow.Size = 2000; //5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = true;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,5,10);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.05;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 7.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.9;
	Weathers[n].Sea.FrenelCoefficient = 0.5;
	Weathers[n].Sea.WaterReflection = 0.9;
	Weathers[n].Sea.WaterAttenuation = 0.2;
	Weathers[n].Sea.Sky.Color = argb(0,175,255,255);
	Weathers[n].Sea.Water.Color = argb(0,25,55,80);
	Weathers[n].Sea.Pena.Color = argb(0,175,175,155);
	Weathers[n].Sea.Bump.Dir = "textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.04;
	Weathers[n].Sea.Bump.Ang = 0.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 15.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 0.99;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,128,55,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,200,150);
	Weathers[n].Sea.SunRoad.Power = 0.2;

	Weathers[n].Sea.Harmonics.h1 = "90.0, 2.0, 4.5, 0.0, 10.0";
	Weathers[n].Sea.Harmonics.h2 = "45.0, 1.0, 6.0, 0.0, 50.0";
	Weathers[n].Sea.Harmonics.h2 = "0.0, 4.0, 2.0, 0.0, 150.0";
	Weathers[n].Sea.Harmonics.h2 = "180.0, 5.0, 1.0, 0.0, 150.0";

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.05;
	Weathers[n].Sea2.PosShift = 0.0;

	Weathers[n].Sea2.WaterColor = argb(0, 25, 55, 80);
	Weathers[n].Sea2.SkyColor = argb(0, 175, 255, 255);


	Weathers[n].Sea2.Reflection = 0.9;
	Weathers[n].Sea2.Transparency = 0.9;
	Weathers[n].Sea2.Frenel = 0.5;
	Weathers[n].Sea2.Attenuation = 0.3;

	Weathers[n].Sea2.Amp1 = 25.0;
	Weathers[n].Sea2.AnimSpeed1 = 1.0;
	Weathers[n].Sea2.Scale1 = 0.15;
	Weathers[n].Sea2.MoveSpeed1 = "1.0, 0.0, 6.0";

	Weathers[n].Sea2.Amp2 = 0.8;
	Weathers[n].Sea2.AnimSpeed2 = 19.0;
	Weathers[n].Sea2.Scale2 = 4.0;
	Weathers[n].Sea2.MoveSpeed2 = "0.0, 0.0, 1.0";

	Weathers[n].Sea2.FoamEnable = true;
	Weathers[n].Sea2.FoamK = 0.03;
	Weathers[n].Sea2.FoamV = 7.0;
	Weathers[n].Sea2.FoamUV = 0.1;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 7.0;
	Weathers[n].Wind.Speed.Max = 12.0;

	n++;

// Day4 17
	Weathers[n].id = "17 Hour";
	Weathers[n].Hour.Min = 17;
	Weathers[n].Hour.Max = 17;
	Weathers[n].Lighting = "day17";
	Weathers[n].LightingLm = "day4";
	Weathers[n].InsideBack = "d";

	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = true;
	Weathers[n].Lights = 0;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1;
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "weather\skies\17\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 2048.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 450;
	Weathers[n].Fog.Start = 1;
	Weathers[n].Fog.Density = 0.0008;
	Weathers[n].Fog.IslandDensity = 0.00035;
	Weathers[n].Fog.SeaDensity = 0.0009;
	Weathers[n].Fog.Color = argb(0,110,130,150);

	Weathers[n].Rain.NumDrops = 0;
	Weathers[n].Rain.Color = argb(0,73,73,73);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

    Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.06;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(48, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,116,114,94);
	Weathers[n].Sun.Ambient = argb(0,100,100,90);
	//Weathers[n].Sun.AzimuthAngle = Degree2Radian(-25.0);
	//Weathers[n].Sun.HeightAngle = 0.60;
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(276.0);
	Weathers[n].Sun.HeightAngle = 41.0;
	Weathers[n].Sun.Glow.Enable = true;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 500.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\reflection\refl_evening.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,100,100,100);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	//#20190721-01
	Weathers[n].Sun.Overflow.Size = 2000; //5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = false
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,5,10);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.05;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 7.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.9;
	Weathers[n].Sea.FrenelCoefficient = 0.5;
	Weathers[n].Sea.WaterReflection = 0.9;
	Weathers[n].Sea.WaterAttenuation = 0.2;
	Weathers[n].Sea.Sky.Color = argb(0,210,210,210);
	Weathers[n].Sea.Water.Color = argb(0,25,55,80);
	Weathers[n].Sea.Pena.Color = argb(0,175,175,155);
	Weathers[n].Sea.Bump.Dir = "textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.04;
	Weathers[n].Sea.Bump.Ang = 0.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 15.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 0.99;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,128,55,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,200,150);
	Weathers[n].Sea.SunRoad.Power = 0.2;

	Weathers[n].Sea.Harmonics.h1 = "90.0, 2.0, 4.5, 0.0, 10.0";
	Weathers[n].Sea.Harmonics.h2 = "45.0, 1.0, 6.0, 0.0, 50.0";
	Weathers[n].Sea.Harmonics.h2 = "0.0, 4.0, 2.0, 0.0, 150.0";
	Weathers[n].Sea.Harmonics.h2 = "180.0, 5.0, 1.0, 0.0, 150.0";

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.05;
	Weathers[n].Sea2.PosShift = 0.1;

	//Weathers[n].Sea2.WaterColor = argb(0, 25, 55, 80);
	//Weathers[n].Sea2.SkyColor = argb(0, 175, 255, 255);

	Weathers[n].Sea2.WaterColor = argb(0, 70, 95, 120);
	Weathers[n].Sea2.SkyColor = argb(0, 105, 205, 255);

	Weathers[n].Sea2.Reflection = 0.9;
	Weathers[n].Sea2.Transparency = 0.9;
	Weathers[n].Sea2.Frenel = 0.4;
	Weathers[n].Sea2.Attenuation = 0.5;

	Weathers[n].Sea2.Amp1 = 19.0;
	Weathers[n].Sea2.AnimSpeed1 = 2.0;
	Weathers[n].Sea2.Scale1 = 0.25;
	Weathers[n].Sea2.MoveSpeed1 = "1.0, 0.0, 7.5";

	Weathers[n].Sea2.Amp2 = 1.5;
	Weathers[n].Sea2.AnimSpeed2 = 9.0;
	Weathers[n].Sea2.Scale2 = 3.0;
	Weathers[n].Sea2.MoveSpeed2 = "0.0, 0.0, 1.0";

	Weathers[n].Sea2.FoamEnable = true;
	Weathers[n].Sea2.FoamK = 0.04;
	Weathers[n].Sea2.FoamV = 7.0;
	Weathers[n].Sea2.FoamUV = 0.1;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 5.0;
	Weathers[n].Wind.Speed.Max = 8.8;

	n++;

// Day4 18
	Weathers[n].id = "18 Hour";
	Weathers[n].Hour.Min = 18;
	Weathers[n].Hour.Max = 18;
	Weathers[n].Lighting = "day18";
	Weathers[n].LightingLm = "day4";
	Weathers[n].InsideBack = "d";

	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = true;
	Weathers[n].Lights = 0;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1;
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "weather\skies\18\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 2048.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 450;
	Weathers[n].Fog.Start = 1;
	Weathers[n].Fog.Density = 0.0008;
	Weathers[n].Fog.IslandDensity = 0.00035;
	Weathers[n].Fog.SeaDensity = 0.0009;
	Weathers[n].Fog.Color = argb(0,110,130,150);

	Weathers[n].Rain.NumDrops = 0;
	Weathers[n].Rain.Color = argb(0,73,73,73);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

    Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.06;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(46, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,116,114,94);
	Weathers[n].Sun.Ambient = argb(0,100,100,90);
	//Weathers[n].Sun.AzimuthAngle = Degree2Radian(-25.0);
	//Weathers[n].Sun.HeightAngle = 0.60;
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(281.0);
	Weathers[n].Sun.HeightAngle = 28.0;
	Weathers[n].Sun.Glow.Enable = true;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 500.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\reflection\refl_evening.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,100,100,100);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	//#20190721-01
	Weathers[n].Sun.Overflow.Size = 2000; //5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = false
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,5,10);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.05;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 7.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.9;
	Weathers[n].Sea.FrenelCoefficient = 0.5;
	Weathers[n].Sea.WaterReflection = 0.9;
	Weathers[n].Sea.WaterAttenuation = 0.2;
	Weathers[n].Sea.Sky.Color = argb(0,210,210,210);
	Weathers[n].Sea.Water.Color = argb(0,25,55,80);
	Weathers[n].Sea.Pena.Color = argb(0,175,175,155);
	Weathers[n].Sea.Bump.Dir = "textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.04;
	Weathers[n].Sea.Bump.Ang = 0.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 15.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 0.99;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,128,55,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,200,150);
	Weathers[n].Sea.SunRoad.Power = 0.2;

	Weathers[n].Sea.Harmonics.h1 = "90.0, 2.0, 4.5, 0.0, 10.0";
	Weathers[n].Sea.Harmonics.h2 = "45.0, 1.0, 6.0, 0.0, 50.0";
	Weathers[n].Sea.Harmonics.h2 = "0.0, 4.0, 2.0, 0.0, 150.0";
	Weathers[n].Sea.Harmonics.h2 = "180.0, 5.0, 1.0, 0.0, 150.0";

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.05;
	Weathers[n].Sea2.PosShift = 0.1;

	//Weathers[n].Sea2.WaterColor = argb(0, 97, 123, 163);
	//Weathers[n].Sea2.SkyColor = argb(0, 175, 255, 255);

	Weathers[n].Sea2.WaterColor = argb(0, 25, 55, 80);
	Weathers[n].Sea2.SkyColor = argb(0, 105, 205, 255);

	Weathers[n].Sea2.Reflection = 0.9;
	Weathers[n].Sea2.Transparency = 0.9;
	Weathers[n].Sea2.Frenel = 0.4;
	Weathers[n].Sea2.Attenuation = 0.5;

	Weathers[n].Sea2.Amp1 = 19.0;
	Weathers[n].Sea2.AnimSpeed1 = 2.0;
	Weathers[n].Sea2.Scale1 = 0.25;
	Weathers[n].Sea2.MoveSpeed1 = "1.0, 0.0, 7.5";

	Weathers[n].Sea2.Amp2 = 1.5;
	Weathers[n].Sea2.AnimSpeed2 = 9.0;
	Weathers[n].Sea2.Scale2 = 3.0;
	Weathers[n].Sea2.MoveSpeed2 = "0.0, 0.0, 1.0";

	Weathers[n].Sea2.FoamEnable = true;
	Weathers[n].Sea2.FoamK = 0.04;
	Weathers[n].Sea2.FoamV = 4.5;
	Weathers[n].Sea2.FoamUV = 0.1;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 5.0;
	Weathers[n].Wind.Speed.Max = 8.8;

	n++;

	return n;
}
