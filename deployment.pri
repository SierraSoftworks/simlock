# checksum 0xfb0c version 0x30001
# This file was generated by an application wizard of Qt Creator.
# The code below handles deployment to Symbian and Maemo, aswell as copying
# of the application data to shadow build directories on desktop.
# It is recommended not to modify this file, since newer versions of Qt Creator
# may offer an updated version of it.

defineTest(qtcAddDeployment) {
for(deploymentfolder, DEPLOYMENTFOLDERS) {
    item = item$${deploymentfolder}
    itemsources = $${item}.sources
    $$itemsources = $$eval($${deploymentfolder}.source)
    itempath = $${item}.path
    $$itempath= $$eval($${deploymentfolder}.target)
    export($$itemsources)
    export($$itempath)
    DEPLOYMENT += $$item
}

MAINPROFILEPWD = $$PWD

unix {
    maemo5 {
	installPrefix = /opt/simlock
    }
    for(deploymentfolder, DEPLOYMENTFOLDERS) {
	item = item$${deploymentfolder}
	itemfiles = $${item}.files
	$$itemfiles = $$eval($${deploymentfolder}.source)
	itempath = $${item}.path
	$$itempath = $${installPrefix}/$${TARGET}/$$eval($${deploymentfolder}.target)
	export($$itemfiles)
	export($$itempath)
	INSTALLS += $$item
    }
    target.path = $${installPrefix}
    eventScript.path = /etc/event.d
    eventScript.files = $${TARGET}
    export(target.path)
    export(eventScript.files)
    export(eventScript.path)
    INSTALLS += target eventScript
}

export (ICON)
export (INSTALLS)
export (DEPLOYMENT)
export (TARGET.EPOCHEAPSIZE)
export (TARGET.CAPABILITY)
export (LIBS)
export (QMAKE_EXTRA_TARGETS)
}
