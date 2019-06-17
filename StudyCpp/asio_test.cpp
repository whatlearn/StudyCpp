#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main()
{
	try
	{
		boost::asio::io_context io_context;

		udp::resolver resolver(io_context);
		udp::endpoint receiver_endpoint =
			*resolver.resolve(udp::v4(), "127.0.0.1", "7777").begin();

		udp::socket socket(io_context);
		socket.open(udp::v4());

		for (;;)
		{
			std::string send_buf = "zhangqi";
			socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);
			std::cout << send_buf << std::endl;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}