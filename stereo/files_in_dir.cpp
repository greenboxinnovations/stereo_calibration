#include <string>
#include <iostream>
// #include <filesystem>
// namespace fs = std::filesystem;

#include <experimental/filesystem>

// for brevity
namespace fs = std::experimental::filesystem;



#include <boost/algorithm/string.hpp> // include Boost, a C++ library



int nextPhotoIndex(std::string folder){

	int max_int = 0;	
	int temp_int = 0;
	try {
		std::string path = "/home/greenbox-desktop/Desktop/desktop/stereo_calibration/stereo/"+folder;
		for (const auto & entry : fs::directory_iterator(path)){

			std::string path_string = entry.path().u8string();
			boost::replace_all(path_string, path, "");		
			boost::replace_all(path_string, ".jpg", "");
			boost::replace_all(path_string, "/", "");
			boost::replace_all(path_string, "l", "");
			boost::replace_all(path_string, "r", "");
			std::cout << path_string << std::endl;
			temp_int = std::stoi(path_string);

			if(temp_int >= max_int){
				max_int = temp_int;
				max_int++;
			}			
		}
	}catch (...) {}

	if(max_int == 0){
		max_int = 1;
	}

	return max_int;
}


int main()
{
	
	// std::string path = "/home/greenbox-desktop/Desktop/desktop/stereo_calibration/stereo/chinese_cam";
	// for (const auto & entry : fs::directory_iterator(path)){
	// 	std::string path_string = entry.path().u8string();
 //    	// path_string = entry.path().u8string();


 //    	// directory
	// 	// std::cout << path_string.substr(0, path_string.find_last_of("\\/")) << std::endl;

 //    	// file
	// 	//std::cout << path_string.substr(path_string.find_last_of("\\/"), path_string.length()) << std::endl;
	// 	boost::replace_all(path_string, path, "");		
	// 	boost::replace_all(path_string, ".jpg", "");
	// 	boost::replace_all(path_string, "/", "");
	// 	boost::replace_all(path_string, "l", "");
	// 	boost::replace_all(path_string, "r", "");
	// 	std::cout << path_string << std::endl;

	// }


	std::cout << nextPhotoIndex("chinese_cam2") << std::endl;


	// std::string target("Would you like a foo of chocolate. Two foos of chocolate?");
	// boost::replace_all(target, "foo", "bar");
	// std::cout << target << std::endl;

}