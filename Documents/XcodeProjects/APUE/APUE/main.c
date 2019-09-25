//
//  main.c
//  APUE
//
//  Created by Johnson Johnson on 2016-07-25.
//  Copyright © 2016 Johnson Johnson. All rights reserved.
//

#include "/Users/JohnsonJohnson/Downloads/apue.3e/include/apue.h"
#include <dirent.h>


int  main(int argc, char *argv[])
{
    fpritf(stderr,"EACCES:%s\%n",strerror(EACCES));
    error = ENOENT;
    perror(argv[0]);
    exit(0);
}



