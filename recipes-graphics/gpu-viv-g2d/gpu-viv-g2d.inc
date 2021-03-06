# Copyright (C) 2013, 2014 Freescale Semiconductor

DESCRIPTION = "GPU Vivante G2D library and sample applications for imx6"
SECTION = "libs"
LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://usr/include/g2d.h;endline=7;md5=53b61e015f8e1c386057c5ba8b081d53"

PROVIDES += "virtual/libg2d"

PACKAGES = "${PN} ${PN}-dev ${PN}-dbg"

inherit fsl-eula-unpack

PE = "1"

# FIXME: Drop 'beta' suffix for GA release
SRC_URI = "${FSL_MIRROR}/${PN}-${@'${PV}'.replace('1.1.0', '1.1.0-beta')}.bin;fsl-eula=true"
S = "${WORKDIR}/${PN}-${@'${PV}'.replace('1.1.0', '1.1.0-beta')}"

PACKAGES += "libg2d"

# Inhibit warnings about files being stripped.
INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

do_install () {
    install -d ${D}${libdir}
    install -d ${D}${includedir}

    cp ${S}/usr/lib/*.so ${D}${libdir}
    cp -Pr ${S}/usr/include/* ${D}${includedir}
    cp -Pr ${S}/opt ${D}

    find ${D}${libdir} -type f -exec chmod 644 {} \;
    find ${D}${includedir} -type f -exec chmod 644 {} \;
}

# FIXME: The provided binary doesn't provide soname. If in future BSP
# release the libraries are fixed, we can drop this hack.
REALSOLIBS := "${SOLIBS}"
SOLIBS = "${SOLIBSDEV}"

FILES_${PN} = "/opt"
FILES_libg2d =  "${libdir}/libg2d-viv${SOLIBS} ${libdir}/libg2d${SOLIBS}"
FILES_${PN}-dev = "${includedir}"

COMPATIBLE_MACHINE = "(mx6)"
