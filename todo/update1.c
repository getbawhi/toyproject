#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

#pragma warning(disable:4996)

#define LINE1 "=================================="
#define LINE2 "----------------------------------"
#define MAX 50
#define Text_MAX 256

/*
<일정 관리 프로그램> => 동기부여 가능하게 
>> 파일 시스템 

>>구현할 기능

0. 메인에 보일 화면 

- 메인 타이틀 / 오늘 날짜 
- 오늘의 일정 / <중요 일정> 
- 오늘의 일정
- 오늘의 할 일 
- 다가오는 일정 -- 급한 일정들 D-d 표시로 
- start 

1. 해야 할 일 보여주기 & 일정 보여주기 
	- 오늘 날짜 단위
	- 주 단위
	- 전체 목록 

2. 할 일 추가하기 - 구조체 / 카테고리, 이름 , 완료 여부 , 기한 , 중요도 (이모티콘 호환 ★)
3. 일정 추가하기 - 구조체 / 카테고리, 이름, 기한 , 기한 표시 여부 , 중요도 
4. 관리 - 삭제 , 수정 

5. 완료 된 할 일 보기 

6. 저장 


<할일 박물관 상점>

1. 공룡 뼈 얻기  (2/10) 
2. 유적 얻기
3. 공룡 해금 

<박물관>

1. 공룡 전시 
2. 인기 , 명성도 
3. 박물관 -> 공룡이 많을 수록 돈이 잘 벌림 

*/

// 파일 첫 줄에 글자 넣어서 관리 하는 시스템으로 바꾸기 

typedef struct todo {

	char category[50];
	char name[Text_MAX];
	char done[2];
	char date[10];
	char level[2];

}TODO;

typedef struct schedule {

	char category[50];
	char name[Text_MAX];
	int done;
	int date;
	int level;

}DAY;

void Menu();
void reset();
void Print(TODO* list, int cnt_file[2]);
void Print_all(TODO* list, int cnt_file[2]);
TODO* setup(int cnt_file[2]); // 처음 읽는 작업 
TODO* Add_todo(TODO *list, int cnt_file[2]); // 투두 만들기

void Save_File(TODO* list, int cnt_file[2]); //파일 세이브 
void Delete_todo(TODO* list, int cnt_file[2]); // 투두 지우기 

int main(){

	int cnt_file[2] = { 0,0 }; // 투두, 일정의 갯수 카운트 배열 
	int choice = -1;
	TODO* list = NULL;
	
	//프로그램 시작 시 파일 읽으며 시작 
	list = setup(cnt_file);
	int cnt_todo = 1;

	while (1)
	{
		system("cls");
		Menu();
		scanf("%d", &choice);


		switch(choice)
		{

		case 1:
			Print_all(list,cnt_file);
			break;
		case 2:
			list = Add_todo(list,cnt_file);
			break;
		case 3: //체크 기능 넣기 
			
			break;
		case 4:
			Delete_todo(list, cnt_file);
			break;

		case 5:
			Save_File(list, cnt_file);



		}



	}








	return 0;
}

TODO* setup(int cnt_file[2]) {

	char tmp[MAX][Text_MAX]; //잠시 담을 임시 저장소
	int cnt = 0;
	char* token = NULL;
	char* box[5] = { NULL }; //구조체 옮기기 전 잠시 넣을 곳 

	FILE* input = fopen("current_list.txt", "r");
	
	if (input == NULL)
	{
		printf("파일 열기를 실패하였습니다.\n");
	}

	fscanf(input, "%d", &cnt);
	fscanf(input, "%*c");

	for(int i=0; i<cnt; i++)
	{
		fgets(tmp[i], 256, input);
	
		
	}

	cnt_file[0] = cnt; //배열에 옮겨주기 
	

	TODO *list = (struct todo*)malloc(sizeof(struct todo) * cnt);


	for (int i = 0; i < cnt; i++)
	{
		token = strtok(tmp[i], "__");

		for (int j = 0; j < 5; j++)
		{
			box[j] = token;
			token = strtok(NULL, "__");
		}

		strcpy(list[i].category, box[0]);
		strcpy(list[i].name, box[1]);
		strcpy(list[i].done, box[2]);
		strcpy(list[i].date, box[3]);
		strcpy(list[i].level, box[4]);
		token = NULL;
	}

	return list;
}


void Menu() {

	printf("\n");
	printf("		Todo List Program     v.0.0\n");
	printf("		===========================\n");
	printf("		리스트					   \n");
	printf("								   \n");
	printf("		---------------------------\n");
	printf("		◎ 1. Show List (Current)\n");
	printf("		◎ 2. Add Todo\n");
	printf("		◎ 3. Check Todo\n");
	printf("		◎ 4. Delete\n");
	printf("		◎ 5. Save all\n");
	printf("		---------------------------\n");
	printf("		Choose >> ");

}

void reset()
{
	int reset = -1;
	printf("\n\nPress any number... >> ");
	scanf("%d", &reset);

}


void Print(TODO *list, int cnt_file[2])
{
	

	system("cls");
	
	printf("L I S T\n\n");
	printf(":: Name   \n");
	printf("================================================================\n");
	


	for (int i = 0; i < cnt_file[0]; i++)
	{
		printf("%d) %s  \t%-20s  \t",i+1, list[i].category, list[i].name);
		printf("%c%c월 %c%c일\t", list[i].date[4], list[i].date[5],
			list[i].date[6], list[i].date[7]);

		if (list[i].done[0] == '0') printf("□\n");
		else if (list[i].done[0] == '1') printf("■\n");

	}

	

}

void Print_all(TODO* list, int cnt_file[2]) {

	Print(list, cnt_file);

	reset();



}



TODO* Add_todo(TODO *list, int cnt_file[2]) {
	
	

	system("cls");
	
	int count = cnt_file[0];
	
	cnt_file[0] = cnt_file[0] + 1;

	list = (struct todo*)realloc(list,sizeof(struct todo) * cnt_file[0]);

	printf("\nADD LIST");
	printf("=======================================\n");
	printf("Todo category : ");

	scanf("%*c");

	gets(list[count].category);

	printf("\nTodo name : ");

	gets(list[count].name);

	printf("\nTodo date :");
	
	gets(list[count].date);
	

	printf("\nTodo level :");

	gets(list[count].level);

	strcpy(list[count].done, "0");

	reset();

	return list;

}

void Save_File(TODO* list, int cnt_file[2])
{
	char tmp[Text_MAX];

	FILE* output;

	output = fopen("current_list.txt", "w+");


	fprintf(output, "%d\n", cnt_file[0]); //현재 카운트 개수 첫줄에 적음


	for (int i = 0; i < cnt_file[0]; i++)
	{	
		
		fprintf(output, "%s__%s__%s__%s__%s__\n",
			 list[i].category, list[i].name, list[i].done, list[i].date, list[i].level);
		
		
		

	}

	fclose(output);
	
	//안내 메세지 코드
	printf("\n		Save successed!\n");
	int reset = -1;
	printf("\n		Press any number... >> ");
	scanf("%d", &reset);
	
}

void Delete_todo(TODO* list, int cnt_file[2])
{
	int choice = -1;

	system("cls");
	Print(list, cnt_file);

	printf("------------------------------------------\n");
	printf("# if you want to go back, press 0\n");
	printf("# Press the number you want to delete... >> ");


	scanf("%d", &choice);
	if (choice == 0) reset();
	
	else if (choice > cnt_file[0])
	{
		printf("\n\n# There's no number in the list... ");
		reset();
	}
	
	else {
		
		for (int i = choice - 1; i < cnt_file[0] - 1; i++)
		{
			memcpy(&list[i], &list[i + 1], sizeof(TODO));

		}

		cnt_file[0] = cnt_file[0] - 1;

		printf("\nDelete successed...");
		reset();



	}
	


}


