/******************预处理模块和结构体******************/
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#define LEN sizeof(struct student)//sizeof(char)
#define FORMAT "%-12d%-12s%-13.1f%-13.1f%-13.1f%-13.1f\n"
#define  DATA stu[i].num,stu[i].name, stu[i].chinese,stu[i].math,stu[i].english,stu[i].sum
/******************定义学生成绩结构体******************/
struct student		
{ 
	int num;			/*学号*/ 
	char name[15];	/*姓名*/
	float chinese;	/*语文课*/
	float math;		/*数学课*/
	float english;		/*英语课*/
	float sum;		/*总分*/
};
struct student stu[50];	/*定义全局结构体数组*/

/******************函数声明与简介******************/
void input();	/*录入学生成绩信息*/
void show();	/*显示学生基本信息*/
void order();	/*按总分排序*/
void del();		/*删除学生成绩信息*/
void modify();	/*修改学生成绩信息*/
void menu();	/*程序主菜单*/
void insert();	/*插入学生信息*/
void total();	/*计算总人数*/
void search();	/*查找学生信息*/
/******************主函数******************/
int main()
{ 
	int n;
	menu();
	scanf("%d",&n);			/*输入选择功能的编号*/
	while(n)
	{ 
		switch(n)
		{ 
		case 0: exit(0);			/*退出功能*/
		case 1: input();break;		/*录入记录功能函数调用*/
		case 2: search();break;		/*查找记录功能函数调用*/
		case 3: del();break;		/*删除记录功能函数调用*/
		case 4: modify();break;		/*修改记录功能函数调用*/
		case 5: insert();break;		/*插入记录功能函数调用*/
		case 6: order();break;		/*记录排序功能函数调用*/
		case 7: total();break;		/*人数统计功能函数调用*/
		case 8: show();break;		/*所有记录显示功能函数调用*/
		default:printf("输入有误，请重新输入:");break;
		}
	getch();
	menu();							/*菜单界面循环显示*/
	scanf("%d",&n);
	}
	return 0;
}
/******************自定义函数实现菜单功能******************/
void menu()
{
	system("cls");
	printf("\t\t|-------------学生信息管理系统----------|\n");
	printf("\t\t|\t 0. 退出系统\t\t\t|\n");
	printf("\t\t|\t 1. 输入记录\t\t\t|\n");
	printf("\t\t|\t 2. 查找记录\t\t\t|\n");
	printf("\t\t|\t 3. 删除记录\t\t\t|\n");
	printf("\t\t|\t 4. 修改记录\t\t\t|\n");
	printf("\t\t|\t 5. 插入记录\t\t\t|\n");
	printf("\t\t|\t 6. 记录排序\t\t\t|\n");
	printf("\t\t|\t 7. 记录个数\t\t\t|\n");
	printf("\t\t|\t 8. 显示记录\t\t\t|\n");
	printf("\t\t|---------------------------------------|\n");
	printf("\t\t请输入您的操作(0-8):");
}
/******************录入学生信息******************/
void input()
{ 
	int i,m=0;	/*变量m表示记录的条数*/
	char ch[2];  
	FILE *fp;	/*定义文件指针*/
	if((fp=fopen("stuData.txt","a+"))==NULL)	/*打开指定文件*/
	{ 
		printf("打开文件失败\n");
		return;
	}
	while(!feof(fp)) //  feof=>file end of file
	{
		if(fread(&stu[m] ,LEN,1,fp)==1)
			m++;	/*统计当前记录条数*/
	}
	fclose(fp);
	if(m==0)
		printf("没有数据!\n");
	else
	{
		system("cls");   //清屏
		show();	/*调用show函数，显示原有信息*/
	}
	
	if((fp=fopen("stuData.txt","wb"))==NULL)
	{
		printf("打开文件失败\n");
		return;
	}
	for(i=0;i<m;i++)
	{
		fwrite(&stu[i] ,LEN,1,fp);	/*向指定的磁盘文件写入信息*/
	}

	printf("请确认(y/n):");
	scanf("%s",ch);
	while(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)	/*判断是否要录入新信息*/
	{
		printf("学号:");
		scanf("%d",&stu[m].num);	/*输入学生学号*/
		for(i=0;i<m;i++)
			if(stu[i].num==stu[m].num)
			{
				printf("此学号已存在！");
				getch();
				fclose(fp);
				return;
			}
		/*如果学号可用，则继续输入其它数据*/
		printf("姓名:");
		scanf("%s",stu[m].name);		/*输入学生姓名*/
		printf("语文成绩:");
		scanf("%f",&stu[m].chinese);	/*输入语文课成绩*/
		printf("数学成绩:");
		scanf("%f",&stu[m].math);		/*输入数学课成绩*/
		printf("英语成绩:");
		scanf("%f",&stu[m].english);	/*输入英语课成绩*/
		stu[m].sum=stu[m].chinese+stu[m].math+stu[m].english;	/*计算出总成绩*/
		if(fwrite(&stu[m],LEN,1,fp)!=1)	/*将新录入的信息写入指定的磁盘文件*/
		{
			printf("保存失败!");
			getch();
		}
		else
		{
			printf("%s 已保存!\n",stu[m].name);
			m++;
		}
		printf("是否继续?(y/n):");	/*询问是否继续*/
		scanf("%s",ch);
	}
	fclose(fp);
	printf("操作成功!\n");
}
/******************自定义查找函数******************/
void search()
{ 
	FILE *fp;
	int snum,i,m=0;
	char ch[2];
	if((fp=fopen("stuData.txt","rb"))==NULL)
	{ 
		printf("打开文件失败\n");
		return;
	}
	while(!feof(fp))  
		if(fread(&stu[m],LEN,1,fp)==1) 
			m++;
	fclose(fp);
	if(m==0) 
	{
		printf("文件无记录!\n");
		return;
	}
	printf("请输入需要查找的学生学号:");
	scanf("%d",&snum);
	for(i=0;i<m;i++)
		if(snum==stu[i].num)		/*查找输入的学号是否在记录中*/
		{ 
			printf("学生数据已找到，确认显示?(y/n)");
			scanf("%s",ch);
			if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0) 
			{
				printf("学号        姓名          语文         数学         英语        总分\t\n");
				printf(FORMAT,DATA);	/*将查找出的结果按指定格式输出*/
				break;
			}
		}   
	if(i==m) 
		printf("查找失败!\n");			/*未找到要查找的信息*/
}
/******************自定义删除函数******************/
void del()
{
	FILE *fp;
	int snum,i,j,m=0;
	char ch[2];
	if((fp=fopen("stuData.txt","r+"))==NULL)
	{
		printf("打开文件失败\n");return;
	}
	while( !feof(fp) )  
		if(fread(&stu[m],LEN,1,fp)==1) 
			m++;
		fclose(fp);
		if(m==0) 
		{
			printf("文件无记录!\n");
			return;
		}
		show();									/*显示已有数据*/
		printf("请输入需要删除的学生学号:");
		scanf("%d",&snum);	
		for(i=0;i<m;i++)
		{
			if(snum==stu[i].num)				/*查找到输入的学号*/
			{    
				printf("数据已找到，是否确认删除?(y/n)");
				scanf("%s",ch);
				if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)/*判断是否要进行删除*/
				{	
					for(j=i;j<m;j++)
						stu[j]=stu[j+1];		/*将记录依次移到前面的位置*/
					m--;							/*记录的总个数减1*/
					if((fp=fopen("stuData.txt","wb"))==NULL)
					{ 
						printf("打开文件失败\n");
						return;
					}
					for(j=0;j<m;j++)/*将更改后的记录重新写入指定的磁盘文件中*/
						if(fwrite(&stu[j] ,LEN,1,fp)!=1)
						{ 
							printf("对不起，保存失败!\n");
							getch();				/*程序暂停*/
						}
						fclose(fp);
						printf("删除成功!\n");
						return;
				}
				else				/*用户输入的字符不是y或Y，表示取消删除*/
				{
					printf("取消删除!\n");
					return;
				}
			}
		} 
printf("没有找到要删除的信息！\n");
}
/******************自定义修改函数******************/
void modify()
{ 
	FILE *fp;
	int i,j,m=0,snum;
	if((fp=fopen("stuData.txt","r+"))==NULL)
	{ 
		printf("打开文件失败\n");
		return;
	}
	while(!feof(fp))  
		if(fread(&stu[m],LEN,1,fp)==1) 
			m++;
	if(m==0) 
	{
		printf("文件无记录!\n");
		fclose(fp);
		return;
	}
	show();
	printf("请输入你要修改的学生的学号\n");
	printf("学号是:");
	scanf("%d",&snum);
	for(i=0;i<m;i++)
	{
		if(snum==stu[i].num)/*检索记录中是否有要修改的信息*/
		{
			printf("学生数据已找到，请修改!\n");			
			printf("name:");
			scanf("%s",stu[i].name);/*输入名字*/
			printf("chinese:");
			scanf("%f",&stu[i].chinese);/*输入语文课成绩*/
			printf("math:");
			scanf("%f",&stu[i].math);/*输入数学课成绩*/
			printf("english:");
			scanf("%f",&stu[i].english);/*输入英语课成绩*/
			printf("modify successful!");			
			stu[i].sum=stu[i].chinese+stu[i].math+stu[i].english;
			if((fp=fopen("stuData.txt","wb"))==NULL)
			{ 
				printf("打开文件失败\n");
				return;
			}
			for(j=0;j<m;j++)/*将新修改的信息写入指定的磁盘文件中*/
				if(fwrite(&stu[j] ,LEN,1,fp)!=1)
				{ 
					printf("保存失败!");
					getch(); 
				}
			fclose(fp);
			return ;
		}	 
	}
	printf("没有找到匹配信息！\n");
}
/******************自定义插入函数******************/
void insert()
{ 
	FILE *fp;
	int i,j,k,m=0,snum;
	if((fp=fopen("stuData.txt","r+"))==NULL)
	{ 
		printf("打开文件失败\n");
		return;
	}
	while(!feof(fp))  
		if(fread(&stu[m],LEN,1,fp)==1) m++;
	if(m==0) 
	{
		printf("没有数据!\n");
		fclose(fp);
		return;
	}
	printf("请输入数据插入的位置：\n");
	scanf("%d",&snum);/*输入要插入的位置*/
	for(i=0;i<m;i++)
		if(snum==stu[i].num)
			break;
	for(j=m-1;j>i;j--)
		stu[j+1]=stu[j];		/*从最后一条记录开始均向后移一位*/
	printf("请输入待插入数据信息.\n");
	printf("学号:");	
	scanf("%d",&stu[i+1].num);
	for(k=0;k<m;k++)
		if(stu[k].num==stu[m].num)
		{
			printf("此学号已存在！");
			getch();
			fclose(fp);
			return;
		}
	printf("姓名:");
	scanf("%s",stu[i+1].name);
	printf("语文成绩:");
	scanf("%f",&stu[i+1].chinese);
	printf("数学成绩:");
	scanf("%f",&stu[i+1].math);
	printf("英语成绩:");
	scanf("%f",&stu[i+1].english);
	stu[i+1].sum=stu[i+1].chinese+stu[i+1].math+stu[i+1].english;
	if((fp=fopen("stuData.txt","wb"))==NULL)
	{ 
		printf("打开文件失败\n");
		return;
	}
	for(k=0;k<=m;k++)
		if(fwrite(&stu[k] ,LEN,1,fp)!=1)		/*将修改后的记录写入磁盘文件中*/
		{ 
			printf("保存失败!"); 
			getch(); 
			return;
		}
	printf("插入数据成功!");
	getch();
	fclose(fp);
}
/******************自定义排序函数******************/
void order()
{ 
	FILE *fp;
	struct student t;
	int i=0,j=0,m=0;
	if((fp=fopen("stuData.txt","r+"))==NULL)
	{ 
		printf("打开文件失败!\n");
		return;
	}
	while(!feof(fp)) 
		if(fread(&stu[m] ,LEN,1,fp)==1) 
			m++;
	fclose(fp);
	if(m==0) 
	{
		printf("无记录!\n");
		return;
	}
	if((fp=fopen("stuData.txt","wb"))==NULL)
	{
		printf("打开文件失败\n");
		return;
	}
	for(i=0;i<m-1;i++)
		for(j=i+1;j<m;j++)/*双重循环实现成绩比较并交换*/
			if(stu[i].sum<stu[j].sum)
			{ 
				t=stu[i];stu[i]=stu[j];
				stu[j]=t;
			}
	if((fp=fopen("stuData.txt","wb"))==NULL)
	{ 
		printf("打开文件失败\n");
		return;
	}
	for(i=0;i<m;i++)	/*将重新排好序的内容重新写入指定的磁盘文件中*/
		if(fwrite(&stu[i] ,LEN,1,fp)!=1)
		{ 
			printf("%s 保存失败!\n"); 
			getch();
		}
	fclose(fp);
	printf("操作成功\n");
}
/******************显示学生总人数******************/
void total()
{ 
	FILE *fp;
	int m=0;
	if((fp=fopen("stuData.txt","r+"))==NULL)
	{ 
		printf("打开文件失败\n");
		return;
	}
	while(!feof(fp))  
		if(fread(&stu[m],LEN,1,fp)==1) 
			m++;/*统计记录个数即学生个数*/
	if(m==0)
	{
		printf("文件无记录!\n");
		fclose(fp);
		return;
	}
	printf("学生总数为 %d 位!\n",m);/*将统计的个数输出*/
		fclose(fp);
}
/******************显示学生信息******************/
void show()
{ 
	FILE *fp;
	int i,m=0;
	fp=fopen("stuData.txt","rb");
	while(!feof(fp))
	{
		if(fread(&stu[m] ,LEN,1,fp)==1) 
			m++;
	}  
	fclose(fp);
	printf("学 号      姓 名       语 文        数 学       英 语       总 分\t\n");
	for(i=0;i<m;i++)
	{ 
		printf(FORMAT,DATA);		/*将学生信息按指定格式打印*/
	}
}
