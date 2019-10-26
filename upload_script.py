################################################################################################
#
# This script is currently not used, but kept here as an example for options to influence upload
#
# all env-vairables are available with pio run --target envdump
#
################################################################################################

Import("env")

# please keep $SOURCE variable, it will be replaced with a path to firmware

# # Generic
# env.Replace(
#     UPLOADER="C:\\Users\\d019748\\.platformio\\packages\\tool-bossac\\bossac.exe",
#     UPLOADCMD="$UPLOADER $UPLOADERFLAGS -w $SOURCE"
# )

# # In-line command with arguments
# env.Replace(
#     UPLOADCMD="C:\\Users\\d019748\\.platformio\\packages\\tool-bossac\\bossac.exe -v -R -w $SOURCE"
# )

# Python callback
def on_upload(source, target, env):
    firmware_path = str(source[0])
    print("firmware_path {0}".format(firmware_path))
    print("UPLOADCMD: {0}, UPLOADPORT: {1}".format(env.Dump("UPLOADCMD"), "leer")) # env.Dump("UPLOADPORT"))) 
    # do something
    # env.Execute("executable arg1 arg2")
    
env.Replace(UPLOADCMD=on_upload)