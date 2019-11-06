/*
 *  Copyright (C) 2002-2017  The DOSBox Team
 *  Copyright (C) 2016 akm
 *  Copyright (C) 2019 takapyu
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#ifndef DOSBOX_DOSBOX_H
#define DOSBOX_DOSBOX_H

#include "config.h"

#define	BUILD_VERSION	"JP190820"
#ifndef VERSION
#define VERSION BUILD_VERSION
#endif

GCC_ATTRIBUTE(noreturn) void E_Exit(const char * message,...) GCC_ATTRIBUTE( __format__(__printf__, 1, 2));

void MSG_Add(const char*,const char*); //add messages to the internal languagefile
const char* MSG_Get(char const *);     //get messages from the internal languagefile

class Section;

typedef Bitu (LoopHandler)(void);

void DOSBOX_RunMachine();
#if defined(EMSCRIPTEN) && defined(EMTERPRETER_SYNC)
/* This is for cases where RunMachine is called from code not using
 * emterpreter. There, emscripten_sleep() is prohibited and emulation
 * will be aborted with a timeout error if this takes too long.
 */
extern int nosleep_lock;
static void inline DOSBOX_RunMachineNoSleep() {
	nosleep_lock++;
	DOSBOX_RunMachine();
	nosleep_lock--;
}
#else
static void inline DOSBOX_RunMachineNoSleep() {
	DOSBOX_RunMachine();
}
#endif

void DOSBOX_SetLoop(LoopHandler * handler);
void DOSBOX_SetNormalLoop();

void DOSBOX_Init(void);

class Config;
extern Config * control;

enum MachineType {
	MCH_HERC,
	MCH_CGA,
	MCH_TANDY,
	MCH_PCJR,
	MCH_EGA,
	MCH_DCGA,
	MCH_VGA
};

enum SVGACards {
	SVGA_None,
	SVGA_S3Trio,
	SVGA_TsengET4K,
	SVGA_TsengET3K,
	SVGA_ParadisePVGA1A
}; 

extern SVGACards svgaCard;
extern MachineType machine;
extern bool SDLNetInited, uselfn, autolfn;;

#define IS_TANDY_ARCH ((machine==MCH_TANDY) || (machine==MCH_PCJR))
#define IS_EGAVGA_ARCH ((machine==MCH_EGA) || (machine==MCH_VGA))
#define IS_VGA_ARCH ((machine==MCH_VGA))
#define TANDY_ARCH_CASE MCH_TANDY: case MCH_PCJR
#define EGAVGA_ARCH_CASE MCH_EGA: case MCH_VGA
#define VGA_ARCH_CASE MCH_VGA
#define IS_AX_ARCH (machine==MCH_EGA)// upper compatible with EGA
//#define IS_AX_ARCH (machine==MCH_AX)
#define IS_J3_ARCH (machine==MCH_DCGA)

#ifndef DOSBOX_LOGGING_H
#include "logging.h"
#endif // the logging system.

#if !defined (WIN32)
	typedef unsigned int DWORD;
	typedef   signed int HANDLE;
#define INVALID_HANDLE_VALUE -1
#endif

#endif /* DOSBOX_DOSBOX_H */
