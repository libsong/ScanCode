Windows Driver v4.20 Release Notes
Copyright (C) 2006 Silicon Laboratories, Inc.

This release contains the following components:

* unin98.exe
* uninstall.exe
* unin98.ini
* uninstall.ini
* slabbus.cat
* slabser.cat
* slabbus.inf
* slabvxd.inf
* slabw2k.inf
* slabwdm.inf
* slabbus.sys
* slabcm95.sys
* slabcmnt.sys
* slabcr.sys
* slabser.sys
* slabwh95.sys
* slabwhnt.sys
* slabcomm.vxd
* slabvcd.vxd
* slabvcr.vxd
* Readme.txt (this file)


Driver Installation
-------------------

	See Evaluation Kit User's Guide for installation instructions.


FOURSTAR Windows Driver Revision History
--------------------------------------

Version 4.20

	New features/Enhancements
	-------------------------

	Changed driver binary file names from cyg_* to slab*.  Also changed 
	default inf file strings to SLAB and Silicon Laboratories.

	This installation includes catalog files for Windows 2000/XP Windows 
	Hardware Quality Lab (WHQL) Certification.

	
	Corrections
        -----------

	Modified behavior of SERIAL_EV_TXEMPTY event notification.  Applications 
	will no longer miss TXEMPTY events if a	write is pending during the 
	IOCTL_SERIAL_WAIT_ON_MASK control request.


Version 4.16

	New features/Enhancements
	-------------------------
	
	Corrections
        -----------

	Changed behavior for IOCTL_SERIAL_LSRMST_INSERT for correct modem 
	event insertion.


Version 4.09
	
	Initial Release


