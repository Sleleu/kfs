CP = cp
RM = rm
MKDIR = mkdir -pv

NAME = kernel
CFG = grub.cfg
ISO_PATH = iso
BOOT_PATH = $(ISO_PATH)/boot
GRUB_PATH = $(BOOT_PATH)/grub

CC = cc
CFLAGS = -m32 -Wall -Wextra -Werror -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

OBJS = boot.o kernel.o

all: kfs.iso

# Compilation
boot.o: boot.asm
	nasm -f elf32 $< -o $@

kernel.o: kernel.c
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
	$(RM) -f *.o

fclean: clean
	$(RM) -rf $(NAME) *iso

re: fclean all

reload: re
	qemu-system-i386 -cdrom kernel.iso

.PHONY: clean fclean re all
