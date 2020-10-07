CC		=	cl
CXX		=   cl
LD		= 	link
LIBR	=	lib
WINDRES =	rc

DBX_PATH	= ..

CXXFLAGS =  -nologo -O2 -MT -EHsc -DNDEBUG -DWIN32 -D_FILE_OFFSET_BITS=64 -DC_OPENGL=1 -DC_DYNREC=1 -DC_MT32=1 -I. \
			-D_WIN32_WINNT=0x0501 \
			-Dmain=SDL_main -Isdl\include \
			-Ilibpng -Izlib \
			-I$(DBX_PATH) \
			-I$(DBX_PATH)/include \
			-I$(DBX_PATH)/src \
			-I$(DBX_PATH)/src/mt32 \
			-I$(DBX_PATH)/src/sha1

CFLAGS	=	-nologo -O2 -MT -DNDEBUG -DWIN32 -D_WIN32_WINNT=0x0501 -I. \
			-Dmain=SDL_main -Isdl\include \
			-Ilibpng \
			-I$(DBX_PATH) \
			-I$(DBX_PATH)/include \
			-I$(DBX_PATH)/src \
			-I$(DBX_PATH)/src/mt32 \
			-I$(DBX_PATH)/src/sha1

LFLAGS	=	-nologo -SUBSYSTEM:Windows,"5.01"

TARGET	=	dosbox.exe

OBJS	=	$(DBX_PATH)\src\dosbox.obj \
			$(DBX_PATH)\src\cpu\callback.obj \
			$(DBX_PATH)\src\cpu\core_dynrec.obj \
			$(DBX_PATH)\src\cpu\core_dyn_x86.obj \
			$(DBX_PATH)\src\cpu\core_full.obj \
			$(DBX_PATH)\src\cpu\core_normal.obj \
			$(DBX_PATH)\src\cpu\core_prefetch.obj \
			$(DBX_PATH)\src\cpu\core_simple.obj \
			$(DBX_PATH)\src\cpu\cpu.obj \
			$(DBX_PATH)\src\cpu\flags.obj \
			$(DBX_PATH)\src\cpu\modrm.obj \
			$(DBX_PATH)\src\cpu\paging.obj \
			$(DBX_PATH)\src\debug\debug.obj \
			$(DBX_PATH)\src\debug\debug_disasm.obj \
			$(DBX_PATH)\src\debug\debug_gui.obj \
			$(DBX_PATH)\src\debug\debug_win32.obj \
			$(DBX_PATH)\src\dos\cdrom.obj \
			$(DBX_PATH)\src\dos\cdrom_aspi_win32.obj \
			$(DBX_PATH)\src\dos\cdrom_image.obj \
			$(DBX_PATH)\src\dos\cdrom_ioctl_linux.obj \
			$(DBX_PATH)\src\dos\cdrom_ioctl_os2.obj \
			$(DBX_PATH)\src\dos\cdrom_ioctl_win32.obj \
			$(DBX_PATH)\src\dos\dos.obj \
			$(DBX_PATH)\src\dos\dos_classes.obj \
			$(DBX_PATH)\src\dos\dos_devices.obj \
			$(DBX_PATH)\src\dos\dos_execute.obj \
			$(DBX_PATH)\src\dos\dos_files.obj \
			$(DBX_PATH)\src\dos\dos_ioctl.obj \
			$(DBX_PATH)\src\dos\dos_keyboard_layout.obj \
			$(DBX_PATH)\src\dos\dos_memory.obj \
			$(DBX_PATH)\src\dos\dos_misc.obj \
			$(DBX_PATH)\src\dos\dos_mscdex.obj \
			$(DBX_PATH)\src\dos\dos_programs.obj \
			$(DBX_PATH)\src\dos\dos_tables.obj \
			$(DBX_PATH)\src\dos\drives.obj \
			$(DBX_PATH)\src\dos\drive_cache.obj \
			$(DBX_PATH)\src\dos\drive_fat.obj \
			$(DBX_PATH)\src\dos\drive_iso.obj \
			$(DBX_PATH)\src\dos\drive_local.obj \
			$(DBX_PATH)\src\dos\drive_virtual.obj \
			$(DBX_PATH)\src\fpu\fpu.obj \
			$(DBX_PATH)\src\gui\midi.obj \
			$(DBX_PATH)\src\gui\render.obj \
			$(DBX_PATH)\src\gui\render_scalers.obj \
			$(DBX_PATH)\src\gui\sdlmain.obj \
			$(DBX_PATH)\src\gui\sdl_gui.obj \
			$(DBX_PATH)\src\gui\sdl_mapper.obj
			
OBJS2	= 	$(DBX_PATH)\src\hardware\adlib.obj \
			$(DBX_PATH)\src\hardware\cmos.obj \
			$(DBX_PATH)\src\hardware\dbopl.obj \
			$(DBX_PATH)\src\hardware\disney.obj \
			$(DBX_PATH)\src\hardware\dma.obj \
			$(DBX_PATH)\src\hardware\gameblaster.obj \
			$(DBX_PATH)\src\hardware\gus.obj \
			$(DBX_PATH)\src\hardware\hardware.obj \
			$(DBX_PATH)\src\hardware\iohandler.obj \
			$(DBX_PATH)\src\hardware\ipx.obj \
			$(DBX_PATH)\src\hardware\ipxserver.obj \
			$(DBX_PATH)\src\hardware\joystick.obj \
			$(DBX_PATH)\src\hardware\keyboard.obj \
			$(DBX_PATH)\src\hardware\memory.obj \
			$(DBX_PATH)\src\hardware\mixer.obj \
			$(DBX_PATH)\src\hardware\mpu401.obj \
			$(DBX_PATH)\src\hardware\opl.obj \
			$(DBX_PATH)\src\hardware\pci_bus.obj \
			$(DBX_PATH)\src\hardware\pcspeaker.obj \
			$(DBX_PATH)\src\hardware\pic.obj \
			$(DBX_PATH)\src\hardware\sblaster.obj \
			$(DBX_PATH)\src\hardware\tandy_sound.obj \
			$(DBX_PATH)\src\hardware\timer.obj \
			$(DBX_PATH)\src\hardware\vga.obj \
			$(DBX_PATH)\src\hardware\vga_attr.obj \
			$(DBX_PATH)\src\hardware\vga_crtc.obj \
			$(DBX_PATH)\src\hardware\vga_dac.obj \
			$(DBX_PATH)\src\hardware\vga_draw.obj \
			$(DBX_PATH)\src\hardware\vga_gfx.obj \
			$(DBX_PATH)\src\hardware\vga_jega.obj \
			$(DBX_PATH)\src\hardware\vga_memory.obj \
			$(DBX_PATH)\src\hardware\vga_misc.obj \
			$(DBX_PATH)\src\hardware\vga_other.obj \
			$(DBX_PATH)\src\hardware\vga_paradise.obj \
			$(DBX_PATH)\src\hardware\vga_s3.obj \
			$(DBX_PATH)\src\hardware\vga_seq.obj \
			$(DBX_PATH)\src\hardware\vga_tseng.obj \
			$(DBX_PATH)\src\hardware\vga_xga.obj \
			$(DBX_PATH)\src\hardware\serialport\directserial.obj \
			$(DBX_PATH)\src\hardware\serialport\libserial.obj \
			$(DBX_PATH)\src\hardware\serialport\misc_util.obj \
			$(DBX_PATH)\src\hardware\serialport\nullmodem.obj \
			$(DBX_PATH)\src\hardware\serialport\serialdummy.obj \
			$(DBX_PATH)\src\hardware\serialport\serialport.obj \
			$(DBX_PATH)\src\hardware\serialport\softmodem.obj 
			
OBJS3	=	$(DBX_PATH)\src\ints\bios.obj \
			$(DBX_PATH)\src\ints\bios_disk.obj \
			$(DBX_PATH)\src\ints\bios_keyboard.obj \
			$(DBX_PATH)\src\ints\ems.obj \
			$(DBX_PATH)\src\ints\int_dosv.obj \
			$(DBX_PATH)\src\ints\int_j3.obj \
			$(DBX_PATH)\src\ints\int10.obj \
			$(DBX_PATH)\src\ints\int10_ax.obj \
			$(DBX_PATH)\src\ints\int10_char.obj \
			$(DBX_PATH)\src\ints\int10_memory.obj \
			$(DBX_PATH)\src\ints\int10_misc.obj \
			$(DBX_PATH)\src\ints\int10_modes.obj \
			$(DBX_PATH)\src\ints\int10_pal.obj \
			$(DBX_PATH)\src\ints\int10_put_pixel.obj \
			$(DBX_PATH)\src\ints\int10_vesa.obj \
			$(DBX_PATH)\src\ints\int10_video_state.obj \
			$(DBX_PATH)\src\ints\int10_vptable.obj \
			$(DBX_PATH)\src\ints\mouse.obj \
			$(DBX_PATH)\src\ints\xms.obj \
			$(DBX_PATH)\src\libs\gui_tk\gui_tk.obj \
			$(DBX_PATH)\src\misc\cross.obj \
			$(DBX_PATH)\src\misc\jfont.obj \
			$(DBX_PATH)\src\misc\jfontload.obj \
			$(DBX_PATH)\src\misc\messages.obj \
			$(DBX_PATH)\src\misc\programs.obj \
			$(DBX_PATH)\src\misc\setup.obj \
			$(DBX_PATH)\src\misc\support.obj \
			$(DBX_PATH)\src\shell\shell.obj \
			$(DBX_PATH)\src\shell\shell_batch.obj \
			$(DBX_PATH)\src\shell\shell_cmds.obj \
			$(DBX_PATH)\src\shell\shell_misc.obj \
			$(DBX_PATH)\src\mt32\Analog.obj \
			$(DBX_PATH)\src\mt32\AReverbModel.obj \
			$(DBX_PATH)\src\mt32\BReverbModel.obj \
			$(DBX_PATH)\src\mt32\File.obj \
			$(DBX_PATH)\src\mt32\FileStream.obj \
			$(DBX_PATH)\src\mt32\LA32FloatWaveGenerator.obj \
			$(DBX_PATH)\src\mt32\LA32Ramp.obj \
			$(DBX_PATH)\src\mt32\LA32WaveGenerator.obj \
			$(DBX_PATH)\src\mt32\LegacyWaveGenerator.obj \
			$(DBX_PATH)\src\mt32\Part.obj \
			$(DBX_PATH)\src\mt32\Partial.obj \
			$(DBX_PATH)\src\mt32\PartialManager.obj \
			$(DBX_PATH)\src\mt32\Poly.obj \
			$(DBX_PATH)\src\mt32\ROMInfo.obj \
			$(DBX_PATH)\src\mt32\Synth.obj \
			$(DBX_PATH)\src\mt32\Tables.obj \
			$(DBX_PATH)\src\mt32\TVA.obj \
			$(DBX_PATH)\src\mt32\TVF.obj \
			$(DBX_PATH)\src\mt32\TVP.obj \
			$(DBX_PATH)\src\mt32\sha1\sha1.obj \
			$(DBX_PATH)\src\winres.res
			
LIBS = kernel32.lib user32.lib gdi32.lib imm32.lib winmm.lib dxguid.lib shell32.lib opengl32.lib advapi32.lib ws2_32.lib sdl\sdl.lib sdl\sdlmain.lib zlib\z.lib libpng\png.lib

!IFDEF SSE2
CFLAGS = -arch:SSE2 $(CFLAGS)
CXXFLAGS = -arch:SSE2 $(CXXFLAGS)
!ELSE
CFLAGS = -arch:IA32 $(CFLAGS)
CXXFLAGS = -arch:IA32 $(CXXFLAGS)
!ENDIF

!IFDEF LTCG
CXXFLAGS = $(CXXFLAGS) -GL
CFLAGS = $(CFLAGS) -GL
LFLAGS = $(LFLAGS) -LTCG
!ENDIF

!IFDEF D3D9
CXXFLAGS = -DHAVE_D3D9_H=1 $(CXXFLAGS)
!ENDIF

.SUFFIXES: .c.o
.SUFFIXES: .cpp.o

all: $(TARGET) $(SDLMAIN)

$(TARGET):	$(OBJS) $(OBJS2) $(OBJS3)
	$(LD) $(LFLAGS) -OUT:$@ $(OBJS) $(OBJS2) $(OBJS3) $(LIBS)
	
.c.obj:
	$(CC) $(CFLAGS) -c -Fo$@ $<

.cpp.obj:
	$(CXX) $(CXXFLAGS) -c -Fo$@ $<

.rc.res: 
	$(WINDRES) -fo $@ $< 
	
clean:
	del $(TARGET) $(OBJS) 
	del $(OBJS2)
	del $(OBJS3)