all:
	mkdir robot &2>/dev/null
	javac -cp robot Robot.java
	mv *.class robot/
	jar cfe Robot.jar robot.Robot robot/*.class

runImage:
	java -jar Robot.jar localhost 1000

runFirmware:
	java -jar Robot.jar localhost 1000 ./firmware.bin
