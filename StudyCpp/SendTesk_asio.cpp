#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include<string>
#include<io.h>

using namespace std;
using boost::asio::ip::udp;

void getAllFiles(string path, vector<string>& files);

int main()
{
	try
	{
		string path = "F:\\Image_LIB\\Tire_src\\first_line\\200_2";

		vector<string> files;
		getAllFiles(path, files);

		boost::asio::io_context io_context;

		udp::resolver resolver(io_context);
		udp::endpoint receiver_endpoint =
			*resolver.resolve(udp::v4(), "localhost", "7777").begin();
		udp::socket socket(io_context);
		socket.open(udp::v4());

		for (size_t i = 0; i < files.size(); i++)
		{
			try {
				string file = files[i];
				std::cout << file << std::endl;
				socket.send_to(boost::asio::buffer(file), receiver_endpoint);
			}
			catch (std::exception& e) {
				std::cerr << e.what() << std::endl;
			}

			boost::asio::steady_timer t(io_context, boost::asio::chrono::seconds(2));
			t.wait();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

void getAllFiles(string path, vector<string>& files) {
	long long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			string fileName(fileinfo.name);
			if (fileName.length() < 3) {
				continue;
			}
			files.push_back(p.assign(path).append("\\").append(fileinfo.name));
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}