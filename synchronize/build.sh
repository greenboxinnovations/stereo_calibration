# #!/bin/bash
if [ $# -eq 0 ]
	then
		echo "No arguments supplied"
	else
		if [ -z "$2" ]
			then
				a=$(basename $1 .cpp)
				# g++ -std=c++0x $1 -o $a `pkg-config --cflags --libs opencv ` -lpthread  -lmysqlcppconn
				# ADDED VLC AND VLC CAP HELPER CLASS IN COMPILER				
				g++ -std=c++0x -g -Wall -w $1 -o $a -I/home/greenbox/ffmpeg_sources/ffmpeg/ `pkg-config --cflags --libs opencv4 libvlc` -lpthread  -lmysqlcppconn -lavformat -lavcodec -lavutil -lswscale
			else
				# g++ -std=c++0x $1 -o $2 `pkg-config --cflags --libs opencv` -lpthread  -lmysqlcppconn
				g++ -std=c++0x $1 -o $2 `pkg-config --cflags --libs opencv libvlc` -lpthread  -lmysqlcppconn
		fi 	
  	# g++ -std=c++0x $1 -o app `pkg-config --cflags --libs opencv` -lpthread  -lmysqlcppconn
fi

echo Done!
