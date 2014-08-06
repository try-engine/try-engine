# Locate Horde3D library
#
# This module defines:
#
# Horde3D_FOUND, if false, do not try to link to Horde3D
# Horde3D_LIBRARY, the pathname of the main library to link against
# Horde3DUtils_LIBRARY, the pathname of the utility library to link against
# Horde3D_LIBRARIES, the full list of libs to link against
# Horde3D_INCLUDE_DIR, where to find Horde3D.h
# Horde3DUtils_INCLUDE_DIR, where to find Horde3DUtils.h
# Horde3D_INCLUDE_DIRS, where to find Horde3D.h and Horde3DUtils.h
#=============================================================================

FIND_PATH(Horde3D_INCLUDE_DIR Horde3D.h
	HINTS
	$ENV{HORDE3DDIR}
	PATH_SUFFIXES include/horde3d include/Horde3D include
	PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local/include/Horde3D
	/usr/include/Horde3D
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
)

#MESSAGE("Horde3D_INCLUDE_DIR is ${Horde3D_INCLUDE_DIR}")

FIND_PATH(Horde3DUtils_INCLUDE_DIR Horde3DUtils.h
    HINTS
    $ENV{HORDE3DDIR}
    PATH_SUFFIXES include/horde3d include/Horde3D include
    PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include/Horde3D
    /usr/include/Horde3D
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
)

#MESSAGE("Horde3DUtils_INCLUDE_DIR is ${Horde3DUtils_INCLUDE_DIR}")

FIND_LIBRARY(Horde3D_LIBRARY
	NAMES Horde3D
	HINTS
	$ENV{HORDE3DDIR}
	PATH_SUFFIXES lib64 lib
	PATHS
	/sw
	/usr
	/usr/local
	/opt/local
	/opt/csw
	/opt
)

#MESSAGE("Horde3D_LIBRARY is ${Horde3D_LIBRARY}")

FIND_LIBRARY(Horde3DUtils_LIBRARY
	NAMES Horde3DUtils
	HINTS
	$ENV{HORDE3DDIR}
	PATH_SUFFIXES lib64 lib
	PATHS
	/sw
	/usr
	/usr/local
	/opt/local
	/opt/csw
	/opt
)

#MESSAGE("Horde3DUtils_LIBRARY is ${Horde3DUtils_LIBRARY}")

SET(Horde3D_FOUND FALSE)

IF(Horde3D_LIBRARY)
    
    SET(Horde3D_LIBRARIES ${Horde3D_LIBRARY} ${Horde3DUtils_LIBRARY} CACHE STRING "All the libs required to link Horde3D")
    SET(Horde3D_INCLUDE_DIRS ${Horde3D_INCLUDE_DIR} ${Horde3DUtils_INCLUDE_DIR})

    # Set the final strings here so the GUI reflects the final state.
    SET(Horde3D_LIBRARY ${Horde3D_LIBRARY} CACHE STRING "Where the Horde3D Main Library can be found")
    SET(Horde3DUtils_LIBRARY ${Horde3DUtils_LIBRARY} CACHE STRING "Where the Horde3D Utility Library can be found")

    SET(Horde3D_FOUND TRUE)

    #MESSAGE("Horde3D_LIBRARIES is ${Horde3D_LIBRARIES}")

ENDIF(Horde3D_LIBRARY)

MESSAGE("-- Found Horde3D: ${Horde3D_FOUND}")
