#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define WAZA_MAX 12
#define LEVEL_MAX (WAZA_MAX-3)
#define MOB_MAX 8
#define L_NUM_MAX 30

//#define DEBUG

typedef struct enemydata
{
	char name[100]; //キャラ名
	char waza1[60]; //技名1
	char waza2[60]; // 2
	int hp;	    
	int hpmax;
	int at1;
	int at2;
	int xp;
	char zi;//zokusei
	int zi_at;
	int mval1;
	int mval2;
	int mvalflag;
	int sbreak1;
	int sbreak2;
	int drop_money;
	double hitrate1;//命中率
	double hitrate2;
//	int dropitem[MOB_MAX];
//	int knock_check;
}mobn;
typedef struct userdata
{
	int userhp;
	int xp;
      int valflag;
      int uzi_at;
      int uvalflag;
      int fq;
      int fflag;
      int mhp;
      int docd_flag;
      int docd;
      int atd_flag;
      int atd;
      int pbom_flag;
      int pbom;
	char uzi;
	int fire_flag;
	int fire;
	int money;
	int critical_d;
//	int item[MOB_MAX];
}usern;
int printShikaku(int argc,char *argv[]);
void printBar(int hp,int hpMax);
void usertern(int enemyNum,int sect,char *argv[],int USER_HP_MAX);
void cptern(int enemyNum,int USER_HP_MAX);
void printHPinfo(int enemyNum,int USER_HP_MAX);
int finishq(int*);
void shoptern(char shoptern[][250]);
int skill_check();
//void printf_grey(,...);
int passcheck();
int sect,level,lm_level;
int u_atdamage = 0,u_heal = 0,wat;
double v_atdamage = 0,v_level = 0;
char *sentakushi[WAZA_MAX] =
{
	"逃げる",
	"パンチ",
	"キック",
	"ヒノキの棒",
	"火の玉",
	"カッター",
	"スマホ",
	"落雷",
	"バリア",
	"ポイズンボム",
	"ドローン",
};

//char *dropItem[MOB_MAX] =
/*{
	"特訓の書(ミニ)",//経験値上昇
	"特訓の書(小)",
	"特訓の書(中)",
	"特訓の書(大)",
	"特訓の書(特大)",
	"ストロングミニポーション", //一定時間攻撃強化
	"ストロングポーション",
	"ミリオンストロングポーション",
};*/
mobn mob[MOB_MAX];
usern user;

int main()
{
	//	reset;
	//skill_check();
	int enemyNum = (rand() % MOB_MAX);
	srand((unsigned)time(NULL));
	FILE *fp;
	int sentakusi;
	int i = 20,b,now_levelmax = 1000,now_levelxp = 0;
	char tempStr[30];
	user.fq = 1;
#ifdef DEBUG
	//printf("%d\n",WAZA_MAX);
	//create file	
#endif

	fp = fopen("lev.txt","r");
    if( fp == NULL )
    { /* ファイルが無い時 */
        fp = fopen("lev.txt","w");
        strcpy(tempStr,"120,120,1,500"); /* デフォルト値 */
        fprintf(fp,tempStr);
        fprintf(fp,"\n");
        fclose(fp);
    }
    else
    { /* ファイルがある時 */
        fgets(tempStr,sizeof(tempStr),fp);
        fclose(fp);
    }
    sscanf(tempStr,"%d,%d,%d,%d\n",&user.xp,&now_levelxp,&level,&user.money);

//	printf("%d\n",level);
	lm_level=level;

	if( LEVEL_MAX <= lm_level)
	{
		lm_level = LEVEL_MAX;
	}

//	printf("level=%d,xp=%d\n",level,xp);
	
//	printf("%d\n",level);
	lm_level=level;

	if( LEVEL_MAX <= lm_level)
	{
		lm_level = LEVEL_MAX;
	}
	   int USER_HP_MAX = (300 + (level * 45));

	strcpy(mob[0].name,"スライム"); //名前
	strcpy(mob[0].waza1,"ずつき");  //技1
	strcpy(mob[0].waza2,"ずつき");  //技2
	mob[0].hp = 100 + (level * 30); //HP
	mob[0].hpmax = mob[0].hp;		  //最大HP
	mob[0].at1 = 30;			  //1の攻撃力
	mob[0].at2 = 30;			  //2の攻撃力
	mob[0].xp  = 495;               //獲得経験値
	mob[0].drop_money = 150;        //獲得まねー 単位:ペグ	
	//mob[0].dropitem[0] =1 ;//[0]はミニ経験値
	
	strcpy(mob[1].name,"ファイアスライム");
	strcpy(mob[1].waza1,"ずつき");
	strcpy(mob[1].waza2,"ひのたま");
	mob[1].hp = 200 + (level * 28.85);
	mob[1].hpmax = mob[1].hp;
	mob[1].at1 = 35;
	mob[1].at2 = 40;
	mob[1].xp  = 675;
	mob[0].drop_money = 300;
	//mob[1].dropitem[1] = 1;
	//mob[1].dropitem[2] = 1;
	
	strcpy(mob[2].name,"りゅうのこども");
	strcpy(mob[2].waza1,"ずつき");
	strcpy(mob[2].waza2,"ひのたま");
	mob[2].hp = 235 + (level * 28.5);
	mob[2].hpmax = mob[2].hp;
	mob[2].at1 = 40;
	mob[2].at2 = 55;
	mob[2].xp  = 730;
	mob[3].drop_money = 500;
	//mob[2].dropitem[2] = 1;
	//mob[2].dropitem[5] = 1;

	strcpy(mob[3].name,"こおりのりゅう");
	strcpy(mob[3].waza1,"こおりのキバ");
	strcpy(mob[3].waza2,"もうふぶき");
	mob[3].hp    = 275 + (level * 28);
	mob[3].hpmax = mob[3].hp;
	mob[3].at1   = 50 + (level * 3.85);
	mob[3].at2   = 70 + (level * 3.85);
	mob[3].xp    = 950 + (level * 1.11);
	mob[3].zi    = 's';
	mob[3].zi_at = 20;
	mob[3].drop_money = 750;

	strcpy(mob[4].name,"ナイト");
	strcpy(mob[4].waza1,"回転斬り");
	strcpy(mob[4].waza2,"二段斬り");
	mob[4].hp  = 300 + (level * 27.85);
	mob[4].hpmax = mob[4].hp;
	mob[4].at1 = 65 + (level * 6.5);
	mob[4].at2 = 75 + (level * 6.5);
	mob[4].xp  = 980 + (level * 1.25);
	mob[4].drop_money = 1000;
	
	strcpy(mob[5].name,"炎の騎士");
	strcpy(mob[5].waza1,"火の矢");
	strcpy(mob[5].waza2,"バリア");
	mob[5].hp    	= 375 + (level * 27);
	mob[5].hpmax = mob[5].hp;
	mob[5].at1   	= 65;
	mob[5].xp    	= 1000 + (level * 1.3);
	mob[5].zi    	= 'y';
	mob[5].zi_at 	= 30;
	mob[5].mval2      = 1;	
	mob[5].drop_money = 1500;
	
	strcpy(mob[6].name,"土蜘蛛");
	strcpy(mob[6].waza1,"マグニチュード20");
	strcpy(mob[6].waza2,"地割れ");
	mob[6].hp    	= 400 + (level * 26.5);
	mob[6].hpmax      = mob[6].hp;
	mob[6].at1   	= 60;
	mob[6].at2		= 175;
	mob[6].xp    	= 1002 + (level * 1.45);
	mob[6].drop_money = 1750;
	
	strcpy(mob[7].name,"ユニコーン");
	strcpy(mob[7].waza1,"せいなるつの");
	strcpy(mob[7].waza2,"ツノ突撃");
	mob[7].hp    	= 600 + (level * 13.12);
	mob[7].hpmax      = mob[7].hp;
	mob[7].at1   	= 300 + (level * 2.5 );
	mob[7].at2		= 1000 + (level * 1.89);
	mob[7].xp    	= 1540 + (level * 1.7);
	mob[7].sbreak1    = 0;
	mob[7].sbreak2    = 0;
	mob[7].drop_money = 3000;
	//mob[7].dropitem[7]= 1;
	//mob[7].dropitem[2]= 2;

	char shoplist[15][50] =
	{
		"ミニポーション         ",
		"ヒールポーション       ",
		"ミニパワーポーション   ",
		"パワーポーション       ",
		"ミニシールドポーション ",
		"シールドポーション     ",
		"ミニエクスポーション   ",
		"エクスポーション       ",
	};
/**/
	now_levelmax = 75 * level;			
    printf("\x1b[2J");
	printf("RPGへようこそ!\n");
	printf("あなたのレベルは%d,経験値は%dです\n",level,user.xp);
	for(i=0;i<40;i++)
	{
		printf("*");
	}
	while(user.fq)
	{	
		/*レベル取得*/
		fp = fopen("lev.txt","r");
		fgets(tempStr,sizeof(tempStr),fp);
		fclose(fp);

		sscanf(tempStr,"%d,%d,%d,%d\n",&user.xp,&now_levelxp,&level,&user.money);
	      //printf("%d\n",level);
		lm_level=level;
	
		if( LEVEL_MAX <= lm_level)
		{
			lm_level = LEVEL_MAX;
		}
	      USER_HP_MAX = (300 + (level * 45));
		/**/
//		shoptern(shoplist[15][250]);
		enemyNum = rand() % MOB_MAX;
		user.mhp = mob[enemyNum].hp;		
		printf("\n%sが現れた!\n",mob[enemyNum].name);
		user.userhp = USER_HP_MAX;
		user.fflag = 0;
		int sentaku_max;
		v_level = (double)level;
		user.critical_d = user.userhp/12;
		while(1)
		{
			printf("あなたはどうする?\n");
	
			sentaku_max = (level < 2) ? 3 : (level+1); 
			if(level > WAZA_MAX)
			{
				sentaku_max = WAZA_MAX;
			}
			sect = printShikaku(sentaku_max,sentakushi);
			
            printf("\x1b[2J");
			// user tern
			usertern(enemyNum,sect,sentakushi,USER_HP_MAX);
			// computer tern
			if( user.mhp <= 0 )
			{
			
				printHPinfo(enemyNum,USER_HP_MAX);
				user.fflag = 1;
				printf("%sを倒した!\n",mob[enemyNum].name);
				printf("%dの経験値を獲得!\n",mob[enemyNum].xp);
				printf("経験値が%dから%dに上がった!\n",user.xp,user.xp + mob[enemyNum].xp);
				user.xp += mob[enemyNum].xp;
				now_levelxp += mob[enemyNum].xp;
				for(;now_levelxp > now_levelmax;)
				{
					if(now_levelxp > now_levelmax)
					{
						now_levelxp -= now_levelmax;
						level++;
						now_levelmax = level * 75;
					}
				}
				if(now_levelxp > now_levelmax)
				{
					now_levelxp -= now_levelmax;
					level++;
					now_levelmax = level * 50;
				}
				printf("あなたのレベルは%dです！",level);
				printf("%dレベル    %d  /  %d\n",level,now_levelxp,now_levelmax);
				FILE *fp;
				fp = fopen("lev.txt","w");
				fprintf(fp,"%d,%d,%d",user.xp,now_levelxp,level);
				fclose(fp);
				finishq(&user.fq);
				if(user.fq == 0)
				{
					exit(0);
				}else
				{
					break;
				}
	
//				exit(0);
			}
			cptern(enemyNum,USER_HP_MAX);
			
			printHPinfo(enemyNum,USER_HP_MAX);
			if( user.mhp <= 0 )
			{
				user.fflag = 1;
				printf("%sを倒した!\n",mob[enemyNum].name);
				printf("%dの経験値を獲得!\n",mob[enemyNum].xp);
				user.xp += mob[enemyNum].xp;
				now_levelxp += mob[enemyNum].xp;
				for(;now_levelxp > now_levelmax;)
				{
					if(now_levelxp > now_levelmax)
					{
						now_levelxp -= now_levelmax;
						level++;
						now_levelmax = level * 50;
					}
				}
				printf("%dレベル    %d  /  %d\n",level,user.xp,now_levelmax);
				printf("経験値が%dに上がった!\n",user.xp);
				printf("あなたのレベルは%dです！",user.xp > now_levelmax ? level +1:level);
				FILE *fp;
				fp = fopen("lev.txt","w");
				fprintf(fp,"%d,%d,%d",user.xp,now_levelxp,level);
				fclose(fp);
				finishq(&user.fq);
				if(user.fq == 0)
				{
					exit(0);
				}else
				{
					break;
				}
	
//				exit(0);
			}
		}
	}
	return 0;
}

void
usertern(int enemyNum,int sect,char *argv[],int USER_HP_MAX)
{

//	printf("enemyNum=%d,sect=%d\n",cname,sect);
	int flag = 0;
	u_atdamage = 0;
	int run_q = 0;	
	
	printf("%s!\n",argv[sect]);

	switch(sect)
	{
		case 1://パンチ
		if(rand()  % 50 == 0)
		{
			printf("当たらなかった!\n");
			break;
		}
		if(rand()  % 7 == 0)
		{
			u_atdamage += user.critical_d;
			printf("急所に命中!\n");
		}
		u_atdamage += 15 + (level * 1.75);
		printf("%dダメージヒット!\n",u_atdamage);
		user.mhp -= u_atdamage;
		break;
		
		case 2://キック
		if(rand()  % 11 == 0)
		{
			printf("当たらなかった!\n");
			break;
		}
		if(rand()  % 10 == 0)
		{
			u_atdamage += user.critical_d;
			printf("急所に命中!\n");
		}
		u_atdamage = 30 + (level * 1.65);
		printf("%dダメージヒット!\n",u_atdamage);
		user.mhp -= u_atdamage;
		break;
		
		case 0://逃げる
		if(rand() % 700 == 0)
		{
			printf("逃げ切れた!\n");
			finishq(&user.fq);
			if(user.fq == 0)
			{
				exit(0);
			}else
			{
				break;
			}	
		}
		printf("あなたは死にました\n");
		exit(0);
		break;
		
		case 4://火の玉
		if(level < 3)
		{
			printf("レベルが足りない!\n");
			break;
		}
		if(rand()  % 10 == 0)
		{
			printf("当たらなかった!\n");
			break;
		}
		if(rand()  % 12 == 0)
		{
			u_atdamage += user.critical_d;
			printf("急所に命中!\n");
		}
		u_atdamage += 50;
		printf("%dダメージヒット!\n",u_atdamage);
		user.mhp -= u_atdamage;
		if(level > 8)
		{
			user.uzi = 'y';	
			user.uzi_at = 45;
			printf("%sは火傷を負った!(火傷継続ターン:%d)",mob[enemyNum].name
			,user.fire = rand() % 5 + 3);
			user.fire_flag = user.fire;
		}
		break;
		
		case 5://カッター`
		if(level < 5)
		{
			printf("レベルが足りない!\n");
			break;
		}
		if(rand()  % 9 == 0)
		{
			printf("当たらなかった!\n");
			break;
		}
		if(rand()  % 14 == 0)
		{
			u_atdamage += user.critical_d;
			printf("急所に命中!\n");
		}
		u_atdamage += 60 + (level * 1.7);
		printf("%dダメージヒット!\n",u_atdamage);
		user.mhp -= u_atdamage;
		break;
		
		case 6://スマホ
		if(level < 6)
		{
			printf("レベルが足りない!\n");
			break;
		}
		if(rand()  % 9 == 0)
		{
			printf("繋がらなかった!\n");
			break;
		}
		switch(rand() % 3)
		{
			case 0:
			u_heal = 35 + level * 2.5;
			printf("ケーキを注文!HPを%d回復!\n",u_heal);
			user.userhp += 35;
			break;
			case 1:
			u_heal = 45 + level * 2.25;
			printf("鯖缶を注文!HPを%d回復!\n",u_heal);
			user.userhp += 45;
			break;
			case 2:
			u_heal = 55 + level * 2;
			printf("肉まんを注文!HPを%d回復!\n",u_heal);
			user.userhp += 55;
			break;
		}	
		break;
		
		case 7://落雷
		if(level < 7)
		{
			printf("レベルが足りない!\n");
			break;
		}
		if(rand()  % 6 == 0)
		{
			printf("当たらなかった!\n");
			break;
		}
		if(rand()  % 16 == 0)
		{
			u_atdamage += user.critical_d;
			printf("急所に命中!\n");
		}
		u_atdamage += 75 + (level * 1.9);
		printf("%dダメージヒット!\n",u_atdamage);
		user.mhp -= u_atdamage;
		break;
	
		case 8://バリア
		if(level < 8)
		{
			printf("レベルが足りない!\n");
			break;
		}
		if(!rand() % 6 )//真では無かったら
		{
			printf("呼び出せなかった!\n");
			break;
		}
		u_atdamage = rand() % 3 + 1 + level / 25;
		printf("バリアを%dターン起動!\n",u_atdamage);
		user.valflag  = u_atdamage;
		user.uvalflag = u_atdamage;	
		
		break;
		
		case 3://ヒノキの棒
		if(level <= 2)
		{
			printf("レベルが足りない!\n");
			break;
		}
		if(rand()  % 13 == 0)
		{
			printf("当たらなかった!\n");
			break;
		}
		if(rand()  % 11 == 0)
		{
			u_atdamage += user.critical_d;
			printf("急所に命中!\n");
		}
		u_atdamage += 35 + (level * 1.68);
		printf("%dダメージヒット!\n",u_atdamage);
		user.mhp -= u_atdamage;
		break;			
	
		case 9://ポイズンボム	
		if(level < 9)
		{
			printf("レベルが足りない!\n");
			break;
		}	
		if(rand()  % 7 == 0)
		{
			printf("当たらなかった!\n");
			break;
		}
		printf("65ダメージヒット!(毒継続ターン:%d)\n",user.pbom_flag = rand() % 5 + 3);
		user.uzi    = 'd'; 
		user.uzi_at = 60 + (level * 1.55);
 		user.mhp -= 65;
		user.pbom = user.pbom_flag;
		break;
		
		case 10:
		if(level < 10)
		{
			printf("レベルが足りない!\n");
			break;
		}        
		printf("どちらを実行する? 回復:1,攻撃:2\t");
		scanf("%d",&run_q);
		switch(run_q)
		{
			case 1:
			printf("ヘルスドローンを起動!(使用可能ターン:%d)\n",
			       user.docd_flag = rand() % 4 + 1);
			user.docd = user.docd_flag;
			break;
			
			case 2:
			printf("アタックドローンを起動!(使用可能ターン:%d)\n",
			       user.atd_flag = rand() % 4+1);
			user.atd = user.atd_flag;
			
			break;
		}	
		
		break;
		//case 11:
	//	for(i=0;user.item[i] != NULL;i++)
	/*	{
			if(i == MOB_MAX)
			{
				flag = 1;
				break;
			}
		}
		if(flag)
		{
			break;
		}
		else
		{
			//printf("どのアイテムを使う?\n");	
			//printShikaku(MOB_MAX,*dropItem);
		}
			*/

	if(mob[enemyNum].mvalflag == 1 && user.uvalflag != 1)
	{
		printf("%sがバリアを使用!%d%%軽減!\n",mob[enemyNum].name,mob[enemyNum].hp / 75);
		u_atdamage -= mob[enemyNum].hp / 75;
		user.mhp -= u_atdamage;
		//printHPinfo(enemyNum);
		return;
	}
	
	switch(user.uzi)
	{
		
		case 'y':
			if(user.fire_flag >= 0)
			{
				printf("やけどダメージ！\n");
				printf("%sに%dダメージ!\n",mob[enemyNum].name,user.uzi_at);
				user.mhp -= user.uzi_at;
				user.fire--;
				user.fire_flag--;
				break;
				if(!user.fire_flag)
				{
					printf("%sの火傷が治った!",mob[enemyNum].name);
				}
				break;
			}
/*		
		case 's':
			printf("しもやけダメージ!");
			printf("あなたは%dダメージを受けた!\n"mob[enemyNum].zi_at);
			userhp -= mob[enemyNum].zi_at;
*/		
		case 'd':
			if(user.pbom_flag >= 0 && !user.fflag)
		 	{
			      printf("毒ダメージ!\n");
				printf("%sに%dダメージ!\n",mob[enemyNum].name,user.uzi_at);
				user.mhp -= user.uzi_at;
				user.pbom--;
				user.pbom_flag--;
				break;
				if(!user.pbom_flag)
				{
					printf("%sの毒が切れた!",mob[enemyNum].name);
				}
		 	}		
	} 
	}
	if(user.docd_flag >= 1 && user.docd >= 1)
	{
		u_heal += 65 + level * 2.8;
		printf("ヘルスドローンからHPを%d回復!\n",u_atdamage);
		user.userhp += (65 + level * 2.8);
		user.docd_flag--,user.docd--;
	}
	if(user.atd_flag >= 1 && user.atd >= 1)
	{
		u_atdamage += 65 + level * 2.8;
		printf("アタックドローンで敵に%dダメージ!\n",u_atdamage);
		user.mhp -= (65 + level * 2.8);
		user.docd_flag--,user.docd--;		
	}
}
	


void
cptern(int enemyNum,int USER_HP_MAX)        
{
	int waza;
	char *str_waza;

	waza = rand() % 2 + 1;
		
	if( waza == 1 )
	{
		str_waza = mob[enemyNum].waza1;
		wat = mob[enemyNum].at1;
	}
	else
	{
		str_waza = mob[enemyNum].waza2;
		wat = mob[enemyNum].at2;
	}
	printf("%sの%s!\n",mob[enemyNum].name,str_waza);
/*	if(mob[enemyNum].waza2 == str_waza,mob[enemyNum].hitrate2)
	{
		if((rand() % mob[enemyNum].hitrate2) == 0)
		{
			printf("当たらなかった!\n");
			return;	
		}
	}else if(mob[enemyNum].waza1 == str_waza,mob[enemyNum].hitrate1)
	{
		if(rand() % mob[enemyNum].hitrate1 == 0)
		{
			printf("当たらなかった!\n");
			return;	
		}	
		
	}*/
	if(user.valflag && user.uvalflag && !mob[enemyNum].mvalflag
	 && (!mob[enemyNum].sbreak1 && !mob[enemyNum].sbreak2 && !mob[enemyNum].mvalflag) )
	{
		v_atdamage = 100 - level / 2;
		//printf("debug:level-%d,v_level-%d",level,v_level);
		printf("バリア起動！%d%%軽減！\n",v_atdamage);
		wat = wat / v_atdamage;
		printf("あなたは%dダメージを受けた!\n",wat);
		user.userhp -= wat;
		user.valflag  -= 1;
		user.uvalflag -= 1;
		return;
	}
	if((str_waza == mob[enemyNum].waza2 && mob[enemyNum].mval2 == 1)||
	   (str_waza == mob[enemyNum].waza1 && mob[enemyNum].mval1 == 1))
	{
		printf("%sが1ターンバリアを起動!\n",mob[enemyNum].name);
		mob[enemyNum].mvalflag = 1;
		return;
	}
	printf("あなたは%dダメージを受けた!\n",wat);
	user.userhp -= wat;
	switch(mob[enemyNum].zi)
	{
		
		case 'y':
			printf("やけどダメージ！\n");
			printf("あなたは%dダメージを受けた!\n",mob[enemyNum].zi_at);
			user.userhp -= mob[enemyNum].zi_at;
			break;
		
		case 's':
			printf("しもやけダメージ!\n");
			printf("あなたは%dダメージを受けた!\n",mob[enemyNum].zi_at);
			user.userhp -= mob[enemyNum].zi_at;
			
	}
	if(user.userhp > 0)
	{
        //printHPinfo(enemyNum);
	}
	else 
	{
		printf("あなたは死にました\n");
//		FILE* fp;
//		fprintf(fp,"%d,%d,%d",(user.xp - 250),(now_levelxp - 250),level);
	
		exit(0);
	}
			
}


void shoptern(char shoplist[15][250])
{
	int runcheck = rand() % 2,listopen = 0,buynumber = 0,buycheck =0;
	
	int listpeg[15] =
	{
		15,
		30,
		20,
		45,
		30,
		50,
		45,
		60,
	};	
	
	if(!runcheck)
	{
		return;
	}
	printf("ショップを見つけた!\n");
	u_atdamage = rand() % 6 + 3;
	for(listopen = 0;listopen >= u_atdamage;listopen++)
	{
		printf("%d:%s\n",listopen+1,shoplist[listopen]);
	}
	printf("何を買う?");
	scanf("%d",&buynumber);
	printf("%sを購入:%dペグを消費します。よろしいですか? y:1,n:0",shoplist[buynumber],listpeg[buynumber]);
	scanf("%d",&buycheck);
	if(buycheck)
	{
		user.money -= listpeg[buynumber];
	}
	
	return;	
}


int printShikaku(int argc,char *argv[])
{
	int i,j,k;
	int sect;
	
	for(i=0;i<L_NUM_MAX;i++)
	{
		printf("*");
		sleep(0.01);
	}
	printf("\n");
	for(i=0;i<0;i++)
	{
		printf("*");
		for(j=0;j<L_NUM_MAX-2;j++)
		{
			printf(" ");
		}
		printf("*\n");
	}
	/*if(argc > 7)
	{
		argc -= 2;
	}else
	{
		argc -= 1;
	}*/
	for(i=0;i < argc;i++)/*前条件i<(argc < 8 ? argc - 2:argc)*/
	{
//		printf("strlen:%d\n",strlen(argv[i])/3*2);
		printf("* %d:%s",i,argv[i]);
		for(j=0;j<(int)(L_NUM_MAX-2-((strlen(argv[i])/3*2)+3));j++)
		{
			printf(" ");
		}
		printf("*\n");
	}
	
	for(i=0;i<0;i++)
	{
		printf("*");
		for(j=0;j<L_NUM_MAX-2;j++)
		{
			printf(" ");
		}
		printf("*\n");
	}
	for(i=0;i<L_NUM_MAX;i++)
	{
		printf("*");
	}
	printf("\n");
	scanf("%d",&sect);
//	printf("sect=%d\n",sect);
	
	return sect;
}

void printBar(int hp,int hpMax)
{
    int i;
    int barNum = hp*10/hpMax;

    for(i=0;i<10;i++)
    {
        if( i<=barNum )
        {
            printf("+");
        }
        else
        {
            printf(" ");
        }
    }
}


void printHPinfo(int enemyNum,int USER_HP_MAX)
{
 int nowMax = (mob[enemyNum].hpmax<USER_HP_MAX) ? USER_HP_MAX : mob[enemyNum].hpmax;
	  int i;

	  for(i=0;i<L_NUM_MAX;i++)
        {
            printf("-");
        }
        if(user.mhp <= 0)
        {
        	user.mhp = 0;
        }
        printf("\n");
        printf("<<<HP>>>\n");
        printBar(user.mhp,nowMax);
		printf("%d / %d %s  ",user.mhp,mob[enemyNum].hpmax,mob[enemyNum].name);
            printf("\x1b[31m");
        	printf("-%d\n",u_atdamage);
       	printf("\x1b[0m");

        printBar(user.userhp,nowMax);
  		printf("%d / %d %s  ",user.userhp,USER_HP_MAX,"あなた");
        	printf("\x1b[32m");
        	printf("+%d ",u_heal);
       	printf("\x1b[0m");
        	printf("\x1b[31m");
        	printf("-%d\n",wat);
       	printf("\x1b[0m");

        for(i=0;i<L_NUM_MAX;i++)
        {
            printf("-");
        }
        printf("\n");
}




int finishq(int *fq)
{
	printf("続けますか?(yes:1,no:0)\n");	
	scanf("%d",&*fq);
//	printf("debug.fq=%d",fq);
	return *fq;
}

//void printf_grey()
//{
//	printf("\x1b[47m");
//	printf("%s",str);
//	printf("\x1b[49m");
//}


/*int passcheck()
{
	//char username[50] ="gura-tan"; 
	int password = 2131;
	char/* q_username[50],q_password[50];
	
	while(1)
	{
		//printf("ユーザ名:");
	
		//fgets(q_username,sizeof(q_username),stdin);
		//q_username[strlen(q_username)-1] = NULL;
		//if(q_username != username)
		//{
		//	printf("%s,%s",username,q_username);
	//		continue;
	//	}	
		
		printf("パスワード:");
		fgets(q_password,sizeof(q_password),stdin);
		q_password = atoi(q_password);
		if(q_password != password)
		{
			continue;
		}
		printf("認証完了\n");
		break;
	}
	
	return 0;
}
*/
int skill_check()
{
	int random = 0;
    int i;

	for(i=0;i>6;i++)
	{
		if(!rand() % 3 && !random)
		{
			printf("\x1b[46m");
			printf("  ");
			printf("\x1b[49m");
		}
		printf("-");
	}
	
	return 0;
}
