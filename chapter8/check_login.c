/*
 通过终端输入的密码调内部加密函数加密，然后与从密码文件获取的加密数据作对比
记住：及时清空终端输入的密码信息
 */

#define _XOPEN_SOURCE 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <shadow.h>

static void usage( void )
{
	printf("gcc check_login.c -lcrypt\n");
	printf("sudo ./a.out\n");
}

static int get_pwd(const char* name, char* ret)
{
	struct passwd *pwd = NULL;
	struct spwd *sp_wd = NULL;

	if((pwd = getpwnam(name))==NULL)
	{
		return -1;
	}
	if( (sp_wd = getspnam(name))!=NULL )
	{
		strcpy( ret, sp_wd->sp_pwdp);
	}
	else
	{
		strcpy( ret, pwd->pw_passwd );
	}

	printf( "passwd:%s\n", ret );
		
	return 0;
}

static int crypt_to_pwd(char *pwd_in, char *pw_passwd, char *ret)
{
	char *str = NULL;
	char *p = pwd_in;
	str = crypt( pwd_in , pw_passwd );
	for( p=pwd_in; *p!='\0';)
	{
		*p++ = '\0';
	}
	//printf("pwd_in:%s\npw_passwd:%s\nstr:%s\n",\
			pwd_in, pw_passwd,str);
	strcpy( ret, str );
	return 0;
}

int main( int argc, char *argv[] )
{
	char tmp[256] = {0};
	char str_pwd[256] = {0};
	char str_cpt[256] = {0};
	char *p = NULL;
	
	usage();
	printf("user name:\n");
	memset( tmp, 0, sizeof(tmp) );
	fscanf( stdin, "%s", tmp );
	if( get_pwd(tmp, str_pwd)<0 )
	{
		printf("get_pwd failed\n");
		return -1;
	}
	//printf("password:\n");
	memset( tmp, 0, sizeof(tmp) );
	//fscanf( stdin, "%s", tmp );
	p = getpass("password:");
	crypt_to_pwd( p, str_pwd, str_cpt );
	
	//printf("pwd:%s\ncpt:%s\n", str_pwd, str_cpt);
	if( strcmp(str_pwd, str_cpt)==0 )
	{
		printf("Successfully authenticated.\n");
	}
	else
	{
		printf("Incorrect password\n");
	}
	return 0;
}
