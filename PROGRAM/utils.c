#define PARSE_STRING	"PARSE_STRING"

#event_handler(PARSE_STRING, "ParseString");

int AddStr2Array(ref rNames, int iNum, string sStr)
{
	SetArraySize(rNames, iNum + 1);
	rNames[iNum] = sStr;
	iNum++;
	return iNum;
}

string GetSubStringByNum(string sStr, int iSelect)
{
	string sTemp;
	int iFindPos = findSubStr(&sStr, ",", 0);
	if (iFindPos < 0) return sStr;	
	int iNumFind = 1;
    while (iFindPos > 0)
	{
		iNumFind++;
		iFindPos = findSubStr(&sStr, ",", iFindPos + 1);
	}
	if (iNumFind <= iSelect)
	{
        return GetSubStringByNum(sStr, 0);
	}
	int	iLastPos = 0;
	iFindPos = 0;
	for (int i=0; i<iNumFind; i++)
	{
		iFindPos = findSubStr(&sStr, ",", iFindPos + 1);
		if (i == iSelect)
		{
			if (iFindPos < 0)
            {
                iFindPos = strlen(&sStr);
            }
            if (iLastPos >=  iFindPos) iFindPos = iLastPos + 2;
			sTemp = strcut(&sStr, iLastPos, iFindPos - 1);
			return sTemp;
		}
		iLastPos = iFindPos + 1;
	}

	return GetSubStringByNum(sStr, 0);
}

string GetRandSubString(string sStr)
{
	string sTemp;

    if (strlen(sStr) > 0)
    {
    	
    	int iFindPos = findSubStr(sStr, ",", 0);
    	if (iFindPos < 0) return sStr;	
    	int iNumFind = 1;
    	while (iFindPos > 0)
    	{
    		iNumFind++;
    		
    		iFindPos = findSubStr(sStr, ",", iFindPos + 1);
    	}
    	int iSelect = rand(iNumFind - 1);
    	int	iLastPos = 0;
    	iFindPos = 0; 
    	for (int i=0; i<iNumFind; i++)
    	{
    		
    		iFindPos = findSubStr(sStr, ",", iFindPos + 1);
    		if (i == iSelect)
    		{
    			if (iFindPos == -1)
                {
                    
                    iFindPos = strlen(sStr);
                }
                
                if (iLastPos >=  iFindPos) return "";
    			
    			sTemp = strcut(sStr, iLastPos, iFindPos - 1);
    			return sTemp;
    		}
    		iLastPos = iFindPos + 1;
    	}

    	return "If you see this, you can kick Vano :)";
	}
	return   "";
}


String GetRussianNumberString(int _num)
{
	if(_num < -999 || _num > 999) return "Error";
	if(_num == 0) return XI_ConvertString("zero");
	
	String numString = its(abs(_num));
	
	int strLength = strlen(numString);
	
	String ones = GetSymbol(numString, strLength - 1);
	String tens = GetSymbol(numString, strLength - 2) + "0";
	String hundreds = GetSymbol(numString, strLength - 3) + "00";
	
	numString = "";
	
	if(_num < 0)
	{
		numString = XI_ConvertString("minus") + " ";
	}
	
	if(tens == "10")
	{
		tens = "";
		ones = "1" + ones;
	}
	
	ones = XI_ConvertString(ones);
	
	if(tens != "")
	{
		tens = XI_ConvertString(tens) + " ";
	}
	
	if(hundreds != "")
	{
		hundreds = XI_ConvertString(hundreds) + " ";
	}
	
	return numString + hundreds + tens + ones;
}

float GetDotProduct(float fA1, float fA2)
{
    return cos(fA2 - fA1);  

	 
}

 

 

void ParseString()
{
	int		i, iLen;
	string	sParams[2];
	string	sDst = "";

	aref aRes = GetEventData();
	string rSourceString = GetEventData();
	int	iNumParameters = GetEventData();

	

	if (iNumParameters == 0)
	{
		aRes.Str = rSourceString;
		return;
	}

	SetArraySize(&sParams, iNumParameters + 1);
	for (i=0; i<iNumParameters; i++) { sParams[i] = GetEventData();	}

	iLen = strlen(&rSourceString);
	for (i=0; i<iLen; i++)
	{
		string sChar = GetSymbol(&rSourceString, i);
		if (sChar == "%")
		{
			if (GetSymbol(&rSourceString, i + 1) == "%")
			{
				sDst = sDst + "%"; 
				i++;
				continue;
			}
			
			string sNumber = "";
			i++;
			while (i < iLen)
			{
				string sTmp = GetSymbol(&rSourceString, i);
				if (!isDigit(&sTmp, 0)) { break; }
				sNumber = sNumber + sTmp;
				i++;
			}
			sDst = sDst + sParams[sti(sNumber) - 1]; i--;
			continue;
		}
		sDst = sDst + sChar;
	}

	aRes.Str = sDst;
}

float GetDistance2D(float x1, float y1, float x2, float y2)
{
	return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}


float GetDistance3D(float _x1, float _y1, float _z1, float _x2, float _y2, float _z2)
{
	return sqrt(sqr(_x1 - _x2) + sqr(_y1 - _y2) + sqr(_z1 - _z2));
}

void RotateAroundY(ref rX, ref rZ, float fCos, float fSin)
{
	float xxx = rX;
	float zzz = rZ;
	float xx = xxx * fCos + zzz * fSin;
	float zz = zzz * fCos - xxx * fSin;
	rX = xx;
	rZ = zz;
}

int Tonnes2CWT(int iTonnes)
{
	int a = makeint(iTonnes * 19.685 + 99);
	return a;
}

int CWT2Tonnes(int iCWT)
{
	int a = iCWT - 99;
	a = makeint(a / 19.685);
	return a;
}

int i_min(int a1, int a2)
{
	if (a1 < a2) { return a1; }
	return a2;
}

 


string GetVerNum()
{
 	string  VERSION_STR = VERSION_NUMBER2;

    if (MOD_BETTATESTMODE == "On")
    {
       VERSION_STR = VERSION_STR + "  DEV";
    }
    if (MOD_BETTATESTMODE == "Test")
    {
       VERSION_STR = VERSION_STR + "  TST";
    }
    return VERSION_STR;
}

void Log_Info(string _str)
{
    Log_SetStringToLog(_str);
}

void Log_TestInfo(string logtext)
{
	if (bBettaTestMode)
	{
		Log_SetStringToLog(logtext);
		trace("TestInfo: " + GetQuestBookDataDigit() + " " + logtext)
	}
}
void Log_QuestInfo(string _info)
{
    if (bQuestLogShow)
	{
		Log_SetStringToLog(_info);
	}
}

string NewStr()
{
    int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    string sTemp;
    sTemp = LanguageConvertString(idLngFile,"new_string");
    LanguageCloseFile(idLngFile);

    return sTemp;
}

Object objGrass;

void CreateGrass(string sDataFile, string sTextureFile, float fScale, float fW,float fH, float fMinDist,float fMaxDist, float fMinLod)
{
	CreateEntity(&objGrass,"Grass");
	if( bSeaActive && !bAbordageStarted )
	{
		LayerAddObject(SEA_EXECUTE,&objGrass,1000);
		LayerAddObject(SEA_REALIZE,&objGrass,1000);
	}
	else
	{
		LayerAddObject("execute",&objGrass,1000);
		LayerAddObject("realize",&objGrass,1000);
	}	
	SendMessage(objGrass,"ls",41666, sTextureFile); 
	SendMessage(objGrass,"lffffff",42666, fScale, fW,fH, fMinDist,fMaxDist, fMinLod); 
	SendMessage(objGrass,"ls",40666, sDataFile); 
}

void DeleteGrass()
{
	if (IsEntity(&objGrass))
	{
		DeleteClass(&objGrass); 
	}
	DeleteEntitiesByType("Grass");
}

void HideGrass()
{
	if (IsEntity(&objGrass))
	{
        LayerDelObject("execute", &objGrass);
		LayerDelObject("realize", &objGrass);
		LayerDelObject(SEA_EXECUTE, &objGrass);
		LayerDelObject(SEA_REALIZE, &objGrass);
	}
}

void ShowGrass()
{
	if (IsEntity(&objGrass))
	{
        LayerAddObject(SEA_EXECUTE, &objGrass, 1000);
		LayerAddObject(SEA_REALIZE, &objGrass, 1000);
	}
}

void CalcLocalTime(float _inc)
{
	if (locTmpTime >= _inc)
	{
		 
        locTmpTime = 0.0;
         
    }
}
void RefreshWeather()
{
    Whr_UpdateWeather();
	
	 
}
void RefreshLandTime()
{
    objLandInterface.textinfo.datatext.text = XI_convertString("Date:") + GetQuestBookData();
}

string stripblank(string str)
{
	string retstr = "";
	int iMax = strlen(str);
	for(int i = 0; i < iMax; i++) {
		if(GetSymbol(str,i) != " ") { retstr += GetSymbol(str,i); }}
	return retstr;
}


void ResetTimeScale()
{
    SetTimeScale(1.0);
	TimeScaleCounter = 0;
	if(IsPerkIntoList("TimeSpeed"))
	{	DelPerkFromActiveList("TimeSpeed");
	}
}

void FreeChangeFlagMode(string _tmp)
{
	DeleteAttribute(pchar, "DisableChangeFlagMode");
}

string  xiStr(string _str) 
{
	return XI_ConvertString(_str);
}

string  xiDStr(string _str) 
{
	return GetConvertStr(_str, "DialogSource.txt");
}

void Dev_Trace(string _str) 
{
    if (MOD_BETTATESTMODE	==	"On")	Trace(_str);
}


String FindStringAfterChar(string _string, string _char)
{
	int i = FindSubStr(_string, _char , 0);
	if(i == -1) return "";
	string sRetStr = strcut(_string, i+1, strlen(_string)-1);
	return sRetStr;
}

String FindStringBeforeChar(string _string, string _char) 
{
	int i = FindSubStr(_string, _char , 0);
	if(i == -1) return "";
	string sRetStr = strcut(_string, 0, i-1);
	return sRetStr;
}

bool HasSubStr(string _Str, string _sFindStr)
{
	bool bHas = FindSubStr(_Str, _sFindStr, 0) != -1;
	return bHas;
}


void Log_AStr(string _str) 
{
	Log_SetEternalString(_str);
}

void Log_TestAStr(string _str)
{
	if (bBettaTestMode)
	{
		Log_AStr(_str);
		trace("TestInfo: " + GetQuestBookDataDigit() + " " + _str)
	}
}

void Log_Clear()
{
	ClearAllLogStrings();
}


string TenSpaceStr()
{
	string sTemp = XI_ConvertString("TenSpace");
	return sTemp;
}


int GetCurrentModelrNumber()
{
	int n = 0;
	aref arModel;
	if (FindClass(&arModel, "modelr")) 
	{
		n++;
		while (FindClassNext(&arModel)) 
		{
			n++;
		}
	}
	trace("GetCurrentModelrNumber   n : " + n);
	return n;
}


