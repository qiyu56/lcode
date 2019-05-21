#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

#define MAXNUM 1024
#define MAXNO 32

void strtoargv(char *str, char **argv)
{
	argv[0] = strtok(str, " ");
	int i = 0;
	while (argv[i] != NULL)
	{
		++i;
		argv[i] = strtok(NULL, " ");
	}
}

int main()
{
	string prompt = "[qiyu@mini_shell xxx]# ";
	while(1)
	{
		cout << prompt;
		char command[MAXNUM];
		fgets(command, MAXNUM, stdin);
		command[strlen(command)-1] = 0; //delete '\n'
		//处理 >, >>, <
		string cmd = command;
		string symbol;
		int index;
		if((index = cmd.find('>')) != string::npos)
		{
			symbol += '>';
			if(cmd[index+1] == '>')
			{
				symbol += '>';
				++index;
			}
		}
		else if((index = cmd.find('<')) != string::npos)
		{
			symbol += '<';
		}
		char file[32];
		if(!symbol.empty())	
		{
			string str(cmd, 0, index); //> 之前
			++index; //跳过>
			while(cmd[index] == ' ') { ++index; } //跳过空格
			string temp(cmd, index); //重定向到
			if(symbol == "<")
			{
				swap(str, temp);
				if(temp[temp.size()-1] == ' ')
					temp.resize(temp.size()-1);
			}
			strcpy(command, str.c_str());
			strcpy(file, temp.c_str());
		}
		//对>>的处理有问题
		cout << command << "." << symbol << "."<< file << "." << endl;
		//char *argv[MAXNO];
		//strtoargv(command, argv);
		//pid_t pid = fork();
		//if(pid == 0)
		//{
		//	if(!symbol.empty())
		//	{
		//		int fd;
		//		if(symbol == ">" || symbol == "<")
		//			fd = open(file, O_WRONLY|O_CREAT, 00644);
		//		else if(symbol == ">>")
		//			fd = open(file, O_CREAT|O_WRONLY|O_APPEND, 00644);
		//		if(symbol == "<")
		//			dup2(3, 0);
		//		dup2(fd, 1);
		//	}
		//	execvp(argv[0], argv);
		//}
		//else
		//{
		//	int status;
		//	waitpid(pid, &status, 0);
		//}
	}
	//argv[i-1] = NULL;
	//for (i = 0; argv[i] != NULL; ++i)
	//{
	//	cout << i << ":" << argv[i] << endl;
	//}
	return 0;
}
