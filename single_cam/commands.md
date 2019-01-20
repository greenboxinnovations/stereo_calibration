./read_single kasat_left/ left
./read_single kasat_right/ right

./imagelist_creator left_list.yml kasat_left/*.jpg
./imagelist_creator right_list.yml kasat_right/*.jpg

./check_chessboard_single left_list.yml
./check_chessboard_single right_list.yml

./calibration_single -w=13 -h=9 -s=0.0172 -o=kasat_left.yml -op -oe left_list.yml
./calibration_single -w=13 -h=9 -s=0.0172 -o=kasat_right.yml -op -oe right_list.yml


./undistort_check kasat_left.yml
./undistort_check kasat_right.yml