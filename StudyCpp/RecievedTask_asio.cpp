#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main()
{
	boost::asio::io_context io_context;

	udp::endpoint send_endpoint(udp::v4(), 7777);
	udp::socket socket(io_context);
	socket.open(udp::v4());
	socket.bind(send_endpoint);
	boost::array<char, 1024> recvBuffer;

	while (true)
	{
		size_t len = socket.receive_from(boost::asio::buffer(recvBuffer), send_endpoint);
		std::string key(recvBuffer.data(), len);
		std::cout << key << std::endl;
	}
	return 0;
}