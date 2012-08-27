#!/bin/bash
# MATT OS Boot Script - boot MattOS from CLI.

# Grab the host platform:
UNAME=$(uname)

#Setup some vars depending on Host OS:
if [ ${UNAME} = "Darwin" ]; then
  #Setup for building on OS X: 
  export CC=/usr/bin/gcc-4.2
  export CXX=/usr/bin/g++-4.2
  export CPP=/usr/bin/cpp-4.2
  export LD=/usr/bin/gcc-4.2
fi

# CONFIG PARAMETERS
scratch_dir="build/scratch/"
harddisk_image="mattos.img"
kernel_binary="kernel.bin"
built_image="build/"${harddisk_image}
cat_args=${scratch_dir}"stage1 "${scratch_dir}"stage2 "${scratch_dir}"pad "${scratch_dir}${kernel_binary}

clear

#make sure padding and stage 1 + 2 exist:
checkRequiredFiles

make clean
make all

#compile into floppy image from kernel:
cat $cat_args > ${built_image}

if [ ! -f ${built_image} ];
then
  echo "[ERROR] Failed to build MattOS.IMG!"
  exit 2
fi

#Because i'm lazy, make bash do the kernel boot sector math :P
KSIZE=$(stat -c%s "$built_image")
BOOTSECTOR=$(expr ${KSIZE} / 512)
echo -e "Kernel Size: "${KSIZE}" bytes. Kernel Boot Sector: "${BOOTSECTOR}

echo -e 'Build Successful! Booting Matt OS:'

function checkRequiredFiles() {
  # create pad and check that stage1+2 exist:
  if [ ! -f ${scratch_dir}"pad" ];
  then
    echo "[WARNING] pad file doesn't exist! Building 750b pad:\n";
    dd if=/dev/zero of=pad bs=1 count=750;
    echo "pad built!\n";
  fi

  if [ ! -f ${scratch_dir}"stage1" ];
  then
    echo "[ERROR] stage1 doesn't exist! Terminating!\n";
    exit 1;
  fi

  if [ ! -f ${scratch_dir}"stage2" ];
  then
    echo "[ERROR] stage2 doesn't exist! Terminating!\n";
    exit 1;
  fi

  if [ ! -f ${scratch_dir}${kernel_binary} ];
  then
    echo "[ERROR] failed to build kernel.bin! Terminating!";
    exit 2;
  fi
}

function launch() {
  #Launch emulator, depending on OS:
  if [ ${UNAME} = "Darwin" ]; then
    emulator="/Applications/Q.app/Contents/MacOS/i386-softmmu.app/Contents/MacOS/i386-softmmu" #Q.App's i386 emulator
    ${emulator} ${built_image}

  elif [ ${UNAME} = "Linux" ]; then
    #boot bochs in a new tab, keep the clutter in it's own tab:
    gnome-terminal -e "bash -c \"exec "${bochs}"\""
  fi
}


