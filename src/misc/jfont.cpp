/*
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dosbox.h"
#include "control.h"
#include "jega.h"
#include "jfont.h"
#include "../ints/int10.h"

extern Bit8u jfont_sbcs_19[];
extern Bit8u jfont_dbcs_16[];
extern Bit8u jfont_sbcs_16[];
extern Bit8u jfont_dbcs_24[];
extern Bit8u jfont_sbcs_24[];

static Bit16u jtext_seg;
static Bitu jfont_dbcs_16_flag;
static Bitu jfont_dbcs_24_flag;
static HFONT jfont_16;
static HFONT jfont_24;
static std::string jfont_name;
static Bit8u jfont_dbcs[96];

static Bit8u dosv_font19_data[] = 
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x20,0x27,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfc,0x04,0xe4,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
	0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x27,0x20,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x24,0x24,0x24,0x24,0x24,0x24,0x24,0xe4,0x04,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x1c,0x1c,0x08,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x18,0x24,0x24,0x42,0x42,0x42,0x42,0x24,0x24,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xfe,0x82,0xc6,0xaa,0xaa,0x92,0x92,0xaa,0xaa,0xc6,0x82,0xfe,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0x00,0x00,
	0x00,0x00,0x00,0x49,0x49,0x2a,0x36,0x14,0x22,0xe3,0x22,0x14,0x36,0x2a,0x49,0x49,0x00,0x00,0x00,
	0x24,0x24,0x24,0x24,0x24,0x24,0x24,0xe7,0x00,0xe7,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x08,0x1c,0x1c,0x3e,0x08,0x08,0x08,0x08,0x08,0x3e,0x1c,0x1c,0x08,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	0x24,0x24,0x24,0x24,0x24,0x24,0x24,0xe7,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0xe7,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
	0x24,0x24,0x24,0x24,0x24,0x24,0x24,0xe4,0x04,0xe4,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x27,0x20,0x27,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
	0xaa,0x00,0x55,0x00,0xaa,0x00,0x55,0x00,0xaa,0x00,0x55,0x00,0xaa,0x00,0x55,0x00,0xaa,0x00,0x55,
	0x00,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x22,0x62,0xfe,0x60,0x20,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x08,0x1c,0x1c,0x3e,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
	0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x06,0x7f,0x06,0x04,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x60,0xfe,0x60,0x20,0x00,0x00,0x00,0x00,0x00,0x00,
};

static Bit8u dosv_font16_data[] = 
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x20,0x27,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
	0x00,0x00,0x00,0x00,0x00,0x00,0xfc,0x04,0xe4,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
	0x24,0x24,0x24,0x24,0x24,0x24,0x27,0x20,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x24,0x24,0x24,0x24,0x24,0x24,0xe4,0x04,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
	0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x1c,0x1c,0x08,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x18,0x24,0x24,0x42,0x42,0x42,0x42,0x24,0x24,0x18,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xfe,0x82,0xc6,0xaa,0xaa,0x92,0x92,0xaa,0xaa,0xc6,0x82,0xfe,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,
	0x00,0x00,0x49,0x49,0x2a,0x36,0x14,0x22,0xe3,0x22,0x14,0x36,0x2a,0x49,0x49,0x00,
	0x24,0x24,0x24,0x24,0x24,0x24,0xe7,0x00,0xe7,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x08,0x1c,0x1c,0x3e,0x08,0x08,0x08,0x08,0x08,0x3e,0x1c,0x1c,0x08,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	0x24,0x24,0x24,0x24,0x24,0x24,0xe7,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0xe7,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
	0x24,0x24,0x24,0x24,0x24,0x24,0xe4,0x04,0xe4,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x24,0x24,0x24,0x24,0x24,0x24,0x27,0x20,0x27,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
	0x00,0x55,0x00,0xaa,0x00,0x55,0x00,0xaa,0x00,0x55,0x00,0xaa,0x00,0x55,0x00,0xaa,
	0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x22,0x62,0xfe,0x60,0x20,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x08,0x1c,0x1c,0x3e,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
	0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x06,0x7f,0x06,0x04,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x60,0xfe,0x60,0x20,0x00,0x00,0x00,0x00
};

static Bit8u frame_font_data[] = 
{
//0x849f ��
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x84a0 ��
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
//0x84a1 ��
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xff,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
//0x84a2 ��
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
//0x84a3 ��
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x84a4 ��
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x84a5 ��
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0xff,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
//0x84a6 ��
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
//0x84a7 ��
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xff,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
//0x84a8 ��
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x84a9 ��
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xff,0xff,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
//0x84aa ��
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x84ab ��
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
//0x84ac ��
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xff,0x01,0xff,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
//0x84ad ��
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x80,0xff,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
//0x84ae ��
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0xff,0x80,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x84af ��
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0xff,0x01,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x84b0 ��
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0xff,0x01,0xff,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
//0x84b1 ��
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
//0x84b2 ��
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0xff,0x80,0xff,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
//0x84b3 ��
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x84b4 ��
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0xff,0xff,0xff,0xff,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
//0x84b5 ��
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0xff,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
//0x84b6 ��
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
//0x84b7 ��
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0xff,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
//0x84b8 ��
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x84b9 ��
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xff,0xff,0xff,0xff,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
//0x84ba ��
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0xff,0x01,0xff,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
//0x84bb ��
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
//0x84bc ��
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xff,0x00,0xff,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
//0x84bd ��
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x84be ��
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0xff,0xff,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80
};

void InitFontHandle()
{
	if(jfont_name.empty()) {
		jfont_name = "�l�r �S�V�b�N";
	}
	if(jfont_16 == NULL || jfont_24 == NULL) {
		LOGFONT lf = { 0 };
		lf.lfHeight = 16;
		lf.lfCharSet = SHIFTJIS_CHARSET;
		lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
		lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		lf.lfQuality = DEFAULT_QUALITY;
		lf.lfPitchAndFamily = FIXED_PITCH;
		strcpy(lf.lfFaceName, jfont_name.c_str());
		jfont_16 = CreateFontIndirect(&lf);
		lf.lfHeight = 24;
		jfont_24 = CreateFontIndirect(&lf);
	}
}

bool GetWindowsFont(Bitu code, Bit8u *buff, int width, int height)
{
	HFONT font = (height == 16) ? jfont_16 : jfont_24;
	if(font != NULL) {
		HDC hdc = GetDC(NULL);
		HFONT old_font = (HFONT)SelectObject(hdc, font);

		TEXTMETRIC tm;
		GetTextMetrics(hdc, &tm);
		GLYPHMETRICS gm;
		CONST MAT2 mat = { {0,1},{0,0},{0,0},{0,1} };
		DWORD size = GetGlyphOutline(hdc, code, GGO_BITMAP, &gm, 0, NULL, &mat);
		if(size > 0) {
			char *fontbuff = new char[size];
			memset(fontbuff, 0, size);
			GetGlyphOutline(hdc, code, GGO_BITMAP, &gm, size, fontbuff, &mat);

			Bitu off_y = tm.tmAscent - gm.gmptGlyphOrigin.y;
			Bitu pos = off_y;
			Bitu count = (1 + (gm.gmBlackBoxX / 32)) * 4;
			if(width >= 16 || (width == 12 && height == 24)) {
				pos += off_y;
				if(width == 24) {
					pos += off_y;
				}
			}
			for(Bitu y = off_y ; y < off_y + gm.gmBlackBoxY; y++) {
				Bit32u data = 0;
				Bit32u bit = 0x800000 >> ((width - gm.gmBlackBoxX) / 2);
				for (Bitu x = gm.gmptGlyphOrigin.x; x < gm.gmptGlyphOrigin.x + gm.gmBlackBoxX; x++) {
					Bit8u src = *((Bit8u *)fontbuff + count * (y - off_y) + ((x - gm.gmptGlyphOrigin.x) / 8));
					if(src & (1 << (7 - ((x - gm.gmptGlyphOrigin.x) % 8)))) {
						data |= bit;
					}
					bit >>= 1;
				}
				buff[pos++] = (data >> 16) & 0xff;
				if(width >= 16 || (width == 12 && height == 24)) {
					buff[pos++] = (data >> 8) & 0xff;
					if(width == 24) {
						buff[pos++] = data & 0xff;
					}
				}
			}
			delete [] fontbuff;
		}
		SelectObject(hdc, old_font);
		ReleaseDC(NULL, hdc);

		return true;
	}
	return false;
}


Bit16u GetTextSeg()
{
	return jtext_seg;
}

void SetTextSeg()
{
	if(jtext_seg == 0) {
		jtext_seg = DOS_GetMemory(VIRTUAL_TEXT_SIZE);
	}
}

bool MakeSbcs19Font()
{
	InitFontHandle();
	for(Bitu code = 0 ; code < 256 ; code++) {
		if(!GetWindowsFont(code, &jfont_sbcs_19[code * 19 + 1], 8, 16)) {
			return false;
		}
	}
	if(IS_J3_ARCH || IS_DOSV) {
		memcpy(jfont_sbcs_19, dosv_font19_data, sizeof(dosv_font19_data));
	}
	return true;
}

bool MakeSbcs16Font()
{
	InitFontHandle();
	for(Bitu code = 0 ; code < 256 ; code++) {
		if(!GetWindowsFont(code, &jfont_sbcs_16[code * 16], 8, 16)) {
			return false;
		}
	}
	if(IS_J3_ARCH || IS_DOSV) {
		memcpy(jfont_sbcs_16, dosv_font16_data, sizeof(dosv_font16_data));
	}
	return true;
}

bool MakeSbcs24Font()
{
	InitFontHandle();
	for(Bitu code = 0 ; code < 256 ; code++) {
		if(!GetWindowsFont(code, &jfont_sbcs_24[code * 24 * 2], 12, 24)) {
			return false;
		}
	}
	return true;
}

bool MakeDbcsFont()
{
	if(IS_AX_ARCH) {
		static struct CODE_LIST {
			Bitu start, end;
		} code_list[] = {
			{ 0x8140, 0x8fff },
			{ 0x9040, 0x9fff },
			{ 0xe040, 0xefff },
			{ 0, 0 }
		};
		InitFontHandle();
		Bitu count, code;
		for(count = 0 ; code_list[count].start != 0 ; count++) {
			for(code = code_list[count].start ; code < code_list[count].end ; code++) {
				if(code >= 0x849f && code <= 0x84be) {
					GetDbcsFrameFont(code, &jfont_dbcs_16[code * 32]);
				} else if(!GetWindowsFont(code, &jfont_dbcs_16[code * 32], 16, 16)) {
					return false;
				}
			}
		}
	}
	return true;
}

Bit8u GetKanjiAttr(Bitu x, Bitu y)
{
	Bitu cx, pos;
	Bit8u flag;
	Bit16u seg = (IS_AX_ARCH) ? 0xb800 : jtext_seg;
	pos = y * real_readw(BIOSMEM_SEG, BIOSMEM_NB_COLS) * 2;
	cx = 0;
	flag = 0x00;
	do {
		if(flag == 0x01) {
			flag = 0x02;
		} else {
			flag = 0x00;
			if(isKanji1(real_readb(seg, pos))) {
				flag = 0x01;
			}
		}
		pos += 2;
		cx++;
	} while(cx <= x);
	return flag;
}

Bit8u GetKanjiAttr()
{
	return GetKanjiAttr(real_readb(BIOSMEM_SEG, BIOSMEM_CURSOR_POS), real_readb(BIOSMEM_SEG, BIOSMEM_CURSOR_POS + 1));
}

Bit8u *GetSbcsFont(Bitu code)
{
	return &jfont_sbcs_16[code * 16];
}

Bit8u *GetSbcs19Font(Bitu code)
{
	return &jfont_sbcs_19[code * 19];
}

Bit8u *GetSbcs24Font(Bitu code)
{
	return &jfont_sbcs_24[code * 2 * 24];
}

void EnableDbcs16Font()
{
	jfont_dbcs_16_flag = 1;
}

void EnableDbcs24Font()
{
	jfont_dbcs_24_flag = 1;
}

void SetFontName(const char *name)
{
	jfont_name = name;
}

void GetDbcsFrameFont(Bitu code, Bit8u *buff)
{
	if(code >= 0x849f && code <= 0x84be) {
		memcpy(buff, &frame_font_data[(code - 0x849f) * 32], 32);
	}
}

Bit8u *GetDbcsFont(Bitu code)
{
	memset(jfont_dbcs, 0, sizeof(jfont_dbcs));
	if(!jfont_dbcs_16_flag) {
		if(code >= 0x849f && code <= 0x84be) {
			GetDbcsFrameFont(code, jfont_dbcs);
			return jfont_dbcs;
		} else if(GetWindowsFont(code, jfont_dbcs, 16, 16)) {
			return jfont_dbcs;
		}
	}
	return &jfont_dbcs_16[code * 32];
}

Bit8u *GetDbcs24Font(Bitu code)
{
	memset(jfont_dbcs, 0, sizeof(jfont_dbcs));
	if(code >= 0x809e && code < 0x80fe) {
		if (GetWindowsFont(code - 0x807e, jfont_dbcs, 12, 24)) {
			return jfont_dbcs;
		}
	} else if(code >= 0x8540 && code < 0x857e) {
		if (GetWindowsFont(code - 0x8540 + 0xa1, jfont_dbcs, 12, 24)) {
			return jfont_dbcs;
		}
	} else if(!jfont_dbcs_24_flag) {
		if (GetWindowsFont(code, jfont_dbcs, 24, 24)) {
			return jfont_dbcs;
		}
	} else {
		return &jfont_dbcs_24[code * 72];
	}
	return jfont_dbcs;
}

bool CheckStayVz()
{
	if(mem_readw(0x0086) != 0xf000) {
		Bitu addr = mem_readw(0x0086) << 4;
		char text[4];
		MEM_BlockRead(addr - 8, text, 2);
		text[2] = '\0';
		if(!strcasecmp(text, "VZ")) {
			return true;
		}
	}
	return false;
}

bool CheckAnotherDisplayDriver()
{
	if(mem_readw(0x0042) != 0xf000) {
		Bitu addr = mem_readw(0x0042) << 4;
		char text[10];

		MEM_BlockRead(addr + 10, text, 8);
		text[8] = '\0';
		if(!strcmp(text, "$IBMADSP")) {
			return true;
		}
		MEM_BlockRead(addr - 8, text, 4);
		text[4] = '\0';
		if(!strcmp(text, "DSP4")) {
			if(mem_readb(0x0449) == 0x70) {
				return true;
			}
		}
	}
	return false;
}

#ifndef NDEBUG
#include <stdarg.h>
void JTrace(const char *form , ...)
{
	va_list	ap;
	static char work[1000];

	va_start(ap, form);
	vsprintf(work, form, ap);
	va_end(ap);
#if defined(WIN32)
	OutputDebugString(work);
#endif
}
#endif


extern "C" FILE * __cdecl __iob_func(void)
{
	return NULL;
}
