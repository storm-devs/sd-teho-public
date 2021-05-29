object CoastFoam;

void CreateCoastFoamEnvironment(string sFoamID, string sExecuteLayer, string sRealizeLayer)
{
	CoastFoam.id = sFoamID;
	CoastFoam.Edit = false;
	CreateEntity(&CoastFoam, "CoastFoam");
	LayerAddObject(sExecuteLayer, &CoastFoam, 65530);
	LayerAddObject(sRealizeLayer, &CoastFoam, 65531);
}

void DeleteCoastFoamEnvironment()
{
	DeleteClass(&CoastFoam);
}