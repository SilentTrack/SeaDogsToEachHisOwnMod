
void GenerateRumour()
{
    string RumText;
    ref CurRum;

   
   if ( isGoldFleet == 0 && Colonies[FindColony("Havana")].nation == SPAIN
    && Colonies[FindColony("PortoBello")].nation == SPAIN && rand(5) == 0 )
    {

        
        Log_TestInfo("loading GoldFleet "+XI_ConvertString("target_month_"+GetAddingDataMonth(0, 6, 0)));
        isGoldFleet = true;
        string sQuest = "GenerateGoldFleet";
        SetTimerCondition(sQuest, 0, 6, 0, false);
        pchar.quest.(sQuest).win_condition = "StartGoldFleet";
        pchar.quest.(sQuest).function= "StartGoldFleet";
        
        GoldMonth = XI_ConvertString("target_month_"+GetAddingDataMonth(0, 6, 0));
        AddTemplRumour("Init_GoldFleet", id_counter+1);
    }
    
    ref MerPrm;
    makeref(MerPrm, MerchantParam);
    if (!CheckAttribute(MerPrm, "active") || MerPrm.active == false)
    AddTemplRumour("MerchantOnMap", id_counter+1);
    
    if (rand(5)==0)AddTemplRumour("GetColonyPrices", id_counter+1);
    
    
    
}
