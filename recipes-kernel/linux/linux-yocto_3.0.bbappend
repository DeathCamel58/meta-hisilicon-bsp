# TODO: Check this
# Ref: https://docs.yoctoproject.org/kernel-dev/common.html
KBRANCH:K9604-W  = "standard/base"

# TODO: Figure out what to set this to
KMACHINE:K9604-W ?= "common-pc"

SRCREV_machine:K9604-W    ?= "02f8c6aee8df3cdc935e9bdd4f2d020306035dbe"

COMPATIBLE_MACHINE:K9604-W = "K9604-W"

LINUX_VERSION:K9604-W = "3.0"

# TODO: Add patches
SRC_URI += "file://patches/hi3520dv200/0001-Add-Linux-files-from-Hi3520D_SDK_V1.0.3.0.patch"
