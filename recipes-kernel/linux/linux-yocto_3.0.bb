# SPDX-License-Identifier: MIT
#
# Created by Dylan Corrales <deathcamel57@gmail.com>
# This is the OEM kernel. Old and outdated!
#

DESCRIPTION = "Linux kernel for the Hisilicon SoCs"
SECTION = "kernel"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

# Use folder specific to this kernel for patches
FILESEXTRAPATHS:prepend := "${THISDIR}/kernel-3.0:"

require recipes-kernel/linux/linux-yocto.inc

# Set the machine this is compatible with
COMPATIBLE_MACHINE = "k9604-w"

# All versions of linux use `master` branch
KBRANCH ?= "master"

# Commit SHA hash for v3.0
SRCREV:k9604-w = "02f8c6aee8df3cdc935e9bdd4f2d020306035dbe"

# Kernel repository
SRC_URI = "git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git;protocol=git;branch=${KBRANCH}"

# Custom Patches
SRC_URI += " \
    file://0001-Add-Linux-files-from-Hi3520D_SDK_V1.0.3.0.patch \
    file://defconfig \
"

