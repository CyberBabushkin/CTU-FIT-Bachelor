all:
	mkdir tcp &2>/dev/null
	javac -cp tcp TCPServer.java
	mv *.class tcp/
	jar cfe TCPServer.jar tcp.TCPServer tcp/*.class

run:
	java -jar TCPServer.jar