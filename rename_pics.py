import sys
import os


if(len(sys.argv) != 2):
	print("Usage:\npython3 rename_pics.py <dir>")
	quit()

path = sys.argv[1]

for f in os.listdir(path):
	filename, file_extention = os.path.splitext(f)
	
	if "left" in filename:
		num = filename.replace("left","")
		newfile = num+"l"+file_extention
		print(newfile)
		os.rename(os.path.join(path,f),os.path.join(path,newfile))
	elif "right" in filename:
		num = filename.replace("right","")
		newfile = num+"r"+file_extention
		print(newfile)
		os.rename(os.path.join(path,f),os.path.join(path,newfile))
