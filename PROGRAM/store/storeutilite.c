#define PRICE_TYPE_BUY	0
#define PRICE_TYPE_SELL	1

#define CONTRA_SELL		1
#define CONTRA_BUY		2

#event_handler("NextDay","StoreDayUpdateStart");
#event_handler("EvStoreDayUpdate","StoreDayUpdate");

 

void SetStoreGoods(ref _refStore,int _Goods,int _Quantity)
{
	string tmpstr = Goods[_Goods].name;
	_refStore.Goods.(tmpstr).Quantity = _Quantity;
}

void AddStoreGoods(ref _refStore,int _Goods,int _Quantity)
{
	aref refGoods;
	string tmpstr = Goods[_Goods].name;
	makearef(refGoods,_refStore.Goods.(tmpstr));
	int q = 0;
	if( CheckAttribute(refGoods,"Quantity") ) {q = sti(refGoods.Quantity);}
	refGoods.Quantity = q +_Quantity;
}

void RemoveStoreGoods(ref _refStore,int _Goods,int _Quantity)
{
	aref refGoods;
	string tmpstr = Goods[_Goods].name;
	makearef(refGoods,_refStore.Goods.(tmpstr));
	int q = 0;
	if( CheckAttribute(refGoods,"Quantity") ) q = sti(refGoods.Quantity);
	if(q < _Quantity) {refGoods.Quantity = 0;}
	else {refGoods.Quantity = q - _Quantity;}
}

int GetStoreGoodsQuantity(ref _refStore,int _Goods)
{
	string tmpstr = Goods[_Goods].name;
	int q = 0;
	if( CheckAttribute(_refStore,"Goods."+tmpstr) )
		q = sti(_refStore.Goods.(tmpstr).Quantity);
	return q;
}

int GetContrabandGoods(ref _refStore, int _Goods)
{
	string tmpstr = Goods[_Goods].name;
	if( CheckAttribute(_refStore,"Goods."+tmpstr+".canbecontraband") )
	{
		return sti(_refStore.Goods.(tmpstr).canbecontraband); 
	}
	return 0;	
}

string GetStoreGoodsType(ref _refStore,int _Goods)
{
	string tmpstr = Goods[_Goods].name;
	int tradeType = T_TYPE_NORMAL;
	if( CheckAttribute(_refStore,"Goods."+tmpstr) )
	{
		tradeType = sti(_refStore.Goods.(tmpstr).TradeType);
	}

	switch(tradeType)
	{
		case T_TYPE_NORMAL:
			return T_TYPE_NORMAL_NAME;
		break;
		case T_TYPE_EXPORT:
			return T_TYPE_EXPORT_NAME;
		break;
		case T_TYPE_IMPORT:
			return T_TYPE_IMPORT_NAME;
		break;
		case T_TYPE_AGGRESSIVE:
			return T_TYPE_AGGRESSIVE_NAME;
		break;
		case T_TYPE_CONTRABAND:
			return T_TYPE_CONTRABAND_NAME;
		break;
		case T_TYPE_AMMUNITION:
			return T_TYPE_AMMUNITION_NAME;
		break;
		case T_TYPE_CANNONS:   
			return T_TYPE_CANNONS_NAME;
		break;		
	}
	Trace("Missing trade type");
	return T_TYPE_NORMAL_NAME;
}

bool GetStoreGoodsUsed(ref _refStore,int _Goods)
{
	string tmpstr = Goods[_Goods].name;
	if( !CheckAttribute(_refStore,"Goods."+tmpstr) ) return false;
	if( sti(_refStore.Goods.(tmpstr).NotUsed)==true ) return false;
	
	if( sti(_refStore.Goods.(tmpstr).canbecontraband) == CONTRA_SELL || sti(_refStore.Goods.(tmpstr).TradeType) == T_TYPE_CONTRABAND)
	{
		if( !CheckOfficersPerk(GetMainCharacter(),"Trustworthy") ) return false;
	}	
	
	return true;
}

 
int GetStoreGoodsPrice(ref _refStore, int _Goods, int _PriceType, ref chref, int _qty)
{
	float _TradeSkill = GetSummonSkillFromNameToOld(chref,SKILL_COMMERCE); 
	aref refGoods;
	string tmpstr = Goods[_Goods].name;
	int basePrice = MakeInt(Goods[_Goods].Cost);
	if (!CheckAttribute(_refStore,"Goods."+tmpstr) ) return 0;
	makearef(refGoods,_refStore.Goods.(tmpstr));
 	int tradeType = MakeInt(refGoods.TradeType);
	int Type = MakeInt(refGoods.Type);	 

	float tradeModify 	= 1.0;
	float costCoeff		= 1.0;
	float priceModify   = 1.0;
	
	ref mc = GetMainCharacter();
	
	switch (tradeType)
	{	
		case T_TYPE_NORMAL:
			tradeModify = 1.00 + stf(refGoods.RndPriceModify); 
			break;
		case T_TYPE_EXPORT:
			tradeModify = 0.80 + stf(refGoods.RndPriceModify); 
			break;
		case T_TYPE_IMPORT:
			tradeModify = 1.20 + stf(refGoods.RndPriceModify); 
			break;
		case T_TYPE_AGGRESSIVE:
			tradeModify = 1.40 + stf(refGoods.RndPriceModify); 
			break;	
		case T_TYPE_CONTRABAND:
			tradeModify = 1.00 + stf(refGoods.RndPriceModify); 
			break;
		case T_TYPE_AMMUNITION:
			tradeModify = 1.00 + stf(refGoods.RndPriceModify);
			break;  
		case T_TYPE_CANNONS:
			tradeModify = 1.00 + stf(refGoods.RndPriceModify); 
			break;				
	}
	tradeModify = tradeModify * stf(refGoods.AddPriceModify);

	float skillModify;
	float cModify = 1.0;
	
	if(_PriceType == PRICE_TYPE_BUY) 
	{
		skillModify = 1.325 - _TradeSkill * 0.005; 
		if(tradeType == T_TYPE_CANNONS) cModify = 3.0 + MOD_SKILL_ENEMY_RATE/5.0;
		if(CheckCharacterPerk(chref,"HT2"))
		{
			if(CheckOfficersPerk(chref,"ProfessionalCommerce"))	{ skillModify -= 0.20; }
			else
			{
				if(CheckOfficersPerk(chref,"BasicCommerce"))	{ skillModify -= 0.15; }
				else skillModify -= 0.05;
			}						
		}
		else
		{
			if(CheckOfficersPerk(chref,"ProfessionalCommerce"))	{ skillModify -= 0.15; }
			else
			{
				if(CheckOfficersPerk(chref,"BasicCommerce"))	{ skillModify -= 0.10; }
			}				
		}
	}
	else	
	{
		skillModify = 0.675 + _TradeSkill * 0.005; 
		if(CheckCharacterPerk(chref,"HT2"))
		{
			if(CheckOfficersPerk(chref,"ProfessionalCommerce"))	skillModify += 0.20;
			else
			{
				if(CheckOfficersPerk(chref,"AdvancedCommerce"))	{ skillModify += 0.15; }
				else skillModify += 0.05;
			}				
		}
		else
		{
			if(CheckOfficersPerk(chref,"ProfessionalCommerce"))	skillModify += 0.15;
			else
			{
				if(CheckOfficersPerk(chref,"AdvancedCommerce"))	{ skillModify += 0.10; }
			}		
		}
						
		if(CheckAttribute(mc,"Goods." + (tmpstr) + ".costCoeff"))
		{
			costCoeff = stf(mc.Goods.(tmpstr).costCoeff);
		}
	}

	
	if (MakeInt(basePrice * tradeModify * skillModify * costCoeff + 0.5) < 1) return 1;
	
	
	switch (Type)
	{
		case T_TYPE_NORMAL			:
			priceModify = 1.0;
			break;
		case T_TYPE_AMMUNITION		:
			priceModify = 1.0;
			break;
		case T_TYPE_CROWN			:
			priceModify = 5.0;
			break;
		case T_TYPE_EXPORT			:
			priceModify = 2.0;
			break;
		case T_TYPE_IMPORT			:
			priceModify = 3.0;
			break;
		case T_TYPE_UNIQUE			:
			priceModify = 10.0;
			break;
		case T_TYPE_CANNONS 		:
			priceModify = 1.0;
			break;
	}
	
    return MakeInt(priceModify * basePrice * tradeModify * skillModify * _qty * costCoeff * cModify + 0.5);
}


float GetStoreGoodsRndPriceModify(ref _refStore, int _Goods, int _PriceType, ref chref, int _price)
{
    float skillModify;
	float _TradeSkill = GetSummonSkillFromNameToOld(chref,SKILL_COMMERCE);
	aref refGoods;
	string tmpstr = Goods[_Goods].name;
	int basePrice = MakeInt(Goods[_Goods].Cost);
	if (!CheckAttribute(_refStore,"Goods."+tmpstr) ) return 0;
	makearef(refGoods,_refStore.Goods.(tmpstr));
 	int tradeType = MakeInt(refGoods.TradeType);
	int Type = MakeInt(refGoods.Type);

	float tradeModify 	= 1.0;
	float priceModify   = 1.0;
	float cModify 		= 1.0;
	
	switch (Type)
	{
		case T_TYPE_NORMAL			:
			priceModify = 1.0;
			break;
		case T_TYPE_AMMUNITION		:
			priceModify = 1.0;
			break;
		case T_TYPE_CROWN			:
			priceModify = 5.0;
			break;
		case T_TYPE_EXPORT			:
			priceModify = 2.0;
			break;
		case T_TYPE_IMPORT			:
			priceModify = 3.0;
			break;
		case T_TYPE_UNIQUE			:
			priceModify = 10.0;
			break;
		case T_TYPE_CANNONS 		:
			priceModify = 1.0;
			break;
	}

    if(_PriceType == PRICE_TYPE_BUY) 
	{
		skillModify = 1.325 - _TradeSkill * 0.005; 
		if(tradeType == T_TYPE_CANNONS) cModify = 3.0 + MOD_SKILL_ENEMY_RATE/5.0;
		if(CheckCharacterPerk(chref,"HT2"))
		{
			if(CheckOfficersPerk(chref,"ProfessionalCommerce"))	{ skillModify -= 0.20; }
			else
			{
				if(CheckOfficersPerk(chref,"BasicCommerce"))	{ skillModify -= 0.15; }
				else skillModify -= 0.05;
			}						
		}
		else
		{
			if(CheckOfficersPerk(chref,"ProfessionalCommerce"))	{ skillModify -= 0.15; }
			else
			{
				if(CheckOfficersPerk(chref,"BasicCommerce"))	{ skillModify -= 0.10; }
			}				
		}	
	}
	else 
	{
		skillModify = 0.675 + _TradeSkill * 0.005; 
		if(CheckCharacterPerk(chref,"HT2"))
		{
			if(CheckOfficersPerk(chref,"ProfessionalCommerce"))	skillModify += 0.20;
			else
			{
				if(CheckOfficersPerk(chref,"AdvancedCommerce"))	{ skillModify += 0.15; }
				else skillModify += 0.05;
			}				
		}
		else
		{
			if(CheckOfficersPerk(chref,"ProfessionalCommerce"))	skillModify += 0.15;
			else
			{
				if(CheckOfficersPerk(chref,"AdvancedCommerce"))	{ skillModify += 0.10; }
			}		
		}
	}
	
	tradeModify = makefloat(_price) / (basePrice*skillModify * priceModify * cModify);
	
	tradeModify = tradeModify/stf(refGoods.AddPriceModify);
	
	switch (tradeType)
	{
		case T_TYPE_NORMAL:
			tradeModify = tradeModify - 1.00;
			break;
		case T_TYPE_EXPORT:
			tradeModify = tradeModify - 0.80; 
			break;
		case T_TYPE_IMPORT:
			tradeModify = tradeModify - 1.20; 
			break;
		case T_TYPE_AGGRESSIVE:
			tradeModify = tradeModify - 1.40; 
			break;	
		case T_TYPE_CONTRABAND:
			tradeModify = tradeModify - 1.00; 
			break;
		case T_TYPE_AMMUNITION:
			tradeModify = tradeModify - 1.00;
			break;
		case T_TYPE_CANNONS:
			tradeModify = tradeModify - 1.00;
			break;	
	}
	 
    return tradeModify;
}


void UpdateStore(ref pStore)
{	
	int 	oldQty;
	int 	Norm, delta;
	int 	TradeType;
	int 	Type; 
	string 	tmpstr, nsale;
    float 	rateInc 	= 0.0;
	float 	aim 		= 0.0;		
	float 	Manufacture = 0.0;	
	float 	Consumption = 0.0;	
	float   crunch		= 0.0;

	aref gref, curref, arTypes;
	makearef(gref, pStore.Goods);
	
	for(int i=0; i<GOODS_QUANTITY; i++)
	{
		tmpstr = Goods[i].name;
		if (!CheckAttribute(gref,tmpstr) ) continue;		
		makearef(curref, gref.(tmpstr));
		delta = 0;
				
		
		Manufacture = 0.0;					
		Consumption = 0.0;					
		oldQty 	= sti(curref.Quantity);		
		Norm	= sti(curref.Norm);			
		aim = frnd();
		if(Aim < 0.25) { Aim = 1.0; } 		
		else 
		{
			if(Aim > 0.70)	Aim = -1.0;		
			else 			Aim =  0.0; 	
		}
		Aim = Aim * Norm * (frnd() * 0.2 + frnd() * 0.2 + 0.1);
		
		if(aim >= 0.0) 	     				{Manufacture = 0.2;} 	
        if(oldQty > makeint(0.25 * Norm)) 	{Consumption = 0.1;}	

        oldQty = oldQty + makeint(Aim); 						    
		if(oldQty < 0)        				{oldQty = 0;}			

        if(oldQty < makeint(1.75 * Norm)) 
		{
			
			curref.Quantity = oldQty + makeint(( Manufacture - Consumption ) * Norm); 			
		}	
        else
		{
			
			crunch = frnd();  
            if(crunch < 0.15) 	curref.Quantity = makeint(Norm * frnd()); 	
            else				curref.Quantity = makeint(Norm * ( 1.75 + frnd() * 0.25 ));
		}
		if(sti(curref.Quantity) < 0) curref.Quantity = 0;	
		
				
		if( sti(Goods[i].type) == T_TYPE_UNIQUE || sti(Goods[i].type) == T_TYPE_CROWN ) curref.Quantity = 0;
		
		TradeType 	= sti(pStore.Goods.(tmpstr).TradeType);		
		Type 		= sti(pStore.Goods.(tmpstr).Type);	
		
		pStore.Goods.(tmpstr).canbecontraband = 0; 		
								
		if( TradeType == T_TYPE_CANNONS )
		{
			pStore.Goods.(tmpstr).canbecontraband = CONTRA_SELL;
			delta = makeint((oldQty - sti(curref.Norm))/7);
			curref.Quantity = oldQty - delta + (rand(2) - 1)*rand(sti(sti(curref.Norm) * 3/100));
			if(sti(Goods[i].NotSale) == 1) 
			{
				curref.Quantity = 0; continue;
			}		
		}
		else
		{
			if(Type == T_TYPE_EXPORT || Type == T_TYPE_IMPORT )
			{
				if(sti(curref.Quantity) < makeint(0.80 * Norm)) 
				{
					pStore.Goods.(tmpstr).canbecontraband = CONTRA_SELL; 
				}				
				if(sti(curref.Quantity) > makeint(1.20 * Norm))
				{
					pStore.Goods.(tmpstr).canbecontraband = CONTRA_BUY; 
				}
			}				
		}

		if( TradeType == T_TYPE_CONTRABAND )	
		{
			pStore.Goods.(tmpstr).canbecontraband = CONTRA_SELL;	
		}
				
		if(stf(curref.Norm) > 0.0)
		{
			rateInc = stf(curref.Quantity) / stf(curref.Norm);
			curref.AddPriceModify = AddPriceModify(rateInc);
		}
 		
	}
}

float AddPriceModify(float rateInc)
{
	float modifier = 1.05 - (rateInc /20.0));
	return modifier;
}

void SetStoresTradeUsed(int StoreNum,int GoodsNum,bool goodsUsed)
{
	string tmpstr = Goods[GoodsNum].Name;
	Stores[StoreNum].Goods.(tmpstr).NotUsed = !goodsUsed;
}

int storeDayUpdateCnt = -1;
void StoreDayUpdateStart()
{	

	Event("EvSituationsUpdate", "l", 0);   


	if(storeDayUpdateCnt >= 0) return;
	storeDayUpdateCnt = 0;
	PostEvent("EvStoreDayUpdate", 30);
}

void StoreDayUpdate()
{
	if(storeDayUpdateCnt >= 0)
	{
		UpdateStore(&Stores[storeDayUpdateCnt]);
		storeDayUpdateCnt++;
		if(storeDayUpdateCnt >= STORE_QUANTITY) storeDayUpdateCnt = -1;
		PostEvent("EvStoreDayUpdate", 30);
	}
}

void FillShipStore( ref chr)
{
	ref pRef = &stores[SHIP_STORE];
	
	int iQuantity = 0;
	string goodName;
	
	for(int i = 0; i<GOODS_QUANTITY; i++)
	{
		iQuantity = GetCargoGoods(chr, i); 
		SetStoreGoods(pref, i, iQuantity);

		goodName = Goods[i].name;
		pRef.Goods.(goodName).RndPriceModify = 1.0;
	}
}

int FindStore(string sColony)
{
	for(int i = 0; i < STORE_QUANTITY; i++)
	{
		if (Stores[i].colony == sColony)
		{
			return i;
		}
	}
	return -1;
}

void CheckForGoodsSpoil(aref chr)
{
	int iGoodsQ = 0;
	for(int i = 0; i < GOODS_QUANTITY; i++)
	{
		iGoodsQ = GetCargoGoods(chr, i);
		if(iGoodsQ > 0)
		{
			if(CheckAttribute(&Goods[i], "AfraidWater"))
			{
				if(sti(Goods[i].AfraidWater) > 0)
				{
					iGoodsQ = iGoodsQ - sti(Goods[i].AfraidWater);
					if(iGoodsQ < 0)
					{
						iGoodsQ = 0;
					}
					SetCharacterGoods(chr, i, iGoodsQ);
				}
			}
		}
	}
}

int GetStoreFreeSpace(object refStore)
{
	int iGoodsQ = 0;
	int iWeight = 0;
	for(int i = 0; i < GOODS_QUANTITY; i++)
	{
		iGoodsQ = GetStoreGoodsQuantity(refStore, i);
		iWeight = iWeight + iGoodsQ * stf(Goods[i].weight);
	}
	return iWeight;
}


string GetGoodsNameAlt(int idx)
{
    string ret;
    int iSeaGoods = LanguageOpenFile("ShipEatGood.txt");
    ret = LanguageConvertString(iSeaGoods, "seg_" + Goods[idx].Name);
    LanguageCloseFile(iSeaGoods);

    return ret;
}


void SetPriceListByStoreMan(ref rchar)   
{
    ref refStore, nulChr;
    string attr1, sGoods;
    int i, tradeType;
    string tmpstr;
    aref   refGoods;

    nulChr = &NullCharacter;

    if (sti(rchar.StoreNum) >= 0)
    {
        refStore = &stores[sti(rchar.StoreNum)];
        attr1 = rchar.id; 
        for (i = 0; i < GOODS_QUANTITY; i++)
        {
            sGoods = "Gidx" + i;
        	tmpstr = Goods[i].name;
        	tradeType = 0;
        	if (CheckAttribute(refStore,"Goods."+tmpstr))
        	{
        	   makearef(refGoods, refStore.Goods.(tmpstr));
         	   tradeType = MakeInt(refGoods.TradeType);
         	}
            nulChr.PriceList.(attr1).(sGoods).tradeType = tradeType; 
            nulChr.PriceList.(attr1).(sGoods).Buy  = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_BUY,  pchar, 1);            
			if (tradeType == T_TYPE_CONTRABAND && !bBettaTestMode)
            {
                nulChr.PriceList.(attr1).(sGoods).Buy  = "???";
            }
            nulChr.PriceList.(attr1).(sGoods).Sell = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_SELL, pchar, 1);  
			if (tradeType == T_TYPE_CONTRABAND && !bBettaTestMode)
            {
                nulChr.PriceList.(attr1).(sGoods).Sell  = "???";
            }			
            nulChr.PriceList.(attr1).(sGoods).Qty  = GetStoreGoodsQuantity(refStore, i);
			if (tradeType == T_TYPE_CONTRABAND && !bBettaTestMode)
            {
                nulChr.PriceList.(attr1).(sGoods).Qty  = "???";
            }
        }
        nulChr.PriceList.(attr1).AltDate = GetQuestBookDataDigit();
    }
}


void SetNull2StoreMan(ref rchar)
{
    ref refStore;
    int i;
    string tmpstr

    if (sti(rchar.StoreNum) >= 0)
    {
        refStore = &stores[sti(rchar.StoreNum)];

        for (i = 0; i < GOODS_QUANTITY; i++)
        {
            tmpstr = Goods[i].name;
        	if( CheckAttribute(refStore,"Goods."+tmpstr) )
        	{
        		refStore.Goods.(tmpstr).Quantity = 0;
            }
        }
    }
}


void SetNull2StoreGood(ref rchar, int iGood)
{
    ref refStore;
    string tmpstr;

    if (sti(rchar.StoreNum) >= 0)
    {
        refStore = &stores[sti(rchar.StoreNum)];
		tmpstr = Goods[iGood].name;
        if( CheckAttribute(refStore,"Goods."+tmpstr) )
        {
        	refStore.Goods.(tmpstr).Quantity = 0;
        }
    }
}


void SetNull2StoreManPart(ref rchar, float part)
{
    ref refStore;
    int i;
    string tmpstr

    if (sti(rchar.StoreNum) >= 0)
    {
        refStore = &stores[sti(rchar.StoreNum)];

        for (i = 0; i < GOODS_QUANTITY; i++)
        {
            tmpstr = Goods[i].name;
        	if (CheckAttribute(refStore,"Goods."+tmpstr) )
        	{
        		refStore.Goods.(tmpstr).Quantity = makeint(sti(refStore.Goods.(tmpstr).Quantity) / part);
            }
        }
    }
}


void SetNull2Deposit(string _city)
{
    if (CheckAttribute(Pchar, "quest.Deposits." + _city))
    {
        Log_Info("All investments of yours in " + GetCityName(_city) + " are gone.");
        DeleteAttribute(Pchar, "quest.Deposits." + _city);
    }
}

 
void SetStorageGoods(ref _refStore,int _Goods,int _Quantity, float _costCoeff)
{
	string tmpstr = Goods[_Goods].name;
	_refStore.Storage.Goods.(tmpstr).Quantity = _Quantity;
	if(_Quantity > 0)
	{
		_refStore.Storage.Goods.(tmpstr).costCoeff = _costCoeff;
	}
	else
	{
		_refStore.Storage.Goods.(tmpstr).costCoeff = 1.0;
	}	
}

float GetStorageGoodsCostCoeff(ref _refStore, int _Goods)
{
	float costCoeff = 1.0;
	string tmpstr = Goods[_Goods].name;
	if(CheckAttribute(_refStore,"Storage.Goods." + (tmpstr) + ".costCoeff" ))
	{
		costCoeff = stf(_refStore.Storage.Goods.(tmpstr).costCoeff);
	}
	return costCoeff;
}

void AddStorageGoods(ref _refStore,int _Goods,int _Quantity)
{
	aref refGoods;
	string tmpstr = Goods[_Goods].name;
	makearef(refGoods,_refStore.Storage.Goods.(tmpstr));
	int q = 0;
	if( CheckAttribute(refGoods,"Quantity") ) {q = sti(refGoods.Quantity);}
	refGoods.Quantity = q +_Quantity;
}

void RemoveStorageGoods(ref _refStore,int _Goods,int _Quantity)
{
	aref refGoods;
	string tmpstr = Goods[_Goods].name;
	makearef(refGoods,_refStore.Storage.Goods.(tmpstr));
	int q = 0;
	if( CheckAttribute(refGoods,"Quantity") ) q = sti(refGoods.Quantity);
	if(q<_Quantity) {refGoods.Quantity = 0;}
	else {refGoods.Quantity = q - _Quantity;}
}

int GetStorageGoodsQuantity(ref _refStore,int _Goods)
{
	aref refGoods;
	string tmpstr = Goods[_Goods].name;
	makearef(refGoods,_refStore.Storage.Goods.(tmpstr));
	int q = 0;
	if( CheckAttribute(_refStore,"Storage.Goods."+tmpstr) && CheckAttribute(refGoods,"Quantity"))
	{
		q = sti(_refStore.Storage.Goods.(tmpstr).Quantity);
	}	
	return q;
}

int GetStorageUsedWeight(object refStore)
{
	int iGoodsQ = 0;
	int iWeight = 0;
	for(int i = 0; i < GOODS_QUANTITY; i++)
	{
		iGoodsQ = GetStorageGoodsQuantity(refStore, i);
		iWeight = iWeight + GetGoodWeightByType(i, iGoodsQ)
	}
	return iWeight;
}

int GetStorage(string sColony)
{
	for(int i = 0; i < STORE_QUANTITY; i++)
	{
		if (Stores[i].colony == sColony)
		{
			return i;
		}
	}
	return -1;
}

