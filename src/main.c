/*!
 * \file 	main.c
 * \brief 	Application main function
 * \author 	O.D
 * \version 0.1
 * \date 	September 4th, 2018
 *
 * O.D - September 4th, 2018
 * File creation.
 *
 */
 
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "unistd.h"
#include "stdio.h"
#include "string.h"
#include "errno.h"
#include "sys/ioctl.h"
#include "../../../kernel/ioctl/inc/ioctl_cmd.h" /*cf kernel ioctl module*/

/*!
 * \fn 		main
 * \brief 	main function
 * \param 	int, char **
 * \return 	0
 * \author 	O.D
 */
int main (int arg, char **argv)
{
	int fd;
	mod_arg_t st;
	char *filename = "/dev/test_command"; /*cf kernel ioctl module*/
	
	/*Void cast for unused inputs in order to avoid compilation warnings*/
	(void)arg;
	(void)argv;

	/*Open file in read/write mode*/
	fd = open(filename, O_RDWR); 
	
	if (fd < 0) {
		printf("Impossible to open the file: %s (ret=%d)\n", strerror(errno), fd);
		goto end;
	}
	
	/*IOCTL read (get)*/
	if (ioctl(fd, MOD_GET_VAR, &st) == -1) {
		printf("Impossible to get from ioctl: %s (ret=%d)\n", strerror(errno), fd);
		goto end;
	}
	else {
		printf("status = %d\n", st.status);
		printf("action = %d\n", st.action);
	}
	
	/*IOCTL clear (reset)*/
	if (ioctl(fd, MOD_CLR_VAR) == -1) {
		printf("Impossible to clear from ioctl: %s (ret=%d)\n", strerror(errno), fd);
		goto end;
	}
	else {
		printf("device variables are cleared to 0\n");
	}
	
	/*IOCTL write (set)*/
	st.status = 29;
	st.action = 34;
	
	if (ioctl(fd, MOD_SET_VAR, &st) == -1) {
		printf("Impossible to set from ioctl: %s (ret=%d)\n", strerror(errno), fd);
		goto end;
	}
	else {
		printf("device variables are set to %d and %d\n", st.status, st.action);
	}
	
end:
	if (fd >= 0)	
		close(fd);

	return 0;
}
