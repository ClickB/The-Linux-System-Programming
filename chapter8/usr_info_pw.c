/* 从密码文件获取记录 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>


void usage( void )
{
	printf("./a.out -u [uid] or\n ./a.out -n [name] \n");
}

int main( int argc, char *argv[] )
{
	//struct passwd pws = {0}; 不能再另外申请
	struct passwd *pwd = NULL;
	int tmp1 = -1; /* 初始值不要为零，会带来后面比较结果不必要的麻烦 */
	int tmp2 = -1;

	if( argc < 3 || 
	( (tmp1=strcmp( argv[1],"-u"))!=0 &&(tmp2=strcmp(argv[1],"-n")) != 0))
	{
		usage();
		return -1;
	}

	if(tmp2 == 0)
	{
		pwd = getpwnam( argv[2] );	
	}
	else if(tmp1 == 0)
	{
		pwd = getpwuid( atoi(argv[2]) );
	}
	else
	{
		return -1;
	}
	
	if(pwd!=NULL)
	{	
		printf("pw_\nname:%s\npasswd:%s\nuid:%d\ngid:%d\n",
			pwd->pw_name, pwd->pw_passwd, pwd->pw_uid, pwd->pw_gid);
	}
	return 0;
}
