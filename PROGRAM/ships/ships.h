#define SAILS_COLOR_QUANTITY				9
#define SHIP_TYPES_QUANTITY					50
#define SHIP_TYPES_QUANTITY_WITH_FORT		51	// must be (SHIP_TYPES_QUANTITY + 1)

#define SHIP_TARTANE			0   // ������			- 6-�� ����� 	(SEFH)
#define SHIP_WAR_TARTANE		1	// �������			- 6-�� �����	(SEFHP)

#define SHIP_BARQUE				2	// ����			- �������� 5-�� �����	(SEFH)
#define SHIP_SCHOONER			3	// �������� �����	- �������� 4-�� �����	(SEFH)
#define SHIP_BARKENTINE			4	// ����������		- �������� 4-�� �����	(SEFH)
#define SHIP_SHNYAVA			5	// �����			- �������� 4-�� �����	(SEFH)
#define SHIP_FLEUT				6	// �����			- �������� 4-�� �����	(SEFH)
#define SHIP_CARAVEL			7	// ���������		- �������� 3-�� �����	(SEFH)
#define SHIP_PINNACE			8	// ������			- �������� 3-�� �����	(SEFH)
#define SHIP_CARACCA			9	// �������			- �������� 3-�� �����	(SEFH)
#define SHIP_NAVIO				10	// �����			- �������� 2-�� �����	(SEFH)
#define SHIP_EASTINDIAMAN		11	// ���-�����		- �������� 2-�� �����	(SEFH)

#define SHIP_CAREERLUGGER       12	// ���������� ������	- ������� 5-�� �����	(SEFH)
#define SHIP_LUGGER				13	// ������			- ������� 5-�� �����	(SEFHP)
#define SHIP_SLOOP				14	// ����			- ������� 5-�� �����	(SEFHP)
#define SHIP_BRIGANTINE			15	// ����������		- ������� 4-�� �����	(SP)
#define SHIP_BRIG				16	// ����			- ������� 4-�� �����	(EP)
#define SHIP_SCHOONER_W			17	// ������� �����	- ������� 4-�� �����	(FHP)
#define SHIP_GALEON_L			18	// ������			- ������� 3-�� �����	(SEFHP)
#define SHIP_CORVETTE			19	// ������			- ������� 3-�� �����	(EFP)
#define SHIP_XebekVML			20	// ������			- ������� 3-�� �����	(SH)
#define SHIP_POLACRE			21	// ������			- ������� 3-�� �����	(SF)

#define SHIP_GALEON_H			22	// ������� ������	- ������� 2-�� �����	(SP)
#define SHIP_FRIGATE			23	// ������			- ������� 2-�� �����	(EFH)
#define SHIP_FRIGATE_H			24	// ������� ������	- ������� 2-�� �����	(SEFH)

#define SHIP_LINESHIP			25	// ������� �������	- ������� 1-�� �����	(SEFHP)
#define SHIP_LSHIP_FRA			26	// �������� �������	- ������� 1-�� ����� (�������)	(F)
#define SHIP_LSHIP_HOL			27	// �������� �������	- ������� 1-�� ����� (���������)	(H)
#define SHIP_LSHIP_SPA			28	// �������� �������	- ������� 1-�� ����� (�������)	(S)
#define SHIP_LSHIP_ENG			29	// �������� �������	- ������� 1-�� ����� (������)	(E)

// ���������
#define SHIP_MAYFANG			30 	// ������� 			- ������ ������			- 4-�� �����
#define SHIP_MIRAGE				31	// �����			- ������������ ���	 	- 4-�� �����
#define SHIP_VALCIRIA			32	// ���������		- ���������� ����	 	- 4-�� �����

#define SHIP_CORVETTE_QUEST		33	// ����������		- ����� ������			- 3-�� �����
#define SHIP_POLACRE_QUEST		34	// ������			- ������		    	- 3-�� �����
#define SHIP_FRIGATE_L			35	// ������ "�����"	- ������� ������		- 2-�� �����

// --> ��������� - �������� !!!!
#define SHIP_QUEST0				36  // ��������� �0 - 6-�� ����� <-- ���������� ��� ������� :)
#define SHIP_QUEST1				37  // ��������� �1 - 5-�� �����
#define SHIP_QUEST2             38  // ��������� �2 - 4-�� �����
#define SHIP_QUEST3             39  // ��������� �3 - 4-�� �����
#define SHIP_QUEST4             40  // ��������� �4 - 3-�� �����
#define SHIP_QUEST5				41  // ��������� �5 - 3-�� �����
#define SHIP_QUEST6				42  // ��������� �6 - 2-�� �����
#define SHIP_QUEST7				43  // ��������� �7 - 2-�� �����
#define SHIP_QUEST8				44  // ��������� �8 - 1-�� �����
// <-- ��������� - �������� !!!!

#define SHIP_CURSED_FDM			45	// ��������� �������	- ������� �������		- 1-�� �����
#define SHIP_FDM				46	// ����� �������	- ������� �������	    	- 1-�� �����

#define SHIP_LSHIP_QUEST		47	// "���� �� ���-�����" - �������� �������		- 1-�� �����

#define SHIP_BOAT               48	// ����� � ������
#define SHIP_FORT               49	// ����

#define SHIP_NOTUSED			 1000
#define SHIP_NOTUSED_TYPE_NAME	"Not Used"
#define SHIP_NAME_NOTUSED		"Noname"

object  ShipsTypes[SHIP_TYPES_QUANTITY_WITH_FORT];  // RealShips
object	SailsColors[SAILS_COLOR_QUANTITY];

ref GetShipByType(int iType) { return &ShipsTypes[iType]; }  // ���������� GetRealShip
