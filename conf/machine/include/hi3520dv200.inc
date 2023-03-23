require conf/machine/include/hisilicon-soc.inc
SOC_FAMILY:append = ":hi3520dv200"

# TODO: Not sure what to set `DEFAULTTUNE` as. Double check this.
DEFAULTTUNE ?= "armv7athf-neon"
require conf/machine/include/arm/armv7a/tune-cortexa7.inc

# Increase this everytime you change something in the kernel
MACHINE_KERNEL_PR = "r1"

# Default providers, may need to override for specific machines
PREFERRED_PROVIDER_virtual/kernel ?= "linux-yocto"
PREFERRED_VERSION_linux-yocto ?= "3.0%"
#PREFERRED_PROVIDER_virtual/kernel ?= "linux-hisilicon-staging"
#PREFERRED_PROVIDER_virtual/bootloader ?= "u-boot-hisilicon-staging"
#PREFERRED_PROVIDER_u-boot ?= "u-boot-hisilicon-staging"

# Graphics providers and variables
# TODO: Double check these
PREFERRED_PROVIDER_virtual/gpudriver ?= ""
PVR_DISPLAY_CONTROLLER_ALIAS ?= "omapdrm"

KERNEL_IMAGETYPE = "uImage"

# TODO: Double check these
KERNEL_DEVICETREE = " \
    am437x-gp-evm.dtb \
    ${@oe.utils.conditional('PREFERRED_PROVIDER_virtual/kernel', 'linux-ti-mainline', '', 'am437x-gp-evm-hdmi.dtb', d)} \
    am437x-sk-evm.dtb am437x-idk-evm.dtb \
    am43x-epos-evm.dtb \
    ${@oe.utils.conditional('PREFERRED_PROVIDER_virtual/kernel', 'linux-ti-mainline', '', 'am43x-epos-evm-hdmi.dtb', d)} \
"

# TODO: Double check these
KERNEL_DEVICETREE += "${@oe.utils.conditional('ENABLE_TI_UIO_DEVICES', '1', 'am437x-idk-pru-excl-uio.dtb', '', d)}"

# TODO: Double check these
UBOOT_ARCH = "arm"
UBOOT_MACHINE = "am43xx_evm_config"

# TODO: Double check these
UBOOT_ENTRYPOINT = "0x80008000"
UBOOT_LOADADDRESS = "0x80008000"

# Generate an extlinux.conf file
# TODO: Double check these
UBOOT_EXTLINUX = "1"
UBOOT_EXTLINUX_ROOT = "root=PARTUUID=${uuid}"
UBOOT_EXTLINUX_BOOT_FILES = " \
    extlinux.conf;extlinux/extlinux.conf \
    ${KERNEL_IMAGETYPE} \
    ${KERNEL_DEVICETREE} \
"

# TODO: Double check these
UBOOT_SUFFIX = "img"

# Use the expected value of the ubifs filesystem's volume name in the kernel
# and u-boot.
# TODO: Double check these
UBI_VOLNAME = "rootfs"

# TODO: Double check these
EXTRA_IMAGEDEPENDS += "u-boot"

# List common SoC features
# TODO: Double check these
MACHINE_FEATURES = "kernel26 apm usbgadget usbhost vfat ext2 screen alsa ethernet gpu"

# TODO: Double check these
IMAGE_FSTYPES += "tar.xz wic.xz wic.bmap"
WKS_FILE ?= "sdimage-2part.wks"
IMAGE_BOOT_FILES ?= "u-boot.${UBOOT_SUFFIX} ${UBOOT_EXTLINUX_BOOT_FILES}"
do_image_wic[depends] += "virtual/bootloader:do_deploy"
