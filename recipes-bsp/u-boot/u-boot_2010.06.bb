# SPDX-License-Identifier: MIT
#
# Created by Dylan Corrales <deathcamel57@gmail.com>
#

HOMEPAGE = "http://www.denx.de/wiki/U-Boot/WebHome"
DESCRIPTION = "U-Boot, a boot loader for Embedded boards based on PowerPC, \
ARM, MIPS and several other processors, which can be installed in a boot \
ROM and used to initialize and test the hardware or to download and run \
application code."
SECTION = "bootloaders"
DEPENDS += "flex-native bison-native"

LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://Licenses/README;md5=2ca5f2c35c8cc335f0a19756634782f1"
PE = "1"

# Use folder specific to this U-Boot version for patches
FILESEXTRAPATHS:prepend := "${THISDIR}/u-boot-2010.06:"

require recipes-bsp/u-boot/u-boot-common.inc
require recipes-bsp/u-boot/u-boot.inc

# Commit SHA hash for 2010.06
SRCREV = "a59e27997637a2395ae2cc7f809127f24119a167"

# U-Boot repository
SRC_URI = "git://source.denx.de/u-boot/u-boot.git;protocol=https;branch=master"

# Custom Patches
SRC_URI += " \
    file://0001-Add-U-Boot-files-from-Hi3520D_SDK_V1.0.3.0.patch \
"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

inherit pkgconfig

do_configure[cleandirs] = "${B}"
