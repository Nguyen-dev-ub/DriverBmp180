cmd_/home/pi/Documents/bmp180/driverbmp180.mod := printf '%s\n'   driverbmp180.o | awk '!x[$$0]++ { print("/home/pi/Documents/bmp180/"$$0) }' > /home/pi/Documents/bmp180/driverbmp180.mod
