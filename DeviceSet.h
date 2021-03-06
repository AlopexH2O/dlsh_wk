/* ##########################################################################  
 # Device Cal Point Setting Definination  
 #  
 # Author:  zhengh  
 # Date:    2017/11/13 (version 0.1)  
 #  
 # Description:  
 # ------------  
 # 文件设定需要逻辑计算的的模拟量、开入、定值等信息的fun,inf  
 # 设定相关量的数目及顺序，主程序按照此头文件中设定顺序执行 
 
 ############################################################################*/  
#ifndef DEVICE_SET_H
#define DEVICE_SET_H 

typedef unsigned char uint8;

//厂站标识
#define SHZZ "SHZZ"
#define SHZ  "SHZ"
#define KGZ  "KGZ"
#define EKY  "EKY"
#define CH3  "CH3"
#define CH4  "CH4"

#define TACOUT_NUM 16
#define INDEX_TAC1 0
#define INDEX_TAC2 1
#define INDEX_TAC3 2
#define INDEX_TAC4 3
#define INDEX_TAC5 4
#define INDEX_TAC6 7
#define INDEX_TAC7 10
#define INDEX_TAC8 13

#define LOAD_ALIVE_P   1.0

#define SYS_P_NUM 10
const uint8 FUN_SYS_P[SYS_P_NUM] = {12, 12, 12, 12, 12, 12, 12, 12, 12, 12};
const uint8 INF_SYS_P[SYS_P_NUM] = { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10};

#define LOAD_P_NUM 63
const uint8 FUN_LOAD_P[LOAD_P_NUM] = {12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
									12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
									12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
									12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
									12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
									12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
									12,  12,  12};
const uint8 INF_LOAD_P[LOAD_P_NUM] = {111, 112, 113, 114, 115, 116, 117, 118, 119, 120,
									121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
									131, 132, 133, 134, 135, 136, 137, 138, 139, 140,
									141, 142, 143, 144, 145, 146, 147, 148, 149, 150,
									151, 152, 153, 154, 155, 156, 157, 158, 159, 160,
									161, 162, 163, 164, 165, 166, 167, 168, 169, 170,
									171, 172, 173};
//最后一个为频率欠切功率定值
const uint8 FUN_LOAD_PRIOR[LOAD_P_NUM + 1] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
											  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
											  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
											  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
											  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
											  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
											  1, 1, 1, 1};
const uint8 INF_LOAD_PRIOR[LOAD_P_NUM + 1] = {3, 4, 5, 6, 7, 8, 9,10,11,12,
											 13,14,15,16,17,18,19,20,21,22,
											 23,24,25,26,27,28,29,30,31,32,
											 33,34,35,36,37,38,39,40,41,42,
											 43,44,45,46,47,48,49,50,51,52,
											 53,54,55,56,57,58,59,60,61,62,
											 63,64,65, 2};

#define LOAD_CONN_NUM 12
const uint8 FUN_LOAD_CONN[LOAD_CONN_NUM] = {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12};
const uint8 INF_LOAD_CONN[LOAD_CONN_NUM] = {28, 29, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};

#define SYS_STAT_NUM 15
const uint8 FUN_SYS_STAT[SYS_STAT_NUM] = {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15};
const uint8 INF_SYS_STAT[SYS_STAT_NUM] = {76, 77, 78, 65, 66, 67, 68, 69, 70, 71, 72, 81, 82, 83, 84};


#define SYS_TAC_NUM 8	//策略数目
#define MAX_PRIOR   80	//优先级最大数目


#define LINE_NUM_KGZ 12	//开关站负荷数目
#define LINE_NUM_EKY 9	//二空压负荷数目
#define LINE_NUM_CH3 20	//三催化负荷数目
#define LINE_NUM_CH4 22 //四催化负荷数目
#define LINE_NUM_SHZ 1 //石化子站需求点数目

#define INDEX_EKY LINE_NUM_KGZ					//二空压负荷索引起点
#define INDEX_CH3 (LINE_NUM_EKY + INDEX_EKY)    //三催化负荷索引起点
#define INDEX_CH4 (LINE_NUM_CH3 + INDEX_CH3)    //四催化负荷索引起点



//开关站负荷系统连接信息
//66kV母线挂载信息
const uint8 FUN_KGZ_LOAD[LINE_NUM_KGZ] = {12,12,12,12,12,12,12,12,12,12,12,12};
const uint8 INF_KGZ_LOAD[LINE_NUM_KGZ] = { 3, 5, 7, 9,11,13,15,17,19,21,23,25};

//二空压负荷系统连接信息
const uint8 FUN_EKY_LOAD[LINE_NUM_EKY] = {12,12,12,12,12,12,12,12,12};
const uint8 INF_EKY_LOAD[LINE_NUM_EKY] = { 3, 5, 7, 9,11,13,15,17,19};

//三催化负荷系统连接信息
const uint8 FUN_CH3_LOAD[LINE_NUM_CH3] = {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12};
const uint8 INF_CH3_LOAD[LINE_NUM_CH3] = { 3,  5,  7,  9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41};

//四催化负荷系统连接信息
const uint8 FUN_CH4_LOAD[LINE_NUM_CH4] = {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12};
const uint8 INF_CH4_LOAD[LINE_NUM_CH4] = { 3,  5,  7,  9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45};

//石化控制子站--9571开关TWJ信息
const uint8 FUN_SHZ_LOAD[LINE_NUM_SHZ] = {15 };
const uint8 INF_SHZ_LOAD[LINE_NUM_SHZ] = {27 };


#endif
/****************************逻辑判断需要用的量
typedef struct
{//输入
	int16  INPUTP[10];				//策略计算元件 功率
	int16  LOAD_P[63];			//负荷线路可切功率
	int16  LOAD_Prior[63];	//负荷线路优先级定值
	Uint16 LOAD_SYSTEM[12];		//负荷归属系统
	//输出
	int16  PtacYq[8];				//策略1～8需切量
	int16  Pcutted[8];			//策略1～8匹配切量
	Uint8  FlagCutTac1[63]; //策略1负荷选切结果
	Uint8  FlagCutTac2[63]; //策略2负荷选切结果
	Uint8  FlagCutTac3[63]; //策略3负荷选切结果
	Uint8  FlagCutTac4[63]; //策略4负荷选切结果
	Uint8  FlagCutTac5[63]; //策略5负荷选切结果
	Uint8  FlagCutTac6[63]; //策略6负荷选切结果
	Uint8  FlagCutTac7[63]; //策略7负荷选切结果
	Uint8  FlagCutTac8[63]; //策略8负荷选切结果	
}SYSTAC;
*/
/****************************************
			系统线路模拟量
*****************************************/
/***************************************
INPUTP: （模拟量）
组号  条目号 描述
12  ,1, 1#变高功率     
12  ,2, 1#变中功率     
12  ,3, 2#变高功率     
12  ,4, 2#变中功率     
12  ,5, 66kV母联9572功率 
12  ,6, 化机一线功率   
12  ,7, 化机二线功率   
12  ,8, 化总一线功率
12  ,9, 化总二线功率
****************************************/
/* **************************************
			负荷线路功率
*****************************************/
/****************************************
LOAD_P： （模拟量）  
组号  条目号   描述
12  ,111,  8012线功率	开关站
12  ,112,  8013线功率
12  ,113,  8014线功率
12  ,114,  8015线功率
12  ,115,  备用线功率
12  ,116,  备用线功率
12  ,117,  8022线功率
12  ,118,  8023线功率
12  ,119,  8024线功率
12  ,120,  8025线功率
12  ,121,  备用线功率
12  ,122,  备用线功率

12  ,123,  3101线功率   二空压
12  ,124,  3103线功率
12  ,125,  3105甲功率
12  ,126,  备用线功率
12  ,127,  3102线功率
12  ,128,  3104线功率
12  ,129,  3105乙功率
12  ,130,  3151线功率
12  ,131,  3152线功率

12  ,132,  3557线功率	三催化
12  ,133,  3558线功率
12  ,134,  3605线功率
12  ,135,  3607线功率
12  ,136,  3609线功率
12  ,137,  3551线功率
12  ,138,  3552线功率
12  ,139,  3651线功率
12  ,140,  3569线功率
12  ,141,  3606线功率
12  ,142,  3608线功率
12  ,143,  3611线功率
12  ,144,  3615线功率
12  ,145,  3617线功率
12  ,146,  3612线功率
12  ,147,  3616线功率
12  ,148,  3618线功率
12  ,149,  3653线功率
12  ,150,  3654线功率
12  ,151,  3652线功率

12  ,152,  3903线功率	四催化
12  ,153,  3905线功率
12  ,154,  备用线功率
12  ,155,  3904线功率
12  ,156,  3906线功率
12  ,157,  备用线功率
12  ,158,  3953线功率
12  ,159,  3954线功率
12  ,160,  3931线功率
12  ,161,  3941线功率
12  ,162,  4801线功率
12  ,163,  备用线功率
12  ,164,  备用线功率
12  ,165,  备用线功率
12  ,166,  备用线功率
12  ,167,  4802线功率
12  ,168,  备用线功率
12  ,169,  备用线功率
12  ,170,  备用线功率
12  ,171,  备用线功率
12  ,172,  4851线功率
12  ,173,  4852线功率


LOAD_Prior：（定值）
组号 条目号 描述
1      3          8012线优先级
1      4          8013线优先级
1      5          8014线优先级
1      6          8015线优先级
1      7          备用线优先级
1      8          备用线优先级
1      9          8022线优先级
1      10         8023线优先级
1      11         8024线优先级
1      12         8025线优先级
1      13         备用线优先级
1      14         备用线优先级
1      15         3101线优先级
1      16         3103线优先级
1      17         3105甲优先级
1      18         备用线优先级
1      19         3102线优先级
1      20         3104线优先级
1      21         3105乙优先级
1      22         3151线优先级
1      23         3152线优先级
1      24         3557线优先级
1      25         3558线优先级
1      26         3605线优先级
1      27         3607线优先级
1      28         3609线优先级
1      29         3551线优先级
1      30         3552线优先级
1      31         3651线优先级
1      32         3569线优先级
1      33         3606线优先级
1      34         3608线优先级
1      35         3611线优先级
1      36         3615线优先级
1      37         3617线优先级
1      38         3612线优先级
1      39         3616线优先级
1      40         3618线优先级
1      41         3653线优先级
1      42         3654线优先级
1      43         3652线优先级
1      44         3903线优先级
1      45         3905线优先级
1      46         备用线优先级
1      47         3904线优先级
1      48         3906线优先级
1      49         备用线优先级
1      50         3953线优先级
1      51         3954线优先级
1      52         3931线优先级
1      53         3941线优先级
1      54         4801线优先级
1      55         备用线优先级
1      56         备用线优先级
1      57         备用线优先级
1      58         备用线优先级
1      59         4802线优先级
1      60         备用线优先级
1      61         备用线优先级
1      62         备用线优先级
1      63         备用线优先级
1      64         4851线优先级
1      65         4852线优先级
1      2          频率欠切功率定值


LOAD_SYSTEM：  （模拟量） 
组号 条目号 描述
12   ,28    ,开关站系统1线路        
12   ,29    ,开关站系统2线路  
12   ,18    ,二空压系统1线路        
12   ,19    ,二空压系统2线路        
12   ,20    ,三催化系统1线路1       
12   ,21    ,三催化系统1线路2       
12   ,22    ,三催化系统2线路1       
12   ,23    ,三催化系统2线路2       
12   ,24    ,四催化系统1线路1       
12   ,25    ,四催化系统1线路2       
12   ,26    ,四催化系统2线路1       
12   ,27    ,四催化系统2线路2       


SYS_STATE（系统运行方式状态）
组号 条目号 描述
12   ,16    ,系统1联网
12   ,17    ,系统2联网
12   ,18    ,系统12互联联网
12   ,18    ,9511开关运行 
12   ,20    ,9512开关运行       
12   ,21    ,9561开关运行       
12   ,22    ,9562开关运行
12   ,23    ,9591开关运行
12   ,24    ,9592开关运行
12   ,25    ,9572开关运行		
12   ,26    ,9573开关运行
12   ,xx    ,35kVI母归于系统I
12   ,xx    ,35kVI母归于系统II
12   ,xx    ,35kVII母归于系统I
12   ,xx    ,35kVII母归于系统II


*/


