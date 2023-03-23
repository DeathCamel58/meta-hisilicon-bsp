# This is a generic Hisilicon SOC family. It is a superset of all other SOCs
# and platforms defined in meta-hisilicon to allow BSP-level overrides.
SOC_FAMILY = "hisilicon-soc"
KERNEL_DTB_OVERLAY_SUPPORT ?= "1"
require conf/machine/include/soc-family.inc
