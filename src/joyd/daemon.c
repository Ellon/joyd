/*
 *    daemon.c - daemon functionality
 *
 *    this file is part of:
 *
 *    joyd 0.2.2   ---   The Joystick Daemon
 *
 *    2000 (C) by Christian Garbs <mitch@uni.de>
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*  joyd 0.0.1 2000-01-09
 *
 *  initial version
 */

/*  joyd 0.0.2 2000-01-10
 *  joyd 0.0.3 2000-01-17
 *  joyd 0.0.4 2000-02-09
 *  joyd 0.0.5 2000-03-19
 *  joyd 0.0.6 2000-04-06
 *  joyd 0.0.7 2000-04-13
 *  joyd 0.2.0 2000-04-22
 *  joyd 0.2.1 2000-05-25
 *  joyd 0.2.2 2000-10-11
 *
 *  (no changes)
 */

/*****************************************************************************
 * now goes it loose...                                                      *
 *****************************************************************************/


/*
 * system include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
 * my headers and definitions
 */

#include "joyd.h"
#include "daemon.h"
#include "log.h"

/*
 * now to the functions
 */


void ForkToBackground()
/* Fork into background (daemon) mode */
{
	pid_t pid;
	char buffer[48];

	if ((pid = fork()) < 0) {
		Print(stderr,"exit: error while changing to daemon mode",NOTHING);
		exit(3);
	}

	if (pid != 0) {
		if (config.debug > 1) {
			sprintf(buffer,"%i",pid);
			Print(stdout,"start routine exits now, daemon created: pid=",buffer);
		}
		exit(0);
	}

	if (config.debug > 1) {
		sprintf(buffer,"%i",getpid());
		Print(stdout,"daemon created and alive: pid=",buffer);
	}
}
