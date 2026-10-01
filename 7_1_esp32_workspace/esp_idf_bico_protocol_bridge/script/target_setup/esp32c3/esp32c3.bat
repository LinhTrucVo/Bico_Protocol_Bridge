
@echo off
@REM This is generated file, do not edit it manually
call "D:\vor5hc\.espressif\v5.4.3\esp-idf\export.bat"
idf.py set-target esp32c3
idf.py fullclean
idf.py build
idf.py flash monitor
