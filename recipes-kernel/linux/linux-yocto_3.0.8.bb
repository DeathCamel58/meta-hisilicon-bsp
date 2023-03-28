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
FILESEXTRAPATHS:prepend := "${THISDIR}/kernel-3.0.8:"

require recipes-kernel/linux/linux-yocto.inc

# Set the machine this is compatible with
COMPATIBLE_MACHINE = "k9604-w"

KBRANCH ?= "linux-3.0.y"

# Commit SHA hash for v3.0.8
# This was found at https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/commit/?h=linux-3.0.y&id=97596c34030ed28657ccafddb67e17a03890b90a
SRCREV:k9604-w = "97596c34030ed28657ccafddb67e17a03890b90a"

# Kernel repository
SRC_URI = "git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git;protocol=git;branch=${KBRANCH}"

# Custom Patches
SRC_URI += " \
    file://0001-Add-Linux-files-from-Hi3520D_SDK_V1.0.3.0.patch \
    file://defconfig \
"

