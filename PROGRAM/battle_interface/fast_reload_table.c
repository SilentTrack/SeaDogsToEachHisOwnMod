
#define FRP_STORE			0
#define FRT_STORE			0

#define FRP_SHIPYARD		1
#define FRT_SHIPYARD		0

#define FRP_TAVERN			2
#define FRT_TAVERN			0

#define FRP_RESIDENCE		4
#define FRT_RESIDENCE		0

#define FRP_USURER			3
#define FRT_USURER			0

#define FRP_PRISON			5
#define FRT_PRISON			0

#define FRP_CHURCH			6
#define FRT_CHURCH			0

#define FRP_BROTHEL			9
#define FRT_BROTHEL			0

#define FRP_PORT_OFFICE		8
#define FRT_PORT_OFFICE		0


void initFastReloadTable()
{
	InitTownTable();

	objFastReloadTable.reloadEnable = true;
	aref curTable;

	makearef(curTable,objFastReloadTable.table.SentJons);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "SentJons_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "SentJons_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "SentJons_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "SentJons_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "SentJons_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "SentJons_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "SentJons_PortOffice";

	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "SentJons_prison";

	makearef(curTable,objFastReloadTable.table.Bridgetown);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "Bridgetown_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "Bridgetown_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "Bridgetown_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "Bridgetown_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "Bridgetown_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "Bridgetown_church";
	
	curTable.l7.pic = FRP_BROTHEL;
	curTable.l7.tex = FRT_BROTHEL;
	curTable.l7.location = "Bridgetown_brothel";

	curTable.l8.pic = FRP_PORT_OFFICE;
	curTable.l8.tex = FRT_PORT_OFFICE;
	curTable.l8.location = "Bridgetown_PortOffice";

	curTable.l9.pic = FRP_PRISON;
	curTable.l9.tex = FRT_PRISON;
	curTable.l9.location = "Bridgetown_prison";

	makearef(curTable,objFastReloadTable.table.PortRoyal);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "PortRoyal_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "PortRoyal_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "PortRoyal_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "PortRoyal_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "PortRoyal_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "PortRoyal_church";
	
	curTable.l7.pic = FRP_BROTHEL;
	curTable.l7.tex = FRT_BROTHEL;
	curTable.l7.location = "PortRoyal_brothel";

	curTable.l8.pic = FRP_PORT_OFFICE;
	curTable.l8.tex = FRT_PORT_OFFICE;
	curTable.l8.location = "PortRoyal_PortOffice";

	curTable.l9.pic = FRP_PRISON;
	curTable.l9.tex = FRT_PRISON;
	curTable.l9.location = "PortRoyal_prison";

	makearef(curTable,objFastReloadTable.table.FortOrange);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "FortOrange_store";
	
	curTable.l2.pic = FRP_TAVERN;
	curTable.l2.tex = FRT_TAVERN;
	curTable.l2.location = "FortOrange_tavern";
	
	curTable.l3.pic = FRP_RESIDENCE;
	curTable.l3.tex = FRT_RESIDENCE;
	curTable.l3.location = "FortOrange_townhall";

	makearef(curTable,objFastReloadTable.table.Pirates);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "Pirates_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "Pirates_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "Pirates_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "Pirates_townhall";

	makearef(curTable,objFastReloadTable.table.Villemstad);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "Villemstad_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "Villemstad_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "Villemstad_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "Villemstad_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "Villemstad_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "Villemstad_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "Villemstad_PortOffice";

	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "Villemstad_prison";

	makearef(curTable,objFastReloadTable.table.BasTer);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "BasTer_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "BasTer_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "BasTer_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "BasTer_townhall";
	
	curTable.l5.pic = FRP_CHURCH;
	curTable.l5.tex = FRT_CHURCH;
	curTable.l5.location = "BasTer_church";
	
	curTable.l6.pic = FRP_USURER;
	curTable.l6.tex = FRT_USURER;
	curTable.l6.location = "BasTer_bank";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "BasTer_PortOffice";

	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "BasTer_prison";

	makearef(curTable,objFastReloadTable.table.Santiago);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "Santiago_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "Santiago_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "Santiago_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "Santiago_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "Santiago_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "Santiago_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "Santiago_PortOffice";

	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "Santiago_prison";

 	makearef(curTable,objFastReloadTable.table.PuertoPrincipe);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "PuertoPrincipe_store";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "PuertoPrincipe_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "PuertoPrincipe_townhall";

	makearef(curTable,objFastReloadTable.table.LaVega);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "LaVega_store";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "LaVega_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "LaVega_townhall";

	makearef(curTable,objFastReloadTable.table.FortFrance);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "FortFrance_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "FortFrance_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "FortFrance_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "FortFrance_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "FortFrance_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "FortFrance_church";
	
	curTable.l7.pic = FRP_BROTHEL;
	curTable.l7.tex = FRT_BROTHEL;
	curTable.l7.location = "FortFrance_brothel";

	curTable.l8.pic = FRP_PORT_OFFICE;
	curTable.l8.tex = FRT_PORT_OFFICE;
	curTable.l8.location = "FortFrance_PortOffice";

	curTable.l9.pic = FRP_PRISON;
	curTable.l9.tex = FRT_PRISON;
	curTable.l9.location = "FortFrance_prison";

	makearef(curTable,objFastReloadTable.table.LeFransua);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "LeFransua_store";
	
	curTable.l2.pic = FRP_TAVERN;
	curTable.l2.tex = FRT_TAVERN;
	curTable.l2.location = "LeFransua_tavern";
	
	curTable.l3.pic = FRP_RESIDENCE;
	curTable.l3.tex = FRT_RESIDENCE;
	curTable.l3.location = "LeFransua_townhall";

	makearef(curTable,objFastReloadTable.table.Havana);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "Havana_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "Havana_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "Havana_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "Havana_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "Havana_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "Havana_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "Havana_PortOffice";
	
	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "Havana_prison";
	
	makearef(curTable,objFastReloadTable.table.Charles);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "Charles_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "Charles_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "Charles_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "Charles_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "Charles_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "Charles_church";
	
	curTable.l7.pic = FRP_BROTHEL;
	curTable.l7.tex = FRT_BROTHEL;
	curTable.l7.location = "Charles_brothel";

	curTable.l8.pic = FRP_PORT_OFFICE;
	curTable.l8.tex = FRT_PORT_OFFICE;
	curTable.l8.location = "Charles_PortOffice";

	curTable.l9.pic = FRP_PRISON;
	curTable.l9.tex = FRT_PRISON;
	curTable.l9.location = "Charles_prison";

	makearef(curTable,objFastReloadTable.table.PortPax);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "PortPax_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "PortPax_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "PortPax_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "PortPax_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "PortPax_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "PortPax_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "PortPax_PortOffice";

	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "PortPax_prison";

	makearef(curTable,objFastReloadTable.table.SanJuan);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "SanJuan_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "SanJuan_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "SanJuan_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "SanJuan_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "SanJuan_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "SanJuan_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "SanJuan_PortOffice";

	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "SanJuan_prison";

	makearef(curTable,objFastReloadTable.table.SantoDomingo);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "SantoDomingo_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "SantoDomingo_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "SantoDomingo_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "SantoDomingo_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "SantoDomingo_Bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "SantoDomingo_church";
	
	curTable.l7.pic = FRP_BROTHEL;
	curTable.l7.tex = FRT_BROTHEL;
	curTable.l7.location = "SantoDomingo_brothel";

	curTable.l8.pic = FRP_PORT_OFFICE;
	curTable.l8.tex = FRT_PORT_OFFICE;
	curTable.l8.location = "SantoDomingo_PortOffice";

	curTable.l9.pic = FRP_PRISON;
	curTable.l9.tex = FRT_PRISON;
	curTable.l9.location = "SantoDomingo_prison";

	makearef(curTable,objFastReloadTable.table.PortSpein);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "PortSpein_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "PortSpein_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "PortSpein_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "PortSpein_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "PortSpein_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "PortSpein_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "PortSpein_PortOffice";

	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "PortSpein_prison";

	makearef(curTable,objFastReloadTable.table.Marigo);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "Marigo_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "Marigo_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "Marigo_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "Marigo_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "Marigo_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "Marigo_church";
	
	curTable.l7.pic = FRP_BROTHEL;
	curTable.l7.tex = FRT_BROTHEL;
	curTable.l7.location = "Marigo_brothel";

	curTable.l8.pic = FRP_PORT_OFFICE;
	curTable.l8.tex = FRT_PORT_OFFICE;
	curTable.l8.location = "Marigo_PortOffice";

	curTable.l9.pic = FRP_PRISON;
	curTable.l9.tex = FRT_PRISON;
	curTable.l9.location = "Marigo_prison";

	makearef(curTable,objFastReloadTable.table.Tortuga);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "Tortuga_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "Tortuga_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "Tortuga_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "Tortuga_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "Tortuga_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "Tortuga_church";
	
	curTable.l7.pic = FRP_BROTHEL;
	curTable.l7.tex = FRT_BROTHEL;
	curTable.l7.location = "Tortuga_brothel";

	curTable.l8.pic = FRP_PORT_OFFICE;
	curTable.l8.tex = FRT_PORT_OFFICE;
	curTable.l8.location = "Tortuga_PortOffice";

	curTable.l9.pic = FRP_PRISON;
	curTable.l9.tex = FRT_PRISON;
	curTable.l9.location = "Tortuga_prison";

	makearef(curTable,objFastReloadTable.table.Panama);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "Panama_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "Panama_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "Panama_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "Panama_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "Panama_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "Panama_church";
	
	curTable.l7.pic = FRP_BROTHEL;
	curTable.l7.tex = FRT_BROTHEL;
	curTable.l7.location = "Panama_brothel";

	curTable.l8.pic = FRP_PORT_OFFICE;
	curTable.l8.tex = FRT_PORT_OFFICE;
	curTable.l8.location = "Panama_PortOffice";

	curTable.l9.pic = FRP_PRISON;
	curTable.l9.tex = FRT_PRISON;
	curTable.l9.location = "Panama_prison";

	makearef(curTable,objFastReloadTable.table.PortoBello);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "PortoBello_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "PortoBello_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "PortoBello_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "PortoBello_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "PortoBello_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "PortoBello_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "PortoBello_PortOffice";
	
	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "PortoBello_prison";
	
	makearef(curTable,objFastReloadTable.table.Cartahena);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "Cartahena_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "Cartahena_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "Cartahena_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "Cartahena_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "Cartahena_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "Cartahena_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "Cartahena_PortOffice";

	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "Cartahena_prison";

	makearef(curTable,objFastReloadTable.table.Maracaibo);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "Maracaibo_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "Maracaibo_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "Maracaibo_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "Maracaibo_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "Maracaibo_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "Maracaibo_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "Maracaibo_PortOffice";
	
	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "Maracaibo_prison";
	
	makearef(curTable,objFastReloadTable.table.Caracas);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "Caracas_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "Caracas_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "Caracas_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "Caracas_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "Caracas_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "Caracas_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "Caracas_PortOffice";

	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "Caracas_prison";

	makearef(curTable,objFastReloadTable.table.Cumana);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "Cumana_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "Cumana_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "Cumana_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "Cumana_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "Cumana_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "Cumana_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "Cumana_PortOffice";

	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "Cumana_prison";

	makearef(curTable,objFastReloadTable.table.SantaCatalina);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "SantaCatalina_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "SantaCatalina_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "SantaCatalina_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "SantaCatalina_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "SantaCatalina_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "SantaCatalina_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "SantaCatalina_PortOffice";
	
	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "SantaCatalina_prison";
	
	makearef(curTable,objFastReloadTable.table.Beliz);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "Beliz_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "Beliz_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "Beliz_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "Beliz_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "Beliz_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "Beliz_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "Beliz_PortOffice";

	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "Beliz_prison";

	makearef(curTable,objFastReloadTable.table.SanAndres);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "SanAndres_store";
	
	curTable.l2.pic = FRP_SHIPYARD;
	curTable.l2.tex = FRT_SHIPYARD;
	curTable.l2.location = "SanAndres_shipyard";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "SanAndres_tavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "SanAndres_townhall";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "SanAndres_bank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "SanAndres_church";

	curTable.l7.pic = FRP_PORT_OFFICE;
	curTable.l7.tex = FRT_PORT_OFFICE;
	curTable.l7.location = "SanAndres_PortOffice";
	
	curTable.l8.pic = FRP_PRISON;
	curTable.l8.tex = FRT_PRISON;
	curTable.l8.location = "SanAndres_prison";
	
	makearef(curTable,objFastReloadTable.table.LostShipsCity);
	
	curTable.l1.pic = FRP_STORE;
	curTable.l1.tex = FRT_STORE;
	curTable.l1.location = "EsmeraldaStoreBig";
	
	curTable.l3.pic = FRP_TAVERN;
	curTable.l3.tex = FRT_TAVERN;
	curTable.l3.location = "FleuronTavern";
	
	curTable.l4.pic = FRP_RESIDENCE;
	curTable.l4.tex = FRT_RESIDENCE;
	curTable.l4.location = "SanAugustineResidence";
	
	curTable.l5.pic = FRP_USURER;
	curTable.l5.tex = FRT_USURER;
	curTable.l5.location = "CarolineBank";
	
	curTable.l6.pic = FRP_CHURCH;
	curTable.l6.tex = FRT_CHURCH;
	curTable.l6.location = "GloriaChurch";
}

void InitTownTable()
{
	
	objTownStateTable.towns.t1.name = "SentJons";
	objTownStateTable.towns.t1.captured = false;
	objTownStateTable.towns.t1.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t1.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t1.crew.data.year = 1;
	objTownStateTable.towns.t1.crew.data.month = 1;
	objTownStateTable.towns.t1.crew.data.day = 1;

	objTownStateTable.towns.t2a.name = "Bridgetown";
	objTownStateTable.towns.t2a.captured = false;
	objTownStateTable.towns.t2a.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t2a.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t2a.crew.data.year = 1;
	objTownStateTable.towns.t2a.crew.data.month = 1;
	objTownStateTable.towns.t2a.crew.data.day = 1;

	objTownStateTable.towns.t2.name = "PortRoyal";
	objTownStateTable.towns.t2.captured = false;
	objTownStateTable.towns.t2.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t2.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t2.crew.data.year = 1;
	objTownStateTable.towns.t2.crew.data.month = 1;
	objTownStateTable.towns.t2.crew.data.day = 1;

	objTownStateTable.towns.t3.name = "Villemstad";
	objTownStateTable.towns.t3.captured = false;
	objTownStateTable.towns.t3.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t3.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t3.crew.data.year = 1;
	objTownStateTable.towns.t3.crew.data.month = 1;
	objTownStateTable.towns.t3.crew.data.day = 1;

	objTownStateTable.towns.t4.name = "BasTer";
	objTownStateTable.towns.t4.captured = false;
	objTownStateTable.towns.t4.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t4.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t4.crew.data.year = 1;
	objTownStateTable.towns.t4.crew.data.month = 1;
	objTownStateTable.towns.t4.crew.data.day = 1;

	objTownStateTable.towns.t5.name = "Pirates";
	objTownStateTable.towns.t5.captured = false;
	objTownStateTable.towns.t5.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t5.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t5.crew.data.year = 1;
	objTownStateTable.towns.t5.crew.data.month = 1;
	objTownStateTable.towns.t5.crew.data.day = 1;
	
	objTownStateTable.towns.t6.name = "Santiago";
	objTownStateTable.towns.t6.captured = false;
	objTownStateTable.towns.t6.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t6.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t6.crew.data.year = 1;
	objTownStateTable.towns.t6.crew.data.month = 1;
	objTownStateTable.towns.t6.crew.data.day = 1;
	
	objTownStateTable.towns.t7.name = "LaVega";
	objTownStateTable.towns.t7.captured = false;
	objTownStateTable.towns.t7.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t7.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t7.crew.data.year = 1;
	objTownStateTable.towns.t7.crew.data.month = 1;
	objTownStateTable.towns.t7.crew.data.day = 1;

	objTownStateTable.towns.t8.name = "PuertoPrincipe";
	objTownStateTable.towns.t8.captured = false;
	objTownStateTable.towns.t8.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t8.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t8.crew.data.year = 1;
	objTownStateTable.towns.t8.crew.data.month = 1;
	objTownStateTable.towns.t8.crew.data.day = 1;
	
	objTownStateTable.towns.t9.name = "FortFrance";
	objTownStateTable.towns.t9.captured = false;
	objTownStateTable.towns.t9.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t9.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t9.crew.data.year = 1;
	objTownStateTable.towns.t9.crew.data.month = 1;
	objTownStateTable.towns.t9.crew.data.day = 1;
	
	objTownStateTable.towns.t10.name = "LeFransua";
	objTownStateTable.towns.t10.captured = false;
	objTownStateTable.towns.t10.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t10.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t10.crew.data.year = 1;
	objTownStateTable.towns.t10.crew.data.month = 1;
	objTownStateTable.towns.t10.crew.data.day = 1;

	objTownStateTable.towns.t11.name = "Havana";
	objTownStateTable.towns.t11.captured = false;
	objTownStateTable.towns.t11.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t11.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t11.crew.data.year = 1;
	objTownStateTable.towns.t11.crew.data.month = 1;
	objTownStateTable.towns.t11.crew.data.day = 1;
	
	objTownStateTable.towns.t12.name = "Charles";
	objTownStateTable.towns.t12.captured = false;
	objTownStateTable.towns.t12.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t12.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t12.crew.data.year = 1;
	objTownStateTable.towns.t12.crew.data.month = 1;
	objTownStateTable.towns.t12.crew.data.day = 1;
	
	objTownStateTable.towns.t13.name = "PortPax";
	objTownStateTable.towns.t13.captured = false;
	objTownStateTable.towns.t13.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t13.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t13.crew.data.year = 1;
	objTownStateTable.towns.t13.crew.data.month = 1;
	objTownStateTable.towns.t13.crew.data.day = 1;
	
	objTownStateTable.towns.t14.name = "SanJuan";
	objTownStateTable.towns.t14.captured = false;
	objTownStateTable.towns.t14.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t14.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t14.crew.data.year = 1;
	objTownStateTable.towns.t14.crew.data.month = 1;
	objTownStateTable.towns.t14.crew.data.day = 1;
	
	objTownStateTable.towns.t15.name = "SantoDomingo";
	objTownStateTable.towns.t15.captured = false;
	objTownStateTable.towns.t15.crew.quantity = 100 + Rand(100);
	objTownStateTable.towns.t15.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t15.crew.data.year = 1;
	objTownStateTable.towns.t15.crew.data.month = 1;
	objTownStateTable.towns.t15.crew.data.day = 1;

	objTownStateTable.towns.t17.name = "PortSpein";
	objTownStateTable.towns.t17.captured = false;
	objTownStateTable.towns.t17.crew.quantity = 100 + Rand(100);
	objTownStateTable.towns.t17.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t17.crew.data.year = 1;
	objTownStateTable.towns.t17.crew.data.month = 1;
	objTownStateTable.towns.t17.crew.data.day = 1;

	objTownStateTable.towns.t18.name = "Marigo";
	objTownStateTable.towns.t18.captured = false;
	objTownStateTable.towns.t18.crew.quantity = 100 + Rand(100);
	objTownStateTable.towns.t18.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t18.crew.data.year = 1;
	objTownStateTable.towns.t18.crew.data.month = 1;
	objTownStateTable.towns.t18.crew.data.day = 1;

	objTownStateTable.towns.t19.name = "Tortuga";
	objTownStateTable.towns.t19.captured = false;
	objTownStateTable.towns.t19.crew.quantity = 100 + Rand(100);
	objTownStateTable.towns.t19.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t19.crew.data.year = 1;
	objTownStateTable.towns.t19.crew.data.month = 1;
	objTownStateTable.towns.t19.crew.data.day = 1;

	objTownStateTable.towns.t20.name = "FortOrange";
	objTownStateTable.towns.t20.captured = false;
	objTownStateTable.towns.t20.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t20.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t20.crew.data.year = 1;
	objTownStateTable.towns.t20.crew.data.month = 1;
	objTownStateTable.towns.t20.crew.data.day = 1;

	objTownStateTable.towns.t21.name = "Panama";
	objTownStateTable.towns.t21.captured = false;
	objTownStateTable.towns.t21.crew.quantity = 200 + Rand(300);
	objTownStateTable.towns.t21.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t21.crew.data.year = 1;
	objTownStateTable.towns.t21.crew.data.month = 1;
	objTownStateTable.towns.t21.crew.data.day = 1;

	objTownStateTable.towns.t22.name = "PortoBello";
	objTownStateTable.towns.t22.captured = false;
	objTownStateTable.towns.t22.crew.quantity = 100 + Rand(100);
	objTownStateTable.towns.t22.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t22.crew.data.year = 1;
	objTownStateTable.towns.t22.crew.data.month = 1;
	objTownStateTable.towns.t22.crew.data.day = 1;

	objTownStateTable.towns.t23.name = "Cartahena";
	objTownStateTable.towns.t23.captured = false;
	objTownStateTable.towns.t23.crew.quantity = 100 + Rand(100);
	objTownStateTable.towns.t23.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t23.crew.data.year = 1;
	objTownStateTable.towns.t23.crew.data.month = 1;
	objTownStateTable.towns.t23.crew.data.day = 1;
	
	objTownStateTable.towns.t24.name = "Maracaibo";
	objTownStateTable.towns.t24.captured = false;
	objTownStateTable.towns.t24.crew.quantity = 100 + Rand(100);
	objTownStateTable.towns.t24.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t24.crew.data.year = 1;
	objTownStateTable.towns.t24.crew.data.month = 1;
	objTownStateTable.towns.t24.crew.data.day = 1;

	objTownStateTable.towns.t25.name = "Caracas";
	objTownStateTable.towns.t25.captured = false;
	objTownStateTable.towns.t25.crew.quantity = 100 + Rand(100);
	objTownStateTable.towns.t25.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t25.crew.data.year = 1;
	objTownStateTable.towns.t25.crew.data.month = 1;
	objTownStateTable.towns.t25.crew.data.day = 1;

	objTownStateTable.towns.t26.name = "Cumana";
	objTownStateTable.towns.t26.captured = false;
	objTownStateTable.towns.t26.crew.quantity = 100 + Rand(100);
	objTownStateTable.towns.t26.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t26.crew.data.year = 1;
	objTownStateTable.towns.t26.crew.data.month = 1;
	objTownStateTable.towns.t26.crew.data.day = 1;

	objTownStateTable.towns.t27.name = "SantaCatalina";
	objTownStateTable.towns.t27.captured = false;
	objTownStateTable.towns.t27.crew.quantity = 100 + Rand(100);
	objTownStateTable.towns.t27.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t27.crew.data.year = 1;
	objTownStateTable.towns.t27.crew.data.month = 1;
	objTownStateTable.towns.t27.crew.data.day = 1;

	objTownStateTable.towns.t28.name = "Beliz";
	objTownStateTable.towns.t28.captured = false;
	objTownStateTable.towns.t28.crew.quantity = 100 + Rand(100);
	objTownStateTable.towns.t28.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t28.crew.data.year = 1;
	objTownStateTable.towns.t28.crew.data.month = 1;
	objTownStateTable.towns.t28.crew.data.day = 1;
	
	objTownStateTable.towns.t29.name = "SanAndres";
	objTownStateTable.towns.t29.captured = false;
	objTownStateTable.towns.t29.crew.quantity = 100 + Rand(100);
	objTownStateTable.towns.t29.crew.morale = MORALE_NORMAL - 20 + Rand(40);
	objTownStateTable.towns.t29.crew.data.year = 1;
	objTownStateTable.towns.t29.crew.data.month = 1;
	objTownStateTable.towns.t29.crew.data.day = 1;
}
