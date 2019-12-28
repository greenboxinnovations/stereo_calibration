set cam-ip in ip.yml

./read_single cc4_123/ left
./read_single cc4_124/ right

./imagelist_creator cc4_123_list.yml cc4_123/*.jpg
./imagelist_creator cc4_124_list.yml cc4_124/*.jpg

./check_chessboard_single left_list.yml
./check_chessboard_single right_list.yml

./calibration_single -w=9 -h=6 -s=0.0272 -o=cc4_123left.yml -op -oe cc4_123_list.yml
./calibration_single -w=9 -h=6 -s=0.0272 -o=cc4_124right.yml -op -oe cc4_124_list.yml


./undistort_check cc4_123left.yml
./undistort_check cc4_124right.yml



ffplay -probesize 32 -sync ext rtsp://192.168.0.140:8554/live0.264
ffplay -probesize 32 -sync ext rtsp://192.168.0.123:554/Streaming/Channels/1/?transportmode=unicast