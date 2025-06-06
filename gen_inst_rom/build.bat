@echo off
cls

echo ====================  BUILD  ====================

set compiler_warnings=/WX /W4 /WL /wd4201 /wd4100 /wd4189 /wd4505 /wd4127 /wd4115 /wd4456 /wd4457 /wd4244 /wd4245 /wd4701 /wd4310 /wd4471 /wd4551
set compiler_defs=/D_CRT_SECURE_NO_WARNINGS /Od /Zo /Z7 /DDEBUG
set compiler_flags=%compiler_defs% %compiler_warnings% /std:c++20 /nologo /diagnostics:column /fp:fast /fp:except- /GR- /FC /GS- /EHsc /MDd /Zc:strictStrings- /Isrc\

set linker_flags=/INCREMENTAL:NO /OPT:REF
set linker_libs=

pushd Z:\computer\gen_inst_rom
IF NOT EXIST .\build mkdir .\build
IF NOT EXIST .\bin mkdir .\bin

cl %compiler_flags% src\main.cc /Fobuild\ /Fmbuild\ /Fdbuild\ /Febin\^
 /link %linker_flags% %linker_libs% /SUBSYSTEM:console

popd
