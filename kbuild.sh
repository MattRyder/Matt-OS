#!/bin/bash

# MATT OS Boot Script - boot MattOS from CLI.

# CONFIG PARAMETERS
scratch_dir="build/scratch/"
harddisk_image="mattos.img"
bochs="bochs"
kernel_binary="kernel.bin"
built_image="build/"${harddisk_image}
cat_args=${scratch_dir}"stage1 "${scratch_dir}"stage2 "${scratch_dir}"pad "${scratch_dir}${kernel_binary}

clear

#make kernel:
make clean;
make all;

# create pad and check that stage1+2 exist:
if [ ! -f "build/scratch/pad" ];
then
  echo "[WARNING] pad file doesn't exist! Building 750b pad:\n";
  dd if=/dev/zero of=pad bs=1 count=750;
  echo "pad built!";
fi

if [ ! -f "build/scratch/stage1" ];
then
  echo "[ERROR] stage1 doesn't exist! Terminating!";
  exit 1;
fi

if [ ! -f "build/scratch/stage2" ];
then
  echo "[ERROR] stage2 doesn't exist! Terminating!";
  exit 1;
fi

#compile into floppy image from kernel:
cat $cat_args > ${built_image};

if [ ! -f ${built_image} ];
then
  echo "[ERROR] Failed to build MattOS.IMG!";
  exit 2;
fi

#Because i'm lazy, make bash do the kernel boot sector math :P
KSIZE=$(stat -c%s "$built_image");
echo "Kernel Size: "${KSIZE}" bytes.";
BOOTSECTOR=$(expr ${KSIZE} / 512);
echo "Kernel Boot Sector: "${BOOTSECTOR};

echo "Build Successful! Booting bochs:"
#boot bochs in a new tab, keep the clutter in it's own tab:
gnome-terminal -e "bash -c \"echo foo; echo bar; exec "${bochs}"\""
