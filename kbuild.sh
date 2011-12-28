#!/bin/bash

# MATT OS Boot Script - boot MattOS from CLI.
 
# CONFIG PARAMETERS
scratch_dir="build/scratch/"
harddisk_image="mattos.img"
bochs="bochs"
bochs_bochsrc='boot: floppy' 'floppya: 1_44="build/mattos.img", status=inserted'
kernel_binary="kernel.bin"
cat_args=${scratch_dir}"stage1 "${scratch_dir}"stage2 "${scratch_dir}"pad "${scratch_dir}${kernel_binary}

#make kernel:
make all;

# create pad and check that stage1+2 exist:
if [ ! -f "build/scratch/pad" ]; 
then
  echo "pad file doesn't exist!";
  dd if=/dev/zero of=pad bs=1 count=750;
  exit 1;
fi

if [ ! -f "build/scratch/stage1" ]; 
then
  echo "stage1 doesn't exist! Terminating!";
  exit 1;
fi

if [ ! -f "build/scratch/stage2" ]; 
then
  echo "stage2 doesn't exist! Terminating!";
  exit 1;
fi

#compile into floppy image from kernel:
cat $cat_args > $harddisk_image;
mv ${scratch_dir}${harddisk_image} "build/"${harddisk_image};

#boot into Bochs
${bochs} ${bochs_bochsrc}

echo