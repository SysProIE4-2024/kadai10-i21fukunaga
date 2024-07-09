/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース

char *execpath = "/bin/sh";
// system関数のクローン
int mysystem(char *command) {
  int status = 0;
  // ここにプログラムを書く

  if (command == NULL){  //NULL
    return 1;
  }
  int pid = 0;

  if ((pid = fork()) < 0){  //fork失敗
    return -1;  
  }

  if (pid != 0){  //親プロセス
    while (wait(&status) != pid);
  } else {  //子プロセス
    execl(execpath, "sh", "-c", command, NULL);
    perror(execpath);
    exit(127);
  }

  return status;
}

/* 実行例
mei@Mei-no-MacBook-Air kadai10-i21fukunaga % make
cc -Wall -std=c99 -o mysysmain mysysmain.c  mysystem.c

mei@Mei-no-MacBook-Air kadai10-i21fukunaga % ls -l
total 616
-rw-r--r--  1 mei  staff     143  7  4 09:46 Makefile
-rw-r--r--  1 mei  staff    2795  7  4 09:46 README.md
-rw-r--r--  1 mei  staff  238232  7  4 09:46 README.pdf
-rwxr-xr-x  1 mei  staff   50392  7  9 16:20 mysysmain
-rw-r--r--  1 mei  staff     925  7  4 09:46 mysysmain.c
-rw-r--r--  1 mei  staff    2458  7  9 16:30 mysystem.c
-rw-r--r--  1 mei  staff      90  7  4 09:46 mysystem.h

mei@Mei-no-MacBook-Air kadai10-i21fukunaga % ./mysysmain "ls -l"
mysystem:
total 616
-rw-r--r--  1 mei  staff     143  7  4 09:46 Makefile
-rw-r--r--  1 mei  staff    2795  7  4 09:46 README.md
-rw-r--r--  1 mei  staff  238232  7  4 09:46 README.pdf
-rwxr-xr-x  1 mei  staff   50392  7  9 16:20 mysysmain
-rw-r--r--  1 mei  staff     925  7  4 09:46 mysysmain.c
-rw-r--r--  1 mei  staff     738  7  9 16:20 mysystem.c
-rw-r--r--  1 mei  staff      90  7  4 09:46 mysystem.h
retval = 00000000
system:
total 616
-rw-r--r--  1 mei  staff     143  7  4 09:46 Makefile
-rw-r--r--  1 mei  staff    2795  7  4 09:46 README.md
-rw-r--r--  1 mei  staff  238232  7  4 09:46 README.pdf
-rwxr-xr-x  1 mei  staff   50392  7  9 16:20 mysysmain
-rw-r--r--  1 mei  staff     925  7  4 09:46 mysysmain.c
-rw-r--r--  1 mei  staff     738  7  9 16:20 mysystem.c
-rw-r--r--  1 mei  staff      90  7  4 09:46 mysystem.h
retval = 00000000

mei@Mei-no-MacBook-Air kadai10-i21fukunaga % ./mysysmain
使い方 : ./mysysmain コマンド文字列

mei@Mei-no-MacBook-Air kadai10-i21fukunaga % ./mysysmain "aaa"
mysystem:
sh: aaa: command not found
retval = 00007f00
system:
sh: aaa: command not found
retval = 00007f00

mei@Mei-no-MacBook-Air kadai10-i21fukunaga % ./mysysmain "echo aaa"
mysystem:
aaa
retval = 00000000
system:
aaa
retval = 00000000

mei@Mei-no-MacBook-Air kadai10-i21fukunaga % ./mysysmain "rmdir aaa"
mysystem:
rmdir: aaa: No such file or directory
retval = 00000100
system:
rmdir: aaa: No such file or directory
retval = 00000100
*/
