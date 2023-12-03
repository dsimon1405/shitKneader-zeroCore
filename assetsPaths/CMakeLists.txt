#  Config/ZC_Config.h.in

if(WIN32)
    set(SK_SLESH \\\\)
else()
    set(SK_SLESH /)
endif()

#   sounds
set(SK_Path_sounds_lp sounds${SK_SLESH}lp.wav)
set(SK_Path_sounds_Airplanes sounds${SK_SLESH}Airplanes.wav)

#   shaders
set(SK_Path_shaders_testVS shaders${SK_SLESH}test.vs)
set(SK_Path_shaders_testFS shaders${SK_SLESH}test.fs)

# #========================= make config file
configure_file(SK_AssetsPaths.h.in ${PROJECT_BINARY_DIR}/assetsPaths/SK_AssetsPaths.h)