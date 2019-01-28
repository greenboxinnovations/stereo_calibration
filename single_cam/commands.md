set cam-ip in ip.yml

./read_single cam_123/ left
./read_single cam_124/ right

./imagelist_creator left_list.yml cam_123/*.jpg
./imagelist_creator right_list.yml cam_124/*.jpg

./check_chessboard_single left_list.yml
./check_chessboard_single right_list.yml

./calibration_single -w=13 -h=9 -s=0.0172 -o=cam_123.yml -op -oe left_list.yml
./calibration_single -w=13 -h=9 -s=0.0172 -o=cam_124.yml -op -oe right_list.yml


./undistort_check cam_123.yml
./undistort_check cam_124.yml