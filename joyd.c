/*
 *    joyd.c
 *
 *    this is the mail file of:
 *
 *    joyd 0.0.1   ---   The Joystick Daemon
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

/*
 * You can execute commands by using your joystick, joypad or whatever
 * is supported by the Linux Joystick Driver. This allows you to
 * reboot your computer when your keyboard is hung or you can even use
 * your system without any keyboard at all. 
 *
 * I use one of my computers (no screen, no keyboard) for listening to
 * mp3-files - with this program I can stop/start/skip songs, change
 * the volume, shutdown the computer and much more just by using an
 * joypad (in fact, it's an original SNES joypad).
 *
 * If you use this and find it useful, please let me know!
 * If you find a bug or have any suggestions or questions: tell me!
 *
 * My mail adress is:    <mitch@uni.de>
 * My homepage is here:  http://www.h.shuttle.de/mitch/
 *
 *
 *                                    Now enjoy this.
 *                                    Christian
 */

/*
 * This program is based on jstest.c Version 1.2 by Vojtech Pavlik,
 * which "is also intended to serve as an example implementation for
 * those who wish to learn how to write their own joystick using
 * applications."
 *
 * That's just what I did. That's GPL. Thanks!
 */


/*****************************************************************************
 *                                                                           *
 *     "Even the little things make me happy. It's that... that ordinary     *
 *      life I want back... I want back."                (Tsukino Usagi)     *
 *                                                                           *
 *****************************************************************************/


/*  joyd 0.0.1 2000-01-09
 *
 *  first version
 *  - added signal handlers
 *  - added syslog routines
 *  - added background mode
 */

/*
 *  2do:
 *  - write joyd(1)
 *  - write joydrc(5)
 *  - implement shift_axes like shift_keys?
 *  - split the ActionLoop() function into smaller parts, it's way too big
 */

/*****************************************************************************
 * now goes it loose...                                                      *
 *****************************************************************************/


/*
 * system include files
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * my headers and definitions
 */

#include "joyd.h"
#include "config.h"
#include "daemon.h"
#include "joystick.h"
#include "log.h"
#include "signal.h"
#include "string.h"

/*
 * now to the functions
 */



int main (int argc, char **argv)
/* simple main program */
{
	SetDefaultValues();

	if (config.debug > 1) {
		Print(stdout,JOYD_VERSION," starting up");
	}

	InstallSignalHandler();

	if (argc > 1) {
		free(config.config_file);
		config.config_file = AllocString(argv[1]);
	}
	
	ReadConfigFile();

	if (config.daemon) {
		ForkToBackground();
	}
	
	OpenJoystick();

	AddMissingCalibrations();

	ActionLoop();

	CloseJoystick();

	Print(stdout,JOYD_VERSION," quits now (should've never come around here!?)");

	return 0;
}