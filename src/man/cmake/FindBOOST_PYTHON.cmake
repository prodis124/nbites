
##
# Includes
##

INCLUDE( ${CMAKE_MODULE_PATH}/base_definitions.cmake )

##
# Clear variables/caches
##

SET( BOOST_PYTHON_DEFINITIONS "" )
SET( BOOST_PYTHON_INCLUDE_DIR "PYTHON_INCLUDE_DIR-NOT-FOUND" CACHE FILEPATH "Cleared." FORCE)
SET( BOOST_PYTHON_LIBRARIES "PYTHON_LIBRARIES-NOT-FOUND" CACHE FILEPATH "Cleared." FORCE)

##
# Defined package variable
##

SET( BOOST_PYTHON_LIBRARIES ${OE_CROSS_DIR}/staging/geode-linux/usr/lib/libboost_python-mt.so)
SET( BOOST_PYTHON_INCLUDE_DIR ${OE_CROSS_DIR}/staging/geode-linux/usr/include)

IF( BOOST_PYTHON_INCLUDE_DIR AND BOOST_PYTHON_LIBRARIES )
  IF ( EXISTS BOOST_PYTHON_INCLUDE_DIR AND EXISTS BOOST_PYTHON_LIBRARIES )
    SET( BOOST_PYTHON_FOUND TRUE )
  ENDIF ( EXISTS BOOST_PYTHON_INCLUDE_DIR AND EXISTS BOOST_PYTHON_LIBRARIES )
ENDIF( BOOST_PYTHON_INCLUDE_DIR AND BOOST_PYTHON_LIBRARIES )

IF( NOT BOOST_PYTHON_FOUND AND BOOST_PYTHON_FIND_REQUIRED )
  IF( NOT BOOST_PYTHON_INCLUDE_DIR OR NOT EXISTS ${BOOST_PYTHON_INCLUDE_DIR} )
    MESSAGE( STATUS "Required include not found" )
    MESSAGE( FATAL_ERROR "Could not find BOOST_PYTHON include!" )
  ENDIF( NOT BOOST_PYTHON_INCLUDE_DIR OR NOT EXISTS ${BOOST_PYTHON_INCLUDE_DIR} )
  IF( NOT BOOST_PYTHON_LIBRARIES OR NOT EXISTS ${BOOST_PYTHON_LIBRARIES} )
    MESSAGE( STATUS "Required libraries not found" )
    MESSAGE( FATAL_ERROR "Could not find BOOST_PYTHON libraries!" )
  ENDIF( NOT BOOST_PYTHON_LIBRARIES OR NOT EXISTS ${BOOST_PYTHON_LIBRARIES} )
ENDIF( NOT BOOST_PYTHON_FOUND AND BOOST_PYTHON_FIND_REQUIRED )

# Finally, display informations if not in quiet mode
IF( NOT BOOST_PYTHON_FIND_QUIETLY )
  MESSAGE( STATUS "BOOST_PYTHON found " )
  MESSAGE( STATUS "  includes   : ${BOOST_PYTHON_INCLUDE_DIR}" )
  MESSAGE( STATUS "  libraries  : ${BOOST_PYTHON_LIBRARIES}" )
  MESSAGE( STATUS "  definitions: ${BOOST_PYTHON_DEFINITIONS}" )
ENDIF( NOT BOOST_PYTHON_FIND_QUIETLY )



MARK_AS_ADVANCED(
  BOOST_PYTHON_DEFINITIONS
  BOOST_PYTHON_INCLUDE_DIR
  BOOST_PYTHON_LIBRARIES
)
