/*
 * Raspberry Pi PIC Programmer using GPIO connector
 * https://github.com/WallaceIT/picberry
 * Copyright 2014 Francesco Valla
 * Copyright 2017 Akimasa Tateba
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * Author : Ulysse VAUTIER
 *
 */

#include <iostream>

#include "../common.h"
#include "device.h"

using namespace std;

#define SF_PIC16F1501_7		0x00
#define SF_PIC16F1508_9		0x01

class pic16f150x: public Pic{

	public:
		uint8_t detailed_subfamily;
		uint8_t	latch_size;
		pic16f150x(void){
			latch_size = 0;
		};
		void enter_program_mode(void);
		void exit_program_mode(void);
		bool setup_pe(void){return true;};
		bool read_device_id(void);
		void bulk_erase(void);
		void dump_configuration_registers(void);
		void read(char *outfile, uint32_t start, uint32_t count);
		void write(char *infile);
		uint8_t blank_check(void);

	protected:
		void send_cmd(uint8_t cmd, unsigned int delay);
		uint16_t read_data(void);
		void write_data(uint16_t data);
		void reset_mem_location(void);

		/*
		* DEVICES SECTION
		*                    	ID       NAME           MEMSIZE
		*/
		pic_device piclist[10] = {{0x166,  "PIC12F1501", 0x800},
								{0x16C,  "PIC12LF1501", 0x800},
								{0x167,  "PIC16F1503", 0x400},
								{0x16D,  "PIC16LF1503", 0x400},
								{0x168,  "PIC16F1507", 0x400},
								{0x16E,  "PIC16LF1507", 0x400},
								{0x169,  "PIC16F1508", 0x800},
								{0x16F,  "PIC16LF1508", 0x800},
								{0x16A,  "PIC16F1509", 0x800},
								{0x170,  "PIC16LF1509", 0x800}
								};
		detailed_subfamily_t detailed_subfamily_table[10] = {
			{0x166,  SF_PIC16F1501_7, 32},
								{0x16C, SF_PIC16F1501_7, 32},
								{0x167,  SF_PIC16F1501_7, 16},
								{0x16D,  SF_PIC16F1501_7, 16},
								{0x168,  SF_PIC16F1501_7, 16},
								{0x16E,  SF_PIC16F1501_7, 16},
								{0x169,  SF_PIC16F1508_9, 32},
								{0x16F,  SF_PIC16F1508_9, 32},
								{0x16A,  SF_PIC16F1508_9, 32},
								{0x170,  SF_PIC16F1508_9, 32}
								};
};
