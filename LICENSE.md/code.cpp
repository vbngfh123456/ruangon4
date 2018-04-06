#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define L 1000            //哈希表的长度
#define RAND_MAX 10       //随机数范围
#define M 47              //除留取余数值
#define NAME_NO 35        //人名的个数
#define SUCCESS 1
#define UNSUCESS 0
#define ElemType char
const int MOD0 = 50;
typedef struct	Hash	//哈希表
{
	ElemType *data;
	int s;				//查找长度
	int k;				//当前姓名的ASCII码
}Hash;Hash hlist[L];

typedef struct	DATE		//班级成员
{   char *data;			//姓名
    int k;				//姓名ASCII码的和
}DATA;DATE DATALIST[NAME_NO];
char s[20];

void input() //姓名（结构体数组）初始化
{   char *m;
    DATALIST[0].data="chenlu";
    DATALIST[1].data="wanning";
    DATALIST[2].data="mengxianxian";
    DATALIST[3].data="wanrui";
    DATALIST[4].data="mengliu";
    DATALIST[5].data="hubo";
    DATALIST[6].data="liuzijun";
    DATALIST[7].data="lvxiaoyun";
    DATALIST[8].data="fengyuzheng";
    DATALIST[9].data="chenzhuo";
    DATALIST[10].data="xushanze";
    DATALIST[11].data="zhangtianqi";
    DATALIST[12].data="xudong";
    DATALIST[13].data="wangjiangfeng";
    DATALIST[14].data="liuya";
    DATALIST[15].data="liupengfei";
    DATALIST[16].data="liuxueye";
    DATALIST[17].data="zhanglin";
    DATALIST[18].data="liyibo";
    DATALIST[19].data="wangyalong";
    DATALIST[20].data="jiangminliang";
    DATALIST[21].data="zengzihui";
    DATALIST[22].data="yaosiqi";
    DATALIST[23].data="zhangziyang";
    DATALIST[24].data="guanxinyu";
    DATALIST[25].data="lizhuoru";
    DATALIST[26].data="lvsida";
    DATALIST[27].data="liangheng";
    DATALIST[28].data="yuanrui";
    DATALIST[29].data="haozhirong";
    DATALIST[30].data="hudeguang";
    DATALIST[31].data="lixingming";
    DATALIST[32].data="puxuebing";
    DATALIST[33].data="fuchangyu";
    DATALIST[34].data="hetao";
    for(int i=0;i<NAME_NO;i++)
	{
		DATALIST[i].k=0;
        m=DATALIST[i].data;
        for(int r=0;m[r];r++)
			DATALIST[i].k = m[r] + DATALIST[i].k;
	}
}
int hashk(char *name)
{
    int s0=0,r;
    for(r=0;*(name+r)!='\0';r++)
        s0=*(name+r)+s0;
    return s0;
}
int hash0(char *name)
{
    return hashk(name)%M;
}
void init_hash()
{
    for(int i=0;i<L;i++)	//哈希表的初始化
    {
        hlist[i].data="";
        hlist[i].k=0;
        hlist[i].s=0;
    }
}
void insert_hash(int adr,int mo,int i)   //冲突处理
{
    int d=adr,sum = 0;
    if(hlist[adr].s==0)
    {
        hlist[adr].k=DATALIST[i].k;
        hlist[adr].data=DATALIST[i].data;
        hlist[adr].s=1;			//此处已有数据
    }
    else if(mo==1)
    {
        do
        {
            d=d+1;					 //线性探测再散列法处理冲突
            sum=sum+1;                    //查找次数加1
        }while (hlist[d].s!=0);
        hlist[d].k=DATALIST[i].k;
        hlist[d].data=DATALIST[i].data;
        hlist[d].s=sum+1;
    }
    else if(mo==2)
    {
        do
        {
            srand(DATALIST[i].k);
            d=(d+rand()%L)%M;			 //伪随机数探测再散列法处理冲突
            sum=sum+1;                    //查找次数加1
        }while (hlist[d].s!=0);
        hlist[d].k=DATALIST[i].k;
        hlist[d].data=DATALIST[i].data;
        hlist[d].s=sum+1;
    }
}
void show_way()
{
    printf("请选择冲突处理方法\n");
	printf("1.线性探测再散列\n");
	printf("2.伪随机数探测再散列\n");
}
int CreateHashList0() //余数 建立哈希表
{
	int num;
    show_way();
	scanf("%d",&num);

    init_hash();
    for(int i=0;i<L;i++)
    {
        int adr=(DATALIST[i].k)%M;  //哈希函数（除留余数）
        if(i==NAME_NO)
            break;
        insert_hash(adr,num,i);
    }
    if(num==1) return 1;
    else if(num==2) return 2;
}

int CreateHashList1() //随机 建立哈希表
{
	int num;
    show_way();
	scanf("%d",&num);

	init_hash();
    for(int i=0;i<L;i++)
    {
        srand(DATALIST[i].k);
        itoa(DATALIST[i].k,s,10);
        int adr= rand() % MOD0;  //哈希函数（随机）
        if(i==NAME_NO)
            break;
        insert_hash(adr,num,i);
    }
	if(num==1) return 1;
	else if(num==2) return 2;
}

int CreateHashList2() //分割法 建立哈希表
{
	int num;
    show_way();
	scanf("%d",&num);

	init_hash();
    for(int i=0;i<L;i++)
    {
        itoa(DATALIST[i].k,s,10);
        int adr= s[1]*10 + s[2];  //哈希函数（分割）
        if(i==NAME_NO)
            break;
        insert_hash(adr,num,i);
    }
    if(num==1) return 1;
    else if(num==2) return 2;
}
int SearchHash1(char *name,Hash hlist[],int m,int *k) //k为查找次数,线性探测查找
{
        int n=0;
		int adr;
		if(m==0) adr = hash0(name);
		else if(m==1){
            for(int i=0;i<L;++i){
                if(strcmp(hlist[i].data,name)==0){
                    *k = hlist[i].s;
                    return SUCCESS;
                }
            }
		}
		else if(m==2) {
            itoa(hashk(name),s,10);
            adr = s[1]*10 + s[2];
		}
		if(stricmp(hlist[adr].data,name)==0)
		{
			*k=hlist[adr].s;
			return SUCCESS;
		}
		else
		{
			while(1)
			{
				if(n>L||strlen(hlist[adr].data)==0)
					return UNSUCESS;
				adr=adr+1;
				n++;
				if(stricmp(hlist[adr].data,name)==0)
				{
					*k=hlist[adr].s;
					return SUCCESS;
				}
			}
		}
}
int SearchHash2(char *name,Hash hlist[],int *k) //k为查找次数,伪随机数探测查找
{
		for(int i=0;i<L;++i){
            if(strcmp(hlist[i].data,name)==0){
                *k = hlist[i].s;
                return SUCCESS;
            }
        }
        return UNSUCESS;
}
void print()
{
    printf("\t沈阳航空航天大学-计算机学院-冯玉正-学号：153401010110\n");
	printf("*******************************************\n");
	printf("**					**\n");
	printf("**					**\n");
	printf("**		哈希表			**\n");
	printf("**					**\n");
	printf("**					**\n");
	printf("**					**\n");
	printf("******************************************\n");
}

int main()
{
	char name[20];
	int result=0,m,n;//m判断选择探测方法
	int k;
	int i=1;
	float c=0,d;
	while(1)
	{
	lp:	print();
		input();
		int mod = 0;
		printf("请选择哈希算法\n");
		printf("1.除留取余法\n");
		printf("2.随机函数法\n");
		printf("3.分割法\n");
		scanf("%d",&mod);
		switch(mod)
		{
            case 1:m = CreateHashList0();break;
            case 2:m = CreateHashList1();break;
            case 3:m = CreateHashList2();break;
		}
		printf("请选择\n");
		printf("1.查找姓名\n");
		printf("2.显示该哈希函数的平均查找长度\n");
		printf("3.退到上级\n");
		scanf("%d",&n);
		switch(n)
		{
		case 1:{
					if(m==1)
					{
						printf("请输入姓名\n");
						scanf("%s",name);
						result=SearchHash1(name,hlist,mod-1,&k);
						if(result==1)
						{
							printf("查找成功\n");
							printf("查找长度为%d\n",k);
						}
						else
							printf("查找失败\n");
					}
					else if(m==2)
					{
						printf("请输入姓名\n");
						scanf("%s",name);
						result=SearchHash2(name,hlist,&k);
						if(result==1)
						{
							printf("查找成功\n");
							printf("查找长度为%d\n",k);
						}
						else
							printf("查找失败\n");
					}

			   }break;
		case 2:{
					d=0;
					for(i=0;i<L;i++)
						d+=hlist[i].s;
					c=d/NAME_NO;
					printf("平均查找长度为%f\n",c);
			   }break;
		case 3:{
					system("cls");
					goto lp;
			   }break;
		}
	}
	return 0;
}
