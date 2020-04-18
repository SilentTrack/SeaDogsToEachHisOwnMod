bool NetServer_CheckGameOver_Convoy()
{
	int i;
	bool bFlagCarrierAlive = false;

	
	int iSurvivedTeams[2];
	for (i=0; i<2; i++) { iSurvivedTeams[i] = 0; }
	for (i=0; i<NET_MAXCLIENTS; i++) 
	{ 
		if (!sti(NSClients[i].Use)) { continue; } 
		if (stf(NSClients[i].Ship.hp) <= 0.0) { continue; } 

		int iTeam = sti(NSClients[i].Team);
		iSurvivedTeams[iTeam] = iSurvivedTeams[iTeam] + 1;
	}

	if (sti(NetServer.ConvoyShipID) != DST_INVALID)
	{
		ref rConvoyClient = NetServer_GetClient(sti(NetServer.ConvoyShipID));
		if (stf(rConvoyClient.Ship.hp) > 0.0) { bFlagCarrierAlive = true;	} 
	}
	
	
	if (!bFlagCarrierAlive)
	{
		NetServer.iWinnerTeam = 1;
		return true;
	}

	
	float fDistance = CONVOY_POINT_RADIUS + 1.0;
	if (sti(NetServer.ConvoyShipID) != DST_INVALID)
	{
		ref rClient = NetServer_GetClient(sti(NetServer.ConvoyShipID));
		
		float x = stf(rClient.Ship.Pos.x);
		float z = stf(rClient.Ship.Pos.z);

		fDistance = GetDistance2D(x, z, stf(NetServer.ConvoyPoint.x), stf(NetServer.ConvoyPoint.z));
	}
	if (fDistance <= CONVOY_POINT_RADIUS)
	{
		NetServer.iWinnerTeam = 0;
		return true;
	}

	
	if (iSurvivedTeams[1] == 0)
	{
		NetServer.iWinnerTeam = 0;
		return true;
	}

	return false;
}
