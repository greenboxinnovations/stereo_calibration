./read_stereo stereo_dir_new/
./imagelist_creator stereo_list_new.yml stereo_dir_new/*.jpg 
./stereo_calib3 -w=9 -h=6 -s=0.0272 stereo_list_new.yml
./imagelist_creator stereo_list_new.yml test/*.jpg



./stereo_calib4 -w=9 -h=6 -s=0.0272 stereo_list_new.yml


old

done with RMS error=0.762175
average epipolar err = 1.09799


initcameramatrix
done with RMS error=2.50776
average epipolar err = 2.34376