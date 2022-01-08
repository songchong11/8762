@echo off
set linker_output_file_name=%1

:: without secure boot
 .\flash_download\hex\srec_cat "bin\%linker_output_file_name%.bin" -binary -offset 0x80D000 -o "flash_download\hex\%linker_output_file_name%.hex" -intel

:: with secure boot
:: .\flash_download\hex\srec_cat "bin\%linker_output_file_name%.bin" -binary -offset 0x811000 -o "flash_download\hex\%linker_output_file_name%.hex" -intel