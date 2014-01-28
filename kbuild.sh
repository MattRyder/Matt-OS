#!/bin/bash
# MATT OS Boot Script - boot MattOS from CLI.

##
# launch
# Used to boot whatever emulator we're using with special rules for OSX.
##
function launch() {
  #Launch emulator, depending on OS:

  if [ ${UNAME} = "Darwin" ]; then
    emulator="/Applications/Q.app/Contents/MacOS/i386-softmmu.app/Contents/MacOS/i386-softmmu" #Q.App's i386 emulator
    ${emulator} ${built_image}

  elif [ ${UNAME} = "Linux" ]; then
    #boot bochs in a new tab, keep the clutter in it's own tab:
    $SHELL -c "qemu-system-i386 -kernel ${scratch_dir}${kernel_binary}"
  fi
}

##
# checkPrerequisites
# Make sure all the files and programs require are onboard
##
function checkPrerequisites() {
  req_files=("stage1" "stage2" "kernel.bin")

  if [ ! -f ${scratch_dir}"pad" ];
  then
    echo "[WARNING] pad file doesn't exist! Building 750b pad:\n";
    dd if=/dev/zero of=pad bs=1 count=750;
    echo "pad built!\n";
  fi

  for req_file in "${req_files[@]}"; do
    if [ ! -f ${scratch_dir}${req_file} ]; then
      echo "[ERROR] Terminating because "${req_file}" doesn't exist!"
      exit 1
    fi
  done
}


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

build_dir="build/"
scratch_dir=${build_dir}"scratch/"
harddisk_image="mattos.img"
kernel_binary="kernel.bin"
built_image=${build_dir}${harddisk_image}
cat_args=${scratch_dir}"stage1 "${scratch_dir}"stage2 "${scratch_dir}"pad "${scratch_dir}${kernel_binary}

clear


make clean
make all

#make sure padding, stage1/2 and kernel.bin exist:
checkPrerequisites

#compile into floppy image from kernel:
cat $cat_args > ${built_image}

if [ ! -f ${built_image} ];
then
  echo "[ERROR] Failed to build MattOS.IMG!"
  exit 2
fi

# This isn't really needed, but it's nice to know
KSIZE=$(stat -c%s "$built_image")
BSECT=$(expr ${KSIZE} / 512) 
echo -e "Kernel Size: "${KSIZE}" bytes. Kernel Boot Sector: "${BSECT} 

echo -e 'Build Successful! Booting Matt OS:'
launch


