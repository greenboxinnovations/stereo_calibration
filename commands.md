python3 rename_pics.py jan1
./imagelist_creator jan1_list.yml jan1/*.jpg
./check_chessboard jan1_list.yml
./stereo_calib2 -w=13 -h=9 -s=0.0172 jan1_list.yml 
