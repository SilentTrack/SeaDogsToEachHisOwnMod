string	sEnManFaces = "30,35,10,6,32,33,42,43";
string	sFrManFaces = "19,27,29,31,32,33,43,43";
string	sSpManFaces = "25,37,38,44,7,32,33,42,43";
string	sHoManFaces = "11,26,28,36,32,33,42,43";
string	sPoManFaces = "12,30,39,32,33,42,43";
string	sPiManFaces = "0,1,13,14,2,23,24,3,40,5";

void SetRandomFaceToCharacter(ref rCharacter)
{
	string sFaceID = "1";
	if (rCharacter.sex == "man")
	{
		switch (sti(rCharacter.nation))
		{
			case ENGLAND:	
				sFaceID = GetRandSubString(sEnManFaces); 
			break;
			case FRANCE:	
				sFaceID = GetRandSubString(sFrManFaces); 
			break;
			case SPAIN:		
				sFaceID = GetRandSubString(sSpManFaces); 
				break;
			case PIRATE:	
				sFaceID = GetRandSubString(sPiManFaces); 
				break;
			case HOLLAND:	
				sFaceID = GetRandSubString(sHoManFaces); 
				break;
		}
	}
	else
	{
		sFaceID = "16";
	}
	
	rCharacter.FaceId = sti(sFaceID);
}

void FaceMaker(aref rCharacter)
{
	// Warship 07.07.09 �������� � �������� "���� ������" - �� ����� ���� ���� - ���� � ��������
	if(rCharacter.ID == "MaryCelesteCapitan")
	{
		rCharacter.FaceId = 333;
		return;
	}
	if (findsubstr(rCharacter.model, "banker", 0) != -1)
	{
		rCharacter.FaceId = 1;
		return;
	}
	if (findsubstr(rCharacter.model, "gipsy", 0) != -1)
	{
		rCharacter.FaceId = 2;
		return;
	}
	if (findsubstr(rCharacter.ID, "_Lightman", 0) != -1)
	{
		rCharacter.FaceId = 3;
		return;
	}

	switch (rCharacter.model)
	{
		case "beatrice":		rCharacter.FaceId = 0; break;
		case "beatriceA":		rCharacter.FaceId = 0; break;
		//case "devlin":			rCharacter.FaceId = 1; break;

		//case "barmen_1":		rCharacter.FaceId = 2; break;
		//case "barmen_2":		rCharacter.FaceId = 3; break;
		case "barmen_3":		rCharacter.FaceId = 4; break;
		
		// --> ���
		// ����������� �������
		case "off_fra_1"	:		rCharacter.FaceId = 5; 		break;
		case "off_fra_2"	:		rCharacter.FaceId = 6; 		break;
		case "off_fra_3"	:		rCharacter.FaceId = 7; 		break;
		case "off_fra_4"	:		rCharacter.FaceId = 8; 		break;
		case "off_fra_5"	:		rCharacter.FaceId = 9; 		break;
		case "off_fra_6"	:		rCharacter.FaceId = 10; 	break;
		// ���������� �������
		case "off_eng_1"	:		rCharacter.FaceId = 11; 	break;
		case "off_eng_2"	:		rCharacter.FaceId = 12; 	break;
		case "off_eng_3"	:		rCharacter.FaceId = 13; 	break;
		case "off_eng_4"	:		rCharacter.FaceId = 14; 	break;
		case "off_eng_5"	:		rCharacter.FaceId = 15; 	break;
		case "off_eng_6"	:		rCharacter.FaceId = 16; 	break;
		// ����������� �������
		case "off_hol_1"	:		rCharacter.FaceId = 17; 	break;
		case "off_hol_2"	:		rCharacter.FaceId = 18; 	break;
		case "off_hol_3"	:		rCharacter.FaceId = 19; 	break;
		case "off_hol_4"	:		rCharacter.FaceId = 20; 	break;
		case "off_hol_5"	:		rCharacter.FaceId = 21; 	break;
		case "off_hol_6"	:		rCharacter.FaceId = 22; 	break;
		// ��������� �������
		case "off_spa_1"	:		rCharacter.FaceId = 23; 	break;
		case "off_spa_2"	:		rCharacter.FaceId = 24; 	break;
		case "off_spa_3"	:		rCharacter.FaceId = 25; 	break;
		case "off_spa_4"	:		rCharacter.FaceId = 26; 	break;
		case "off_spa_5"	:		rCharacter.FaceId = 27; 	break;
		case "off_spa_6"	:		rCharacter.FaceId = 28; 	break;
		// ��������-������������,  �������� ��������
		case "mercen_1"		: 		rCharacter.FaceId = 29;		break;
		case "mercen_2"		: 		rCharacter.FaceId = 30;		break;
		case "mercen_3"		: 		rCharacter.FaceId = 31;		break;
		case "mercen_4"		: 		rCharacter.FaceId = 32;		break;
		case "mercen_5"		: 		rCharacter.FaceId = 33;		break;
		case "mercen_6"		: 		rCharacter.FaceId = 34;		break;
		case "mercen_7"		: 		rCharacter.FaceId = 35;		break;
		case "mercen_8"		: 		rCharacter.FaceId = 36;		break;
		case "mercen_9"		: 		rCharacter.FaceId = 37;		break;
		case "mercen_10"	: 		rCharacter.FaceId = 38;		break;
		case "mercen_11"	: 		rCharacter.FaceId = 39;		break;
		case "mercen_12"	: 		rCharacter.FaceId = 40;		break;
		case "mercen_13"	: 		rCharacter.FaceId = 41;		break;
		case "mercen_14"	: 		rCharacter.FaceId = 42;		break;
		case "mercen_15"	: 		rCharacter.FaceId = 43;		break;
		// ��������-����������,  ��������� ��������
		case "mercen_16"	: 		rCharacter.FaceId = 44;		break;
		case "mercen_17"	: 		rCharacter.FaceId = 45;		break;
		case "mercen_18"	: 		rCharacter.FaceId = 46;		break;
		case "mercen_19"	: 		rCharacter.FaceId = 47;		break;
		case "mercen_20"	: 		rCharacter.FaceId = 48;		break;
		case "mercen_21"	: 		rCharacter.FaceId = 49;		break;
		case "mercen_22"	: 		rCharacter.FaceId = 50;		break;
		case "mercen_23"	: 		rCharacter.FaceId = 51;		break;
		case "mercen_24"	: 		rCharacter.FaceId = 52;		break;
		case "mercen_25"	: 		rCharacter.FaceId = 53;		break;
		case "mercen_26"	: 		rCharacter.FaceId = 54;		break;
		case "mercen_27"	: 		rCharacter.FaceId = 55;		break;
		case "mercen_28"	: 		rCharacter.FaceId = 56;		break;
		
		// ����������� ���������
		// �������
		case "citiz_1"		:		rCharacter.FaceId = 61; 	break;
		case "citiz_2"		:		rCharacter.FaceId = 62; 	break;
		case "citiz_3"		:		rCharacter.FaceId = 63; 	break;
		case "citiz_4"		:		rCharacter.FaceId = 64; 	break;
		case "citiz_5"		:		rCharacter.FaceId = 65; 	break;
		case "citiz_6"		:		rCharacter.FaceId = 66; 	break;
		case "citiz_7"		:		rCharacter.FaceId = 67; 	break;
		case "citiz_8"		:		rCharacter.FaceId = 68; 	break;
		case "citiz_9"		:		rCharacter.FaceId = 69; 	break;
		case "citiz_10"		:		rCharacter.FaceId = 70; 	break;
		// �������
		case "citiz_11"		:		rCharacter.FaceId = 71; 	break;
		case "citiz_12"		:		rCharacter.FaceId = 72; 	break;
		case "citiz_13"		:		rCharacter.FaceId = 73; 	break;
		case "citiz_14"		:		rCharacter.FaceId = 74; 	break;
		case "citiz_15"		:		rCharacter.FaceId = 75; 	break;
		case "citiz_16"		:		rCharacter.FaceId = 76; 	break;
		case "citiz_17"		:		rCharacter.FaceId = 77; 	break;
		case "citiz_18"		:		rCharacter.FaceId = 78; 	break;
		case "citiz_19"		:		rCharacter.FaceId = 79; 	break;
		case "citiz_20"		:		rCharacter.FaceId = 80; 	break;
		// ������������ (��������)
		case "citiz_21"		:		rCharacter.FaceId = 81; 	break;
		case "citiz_22"		:		rCharacter.FaceId = 82; 	break;
		case "citiz_23"		:		rCharacter.FaceId = 83; 	break;
		case "citiz_24"		:		rCharacter.FaceId = 84; 	break;
		case "citiz_25"		:		rCharacter.FaceId = 85; 	break;
		case "citiz_26"		:		rCharacter.FaceId = 86; 	break;
		case "citiz_27"		:		rCharacter.FaceId = 87; 	break;
		case "citiz_28"		:		rCharacter.FaceId = 88; 	break;
		case "citiz_29"		:		rCharacter.FaceId = 89; 	break;
		case "citiz_30"		:		rCharacter.FaceId = 90; 	break;		
		// �������
		case "citiz_31"		:		rCharacter.FaceId = 91; 	break;
		case "citiz_32"		:		rCharacter.FaceId = 92; 	break;
		case "citiz_33"		:		rCharacter.FaceId = 93; 	break;
		case "citiz_34"		:		rCharacter.FaceId = 94; 	break;
		case "citiz_35"		:		rCharacter.FaceId = 95; 	break;
		case "citiz_36"		:		rCharacter.FaceId = 96; 	break;
		case "citiz_37"		:		rCharacter.FaceId = 97; 	break;
		case "citiz_38"		:		rCharacter.FaceId = 98; 	break;
		case "citiz_39"		:		rCharacter.FaceId = 99; 	break;
		case "citiz_40"		:		rCharacter.FaceId = 100; 	break;
		// ������
		case "citiz_41"		:		rCharacter.FaceId = 101; 	break;
		case "citiz_42"		:		rCharacter.FaceId = 102; 	break;
		case "citiz_43"		:		rCharacter.FaceId = 103; 	break;
		case "citiz_44"		:		rCharacter.FaceId = 104; 	break;
		case "citiz_45"		:		rCharacter.FaceId = 105; 	break;
		case "citiz_46"		:		rCharacter.FaceId = 106; 	break;
		case "citiz_47"		:		rCharacter.FaceId = 107; 	break;
		case "citiz_48"		:		rCharacter.FaceId = 108; 	break;
		case "citiz_49"		:		rCharacter.FaceId = 109; 	break;
		case "citiz_50"		:		rCharacter.FaceId = 110; 	break;
		// ���
		case "citiz_51"		:		rCharacter.FaceId = 111; 	break;
		case "citiz_52"		:		rCharacter.FaceId = 112; 	break;
		case "citiz_53"		:		rCharacter.FaceId = 113; 	break;
		case "citiz_54"		:		rCharacter.FaceId = 114; 	break;
		case "citiz_55"		:		rCharacter.FaceId = 115; 	break;
		case "citiz_56"		:		rCharacter.FaceId = 116; 	break;
		case "citiz_57"		:		rCharacter.FaceId = 117; 	break;
		case "citiz_58"		:		rCharacter.FaceId = 118; 	break;
		case "citiz_59"		:		rCharacter.FaceId = 119; 	break;
		case "citiz_60"		:		rCharacter.FaceId = 120; 	break;		
		// �����������
		case "prizon_1"		:		rCharacter.FaceId = 137; 	break;		
		case "prizon_2"		:		rCharacter.FaceId = 138; 	break;		
		case "prizon_3"		:		rCharacter.FaceId = 139; 	break;		
		case "prizon_4"		:		rCharacter.FaceId = 140; 	break;		
		case "prizon_5"		:		rCharacter.FaceId = 141; 	break;		
		case "prizon_6"		:		rCharacter.FaceId = 142; 	break;		
		case "prizon_7"		:		rCharacter.FaceId = 143; 	break;		
		case "prizon_8"		:		rCharacter.FaceId = 144; 	break;		
		// ��������
		case "women_1"		:		rCharacter.FaceId = 151; 	break;
		case "women_2"		:		rCharacter.FaceId = 152; 	break;
		case "women_3"		:		rCharacter.FaceId = 153; 	break;
		case "women_4"		:		rCharacter.FaceId = 154; 	break;
		case "women_5"		:		rCharacter.FaceId = 155; 	break;
		case "women_6"		:		rCharacter.FaceId = 156; 	break;
		// ��������� ������� ��������
		case "women_7"		:		rCharacter.FaceId = 157; 	break;
		case "women_8"		:		rCharacter.FaceId = 158; 	break;
		case "women_9"		:		rCharacter.FaceId = 159; 	break;
		case "women_10"		:		rCharacter.FaceId = 160; 	break;
		// ��������� ������� ����������
		case "women_11"		:		rCharacter.FaceId = 161; 	break;
		case "women_12"		:		rCharacter.FaceId = 162; 	break;
		case "women_13"		:		rCharacter.FaceId = 163; 	break;
		case "women_14"		:		rCharacter.FaceId = 164; 	break;
		case "women_15"		:		rCharacter.FaceId = 165; 	break;
		case "women_16"		:		rCharacter.FaceId = 166; 	break;
		// �������
		case "women_17"		:		rCharacter.FaceId = 167; 	break;
		case "women_18"		:		rCharacter.FaceId = 168; 	break;
		// �����
		case "women_19"		:		rCharacter.FaceId = 169; 	break;
		case "women_20"		:		rCharacter.FaceId = 170; 	break;
		case "women_21"		:		rCharacter.FaceId = 171; 	break;
		case "women_22"		:		rCharacter.FaceId = 172; 	break;
		case "women_23"		:		rCharacter.FaceId = 173; 	break;
		case "women_24"		:		rCharacter.FaceId = 174; 	break;
		case "women_25"		:		rCharacter.FaceId = 175; 	break;
		case "women_26"		:		rCharacter.FaceId = 176; 	break;
		// ������
		case "monk_1"		:		rCharacter.FaceId = 194; 	break;
		case "monk_2"		:		rCharacter.FaceId = 195; 	break;
		case "monk_3"		:		rCharacter.FaceId = 196; 	break;
		case "monk_4"		:		rCharacter.FaceId = 197; 	break;
		case "monk_5"		:		rCharacter.FaceId = 198; 	break;
		case "monk_6"		:		rCharacter.FaceId = 199; 	break;	

		// ��������� ���������			
		// �������� ������� ������
		case "Migel_2"		:     	rCharacter.FaceId = 204; 	break;		// ������ ������
		case "Maskog"		:     	rCharacter.FaceId = 205; 	break;		// ���������
		case "Maskog_mush"	:     	rCharacter.FaceId = 205; 	break;		// ��������� - ������ ���������		
		case "Archy"		:		rCharacter.FaceId = 206; 	break;		// ��������� ��������
		case "Archy_mush"	:		rCharacter.FaceId = 206; 	break;		// ��������� �������� - ������ ���������		
		case "Alonso"		:		rCharacter.FaceId = 207; 	break;		// ������ �� ����������
		case "Alonso_mush"	:		rCharacter.FaceId = 207; 	break;		// ������ �� ���������� - ������ ���������
		
		// ��������� ������
		case "Jeckman"		:		rCharacter.FaceId = 208; 	break;		// ���� �������
		case "Hawk_1"		:		rCharacter.FaceId = 209;	break;		// ��������� ����
		case "Hawk_2"		:		rCharacter.FaceId = 209;	break;		// ��������� ����
		case "Marlow"		:		rCharacter.FaceId = 210;	break;		// ������� ������
		case "Terrax"		:		rCharacter.FaceId = 211;	break;		// ������ ������
		case "Barbazon"		:		rCharacter.FaceId = 212;	break;		// ��� ��������
		case "Svenson"		:		rCharacter.FaceId = 213;	break;		// �� �������
		
		// ����������� "����������� ������"
		case "huber_1"		:		rCharacter.FaceId = 214;	break;		// ����� ����������
		case "huber_25"		:		rCharacter.FaceId = 215;	break;		// ������ ���
		case "Lucas"		:		rCharacter.FaceId = 216;	break;		// ����� ���������
		case "Fleetwood"	: 		rCharacter.FaceId = 217;	break;		// ������ �������
		case "Merdok"		: 		rCharacter.FaceId = 218;	break;		// ���� ������
		case "VanBerg"		: 		rCharacter.FaceId = 219;	break;		// ���� ��� ����
		case "Longway"		: 		rCharacter.FaceId = 220;	break;		// �������
		case "Gaston"		: 		rCharacter.FaceId = 221;	break;		// �������� ������
		case "Tonzag"		: 		rCharacter.FaceId = 221;	break;		// ������ ������
		case "Kneepel"		: 		rCharacter.FaceId = 222;	break;		// ����� ��������
		case "Meriman_1"	: 		rCharacter.FaceId = 223;	break;		// ������ �������
		case "Meriman_2"	: 		rCharacter.FaceId = 223;	break;		// ������ �������
		case "Solomon"      :		rCharacter.FaceId = 224;	break;		// ������� �����
		case "Aby"      	:		rCharacter.FaceId = 225;	break;		// �������� �����		
		case "Rodriges"		: 		rCharacter.FaceId = 286;	break;		// �������� ��������
		
		// ����� "������ ���� � ��������"
		case "Gino"			: 		rCharacter.FaceId = 226;	break;		// ����� ��������
		case "Port_A"		: 		rCharacter.FaceId = 227;	break;		// ���� ����������
		case "Port_B"		: 		rCharacter.FaceId = 227;	break;		// ���� ����������
		case "Hugh"			: 		rCharacter.FaceId = 228;	break;		// ����� ��������
		case "VanShtal"		: 		rCharacter.FaceId = 229;	break;		// ����� ��� �����
		case "Vasces"		: 		rCharacter.FaceId = 230;	break;		// ������� ������
		
		// ���
		case "Itza_Kanek"	: 		rCharacter.FaceId = 231;	break;		// ����� - ��������� ���� ���
		case "Itza_Urakan"	: 		rCharacter.FaceId = 232;	break;		// ������ - ������� ����� ���
		
		// ����������
		case "DeLuck"		:		rCharacter.FaceId = 149;	break;		// ������ ������
		case "Mendosa"		:		rCharacter.FaceId = 233;	break;		// ��� ����� �� �������-�-����
		case "Vincento"		:		rCharacter.FaceId = 234;	break;		// ���� ��������
		case "Alexus"		:		rCharacter.FaceId = 235;	break;		// ������ �������
		case "Shaman"		:		rCharacter.FaceId = 236;	break;		// ������� ����
		case "Moscovit"		:		rCharacter.FaceId = 237;	break;		// ����� ��������
		case "Shark"		:		rCharacter.FaceId = 238;	break;		// ����� ������		
		case "Abbat"		:		rCharacter.FaceId = 239;	break;		// ����� �����
		case "Tomazo"		:		rCharacter.FaceId = 240;	break;		// ������
		case "Kumvana"		:		rCharacter.FaceId = 241;	break;		//  ������� (����� �������)
		case "Zikomo"		:		rCharacter.FaceId = 242;	break;		// ������ ������ (���� �������)
		case "Canib"		:		rCharacter.FaceId = 243;	break;		// ������������ (����� �������)
		case "Fox"			:		rCharacter.FaceId = 244;	break;		// ��������� ����
		
		// ��������� ����+LSC
		case "Balthrop"		:		rCharacter.FaceId = 249;	break;		// ������� �������
		case "Rumba"		:		rCharacter.FaceId = 250;	break;		// ���� ��������
		case "Gladys"		:		rCharacter.FaceId = 251;	break;		//  ������ ��������
		case "Donovan"		:		rCharacter.FaceId = 252;	break;		// ����� �������
		case "Danny"		:		rCharacter.FaceId = 253;	break;		// ������� ����
		case "keeper_1"		:		rCharacter.FaceId = 254;	break;		// �������� ������
		case "Norman_1"		:		rCharacter.FaceId = 255;	break;		// ������� ������
		case "Norman_2"		:		rCharacter.FaceId = 255;	break;		// ������� ������
		case "Baker"		:		rCharacter.FaceId = 256;	break;		// ������� ������
		case "Ghost_1"		:		rCharacter.FaceId = 259;	break;		// �������� (������)
		case "Black"		:		rCharacter.FaceId = 260;	break;		// ���� ����
		case "Carpentero"	:		rCharacter.FaceId = 262;	break;		// ����� ����������
		case "Mechanic"		:		rCharacter.FaceId = 263;	break;		// ������ �������
		case "Schmidt"		:		rCharacter.FaceId = 264;	break;		// ����� �����
		case "Ole"			:		rCharacter.FaceId = 265;	break;		// ��� ����������� (����� �������)
		case "Chimiset"		:		rCharacter.FaceId = 266;	break;		// �������
		case "Mary"			:		rCharacter.FaceId = 267;	break;		// ���� ������
		case "Axel"			:		rCharacter.FaceId = 268;	break;		// ������ ����
		case "Dios"			:		rCharacter.FaceId = 269;	break;		// ���� ����
		case "Vensan"		:		rCharacter.FaceId = 270;	break;		// ������ ������
		case "Rat"			:		rCharacter.FaceId = 271;	break;		// ���� ��������
		case "Molligan"		:		rCharacter.FaceId = 283;	break;		// ���� ��������
		case "Rozencraft"	:		rCharacter.FaceId = 288;	break;		// ������� ����������
		
		// ��� �� ��������
		case "Marten"		:		rCharacter.FaceId = 272;	break;		// ����� ������
		case "Tibo"			:		rCharacter.FaceId = 273;	break;		// ���� ����
		case "Catherine"	:		rCharacter.FaceId = 274;	break;		// ���� ����
		
		// ����� ������
		case "q_spa_off_1"	:		rCharacter.FaceId = 285;	break;		// ������� �������
		case "q_spa_off_2"	:		rCharacter.FaceId = 285;	break;		// ������������� �������
		case "GayMarshe"	:		rCharacter.FaceId = 148;	break;		// ��� �����
		
		// �������
		case "skeletcap" 	:		rCharacter.FaceId = 556;	break;		// ������� �������
		
		// ������ ������
		case "AdamRainer" 	:		rCharacter.FaceId = 145;	break;		// ���� ������
		case "CatRainer" 	:		rCharacter.FaceId = 147;	break;		// �������� ������
		case "q_eng_Cap_1" 	:		rCharacter.FaceId = 146;	break;		// ������� �������
		case "HuanTubercul" :		rCharacter.FaceId = 150;	break;		// ���� �������
		case "Gontier" 		:		rCharacter.FaceId = 284;	break;		// ������� �������
		case "Doggerty" 	:		rCharacter.FaceId = 287;	break;		// ����� ��������
		
		// // Addon-2016 Jason, ����������� ���������� (���)
		case "q_citizen_1" 	:		rCharacter.FaceId = 75;		break;		// ������� ������
		case "quest_off_eng":		rCharacter.FaceId = 304;	break;		// ������ �������
		case "quest_off_holl" :		rCharacter.FaceId = 19;		break;		// ������ �������
		case "quest_off_franc":		rCharacter.FaceId = 302;	break;		// ��� ����
		case "quest_off_spain":		rCharacter.FaceId = 303; 	break;		// ���� ����
		case "Guide_1":				rCharacter.FaceId = 305; 	break;		// ������� �������
		case "Spain_Major":			rCharacter.FaceId = 306; 	break;		// ������� ���������
		case "Levaser_Wife":		rCharacter.FaceId = 307; 	break;		// ��������� ��������
		case "quest_pirat_1":		rCharacter.FaceId = 301; 	break;		// ����� ������-�����
		case "quest_pirat_2":		rCharacter.FaceId = 308; 	break;		// ��������� ������
		case "Prospero_mush":		rCharacter.FaceId = 278; 	break;		// ������� ������� // may-16
		case "Claude_Durand":		rCharacter.FaceId = 309; 	break;		// ���� ����� // may-16
		
		// Addon 2016-1 Jason ��������� �������
		case "Billy_Pirt" 	:		rCharacter.FaceId = 310		break;		// ����� ����
		case "Jan_Slave"	:		rCharacter.FaceId = 311;	break;		// ��� �����
		case "Jan_Pikar"	:		rCharacter.FaceId = 311;	break;		// ��� �����
		case "Jeffry"		:		rCharacter.FaceId = 312;	break;		// ������� ����
		case "Tesak"		:		rCharacter.FaceId = 313;	break;		// ��� ����
		case "Leprechaun"	:		rCharacter.FaceId = 314; 	break;		// ���� ������
		case "Mirabelle"	:		rCharacter.FaceId = 316; 	break;		// ��������
		case "Marco"		:		rCharacter.FaceId = 317; 	break;		// ������� �����
		
		// Jason ���
		case "Boss_1"	 	:		rCharacter.FaceId = 331;	break;		// ��������� ����� �����
		case "Off_Fra_Z"	:		rCharacter.FaceId = 332;	break;		// ������� ��������
		case "huber_9"		:		rCharacter.FaceId = 333;	break;		// �����
		case "Fox"			:		rCharacter.FaceId = 244;	break;		// ����
		case "Boss_2"		:		rCharacter.FaceId = 334;	break;		// ��������� �������
		// <-- ���
		
		case "officer_6":		rCharacter.FaceId = 23; break;
		case "officer_7":		rCharacter.FaceId = 24; break;
		case "officer_8":		rCharacter.FaceId = 25; break;
		case "officer_9":		rCharacter.FaceId = 26; break;
		case "officer_10":		rCharacter.FaceId = 27; break;
		case "officer_11":		rCharacter.FaceId = 28; break;
		
		//--> �������� ���������������
		case "Espinosa":		rCharacter.FaceId = 414; break;
		case "Hero1":			rCharacter.FaceId = 415; break;
		case "Isterling":		rCharacter.FaceId = 416; break;
		case "Morgan":			rCharacter.FaceId = 417; break;
		case "SpaOfficer1":		rCharacter.FaceId = 418; break;
		case "SpaOfficer2":		rCharacter.FaceId = 419; break;
		case "Youngman":		rCharacter.FaceId = 420; break;
		case "Blood5":			rCharacter.FaceId = 421; break;
		case "blood_bomj":		rCharacter.FaceId = 421; break;
		case "Mechanic":		rCharacter.FaceId = 422; break;
		case "capitan_2":		rCharacter.FaceId = 423; break;
		case "capitan_3":		rCharacter.FaceId = 424; break;
		case "MusketeerEnglish_1":		rCharacter.FaceId = 425; break;
		case "MusketeerEnglish_2":		rCharacter.FaceId = 425; break;
		
		case "officer_12":		rCharacter.FaceId = 329; break;
		case "officer_13":		rCharacter.FaceId = 330; break;
		case "officer_14":		rCharacter.FaceId = 331; break;
		case "officer_15":		rCharacter.FaceId = 332; break;
		case "officer_16":		rCharacter.FaceId = 359; break;
		case "officer_17":		rCharacter.FaceId = 334; break;
		case "officer_18":		rCharacter.FaceId = 335; break;
		case "officer_19":		rCharacter.FaceId = 336; break;
		case "officer_20":		rCharacter.FaceId = 337; break;

		case "girl_1":			rCharacter.FaceId = 350; break;
		case "girl_2":			rCharacter.FaceId = 351; break;
		case "girl_3":			rCharacter.FaceId = 352; break;
		case "girl_4":			rCharacter.FaceId = 353; break;
		case "girl_5":			rCharacter.FaceId = 354; break;
		case "girl_6":			rCharacter.FaceId = 355; break;
		case "girl_7":			rCharacter.FaceId = 356; break;
		case "girl_8":			rCharacter.FaceId = 357; break;
		case "head_pir":		rCharacter.FaceId = 358; break;
		//<-- �������� ���������������
		
		case "huber_eng":		rCharacter.FaceId = 59; break;
		case "huber_fra":		rCharacter.FaceId = 60; break;
		
		//--> �������� ���������������
		case "huber_spa":		rCharacter.FaceId = 361; break;
		case "huber_hol":		rCharacter.FaceId = 362; break;
		case "lady_1":			rCharacter.FaceId = 363; break;
		case "lady_2":			rCharacter.FaceId = 364; break;
		case "lady_3":			rCharacter.FaceId = 365; break;
		case "lady_4":			rCharacter.FaceId = 366; break;
		case "lady_5":			rCharacter.FaceId = 367; break;
		case "lady_6":			rCharacter.FaceId = 368; break;


		case "pirate_1":		rCharacter.FaceId = 377; break;
		case "pirate_2":		rCharacter.FaceId = 378; break;
		case "pirate_3":		rCharacter.FaceId = 379; break;
		case "pirate_4":		rCharacter.FaceId = 380; break;
		case "pirate_5":		rCharacter.FaceId = 381; break;
		case "pirate_6":		rCharacter.FaceId = 382; break;
		case "pirate_7":		rCharacter.FaceId = 383; break;
		case "pirate_8":		rCharacter.FaceId = 384; break;
		case "pirate_9":		rCharacter.FaceId = 385; break;
		case "pirate_10":		rCharacter.FaceId = 386; break;
		case "priest_1":		rCharacter.FaceId = 387; break;
		case "priest_2":		rCharacter.FaceId = 388; break;
		case "priest_3":		rCharacter.FaceId = 389; break;
		case "priest_4":		rCharacter.FaceId = 390; break;
		case "shipowner_1":		rCharacter.FaceId = 491; break;
		case "shipowner_2":		rCharacter.FaceId = 492; break;
		case "shipowner_3":		rCharacter.FaceId = 493; break;
		case "shipowner_4":		rCharacter.FaceId = 494; break;
		case "shipowner_5":		rCharacter.FaceId = 495; break;
		case "shipowner_6":		rCharacter.FaceId = 496; break;
		case "shipowner_7":		rCharacter.FaceId = 497; break;
		case "shipowner_8":		rCharacter.FaceId = 498; break;
		case "shipowner_9":		rCharacter.FaceId = 499; break;
		case "shipowner_10":	rCharacter.FaceId = 500; break;
		case "shipowner_11":	rCharacter.FaceId = 501; break;
		case "shipowner_12":	rCharacter.FaceId = 502; break;
		case "shipowner_13":	rCharacter.FaceId = 503; break;
		case "shipowner_14":	rCharacter.FaceId = 504; break;
		case "shipowner_15":	rCharacter.FaceId = 505; break;
		case "shipowner_16":	rCharacter.FaceId = 506; break;
		case "smuggler_boss":	rCharacter.FaceId = 507; break;


		//<-- �������� ���������������
		
		case "trader_1":		rCharacter.FaceId = 121; break;
		case "trader_2":		rCharacter.FaceId = 122; break;
		case "trader_3":		rCharacter.FaceId = 123; break;
		case "trader_4":		rCharacter.FaceId = 124; break;
		case "trader_5":		rCharacter.FaceId = 125; break;
		case "trader_6":		rCharacter.FaceId = 126; break;
		case "trader_7":		rCharacter.FaceId = 127; break;
		case "trader_8":		rCharacter.FaceId = 128; break;
		case "trader_9":		rCharacter.FaceId = 129; break;
		case "trader_10":		rCharacter.FaceId = 130; break;
		case "trader_11":		rCharacter.FaceId = 131; break;
		case "trader_12":		rCharacter.FaceId = 132; break;
		case "trader_13":		rCharacter.FaceId = 133; break;
		case "trader_13_1":		rCharacter.FaceId = 134; break;
		case "trader_14":		rCharacter.FaceId = 135; break;
		case "Pasquale":		rCharacter.FaceId = 136; break; 
		case "trader_15":		rCharacter.FaceId = 131; break;
		case "trader_16":		rCharacter.FaceId = 128; break;
		case "usurer_1":		rCharacter.FaceId = 156; break;
		case "usurer_2": 		rCharacter.FaceId = 157; break;
		case "usurer_3":		rCharacter.FaceId = 158; break;
		case "usurer_4":		rCharacter.FaceId = 159; break;
		case "usurer_5":		rCharacter.FaceId = 160; break;
		case "usurer_6":		rCharacter.FaceId = 161; break;
		case "usurer_7":		rCharacter.FaceId = 162; break;
		case "usurer_8":		rCharacter.FaceId = 163; break;
		case "whore_1":			rCharacter.FaceId = 164; break;
		case "whore_2":			rCharacter.FaceId = 165; break;
		case "whore_3":			rCharacter.FaceId = 166; break;
		case "whore_4":			rCharacter.FaceId = 167; break;
		// 1.2.3 -->
		case "Daniel":			rCharacter.FaceId = 170; break;
		case "Researcher":		rCharacter.FaceId = 168; break;
		// 1.2.3 <--
		case "mushketer_1":		rCharacter.FaceId = 80; break;
		case "mushketer_2":		rCharacter.FaceId = 77; break;
		case "mushketer_3":		rCharacter.FaceId = 81; break;
		case "mushketer_4":		rCharacter.FaceId = 79; break;
		case "mushketer_5":		rCharacter.FaceId = 78; break;
		
		
		// ����� ��������
		case "BigPirate":		rCharacter.FaceId = 210; break;
		case "chard":			rCharacter.FaceId = 211; break;
		case "chard2":			rCharacter.FaceId = 37;  break;
		case "chard3":			rCharacter.FaceId = 213; break;

		//����
		case "ozg_carlos":		rCharacter.FaceId = 281; break; //������ ������
		case "ozg_horn":		rCharacter.FaceId = 282; break; //�������� ����
		case "ozg_piRat":		rCharacter.FaceId = 283; break; //������ ����-�����
		case "ozg_bonnet1":		rCharacter.FaceId = 286; break; //
		case "ozg_miko":		rCharacter.FaceId = 284; break; //���� ����������
		case "ozg_martin":		rCharacter.FaceId = 285; break; //������ ��� �����
		case "QuestCaptain":	rCharacter.FaceId = 290; break; //��� �������
		// �����
		case "OffOrion":		rCharacter.FaceId = 291; break; //������ ������
		// ���������
		case "quest_mush_1":		rCharacter.FaceId = 292; break; //��������
		case "quest_mush_2":		rCharacter.FaceId = 293; break; //�����
		// ��������� ������� ��� ����� �� �������
		case "horse01": 		rCharacter.FaceId = 164; break;
		case "horse02": 		rCharacter.FaceId = 165; break;
		case "horse03": 		rCharacter.FaceId = 166; break;
		case "horse04": 		rCharacter.FaceId = 167; break;
		case "horse05": 		rCharacter.FaceId = 164; break;
		case "horse06": 		rCharacter.FaceId = 165; break;
		case "horse07": 		rCharacter.FaceId = 166; break;
		case "horse08": 		rCharacter.FaceId = 167; break;
	}
}

void CirassMaker(aref rCharacter)
{
/*
0 - ��
1 - �������� (����� ������)
2 - ����� ������� ������
3 - ������ ������ ��� ������
4 - �������� (�.�. ������) 
*/
	if(CheckAttribute(rCharacter,"cirassIDX")) return;
	rCharacter.cirassIDX = 1; // ���� ������� ����������� ������ ������ ��� ����
	switch (rCharacter.model)
	{
		// �� ����� ����� � ��������
		case "mercen_1"		: 		rCharacter.cirassIDX = 4;		break;
		case "mercen_2"		: 		rCharacter.cirassIDX = 4;		break;
		case "mercen_3"		: 		rCharacter.cirassIDX = 4;		break;
		case "mercen_4"		: 		rCharacter.cirassIDX = 4;		break;
		case "mercen_5"		: 		rCharacter.cirassIDX = 4;		break;
		case "mercen_6"		: 		rCharacter.cirassIDX = 4;		break;
		case "mercen_7"		: 		rCharacter.cirassIDX = 4;		break;
		case "mercen_8"		: 		rCharacter.cirassIDX = 4;		break;
		case "mercen_9"		: 		rCharacter.cirassIDX = 4;		break;
		case "mercen_10"	: 		rCharacter.cirassIDX = 4;		break;
		
		// ������ ������
		case "mercen_11"	: 		rCharacter.cirassIDX = 2;		break;
		case "mercen_12"	: 		rCharacter.cirassIDX = 2;		break;
		case "mercen_13"	: 		rCharacter.cirassIDX = 2;		break;
		case "mercen_14"	: 		rCharacter.cirassIDX = 2;		break;
		case "mercen_15"	: 		rCharacter.cirassIDX = 2;		break;
		case "mercen_16"	: 		rCharacter.cirassIDX = 2;		break;
		case "mercen_17"	: 		rCharacter.cirassIDX = 2;		break;
		case "mercen_18"	: 		rCharacter.cirassIDX = 2;		break;
		case "mercen_19"	: 		rCharacter.cirassIDX = 2;		break;
		case "mercen_20"	: 		rCharacter.cirassIDX = 2;		break;
				
		// ������� ������
		case "mercen_21"	: 		rCharacter.cirassIDX = 1;		break;
		case "mercen_22"	: 		rCharacter.cirassIDX = 1;		break;
		case "mercen_23"	: 		rCharacter.cirassIDX = 1;		break;
		case "mercen_24"	: 		rCharacter.cirassIDX = 1;		break;
		case "mercen_25"	: 		rCharacter.cirassIDX = 1;		break;
		case "mercen_26"	: 		rCharacter.cirassIDX = 1;		break;
		case "mercen_27"	: 		rCharacter.cirassIDX = 1;		break;
		case "mercen_28"	: 		rCharacter.cirassIDX = 1;		break;	
		
		case "itza_1"		: 		rCharacter.cirassIDX = 2;		break;
		case "itza_2"		: 		rCharacter.cirassIDX = 2;		break;
		case "itza_3"		: 		rCharacter.cirassIDX = 2;		break;
		case "itza_4"		: 		rCharacter.cirassIDX = 2;		break;
		case "itza_5"		: 		rCharacter.cirassIDX = 2;		break;
		case "itza_6"		: 		rCharacter.cirassIDX = 2;		break;
		case "itza_7"		: 		rCharacter.cirassIDX = 2;		break;
		case "itza_8"		: 		rCharacter.cirassIDX = 2;		break;
	}
}

//�������� ��������� ��������
string GetRandSkelModel()
{
	string emodel = "mummy";

	switch (rand(3))
    {
        case 0: emodel = "Skel1";   break;
        case 1: emodel = "Skel2";   break;
        case 2: emodel = "Skel3";   break;
        case 3: emodel = "Skel4";   break;
    }
    return emodel;
}

// boal 22.04.04 ����� ������ �������� �� ����
void SetCaptanModelByEncType(ref Chref, string sFantomType)
{
    string ModelPirate = "Albermal"; // ������ ���
	
	int st = GetCharacterShipType(Chref);	

	if (sti(Chref.nation) == PIRATE) sFantomType = "pirate"; // ����� ���
	
	if(st != SHIP_NOTUSED) 	// ���� �������
	{
		ref rBaseShip = GetRealShip(sti(Chref.Ship.Type));
		int shClass = sti(rBaseShip.Class);
		switch (sFantomType)
		{
			case "trade":
				if(shClass >= 4) ModelPirate = "mercen_" + (rand(4) + 1);
				if(shClass == 3) ModelPirate = "mercen_" + (rand(4) + 11);
				if(shClass <  3) ModelPirate = "mercen_" + (rand(3) + 21);
				Chref.PhantomType = "citizen";
			break;
			case "pirate":
				if(shClass >= 4) ModelPirate = "mercen_" + (rand(4) + 6);
				if(shClass == 3) ModelPirate = "mercen_" + (rand(4) + 16);
				if(shClass <  3) ModelPirate = "mercen_" + (rand(3) + 25);
				Chref.PhantomType = "pirate";
			break;
			case "war":			
				if(shClass >= 4) 				ModelPirate = "off_" + NationShortName(sti(Chref.nation)) + "_" + (rand(2) + 1);
				if(shClass < 4 && shClass > 1)  ModelPirate = "off_" + NationShortName(sti(Chref.nation)) + "_" + (rand(1) + 4);
				if(shClass == 1)
				{
						if(sti(chref.Ship.Type) == SHIP_FORT) 	// ����������� �������
						{
							ModelPirate = "off_" + NationShortName(sti(Chref.nation)) + "_" + (rand(1) + 4);
						}
						else									// ����������� ��������� ���������
						{
							ModelPirate = "off_" + NationShortName(sti(Chref.nation)) + "_6";
						}	
				}		
				Chref.PhantomType = "officer";
			break;		
		}
	}
	else									// ������� �����������
	{
		switch (sFantomType)
		{
			case "trade":
				switch( rand(2) )
				{
					case 0: ModelPirate = "mercen_" + (rand(4) + 1); 	break;
					case 1: ModelPirate = "mercen_" + (rand(4) + 11);	break;
					case 2: ModelPirate = "mercen_" + (rand(3) + 21);	break;
				}
				Chref.PhantomType = "citizen";
			break;
			case "pirate":
				switch( rand(2) )
				{
					case 0: ModelPirate = "mercen_" + (rand(4) + 6);	break;
					case 1: ModelPirate = "mercen_" + (rand(4) + 16);	break;
					case 2: ModelPirate = "mercen_" + (rand(3) + 25);	break;
				}
				Chref.PhantomType = "pirate";
			break;
			case "war":
				ModelPirate = "off_" + NationShortName(sti(Chref.nation)) + "_" + (rand(2) + 1);
				Chref.PhantomType = "officer";
			break;			
		}
	}
		
	Chref.model = ModelPirate;
	FaceMaker(Chref);
	CirassMaker(Chref);
}

void SetModelPirate(ref ChrefPirate)
{
    string ModelPirate;
    
    ModelPirate = "citiz_" + (rand(9) + 41);
    
    ChrefPirate.model = ModelPirate;
    FaceMaker(ChrefPirate);
	CirassMaker(ChrefPirate);
}

// Warship. ������� ����� ������ � ��������. ����-��� �����
void Characters_RefreshModel(ref rChar)
{
	SendMessage(rChar, "lss", MSG_CHARACTER_SETMODEL, rChar.model, rChar.model.animation);
}

//Jason - ������������ ����� ������ �� �������, ������� ������ �� 10 �� 16 - '�������'
string GetRandQuestSoldierModel(int _iNation)
{
	string sModel = "sold_" + NationShortName(_iNation) + "_" + (rand(6)+10);

    return sModel;
}
//Jason - ��� ������ ��������� ��������� ������ - ��������
string GetRandQuestMercenaryModel()
{
	string sModel = "citiz_"+(51+(rand(9)));

    return sModel;
}

// Warship, 30.05.11. ��� ������� ��� ������������ ��������� ������������ ����� ������� ��� ������� -->
// ������� �� ������� ���� - ����������� ��� ������.
// Jason: ��� ������ ����� ����� ������ �� 1 �� 9
void SetRandNationSoldierModel(ref _character)
{
	_character.model = "sold_" + NationShortName(sti(_character.nation)) + "_" + (1 + rand(8));
    FaceMaker(_character);
	CirassMaker(_character);
}

void SetRandNationOfficerModel(ref _character)
{
	_character.model = "off_" + NationShortName(sti(_character.nation)) + "_" + (1 + rand(5));
    FaceMaker(_character);
	CirassMaker(_character);
}
// <--

// Warship, 04.06.11. ������ ��������� ������.
void SetModel(ref _character, string _model)
{
	_character.model = _model;
    FaceMaker(_character);
	CirassMaker(_character);
}
