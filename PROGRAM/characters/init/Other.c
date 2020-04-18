int CreateOtherCharacters(int n)
{
	ref ch;
	
	
	
	
	
	

	makeref(ch,Characters[n]);		

	ch.name 	= "�����";
	ch.lastname = "�����";
	ch.id		= "BoatChar";
	ch.nation	= ENGLAND;
	ch.activity_begin = "0";
	ch.activity_end = "24";
	ch.experience = "0";
	ch.Ship.Name = "�����";
	ch.Ship.Type = GenerateShip(SHIP_BOAT, 1);
	ch.Ship.Stopped = true;
	n = n + 1;
	
	return n;
}

