/*
 ============================================================================
 Name        : Prog_Proj_1.c
 Author      : Maha Alshawi
 Version     :
 Copyright   : @Dartmouth college
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>  // because man waitpid() said we'd need this
#include "html_template.h"
#include <stdarg.h>
//#define indent "========"
#define MAX_NUMBER_OF_PHOTOS 400
int main(int argc, char *argv[]) {
	//const char * filename
	// Adding comment
	int count,rc,pid,status,arg_count=0;
	char multi_arg[MAX_NUMBER_OF_PHOTOS][50];
	char command[MAX_NUMBER_OF_PHOTOS][5][50];
	memset(command,0,sizeof(command));
	mkdir("Maha",0777);
	if (argc > 1 && argc < MAX_NUMBER_OF_PHOTOS) {
		//for()
		//rc = fork();
		if(!strcmp(argv[1],"photos/*.jpg"))
		{
			//printf("BP1\n");
			DIR* d;
			struct dirent *dir;
			d=opendir("./main/photos");
			if(d)
			{
				while((dir=readdir(d))!=NULL)
				{
					const char *ext = strrchr(dir->d_name,'.');
					//printf("extend = %s\n",ext);
					if(strcmp(ext, ".jpg") == 0)
					{
						strcat(multi_arg[arg_count],"photos/");
						strcat(multi_arg[arg_count],dir->d_name);
						printf("%s\n",multi_arg[arg_count]);
						arg_count++;
					}
				}
				closedir(d);
			}
		}
		else
		{
			for(int i=1;i<argc;i++)
			{
				strcpy(multi_arg[arg_count],argv[i]);
				arg_count++;
			}
		}
		printf("count lenght = %d\n",arg_count);

		for (count = 0; count < arg_count; count++) {
			//printf("argv[%d] = %s\n", count, argv[count]);
			// source
			strcat(command[count][0],"./main/");
			strcat(command[count][0],(const char*)multi_arg[count]);
			// destination of thumbnail
			strcat(command[count][1],"./main/thumbnail/");
			strcat(command[count][1],(const char*)multi_arg[count]);
			// destination of properly oriented thumbnail
			strcat(command[count][2],"./main/destination2/");
			strcat(command[count][2],(const char*)multi_arg[count]);
			// destination of properly oriented picture
			strcat(command[count][3],"./main/destination3/");
			strcat(command[count][3],(const char*)multi_arg[count]);
			// destination of properly oriented medium size photo
			strcat(command[count][4],"./main/destination4/");
			strcat(command[count][4],(const char*)multi_arg[count]);

			printf("magick %s %s %s\r\n","convert -resize 10%",command[count][0],command[count][1]);
		}
		for(count = 0; count < arg_count; count++){
			rc = fork();
			printf("After Forking!! %s\n\n",command[count][1]);
			if(rc == 0){
				execlp("magick","convert","-resize","10%",command[count][0],command[count][1],NULL);
				exit(0);
			}
		}
		//pid = rc;
		//printf("%s my child has pid %d\n", indent, pid);
		//waitpid(pid, &status, 0);
		int var[arg_count-1];
		char caption[arg_count-1][200];

		for(count = 0; count < arg_count; count++){
			rc = fork();
			if(rc == 0){
				execlp("magick","display",command[count][1],  NULL);
			}
			pid=rc;
			rc = waitpid(pid, &status, 0);
			puts("For no rotation please enter 0\
						\rFor Counter CW enter 1\
						\rFor CW enter 2\nEnter:");

			scanf("%d",&var[count]);
			printf("Please write a caption for this picture \n");
			scanf("%s",(char *)caption[count]);
			if (var[count]==0)
			{
				rc=fork();
				if(rc==0)
				{
					execlp("magick","convert","-rotate","0",command[count][1],command[count][2],NULL);

				}
				rc=fork();
				if(rc==0)
				{
					execlp("magick","convert","-rotate","0",command[count][0],command[count][3],NULL);

				}
				pid = rc;
				waitpid(pid, &status, 0);
				rc=fork();
				if(rc==0)
				{
					execlp("magick","convert","-resize","25%",command[count][3],command[count][4],NULL);

				}
			}
			else if (var[count]==1)
			{
				rc=fork();
				if(rc==0)
				{
					execlp("magick","convert","-rotate","-90",command[count][1],command[count][2],NULL);

				}
				rc=fork();
				if(rc==0)
				{
					execlp("magick","convert","-rotate","-90",command[count][0],command[count][3],NULL);
				}
				pid = rc;
				waitpid(pid, &status, 0);
				rc=fork();
				if(rc==0)
				{
					execlp("magick","convert","-resize","25%",command[count][3],command[count][4],NULL);

				}
			}
			else if (var[count]==2)
			{
				rc=fork();
				if(rc==0)
				{
					execlp("magick","convert","-rotate","90",command[count][1],command[count][2],NULL);

				}
				pid = rc;
				waitpid(pid, &status, 0);
				rc=fork();
				if(rc==0)
				{
					execlp("magick","convert","-rotate","90",command[count][0],command[count][3],NULL);

				}
				rc=fork();
				if(rc==0)
				{
					execlp("magick","convert","-resize","25%",command[count][3],command[count][4],NULL);

				}
			}
			else{}
				//printf("Wrong choice");

		}
		FILE *fp;
		fp = fopen("./main/Album.html", "w+");
		fprintf(fp,HEAD);
		for(count = 0; count < arg_count; count++){
			fprintf(fp,REP1);
			fprintf(fp,"%s", caption[count]);
			fprintf(fp,REP2);
			fprintf(fp,"%s", multi_arg[count]);
			fprintf(fp,REP3);
			fprintf(fp,"%s", multi_arg[count]);
			fprintf(fp,REP4);
		}
		fprintf(fp,TAIL);
		fclose(fp);
	}
	else {
		printf("The command had no other arguments.\n");
	}

	return EXIT_SUCCESS;
}

