DESCRIPTION = "Linux Kernel"
SECTION = "kernel"
LICENSE = "GPLv2"

LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

inherit kernel siteinfo
require recipes-kernel/linux/linux-yocto.inc

# Enable OABI compat for people stuck with obsolete userspace
ARM_KEEP_OABI ?= "1"

# Quirk for udev greater or equal 141
UDEV_GE_141 ?= "1"

# Set the verbosity of kernel messages during runtime
# You can define CMDLINE_DEBUG in your local.conf or distro.conf to override this behaviour
CMDLINE_DEBUG ?= '${@base_conditional("DISTRO_TYPE", "release", "quiet", "debug", d)}'
#CMDLINE_append = " ${CMDLINE_DEBUG}"

# Set a variable in .configure
# $1 - Configure variable to be set
# $2 - value [n/y/value]
kernel_configure_variable() {
	# Remove the config
	CONF_SED_SCRIPT="$CONF_SED_SCRIPT /CONFIG_$1[ =]/d;"
	if test "$2" = "n"
	then
		echo "# CONFIG_$1 is not set" >> ${B}/.config
	else
		echo "CONFIG_$1=$2" >> ${B}/.config
	fi
}

do_configure_prepend() {
	# Clean .config
	echo "" > ${B}/.config
	CONF_SED_SCRIPT=""

	# oabi / eabi support
	if [ "${TARGET_OS}" = "linux-gnueabi" -o  "${TARGET_OS}" = "linux-uclibceabi" ]; then
		kernel_configure_variable AEABI y
		if [ "${ARM_KEEP_OABI}" = "1" ] ; then
			kernel_configure_variable OABI_COMPAT y
		else
			kernel_configure_variable OABI_COMPAT n
		fi
	else
		kernel_configure_variable AEABI n
		kernel_configure_variable OABI_COMPAT n
	fi

	# Set cmdline
	kernel_configure_variable CMDLINE "\"${CMDLINE}\""

	# Localversion
	kernel_configure_variable LOCALVERSION "\"\""
	kernel_configure_variable LOCALVERSION_AUTO n

	# Udev quirks
	# Newer versions of udev mandate that sysfs doesn't have deprecated entries
	if [ "${UDEV_GE_141}" = "1" ] ; then
		kernel_configure_variable SYSFS_DEPRECATED n
		kernel_configure_variable SYSFS_DEPRECATED_V2 n
		kernel_configure_variable HOTPLUG y
		kernel_configure_variable UEVENT_HELPER_PATH "\"\""
		kernel_configure_variable UNIX y
		kernel_configure_variable SYSFS y
		kernel_configure_variable PROC_FS y
		kernel_configure_variable TMPFS y
		kernel_configure_variable INOTIFY_USER y
		kernel_configure_variable SIGNALFD y
		kernel_configure_variable TMPFS_POSIX_ACL y
		kernel_configure_variable BLK_DEV_BSG y
		kernel_configure_variable DEVTMPFS y
		kernel_configure_variable DEVTMPFS_MOUNT y
	fi

	# Newer inits like systemd need cgroup support
	if [ "${KERNEL_ENABLE_CGROUPS}" = "1" ] ; then
		kernel_configure_variable CGROUP_SCHED y
		kernel_configure_variable CGROUPS y
		kernel_configure_variable CGROUP_NS y
		kernel_configure_variable CGROUP_FREEZER y
		kernel_configure_variable CGROUP_DEVICE y
		kernel_configure_variable CPUSETS y
		kernel_configure_variable PROC_PID_CPUSET y
		kernel_configure_variable CGROUP_CPUACCT y
		kernel_configure_variable RESOURCE_COUNTERS y
	fi

	# root-over-nfs-over-usb-eth support. Limited, but should cover some cases
	# Enable this by setting a proper CMDLINE_NFSROOT_USB.
	if [ ! -z "${CMDLINE_NFSROOT_USB}" ]; then
		oenote "Configuring the kernel for root-over-nfs-over-usb-eth with CMDLINE ${CMDLINE_NFSROOT_USB}"
		kernel_configure_variable INET y
		kernel_configure_variable IP_PNP y
		kernel_configure_variable USB_GADGET y
		kernel_configure_variable USB_GADGET_SELECTED y
		kernel_configure_variable USB_ETH y
		kernel_configure_variable NFS_FS y
		kernel_configure_variable ROOT_NFS y
		kernel_configure_variable ROOT_NFS y
		kernel_configure_variable CMDLINE "\"${CMDLINE_NFSROOT_USB}\""
	fi

	# Activate CONFIG_LEGACY_PTYS
	kernel_configure_variable LEGACY_PTYS y

	# Keep this the last line
	# Remove all modified configs and add the rest to .config
	sed -e "${CONF_SED_SCRIPT}" < '${WORKDIR}/defconfig' >> '${B}/.config'

	yes '' | oe_runmake oldconfig
}

# Automatically depend on lzop-native if CONFIG_KERNEL_LZO is enabled
python () {
    try:
        defconfig = bb.fetch2.localpath('file://defconfig', d)
    except bb.fetch2.FetchError:
        return

    try:
        configfile = open(defconfig)
    except IOError:
        return

    if 'CONFIG_KERNEL_LZO=y\n' in configfile.readlines():
        depends = d.getVar('DEPENDS', False)
        d.setVar('DEPENDS', depends + ' lzop-native')
}
