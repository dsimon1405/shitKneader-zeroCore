#  Config/ZC_Config.h.in

#========================= ErrorLogger
#	types
set(ZC_EL_console 0)
set(ZC_EL_database 1)
set(ZC_EL_none 2)
#	define ZC_EL_type
if(ZC_ERROR_LOGGER_CONSOLE)
	set(ZC_EL_type ${ZC_EL_console})
elseif(ZC_ERROR_LOGGER_DATABASE)
	set(ZC_EL_type ${ZC_EL_database})
else()
	set(ZC_EL_type ${ZC_EL_none})
endif()

#========================= API
#	types
set(ZC_API_sdl 0)
set(ZC_API_android 1)
#	define ZC_API_type
if(ZC_API_SDL)
	set(ZC_API_type ${ZC_API_sdl})
elseif(ZC_API_ANDROID)
	set(ZC_API_type ${ZC_API_android})
endif()

#========================= make config file
configure_file(ZC_Config.h.in ZC_Config.h)