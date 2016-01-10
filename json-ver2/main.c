#include <stdio.h>
#include "cJSON.h"
#include <string.h>
#include <stdlib.h>
//#include <iostream.h>

/*create a json
 * {
 *	"name":"duanqi",
 *	"info":{
 *		"age":30,
 *		"sex":"male",
 *		"height":165,
 *		"work":true,
 *		"son":true
 *	}
 * }*/
void createOne(cJSON *root)
{
	cJSON *item = NULL;
	//root = cJSON_CreateObject();
	cJSON_AddStringToObject(root,"name","duanqi");
	cJSON_AddItemToObject(root,"info",item = cJSON_CreateObject());
	cJSON_AddNumberToObject(item,"age",30);
	cJSON_AddStringToObject(item,"sex","male");
	cJSON_AddNumberToObject(item,"height",165);
	cJSON_AddTrueToObject(item,"work");
	cJSON_AddTrueToObject(item,"son");
}

/*
 * {
 * 	"users":[
 * 			{
 * 				"usr":"duanqi",
 * 				"pwd":"qwe123"
 * 			},
 * 			{
 * 				"usr":"wang",
 * 				"pwd":"123456"
 * 			}
 * 		]
 * 		
 * }*/

void createTwo(cJSON *root)
{
	//cJSON *rootTwo= cJSON_CreateObject();
	cJSON *item = NULL;
	cJSON *item1 = NULL;
	cJSON *array = NULL;
	cJSON_AddItemToObject(root,"users",array = cJSON_CreateArray());
	cJSON_AddItemToArray(array,item = cJSON_CreateObject());
	cJSON_AddStringToObject(item,"usr","duanqi");
	cJSON_AddStringToObject(item,"pwd","qwe123");
	cJSON_AddItemToArray(array,item1 = cJSON_CreateObject());
	cJSON_AddStringToObject(item1,"usr","wang");
	cJSON_AddStringToObject(item1,"pwd","123456");
}

/*create a json
 *  * {
 *   *      "name":"duanqi",
 *    *      "info":{
 *     *              "age":30,
 *      *              "sex":"male",
 *       *              "height":165,
 *        *              "work":true,
 *         *              "son":true
 *          *      }
 *           * }*/


void parseOne(char *str)
{
	cJSON *item = NULL;
	cJSON *first = NULL;
	cJSON *second = NULL;
	cJSON *root = cJSON_Parse(str);
	if(root)
	{
		item = cJSON_GetObjectItem(root,"name"); // get : "name":"duanqi",
		printf("name is %s\n",item->valuestring); 
/* get :
 * 	  {
 *                  "age":30,
 *                   "sex":"male",
 *                   "height":165,
 *                   "work":true,
 *                   "son":true
 *        }
 * 
*/ 
		first = cJSON_GetObjectItem(root,"info");	// type is object	
		second = cJSON_GetObjectItem(first,"age");
		printf("age is %d\n",second->valueint);
		second = cJSON_GetObjectItem(first,"sex");
		printf("sex is %s\n",second->valuestring);
		second = cJSON_GetObjectItem(first,"height");
		printf("height is %d\n",second->valueint);
		second = cJSON_GetObjectItem(first,"work");
		printf("height is %d\n",second->valueint);
		second = cJSON_GetObjectItem(first,"son");
		printf("son is %d\n",second->valueint);
		
		cJSON_Delete(root);
	}
	
}

/*
 *  * {
 *   *      "users":[
 *    *                      {
 *     *                              "usr":"duanqi",
 *      *                              "pwd":"qwe123"
 *       *                      },
 *        *                      {
 *         *                              "usr":"wang",
 *          *                              "pwd":"123456"
 *           *                      }
 *            *              ]
 *             *              
 *              * }*/


void parseTwo(char *str)
{
	cJSON *item = NULL;
	cJSON *first = NULL;
	cJSON *second = NULL;
	int arrayNum = 0;
	cJSON *root = cJSON_Parse(str);
	if(root)
	{

/* 
 * [
 * 	{
 * 		"usr":"duanqi",
 * 		"pwd":"qwe123"
 * 	},
 * 	{
 * 		"usr":"wang",
 * 		"pwd":"123456"
 * 	}
 * ]
 */
		item = cJSON_GetObjectItem(root,"users");  // type is array
		arrayNum = cJSON_GetArraySize(item);	
		printf("arrayNum is %d\n",arrayNum);
		int i = 0;
		for(;i < arrayNum ;i++)
		{
			first = cJSON_GetArrayItem(item,i);  // item[n] n = 1,2,3...
			second = cJSON_GetObjectItem(first,"usr");
			printf("item[%d]'s usr is %s\n",i,second->valuestring);
			second = cJSON_GetObjectItem(first,"pwd");
			printf("item[%d]'s pwd is %s\n",i,second->valuestring);
		}		
	
		cJSON_Delete(root);
	}

}

int main()
{
	cJSON *rootOne = cJSON_CreateObject();
	createOne(rootOne);
	char * jsonStr = cJSON_Print(rootOne);
	printf("jsonStr is %s\n",jsonStr);
	parseOne(jsonStr);
	free(jsonStr);
	cJSON_Delete(rootOne); // 遍历释放内存
	rootOne = NULL;
	jsonStr = NULL;
	printf("+++++++++++++++++++++++++++++++\n");
	cJSON *rootTwo= cJSON_CreateObject();
	createTwo(rootTwo);
	jsonStr = cJSON_Print(rootTwo);
	printf("jsonStr is %s\n",jsonStr);
	parseTwo(jsonStr);
	free(jsonStr);
	jsonStr = NULL;
	cJSON_Delete(rootTwo);
	rootTwo = NULL;

	return 0;
}
