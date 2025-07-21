CP = cp
RM = rm
MKDIR = mkdir -pv

NAME = kfs
CFG = grub.cfg
ISO_PATH = iso
BOOT_PATH = $(ISO_PATH)/boot
GRUB_PATH = $(BOOT_PATH)/grub
INC_PATH = ./kernel/include

CC = cc
CFLAGS =	-m32 -Wall -Wextra -Werror  \
			--freestanding -fno-builtin -fno-exceptions \
			-fno-stack-protector -nostdlib -nodefaultlibs \
			-I$(INC_PATH)

# sources .c
C_SOURCES =	kernel/kernel.c				\
			kernel/io/io.c 				\
			kernel/kfslib/strlen.c		\
			kernel/kfslib/printk.c		\
			kernel/kfslib/memset.c		\
			kernel/kfslib/strncmp.c		\
			kernel/kfslib/hexdump.c		\
			kernel/interrupt/idt.c		\
			kernel/timer/timer.c		\
			kernel/keyboard/keyboard.c	\
			kernel/shell/shell_main.c


# sources .asm
ASM_SOURCES =	boot.asm 						\
				kernel/io/outb.asm				\
				kernel/io/inb.asm				\
				kernel/gdt/gdt.asm				\
				kernel/interrupt/idt_init.asm


# objects
C_OBJS = $(C_SOURCES:.c=.o)
ASM_OBJS = $(ASM_SOURCES:.asm=.o)
OBJS = $(ASM_OBJS) $(C_OBJS)

all: kfs.iso

# compilation
%.o: %.asm
	nasm -f elf32 $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): linker.ld $(OBJS)
	ld -m elf_i386 -T $< -o $@ $(OBJS)

kfs.iso: $(NAME) $(CFG)
	$(MKDIR) $(GRUB_PATH)
	$(CP) $(NAME) $(BOOT_PATH)
	$(CP) $(CFG) $(GRUB_PATH)
	grub-file --is-x86-multiboot $(BOOT_PATH)/$(NAME)
	grub-mkrescue -o $(NAME).iso $(ISO_PATH)

clean:
	$(RM) -rf $(OBJS) iso/ kfs

fclean: clean
	$(RM) -rf $(NAME) *iso

re: fclean all

start:
	qemu-system-i386 -cdrom $(NAME).iso

restart: re start

.PHONY: clean fclean re all start restart
