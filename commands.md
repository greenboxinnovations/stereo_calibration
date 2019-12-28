python3 rename_pics.py jan1
./imagelist_creator jan1_list.yml jan1/*.jpg
./check_chessboard jan1_list.yml
./stereo_calib3 -w=9 -h=6 -s=0.0027 jan1_list.yml 
