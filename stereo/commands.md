set cam-ip in ip.yml

./read_stereo stereo_dir1/
./imagelist_creator stereo_list.yml stereo_dir1/*.jpg 
./stereo_calib2 -w=13 -h=9 -s=0.0172 stereo_list.yml 





./imagelist_creator stereo_list.yml test/*.jpg
