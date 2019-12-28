set cam-ip in ip.yml

./read_stereo chinese_cam/
./read_stereo cc4/
./imagelist_creator cc4_list.yml cc4/*.jpg 
./stereo_calib4 -w=9 -h=6 -s=0.0272 cc4_list.yml
<!-- ./stereo_calib3 -w=11 -h=7 -s=0.086 chinese_list2.yml -->


<!-- ./imagelist_creator chinese_list.yml test/*.jpg -->



ffplay -probesize 32 -sync ext rtsp://192.168.0.140:8554/live0.264
